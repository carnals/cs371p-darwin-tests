/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

    % valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdio.h>

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TESTDarwin
// -----------

using namespace std;

// ------------
// print_grid()
// ------------
TEST(Darwin, print_grid_1) { 
	World w(5, 5, 5);

	Creature food_1(FOOD, 0, 0, RIGHT);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 2, 2, LEFT);
	Creature* f2 = &food_2;
	Creature food_3(FOOD, 3, 3, DOWN);
	Creature* f3 = &food_3;

	w.add_creature(f1);
	w.add_creature(f2);
	w.add_creature(f3);

	w.print_world();	 
}

TEST(Darwin, print_grid_2) { 
	World w(5, 5, 5);

	Creature rover_1(ROVER, 0, 0, RIGHT);
	Creature* f1 = &rover_1;
	Creature food_1(FOOD, 2, 2, LEFT);
	Creature* f2 = &food_1;
	Creature trap_1(TRAP, 3, 3, DOWN);
	Creature* f3 = &trap_1;

	w.add_creature(f1);
	w.add_creature(f2);
	w.add_creature(f3);

	w.print_world();	 
}

TEST(Darwin, print_grid_3) { 
	World w(5, 5, 5);

	Creature hopper_1(HOPPER, 3, 3, RIGHT);
	Creature* f1 = &hopper_1;
	Creature trap_1(TRAP, 2, 2, LEFT);
	Creature* f2 = &trap_1;
	Creature rover_1(ROVER, 4, 4, DOWN);
	Creature* f3 = &rover_1;

	w.add_creature(f1);
	w.add_creature(f2);
	w.add_creature(f3);

	w.print_world();	 
}

// -------
// check()
// -------

TEST(Darwin, check_1) {
	Grid g(5, 5);
	ASSERT_EQ(g.check(2, 2), EMPTY); 
}

TEST(Darwin, check_2) {
	Grid g(5, 5);
	ASSERT_EQ(g.check(12, 12), EMPTY); 
}

TEST(Darwin, check_3) {
	Grid g(5, 5);
	g.set(2, 2, ROVER);
	ASSERT_EQ(g.check(2, 2), ROVER); 
}

// -----
// set()
// -----

TEST(Darwin, set_1) {
	Grid g(1, 1);
	g.set(1, 1, TRAP);
	ASSERT_EQ(g.check(1, 1), TRAP);
}

TEST(Darwin, set_2) {
	Grid g(5, 5);
	g.set(3, 3, EMPTY);
	ASSERT_EQ(g.check(3, 3), EMPTY);
}

TEST(Darwin, set_3) {
	Grid g(1, 5);
	g.set(1, 5, HOPPER);
	ASSERT_EQ(g.check(1, 5), HOPPER);
}

// ------
// move()
// ------

TEST(Darwin, move_1) {
	Grid g(5, 5);
	g.set(1, 1, HOPPER);
	g.move(1, 1, 4, 4);
	ASSERT_EQ(g.check(4, 4), HOPPER);
}

TEST(Darwin, move_2) {
	Grid g(5, 5);
	g.set(1, 1, HOPPER);
	g.move(1, 1, 2, 2);
	ASSERT_EQ(g.check(2, 2), HOPPER);
}

TEST(Darwin, move_3) {
	Grid g(5, 5);
	g.set(3, 5, TRAP);
	g.move(3, 5, 5, 3);
	ASSERT_EQ(g.check(5, 3), TRAP);
}

// -----------
// in_bounds()
// -----------

TEST(Darwin, in_bounds_1) {
	Grid g(10, 10);
	ASSERT_TRUE(g.in_bounds(5, 3));
}

TEST(Darwin, in_bounds_2) {
	Grid g(10, 10);
	ASSERT_FALSE(g.in_bounds(-15, 15));
}

TEST(Darwin, in_bounds_3) {
	Grid g(10, 10);
	ASSERT_FALSE(g.in_bounds(20, 5));
}

// -------------
// comp_coords()
// -------------

TEST(Darwin, comp_coords_1) {
	Creature food_1(FOOD, 1, 1, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 2, 2, UP);
	Creature* f2 = &food_2;
	ASSERT_FALSE(World::comp_coords(f2, f1));
}

TEST(Darwin, comp_coords_2) {
	Creature food_1(FOOD, 3, 3, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 2, 2, UP);
	Creature* f2 = &food_2;
	ASSERT_TRUE(World::comp_coords(f2, f1));
}

TEST(Darwin, comp_coords_3) {
	Creature food_1(FOOD, 2, 2, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 5, 5, UP);
	Creature* f2 = &food_2;
	ASSERT_FALSE(World::comp_coords(f2, f1));
}

TEST(Darwin, comp_coords_4) {
	Creature food_1(FOOD, 1, 2, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 1, 5, UP);
	Creature* f2 = &food_2;
	ASSERT_FALSE(World::comp_coords(f2, f1));
}

TEST(Darwin, comp_coords_5) {
	Creature food_1(FOOD, 1, 2, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 1, 3, UP);
	Creature* f2 = &food_2;
	ASSERT_FALSE(World::comp_coords(f2, f1));
}

TEST(Darwin, comp_coords_6) {
	Creature food_1(FOOD, 4, 5, UP);
	Creature* f1 = &food_1;
	Creature food_2(FOOD, 4, 3, UP);
	Creature* f2 = &food_2;
	ASSERT_TRUE(World::comp_coords(f2, f1));
}

// ----------
// Creature()
// ----------

TEST(Darwin, creature_1) {
	Creature c1(HOPPER, 2, 2, UP);
	ASSERT_EQ(c1.get_r(), 2);
	ASSERT_EQ(c1.get_c(), 2);
}

TEST(Darwin, creature_2) {
	Creature c1(HOPPER, 3, 5, UP);
	ASSERT_EQ(c1.get_r(), 3);
	ASSERT_EQ(c1.get_c(), 5);
}

TEST(Darwin, creature_3) {
	Creature c1(HOPPER, 19, 2, UP);
	ASSERT_EQ(c1.get_r(), 19);
	ASSERT_EQ(c1.get_c(), 2);
}

TEST(Darwin, creature_4) {
	Creature c1(HOPPER, 33, 14, UP);
	ASSERT_EQ(c1.get_r(), 33);
	ASSERT_EQ(c1.get_c(), 14);
}

TEST(Darwin, creature_5) {
	Creature c1(HOPPER, 15, 162, UP);
	ASSERT_EQ(c1.get_r(), 15);
	ASSERT_EQ(c1.get_c(), 162);
}

TEST(Darwin, creature_6) {
	Creature c1(HOPPER, 0, 0, UP);
	ASSERT_EQ(c1.get_r(), 0);
	ASSERT_EQ(c1.get_c(), 0);
}

TEST(Darwin, creature_7) {
	Creature c1(HOPPER, -5, 15, UP);
	ASSERT_EQ(c1.get_r(), -5);
	ASSERT_EQ(c1.get_c(), 15);
}

TEST(Darwin, creature_8) {
	Creature c1(HOPPER, 2, 3, UP);
	ASSERT_EQ(c1.get_r(), 2);
	ASSERT_EQ(c1.get_c(), 3);
}

TEST(Darwin, creature_9) {
	Creature c1(HOPPER, 5, 44, UP);
	ASSERT_EQ(c1.get_r(), 5);
	ASSERT_EQ(c1.get_c(), 44);
}

TEST(Darwin, creature_10) {
	Creature c1(HOPPER, 15, 200, UP);
	ASSERT_EQ(c1.get_r(), 15);
	ASSERT_EQ(c1.get_c(), 200);
}

TEST(Darwin, creature_11) {
	Creature c1(HOPPER, 15, 200, UP);
	ASSERT_TRUE(c1.is_same_coord(15, 200));
}

TEST(Darwin, creature_12) {
	Creature c1(HOPPER, 15, 200, UP);
	ASSERT_FALSE(c1.is_same_coord(20, 15));
}

// -----
// act()
// -----

TEST(Darwin, act_1) {
	Grid g(10, 10);
	Creature c1(HOPPER, 0, 0, DOWN);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_r(), 1);
}

TEST(Darwin, act_2) {
	Grid g(10, 10);
	Creature c1(HOPPER, 1, 0, DOWN);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_r(), 2);
}

TEST(Darwin, act_3) {
	Grid g(10, 10);
	Creature c1(HOPPER, 5, 5, DOWN);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_r(), 6);
}

TEST(Darwin, act_4) {
	Grid g(10, 10);
	Creature c1(HOPPER, 0, 0, RIGHT);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_c(), 1);
}

TEST(Darwin, act_5) {
	Grid g(10, 10);
	Creature c1(HOPPER, 0, 0, LEFT);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_c(), 0);
}

TEST(Darwin, act_6) {
	Grid g(10, 10);
	Creature c1(HOPPER, 0, 0, UP);
	Creature* f1 = &c1;
	vector<Creature*> players;
	players.push_back(f1);
	f1->act(g, players);
	ASSERT_EQ(f1->get_r(), 0);
}

// ---------------
// is_same_coord()
// ---------------

TEST(Darwin, is_same_coord_1) {
	Creature c1(HOPPER, 0, 0, UP);
	ASSERT_TRUE(c1.is_same_coord(0, 0));
}

TEST(Darwin, is_same_coord_2) {
	Creature c1(HOPPER, 0, 5, UP);
	ASSERT_TRUE(c1.is_same_coord(0, 5));
}

TEST(Darwin, is_same_coord_3) {
	Creature c1(HOPPER, 6, 0, UP);
	ASSERT_TRUE(c1.is_same_coord(6, 0));
}

TEST(Darwin, is_same_coord_4) {
	Creature c1(HOPPER, 7, 5, UP);
	ASSERT_TRUE(c1.is_same_coord(7, 5));
}

TEST(Darwin, is_same_coord_5) {
	Creature c1(HOPPER, 20, 1, UP);
	ASSERT_TRUE(c1.is_same_coord(20, 1));
}

TEST(Darwin, is_same_coord_6) {
	Creature c1(HOPPER, 0, 0, UP);
	ASSERT_FALSE(c1.is_same_coord(1, 1));
}

TEST(Darwin, is_same_coord_7) {
	Creature c1(HOPPER, 0, 0, UP);
	ASSERT_FALSE(c1.is_same_coord(4, 5));
}

TEST(Darwin, is_same_coord_8) {
	Creature c1(HOPPER, 6, 6, UP);
	ASSERT_FALSE(c1.is_same_coord(7, 7));
}

TEST(Darwin, is_same_coord_9) {
	Creature c1(HOPPER, 8, 8, UP);
	ASSERT_FALSE(c1.is_same_coord(4, 99));
}

// -----------------
// is_same_species()
// -----------------

TEST(Darwin, is_same_species_1) {
	Creature c1(HOPPER, 0, 0, LEFT);
	ASSERT_TRUE(c1.is_same_species(HOPPER));
}

TEST(Darwin, is_same_species_2) {
	Creature c1(ROVER, 0, 0, LEFT);
	ASSERT_TRUE(c1.is_same_species(ROVER));
}

TEST(Darwin, is_same_species_3) {
	Creature c1(TRAP, 0, 0, LEFT);
	ASSERT_TRUE(c1.is_same_species(TRAP));
}

TEST(Darwin, is_same_species_4) {
	Creature c1(BEST, 0, 0, LEFT);
	ASSERT_TRUE(c1.is_same_species(BEST));
}

TEST(Darwin, is_same_species_5) {
	Creature c1(HOPPER, 0, 0, LEFT);
	ASSERT_FALSE(c1.is_same_species(ROVER));
}

TEST(Darwin, is_same_species_6) {
	Creature c1(HOPPER, 0, 0, LEFT);
	ASSERT_FALSE(c1.is_same_species(TRAP));
}

TEST(Darwin, is_same_species_7) {
	Creature c1(HOPPER, 0, 0, LEFT);
	ASSERT_FALSE(c1.is_same_species(BEST));
}

TEST(Darwin, is_same_species_8) {
	Creature c1(HOPPER, 0, 0, LEFT);
	ASSERT_FALSE(c1.is_same_species(FOOD));
}

TEST(Darwin, is_same_species_9) {
	Creature c1(FOOD, 0, 0, LEFT);
	ASSERT_FALSE(c1.is_same_species(HOPPER));
}

// -----
// hop()
// -----

TEST(Darwin, hop_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 1);
}

TEST(Darwin, hop_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, LEFT);
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 0);
}

TEST(Darwin, hop_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, UP);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 0);
}

TEST(Darwin, hop_4) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, RIGHT);
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 1);
}

TEST(Darwin, hop_5) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, DOWN);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 6);
}

TEST(Darwin, hop_6) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, LEFT);
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 4);
}

TEST(Darwin, hop_7) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, UP);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 4);
}

TEST(Darwin, hop_8) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, RIGHT);
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 6);
}

TEST(Darwin, hop_9) {
	Grid g(10, 10);
	Creature c1(ROVER, -5, -5, DOWN);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), -5);
}

TEST(Darwin, hop_10) {
	Grid g(10, 10);
	Creature c1(ROVER, -5, -5, RIGHT);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), -5);
}

TEST(Darwin, hop_11) {
	Grid g(10, 10);
	Creature c1(ROVER, -5, -5, UP);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), -5);
}

TEST(Darwin, hop_12) {
	Grid g(10, 10);
	Creature c1(ROVER, -5, -5, LEFT);
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), -5);
}

// ------
// left()
// ------

TEST(Darwin, left_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 1);
}

TEST(Darwin, left_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, RIGHT);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 0);
}

TEST(Darwin, left_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, UP);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 0);
}

TEST(Darwin, left_4) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, LEFT);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 1);
}

TEST(Darwin, left_5) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, DOWN);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 6);
}

TEST(Darwin, left_6) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, UP);
	c1.left();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 4);
}

// -------
// right()
// -------

TEST(Darwin, right_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 0);
}

TEST(Darwin, right_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, RIGHT);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 1);
}

TEST(Darwin, right_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, UP);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 1);
}

TEST(Darwin, right_4) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, LEFT);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_r(), 0);
}

TEST(Darwin, right_5) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, DOWN);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 4);
}

TEST(Darwin, right_6) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, UP);
	c1.right();
	c1.hop(g);
	ASSERT_EQ(c1.get_c(), 6);
}

// ----------
// is_empty()
// ----------

TEST(Darwin, is_empty_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	ASSERT_TRUE(c1.is_empty(g, 0));
}

TEST(Darwin, is_empty_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 5, 5, LEFT);
	ASSERT_TRUE(c1.is_empty(g, 0));
}

TEST(Darwin, is_empty_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 6, 6, UP);
	ASSERT_TRUE(c1.is_empty(g, 0));
}

// ---------
// is_wall()
// ---------

TEST(Darwin, is_wall_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	ASSERT_FALSE(c1.is_wall(g, 0));
}

TEST(Darwin, is_wall_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, UP);
	ASSERT_TRUE(c1.is_wall(g, 0));
}

TEST(Darwin, is_wall_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, LEFT);
	ASSERT_TRUE(c1.is_wall(g, 0));
}

// ----------
// is_enemy()
// ---------

TEST(Darwin, is_enemy_1) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	g.set(1, 0, HOPPER);
	ASSERT_TRUE(c1.is_enemy(g, 0));
}

TEST(Darwin, is_enemy_2) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	g.set(1, 0, FOOD);
	ASSERT_FALSE(c1.is_enemy(g, 0));
}

TEST(Darwin, is_enemy_3) {
	Grid g(10, 10);
	Creature c1(FOOD, 0, 0, DOWN);
	g.set(1, 0, ROVER);
	ASSERT_TRUE(c1.is_enemy(g, 0));
}

// -----------------
// get_space_ahead()
// -----------------

TEST(Darwin, get_space_ahead_1) {
	Creature c1(FOOD, 0, 0, DOWN);
	int r = 0;
	int c = 0;
	c1.get_space_ahead(r, c);
	ASSERT_EQ(r, 1);
	ASSERT_EQ(c, 0);
}

TEST(Darwin, get_space_ahead_2) {
	Creature c1(FOOD, 0, 0, RIGHT);
	int r = 0;
	int c = 0;
	c1.get_space_ahead(r, c);
	ASSERT_EQ(r, 0);
	ASSERT_EQ(c, 1);
}

TEST(Darwin, get_space_ahead_3) {
	Creature c1(FOOD, 5, 5, LEFT);
	int r = 0;
	int c = 0;
	c1.get_space_ahead(r, c);
	ASSERT_EQ(r, 0);
	ASSERT_EQ(c, -1);
}

// -------
// get_r()
// -------

TEST(Darwin, get_r_1) {
	Creature c1(FOOD, 9, 9, RIGHT);
	ASSERT_EQ(c1.get_r(), 9);
}

TEST(Darwin, get_r_2) {
	Creature c1(FOOD, 5, 9, RIGHT);
	ASSERT_EQ(c1.get_r(), 5);
}

TEST(Darwin, get_r_3) {
	Creature c1(FOOD, 11, 9, RIGHT);
	ASSERT_EQ(c1.get_r(), 11);
}

// -------
// get_c()
// -------

TEST(Darwin, get_c_1) {
	Creature c1(FOOD, 9, 9, RIGHT);
	ASSERT_EQ(c1.get_c(), 9);
}

TEST(Darwin, get_c_2) {
	Creature c1(FOOD, 9, 5, RIGHT);
	ASSERT_EQ(c1.get_c(), 5);
}

TEST(Darwin, get_c_3) {
	Creature c1(FOOD, 9, 55, RIGHT);
	ASSERT_EQ(c1.get_c(), 55);
}

// ----------
// set_name()
// ----------

TEST(Darwin, set_name_1) {
	Creature c1(FOOD, 0, 0, DOWN);
	c1.set_name(HOPPER);
	ASSERT_TRUE(c1.is_same_species(HOPPER));
}

TEST(Darwin, set_name_2) {
	Creature c1(FOOD, 0, 0, DOWN);
	c1.set_name(ROVER);
	ASSERT_TRUE(c1.is_same_species(ROVER));
}

TEST(Darwin, set_name_3) {
	Creature c1(FOOD, 0, 0, DOWN);
	c1.set_name(FOOD);
	ASSERT_TRUE(c1.is_same_species(FOOD));
}
