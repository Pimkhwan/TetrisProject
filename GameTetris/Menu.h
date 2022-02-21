#pragma once
#include <sfml\Graphics.hpp>
#define MAX_ITEM 3 //start leaderbaord exit 
class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void drawMenu(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEM];
};