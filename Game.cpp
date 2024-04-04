#include "Game.h"
#include "Const.h"
#include <windows.h>
using namespace std;

int gr_c = 0;
int herb_c = 0;
int pred_c = 0;
int CheckNeighbours(Position &p);
vector<Position> free_space;
int baby_born = 0;

Game::Game()
{
	tick = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			world[i][j].cont = content::empty;
			world[i][j].index = -1;
		}

	//preset: 10 food, 4 civilians, 2 invaders

	// preset: 10 food, 4 civilians, 2 invaders
	srand(clock());
	for (int i = 0; i < start_grass_count; i++)
	{
		int y = rand() % height;
		int x = rand() % width;
		while (world[y][x].cont != content::empty)
		{
			y = rand() % height;
			x = rand() % width;
		}
		grass.push_back(Grass(x, y));
		gr_c++;																// GRASS COUNT
		cout << "GRASS: " << gr_c << " POS: X Y " << x << " " << y << endl; // SHOW GRASS COORD
		// todo: check if this position is full
		int s = grass.size() - 1;
		world[grass[s].pos.y][grass[s].pos.x].cont = content::gr;
		world[grass[s].pos.y][grass[s].pos.x].index = s;
	}
	for (int i = 0; i < start_herb_count; i++)
	{
	for (size_t i = 0; i < start_herb_count; i++)
	{
		int y = rand() % height;
		int x = rand() % width;
		while (world[y][x].cont != content::empty)
		{
			y = rand() % height;
			x = rand() % width;
		}
		herb.push_back(Herbivorous(x, y, herb_startstarve, herb_speed, herb_rad));
		herb_c++;
		cout << "HERB: " << herb_c << " POS: X Y " << x << " " << y << endl; // SHOW GRASS COORD
		// todo: check if this position is full
		int s = herb.size() - 1;
		world[herb[s].pos.y][herb[s].pos.x].cont = content::herbivorous;
		world[herb[s].pos.y][herb[s].pos.x].index = s;
	}

	for (int i = 0; i < start_pred_count; i++)
	{
		int y = rand() % height;
		int x = rand() % width;
		while (world[y][x].cont != content::empty)
		{
			y = rand() % height;
			x = rand() % width;
		}
		pred.push_back(Predator(x, y, pred_startstarve, pred_speed, pred_rad));
		pred_c++;
		// todo: check if this position is full
		int s = pred.size() - 1;
		world[pred[s].pos.y][pred[s].pos.x].cont = content::predator;
		world[pred[s].pos.y][pred[s].pos.x].index = s;
	}
	printworld();
}

void Game::printworld()
{
	system("cls");
	cout << "started to print world at tick " << tick << endl;
	// if (baby_born)
	// cout << "baby had born at this tick" << endl;
	// Sleep(100);
	cout << "herb.size " << herb.size() << endl;
	cout << "grass.size " << grass.size() << endl;
	cout << "pred.size " << pred.size() << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			switch (world[i][j].cont)
			{
			case content::empty:
				std::cout << '_';
				break;
			case content::gr:
				std::cout << GREEN << "*" << RESET;
				break;
			case content::herbivorous:
				std::cout << ORANGE << '&' << RESET;
				herb[world[i][j].index].set_mark(0);
				break;
			case content::predator:
				std::cout << BLUE << '#' << RESET;
				pred[world[i][j].index].set_mark(0);
				break;
			default:
				std::cout << '!';
				break;
			}
		}
		std::cout << "\n";
	}
}

void Game::start()
{
	int msg;

	while (true) { //all speices of objs in map condition?
		++tick;
		if (grass.empty()) {

	while (true)
	{ // all speices of objs in map condition?
		tick++;
		if (grass.empty())
		{
			cout << "The world has perished because the grass has run out." << endl;
			break;
		}
		if (herb.empty())
		{
			cout << "The world has perished because the herbivores have run out." << endl;
			break;
		}
		
		if (pred.empty()) {
		if (pred.empty())
		{
			cout << "The world has perished because the predators have run out." << endl;
			break;
		}
		int total_cells = height * width;
		double occupied_percentage = (static_cast<double>(grass.size() + herb.size() + pred.size()) / total_cells) * 100;
		if (occupied_percentage >= 90)
		{
			cout << "The world has perished due to overpopulation." << endl;
			break;
		};
		baby_born = 0;
		Position newp, eat, sex, enemy;
		//for (int i = 0; i < grass.size(); i++) 
		// for (size_t i = 0; i < grass.size(); i++)
		//{
		//	msg = grass[i].act(&newp, &eat, &sex, &enemy);
		//	if (msg == -1)
		//	{
		//		world[grass[i].pos.y][grass[i].pos.x] = content::empty; //NEED TO CHECK Y and X
		//		grass.erase(grass.begin() + i);//change the state of the cell
		//	}
		//	else if (msg == 1)
		//	{
		//
		//		while (world[newp.y][newp.x] != content::empty) //NEED TO CHECK Y and X
		//		{
		//			grass[i].act_(&newp, &eat, &sex, &enemy);
		//		}
		//		world[newp.y][newp.x] = content::gr;
		//		grass.push_back(Grass(newp.x, newp.y)); //NEED TO CHECK Y and X

		//	}
		//}

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				// replace that if switch after tests
				if (world[i][j].cont == content::gr)
				{
					msg = grass[world[i][j].index].act(&newp, &eat, &sex, &enemy);
					if (msg == -1)
					{
						//delete_grass(world[i][j].index);
						grass.erase(grass.begin() + world[i][j].index);//change the state of the cell
						world[i][j].cont = content::empty;				// NEED TO CHECK Y and X
						grass.erase(grass.begin() + world[i][j].index); // change the state of the cell
						int s = grass.size();
						for (int k = world[i][j].index; k < s; ++k)
						{
							world[grass[k].pos.y][grass[k].pos.x].index -= 1;
							// if (world[grass[k].pos.y][grass[k].pos.x].index < 0)
							//	cout << "grass dying negative index" << endl;
						}
						world[i][j].cont = content::empty; //NEED TO CHECK Y and X
						world[i][j].index = -1;
					}
					else if (msg == 1)
					{
						int count_neighbours = 0;
						while (world[newp.y][newp.x].cont != content::empty) //NEED TO CHECK Y and X 
						int count_neighbours = 0;
						while (world[newp.y][newp.x].cont != content::empty) // NEED TO CHECK Y and X
						{
							grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
							++count_neighbours;
							if (count_neighbours > 9) break;
							++count_neighbours;
							if (count_neighbours > 9)
								break;
						}
						//TO DO: remove the endless loop
						if (count_neighbours < 10)
						{
							world[newp.y][newp.x].cont = content::gr;
							grass.push_back(Grass(newp.x, newp.y)); //NEED TO CHECK Y and X 
							world[newp.y][newp.x].index = grass.size() - 1;
						}

						// TO DO: remove the endless loop
						if (count_neighbours < 10)
						{
							world[newp.y][newp.x].cont = content::gr;
							grass.push_back(Grass(newp.x, newp.y)); // NEED TO CHECK Y and X
							world[newp.y][newp.x].index = grass.size() - 1;
						}
					}
				}
				if (world[i][j].cont == content::herbivorous && herb[world[i][j].index].get_mark() != 1)
				{
					//cout << "herb y x " << i << " " << j << " is ready to do a step" << endl;
					eat = herb[world[i][j].index].check_vision(grass, 0);
					sex = herb[world[i][j].index].check_vision(herb, 1);
					enemy = herb[world[i][j].index].check_vision(pred, 0);
					newp.x = -1;
					newp.y = -1;
				{
					// cout << "herb y x " << i << " " << j << " is ready to do a step" << endl;
					eat = herb[world[i][j].index].check_vision(grass, 0);
					sex = herb[world[i][j].index].check_vision(herb, 1);
					enemy = herb[world[i][j].index].check_vision(pred, 0);
					msg = herb[world[i][j].index].act(&newp, &eat, &sex, &enemy); // we change y x of this herb
					if (msg == 1)
					{
						herb_c -= 1;
						world[i][j].cont = content::empty;
						herb.erase(herb.begin() + world[i][j].index);
						int s = herb.size();
						for (int k = world[i][j].index; k < s; ++k)
						{
							world[herb[k].pos.y][herb[k].pos.x].index -= 1;
							// if (world[herb[k].pos.y][herb[k].pos.x].index < 0)
							//	cout << "herb dying negative index" << endl;
						}
						world[i][j].index = -1;
					}
					else if (msg == 1)
					{
						if (world[newp.y][newp.x].cont == content::gr)
						{
							gr_c -= 1;
							//delete_grass(world[newp.y][newp.x].index);
							gr_c -= 1;
							grass.erase(grass.begin() + world[newp.y][newp.x].index);
							int s = grass.size();
							for (int k = world[newp.y][newp.x].index; k < s; ++k)
							{
								world[grass[k].pos.y][grass[k].pos.x].index -= 1;
								// if (world[grass[k].pos.y][grass[k].pos.x].index < 0)
								//	cout << "grass eating negative index" << endl;
							}
							herb[world[i][j].index].increase_starve();
							herb[world[i][j].index].set_mark(1);
							herb[world[i][j].index].pos = newp;
							world[newp.y][newp.x].cont = content::herbivorous; // change the state of world's state
							world[newp.y][newp.x].index = world[i][j].index;
							world[i][j].cont = content::empty;
							world[i][j].index = -1;
						}
						else if (world[newp.y][newp.x].cont == content::herbivorous && herb[world[newp.y][newp.x].index].get_birth_cooldown() >= to_birth && herb[world[i][j].index].get_birth_cooldown() >= to_birth) // todo: set 0 birth cooldown after making a baby
						{
							// std::cout << "herb in act met, trying to make a baby. herb acting y,x are " << i << " " << j <<  endl;
							if (free_space.size() != 0)
								free_space.erase(free_space.begin(), free_space.end() - 1);
							for (int i_index = -2; i_index <= 2; ++i_index)
								for (int j_index = -2; j_index <= 2; ++j_index)
								{
									if (world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content::herbivorous &&
										world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content::predator) // ignore grass
									{
										Position current_free;
										current_free.y = (newp.y + i_index) % height;
										current_free.x = (newp.x + j_index) % width;
										free_space.push_back(current_free);
									}
								}
							// std::cout << "free_space is initialized" << endl;
							if (free_space.size() >= 1)
							{

								int pick_space = rand() % free_space.size(); // pick random in free_space
								// std::cout << "pick_space is initialized" << endl;
								//  lets make a baby first
								if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::empty) // if no grass here
								{
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::herbivorous;
									herb.push_back(Herbivorous(free_space[pick_space].x, free_space[pick_space].y, herb_startstarve, herb_speed, herb_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = herb.size() - 1;
									herb[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
								}
								else if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::gr) // grass here, need to delete it first
								{
									//delete_grass(world[free_space[pick_space].y][free_space[pick_space].x].index);
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::herbivorous;

									grass.erase(grass.begin() + world[free_space[pick_space].y][free_space[pick_space].x].index);//change the state of the cell
									grass.erase(grass.begin() + world[free_space[pick_space].y][free_space[pick_space].x].index); // change the state of the cell
									int s = grass.size();
									for (int k = world[free_space[pick_space].y][free_space[pick_space].x].index; k < s; ++k)
										world[grass[k].pos.y][grass[k].pos.x].index -= 1;
									herb.push_back(Herbivorous(free_space[pick_space].x, free_space[pick_space].y, herb_startstarve, herb_speed, herb_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = herb.size() - 1;
									herb[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
									herb[world[free_space[pick_space].y][free_space[pick_space].x].index].set_birth_cooldown(0);
								}
								// cout << "baby has born at " << free_space[pick_space].y << " " << free_space[pick_space].x << endl;
								free_space.erase(free_space.begin() + pick_space);

								//		// end of making a baby

								herb[world[i][j].index].pos.y = i; // save coords so the second parent wont move
								herb[world[i][j].index].pos.x = j;
								herb[world[i][j].index].set_mark(1);
								herb[world[i][j].index].set_birth_cooldown(0);

								// lets mark the first parent as 1
								herb[world[newp.y][newp.x].index].set_mark(1);
								herb[world[newp.y][newp.x].index].set_birth_cooldown(0);
							}
							else
								// cout << "making baby failed, no space for baby" << endl;
								continue; // continue if no free space for create a baby
						}
						else if (world[newp.y][newp.x].cont == content::empty) // empty cell met
						{
							herb[world[i][j].index].set_mark(1);
							herb[world[i][j].index].pos = newp;
							world[newp.y][newp.x].cont = content::herbivorous; // change the state of world's state
							world[newp.y][newp.x].index = world[i][j].index;
							world[i][j].cont = content::empty;
							world[i][j].index = -1;
						}
						//while (world[newp.y][newp.x].cont != content::empty)
						//{
							//grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
						//}
						/*herb_c++;
						world[newp.y][newp.x].cont = content::herbivorous;
						herb.push_back(Herbivorous(newp.x, newp.y, herb_starving, herb_speed, herb_rad));
						world[newp.y][newp.x].index = herb.size() - 1;*/


					}
					else if (msg == -1)
					{
						herb_c -= 1;
						//delete_herb(world[i][j].index);
						world[i][j].cont = content::empty;
						herb.erase(herb.begin() + world[i][j].index);
						int s = herb.size();
						for (int k = 0; k < s; ++k)
						{
							world[herb[k].pos.y][herb[k].pos.x].cont = content::herbivorous;
							world[herb[k].pos.y][herb[k].pos.x].index = k;
							//if (world[herb[k].pos.y][herb[k].pos.x].index < 0)
							//	cout << "herb dying negative index" << endl;
						}
						world[i][j].index = -1;
					}

				}
				if (world[i][j].cont == content::predator && pred[world[i][j].index].get_mark() != 1)
				{
					// cout << "herb y x " << i << " " << j << " is ready to do a step" << endl;
					eat = pred[world[i][j].index].check_vision(herb, 0);
					sex = pred[world[i][j].index].check_vision(pred, 1);
					msg = pred[world[i][j].index].act(&newp, &eat, &sex, &enemy); // we change y x of this herb

					if (msg == 1)
					{
						if (world[newp.y][newp.x].cont == content::herbivorous)
						{
							herb_c -= 1;
							herb.erase(herb.begin() + world[newp.y][newp.x].index);
							int s = herb.size();
							for (int k = world[newp.y][newp.x].index; k < s; ++k)
							{
								world[herb[k].pos.y][herb[k].pos.x].index -= 1;
								// if (world[grass[k].pos.y][grass[k].pos.x].index < 0)
								//	cout << "grass eating negative index" << endl;
							}
							pred[world[i][j].index].increase_starve();
							pred[world[i][j].index].set_mark(1);
							pred[world[i][j].index].pos = newp;
							world[newp.y][newp.x].cont = content::predator; // change the state of world's state
							world[newp.y][newp.x].index = world[i][j].index;
							world[i][j].cont = content::empty;
							world[i][j].index = -1;
						}
						else if (world[newp.y][newp.x].cont == content::predator && pred[world[newp.y][newp.x].index].get_birth_cooldown() >= to_birth && pred[world[i][j].index].get_birth_cooldown() >= to_birth) // todo: set 0 birth cooldown after making a baby
						{
							// std::cout << "herb in act met, trying to make a baby. herb acting y,x are " << i << " " << j <<  endl;
							if (free_space.size() != 0)
								free_space.erase(free_space.begin(), free_space.end() - 1);
							for (int i_index = -2; i_index <= 2; ++i_index)
								for (int j_index = -2; j_index <= 2; ++j_index)
								{
									if (world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content::gr &&
										world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content::predator) // ignore grass
									{
										Position current_free;
										current_free.y = (newp.y + i_index) % height;
										current_free.x = (newp.x + j_index) % width;
										free_space.push_back(current_free);
									}
								}
							// std::cout << "free_space is initialized" << endl;
							if (free_space.size() >= 1)
							{

								int pick_space = rand() % free_space.size(); // pick random in free_space
								// std::cout << "pick_space is initialized" << endl;
								//  lets make a baby first
								if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::empty) // if no grass here
								{
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::predator;
									pred.push_back(Predator(free_space[pick_space].x, free_space[pick_space].y, pred_startstarve, pred_speed, pred_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = pred.size() - 1;
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
								}
								else if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::herbivorous) // grass here, need to delete it first
								{
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::predator;
									herb.erase(herb.begin() + world[free_space[pick_space].y][free_space[pick_space].x].index); // change the state of the cell
									int s = herb.size();
									for (int k = world[free_space[pick_space].y][free_space[pick_space].x].index; k < s; ++k)
										world[herb[k].pos.y][herb[k].pos.x].index -= 1;
									pred.push_back(Predator(free_space[pick_space].x, free_space[pick_space].y, pred_startstarve, pred_speed, pred_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = pred.size() - 1;
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_birth_cooldown(0);
								}
								// cout << "baby has born at " << free_space[pick_space].y << " " << free_space[pick_space].x << endl;
								free_space.erase(free_space.begin() + pick_space);

								// end of making a baby

								pred[world[i][j].index].pos.y = i; // save coords so the second parent wont move
								pred[world[i][j].index].pos.x = j;
								pred[world[i][j].index].set_mark(1);
								pred[world[i][j].index].set_birth_cooldown(0);

								// lets mark the first parent as 1
								pred[world[newp.y][newp.x].index].set_mark(1);
								pred[world[newp.y][newp.x].index].set_birth_cooldown(0);
							}
							else
								// cout << "making baby failed, no space for baby" << endl;
								continue; // continue if no free space for create a baby
						}
						else if (world[newp.y][newp.x].cont == content::gr) {
							gr_c -= 1;
							grass.erase(grass.begin() + world[newp.y][newp.x].index);
							int s = grass.size();
							for (int k = world[newp.y][newp.x].index; k < s; ++k)
							{
								world[grass[k].pos.y][grass[k].pos.x].index -= 1;
								//if (world[grass[k].pos.y][grass[k].pos.x].index < 0)
								//	cout << "grass eating negative index" << endl;
							}
							world[newp.y][newp.x].cont = content::predator;
							world[newp.y][newp.x].index = world[i][j].index;
							pred[world[i][j].index].pos = newp;
							world[i][j].index = -1;
							world[i][j].cont = content::empty;
							pred[world[newp.y][newp.x].index].set_mark(1);
						}
						else if (world[newp.y][newp.x].cont == content::empty) // empty cell met
						{
							world[newp.y][newp.x].cont = content::predator;
							world[newp.y][newp.x].index = world[i][j].index;
							pred[world[i][j].index].pos = newp;
							world[i][j].index = -1;
							world[i][j].cont = content::empty;
							pred[world[newp.y][newp.x].index].set_mark(1);
						}
						//	//while (world[newp.y][newp.x].cont != content::empty)
						//	//{
						//		//grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
						//	//}
						//	herb_c++;
						//	world[newp.y][newp.x].cont = content::herbivorous;
						//	herb.push_back(Herbivorous(newp.x, newp.y, herb_starving, herb_speed, herb_rad));
						//	world[newp.y][newp.x].index = herb.size() - 1;
						//	//while (world[newp.y][newp.x].cont != content::empty)
						//	//{
						//		//grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
						//	//}
						//	herb_c++;
						//	world[newp.y][newp.x].cont = content::herbivorous;
						//	herb.push_back(Herbivorous(newp.x, newp.y, herb_starving, herb_speed, herb_rad));
						//	world[newp.y][newp.x].index = herb.size() - 1;
					}
				}

				if (world[i][j].cont == content::predator && pred[world[i][j].index].get_mark() != 1)
				{
					// cout << "herb y x " << i << " " << j << " is ready to do a step" << endl;
					eat = pred[world[i][j].index].check_vision(herb, 0);
					sex = pred[world[i][j].index].check_vision(pred, 1);
					msg = pred[world[i][j].index].act(&newp, &eat, &sex, &enemy); // we change y x of this herb
					if (msg == -1)
					{
						pred_c -= 1;
						world[i][j].cont = content::empty;
						pred.erase(pred.begin() + world[i][j].index);
						int s = pred.size();
						for (int k = world[i][j].index; k < s; ++k)
						{
							world[pred[k].pos.y][pred[k].pos.x].index -= 1;
							// if (world[herb[k].pos.y][herb[k].pos.x].index < 0)
							//	cout << "herb dying negative index" << endl;
						}
						world[i][j].index = -1;
					}
					else if (msg == 1)
					{
						if (world[newp.y][newp.x].cont == content::herbivorous)
						{
							herb_c -= 1;
							herb.erase(herb.begin() + world[newp.y][newp.x].index);
							int s = herb.size();
							for (int k = world[newp.y][newp.x].index; k < s; ++k)
							{
								world[herb[k].pos.y][herb[k].pos.x].index -= 1;
								// if (world[grass[k].pos.y][grass[k].pos.x].index < 0)
								//	cout << "grass eating negative index" << endl;
							}
							pred[world[i][j].index].increase_starve();
							pred[world[i][j].index].set_mark(1);
							world[newp.y][newp.x].cont = content::predator; // change the state of world's state
							world[newp.y][newp.x].index = world[i][j].index;
							world[i][j].cont = content::empty;
							world[i][j].index = -1;
						}
						else if (world[newp.y][newp.x].cont == content::predator && pred[world[newp.y][newp.x].index].get_birth_cooldown() >= to_birth && pred[world[i][j].index].get_birth_cooldown() >= to_birth) // todo: set 0 birth cooldown after making a baby
						{
							// std::cout << "herb in act met, trying to make a baby. herb acting y,x are " << i << " " << j <<  endl;
							if (free_space.size() != 0)
								free_space.erase(free_space.begin(), free_space.end() - 1);
							for (int i_index = -2; i_index <= 2; ++i_index)
								for (int j_index = -2; j_index <= 2; ++j_index)
								{
									if (world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content:: &&
										world[(newp.y + i_index) % height][(newp.x + j_index) % width].cont != content::predator) // ignore grass
									{
										Position current_free;
										current_free.y = (newp.y + i_index) % height;
										current_free.x = (newp.x + j_index) % width;
										free_space.push_back(current_free);
									}
								}
							// std::cout << "free_space is initialized" << endl;
							if (free_space.size() >= 1)
							{

								int pick_space = rand() % free_space.size(); // pick random in free_space
								// std::cout << "pick_space is initialized" << endl;
								//  lets make a baby first
								if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::empty) // if no grass here
								{
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::predator;
									pred.push_back(Predator(free_space[pick_space].x, free_space[pick_space].y, pred_startstarve, pred_speed, pred_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = pred.size() - 1;
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
								}
								else if (world[free_space[pick_space].y][free_space[pick_space].x].cont == content::herbivorous) // grass here, need to delete it first
								{
									world[free_space[pick_space].y][free_space[pick_space].x].cont = content::predator;
									herb.erase(herb.begin() + world[free_space[pick_space].y][free_space[pick_space].x].index); // change the state of the cell
									int s = herb.size();
									for (int k = world[free_space[pick_space].y][free_space[pick_space].x].index; k < s; ++k)
										world[herb[k].pos.y][herb[k].pos.x].index -= 1;
									pred.push_back(Predator(free_space[pick_space].x, free_space[pick_space].y, pred_startstarve, pred_speed, pred_rad)); // create a baby
									world[free_space[pick_space].y][free_space[pick_space].x].index = pred.size() - 1;
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_mark(1); // mark it as 1
									pred[world[free_space[pick_space].y][free_space[pick_space].x].index].set_birth_cooldown(0);
								}
								// cout << "baby has born at " << free_space[pick_space].y << " " << free_space[pick_space].x << endl;
								free_space.erase(free_space.begin() + pick_space);

								// end of making a baby

								pred[world[i][j].index].pos.y = i; // save coords so the second parent wont move
								pred[world[i][j].index].pos.x = j;
								pred[world[i][j].index].set_mark(1);
								pred[world[i][j].index].set_birth_cooldown(0);

								// lets mark the first parent as 1
								pred[world[newp.y][newp.x].index].set_mark(1);
								pred[world[newp.y][newp.x].index].set_birth_cooldown(0);
							}
							else
								// cout << "making baby failed, no space for baby" << endl;
								continue; // continue if no free space for create a baby
						}
						else if (world[newp.y][newp.x].cont == content::empty) // empty cell met
						{
							world[newp.y][newp.x].cont = content::predator;
							world[newp.y][newp.x].index = world[i][j].index;
							world[i][j].index = -1;
							world[i][j].cont = content::empty;
							pred[world[newp.y][newp.x].index].set_mark(1);
						}
						//	//while (world[newp.y][newp.x].cont != content::empty)
						//	//{
						//		//grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
						//	//}
						//	herb_c++;
						//	world[newp.y][newp.x].cont = content::herbivorous;
						//	herb.push_back(Herbivorous(newp.x, newp.y, herb_starving, herb_speed, herb_rad));
						//	world[newp.y][newp.x].index = herb.size() - 1;
					}
					else if (msg == -1)
					{
						pred_c -= 1;
						world[i][j].cont = content::empty;
						pred.erase(pred.begin() + world[i][j].index);
						int s = pred.size();
						for (int k = world[i][j].index; k < s; ++k)
						{
							world[pred[k].pos.y][pred[k].pos.x].index -= 1;
							// if (world[herb[k].pos.y][herb[k].pos.x].index < 0)
							//	cout << "herb dying negative index" << endl;
						}
						world[i][j].index = -1;
					}
				}
			}
		}
				}
			}
		}

		// check the worst cases when someone dies or full world etc.
		// add the logic of other species
		Sleep(1);
		printworld();
		cout << "\n" << tick << "\n";
		cout << "\n"
			 << tick << "\n";
		cout << "herb number " << herb.size() << endl;
		cout << "grass number " << grass.size() << endl;
		Sleep(100);
	}
}

void Game::delete_grass(int index)
{
	int s = grass.size();
	if (index < s && index >= 0) {
		world[grass[index].pos.y][grass[index].pos.x].cont = content::empty;
		world[grass[index].pos.y][grass[index].pos.x].index = -1;

		Grass temp = grass[index];
		grass[index] = grass[s - 1];
		grass[s - 1] = temp;
		grass.pop_back();

		world[grass[index].pos.y][grass[index].pos.x].index = index;
	}
}

void Game::delete_herb(int index)
{
	int s = herb.size();
	if (index < s && index >= 0) {
		world[herb[index].pos.y][herb[index].pos.x].cont = content::empty;
		world[herb[index].pos.y][herb[index].pos.x].index = -1;

		Herbivorous temp = herb[index];
		herb[index] = herb[s - 1];
		herb[s - 1] = temp;
		herb.pop_back();

		world[herb[index].pos.y][herb[index].pos.x].index = index;
	}
}

void Game::delete_pred(int index)
{
	int s = pred.size();
	if (index < s && index >= 0) {
		world[pred[index].pos.y][pred[index].pos.x].cont = content::empty;
		world[pred[index].pos.y][pred[index].pos.x].index = -1;

		Predator temp = pred[index];
		pred[index] = pred[s - 1];
		pred[s - 1] = temp;
		pred.pop_back();

		world[pred[index].pos.y][pred[index].pos.x].index = index;
	}
}


int CheckNeighbours(Position& p) //TODO
int CheckNeighbours(Position &p) // TODO
{
	return 0;
}
