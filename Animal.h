#pragma once
#include "Object.h"

class Animal: public Object
{
public:
	int get_hunger();
	int get_priority();
	int get_gender();
protected:
	int gender;
	int hunger;
	int speed;
	int vision;
	int priority;
	int reproduction;
};