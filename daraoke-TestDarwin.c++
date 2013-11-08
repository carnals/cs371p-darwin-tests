/*
To test the program:

% g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

% valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Darwin.c++"

using namespace std;

// -----------
// add_creature
// -----------

TEST(Darwin, add_creature1) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 0, 0);
	ASSERT_TRUE(world.creatures[0].species.letter == trap.letter);
	ASSERT_TRUE(world.creatures[0].direction == NORTH);
}

TEST(Darwin, add_creature2) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	Species food('f');
	world.add_creature(trap, NORTH, 0, 0);
	world.add_creature(food, WEST, 2, 2);
	ASSERT_TRUE(world.creatures[0].species.letter == trap.letter);
	ASSERT_TRUE(world.creatures[0].direction == NORTH);
	ASSERT_TRUE(world.creatures[1].species.letter == food.letter);
	ASSERT_TRUE(world.creatures[1].direction == WEST);
}

TEST(Darwin, add_creature3) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	Species food('f');
	Species hopper('h');
	world.add_creature(trap, NORTH, 0, 0);
	world.add_creature(food, WEST, 2, 2);
	world.add_creature(hopper, EAST, 2, 2);

	ASSERT_TRUE(world.creatures[0].species.letter == trap.letter);
	ASSERT_TRUE(world.creatures[0].direction == NORTH);
	ASSERT_TRUE(world.creatures[1].species.letter == food.letter);
	ASSERT_TRUE(world.creatures[1].direction == WEST);
	ASSERT_TRUE(world.creatures[2].species.letter == hopper.letter);
	ASSERT_TRUE(world.creatures[2].direction == EAST);
}

// -----------
// get_creature
// -----------

TEST(Darwin, get_creature1) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 0, 0);

	ASSERT_TRUE(world.get_creature(0, 0) == 0);
}

TEST(Darwin, get_creature2) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	Species food('f');
	world.add_creature(trap, NORTH, 0, 0);
	world.add_creature(food, WEST, 2, 3);

	ASSERT_TRUE(world.get_creature(0, 0) == 0);
	ASSERT_TRUE(world.get_creature(2, 3) == 1);
}


TEST(Darwin, get_creature3) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	Species food('f');
	Species hopper('h');
	world.add_creature(trap, NORTH, 9, 9);
	world.add_creature(food, WEST, 2, 3);
	world.add_creature(hopper, EAST, 3, 2);

	ASSERT_TRUE(world.get_creature(9, 9) == 0);
	ASSERT_TRUE(world.get_creature(2, 3) == 1);
	ASSERT_TRUE(world.get_creature(3, 2) == 2);
}

// -----------
// if_empty
// -----------

TEST(Darwin, if_empty1) {
	DarwinWorld world(10, 10);	
	ASSERT_TRUE(world.if_empty(0, 0) == true);
}

TEST(Darwin, if_empty2) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 3, 3);
	ASSERT_TRUE(world.if_empty(0, 2) == true);
	ASSERT_TRUE(world.if_empty(3, 3) == false);
}

TEST(Darwin, if_empty3) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 3, 3);
	world.add_creature(trap, NORTH, 5, 5);
	ASSERT_TRUE(world.if_empty(2, 2) == true);
	ASSERT_TRUE(world.if_empty(3, 3) == false);
	ASSERT_TRUE(world.if_empty(5, 5) == false);
}

// -----------
// if_wall
// -----------

TEST(Darwin, if_wall1) {
	DarwinWorld world(10, 10);	
	ASSERT_TRUE(world.if_wall(0, 0) == false);
	ASSERT_TRUE(world.if_wall(-1, 0) == true);
}

TEST(Darwin, if_wall2) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 0, 0);
	ASSERT_TRUE(world.if_wall(0, 0) == false);
	ASSERT_TRUE(world.if_wall(0, -4) == true);
}

TEST(Darwin, if_wall3) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 0, 0);
	ASSERT_TRUE(world.if_wall(0, 0) == false);
	ASSERT_TRUE(world.if_wall(10, 0) == true);
}

// -----------
// if_enemy
// -----------

TEST(Darwin, if_enemy1) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	world.add_creature(trap, NORTH, 0, 0);
	world.add_creature(trap, NORTH, 1, 0);

	ASSERT_TRUE(world.if_enemy(world.creatures[0], 1, 0) == false);
}

TEST(Darwin, if_enemy2) {
	DarwinWorld world(10, 10);	
	Species trap('t');
	Species food('f');
	world.add_creature(trap, NORTH, 0, 0);
	world.add_creature(food, NORTH, 1, 0);

	ASSERT_TRUE(world.if_enemy(world.creatures[0], 1, 0) == true);
}

TEST(Darwin, if_enemy3) {
	DarwinWorld world(12, 12);
	Species food('f');
	world.add_creature(food, NORTH, 10, 0);

	// Enemy to self?
	ASSERT_TRUE(world.if_enemy(world.creatures[0], 10, 0) == false);
}

// -----------
// infect
// -----------

TEST(Darwin, infect1) {
	DarwinWorld world(10, 10);	
	Species food('f');
	Species trap('t');
	world.add_creature(food, NORTH, 0, 0);
	world.add_creature(trap, NORTH, 1, 1);
	world.infect(world.creatures[0], 1, 1);

	ASSERT_TRUE(world.creatures[1].species.letter == 'f');
}

TEST(Darwin, infect2) {
	DarwinWorld world(10, 10);	
	Species food('f');
	world.add_creature(food, NORTH, 0, 0);
	world.add_creature(food, EAST, 1, 1);
	world.infect(world.creatures[0], 1, 1);

	ASSERT_TRUE(world.creatures[1].species.letter == 'f');
}

TEST(Darwin, infect3) {
	DarwinWorld world(10, 10);	
	Species food('f');
	Species trap('t');
	world.add_creature(food, NORTH, 0, 0);
	world.add_creature(trap, EAST, 1, 1);
	world.add_creature(trap, EAST, 2, 2);
	world.infect(world.creatures[0], 1, 1);

	// other trap is unaffected
	ASSERT_TRUE(world.creatures[1].species.letter == 'f');
	ASSERT_TRUE(world.creatures[2].species.letter == 't');
}

// -----------
// front
// -----------

TEST(Darwin, front1) {
	DarwinWorld world(10, 10);	
	Species food('f');
	world.add_creature(food, NORTH, 0, 0);

	int x;
	int y;
	world.front(world.creatures[0], x, y);

	ASSERT_TRUE(x == -1 || y == 0);
}

TEST(Darwin, front2) {
	DarwinWorld world(10, 10);	
	Species food('f');
	world.add_creature(food, EAST, 0, 0);

	int x;
	int y;
	world.front(world.creatures[0], x, y);

	ASSERT_TRUE(x == 0 || y == 1);
}

TEST(Darwin, front3) {
	DarwinWorld world(10, 10);	
	Species food('f');
	world.add_creature(food, SOUTH, 0, 0);

	int x;
	int y;
	world.front(world.creatures[0], x, y);

	ASSERT_TRUE(x == 1 || y == 0);
}

// -----------
// next
// -----------

TEST(Darwin, next1) {
	DarwinWorld world(10, 10);	

	Species food('f');
	food.add_instruction(ACTION, HOP);

	world.add_creature(food, SOUTH, 0, 0);
	world.next(0);

	ASSERT_TRUE(world.creatures[0].x == 1);
	ASSERT_TRUE(world.creatures[0].y == 0);
}

TEST(Darwin, next2) {
	DarwinWorld world(10, 10);	

	Species food('f');
	food.add_instruction(ACTION, LEFT);

	world.add_creature(food, SOUTH, 0, 0);
	world.next(0);

	ASSERT_TRUE(world.creatures[0].direction == EAST);
}

TEST(Darwin, next3) {
	DarwinWorld world(10, 10);	

	Species food('f');
	food.add_instruction(ACTION, RIGHT);

	world.add_creature(food, SOUTH, 0, 0);
	world.next(0);

	ASSERT_TRUE(world.creatures[0].direction == WEST);
}

// -----------
// step
// -----------

TEST(Darwin, step1) {
	DarwinWorld world(10, 10);	

	Species hopper('f');

	hopper.add_instruction(ACTION, HOP);
	hopper.add_instruction(CONTROL, GO, 0);

	world.add_creature(hopper, SOUTH, 0, 0);
	world.add_creature(hopper, SOUTH, 0, 1);
	world.step();

	ASSERT_TRUE(world.creatures[0].x == 1);
	ASSERT_TRUE(world.creatures[0].y == 0);
	ASSERT_TRUE(world.creatures[1].x == 1);
	ASSERT_TRUE(world.creatures[1].y == 1);
}

TEST(Darwin, step2) {
	DarwinWorld world(10, 10);	

	Species hopper('f');

	hopper.add_instruction(ACTION, HOP);
	hopper.add_instruction(CONTROL, GO, 0);

	world.add_creature(hopper, SOUTH, 0, 0);
	world.add_creature(hopper, SOUTH, 0, 1);
	world.step();
	world.step();

	ASSERT_TRUE(world.creatures[0].x == 2);
	ASSERT_TRUE(world.creatures[0].y == 0);
	ASSERT_TRUE(world.creatures[1].x == 2);
	ASSERT_TRUE(world.creatures[1].y == 1);
}

TEST(Darwin, step3) {
	DarwinWorld world(10, 10);	

	Species hopper('f');

	hopper.add_instruction(ACTION, HOP);
	hopper.add_instruction(CONTROL, GO, 0);

	world.add_creature(hopper, SOUTH, 0, 1);
	world.add_creature(hopper, SOUTH, 0, 2);
	world.add_creature(hopper, SOUTH, 0, 3);
	world.step();
	world.step();
	world.step();

	ASSERT_TRUE(world.creatures[0].x == 3);
	ASSERT_TRUE(world.creatures[0].y == 1);
	ASSERT_TRUE(world.creatures[1].x == 3);
	ASSERT_TRUE(world.creatures[1].y == 2);
	ASSERT_TRUE(world.creatures[2].x == 3);
	ASSERT_TRUE(world.creatures[2].y == 3);
}

// -----------
// Instruction.set
// -----------

TEST(Darwin, instruction_set1) {
	Instruction i;
	i.set(CONTROL, GO, 0);	

	ASSERT_TRUE(i.type == CONTROL);
	ASSERT_TRUE(i.which == GO);
	ASSERT_TRUE(i.value == 0);
}

TEST(Darwin, instruction_set2) {
	Instruction i;
	i.set(ACTION, LEFT);	

	ASSERT_TRUE(i.type == ACTION);
	ASSERT_TRUE(i.which == LEFT);
	ASSERT_TRUE(i.value == 0);
}

TEST(Darwin, instruction_set3) {
	Instruction i;
	i.set(CONTROL, IF_WALL);

	ASSERT_TRUE(i.type == CONTROL);
	ASSERT_TRUE(i.which == IF_WALL);
	ASSERT_TRUE(i.value == 0);
}

// -----------
// Species.set_instruction
// -----------

TEST(Darwin, species_set1) {
	Species s('s');
	s.add_instruction(ACTION, LEFT);

	ASSERT_TRUE(s.instructions[0].type == ACTION);
	ASSERT_TRUE(s.instructions[0].which == LEFT);
	ASSERT_TRUE(s.instructions[0].value == 0);
	ASSERT_TRUE(s.num_instructions == 1);
}

TEST(Darwin, species_set2) {
	Species s('s');
	s.add_instruction(CONTROL, GO, 0);

	ASSERT_TRUE(s.instructions[0].type == CONTROL);
	ASSERT_TRUE(s.instructions[0].which == GO);
	ASSERT_TRUE(s.instructions[0].value == 0);
	ASSERT_TRUE(s.num_instructions == 1);
}

TEST(Darwin, species_set3) {
	Species s('s');
	s.add_instruction(CONTROL, GO, 0);
	s.add_instruction(CONTROL, GO, 2);

	ASSERT_TRUE(s.instructions[0].type == CONTROL);
	ASSERT_TRUE(s.instructions[0].which == GO);
	ASSERT_TRUE(s.instructions[0].value == 0);
	ASSERT_TRUE(s.instructions[1].type == CONTROL);
	ASSERT_TRUE(s.instructions[1].which == GO);
	ASSERT_TRUE(s.instructions[1].value == 2);
	ASSERT_TRUE(s.num_instructions == 2);
}
