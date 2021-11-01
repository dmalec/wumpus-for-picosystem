// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "SplashScreenState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

void SplashScreenState::handle_init(uint32_t total_ticks) {
  fade_in = true;
  fade_level = 0;
}

State *SplashScreenState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (!any_key_pressed()) {
    return NULL;
  }

  return new_game_state;
}

void SplashScreenState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  uint32_t time_slice = elapsed_ticks % 150;
  if (time_slice == 0) {
    fade_in = !fade_in;
  }

  fade_level = fade_in ? time_slice / 10 :  15 - time_slice / 10;
}

void SplashScreenState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 0, 0);
  frect(0, 0, 120, 120);

  sprite(WUMPUS_EYE, 10, 20, 1, 1, 24, 24);
  sprite(WUMPUS_EYE, (120 - 10 - 24), 20, 1, 1, 24, 24);

  blit(wumpus_title_buffer, 0, 0, 112, 16, 4, 64);

  pen(15, 15, 15);
  text_centered("PRESS  ANY  KEY", 60, 100);

  pen(15, 0, 0, fade_level);
  frect(0, 90, 120, 30);
}
