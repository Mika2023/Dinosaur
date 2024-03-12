#include "Predator.h"

Predator::Predator(int x, int y)
{
	starve = animal2startstarve;
	pos.x = x;
	pos.y = y;
}

int Predator::act(Position* p, Position* eat, Position* sex, Position*)
{
	age++;
	starve -= 2;
	if (health <= 0 || starve <= 0 || age > animal1age) return -1;
	if (age % animal2speed == 0) {
		if (starve <= animal2starving && eat->x != -1 && eat->y != -1) {
			pos.x += (pos.x <= eat->x) * 2 - 1;
			pos.y += (pos.y <= eat->y) * 2 - 1;
		}
		else if (sex->x != -1 && sex->y != -1) {
			pos.x += (pos.x <= sex->x) * 2 - 1;
			pos.y += (pos.y <= sex->y) * 2 - 1;
		}
		else {
			srand(clock());
			if (pos.x != 0 && pos.x != width - 1) pos.x += rand() % 3 - 1;
			else if (pos.x == 0) pos.x++;
			else if (pos.x == width - 1) pos.x--;
			if (pos.y != 0 && pos.y != height - 1) pos.y += rand() % 3 - 1;
			else if (pos.y == 0) pos.y++;
			else if (pos.y == height - 1) pos.y--;
		}
		normalizepos();
	}
	return 0;
}
