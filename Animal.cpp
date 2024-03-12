#include "Animal.h"

Animal::Animal(int sp, int radius, int st)
{
	Object();
	speed = sp;
	vision_rad = radius;
	starve = st;
}

Position Animal::check_vision(vector<Object> grass)
{
	int size = grass.size();
	for (int i = 0; i < size; ++i)
	{
		if (abs(grass[i].pos.x - pos.x) <= vision_rad && abs(grass[i].pos.y - pos.y) <= vision_rad)
			return grass[i].pos;
	}
	Position p;
	p.x = -1;
	p.y = -1;
	return p;
}

