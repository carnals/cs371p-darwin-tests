// ----------------------------
// /cs371p-darwin/RunDarwin.c++
// Copyright (C) 2013
// CS371p Fall 2013
// Kevin Tran
// ----------------------------

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


// Generate random creature position
void getRandomCreature (Darwin& world, Species& s, Creature* allCreature, int index, int h, int w)
{
    int pos = rand() % (h * w);
    int row = pos / h;
    int col = pos % h;
    char dir;

    switch(rand() % 4)
    {
        case 0:     dir = 'w';       break; 
        case 1:     dir = 'n';       break;
        case 2:     dir = 'e';       break;
        case 3:     dir = 's';       break;
    }

    allCreature[index] = Creature(&s, dir);
    world.addCreature(allCreature[index], row, col);

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
    food.addInstruction("left", 0);
    food.addInstruction("go", 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper('h');
    hopper.addInstruction("hop", 0);
    hopper.addInstruction("go", 0);
    
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
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", 0);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", 0);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", 0);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", 0);
    rover.addInstruction("go", 0);

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
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", 0);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", 0);
    trap.addInstruction("go", 0);

    // ----------
    // darwin 8x8
    // ----------

    try 
    {
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

        Darwin world(8, 8);
        Creature a = Creature(&food, 'e');
        Creature b = Creature(&hopper, 'n');
        Creature c = Creature(&hopper, 'e');
        Creature d = Creature(&hopper, 's');
        Creature e = Creature(&hopper, 'w');
        Creature f = Creature(&food, 'n');
        world.addCreature(a, 0, 0);
        world.addCreature(b, 3, 3);
        world.addCreature(c, 3, 4);
        world.addCreature(d, 4, 4);
        world.addCreature(e, 4, 3);
        world.addCreature(f, 7, 7);
        world.simulate(5, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try 
    {
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

        Darwin world(7, 9);
        Creature a = Creature(&trap, 's');
        Creature b = Creature(&hopper, 'e');
        Creature c = Creature(&rover, 'n');
        Creature d = Creature(&trap, 'w');
        world.addCreature(a, 0, 0);
        world.addCreature(b, 3, 2);
        world.addCreature(c, 5, 4);
        world.addCreature(d, 6, 8);
        world.simulate(5, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 3x3
    // ----------

    try 
    {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);

        Darwin world(3, 3);
        Creature allCreature[6];

        allCreature[0] = Creature(&hopper, 'n');
        world.addCreature(allCreature[0], 0, 0);
        allCreature[1] = Creature(&hopper, 's');
        world.addCreature(allCreature[1], 1, 1);
        allCreature[2] = Creature(&hopper, 'e');
        world.addCreature(allCreature[2], 2, 2);
        allCreature[3] = Creature(&rover, 'w');
        world.addCreature(allCreature[3], 0, 2);
        allCreature[4] = Creature(&rover, 'n');
        world.addCreature(allCreature[4], 2, 0);
        allCreature[5] = Creature(&rover, 's');
        world.addCreature(allCreature[5], 0, 1);

        world.simulate(10, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // darwin 4x4
    // ----------

    try 
    {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);

        Darwin world(4, 4);
        Creature allCreature[6];

        allCreature[0] = Creature(&hopper, 'n');
        world.addCreature(allCreature[0], 0, 0);
        allCreature[1] = Creature(&hopper, 's');
        world.addCreature(allCreature[1], 1, 1);
        allCreature[2] = Creature(&hopper, 'e');
        world.addCreature(allCreature[2], 2, 2);
        allCreature[3] = Creature(&hopper, 'w');
        world.addCreature(allCreature[3], 3, 3);
        allCreature[4] = Creature(&rover, 'n');
        world.addCreature(allCreature[4], 3, 0);
        allCreature[5] = Creature(&rover, 's');
        world.addCreature(allCreature[5], 0, 3);

        world.simulate(10, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 5x5
    // ----------

    try 
    {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);

        Darwin world(5, 5);
        Creature allCreature[10];

        allCreature[0] = Creature(&trap, 'n');
        world.addCreature(allCreature[0], 0, 0);
        allCreature[1] = Creature(&trap, 's');
        world.addCreature(allCreature[1], 4, 4);
        allCreature[2] = Creature(&trap, 'e');
        world.addCreature(allCreature[2], 0, 4);
        allCreature[3] = Creature(&trap, 'w');
        world.addCreature(allCreature[3], 4, 0);
        allCreature[4] = Creature(&trap, 'n');
        world.addCreature(allCreature[4], 2, 2);
        allCreature[5] = Creature(&rover, 's');
        world.addCreature(allCreature[5], 4, 1);
        allCreature[6] = Creature(&hopper, 'n');
        world.addCreature(allCreature[6], 3, 4);
        allCreature[7] = Creature(&hopper, 's');
        world.addCreature(allCreature[7], 1, 1);
        allCreature[8] = Creature(&rover, 'e');
        world.addCreature(allCreature[8], 3, 3);
        allCreature[9] = Creature(&rover, 'w');
        world.addCreature(allCreature[9], 0, 2);


        world.simulate(20, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // darwin 10x10
    // ----------

    try 
    {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);

        Darwin world(10, 10);
        Creature allCreature[10];

        allCreature[0] = Creature(&hopper, 'n');
        world.addCreature(allCreature[0], 0, 0);
        allCreature[1] = Creature(&hopper, 's');
        world.addCreature(allCreature[1], 9, 9);
        allCreature[2] = Creature(&hopper, 'e');
        world.addCreature(allCreature[2], 0, 9);
        allCreature[3] = Creature(&hopper, 'w');
        world.addCreature(allCreature[3], 9, 0);
        allCreature[4] = Creature(&hopper, 'n');
        world.addCreature(allCreature[4], 5, 5);
        allCreature[5] = Creature(&rover, 's');
        world.addCreature(allCreature[5], 5, 1);
        allCreature[6] = Creature(&hopper, 'n');
        world.addCreature(allCreature[6], 3, 4);
        allCreature[7] = Creature(&hopper, 's');
        world.addCreature(allCreature[7], 1, 1);
        allCreature[8] = Creature(&rover, 'e');
        world.addCreature(allCreature[8], 2, 2);
        allCreature[9] = Creature(&rover, 'w');
        world.addCreature(allCreature[9], 0, 2);


        world.simulate(20, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 50x50
    // ----------

    try 
    {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);

        Darwin world(50, 50);
        Creature allCreature[10];

        allCreature[0] = Creature(&trap, 'n');
        world.addCreature(allCreature[0], 0, 0);
        allCreature[1] = Creature(&trap, 's');
        world.addCreature(allCreature[1], 49, 49);
        allCreature[2] = Creature(&trap, 'e');
        world.addCreature(allCreature[2], 0, 49);
        allCreature[3] = Creature(&trap, 'w');
        world.addCreature(allCreature[3], 49, 0);
        allCreature[4] = Creature(&hopper, 'n');
        world.addCreature(allCreature[4], 25, 25);
        allCreature[5] = Creature(&rover, 's');
        world.addCreature(allCreature[5], 15, 11);
        allCreature[6] = Creature(&hopper, 'n');
        world.addCreature(allCreature[6], 23, 14);
        allCreature[7] = Creature(&hopper, 's');
        world.addCreature(allCreature[7], 11, 11);
        allCreature[8] = Creature(&rover, 'e');
        world.addCreature(allCreature[8], 32, 32);
        allCreature[9] = Creature(&rover, 'w');
        world.addCreature(allCreature[9], 40, 22);


        world.simulate(20, true, cout);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}




    // ------------
    // darwin 72x72
    // without best
    // ------------

    try 
    {
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
        Darwin world(72,72);
        Creature allCreature[40];

        for (int i = 0; i < 10; ++i)
            getRandomCreature (world, food, allCreature, i, 72, 72);
        for (int i = 10; i < 20; ++i)
            getRandomCreature (world, hopper, allCreature, i, 72, 72);
        for (int i = 20; i < 30; ++i)
            getRandomCreature (world, rover, allCreature, i, 72, 72);
        for (int i = 30; i < 40; ++i)
            getRandomCreature (world, trap, allCreature, i, 72, 72);

        world.simulate(9, true, cout);

        world.simulate(90, false, cout);
        world.simulate(1, true, cout);

        for (int i = 0; i < 9; ++i) {
            world.simulate(99, false, cout);
            world.simulate(1, true, cout);
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

    try 
    {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        
        // Randomly place the following creatures facing randomly.
        // Call rand(), mod it with 5184 (72x72), and use that for the position
        // in a row-major order grid.
        // Call rand() again, mod it with 4 and use that for it's direction with
        // the ordering: 0:west, 1:north, 2:east, 3:south.
        // Do that for each kind of creature.
        // 10 Food
        // 10 Hopper
        // 10 Rover
        // 10 Trap
        // 10 Best
        // Simulate 1000 moves.
        // Best MUST outnumber ALL other species for the bonus pts.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        // Print every 100th grid after that (i.e. 100, 200, 300...1000).
               

        Darwin world(72,72);
        Creature allCreature[50];

        for (int i = 0; i < 10; ++i)
            getRandomCreature (world, food, allCreature, i, 72, 72);
        for (int i = 10; i < 20; ++i)
            getRandomCreature (world, hopper, allCreature, i, 72, 72);
        for (int i = 20; i < 30; ++i)
            getRandomCreature (world, rover, allCreature, i, 72, 72);
        for (int i = 30; i < 40; ++i)
            getRandomCreature (world, trap, allCreature, i, 72, 72);
        for (int i = 40; i < 50; ++i)
            getRandomCreature (world, rover, allCreature, i, 72, 72);

        world.simulate(9, true, cout);

        world.simulate(90, false, cout);
        world.simulate(1, true, cout);

        for (int i = 0; i < 9; ++i) {
            world.simulate(99, false, cout);
            world.simulate(1, true, cout);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
