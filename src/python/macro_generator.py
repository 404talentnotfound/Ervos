import sys,msgpack,json

# read json file from command line argument
macro_file = open(sys.argv[1],"rb").read()
try:
    json_macro = msgpack.unpackb(macro_file)
except:
    json_macro = json.loads(macro_file)

# create an empty list to append inputs to later
new_macro = []

jump_pressed = False
left_pressed = False
right_pressed = False

try:
    fps = json_macro["framerate"]
except:
    fps = 240

clickdelay = 2
releasedelay = 2

clicks_on_this_frame = 0

click_frames = [f["frame"] for f in json_macro["inputs"] if f["down"]]
release_frames = [f["frame"] for f in json_macro["inputs"] if not f["down"]]

for i, click in enumerate(click_frames):
    clicks_on_this_frame += 1
    try:
        if release_frames[i] > click:
            if clicks_on_this_frame > 1:
                new_macro.append(2)
                new_macro.append(click-clickdelay)
                new_macro.append(clicks_on_this_frame)
            else:
                new_macro.append(1)
                new_macro.append(click-clickdelay)
                new_macro.append(1)

                new_macro.append(1)
                new_macro.append(release_frames[i]-releasedelay)
                new_macro.append(1)

            clicks_on_this_frame = 0

        elif len(click_frames) > i+1:
            if click_frames[i+1] > click:
                new_macro.append(2)
                new_macro.append(click-clickdelay)
                new_macro.append(1)
                clicks_on_this_frame = 0

        elif len(click_frames) == i+1:
            new_macro.append(2)
            new_macro.append(click-clickdelay)
            new_macro.append(1)
            clicks_on_this_frame = 0
    except:
        pass

level_name = json_macro["level"]["name"]

num = ""

if sys.argc > 2:
    level_name = sys.argv[2]

if level_name == "":
    level_name = input("what's the level name?: ")

new_macro_file = open(f"C:\\macros\\{level_name}.soup{num}", "w")

new_macro_file.write(str(round(len(new_macro) / 3)) + '\n')

for i in new_macro:
    new_macro_file.write(str(i) + "\n")

new_macro_file.close()

print(f'saved to "C:\\macros\\{level_name}.soup{num}"')
