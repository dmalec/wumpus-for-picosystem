// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "picosystem.hpp"
#include "utils.hpp"

using namespace picosystem;


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
