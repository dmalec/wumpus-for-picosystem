// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef LOSE_TO_WUMPUS_STATE_HPP_INCLUDED_
#define LOSE_TO_WUMPUS_STATE_HPP_INCLUDED_

#include "picosystem.hpp"
#include "State.hpp"

class LoseToWumpusState: public State {

public:
  void handle_init(uint32_t total_ticks);
  State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks);

private:
  uint32_t teeth_offset;
  bool show_text;
};

#endif // LOSE_TO_WUMPUS_STATE_HPP_INCLUDED_
