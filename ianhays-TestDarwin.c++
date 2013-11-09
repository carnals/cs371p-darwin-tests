// --------------------------------------------
// University of Texas - Austin
// CS371p: Object-Oriented Programming
// PROJECT 4: Darwin
// Ian A. Hays - IH2974
// --------------------------------------------

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

    % make TestVoting

    % valgrind TestVoting > TestVoting.out
*/
// ------------------------
// #includes
// ------------------------
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"
#include "Darwin.h"

// ------------------------------------------------
// Species Class Unit Tests
// ------------------------------------------------
// ------------------------
// Species::Species
// ------------------------
TEST(Species, Species_Constructor_1) 
{
	Species test1("some string");
	ASSERT_TRUE(test1.name == "some string");
}

TEST(Species, Species_Constructor_2) 
{
	std::string string1 = "some string";
	Species test1(string1);
	ASSERT_TRUE(test1.name == "some string");
}

TEST(Species, Species_Constructor_3) 
{
	std::string string1 = "some string";
	Species test1(string1);
	string1 = "no string!";
	ASSERT_TRUE(test1.name == "some string");
}

// ------------------------
// Species::addInstruction
// ------------------------
TEST(Species, Species_addInstruction_1) 
{
	Species test1("n");
	ASSERT_TRUE(test1.instructions.size() == 0);
}

TEST(Species, Species_addInstruction_2) 
{
	Species test1("n");
	test1.addInstruction(HOP);
	ASSERT_TRUE(test1.instructions.size() == 1);
	ASSERT_TRUE(test1.instruction_params.size() == 1);
}

TEST(Species, Species_addInstruction_3) 
{
	Species test1("n");
	test1.addInstruction(HOP);
	ASSERT_TRUE(test1.instructions[0] == HOP);
	ASSERT_TRUE(test1.instruction_params[0] == 0);
}

// ------------------------------------------------
// End of Species Class Unit Tests
// ------------------------------------------------
// ------------------------------------------------
// Creature Class Unit Tests
// ------------------------------------------------
// ------------------------
// Creature::Creature
// ------------------------
TEST(Creature, Creature_Constructor_1) 
{
	Species spec1("name");
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.facing == EAST);
	ASSERT_TRUE(test1.species == &spec1);
}

TEST(Creature, Creature_Constructor_2) 
{
	Species spec1("name");
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.species->name == "name");
}

TEST(Creature, Creature_Constructor_3) 
{
	Species spec1("name");
	Creature test1(&spec1, EAST);
	spec1.name = "name2";
	ASSERT_TRUE(test1.species->name == "name2");
}

// ------------------------
// Creature::convert
// ------------------------
TEST(Creature, Creature_convert_1) 
{
	Species spec1("spec1");
	Species spec2("spec2");
	Creature test1(&spec1, EAST);
	test1.convert(&spec2);
	ASSERT_TRUE(test1.species == &spec2);
}

// ------------------------
// Creature::nextInstruction
// ------------------------
TEST(Creature, Creature_nextInstruction_1) 
{
	Species spec1("spec1");
	Species spec2("spec2");
	spec1.addInstruction(HOP);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO, 0);
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.nextInstruction(EMPTY) == HOP);
	test1.convert(&spec1);
	ASSERT_TRUE(test1.nextInstruction(ENEMY) == HOP);
	test1.convert(&spec1);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);
	ASSERT_TRUE(test1.nextInstruction(WALL) == LEFT);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);	
}

TEST(Creature, Creature_nextInstruction_IFEMPTY_1) 
{
	Species spec1("spec1");
	spec1.addInstruction(HOP);
	spec1.addInstruction(IF_EMPTY, 0);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO, 2);
	
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);
	ASSERT_TRUE(test1.nextInstruction(EMPTY) == HOP);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == LEFT);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == LEFT);
}

TEST(Creature, Creature_nextInstruction_IFWALL_1) 
{
	Species spec1("spec1");
	spec1.addInstruction(HOP);
	spec1.addInstruction(IF_WALL, 0);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO, 2);
	
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);	
	ASSERT_TRUE(test1.nextInstruction(EMPTY) == LEFT);
}

TEST(Creature, Creature_nextInstruction_IFENEMY_1) 
{
	Species spec1("spec1");
	spec1.addInstruction(HOP);
	spec1.addInstruction(IF_ENEMY, 0);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO, 2);
	
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);
	ASSERT_TRUE(test1.nextInstruction(ENEMY) == HOP);	
	ASSERT_TRUE(test1.nextInstruction(EMPTY) == LEFT);
	ASSERT_TRUE(test1.nextInstruction(ENEMY) == LEFT);
}

TEST(Creature, Creature_nextInstruction_and_convert_1) 
{
	Species spec1("spec1");
	spec1.addInstruction(HOP);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO, 0);
	
	Species spec2("spec2");
	spec2.addInstruction(RIGHT);
	spec2.addInstruction(RIGHT);
	spec2.addInstruction(GO, 0);
	
	Creature test1(&spec1, EAST);
	ASSERT_TRUE(test1.nextInstruction(WALL) == HOP);
	ASSERT_TRUE(test1.nextInstruction(WALL) == LEFT);	
	test1.convert(&spec2);
	ASSERT_TRUE(test1.nextInstruction(WALL) == RIGHT);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == RIGHT);
	ASSERT_TRUE(test1.nextInstruction(WALL) == RIGHT);	
	ASSERT_TRUE(test1.nextInstruction(WALL) == RIGHT);	
}

// ------------------------------------------------
// End of Creature Class Unit Tests
// ------------------------------------------------
// ------------------------------------------------
// Darwin Class Unit Tests
// ------------------------------------------------
// ------------------------
// Darwin::Darwin
// ------------------------
// ------------------------
// Darwin::printGrid
// ------------------------
TEST(Darwin, Darwin_printGrid_1) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 ........\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 ........\n"  <<
					 "7 ........\n\n";
	Darwin test1(8,8);
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_printGrid_OVER10COLUMNS) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  0123456789012\n"  <<
					 "0 .............\n"  <<
					 "1 .............\n"  <<
					 "2 .............\n"  <<
					 "3 .............\n"  <<
					 "4 .............\n"  <<
					 "5 .............\n"  <<
					 "6 .............\n"  <<
					 "7 .............\n"  <<
					 "8 .............\n\n";
	Darwin test1(9,13);
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_printGrid_OVER10ROWS) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  0123456789\n"  <<
					 "0 ..........\n"  <<
					 "1 ..........\n"  <<
					 "2 ..........\n"  <<
					 "3 ..........\n"  <<
					 "4 ..........\n"  <<
					 "5 ..........\n"  <<
					 "6 ..........\n"  <<
					 "7 ..........\n"  <<
					 "8 ..........\n"  <<
					 "9 ..........\n"  <<
					 "0 ..........\n"  <<
					 "1 ..........\n"  <<
					 "2 ..........\n\n";
	Darwin test1(13,10);
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

// ------------------------
// Darwin::addCreature
// ------------------------
TEST(Darwin, Darwin_addCreature_1) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 .....n..\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 ........\n"  <<
					 "7 ........\n\n";
	Darwin test1(8,8);
	Species spec1("name");
	Creature creat1(&spec1, EAST);
	test1.addCreature(creat1, 0, 5);
	
	
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_addCreature_2) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 .....n..\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 ........\n"  <<
					 "7 ........\n\n";
	Darwin test1(8,8);
	Species spec1("name");
	Creature creat1(&spec1, EAST);
	test1.addCreature(creat1, 0, 5);
	test1.addCreature(creat1, 0, 5);
	test1.addCreature(creat1, 0, 5);
	test1.addCreature(creat1, 0, 5);
	
	
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_addCreature_3) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 o......n\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 ........\n"  <<
					 "7 o......n\n\n";
	Darwin test1(8,8);
	Species spec1("name");
	Creature creat1(&spec1, EAST);
	Species spec2("other");
	Creature creat2(&spec1, NORTH);
	Creature creat3(&spec2, WEST);
	Creature creat4(&spec2, SOUTH);
	test1.addCreature(creat1, 0, 7);
	test1.addCreature(creat2, 0, 7);
	test1.addCreature(creat2, 7, 7);
	test1.addCreature(creat3, 7, 0);
	test1.addCreature(creat4, 0, 0);
	
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

// ------------------------
// Darwin::nextTurn
// ------------------------
TEST(Darwin, Darwin_nextTurn_1) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 s......f\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 .......f\n"  <<
					 "7 s.......\n\n";
	Darwin test1(8,8);
	
	Species spec1("first");
	spec1.addInstruction(HOP);
	spec1.addInstruction(GO, 0);
	
	Creature creat1(&spec1, EAST);
	Creature creat2(&spec1, NORTH);
	
	
	
	test1.addCreature(creat1, 0, 7);
	test1.addCreature(creat2, 7, 7);
	
	
	Species spec2("second");
	spec2.addInstruction(LEFT);
	spec2.addInstruction(GO, 0);
	
	Creature creat3(&spec2, WEST);
	Creature creat4(&spec2, SOUTH);

	test1.addCreature(creat3, 7, 0);
	test1.addCreature(creat4, 0, 0);
	
	test1.nextTurn();
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_nextTurn_2) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 .......f\n"  <<
					 "1 .......f\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 ........\n"  <<
					 "5 ........\n"  <<
					 "6 ........\n"  <<
					 "7 s......s\n\n";
	Darwin test1(8,8);
	
	Species spec1("first");
	spec1.addInstruction(HOP);
	spec1.addInstruction(GO, 0);
	
	Creature creat1(&spec1, EAST);
	Creature creat2(&spec1, NORTH);
	
	
	
	test1.addCreature(creat1, 0, 7);
	test1.addCreature(creat2, 7, 7);
	
	
	Species spec2("second");
	spec2.addInstruction(HOP);
	spec2.addInstruction(GO, 0);
	
	Creature creat3(&spec2, EAST);
	Creature creat4(&spec2, SOUTH);

	test1.addCreature(creat3, 7, 0);
	test1.addCreature(creat4, 0, 0);
	for (int i = 0; i < 10; i++) test1.nextTurn();
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_nextTurn_3) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  01234567\n"  <<
					 "0 f...f..f\n"  <<
					 "1 ........\n"  <<
					 "2 ........\n"  <<
					 "3 ........\n"  <<
					 "4 .......f\n"  <<
					 "5 f.......\n"  <<
					 "6 f.......\n"  <<
					 "7 .....ff.\n\n";
	Darwin test1(8,8);
	
	Species spec1("first");
	spec1.addInstruction(HOP);
	spec1.addInstruction(IF_ENEMY,3);
	spec1.addInstruction(GO, 0);
	spec1.addInstruction(INFECT);
	spec1.addInstruction(LEFT);
	spec1.addInstruction(GO,4);
	
	Creature creat1(&spec1, EAST);
	test1.addCreature(creat1, 0, 0);
	Creature creat2(&spec1, SOUTH);
	test1.addCreature(creat2, 0, 7);	
	Creature creat3(&spec1, NORTH);
	test1.addCreature(creat3, 7, 0);
	Creature creat4(&spec1, WEST);
	test1.addCreature(creat4, 7, 7);

	Species spec2("second");
	spec2.addInstruction(LEFT);
	spec2.addInstruction(GO, 0);
	
	Creature creat5(&spec2, EAST);
	test1.addCreature(creat5, 0, 5);
	Creature creat6(&spec2, SOUTH);
	test1.addCreature(creat6, 5, 0);	
	Creature creat7(&spec2, NORTH);
	test1.addCreature(creat7, 7, 5);
	Creature creat8(&spec2, WEST);
	test1.addCreature(creat8, 5, 7);

	for (int i = 0; i < 20; i++) 
	{
		test1.nextTurn();
		//test1.printGrid(std::cout);
		//std::cout << "\n\n";
	}
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_nextTurn_FULL) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  0123\n"  <<
					 "0 ffff\n"  <<
					 "1 ffff\n"  <<
					 "2 ffff\n"  <<
					 "3 ffff\n\n";
	Darwin test1(4,4);
	
	Species spec1("first");
	spec1.addInstruction(INFECT);
	spec1.addInstruction(RIGHT);
	spec1.addInstruction(GO, 0);
	
	Creature creat0(&spec1, EAST);
	test1.addCreature(creat0, 0, 0);

	Species spec2("second");
	spec2.addInstruction(RIGHT);
	spec2.addInstruction(GO, 0);
	
	Creature creat1(&spec2, EAST);
	test1.addCreature(creat1, 0, 1);
	Creature creat2(&spec2, SOUTH);
	test1.addCreature(creat2, 0, 2);	
	Creature creat3(&spec2, NORTH);
	test1.addCreature(creat3, 0, 3);
	Creature creat4(&spec2, WEST);
	test1.addCreature(creat4, 1, 0);
	Creature creat5(&spec2, EAST);
	test1.addCreature(creat5, 1, 1);
	Creature creat6(&spec2, SOUTH);
	test1.addCreature(creat6, 1, 2);	
	Creature creat7(&spec2, NORTH);
	test1.addCreature(creat7, 1, 3);
	Creature creat8(&spec2, WEST);
	test1.addCreature(creat8, 2, 0);
	Creature creat9(&spec2, NORTH);
	test1.addCreature(creat9, 2, 1);
	Creature creat10(&spec2, NORTH);
	test1.addCreature(creat10, 2, 2);
	Creature creat11(&spec2, EAST);
	test1.addCreature(creat11, 2, 3);
	Creature creat12(&spec2, SOUTH);
	test1.addCreature(creat12, 3, 0);	
	Creature creat13(&spec2, NORTH);
	test1.addCreature(creat13, 3, 1);
	Creature creat14(&spec2, WEST);
	test1.addCreature(creat14, 3, 2);
	Creature creat15(&spec2, EAST);
	test1.addCreature(creat15, 3, 3);


	for (int i = 0; i < 10; i++) 
	{
		test1.nextTurn();
		//test1.printGrid(std::cout);
		//std::cout << "\n\n";
	}
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_nextTurn_ALMOSTEMPTY) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  0\n"  <<
					 "0 f\n\n";
	Darwin test1(1,1);
	
	Species spec1("first");
	spec1.addInstruction(HOP);
	spec1.addInstruction(GO,0);
	
	Creature creat1(&spec1, EAST);
	test1.addCreature(creat1, 0, 0);

	for (int i = 0; i < 3; i++) 
	{
		test1.nextTurn();
		//test1.printGrid(std::cout);
		//std::cout << "\n\n";
	}
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

TEST(Darwin, Darwin_nextTurn_NOCREATURES) 
{
	std::ostringstream correct_out;
	std::ostringstream test_out;

	correct_out  <<  "  0\n"  <<
					 "0 .\n\n";
	Darwin test1(1,1);
	
	for (int i = 0; i < 3; i++) 
	{
		test1.nextTurn();
		//test1.printGrid(std::cout);
		//std::cout << "\n\n";
	}
	test1.printGrid(test_out);
	ASSERT_TRUE(test_out.str() == correct_out.str());
}

// ------------------------------------------------
// End of Darwin Class Unit Tests
// ------------------------------------------------