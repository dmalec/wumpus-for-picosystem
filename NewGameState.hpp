// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef NEW_GAME_STATE_HPP_INCLUDED_
#define NEW_GAME_STATE_HPP_INCLUDED_

#include "picosystem.hpp"
#include "State.hpp"

class NewGameState: public State {

public:
  void handle_init(uint32_t total_ticks);
  State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) { /* do nothing */ }
  void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) { /* do nothing */ }
};

#endif // NEW_GAME_STATE_HPP_INCLUDED_
