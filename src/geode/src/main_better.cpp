#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <iostream>
#include "serial_library/include/SerialPort.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>

using namespace geode::prelude;

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

std::thread play_thread;

// global variable to keep track of the size of the current macro
int msize = 0;

// amount of bytes for messages sent to the arduino
#define MAX_DATA_LENGTH 1

// this is a text file that contains the usb port you plug the arduino into.
const char* portfile_name = "C:\\macros\\port.txt";

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
	stringstream file;
	std::string name = level_name.c_str();
	file << "C:\\macros\\" << name << ".soup";

	// if a macro for a level can't be found, it opens backup.soup. this is just to prevent crashes.
	if (!filesystem::exists(file.str())) {
		macro_file.open("C:\\macros\\backup.soup");
		macro_file >> macro_size;
		msize = macro_size;
		for(int i = 0; i < macro_size; i++) {
			macro_file >> input;
			macro_file >> frame;
			readable_macro.push_back({input, frame});
		}
		macro_file.close();
		msize = readable_macro.size();

		return readable_macro;
	}

	// since the previous if statement ends with a return, an else statement is not needed.
	macro_file.open(file.str());
    macro_file >> macro_size;
    msize = macro_size;
    for(int i = 0; i < macro_size; i++) {
        macro_file >> input;
		macro_file >> frame;
		readable_macro.push_back({input, frame});
    }
	macro_file.close();
	msize = readable_macro.size();
    return readable_macro;
}

/*
this variable keeps track of if a macro should be played, so that if you want to play it won't start moving the servos.
it's also used for checking if the serial port is open, rather than sending a message when it's closed and crashing the game.
*/
bool activated = false;
SerialPort *arduino;

// this variable is used to check if the macro should continue being played, so if you pause or exit a level it won't keep going.
bool should_play = true;

gd::string current_level;

// this is the frame counter, it starts counting when your player gets initialised and resets when you exit a level.
int frame = 0;

void play_macro(vector<vector<int>> macro) {
	if (activated) {
		bool left_button_state = false;
		bool middle_button_state = false;
		bool right_button_state = false;

		for (int i = 0; i < macro.size(); i++) {
			// check if next instruction is less than 12 frames away from the last one (to avoid trying to move too quickly)
			int current_frame = frame;
			if (frame - macro[i][1] < 12) {
				// wait 12 frames
				while (frame < current_frame + 12) if (!should_play) break;
			}
			else {
				// wait until the frame of the next instruction
				while (frame < macro[i][1]) if (!should_play) break;
			}

			if (should_play) {
				if (macro[i][0] == 2) {
					if (left_button_state)
						arduino->writeSerialPort("0", MAX_DATA_LENGTH);
					else 
						arduino->writeSerialPort("1", MAX_DATA_LENGTH);
					left_button_state = !left_button_state;
				}

				else if (macro[i][0] == 1) {
					if (middle_button_state)
						arduino->writeSerialPort("2", MAX_DATA_LENGTH);
					else 
						arduino->writeSerialPort("3", MAX_DATA_LENGTH);
					middle_button_state = !middle_button_state;
				}
				
				else if (macro[i][0] == 3){
					if (right_button_state)
						arduino->writeSerialPort("4", MAX_DATA_LENGTH);
					else 
						arduino->writeSerialPort("5", MAX_DATA_LENGTH);
					right_button_state = !right_button_state;
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
			sleep_for(milliseconds(250));
			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			arduino->closeSerial();
		}
		activated = !activated;
	}
};

class $modify(PlayerObject) {

	// this function gets called every time the player gets updated, which in this case is every frame.
	void update(float p0) {
		// call the original update function. because i'm modifying it, the game wouldn't do anything other than what's written down here. calling the original function makes it so the game still updates the player correctly. 
		PlayerObject::update(p0);

		// update the frame count.
		frame++;
	}

	// this function gets called when the player dies, i'm using it to reset the playthrough.
	void playerDestroyed(bool p0) {
		if (activated) {
			frame = 0;
			should_play = false;

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
			
			frame = 0;
			should_play = false;

			std::thread restart_thread = std::thread{[]{ sleep_for(milliseconds(50)); arduino->writeSerialPort("6", MAX_DATA_LENGTH); }};
			restart_thread.detach();
		}
		else {
			PlayLayer::levelComplete();
		}
	}

	// this function gets called when a level is started.
	void startGame() {
		if (activated) {
			PlayLayer::startGame();
			frame = 0;

			// set the level name variable to the one being played
			current_level = this->m_level->m_levelName;
			should_play = true;

			play_thread = std::thread{[&]{ play_macro(get_macro(current_level)); }};
			play_thread.detach();
		}
		else {
			PlayLayer::startGame();
		}
	}

	// this function gets called when a level is restarted from the pause menu.
	void resumeAndRestart(bool p0) {
		if (activated) {
			PlayLayer::resumeAndRestart(p0);
			should_play = true;
			frame = 0;

			play_thread = std::thread{[&]{ play_macro(get_macro(current_level)); }};
			play_thread.detach();
		}
		else {
			PlayLayer::resumeAndRestart(p0);
		}
	}

	// this function gets called when a level gets restarted automatically
	void delayedResetLevel() {
		if (activated) {
			PlayLayer::delayedResetLevel();
			should_play = true;
			frame = 0;

			play_thread = std::thread{[&]{ play_macro(get_macro(current_level)); }};
			play_thread.detach();
		}
		else {
			PlayLayer::delayedResetLevel();
		}
	}

	// this function gets called when a level gets paused.
	void pauseGame(bool p0) {
		if (activated) {
			PlayLayer::pauseGame(p0);
			should_play = false;
			frame = 0;

			std::thread restart_thread = std::thread{[]{ sleep_for(milliseconds(50)); arduino->writeSerialPort("6", MAX_DATA_LENGTH); }};
			restart_thread.detach();
		}
		else {
			PlayLayer::pauseGame(p0);
		}
	}
};
