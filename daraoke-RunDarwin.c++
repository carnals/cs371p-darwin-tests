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
// --------
	*/
	
	Species food('f');
	food.add_instruction(ACTION, LEFT, 0);
	food.add_instruction(CONTROL, GO, 0);
	// ------
	// hopper
	// ------

	/*
	 0: hop
	 1: go 0
	*/
	Species hopper('h');
	hopper.add_instruction(ACTION, HOP, 0);
	hopper.add_instruction(CONTROL, GO, 0);
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
	 7: hop
	 6: go 0
	 8: go 0
	 9: infect
	10: go 0
	*/
	Species rover('r');
	rover.add_instruction(CONTROL, IF_ENEMY, 9);
	rover.add_instruction(CONTROL, IF_EMPTY, 7);
	rover.add_instruction(CONTROL, IF_RANDOM, 5);
	rover.add_instruction(ACTION, LEFT, 0);
	rover.add_instruction(CONTROL, GO, 0);
	rover.add_instruction(ACTION, RIGHT, 0);
	rover.add_instruction(CONTROL, GO, 0);
	rover.add_instruction(ACTION, HOP, 0);
	rover.add_instruction(CONTROL, GO, 0);
	rover.add_instruction(ACTION, INFECT, 0);
	rover.add_instruction(CONTROL, GO, 0);
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
	trap.add_instruction(CONTROL, IF_ENEMY, 3);
	trap.add_instruction(ACTION, LEFT, 0);
	trap.add_instruction(CONTROL, GO, 0);
	trap.add_instruction(ACTION, INFECT, 0);
	trap.add_instruction(CONTROL, GO, 0);
	
	// ----
	// best
	// ----
	Species best('b');
	best.add_instruction(CONTROL, IF_ENEMY, 6);
	best.add_instruction(CONTROL, IF_RANDOM, 5);
	best.add_instruction(ACTION, HOP);
	best.add_instruction(CONTROL, GO, 0);
	best.add_instruction(ACTION, LEFT);
	best.add_instruction(CONTROL, GO, 0);
	best.add_instruction(ACTION, INFECT);
	best.add_instruction(CONTROL, GO, 0);

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
		
		DarwinWorld world1(8, 8);
		world1.add_creature(food, EAST, 0, 0);
		world1.add_creature(hopper, NORTH, 3, 3);
		world1.add_creature(hopper, EAST, 3, 4);
		world1.add_creature(hopper, SOUTH, 4, 4);
		world1.add_creature(hopper, WEST, 4, 3);
		world1.add_creature(food, NORTH, 7, 7);
	
		for (int i = 0; i < 5; i++) {
			world1.print_grid();
			world1.step();
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
		srand(0);

		/*
		7x9 Darwin
		Trap,   facing south, at (0, 0)
		Hopper, facing east,  at (3, 2)
		Rover,  facing north, at (5, 4)
		Trap,   facing west,  at (6, 8)
		Simulate 5 moves.
		Print every grid.
		*/
	
		DarwinWorld world2(7, 9);
		world2.add_creature(trap, SOUTH, 0, 0);
		world2.add_creature(hopper, EAST, 3, 2);
		world2.add_creature(rover, NORTH, 5, 4);
		world2.add_creature(trap, WEST, 6, 8);

		for (int i = 0; i < 6; i++) {
			world2.print_grid();
			world2.step();
		}
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
    
    
    // ----------
	// darwin 10x15
	// ----------
    
	try {
		cout << "*** Darwin 10x15 ***" << endl;
		srand(0);
        
		/*
         10x15 Darwin
         Trap,   facing south, at (0, 0)
         Hopper, facing east,  at (3, 2)
         Rover,  facing north, at (5, 4)
         Trap,   facing north, at (9,11)
         Food,   facing west,  at (8,8)
         Rover,  facing east,  at (2,10)
         Hopper, facing south, at (1, 3)
         Trap,   facing west,  at (6, 8)
         Simulate 5 moves.
         Print every grid.
         */
        
		DarwinWorld world3(10, 15);
		world3.add_creature(trap, SOUTH, 0, 0);
		world3.add_creature(hopper, EAST, 3, 2);
		world3.add_creature(rover, NORTH, 5, 4);
        world3.add_creature(trap, NORTH, 9, 11);
        world3.add_creature(food, WEST, 8,8);
        world3.add_creature(rover, EAST, 2, 10);
        world3.add_creature(hopper, SOUTH, 1, 3);
		world3.add_creature(trap, WEST, 6, 8);
        
		for (int i = 0; i < 20; i++) {
			if (i % 5 == 0) world3.print_grid();
			world3.step();
		}
    }
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
    
    // ----------
	// darwin 10x10
    // ALL FOUR CORNERS
	// ----------
    
	try {
		cout << "*** Darwin 10x10 ***" << endl;
		srand(0);
        
		/*
         10x10 Darwin
         Trap,   facing north, at (0, 0)
         Hopper, facing west,  at (9, 0)
         Rover,  facing north, at (0, 9)
         Trap,   facing south, at (9, 9)
         Simulate 5 moves.
         Print every grid.
         */
        
		DarwinWorld world4(10, 10);
		world4.add_creature(trap, NORTH, 0, 0);
		world4.add_creature(hopper, WEST, 9, 0);
		world4.add_creature(rover, NORTH, 0, 9);
        world4.add_creature(trap, SOUTH, 9, 9);

        
		for (int i = 0; i < 6; i++) {
			world4.print_grid();
			world4.step();
		}
    }
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
    
    // ----------
	// darwin 2x2
    // TRAP TAKEOVER
	// ----------
    
	try {
		cout << "*** Darwin 2x2 ***" << endl;
		srand(0);
        
		/*
         2x2 Darwin
         Trap,   facing south, at (0, 0)
         Hopper, facing west,  at (0, 1)
         Rover,  facing north, at (1, 0)
         Trap,   facing west, at  (1,1)
         Simulate 5 moves.
         Print every grid.
         */
        
		DarwinWorld world5(2, 2);
		world5.add_creature(trap, SOUTH, 0, 0);
		world5.add_creature(hopper, WEST, 0, 1);
		world5.add_creature(rover, NORTH, 1, 0);
		world5.add_creature(trap, WEST, 1, 1);

        
		for (int i = 0; i < 5; i++) {
			world5.print_grid();
			world5.step();
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
		Print the first 10 grids		  (i.e. 0, 1, 2...9).
		Print every 100th grid after that (i.e. 100, 200, 300...1000).
		*/
    
        DarwinWorld world6(72, 72);
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world6.add_creature(food, dir, x, y);
        }
        
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world6.add_creature(hopper, dir, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world6.add_creature(rover, dir, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world6.add_creature(trap, dir, x, y);
        }
        
	for (int i = 0; i < 10; i++) {
	world6.print_grid();
	world6.step();
	}
	
	for (int i = 10; i < 1001; i++) {
	if (i % 100 == 0) world6.print_grid();
	world6.step();
	}
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------
	// darwin 72x72
	// with best
	// ------------

	try {
		cout << "*** Darwin 72x72 with Best ***" << endl;
		srand(0);
		/*
		Randomly place the following creatures facing randomly.
		Call rand(), mod it with 5184 (72x72), and use that for the position
		in a row-major order grid.
		Call rand() again, mod it with 4 and use that for it's direction with
		the ordering: 0:west, 1:north, 2:east, 3:south.
		Do that for each kind of creature.
		10 Food
		10 Hopper
		10 Rover
		10 Trap
		10 Best
		Simulate 1000 moves.
		Best MUST outnumber ALL other species for the bonus pts.
		Print the first 10 grids		  (i.e. 0, 1, 2...9).
		Print every 100th grid after that (i.e. 100, 200, 300...1000).
		*/
		
	DarwinWorld world7(72, 72);
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world7.add_creature(food, dir, x, y);
        }
        
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world7.add_creature(hopper, dir, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world7.add_creature(rover, dir, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world7.add_creature(trap, dir, x, y);
        }
        for (int i = 0; i < 10; i++) {
            int dir = rand() % 4;
            int pos = rand() % 5184;
	    int x = pos % 72;
	    int y = pos / 72;
	    world7.add_creature(best, dir, x, y);
        }
        
	for (int i = 0; i < 10; i++) {
	world7.print_grid();
	world7.step();
	}
	
	for (int i = 10; i < 1001; i++) {
	if (i % 100 == 0) {world7.print_grid();}
	world7.step();
	}
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	return 0;}

