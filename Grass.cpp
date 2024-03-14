#include "Grass.h"
const int grass_age = 10;
const int grass_spawnrate = 5; //lower is more
Grass::Grass(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

int Grass::act(Position* p, Position*, Position*, Position*)
{//-1 delete obj; 1 create new obj; 0 do nothing. Have no aims
	age++;
	if (age > grass_age)
	{
		return -1;
	}
	if (age % grass_spawnrate == 0) 
	{
		spawn(p);
		return 1;
	}
	return 0;
}
