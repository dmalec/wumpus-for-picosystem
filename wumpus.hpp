// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef WUMPUS_HPP_INCLUDED_
#define WUMPUS_HPP_INCLUDED_


// -------------------------------------------------------------------------------
// State types / functions
// -------------------------------------------------------------------------------

struct state {
  void (*update)(uint32_t);
  void (*draw)();
  uint32_t change_time;
};

void set_state(uint32_t tick, state new_state);


// -------------------------------------------------------------------------------
// Room states / functions
// -------------------------------------------------------------------------------

void update_enter_new_room(uint32_t tick);
void update_standing_in_room(uint32_t tick);
void draw_single_room();

const state ENTER_NEW_ROOM_STATE{.update = update_enter_new_room, .draw=draw_single_room};
const state STANDING_STATE{.update = update_standing_in_room, .draw=draw_single_room};


// -------------------------------------------------------------------------------
// Walking states / functions
// -------------------------------------------------------------------------------

void update_walking(uint32_t tick);
void draw_walking();

const state WALKING_STATE{.update = update_walking, .draw=draw_walking};


// -------------------------------------------------------------------------------
// Bat states / functions
// -------------------------------------------------------------------------------

void update_bat_travel(uint32_t tick);
void draw_bat_travel();

const state BAT_TRAVEL_STATE{.update = update_bat_travel, .draw=draw_bat_travel};


// -------------------------------------------------------------------------------
// Pit states / functions
// -------------------------------------------------------------------------------

void update_fell_in_pit(uint32_t tick);
void draw_fell_in_pit();

const state FELL_IN_PIT_STATE{.update = update_fell_in_pit, .draw=draw_fell_in_pit};


// -------------------------------------------------------------------------------
// Wumpus states / functions
// -------------------------------------------------------------------------------

void update_bumped_wumpus(uint32_t tick);
void draw_bumped_wumpus();

const state BUMPED_WUMPUS_STATE{.update = update_bumped_wumpus, .draw=draw_bumped_wumpus};


// -------------------------------------------------------------------------------
// Splash screen states / functions
// -------------------------------------------------------------------------------

void update_game_over(uint32_t tick);
void draw_game_over();

const state GAME_OVER_STATE{.update = update_game_over, .draw=draw_game_over};


#endif // WUMPUS_HPP_INCLUDED_
