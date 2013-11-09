/*
 * =====================================================================================
 *
 *       Filename:  TestDarwin.c++
 *
 *    Description:  Unit Tests for Darwin
 *
 *        Version:  1.0
 *        Created:  11/07/2013 05:18:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Patrick Fennelly (), patrickfennelly0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/*
To test the program:

 % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

 % valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"


#define private public
#define protected public
#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

// ----------------------
// Creature.set_direction
// ----------------------

  species food   = species ("Food", 
                            "left\
                             \ngo 0\
                             \n\n");

  species hopper = species ("Hopper", 
                            "hop\
                             \ngo 0\
                             \n\n");

  species roamer = species ("Roamer",
                            "if_enemy 9\
                            \nif_empty 7\
                            \nif_random 5\
                            \nleft\
                            \ngo 0\
                            \nright\
                            \ngo 0\
                            \nhop\
                            \ngo 0\
                            \ninfect\
                            \ngo 0\
                            \n\n");

  species trap  = species ("Trap", 
                           "if_enemy 3\
                            \nleft\
                            \ngo 0\
                            \ninfect\
                            \ngo 0\
                            \n\n");

TEST(Darwin, execute1) {
	ASSERT_TRUE(interpreter::execute(0, 0, 0, 0, "hop") == -1);
}
TEST(Darwin, execute2) {
	ASSERT_TRUE(interpreter::execute(0, 0, 0, 0, "right") == -1);
}
TEST(Darwin, execute3) {
	ASSERT_TRUE(interpreter::execute(0, 0, 0, 0, "left") == -1);
}
TEST(Darwin, execute4) {
	ASSERT_TRUE(interpreter::execute(0, 0, 0, 0, "infect") == -1);
}
TEST(Darwin, execute5) {
	ASSERT_TRUE(interpreter::execute(100, 100, 0, 0, "hop") == -1);
}
TEST(Darwin, execute6) {
	ASSERT_TRUE(interpreter::execute(100, 100, 0, 0, "hop") == -1);
}
TEST(Darwin, execute7) {
	ASSERT_TRUE(interpreter::execute(-100, 100, 0, 0, "hop") == -1);
}
TEST(Darwin, execute8) {
	ASSERT_TRUE(interpreter::execute(100, 100, -10, 0, "hop") == -1);
}
game test;
TEST(Darwin, add1) {
test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&food, 1, 1, NORTH) == true);
}
TEST(Darwin, add2) {
  ASSERT_TRUE(test.add_creature(&food, 1, 1, NORTH) == false);
}
TEST(Darwin, add3) {
  ASSERT_TRUE(test.add_creature(&food, 0, 0, SOUTH) == true);
}
TEST(Darwin, add4) {
  ASSERT_TRUE(test.add_creature(&food, 1, 1, EAST) == false);
}
TEST(Darwin, add5) {
  ASSERT_TRUE(test.add_creature(&food, 9, 9, WEST) == false);
}
TEST(Darwin, add6) {
  ASSERT_TRUE(test.add_creature(&food, -1, 1, NORTH) == false);
}
TEST(Darwin, add7) {
  ASSERT_TRUE(test.add_creature(&food, 2, 2, SOUTH) == true);
}
TEST(Darwin, add8) {
  ASSERT_TRUE(test.add_creature(&food, 0, 0, NORTH) == false);
}
TEST(Darwin, reset) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, NORTH) == true);
}
TEST(Darwin, is_enemy1) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, NORTH) == true);
  ASSERT_TRUE(test.add_creature(&food, 1, 2, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 2, 1, 1) == true);
}
TEST(Darwin, is_enemy2) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, NORTH) == true);
  ASSERT_TRUE(test.add_creature(&food, 1, 2, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 2, 1, 1) == true);
}
TEST(Darwin, is_enemy3) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 2, 1, 1) == false);
}
TEST(Darwin, is_enemy4) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, NORTH) == true);
  ASSERT_TRUE(test.add_creature(&hopper, 1, 2, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 2, 1, 1) == false);
}
TEST(Darwin, is_enemy5) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, SOUTH) == true);
  ASSERT_TRUE(test.add_creature(&food, 1, 2, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 1, 1, 2) == true);
}
TEST(Darwin, is_enemy6) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, SOUTH) == true);
  ASSERT_TRUE(test.add_creature(&hopper, 2, 3, NORTH) == true);
  ASSERT_TRUE(board::enemy(1, 1, 2, 3) == false);
}
TEST(Darwin, is_wall1) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 1, SOUTH) == true);
  ASSERT_TRUE(board::wall(1, 1) == false);
}
TEST(Darwin, is_wall2) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 0, 1, SOUTH) == true);
  ASSERT_TRUE(board::wall(0, -1) == true);
}
TEST(Darwin, is_wall3) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 0, SOUTH) == true);
  ASSERT_TRUE(board::wall(1, 0) == false);
}
TEST(Darwin, is_wall4) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 7, 7, SOUTH) == true);
  ASSERT_TRUE(board::wall(7, 9) == true);
}
TEST(Darwin, is_wall5) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 1, 7, SOUTH) == true);
  ASSERT_TRUE(board::wall(1, 8) == true);
}
TEST(Darwin, is_wall6) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 0, 7, SOUTH) == true);
  ASSERT_TRUE(board::wall(-3, 7) == true);
}
TEST(Darwin, is_wall7) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 0, 7, SOUTH) == true);
  ASSERT_TRUE(board::wall(100, 7) == true);
}
TEST(Darwin, is_wall8) {
  test = {8, 8, -1};
  ASSERT_TRUE(test.add_creature(&hopper, 0, 7, SOUTH) == true);
  ASSERT_TRUE(board::wall(-3, 888) == true);
}
