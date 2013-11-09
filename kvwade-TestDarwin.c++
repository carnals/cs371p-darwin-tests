// --------------------------------
// projects/cs371p-darwin/TestDarwin.c++
// Copyright (C) 2013
// Nick Crum
// --------------------------------

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

#include "gtest/gtest.h"

#define private public
#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// ----
// Species::addInstruction
// ----

TEST(Species, addInstruction1) {
    Species test("Test");
    test.addInstruction(IFEMPTY,3);
    test.addInstruction(LEFT);
    test.addInstruction(GO);
    test.addInstruction(HOP);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==IFEMPTY);
    test.next(1,inst);
    ASSERT_TRUE(inst[0]==LEFT);
	test.next(2,inst);
    ASSERT_TRUE(inst[0]==GO);
	test.next(3,inst);
    ASSERT_TRUE(inst[0]==HOP);
    test.next(4,inst);
    ASSERT_TRUE(inst[0]==GO);}

TEST(Species, addInstruction2) {
    Species test("Test");
    test.addInstruction(LEFT);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==LEFT);
	test.next(1,inst);
    ASSERT_TRUE(inst[0]==GO);}

TEST(Species, addInstruction3) {
    Species test("Test");
    test.addInstruction(HOP);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==HOP);
    test.next(1,inst);
    ASSERT_TRUE(inst[0]==GO);}

// ----
// Species::equals
// ----

TEST(Species, equals1) {
	Species test("Test");
	Species test2("Test2");
	bool b = test == test2;

	ASSERT_TRUE(!b);
}

TEST(Species, equals2) {
	Species test("Test");
	Species test2("Test");
	bool b = test == test2;

	ASSERT_TRUE(b);
}

TEST(Species, equals3) {
	Species test("Test");
	Species test2("Test2");
	bool b = test != test2;

	ASSERT_TRUE(b);
}

// ----
// Species::next
// ----

TEST(Species, next1) {
    Species test("Test");
    test.addInstruction(IFEMPTY,3);
    test.addInstruction(LEFT);
    test.addInstruction(GO);
    test.addInstruction(HOP);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==IFEMPTY);
    test.next(1,inst);
    ASSERT_TRUE(inst[0]==LEFT);
	test.next(2,inst);
    ASSERT_TRUE(inst[0]==GO);
	test.next(3,inst);
    ASSERT_TRUE(inst[0]==HOP);
    test.next(4,inst);
    ASSERT_TRUE(inst[0]==GO);}

TEST(Species, next2) {
    Species test("Test");
    test.addInstruction(LEFT);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==LEFT);
	test.next(1,inst);
    ASSERT_TRUE(inst[0]==GO);}

TEST(Species, next3) {
    Species test("Test");
    test.addInstruction(HOP);
    test.addInstruction(GO);

    vector<int> inst(2,0);
    test.next(0,inst);
    ASSERT_TRUE(inst[0]==HOP);
    test.next(1,inst);
    ASSERT_TRUE(inst[0]==GO);}

// ----
// Species::printSig
// ----
TEST(Species, printSig1){
	std::ostringstream w;
	Species test("test");

    test.printSig(w);
    ASSERT_EQ("t", w.str());}

TEST(Species, printSig2){
	std::ostringstream w;
	Species test("food");
    test.printSig(w);
    ASSERT_EQ("f", w.str());}

TEST(Species, printSig3){
	std::ostringstream w;
	Species test("test");
	Species test2("food");

    test.printSig(w);
    ASSERT_EQ("t", w.str());
	test2.printSig(w);
	ASSERT_EQ("tf",w.str());}

// ----
// Darwin::addCreature
// ----
TEST(Darwin, addCreature1) {
    Darwin world(1,1);
    Species food("food");
    world.addCreature(0,0,NORTH,food);
    ASSERT_TRUE(world._creeps[0]._spec == &food);
    ASSERT_TRUE(world._creeps[0]._x == 0);
    ASSERT_TRUE(world._creeps[0]._y == 0);
    ASSERT_TRUE(world._creeps[0]._d == NORTH);
}
TEST(Darwin, addCreature2) {
    Darwin world(1,2);
    Species food("food");
    world.addCreature(0,0,NORTH,food);
    world.addCreature(0,1,NORTH,food);
    ASSERT_TRUE(world._creeps[0]._spec == &food);
    ASSERT_TRUE(world._creeps[1]._spec == &food);
}
TEST(Darwin, addCreature3) {
    Darwin world(1,2);
    Species food("food");
    Species hopper("hopper");
    world.addCreature(0,0,NORTH,food);
    world.addCreature(0,1,SOUTH,hopper);
    ASSERT_TRUE(world._creeps[0]._spec == &food);
    ASSERT_TRUE(world._creeps[1]._spec == &hopper);
}
TEST(Darwin, addCreature4) {
    Darwin world(1,1);
    Species food("food");
    Species hopper("hopper");
    world.addCreature(0,0,NORTH,food);
    world.addCreature(0,0,SOUTH,hopper);
    ASSERT_TRUE(world._creeps[0]._spec == &food);
    ASSERT_TRUE(world._creeps.size() == 1);
}

// ----
// Darwin::update
// ----
TEST(Darwin, update1) {
    Darwin world(1,2);
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == EAST);
}
TEST(Darwin, update2) {
    Darwin world(1,2);
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.addCreature(0,1,SOUTH,food);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == EAST);
    ASSERT_TRUE(world._creeps[1]._d == EAST);
}
TEST(Darwin, update3) {
    Darwin world(1,2);
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == EAST);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == NORTH);
}
TEST(Darwin, update4) {
    Darwin world(1,2);
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.addCreature(0,1,SOUTH,food);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == EAST);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == NORTH);
    ASSERT_TRUE(world._creeps[1]._d == NORTH);
}
TEST(Darwin, update5) {
    Darwin world(1,2);
    Species food("food");
    Species food2("2food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    food2.addInstruction(RIGHT);
    food2.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.addCreature(0,1,NORTH,food2);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == EAST);
    ASSERT_TRUE(world._creeps[1]._d == EAST);
    world.update();
    ASSERT_TRUE(world._creeps[0]._d == NORTH);
    ASSERT_TRUE(world._creeps[1]._d == SOUTH);   
}

// ----
// Creature::infect
// ----

TEST(Creature, infect1) {
    Darwin world(1,2);
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);
    Species infecter("infecter");
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO);
    world.addCreature(0,0,SOUTH,food);
    world.addCreature(0,1,WEST,infecter);
    world.update();
    ASSERT_TRUE(world._creeps[0]._spec == &infecter);
    ASSERT_TRUE(world._creeps[1]._spec == &infecter);
}
TEST(Creature, infect2) {
    Darwin world(1,2);
    Species infecter("infecter");
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO);
    world.addCreature(0,1,WEST,infecter);
    world.update();
    ASSERT_TRUE(world._creeps[0]._spec == &infecter);
    ASSERT_TRUE(world._creeps[0]._y == 0);
    ASSERT_TRUE(world._creeps[0]._x == 1);
    ASSERT_TRUE(world._creeps[0]._d == WEST);
}
TEST(Creature, infect3) {
    Darwin world(1,2);
    Species infecter("infecter");
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO);
    world.addCreature(0,1,WEST,infecter);
    world.addCreature(0,0,EAST,infecter);
    world.update();
    ASSERT_TRUE(world._creeps[0]._spec == &infecter);
    ASSERT_TRUE(world._creeps[0]._y == 0);
    ASSERT_TRUE(world._creeps[0]._x == 1);
    ASSERT_TRUE(world._creeps[0]._d == WEST);
    ASSERT_TRUE(world._creeps[1]._spec == &infecter);
    ASSERT_TRUE(world._creeps[1]._y == 0);
    ASSERT_TRUE(world._creeps[1]._x == 0);
    ASSERT_TRUE(world._creeps[1]._d == EAST);
}

// ----
// Creature::left
// ----

TEST(Creature, left1) {
    Creature c(0,0,NORTH,0,0);
    c.left();
    ASSERT_TRUE(c._d == WEST);
}
TEST(Creature, left2) {
    Creature c(0,0,WEST,0,0);
    c.left();
    ASSERT_TRUE(c._d == SOUTH);
}
TEST(Creature, left3) {
    Creature c(0,0,SOUTH,0,0);
    c.left();
    ASSERT_TRUE(c._d == EAST);
}

// ----
// Creature::right
// ----

TEST(Creature, right1) {
    Creature c(0,0,WEST,0,0);
    c.right();
    ASSERT_TRUE(c._d == NORTH);
}
TEST(Creature, right2) {
    Creature c(0,0,SOUTH,0,0);
    c.right();
    ASSERT_TRUE(c._d == WEST);
}
TEST(Creature, right3) {
    Creature c(0,0,NORTH,0,0);
    c.right();
    ASSERT_TRUE(c._d == EAST);
}
TEST(Creature, right4) {
    Creature c(0,0,EAST,0,0);
    c.right();
    ASSERT_TRUE(c._d == SOUTH);
}
// ----
// Creature:hop
// ----

TEST(Creature, hop1) {
    Darwin world(1,2);
    Species test("t");
    world.addCreature(0,0,EAST, test);
    world._creeps[0].hop(world._grid);
    ASSERT_TRUE(world._creeps[0]._x == 1);
    ASSERT_TRUE(world._creeps[0]._y == 0);
}
TEST(Creature, hop2) {
    Darwin world(1,2);
    Species test("t");
    world.addCreature(0,0,NORTH, test);
    world._creeps[0].hop(world._grid);
    ASSERT_TRUE(world._creeps[0]._x == 0);
    ASSERT_TRUE(world._creeps[0]._y == 0);
}
TEST(Creature, hop3) {
    Darwin world(1,2);
    Species test("t");
    world.addCreature(0,0,EAST, test);
    world.addCreature(0,1,EAST, test);
    world._creeps[0].hop(world._grid);
    ASSERT_TRUE(world._creeps[0]._x == 0);
    ASSERT_TRUE(world._creeps[0]._y == 0);
}

// ----
// Creature::ifEmpty
// ----

TEST(Creature, ifEmpty1) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    ASSERT_TRUE(world._creeps[0].ifEmpty(world._grid));
}
TEST(Creature, ifEmpty2) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    world.addCreature(0,1,EAST,test);
    ASSERT_FALSE(world._creeps[0].ifEmpty(world._grid));
}
TEST(Creature, ifEmpty3) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,NORTH,test);
    ASSERT_FALSE(world._creeps[0].ifEmpty(world._grid));
}

// ----
// Creature::ifWall
// ----

TEST(Creature, ifWall1) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    ASSERT_TRUE(!world._creeps[0].ifWall(1, 2));
}
TEST(Creature, ifWall2) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    world.addCreature(0,1,EAST,test);
    ASSERT_TRUE(!world._creeps[0].ifWall(1, 2));
}
TEST(Creature, ifWall3) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,NORTH,test);
    ASSERT_TRUE(world._creeps[0].ifWall(1, 2));
}

// ----
// Creature::ifEnemy
// ----

TEST(Creature, ifEnemy1) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    ASSERT_TRUE(!world._creeps[0].ifEnemy(world._grid, world._creeps));
}
TEST(Creature, ifEnemy2) {
    Darwin world(1, 2); 
    Species test("t");
    world.addCreature(0,0,EAST,test);
    world.addCreature(0,1,EAST,test);
    ASSERT_TRUE(!world._creeps[0].ifEnemy(world._grid, world._creeps));
}
TEST(Creature, ifEnemy3) {
    Darwin world(1, 2); 
    Species test("t");
    Species test2("2");
    world.addCreature(0,0,EAST,test);
    world.addCreature(0,1,EAST,test2);
    ASSERT_TRUE(world._creeps[0].ifEnemy(world._grid, world._creeps));
}

// ----
// Creature::ifRand
// ----
TEST(Creature, ifRand1) {
    srand(0);
    int i = rand();
    srand(0);
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c.ifRand() == (i%2));
}
TEST(Creature, ifRand2) {
    srand(0);
    rand();
    int i = rand();
    srand(0);
    rand();
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c.ifRand() == (i%2));
}

// ----
// Creature::go
// ----
TEST(Creature, go1) {
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c._pc == 0);
    c.go(0);
    ASSERT_TRUE(c._pc == 0);
}
TEST(Creature, go2) {
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c._pc == 0);
    c.go(5);
    ASSERT_TRUE(c._pc == 5);
}
TEST(Creature, go3) {
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c._pc == 0);
    c.go(10);
    ASSERT_TRUE(c._pc == 10);
}

// ----
// Creature::nextX
// ----
TEST(Creature, nextX1) {
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c.nextX() == 1);
}
TEST(Creature, nextX2) {
    Creature c(0,0,WEST,0,0);
    ASSERT_TRUE(c.nextX() == -1);
}
TEST(Creature, nextX3) {
    Creature c(0,0,NORTH,0,0);
    ASSERT_TRUE(c.nextX() == 0);
}

// ----
// Creature::nextY
// ----
TEST(Creature, nextY1) {
    Creature c(0,0,EAST,0,0);
    ASSERT_TRUE(c.nextY() == 0);
}
TEST(Creature, nextY2) {
    Creature c(0,0,NORTH,0,0);
    ASSERT_TRUE(c.nextY() == -1);
}
TEST(Creature, nextY3) {
    Creature c(0,0,SOUTH,0,0);
    ASSERT_TRUE(c.nextY() == 1);
}