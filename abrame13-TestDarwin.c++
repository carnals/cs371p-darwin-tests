#define private public

// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
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

% g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

% valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"
#include "darwin.h"




TEST(Darwin, species_name1) {
    Species s('a');
    assert(s._name == 'a');
}

TEST(Darwin, species_name2) {
    Species s('b');
    assert(s._name == 'b');
}

TEST(Darwin, species_name3) {
    Species s('c');
    assert(s._name == 'c');
}

TEST(Darwin, species_name4) {
    Species s('d');
    assert(s._name == 'd');
}

TEST(Darwin, species_name5) {
    Species s('e');
    assert(s._name == 'e');
}

TEST(Darwin, species_execute1) {
    Species s('e');
    s.addInstruction(I_LEFT);
    s.addInstruction(I_GO, 0);

    Darwin g(1, 1);

    Creature c(&s, D_NORTH);
    s.execute(c._pc, c._dir, 0, 0, &g);

    assert(c._pc == 1);
}

TEST(Darwin, species_execute2) {
    Species s('e');
    s.addInstruction(I_LEFT);
    s.addInstruction(I_GO, 0);

    Darwin g(1, 1);

    Creature c(&s, D_NORTH);
    s.execute(c._pc, c._dir, 0, 0, &g);
    s.execute(c._pc, c._dir, 0, 0, &g);

    assert(c._pc == 0);
}

TEST(Darwin, species_execute3) {
    Species s('e');
    s.addInstruction(I_GO, 5);
    s.addInstruction(I_GO, 0);
    s.addInstruction(I_GO, 0);
    s.addInstruction(I_GO, 0);
    s.addInstruction(I_GO, 0);
    s.addInstruction(I_HOP);

    Darwin g(1, 1);

    Creature c(&s, D_NORTH);
    s.execute(c._pc, c._dir, 0, 0, &g);

    assert(c._pc == 5);
}

TEST(Darwin, species_add_instr1) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_HOP);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_HOP);
}

TEST(Darwin, species_add_instr2) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_HOP);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_HOP);

    s.addInstruction(I_LEFT);
    assert(s._instructions.size() == 2);
    assert(s._instructions[1] == I_LEFT);
}

TEST(Darwin, species_add_instr3) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_HOP);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_HOP);

    s.addInstruction(I_LEFT);
    assert(s._instructions.size() == 2);
    assert(s._instructions[1] == I_LEFT);

    s.addInstruction(I_RIGHT);
    assert(s._instructions.size() == 3);
    assert(s._instructions[2] == I_RIGHT);
}

TEST(Darwin, species_add_instr4) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_GO, 0);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_GO);
    assert(s._jumps[0] == 0);
}

TEST(Darwin, species_add_instr5) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_RANDOM, 1);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_RANDOM);
    assert(s._jumps[0] == 1);
}

TEST(Darwin, species_add_instr6) {
    Species s('a');
    assert(s._name == 'a');

    s.addInstruction(I_ENEMY, 2);
    assert(s._instructions.size() == 1);
    assert(s._instructions[0] == I_ENEMY);
    assert(s._jumps[0] == 2);
}

TEST(Darwin, species_enemy1) {
    Species s('a');
    Species t('b');

    assert(s.isEnemy(&t));
}

TEST(Darwin, species_enemy2) {
    Species s('a');
    Species t('b');

    assert(t.isEnemy(&s));
}

TEST(Darwin, species_enemy3) {
    Species s('a');
    Species t('a');

    assert(s.isEnemy(&t));
}

TEST(Darwin, species_enemy4) {
    Species s('a');

    assert(!s.isEnemy(&s));
}

TEST(Darwin, species_print1) {
    Species s('a');
	std::ostringstream w;
	s.print(w);

    assert(w.str() == "a");
}

TEST(Darwin, species_print2) {
    Species s('b');
	std::ostringstream w;
	s.print(w);

    assert(w.str() == "b");
}

TEST(Darwin, species_print3) {
    Species s('a');
    Species t('a');
	std::ostringstream w;

	s.print(w);
    assert(w.str() == "a");

    t.print(w);
    assert(w.str() == "aa");
}

TEST(Darwin, creature_constr1) {
    Species s('a');
    Creature c;

    assert(c._s == NULL);
}

TEST(Darwin, creature_constr2) {
    Species s('a');
    Creature c;

    assert(c._s != &s);
}

TEST(Darwin, creature_constr3) {
    Species s('a');
    Creature c(&s, D_NORTH);

    assert(c._s == &s);
}

TEST(Darwin, creature_constr4) {
    Species s('a');
    Creature c(&s, D_NORTH);

    assert(c._pc == 0);
}

TEST(Darwin, creature_constr5) {
    Species s('a');
    Creature c(&s, D_NORTH);

    assert(c._dir == D_NORTH);
}

TEST(Darwin, creature_constr6) {
    Species s('a');
    Creature c(&s, D_NORTH);

    assert(c._turn == 0);
}

TEST(Darwin, creature_takeTurn1) {
    Species s('a');
    s.addInstruction(I_LEFT);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);
    c->takeTurn(0, 0, 0, &g);

    assert(c->_turn == 1);
    assert(c->_dir == D_WEST);
}

TEST(Darwin, creature_takeTurn2) {
    Species s('a');
    s.addInstruction(I_LEFT);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);
    c->takeTurn(0, 0, 0, &g);
    c->takeTurn(0, 0, 0, &g);  // no repeating turns
    c->takeTurn(0, 0, 0, &g);

    assert(c->_turn == 1);
    assert(c->_dir == D_WEST);
}

TEST(Darwin, creature_takeTurn3) {
    Species s('a');
    s.addInstruction(I_LEFT);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);
    c->takeTurn(0, 0, 0, &g);
    c->takeTurn(1, 0, 0, &g);

    assert(c->_turn == 2);
    assert(c->_dir == D_SOUTH);
}

TEST(Darwin, creature_isEnemy1) {
    Species s('a');
    Species t('b');

    Creature c(&s, D_NORTH);

    assert(c.isEnemy(&t));
}

TEST(Darwin, creature_isEnemy2) {
    Species s('a');
    Species t('a');

    Creature c(&s, D_NORTH);

    assert(c.isEnemy(&t));
}

TEST(Darwin, creature_isEnemy3) {
    Species s('a');

    Creature c(&s, D_NORTH);

    assert(!c.isEnemy(&s));
}

TEST(Darwin, creature_transform1) {
    Species s('a');
    s.addInstruction(I_LEFT);

    Species t('b');
    t.addInstruction(I_RIGHT);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);
    c->transform(&t);

    assert(c->_s == &t);
    assert(c->_pc == 0);
}

TEST(Darwin, creature_transform2) {
    Species s('a');
    s.addInstruction(I_LEFT);
    s.addInstruction(I_GO, 0);

    Species t('b');
    t.addInstruction(I_RIGHT);
    t.addInstruction(I_GO, 0);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);
    c->takeTurn(0, 0, 0, &g);
    assert(c->_dir == D_WEST);
    assert(c->_pc == 1);

    c->transform(&s);
    assert(c->_s == &s);
    assert(c->_dir == D_WEST);
    assert(c->_pc == 1);
}

TEST(Darwin, creature_transform3) {
    Species s('a');
    s.addInstruction(I_LEFT);
    s.addInstruction(I_GO, 0);

    Species t('b');
    t.addInstruction(I_RIGHT);
    t.addInstruction(I_GO, 0);

    Darwin g(1, 1);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    Creature* c = g.creatureAt(0, 0);

    c->takeTurn(0, 0, 0, &g);
    assert(c->_pc == 1);

    c->transform(&t);

    assert(c->_s == &t);
    assert(c->_pc == 0);
}

TEST(Darwin, creature_print1) {
    Species s('a');
    Creature c(&s, D_NORTH);

	std::ostringstream w;
	c.print(w);

    assert(w.str() == "a");
}

TEST(Darwin, creature_print2) {
    Species s('a');
    Species t('b');
    Creature c(&s, D_NORTH);
    
	std::ostringstream w;
	c.print(w);
	c.transform(&t);
	c.print(w);

    assert(w.str() == "ab");
}

TEST(Darwin, creature_print3) {
    Species s('a');
    Species t('b');
    Creature c(&s, D_NORTH);
    
	std::ostringstream w;
	c.print(w);
	c.transform(&s);
	c.print(w);

    assert(w.str() == "aa");
}

TEST(Darwin, darwin_constr1) {
    Darwin g(1, 1);

    assert(g._rows == 1);
    assert(g._cols == 1);
}

TEST(Darwin, darwin_constr2) {
    Darwin g(5, 5);

    assert(g._rows == 5);
    assert(g._cols == 5);
    assert(g._creatures.size() == 25);
    assert(g._grid.size() == 25);
}

TEST(Darwin, darwin_constr3) {
    Darwin g(10, 10);

    assert(g._rows == 10);
    assert(g._cols == 10);
    assert(g._creatures.size() == 100);
    assert(g._grid.size() == 100);
    assert(g._count == 0);
    assert(g._turn == 0);
}

TEST(Darwin, darwin_addCreature1) {
    Darwin g(1, 1);
    Species s('a');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    assert(g._rows == 1);
    assert(g._cols == 1);
    assert(g._count == 1);
}

TEST(Darwin, darwin_addCreature2) {
    Darwin g(1, 1);
    Species s('a');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    assert (!g.addCreature(Creature(&s, D_NORTH), 0, 1));

    assert(g._rows == 1);
    assert(g._cols == 1);
    assert(g._count == 1);
}

TEST(Darwin, darwin_addCreature3) {
    Darwin g(2, 2);
    Species s('a');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&s, D_NORTH), 0, 0);

    assert(g._rows == 2);
    assert(g._cols == 2);
    assert(g._count == 1);
}

TEST(Darwin, darwin_creatureAt1) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(0, 0);

    assert(c1->_s == &s);
}

TEST(Darwin, darwin_creatureAt2) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(0, 1);

    assert(c1->_s == &t);
}

TEST(Darwin, darwin_creatureAt3) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(1, 1);

    assert(c1 == NULL);
}

TEST(Darwin, darwin_creatureAt4) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(D_EAST, 0, 0);

    assert(c1 != NULL);
    assert(c1->_s == &t);
}

TEST(Darwin, darwin_creatureAt5) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(D_WEST, 0, 1);

    assert(c1 != NULL);
    assert(c1->_s == &s);
}

TEST(Darwin, darwin_creatureAt6) {
    Darwin g(2, 2);
    Species s('a');
    Species t('b');

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.addCreature(Creature(&t, D_EAST), 0, 1);

    Creature* c1 = g.creatureAt(D_WEST, 0, 0);

    assert(c1 == NULL);
}

TEST(Darwin, darwin_print1) {
    Darwin g(1, 1);
    Species s('a');
	std::ostringstream w;

    g.print(w);

    assert(w.str() == "Turn = 0.\n  0\n0 .\n\n");
}

TEST(Darwin, darwin_print2) {
    Darwin g(1, 1);
    Species s('a');
	std::ostringstream w;

	g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.print(w);

    assert(w.str() == "Turn = 0.\n  0\n0 a\n\n");
}

TEST(Darwin, darwin_print3) {
    Darwin g(1, 1);
    Species s('a');
    s.addInstruction(I_HOP);
	std::ostringstream w;

	g.addCreature(Creature(&s, D_NORTH), 0, 0);
	g.play();
    g.print(w);

    assert(w.str() == "Turn = 1.\n  0\n0 a\n\n");
}

TEST(Darwin, darwin_isWall1) {
    Darwin g(1, 1);
    Species s('a');
    s.addInstruction(I_HOP);

	assert(g.isWall(D_NORTH, 0, 0));
}

TEST(Darwin, darwin_isWall2) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

	assert(!g.isWall(D_SOUTH, 0, 0));
}

TEST(Darwin, darwin_isWall3) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

	assert(g.isWall(D_SOUTH, 1, 0));
}

TEST(Darwin, darwin_isEmpty1) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

	assert(g.isEmpty(D_SOUTH, 0, 0));
}

TEST(Darwin, darwin_isEmpty2) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

	assert(!g.isEmpty(D_SOUTH, 1, 0));
}

TEST(Darwin, darwin_isEmpty3) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

    g.addCreature(Creature(&s, D_NORTH), 0, 0);

	assert(!g.isEmpty(D_NORTH, 1, 0));
}

TEST(Darwin, darwin_move1) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.move(D_SOUTH, 0, 0);

	assert(!g.isEmpty(D_SOUTH, 0, 0));
}

TEST(Darwin, darwin_move2) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.move(D_SOUTH, 0, 0);
    g.move(D_SOUTH, 0, 0);

	assert(!g.isEmpty(D_SOUTH, 0, 0));
	assert(g.isEmpty(D_NORTH, 1, 0));
}

TEST(Darwin, darwin_play1) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

    g.addCreature(Creature(&s, D_NORTH), 0, 0);
    g.play();

	assert(g.isEmpty(D_SOUTH, 0, 0));
	assert(!g.isEmpty(D_NORTH, 1, 0));
}

TEST(Darwin, darwin_play2) {
    Darwin g(2, 2);
    Species s('a');
    s.addInstruction(I_HOP);

    g.addCreature(Creature(&s, D_SOUTH), 0, 0);
    g.play();

	assert(!g.isEmpty(D_SOUTH, 0, 0));
	assert(g.isEmpty(D_NORTH, 1, 0));
}