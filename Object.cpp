#include "Object.h"

const size_t width = 20;
const size_t height = 20;

Object::Object()
{
	pos.x = -1;
	pos.y = -1;
	age = 0;
}

void Object::spawn(Position* p)
{
	do {
		srand(clock()); //to avoid stacks of content. Not nessessary
		int x = pos.x + rand() % 3 - 1;
		int y = pos.y + rand() % 3 - 1;
		p->x = x;
		p->y = y;
		normalizepos(*p);
		//make the good generation of position with checking destination cell if it occupied
	} while (pos.y == p->y && pos.x == p->x);
}

void Object::normalizepos(Position& p)
{
	p.x %= width;
	p.y %= height;
}
