// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "StandingInRoomState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

void StandingInRoomState::handle_init(uint32_t total_ticks) {
  // Do nothing
}

State *StandingInRoomState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  moving_north = pressed(UP) && (map[world_x][world_y] & 0x0010);
  moving_south = pressed(DOWN) && (map[world_x][world_y] & 0x1000);
  moving_east = pressed(RIGHT) && (map[world_x][world_y] & 0x0100);
  moving_west = pressed(LEFT) && (map[world_x][world_y] & 0x0001);

  if (currently_moving()) {
    return walking_state;
  }

  if (pressed(A) | pressed(B) | pressed(X) | pressed(Y)) {
    return shooting_state;
  }

  return NULL;
}

void StandingInRoomState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  // Do nothing
}

void StandingInRoomState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  draw_single_room();
}
