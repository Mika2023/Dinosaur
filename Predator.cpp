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
	starve--;
	birth_cooldown++;
	if (starve <= 0 || age > pred_age)
		return -1;
	if (age % pred_speed == 0)
	{
		if (starve <= pred_starving && eat->x != -1 && eat->y != -1)
		{

			/*if (pos.x < eat->x)
			{
				pos.x += 1;
			}
			else if (pos.x > eat->x)
			{
				pos.x -= 1;
			}
			else
				pos.x += 0;

			if (pos.y < eat->y)
			{
				pos.y += 1;
			}
			else if (pos.y > eat->y)
			{
				pos.y -= 1;
			}
			else
				pos.y += 0;*/

			pos.x += (pos.x <= eat->x) * 2 - 1; // straight moving, plus
			pos.y += (pos.y <= eat->y) * 2 - 1;
		}
		else if (sex->x != -1 && sex->y != -1 && sex->x != pos.x && sex->y != pos.y && age >= birth_age && birth_cooldown >= to_birth)
		{
			/*if (pos.x < sex->x)
			{
				pos.x += 1;
			}
			else if (pos.x > sex->x)
			{
				pos.x -= 1;
			}
			else
				pos.x += 0;

			if (pos.y < sex->y)
			{
				pos.y += 1;
			}
			else if (pos.y > sex->y)
			{
				pos.y -= 1;
			}
			else
				pos.y += 0;*/
			pos.x += (pos.x <= sex->x) * 2 - 1;
			pos.y += (pos.y <= sex->y) * 2 - 1;
		}
		else
		{
			// pos.x += arr[rand1];
			// pos.y += arr[rand2];
			return 0;
		}
		normalizepos(pos);
		p->x = pos.x;
		p->y = pos.y;
		return 1;
	}
}
