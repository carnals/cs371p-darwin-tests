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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "gtest/gtest.h"

#include "Darwin.h"

// ----------
// TestDarwin
// ----------



// ---------------
// Class Direction
// ---------------

// ---------
// Direction
// ---------

TEST(Darwin, direction_west) {
    Direction dir = Direction(0);
    ASSERT_TRUE(dir.dir == 0);}

TEST(Darwin, direction_north) {
    Direction dir = Direction(1);
    ASSERT_TRUE(dir.dir == 1);}

TEST(Darwin, direction_east) {
    Direction dir = Direction(2);
    ASSERT_TRUE(dir.dir == 2);}

TEST(Darwin, direction_south) {
    Direction dir = Direction(3);
    ASSERT_TRUE(dir.dir == 3);} 

// ----------
// turn_right
// ----------

TEST(Darwin, right_west) {
    Direction dir = Direction(0);
    dir.turn_right();
    ASSERT_TRUE(dir.dir == 1);}

TEST(Darwin, right_north) {
    Direction dir = Direction(1);
    dir.turn_right();
    ASSERT_TRUE(dir.dir == 2);}

TEST(Darwin, right_east) {
    Direction dir = Direction(2);
    dir.turn_right();
    ASSERT_TRUE(dir.dir == 3);}

TEST(Darwin, right_south) {
    Direction dir = Direction(3);
    dir.turn_right();
    ASSERT_TRUE(dir.dir == 0);}

// ---------
// turn_left
// ---------

TEST(Darwin, left_west) {
    Direction dir = Direction(0);
    dir.turn_left();
    ASSERT_TRUE(dir.dir == 3);}

TEST(Darwin, left_north) {
    Direction dir = Direction(1);
    dir.turn_left();
    ASSERT_TRUE(dir.dir == 0);}

TEST(Darwin, left_east) {
    Direction dir = Direction(2);
    dir.turn_left();
    ASSERT_TRUE(dir.dir == 1);}

TEST(Darwin, left_south) {
    Direction dir = Direction(3);
    dir.turn_left();
    ASSERT_TRUE(dir.dir == 2);}

// --------------
// Class Location
// --------------



// --------
// Location
// --------

TEST(Darwin, location_west_origin) {
    Location location = Location(Direction(0), 0, 0);
    ASSERT_TRUE(location.direction == 0);
    ASSERT_TRUE(location.x == 0);
    ASSERT_TRUE(location.y == 0);}

TEST(Darwin, location_north_origin) {
    Location location = Location(Direction(1), 0, 0);
    ASSERT_TRUE(location.direction == 1);
    ASSERT_TRUE(location.x == 0);
    ASSERT_TRUE(location.y == 0);}

TEST(Darwin, location_east_origin) {
    Location location = Location(Direction(2), 0, 0);
    ASSERT_TRUE(location.direction == 2);
    ASSERT_TRUE(location.x == 0);
    ASSERT_TRUE(location.y == 0);}

TEST(Darwin, location_south_origin) {
    Location location = Location(Direction(3), 0, 0);
    ASSERT_TRUE(location.direction == 3);
    ASSERT_TRUE(location.x == 0);
    ASSERT_TRUE(location.y == 0);}

// ---------
// get_front
// ---------

TEST(Darwin, get_front_west) {
    Location location1 = Location(Direction(0), 5, 5);
    Location location2 = location1.get_front();
    ASSERT_TRUE(location2.x == 5);
    ASSERT_TRUE(location2.y == 4);	
}

TEST(Darwin, get_front_north) {
    Location location1 = Location(Direction(1), 5, 5);
    Location location2 = location1.get_front();
    ASSERT_TRUE(location2.x == 4);
    ASSERT_TRUE(location2.y == 5);
}

TEST(Darwin, get_front_east) {
    Location location1 = Location(Direction(2), 5, 5);
    Location location2 = location1.get_front();
    ASSERT_TRUE(location2.x == 5);
    ASSERT_TRUE(location2.y == 6);
}

TEST(Darwin, get_front_south) {
    Location location1 = Location(Direction(3), 5, 5);
    Location location2 = location1.get_front();
    ASSERT_TRUE(location2.x == 6);
    ASSERT_TRUE(location2.y == 5);
}

// ---------
// turn_left
// ---------

TEST(Darwin, left2_west) {
    Location location = Location(Direction(0), 0, 0);
    location.turn_left();
    ASSERT_TRUE(location.direction == 3);}

TEST(Darwin, left2_north) {
    Location location = Location(Direction(1), 0, 0);
    location.turn_left();
    ASSERT_TRUE(location.direction == 0);}

TEST(Darwin, left2_east) {
    Location location = Location(Direction(2), 0, 0);
    location.turn_left();
    ASSERT_TRUE(location.direction == 1);}

TEST(Darwin, left2_south) {
    Location location = Location(Direction(3), 0, 0);
    location.turn_left();
    ASSERT_TRUE(location.direction == 2);}

// ----------
// turn_right
// ----------

TEST(Darwin, right2_west) {
    Location location = Location(Direction(0), 0, 0);
    location.turn_right();
    ASSERT_TRUE(location.direction == 1);}

TEST(Darwin, right2_north) {
    Location location = Location(Direction(1), 0, 0);
    location.turn_right();
    ASSERT_TRUE(location.direction == 2);}

TEST(Darwin, right2_east) {
    Location location = Location(Direction(2), 0, 0);
    location.turn_right();
    ASSERT_TRUE(location.direction == 3);}

TEST(Darwin, right2_south) {
    Location location = Location(Direction(3), 0, 0);
    location.turn_right();
    ASSERT_TRUE(location.direction == 0);}

// -----------------
// Class Instruction
// -----------------



// -----------
// Instruction
// -----------

TEST(Darwin, instruction_zero) {
    Instruction instruction = Instruction(0,0);
    ASSERT_TRUE(instruction.instruction == 0);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_one) {
    Instruction instruction = Instruction(1,0);
    ASSERT_TRUE(instruction.instruction == 1);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_two) {
    Instruction instruction = Instruction(2,0);
    ASSERT_TRUE(instruction.instruction == 2);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_three) {
    Instruction instruction = Instruction(3,0);
    ASSERT_TRUE(instruction.instruction == 3);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_four) {
    Instruction instruction = Instruction(4,0);
    ASSERT_TRUE(instruction.instruction == 4);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_five) {
    Instruction instruction = Instruction(5,0);
    ASSERT_TRUE(instruction.instruction == 5);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_six) {
    Instruction instruction = Instruction(6,0);
    ASSERT_TRUE(instruction.instruction == 6);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_seven) {
    Instruction instruction = Instruction(7,0);
    ASSERT_TRUE(instruction.instruction == 7);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_eight) {
    Instruction instruction = Instruction(8,0);
    ASSERT_TRUE(instruction.instruction == 8);
    ASSERT_TRUE(instruction.argument == 0);}

TEST(Darwin, instruction_nine) {
    Instruction instruction = Instruction(9,0);
    ASSERT_TRUE(instruction.instruction == 9);
    ASSERT_TRUE(instruction.argument == 0);}

// --------------
// Class Creature
// --------------



// --------
// Creature
// --------

TEST(Darwin, creature1) {
    Creature creature1 = Creature("f", Direction(0), 0, 0);
    ASSERT_TRUE(creature1.turn_count == 0);
    ASSERT_TRUE(creature1.pc == 0);
    ASSERT_TRUE(creature1.species == "f");}

TEST(Darwin, creature2) {
    Creature creature2 = Creature("s", Direction(0), 0, 0);
    ASSERT_TRUE(creature2.turn_count == 0);
    ASSERT_TRUE(creature2.pc == 0);
    ASSERT_TRUE(creature2.species == "s");}

TEST(Darwin, creature3) {
    Creature creature3 = Creature("d", Direction(0), 0, 0);
    ASSERT_TRUE(creature3.turn_count == 0);
    ASSERT_TRUE(creature3.pc == 0);
    ASSERT_TRUE(creature3.species == "d");}

TEST(Darwin, creature4) {
    Creature creature4 = Creature("a", Direction(0), 0, 0);
    ASSERT_TRUE(creature4.turn_count == 0);
    ASSERT_TRUE(creature4.pc == 0);
    ASSERT_TRUE(creature4.species == "a");}

// ---
// hop
// ---

TEST(Darwin, hop_west) {
    Creature hop = Creature("h", Direction(0), 5, 5);
    ASSERT_TRUE(hop.location.direction == 0);
    ASSERT_TRUE(hop.location.x == 5);
    ASSERT_TRUE(hop.location.y == 5);}

TEST(Darwin, hop_north) {
    Creature hop = Creature("h", Direction(1), 5, 5);
    ASSERT_TRUE(hop.location.direction == 1);
    ASSERT_TRUE(hop.location.x == 5);
    ASSERT_TRUE(hop.location.y == 5);}


TEST(Darwin, hop_east) {
    Creature hop = Creature("h", Direction(2), 5, 5);
    ASSERT_TRUE(hop.location.direction == 2);
    ASSERT_TRUE(hop.location.x == 5);
    ASSERT_TRUE(hop.location.y == 5);}


TEST(Darwin, hop_south) {
    Creature hop = Creature("h", Direction(3), 5, 5);
    ASSERT_TRUE(hop.location.direction == 3);
    ASSERT_TRUE(hop.location.x == 5);
    ASSERT_TRUE(hop.location.y == 5);}

// ----
// left
// ----

TEST(Darwin, left3_west) {
    Creature left = Creature("f", Direction(0), 5, 5);
    ASSERT_TRUE(left.location.direction == 0);}

TEST(Darwin, left3_north) {
    Creature left = Creature("f", Direction(1), 5, 5);
    ASSERT_TRUE(left.location.direction == 1);}


TEST(Darwin, left3_east) {
    Creature left = Creature("f", Direction(2), 5, 5);
    ASSERT_TRUE(left.location.direction == 2);}

TEST(Darwin, left3_south) {
    Creature left = Creature("f", Direction(3), 5, 5);
    ASSERT_TRUE(left.location.direction == 3);}

// -----
// right
// -----

TEST(Darwin, right3_west) {
    Creature right = Creature("f", Direction(0), 5, 5);
    ASSERT_TRUE(right.location.direction == 0);}

TEST(Darwin, right3_north) {
    Creature right = Creature("f", Direction(1), 5, 5);
    ASSERT_TRUE(right.location.direction == 1);}

TEST(Darwin, right3_east) {
    Creature right = Creature("f", Direction(2), 5, 5);
    ASSERT_TRUE(right.location.direction == 2);}

TEST(Darwin, right3_south) {
    Creature right = Creature("f", Direction(3), 5, 5);
    ASSERT_TRUE(right.location.direction == 3);}

// ------
// infect
// ------
TEST(Darwin, infect_west) {
    Creature temp = Creature("f", Direction(0), 5, 5);
    Creature infectee = Creature("i", Direction(0), 5, 4);
    temp.infect(&infectee);
    ASSERT_TRUE(infectee.pc == 0);
    ASSERT_TRUE(infectee.species == "f");}

TEST(Darwin, infect_north) {
    Creature temp = Creature("f", Direction(1), 5, 5);
    Creature infectee = Creature("i", Direction(1), 4, 5);
    temp.infect(&infectee);
    ASSERT_TRUE(infectee.pc == 0);
    ASSERT_TRUE(infectee.species == "f");}

TEST(Darwin, infect_east) {
    Creature temp = Creature("f", Direction(2), 5, 5);
    Creature infectee = Creature("i", Direction(2), 5, 6);
    temp.infect(&infectee);
    ASSERT_TRUE(infectee.pc == 0);
    ASSERT_TRUE(infectee.species == "f");}

TEST(Darwin, infect_south) {
    Creature temp = Creature("f", Direction(3), 5, 5);
    Creature infectee = Creature("i", Direction(3), 6, 5);
    temp.infect(&infectee);
    ASSERT_TRUE(infectee.pc == 0);
    ASSERT_TRUE(infectee.species == "f");}

// ----------
// Class Food
// ----------

// ----
// Food
// ----

TEST(Darwin, food_west) {
    Food food = Food(Direction(0), 0, 0);
    ASSERT_TRUE(food.pc == 0);
    ASSERT_TRUE(food.species == "f");
    ASSERT_TRUE(food.turn_count == 0);}

TEST(Darwin, food_north) {
    Food food = Food(Direction(1), 0, 0);
    ASSERT_TRUE(food.pc == 0);
    ASSERT_TRUE(food.species == "f");
    ASSERT_TRUE(food.turn_count == 0);}

TEST(Darwin, food_east) {
    Food food = Food(Direction(2), 0, 0);
    ASSERT_TRUE(food.pc == 0);
    ASSERT_TRUE(food.species == "f");
    ASSERT_TRUE(food.turn_count == 0);}

TEST(Darwin, food_south) {
    Food food = Food(Direction(3), 0, 0);
    ASSERT_TRUE(food.pc == 0);
    ASSERT_TRUE(food.species == "f");
    ASSERT_TRUE(food.turn_count == 0);}

// ------------
// Class Hopper
// ------------



// ------
// Hopper
// ------
TEST(Darwin, hopper_west) {
    Hopper hopper = Hopper(Direction(0), 0, 0);
    ASSERT_TRUE(hopper.pc == 0);
    ASSERT_TRUE(hopper.species == "h");
    ASSERT_TRUE(hopper.turn_count == 0);}

TEST(Darwin, hopper_north) {
    Hopper hopper = Hopper(Direction(1), 0, 0);
    ASSERT_TRUE(hopper.pc == 0);
    ASSERT_TRUE(hopper.species == "h");
    ASSERT_TRUE(hopper.turn_count == 0);}

TEST(Darwin, hopper_east) {
    Hopper hopper = Hopper(Direction(2), 0, 0);
    ASSERT_TRUE(hopper.pc == 0);
    ASSERT_TRUE(hopper.species == "h");
    ASSERT_TRUE(hopper.turn_count == 0);}

TEST(Darwin, hopper_south) {
    Hopper hopper = Hopper(Direction(3), 0, 0);
    ASSERT_TRUE(hopper.pc == 0);
    ASSERT_TRUE(hopper.species == "h");
    ASSERT_TRUE(hopper.turn_count == 0);}


// -----------
// Class Rover
// -----------

// -----
// Rover
// -----
TEST(Darwin, rover_west) {
    Rover rover = Rover(Direction(0), 0, 0);
    ASSERT_TRUE(rover.pc == 0);
    ASSERT_TRUE(rover.species == "r");
    ASSERT_TRUE(rover.turn_count == 0);}

TEST(Darwin, rover_north) {
    Rover rover = Rover(Direction(1), 0, 0);
    ASSERT_TRUE(rover.pc == 0);
    ASSERT_TRUE(rover.species == "r");
    ASSERT_TRUE(rover.turn_count == 0);}

TEST(Darwin, rover_east) {
    Rover rover = Rover(Direction(2), 0, 0);
    ASSERT_TRUE(rover.pc == 0);
    ASSERT_TRUE(rover.species == "r");
    ASSERT_TRUE(rover.turn_count == 0);}

TEST(Darwin, rover_south) {
    Rover rover = Rover(Direction(3), 0, 0);
    ASSERT_TRUE(rover.pc == 0);
    ASSERT_TRUE(rover.species == "r");
    ASSERT_TRUE(rover.turn_count == 0);}


// ----------
// Class Trap
// ----------

// ----
// Trap
// ----
TEST(Darwin, trap_west) {
    Trap trap = Trap(Direction(0), 0, 0);
    ASSERT_TRUE(trap.pc == 0);
    ASSERT_TRUE(trap.species == "t");
    ASSERT_TRUE(trap.turn_count == 0);}

TEST(Darwin, trap_north) {
    Trap trap = Trap(Direction(1), 0, 0);
    ASSERT_TRUE(trap.pc == 0);
    ASSERT_TRUE(trap.species == "t");
    ASSERT_TRUE(trap.turn_count == 0);}

TEST(Darwin, trap_east) {
    Trap trap = Trap(Direction(2), 0, 0);
    ASSERT_TRUE(trap.pc == 0);
    ASSERT_TRUE(trap.species == "t");
    ASSERT_TRUE(trap.turn_count == 0);}

TEST(Darwin, trap_south) {
    Trap trap = Trap(Direction(3), 0, 0);
    ASSERT_TRUE(trap.pc == 0);
    ASSERT_TRUE(trap.species == "t");
    ASSERT_TRUE(trap.turn_count == 0);}


// --------------
// Class Elephant
// --------------

// --------
// Elephant
// --------
TEST(Darwin, elephant_west) {
    Elephant elephant= Elephant(Direction(0), 0, 0);
    ASSERT_TRUE(elephant.pc == 0);
    ASSERT_TRUE(elephant.species == "e");
    ASSERT_TRUE(elephant.turn_count == 0);}

TEST(Darwin, elephant_north) {
    Elephant elephant = Elephant(Direction(1), 0, 0);
    ASSERT_TRUE(elephant.pc == 0);
    ASSERT_TRUE(elephant.species == "e");
    ASSERT_TRUE(elephant.turn_count == 0);}

TEST(Darwin, elephant_east) {
    Elephant elephant = Elephant(Direction(2), 0, 0);
    ASSERT_TRUE(elephant.pc == 0);
    ASSERT_TRUE(elephant.species == "e");
    ASSERT_TRUE(elephant.turn_count == 0);}

TEST(Darwin, elephant_south) {
    Elephant elephant = Elephant(Direction(3), 0, 0);
    ASSERT_TRUE(elephant.pc == 0);
    ASSERT_TRUE(elephant.species == "e");
    ASSERT_TRUE(elephant.turn_count == 0);}


// -----------
// Class Board
// -----------

// -----
// Board
// -----

TEST(Darwin, board1) {
    Board board1 = Board(1, 1);
    ASSERT_TRUE(board1.board.size() == 1);}

TEST(Darwin, board2) {
    Board board2 = Board(5, 5);
    ASSERT_TRUE(board2.board.size() == 5);}

TEST(Darwin, board3) {
    Board board3 = Board(10, 10);
    ASSERT_TRUE(board3.board.size() == 10);}
