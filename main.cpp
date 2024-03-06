#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <SFML/Graphics.hpp>

void get_random_cords(int& x, int& y, sf::RenderWindow &window, sf::Image grass_image) // calculate random grass coordinates
{
	x = rand() % (window.getSize().x - grass_image.getSize().x - 0 + 1) + 0; // from 0 to (window length - image length)
	y = rand() % (window.getSize().y - grass_image.getSize().y - 0 + 1) + 0; // from 0 to (window width - image width)
	std::cout << "x: " << x << " y: " << y << std::endl;
}
void remark_grass(std::vector<std::vector<int>> &field, int& x, int& y) // remark grass area
{
	// My last variant - remark only the dot of grass:
	field[y][x] = 1; // grass number
	/* My first variant - remark all grass area:
	for (int i = y; i < 75 + y; ++i)
	{
		for (int j = x; j < 100 + x; ++j)
		{
			field[i][j] = 1; // set grass
		}
	}
	*/
}
void delete_grass(std::vector<std::vector<int>>& field, int& x, int& y) // delete grass area
{
	// My last variant - delete only the dot of grass:
	field[y][x] = 0;
	/* My first variant - delete all grass area:
	for (int i = y; i < 75 + y; ++i)
	{
		for (int j = x; j < 100 + x; ++j)
		{
			field[i][j] = 0; // set grass
		}
	}
	*/
}
void set_grass(int count, std::vector<std::vector<int>>& field, std::vector<sf::Sprite>& arr, sf::Sprite grass, int& i, std::vector<std::pair<int, int>>& c, sf::RenderWindow& window, sf::Image grass_image)
{
	while (count > 0)
	{
		int x = 0, y = 0;
		get_random_cords(x, y, window, grass_image);
		while (field[y][x] == 1) // while grass area
		{
			srand(time(0));
			get_random_cords(x, y, window, grass_image);
		}
		c.push_back(std::make_pair(y, x)); // coordinates from field for each grass 
		//Create grass arr
		arr.push_back(grass);
		arr[i].setPosition(x, y);
		remark_grass(field, x, y);
		count -= 1;
		i += 1;
	}
}

int main()
{
	int count_grass = 0; // start value for grass
	int life_time = 3000; // 3000 iterations
	int die_next = life_time; // time at which previous grass group dies
	std::queue<int> die; // queue of die next time
	die.push(die_next);
	int grow_time = 2000; // in which iteration new grass created
	int i = 0;
	int die_index = 0; // index from which the dying grass begin
	int iterator = 0; // main loop counter

	std::cout << "How much grass do you want: ";
	std::cin >> count_grass;

	//int count_die = count_grass;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Dinosaurs world"); // play screen 1000 x 600 pixels
	//Create a field 1000 x 600 cells
	std::vector<std::vector<int>> field(600, std::vector<int> (1000, 0)); // 0 - has not elements, 1 - it is a grass
	std::vector<std::pair<int, int>> coordinates; // coordinates from field for each grass

	// Background
	sf::Texture background;
	background.loadFromFile("project_images/ground_3.png");
	sf::Sprite back_image(background);
	//Grass
	sf::Image grass_image;
	grass_image.loadFromFile("project_images/grass_6_1.png");
	sf::Texture grass_texture;
	grass_texture.loadFromImage(grass_image);
	sf::Sprite grass_sprite(grass_texture);
	std::vector<sf::Sprite> grass_arr; // grass array
	set_grass(count_grass, field, grass_arr, grass_sprite, i, coordinates, window, grass_image);
	// Dino (for example)
	sf::Image dino_image;
	dino_image.loadFromFile("project_images/brown_dino_right.png");
	sf::Texture dino_texture;
	dino_texture.loadFromImage(dino_image);
	sf::Sprite dino_sprite(dino_texture);
	dino_sprite.setPosition(80, 80);

	// the main loop of game
	while (window.isOpen())
	{
		iterator += 1;
		if (iterator % grow_time == 0) // check time in which we should create new grass
		{
			set_grass(count_grass, field, grass_arr, grass_sprite, i, coordinates, window, grass_image);
			die.push(iterator + life_time); // time when this grass will die
		}
		if (iterator == die.front()) // check time in which grass die
		{
			die.pop();
			for (int i = die_index; i < die_index + count_grass; ++i)
			{
				delete_grass(field, coordinates[i].second, coordinates[i].first);
			}
			die_index += count_grass; // we move index to next dying grass group
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(back_image);
		for (int i = die_index; i < grass_arr.size(); ++i)
		{
			window.draw(grass_arr[i]);
		}
		window.draw(dino_sprite);
		window.display();
	}
	return 0;
}