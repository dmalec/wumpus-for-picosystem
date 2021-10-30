// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "WinState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 200

void WinState::handle_init(uint32_t total_ticks) {
  wumpus_wins++;
}

State *WinState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (elapsed_ticks < STATE_DURATION_IN_TICKS) {
    return NULL;
  }

  return game_over_state;
}

void WinState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  // Do nothing
}

void WinState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 15, 15);
  draw_room(0, 0, target_x, target_y);

  sprite(WUMPUS_ICON, 40, 40, 1, 1, 40, 40);

  pen(15, 0, 0);
  text_centered("YOU  GOT  THE  WUMPUS!", 60, 110);
}
