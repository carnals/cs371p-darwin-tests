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
#include "Darwin.h"

// helper function to generate random creature
void generateRandomValues(int rows, int cols, int&r, int&c, int&d){
	int val = rand() % (rows * cols);
	r = val / cols;
	c = val % cols;
	d = rand() % 4;
}

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
		Species food('f');
		food.addInstruction(lft);
		food.addInstruction(go, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
		Species hopper('h');
		hopper.addInstruction(hop);
		hopper.addInstruction(go, 0);

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

		Species rover('r');
		rover.addInstruction(if_enemy, 9);
		rover.addInstruction(if_empty, 7);
		rover.addInstruction(if_random, 5);
		rover.addInstruction(lft);
		rover.addInstruction(go, 0);
		rover.addInstruction(rgt);
		rover.addInstruction(go, 0);
		rover.addInstruction(hop);
		rover.addInstruction(go, 0);
		rover.addInstruction(infect);
		rover.addInstruction(go, 0);

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

		Species trap('t');
		trap.addInstruction(if_enemy, 3);
		trap.addInstruction(lft);
		trap.addInstruction(go, 0);
		trap.addInstruction(infect);
		trap.addInstruction(go, 0);


    // -----
    // best (removed)
    // -----
    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
				// 0 west 1 north 2 east 3 south
				Darwin x(8, 8);
				Creature f1(food, 2);
				Creature h1(hopper, 1);
				Creature h2(hopper, 2);
				Creature h3(hopper, 3);
				Creature h4(hopper, 0);
				Creature f2(food, 1);
				x.addCreature(f1, 0, 0);
				x.addCreature(h1, 3, 3);
				x.addCreature(h2, 3, 4);
				x.addCreature(h3, 4, 4);
				x.addCreature(h4, 4, 3);
				x.addCreature(f2, 7, 7);
				x.print();		
				for (int i = 0; i < 5; i++){
					x.runTurn();
					x.print();
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
       /* 
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
				Darwin x(7, 9);
				Creature t1(trap, 3);
				Creature h1(hopper, 2);
				Creature r1(rover, 1);
				Creature t2(trap, 0);
				x.addCreature(t1, 0, 0);
				x.addCreature(h1, 3, 2);
				x.addCreature(r1, 5, 4);
				x.addCreature(t2, 6, 8);
      	x.print();
				for (int i = 0; i < 5; i++){
					x.runTurn();
					x.print();
				} 
			 }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
       
				/*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
	
				Species a[]= {food, hopper, rover, trap};
				Darwin d(72, 72);
				int r = 0;
				int c = 0;
				int dir = 0;
				for (int i = 0; i < 4; i++){
					for (int j = 0; j < 10; j++){	
						generateRandomValues(72, 72, r, c, dir);
						Creature x(a[i], dir);
						d.addCreature(x, r, c);
					}
				}
				d.print();
				for (int i = 1; i <= 1000; i++){
					d.runTurn();
					if ((i < 10) || (i % 100 == 0)) 
						d.print();	
				}
    }
		catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best (removed)
    // ------------

    // ------------
    // Rover 1x1
    // ------------

    try {
        cout << "*** Rover 1x1 ***" << endl;
        srand(0);
				/*	
				1x1 Darwin
				Rover, facing north at (0, 0)
				Simulate 10 moves
				Print every move
				*/
				Darwin d(1, 1);
				Creature c = Creature(rover, 1);
				d.addCreature(c, 0, 0);
				d.print();
				for (int i = 1; i <= 10; i++){
					d.runTurn();
					d.print();	
    		}
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------------------
    // Full Grid, 1 Trap 20x20
    // -------------------------

    try {
        cout << "*** Full Grid, 1 Trap 20x20 ***" << endl;
        srand(0);
				/*	
				20x20 Darwin
				1 Trap, facing west at (10, 10)
				399 Food, facing north at each location except (10, 10)
				Simulate 50 moves
				Print first 10 moves and every multiple of 10
				*/
				Darwin d(20, 20);
				Creature t(trap, 0);
				d.addCreature(t, 10, 10);
				for (int i = 0; i < 20; i++){
					for (int j = 0; j < 20; j++){
						if (!(i == 10 && j == 10)){
							Creature x(food, 1);
							d.addCreature(x, i, j);
						}
					}
				}
				d.print();
				for (int i = 1; i <= 50; i++){
					d.runTurn();
					if ((i < 10) || (i % 10 == 0)) 
						d.print();	
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------------
    // Hopper Collide 10x4
    // ------------------

    try {
        cout << "*** Hopper Collide 10x4 ***" << endl;
        srand(0);
				/*	
				10x4 Darwin
				4 Hoppers, facing south in each column of row 0
				4 Hoppers, facing north in each column of row 9
				Simulate 10 moves
				Print every move
				*/
				Darwin d(10, 4);
				Creature c1(hopper, 3);
				Creature c2(hopper, 3);
				Creature c3(hopper, 3);
				Creature c4(hopper, 3);
				Creature c5(hopper, 1);
				Creature c6(hopper, 1);
				Creature c7(hopper, 1);
				Creature c8(hopper, 1);
				d.addCreature(c1, 0, 0);
				d.addCreature(c2, 0, 1);
				d.addCreature(c3, 0, 2);
				d.addCreature(c4, 0, 3);
				d.addCreature(c5, 9, 0);
				d.addCreature(c6, 9, 1);
				d.addCreature(c7, 9, 2);
				d.addCreature(c8, 9, 3);
				d.print();
				for (int i = 1; i <= 10; i++){
					d.runTurn();
					d.print();
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------------
    // Rover Takeover 8x8
    // ------------------

    try {
        cout << "*** Rover Takeover 8x8 ***" << endl;
        srand(0);
				/*	
				8x8 Darwin
				Rover, facing south at (3, 4)
				Food, facing south at (0, 2)
				Food, facing south at (7, 4)
				Food, facing south at (2, 7)
				Food, facing north at (3, 0)
				Food, facing north at (4, 5)
				Food, facing north at (5, 2)
				Food, facing north at (6, 3)
				Simulate 100 moves
				Print first 10 moves and multiples of 10
				*/
				Darwin d(8, 8);
				Creature c1(rover, 3);
				Creature c2(food, 3);
				Creature c3(food, 3);
				Creature c4(food, 3);
				Creature c5(food, 1);
				Creature c6(food, 1);
				Creature c7(food, 1);
				Creature c8(food, 1);
				d.addCreature(c1, 3, 4);
				d.addCreature(c2, 0, 2);
				d.addCreature(c3, 7, 4);
				d.addCreature(c4, 2, 7);
				d.addCreature(c5, 3, 0);
				d.addCreature(c6, 4, 5);
				d.addCreature(c7, 5, 2);
				d.addCreature(c8, 6, 3);
				d.print();
				for (int i = 1; i <= 100; i++){
					d.runTurn();
					if (i < 10 || i % 10 == 0)
						d.print();
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hop Down 10x1
    // ------------------

    try {
        cout << "*** Hop Down 10x1 ***" << endl;
        srand(0);
				/*	
				10x1 Darwin
				Hopper, facing south at (0, 0)
				Simulate 9 moves
				Print every move
				*/
				Darwin d(10, 1);
				Creature c1(hopper, 3);
				d.addCreature(c1, 0, 0);
				d.print();
				for (int i = 1; i <= 9; i++){
					d.runTurn();
					d.print();
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hoppers Trapped 4x4
    // ------------------

    try {
        cout << "*** Hoppers Trapped 4x4 ***" << endl;
        srand(0);
				/*	
				4x4 Darwin
				Hopper, facing east at (0, 0)
				Hopper, facing south at (0, 1)
				Hopper, facing west at (1, 1)
				Hopper, facing north at (1, 0)
				Simulate 10
				Print every move
				*/
				Darwin d(4, 4);
				Creature c1(hopper, 2);
				Creature c2(hopper, 3);
				Creature c3(hopper, 0);
				Creature c4(hopper, 1);
				d.addCreature(c1, 0, 0);
				d.addCreature(c2, 0, 1);
				d.addCreature(c3, 1, 1);
				d.addCreature(c4, 1, 0);
				d.print();
				for (int i = 1; i <= 10; i++){
					d.runTurn();
					d.print();
				}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
	return 0;}
