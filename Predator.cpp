#include "Predator.h"
#include "Const.h"

Predator::Predator(int x, int y, int st, int sp, int radius) : Animal(sp, radius, st)
{
	pos.x = x;
	pos.y = y;
}

int Predator::act(Position *p, Position *eat, Position *sex, Position *)
{
	// int arr[SIZE] = { -1, 0, 1 };
	// int rand1 = rand() % 3;
	// int rand2 = rand() % 3;
	age++;
	starve -= 2;
	birth_cooldown++;
	if (starve <= 0 || age > pred_age) return -1;
	if (age % pred_speed == 0) {
		if (starve <= pred_starving && eat->x != -1 && eat->y != -1) {
			p->x = pos.x + ((pos.x <= eat->x) * 2 - 1);
			p->y = pos.y + ((pos.y <= eat->y) * 2 - 1);
		}
		else if (sex->x != -1 && sex->y != -1) {
			p->x = pos.x + ((pos.x <= sex->x) * 2 - 1);
			p->y = pos.y + ((pos.y <= sex->y) * 2 - 1);
			
		}
		else {
			return 0;
		}
		normalizepos(*p);
		return 1;
	}
	return 0;
}
