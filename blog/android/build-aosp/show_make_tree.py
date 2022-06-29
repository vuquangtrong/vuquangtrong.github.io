#!/usr/bin/python3

import sys
from os.path import exists

__FILE    = "\u001b[32mFile   : " # green
__INHERIT = "\u001b[33mInherit: " # yellow
__SEARCH  = "\u001b[31mSearch : " # read
__INCLUDE = "\u001b[36mInclude: " # cyan
__NONE    = "\u001b[0m"           # reset

def indent(level, type, line):
    print(type, end="")
    for _ in range(level):
        print("  ", end="")
    print(line, end="")
    print(__NONE)

def find(file, level, type):
    if exists(file):
        indent(level, type, file)
        with open(file, "r") as f:
            for line in f.readlines():
                if line.startswith("$(call inherit-product"):
                    line = line.replace("$(SRC_TARGET_DIR)", "build/target")
                    line = line.split(",")[1]
                    line = line.strip()
                    line = line[:-1]
                    find(line, level+1, __INHERIT)
                if line.startswith("include"):
                    line = line.split(" ")[1]
                    line = line.strip()
                    find(line, level+1, __INCLUDE)
                if search in line:
                    indent(level+1, __SEARCH, line.strip())

if len(sys.argv) >= 3:
    root = sys.argv[1]
    search = sys.argv[2]

    print("Search for\n\u001b[31m" + search + "\u001b[0m\nin");
    find(root, 0, __FILE)
