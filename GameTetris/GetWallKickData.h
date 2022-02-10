#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

std::vector<Position> get_wall_kick_data(bool i_is_i_shape, unsigned char i_current_rotation, unsigned char i_next_rotation);