// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef STATE_HPP_INCLUDED_
#define STATE_HPP_INCLUDED_

#include "game_types.hpp"

class State {

public:
  virtual void handle_init(uint32_t total_ticks) = 0;

  void init(uint32_t total_ticks) {
    state_change_tick = total_ticks;

    handle_init(total_ticks);
  }

  virtual State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks) = 0;
  virtual void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks) = 0;

  State *update(uint32_t total_ticks) {
    uint32_t elapsed_ticks = total_ticks - state_change_tick;

    State *new_state = check_state_change(total_ticks, elapsed_ticks);

    handle_update(total_ticks, elapsed_ticks);

    return new_state;
  }

  virtual void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks) = 0;

  void draw(uint32_t total_ticks) {
    uint32_t elapsed_ticks = total_ticks - state_change_tick;

    handle_draw(total_ticks, elapsed_ticks);
  }


protected:
  uint32_t state_change_tick;
};

#endif // STATE_HPP_INCLUDED_
