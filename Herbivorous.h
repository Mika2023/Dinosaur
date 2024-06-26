#pragma once
#include "Animal.h"
#include "Object.h"
#include "Const.h"

class Herbivorous : public Animal
{
public:
	Herbivorous(int x, int y, int st, int sp, int radius);
  virtual ~Herbivorous() {};
	int act(Position* p, Position* eat, Position* sex, Position* enemy) override;
};
