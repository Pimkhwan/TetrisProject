#include <vector>

#include "Global.h"
#include "GetTetromino.h"
#include "GetWallKickData.h"
#include "Tetromino.h"

Tetromino::Tetromino(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix) :
	rotation(0),
	shape(i_shape),
	minos(get_tetromino(i_shape, COLUMNS / 2, 1))
{
	
}

bool Tetromino::move_down(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	for (Position& mino : minos)
	{
		//พวกมันจะไปนอกเมทริกซ์ถ้าพวกมันเลื่อนลงมาหรือไม่?
		if (ROWS == 1 + mino.y)
		{
			return 0;
		}

		//เราจะตี tetromino อีกหรือไม่ถ้าเราเลื่อนลง?
		if (0 < i_matrix[mino.x][1 + mino.y])
		{
			return 0;
		}
	}

	//เลื่อน tetromino ลง
	for (Position& mino : minos)
	{
		mino.y++;
	}

	//กลับมาให้ทุกอย่างโอเค
	return 1;
}

bool Tetromino::reset(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//รีเซ็ตตัวแปร
	rotation = 0;
	shape = i_shape;

	minos = get_tetromino(shape, COLUMNS / 2, 1);

	for (Position& mino : minos)
	{
		if (0 < i_matrix[mino.x][mino.y])
		{
			//กลับมาที่เราไม่สามารถรีเซ็ตได้เพราะมีเทโทรมิโนอยู่ที่ตำแหน่งเริ่มต้น
			return 0;
		}
	}

	//กลับมาว่าทุกอย่างเรียบร้อย
	return 1;
}

unsigned char Tetromino::get_shape()
{
	//ฉันจะลองเดาดูและบอกว่านี่จะคืนรูปร่างของ tetromino
	return shape;
}

void Tetromino::hard_drop(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//ฉันฉลาดมาก ฉันใช้ฟังก์ชัน ghost tetromino เพื่อสร้างฟังก์ชันฮาร์ดดร็อป
	minos = get_ghost_minos(i_matrix);
}

void Tetromino::move_left(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//มันคล้ายกับฟังก์ชั่นเลื่อนลง ดังนั้นฉันจะไม่อธิบายอะไรที่นี่ กัดฉัน!
	for (Position& mino : minos)
	{
		if (0 > mino.x - 1)
		{
			return;
		}

		if (0 > mino.y)
		{
			continue;
		}
		else if (0 < i_matrix[mino.x - 1][mino.y])
		{
			return;
		}
	}

	for (Position& mino : minos)
	{
		mino.x--;
	}
}

void Tetromino::move_right(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//สวัสดี!
	for (Position& mino : minos)
	{
		if (COLUMNS == 1 + mino.x)
		{
			return;
		}

		if (0 > mino.y)
		{
			continue;
		}
		else if (0 < i_matrix[1 + mino.x][mino.y])
		{
			return;
		}
	}

	for (Position& mino : minos)
	{
		mino.x++;
	}
}

void Tetromino::rotate(bool i_clockwise, const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//ฉันไม่อยากอธิบายเรื่องนี้ ฉันใช้เวลามากเกินไปในการเขียนสิ่งนี้
	if (3 != shape)
	{
		unsigned char next_rotation;

		std::vector<Position> current_minos = minos;

		//กำลังคำนวณสถานะการหมุนครั้งต่อไป
		if (0 == i_clockwise)
		{
			next_rotation = (3 + rotation) % 4;
		}
		else
		{
			next_rotation = (1 + rotation) % 4;
		}

		//ถ้าเป็นรูปตัวฉัน
		if (0 == shape)
		{
			//We find it's center
			float center_x = 0.5f * (minos[1].x + minos[2].x);
			float center_y = 0.5f * (minos[1].y + minos[2].y);

			switch (rotation)
			{
			case 0:
			{
				center_y += 0.5f;

				break;
			}
			case 1:
			{
				center_x -= 0.5f;

				break;
			}
			case 2:
			{
				center_y -= 0.5f;

				break;
			}
			case 3:
			{
				center_x += 0.5f;
			}
			}

			//จากนั้นเราจะหมุนทุก mino ตามศูนย์
			for (Position& mino : minos)
			{
				//เราหาตำแหน่งของมิโนที่สัมพันธ์กับจุดศูนย์กลาง
				float x = mino.x - center_x;
				float y = mino.y - center_y;

				if (0 == i_clockwise)
				{
					mino.x = static_cast<char>(center_x + y);
					mino.y = static_cast<char>(center_y - x);
				}
				else
				{
					mino.x = static_cast<char>(center_x - y);
					mino.y = static_cast<char>(center_y + x);
				}
			}
		}
		else
		{
			//เราไม่หมุนมิโนที่อยู่ตรงกลางการหมุน
			for (unsigned char a = 1; a < minos.size(); a++)
			{
				//เราหาตำแหน่งของ mino ที่สัมพันธ์กับ mino ส่วนกลาง
				char x = minos[a].x - minos[0].x;
				char y = minos[a].y - minos[0].y;

				if (0 == i_clockwise)
				{
					minos[a].x = y + minos[0].x;
					minos[a].y = minos[0].y - x;
				}
				else
				{
					minos[a].x = minos[0].x - y;
					minos[a].y = x + minos[0].y;
				}
			}
		}

		//เราลองเวกเตอร์ทุกตัวจากข้อมูลการเตะกำแพง
		for (Position& wall_kick : get_wall_kick_data(0 == shape, rotation, next_rotation))
		{
			bool can_turn = 1;

			for (Position& mino : minos)
			{
				//เราตรวจสอบทุกการชนที่อาจเกิดขึ้น
				if (0 > mino.x + wall_kick.x || COLUMNS <= mino.x + wall_kick.x || ROWS <= mino.y + wall_kick.y)
				{
					can_turn = 0;

					break;
				}

				if (0 > mino.y + wall_kick.y)
				{
					continue;
				}
				else if (0 < i_matrix[mino.x + wall_kick.x][mino.y + wall_kick.y])
				{
					can_turn = 0;

					break;
				}
			}

			//ถ้าฉันสามารถหัน
			if (1 == can_turn)
			{
				//เราหัน
				rotation = next_rotation;

				for (Position& mino : minos)
				{
					mino.x += wall_kick.x;
					mino.y += wall_kick.y;
				}

				return;
			}
		}

		//เนื่องจากเราใช้การเปลี่ยนแปลงกับอาร์เรย์ minos เราจึงรีเซ็ตเมื่อเราไม่สามารถหมุน tetromino
		minos = current_minos;
	}
}

void Tetromino::update_matrix(std::vector<std::vector<unsigned char>>& i_matrix)
{
	//การใส่ tetromino ให้กับเมทริกซ์
	for (Position& mino : minos)
	{
		if (0 > mino.y)
		{
			continue;
		}

		i_matrix[mino.x][mino.y] = 1 + shape;
	}
}

std::vector<Position> Tetromino::get_ghost_minos(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//เราแค่ขยับเทโทรมิโนลงไป จนกว่ามันจะกระทบอะไรบางอย่าง แล้วเราก็คืนตำแหน่ง
	bool keep_falling = 1;

	unsigned char total_movement = 0;

	std::vector<Position> ghost_minos = minos;

	while (1 == keep_falling)
	{
		total_movement++;

		for (Position& mino : minos)
		{
			if (ROWS == total_movement + mino.y)
			{
				keep_falling = 0;

				break;
			}

			if (0 > total_movement + mino.y)
			{
				continue;
			}
			else if (0 < i_matrix[mino.x][total_movement + mino.y])
			{
				keep_falling = 0;

				break;
			}
		}
	}

	for (Position& mino : ghost_minos)
	{
		mino.y += total_movement - 1;
	}

	return ghost_minos;
}

std::vector<Position> Tetromino::get_minos()
{
	//คืนมิโน
	return minos;
}
