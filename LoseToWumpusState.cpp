// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "LoseToWumpusState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 400
#define MOUTH_CLOSE_DURATION_IN_TICKS 200
#define MOUTH_CLOSE_DISTANCE (60 - 15)

void LoseToWumpusState::handle_init(uint32_t total_ticks) {
  wumpus_losses++;

  teeth_offset = -8;
  show_text = false;
}

State *LoseToWumpusState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (elapsed_ticks < STATE_DURATION_IN_TICKS) {
    return NULL;
  }

  return game_over_state;
}

void LoseToWumpusState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  teeth_offset = scale_value(elapsed_ticks, MOUTH_CLOSE_DURATION_IN_TICKS, MOUTH_CLOSE_DISTANCE);
  teeth_offset = teeth_offset < MOUTH_CLOSE_DISTANCE ? teeth_offset : MOUTH_CLOSE_DISTANCE;

  show_text = elapsed_ticks > MOUTH_CLOSE_DURATION_IN_TICKS;
}

void LoseToWumpusState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 0, 0);
  frect(0, 0, 120, teeth_offset);
  frect(0, 120-teeth_offset, 120, teeth_offset);

  for (int x=0; x<8; x++) {
    sprite(WUMPUS_TOP_TOOTH, x*15, teeth_offset, 1, 1, 15, 15);
    sprite(WUMPUS_BOTTOM_TOOTH, x*15, 120-teeth_offset-15, 1, 1, 15, 15);
  }

  if (show_text) {
    sprite(WUMPUS_EYE, 10, 20, 1, 1, 24, 24);
    sprite(WUMPUS_EYE, (120 - 10 - 24), 20, 1, 1, 24, 24);

    pen(15, 15, 15);
    text_centered("THE  WUMPUS  GOT  YOU!", 60, 110);
  }
}
