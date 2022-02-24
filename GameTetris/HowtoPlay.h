#pragma once
#include <sfml\Graphics.hpp>
#define MAX_ITEM 7

using namespace sf;

class HowtoPlay
{
	public:
		HowtoPlay(float width, float height);
		~HowtoPlay();

		void drawHowtoPlay(RenderWindow& window);
	private:
		Font font;
		Text howto[MAX_ITEM];
	};


