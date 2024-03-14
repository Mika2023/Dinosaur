#pragma once
#include "Position.h"
#include <iostream>
#include <chrono>

class Object
{
protected:
	int age;
public:
	Position pos;
	Object();
	virtual int act(Position*, Position*, Position*, Position*) { return 0; };
	virtual void act_(Position*, Position*, Position*, Position*) {};
	void spawn(Position* p);
	void normalizepos(Position& p);
};
