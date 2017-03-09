all:
	g++ -std=c++11 -Wall -Wpedantic -oPathfinding -Iinclude main.cpp src/*.cpp -lglfw -lGL -lGLU
