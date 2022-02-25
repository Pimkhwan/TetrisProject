#include "HowtoPlay.h"
#include <iostream>

using namespace std;

HowtoPlay::HowtoPlay(float width, float height) {
	if (!font.loadFromFile("Font/AGoblinAppears-o2aV.ttf")) {
		cout << "No font is here";
	}
	
	howto[0].setFont(font);
	howto[0].setFillColor(sf::Color::Red);
	howto[0].setString("How To Play");
	howto[0].setCharacterSize(24);
	howto[0].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 1));

	howto[1].setFont(font);
	howto[1].setFillColor(sf::Color::White);
	howto[1].setString("Left-Right is to move left-right");
	howto[1].setCharacterSize(16);
	howto[1].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[1].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 2));

	howto[2].setFont(font);
	howto[2].setFillColor(sf::Color::White);
	howto[2].setString("Down is drop termino normal");
	howto[2].setCharacterSize(16);
	howto[2].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[2].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 3));

	howto[3].setFont(font);
	howto[3].setFillColor(sf::Color::White);
	howto[3].setString("Press space bar if you sure to drop very fast");
	howto[3].setCharacterSize(16);
	howto[3].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[3].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 4));

	howto[4].setFont(font);
	howto[4].setFillColor(sf::Color::White);
	howto[4].setString("Press Z and C if you want to change a shape 90° to right or left");
	howto[4].setCharacterSize(16);
	howto[4].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[4].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 5));

	howto[5].setFont(font);
	howto[5].setFillColor(sf::Color::White);
	howto[5].setString("Enter to return to Menu");
	howto[5].setCharacterSize(16);
	howto[5].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[5].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 6));

	howto[6].setFont(font);
	howto[6].setFillColor(sf::Color::White);
	howto[6].setString("Press Esc to exit if it's too hard for you");
	howto[6].setCharacterSize(16);
	howto[6].setOrigin(howto[0].getLocalBounds().width / 2, howto[0].getLocalBounds().height / 2);
	howto[6].setPosition(sf::Vector2f(width / 3, height / (MAX_ITEM + 1) * 7));
}
HowtoPlay::~HowtoPlay() {

}

void HowtoPlay::drawHowtoPlay(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_ITEM; i++) {
		window.draw(howto[i]);
	}
}
