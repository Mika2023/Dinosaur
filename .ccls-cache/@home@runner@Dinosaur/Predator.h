#pragma once
#include "Animal.h"
#include "Object.h"
#include "Const.h"

class Predator : public Animal
{
public:
	Predator(int x, int y, int st, int sp, int radius);
	int act(Position* p, Position* eat, Position* sex, Position*) override;
};
