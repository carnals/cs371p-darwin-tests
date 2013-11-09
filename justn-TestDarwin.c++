// Compile with g++ -pedantic -std=c++0x -Wall TestDarwin.c++ -o TestDarwin

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <stdexcept>

#include "gtest/gtest.h"
#define private public
#include "Darwin.h"

TEST(Darwin, simple1) {
	Darwin d(2, 3);

	assert(d._row == 2);
	assert(d._col == 3);
	assert(d._grid.size() == 2);
	assert(d._grid[0].size() == 3);
}

TEST(Darwin, simple2) {
	Darwin d(20, 1);

	assert(d._row == 20);
	assert(d._col == 1);
	assert(d._grid.size() == 20);
	assert(d._grid[0].size() == 1);
}

TEST(Darwin, simple3) {
	Darwin d(789, 992);

	assert(d._row == 789);
	assert(d._col == 992);
	assert(d._grid.size() == 789);
	assert(d._grid[0].size() == 992);
}

TEST(Darwin, species1) {
	Species f('f');
	assert(f._id == 'f');
}

TEST(Darwin, species2) {
	Species a('a');
	assert(a._id == 'a');
}

TEST(Darwin, speciesInstr1) {
	Species f('f');
	f.addInstruction(Instr::hop);
	f.addInstruction(Instr::go, 0);
	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::hop);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);
}

TEST(Darwin, speciesInstr2) {
	Species f('f');
    f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::left);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);
}

TEST(Darwin, speciesInstr3) {
	Species f('f');
    f.addInstruction(Instr::if_enemy, 3);
    f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
    f.addInstruction(Instr::infect);
    f.addInstruction(Instr::go, 0);
    
	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::if_enemy);
	assert(f._pp[0]._num == 3);
	assert(f._pp[1]._instr == Instr::left);
	assert(f._pp[2]._instr == Instr::go);
	assert(f._pp[2]._num == 0);
	assert(f._pp[3]._instr == Instr::infect);
	assert(f._pp[4]._instr == Instr::go);
	assert(f._pp[4]._num == 0);
}

TEST(Darwin, speciesInstr4) {
	Species f('f');
    f.addInstruction(Instr::if_enemy, 9);
    f.addInstruction(Instr::if_empty, 7);
    f.addInstruction(Instr::if_random, 5);
    f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
    f.addInstruction(Instr::right);
    f.addInstruction(Instr::go, 0);
    f.addInstruction(Instr::hop);
    f.addInstruction(Instr::go, 0);
    f.addInstruction(Instr::infect);
    f.addInstruction(Instr::go, 0);

	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::if_enemy);
	assert(f._pp[0]._num == 9);
	assert(f._pp[1]._instr == Instr::if_empty);
	assert(f._pp[1]._num == 7);
	assert(f._pp[2]._instr == Instr::if_random);
	assert(f._pp[2]._num == 5);
	assert(f._pp[3]._instr == Instr::left);
	assert(f._pp[4]._instr == Instr::go);
	assert(f._pp[4]._num == 0);
	assert(f._pp[5]._instr == Instr::right);
	assert(f._pp[6]._instr == Instr::go);
	assert(f._pp[6]._num == 0);
	assert(f._pp[7]._instr == Instr::hop);
	assert(f._pp[8]._instr == Instr::go);
	assert(f._pp[8]._num == 0);
	assert(f._pp[9]._instr == Instr::infect);
	assert(f._pp[10]._instr == Instr::go);
	assert(f._pp[10]._num == 0);
}

TEST(Darwin, addCreature1) {
	Darwin d(10,10);
	Species f('f');
	Creature f1(f);
	d.addCreature(f1, 0, 0, Dir::east);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::east);
	assert((*d._grid[0][0])._turnTaken == false);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);
}

TEST(Darwin, addCreature2) {
	Darwin d(15,12);
	Species f('f');
	Creature f1(f);
	Creature f2(f);
	Creature f3(f);
	d.addCreature(f1, 1, 5, Dir::west);
	d.addCreature(f2, 0, 3, Dir::east);
	d.addCreature(f3, 9, 2, Dir::south);
	assert(d._grid[1][5] != 0);
	assert((*d._grid[1][5])._lrow == 1);
	assert((*d._grid[1][5])._lcol == 5);
	assert((*d._grid[1][5])._dir == Dir::west);
	assert((*d._grid[1][5])._turnTaken == false);
	assert((*d._grid[1][5])._spc == &f);
	assert((*d._grid[1][5])._Dar == &d);

	assert(d._grid[0][3] != 0);
	assert((*d._grid[0][3])._lrow == 0);
	assert((*d._grid[0][3])._lcol == 3);
	assert((*d._grid[0][3])._dir == Dir::east);
	assert((*d._grid[0][3])._turnTaken == false);
	assert((*d._grid[0][3])._spc == &f);
	assert((*d._grid[0][3])._Dar == &d);

	assert(d._grid[9][2] != 0);
	assert((*d._grid[9][2])._lrow == 9);
	assert((*d._grid[9][2])._lcol == 2);
	assert((*d._grid[9][2])._dir == Dir::south);
	assert((*d._grid[9][2])._turnTaken == false);
	assert((*d._grid[9][2])._spc == &f);
	assert((*d._grid[9][2])._Dar == &d);
}

TEST(Darwin, addCreature3) {
	Darwin d(20,25);
	Species f('f');
	Species r('r');
	Species z('z');
	Creature f1(f);
	Creature r2(r);
	Creature z3(z);
	d.addCreature(f1, 13, 5, Dir::south);
	d.addCreature(r2, 1, 10, Dir::west);
	d.addCreature(z3, 15, 19, Dir::west);
	assert(d._grid[13][5] != 0);
	assert((*d._grid[13][5])._lrow == 13);
	assert((*d._grid[13][5])._lcol == 5);
	assert((*d._grid[13][5])._dir == Dir::south);
	assert((*d._grid[13][5])._turnTaken == false);
	assert((*d._grid[13][5])._spc == &f);
	assert((*d._grid[13][5])._Dar == &d);

	assert(d._grid[1][10] != 0);
	assert((*d._grid[1][10])._lrow == 1);
	assert((*d._grid[1][10])._lcol == 10);
	assert((*d._grid[1][10])._dir == Dir::west);
	assert((*d._grid[1][10])._turnTaken == false);
	assert((*d._grid[1][10])._spc == &r);
	assert((*d._grid[1][10])._Dar == &d);

	assert(d._grid[15][19] != 0);
	assert((*d._grid[15][19])._lrow == 15);
	assert((*d._grid[15][19])._lcol == 19);
	assert((*d._grid[15][19])._dir == Dir::west);
	assert((*d._grid[15][19])._turnTaken == false);
	assert((*d._grid[15][19])._spc == &z);
	assert((*d._grid[15][19])._Dar == &d);
}

TEST(Darwin, addCreature4) {
	Darwin d(30,25);
	Species f('f');
	Species r('r');
	Species z('z');
	Creature f1(f);
	Creature r2(r);
	Creature z3(z);
	Creature f4(f);
	Creature r5(r);
	Creature z6(z);
	d.addCreature(f1, 13, 5, Dir::south);
	d.addCreature(r2, 1, 10, Dir::west);
	d.addCreature(z3, 15, 19, Dir::west);
	d.addCreature(f4, 1, 1, Dir::south);
	d.addCreature(r5, 3, 22, Dir::east);
	d.addCreature(z6, 21, 23, Dir::north);

	assert(d._grid[13][5] != 0);
	assert((*d._grid[13][5])._lrow == 13);
	assert((*d._grid[13][5])._lcol == 5);
	assert((*d._grid[13][5])._dir == Dir::south);
	assert((*d._grid[13][5])._turnTaken == false);
	assert((*d._grid[13][5])._spc == &f);
	assert((*d._grid[13][5])._Dar == &d);

	assert(d._grid[1][10] != 0);
	assert((*d._grid[1][10])._lrow == 1);
	assert((*d._grid[1][10])._lcol == 10);
	assert((*d._grid[1][10])._dir == Dir::west);
	assert((*d._grid[1][10])._turnTaken == false);
	assert((*d._grid[1][10])._spc == &r);
	assert((*d._grid[1][10])._Dar == &d);

	assert(d._grid[15][19] != 0);
	assert((*d._grid[15][19])._lrow == 15);
	assert((*d._grid[15][19])._lcol == 19);
	assert((*d._grid[15][19])._dir == Dir::west);
	assert((*d._grid[15][19])._turnTaken == false);
	assert((*d._grid[15][19])._spc == &z);
	assert((*d._grid[15][19])._Dar == &d);

	assert(d._grid[1][1] != 0);
	assert((*d._grid[1][1])._lrow == 1);
	assert((*d._grid[1][1])._lcol == 1);
	assert((*d._grid[1][1])._dir == Dir::south);
	assert((*d._grid[1][1])._turnTaken == false);
	assert((*d._grid[1][1])._spc == &f);
	assert((*d._grid[1][1])._Dar == &d);

	assert(d._grid[3][22] != 0);
	assert((*d._grid[3][22])._lrow == 3);
	assert((*d._grid[3][22])._lcol == 22);
	assert((*d._grid[3][22])._dir == Dir::east);
	assert((*d._grid[3][22])._turnTaken == false);
	assert((*d._grid[3][22])._spc == &r);
	assert((*d._grid[3][22])._Dar == &d);

	assert(d._grid[21][23] != 0);
	assert((*d._grid[21][23])._lrow == 21);
	assert((*d._grid[21][23])._lcol == 23);
	assert((*d._grid[21][23])._dir == Dir::north);
	assert((*d._grid[21][23])._turnTaken == false);
	assert((*d._grid[21][23])._spc == &z);
	assert((*d._grid[21][23])._Dar == &d);
}


TEST(Darwin, addCreatureInstructions1) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	d.addCreature(f1, 1, 1, Dir::south);

	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::left);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);
	assert(d._grid[1][1] != 0);
	assert((*d._grid[1][1])._lrow == 1);
	assert((*d._grid[1][1])._lcol == 1);
	assert((*d._grid[1][1])._dir == Dir::south);
	assert((*d._grid[1][1])._turnTaken == false);
	assert((*d._grid[1][1])._spc == &f);
	assert((*d._grid[1][1])._Dar == &d);
}


TEST(Darwin, addCreatureInstructions2) {
	Darwin d(10,10);
	Species f('f');
	Species h('h');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);

	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);

	Creature f1(f);
	Creature h1(h);
	d.addCreature(f1, 1, 1, Dir::south);
	d.addCreature(h1, 6, 9, Dir::west);

	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::left);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);
	assert(d._grid[1][1] != 0);
	assert((*d._grid[1][1])._lrow == 1);
	assert((*d._grid[1][1])._lcol == 1);
	assert((*d._grid[1][1])._dir == Dir::south);
	assert((*d._grid[1][1])._turnTaken == false);
	assert((*d._grid[1][1])._spc == &f);
	assert((*d._grid[1][1])._Dar == &d);

	assert(h._id == 'h');
	assert(h._pp[0]._instr == Instr::hop);
	assert(h._pp[1]._instr == Instr::go);
	assert(h._pp[1]._num == 0);
	assert(d._grid[6][9] != 0);
	assert((*d._grid[6][9])._lrow == 6);
	assert((*d._grid[6][9])._lcol == 9);
	assert((*d._grid[6][9])._dir == Dir::west);
	assert((*d._grid[6][9])._turnTaken == false);
	assert((*d._grid[6][9])._spc == &h);
	assert((*d._grid[6][9])._Dar == &d);
}

TEST(Darwin, addCreatureInstructions3) {
	Darwin d(15,12);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature f2(f);
	Creature f3(f);
	d.addCreature(f1, 1, 5, Dir::west);
	d.addCreature(f2, 0, 3, Dir::east);
	d.addCreature(f3, 9, 2, Dir::south);


	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::left);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);
	assert(d._grid[1][5] != 0);
	assert((*d._grid[1][5])._lrow == 1);
	assert((*d._grid[1][5])._lcol == 5);
	assert((*d._grid[1][5])._dir == Dir::west);
	assert((*d._grid[1][5])._turnTaken == false);
	assert((*d._grid[1][5])._spc == &f);
	assert((*d._grid[1][5])._Dar == &d);
	assert(d._grid[0][3] != 0);
	assert((*d._grid[0][3])._lrow == 0);
	assert((*d._grid[0][3])._lcol == 3);
	assert((*d._grid[0][3])._dir == Dir::east);
	assert((*d._grid[0][3])._turnTaken == false);
	assert((*d._grid[0][3])._spc == &f);
	assert((*d._grid[0][3])._Dar == &d);
	assert(d._grid[9][2] != 0);
	assert((*d._grid[9][2])._lrow == 9);
	assert((*d._grid[9][2])._lcol == 2);
	assert((*d._grid[9][2])._dir == Dir::south);
	assert((*d._grid[9][2])._turnTaken == false);
	assert((*d._grid[9][2])._spc == &f);
	assert((*d._grid[9][2])._Dar == &d);
}

TEST(Darwin, addCreatureInstructions4) {
	Darwin d(15,12);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Species r('r');
	r.addInstruction(Instr::hop);
    r.addInstruction(Instr::go, 0);
	Species z('z');
	z.addInstruction(Instr::if_enemy, 4);
    z.addInstruction(Instr::hop);
	z.addInstruction(Instr::left);
    z.addInstruction(Instr::go, 0);
	z.addInstruction(Instr::infect);
    z.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature r2(r);
	Creature z3(z);
	d.addCreature(f1, 1, 4, Dir::west);
	d.addCreature(r2, 1, 3, Dir::east);
	d.addCreature(z3, 2, 2, Dir::south);


	assert(f._id == 'f');
	assert(f._pp[0]._instr == Instr::left);
	assert(f._pp[1]._instr == Instr::go);
	assert(f._pp[1]._num == 0);

	assert(r._id == 'r');
	assert(r._pp[0]._instr == Instr::hop);
	assert(r._pp[1]._instr == Instr::go);
	assert(r._pp[1]._num == 0);

	assert(z._id == 'z');
	assert(z._pp[0]._instr == Instr::if_enemy);
	assert(z._pp[0]._num == 4);
	assert(z._pp[1]._instr == Instr::hop);
	assert(z._pp[2]._instr == Instr::left);
	assert(z._pp[3]._instr == Instr::go);
	assert(z._pp[3]._num == 0);
	assert(z._pp[4]._instr == Instr::infect);
	assert(z._pp[5]._instr == Instr::go);
	assert(z._pp[5]._num == 0);

	assert(d._grid[1][4] != 0);
	assert((*d._grid[1][4])._lrow == 1);
	assert((*d._grid[1][4])._lcol == 4);
	assert((*d._grid[1][4])._dir == Dir::west);
	assert((*d._grid[1][4])._turnTaken == false);
	assert((*d._grid[1][4])._spc == &f);
	assert((*d._grid[1][4])._Dar == &d);
	assert(d._grid[1][3] != 0);
	assert((*d._grid[1][3])._lrow == 1);
	assert((*d._grid[1][3])._lcol == 3);
	assert((*d._grid[1][3])._dir == Dir::east);
	assert((*d._grid[1][3])._turnTaken == false);
	assert((*d._grid[1][3])._spc == &r);
	assert((*d._grid[1][3])._Dar == &d);
	assert(d._grid[2][2] != 0);
	assert((*d._grid[2][2])._lrow == 2);
	assert((*d._grid[2][2])._lcol == 2);
	assert((*d._grid[2][2])._dir == Dir::south);
	assert((*d._grid[2][2])._turnTaken == false);
	assert((*d._grid[2][2])._spc == &z);
	assert((*d._grid[2][2])._Dar == &d);
}


TEST(Darwin, sim1left) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	d.addCreature(f1, 0, 0, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::west);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);
}

TEST(Darwin, sim1right) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::right);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	d.addCreature(f1, 0, 0, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::east);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);
}

TEST(Darwin, sim1infect) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::right);
    f.addInstruction(Instr::go, 0);
	Species i('i');
	i.addInstruction(Instr::infect);
    i.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature i2(i);
	d.addCreature(f1, 0, 0, Dir::north);
	d.addCreature(i2, 1, 0, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::east);
	assert((*d._grid[0][0])._spc == &i);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &i);
	assert((*d._grid[1][0])._Dar == &d);
}

TEST(Darwin, sim1infect_false) {
	Darwin d(2,2);
	Species i('i');
	i.addInstruction(Instr::infect);
    i.addInstruction(Instr::go, 0);
	Creature i1(i);
	Creature i2(i);
	d.addCreature(i1, 0, 0, Dir::south);
	d.addCreature(i2, 1, 0, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &i);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &i);
	assert((*d._grid[1][0])._Dar == &d);
}

TEST(Darwin, sim1hop) {
	Darwin d(2,2);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::south);
	d.simulate();


	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::south);
	assert((*d._grid[1][0])._spc == &h);
	assert((*d._grid[1][0])._Dar == &d);
}

TEST(Darwin, sim1hop_blocked) {
	Darwin d(2,2);
	Species h('h');
	Species f('f');
	f.addInstruction(Instr::right);
    f.addInstruction(Instr::go, 0);
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	Creature f2(f);
	d.addCreature(h1, 0, 0, Dir::south);
	d.addCreature(f2, 1, 0, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &h);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::east);
	assert((*d._grid[1][0])._spc == &f);
	assert((*d._grid[1][0])._Dar == &d);
}


TEST(Darwin, sim2) {
	Darwin d(1,5);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature f2(f);
	Creature f3(f);
	Creature f4(f);
	Creature f5(f);
	d.addCreature(f1, 0, 0, Dir::north);
	d.addCreature(f2, 0, 1, Dir::west);
	d.addCreature(f3, 0, 2, Dir::south);
	d.addCreature(f4, 0, 3, Dir::east);
	d.addCreature(f5, 0, 4, Dir::north);

	d.simulate();

	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::west);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._dir == Dir::south);
	assert((*d._grid[0][1])._spc == &f);
	assert((*d._grid[0][1])._Dar == &d);

	assert(d._grid[0][2] != 0);
	assert((*d._grid[0][2])._lrow == 0);
	assert((*d._grid[0][2])._lcol == 2);
	assert((*d._grid[0][2])._dir == Dir::east);
	assert((*d._grid[0][2])._spc == &f);
	assert((*d._grid[0][2])._Dar == &d);

	assert(d._grid[0][3] != 0);
	assert((*d._grid[0][3])._lrow == 0);
	assert((*d._grid[0][3])._lcol == 3);
	assert((*d._grid[0][3])._dir == Dir::north);
	assert((*d._grid[0][3])._spc == &f);
	assert((*d._grid[0][3])._Dar == &d);

	assert(d._grid[0][4] != 0);
	assert((*d._grid[0][4])._lrow == 0);
	assert((*d._grid[0][4])._lcol == 4);
	assert((*d._grid[0][4])._dir == Dir::west);
	assert((*d._grid[0][4])._spc == &f);
	assert((*d._grid[0][4])._Dar == &d);
}


TEST(Darwin, sim3) {
	Darwin d(1,2);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::east);

	d.simulate();

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._dir == Dir::east);
	assert((*d._grid[0][1])._spc == &h);
	assert((*d._grid[0][1])._Dar == &d);
}


TEST(Darwin, sim4) {
	Darwin d(4,4);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	Creature h2(h);
	d.addCreature(h1, 0, 0, Dir::east);
	d.addCreature(h2, 3, 3, Dir::west);

	d.simulate(2);

	assert(d._grid[0][2] != 0);
	assert((*d._grid[0][2])._lrow == 0);
	assert((*d._grid[0][2])._lcol == 2);
	assert((*d._grid[0][2])._dir == Dir::east);
	assert((*d._grid[0][2])._spc == &h);
	assert((*d._grid[0][2])._Dar == &d);

	assert(d._grid[3][1] != 0);
	assert((*d._grid[3][1])._lrow == 3);
	assert((*d._grid[3][1])._lcol == 1);
	assert((*d._grid[3][1])._dir == Dir::west);
	assert((*d._grid[3][1])._spc == &h);
	assert((*d._grid[3][1])._Dar == &d);
}

TEST(Darwin, reqAction_Empty) {
	Darwin d(2,2);
	Species h('h');
	h.addInstruction(Instr::left);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::south);
	
	bool b = d.requestAction(Instr::if_empty, h1);

	assert(b == true);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &h);
	assert((*d._grid[0][0])._Dar == &d);
}

TEST(Darwin, reqAction_notEmpty) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature f2(f);
	d.addCreature(f1, 0, 0, Dir::south);
	d.addCreature(f2, 1, 0, Dir::north);
	
	bool b = d.requestAction(Instr::if_empty, f1);
	bool b2 = d.requestAction(Instr::if_empty, f2);

	assert(b == false);
	assert(b2 == false);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &f);
	assert((*d._grid[1][0])._Dar == &d);
}

TEST(Darwin, reqAction_enemy) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature f2(f);
	d.addCreature(f1, 0, 0, Dir::south);
	d.addCreature(f2, 1, 0, Dir::north);
	
	bool b = d.requestAction(Instr::if_enemy, f1);
	bool b2 = d.requestAction(Instr::if_enemy, f2);

	assert(b == false);
	assert(b2 == false);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &f);
	assert((*d._grid[1][0])._Dar == &d);
}

TEST(Darwin, reqAction_enemy2) {
	Darwin d(2,2);
	Species f('f');
	Species h('h');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
    h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature f1(f);
	Creature h2(h);
	d.addCreature(f1, 0, 0, Dir::south);
	d.addCreature(h2, 1, 0, Dir::north);
	
	bool b = d.requestAction(Instr::if_enemy, f1);
	bool b2 = d.requestAction(Instr::if_enemy, h2);

	assert(b == true);
	assert(b2 == true);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::south);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &h);
	assert((*d._grid[1][0])._Dar == &d);
}


TEST(Darwin, reqAction_wall) {
	Darwin d(2,2);
	Species f('f');
	f.addInstruction(Instr::left);
    f.addInstruction(Instr::go, 0);
	Creature f1(f);
	d.addCreature(f1, 0, 0, Dir::north);
	
	bool b = d.requestAction(Instr::if_enemy, f1);

	assert(b == false);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::north);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);
}

TEST(Darwin, reqAction_wall2) {
	Darwin d(2,2);
	Species f('f');
	Species h('h');
	f.addInstruction(Instr::if_wall, 2);
    f.addInstruction(Instr::go, 0);
    f.addInstruction(Instr::left);
    h.addInstruction(Instr::if_wall, 2);
    h.addInstruction(Instr::go, 0);
    h.addInstruction(Instr::hop);
	Creature f1(f);
	Creature h2(h);
	d.addCreature(f1, 0, 0, Dir::north);
	d.addCreature(h2, 1, 0, Dir::north);
	
	bool b = d.requestAction(Instr::if_wall, f1);
	bool b2 = d.requestAction(Instr::if_wall, h2);

	assert(b == true);
	assert(b2 == false);
	assert(d._grid[0][0] != 0);
	assert((*d._grid[0][0])._lrow == 0);
	assert((*d._grid[0][0])._lcol == 0);
	assert((*d._grid[0][0])._dir == Dir::north);
	assert((*d._grid[0][0])._spc == &f);
	assert((*d._grid[0][0])._Dar == &d);

	assert(d._grid[1][0] != 0);
	assert((*d._grid[1][0])._lrow == 1);
	assert((*d._grid[1][0])._lcol == 0);
	assert((*d._grid[1][0])._dir == Dir::north);
	assert((*d._grid[1][0])._spc == &h);
	assert((*d._grid[1][0])._Dar == &d);
}


TEST(Darwin, exec1) {
	Darwin d(3,3);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::east);

	h1.execute();

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._dir == Dir::east);
	assert((*d._grid[0][1])._spc == &h);
	assert((*d._grid[0][1])._Dar == &d);
}

TEST(Darwin, exec2) {
	Darwin d(4,4);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	Creature h2(h);
	d.addCreature(h1, 0, 0, Dir::east);
	d.addCreature(h2, 3, 3, Dir::west);

	h1.execute();
	h2.execute();

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._dir == Dir::east);
	assert((*d._grid[0][1])._spc == &h);
	assert((*d._grid[0][1])._Dar == &d);

	assert(d._grid[3][2] != 0);
	assert((*d._grid[3][2])._lrow == 3);
	assert((*d._grid[3][2])._lcol == 2);
	assert((*d._grid[3][2])._dir == Dir::west);
	assert((*d._grid[3][2])._spc == &h);
	assert((*d._grid[3][2])._Dar == &d);
}


TEST(Darwin, turnFinished1) {
	Darwin d(5,3);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::east);

	h1.execute();
	h1.turnFinished();

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._turnTaken == true);
	assert((*d._grid[0][1])._dir == Dir::east);
	assert((*d._grid[0][1])._spc == &h);
	assert((*d._grid[0][1])._Dar == &d);
}


TEST(Darwin, nextTurn1) {
	Darwin d(5,3);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::east);

	h1.execute();
	h1.turnFinished();
	h1.nextTurn();

	assert(d._grid[0][1] != 0);
	assert((*d._grid[0][1])._lrow == 0);
	assert((*d._grid[0][1])._lcol == 1);
	assert((*d._grid[0][1])._turnTaken == false);
	assert((*d._grid[0][1])._dir == Dir::east);
	assert((*d._grid[0][1])._spc == &h);
	assert((*d._grid[0][1])._Dar == &d);

}

TEST(Darwin, nextTurn2) {
	Darwin d(5,3);
	Species h('h');
	h.addInstruction(Instr::hop);
    h.addInstruction(Instr::go, 0);
	Creature h1(h);
	d.addCreature(h1, 0, 0, Dir::east);

	h1.execute();
	h1.turnFinished();
	h1.nextTurn();

	h1.execute();
	h1.turnFinished();
	h1.nextTurn();

	assert(d._grid[0][2] != 0);
	assert((*d._grid[0][2])._lrow == 0);
	assert((*d._grid[0][2])._lcol == 2);
	assert((*d._grid[0][2])._turnTaken == false);
	assert((*d._grid[0][2])._dir == Dir::east);
	assert((*d._grid[0][2])._spc == &h);
	assert((*d._grid[0][2])._Dar == &d);

}