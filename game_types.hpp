// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef GAME_TYPES_HPP_INCLUDED_
#define GAME_TYPES_HPP_INCLUDED_


struct GamePoint {
  uint8_t x;
  uint8_t y;
};


enum GameWall {
  NONE =  0x0000,
  WEST =  0x0001,
  NORTH = 0x0010,
  EAST =  0x0100,
  SOUTH = 0x1000
};


#endif // GAME_TYPES_HPP_INCLUDED_
