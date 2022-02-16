#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "DrawText.h"
#include "Global.h"
#include "GetTetromino.h"
#include "GetWallKickData.h"
#include "Tetromino.h"

int main()
{
	//ใช้เช็คว่าจบเกมหรือไม่
	bool game_over = 0;
	//ปุ่มฮาร์ดดรอปถูกกดหรือไม่
	bool hard_drop_pressed = 0;
	//กดปุ่มหมุนหรือไม่?
	bool rotate_pressed = 0;

	//ใช้เพื่อทำให้เฟรมเรทของเกมเป็นอิสระ
	unsigned lag = 0;
	//ผู้เล่นเคลียร์กี่บรรทัด?
	unsigned lines_cleared = 0;

	//ตัวจับเวลาสำหรับเอฟเฟกต์การล้างเส้น
	unsigned char clear_effect_timer = 0;
	//กำหนดค่า current_fall_speed = START_FALL_SPEED
	unsigned char current_fall_speed = START_FALL_SPEED;
	//จับเวลาสำหรับ tetromino ล้ม
	unsigned char fall_timer = 0;
	//ตัวจับเวลาสำหรับ tetromino เคลื่อนที่ในแนวนอน
	unsigned char move_timer = 0;
	//รูปร่างถัดไป (รูปร่างที่มาหลังรูปร่างปัจจุบัน)
	unsigned char next_shape;
	//ตัวจับเวลาสำหรับ soft drop tetromino
	unsigned char soft_drop_timer = 0;

	//คล้ายกับแลค ใช้เพื่อทำให้เฟรมเรทของเกมเป็นอิสระ
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	//สุ่มอุปกรณ์
	std::random_device random_device;

	//Random engine
	std::default_random_engine random_engine(random_device());

	//กระจายทุกรูปทรง เราจะสุ่มเลือก
	std::uniform_int_distribution<unsigned short> shape_distribution(0, 6);

	//เก็บสถานะปัจจุบันของแต่ละแถว ไม่ว่าจะต้องเคลียร์หรือไม่
	std::vector<bool> clear_lines(ROWS, 0);

	//รหัสสีสำหรับเซลล์
	std::vector<sf::Color> cell_colors = {
		sf::Color(36, 36, 85),
		sf::Color(0, 219, 255),
		sf::Color(0, 36, 255),
		sf::Color(255, 146, 0),
		sf::Color(255, 219, 0),
		sf::Color(0, 219, 0),
		sf::Color(146, 0, 255),
		sf::Color(219, 0, 0),
		sf::Color(73, 73, 85)
	};

	//เกมเมทริกซ์ ทุกอย่างจะเกิดขึ้นกับเมทริกซ์นี้
	std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));

	//SFML store event
	sf::Event event;

	//วินโดว์
	sf::RenderWindow window(sf::VideoMode(2 * CELL_SIZE * COLUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close);
	//การปรับขนาดหน้าต่าง
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));

	//tetromino ที่ตกมาในตอนแรกเราจะสุ่มรูปร่างให้
	Tetromino tetromino(static_cast<unsigned char>(shape_distribution(random_engine)), matrix);

	//สร้างรูปร่างแบบสุ่มและจัดเก็บเป็นรูปร่างถัดไป
	next_shape = static_cast<unsigned char>(shape_distribution(random_engine));

	//รับเวลาปัจจุบันและเก็บไว้ในตัวแปร
	previous_time = std::chrono::steady_clock::now();
		
	//While the window is open
	while (1 == window.isOpen())
	{		
		//รับความแตกต่างของเวลาระหว่างเฟรมปัจจุบันและเฟรมก่อนหน้า
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		//Add the difference to the lag 
		lag += delta_time;

		//อัพเดทเวลาปัจจุบันกับเฟรมถัดไป
		previous_time += std::chrono::microseconds(delta_time);

		//While the lag exceeds the maximum allowed frame duration
		while (FRAME_DURATION <= lag)
		{
			//ลบ thing ด้านขวา ออกจากสิ่งด้านซ้าย
			lag -= FRAME_DURATION;
		
			//Loop events
			while (1 == window.pollEvent(event))
			{
				//เช็คชนิด event
				switch (event.type)
				{
					//เคศยูสเซอร์ปิดตัวเกม
				case sf::Event::Closed:
				{
					//ปิดวินโดว์
					window.close();

					break;
				}
				//เคส key 
				case sf::Event::KeyReleased:
				{
					//เช็คว่า key อะไร
					switch (event.key.code)
					{
						//เคส C or Z
					case sf::Keyboard::C:
					case sf::Keyboard::Z:
					{
						//เซ็ตปุ่มหมุน
						rotate_pressed = 0;

						break;
					}
					//เคสปุ่ม Down
					case sf::Keyboard::Down:
					{
						//รีเซ็ตตัวจับเวลาแบบซอฟต์ดร็อป
						soft_drop_timer = 0;

						break;
					}
					//เคส key ซ้ายหรือขวา
					case sf::Keyboard::Left:
					case sf::Keyboard::Right:
					{
						//รีเซ็ตตัวจับเวลาการย้าย
						move_timer = 0;

						break;
					}
					//เคสปุ่ม space
					case sf::Keyboard::Space:
					{
						//ปุ่มฮาร์ดดรอปไม่ได้ถูกกด
						hard_drop_pressed = 0;
					}
					}
				}
				}
			}

			//ถ้า clear effect timer == 0
			if (0 == clear_effect_timer)
			{
				//ถ้า game over == 0
				if (0 == game_over)
				{
					//ถ้า rotate pressed == 0 
					if (0 == rotate_pressed)
					{
						//ถ้า C is pressed
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::C))
						{
							//Rotation key is pressed
							rotate_pressed = 1;

							//Do a barrel roll
							tetromino.rotate(1, matrix);
						} //Else, if the Z is pressed
						else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
						{
							//Rotation key is pressed!
							rotate_pressed = 1;

							//Do a barrel roll but to the other side!
							tetromino.rotate(0, matrix);
						}
					}

					//ถ้า move timer == 0
					if (0 == move_timer)
					{
						//ถ้า the Left is pressed
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							//Reset the move timer
							move_timer = 1;

							//Move the tetromino to the left
							tetromino.move_left(matrix);
						}
						else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							//Reset the move timer
							move_timer = 1;

							//Move the tetromino to the opposite of left
							tetromino.move_right(matrix);
						}
					}
					else
					{
						//Update the move timer
						move_timer = (1 + move_timer) % MOVE_SPEED;
					}

					//ถ้า hard drop ไม่ได้ถูกกด
					if (0 == hard_drop_pressed)
					{
						//แต่กด Space แล้วอันไหนคือคีย์ฮาร์ดดร็อป (Paradox?)
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							//กำหนดค่า hard drop!
							hard_drop_pressed = 1;

							//รีเซ็ตค่า fall timer
							fall_timer = current_fall_speed;

							//ทำให้ tetromino ร่วงหล่น HAAAAARD!
							tetromino.hard_drop(matrix);
						}
					}

					//คล้าย hard drop แต่เปลี่ยนเป็น soft drop
					if (0 == soft_drop_timer)
					{
						if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							if (1 == tetromino.move_down(matrix))
							{
								fall_timer = 0;
								soft_drop_timer = 1;
							}
						}
					}
					else
					{
						soft_drop_timer = (1 + soft_drop_timer) % SOFT_DROP_SPEED;
					}

					//ถ้า timer is over
					if (current_fall_speed == fall_timer)
					{
						//ถ้า the tetromino can't move down anymore
						if (0 == tetromino.move_down(matrix))
						{
							//Put the falling tetromino to the matrix
							tetromino.update_matrix(matrix);

							//Loop through every row
							for (unsigned char a = 0; a < ROWS; a++)
							{
								//check if the current row should be cleared or not
								bool clear_line = 1;

								//Check if the every cell in the row is filled or not
								for (unsigned char b = 0; b < COLUMNS; b++)
								{
									if (0 == matrix[b][a])
									{
										clear_line = 0;

										break;
									}
								}

								//clear line 
								if (1 == clear_line)
								{
									//WE CLEAR IT!
									//First we increase the score
									lines_cleared++;

									//Then we start the effect timer
									clear_effect_timer = CLEAR_EFFECT_DURATION;

									//ตั้งค่าแถวปัจจุบันเป็นแถวที่ถูกล้าง
									clear_lines[a] = 1;

									//If the player reached a certain number of lines
									if (0 == lines_cleared % LINES_TO_INCREASE_SPEED)
									{
										//increase the game speed
										current_fall_speed = std::max<unsigned char>(SOFT_DROP_SPEED, current_fall_speed - 1);
									}
								}
							}

							//If the effect timer is over
							if (0 == clear_effect_timer)
							{
								//Decide if the game is over or not based on the return value of the reset function
								//Yes I know I could use "!" but it looks ugly and I hate using it!
								game_over = 0 == tetromino.reset(next_shape, matrix);

								//Generate the next shape
								next_shape = static_cast<unsigned char>(shape_distribution(random_engine));
							}
						}

						//Restart the fall timer
						fall_timer = 0;
					}
					else
					{
						//Increment the fall timer
						fall_timer++;
					}
				} //restarting the game
				else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					//We set everything to 0
					game_over = 0;
					hard_drop_pressed = 0;
					rotate_pressed = 0;

					lines_cleared = 0;

					//Except the current fall speed 
					current_fall_speed = START_FALL_SPEED;
					fall_timer = 0;
					move_timer = 0;
					soft_drop_timer = 0;

					//clear the matrix
					for (std::vector<unsigned char>& a : matrix)
					{
						std::fill(a.begin(), a.end(), 0);
					}
				}
			}
			else
			{
				//ลด effect timer
				clear_effect_timer--;

				//If the effect timer is between 1 and -1
				if (0 == clear_effect_timer)
				{
					//Loop through each row
					for (unsigned char a = 0; a < ROWS; a++)
					{
						//If the row should be cleared
						if (1 == clear_lines[a])
						{
							//Loop through each cell in the row
							for (unsigned char b = 0; b < COLUMNS; b++)
							{
								//Set the cell to 0 (empty) (the absence of existence)
								matrix[b][a] = 0;

								//Swap the row with the rows above
								for (unsigned char c = a; 0 < c; c--)
								{
									matrix[b][c] = matrix[b][c - 1];
									matrix[b][c - 1] = 0;
								}
							}
						}
					}

					game_over = 0 == tetromino.reset(next_shape, matrix);

					next_shape = static_cast<unsigned char>(shape_distribution(random_engine));

					//Clear the clear lines array
					std::fill(clear_lines.begin(), clear_lines.end(), 0);
				}
			}

			//drawing everything
			if (FRAME_DURATION > lag)
			{
				//Calculating the size of the effect squares
				unsigned char clear_cell_size = static_cast<unsigned char>(2 * round(0.5f * CELL_SIZE * (clear_effect_timer / static_cast<float>(CLEAR_EFFECT_DURATION))));

				//We're gonna use this object to draw every cell in the game
				sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
				//Next shape preview border (White square at the corner)
				sf::RectangleShape preview_border(sf::Vector2f(5 * CELL_SIZE, 5 * CELL_SIZE));
				preview_border.setFillColor(sf::Color(0, 0, 0));
				preview_border.setOutlineThickness(-1);
				preview_border.setPosition(CELL_SIZE * (1.5f * COLUMNS - 2.5f), CELL_SIZE * (0.25f * ROWS - 2.5f));

				//Clear the window from the previous frame
				window.clear();

				//Draw the matrix
				for (unsigned char a = 0; a < COLUMNS; a++)
				{
					for (unsigned char b = 0; b < ROWS; b++)
					{
						if (0 == clear_lines[b])
						{
							cell.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));

							if (1 == game_over && 0 < matrix[a][b])
							{
								cell.setFillColor(cell_colors[8]);
							}
							else
							{
								cell.setFillColor(cell_colors[matrix[a][b]]);
							}

							window.draw(cell);
						}
					}
				}

				//Set the cell color to gray
				cell.setFillColor(cell_colors[8]);

				//If the game is not over
				if (0 == game_over)
				{
					//Drawing the ghost tetromino
					for (Position& mino : tetromino.get_ghost_minos(matrix))
					{
						cell.setPosition(static_cast<float>(CELL_SIZE * mino.x), static_cast<float>(CELL_SIZE * mino.y));

						window.draw(cell);
					}

					cell.setFillColor(cell_colors[1 + tetromino.get_shape()]);
				}

				//Drawing the falling tetromino
				for (Position& mino : tetromino.get_minos())
				{
					cell.setPosition(static_cast<float>(CELL_SIZE * mino.x), static_cast<float>(CELL_SIZE * mino.y));

					window.draw(cell);
				}

				//Drawing the effect
				for (unsigned char a = 0; a < COLUMNS; a++)
				{
					for (unsigned char b = 0; b < ROWS; b++)
					{
						if (1 == clear_lines[b])
						{
							cell.setFillColor(cell_colors[0]);
							cell.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
							cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

							window.draw(cell);

							cell.setFillColor(sf::Color(255, 255, 255));
							cell.setPosition(floor(CELL_SIZE * (0.5f + a) - 0.5f * clear_cell_size), floor(CELL_SIZE * (0.5f + b) - 0.5f * clear_cell_size));
							cell.setSize(sf::Vector2f(clear_cell_size, clear_cell_size));

							window.draw(cell);
						}
					}
				}

				//Fanuitemg iow gfnreuignoei gnrign yerashr trujngfipoag
				cell.setFillColor(cell_colors[1 + next_shape]);
				cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

				//Draw the preview border
				window.draw(preview_border);

				//Draw the next tetromino
				for (Position& mino : get_tetromino(next_shape, static_cast<unsigned char>(1.5f * COLUMNS), static_cast<unsigned char>(0.25f * ROWS)))
				{
					//Shifting the tetromino to the center of the preview border
					unsigned short next_tetromino_x = CELL_SIZE * mino.x;
					unsigned short next_tetromino_y = CELL_SIZE * mino.y;

					if (0 == next_shape)
					{
						next_tetromino_y += static_cast<unsigned char>(round(0.5f * CELL_SIZE));
					}
					else if (3 != next_shape)
					{
						next_tetromino_x -= static_cast<unsigned char>(round(0.5f * CELL_SIZE));
					}

					cell.setPosition(next_tetromino_x, next_tetromino_y);

					window.draw(cell);
				}

				//draw text
				draw_text(static_cast<unsigned short>(CELL_SIZE * (0.5f + COLUMNS)), static_cast<unsigned short>(0.5f * CELL_SIZE * ROWS), "Lines:" + std::to_string(lines_cleared) + "\nSpeed:" + std::to_string(START_FALL_SPEED / current_fall_speed) + 'x', window);
		
				window.display();
				
			}
		}
	}
	return 0;
}
