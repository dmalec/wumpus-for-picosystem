// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef PIT_FALL_STATE_HPP_INCLUDED_
#define PIT_FALL_STATE_HPP_INCLUDED_

#include "picosystem.hpp"
#include "State.hpp"

class PitFallState: public State {

public:
  void handle_init(uint32_t total_ticks);
  State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks);

private:
  uint32_t pit_y_pos;
  bool pit_show_text;
};

#endif // PIT_FALL_STATE_HPP_INCLUDED_
