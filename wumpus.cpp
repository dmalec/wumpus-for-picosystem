// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#include <cstdlib>
#include <ctime>

#include "picosystem.hpp"
#include "wumpus.hpp"
#include "spritesheet.hpp"
#include "utils.hpp"

using namespace picosystem;


state current_state;
bool moving_north, moving_south, moving_east, moving_west;
uint32_t shooting_direction = NONE;
int camera_x, camera_y;
int world_x, world_y;

// Hazard locations
Point wumpus, bat_a, bat_b, pit_a, pit_b;

int map[10][10];


// -------------------------------------------------------------------------------
// Initialize functions
// -------------------------------------------------------------------------------

void init_globals() {
  moving_north = false;
  moving_south = false;
  moving_east = false;
  moving_west = false;
  camera_x = 0;
  camera_y = 0;
  world_x = 0;
  world_y = 0;
}

void init_hazards() {
  wumpus = random_location();
  bat_a = random_location();
  bat_b = random_location();
  pit_a = random_location();
  pit_b = random_location();
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

void set_state(uint32_t tick, state new_state) {
  current_state.update = new_state.update;
  current_state.draw = new_state.draw;
  current_state.change_time = tick;
}

void init() {
  spritesheet(custom_sprite_sheet);

  init_globals();
  init_hazards();
  init_map();

  set_state(0, ENTER_NEW_ROOM_STATE);
}

void update(uint32_t tick) {
  current_state.update(tick);
}

void draw() {
  camera(0, 0);
  pen(0, 0, 0);
  clear();

  current_state.draw();
}


// -------------------------------------------------------------------------------
// Moving states / functions
// -------------------------------------------------------------------------------

bool currently_moving() {
  return moving_north || moving_south || moving_east || moving_west;
}

bool is_neighbor(Point p, int x, int y) {
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


// -------------------------------------------------------------------------------
// Room states / functions
// -------------------------------------------------------------------------------

void update_enter_new_room(uint32_t tick) {
  if (compare_points(bat_a, world_x, world_y) ||
      compare_points(bat_b, world_x, world_y)) {
    set_state(tick, BAT_TRAVEL_STATE);
  } else if (compare_points(pit_a, world_x, world_y) ||
             compare_points(pit_b, world_x, world_y)) {
    set_state(tick, FELL_IN_PIT_STATE);
  } else if (compare_points(wumpus, world_x, world_y)) {
    set_state(tick, BUMPED_WUMPUS_STATE);
  } else {
    set_state(tick, STANDING_STATE);
  }
}

void update_standing_in_room(uint32_t tick) {
  moving_north = pressed(UP) && (map[world_x][world_y] & 0x0010);
  moving_south = pressed(DOWN) && (map[world_x][world_y] & 0x1000);
  moving_east = pressed(RIGHT) && (map[world_x][world_y] & 0x0100);
  moving_west = pressed(LEFT) && (map[world_x][world_y] & 0x0001);

  if (currently_moving()) {
    set_state(tick, WALKING_STATE);
  } else if (pressed(A) | pressed(B) | pressed(X) | pressed(Y)) {
    set_state(tick, SHOOTING_STATE);
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
    sprite(2, 22, 2);
  }

  if (is_neighbor(bat_a, world_x, world_y) ||
      is_neighbor(bat_b, world_x, world_y)) {
    sprite(1, 12, 2);
  }

  if (is_neighbor(pit_a, world_x, world_y) ||
      is_neighbor(pit_b, world_x, world_y)) {
    sprite(0, 2, 2);
  }
}


// -------------------------------------------------------------------------------
// Shooting states / functions
// -------------------------------------------------------------------------------

bool shooting_blink = false;
uint8_t shooting_fade = 0;
uint8_t target_x = world_x;
uint8_t target_y = world_y;

void update_shooting(uint32_t tick) {
  shooting_direction = NONE;
  target_x = world_x;
  target_y = world_y;

  if (pressed(A) | pressed(B) | pressed(X) | pressed(Y)) {
    set_state(tick, STANDING_STATE);
  } else if (pressed(UP) && (map[world_x][world_y] & NORTH)) {
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
    set_state(tick, ARROW_FLIGHT_STATE);
  }

  uint32_t time_slice = (tick - current_state.change_time) % 75;
  if (time_slice == 0) {
    shooting_blink = !shooting_blink;
  }

  if (shooting_blink) {
    shooting_fade = time_slice / 5;
  } else {
    shooting_fade = 15 - time_slice / 5;
  }
}

void draw_shooting() {
  draw_single_room();

  pen(0, 0, 0);

  if (map[world_x][world_y] & NORTH) {
    sprite(8, 52, 2, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & SOUTH) {
    sprite(10, 52, 102, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & EAST) {
    sprite(9, 102, 52, 1, 1, 16, 16);
  }
  if (map[world_x][world_y] & WEST) {
    sprite(11, 2, 52, 1, 1, 16, 16);
  }

  pen(15, 15, 15, shooting_fade);

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


// -------------------------------------------------------------------------------
// Arrow flight states / functions
// -------------------------------------------------------------------------------

int arrow_pos = 0;

void update_arrow_flight(uint32_t tick) {

  if (tick - current_state.change_time > 200) {
    if (compare_points(wumpus, target_x, target_y)) {
      set_state(tick, WIN_STATE);
    } else {
      set_state(tick, BUMPED_WUMPUS_STATE);
    }

    return;
  }

  arrow_pos = (int)((float)(tick - current_state.change_time) / 200.0 * 120.0);
}

void draw_arrow_flight() {
  pen(15, 15, 15);
  if (shooting_direction == EAST || shooting_direction == WEST) {
    frect(0, 40, 120, 40);
  } else {
    frect(40, 0, 40, 120);
  }

  if (shooting_direction == NORTH) {
    sprite(8, 56, 120 - arrow_pos);
  } else if (shooting_direction == EAST) {
    sprite(9, arrow_pos, 56);
  } else if (shooting_direction == SOUTH) {
    sprite(10, 56, arrow_pos);
  } else if (shooting_direction == WEST) {
    sprite(11, 120 - arrow_pos, 56);
  }
}


// -------------------------------------------------------------------------------
// Walking states / functions
// -------------------------------------------------------------------------------

void update_walking(uint32_t tick) {
  bool done_moving = false;

  if (moving_north) {
    camera_y--;
    if (camera_y <= -120) {
      world_y--;
      done_moving = true;
    }
  }

  if (moving_south) {
    camera_y++;
    if (camera_y >= 121) {
      world_y++;
      done_moving = true;
    }
  }

  if (moving_west) {
    camera_x--;
    if (camera_x <= -120) {
      world_x--;
      done_moving = true;
    }
  }

  if (moving_east) {
    camera_x++;
    if (camera_x >= 121) {
      world_x++;
      done_moving = true;
    }
  }

  if (done_moving) {
    camera_x = camera_y = 0;
    moving_north = moving_south = moving_east = moving_west = false;

    set_state(tick, ENTER_NEW_ROOM_STATE);
  }
}

void draw_walking() {
  camera(camera_x, camera_y);
  pen(15, 15, 15);

  draw_room(   0,    0, world_x,     world_y);

  draw_room(-120,    0, world_x - 1, world_y);
  draw_room(   0, -120, world_x,     world_y - 1);
  draw_room( 120,    0, world_x + 1, world_y);
  draw_room(   0,  120, world_x,     world_y + 1);

  camera(0, 0);
}


// -------------------------------------------------------------------------------
// Bat travel states / functions
// -------------------------------------------------------------------------------

int bat_x_pos = 0;

void update_bat_travel(uint32_t tick) {
  if (tick - current_state.change_time > 400) {
    world_x = rand_range(9);
    world_y = rand_range(9);

    set_state(tick, ENTER_NEW_ROOM_STATE);
  }

  bat_x_pos = (int)((float)(tick - current_state.change_time) / 400.0 * 120.0);
}

void draw_bat_travel() {
  pen(15, 15, 15);
  frect(0, 40, 120, 40);

  sprite(1, bat_x_pos, 52);
  sprite(7, bat_x_pos, 60);

  pen(15, 15, 15);
  text_centered("BAT!", 60, 110);
}


// -------------------------------------------------------------------------------
// Pit states / functions
// -------------------------------------------------------------------------------

int pit_y_pos = -8;
bool pit_show_text = false;

void update_fell_in_pit(uint32_t tick) {
  if (tick - current_state.change_time > 400) {
    set_state(tick, GAME_OVER_STATE);
    return;
  }

  pit_y_pos = (int)((float)(tick - current_state.change_time) / 200.0 * 120.0);
  pit_show_text = tick - current_state.change_time > 200;
}

void draw_fell_in_pit() {
  pen(15, 15, 15);
  frect(40, 0, 40, 120);

  pen(0, 11, 0);
  frect(40, 96, 40, 24);

  sprite(3, 56, pit_y_pos);

  if (pit_show_text) {
    pen(15, 15, 15);
    text_centered("PIT!", 60, 110);
  }
}


// -------------------------------------------------------------------------------
// Wumpus states / functions
// -------------------------------------------------------------------------------

int wumpus_y_offset = -8;
bool wumpus_show_text = false;

void update_bumped_wumpus(uint32_t tick) {
  if (tick - current_state.change_time > 400) {
    set_state(tick, GAME_OVER_STATE);
    return;
  }

  wumpus_y_offset = (int)((float)(tick - current_state.change_time) / 200.0 * (60.0 - 15.0));
  wumpus_y_offset = wumpus_y_offset < (60 - 15) ? wumpus_y_offset : (60 - 15);
  wumpus_show_text = tick - current_state.change_time > 200;
}

void draw_bumped_wumpus() {
  pen(15, 0, 0);
  frect(0, 0, 120, wumpus_y_offset);
  frect(0, 120-wumpus_y_offset, 120, wumpus_y_offset);

  for (int x=0; x<8; x++) {
    sprite(4, x*15, wumpus_y_offset, 1, 1, 15, 15);
    sprite(5, x*15, 120-wumpus_y_offset-15, 1, 1, 15, 15);
  }

  if (wumpus_show_text) {
    sprite(6, 10, 20, 1, 1, 24, 24);
    sprite(6, (120 - 10 - 24), 20, 1, 1, 24, 24);

    pen(15, 15, 15);
    text_centered("THE WUMPUS GOT YOU!", 60, 110);
  }
}


// -------------------------------------------------------------------------------
// Win states / functions
// -------------------------------------------------------------------------------

void update_win(uint32_t tick) {
  if (tick - current_state.change_time > 300) {
    set_state(tick, GAME_OVER_STATE);
    return;
  }
}

void draw_win() {
  pen(15, 15, 15);
  draw_room(0, 0, target_x, target_y);

  sprite(2, 40, 40, 1, 1, 40, 40);

  pen(15, 0, 0);
  text_centered("YOU GOT THE WUMPUS!", 60, 110);
}


// -------------------------------------------------------------------------------
// Splash screen states / functions
// -------------------------------------------------------------------------------

bool game_over_blink = false;
uint8_t game_over_fade = 0;

void update_game_over(uint32_t tick) {
  if (any_key_pressed()) {
    world_x = 0;
    world_y = 0;

    set_state(tick, ENTER_NEW_ROOM_STATE);
    return;
  }

  uint32_t time_slice = (tick - current_state.change_time) % 150;
  if (time_slice == 0) {
    game_over_blink = !game_over_blink;
  }

  if (game_over_blink) {
    game_over_fade = time_slice / 10;
  } else {
    game_over_fade = 15 - time_slice / 10;
  }
}

void draw_game_over() {
  pen(15, 15, 15);
  text_centered("GAME OVER", 60, 60);

  text_centered("PRESS ANY KEY", 60, 100);
  pen(0, 0, 0, game_over_fade);
  frect(0, 90, 120, 30);
}
