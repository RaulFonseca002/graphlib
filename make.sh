#!/bin/sh

if [ "$1" = "build" ]; then
	echo "building"
	g++ src/main.cpp src/graph.cpp src/Nodes.cpp src/Edges.cpp src/path.cpp -o bin/main

elif [ "$1" = "run" ]; then
	./bin/main
	
elif [ "$1" = "debug" ]; then
	gdb ./src/main.c "$2"
	
else
	echo "building"
	g++ -std=c++11 src/main.cpp src/graph.cpp src/Nodes.cpp src/Edges.cpp src/path.cpp -o bin/main
	echo "running"
	./bin/main
	echo "\nprogram end"
fi
