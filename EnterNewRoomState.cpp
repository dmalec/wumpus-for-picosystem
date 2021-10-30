// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "EnterNewRoomState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

void EnterNewRoomState::handle_init(uint32_t total_ticks) {
  // Do nothing
}

State *EnterNewRoomState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (compare_points(bat_a, world_x, world_y) ||
      compare_points(bat_b, world_x, world_y)) {
    return bat_travel_state;
  } else if (compare_points(pit_a, world_x, world_y) ||
             compare_points(pit_b, world_x, world_y)) {
    return pit_fall_state;
  } else if (compare_points(wumpus, world_x, world_y)) {
    return lose_to_wumpus_state;
  } else {
    return standing_in_room_state;
  }
}

void EnterNewRoomState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  // Do nothing
}

void EnterNewRoomState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  draw_single_room();
}
