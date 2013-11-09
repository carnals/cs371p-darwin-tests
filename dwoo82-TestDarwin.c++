/*
 * David Woo
 * daw2399
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// -----------------------
// =====Species tests=====
// -----------------------

// -------------------------
// Species::addInstruction()
// -------------------------

TEST(Darwin, Species_addInstruction1){
	Species s = Species("Bob");
	s.addInstruction("Do a thing");
	
	ASSERT_EQ("Bob", s._name);
	ASSERT_EQ('B', s._symbol);
	ASSERT_EQ(1, s._instructions.size());
	ASSERT_EQ("Do a thing", s._instructions[0]);
}

TEST(Darwin, Species_addInstruction2){
	Species s = Species("George");
	s.addInstruction("Do a thing");
	s.addInstruction("Do another thing");
	
	ASSERT_EQ("George", s._name);
	ASSERT_EQ('G', s._symbol);
	ASSERT_EQ(2, s._instructions.size());
	ASSERT_EQ("Do a thing", s._instructions[0]);
	ASSERT_EQ("Do another thing", s._instructions[1]);
}

TEST(Darwin, Species_addInstruction3){
	Species s = Species("Larry");
	s.addInstruction("hop");
	s.addInstruction("go 0");

	ASSERT_EQ("Larry", s._name);
	ASSERT_EQ('L', s._symbol);
	ASSERT_EQ(2, s._instructions.size());
	ASSERT_EQ("hop", s._instructions[0]);
	ASSERT_EQ("go 0", s._instructions[1]);
}

// --------------
// Creature tests
// --------------

TEST(Darwin, Creature_construction1){
	Species s = Species("Elephant");
	Creature c = Creature(&s);

	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);
	ASSERT_EQ(NORTH, c._direction);
	ASSERT_EQ(&s, c._species);
	ASSERT_EQ("Elephant", c._species->_name);
	ASSERT_EQ('E', c._species->_symbol);
}

TEST(Darwin, Creature_construction2){
	Species s = Species("Fool");
	Creature c = Creature(&s, WEST);

	ASSERT_EQ(WEST, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);
	
	ASSERT_EQ("Fool", c._species->_name);
	ASSERT_EQ('F', c._species->_symbol);
}

TEST(Darwin, Creature_construction3){
	Species s = Species("Dagnabbit");
	Creature c = Creature(&s, SOUTH);

	ASSERT_EQ(SOUTH, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	ASSERT_EQ("Dagnabbit", c._species->_name);
	ASSERT_EQ('D', c._species->_symbol);
}

// ---------------------
// Creature::turnRight()
// ---------------------

TEST(Darwin, Creature_turnRight_N){
	Species s = Species("RightN");
	Creature c = Creature(&s);

	ASSERT_EQ(NORTH, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnRight();

	ASSERT_EQ(EAST, c._direction);
}

TEST(Darwin, Creature_turnRight_S){
	Species s = Species("RightS");
	Creature c = Creature(&s, SOUTH);

	ASSERT_EQ(SOUTH, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnRight();

	ASSERT_EQ(WEST, c._direction);
}

TEST(Darwin, Creature_turnRight_E){
	Species s = Species("RightE");
	Creature c = Creature(&s, EAST);

	ASSERT_EQ(EAST, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnRight();

	ASSERT_EQ(SOUTH, c._direction);
}

TEST(Darwin, Creature_turnRight_W){
	Species s = Species("RightW");
	Creature c = Creature(&s, WEST);

	ASSERT_EQ(WEST, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnRight();

	ASSERT_EQ(NORTH, c._direction);
}

// --------------------
// Creature::turnLeft()
// --------------------

TEST(Darwin, Creature_turnLeft_N){
	Species s = Species("LeftN");
	Creature c = Creature(&s, NORTH);

	ASSERT_EQ(NORTH, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnLeft();

	ASSERT_EQ(WEST, c._direction);
}

TEST(Darwin, Creature_turnLeft_S){
	Species s = Species("LeftS");
	Creature c = Creature(&s, SOUTH);

	ASSERT_EQ(SOUTH, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnLeft();

	ASSERT_EQ(EAST, c._direction);
}

TEST(Darwin, Creature_turnLeft_E){
	Species s = Species("LeftE");
	Creature c = Creature(&s, EAST);

	ASSERT_EQ(EAST, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnLeft();

	ASSERT_EQ(NORTH, c._direction);
}

TEST(Darwin, Creature_turnLeft_W){
	Species s = Species("LeftW");
	Creature c = Creature(&s, WEST);

	ASSERT_EQ(WEST, c._direction);
	ASSERT_EQ(0, c._counter);
	ASSERT_FALSE(c._spawned);

	c.turnLeft();

	ASSERT_EQ(SOUTH, c._direction);
}

// -----------------
// Creature::morph()
// -----------------

TEST(Darwin, Creature_morph){
	Species s = Species("Bystander");
	Species i = Species("Infector");

	Creature c = Creature(&s);
	c._counter = 4;

	ASSERT_EQ(&s, c._species);
	ASSERT_EQ("Bystander", c._species->_name);
	ASSERT_EQ(4, c._counter);

	c.morph(&i);

	ASSERT_EQ(&i, c._species);
	ASSERT_EQ("Infector", c._species->_name);
	ASSERT_EQ(0, c._counter);
	ASSERT_EQ(NORTH, c._direction);
}

TEST(Darwin, Creature_morph_back){
	Species a = Species("A");
	Species b = Species("B");

	Creature c = Creature(&a, SOUTH);
	c._counter = 4;

	ASSERT_EQ(&a, c._species);
	ASSERT_EQ("A", c._species->_name);
	ASSERT_EQ(4, c._counter);

	c.morph(&b);

	ASSERT_EQ(&b, c._species);
	ASSERT_EQ("B", c._species->_name);
	ASSERT_EQ(0, c._counter);

	c.morph(&a);

	ASSERT_EQ(&a, c._species);
	ASSERT_EQ("A", c._species->_name);
	ASSERT_EQ(0, c._counter);
	ASSERT_EQ(SOUTH, c._direction);
}

TEST(Darwin, Creature_morph_twice){
	Species a = Species("A");
	Species b = Species("B");
	Species d = Species("D");

	Creature c = Creature(&a, WEST);
	c._counter = 4;

	ASSERT_EQ(&a, c._species);
	ASSERT_EQ("A", c._species->_name);
	ASSERT_EQ(4, c._counter);

	c.morph(&b);

	ASSERT_EQ(&b, c._species);
	ASSERT_EQ("B", c._species->_name);
	ASSERT_EQ(0, c._counter);

	c.morph(&d);

	ASSERT_EQ(&d, c._species);
	ASSERT_EQ("D", c._species->_name);
	ASSERT_EQ(0, c._counter);
	ASSERT_EQ(WEST, c._direction);
}

TEST(Darwin, Creature_instruction_access){
	Species s = Species("Animal-thing");
	s.addInstruction("hop");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	
	ASSERT_EQ(&s, c._species);
	ASSERT_EQ("Animal-thing", c._species->_name);
	ASSERT_EQ("hop", c._species->_instructions[0]);
	ASSERT_EQ("go 0", c._species->_instructions[1]);
}

// ------------
// Darwin tests
// ------------

TEST(Darwin, Darwin_default_construction){
	Darwin d = Darwin();

	ASSERT_EQ(0, d._numTurn);
	ASSERT_EQ(8, d._length);
	ASSERT_EQ(8, d._width);
	ASSERT_EQ(64, d._grid.size());

	for(int i = 0; i < 64; ++i)
		ASSERT_EQ(-1, d._grid[i]);
}

TEST(Darwin, Darwin_construction){
	std::ostringstream oss;
	Darwin d = Darwin(2, 3, oss);

	ASSERT_EQ(2, d._length);
	ASSERT_EQ(3, d._width);
	ASSERT_EQ(6, d._grid.size());
	ASSERT_EQ(&oss, &d._outStream);

	for(int i = 0; i < 6; ++i)
		ASSERT_EQ(-1, d._grid[i]);
}

// -------------------
// Darwin::printGrid()
// -------------------

TEST(Darwin, Darwin_printGrid1){
	std::ostringstream oss;
	std::string output;
	Darwin d = Darwin(2, 2, oss);

	ASSERT_EQ(2, d._length);
	ASSERT_EQ(2, d._width);
	ASSERT_EQ(&oss, &d._outStream);

	d.printGrid();
	output = oss.str();

	ASSERT_EQ("   01\n 0 ..\n 1 ..\n", output);
}

TEST(Darwin, Darwin_printGrid2){
	std::ostringstream oss;
	std::string output;
	Darwin d = Darwin(2, 4, oss);

	ASSERT_EQ(2, d._length);
	ASSERT_EQ(4, d._width);
	ASSERT_EQ(&oss, &d._outStream);

	d.printGrid();
	output = oss.str();

	ASSERT_EQ("   0123\n 0 ....\n 1 ....\n", output);
}

TEST(Darwin, Darwin_printGrid3){
	std::ostringstream oss;
	std::string output;
	Darwin d = Darwin(4, 2, oss);

	ASSERT_EQ(4, d._length);
	ASSERT_EQ(2, d._width);
	ASSERT_EQ(&oss, &d._outStream);

	d.printGrid();
	output = oss.str();

	ASSERT_EQ("   01\n 0 ..\n 1 ..\n 2 ..\n 3 ..\n", output);
}

TEST(Darwin, Darwin_printCreature){
	std::ostringstream oss;
	std::string output;
	Darwin d = Darwin(4, 2, oss);

	ASSERT_EQ(4, d._length);
	ASSERT_EQ(2, d._width);
	ASSERT_EQ(&oss, &d._outStream);

	Species s = Species("Aardvark");
	Creature c = Creature(&s);
	
	d.addCreature(&c);
	d.spawnCreature("Aardvark", 0, 0, SOUTH);

	d.printGrid();
	output = oss.str();

	ASSERT_EQ("   01\n 0 A.\n 1 ..\n 2 ..\n 3 ..\n", output);
}

// ---------------------
// Darwin::addCreature()
// ---------------------

TEST(Darwin, Darwin_addCreature){
	Species s = Species("Pikachu");
	Creature c = Creature(&s);
	Darwin d = Darwin();

	d.addCreature(&c);
	ASSERT_EQ(1, d._actors.size());
	ASSERT_EQ(&c, d._actors[0]);
	ASSERT_EQ(&s, d._actors[0]->_species);
	ASSERT_EQ("Pikachu", d._actors[0]->_species->_name);
}

TEST(Darwin, Darwin_add_creatures_of_same_species){
	Species s = Species("Tomato");
	Creature c1 = Creature(&s);
	Creature c2 = Creature(&s);
	Darwin d = Darwin();

	d.addCreature(&c1);
	d.addCreature(&c2);

	ASSERT_EQ(2, d._actors.size());
	ASSERT_EQ(&c1, d._actors[0]);
	ASSERT_EQ(&c2, d._actors[1]);

	ASSERT_NE(d._actors[0], d._actors[1]);
	ASSERT_EQ(&s, d._actors[0]->_species);
	ASSERT_EQ(&s, d._actors[1]->_species);
}

TEST(Darwin, Darwin_add_creatures_of_different_species){
	Species s1 = Species("Broccoli");
	Species s2 = Species("Banana");

	Creature c1 = Creature(&s1);
	Creature c2 = Creature(&s2);

	Darwin d = Darwin();

	d.addCreature(&c1);
	d.addCreature(&c2);

	ASSERT_EQ(2, d._actors.size());
	ASSERT_EQ(&c1, d._actors[0]);
	ASSERT_EQ(&c2, d._actors[1]);

	ASSERT_EQ(&s1, d._actors[0]->_species);
	ASSERT_EQ(&s2, d._actors[1]->_species);
}

// -----------------------
// Darwin::spawnCreature()
// -----------------------

TEST(Darwin, Darwin_spawnCreature){
	Species s = Species("Duck");

	Creature c = Creature(&s);

	Darwin d = Darwin();

	d.addCreature(&c);
	int i = d.spawnCreature("Duck", 0, 0, EAST);

	ASSERT_EQ(1, i);
	ASSERT_EQ(&c, d._actors[0]);
	ASSERT_EQ(&s, d._actors[0]->_species);
	ASSERT_EQ(0, d._grid[0]);
}

TEST(Darwin, Darwin_spawn_creatures_of_same_species){
	Species s = Species("Duck");

	Creature c1 = Creature(&s);
	Creature c2 = Creature(&s);
	Creature c3 = Creature(&s);

	Darwin d = Darwin();

	d.addCreature(&c1);
	d.addCreature(&c2);
	d.addCreature(&c3);

	int i = d.spawnCreature("Duck", 0, 0, EAST);
	ASSERT_EQ(1, i);

	i = d.spawnCreature("Duck", 0, 0, NORTH);
	ASSERT_EQ(0, i);

	i = d.spawnCreature("Duck", 0, 1, WEST);
	ASSERT_EQ(1, i);

	i = d.spawnCreature("Duck", 0, 2, EAST);
	ASSERT_EQ(1, i);

	ASSERT_EQ(&c1, d._actors[0]);
	ASSERT_EQ(&c2, d._actors[1]);
	ASSERT_EQ(&c3, d._actors[2]);
	ASSERT_EQ(&s, d._actors[0]->_species);
	ASSERT_EQ(&s, d._actors[1]->_species);
	ASSERT_EQ(&s, d._actors[2]->_species);
	ASSERT_EQ(0, d._grid[0]);
}

TEST(Darwin, Darwin_bad_spawn){
	Species s = Species("Waffle");

	Creature c1 = Creature(&s);
	Creature c2 = Creature(&s);

	Darwin d = Darwin();

	d.addCreature(&c1);

	int i = d.spawnCreature("Pancake", 0, 0, NORTH);
	ASSERT_EQ(-1, i);	// no such species

	i = d.spawnCreature("Waffle", 0, 0, NORTH);
	ASSERT_EQ(1, i);	// success

	i = d.spawnCreature("Waffle", 0, 0, NORTH);
	ASSERT_EQ(0, i); // space already occupied
	
	i = d.spawnCreature("Waffle", 0, 1, NORTH);
	ASSERT_EQ(-1, i); // no more Waffles in the creatures list

	d.addCreature(&c2);
	
	i = d.spawnCreature("Waffle", 0, 1, NORTH);
	ASSERT_EQ(1, i); // success
}

// ----------------------
// Darwin::whatObstacle()
// ----------------------
TEST(Darwin, Darwin_obstacle_wall_N){
	Species s = Species("NWallHugger");
	Creature c = Creature(&s);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c);

	int i = d.spawnCreature("NWallHugger", 0, 1, NORTH);
	ASSERT_EQ(1, i);

	i = d.whatObstacle(0, 1, NORTH);
	ASSERT_EQ(-2, i);
}

TEST(Darwin, Darwin_obstacle_wall_E){
	Species s = Species("EWallHugger");
	Creature c = Creature(&s);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c);

	int i = d.spawnCreature("EWallHugger", 0, 1, EAST);
	ASSERT_EQ(1, i);

	i = d.whatObstacle(0, 1, EAST);
	ASSERT_EQ(-2, i);
}

TEST(Darwin, Darwin_obstacle_wall_S){
	Species s = Species("SWallHugger");
	Creature c = Creature(&s);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c);

	int i = d.spawnCreature("SWallHugger", 1, 1, SOUTH);
	ASSERT_EQ(1, i);

	i = d.whatObstacle(1, 1, SOUTH);
	ASSERT_EQ(-2, i);
}

TEST(Darwin, Darwin_obstacle_wall_W){
	Species s = Species("WWallHugger");
	Creature c = Creature(&s);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c);

	int i = d.spawnCreature("WWallHugger", 0, 0, WEST);
	ASSERT_EQ(1, i);

	i = d.whatObstacle(0, 0, WEST);
	ASSERT_EQ(-2, i);
}

TEST(Darwin, Darwin_obstacle_multiple_creatures){
	Species s = Species("Sandshrew");
	Species x = Species("Mudkip");
	Creature c1 = Creature(&s);
	Creature c2 = Creature(&s);
	Creature b = Creature(&x);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c1);
	d.addCreature(&c2);
	d.addCreature(&b);

	int i = d.spawnCreature("Mudkip", 1, 0, EAST);
	ASSERT_EQ(1, i); // b

	i = d.spawnCreature("Sandshrew", 0, 0, SOUTH);
	ASSERT_EQ(1, i); // c1

	i = d.spawnCreature("Sandshrew", 0, 1, WEST);
	ASSERT_EQ(1, i); // c2

//	The grid:
//	  01
//	0 SS
//	1 M.

	i = d.whatObstacle(1, 0, EAST); // b
	ASSERT_EQ(-1, i); // empty space

	i = d.whatObstacle(0, 1, WEST); // c2
	ASSERT_EQ(0, i); // c1

	i = d.whatObstacle(0, 0, SOUTH); // c1
	ASSERT_EQ(2, i); // b
}

// --------------------
// Darwin::nextAction()
// --------------------

TEST(Darwin, Darwin_nextAction_hop_go){
	Species s = Species("Hopper");

	s.addInstruction("hop");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	Darwin d = Darwin();

	d.addCreature(&c);
	d.spawnCreature("Hopper", 0, 0, EAST);

	Action action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);
}

TEST(Darwin, Darwin_nextAction_hop_left_go){
	Species s = Species("Hopper");

	s.addInstruction("hop");
	s.addInstruction("left");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	Darwin d = Darwin();

	d.addCreature(&c);
	d.spawnCreature("Hopper", 0, 0, EAST);

	Action action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(LEFT, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);
}

TEST(Darwin, Darwin_nextAction_if_wall){
	Species s = Species("Hopper");

	s.addInstruction("hop");
	s.addInstruction("if_wall 3");
	s.addInstruction("go 0");
	s.addInstruction("right");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	Darwin d = Darwin(2, 4);

	d.addCreature(&c);
	d.spawnCreature("Hopper", 0, 0, EAST);

	Action action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -2);
	ASSERT_EQ(RIGHT, action);
	
	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -2);
	ASSERT_EQ(RIGHT, action);
}

TEST(Darwin, Darwin_nextAction_if_enemy){
	Species s = Species("Sandshrew");
	Species x = Species("Mudkip");

	s.addInstruction("if_enemy 3");
	s.addInstruction("hop");
	s.addInstruction("go 0");
	s.addInstruction("infect");
	s.addInstruction("go 0");

	x.addInstruction("hop");
	x.addInstruction("go 0");

	Creature c1 = Creature(&s);
	Creature c2 = Creature(&s);
	Creature b = Creature(&x);

	Darwin d = Darwin(2, 2);

	d.addCreature(&c1);
	d.addCreature(&c2);
	d.addCreature(&b);

	d.spawnCreature("Sandshrew", 0, 0, SOUTH);	// facing Mudkip
	d.spawnCreature("Sandshrew", 0, 1, WEST);
	d.spawnCreature("Mudkip", 1, 0, EAST);

	// The grid:
	//   0    1
	// 0 c1   c2
	// 1 b    .

	Action action = d.nextAction(&c1, 2);
	ASSERT_EQ(INFECT, action);

	action = d.nextAction(&c2, 0);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&b, -1);
	ASSERT_EQ(HOP, action);
}

TEST(Darwin, Darwin_nextAction_if_empty){
	Species s = Species("Lonely");

	s.addInstruction("if_empty 5");
	s.addInstruction("if_wall 3");
	s.addInstruction("go 0");
	s.addInstruction("right");		// line 3
	s.addInstruction("go 0");
	s.addInstruction("hop");		// line 5
	s.addInstruction("go 0");
	

	Creature c = Creature(&s);
	Darwin d = Darwin(2, 4);

	d.spawnCreature("Lonely", 0, 0, EAST);

	Action action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -2);
	ASSERT_EQ(RIGHT, action);
	
	action = d.nextAction(&c, -1);
	ASSERT_EQ(HOP, action);

	action = d.nextAction(&c, -2);
	ASSERT_EQ(RIGHT, action);
}

TEST(Darwin, Darwin_nextAction_if_random){
	srand(0);	// seed
	Species s = Species("Random");

	s.addInstruction("if_random 3");
	s.addInstruction("left");
	s.addInstruction("go 0");
	s.addInstruction("right");
	s.addInstruction("go 0");
	

	Creature c = Creature(&s);
	Darwin d = Darwin(2, 4);

	d.addCreature(&c);
	d.spawnCreature("Random", 0, 0, EAST);

	Action action = d.nextAction(&c, -1);
	ASSERT_EQ(RIGHT, action);

	action = d.nextAction(&c, -1);
	ASSERT_EQ(LEFT, action);
}

// --------------
// Darwin::step()
// --------------

TEST(Darwin, Darwin_step_simpleHopper){
	std::ostringstream oss;
	std::string output;
	Species s = Species("Hopper");

	s.addInstruction("hop");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	Darwin d = Darwin(2, 2, oss);

	d.addCreature(&c);
	d.spawnCreature("Hopper", 0, 0, EAST);

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 0.\n   01\n 0 H.\n 1 ..\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 1.\n   01\n 0 .H\n 1 ..\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 2.\n   01\n 0 .H\n 1 ..\n\n", output);
	oss.str("");
}

TEST(Darwin, Darwin_step_CWHopper){
	std::ostringstream oss;
	std::string output;
	Species s = Species("Hopper");

	s.addInstruction("if_wall 3");
	s.addInstruction("hop");
	s.addInstruction("go 0");
	s.addInstruction("right");
	s.addInstruction("go 0");

	Creature c = Creature(&s);
	Darwin d = Darwin(2, 2, oss);

	d.addCreature(&c);
	d.spawnCreature("Hopper", 0, 0, EAST);

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 0.\n   01\n 0 H.\n 1 ..\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 1.\n   01\n 0 .H\n 1 ..\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 2.\n   01\n 0 .H\n 1 ..\n\n", output);
	ASSERT_EQ(SOUTH, c._direction);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 3.\n   01\n 0 ..\n 1 .H\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 4.\n   01\n 0 ..\n 1 .H\n\n", output);
	ASSERT_EQ(WEST, c._direction);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 5.\n   01\n 0 ..\n 1 H.\n\n", output);
	oss.str("");
}

TEST(Darwin, Darwin_step_infection){
	std::ostringstream oss;
	std::string output;

	Species w = Species("Winner");
	Species l = Species("Loser");

	w.addInstruction("if_enemy 3");
	w.addInstruction("hop");
	w.addInstruction("go 0");
	w.addInstruction("infect");
	w.addInstruction("go 0");

	l.addInstruction("if_enemy 3");
	l.addInstruction("hop");
	l.addInstruction("go 0");
	l.addInstruction("infect");
	l.addInstruction("go 0");

	Creature c1 = Creature(&w);
	Creature c2 = Creature(&l);
	Darwin d = Darwin(2, 2, oss);

	d.addCreature(&c1);
	d.addCreature(&c2);
	d.spawnCreature("Winner", 0, 0, EAST);
	d.spawnCreature("Loser", 0, 1, WEST);

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 0.\n   01\n 0 WL\n 1 ..\n\n", output);
	oss.str("");

	d.step();
	output = oss.str();
	ASSERT_EQ("Turn = 1.\n   01\n 0 WW\n 1 ..\n\n", output);
	oss.str("");
}
