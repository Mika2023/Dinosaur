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
	int mark;
public:
        //Animal();
	Animal(int sp, int radius, int st);
	int get_mark() const;
	void set_mark(int value);
	void increase_starve();
        template<typename Type>
	Position check_vision(vector<Type>& food, int is_sex)
	{
		int size = food.size();
		int st_x = pos.x - vision_rad;
		int end_x = pos.x + vision_rad;
		int st_y = pos.y - vision_rad;
		int end_y = pos.y + vision_rad;
		int f_x = 0, f_y = 0;
		for (int i = 0; i < size; ++i)
		{
			f_x = 0;
			f_y = 0;
			Position checking = ((Object)food[i]).pos;

			if (st_x < 0 && checking.x - width >= st_x && checking.x - width <= end_x)  f_x = 1;
			else if (end_x >= width && checking.x + width >= st_x && checking.x + width <= end_x) f_x = 1;
			else if (st_x <= checking.x && checking.x <= end_x) f_x = 1;
			if (st_y < 0 && checking.y - height <= end_y && checking.y - height >= st_x)  f_y = 1;
			else if (end_y >= height && checking.y+height >= st_y && checking.y + height <= end_y) f_y = 1;
			else if (st_y <= checking.y && checking.y <= end_y) f_y = 1;
			if (is_sex && checking.x == pos.x && checking.y == pos.y)
			{
				f_x = 0;
				f_y = 0;
			}
			if (f_x && f_y) return checking;
		}
		Position p;
		p.x = -1;
		p.y = -1;
		return p;
	}
};
