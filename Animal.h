#pragma once
#include <vector>
#include <cmath>
#include "Object.h"
#include "Grass.h"
using namespace std;

class Animal: public Object
{
//public:
//	int get_hunger();
//	int get_priority();
//	int get_gender();
//protected:
//	int gender;
//	int speed;
//	int vision;
//	int priority;
//	int reproduction;
protected:
	int speed;
	int starve;
	int vision_rad;
public:
	Animal(int sp, int radius, int st);
	Position check_vision(vector<Object> foods);
};