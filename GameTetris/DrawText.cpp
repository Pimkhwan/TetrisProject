#include <SFML/Graphics.hpp>

#include "DrawText.h"
using namespace std;
using namespace sf;

void draw_text(unsigned short i_x, unsigned short i_y, const string& i_text, RenderWindow& i_window)
{
	
	//เราจะจัดข้อความให้ชิดซ้ายบน
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_width;

	Sprite character_sprite;

	Texture font_texture;
	font_texture.loadFromFile("Font/Font.png");

	//เราจะคำนวณความกว้างของอักขระตามขนาดภาพแบบอักษร
	//96 เพราะมี 96 ตัวอักษรในภาพ
	
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	for (const char a : i_text)
	{
		if ('\n' == a)
		{
			//หลังจากขึ้นบรรทัดใหม่ทุกครั้ง เราเพิ่มพิกัด y และรีเซ็ตพิกัด x
			character_x = i_x;
			character_y += font_texture.getSize().y;

			continue;
		}

		//เปลี่ยนตำแหน่งของตัวละครถัดไป
		character_sprite.setPosition(character_x, character_y);
		//เลือกตัวละครจากภาพฟอนต์
		character_sprite.setTextureRect(IntRect(character_width * (a - 32), 0, character_width, font_texture.getSize().y));

		//เพิ่มพิกัด x
		character_x += character_width;

		//วาดตัวละคร
		i_window.draw(character_sprite);
	}
}
