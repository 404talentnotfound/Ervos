import json,sys

# read json file from command line argument
json_file = open(sys.argv[1],"r").read()
json_macro = json.loads(json_file)

# create an empty list to append inputs to later
new_macro = []

# get every input from the json file (both clicks and releases)
for input in json_macro["inputs"]:
    try:
        # check which button is being pressed/released
        match input["btn"]:
            case 1:
                # append the input key and frame to the macro
                new_macro.append("1")
                new_macro.append(input["frame"])

            case 2:
                new_macro.append("2")
                new_macro.append(input["frame"])

            case 3:
                new_macro.append("3")
                new_macro.append(input["frame"])
            
            # if previous cases don't match, just continue
            case _:
                continue
    
    # if an exception occurs, capture and print it before continuing
    except Exception as e:
        print(e)
        continue

# get the level name
level_name = json_macro["level"]["name"]

# create/open file
new_macro_file = open(f"C:\\macros\\{level_name}.soup", "w")

# write macro length to file (divided by two because every input uses two lines)
new_macro_file.write(str(round(len(new_macro) / 2)) + '\n')

# write macro to file
for i in new_macro:
    new_macro_file.write(str(i) + "\n")

# close file
new_macro_file.close()
