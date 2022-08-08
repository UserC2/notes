#!/bin/bash

# replace this with the location of UserC2/include
externPath="../include/"

#externIncludes="${externPath}"

source="main.cpp TextInterface.cpp"
g++ -std=c++17 -Wall -Werror -I./ -I${externPath} ${source} -o notes
