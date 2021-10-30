// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "BatTravelState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 400
#define BAT_TRAVEL_DISTANCE 120

void BatTravelState::handle_init(uint32_t total_ticks) {
  bat_x_pos = 0;
}

State *BatTravelState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (elapsed_ticks < STATE_DURATION_IN_TICKS) {
    return NULL;
  }

  world_x = rand_range(9);
  world_y = rand_range(9);

  return enter_new_room_state;
}

void BatTravelState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  bat_x_pos = scale_value(elapsed_ticks, STATE_DURATION_IN_TICKS, BAT_TRAVEL_DISTANCE);
}

void BatTravelState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 15, 15);
  frect(0, 40, 120, 40);

  sprite(BAT_ICON, bat_x_pos, 52);
  sprite(PLAYER_CARRIED, bat_x_pos, 60);

  pen(15, 15, 15);
  text_centered("BAT!", 60, 110);
}
