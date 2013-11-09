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

    // Darwin x(11,11);

    // x.addCreature(&hopper, 0, 0, 0);

    // x.printBoard(0);

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

     Species food("food");
     food.addInstruction("left");
     food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

     Species hopper("hopper");
     hopper.addInstruction("hop");
     hopper.addInstruction("go 0");

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

    Species rover("rover");
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

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

     Species trap("trap");
     trap.addInstruction("if_enemy 3");
     trap.addInstruction("left");
     trap.addInstruction("go 0");
     trap.addInstruction("infect");
     trap.addInstruction("go 0");

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

            Darwin a(8, 8);
            Creature f1(&food, 1, 0, 0);
            a.addCreature(&f1);
            Creature h1(&hopper, 0, 3, 3);
            a.addCreature(&h1);
            Creature h2(&hopper, 1, 3, 4);
            a.addCreature(&h2);
            Creature h3(&hopper, 2, 4, 4);
            a.addCreature(&h3);
            Creature h4(&hopper, 3, 4, 3);
            a.addCreature(&h4);
            Creature f2(&food, 0, 7, 7);
            a.addCreature(&f2);

            for(int i = 0; i < 5; ++i) {
                a.printBoard(i);
                a.go();
            }
            a.printBoard(5);

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

            Darwin b(7, 9);
            Creature t1(&trap, 2, 0, 0);
            b.addCreature(&t1);
            Creature h1(&hopper, 1, 3, 2);
            b.addCreature(&h1);
            Creature r1(&rover, 0, 5, 4);
            b.addCreature(&r1);
            Creature t2(&trap, 3, 6, 8);
            b.addCreature(&t2);


            for(int i = 0; i < 5; ++i) {
                b.printBoard(i);
                b.go();
            }
            b.printBoard(5);

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
            Darwin c(72, 72);
            int p, r, col, f;

            // food
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f1 (&food, f, r, col); c.addCreature(&f1);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f2 (&food, f, r, col); c.addCreature(&f2);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f3 (&food, f, r, col); c.addCreature(&f3);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f4 (&food, f, r, col); c.addCreature(&f4);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f5 (&food, f, r, col); c.addCreature(&f5);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f6 (&food, f, r, col); c.addCreature(&f6);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f7 (&food, f, r, col); c.addCreature(&f7);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f8 (&food, f, r, col); c.addCreature(&f8);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f9 (&food, f, r, col); c.addCreature(&f9);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature f10 (&food, f, r, col); c.addCreature(&f10);

            // hopper 
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h1 (&hopper, f, r, col); c.addCreature(&h1);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h2 (&hopper, f, r, col); c.addCreature(&h2);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h3 (&hopper, f, r, col); c.addCreature(&h3);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h4 (&hopper, f, r, col); c.addCreature(&h4);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h5 (&hopper, f, r, col); c.addCreature(&h5);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h6 (&hopper, f, r, col); c.addCreature(&h6);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h7 (&hopper, f, r, col); c.addCreature(&h7);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h8 (&hopper, f, r, col); c.addCreature(&h8);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h9 (&hopper, f, r, col); c.addCreature(&h9);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature h10 (&hopper, f, r, col); c.addCreature(&h10);

            // Rover
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r1 (&rover, f, r, col); c.addCreature(&r1);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r2 (&rover, f, r, col); c.addCreature(&r2);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r3 (&rover, f, r, col); c.addCreature(&r3);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r4 (&rover, f, r, col); c.addCreature(&r4);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r5 (&rover, f, r, col); c.addCreature(&r5);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r6 (&rover, f, r, col); c.addCreature(&r6);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r7 (&rover, f, r, col); c.addCreature(&r7);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r8 (&rover, f, r, col); c.addCreature(&r8);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r9 (&rover, f, r, col); c.addCreature(&r9);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature r10 (&rover, f, r, col); c.addCreature(&r10);

            // trap
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t1 (&trap, f, r, col); c.addCreature(&t1);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t2 (&trap, f, r, col); c.addCreature(&t2);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t3 (&trap, f, r, col); c.addCreature(&t3);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t4 (&trap, f, r, col); c.addCreature(&t4);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t5 (&trap, f, r, col); c.addCreature(&t5);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t6 (&trap, f, r, col); c.addCreature(&t6);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t7 (&trap, f, r, col); c.addCreature(&t7);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t8 (&trap, f, r, col); c.addCreature(&t8);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t9 (&trap, f, r, col); c.addCreature(&t9);
            p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
            Creature t10 (&trap, f, r, col); c.addCreature(&t10);

            for(int i = 0; i < 1000; ++i) {
                if (i < 10 || i%100 == 0)
                c.printBoard(i);
                c.go();
                // cout << "end round" << endl;
            }
            c.printBoard(1000);

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
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // NEW TESTS //
    try {
        cout << "*** Darwin 72x72 own test ***" << endl;
        
        // 72x72 board with randoming placed 
        // 21 food
        // 21 hoppers
        // 21 rovers
        // 21 traps
        // 100 moves
        // printed every 10th board

        Darwin c(72, 72);
        int p, r, col, f;

        // food
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f1 (&food, f, r, col); c.addCreature(&f1);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f2 (&food, f, r, col); c.addCreature(&f2);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f3 (&food, f, r, col); c.addCreature(&f3);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f4 (&food, f, r, col); c.addCreature(&f4);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f5 (&food, f, r, col); c.addCreature(&f5);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f6 (&food, f, r, col); c.addCreature(&f6);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f7 (&food, f, r, col); c.addCreature(&f7);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f8 (&food, f, r, col); c.addCreature(&f8);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f9 (&food, f, r, col); c.addCreature(&f9);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f10 (&food, f, r, col); c.addCreature(&f10);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f11 (&food, f, r, col); c.addCreature(&f11);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f12 (&food, f, r, col); c.addCreature(&f12);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f13 (&food, f, r, col); c.addCreature(&f13);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f14 (&food, f, r, col); c.addCreature(&f14);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f15 (&food, f, r, col); c.addCreature(&f15);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f16 (&food, f, r, col); c.addCreature(&f16);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f17 (&food, f, r, col); c.addCreature(&f17);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f18 (&food, f, r, col); c.addCreature(&f18);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f19 (&food, f, r, col); c.addCreature(&f19);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f20 (&food, f, r, col); c.addCreature(&f20);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature f21 (&food, f, r, col); c.addCreature(&f21);

        // hoppers
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h1 (&hopper, f, r, col); c.addCreature(&h1);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h2 (&hopper, f, r, col); c.addCreature(&h2);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h3 (&hopper, f, r, col); c.addCreature(&h3);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h4 (&hopper, f, r, col); c.addCreature(&h4);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h5 (&hopper, f, r, col); c.addCreature(&h5);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h6 (&hopper, f, r, col); c.addCreature(&h6);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h7 (&hopper, f, r, col); c.addCreature(&h7);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h8 (&hopper, f, r, col); c.addCreature(&h8);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h9 (&hopper, f, r, col); c.addCreature(&h9);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h10 (&hopper, f, r, col); c.addCreature(&h10);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h11 (&hopper, f, r, col); c.addCreature(&h11);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h12 (&hopper, f, r, col); c.addCreature(&h12);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h13 (&hopper, f, r, col); c.addCreature(&h13);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h14 (&hopper, f, r, col); c.addCreature(&h14);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h15 (&hopper, f, r, col); c.addCreature(&h15);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h16 (&hopper, f, r, col); c.addCreature(&h16);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h17 (&hopper, f, r, col); c.addCreature(&h17);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h18 (&hopper, f, r, col); c.addCreature(&h18);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h19 (&hopper, f, r, col); c.addCreature(&h19);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h20 (&hopper, f, r, col); c.addCreature(&h20);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature h21 (&hopper, f, r, col); c.addCreature(&h21);

        // Rover
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r1 (&rover, f, r, col); c.addCreature(&r1);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r2 (&rover, f, r, col); c.addCreature(&r2);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r3 (&rover, f, r, col); c.addCreature(&r3);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r4 (&rover, f, r, col); c.addCreature(&r4);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r5 (&rover, f, r, col); c.addCreature(&r5);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r6 (&rover, f, r, col); c.addCreature(&r6);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r7 (&rover, f, r, col); c.addCreature(&r7);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r8 (&rover, f, r, col); c.addCreature(&r8);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r9 (&rover, f, r, col); c.addCreature(&r9);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r10 (&rover, f, r, col); c.addCreature(&r10);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r11 (&rover, f, r, col); c.addCreature(&r11);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r12 (&rover, f, r, col); c.addCreature(&r12);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r13 (&rover, f, r, col); c.addCreature(&r13);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r14 (&rover, f, r, col); c.addCreature(&r14);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r15 (&rover, f, r, col); c.addCreature(&r15);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r16 (&rover, f, r, col); c.addCreature(&r16);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r17 (&rover, f, r, col); c.addCreature(&r17);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r18 (&rover, f, r, col); c.addCreature(&r18);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r19 (&rover, f, r, col); c.addCreature(&r19);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r20 (&rover, f, r, col); c.addCreature(&r20);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature r21 (&rover, f, r, col); c.addCreature(&r21);

        // trap
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t1 (&trap, f, r, col); c.addCreature(&t1);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t2 (&trap, f, r, col); c.addCreature(&t2);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t3 (&trap, f, r, col); c.addCreature(&t3);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t4 (&trap, f, r, col); c.addCreature(&t4);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t5 (&trap, f, r, col); c.addCreature(&t5);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t6 (&trap, f, r, col); c.addCreature(&t6);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t7 (&trap, f, r, col); c.addCreature(&t7);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t8 (&trap, f, r, col); c.addCreature(&t8);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t9 (&trap, f, r, col); c.addCreature(&t9);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t10 (&trap, f, r, col); c.addCreature(&t10);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t11 (&trap, f, r, col); c.addCreature(&t11);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t12 (&trap, f, r, col); c.addCreature(&t12);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t13 (&trap, f, r, col); c.addCreature(&t13);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t14 (&trap, f, r, col); c.addCreature(&t14);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t15 (&trap, f, r, col); c.addCreature(&t15);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t16 (&trap, f, r, col); c.addCreature(&t16);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t17 (&trap, f, r, col); c.addCreature(&t17);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t18 (&trap, f, r, col); c.addCreature(&t18);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t19 (&trap, f, r, col); c.addCreature(&t19);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t20 (&trap, f, r, col); c.addCreature(&t20);
        p = rand() % 5184; r = p / 72; col = p % 72; f = c.fi(rand() % 4); 
        Creature t21 (&trap, f, r, col); c.addCreature(&t21);

        for(int i = 0; i < 100; ++i) {
                if (i%10 == 0)
                c.printBoard(i);
                c.go();
                // cout << "end round" << endl;
            }
            c.printBoard(100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}

    // 205 lines of NEW TESTS //
