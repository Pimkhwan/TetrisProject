#pragma once

//ขนาดcell
constexpr unsigned char CELL_SIZE = 8;
//ระยะเวลาของการเคลียเอฟเฟค
constexpr unsigned char CLEAR_EFFECT_DURATION = 8;
//จำนวนคอลั่ม
constexpr unsigned char COLUMNS = 10;
//เพิ่มความเร็วเกม
constexpr unsigned char LINES_TO_INCREASE_SPEED = 2;
//ความเร็ว
constexpr unsigned char MOVE_SPEED = 4;

constexpr unsigned char ROWS = 20;
//ขนาดจอ
constexpr unsigned char SCREEN_RESIZE = 4;
//ความเร็ว
constexpr unsigned char SOFT_DROP_SPEED = 4;
//ความเร็วในการหล่นตอนเริ่มเกม
constexpr unsigned char START_FALL_SPEED = 32;

//ระยะห่างของเฟรม
constexpr unsigned short FRAME_DURATION = 16667;

//ตำแหน่ง
struct Position
{
	char x;
	char y;
};
