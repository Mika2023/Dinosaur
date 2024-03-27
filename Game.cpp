#include "Game.h"
#include "Const.h"



int gr_c = 0;
int herb_c = 0;
int pred_c = 0;
int CheckNeighbours(Position& p);

Game::Game()
{
	tick = 0;
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			world[i][j].cont = content::empty;
			world[i][j].index = -1;
		}
			
	//preset: 10 food, 4 civilians, 2 invaders
	srand(clock());
	for (size_t i = 0; i < start_grass_count; i++)
	{
		int y = rand() % height;
		int x = rand() % width;
		while (world[y][x].cont != content::empty)
		{
			y = rand() % height;
			x = rand() % width;
		}
		grass.push_back(Grass(x, y));
		gr_c++; // GRASS COUNT
		cout << "GRASS: " << gr_c << " POS: X Y " << x << " " << y << endl; // SHOW GRASS COORD
		//todo: check if this position is full
		int s = grass.size() - 1;
		world[grass[s].pos.y][grass[s].pos.x].cont = content::gr;
		world[grass[s].pos.y][grass[s].pos.x].index = s;
	}
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
		//todo: check if this position is full
		int s = herb.size() - 1;
		world[herb[s].pos.y][herb[s].pos.x].cont = content::herbivorous;
		world[herb[s].pos.y][herb[s].pos.x].index = s;
	}

	for (size_t i = 0; i < start_pred_count; i++)
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
		//todo: check if this position is full
		int s = pred.size() - 1;
		world[pred[s].pos.y][pred[s].pos.x].cont = content::predator;
		world[pred[s].pos.y][pred[s].pos.x].index = s;
	}
	printworld();
}

void Game::printworld()
{
	//system("cls");
	Sleep(100);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			switch (world[i][j].cont)
			{
			case content::empty:
				std::cout << '_';
				break;
			case content::gr:
				std::cout << GREEN << '*' << RESET;
				break;
			case content::herbivorous:
				std::cout << ORANGE << '&' << RESET;
				herb[world[i][j].index].set_mark(0);
				break;
			case content::predator:
				std::cout << BLUE << '#' << RESET;
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
		tick++;
		Position newp, eat, sex, enemy;
		//for (size_t i = 0; i < grass.size(); i++) 
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
				//replace that if switch after tests
				if (world[i][j].cont == content::gr)
				{
					msg = grass[world[i][j].index].act(&newp, &eat, &sex, &enemy);
					if (msg == -1)
					{
						world[i][j].cont = content::empty; //NEED TO CHECK Y and X 
						grass.erase(grass.begin() + world[i][j].index);//change the state of the cell
						int s = grass.size();
						for (int k = world[i][j].index; k < s; ++k) world[grass[k].pos.y][grass[k].pos.x].index -= 1;
					}
					else if (msg == 1)
					{

						while (world[newp.y][newp.x].cont != content::empty) //NEED TO CHECK Y and X 
						{
							grass[world[i][j].index].act_(&newp, &eat, &sex, &enemy);
						}
						//TO DO: remove the endless loop
						world[newp.y][newp.x].cont = content::gr;
						grass.push_back(Grass(newp.x, newp.y)); //NEED TO CHECK Y and X 
						world[newp.y][newp.x].index = grass.size() - 1;

					}
				}
				if (world[i][j].cont == content::herbivorous && herb[world[i][j].index].get_mark() != 1)
				{	
					herb[world[i][j].index].set_mark(1);
					eat = herb[world[i][j].index].check_vision(grass,0);
					sex = herb[world[i][j].index].check_vision(herb,1);
					enemy = herb[world[i][j].index].check_vision(pred,0);
					msg = herb[world[i][j].index].act(&newp, &eat, &sex, &enemy);
					if (msg == -1)
					{
						herb_c -= 1;
						world[i][j].cont = content::empty;
						herb.erase(herb.begin() + world[i][j].index);
						int s = herb.size();
						for (int k = world[i][j].index; k < s; ++k)
						{
							world[herb[k].pos.y][herb[k].pos.x].index -= 1;
						}
					}
					else if (msg == 1)
					{
						if (world[newp.y][newp.x].cont == content::gr)
						{
							gr_c -= 1;	
							grass.erase(grass.begin() + world[newp.y][newp.x].index);
							int s = grass.size();
							for (int k = world[newp.y][newp.x].index; k < s; ++k)
							{
								world[grass[k].pos.y][grass[k].pos.x].index -= 1;
							}
							herb[world[i][j].index].increase_starve();
						}
						world[i][j].cont = content::empty;
						world[newp.y][newp.x].cont = content::herbivorous;
						world[newp.y][newp.x].index = world[i][j].index;
						world[i][j].index = -1;
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
			}
		}

		//check the worst cases when someone dies or full world etc.
		//add the logic of other species
		//Sleep(2000);
		printworld();
		cout << "\n";
		Sleep(1000);
	}
}


int CheckNeighbours(Position& p) //TODO
{
	return 0;
}
