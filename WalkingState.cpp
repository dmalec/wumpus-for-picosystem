// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "WalkingState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

#define STATE_DURATION_IN_TICKS 200
#define ARROW_FLIGHT_DISTANCE 120

void WalkingState::handle_init(uint32_t total_ticks) {
  camera_x = 0;
  camera_y = 0;
}

State *WalkingState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  bool done_moving = false;

  if (moving_north) {
    camera_y -= 3;
    if (camera_y <= -120) {
      world_y--;
      done_moving = true;
    }
  }

  if (moving_south) {
    camera_y += 3;
    if (camera_y >= 121) {
      world_y++;
      done_moving = true;
    }
  }

  if (moving_west) {
    camera_x -= 3;
    if (camera_x <= -120) {
      world_x--;
      done_moving = true;
    }
  }

  if (moving_east) {
    camera_x += 3;
    if (camera_x >= 121) {
      world_x++;
      done_moving = true;
    }
  }

  if (done_moving) {
    camera_x = camera_y = 0;
    moving_north = moving_south = moving_east = moving_west = false;

    return enter_new_room_state;
  }

  return NULL;
}

void WalkingState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  // Do nothing
}

void WalkingState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  camera(camera_x, camera_y);
  pen(15, 15, 15);

  draw_room(   0,    0, world_x,     world_y);

  draw_room(-120,    0, world_x - 1, world_y);
  draw_room(   0, -120, world_x,     world_y - 1);
  draw_room( 120,    0, world_x + 1, world_y);
  draw_room(   0,  120, world_x,     world_y + 1);

  camera(0, 0);
}
