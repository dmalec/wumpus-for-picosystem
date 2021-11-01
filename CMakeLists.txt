cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(wumpus C CXX ASM)

# Initialize the SDK
pico_sdk_init()

find_package(PICOSYSTEM REQUIRED)

picosystem_executable(
  wumpus

  game_types.hpp
  game_utils.hpp
  game_utils.cpp
  rand_utils.hpp
  rand_utils.cpp


  wumpus.hpp
  wumpus.cpp
  spritesheet.hpp
  spritesheet.cpp

  ArrowFlightState.cpp
  ArrowFlightState.hpp
  BatTravelState.cpp
  BatTravelState.hpp
  EnterNewRoomState.cpp
  EnterNewRoomState.hpp
  GameOverState.cpp
  GameOverState.hpp
  LoseToWumpusState.cpp
  LoseToWumpusState.hpp
  NewGameState.cpp
  NewGameState.hpp
  PitFallState.cpp
  PitFallState.hpp
  ShootingState.cpp
  ShootingState.hpp
  SplashScreenState.cpp
  SplashScreenState.hpp
  StandingInRoomState.cpp
  StandingInRoomState.hpp
  State.hpp
  WalkingState.cpp
  WalkingState.hpp
  WinState.cpp
  WinState.hpp
)

pixel_double(wumpus)
no_spritesheet(wumpus)
