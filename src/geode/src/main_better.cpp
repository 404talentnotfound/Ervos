#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <iostream>
#include "serial_library/include/SerialPort.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <thread>

using namespace geode::prelude;

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

// global variable to keep track of the size of the current macro
int msize = 0;

// this is a text file that contains the usb port you plug the arduino into.
const char* portfile_name = "C:\\macros\\port.txt";
const char* swiftclickfile_name = "C:\\macros\\swift.txt";

// amount of bytes for messages sent to the arduino
#define MAX_DATA_LENGTH 1

/*
this variable keeps track of if a macro should be played, so that if you want to play it won't start moving the servos.
it's also used for checking if the serial port is open, rather than sending a message when it's closed and crashing the game.
*/
bool activated = false;
SerialPort *arduino;

// this variable is used to check if the macro should continue being played, so if you pause or exit a level it won't keep going.
bool should_play = true;

int framecount = 0;

float fps = 240;

gd::string current_level;

int swiftclick;

/*
get macro from the C:\\macros directory, using the name of the level being played to find the file.
a macro from this directory will have the name [levelname].soup and the format works as follows (annotations are written in parentheses like done here).

example.soup:
100 (size of the macro, this line is at the start of every file and is done to simplify the function and make it more efficient. NOTE: this is not the line count, as every click/release uses two lines)
1 (input key, this is to specify what button needs to be pressed. 1 = jump, 2 = move left, 3 = move right)
50 (frame, this line specifies which frame the input key needs to be pressed. NOTE: a frame is essentially an update of the physics or rendering engine. rather than when using milliseconds as a delay, if the game starts to run slower, using frames can account for the slowdown)
2 (input key)
67 (frame)
(etc..)
*/
vector<vector<int>> get_macro(gd::string level_name) {
    ifstream macro_file;
    vector<vector<int>> readable_macro;
    int macro_size;
    int input;
    int frame;
    int repetitions;
    stringstream file;
    std::string name = level_name.c_str();
    file << "C:\\macros\\" << name << ".soup";

	ifstream swiftclickfile;
	swiftclickfile.open(swiftclickfile_name);
	swiftclickfile >> swiftclick;

    macro_file.open(file.str());
    macro_file >> macro_size;
    msize = macro_size;
    for (int i = 0; i < macro_size; i++) {
        macro_file >> input;
        macro_file >> frame;
        macro_file >> repetitions;
        readable_macro.push_back({input, frame, repetitions});
    }
    macro_file.close();
    msize = readable_macro.size();
    return readable_macro;
}


void play_macro(vector<vector<int>> macro) {
	if (activated) {
		for (int i = 0; i < macro.size(); i++) {
			// wait until the frame of the next instruction
			while (PlayLayer::get()->m_gameState.m_currentProgress < macro[i][1] && should_play);

			if (should_play) {
				if (macro[i][0] == 1) arduino->writeSerialPort("1", MAX_DATA_LENGTH);
				else if (macro[i][0] == 2) {
					for (int j = 0; j < macro[i][2]; j++) {
						arduino->writeSerialPort("1", MAX_DATA_LENGTH);
						auto time = std::chrono::steady_clock::now();
						while (std::chrono::steady_clock::now() - time < microseconds(swiftclick)) continue;
						arduino->writeSerialPort("1", MAX_DATA_LENGTH);
					}
				}
			}
			else {
				break;
			}
		}
	}
}

// this class modifies the menu layer of the game, when you open the game you start at the menu layer.
class $modify(MenuLayer) {
	// this void gets called when you press the more games button at the bottom right of the menu layer, i made this button open and close the serial port so i can easily toggle between me and the servos playing.
	void onMoreGames(CCObject*) {
		if (!activated) {
			ifstream portfile;
			portfile.open(portfile_name);
			
			std::string portname;
			portfile >> portname;
			arduino = new SerialPort(portname.c_str());

			// wait for connection to be established before sending a message.
			sleep_for(milliseconds(100));
			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			arduino->closeSerial();
		}
		activated = !activated;
	}
};

class $modify(PlayerObject) {
	// this function gets called when the player dies, i'm using it to reset the playthrough.
	void playerDestroyed(bool p0) {
		if (activated) {
			should_play = false;

			framecount = 0;

			// this creates a thread to reset the position of the servos. the sleep_for is there to keep the message from being sent at the exact same time as a click/release, as that would cause the servos to move weirdly or not move at all.
			std::thread restart_thread = std::thread{[]{ sleep_for(milliseconds(50)); arduino->writeSerialPort("6", MAX_DATA_LENGTH); }};

			// this detaches the thread from the main thread so it gets terminated when finished. not calling this crashes the game.
			restart_thread.detach();
		}
	}
};

// this class modifies the layer of a level
class $modify(PlayLayer) {
	// this function gets called when a level is completed.
	void levelComplete() {
		if (activated) {
			PlayLayer::levelComplete();

			should_play = false;

			framecount = 0;

			std::thread restart_thread = std::thread{[]{ sleep_for(milliseconds(50)); arduino->writeSerialPort("6", MAX_DATA_LENGTH); }};
			restart_thread.detach();
		}
		else {
			PlayLayer::levelComplete();
		}
	}

	void resetLevel() {
		if (activated) {
			PlayLayer::resetLevel();

			// set the level name variable to the one being played
			current_level = PlayLayer::get()->m_level->m_levelName;

			should_play = true;

			framecount = 0;

			std::thread play_thread = std::thread{[&]{ play_macro(get_macro(current_level)); }};
			play_thread.detach();
		}
		else {
			PlayLayer::resetLevel();
		}
	}

	void onQuit() {
		if (activated) {
			PlayLayer::onQuit();

			should_play = false;

			framecount = 0;
		}
		else {
			PlayLayer::onQuit();
		}
	}

	// this function gets called when a level gets paused.
	void pauseGame(bool p0) {
		if (activated) {
			PlayLayer::pauseGame(p0);

			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			PlayLayer::pauseGame(p0);
		}
	}
};