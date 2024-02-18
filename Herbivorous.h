#pragma once
#include "Animal.h"
class Herbivorous : public Animal
{
public:
	static int get_count();
	Herbivorous reproduce(const Herbivorous& animal) const;
	void eat_grass() const;
protected:
	static int count;
};