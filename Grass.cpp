#include "Grass.h"
#include "Const.h"

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

void Grass::act_(Position* p, Position*, Position*, Position*)
{//-1 delete obj; 1 create new obj; 0 do nothing. Have no aims
		spawn(p);
}
