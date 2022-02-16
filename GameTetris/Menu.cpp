#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("AGoblinAppears-o2aV.ttf")) {

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(72);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 3));
}
Menu::~Menu() {

}

void Menu::drawMenu(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_ITEM; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItem - 1 >= 0) {
		menu[selectedItem].setFillColor(sf::Color::White);
			selectedItem--;
			menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::Movedown() {
	if (selectedItem + 1 < MAX_ITEM) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}