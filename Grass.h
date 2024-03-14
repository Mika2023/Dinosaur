#pragma once
#include "Object.h"

class Grass: public Object
{
public:
	Grass(int x, int y);
	int act(Position* p, Position*, Position*, Position*) override;
};
