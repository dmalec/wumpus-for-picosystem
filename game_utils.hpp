// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef GAME_UTILS_HPP_INCLUDED_
#define GAME_UTILS_HPP_INCLUDED_

#include "game_types.hpp"


bool compare_points(GamePoint p, uint8_t x, uint8_t y);
GamePoint location(uint8_t x, uint8_t y);

uint8_t rand_range(uint8_t max);


bool any_key_pressed();


void text_centered(const std::string &str, uint32_t x, uint32_t y);


uint32_t scale_value(uint32_t current_value, uint32_t max_value, uint32_t scaled_max_value);

#endif // GAME_UTILS_HPP_INCLUDED_

