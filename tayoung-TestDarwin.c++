// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2013
// Tyler A. Young
// ------------------------------

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

    % g++ -pedantic -std=c++0x -Wall TestAllocator.c++ -o TestAllocator -lgtest -lpthread -lgtest_main

    % valgrind TestAllocator > TestAllocator.out
*/

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string>

#define private public
#define protected public
#define class struct

#include "Darwin.h"

// --------
// typedefs
// --------
//typedef std::vector< std::vector<Creature*> > Board;

// ------------------------------------------------------------------------- //
//                                  DARWIN                                   //
// ------------------------------------------------------------------------- //

// ------------
// Constructors
// ------------
TEST(TestDarwin,construct1){
	using namespace std;
	Darwin game(3,3);
	ASSERT_TRUE(game.gameboard.size() == 3);
	ASSERT_TRUE(game.gameboard[0].size() == 3);
}
TEST(TestDarwin,construct2){
	using namespace std;
	Darwin game(5,5);
	ASSERT_TRUE(game.gameboard.size() == 5);
	ASSERT_TRUE(game.gameboard[0].size() == 5);
}

// ------------
// add_creature
// ------------
TEST(TestDarwin,add_creature1){
	using namespace std;
	Darwin game(5,5);
	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	game.add_creature(spider_s, 1,1, West);
	game.add_creature(spider_s, 1,4, North);

	ASSERT_NE(game.gameboard[1][1], game.gameboard[1][4]);
}

// ------------------------------------------------------------------------- //
//                                 CREATURE                                  //
// ------------------------------------------------------------------------- //

// ------------
// Constructors
// ------------
TEST(TestCreature,construct1){
	using namespace std;
	Darwin game(5,5);
	Creature spider;
	ASSERT_TRUE((spider.pos.x == -1) && (spider.pos.y == -1));
}
TEST(TestCreature,construct2){
	using namespace std;
	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 1,2, South);

	ASSERT_TRUE(spider.species->name == "SPIDER");
	ASSERT_TRUE(spider.gameboard != NULL);
}
TEST(TestCreature,construct3){
	using namespace std;
	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, South);
	ASSERT_TRUE(*game.gameboard[3][4] == spider);
}

// ---------------
// Copy assignment
// ---------------
TEST(TestCreature,copyassign1){
	using namespace std;
	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, South);
	Creature thing = spider;
	ASSERT_TRUE(thing.species == spider.species);
}
TEST(TestCreature,copyassign2){
	using namespace std;
	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 1,2, South);
	Creature thing = spider;
	ASSERT_TRUE(thing.species->program == spider.species->program);
}
TEST(TestCreature,copyassign3){
	using namespace std;
	Creature spider;
	Creature thing = spider;
	ASSERT_TRUE(thing == spider);
}

// ---
// Hop
// ---
TEST(TestCreature,hop1){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.hop();

	ASSERT_EQ(game.gameboard[3][4], &spider);
}
TEST(TestCreature,hop2){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	Creature spider(&game.gameboard, spider_s, 3,3, East);


	spider.hop();

	ASSERT_NE(game.gameboard[3][3], &spider);
	ASSERT_EQ(game.gameboard[3][4], &spider);
}
TEST(TestCreature,hop3){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	Creature spider(&game.gameboard, spider_s, 3,3, South);

	spider.hop();

	ASSERT_NE(game.gameboard[3][3], &spider);
	ASSERT_EQ(game.gameboard[4][3], &spider);
}
TEST(TestCreature,hop4){
	using namespace std;

	Darwin game(5,9);

	Species spider_s("SPIDER");

	Creature spider(&game.gameboard, spider_s, 3,3, West);

	spider.hop();

	ASSERT_NE(game.gameboard[3][3], &spider);
	ASSERT_EQ(game.gameboard[3][2], &spider);
}
TEST(TestCreature,hop5){
	using namespace std;

	Darwin game(5,9);
	vector<string> spider_i = {"left","go 0"};

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");
	Creature spider(&game.gameboard, spider_s, 3,3, North);

	spider.hop();

	ASSERT_NE(game.gameboard[3][3], &spider);
	ASSERT_EQ(game.gameboard[2][3], &spider);
}
TEST(TestCreature,hop6){
	using namespace std;

	Darwin game(5,9);
	vector<string> spider_i = {"left","go 0"};

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");
	Creature spider(&game.gameboard, spider_s, 0,0, North);

	spider.hop();

	ASSERT_EQ(game.gameboard[0][0], &spider);
}
TEST(TestCreature,hop7){
	using namespace std;

	Darwin game(5,9);
	vector<string> spider_i = {"left","go 0"};

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");
	Creature spider(&game.gameboard, spider_s, 2,0, West);

	spider.hop();

	ASSERT_EQ(game.gameboard[2][0], &spider);
}
TEST(TestCreature,hop8){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");
	Creature spider(&game.gameboard, spider_s, 4,3, South);

	spider.hop();

	ASSERT_EQ(game.gameboard[4][3], &spider);
}

// ----
// Left
// ----
TEST(TestCreature,left1){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.left();

	ASSERT_TRUE(spider.direction == North);
}
TEST(TestCreature,left2){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.left();
	spider.left();

	ASSERT_TRUE(spider.direction == West);
}
TEST(TestCreature,left3){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.left();
	spider.left();
	spider.left();

	ASSERT_TRUE(spider.direction == South);
}
TEST(TestCreature,left4){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.left();
	spider.left();
	spider.left();
	spider.left();

	ASSERT_TRUE(spider.direction == East);
}

// -----
// Right
// -----
TEST(TestCreature,right1){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.right();

	ASSERT_TRUE(spider.direction == South);
}
TEST(TestCreature,right2){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.right();
	spider.right();

	ASSERT_TRUE(spider.direction == West);
}
TEST(TestCreature,right3){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.right();
	spider.right();
	spider.right();

	ASSERT_TRUE(spider.direction == North);
}
TEST(TestCreature,right4){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("left");

	Creature spider(&game.gameboard, spider_s, 3,4, East);

	spider.right();
	spider.right();
	spider.right();
	spider.right();

	ASSERT_TRUE(spider.direction == East);
}

// ------
// Infect
// ------
TEST(TestCreature,infect1){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("if_random 3");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_enemy 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");

	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, South);
	Creature food(&game.gameboard, food_s, 3,3, East);

	spider.infect();

	ASSERT_TRUE(*game.gameboard[3][3] == *game.gameboard[2][3]);
}
TEST(TestCreature,infect2){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("if_random 3");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_enemy 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");

	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, West);
	Creature food(&game.gameboard, food_s, 2,2, East);

	spider.infect();

	ASSERT_TRUE(*game.gameboard[2][2] == *game.gameboard[2][3]);
}
TEST(TestCreature,infect3){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("if_random 3");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_enemy 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");

	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, North);
	Creature food(&game.gameboard, food_s, 1,3, East);

	spider.infect();

	ASSERT_TRUE(*game.gameboard[1][3] == *game.gameboard[2][3]);
}
TEST(TestCreature,infect4){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("if_random 3");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_enemy 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");

	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, East);
	Creature food(&game.gameboard, food_s, 2,4, East);

	spider.infect();

	ASSERT_TRUE(*game.gameboard[2][4] == *game.gameboard[2][3]);
}

// --------
// if_empty
// --------
TEST(TestCreature,if_empty1){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_empty 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("hop");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 2);
}
TEST(TestCreature,if_empty2){
	using namespace std;

	Darwin game(5,5);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_empty 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("hop");
	spider_s.add_instruction("go 0");
	Species food_s("food");

	Creature spider(&game.gameboard, spider_s, 2,3, East);
	Creature food(&game.gameboard, food_s, 2,4, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc,1);
}

// --------
// if_enemy
// --------
TEST(TestCreature,if_enemy1){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_enemy 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 1);
}
TEST(TestCreature,if_enemy2){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_enemy 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");
	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, North);
	Creature food(&game.gameboard, food_s, 1,3, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 2);
}
TEST(TestCreature,if_enemy3){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_enemy 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");
	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 1,1, East);
	Creature food(&game.gameboard, food_s, 1,2, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 2);
}
TEST(TestCreature,if_enemy4){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_enemy 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");
	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 1,1, South);
	Creature food(&game.gameboard, food_s, 2,1, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 2);
}
TEST(TestCreature,if_enemy5){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_enemy 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("go 0");
	Species food_s("food");
	food_s.add_instruction("left");
	food_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 1,1, West);
	Creature food(&game.gameboard, food_s, 1,0, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_EQ(spider.pc, 2);
}

// --------
// if_wall
// --------
TEST(TestCreature,if_wall1){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("right");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,3, East);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 2);
}
TEST(TestCreature,if_wall2){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("right");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 0,3, North);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 2);
}
TEST(TestCreature,if_wall3){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("right");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 2,0, West);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 2);
}
TEST(TestCreature,if_wall4){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("left");
	spider_s.add_instruction("right");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 3,2, South);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 2);
}

// --------
// go
// --------
TEST(TestCreature,go1){
	using namespace std;

	Darwin game(4,4);

	Species spider_s("SPIDER");
	spider_s.add_instruction("go 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("hop");
	spider_s.add_instruction("right");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_empty 2");
	spider_s.add_instruction("if_wall 2");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 3,2, South);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 5);
}

// -----------
// reset_board
// -----------
TEST(TestCreature,execute_instruction1){
	using namespace std;

	Darwin game(6,6);

	Species spider_s("SPIDER");
	spider_s.add_instruction("go 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("hop");
	spider_s.add_instruction("right");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_empty 2");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 3,2, South);

	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 5);
}
TEST(TestCreature,execute_instruction2){
	using namespace std;

	Darwin game(6,6);

	Species spider_s("SPIDER");
	spider_s.add_instruction("go 5");
	spider_s.add_instruction("left");
	spider_s.add_instruction("hop");
	spider_s.add_instruction("right");
	spider_s.add_instruction("infect");
	spider_s.add_instruction("left");
	spider_s.add_instruction("if_empty 2");
	spider_s.add_instruction("go 0");

	Creature spider(&game.gameboard, spider_s, 3,2, South);

	spider.execute_instruction(spider.species->program[spider.pc]);
	spider.execute_instruction(spider.species->program[spider.pc]);

	ASSERT_TRUE(spider.pc == 6);
}

// TINY TEST HARNESS
//int main()
//{
//	using namespace std;
//	Darwin game(7,8);
//	vector<string> spider_i = {"left","go 0"};
//	Creature spider(game.gameboard, "SPIDER",3,4, spider_i);
//	Creature thing = spider;
//	cout << spider.species << endl;
//	cout << thing.species << endl;
//	cout << (*spider.gameboard)[3][4]->species << endl;
//	cout << game.gameboard[3][4]->species << endl;
//	assert(thing == spider);
//	assert(*game.gameboard[3][4] == spider);
//}
