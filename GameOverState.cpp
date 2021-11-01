// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "GameOverState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

void GameOverState::handle_init(uint32_t total_ticks) {
  fade_in = true;
  fade_level = 0;
}

State *GameOverState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (!any_key_pressed()) {
    return NULL;
  }

  return new_game_state;
}

void GameOverState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  uint32_t time_slice = elapsed_ticks % 150;
  if (time_slice == 0) {
    fade_in = !fade_in;
  }

  fade_level = fade_in ? time_slice / 10 :  15 - time_slice / 10;
}

void GameOverState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 15, 15);
  text_centered("GAME  OVER", 60, 10);

  sprite(WUMPUS_ICON,       20, 40);
  text(str(wumpus_losses),  40, 40);

  sprite(ARROW_EAST,        20, 60);
  text(str(wumpus_wins),    40, 60);

  sprite(PIT_ICON,          20, 80);
  text(str(pit_losses),     40, 80);

  text_centered("PRESS  ANY  KEY", 60, 110);
  pen(0, 0, 0, fade_level);
  frect(0, 90, 120, 30);
}
