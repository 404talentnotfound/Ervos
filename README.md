# Ervos
Ervos is an anagram of "servo", which is a type of motor I am using to press the buttons on my sayodevice.
I started this on the 14th of december 2023 (right before 2.2, which is funny but also made this a lot more difficult). I had recently bought some new arduino components, one of which was a servo motor. I had also recently come across a video by Stormfly, named "The History of Hacking in Geometry Dash". In this video was a brief clip of a person using a little motor with tin foil on it to act as their finger and play Stereo Madness on their phone by hardcoding the inputs. I was fascinated by this idea so I quickly checked if I had an old mouse or something of the sort, after I found one I just duct taped the servo to it. It looked incredibly dumb and had a completely unnecessary amount of duct tape, but it seemed to hold. I then made a quick arduino project and hardcoded every input to play Stereo Madness (up to about 12% because I got bored), but this was not efficient in the slightest and was also surprisingly inaccurate. I then remembered an old project I made, where I could mirror my screen on an 128*64 monochrome display. I had used python to send a screenshot in a format that was essentially just 1s and 0s through the usb port of my pc, and then had the arduino recieve and display it.

TL;DR, I made a python script that generates a macro file in a format I created from a megahack json macro for a geode mod. The mod then sends a number to through the serial bus on the exact frame specified in the file, according to which servo had to move and in what direction. This then gets read by the arduino which actually moves the servos.

TL;DR for the TL;DR, servo go up and down, servo beat Acheron.

# Showcases
[first two levels in zip lash](https://www.youtube.com/watch?v=4Cht7uo_oFA)

# Usage
This is probably very difficult to set up but I'm adding this anyway.
There's two ways you can make this, the normal way (copying my exact setup without changing too much) or the chad way (set up a servo on an input device you already own without buying a sayodevice or a 3d printer for this stupid ass project).

---
NORMAL METHOD:

-PREREQUISITES:

1. 3x Servo motors. I use an sg90 (honestly don't know what that means) but one with metal gears should work fine too, just make sure it fits in the case. NOTE: You technically don't need three if you're only playing non-platformer levels, in that case you can buy just one.

2. 1x Sayodevice o3c. Set the actuation force relatively low so the servo can press easily. NOTE: Not the four key one.  

3. 1x 3D printer. I personally use an ender 3 v3 se, it's insanely affordable (for a 3d printer that is). NOTE: You can get stuff printed for you if there is such a service near you, don't buy a 3d printer *just* for this.
 
4. 1x PLA filament. My printer does not support ABS but that's fine too. NOTE: I have not tried printing this with a flexible filament like TPU, I advise you stick with hard plastic (unless you just want to experiment, in which case go ahead).

5. 1x Arduino. I'm using an arduino uno R4 but you can pretty much use any arduino microcontroller as long as it can communicate through usb and provides enough voltage to the servos (usually 5v).

6. 11x Jumper wires. I'm using a breadboard because I don't have enough 5v pins on my arduino for all the servos, if you have at least three 5v and gnd pins on your arduino you only need 9 wires.

7. 1x Screwdriver. To screw the servos into place.

8. Geometry dash (obviously).

9. Geode.

10. Megahack (only if you want to bot levels yourself).

11. Python.

12. Arduino IDE.

13. An STL slicer.

14. A tolerance for jank and working with code if necessary.

-INSTRUCTIONS:

1. Slice the stl file and print it with a 3d printer. NOTE: Add supports! I doubt it would print correctly without them. They aren't too hard to remove with a tool like tweezers and you don't even have to remove all of it, as long as the sayodevice fits into it.

2. Put the 3d printed case on your sayodevice.

3. Screw the servos in using the provided screws. NOTE: Do not add the servo horns (the little plastic arms) to the servos yet.

4. Wire the servos into the arduino, the data pins should be as follows: left servo - 11, middle servo - 9, right servo - 10. You could also just change the arduino code if you want to choose other pins, just make sure you're using analogue pins (on an arduino it will have a tilde next to the pin number).

5. Plug the arduino into your pc and upload the ino file. If you hear your servos moving, it's functioning correctly.

6. Now that the servos are at the right angle, put on the servo horns right above the keys of your sayodevice.

7. Create a directory/folder at the root of your C drive called "macros"

8. Create a file in the C:\\macros directory called "port.txt" and write the com port of the arduino in it, e.g. "COM3".

9. Make/get a megahack macro json file, if you bot a level with megahack you should have the option to export it as a json file.

10. Run the python script with an argument of the location of your json file, e.g. "python macro_generator.py C:\\somefolder\\macro.gdr.json".

11. Compile/install the geode mod.

12. Run geometry dash.

13. Press the more games button at the bottom left of the main menu.

14. Enter a level that you've generated a macro of and watch it go!
 ---
 CHAD METHOD:

 If you're good enough at electronics and programming to do the chad method, you don't need an explaination in the first place.
 
 ---

# Credits
Myself ([404talentnotfound](https://github.com/404talentnotfound)) - pretty much all of it

My friend ([ImXyper](https://github.com/ImXyper)) - some of the python side & incredibly dumb comment lines in main_old.cpp
