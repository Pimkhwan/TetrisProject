#include <SFML/Graphics.hpp>

#include "DrawText.h"

void draw_text(unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window)
{
	//เราจะจัดข้อความให้ชิดซ้ายบน
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_width;

	sf::Sprite character_sprite;

	sf::Texture font_texture;
	font_texture.loadFromFile("Font/Font.png");

	//เราจะคำนวณความกว้างของอักขระตามขนาดภาพแบบอักษร
	//96 เพราะว่านี่คือ 96 ตัวละครในภาพ
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	for (const char a : i_text)
	{
		if ('\n' == a)
		{
			//After every newline we put increase the y-coordinate and reset the x-coordinate
			character_x = i_x;
			character_y += font_texture.getSize().y;

			continue;
		}

		//เปลี่ยนตำแหน่งของตัวละครถัดไป
		character_sprite.setPosition(character_x, character_y);
		//เลือกตัวละครจากภาพฟอนต์
		character_sprite.setTextureRect(sf::IntRect(character_width * (a - 32), 0, character_width, font_texture.getSize().y));

		//เพิ่มพิกัด x
		character_x += character_width;

		//วาดตัวละคร
		i_window.draw(character_sprite);
	}
}

