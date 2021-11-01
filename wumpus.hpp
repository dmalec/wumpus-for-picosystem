// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef WUMPUS_HPP_INCLUDED_
#define WUMPUS_HPP_INCLUDED_

#include "game_types.hpp"
#include "game_utils.hpp"

#include "State.hpp"


// -------------------------------------------------------------------------------
// Compile Time Options
// -------------------------------------------------------------------------------

// #define FIXED_PLACEMENT 1

// -------------------------------------------------------------------------------
// Globals
// -------------------------------------------------------------------------------

extern State *current_state;
extern bool moving_north, moving_south, moving_east, moving_west;
extern uint32_t shooting_direction;
extern GamePoint wumpus, bat_a, bat_b, pit_a, pit_b;
extern uint8_t target_x, target_y;
extern uint8_t world_x, world_y;
extern int32_t pit_losses, wumpus_losses, wumpus_wins;
extern int map[10][10];


// -------------------------------------------------------------------------------
// Map functions
// -------------------------------------------------------------------------------

GamePoint random_location();
bool currently_moving();
bool is_neighbor(GamePoint p, int x, int y);


// -------------------------------------------------------------------------------
// States
// -------------------------------------------------------------------------------

extern State *arrow_flight_state;
extern State *bat_travel_state;
extern State *enter_new_room_state;
extern State *game_over_state;
extern State *lose_to_wumpus_state;
extern State *new_game_state;
extern State *pit_fall_state;
extern State *shooting_state;
extern State *splash_screen_state;
extern State *standing_in_room_state;
extern State *walking_state;
extern State *win_state;


// -------------------------------------------------------------------------------
// Drawing function
// -------------------------------------------------------------------------------

void draw_room(int x, int y, int map_x, int map_y);
void draw_single_room();


#endif // WUMPUS_HPP_INCLUDED_
