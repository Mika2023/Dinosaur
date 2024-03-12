#pragma once
#include "Animal.h"
#include "Object.h"
class Predator : public Object
{
//public:
//	static int get_count();
//	Predator reproduce(const Predator& animal) const;
//	void eat_herb() const;
//protected:
//	static int count;
public:
	Predator(int x, int y);
	int act(Position* p, Position* eat, Position* sex, Position*) override;
};