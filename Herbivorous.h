#pragma once
#include "Animal.h"
#include "Object.h"
class Herbivorous : public Object
{
//public:
//	static int get_count();
//	Herbivorous reproduce(const Herbivorous& animal) const;
//	void eat_grass() const;
//protected:
//	static int count;
public:
	Herbivorous(int x, int y);
	int act(Position* p, Position* eat, Position* sex, Position* enemy) override;
};