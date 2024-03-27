#include "Herbivorous.h"
#include "Const.h"

Herbivorous::Herbivorous(int x, int y, int st, int sp, int radius):Animal(sp, radius, st)
{
	pos.x = x;
	pos.y = y;
}

int Herbivorous::act(Position* p, Position* eat, Position* sex, Position* enemy)
{
	age++;
	starve--;
	if (starve <= 0 || age > herb_age) return -1;
	if (enemy->x != -1 && enemy->y != -1) {
		pos.x -= (pos.x <= enemy->x) * 2 - 1; //oposite moving, minus
		pos.y -= (pos.y <= enemy->y) * 2 - 1;
	}
	else if (starve <= herb_starving && eat->x != -1 && eat->y != -1) {
		pos.x += (pos.x <= eat->x) * 2 - 1; //straight moving, plus
		pos.y += (pos.y <= eat->y) * 2 - 1;
	}
	else if (sex->x != -1 && sex->y != -1 && sex->x != pos.x && sex->y != pos.y) {
		pos.x += (pos.x <= sex->x) * 2 - 1;
		pos.y += (pos.y <= sex->y) * 2 - 1;
	}
	else {
		return 0;
	}
	normalizepos(pos);
	p->x = pos.x;
	p->y = pos.y;
	return 1;
}
