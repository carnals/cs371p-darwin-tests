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



#define private public
#define protected public
#include "Darwin.h"

using namespace std;

TEST(Species, constructor_1) {
	Species h("hopper");
	ASSERT_TRUE(h.getSpecies() == "hopper");
}

TEST(Species, constructor_2) {
	Species h("food");
	ASSERT_TRUE(h.getSpecies() == "food");
}

TEST(Species, constructor_3) {
	Species h("rover");
	ASSERT_TRUE(h.getSpecies() == "rover");
}

TEST(Species, addInstruction_1) {
	Species h("hopper");
	h.addInstruction("left");
	ASSERT_TRUE(h.getInstr(0) == "left");
}

TEST(Species, addInstruction_2) {
	Species h("hopper");
	h.addInstruction("right");
	ASSERT_TRUE(h.getInstr(0) == "right");
}

TEST(Species, addInstruction_3) {
	Species h("hopper");
	h.addInstruction("go 0");
	ASSERT_TRUE(h.getInstr(0) == "go 0");
}

TEST(Species, getSpecies_1) {
	Species h("hopper");
	ASSERT_TRUE(h.getSpecies() == "hopper");
}

TEST(Species, getSpecies_2) {
	Species h("food");
	ASSERT_TRUE(h.getSpecies() == "food");
}

TEST(Species, getSpecies_3) {
	Species h("rover");
	ASSERT_TRUE(h.getSpecies() == "rover");
}

TEST(Species, getInstr_1) {
	Species h("hopper");
	h.addInstruction("left");
	ASSERT_TRUE(h.getInstr(0) == "left");
}

TEST(Species, getInstr_2) {
	Species h("hopper");
	h.addInstruction("right");
	ASSERT_TRUE(h.getInstr(0) == "right");
}

TEST(Species, getInstr_3) {
	Species h("hopper");
	h.addInstruction("go 0");
	ASSERT_TRUE(h.getInstr(0) == "go 0");
}

TEST(Creature, constructor_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getSpeciesString() == "hopper");
}

TEST(Creature, constructor_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getFace() == 0);
}

TEST(Creature, constructor_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getX() == 1);
}

TEST(Creature, getSpeciesString_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getSpeciesString() == "hopper");
}

TEST(Creature, getSpeciesString_2) {
	Species h("rover");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getSpeciesString() == "rover");
}

TEST(Creature, getSpeciesString_3) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getSpeciesString() == "food");
}

TEST(Creature, getSpecies_1) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	Species g = c.getSpecies();
	ASSERT_TRUE(g.getSpecies() == "food");
}

TEST(Creature, getSpecies_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	Species g = c.getSpecies();
	ASSERT_TRUE(g.getSpecies() == "hopper");
}

TEST(Creature, getSpecies_3) {
	Species h("rover");
	Creature c (&h, 0, 1, 1);
	Species g = c.getSpecies();
	ASSERT_TRUE(g.getSpecies() == "rover");
}

TEST(Creature, getSpeciesPointer_1) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	Species* g = c.getSpeciesPointer();
	ASSERT_TRUE(g == &h);
}

TEST(Creature, getSpeciesPointer_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	Species* g = c.getSpeciesPointer();
	ASSERT_TRUE(g == &h);
}

TEST(Creature, getSpeciesPointer_3) {
	Species h("rover");
	Creature c (&h, 0, 1, 1);
	Species* g = c.getSpeciesPointer();
	ASSERT_TRUE(g == &h);
}

TEST(Creature, setSpecies_1) {
	Species f("food");
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setSpecies(&f);
	ASSERT_TRUE(c.getSpeciesString() == "food");
}

TEST(Creature, setSpecies_2) {
	Species f("rover");
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setSpecies(&f);
	ASSERT_TRUE(c.getSpeciesString() == "rover");
}

TEST(Creature, setSpecies_3) {
	Species f("trap");
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setSpecies(&f);
	ASSERT_TRUE(c.getSpeciesString() == "trap");
}

TEST(Creature, getFace_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getFace() == 0);
}

TEST(Creature, getFace_2) {
	Species h("hopper");
	Creature c (&h, 1, 1, 1);
	ASSERT_TRUE(c.getFace() == 1);
}

TEST(Creature, getFace_3) {
	Species h("hopper");
	Creature c (&h, 2, 1, 1);
	ASSERT_TRUE(c.getFace() == 2);
}

TEST(Creature, setFace_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setFace(1);
	ASSERT_TRUE(c.getFace() == 1);
}

TEST(Creature, setFace_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setFace(2);
	ASSERT_TRUE(c.getFace() == 2);
}

TEST(Creature, setFace_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setFace(3);
	ASSERT_TRUE(c.getFace() == 3);
}

TEST(Creature, getX_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getX() == 1);
}

TEST(Creature, getX_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 2);
	ASSERT_TRUE(c.getX() == 2);
}

TEST(Creature, getX_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 3);
	ASSERT_TRUE(c.getX() == 3);
}

TEST(Creature, getY_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getX() == 1);
}

TEST(Creature, getY_2) {
	Species h("hopper");
	Creature c (&h, 0, 2, 2);
	ASSERT_TRUE(c.getX() == 2);
}

TEST(Creature, getY_3) {
	Species h("hopper");
	Creature c (&h, 0, 3, 3);
	ASSERT_TRUE(c.getX() == 3);
}

TEST(Creature, setX_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setX(2);
	ASSERT_TRUE(c.getX() == 2);
}

TEST(Creature, setX_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setX(3);
	ASSERT_TRUE(c.getX() == 3);
}

TEST(Creature, setX_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setX(0);
	ASSERT_TRUE(c.getX() == 0);
}

TEST(Creature, setY_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setY(2);
	ASSERT_TRUE(c.getY() == 2);
}

TEST(Creature, setY_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setY(3);
	ASSERT_TRUE(c.getY() == 3);
}

TEST(Creature, setY_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setY(0);
	ASSERT_TRUE(c.getY() == 0);
}

TEST(Creature, getPc_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getPc() == 0);
}

TEST(Creature, getPc_2) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getPc() == 0);
}

TEST(Creature, getPc_3) {
	Species h("trap");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getPc() == 0);
}

TEST(Creature, setPc_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setPc(2);
	ASSERT_TRUE(c.getPc() == 2);
}

TEST(Creature, setPc_2) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setPc(3);
	ASSERT_TRUE(c.getPc() == 3);
}

TEST(Creature, setPc_3) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setPc(4);
	ASSERT_TRUE(c.getPc() == 4);
}

TEST(Creature, getMoved_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getMoved() == 0);
}

TEST(Creature, getMoved_2) {
	Species h("rover");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getMoved() == 0);
}

TEST(Creature, getMoved_3) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	ASSERT_TRUE(c.getMoved() == 0);
}

TEST(Creature, setMoved_1) {
	Species h("hopper");
	Creature c (&h, 0, 1, 1);
	c.setMoved(true);
	ASSERT_TRUE(c.getMoved() == 1);
}

TEST(Creature, setMoved_2) {
	Species h("rover");
	Creature c (&h, 0, 1, 1);
	c.setMoved(true);
	ASSERT_TRUE(c.getMoved() == 1);
}

TEST(Creature, setMoved_3) {
	Species h("food");
	Creature c (&h, 0, 1, 1);
	c.setMoved(true);
	ASSERT_TRUE(c.getMoved() == 1);
}

TEST(Darwin, constructor_1) {
	Darwin d(1, 1);
	ASSERT_TRUE(d.getX() == 1);
}

TEST(Darwin, constructor_2) {
	Darwin d(1, 2);
	ASSERT_TRUE(d.getX() == 2);
}

TEST(Darwin, constructor_3) {
	Darwin d(1, 3);
	ASSERT_TRUE(d.getX() == 3);
}

TEST(Darwin, printBoard_1) {
	Darwin d(1, 1);
	ASSERT_TRUE(d.getX() == 1);
}

TEST(Darwin, printBoard_2) {
	Darwin d(1, 2);
	ASSERT_TRUE(d.getX() == 2);
}

TEST(Darwin, printBoard_3) {
	Darwin d(1, 3);
	ASSERT_TRUE(d.getX() == 3);
}

TEST(Darwin, addCreature_1) {
	Species h("hopper");
	Darwin d(3, 3);
	Creature c(&h, 0, 0, 0);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(0, 0) == 'h');
}

TEST(Darwin, addCreature_2) {
	Species h("trap");
	Darwin d(3, 3);
	Creature c(&h, 0, 1, 1);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(1, 1) == 't');
}

TEST(Darwin, addCreature_3) {
	Species h("rover");
	Darwin d(3, 3);
	Creature c(&h, 0, 2, 2);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(2, 2) == 'r');
}

TEST(Darwin, go_1) {
	Species h("hopper");
	h.addInstruction("hop");
	Darwin d(3, 3);
	Creature c(&h, 1, 0, 0);
	d.addCreature(&c);
	d.go();
	ASSERT_TRUE(d.getCreature(0, 1) == 'h');
}

TEST(Darwin, go_2) {
	Species h("hopper");
	h.addInstruction("hop");
	Darwin d(3, 3);
	Creature c(&h, 1, 2, 0);
	d.addCreature(&c);
	d.go();
	ASSERT_TRUE(d.getCreature(2, 1) == 'h');
}

TEST(Darwin, go_3) {
	Species h("hopper");
	h.addInstruction("hop");
	Darwin d(3, 3);
	Creature c(&h, 2, 0, 0);
	d.addCreature(&c);
	d.go();
	ASSERT_TRUE(d.getCreature(1, 0) == 'h');
}

TEST(Darwin, getX_1) {
	Darwin d(3, 3);
	ASSERT_TRUE(d.getX() == 3);
}

TEST(Darwin, getX_2) {
	Darwin d(3, 4);
	ASSERT_TRUE(d.getX() == 4);
}

TEST(Darwin, getX_3) {
	Darwin d(3, 1);
	ASSERT_TRUE(d.getX() == 1);
}

TEST(Darwin, getY_1) {
	Darwin d(3, 3);
	ASSERT_TRUE(d.getY() == 3);
}

TEST(Darwin, getY_2) {
	Darwin d(2, 4);
	ASSERT_TRUE(d.getY() == 2);
}

TEST(Darwin, getY_3) {
	Darwin d(4, 1);
	ASSERT_TRUE(d.getY() == 4);
}

TEST(Darwin, getCreature_1) {
	Species h("hopper");
	Darwin d(3, 3);
	Creature c(&h, 0, 0, 0);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(0, 0) == 'h');
}

TEST(Darwin, getCreature_2) {
	Species h("trap");
	Darwin d(3, 3);
	Creature c(&h, 0, 1, 1);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(1, 1) == 't');
}

TEST(Darwin, getCreature_3) {
	Species h("rover");
	Darwin d(3, 3);
	Creature c(&h, 0, 2, 2);
	d.addCreature(&c);
	ASSERT_TRUE(d.getCreature(2, 2) == 'r');
}

TEST(Darwin, fi_1) {
	Darwin d(3, 3);
	int i = d.fi(2);
	ASSERT_TRUE(i == 1);
}

TEST(Darwin, fi_2) {
	Darwin d(3, 3);
	int i = d.fi(1);
	ASSERT_TRUE(i == 0);
}

TEST(Darwin, fi_3) {
	Darwin d(3, 3);
	int i = d.fi(0);
	ASSERT_TRUE(i == 3);
}

