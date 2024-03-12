#include "Grass.h"

Grass::food(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

int Grass::act(Position* p, Position*, Position*, Position*)
{//-1 delete obj; 1 create new obj; 0 do nothing. Have no aims
	age++;
	if (age > foodage) return -1;//все эти глобальные переменные, которые мы передаем в самом начале
	//надо запихать либо в поля соответствующих классов, либо передавать в методы в качестве параметров
	if (age % foodspawnrate == 0) {
		spawn(p);
		return 1;
	}
	return 0;
}
