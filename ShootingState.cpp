// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "ShootingState.hpp"
#include "spritesheet.hpp"
#include "wumpus.hpp"

void ShootingState::handle_init(uint32_t total_ticks) {
  fade_in = true;
  fade_level = 0;
}

State *ShootingState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  shooting_direction = NONE;
  target_x = world_x;
  target_y = world_y;

  if (pressed(A) | pressed(B) | pressed(X) | pressed(Y)) {
    return standing_in_room_state;
  }

  if (pressed(UP) && (map[world_x][world_y] & NORTH)) {
    target_y--;
    shooting_direction = NORTH;
  } else if (pressed(RIGHT) && (map[world_x][world_y] & EAST)) {
    target_x++;
    shooting_direction = EAST;
  } else if (pressed(DOWN) && (map[world_x][world_y] & SOUTH)) {
    target_y++;
    shooting_direction = SOUTH;
  } else if (pressed(LEFT) && (map[world_x][world_y] & WEST)) {
    target_x--;
    shooting_direction = WEST;
  }

  if (shooting_direction != NONE) {
    return arrow_flight_state;
  }

  return NULL;
}

void ShootingState::handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) {
  uint32_t time_slice = elapsed_ticks % 150;
  if (time_slice == 0) {
    fade_in = !fade_in;
  }

  fade_level = fade_in ? time_slice / 10 :  15 - time_slice / 10;
}

void ShootingState::handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) {
  draw_single_room();

  pen(0, 0, 0);

  if (map[world_x][world_y] & NORTH) {
    sprite(ARROW_NORTH, 52, 2, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & SOUTH) {
    sprite(ARROW_SOUTH, 52, 102, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & EAST) {
    sprite(ARROW_EAST, 102, 52, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & WEST) {
    sprite(ARROW_WEST, 2, 52, 1, 1, 16, 16);
  }

  pen(15, 15, 15, fade_level);

  if (map[world_x][world_y] & NORTH) {
    frect(50, 0, 20, 20);
  }
  if (map[world_x][world_y] & SOUTH) {
    frect(50, 100, 20, 20);
  }
  if (map[world_x][world_y] & EAST) {
    frect(100, 50, 20, 20);
  }
  if (map[world_x][world_y] & WEST) {
    frect(0, 50, 20, 20);
  }
}
