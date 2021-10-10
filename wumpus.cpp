#include "picosystem.hpp"

using namespace picosystem;

bool moving_north, moving_south, moving_east, moving_west;
int camera_x, camera_y;
int world_x, world_y;

int map[10][10];

void init() {
  moving_north = false;
  moving_south = false;
  moving_east = false;
  moving_west = false;
  camera_x = 0;
  camera_y = 0;
  world_x = 0;
  world_y = 0;

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

bool currently_moving() {
  return moving_north || moving_south || moving_east || moving_west;
}

void update(uint32_t tick) {
  if (!currently_moving()) {
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

void draw() {
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
}
