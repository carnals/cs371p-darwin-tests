
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
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO);

    // ------
    // hopper
    // ------
     Species hopper("hopper");
     hopper.addInstruction(HOP);
     hopper.addInstruction(GO);

    // -----
    // rover
    // -----
     Species rover("rover");
     rover.addInstruction(IFENEMY, 9);
     rover.addInstruction(IFEMPTY, 7);
     rover.addInstruction(IFRAND, 5);
     rover.addInstruction(LEFT);
     rover.addInstruction(GO);
     rover.addInstruction(RIGHT);
     rover.addInstruction(GO);
     rover.addInstruction(HOP);
     rover.addInstruction(GO);
     rover.addInstruction(INFECT);
     rover.addInstruction(GO);
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

    // ----
    // trap
    // ----
    Species trap("trap");
    trap.addInstruction(IFENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO);
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----
    // best
    // ----
    Species corner("corner");


    /*
     0: if_wall 6
     1: if_enemy 4
     2: hop
     3: go 0
     4: infect
     5: go 0
     6: left
     7: if_wall 10
     8: if_enemy 11
     9: if_empty 13
     10: go 15
     11: infect
     12: go 7
     13: hop
     14: go 7
     15: left
     16: if_enemy 21
     17: left
     18: if_enemy 23
     19: right
     20: go 16
     21: infect
     22: go 16
     23: infect
     24: go 18
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin world(8, 8);
        world.addCreature(0, 0, EAST, food);
        world.addCreature(3, 3, NORTH, hopper);
        world.addCreature(3, 4, EAST, hopper);
        world.addCreature(4, 4, SOUTH, hopper);
        world.addCreature(4, 3, WEST, hopper);
        world.addCreature(7, 7, NORTH, food);
        world.printWorld(cout);

        for (int i = 0; i < 5; i++) {
            world.update();
            world.printWorld(cout);
        }
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
        Darwin world (7, 9);
        world.addCreature(0, 0, SOUTH, trap);
        world.addCreature(3, 2, EAST, hopper);
        world.addCreature(5, 4, NORTH, rover);
        world.addCreature(6, 8, WEST, trap);

        world.printWorld(cout);
        for (int i = 0; i < 5; i++) {
            world.update();
            world.printWorld(cout);
        }
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
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
        Darwin world(72, 72);
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, food);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, hopper);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, rover);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, trap);
        }
        world.printWorld(cout);
        for (int i = 0; i < 1000; i++) {
            world.update();
            if (i < 9 || i % 100 == 99) {
                world.printWorld(cout);
            }
        }
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
        Darwin world(72, 72);
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, food);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, hopper);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, rover);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, trap);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%5184;
            world.addCreature(r/72, r%72, rand()%4+1, corner);
        }
        world.printWorld(cout);
        for (int i = 0; i < 1000; i++) {
            world.update();
            if (i < 9 || i % 100 == 99) {
                world.printWorld(cout);
            }
        }
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
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
         /*
        1x10 Darwin
        Hopper,   facing east, at (0, 0)
        Trap, facing east,  at (0, 5)
        Rover,  facing WEST, at (0, 9)
        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** KVWADETEST1 1x10 ***" << endl;
        srand(0);
        Darwin world (1, 10);
        world.addCreature(0, 0, EAST, hopper);
        world.addCreature(0, 5, EAST, trap);
        world.addCreature(0, 9, WEST, rover);

        world.printWorld(cout);
        for (int i = 0; i < 5; i++) {
            world.update();
            world.printWorld(cout);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    try {
         /*
        10x1 Darwin
        Hopper,   facing south, at (0, 0)
        Trap, facing east,  at (5, 0)
        Rover,  facing north, at (0, 9)
        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** KVWADETEST2 10x1 ***" << endl;
        srand(0);
        Darwin world (10, 1);
        world.addCreature(0, 0, SOUTH, hopper);
        world.addCreature(5, 0, EAST, trap);
        world.addCreature(9, 0, NORTH, rover);

        world.printWorld(cout);
        for (int i = 0; i < 5; i++) {
            world.update();
            world.printWorld(cout);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        /*
        1x1 Darwin 
        Rover at 0,0 facing south
        simulate 2 moves
        print every grid
        */
        cout << "*** KVWADETEST3 1x1 ***" << endl;
        srand(0);
        Darwin world (1, 1);
        world.addCreature(0, 0, SOUTH, rover);

        world.printWorld(cout);
        for (int i = 0; i < 2; i++) {
            world.update();
            world.printWorld(cout);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** KVWADETEST4 30x30 ***" << endl;
         /*
        30x30 Darwin
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 900 (30x30), and use that for the position
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
        srand(0);
        int rows = 30;
        Darwin world(rows, rows);
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, food);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, hopper);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, rover);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, trap);
        }
        world.printWorld(cout);
        for (int i = 0; i < 1000; i++) {
            world.update();
            if (i < 9 || i % 100 == 99) {
                world.printWorld(cout);
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    try {
        cout << "*** KVWADETEST5 30x30 ***" << endl;
         /*
        30x30 Darwin
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 900 (30x30), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Rover
        10 2Rover
        (2Rover is a different species from rover but has an identical program to Rover
            2Rover's symbol in the grid is '2')
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        srand(0);
        Species rover2("2rover");
        rover2.addInstruction(IFENEMY, 9);
        rover2.addInstruction(IFEMPTY, 7);
        rover2.addInstruction(IFRAND, 5);
        rover2.addInstruction(LEFT);
        rover2.addInstruction(GO);
        rover2.addInstruction(RIGHT);
        rover2.addInstruction(GO);
        rover2.addInstruction(HOP);
        rover2.addInstruction(GO);
        rover2.addInstruction(INFECT);
        rover2.addInstruction(GO);
        int rows = 30;
        Darwin world(rows, rows);
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, rover);
        }
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, rover2);
        }
        world.printWorld(cout);
        for (int i = 0; i < 1000; i++) {
            world.update();
            if (i < 9 || i % 100 == 99) {
                world.printWorld(cout);
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

     try {
        cout << "*** KVWADETEST6 100x100 ***" << endl;
         /*
        30x30 Darwin
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 10000 (100x100), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        25 Food
        25 Hopper
        25 Rover
        25 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        srand(0);
        int rows = 100;
        Darwin world(rows, rows);
        for (int i = 0; i < 25; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, food);
        }
        for (int i = 0; i < 25; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, hopper);
        }
        for (int i = 0; i < 25; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, rover);
        }
        for (int i = 0; i < 25; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, trap);
        }
        world.printWorld(cout);
        for (int i = 0; i < 1000; i++) {
            world.update();
            if (i < 9 || i % 100 == 99) {
                world.printWorld(cout);
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
     try {
        cout << "*** KVWADETEST7 10x10 ***" << endl;
         /*
        10x10 Darwin
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 100 (10x10), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        5 Rover
        5 Trap
        Simulate 5 moves.
        Print each grid every time.
        */
        srand(0);
        int rows = 10;
        Darwin world(rows, rows);
        for (int i = 0; i < 5; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, rover);
        }
        for (int i = 0; i < 5; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, trap);
        }
        world.printWorld(cout);
        for (int i = 0; i < 5; i++) {
            world.update();
            world.printWorld(cout);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    try {
        cout << "*** KVWADETEST8 10x10 ***" << endl;
         /*
        10x10 Darwin
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 100 (10x10), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        1 Rover
        Simulate 50 moves.
        Print each of first 5 grids, then every 10th grid
        */
        srand(0);
        int rows = 10;
        Darwin world(rows, rows);
        for (int i = 0; i < 10; i++) {
            int r = rand()%(rows*rows);
            world.addCreature(r/rows, r%rows, rand()%4+1, food);
        }
        int r = rand()%(rows*rows);
        world.addCreature(r/rows, r%rows, rand()%4+1, rover);
        world.printWorld(cout);
        for (int i = 0; i < 50; i++) {
            world.update();
            if (i < 4 || i %10 == 9) {
                world.printWorld(cout);
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}