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
#include <string>
#include <stdexcept> // invalid_argument, out_of_range
#include <cstdlib>   // rand, srand

#include "gtest/gtest.h"
#define private public
#include "Darwin.h"

// ----------
// Darwin
// ----------

// ----------------
// Darwin::print()
// ----------------

TEST(Darwin, darwin_print_5_by_5) {
	std::string expectedOutput = "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 .....\n\n";
	Darwin game(5, 5);
	std::stringstream buffer;
	std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
	game.print();
	std::cout.rdbuf(old);	
	ASSERT_TRUE(buffer.str() == expectedOutput);
	}
//test mod of row/column numbering
TEST(Darwin, darwin_print_12_by_12) {
	std::string expectedOutput = "Turn = 0.\n  012345678901\n0 ............\n1 ............\n2 ............\n3 ............\n4 ............\n5 ............\n";
										  expectedOutput += "6 ............\n7 ............\n8 ............\n9 ............\n0 ............\n1 ............\n\n";

	Darwin game(12, 12);
	std::stringstream buffer;
	std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
	game.print();
	std::cout.rdbuf(old);
	//std::cout << "Expected:" << std::endl << expectedOutput << std::endl << "Actual:" << std::endl << buffer.str() << std::endl << "DONE!" << std::endl;
	ASSERT_TRUE(buffer.str() == expectedOutput);
	}

TEST(Darwin, darwin_print_5_by_5_with_creature_at_3_4) {
	std::string expectedOutput = "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 ...N.\n\n";
	Species x("Name");
	Creature c(x, WEST);
	Darwin game(5, 5);
	bool result = game.addCreature(c, 4, 3);
	ASSERT_TRUE(result);
	ASSERT_TRUE(game.creatureExists(3, 4));
	std::stringstream buffer;
	std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
	game.print();
	std::cout.rdbuf(old);
	//std::cout << "Expected:" << std::endl << expectedOutput << std::endl << "Actual:" << std::endl << buffer.str() << std::endl << "DONE!" << std::endl;
	ASSERT_TRUE(buffer.str() == expectedOutput);
}

// ---------------------
// Darwin::addCreature()
// ---------------------

TEST(Darwin, darwin_add_creature) {
	Species x("Name");
	Creature c(x, WEST);
	Darwin game(5, 5);
	bool result = game.addCreature(c, 4, 3);
	ASSERT_TRUE(result);
	ASSERT_TRUE(game.creatureExists(3, 4));
}

TEST(Darwin, darwin_add_two_creatures_at_same_spot) {
	Species x("Name");
	Creature c(x, WEST);
	Darwin game(5, 5);
	bool result = game.addCreature(c, 3, 4);
	ASSERT_TRUE(result);
	ASSERT_TRUE(game.creatureExists(4, 3));
	bool result2 = game.addCreature(c, 3, 4);
	ASSERT_TRUE(!result2);
	ASSERT_TRUE(game.creatureExists(4, 3));
}

TEST(Darwin, darwin_add_creature_out_of_bounds) {
	try {
		Species x("Name");
		Creature c(x, WEST);
		Darwin game(5, 5);
		game.addCreature(c, 7, 7);
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, darwin_add_creature_out_of_bounds_2) {
	try {
		Species x("Name");
		Creature c(x, WEST);
		Darwin game(5, 5);
		game.addCreature(c, 5, 0);
		ASSERT_TRUE(false);
	} 
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, darwin_add_creature_out_of_bounds_3) {
	try {
		Species x("Name");
		Creature c(x, WEST);
		Darwin game(5, 5);
		game.addCreature(c, 0, 5);
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, darwin_add_creature_out_of_bounds_4) {
	try {
		Species x("Name");
		Creature c(x, WEST);
		Darwin game(5, 5);
		game.addCreature(c, 25);
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, create_instruction) {
	Instruction i(HOP);
	ASSERT_TRUE(i.instruction == HOP);
	ASSERT_TRUE(i.action);
}

TEST(Darwin, create_instruction_2) {
	Instruction i(IF_EMPTY, 0);
	ASSERT_TRUE(i.instruction == IF_EMPTY);
	ASSERT_TRUE(!i.action);
}

TEST(Darwin, create_instruction_3) {
	try {
		Instruction i(IF_EMPTY, -1);
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}

}

TEST(Darwin, add_instruction) {
	Instruction i(HOP);
	Species x("Name");
	x.addInstruction(i);
	ASSERT_TRUE(x.instructions.size() == 1);
	ASSERT_TRUE((x.instructions[0]) == i);
}

TEST(Darwin, add_instruction_2) {
	Instruction i(HOP);
	Instruction n(IF_EMPTY, 1);
	Species x("Name");
	x.addInstruction(i);
	x.addInstruction(n);
	ASSERT_TRUE(x.instructions.size() == 2);
	ASSERT_TRUE((x.instructions[0]) == i);
	ASSERT_TRUE((x.instructions[1]) == n);
}

TEST(Darwin, creatureExists){
    Darwin d(5, 5);
    for(int i = 0; i < 25; i++)
        ASSERT_TRUE(!d.creatureExists(i));
}

TEST(Darwin, creatureExists2){
    Species s("name");
    Creature c1(s, EAST);
    Darwin d(5, 5);
    d.addCreature(c1, 2, 2);
    ASSERT_TRUE(d.creatureExists(2, 2));
}

TEST(Darwin, creatureExists3){
    Species s("name");
    Creature c1(s, EAST);
    Darwin d(5, 5);
    d.addCreature(c1, 2, 2);
    ASSERT_TRUE(d.creatureExists(12));
}

TEST(Darwin, creatureExists4){
    Species s("name");
    Creature c1(s, EAST);
    Darwin d(5, 5);
    d.addCreature(c1, 2, 2);
    d.addCreature(c1, 2, 3);
    ASSERT_TRUE(d.creatureExists(12));
    ASSERT_TRUE(d.creatureExists(13));
}

TEST(Darwin, xyToX){
	
	Darwin d(5, 5);
	int x = 0, y = 0;
	int X = d._xyToX(x, y);
	ASSERT_TRUE(X == 0);
}

TEST(Darwin, xyToX2){
	
	Darwin d(5, 5);
	int x = 4, y = 4;
	int X = d._xyToX(x, y);
	ASSERT_TRUE(X == 24);
}

TEST(Darwin, xyToX_outOfBounds){
	
	try {
		Darwin d(5, 5);
		int x = 10, y = 0;
		int X = d._xyToX(x, y);
		X = 4;
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, XToXy){
	
	Darwin d(5, 5);
	int X = 0;
	int x, y;
	d._XToXy(X, x, y);
	ASSERT_TRUE(x == 0 && y == 0);
}

TEST(Darwin, XToXy2){
	
	Darwin d(5, 5);
	int X = 24;
	int x, y;
	d._XToXy(X, x, y);
	ASSERT_TRUE(x == 4 && y == 4);
}

TEST(Darwin, XToXy_outOfBounds){
	try {
		
		Darwin d(5, 5);
		int X = 25;
		int x, y;
		d._XToXy(X, x, y);
		ASSERT_TRUE(false);
	}
	catch (const std::invalid_argument& e) {
		ASSERT_TRUE(true);}
}

TEST(Darwin, areEnemies){
	
	Darwin d(5, 5);
	Species f = getFood();
	Species h = getHopper();
	Creature c1(f, WEST);
	Creature c2(h, WEST);
	ASSERT_TRUE(d._areEnemies(c1, c2));
}

TEST(Darwin, areEnemies2){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, WEST);
	Creature c2(f, EAST);
	ASSERT_TRUE(!d._areEnemies(c1, c2));
}

TEST(Darwin, areEnemies3){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, WEST);
	ASSERT_TRUE(!d._areEnemies(c1, c1));
}

TEST(Darwin, getCoordsInFrontOfCreature){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, WEST);
	d.addCreature(c1, 2, 2);
	int x, y;
	bool b = d._getCoordsInFrontOfCreature(c1, x, y);
	ASSERT_TRUE(x == 1 && y == 2 && b);
}

TEST(Darwin, getCoordsInFrontOfCreature2){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, EAST);
	d.addCreature(c1, 4, 4);
	int x, y;
	bool b = d._getCoordsInFrontOfCreature(c1, x, y);
	ASSERT_TRUE(x == 5 && y == 4 && !b);
}

TEST(Darwin, getCreatureInFront){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, EAST);
	Creature c2(f, WEST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	int x, y;
	Creature *c = 0;
	bool b = d._getCreatureInFront(c1, c, x, y);
	ASSERT_TRUE((*c).direction == WEST);
    ASSERT_TRUE(x == 3);
    ASSERT_TRUE(y == 2);
    ASSERT_TRUE(b);
}

TEST(Darwin, getCreatureInFront2){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, EAST);
	d.addCreature(c1, 2, 2);
	int x, y;
	Creature *c;
	bool b = d._getCreatureInFront(c1, c, x, y);
	ASSERT_TRUE(!(*c).exists);
    ASSERT_TRUE(x == 3);
    ASSERT_TRUE(y == 2);
    ASSERT_TRUE(b);
}

TEST(Darwin, getCreatureInFront_Wall){
	
	Darwin d(5, 5);
	Species f = getFood();
	Creature c1(f, EAST);
	d.addCreature(c1, 4, 4);
	int x, y;
	Creature *c;
	bool b = d._getCreatureInFront(c1, c, x, y);
	ASSERT_TRUE(!b);
}

TEST(Darwin, HOP){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, EAST);
	d.addCreature(c1, 2, 2);
	d._hop(d._grid[12]);
	ASSERT_TRUE(d.creatureExists(3, 2));
	ASSERT_TRUE(!d.creatureExists(2, 2));
}

TEST(Darwin, HOP2){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, EAST);
	d.addCreature(c1, 4, 4);
	d._hop(c1);
	ASSERT_TRUE(d.creatureExists(4, 4));
}

TEST(Darwin, HOP3){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, EAST);
	Creature c2(h, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._hop(c1);
	ASSERT_TRUE(d.creatureExists(2, 2));
	ASSERT_TRUE(d.creatureExists(3, 2));
}


TEST(Darwin, Left){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, WEST);
	d.addCreature(c1, 2, 2);
	d._left(c1);
	ASSERT_TRUE(c1.direction == SOUTH);
}

TEST(Darwin, Left2){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, SOUTH);
	d.addCreature(c1, 2, 2);
	d._left(c1);
	ASSERT_TRUE(c1.direction == EAST);
}

TEST(Darwin, right){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, SOUTH);
	d.addCreature(c1, 2, 2);
	d._right(c1);
	ASSERT_TRUE(c1.direction == WEST);
}

TEST(Darwin, right2){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Creature c1(h, WEST);
	d.addCreature(c1, 2, 2);
	d._right(c1);
	ASSERT_TRUE(c1.direction == NORTH);
}

TEST(Darwin, infect){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Species f = getFood();
	Creature c1(h, EAST);
	Creature c2(f, WEST);
	c1.programCounter = 1;
	c2.programCounter = 3;
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._infect(d._grid[12]);
	ASSERT_TRUE(d._grid[12].Cspecies == d._grid[13].Cspecies );
    ASSERT_TRUE(d._grid[13].direction == WEST);
    ASSERT_TRUE(d._grid[13].programCounter == 0);
}

TEST(Darwin, infect2){
	
	Darwin d(5, 5);
	Species h = getHopper();
	Species f = getFood();
	Creature c1(h, WEST);
	Creature c2(f, EAST);
	c1.programCounter = 1;
	c2.programCounter = 3;
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._infect(c1);
	ASSERT_TRUE(c2.Cspecies == f && c2.direction == EAST && c2.programCounter == 3);
}

TEST(Darwin, if_empty){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_EMPTY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, SOUTH);
	d.addCreature(c1, 2, 2);
	d._if_empty(c1);
	ASSERT_TRUE(c1.programCounter == 2);
}

TEST(Darwin, if_empty2){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_EMPTY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, SOUTH);
	d.addCreature(c1, 4, 4);
	d._if_empty(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, if_empty3){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_EMPTY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	Creature c2(h, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._if_empty(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, if_wall){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_WALL, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	d.addCreature(c1, 4, 4);
	d._if_wall(c1);
	ASSERT_TRUE(c1.programCounter == 2);
}

TEST(Darwin, if_wall2){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_WALL, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	d.addCreature(c1, 2, 2);
	d._if_wall(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, if_wall3){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_WALL, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	Creature c2(h, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._if_wall(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, if_enemy){
	
	Darwin d(5, 5);
	Species h("test");
	Species f = getFood();
	h.addInstruction(Instruction(IF_ENEMY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	Creature c2(f, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._if_enemy(c1);
	ASSERT_TRUE(c1.programCounter == 2);
}

TEST(Darwin, if_enemy2){
	
	Darwin d(5, 5);
	Species h("test");
	Species f = getFood();
	h.addInstruction(Instruction(IF_ENEMY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, WEST);
	Creature c2(f, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._if_enemy(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, if_enemy3){
	
	Darwin d(5, 5);
	Species h("test");
	Species f = getFood();
	h.addInstruction(Instruction(IF_ENEMY, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	Creature c2(h, EAST);
	d.addCreature(c1, 2, 2);
	d.addCreature(c2, 2, 3);
	d._if_enemy(c1);
	ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, go){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(GO, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	d.addCreature(c1, 2, 2);
	d._go(c1);
	ASSERT_TRUE(c1.programCounter == 2);
}

TEST(Darwin, if_random){
	
	Darwin d(5, 5);
	Species h("test");
	h.addInstruction(Instruction(IF_RANDOM, 2));
	h.addInstruction(Instruction(HOP));
	h.addInstruction(Instruction(HOP));
	Creature c1(h, EAST);
	d.addCreature(c1, 2, 2);
	srand(0);
	d._if_random(c1);
	srand(0);
	if(rand() % 2 == 1)
		ASSERT_TRUE(c1.programCounter == 2);
	else
		ASSERT_TRUE(c1.programCounter == 1);
}

TEST(Darwin, executeInstruction) {
    Darwin d(5, 5);
    Species h = getHopper();
    Creature c1(h, EAST);
    d.addCreature(c1, 2, 0);
    d._executeInstruction(d._grid[10]);
    ASSERT_TRUE(!d.creatureExists(10));
    ASSERT_TRUE(d.creatureExists(11));
    d._executeInstruction(d._grid[11]);
    ASSERT_TRUE(!d.creatureExists(11));
    ASSERT_TRUE(d.creatureExists(12));
}

TEST(Darwin, executeInstruction2) {
    Darwin d(5, 5);
    Species h = getFood();
    Creature c1(h, EAST);
    d.addCreature(c1, 2, 0);
    d._executeInstruction(d._grid[10]);
    ASSERT_TRUE(d._grid[10].direction == NORTH);
    d._executeInstruction(d._grid[10]);
    ASSERT_TRUE(d._grid[10].direction == WEST);
}

TEST(Darwin, executeInstruction3) {
    Darwin d(5, 5);
    srand(0);
    Species r = getRover();
    Creature c1(r, EAST);
    d.addCreature(c1, 2, 0);
    d._executeInstruction(d._grid[10]);
    ASSERT_TRUE(!d.creatureExists(10));
    ASSERT_TRUE(d.creatureExists(11));
    d._executeInstruction(d._grid[11]);
    ASSERT_TRUE(!d.creatureExists(11));
    ASSERT_TRUE(d.creatureExists(12));
    d._executeInstruction(d._grid[12]);
    ASSERT_TRUE(!d.creatureExists(12));
    ASSERT_TRUE(d.creatureExists(13));
    d._executeInstruction(d._grid[13]);
    ASSERT_TRUE(!d.creatureExists(13));
    ASSERT_TRUE(d.creatureExists(14));
    d._executeInstruction(d._grid[14]);
    srand(0);
    if(rand() % 2 == 1)
        ASSERT_TRUE(d._grid[14].direction == SOUTH);
    else
        ASSERT_TRUE(d._grid[14].direction == NORTH);
    d._executeInstruction(d._grid[14]);
    ASSERT_TRUE(!d.creatureExists(14));
}

TEST(Darwin, executeInstruction4) {
    Darwin d(5, 5);
    srand(0);
    Species r = getRover();
    Species f = getFood();
    Creature c1(r, EAST);
    Creature c2(f, NORTH);
    d.addCreature(c1, 2, 0);
    d.addCreature(c2, 2, 2);
    d._executeInstruction(d._grid[10]);
    ASSERT_TRUE(!d.creatureExists(10));
    ASSERT_TRUE(d.creatureExists(11));
    d._executeInstruction(d._grid[11]);
    ASSERT_TRUE(d.creatureExists(11));
    ASSERT_TRUE(d.creatureExists(12));
    ASSERT_TRUE(d._grid[11].Cspecies == d._grid[12].Cspecies);
    ASSERT_TRUE(d._grid[12].programCounter == 0);
}