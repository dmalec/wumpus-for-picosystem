// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef ENTER_NEW_ROOM_STATE_HPP_INCLUDED_
#define ENTER_NEW_ROOM_STATE_HPP_INCLUDED_

#include "picosystem.hpp"
#include "State.hpp"

class EnterNewRoomState: public State {

public:
  void handle_init(uint32_t total_ticks);
  State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks);
};

#endif // ENTER_NEW_ROOM_STATE_HPP_INCLUDED_