#pragma once
#include <vector>
#include "Grass.h"
#include "Predator.h"
#include "Herbivorous.h"
#include "Position.h"
using namespace std;
const size_t width = 20;
const size_t height = 20;

class Game {
private:
	size_t tick;
	int world[height][width]; //empty, food, animal1, animal2...
	vector<Grass> grass;
	vector<Herbivorous> herb;
	vector<Predator> pred;
	enum content {
		empty,
		gr,
		herbivorous,
		predator
	};

public:
	Game();

	void printworld();

	void start();
};
