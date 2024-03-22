#pragma once
#include <vector>
#include <cmath>
#include "Object.h"
#include "Grass.h"
using namespace std;

class Animal : public Object
{
protected:
	int speed;
	int starve;
	int vision_rad;
public:
        Animal();
	Animal(int sp, int radius, int st);
	Position check_vision(vector<Object> foods);
};
