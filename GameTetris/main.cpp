#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "header/Global.hpp"
int main()
{	
	//Used to check whether the game is over or not
	bool game_over = 0;
	//Is the hard drop button pressed?
	bool hard_drop_pressed = 0;
	//Is the rotate button pressed?
	bool rotate_pressed = 0;

	//Used to make the game framerate-independent
	unsigned lag = 0;
	//How many lines the player cleared?
	unsigned lines_cleared = 0;

	//Timer for the line clearing effect
	unsigned char clear_effect_timer = 0;
	//Gee, I wonder what this is
	unsigned char current_fall_speed = START_FALL_SPEED;
	//Timer for the tetromino falling
	unsigned char fall_timer = 0;
	//Timer for the tetromino moving horizontally
	unsigned char move_timer = 0;
	//Next shape (The shape that comes after the current shape)
	unsigned char next_shape;
	//Timer for the tetromino's soft drop
	unsigned char soft_drop_timer = 0;

	//Similar to lag, used to make the game framerate-independent
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	//I don't really know what this does, so I'm gonna assume this is a random device
	std::random_device random_device;

	//Random engine
	std::default_random_engine random_engine(random_device());

	//I KNOW THIS ONE! Distribution of all the shapes. We're gonna randomly choose one from them
	std::uniform_int_distribution<unsigned short> shape_distribution(0, 6);

	//Stores the current state of each row. Whether they need to be cleared or not
	std::vector<bool> clear_lines(ROWS, 0);

	//All the colors for the cells
	std::vector<sf::Color> cell_colors = {
		sf::Color(36, 36, 85),
		sf::Color(0, 219, 255),
		sf::Color(0, 36, 255),
		sf::Color(255, 146, 0),
		sf::Color(255, 219, 0),
		sf::Color(0, 219, 0),
		sf::Color(146, 0, 255),
		sf::Color(219, 0, 0),
		sf::Color(73, 73, 85)
	};

	//Game matrix. Everything will happen to this matrix
	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));

	//SFML thing. Stores events, I think
	sf::Event event;

	//Window
	sf::RenderWindow window(sf::VideoMode(2 * CELL_SIZE * COLUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close);
	//Resizing the window
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}
