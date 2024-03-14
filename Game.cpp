#include "Game.h"
#include "Const.h"
#define GREEN "\033[32m"
#define RESET "\033[0m"


int gr_c = 0;
int CheckNeighbours(Position& p);

Game::Game()
{
	tick = 0;
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			world[i][j] = content::empty;
	//preset: 10 food, 4 civilians, 2 invaders
	srand(clock());
	for (size_t i = 0; i < start_grass_count; i++)
	{
		int x = rand() % height;
		int y = rand() % width;
		while (world[y][x] != content::empty)
		{
			x = rand() % height;
			y = rand() % width;
		}
		grass.push_back(Grass(x, y));
		gr_c++; // GRASS COUNT
		cout << "GRASS: " << gr_c << " POS: X Y " << x << " " << y << endl; // SHOW GRASS COORD
		//todo: check if this position is full
		world[grass[grass.size() - 1].pos.y][grass[grass.size() - 1].pos.x] = content::gr;
	}


	/*for (size_t i = 0; i < start_herb_count; i++) {
		herb.push_back(Herbivorous(rand() % width, rand() % height));
		world[herb[herb.size() - 1].pos.y][herb[herb.size() - 1].pos.x] = content::herbivorous;
	}*/

	/*for (size_t i = 0; i < start_pred_count; i++) {
		pred.push_back(Predator(rand() % width, rand() % height));
		world[pred[pred.size() - 1].pos.y][pred[pred.size() - 1].pos.x] = content::predator;
	}*/
}

void Game::printworld()
{
	//system("cls");
	Sleep(100);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			switch (world[i][j])
			{
			case content::empty:
				std::cout << '_';
				break;
			case content::gr:
				std::cout << GREEN << '*' << RESET;
				break;
			case content::herbivorous:
				std::cout << '1';
				break;
			case content::predator:
				std::cout << '2';
				break;
			default:
				std::cout << '!';
				break;
			}
		}
		std::cout << std::endl;
	}
}


void Game::start()
{
	int msg;
	Position newp, eat, sex, enemy;
	while (true) { //all speices of objs in map condition?
		tick++;

		for (size_t i = 0; i < grass.size(); i++) 
		{
			msg = grass[i].act(&newp, &eat, &sex, &enemy);
			if (msg == -1)
			{
				world[grass[i].pos.x][grass[i].pos.y] = content::empty; //NEED TO CHECK Y and X 
				grass.erase(grass.begin() + i);//change the state of the cell
			}
			else if (msg == 1)
			{
				world[grass[i].pos.x][grass[i].pos.y] = content::gr;
				while (world[newp.x][newp.y] != content::empty) //NEED TO CHECK Y and X 
				{
					grass[i].act_(&newp, &eat, &sex, &enemy);
				}
					grass.push_back(Grass(newp.x, newp.y)); //NEED TO CHECK Y and X 

			}
		}



		//check the worst cases when someone dies or full world etc.
		//add the logic of other species
		//Sleep(2000);
		printworld();
		Sleep(1000000);
	}
}


int CheckNeighbours(Position& p) //TODO
{
	return 0;
}