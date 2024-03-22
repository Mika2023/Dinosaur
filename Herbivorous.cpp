#include "Herbivorous.h"
#include "Const.h"

Herbivorous::Herbivorous(int x, int y, int sp, int radius, int st)
{
	Animal(sp, radius, st);
	pos.x = x;
	pos.y = y;
}

int Herbivorous::act(Position* p, Position* eat, Position* sex, Position* enemy)
{
	age++;
	starve--;
	if (starve <= 0 || age > herb_age) return -1;
	if (age % herb_speed == 0) {
		if (enemy->x != -1 && enemy->y != -1) {
			pos.x -= (pos.x <= enemy->x) * 2 - 1; //oposite moving, minus
			pos.y -= (pos.y <= enemy->y) * 2 - 1;
		}
		else if (starve <= herb_starving && eat->x != -1 && eat->y != -1) {
			pos.x += (pos.x <= eat->x) * 2 - 1; //straight moving, plus
			pos.y += (pos.y <= eat->y) * 2 - 1;
		}
		else if (sex->x != -1 && sex->y != -1) {
			pos.x += (pos.x <= sex->x) * 2 - 1;
			pos.y += (pos.y <= sex->y) * 2 - 1;
		}
		else {
			srand(clock());
			//todo: remove this shit code
			//Maxim is the greatest programmer ever
			if (pos.x != 0 && pos.x != width - 1) pos.x += rand() % 3 - 1;
			else if (pos.x == 0) pos.x++;
			else if (pos.x == width - 1) pos.x--;
			if (pos.y != 0 && pos.y != height - 1) pos.y += rand() % 3 - 1;
			else if (pos.y == 0) pos.y++;
			else if (pos.y == height - 1) pos.y--;
		}
		//normalizepos();
	}
	return 0;
}
