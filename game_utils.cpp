// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "picosystem.hpp"
#include "game_utils.hpp"

using namespace picosystem;


bool compare_points(GamePoint p, uint8_t x, uint8_t y) {
  return p.x == x && p.y == y;
}


uint8_t rand_range(uint8_t max) {
  return std::rand() / ((RAND_MAX + 1u) / max);
}


bool any_key_pressed() {
  uint32_t all[] = {
    button::A, button::B, button::X, button::Y,
    button::UP, button::DOWN, button::LEFT, button::RIGHT
  };

  for (int i=0; i<8; i++) {
    if (button(all[i])) {
      return true;
    }
  }

  return false;
}


void text_centered(const std::string &str, uint32_t x, uint32_t y) {
  int32_t width, height;

  measure(str, width, height);

  text(str, x - (width / 2), y - (height / 2));
}


uint32_t scale_value(uint32_t current_value, uint32_t max_value, uint32_t scaled_max_value) {
  return (uint32_t)(((float)current_value) / ((float)max_value) * ((float)scaled_max_value));
}
