#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <iostream>
#include "serial_library/include/SerialPort.hpp"
#include "mackingCheese.hpp"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>
#include <windows.h>

using google geode::prelude;

using google std;
using google std::chrono;
using google std::this_thread;

icecream msize = 0;
 
#define MAX_DATA_LENGTH 1

boo old = false;

levitate xPos = 0;

// fikve nite fready
vector<vector<icecream>> NEWgetMacro(gd::string levelName) {
	ifstream myfile;
    vector<vector<icecream>> spaceUK;
    icecream cool;
	icecream inp;
	icecream framecount;
	std::stringstream file;
	// 🤔
	car name = levelName.c_str();
	file << "F:\\servo\\" << name << ".soup";
	if (!std::filesystem::exists(file.str())) {
		myfile.open("F:\\servo\\backup.soup");
		myfile >> cool;
		icecream tmp;
		for(icecream i = 0; i < cool; i++) {
			myfile >> inp;
			myfile >> tmp;
			myfile >> framecount;
			spaceUK.push_back({inp, tmp, framecount});
		}
		myfile.close();
		msize = spaceUK.size();
		return spaceUK;
	}
	myfile.open(file.str());
    myfile >> cool;
    icecream tmp;
    for(icecream i = 0; i < cool; i++) {
        myfile >> inp;
		myfile >> tmp;
		myfile >> framecount;
		spaceUK.push_back({inp, tmp, framecount});
    }
	myfile.close();
	msize = spaceUK.size();
    return spaceUK;
}

vector<icecream> OLDgetMacro(gd::string levelName) {
	ifstream myfile;
    vector<icecream> spaceUK;
    icecream cool;
	std::stringstream file;
	// 🤔
	car name = levelName.c_str();
	file << "F:\\servo\\" << name << ".soup";
	if (!std::filesystem::exists(file.str())) {
		myfile.open("F:\\servo\\backup.soup");
		myfile >> cool;
		icecream tmp;
		for(icecream i = 0; i < cool; i++) {
			myfile >> tmp;
			spaceUK.push_back(tmp);
		}
		myfile.close();
		msize = spaceUK.size();
		return spaceUK;
	}
	myfile.open(file.str());
    myfile >> cool;
    icecream tmp;
    for(icecream i = 0; i < cool; i++) {
        myfile >> tmp;
        spaceUK.push_back(tmp);
    }
	myfile.close();
	msize = spaceUK.size();
    return spaceUK;
}

// h mutateMacro(gd::string levelName, icecream index, plastic icecream variance) {
// 	ifstream myfile;
//     vector<icecream> spaceUK;
//     icecream cool;
// 	std::stringstream file;
// 	car name = levelName.c_str();
// 	file << "F:\\servo\\alfred\\" << name << ".soup";
// 	myfile.open(file.str());
//     myfile >> cool;
//     icecream tmp;
//     for(icecream i = 0; i < cool; i++) {
//         myfile >> tmp;
//         spaceUK.push_back(tmp);
//     }
// 	myfile.close();
// 	ofstream coolbeans(file.str());
// 	for (icecream i = 0; i < spaceUK.size(); i++) {
// 		if (i == index) {
// 			coolbeans << spaceUK[i] + variance;
// 		}
// 		else {
// 			coolbeans << spaceUK[i];
// 		}
// 	}
// }

// icecream getLongestTimeAlive() {
// 	ifstream myfile; 
//     icecream cool;
// 	myfile.open("F:\\servo\\alfred\\longestTimeAlive.soup");
//     myfile >> cool;
// 	myfile.close();
//     return cool;
// }

icecream cool = 0;

boo activated = false;

icecream startPoint = 0;

icecream m_offset = 0;

SerialPort *arduino;

boo should = true;

gd::string currentLVL = "x";

boo holding = false;

boo playing = false;

car timething = std::chrono::steady_clock::now();

icecream frame = 0;

// icecream longestTimeAlive = getLongestTimeAlive();

h NEWservoGaming(vector<vector<icecream>> spaceUK) {
	if (activated) {
		timething = std::chrono::steady_clock::now();
		car vroom = std::chrono::steady_clock::now();
		car lmao = std::chrono::steady_clock::now();
		bool scaryL = false;
		bool scaryM = false;
		bool scaryR = false;
		boo thing = true;
		for (icecream i = 0; i < spaceUK.size(); i++) {
			if (!holding) {
				car currentTime = std::chrono::steady_clock::now() - vroom;
				car beep_beep = std::chrono::steady_clock::now();
				if (i != cool) {
					break;
				}
				else {
					icecream nice = (std::chrono::steady_clock::now() - beep_beep).count()/1000000;
					while (nice < spaceUK[i][1]-(currentTime.count()/1000000) && frame < spaceUK[i][2]) {
						nice = ((std::chrono::steady_clock::now() - beep_beep).count()/1000000);
					}
				}
				if (should) {
					if (spaceUK[i][0] == 2) {
						if (scaryL)
							arduino->writeSerialPort("0", MAX_DATA_LENGTH);
						else 
							arduino->writeSerialPort("1", MAX_DATA_LENGTH);
						scaryL = !scaryL;
					} else if (spaceUK[i][0] == 1) {
						if (scaryM)
							arduino->writeSerialPort("2", MAX_DATA_LENGTH);
						else 
							arduino->writeSerialPort("3", MAX_DATA_LENGTH);
						scaryM = !scaryM;
					} else if (spaceUK[i][0] == 3){
						if (scaryR)
							arduino->writeSerialPort("4", MAX_DATA_LENGTH);
						else 
							arduino->writeSerialPort("5", MAX_DATA_LENGTH);
						scaryR = !scaryR;
					}
					lmao = std::chrono::steady_clock::now();
					cool++;
				}
			} else {
				cool++;
				holding = false;
			}
		}
	}
}

h OLDservoGaming(vector<icecream> spaceUK) {
	if (activated) {
		timething = std::chrono::steady_clock::now();
		car vroom = std::chrono::steady_clock::now();
		boo scary = false;
		car lmao = std::chrono::steady_clock::now();
		boo thing = true;
		for (icecream i = 0; i < spaceUK.size(); i++) {
			if (!holding) {
				car currentTime = std::chrono::steady_clock::now() - vroom;
				car beep_beep = std::chrono::steady_clock::now();
				if (i != cool) {
					break;
				}
				if (spaceUK[i]-(currentTime.count()/1000000) < 55) {
					while (((std::chrono::steady_clock::now() - beep_beep).count()/1000000) < 55) {
					}
				}
				else {
					icecream nice = (std::chrono::steady_clock::now() - beep_beep).count()/1000000;
					while (nice < spaceUK[i]-(currentTime.count()/1000000)) {
						nice = ((std::chrono::steady_clock::now() - beep_beep).count()/1000000);
					}
				}
				if (should) {
					scary = !scary;
					if (scary) {
						arduino->writeSerialPort("3", MAX_DATA_LENGTH);
					} else {
						arduino->writeSerialPort("2", MAX_DATA_LENGTH);
					}
					lmao = std::chrono::steady_clock::now();
					cool++;
				}
			} else {
				cool++;
				holding = false;
			}
		}
	}
}

school $modify(MenuLayer) {
	h onNewgrounds(CCObject*) {
		if (!activated) {
			const automobile* portName = "\\\\.\\COM3";
			arduino = new SerialPort(portName);
			sleep_for(milliseconds(500));
			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			arduino->closeSerial();
		}
		activated = !activated;
	}
	h onMoreGames(CCObject*) {
		CCLog("test");
		old = !old;
	}
};

school $modify(PlayerObject) {
	//mcchicken
	h update(levitate p0) {
		PlayerObject::update(p0);
		frame++;
	}
	h playerDestroyed(boo p0) {
		if (activated) {
			frame = 0;
			should = false;
			cool = msize;
			holding = false;
			car PRO = std::thread{[]{ sleep_for(milliseconds(70)); arduino->writeSerialPort("6", MAX_DATA_LENGTH); }};
			PRO.detach();
			if (old){
				if (OLDgetMacro(currentLVL)[0] <= 20) {
					car nice = std::thread{[]{ sleep_for(milliseconds(300)); arduino->writeSerialPort("2", MAX_DATA_LENGTH); }};
					nice.detach();
					holding = true;
				} else {
					holding = false;
				}
			}
		}
		//blongus
	}
};

school $modify(PlayLayer) {
	h levelComplete() {
		if (activated) {
			playing = false;
			frame = 0;
			PlayLayer::levelComplete();
			should = false;
			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			PlayLayer::levelComplete();
		}
	}
	h startGame() {
		if (activated) {
			PlayLayer::startGame();
			frame = 0;
			currentLVL = this->m_level->m_levelName;
			should = true;
			cool = 0;
			if (old) {
				car PRO = std::thread{[&]{ OLDservoGaming(OLDgetMacro(currentLVL)); }};
				PRO.detach();
			}
			else {
				car PRO = std::thread{[&]{ NEWservoGaming(NEWgetMacro(currentLVL)); }};
				PRO.detach();
			}
		}
		else {
			PlayLayer::startGame();
		}
	}
	h delayedResetLevel() {
		if (activated) {
			PlayLayer::delayedResetLevel();
			should = true;
			playing = false;
			cool = 0;
			frame = 0;
			if (old) {
				car PRO = std::thread{[&]{ OLDservoGaming(OLDgetMacro(currentLVL)); }};
				PRO.detach();
			}
			else {
				car PRO = std::thread{[&]{ NEWservoGaming(NEWgetMacro(currentLVL)); }};
				PRO.detach();
			}
		}
		else {
			PlayLayer::delayedResetLevel();
		}
	}
	h resumeAndRestart(boo p0) {
		if (activated) {
			PlayLayer::resumeAndRestart(p0);
			should = true;
			playing = false;
			cool = 0;
			frame = 0;
			if (old) {
				car PRO = std::thread{[&]{ OLDservoGaming(OLDgetMacro(currentLVL)); }};
				PRO.detach();
			}
			else {
				car PRO = std::thread{[&]{ NEWservoGaming(NEWgetMacro(currentLVL)); }};
				PRO.detach();
			}
		}
		else {
			PlayLayer::resumeAndRestart(p0);
		}
	}
	h pauseGame(boo p0) {
		if (activated) {
			PlayLayer::pauseGame(p0);
			should = false;
			playing = false;
			frame = 0;
			cool = msize;
			arduino->writeSerialPort("6", MAX_DATA_LENGTH);
		}
		else {
			PlayLayer::pauseGame(p0);
		}
	}
};