import os

# get the absolute path of the script file
script_path = os.path.abspath(__file__)

# get the directory of the script file
script_dir = os.path.dirname(script_path)

print("Directory of the script file:", script_dir)
