#include <vector>

#include "Global.h"
#include "GetTetromino.h"

std::vector<Position> get_tetromino(unsigned char i_shape, unsigned char i_x, unsigned char i_y)
{
	//เซ็ต vector 
	std::vector<Position> output_tetromino(4);

	//กำหนดตำแหน่งสัมพัทธ์ทุกรูปร่าง
	switch (i_shape)
	{
	case 0:
	{
		output_tetromino[0] = { 1, -1 };
		output_tetromino[1] = { 0, -1 };
		output_tetromino[2] = { -1, -1 };
		output_tetromino[3] = { -2, -1 };

		break;
	}
	case 1:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 1, 0 };
		output_tetromino[2] = { -1, -1 };
		output_tetromino[3] = { -1, 0 };

		break;
	}
	case 2:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 1, 0 };
		output_tetromino[2] = { 1, -1 };
		output_tetromino[3] = { -1, 0 };

		break;
	}
	case 3:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 0, -1 };
		output_tetromino[2] = { -1, -1 };
		output_tetromino[3] = { -1, 0 };

		break;
	}
	case 4:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 1, -1 };
		output_tetromino[2] = { 0, -1 };
		output_tetromino[3] = { -1, 0 };

		break;
	}
	case 5:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 1, 0 };
		output_tetromino[2] = { 0, -1 };
		output_tetromino[3] = { -1, 0 };

		break;
	}
	case 6:
	{
		output_tetromino[0] = { 0, 0 };
		output_tetromino[1] = { 1, 0 };
		output_tetromino[2] = { 0, -1 };
		output_tetromino[3] = { -1, -1 };
	}
	}

	//จากนั้นเราบวก x และ y ให้ตัว tetromino
	for (Position& mino : output_tetromino)
	{
		mino.x += i_x;
		mino.y += i_y;
	}

	//Return ตัว tetromino
	return output_tetromino;
}