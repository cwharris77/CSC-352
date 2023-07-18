# sbt.py
# Author: Cooper Harris 
# Course: CSC 252
#
# This program will ask a user for two inputs, a path to a c file
# a path to a test directory with the structure listed below. If the c file
# fails to compile for any reason the program will exit. Otherwise it will loop
# through each directory in the current one and compare the output of the c file
# to the provided input.txt
#
# ───tests 
#   ├── pyth-3-4 │   
#       ├── input.txt │   
#       └── output.txt 
#   └── pyth-7-2 
#       ├── input.txt 
#       └── output.txt

import os
import subprocess

def main():
    path = input("C source file path: ")
    print()
    #path = "../pythagorean/pythagorean.c"
    test_dir = input("Test file directory path: ")
    print()
    #test_dir = "../tests"

    command_result = subprocess.run(['gcc', '-Wall', '-Werror', '-std=c11', path, '-lm'], stderr=subprocess.PIPE)

    if command_result.returncode != 0:
        print("failed to compile your code")
        os._exit(1)

    test_files(test_dir)

# A helper function the handles looping through the test directory and testing the files
# arguemnts: test_dir: the name of the directory to test
# returns None
def test_files(test_dir):
    for parent in os.listdir(test_dir):
        run_file = os.popen(f"cat {test_dir}/{parent}/input.txt | ./a.out")
        file_output = run_file.read()

        get_txt = os.popen(f"cat {test_dir}/{parent}/output.txt")
        txt_output = get_txt.read()

        if (file_output != txt_output):
            print(f"#### Test: {parent} failed! ####")

            expected = os.popen(f"cat {test_dir}/{parent}/output.txt")
            exp_res = expected.read()

            actual = os.popen(f"cat checkDiff.txt ")
            act_res = actual.read()
            print("#### EXPECTED TO SEE:")
            print(exp_res, end="")
            print("#### INSTEAD GOT:")
            print(act_res, end="")
        else:
            print(f"#### Test: {parent} passed! ####")
        
if __name__ == "__main__":
    main()
