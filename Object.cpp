#include "Object.h"

Object::obj()
{
	pos.x = -1;
	pos.y = -1;
	age = 0;
}

void Object::spawn(Position* p)
{
	do {
		srand(clock()); //to avoid stacks of content. Not nessessary
		
		p->x = pos.x + rand() % 3 - 1;
		p->y = pos.y + rand() % 3 - 1;
		normalizepos(*p);
		//make the good generation of position with checking destination cell if it occupied
	} while (pos.y == p->y && pos.x == p->x);
}

void Object::normalizepos(Position& p)
{
	p.x %= width;
	p.y %= height;
}
