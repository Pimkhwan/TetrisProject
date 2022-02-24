#pragma once
#include <sfml\Graphics.hpp>
#define MAX_ITEM 3 //start leaderbaord exit 

using namespace sf;

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void drawMenu(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

private:
	int selectedItem = 0;
	Font font;
	Text menu[MAX_ITEM];
};