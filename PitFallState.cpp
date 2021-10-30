// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "PitFallState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 400
#define FALL_DURATION_IN_TICKS 200
#define PIT_FALL_DISTANCE 120

void PitFallState::handle_init(uint32_t total_ticks) {
  pit_losses++;

  pit_y_pos = -8;
  pit_show_text = false;
}

State *PitFallState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (elapsed_ticks < STATE_DURATION_IN_TICKS) {
    return NULL;
  }

  return game_over_state;
}

void PitFallState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pit_y_pos = scale_value(elapsed_ticks, FALL_DURATION_IN_TICKS, PIT_FALL_DISTANCE);
  pit_show_text = elapsed_ticks > FALL_DURATION_IN_TICKS;
}

void PitFallState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 15, 15);
  frect(40, 0, 40, 120);

  pen(0, 11, 0);
  frect(40, 96, 40, 24);

  sprite(PLAYER_FALLING, 56, pit_y_pos);

  if (pit_show_text) {
    pen(15, 15, 15);
    text_centered("PIT!", 60, 110);
  }
}
