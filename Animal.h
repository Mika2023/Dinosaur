#pragma once
#include <vector>
#include <cmath>
#include "Object.h"
#include "Grass.h"
using namespace std;

class Animal : public Object
{
protected:
	int speed;
	int starve;
	int vision_rad;
public:
        //Animal();
	Animal(int sp, int radius, int st);
        template<typename Type>
	Position check_vision(vector<Type>& food)
	{
		int size = food.size();
		for (int i = 0; i < size; ++i)
		{
			if (abs(((Object)food[i]).pos.x - pos.x) <= vision_rad && abs(((Object)food[i]).pos.y - pos.y) <= vision_rad)
				return ((Object)food[i]).pos;
			/*if (abs(food[i].pos.x - pos.x) <= vision_rad && abs(food[i].pos.y - pos.y) <= vision_rad)
				return food[i].pos;*/
		}
		Position p;
		p.x = -1;
		p.y = -1;
		return p;
	}
};
