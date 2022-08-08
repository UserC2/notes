#!/bin/bash

source="main.cpp"
g++ -std=c++17 -Wall -Werror -I./ ${source} -o notes
