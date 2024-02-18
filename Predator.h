#pragma once
#include "Animal.h"
class Predator : public Animal
{
public:
	static int get_count();
	Predator reproduce(const Predator& animal) const;
	void eat_herb() const;
protected:
	static int count;
};