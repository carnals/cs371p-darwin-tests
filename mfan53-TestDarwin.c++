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

#include <iostream>
#include "gtest/gtest.h"
#include <stdexcept>

#define private public

#include "Darwin.h"
 

using namespace std;

// ----------
// TestDarwin
// ----------

// ------------
// Darwin class
// ------------

// addCreature //
TEST(Darwin, addCreature1) {
	Darwin d(8,8);
	Species Hopper("hopper");
	Creature c(Hopper,NORTH);
	d.addCreature(c,3,3);
	bool b = d.creatureAt(3,3);
	ASSERT_TRUE(b);
}

TEST(Darwin, addCreature2) {
	Darwin d(8,8);
	Species Hopper("hopper");
	Creature c(Hopper,NORTH);
	d.addCreature(c,3,3);
	bool b = d.creatureAt(4,5);
	ASSERT_FALSE(b);
}

TEST(Darwin, addCreature3) {
	Darwin d(8,8);
	Species Hopper("hopper");
	Creature c1(Hopper,NORTH);
	Creature c2(Hopper,SOUTH);
	d.addCreature(c1,3,3);
	d.addCreature(c2,6,7);
	bool b1 = d.creatureAt(3,3);
	bool b2 = d.creatureAt(1,2);
	ASSERT_TRUE(b1);
	ASSERT_FALSE(b2);
}

// outOfBounds //
TEST(Darwin, outOfBounds1) {
	Darwin d(4,4);
	bool b = d.outOfBounds(4,4);
	ASSERT_TRUE(b);
}

TEST(Darwin, outOfBounds2) {
	Darwin d(4,4);
	bool b = d.outOfBounds(2,3);
	ASSERT_FALSE(b);
}

TEST(Darwin, outOfBounds3) {
	Darwin d(4,4);
	bool b = d.outOfBounds(3,3);
	ASSERT_FALSE(b);
}

// if_empty //
TEST(Darwin, ifEmpty1) {
	Darwin d(8,8);
	Species food("Food");
	Creature c(food, WEST);
	d.addCreature(c,2,1);
	bool b = d.ifEmpty(2,1);
	ASSERT_FALSE(b);
}

TEST(Darwin, ifEmpty2) {
	Darwin d(8,8);
	Creature c;
	d.addCreature(c,2,1);
	bool b = d.ifEmpty(2,1);
	ASSERT_TRUE(b);
}

TEST(Darwin, ifEmpty3) {
	Darwin d(8,8);
	Species food("food");
	Creature c(food,EAST);
	d.addCreature(c,5,6);
	bool b = d.ifEmpty(4,3);
	ASSERT_TRUE(b);
}

// if_wall //
TEST(Darwin, ifWall1) {
	Darwin d(8,8);
	bool b = d.ifWall(4,3);
	ASSERT_FALSE(b);
}

TEST(Darwin, ifWall2) {
	Darwin d(8,8);
	bool b = d.ifWall(-1,0);
	ASSERT_TRUE(b);
}

TEST(Darwin, ifWall3) {
	Darwin d(8,8);
	bool b = d.ifWall(7,7);
	ASSERT_FALSE(b);
}

// if_enemy //
TEST(Darwin, ifEnemy1) {
	Darwin d(8,8);
	Species food("food");
	Species rover("Rover");
	Creature c1(food,EAST);
	Creature c2(rover,NORTH);
	d.addCreature(c1,4,5);
	d.addCreature(c2,4,6);
	bool b = d.ifEnemy(4,6,c1);
	ASSERT_TRUE(b);
}

TEST(Darwin, ifEnemy2) {
	Darwin d(8,8);
	Species food("food");
	Creature c1(food,EAST);
	Creature c2(food,NORTH);
	d.addCreature(c1,4,5);
	d.addCreature(c2,4,6);
	bool b = d.ifEnemy(4,6,c1);
	ASSERT_FALSE(b);
}

TEST(Darwin, ifEnemy3) {
	Darwin d(8,8);
	Species toy("toy");
	Species rover("Rover");
	Creature c1(rover,EAST);
	Creature c2(toy,NORTH);
	d.addCreature(c1,4,5);
	d.addCreature(c2,4,6);
	bool b = d.ifEnemy(4,6,c1);
	ASSERT_FALSE(b);
}

// performMove //
TEST(Darwin, move1) {
	Darwin d(8,8);
	Species trap("trap");
	Creature c1(trap,NORTH);
	Creature c2;
	d.addCreature(c1,1,0);
	d.addCreature(c2,0,0);
	d.performMove(1,0,0,0);
	bool b = d.creatureAt(0,0);
	ASSERT_TRUE(b);
}

TEST(Darwin, move2) {
	Darwin d(8,8);
	Species trap("trap");
	Creature c1(trap,NORTH);
	Creature c2;
	d.addCreature(c1,1,0);
	d.addCreature(c2,0,0);
	d.performMove(1,0,0,0);
	bool b = d.creatureAt(1,0);
	ASSERT_FALSE(b);
}

TEST(Darwin, move3) {
	Darwin d(8,8);
	Species trap("trap");
	Creature c1(trap,NORTH);
	Creature c2(trap,EAST);
	d.addCreature(c1,4,5);
	d.addCreature(c2,3,2);
	d.performMove(4,5,3,5);
	d.performMove(3,2,3,3);
	bool b1 = d.creatureAt(3,5);
	bool b2 = d.creatureAt(3,3);
	ASSERT_TRUE(b1);
	ASSERT_TRUE(b2);
}


// --------------
// Creature class
// --------------

// isBlank //
TEST(Darwin, isBlank1) {
	Darwin d(8,8);
	Creature c;
	ASSERT_TRUE(c.isBlank());
}

TEST(Darwin, isBlank2) {
	Darwin d(8,8);
	Species food("food");
	Creature c(food,EAST);
	ASSERT_FALSE(c.isBlank());
}

TEST(Darwin, isBlank3) {
	Darwin d(100,100);
	Species rover("Rover");
	Creature c(rover,NORTH);
	ASSERT_FALSE(c.isBlank());
}

// sameSpecies //
TEST(Darwin, sameSpecies1) {
	Species food("Food");
	Creature c1(food,WEST);
	Creature c2(food,EAST);
	bool b = c1.sameSpecies(c2);
	ASSERT_TRUE(b);
}

TEST(Darwin, sameSpecies2) {
	Species food("Food");
	Species rover("Rover");
	Creature c1(food,WEST);
	Creature c2(rover,EAST);
	bool b = c1.sameSpecies(c2);
	ASSERT_FALSE(b);
}

TEST(Darwin, sameSpecies3) {
	Species blank("foo");
	Species slow("slow");
	Creature c1(blank,WEST);
	Creature c2(slow,EAST);
	bool b = c1.sameSpecies(c2);
	ASSERT_TRUE(b);
}

// left //
TEST(Darwin, left1) {
	ostringstream o;
	Species food("food");
	Creature c(food,NORTH);
	c.left();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "west\n");
}

TEST(Darwin, left2) {
	ostringstream o;
	Species food("food");
	Creature c(food,WEST);
	c.left();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "south\n");
}

TEST(Darwin, left3) {
	ostringstream o;
	Species food("food");
	Creature c(food,EAST);
	c.left();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "north\n");
}

// right //
TEST(Darwin, right1) {
	ostringstream o;
	Species food("food");
	Creature c(food,NORTH);
	c.right();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "east\n");
}

TEST(Darwin, right2) {
	ostringstream o;
	Species food("food");
	Creature c(food,WEST);
	c.right();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "north\n");
}

TEST(Darwin, right3) {
	ostringstream o;
	Species food("food");
	Creature c(food,SOUTH);
	c.right();
	c.printDirection(o);
	ASSERT_TRUE(o.str() == "west\n");
}

// hop //
TEST(Darwin, hop1) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c(test,EAST,d);
	d.addCreature(c,0,0);
	c.hop(0,0);
	bool b = d.creatureAt(0,1);
	ASSERT_TRUE(b);
}

TEST(Darwin, hop2) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c(test,EAST,d);
	d.addCreature(c,0,7);
	c.hop(0,7);
	bool b = d.creatureAt(0,7);
	ASSERT_TRUE(b);
}

TEST(Darwin, hop3) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c1(test,WEST,d);
	Creature c2(test,EAST,d);
	d.addCreature(c1,3,2);
	d.addCreature(c2,3,3);
	c1.hop(3,2);
	bool b = d.creatureAt(3,3);
	ASSERT_TRUE(b);
}

// go //
TEST(Darwin, go1) {
	Species test("trap");
	Creature c(test,NORTH);
	int pcB = c.program_counter;
	c.go(1);
	int pcA = c.program_counter;
	ASSERT_TRUE(pcB == 0);
	ASSERT_TRUE(pcA == 1);
}

TEST(Darwin, go2) {
	Species test("trap");
	Creature c(test,NORTH);
	int pcB = c.program_counter;
	c.go(5);
	int pcA = c.program_counter;
	ASSERT_TRUE(pcB == 0);
	ASSERT_TRUE(pcA == 5);
}

TEST(Darwin, go3) {
	Species test("trap");
	Creature c(test,NORTH);
	try {
		c.go(-1);
	}
	catch(const out_of_range&) {
		ASSERT_TRUE(true);
	}
}

// if_empty //
TEST(Darwin, empty1) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c(test,EAST,d);
	d.addCreature(c,0,0);
	c.if_empty(8,0,0);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 8);
}

TEST(Darwin, empty2) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c1(test,EAST,d);
	Creature c2(test,NORTH,d);
	d.addCreature(c1,0,0);
	d.addCreature(c2,0,1);
	c1.if_empty(8,0,0);
	int pc = c1.program_counter;
	ASSERT_TRUE(pc == 1);
}

TEST(Darwin, empty3) {
	Darwin d(8,8);
	Species test("hopper");
	Creature c(test,NORTH,d);
	d.addCreature(c,0,0);
	c.if_empty(8,0,0);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1);
}

// if_wall //
TEST(Darwin, wall1) {
	Darwin d(8,8);
	Species test("food");
	Creature c(test,NORTH,d);
	d.addCreature(c,0,0);
	c.if_wall(6,0,0);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 6);
}

TEST(Darwin, wall2) {
	Darwin d(8,8);
	Species test("food");
	Creature c(test,NORTH,d);
	d.addCreature(c,3,0);
	c.if_wall(6,3,0);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1);
}

TEST(Darwin, wall3) {
	Darwin d(8,8);
	Species test("food");
	Creature c(test,EAST,d);
	d.addCreature(c,4,3);
	c.if_wall(6,4,3);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1);
}

// if_random //
TEST(Darwin, random1) {
	Species test("rover");
	Creature c(test,SOUTH);
	c.if_random(6);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1 || pc == 6);
}

TEST(Darwin, random2) {
	Species test("rover");
	Creature c(test,SOUTH);
	c.if_random(0);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1 || pc == 0);
}
TEST(Darwin, random3) {
	Species test("rover");
	Creature c(test,SOUTH);
	c.if_random(1);
	int pc = c.program_counter;
	ASSERT_TRUE(pc == 1 || pc == 2);
}

// if_enemy //
TEST(Darwin, enemy1) {
	Darwin d(8,8);
	Species food("food");
	Species rover("rover");
	Creature c1(food,NORTH,d);
	Creature c2(rover,WEST,d);
	d.addCreature(c1,4,3);
	d.addCreature(c2,3,3);
	c1.if_enemy(5,4,3);
	int pc = c1.program_counter;
	ASSERT_TRUE(pc == 5);
}

TEST(Darwin, enemy2) {
	Darwin d(8,8);
	Species food("food");
	Creature c1(food,NORTH,d);
	Creature c2(food,WEST,d);
	d.addCreature(c1,4,3);
	d.addCreature(c2,3,3);
	c1.if_enemy(5,4,3);
	int pc = c1.program_counter;
	ASSERT_TRUE(pc == 1);
}

TEST(Darwin, enemy3) {
	Darwin d(8,8);
	Species food("food");
	Creature c1(food,NORTH,d);
	d.addCreature(c1,4,3);
	c1.if_enemy(5,4,3);
	int pc = c1.program_counter;
	ASSERT_TRUE(pc == 1);
}

// infect //
TEST(Darwin, infect1) {
	Darwin d(8,8);
	Species food("food");
	Species rover("rover");
	Creature c1(food,EAST,d);
	Creature c2(rover,WEST,d);
	d.addCreature(c1,0,0);
	d.addCreature(c2,0,1);
	c1.infect(0,0);
	bool b = d.ifEnemy(0,0,c1);
	int pc = c2.program_counter;
	ASSERT_FALSE(b);
	ASSERT_TRUE(pc == 0);
}

TEST(Darwin, infect2) {
	Darwin d(8,8);
	Species food("food");
	Creature c1(food,EAST,d);
	Creature c2(food,WEST,d);
	d.addCreature(c1,0,0);
	d.addCreature(c2,0,1);
	c1.infect(0,0);
	bool b = d.ifEnemy(0,0,c1);
	ASSERT_FALSE(b);
}

//try to infect a blank spot
TEST(Darwin, infect3) {
	Darwin d(8,8);
	Species food("food");
	Creature c1(food,EAST,d);
	Creature c2;
	d.addCreature(c1,0,0);
	d.addCreature(c2,0,1);
	c1.infect(0,0);
	bool b = d.ifEnemy(0,0,c1);
	ASSERT_FALSE(b);
}


// -------------
// Species class
// -------------

// addInstruction //
TEST(Darwin, addI1) {
	ostringstream o;
	Species Food("food");
	Food.addInstruction(LEFT, -1);
    Food.printList(o);
    ASSERT_TRUE(o.str() == "left\n");
}

TEST(Darwin, addI2) {
	ostringstream o;
	Species Food("food");
	Food.addInstruction(LEFT);
	Food.addInstruction(GO,0);
    Food.printList(o);
    ASSERT_TRUE(o.str() == "left\ngo 0\n");
}

TEST(Darwin, addI3) {
	ostringstream o;
	Species test("trap");
	test.addInstruction(LEFT);
	test.addInstruction(RIGHT);
	test.addInstruction(HOP);
	test.addInstruction(IF_EMPTY, 6);
    test.printList(o);
    ASSERT_TRUE(o.str() == "left\nright\nhop\nif empty 6\n");
}

// getInstruction //
TEST(Darwin, getInstruction1) {
	Species test("food");
	test.addInstruction(LEFT);
	pair<instruction,int> p = test.getInstruction(0);
	ASSERT_TRUE(p.first == LEFT);
	ASSERT_TRUE(p.second == -1);
}

TEST(Darwin, getInstruction2) {
	Species test("food");
	test.addInstruction(LEFT);
	test.addInstruction(GO,0);
	pair<instruction,int> p1 = test.getInstruction(0);
	pair<instruction,int> p2 = test.getInstruction(1);
	ASSERT_TRUE(p1.first == LEFT);
	ASSERT_TRUE(p2.first == GO);
	ASSERT_TRUE(p1.second == -1);
	ASSERT_TRUE(p2.second == 0);
}

TEST(Darwin, getInstruction3) {
	Species test("food");
	test.addInstruction(LEFT);
	try {
		pair<instruction,int> p = test.getInstruction(-1);
	}
	catch(const out_of_range&) {
		ASSERT_TRUE(true);
	}
}
