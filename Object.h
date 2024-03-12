#pragma once
#include "Position.h"
class Object
{
protected:
	int age;
public:
	Position pos;
	obj();
	virtual int act(Position*, Position*, Position*, Position*) { return 0; };
	void spawn(Position* p);
	void normalizepos(Position& p);
};