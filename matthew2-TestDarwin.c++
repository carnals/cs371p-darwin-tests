// --------
// includes
// --------

#include <string>
#include <vector>

#include "gtest/gtest.h"

#define class struct //access private variables for testing

#include "Darwin.h" //const int WEST = 0, NORTH = 1, EAST = 2, SOUTH = 3;

using namespace std;

// -------
// Species
// -------

//constructor
TEST(Darwin, species_constructor_trap){
	Species trap("t");
	ASSERT_TRUE(trap.symbol == "t");
	ASSERT_TRUE(trap.program.size() == 0);
}

TEST(Darwin, species_constructor_best){
	Species best("b");
	ASSERT_TRUE(best.symbol == "b");
	ASSERT_TRUE(best.program.size() == 0);
}

TEST(Darwin, species_constructor_blank){
	Species blank(".");
	ASSERT_TRUE(blank.symbol == ".");
	ASSERT_TRUE(blank.program.size() == 0);
}

//addInstruction
TEST(Darwin, species_addInstruction_single){
	Species test("t");
	test.addInstruction("hop");
	ASSERT_TRUE(test.program.size() == 1);
	ASSERT_TRUE(test.program[0] == "hop");
}

TEST(Darwin, species_addInstruction_double){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("go 0");
	ASSERT_TRUE(test.program.size() == 2);
	ASSERT_TRUE(test.program[0] == "hop");
	ASSERT_TRUE(test.program[1] == "go 0");
}

TEST(Darwin, species_addInstruction_triple){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("go 0");
	test.addInstruction("infect");
	ASSERT_TRUE(test.program.size() == 3);
	ASSERT_TRUE(test.program[0] == "hop");
	ASSERT_TRUE(test.program[1] == "go 0");
	ASSERT_TRUE(test.program[2] == "infect");
}

//getInstruction
TEST(Darwin, species_getInstruction_single){
	Species test("t");
	test.addInstruction("hop");
	ASSERT_TRUE(test.getInstruction(0) == "hop");
	ASSERT_TRUE(test.program.size() == 1);
}

TEST(Darwin, species_getInstruction_double){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("go 0");
	ASSERT_TRUE(test.getInstruction(0) == "hop");
	ASSERT_TRUE(test.getInstruction(1) == "go 0");
	ASSERT_TRUE(test.program.size() == 2);
}

TEST(Darwin, species_getInstruction_triple){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("infect");
	test.addInstruction("go 0");
	ASSERT_TRUE(test.getInstruction(0) == "hop");
	ASSERT_TRUE(test.getInstruction(2) == "go 0");
	ASSERT_TRUE(test.getInstruction(1) == "infect");
	ASSERT_TRUE(test.program.size() == 3);
}

//indexAfter
TEST(Darwin, species_indexAfter_single){
	Species test("t");
	test.addInstruction("hop");
	ASSERT_TRUE(test.indexAfter(0) == 0);
}

TEST(Darwin, species_indexAfter_double){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("go 0");
	ASSERT_TRUE(test.indexAfter(0) == 1);
	ASSERT_TRUE(test.indexAfter(1) == 0);
}

TEST(Darwin, species_indexAfter_triple){
	Species test("t");
	test.addInstruction("hop");
	test.addInstruction("infect");
	test.addInstruction("go 0");
	ASSERT_TRUE(test.indexAfter(0) == 1);
	ASSERT_TRUE(test.indexAfter(1) == 2);
	ASSERT_TRUE(test.indexAfter(2) == 0);
}

//isEmpty
TEST(Darwin, species_isEmpty_empty){
	Species test(".");
	ASSERT_TRUE(test.isEmpty());
}

TEST(Darwin, species_isEmpty_notEmpty){
	Species test("b");
	ASSERT_TRUE(!test.isEmpty());
}

TEST(Darwin, species_isEmpty_notEmpty2){
	Species test("t");
	test.addInstruction("hop");
	ASSERT_TRUE(!test.isEmpty());
}

//operator!=
TEST(Darwin, species_ne_emptyAndNotEmpty){
	Species blank(".");
	Species test("t");
	ASSERT_TRUE(blank != test);
}

TEST(Darwin, species_ne_same){
	Species blank(".");
	Species blank2(".");
	ASSERT_TRUE(!(blank != blank2));
}

TEST(Darwin, species_ne_differentSpecies){
	Species test("t");
	Species test2("b");
	ASSERT_TRUE(test != test2);
}


//---------
// Creature
//---------

//constructor
TEST(Darwin, creature_constructor_hopper){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	ASSERT_TRUE(h1.species.symbol == "h");
	ASSERT_TRUE(h1.species.program.size() == 2);
	ASSERT_TRUE(h1.direction == EAST);
	ASSERT_TRUE(h1.pc == 0);
}

TEST(Darwin, creature_constructor_food){
	Species food("f");
    food.addInstruction("left");
    food.addInstruction("go 0");
	
	Creature f1(food, NORTH);
	ASSERT_TRUE(f1.species.symbol == "f");
	ASSERT_TRUE(f1.species.program.size() == 2);
	ASSERT_TRUE(f1.direction == NORTH);
	ASSERT_TRUE(f1.pc == 0);
}

TEST(Darwin, creature_constructor_blank){
	Species blank(".");
	
	Creature b1(blank, NORTH);
	ASSERT_TRUE(b1.species.symbol == ".");
	ASSERT_TRUE(b1.species.program.size() == 0);
	ASSERT_TRUE(b1.pc == 0);
}

//nextInstruction
TEST(Darwin, creature_nextInstruction_hopper){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	ASSERT_TRUE(h1.nextInstruction() == "hop");
	ASSERT_TRUE(h1.nextInstruction() == "go 0");
	ASSERT_TRUE(h1.nextInstruction() == "hop");
}

TEST(Darwin, creature_nextInstruction_food){
	Species food("f");
    food.addInstruction("left");
    food.addInstruction("go 0");
	
	Creature f1(food, NORTH);
	ASSERT_TRUE(f1.nextInstruction() == "left");
	ASSERT_TRUE(f1.nextInstruction() == "go 0");
	ASSERT_TRUE(f1.nextInstruction() == "left");
}

TEST(Darwin, creature_nextInstruction_trap){
	Species trap("t");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
	
	Creature t1(trap, NORTH);
	ASSERT_TRUE(t1.nextInstruction() == "if_enemy 3");
	ASSERT_TRUE(t1.nextInstruction() == "left");
	ASSERT_TRUE(t1.nextInstruction() == "go 0");
	ASSERT_TRUE(t1.nextInstruction() == "infect");
	ASSERT_TRUE(t1.nextInstruction() == "go 0");
	ASSERT_TRUE(t1.nextInstruction() == "if_enemy 3");
}

//go
TEST(Darwin, creature_go_hopper){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	
	ASSERT_TRUE(h1.pc == 0);
	h1.go(1);
	ASSERT_TRUE(h1.pc == 1);
}

TEST(Darwin, creature_go_food){
	Species food("f");
    food.addInstruction("left");
    food.addInstruction("go 0");
	
	Creature f1(food, EAST);
	
	ASSERT_TRUE(f1.pc == 0);
	f1.go(1);
	ASSERT_TRUE(f1.pc == 1);
}

TEST(Darwin, creature_go_trap){
	Species trap("t");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
	
	Creature t1(trap, EAST);
	
	ASSERT_TRUE(t1.pc == 0);
	t1.go(1);
	ASSERT_TRUE(t1.pc == 1);
	t1.go(3);
	ASSERT_TRUE(t1.pc == 3);
	t1.go(0);
	ASSERT_TRUE(t1.pc == 0);
}

//hasMovedThisTurn
TEST(Darwin, creature_hasMovedThisTurn_oneInstruction){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	
	ASSERT_TRUE(!h1.hasMovedThisTurn());
	h1.nextInstruction();
	ASSERT_TRUE(h1.hasMovedThisTurn());
}

TEST(Darwin, creature_hasMovedThisTurn_manyInstructions){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	
	ASSERT_TRUE(!h1.hasMovedThisTurn());
	h1.nextInstruction();
	h1.nextInstruction();
	h1.nextInstruction();
	h1.nextInstruction();
	h1.go(0);
	h1.go(1);
	ASSERT_TRUE(h1.hasMovedThisTurn());
}

//allowMovement
TEST(Darwin, creature_allowMovement_allow){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	
	h1.allowMovement();
	ASSERT_TRUE(!h1.hasMovedThisTurn());
}

TEST(Darwin, creature_allowMovement_allowAfterPreviousMovement){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
	Creature h1(hopper, EAST);
	
	h1.nextInstruction();
	ASSERT_TRUE(h1.hasMovedThisTurn());
	h1.allowMovement();
	ASSERT_TRUE(!h1.hasMovedThisTurn());
}

//isEmpty
TEST(Darwin, creature_isEmpty_empty){
	Species blank(".");
	
	Creature b1(blank, EAST);

	ASSERT_TRUE(b1.isEmpty());
}

TEST(Darwin, creature_isEmpty_notEmpty){
	Species test("t");
	
	Creature t1(test, EAST);

	ASSERT_TRUE(!t1.isEmpty());
}

//turnLeft
TEST(Darwin, creature_turnLeft_fromEast){
	Species test("t");
	
	Creature t1(test, EAST);
	
	ASSERT_TRUE(t1.direction == EAST);
	t1.turnLeft();
	ASSERT_TRUE(t1.direction == NORTH);
}

TEST(Darwin, creature_turnLeft_fromNorth){
	Species test("t");
	
	Creature t1(test, NORTH);
	
	ASSERT_TRUE(t1.direction == NORTH);
	t1.turnLeft();
	ASSERT_TRUE(t1.direction == WEST);
}

TEST(Darwin, creature_turnLeft_fromWest){
	Species test("t");
	
	Creature t1(test, WEST);
	
	ASSERT_TRUE(t1.direction == WEST);
	t1.turnLeft();
	ASSERT_TRUE(t1.direction == SOUTH);
}

TEST(Darwin, creature_turnLeft_fromSouth){
	Species test("t");
	
	Creature t1(test, SOUTH);
	
	ASSERT_TRUE(t1.direction == SOUTH);
	t1.turnLeft();
	ASSERT_TRUE(t1.direction == EAST);
}

//turnRight
TEST(Darwin, creature_turnRight_fromEast){
	Species test("t");
	
	Creature t1(test, EAST);
	
	ASSERT_TRUE(t1.direction == EAST);
	t1.turnRight();
	ASSERT_TRUE(t1.direction == SOUTH);
}

TEST(Darwin, creature_turnRight_fromNorth){
	Species test("t");
	
	Creature t1(test, NORTH);
	
	ASSERT_TRUE(t1.direction == NORTH);
	t1.turnRight();
	ASSERT_TRUE(t1.direction == EAST);
}

TEST(Darwin, creature_turnRight_fromWest){
	Species test("t");
	
	Creature t1(test, WEST);
	
	ASSERT_TRUE(t1.direction == WEST);
	t1.turnRight();
	ASSERT_TRUE(t1.direction == NORTH);
}

TEST(Darwin, creature_turnRight_fromSouth){
	Species test("t");
	
	Creature t1(test, SOUTH);
	
	ASSERT_TRUE(t1.direction == SOUTH);
	t1.turnRight();
	ASSERT_TRUE(t1.direction == WEST);
}

//isFacing
TEST(Darwin, creature_isFacing_East){
	Species test("t");
	
	Creature t1(test, EAST);
	
	ASSERT_TRUE(t1.isFacing(EAST));
}

TEST(Darwin, creature_isFacing_North){
	Species test("t");
	
	Creature t1(test, NORTH);
	
	ASSERT_TRUE(t1.isFacing(NORTH));
}

TEST(Darwin, creature_isFacing_West){
	Species test("t");
	
	Creature t1(test, WEST);
	
	ASSERT_TRUE(t1.isFacing(WEST));
}

TEST(Darwin, creature_isFacing_South){
	Species test("t");
	
	Creature t1(test, SOUTH);
	
	ASSERT_TRUE(t1.isFacing(SOUTH));
}

//remove
TEST(Darwin, creature_remove_blank){
	Species blank(".");
	
	Creature b1(blank, SOUTH);
	
	b1.remove();
	ASSERT_TRUE(b1.pc == 0);
	ASSERT_TRUE(b1.species.symbol == ".");
	ASSERT_TRUE(b1.species.program.size() == 0);
}

TEST(Darwin, creature_remove_food){
	Species food("f");
	food.addInstruction("left");
    food.addInstruction("go 0");
	
	Creature f1(food, SOUTH);
	
	f1.remove();
	ASSERT_TRUE(f1.pc == 0);
	ASSERT_TRUE(f1.species.symbol == ".");
	ASSERT_TRUE(f1.species.program.size() == 0);
}

//turnInto
TEST(Darwin, creature_turnInto_hopperToTrap){
	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	Species trap("t"); 
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
	
	Creature h1(hopper, NORTH);
	Creature t1(trap, SOUTH);
	
	h1.turnInto(t1);
	
	ASSERT_TRUE(h1.pc == 0);
	ASSERT_TRUE(h1.species.symbol == "t");
	ASSERT_TRUE(h1.species.program.size() == 5);
	ASSERT_TRUE(h1.isFacing(NORTH));
}

//operator!=
TEST(Darwin, creature_ne_emptyAndNotEmpty){
	Species blank(".");
	Species test("t");
	test.addInstruction("hop");
	
	Creature b1(blank, SOUTH);
	Creature t1(test, SOUTH);
	
	ASSERT_TRUE(b1 != t1);
}

TEST(Darwin, creature_ne_same){
	Species blank(".");
	Creature b1(blank, SOUTH);
	Creature b2(blank, SOUTH);
	
	ASSERT_TRUE(!(b1 != b2));
}

TEST(Darwin, creature_ne_differentSpecies){
	Species test1("p");
	Species test2("t");
	test2.addInstruction("hop");
	
	Creature p1(test1, SOUTH);
	Creature t1(test2, SOUTH);
	
	ASSERT_TRUE(p1 != t1);
}

//-------
// Darwin
//-------

//constructor
TEST(Darwin, darwin_constructor_1x1){
	Darwin world(1,1);
	ASSERT_TRUE(world.rows == 1);
	ASSERT_TRUE(world.cols == 1);
	ASSERT_TRUE(world.grid.size() == 1);
	ASSERT_TRUE(world.grid[0].size() == 1);
}

TEST(Darwin, darwin_constructor_8x8){
	Darwin world(8,8);
	ASSERT_TRUE(world.rows == 8);
	ASSERT_TRUE(world.cols == 8);
	ASSERT_TRUE(world.grid.size() == 8);
	ASSERT_TRUE(world.grid[0].size() == 8);
	ASSERT_TRUE(world.grid[7].size() == 8);
}

TEST(Darwin, darwin_constructor_4x98){
	Darwin world(4,98);
	ASSERT_TRUE(world.rows == 4);
	ASSERT_TRUE(world.cols == 98);
	ASSERT_TRUE(world.grid.size() == 4);
	ASSERT_TRUE(world.grid[0].size() == 98);
	ASSERT_TRUE(world.grid[3].size() == 98);
}

//addCreature
TEST(Darwin, darwin_addCreature_1x1){
	Species test("t");
	Creature t1(test, NORTH);
	
	Darwin world(1,1);
	world.addCreature(t1, 0, 0);
	ASSERT_TRUE(world.grid[0][0].direction == NORTH);
	ASSERT_TRUE(world.grid[0][0].species.symbol == "t");
}

TEST(Darwin, darwin_addCreature_2x2){
	Species test("t");
	Creature t1(test, NORTH);
	
	Darwin world(2,2);
	world.addCreature(t1, 1, 0);
	ASSERT_TRUE(world.grid[1][0].direction == NORTH);
	ASSERT_TRUE(world.grid[1][0].species.symbol == "t");
}

TEST(Darwin, darwin_addCreature_4x98){
	Species test("p");
	Creature t1(test, SOUTH);
	
	Darwin world(4,98);
	world.addCreature(t1, 2, 50);
	ASSERT_TRUE(world.grid[2][50].direction == SOUTH);
	ASSERT_TRUE(world.grid[2][50].species.symbol == "p");
}

TEST(Darwin, darwin_addCreature_1x1_conflict){
	Species test("t");
	Creature t1(test, NORTH);
	
	Species bob("b");
	Creature b1(bob, EAST);
	
	Darwin world(1,1);
	world.addCreature(t1, 0, 0);
	world.addCreature(b1, 0, 0);
	ASSERT_TRUE(world.grid[0][0].direction == NORTH);
	ASSERT_TRUE(world.grid[0][0].species.symbol == "t");
}




