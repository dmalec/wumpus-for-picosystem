// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef SHOOTING_STATE_HPP_INCLUDED_
#define SHOOTING_STATE_HPP_INCLUDED_

#include "picosystem.hpp"
#include "State.hpp"

class ShootingState: public State {

public:
  void handle_init(uint32_t total_ticks);
  State *check_state_change(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_update(uint32_t total_ticks, uint32_t elapsed_ticks);
  void handle_draw(uint32_t total_ticks, uint32_t elapsed_ticks);

private:
  bool fade_in;
  uint8_t fade_level;
};

#endif // SHOOTING_STATE_HPP_INCLUDED_
