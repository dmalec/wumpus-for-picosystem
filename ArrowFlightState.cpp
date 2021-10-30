// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "ArrowFlightState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 200
#define ARROW_FLIGHT_DISTANCE 120

void ArrowFlightState::handle_init(uint32_t total_ticks) {
  arrow_pos = 0;
}

State *ArrowFlightState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  if (elapsed_ticks < STATE_DURATION_IN_TICKS) {
    return NULL;
  }

  if (compare_points(wumpus, target_x, target_y)) {
    return win_state;
  } else {
    return lose_to_wumpus_state;
  }
}

void ArrowFlightState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  arrow_pos = scale_value(elapsed_ticks, STATE_DURATION_IN_TICKS, ARROW_FLIGHT_DISTANCE);
}

void ArrowFlightState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  pen(15, 15, 15);
  if (shooting_direction == EAST || shooting_direction == WEST) {
    frect(0, 40, 120, 40);
  } else {
    frect(40, 0, 40, 120);
  }

  if (shooting_direction == NORTH) {
    sprite(ARROW_NORTH, 56, ARROW_FLIGHT_DISTANCE - arrow_pos);
  } else if (shooting_direction == EAST) {
    sprite(ARROW_EAST, arrow_pos, 56);
  } else if (shooting_direction == SOUTH) {
    sprite(ARROW_SOUTH, 56, arrow_pos);
  } else if (shooting_direction == WEST) {
    sprite(ARROW_WEST, ARROW_FLIGHT_DISTANCE - arrow_pos, 56);
  }
}
