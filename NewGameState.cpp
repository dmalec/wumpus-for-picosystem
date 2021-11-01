// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "NewGameState.hpp"
#include "wumpus.hpp"

bool is_neighbor_hazardous() {
  if (is_neighbor(wumpus, world_x, world_y)) {
    return true;
  }

  if (is_neighbor(bat_a, world_x, world_y)) {
    return true;
  }

  if (is_neighbor(bat_b, world_x, world_y)) {
    return true;
  }

  if (is_neighbor(pit_a, world_x, world_y)) {
    return true;
  }

  if (is_neighbor(pit_b, world_x, world_y)) {
    return true;
  }

  return false;
}

void random_placement() {
  wumpus = random_location();
  bat_a = random_location();
  bat_b = random_location();
  pit_a = random_location();
  pit_b = random_location();

  do {
    world_x = rand_range(9);
    world_y = rand_range(9);
  } while (is_neighbor_hazardous());
}

void fixed_placement() {
  wumpus = location(1, 1);
  bat_a = location(2, 1);
  bat_b = location(2, 1);
  pit_a = location(3, 1);
  pit_b = location(3, 1);

  world_x = 0;
  world_y = 0;
}

void NewGameState::handle_init(uint32_t total_ticks) {
  moving_north = false;
  moving_south = false;
  moving_east = false;
  moving_west = false;

  shooting_direction = NONE;

#ifdef FIXED_PLACEMENT
  fixed_placement();
#else
  random_placement();
#endif
}

State *NewGameState::check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) {
  return enter_new_room_state;
}
