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
#include <vector>

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

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

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

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    // --------------------
    // darwin 50x50 crowded
    // --------------------

    try {
        cout << "*** Darwin 50x50 crowded ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2500 (50x50), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        20 Food
        20 Hopper
        20 Rover
        20 Trap
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */

        int turns = 1000;

        int gRows = 50;
        int gCols = 50;
        int gSize = gRows * gCols;
        Darwin grid(gRows, gCols);

        int       cPos;
        int       cRow;
        int       cCol;
        direction cDir;
        int       cNum      = 20;
        Species*  cTypes[]  = {&food, &hopper, &rover, &trap};
        int       cNumTypes = sizeof(cTypes) / sizeof(Species*);
        Creature creatures[10][20];

        for(int i = 0; i < cNumTypes; i++) {
            for(int j = 0; j < cNum; j++) {

                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;

                switch(rand() % 4) {
                    case 0:
                        cDir = WEST;
                    case 1:
                        cDir = NORTH;
                    case 2:
                        cDir = EAST;
                    case 3:
                        cDir = SOUTH;
                }
                
                creatures[i][j] = Creature(cTypes[i], cDir);
                grid.addCreature(creatures[i][j], cRow, cCol);
            }
        }
        grid.simulate(turns);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x50 bottleneck
    // ------------

    try {
        cout << "*** Darwin 10x50 bottleneck ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2500 (50x50), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */

        int       cPos;
        int       cRow;
        int       cCol;
        direction cDir;
        int       cNum       = 10;
        Species*  cTypes[]   = {&food, &hopper, &rover, &trap};
        int       cTypesSize = sizeof(cTypes) / sizeof(Species*);
        Creature creatures[10][20];

        int      gRows      = 10;
        int      gCols      = 50;
        int      gSize      = gRows * gCols;
        Darwin grid(gRows, gCols);

        int turns = 500;

        for(int i = 0; i < cTypesSize; i++) {
            for(int j = 0; j < cNum; j++) {
                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;

                switch(rand() % 4) {
                    case 0:
                        cDir = WEST;
                    case 1:
                        cDir = NORTH;
                    case 2:
                        cDir = EAST;
                    case 3:
                        cDir = SOUTH;
                }
                
                creatures[i][j] = Creature(cTypes[i], cDir);
                grid.addCreature(creatures[i][j], cRow, cCol);
            }
        }
        grid.simulate(turns);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10 traps v rovers
    // ------------

    try {
        cout << "*** Darwin 10x10 traps v rovers ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 100 (10x10), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Rover
        10 Trap
        Simulate 10 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        */

        int       cPos;
        int       cRow;
        int       cCol;
        direction cDir;
        int       cNum       = 10;
        Species*  cTypes[]   = {&rover, &trap};
        int       cTypesSize = sizeof(cTypes) / sizeof(Species*);
        Creature creatures[10][20];

        int      gRows      = 10;
        int      gCols      = 10;
        int      gSize      = gRows * gCols;
        Darwin grid(gRows, gCols);

        int turns = 10;

        for(int i = 0; i < cTypesSize; i++) {
            for(int j = 0; j < cNum; j++) {
                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;

                switch(rand() % 4) {
                    case 0:
                        cDir = WEST;
                    case 1:
                        cDir = NORTH;
                    case 2:
                        cDir = EAST;
                    case 3:
                        cDir = SOUTH;
                }
                
                creatures[i][j] = Creature(cTypes[i], cDir);
                grid.addCreature(creatures[i][j], cRow, cCol);
            }
        }
        grid.simulate(turns);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10 99 foods, 1 trap
    // ------------

    try {
        cout << "*** Darwin 10x10 99 foods, 1 trap ***" << endl;
        srand(0);
        /*
        Fill the grid with food, except for the middle (5, 5) being a trap 
        Call rand(), mod it with 4 and use that for their directions with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Simulate 10 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        */

        direction cDir;
        Creature creatures[10][10];
        Darwin grid(10, 10);

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                switch(rand() % 4) {
                    case 0:
                        cDir = WEST;
                    case 1:
                        cDir = NORTH;
                    case 2:
                        cDir = EAST;
                    case 3:
                        cDir = SOUTH;
                }
                if(i == 5 && j == 5)
                    creatures[i][j] = Creature(&trap, cDir);
                else
                    creatures[i][j] = Creature(&food, cDir);
                grid.addCreature(creatures[i][j], i, j);
            }
        }
            
        grid.simulate(10);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 1x20
    // ------------

    try {
        cout << "*** Darwin 1x20 2 hoppers, 1 row ***" << endl;
        /*
        Put a hopper at each end of a 1-row grid and see what happens.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        */

        Darwin grid(1, 20);

        Creature hopper1(&hopper, EAST);
        grid.addCreature(hopper1, 0, 0);

        Creature hopper2(&hopper, WEST);
        grid.addCreature(hopper2, 0, 19);
            
        grid.simulate(10);

        }
        catch (const invalid_argument&) {
        assert(false);}
        catch (const out_of_range&) {
        assert(false);}

    // -------------------------------
    // darwin 20x20 rover ball of doom
    // -------------------------------

    try {
        cout << "*** Darwin 20x20 rover ball of doom ***" << endl;
        srand(0);
        
        /*
        Fill the edges of the grid with traps 
        Make a 9x9 square of rovers at (6,6)  
        Call rand(), mod it with 4 and use that for the rovers' directions with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Simulate 100 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print the 100th grid
        */

        Darwin grid(20, 20);

        direction cDir;
        Creature creatures[2][81];

        int rCount = 0;
        int tCount = 0;

        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 20; j++) {
                switch(rand() % 4) {
                    case 0:
                        cDir = WEST;
                    case 1:
                        cDir = NORTH;
                    case 2:
                        cDir = EAST;
                    case 3:
                        cDir = SOUTH;
                }
                if(i == 0 || i == 19 || j == 0 || j == 19) {
                    creatures[0][tCount] = Creature(&trap, cDir);
                    grid.addCreature(creatures[0][tCount++], i, j);
                } else if (i >= 6 && i < 15 && j >= 6 && j < 15) {
                    creatures[1][rCount] = Creature(&rover, cDir);
                    grid.addCreature(creatures[1][rCount++], i, j);
                }
            }
        }
            
        grid.simulate(100);

        }
        catch (const invalid_argument&) {
        assert(false);}
        catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 5x10 GLADIATOR
    // ------------

    try {
        cout << "*** Darwin 5x10 Gladiatorial Arena ***" << endl;
        /*
        Put a hopper at each end of a 1-row grid and see what happens.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        */

        Darwin grid(5, 10);

        Creature hopper1(&hopper, EAST);
        grid.addCreature(hopper1, 0, 0);

        Creature hopper2(&hopper, EAST);
        grid.addCreature(hopper2, 1, 0);

        Creature hopper3(&hopper, EAST);
        grid.addCreature(hopper3, 2, 0);

        Creature hopper4(&hopper, EAST);
        grid.addCreature(hopper4, 3, 0);

        Creature hopper5(&hopper, EAST);
        grid.addCreature(hopper5, 4, 0);

        Creature rover1(&rover, WEST);
        grid.addCreature(rover1, 0, 9);

        Creature rover2(&rover, WEST);
        grid.addCreature(rover2, 1, 9);

        Creature rover3(&rover, WEST);
        grid.addCreature(rover3, 2, 9);

        Creature rover4(&rover, WEST);
        grid.addCreature(rover4, 3, 9);

        Creature rover5(&rover, WEST);
        grid.addCreature(rover5, 4, 9);
            
        grid.simulate(10);

        }
        catch (const invalid_argument&) {
        assert(false);}
        catch (const out_of_range&) {
        assert(false);}
    
    return 0;}
