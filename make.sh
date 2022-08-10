#!/bin/bash

# replace this with the location of UserC2/include
externPath="../include/"

externIncludes="${externPath}/C2Utility.cpp ${externPath}/date.cpp ${externPath}/FstreamHandler.cpp"

source="main.cpp TextInterface.cpp ${externIncludes}"
g++ -std=c++17 -Wall -Werror -I./ -I${externPath} ${source} -o notes
