#include "Herbivorous.h"
#include "Const.h"
#include <fstream>

//#define SIZE 3

Herbivorous::Herbivorous(int x, int y, int st, int sp, int radius) :Animal(sp, radius, st)
{
	pos.x = x;
	pos.y = y;
}

int Herbivorous::act(Position* p, Position* eat, Position* sex, Position* enemy)
{
	//int arr[SIZE] = { -1, 0, 1 };
	//int rand1 = rand() % 3;
	//int rand2 = rand() % 3;
	age++;
	starve--;
	birth_cooldown++;
	if (starve <= 0 || age > herb_age)
	{
		std::ofstream out("output.txt", std::ios::app);
		out << "herb died at age " << age << " position " << pos.x << " " << pos.y << " starve " << starve << "\n";
		out.close();
		return -1;
	}
	if (age % herb_speed == 0) {
		if (enemy->x != -1 && enemy->y != -1) {
			/*if (pos.x < enemy->x)
			{
				pos.x -= 1;
			}
			else if (pos.x > enemy->x)
			{
				pos.x += 1;
			}
			else
				pos.x += 0;

			if (pos.y < enemy->y)
			{
				pos.y -= 1;
			}
			else if (pos.y > enemy->y)
			{
				pos.y += 1;
			}
			else
				pos.y += 0;*/
			p->x = pos.x - (pos.x <= enemy->x) * 2 - 1; //opposite moving, minus
			p->y = pos.y - (pos.y <= enemy->y) * 2 - 1;
		}
		else if (starve <= herb_starving && eat->x != -1 && eat->y != -1) {

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

			p->x = pos.x + (pos.x <= eat->x) * 2 - 1; //straight moving, plus
			p->y = pos.y + (pos.y <= eat->y) * 2 - 1;
		}
		else if (sex->x != -1 && sex->y != -1 && sex->x != pos.x && sex->y != pos.y && age >= birth_age && birth_cooldown >= to_birth) {
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
			p->x = pos.x + (pos.x <= sex->x) * 2 - 1;
			p->y = pos.y + (pos.y <= sex->y) * 2 - 1;
		}
		else {
			//pos.x += arr[rand1];
			//pos.y += arr[rand2];
			return 0;
		}
		normalizepos(*p);
		/*p->x = pos.x;
		p->y = pos.y;*/
		return 1;
	}
	return 0;
}
