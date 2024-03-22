#include "Animal.h"

Animal::Animal()
{
	starve = 0;
	speed = 0;
	vision_rad = 0;
}

Animal::Animal(int sp, int radius, int st)
{
	Object();
	speed = sp;
	vision_rad = radius;
	starve = st;
}

Position Animal::check_vision(vector<Object> food)
{
	int size = food.size();
	for (int i = 0; i < size; ++i)
	{
		if (abs(food[i].pos.x - pos.x) <= vision_rad && abs(food[i].pos.y - pos.y) <= vision_rad)
			return food[i].pos;
	}
	Position p;
	p.x = -1;
	p.y = -1;
	return p;
}

