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
TEST(Darwin, set_direction) {
    Hopper h;
	Creature c1 (h, 0);
	c1.set_direction(0);
	ASSERT_TRUE(c1.dir_string == "north");
}

TEST(Darwin, set_direction_2) {
    Hopper h;
	Creature c1 (h, 0);
	c1.set_direction(1);
	ASSERT_TRUE(c1.dir_string == "east");
}

TEST(Darwin, set_direction_3) {
    Hopper h;
	Creature c1 (h, 0);
	c1.set_direction(3);
	ASSERT_TRUE(c1.dir_string == "west");
}


// ---------------
// Creature.equals
// ---------------

TEST(Darwin, equals) {
    Hopper h;
	Creature c1 (h, 0);
	Creature c2 (h, 2);
	ASSERT_TRUE(c1.equals(&c2));
}

TEST(Darwin, equals_1) {
    Hopper h;
    Trap t;
	Creature c1 (t, 0);
	Creature c2 (h, 2);
	ASSERT_TRUE(!c1.equals(&c2));
}

TEST(Darwin, equals_2) {
    Food f1;
    Food f;
	Creature c1 (f1, 0);
	Creature c2 (f, 2);
	ASSERT_TRUE(c1.equals(&c2));
}

//---------------
//Creature.infect
//---------------

TEST(Darwin, infect) {
	Rover r;
	Trap t;
	Creature c1 (r, 0);
	Creature c2 (t, 2);
	c1.infect(&c2);
	ASSERT_TRUE(c1.equals(&c2));
}

TEST(Darwin, infect_2) {
	Rover r;
	Hopper t;
	Creature c1 (r, 0);
	Creature c2 (t, 2);
	c1.infect(&c2);
	ASSERT_TRUE(c1.equals(&c2));
}

TEST(Darwin, infect_3) {
	Rover r;
	Food t;
	Creature c1 (r, 0);
	Creature c2 (t, 2);
	c1.infect(&c2);
	ASSERT_TRUE(c1.equals(&c2));
}

//----------
//GameBoard
//----------

TEST(Darwin, if_enemy) {
	GameBoard g (6, 6);
	Rover r;
	Creature c1 (r, 0);
	Creature c2 (r, 2);
	g.put_creature(&c1, 2, 2);
	g.put_creature(&c2, 1, 2);
	g.update_creature(&c1, 2, 2);
	g.update_creature(&c1, 2, 2);
	g.update_creature(&c1, 2, 2);
	g.update_creature(&c1, 2, 2);
	g.update_creature(&c1, 2, 2);
	ASSERT_TRUE(g.get_front_space(&c2, 1, 2)==NULL); //Should be null because c1 moved. 
													//If if_enemy returns true for c1, 
													//c1 will use up its turn trying to 
													//infect and will still be there
}

//--------------------------
//Gameboard get_front_space
//--------------------------


TEST(Darwin, gameboard_front_space) {
	GameBoard g (6, 6);
	Rover r;
	Creature c1 (r, 0);
	Creature c2 (r, 2);
	g.put_creature(&c1, 2, 1);
	g.put_creature(&c2, 3, 3);
	ASSERT_TRUE(g.get_front_space(&c2, 3, 3) == NULL);
}


TEST(Darwin, gameboard_front_space_2) {
	GameBoard g (6, 6);
	Rover r;
	Creature c1 (r, 0);
	Creature c2 (r, 3);
	g.put_creature(&c1, 0, 0);
	g.put_creature(&c2, 0, 1);
	ASSERT_TRUE(g.get_front_space(&c2, 0, 1) != NULL);
}

//--------------------------
//Gameboard put_creature
//--------------------------

TEST(Darwin, gameboard_put_creature) {
	GameBoard g (6, 6);
	Rover r;
	Creature c1 (r, 0);
	Creature c2 (r, 3);
	g.put_creature(&c1, 0, 0);
	g.put_creature(&c2, 0, 1);
	ASSERT_TRUE(g.board[0][0] == &c1);
	ASSERT_TRUE(g.board[0][1] == &c2);
}

TEST(Darwin, gameboard_put_creature_2) {
	GameBoard g (7, 7);
	Rover r;
	Creature c1 (r, 0);
	Creature c2 (r, 3);
	g.put_creature(&c1, 6, 6);
	g.put_creature(&c2, 0, 6);
	ASSERT_TRUE(g.board[6][6] == &c1);
	ASSERT_TRUE(g.board[0][6] == &c2);
}




//--------------------------
//Creature.increment_counter
//--------------------------

TEST(Darwin, increment_counter_hopper) {
	Hopper h;
	Creature c (h, 0);
	c.increment_counter();
	ASSERT_TRUE(c.pc == 1);
	c.increment_counter();
	ASSERT_TRUE(c.pc == 0);
}

TEST(Darwin, increment_counter_rover) {
	Rover r;
	Creature c (r, 0);
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	ASSERT_TRUE(c.pc == 6);
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	c.increment_counter();
	ASSERT_TRUE(c.pc == 0);
}

TEST(Darwin, increment_counter_hopper_2) {
	Hopper h;
	Creature c (h, 0);
	c.increment_counter();
	c.increment_counter();
	ASSERT_TRUE(c.pc == 0);
}


//--------------------
//Creature.turn_right
//--------------------

TEST(Darwin, turn_right) {
	Trap t;
	Creature c (t, 2);
	c.turn_right();
	ASSERT_TRUE(c.dir_string == "west");
}

TEST(Darwin, turn_right_2) {
	Trap t;
	Creature c (t, 3);
	c.turn_right();
	ASSERT_TRUE(c.dir_string == "north");
}

TEST(Darwin, turn_right_3) {
	Trap t;
	Creature c (t, 0);
	c.turn_right();
	ASSERT_TRUE(c.dir_string == "east");
}

TEST(Darwin, turn_right_4) {
	Trap t;
	Creature c (t, 1);
	c.turn_right();
	ASSERT_TRUE(c.dir_string == "south");
}
//--------------------
//Creature.turn_left
//--------------------

TEST(Darwin, turn_left) {
	Trap t;
	Creature c (t, 0);
	c.turn_left();
	ASSERT_TRUE(c.dir_string == "west");
}

TEST(Darwin, turn_left_1) {
	Trap t;
	Creature c (t, 1);
	c.turn_left();
	ASSERT_TRUE(c.dir_string == "north");
}

TEST(Darwin, turn_left_2) {
	Trap t;
	Creature c (t, 2);
	c.turn_left();
	ASSERT_TRUE(c.dir_string == "east");
}

TEST(Darwin, turn_left_3) {
	Trap t;
	Creature c (t, 3);
	c.turn_left();
	ASSERT_TRUE(c.dir_string == "south");
}

//--------------------
//Creature.next_command
//--------------------
TEST(Darwin, next_command) {
	Trap t;
	Creature c (t, 3);
	pair<string,int> test_pair = c.next_command();
	ASSERT_TRUE(test_pair.first == "if_enemy");
	ASSERT_TRUE(test_pair.second == 3);

}

TEST(Darwin, next_command_2) {
	Trap t;
	Creature c (t, 3);
	pair<string,int> test_pair = c.next_command();
	ASSERT_TRUE(test_pair.first == "if_enemy");
	ASSERT_TRUE(test_pair.second == 3);
	c.set_command(3);
	test_pair = c.next_command();
	ASSERT_TRUE(test_pair.first == "infect");
	ASSERT_TRUE(test_pair.second == -1);

}

TEST(Darwin, next_command_3) {
	Rover t;
	Creature c (t, 3);
	pair<string,int> test_pair = c.next_command();
	ASSERT_TRUE(test_pair.first == "if_enemy");
	ASSERT_TRUE(test_pair.second == 9);
	c.set_command(10);
	test_pair = c.next_command();
	ASSERT_TRUE(test_pair.first == "go");
	ASSERT_TRUE(test_pair.second == 0);

}

//--------------------
//Creature.set_command
//--------------------

TEST(Darwin, set_command) {
	Trap t;
	Creature c (t, 2);
	c.set_command(2);
	ASSERT_TRUE(c.pc == 2);
}


TEST(Darwin, set_command_2) {
	Food f;
	Creature c (f, 1);
	c.set_command(0);
	ASSERT_TRUE(c.pc == 0);
}


TEST(Darwin, set_command_3) {
	Rover t;
	Creature c (t, 2);
	c.set_command(2);
	ASSERT_TRUE(c.pc == 2);
}


TEST(Darwin, set_command_4) {
	Hopper t;
	Creature c (t, 2);
	c.set_command(1);
	ASSERT_TRUE(c.pc == 1);
}

//-------------
//Species.valid
//-------------

TEST(Darwin, valid) {
	Trap t;
	ASSERT_TRUE(t.valid(2));
}

TEST(Darwin, valid_1) {
	Rover r;
	ASSERT_TRUE(!r.valid(11));
}


TEST(Darwin, valid_2) {
	Hopper r;
	ASSERT_TRUE(!r.valid(3));
}


TEST(Darwin, valid_3) {
	Food r;
	ASSERT_TRUE(!r.valid(6));
}

//-----------------------
//Species.get_instruction
//-----------------------

TEST(Darwin, get_instruction_food) {
	Food f;
	ASSERT_TRUE(f.get_instruction(0).first == "left");
	ASSERT_TRUE(f.get_instruction(0).second == -1);
	ASSERT_TRUE(f.get_instruction(1).first == "go");
	ASSERT_TRUE(f.get_instruction(1).second == 0);
}

TEST(Darwin, get_instruction_hopper) {
	Hopper h;
	ASSERT_TRUE(h.get_instruction(0).first == "hop");
	ASSERT_TRUE(h.get_instruction(0).second == -1);
	ASSERT_TRUE(h.get_instruction(1).first == "go");
	ASSERT_TRUE(h.get_instruction(1).second == 0);
}

TEST(Darwin, get_instruction_rover) {
	Rover r;
	ASSERT_TRUE(r.get_instruction(0).first == "if_enemy");
	ASSERT_TRUE(r.get_instruction(0).second == 9);
	ASSERT_TRUE(r.get_instruction(1).first == "if_empty");
	ASSERT_TRUE(r.get_instruction(1).second == 7);
	ASSERT_TRUE(r.get_instruction(2).first == "if_random");
	ASSERT_TRUE(r.get_instruction(2).second == 5);
	ASSERT_TRUE(r.get_instruction(3).first == "left");
	ASSERT_TRUE(r.get_instruction(3).second == -1);
	ASSERT_TRUE(r.get_instruction(4).first == "go");
	ASSERT_TRUE(r.get_instruction(4).second == 0);
	ASSERT_TRUE(r.get_instruction(5).first == "right");
	ASSERT_TRUE(r.get_instruction(5).second == -1);
	ASSERT_TRUE(r.get_instruction(6).first == "go");
	ASSERT_TRUE(r.get_instruction(6).second == 0);
	ASSERT_TRUE(r.get_instruction(7).first == "hop");
	ASSERT_TRUE(r.get_instruction(7).second == -1);
	ASSERT_TRUE(r.get_instruction(8).first == "go");
	ASSERT_TRUE(r.get_instruction(8).second == 0);
	ASSERT_TRUE(r.get_instruction(9).first == "infect");
	ASSERT_TRUE(r.get_instruction(9).second == -1);
	ASSERT_TRUE(r.get_instruction(10).first == "go");
	ASSERT_TRUE(r.get_instruction(10).second == 0);	
}

TEST(Darwin, get_instruction_trap) {
	Trap t;
	ASSERT_TRUE(t.get_instruction(0).first == "if_enemy");
	ASSERT_TRUE(t.get_instruction(0).second == 3);
	ASSERT_TRUE(t.get_instruction(1).first == "left");
	ASSERT_TRUE(t.get_instruction(1).second == -1);
	ASSERT_TRUE(t.get_instruction(2).first == "go");
	ASSERT_TRUE(t.get_instruction(2).second == 0);
	ASSERT_TRUE(t.get_instruction(3).first == "infect");
	ASSERT_TRUE(t.get_instruction(3).second == -1);
	ASSERT_TRUE(t.get_instruction(4).first == "go");
	ASSERT_TRUE(t.get_instruction(4).second == 0);
}


