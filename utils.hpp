// Copyright(c) 2021 Dan Malec
//
// MIT License (see LICENSE file for details)

#ifndef UTILS_HPP_INCLUDED_
#define UTILS_HPP_INCLUDED_


struct Point {
  short x;
  short y;
};


bool compare_points(Point p, int x, int y);


int rand_range(int max);
Point random_location();


bool any_key_pressed();


#endif // UTILS_HPP_INCLUDED_

