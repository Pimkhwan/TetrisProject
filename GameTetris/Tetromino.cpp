#include <vector>

#include "Headers/Global.hpp"
#include "Headers/GetTetromino.hpp"

Tetromino::Tetromino(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix) :
	rotation(0),
	shape(i_shape),
	minos(get_tetromino(i_shape, COLUMNS / 2, 1))
	bool Tetromino::move_down(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	for (Position& mino : minos)
	{
		//Will we go outside the matrix if we move down?
		if (ROWS == 1 + mino.y)
		{
			return 0;
		}

		//Will we hit another tetromino if we move down?
		if (0 < i_matrix[mino.x][1 + mino.y])
		{
			return 0;
		}
	}

	//Move the tetromino down
	for (Position& mino : minos)
	{
		mino.y++;
	}

	//Return that everything is okay
	return 1;
}