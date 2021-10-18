cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(wumpus C CXX ASM)

# Initialize the SDK
pico_sdk_init()

find_package(PICOSYSTEM REQUIRED)

picosystem_executable(
  wumpus
  wumpus.hpp
  wumpus.cpp
)

pixel_double(wumpus)
no_spritesheet(wumpus)
