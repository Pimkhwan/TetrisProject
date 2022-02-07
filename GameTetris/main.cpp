#include <SFML/Graphics.hpp>

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
