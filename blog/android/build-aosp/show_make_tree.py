#!/usr/bin/python

import sys
from os.path import exists

def indent(level, line, char="  "):
    for _ in range(level):
        print(char, end="")
    print(line)

def find(file, level):
    if exists(file):
        indent(level, file)
        with open(file, "r") as f:
            for line in f.readlines():
                if line.startswith("$(call inherit-product"):
                    line = line.replace("$(SRC_TARGET_DIR)", "build/target")
                    line = line.split(",")[1]
                    line = line.strip()
                    line = line[:-1]
                    find(line, level+1)
                if line.startswith("include"):
                    line = line.split(" ")[1]
                    line = line.strip()
                    find(line, level+1)
                if search in line:
                    indent(level+1, line.strip(), char="> ")

if len(sys.argv) >= 3:
    root = sys.argv[1]
    search = sys.argv[2]

    print("Search for\n" + search + "\nin");
    find(root, 0)
