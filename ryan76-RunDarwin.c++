// --------------------
// RunDarwin.c++
// Copyright (C) 2013
// Ryan Niemann
// --------------------

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
    */
    
    Species food("f");
    food.addInstruction(ACTION, LEFT, 1);
    food.addInstruction(CONTROL, go, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper("h");
    hopper.addInstruction(ACTION, HOP, 1);
    hopper.addInstruction(CONTROL, go, 0);
    
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
    
    Species rover("r");
    rover.addInstruction(CONTROL, if_enemy, 9);
    rover.addInstruction(CONTROL, if_empty, 7);
    rover.addInstruction(CONTROL, if_random, 5);
    rover.addInstruction(ACTION, LEFT, 4);
    rover.addInstruction(CONTROL, go, 0);
    rover.addInstruction(ACTION, RIGHT, 6);
    rover.addInstruction(CONTROL, go, 0);
    rover.addInstruction(ACTION, HOP, 8);
    rover.addInstruction(CONTROL, go, 0);
    rover.addInstruction(ACTION, INFECT, 10);
    rover.addInstruction(CONTROL, go, 0);

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

    Species trap("t");
    trap.addInstruction(CONTROL, if_enemy, 3);
    trap.addInstruction(ACTION, LEFT, 2);
    trap.addInstruction(CONTROL, go, 0);
    trap.addInstruction(ACTION, INFECT, 4);
    trap.addInstruction(CONTROL, go, 0);
    
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
        
        Darwin x(8, 8);
        
        Creature f1(food, EAST);
        x.addCreature(f1, 0, 0);
        Creature h1(hopper, NORTH);
        x.addCreature(h1, 3, 3);
        Creature h2(hopper, EAST);
        x.addCreature(h2, 3, 4);
        Creature h3(hopper, SOUTH);
        x.addCreature(h3, 4, 4);
        Creature h4(hopper, WEST);
        x.addCreature(h4, 4, 3);
        Creature f2(food, NORTH);
        x.addCreature(f1, 7, 7);
        
        for (int i = 0; i <= 5; i++) {
            x.printGrid();
            x.step();
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
        
        Darwin x(7, 9);
        
        Creature t1(trap, SOUTH);
        x.addCreature(t1, 0, 0);
        Creature h1(hopper, EAST);
        x.addCreature(h1, 3, 2);
        Creature r2(rover, NORTH);
        x.addCreature(r2, 5, 4);
        Creature t2(trap, WEST);
        x.addCreature(t2, 6, 8);
        
        for (int i = 0; i <= 5; i++) {
            x.printGrid();
            x.step();
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
        
        Darwin d(72, 72);
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            Creature f1(food, direction);
            d.addCreature(f1, row, column);
        }
        
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            Creature h1(hopper, direction);
            d.addCreature(h1, row, column);
        }
        
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            Creature r1(rover, direction);
            d.addCreature(r1, row, column);
        }
        
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            Creature t1(trap, direction);
            d.addCreature(t1, row, column);
        }
        
        for (int i = 0; i < 10; i++) {
            d.printGrid();
            d.step();
        }
        
        for (int i = 10; i < 1001; i++) {
            if (i % 100 == 0) d.printGrid();
            d.step();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}