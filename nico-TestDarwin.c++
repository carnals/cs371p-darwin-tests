#include <iostream>
#include <string>
#include <cassert>

#include "gtest/gtest.h"
#include "Darwin.h"

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

    % g++ -pedantic -std=c++0x -Wall Darwin.h Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

//////////////////////////////////////////////////////////////////////
TEST(Species, string_constructor1){
using namespace std;
	Species hopper("hopper");
	assert(hopper.numInstructions() == 2);
} 

TEST(Species, string_constructor2){
using namespace std;
	Species food("food");
	assert(food.numInstructions() == 2);
}

TEST(Species, string_constructor3){
using namespace std;
	Species rover("rover");
	assert(rover.numInstructions() == 11);
}

TEST(Species, string_constructor4){
using namespace std;
	Species trap("trap");
	assert(trap.numInstructions() == 5);
}

//////////////////////////////////////////////////////////////////////
TEST(Species, add_instruction1){
using namespace std;
	Species trap("trap");
	trap.addInstruction("foo");
	assert(trap.numInstructions() == 6);
}

TEST(Species, add_instruction2){
using namespace std;
	Species food("food");
	food.addInstruction("bar");
	food.addInstruction("foo");
	assert(food.numInstructions() == 4);
}

TEST(Species, add_instruction3){
using namespace std;
	Species food("food");
	food.addInstruction("bar");
	food.addInstruction("foo");
	food.addInstruction("");
	assert(food.numInstructions() == 5);
}

TEST(Species, add_instruction4){
using namespace std;
	Species food("food");
	food.addInstruction("fdfd");
	food.addInstruction("fdfd");
	food.addInstruction("fdfd");
	assert(food.numInstructions() == 5);
}

TEST(Creature, addInstruction5){
using namespace std;
	Species rover("rover");
	rover.addInstruction("F");
	assert(rover.numInstructions() == 12);
}

//////////////////////////////////////////////////////////////////////

TEST(Species, getInstruction1){
using namespace std;
	Species food("food");
	assert(food.getInstruction(0).compare("left") == 0);
}

TEST(Species, getInstruction2){
using namespace std;
	Species food("food");
	assert(food.getInstruction(1).compare("go 0") == 0);
}

TEST(Species, getInstruction3){
using namespace std;
	Species rover("rover");
	assert(rover.getInstruction(10).compare("go 0") == 0);
}

TEST(Species, getInstruction4){
using namespace std;
	Species trap("trap");
	assert(trap.getInstruction(0).compare("if_enemy 3") == 0);
}

TEST(Species, getInstruction5){
using namespace std;
	Species hopper("hopper");
	assert(hopper.getInstruction(0).compare("hop") == 0);
}

TEST(Species, getInstruction6){
using namespace std;
	Species hopper("hopper");
	assert(hopper.getInstruction(1).compare("go 0") == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Species, numInstructions1){
using namespace std;
	Species rover("rover");
	rover.addInstruction("fdfdfd");
	assert(rover.numInstructions() == 12);
}

TEST(Species, numInstructions2){
using namespace std;
	Species food("food");
	food.addInstruction("fdfdfd");
	assert(food.numInstructions() == 3);
}

TEST(Species, numInstructions3){
using namespace std;
	Species hopper("hopper");
	hopper.addInstruction("fdfdfd");
	assert(hopper.numInstructions() == 3);
}

TEST(Species, numInstructions4){
using namespace std;
	Species hopper("hopper");
	hopper.addInstruction("fdfdfd");
	hopper.addInstruction("fdfdfd");
	assert(hopper.numInstructions() == 4);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, creature_constructor1){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	assert(hopper1.toSymbol() == 'h');
}

TEST(Creature, creature_constructor2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'z');		//mislabeling intentionaly
	assert(hopper1.toSymbol() == 'z');
}

TEST(Creature, creature_constructor3){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	assert(food1.toSymbol() == 'f');
}

TEST(Creature, creature_constructor4){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	assert(rover1.toSymbol() == 'r');
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, eligible1){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	assert(food1.eligible() == true);
}

TEST(Creature, eligible2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	assert(hopper1.eligible() == true);
}

TEST(Creature, eligible3){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	assert(rover1.eligible() == true);
}

TEST(Creature, eligible4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 0, 't');
	assert(trap1.eligible() == true);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, toggleEligible1){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.toggleEligibility();
	assert(food1.eligible() != true);
}

TEST(Creature, toggleEligible2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	hopper1.toggleEligibility();
	assert(hopper1.eligible() != true);
}

TEST(Creature, toggleEligible3){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	rover1.toggleEligibility();
	assert(rover1.eligible() != true);
}

TEST(Creature, toggleEligible4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 0, 't');
	trap1.toggleEligibility();
	assert(trap1.eligible() == false);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, nextInstruction1){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	assert(rover1.nextInstruction().compare("if_enemy 9") == 0);
}

TEST(Creature, nextInstruction2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	assert(hopper1.nextInstruction().compare("hop") == 0);
}

TEST(Creature, nextInstruction3){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	assert(food1.nextInstruction().compare("left") == 0);
}

TEST(Creature, nextInstruction4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 0, 't');
	assert(trap1.nextInstruction().compare("if_enemy 3") == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, peekInstruction1){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	assert(rover1.peekInstruction().compare("if_enemy 9") == 0);
}

TEST(Creature, peekInstruction2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	assert(hopper1.peekInstruction().compare("hop") == 0);
}

TEST(Creature, peekInstruction3){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	assert(food1.peekInstruction().compare("left") == 0);
}

TEST(Creature, peekInstruction4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 0, 't');
	assert(trap1.peekInstruction().compare("if_enemy 3") == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, modPC1){
using namespace std;
	Species food("food");
	food.addInstruction("abc");
	Creature food1(&food, 0, 'f');
	food1.modPC(2);
	assert(food1.peekInstruction().compare("abc") == 0);
}

TEST(Creature, modPC2){
using namespace std;
	Species food("food");
	food.addInstruction("abc");
	food.addInstruction("def");
	Creature food1(&food, 0, 'f');
	food1.modPC(3);
	assert(food1.peekInstruction().compare("def") == 0);
}

TEST(Creature, modPC3){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.nextInstruction();
	assert(food1.peekInstruction().compare("go 0") == 0);
	food1.modPC(0);
	assert(food1.peekInstruction().compare("left") == 0);
	
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, incrementPC1){
using namespace std;
	Species rover("rover");
	Creature rover1(&rover, 0, 'r');
	rover1.incrementPC();
	assert(rover1.peekInstruction().compare("if_empty 7") == 0);
}

TEST(Creature, incrementPC2){
using namespace std;
	Species hopper("hopper");
	Creature hopper1(&hopper, 0, 'h');
	hopper1.incrementPC();
	assert(hopper1.peekInstruction().compare("go 0") == 0);
}

TEST(Creature, incrementPC3){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.incrementPC();
	assert(food1.peekInstruction().compare("go 0") == 0);
}

TEST(Creature, incrementPC4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 0, 't');
	trap1.incrementPC();
	assert(trap1.peekInstruction().compare("left") == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, frontSpot1){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	pair<int, int> front = food1.frontSpot(0, 1);
	assert(front.first == 0 && front.second == 0);
}

TEST(Creature, frontSpot2){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'f');
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 1 && front.second == 2);
}

TEST(Creature, frontSpot3){
using namespace std;
	Species food("food");
	Creature food1(&food, 3, 'f');
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 3 && front.second == 2);
}

TEST(Creature, frontSpot4){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'f');
	pair<int, int> front = food1.frontSpot(0, 0);
	assert(front.first == -1 && front.second == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, turnLeft1){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.turnLeft();
	pair<int, int> front = food1.frontSpot(0, 1);
	assert(front.first == 1 && front.second == 1);
}

TEST(Creature, turnLeft2){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'f');
	food1.turnLeft();
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 2 && front.second == 1);
}

TEST(Creature, turnLeft3){
using namespace std;
	Species food("food");
	Creature food1(&food, 3, 'f');
	food1.turnLeft();
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 2 && front.second == 3);
}

TEST(Creature, turnLeft4){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.turnLeft();
	food1.turnLeft();
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 2 && front.second == 3);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, turnRight1){
using namespace std;
	Species food("food");
	Creature food1(&food, 0, 'f');
	food1.turnRight();
	pair<int, int> front = food1.frontSpot(1, 1);
	assert(front.first == 0 && front.second == 1);
}

TEST(Creature, turnRight2){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'f');
	food1.turnRight();
	pair<int, int> front = food1.frontSpot(2, 2);
	assert(front.first == 2 && front.second == 3);
}

TEST(Creature, turnRight3){
using namespace std;
	Species food("food");
	Creature food1(&food, 3, 'f');
	food1.turnRight();
	pair<int, int> front = food1.frontSpot(2, 1);
	assert(front.first == 2 && front.second == 0);
}

TEST(Creature, turnRight4){
using namespace std;
	Species food("food");
	Creature food1(&food, 2, 'f');
	food1.turnRight();
	food1.turnRight();
	pair<int, int> front = food1.frontSpot(2, 1);
	assert(front.first == 2 && front.second == 0);
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, getInfected1){
using namespace std;
	Species food("food");
	Species trap("trap");
	Creature food1(&food, 1, 'f');
	Creature trap1(&trap, 1, 't');
	food1.getInfected(&trap1);
	assert(food1.toSymbol() == 't');
}

TEST(Creature, getInfected2){
using namespace std;
	Species food("food");
	Species trap("trap");
	Creature food1(&food, 1, 'f');
	Creature trap1(&trap, 1, 't');
	trap1.getInfected(&food1);
	assert(trap1.toSymbol() == 'f');
}

TEST(Creature, getInfected3){
using namespace std;
	Species food("food");
	Species rover("rover");
	Creature food1(&food, 1, 'f');
	Creature rover1(&rover, 1, 'r');
	food1.getInfected(&rover1);
	assert(food1.toSymbol() == 'r');
}

TEST(Creature, getInfected4){
using namespace std;
	Species trap("trap");
	Species rover("rover");
	Creature trap1(&trap, 1, 't');
	Creature rover1(&rover, 1, 'r');
	trap1.getInfected(&rover1);
	assert(trap1.toSymbol() == 'r');
}

//////////////////////////////////////////////////////////////////////

TEST(Creature, toSymbol1){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'f');
	assert(food1.toSymbol() == 'f');
}

TEST(Creature, toSymbol2){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, 'e');
	assert(food1.toSymbol() == 'e');
}

TEST(Creature, toSymbol3){
using namespace std;
	Species food("food");
	Creature food1(&food, 1, '1');
	assert(food1.toSymbol() == '1');
}

TEST(Creature, toSymbol4){
using namespace std;
	Species trap("trap");
	Creature trap1(&trap, 1, 't');
	assert(trap1.toSymbol() == 't');
}








