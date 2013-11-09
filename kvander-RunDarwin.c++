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
    EXTRACT_ALL = YES
    EXTRACT_PRIVATE = YES
    EXTRACT_STATIC = YES
    GENERATE_LATEX = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

int randomPos (int row, int col) {
    int pos = rand() % (row * col);
    return pos;
}

Direction randomDir () {
    int dir = rand() % 4;
    Direction d;
    if      (dir == 0) d = NORTH;
    else if (dir == 1) d = SOUTH;
    else if (dir == 2) d = EAST;
    else               d = WEST;
    return d;
}
// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    Species food = Species(FOOD);
    
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    // ------
    // hopper
    // ------

    Species hopper = Species(HOPPER);

    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    // -----
    // rover
    // -----

    Species rover = Species(ROVER);

    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    // ----
    // trap
    // ----

    Species trap = Species(TRAP);

    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    // ----
    // best
    // ----

    Species best = Species(BEST);

    best.addInstruction(IF_ENEMY, 10);
    best.addInstruction(IF_WALL, 12);
    best.addInstruction(IF_EMPTY, 6);
    best.addInstruction(IF_RANDOM, 8);
    best.addInstruction(LEFT);
    best.addInstruction(GO, 0);
    best.addInstruction(HOP);
    best.addInstruction(GO, 0);
    best.addInstruction(RIGHT);
    best.addInstruction(GO, 0);
    best.addInstruction(INFECT);
    best.addInstruction(GO, 3);
    best.addInstruction(IF_RANDOM, 15);
    best.addInstruction(RIGHT);
    best.addInstruction(GO, 0);
    best.addInstruction(LEFT);
    best.addInstruction(IF_ENEMY, 10);
    best.addInstruction(LEFT);
    best.addInstruction(GO, 0);
    
    // ----------
    // darwin 8x8
    // ----------

    try {
        /*
        8x8 Darwin
        Food, facing east, at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east, at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west, at (4, 3)
        Food, facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** Darwin 8x8 ***" << endl;
        Creature f1 = Creature(food);
        Creature f2 = Creature(food);
        Creature h1 = Creature(hopper);
        Creature h2 = Creature(hopper);
        Creature h3 = Creature(hopper);
        Creature h4 = Creature(hopper);

        int n = 5;
        Grid g = Grid(8, 8);
        g.add(f1, EAST, 0, 0);
        g.add(h1, NORTH, 3, 3);
        g.add(h2, EAST, 3, 4);
        g.add(h3, SOUTH, 4, 4);
        g.add(h4, WEST, 4, 3);
        g.add(f2, NORTH, 7, 7);
        g.simulate(n);
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
        Trap, facing south, at (0, 0)
        Hopper, facing east, at (3, 2)
        Rover, facing north, at (5, 4)
        Trap, facing west, at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Creature t1 = Creature(trap);
        Creature h1 = Creature(hopper);
        Creature r1 = Creature(rover);
        Creature t2 = Creature(trap);
        
        int n = 5;
        Grid g = Grid(7, 9);
        g.add(t1, SOUTH, 0, 0);
        g.add(h1, EAST, 3, 2);
        g.add(r1, NORTH, 5, 4);
        g.add(t2, WEST, 6, 8);
        g.simulate(n);
        
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
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int pos;
        Direction dir;
        Grid g = Grid(72, 72);
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(food), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(hopper), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(rover), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(trap), dir, pos / 72, pos % 72);
        }
        g.simulateLarge();
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
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int pos;
        Direction dir;
        Grid g = Grid(72, 72);
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(food), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(hopper), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(rover), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(trap), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(best), dir, pos / 72, pos % 72);
        }
        g.simulateLarge();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3***" << endl;
        srand(0);
        /*
        10x10 Darwin
        Rover, facing south, at (2, 0)
        Trap, facing north, at (2, 2)
        Simulate 10 moves.
        Print every grid.
        */
        Creature r = Creature(rover);
        Creature t = Creature(trap);
        
        Grid g = Grid(3, 3);
        g.add(r, SOUTH, 2, 0);
        g.add(t, NORTH, 2, 2);
        g.simulate(10);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // with best
    // ----------

    try {
        cout << "*** Darwin 3x3 with Best ***" << endl;
        srand(0);
        /*
        10x10 Darwin
        Rover, facing south, at (2, 0)
        Best, facing north, at (2, 2)
        Simulate 10 moves.
        Print every grid.
        */
        Creature r = Creature(rover);
        Creature b = Creature(best);
        
        Grid g = Grid(3, 3);
        g.add(r, SOUTH, 2, 0);
        g.add(b, NORTH, 2, 2);
        g.simulate(10);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10
    // ------------

    try {
        cout << "*** Darwin 10x10***" << endl;
        srand(0);
        /*
        10x10 Darwin
        Trap, facing south, at (0, 0)
        Hopper, facing east, at (3, 2)
        Rover, facing north, at (5, 4)
        Trap, facing west, at (6, 8)
        Simulate 10 moves.
        Print every grid.
        */
        Creature t1 = Creature(trap);
        Creature h1 = Creature(hopper);
        Creature r1 = Creature(rover);
        Creature t2 = Creature(trap);
        
        Grid g = Grid(10, 10);
        g.add(t1, SOUTH, 0, 0);
        g.add(h1, EAST, 3, 2);
        g.add(r1, NORTH, 5, 4);
        g.add(t2, WEST, 7, 9);
        g.simulate(10);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------
    // darwin 10x10
    // with best
    // ------------

    try {
        cout << "*** Darwin 10x10 with Best***" << endl;
        srand(0);
        /*
        10x10 Darwin
        Trap, facing south, at (0, 0)
        Best, facing west, at (1, 3)
        Hopper, facing east, at (3, 2)
        Rover, facing north, at (5, 4)
        Trap, facing west, at (6, 8)
        Best, facing south, at (4, 1)
        Simulate 10 moves.
        Print every grid.
        */
        Creature t1 = Creature(trap);
        Creature b1 = Creature(best);
        Creature h1 = Creature(hopper);
        Creature r1 = Creature(rover);
        Creature t2 = Creature(trap);
        Creature b2  = Creature(best);
        
        Grid g = Grid(10, 10);
        g.add(t1, SOUTH, 0, 0);
        g.add(b1, WEST, 1, 3);
        g.add(h1, EAST, 3, 2);
        g.add(r1, NORTH, 5, 4);
        g.add(t2, WEST, 7, 9);
        g.add(b2, SOUTH, 4, 1);
        g.simulate(10);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------
    // darwin 72x72
    // ------------

    try {
        cout << "*** Darwin 72x72 ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        20 Rover
        20 Trap
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int pos;
        Direction dir;
        Grid g = Grid(72, 72);
        for (int i = 0; i < 20; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(rover), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 20; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(trap), dir, pos / 72, pos % 72);
        }
        g.simulateLarge();
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
        20 Rover
        10 Trap
        20 Best

        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int pos;
        Direction dir;
        Grid g = Grid(72, 72);
        for (int i = 0; i < 20; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(rover), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 10; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(trap), dir, pos / 72, pos % 72);
        }
        for (int i = 0; i < 20; ++i) {
            pos = randomPos(72, 72);
            dir = randomDir(); 
            g.add(Creature(best), dir, pos / 72, pos % 72);
        }
        g.simulateLarge();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}

    