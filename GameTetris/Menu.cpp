#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("Font/AGoblinAppears-o2aV.ttf")) {
		std::cout << "No font is here";
	}
	//Play
	menu[0].setFont(font);
	//menu[0].setCharacterSize();
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Enter to play me");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEM + 1) * 2));
	//Exit
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
			if (selectedItem == -1) {
				selectedItem = 2;
		}
			menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItem + 1 <= MAX_ITEM) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		if (selectedItem == 4) {
			selectedItem = 0;
		}
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

//menu.draw(window);
//in swith case
//case sf::Event::KeyReleased:
// swithch(event.key.code){
//  case sf::Keyboard::Up:
// menu.MoveUp();
// break;
// 
// case sf::Keyboard::Down:
// menu.MoveDown();
// break;
// 
// case sf::Keyboard::Return:
//  switch(menu.GetPressedItem())
//   {
// case 0 :
//			std::cout << "Play has been pressed" << std::end;
//			// go to state
//			break;
// case 1 :
//			std::cout << "Leaderboard has been pressed" << std::end;
//          // go to state 
//			break;
// case 2 :
//			window.close();
//			break;
// }
// 
// 
//break;


//if (selectedItem - 1 >= 0) {
//	menu[selectedItem].setFillColor(sf::Color::White);
//	selectedItem--;
//	if (selectedItem == -1) {
//		selectedItem = 2;
//	}
	//menu[selectedItem].setFillColor(sf::Color::Red);
//}


//if (selectedItem + 1 <= MAX_ITEM) {
	//menu[selectedItem].setFillColor(sf::Color::White);
	//selectedItem++;
	//if (selectedItem == 4) {
	//	selectedItem = 0;
	//}
	//menu[selectedItem].setFillColor(sf::Color::Red);
//}