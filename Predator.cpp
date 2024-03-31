#include "Predator.h"
#include "Const.h"


Predator::Predator(int x, int y, int st, int sp, int radius): Animal(sp, radius, st)
{
	pos.x = x;
	pos.y = y;
}

int Predator::act(Position* p, Position* eat, Position* sex, Position*)
{
	age++;
        starve -= 2;
        if (starve <= 0 || age > pred_age)
            return -1;
        if (starve <= pred_starving && eat->x != -1 && eat->y != -1)
        {
            pos.x += ((pos.x <= eat->x) * 2 - 1) * speed;
            pos.y += ((pos.y <= eat->y) * 2 - 1) * speed;
        }
        else if (sex->x != -1 && sex->y != -1)
        {
            pos.x += ((pos.x <= sex->x) * 2 - 1) * speed;
            pos.y += ((pos.y <= sex->y) * 2 - 1) * speed;
        }
        else
        {
            srand(clock());
        }
        normalizepos(pos);
        p->x = pos.x;
        p->y = pos.y;
        return 1;
}
