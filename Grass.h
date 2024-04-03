#pragma once
#include "Object.h"
#include "Const.h"
class Grass : public Object
{
public:
	Grass(int x, int y);
  virtual ~Grass() {};
	int act(Position* p, Position*, Position*, Position*) override;
	void act_(Position* p, Position*, Position*, Position*) override;
};
