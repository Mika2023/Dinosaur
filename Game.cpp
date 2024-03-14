#include "Game.h"
const int start_grass_count = 10;
const int start_herb_count = 4;
const int start_pred_count = 2;

Game::Game()
{
	tick = 0;
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			world[i][j] = content::empty;
	//preset: 10 food, 4 civilians, 2 invaders
	srand(clock());
	for (size_t i = 0; i < start_grass_count; i++) {
		grass.push_back(Grass(rand() % width, rand() % height));
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
	system("cls");
	Sleep(100);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			switch (world[i][j])
			{
			case content::empty:
				std::cout << '_';
				break;
			case content::gr:
				std::cout << '*';
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

		for (size_t i = 0; i < grass.size(); i++) {
			msg = grass[i].act(&newp, &eat, &sex, &enemy);
			if (msg == -1) grass.erase(grass.begin() + i);//change the state of the cell
			else if (msg == 1) grass.push_back(Grass(newp.x, newp.y));
		}

		//check the worst cases when someone dies or full world etc.
		//add the logic of other species
		//Sleep(2000);
		printworld();
		Sleep(1000);
	}
}
