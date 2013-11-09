#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Darwin.h"
#include "stdexcept"
// -----------
// TestDarwin
// -----------

// ----
// read
// ----

TEST(Darwin, ifWall1) {
	Grid world = Grid(10,10);
	bool b = world.ifWall(0,0,NORTH);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifWall2) {
    Grid world = Grid(10,10);
    bool b = world.ifWall(0,0,SOUTH);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifWall3) {
    Grid world = Grid(10,10);
    bool b = world.ifWall(5,5, EAST);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifWall4) {
    Grid world = Grid(10,10);
    bool b = world.ifWall(9,9,SOUTH);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifWall5) {
    Grid world = Grid(1,1);
    bool b = world.ifWall(0,0,EAST);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifWall6) {
    Grid world = Grid(1,1);
    bool b = world.ifWall(0,0,WEST);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifEmpty01) {
    Grid world = Grid(10,10);
    bool b = world.ifEmpty(0,0,NORTH);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEmpty02) {
    Grid world = Grid(10,10);
    bool b = world.ifEmpty(0,0,SOUTH);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifEmpty03) {
    Grid world = Grid(10,10);
    bool b = world.ifEmpty(5,5, EAST);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifEmpty04) {
    Grid world = Grid(10,10);
    bool b = world.ifEmpty(9,9,SOUTH);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEmpty05) {
    Grid world = Grid(1,1);
    bool b = world.ifEmpty(0,0,EAST);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy1) {
	Grid world = Grid(10,10);
	Species joe  = Species("joe");
	Species phil = Species("phil");
	world.addCreature(joe,0,0,EAST);
	world.addCreature(phil,0,1,WEST);
	bool b = world.ifEnemy(0,0,EAST,joe);
	ASSERT_TRUE(b);
}

TEST(Darwin, ifEnemy2) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,1,WEST,phil);
    ASSERT_TRUE(b);
}

TEST(Darwin, ifEnemy3) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,0,WEST,joe);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy4) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,0,EAST,phil);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy5) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,0,SOUTH,joe);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy6) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(joe,0,1,WEST);
    bool b = world.ifEnemy(0,0,EAST,joe);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy7) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,1,WEST,joe);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy8) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species empty = Species("empty");
    world.addCreature(joe,0,0,EAST);
    bool b = world.ifEnemy(1,1,NORTH,empty);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy9) {
    Grid world = Grid(10,10);
    Species empty = Species("empty");
	bool b = world.ifEnemy(0,0,EAST,empty);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy10) {
    Grid world = Grid(10,10);
    Species empty  = Species("empty");
    bool b = world.ifEnemy(0,0,NORTH,empty);
    ASSERT_TRUE(!b);
}

TEST(Darwin, ifEnemy11) {
    Grid world = Grid(10,10);
    Species joe  = Species("joe");
    Species phil = Species("phil");
    world.addCreature(joe,0,0,EAST);
    world.addCreature(phil,0,1,WEST);
    bool b = world.ifEnemy(0,0,WEST,joe);
    ASSERT_TRUE(!b);
}

TEST(Darwin, Grid1) {
	try{
		Grid world = Grid(-1,10);
	}
	catch(const invalid_argument&){
		return;
	}
	ASSERT_TRUE(false);
}

TEST(Darwin, Grid2) {
    try{
        Grid world = Grid(10,-1);
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, Grid3) {
    try{
        Grid world = Grid(-1,-1);
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, Grid4) {
    try{
        Grid world = Grid(10,1000);
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, Grid5) {
    try{
        Grid world = Grid(1000,10);
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, Grid6) {
    try{
        Grid world = Grid(10,10);
    }   
    catch(const invalid_argument&){
        ASSERT_TRUE(false);
    }   
}

TEST(Darwin, addCreature1) {
    try{
		Species joe = Species("joe");
        Grid world = Grid(10,10);
		world.addCreature(joe, 0,0,(Direction)4);
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature2) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, 0,0,(Direction)(-1));
    }   
    catch(const invalid_argument&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature3) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, -1,0,NORTH);
    }   
    catch(const out_of_range&){
        return;
    }   
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature4) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, -1,0,NORTH);
    }
    catch(const out_of_range&){
        return;
    }
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature5) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, 0,-1,NORTH);
    }
    catch(const out_of_range&){
        return;
    }
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature6) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, 10,0,NORTH);
    }
    catch(const out_of_range&){
        return;
    }
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature7) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, 0,10,NORTH);
    }
    catch(const out_of_range&){
        return;
    }
    ASSERT_TRUE(false);
}

TEST(Darwin, addCreature8) {
    try{
        Species joe = Species("joe");
        Grid world = Grid(10,10);
        world.addCreature(joe, 0,0,NORTH);
    }
    catch(...){
	    ASSERT_TRUE(false);
	}
}

TEST(Darwin, instructionAt2) {
	Species joe = Species("joe");
	joe.addInstruction("hop");
	joe.addInstruction("go 0");
	ASSERT_TRUE(joe.instructionAt(1) == "go 0");
}

TEST(Darwin, instructionAt3) {
    Species joe = Species("joe");
    joe.addInstruction("hop");
    joe.addInstruction("go 0");
	try{
		joe.instructionAt(-1);
	}
	catch(const out_of_range&) {
		return;
	}
    ASSERT_TRUE(false);
}

TEST(Darwin, instructionAt4) {
    Species joe = Species("joe");
    joe.addInstruction("hop");
    joe.addInstruction("go 0");
    try{
        joe.instructionAt(2);
    }
    catch(const out_of_range&) {
        return;
    }
    ASSERT_TRUE(false);
}



TEST(Darwin, turnTaken1) {
    Species hopper = Species("hopper");
    Creature hop1 = Creature(hopper, 0, 0, EAST, 0);
    ASSERT_TRUE(hop1.turnTaken() == false);
}

TEST(Darwin, turnTaken2) {
    Species rover = Species("rover");
    Creature hop1 = Creature(rover, 0, 0, EAST, 0);
    
    ASSERT_TRUE(hop1.turnTaken() == false);
}

TEST(Darwin, turnTaken3) {
    Species hopper = Species("hopper");
    Creature hop1 = Creature(hopper, 0, 0, EAST, 0);
 
    hop1.newTurn();
    ASSERT_TRUE(hop1.turnTaken() == false);
}

TEST(Darwin, turnTaken4) {
    Species trap = Species("trap");
    Creature hop1 = Creature(trap, 0, 0, EAST, 0);
 
    hop1.newTurn();
    ASSERT_TRUE(hop1.turnTaken() == false);
}

TEST(Darwin, isEnemy1) {
    Species hopper = Species("hopper");
    ASSERT_TRUE(hopper.isEnemy(hopper) == false);
}

TEST(Darwin, isEnemy2) {
    Species hopper = Species("hopper");
    Species trap = Species("trap");
    ASSERT_TRUE(hopper.isEnemy(trap) == true);
}

TEST(Darwin, isEnemy3) {
    Species hopper = Species("hopper");
    Species food = Species("food");
    ASSERT_TRUE(hopper.isEnemy(food) == true);
}

TEST(Darwin, isEnemy4) {
    Species hopper = Species("hopper");
    Species empty = Species("empty");
    ASSERT_TRUE(hopper.isEnemy(empty) == false);
}

TEST(Darwin, isEnemy5) {
    Species hopper = Species("hopper");
    Species rover = Species("rover");
    ASSERT_TRUE(hopper.isEnemy(rover) == true);
}

TEST(Darwin, isEnemy6) {
    Species trap = Species("trap");
    ASSERT_TRUE(trap.isEnemy(trap) == false);
}

TEST(Darwin, isEnemy7) {
    Species trap = Species("trap");
    Species hopper = Species("hopper");
    ASSERT_TRUE(trap.isEnemy(hopper) == true);
}

TEST(Darwin, isEnemy8) {
    Species trap = Species("trap");
    Species food = Species("food");
    ASSERT_TRUE(trap.isEnemy(food) == true);
}

TEST(Darwin, isEnemy9) {
    Species trap = Species("trap");
    Species empty = Species("empty");
    ASSERT_TRUE(trap.isEnemy(empty) == false);
}

TEST(Darwin, isEnemy10) {
    Species trap = Species("trap");
    Species rover = Species("rover");
    ASSERT_TRUE(trap.isEnemy(rover) == true);
}

TEST(Darwin, isEnemy11) {
    Species rover = Species("rover");
    ASSERT_TRUE(rover.isEnemy(rover) == false);
}

TEST(Darwin, isEnemy12) {
    Species rover = Species("rover");
    Species trap = Species("trap");
    ASSERT_TRUE(rover.isEnemy(trap) == true);
}

TEST(Darwin, isEnemy13) {
    Species rover = Species("rover");
    Species food = Species("food");
    ASSERT_TRUE(rover.isEnemy(food) == true);
}

TEST(Darwin, isEnemy14) {
    Species rover = Species("rover");
    Species empty = Species("empty");
    ASSERT_TRUE(rover.isEnemy(empty) == false);
}

TEST(Darwin, isEnemy15) {
    Species rover = Species("rover");
    Species hopper = Species("hopper");
    ASSERT_TRUE(rover.isEnemy(hopper) == true);
}

TEST(Darwin, isEnemy16) {
    Species food = Species("food");
    ASSERT_TRUE(food.isEnemy(food) == false);
}

TEST(Darwin, isEnemy17) {
    Species food = Species("food");
    Species trap = Species("trap");
    ASSERT_TRUE(food.isEnemy(trap) == true);
}

TEST(Darwin, isEnemy18) {
    Species food = Species("food");
    Species rover = Species("rover");
    ASSERT_TRUE(food.isEnemy(rover) == true);
}

TEST(Darwin, isEnemy19) {
    Species food = Species("food");
    Species empty = Species("empty");
    ASSERT_TRUE(food.isEnemy(empty) == false);
}

TEST(Darwin, isEnemy20) {
    Species food = Species("food");
    Species hopper = Species("hopper");
    ASSERT_TRUE(food.isEnemy(hopper) == true);
}

TEST(Darwin, isEnemy21) {
    Species empty = Species("empty");
    ASSERT_TRUE(empty.isEnemy(empty) == false);
}

TEST(Darwin, isEnemy22) {
    Species empty = Species("empty");
    Species trap = Species("trap");
    ASSERT_TRUE(empty.isEnemy(trap) == false);
}

TEST(Darwin, isEnemy23) {
    Species empty = Species("empty");
    Species food = Species("food");
    ASSERT_TRUE(empty.isEnemy(food) == false);
}

TEST(Darwin, isEnemy24) {
    Species empty = Species("empty");
    Species hopper = Species("hopper");
    ASSERT_TRUE(empty.isEnemy(hopper) == false);
}

TEST(Darwin, isEnemy25) {
    Species empty = Species("empty");
    Species rover = Species("rover");
    ASSERT_TRUE(empty.isEnemy(rover) == false);
}

TEST(Darwin, isEmpty27) {
    Species empty = Species("empty");
    ASSERT_TRUE(empty.isEmpty() == true);
}

TEST(Darwin, isEmpty28) {
    Species food = Species("food");
    ASSERT_TRUE(food.isEmpty() == false);
}

TEST(Darwin, isEmpty29) {
    Species rover = Species("rover");
    ASSERT_TRUE(rover.isEmpty() == false);
}

TEST(Darwin, isEmpty30) {
    Species hopper = Species("hopper");
    ASSERT_TRUE(hopper.isEmpty() == false);
}

TEST(Darwin, isEmpty31) {
    Species trap = Species("trap");
    ASSERT_TRUE(trap.isEmpty() == false);
}

TEST(Darwin, ifEmpty1) {
    Grid world = Grid(8,8);
    ASSERT_TRUE(world.ifEmpty(0,0,EAST) == true);
}

TEST(Darwin, ifEmpty2) {
    Grid world = Grid(8,8);
    Species trap = Species("trap");
    world.addCreature(trap,0,0,EAST);
    ASSERT_TRUE(world.ifEmpty(0,1,WEST) == false);
}

TEST(Darwin, ifEmpty3) {
    Grid world = Grid(8,8);
    Species hopper = Species("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    world.addCreature(hopper,0,0,EAST);
    world.takeTurn();
    ASSERT_TRUE(world.ifEmpty(0,1,WEST) == true);
}

TEST(Darwin, ifEmpty4) {
    Grid world = Grid(8,8);
    Species food = Species("food");
    food.addInstruction("left");
    food.addInstruction("go 0");
    world.addCreature(food,0,0,EAST);
    world.takeTurn();
    ASSERT_TRUE(world.ifEmpty(0,1,WEST) == false);
}

TEST(Darwin, ifEmpty5) {
    Grid world = Grid(8,8);
    Species trap = Species("trap");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
    world.addCreature(trap,0,0,EAST);
    world.takeTurn();
    ASSERT_TRUE(world.ifEmpty(0,1,WEST) == false);
}