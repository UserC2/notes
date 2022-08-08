#!/bin/bash

source="main.cpp TextInterface.cpp"
g++ -std=c++17 -Wall -Werror -I./ ${source} -o notes
