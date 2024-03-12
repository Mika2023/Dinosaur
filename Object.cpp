#include "Object.h"

Object::obj()
{
	pos.x = -1;
	pos.y = -1;
	starve = 0;
	age = 0;
}

void Object::spawn(Position* p)
{
	do {
		srand(clock()); //to avoid stacks of content. Not nessessary
		/*if (pos.x != 0 && pos.x != width - 1) p->x = pos.x + rand() % 3 - 1;
		else if (pos.x == 0) p->x = pos.x + 1;
		else if (pos.x == width - 1) p->x = pos.x - 1;

		if (pos.y != 0 && pos.y != height - 1) p->y = pos.y + rand() % 3 - 1;
		else if (pos.y == 0) p->y = pos.y + 1;
		else if (pos.y == height - 1) p->y = pos.y - 1;*/

		//make the good generation of position with checking destination cell if it occupied
	} while (pos.y == p->y && pos.x == p->x);
}

void Object::normalizepos()
{
	pos.x %= width;
	pos.y %= height;
}
