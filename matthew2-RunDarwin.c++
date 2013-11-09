// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h" //const int WEST = 0, NORTH = 1, EAST = 2, SOUTH = 3;

// ----
// main
// ----

int main () {
    using namespace std;
	

    // ----
    // food
    // ----

	Species food("f");
    food.addInstruction("left");
    food.addInstruction("go 0");
	
    // ------
    // hopper
    // ------

	Species hopper("h");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	
    // -----
    // rover
    // -----
	
	Species rover("r"); 
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");
	
    // ----
    // trap
    // ----

	Species trap("t"); 
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
	 
	 
	// ----
    // best
    // ----

	Species best("b");
	best.addInstruction("if_enemy 3");
    best.addInstruction("right");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 0");
	
	// --------------------------------------
	// My Tests
	// --------------------------------------

	// ----------
    // darwin 4x45
    // ----------
	
	try {
		cout << "*** Darwin 4x45 ***" << endl;
		srand(0);
		Darwin world(4, 45);
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature f1(food, dir);
			world.addCreature(f1, pos/45, pos%45);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature h1(hopper, dir);
			world.addCreature(h1, pos/45, pos%45);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature r1(rover, dir);
			world.addCreature(r1, pos/45, pos%45);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature t1(trap, dir);
			world.addCreature(t1, pos/45, pos%45);
		}
		
		for (int i = 0; i <= 10; i++){
			cout << "Turn = " << i << "." << endl;
			world.printSelf();
			world.takeTurn();
		}
		
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
	
	
	// ----------
    // darwin 45x4
    // ----------
	
	try {
		cout << "*** Darwin 45x4 ***" << endl;
		srand(0);
		Darwin world(45, 4);
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature f1(food, dir);
			world.addCreature(f1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature h1(hopper, dir);
			world.addCreature(h1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature r1(rover, dir);
			world.addCreature(r1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 180;
			int dir = rand() % 4;
			Creature t1(trap, dir);
			world.addCreature(t1, pos/4, pos%4);
		}
		
		for (int i = 0; i <= 10; i++){
			cout << "Turn = " << i << "." << endl;
			world.printSelf();
			world.takeTurn();
		}
		
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
	
	
	// ----------
    // darwin 4x4
    // ----------
	
	try {
		cout << "*** Darwin 4x4 ***" << endl;
		srand(0);
		Darwin world(4, 4);
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 16;
			int dir = rand() % 4;
			Creature f1(food, dir);
			world.addCreature(f1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 16;
			int dir = rand() % 4;
			Creature h1(hopper, dir);
			world.addCreature(h1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 16;
			int dir = rand() % 4;
			Creature r1(rover, dir);
			world.addCreature(r1, pos/4, pos%4);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 16;
			int dir = rand() % 4;
			Creature t1(trap, dir);
			world.addCreature(t1, pos/4, pos%4);
		}
		
		for (int i = 0; i <= 10; i++){
			cout << "Turn = " << i << "." << endl;
			world.printSelf();
			world.takeTurn();
		}
		
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
	
	
	// ----------
    // darwin 13x30
    // ----------
	
	try {
		cout << "*** Darwin 13x30 ***" << endl;
		srand(0);
		Darwin world(13, 30);
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 390;
			int dir = rand() % 4;
			Creature f1(food, dir);
			world.addCreature(f1, pos/30, pos%30);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 390;
			int dir = rand() % 4;
			Creature h1(hopper, dir);
			world.addCreature(h1, pos/30, pos%30);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 390;
			int dir = rand() % 4;
			Creature r1(rover, dir);
			world.addCreature(r1, pos/30, pos%30);
		}
		
		for(int i = 0; i < 10; i++){
			int pos = rand() % 390;
			int dir = rand() % 4;
			Creature t1(trap, dir);
			world.addCreature(t1, pos/30, pos%30);
		}
		
		for (int i = 0; i <= 10; i++){
			cout << "Turn = " << i << "." << endl;
			world.printSelf();
			world.takeTurn();
		}
		
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
	
	
	// --------------------------------------
	// Others' Tests
	// --------------------------------------
	
	/*
	...
	*/
	
	
	// --------------------------------------
	// Prof. Downing's Tests
	// --------------------------------------
	
	/*
	...
	*/
	
    return 0;}