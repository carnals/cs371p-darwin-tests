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

// -----------
// 
// -----------
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

TEST(Darwin, Darwin_printGrid1){
	std::ostringstream oss;
	std::string output;
	Darwin d = Darwin(2, 2, oss);

	ASSERT_EQ(2, d._length);
	ASSERT_EQ(2, d._width);
	ASSERT_EQ(&oss, &d._outStream);

	d.printGrid();
	output = oss.str();

	ASSERT_EQ("  01\n0 ..\n1 ..\n", output);
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

	ASSERT_EQ("  0123\n0 ....\n1 ....\n", output);
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

	ASSERT_EQ("  01\n0 ..\n1 ..\n2 ..\n3 ..\n", output);
}

TEST(Darwin, Darwin_addSpecies1){
	Species s = Species("Thingie");
	Darwin d = Darwin();

	d.addSpecies(&s);

	ASSERT_EQ(1, d._speciesCol.size());
	ASSERT_EQ(&s, d._speciesCol["Thingie"]);

	ASSERT_EQ("Thingie", d._speciesCol["Thingie"]->_name);
}

TEST(Darwin, Darwin_addSpecies2){
	Species s1 = Species("Thing1");
	Species s2 = Species("Thing2");
	Darwin d = Darwin();

	d.addSpecies(&s1);
	d.addSpecies(&s2);

	ASSERT_EQ(2, d._speciesCol.size());
	ASSERT_EQ(&s1, d._speciesCol["Thing1"]);
	ASSERT_EQ(&s2, d._speciesCol["Thing2"]);


	ASSERT_EQ("Thing1", d._speciesCol["Thing1"]->_name);
	ASSERT_EQ("Thing2", d._speciesCol["Thing2"]->_name);
}

TEST(Darwin, Darwin_addSpecies3){
	Species s1 = Species("Fox");
	Species s2 = Species("Chicken");
	Species s3 = Species("Seeds");
	Darwin d = Darwin();

	d.addSpecies(&s1);
	d.addSpecies(&s2);
	d.addSpecies(&s3);

	ASSERT_EQ(3, d._speciesCol.size());
	ASSERT_EQ(&s1, d._speciesCol["Fox"]);
	ASSERT_EQ(&s2, d._speciesCol["Chicken"]);
	ASSERT_EQ(&s3, d._speciesCol["Seeds"]);

	ASSERT_EQ("Fox", d._speciesCol["Fox"]->_name);
	ASSERT_EQ("Chicken", d._speciesCol["Chicken"]->_name);
	ASSERT_EQ("Seeds", d._speciesCol["Seeds"]->_name);
}

TEST(Darwin, Darwin_addCreature){
	Species s = Species("Pikachu");
	Creature c = Creature(&s);
	Darwin d = Darwin();

	d.addSpecies(&s);
	ASSERT_EQ(1, d._speciesCol.size());
	ASSERT_EQ(&s, d._speciesCol["Pikachu"]);


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

	d.addSpecies(&s);
	ASSERT_EQ(1, d._speciesCol.size());
	ASSERT_EQ(&s, d._speciesCol["Tomato"]);


	d.addCreature(&c1);
	d.addCreature(&c2);

	ASSERT_EQ(2, d._actors.size());
	ASSERT_EQ(&c1, d._actors[0]);
	ASSERT_EQ(&c2, d._actors[1]);
	ASSERT_NE(d._actors[0], d._actors[1]);

	ASSERT_EQ(&s, d._actors[0]->_species);
	ASSERT_EQ(&s, d._actors[1]->_species);
}
