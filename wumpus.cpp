#include <cstdlib>
#include <ctime>

#include "picosystem.hpp"
#include "wumpus.hpp"

using namespace picosystem;


struct State {
  void (*update)(uint32_t);
  void (*draw)();
  uint32_t change_time;
};
State state;

struct Point {
  short x;
  short y;
};

// Custom sprite sheet
const color_t custom_sprite_sheet_data[512] = {
  0xf0f0, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0xf0f0,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000,
  0x0000, 0x0000, 0x00f0, 0x0000, 0x0000, 0x00f0, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0000, 0x0ff0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0ff0, 0x0000,
  0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000,
  0x0000, 0x0000, 0x00f0, 0x0000, 0x0000, 0x00f0, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0ff0, 0x0ff0, 0x0ff0, 0x0000, 0x0000, 0x0ff0, 0x0ff0, 0x0ff0,
  0x00ff, 0x0000, 0x0000, 0x00ff, 0x00ff, 0x0000, 0x0000, 0x00ff,
  0x0000, 0x0000, 0x00f0, 0x0000, 0x0000, 0x00f0, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0ff0, 0x0000, 0x0000, 0x0ff0, 0x0ff0, 0x0000, 0x0000, 0x0ff0,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x0000, 0x0000, 0x0000, 0x00f0, 0x00f0, 0x0000, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0ff0, 0x0000, 0x0000, 0x0ff0, 0x0ff0, 0x0000, 0x0000, 0x0ff0,
  0x0000, 0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x00f0, 0x00f0, 0x0000, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0000, 0x0000, 0x0ff0, 0x0000, 0x0000, 0x0ff0, 0x0000, 0x0000,
  0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000,
  0x0000, 0x0000, 0x00f0, 0x00f0, 0x00f0, 0x00f0, 0x0000, 0x0000,
  0x0000, 0xf0f0, 0x0000, 0x0000, 0x0000, 0x0000, 0xf0f0, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x00ff, 0x0000, 0x0000, 0x0000, 0x0000, 0x00ff, 0x0000,
  0x0000, 0x00f0, 0x0000, 0x00f0, 0x00f0, 0x0000, 0x00f0, 0x0000,
  0x0000, 0xf0f0, 0xf0f0, 0xf0f0, 0xf0f0, 0xf0f0, 0xf0f0, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x0000, 0x00ff, 0x0000, 0x0000, 0x00ff, 0x0000, 0x00ff,
  0x00f0, 0x0000, 0x0000, 0x00f0, 0x00f0, 0x0000, 0x0000, 0x00f0,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x000f, 0x000f, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x000f, 0x000f,
  0x0000, 0x0000, 0x000f, 0x000f, 0x000f, 0x000f, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x000f, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x000f,
  0x0000, 0x000f, 0x000f, 0x000f, 0x000f, 0x000f, 0x000f, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0xffff, 0xffff, 0x000f, 0x000f, 0x000f, 0x000f, 0xffff, 0xffff,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0xffff, 0xffff, 0x00f0, 0x00f0, 0x00f0, 0x00f0, 0xffff, 0xffff,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0xffff, 0xffff, 0x00f0, 0x00f0, 0x00f0, 0x00f0, 0xffff, 0xffff,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0xffff, 0xffff, 0xffff, 0x00f0, 0x00f0, 0xffff, 0xffff, 0xffff,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x0000, 0x0000,
  0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff,
  0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
buffer_t *CUSTOM_SPRITESHEET = buffer(32, 16, (void *)custom_sprite_sheet_data);
buffer_t *custom_sprite_sheet = CUSTOM_SPRITESHEET;

bool moving_north, moving_south, moving_east, moving_west;
int camera_x, camera_y;
int world_x, world_y;

// Hazard locations
Point wumpus, bat_a, bat_b, pit_a, pit_b;

int map[10][10];

int rand_range(int max) {
  return std::rand() / ((RAND_MAX + 1u)/max);
}

Point random_location() {
  Point location;

  location.x = rand_range(9);
  location.y = rand_range(9);

  return location;
}

void init_hazards() {
  wumpus = random_location();
  bat_a = random_location();
  bat_b = random_location();
  pit_a = random_location();
  pit_b = random_location();
}

void init() {
  // Seed random
  std::srand(std::time(nullptr));

  moving_north = false;
  moving_south = false;
  moving_east = false;
  moving_west = false;
  camera_x = 0;
  camera_y = 0;
  world_x = 0;
  world_y = 0;

  init_hazards();

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

  spritesheet(custom_sprite_sheet);

  state.update = update_enter_new_room;
  state.draw = draw_enter_new_room;
  state.change_time = 0;
}

void update(uint32_t tick) {
  state.update(tick);
}

void draw() {
  state.draw();
}


// -------------------------------------------------------------------------------
// Moving states / functions
// -------------------------------------------------------------------------------

bool currently_moving() {
  return moving_north || moving_south || moving_east || moving_west;
}

bool compare_points(Point p, int x, int y) {
  return p.x == x && p.y == y;
}

bool is_neighbor(Point p, int x, int y) {
  return (p.y == y && (p.x == x-1 || p.x == x+1)) ||
    (p.x == x && (p.y == y-1 || p.y == y+1));
}

void update_enter_new_room(uint32_t tick) {
  if (!currently_moving()) {
    if (compare_points(pit_a, world_x, world_y) ||
        compare_points(pit_b, world_x, world_y)) {
      // change state
      state.update = update_fell_in_pit;
      state.draw = draw_fell_in_pit;
      state.change_time = tick;
    }

    if (compare_points(wumpus, world_x, world_y)) {
      // change state
      state.update = update_bumped_wumpus;
      state.draw = draw_bumped_wumpus;
      state.change_time = tick;
    }

    moving_north = pressed(UP) && (map[world_x][world_y] & 0x0010);
    moving_south = pressed(DOWN) && (map[world_x][world_y] & 0x1000);
    moving_east = pressed(RIGHT) && (map[world_x][world_y] & 0x0100);
    moving_west = pressed(LEFT) && (map[world_x][world_y] & 0x0001);
  }

  if (moving_north) {
    camera_y--;
    if (camera_y <= -120) {
      camera_y = 0;
      world_y--;
      moving_north = false;
    }
  }
  if (moving_south) {
    camera_y++;
    if (camera_y >= 121) {
      camera_y = 0;
      world_y++;
      moving_south = false;
    }
  }
  if (moving_west) {
    camera_x--;
    if (camera_x <= -120) {
      camera_x = 0;
      world_x--;
      moving_west = false;
    }
  }
  if (moving_east) {
    camera_x++;
    if (camera_x >= 121) {
      camera_x = 0;
      world_x++;
      moving_east = false;
    }
  }
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

void draw_hazards() {
  if (compare_points(wumpus, world_x, world_y)) {
    pen(15, 0, 0);
    text("WUMPUS", 40, 40);
  } else if (is_neighbor(wumpus, world_x, world_y)) {
    sprite(2, 22, 2);
  }

  if (compare_points(bat_a, world_x, world_y) ||
      compare_points(bat_b, world_x, world_y)) {
    pen(0, 0, 15);
    text("BAT", 40, 50);
  } else if (is_neighbor(bat_a, world_x, world_y) ||
             is_neighbor(bat_b, world_x, world_y)) {
    sprite(1, 12, 2);
  }

  if (compare_points(pit_a, world_x, world_y) ||
      compare_points(pit_b, world_x, world_y)) {
    pen(0, 15, 0);
    text("PIT", 40, 60);
  } else if (is_neighbor(pit_a, world_x, world_y) ||
             is_neighbor(pit_b, world_x, world_y)) {
    sprite(0, 2, 2);
  }
}

void draw_enter_new_room() {
  camera(0, 0);
  pen(0, 0, 0);
  clear();

  camera(camera_x, camera_y);
  pen(15, 15, 15);

  draw_room(   0,    0, world_x,     world_y);

  draw_room(-120,    0, world_x - 1, world_y);
  draw_room(   0, -120, world_x,     world_y - 1);
  draw_room( 120,    0, world_x + 1, world_y);
  draw_room(   0,  120, world_x,     world_y + 1);

  camera(0, 0);
  pen(12, 11, 4 );
  text(str((float)world_x, 0),  96, 112);
  text(",",                    104, 112);
  text(str((float)world_y, 0), 112, 112);

  if (!currently_moving()) {
    draw_hazards();
  }
}

// -------------------------------------------------------------------------------
// Pit states / functions
// -------------------------------------------------------------------------------

int pit_y_pos = -8;
bool pit_show_text = false;

void update_fell_in_pit(uint32_t tick) {
  // animation should take 2 seconds
  if (tick - state.change_time > 400) {
    world_x = 0;
    world_y = 0;

    // change state
    state.update = update_enter_new_room;
    state.draw = draw_enter_new_room;
    state.change_time = tick;
  }

  pit_y_pos = (int)((float)(tick - state.change_time) / 200.0 * 120.0);
  pit_show_text = tick - state.change_time > 200;
}

void draw_fell_in_pit() {
  camera(0, 0);
  pen(0, 0, 0);
  clear();

  pen(15, 15, 15);
  frect(40, 0, 40, 120);

  pen(0, 11, 0);
  frect(40, 96, 40, 24);

  sprite(3, 56, pit_y_pos);

  if (pit_show_text) {
    pen(15, 15, 15);
    text("PIT!", 52, 112);
  }
}


// -------------------------------------------------------------------------------
// Wumpus states / functions
// -------------------------------------------------------------------------------

int wumpus_y_offset = -8;
bool wumpus_show_text = false;

void update_bumped_wumpus(uint32_t tick) {
  if (tick - state.change_time > 400) {
    world_x = 0;
    world_y = 0;

    // change state
    state.update = update_enter_new_room;
    state.draw = draw_enter_new_room;
    state.change_time = tick;
    return;
  }

  wumpus_y_offset = (int)((float)(tick - state.change_time) / 200.0 * (60.0 - 15.0));
  wumpus_y_offset = wumpus_y_offset < (60 - 15) ? wumpus_y_offset : (60 - 15);
  wumpus_show_text = tick - state.change_time > 200;
}

void draw_bumped_wumpus() {
  camera(0, 0);
  pen(0, 0, 0);
  clear();

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
    std::string wumpus_text = "WUMPUS!";
    uint32_t wumpus_width = text_width(wumpus_text);
    text(wumpus_text, 60 - wumpus_width / 2, 112);
  }
}
