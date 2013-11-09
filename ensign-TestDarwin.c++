//---------------------------------------
// Katherine Ensign
// eid: krh524
// csid: ensign
// CS371P Project 4: Darwin's World
// 7 November, 2013
//---------------------------------------

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

#include <string>
#include <cstdlib>
#include <stdexcept>
#include "gtest/gtest.h"

#define private public

#include "Darwin.h"
using namespace std;

// ------------
// Darwin Tests
// ------------

TEST(Darwin, constructor_big){
	Darwin d(99,100);
	ASSERT_TRUE(d.row == 99);
	ASSERT_TRUE(d.col == 100);
	ASSERT_TRUE(d.turn == 0);
}

TEST(Darwin, constructor_empty){
	Darwin d(0,0);
	ASSERT_TRUE(d.row == 0);
	ASSERT_TRUE(d.col == 0);
	ASSERT_TRUE(d.turn == 0);
}

TEST(Darwin, constructor_invalid){
	try{
		Darwin d(-1, -1);
		ASSERT_TRUE(false);
	} catch (const invalid_argument&){
		ASSERT_TRUE(true);
	}
}

TEST(Darwin, addCreature_normal){
	Darwin d(1, 1);
	Species s('s');
	Creature c(s, 0);
	d.addCreature(c, 0, 0);
	ASSERT_TRUE(d.grid[0][0].isValid());
}

TEST(Darwin, addCreature_on_top_of_another){
	Darwin d(1, 1);
	Species s('s');
	Creature c1(s, 0);
	Creature c2(s, 1);
	try{
		d.addCreature(c1, 0, 0);
		d.addCreature(c2, 0, 0);
		ASSERT_TRUE(true);
	} catch (const invalid_argument&){
		ASSERT_TRUE(false);
	}
}

TEST(Darwin, addCreature_fill_grid){
	Darwin d(4, 4);
	Species s('s');
	Creature c1(s, 0);
	Creature c2(s, 1);
	Creature c3(s, 2);
	Creature c4(s, 3);
	try{
		d.addCreature(c1, 0, 0);
		d.addCreature(c2, 0, 1);
		d.addCreature(c3, 1, 0);
		d.addCreature(c4, 1, 1);
		ASSERT_TRUE(true);
	}catch(...){
		ASSERT_TRUE(false);
	}
}

TEST(Darwin, runTurn1){
	Darwin d(1, 1);
	for (int i = 0; i < 10; i++){
		d.runTurn();
	}
	ASSERT_TRUE(d.turn == 10);
}

TEST(Darwin, runTurn2){
	Darwin d(1, 1);
	ASSERT_TRUE(d.turn == 0);
}

TEST(Darwin, nextCoordinate_normal){
	Darwin d(1, 2);
	int r = 0;
	int c = 0;
	d.nextCoordinate(2, r, c);
	ASSERT_TRUE(r == 0);
	ASSERT_TRUE(c == 1);
}

TEST(Darwin, nextCoordinate_boundary){
	Darwin d(1, 1);
	int r = 0;
	int c = 0;
	d.nextCoordinate(0, r, c);
	ASSERT_TRUE(r == 0);
	ASSERT_TRUE(c == 0);
}

TEST(Darwin, nextCoordinate_out_of_bounds){
	Darwin d(1, 1);
	int r = 1;
	int c = 0;
	try{
		d.nextCoordinate(0, r, c);
		ASSERT_TRUE(false);
	}catch(const out_of_range&){
		ASSERT_TRUE(true);
	}
}

TEST(Darwin, isEmpty_true){
	Darwin d(1, 1);
	ASSERT_TRUE(d.isEmpty(0, 0));
}

TEST(Darwin, isEmpty_false){
	Darwin d(2, 1);
	Species s('s');
	Creature c(s, 0);
	d.addCreature(c, 0, 0);
	ASSERT_TRUE(d.isEmpty(1, 0));
	ASSERT_FALSE(d.isEmpty(0, 0));
}

TEST(Darwin, isEmpty_invalid){
	Darwin d(0, 0);
	try{
		d.isEmpty(0, 0);
		ASSERT_TRUE(false);
	} catch (const out_of_range&){
		ASSERT_TRUE(true);
	}
}

TEST(Darwin, isEnemy_true){
	Darwin d(1, 2);
	Species a('a');
	Species b('b');
	Creature c1(a, 2);
	Creature c2(b, 0);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	ASSERT_TRUE(d.isEnemy(0, 1, c1));
	ASSERT_TRUE(d.isEnemy(0, 0, c2));
}

TEST(Darwin, isEnemy_false){
	Darwin d(1, 2);
	Species a('a');
	Creature c1(a, 2);
	Creature c2(a, 0);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	ASSERT_FALSE(d.isEnemy(0, 1, c1));
	ASSERT_FALSE(d.isEnemy(0, 0, c2));
}

TEST(Darwin, isEnemy_invalid){
	Darwin d(1, 1);
	Species s('s');
	Creature c(s, 0);
	try{
		d.isEnemy(0, 1, c);
		ASSERT_TRUE(false);
	}catch(const out_of_range&){
		ASSERT_TRUE(true);
	}
}

TEST(Darwin, infect_success1){
	Darwin d(1, 2);
	Species a('a');
	Species b('b');
	Creature c1(a, 2);
	Creature c2(b, 0);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	d.infect(0, 1, c1);
	ASSERT_TRUE(d.grid[0][0].isAlly(d.grid[0][1]));	
}

TEST(Darwin, infect_success2){
	Darwin d(1, 2);
	Species a('a');
	Species b('b');
	Creature c1(a, 2);
	Creature c2(b, 0);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	d.infect(0, 0, c2);
	ASSERT_TRUE(d.grid[0][0].isAlly(d.grid[0][1]));	
}

TEST(Darwin, infect_success3){
	Darwin d(2, 2);
	Species a('a');
	Species b('b');
	Creature c1(a, 2);
	Creature c2(b, 0);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	d.infect(0, 0, c2);
	ASSERT_TRUE(d.grid[0][0].isAlly(d.grid[0][1]));
}
TEST(Darwin, infect_failure_invalid){
	Darwin d(1, 1);
	Species s('s');
	Creature c(s, 0);
	d.addCreature(c, 0, 0);
	try{
		d.infect(1, 0, c);
		ASSERT_TRUE(false);
	}catch(const out_of_range&){
		ASSERT_TRUE(true);
	}
}

TEST(Darwin, infect_failure_empty){
	Darwin d(1, 2);
	Species s('s');
	Creature c(s, 2);
	d.addCreature(c, 0, 0);
	ASSERT_FALSE(d.infect(0, 1, c));
}

TEST(Creature, default_constructor_normal){
	Creature c;
	ASSERT_FALSE(c.isValid());
	ASSERT_TRUE(c.sp == NULL);
	ASSERT_TRUE(c.direction == 0);
	ASSERT_TRUE(c.pc == 0);
}

TEST(Creature, constructor_normal){
	Species s('s');
	Creature c(s, 0);
	ASSERT_TRUE(c.sp == &s);
	ASSERT_TRUE(c.direction == 0);
}

TEST(Creature, constructor_invalid_direction){
	Species s('s');
	try{
		Creature c(s, 4);
		ASSERT_TRUE(false);
	}catch(const invalid_argument&){
		ASSERT_TRUE(true);
	}
}

TEST(Creature, performInstruction_hop){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(hop);
	Creature c(s, 2);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 1);
}

TEST(Creature, performInstruction_hop_wall){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(hop);
	Creature c(s, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 0);
}

TEST(Creature, performInstruction_left_normal){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(lft);
	Creature c(s, 1);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.direction == 0);
}

TEST(Creature, performInstruction_left_reset){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(lft);
	Creature c(s, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.direction == 3);
}

TEST(Creature, performInstruction_right_normal){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(rgt);
	Creature c(s, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.direction == 1);
}

TEST(Creature, performInstruction_right_reset){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(rgt);
	Creature c(s, 3);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.direction == 0);
}

TEST(Creature, performInstruction_infect_normal){
	Darwin d(2, 2);
	Species a('a');
	Species b('b');
	a.addInstruction(infect);
	Creature c1(a, 2);
	Creature c2(b, 0);
	c2.pc = 1;
	ASSERT_FALSE(c1.isAlly(c2));
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	int row = 0;
	int col = 0;
	c1.performInstruction(row, col, d);
	ASSERT_TRUE(d.grid[0][0].isAlly(d.grid[0][1]));
	ASSERT_TRUE(d.grid[0][1].pc == 0);
}

TEST(Creature, performInstruction_infect_wall){
	Darwin d(2, 2);
	Species a('a');
	Species b('b');
	a.addInstruction(infect);
	Creature c1(a, 0);
	Creature c2(b, 0);
	ASSERT_FALSE(c1.isAlly(c2));
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	int row = 0;
	int col = 0;
	c1.performInstruction(row, col, d);
	ASSERT_FALSE(c1.isAlly(c2));
}

TEST(Creature, performInstruction_if_empty_true){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(if_empty, 2);
	s.addInstruction(lft);
	s.addInstruction(hop);
	s.addInstruction(go, 0);
	Creature c(s, 3);
	d.addCreature(c, 0, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 3);
	ASSERT_TRUE(row == 1);
	ASSERT_TRUE(col == 0);
}

TEST(Creature, performInstruction_if_empty_false){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(if_empty, 2);
	s.addInstruction(lft);
	s.addInstruction(hop);
	s.addInstruction(go, 0);
	Creature c(s, 3);
	Creature x(s, 0);
	d.addCreature(c, 0, 0);
	d.addCreature(x, 1, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 2);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 0);
}

TEST(Creature, performInstruction_if_wall_true){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(if_wall, 2);
	s.addInstruction(hop);
	s.addInstruction(lft);
	s.addInstruction(go, 0);
	Creature c(s, 0);
	d.addCreature(c, 0, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 3);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 0);
}

TEST(Creature, performInstruction_if_wall_false){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(if_wall, 2);
	s.addInstruction(hop);
	s.addInstruction(lft);
	s.addInstruction(go, 0);
	Creature c(s, 2);
	d.addCreature(c, 0, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 2);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 1);
}

TEST(Creature, performInstruction_if_enemy_true){
	Darwin d(2, 2);
	Species a('a');
	Species b('b');
	a.addInstruction(if_enemy, 2);
	a.addInstruction(hop);
	a.addInstruction(lft);
	a.addInstruction(go, 0);
	Creature c(a, 2);
	Creature c2(b, 0);
	d.addCreature(c, 0, 0);
	d.addCreature(c2, 0, 1);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 3);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 0);
	ASSERT_TRUE(c.direction == 1);
}

TEST(Creature, performInstruction_if_enemy_false){
	Darwin d(2, 2);
	Species a('a');
	a.addInstruction(if_enemy, 2);
	a.addInstruction(hop);
	a.addInstruction(lft);
	a.addInstruction(go, 0);
	Creature c(a, 2);
	Creature c2(a, 0);
	ASSERT_TRUE(c.isAlly(c2));
	d.addCreature(c, 0, 0);
	d.addCreature(c2, 0, 1);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 2);
	ASSERT_TRUE(row == 0);
	ASSERT_TRUE(col == 0);
	ASSERT_TRUE(c.direction == 2);
}

TEST(Creature, performInstruction_go_lots){
	Darwin d(2, 2);
	Species s('s');
	s.addInstruction(go, 1);
	s.addInstruction(go, 2);
	s.addInstruction(go, 3);
	s.addInstruction(go, 4);
	s.addInstruction(go, 5);
	s.addInstruction(go, 6);
	s.addInstruction(go, 7);
	s.addInstruction(rgt);
	Creature c(s, 0);
	int row = 0;
	int col = 0;
	c.performInstruction(row, col, d);
	ASSERT_TRUE(c.pc == 0);
	ASSERT_TRUE(c.direction == 1);
}

TEST(Creature, infectOther_test_species){
	Species a('a');
	Species b('b');
	Creature infector(a, 0);
	Creature infectee(b, 0);
	ASSERT_FALSE(infector.isAlly(infectee));
	infector.infectOther(infectee);
	ASSERT_TRUE(infector.isAlly(infectee));
}

TEST(Creature, infectOther_test_pc){
	Species a('a');
	Species b('b');
	Creature infector(a, 0);
	Creature infectee(b, 0);
	infectee.pc = 100;
	infector.infectOther(infectee);
	ASSERT_TRUE(infectee.pc == 0);
}

TEST(Creature, infectOther_test_ally){
	Species a('a');
	Creature infector(a, 0);
	Creature infectee(a, 0);
	infectee.pc = 100;
	ASSERT_FALSE(infector.infectOther(infectee));
	ASSERT_FALSE(infectee.pc == 0);
}

TEST(Creature, isAlly_true){
	Species a('a');
	Creature c1(a, 0);
	Creature c2(a, 3);
	ASSERT_TRUE(c1.isAlly(c2));
}

TEST(Creature, isAlly_false){
	Species a('a');
	Species b('b');
	Creature c1(a, 0);
	Creature c2(b, 3);
	ASSERT_FALSE(c1.isAlly(c2));
}

TEST(Creature, isValid_true){
	Species s('s');
	Creature c(s, 0);
	ASSERT_TRUE(c.isValid());
}

TEST(Creature, isValid_false){
	Creature c;
	ASSERT_FALSE(c.isValid());
}

TEST(Creature, toString_normal){
	Species a('a');
	Creature c(a, 0);
	ASSERT_TRUE(c.toString().compare("a") == 0);
}

TEST(Creature, toString_empty){
	Creature c;
	ASSERT_TRUE(c.toString().compare(".") == 0);
}

TEST(Species, constructor_normal){
	Species s('s');
	ASSERT_TRUE(s.c == 's');
	ASSERT_TRUE(s.size() == 0);
}

TEST(Species, addInstruction_control_normal){
	Species s('s');
	s.addInstruction(if_empty, 2);
	ASSERT_TRUE(s.currentInstruction(0).i == if_empty);
	ASSERT_TRUE(s.currentInstruction(0).arg == 2);
}

TEST(Species, addInstruction_action_normal){
	Species s('s');
	s.addInstruction(infect, -1);
	ASSERT_TRUE(s.currentInstruction(0).i == infect);
	ASSERT_TRUE(s.currentInstruction(0).arg == -1);
}

TEST(Species, addInstruction_invalid_arg){
	Species s('s');
	s.addInstruction(hop, 2);
	ASSERT_TRUE(s.currentInstruction(0).arg == -1);
}

TEST(Species, currentInstruction_normal){
	Species s('s');
	s.addInstruction(go, 1);
	s.addInstruction(lft);
	s.addInstruction(hop);
	ASSERT_TRUE(s.currentInstruction(0).i == go);
	ASSERT_TRUE(s.currentInstruction(1).i == lft);
	ASSERT_TRUE(s.currentInstruction(2).i == hop);
}

TEST(Species, currentInstruction_invalid){
	Species s('s');
	try{
		s.currentInstruction(0);
		ASSERT_TRUE(false);
	}catch(const out_of_range&){
		ASSERT_TRUE(true);
	}
}

TEST(Species, size_empty){
	Species s('s');
	ASSERT_TRUE(s.size() == 0);
}

TEST(Species, size_not_empty){
	Species s('s');
	s.addInstruction(hop);
	s.addInstruction(hop);
	ASSERT_TRUE(s.size() == 2);
}

TEST(Species, toString_normal){
	Species s('s');
	ASSERT_TRUE(s.toString().compare("s") == 0);
}

TEST(Instruction, constructor_normal){
	Instruction in(hop, -1);
	ASSERT_TRUE(in.i == hop);
	ASSERT_TRUE(in.arg == -1);
}

TEST(Instruction, constructor_invalid){
	try{
		Instruction in(go, -2);
		ASSERT_TRUE(false);
	}catch (const invalid_argument&){
		ASSERT_TRUE(true);
	}
}
