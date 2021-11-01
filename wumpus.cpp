// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include "picosystem.hpp"
#include "wumpus.hpp"
#include "spritesheet.hpp"
#include "game_utils.hpp"

#include "ArrowFlightState.hpp"
#include "BatTravelState.hpp"
#include "EnterNewRoomState.hpp"
#include "GameOverState.hpp"
#include "LoseToWumpusState.hpp"
#include "NewGameState.hpp"
#include "PitFallState.hpp"
#include "ShootingState.hpp"
#include "SplashScreenState.hpp"
#include "StandingInRoomState.hpp"
#include "WalkingState.hpp"
#include "WinState.hpp"


using namespace picosystem;


State *current_state;
bool moving_north, moving_south, moving_east, moving_west;
uint32_t shooting_direction = NONE;
uint8_t world_x, world_y;
uint8_t target_x, target_y;

// Hazard locations
GamePoint wumpus, bat_a, bat_b, pit_a, pit_b;

int map[10][10];

// Game stats
int32_t pit_losses, wumpus_losses, wumpus_wins;

// States
State *arrow_flight_state;
State *bat_travel_state;
State *enter_new_room_state;
State *game_over_state;
State *lose_to_wumpus_state;
State *new_game_state;
State *pit_fall_state;
State *shooting_state;
State *splash_screen_state;
State *standing_in_room_state;
State *walking_state;
State *win_state;

// -------------------------------------------------------------------------------
// Initialize functions
// -------------------------------------------------------------------------------

void init_states() {
  arrow_flight_state = new ArrowFlightState();
  bat_travel_state = new BatTravelState();
  enter_new_room_state = new EnterNewRoomState();
  game_over_state = new GameOverState();
  lose_to_wumpus_state = new LoseToWumpusState();
  new_game_state = new NewGameState();
  pit_fall_state = new PitFallState();
  shooting_state = new ShootingState();
  splash_screen_state = new SplashScreenState();
  standing_in_room_state = new StandingInRoomState();
  walking_state = new WalkingState();
  win_state = new WinState();
}

void init_globals() {
  pit_losses = 0;
  wumpus_losses = 0;
  wumpus_wins = 0;
}

void init_map() {
  for (int x=0; x<10; x++) {
    for (int y=0; y<10; y++) {
      map[x][y] = 0x00;
      if (x != 0) {
        map[x][y] |= 0x0001;
      }
      if (y != 0) {
        map[x][y] |= 0x0010;
      }
      if (x != 9) {
        map[x][y] |= 0x0100;
      }
      if (y != 9) {
        map[x][y] |= 0x1000;
      }
    }
  }
}


// -------------------------------------------------------------------------------
// Event loop functions
// -------------------------------------------------------------------------------

void init() {
  spritesheet(custom_sprite_sheet);

  init_states();
  init_globals();
  init_map();

  current_state = splash_screen_state;
  current_state->init(0);
}

void update(uint32_t tick) {
  State *new_state = current_state->update(tick);

  if (new_state != NULL) {
    current_state = new_state;
    current_state->init(tick);
  }
}

void draw(uint32_t tick) {
  camera(0, 0);
  pen(0, 0, 0);
  clear();

  current_state->draw(tick);
}


// -------------------------------------------------------------------------------
// Map functions
// -------------------------------------------------------------------------------

GamePoint random_location() {
  GamePoint location;

  location.x = rand_range(9);
  location.y = rand_range(9);

  return location;
}


// -------------------------------------------------------------------------------
// Moving states / functions
// -------------------------------------------------------------------------------

bool currently_moving() {
  return moving_north || moving_south || moving_east || moving_west;
}

bool is_neighbor(GamePoint p, int x, int y) {
  return (p.y == y && (p.x == x-1 || p.x == x+1)) ||
    (p.x == x && (p.y == y-1 || p.y == y+1));
}

void draw_room(int x, int y, int map_x, int map_y) {
  frect(x+15, y+15, 90, 90);

  if (map_x < 0 || map_x >= 10 || map_y < 0 || map_y >= 10) {
    return;
  }

  if (map[map_x][map_y] & 0x0001) {
    frect(x, y+45, 20, 30);
  }

  if (map[map_x][map_y] & 0x0010) {
    frect(x+45, y, 30, 20);
  }

  if (map[map_x][map_y] & 0x0100) {
    frect(x+100, y+45, 20, 30);
  }

  if (map[map_x][map_y] & 0x1000) {
    frect(x+45, y+100, 30, 20);
  }
}

void draw_single_room() {
  pen(15, 15, 15);
  draw_room(   0,    0, world_x,     world_y);

  pen(12, 11, 4 );
  text(str((float)world_x, 0),  96, 112);
  text(",",                    104, 112);
  text(str((float)world_y, 0), 112, 112);

  if (is_neighbor(wumpus, world_x, world_y)) {
    sprite(WUMPUS_ICON, 22, 2);
  }

  if (is_neighbor(bat_a, world_x, world_y) ||
      is_neighbor(bat_b, world_x, world_y)) {
    sprite(BAT_ICON, 12, 2);
  }

  if (is_neighbor(pit_a, world_x, world_y) ||
      is_neighbor(pit_b, world_x, world_y)) {
    sprite(PIT_ICON, 2, 2);
  }
}
