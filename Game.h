#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "Grass.h"
#include "Predator.h"
#include "Herbivorous.h"
#include "Position.h"
#include "Const.h"

using namespace std;

class Game {
private:
	size_t tick;
	WorldStruct world[height][width]; //empty, food, animal1, animal2...
	vector<Grass> grass;
	vector<Herbivorous> herb;
	vector<Predator> pred;
	

public:
	Game();
	void printworld();
	void start();
};
