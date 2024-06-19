# ervos
Ervos is an anagram of "servo", which is a type of motor i am using to press the buttons on my sayodevice.
I started this on the 14th of december 2023 (right before 2.2, which is funny but also made this a lot more difficult). I had recently bought some new arduino components, one of which was a servo motor. I had also recently come across a video by stormfly, named "The History of Hacking in Geometry Dash". In this video was a brief clip of a person using a little motor with tin foil on it to act as their finger and play stereo madness by hardcoding the inputs. I was fascinated by this idea so I quickly checked if I had an old mouse or something of the sort, after I found one I just duct taped the servo to it. It looked incredibly dumb and had a completely unnecessary amount of duct tape, but it seemed to hold. I then made a quick arduino project and hardcoded every input to play stereo madness (up to about 12% because I got bored), but this was not efficient in the slightest and was also surprisingly inaccurate. I then remembered an old project I made, where I could mirror my screen on an 128*64 monochrome display. I had used python to send a screenshot in a format that was essentially just 1s and 0s through the usb port of my pc, and then had the arduino recieve and display it.

TL;DR, I made a python script that generates a macro file in a format I created from a megahack json macro for a geode mod. The mod then sends a number to through the serial bus on the exact frame specified in the file, according to which servo to move and what direction. This then gets read by the arduino which actually moves the servos.

TL;DR for the TL;DR, servo go up and down, servo beat acheron

# usage
