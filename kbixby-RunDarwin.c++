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
    */

    Species food = Species('f');
    food.add_instruction("left");
    food.add_instruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0"); 

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

    Species rover = Species('r');
    rover.add_instruction("if_enemy 9");
    rover.add_instruction("if_empty 7");
    rover.add_instruction("if_random 5");
    rover.add_instruction("left");
    rover.add_instruction("go 0");
    rover.add_instruction("right");
    rover.add_instruction("go 0");
    rover.add_instruction("hop");
    rover.add_instruction("go 0");
    rover.add_instruction("infect");
    rover.add_instruction("go 0");

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

    Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");

    // ----
    // best
    // ----

    Creature fn = Creature(food, NORTH);
    Creature fe = Creature(food, EAST);
    Creature fs = Creature(food, SOUTH);
    Creature fw = Creature(food, WEST);
    Creature hn = Creature(hopper, NORTH);
    Creature he = Creature(hopper, EAST);
    Creature hs = Creature(hopper, SOUTH);
    Creature hw = Creature(hopper, WEST);
    Creature tn = Creature(trap, NORTH);
    Creature te = Creature(trap, EAST);
    Creature ts = Creature(trap, SOUTH);
    Creature tw = Creature(trap, WEST);
    Creature rn = Creature(rover, NORTH);
    Creature re = Creature(rover, EAST);
    Creature rs = Creature(rover, SOUTH);
    Creature rw = Creature(rover, WEST);
    Creature bn = Creature(best, NORTH);
    Creature be = Creature(best, EAST);
    Creature bs = Creature(best, SOUTH);
    Creature bw = Creature(best, WEST);

    // // ----------
    // // darwin 8x8
    // // ----------

    // try {
    //     cout << "*** Darwin 8x8 ***" << endl;
    //     srand(0);
    //     /*
    //     8x8 Darwin
    //     Food,   facing east,  at (0, 0)
    //     Hopper, facing north, at (3, 3)
    //     Hopper, facing east,  at (3, 4)
    //     Hopper, facing south, at (4, 4)
    //     Hopper, facing west,  at (4, 3)
    //     Food,   facing north, at (7, 7)
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
    //     Creature fe = Creature(food, EAST);
    //     Creature hn = Creature(hopper, NORTH);
    //     Creature he = Creature(hopper, EAST);
    //     Creature hs = Creature(hopper, SOUTH);
    //     Creature hw = Creature(hopper, WEST);
    //     Creature fn = Creature(food, NORTH);
    //     Darwin d = Darwin(8, 8);
    //     d.add_creature(fe, 0, 0);
    //     d.add_creature(hn, 3, 3);
    //     d.add_creature(he, 3, 4);
    //     d.add_creature(hs, 4, 4);
    //     d.add_creature(hw, 4, 3);
    //     d.add_creature(fn, 7, 7);
    //     d.print_state();
    //     for (int i = 0; i < 5; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // ----------
    // // darwin 7x9
    // // ----------

    // try {
    //     cout << "*** Darwin 7x9 ***" << endl;
    //     srand(0);
    //     /*
    //     7x9 Darwin
    //     Trap,   facing south, at (0, 0)
    //     Hopper, facing east,  at (3, 2)
    //     Rover,  facing north, at (5, 4)
    //     Trap,   facing west,  at (6, 8)
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
    //     Creature ts = Creature(trap, SOUTH);
    //     Creature he = Creature(hopper, EAST);
    //     Creature rn = Creature(rover, NORTH);
    //     Creature tw = Creature(trap, WEST);
    //     Darwin d = Darwin(7, 9);
    //     d.add_creature(ts, 0, 0);
    //     d.add_creature(he, 3, 2);
    //     d.add_creature(rn, 5, 4);
    //     d.add_creature(tw, 6, 8);
    //     d.print_state();
    //     for (int i = 0; i < 5; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // ------------
    // // darwin 72x72
    // // without best
    // // ------------

    // try {
    //     cout << "*** Darwin 72x72 without Best ***" << endl;
    //     srand(0);
    //     /*
    //     Randomly place the following creatures facing randomly.
    //     Call rand(), mod it with 5184 (72x72), and use that for the position
    //     in a row-major order grid.
    //     Call rand() again, mod it with 4 and use that for it's direction with
    //     the ordering: west, north, east, south.
    //     Do that for each kind of creature.
    //     10 Food
    //     10 Hopper
    //     10 Rover
    //     10 Trap
    //     Simulate 1000 moves.
    //     Print the first 10 grids          (i.e. 0, 1, 2...9).
    //     Print every 100th grid after that (i.e. 100, 200, 300...1000).
    //     */
    //     Darwin d = Darwin(72, 72);
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(food, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(hopper, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(rover, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(trap, dir), r, c);
    //     }
    //     for (int i = 0; i < 1000; i++) {
    //         if (i < 10 || (i % 100) == 0)
    //             d.print_state();
    //         d.simulate_round();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // ------------
    // // darwin 72x72
    // // with best
    // // ------------

    // try {
    //     cout << "*** Darwin 72x72 with Best ***" << endl;
    //     srand(0);
    //     /*
    //     Randomly place the following creatures facing randomly.
    //     Call rand(), mod it with 5184 (72x72), and use that for the position
    //     in a row-major order grid.
    //     Call rand() again, mod it with 4 and use that for it's direction with
    //     the ordering: 0:west, 1:north, 2:east, 3:south.
    //     Do that for each kind of creature.
    //     10 Food
    //     10 Hopper
    //     10 Rover
    //     10 Trap
    //     10 Best
    //     Simulate 1000 moves.
    //     Best MUST outnumber ALL other species for the bonus pts.
    //     Print the first 10 grids          (i.e. 0, 1, 2...9).
    //     Print every 100th grid after that (i.e. 100, 200, 300...1000).
    //     */
    //     Darwin d = Darwin(72, 72);
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(food, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(hopper, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(rover, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(trap, dir), r, c);
    //     }
    //     for (int i = 0; i < 10; i++) {
    //         int cell = rand() % 5184;
    //         int r = cell / 72;
    //         int c = cell % 72;
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(best, dir), r, c);
    //     }
    //     for (int i = 0; i < 1000; i++) {
    //         if (i < 10 || (i % 100) == 0)
    //             d.print_state();
    //         d.simulate_round();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // Our Tests

    try {
        cout << "*** Darwin 2x2 Two Rovers ***" << endl;
        srand(0);
        /*
        2x2 Grid
        North Rover @ (0, 0)
        East Rover @ (1, 0)
        */
        Darwin d = Darwin(2, 2);
        d.add_creature(rn, 0, 0);
        d.add_creature(re, 1, 0);
        d.print_state();
        for (int i = 0; i < 10; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 4x4 Four Traps Four Rovers***" << endl;
        srand(0);
        /*
        4x4 Grid
        South Trap @ (0, 0)
        North Trap @ (3, 3)
        East Trap @ (3, 0)
        West Trap @ (0, 3)
        North Rover @ (2, 1)
        East Rover @ (1, 2)
        South Rover @ (2, 2)
        West Rover @ (1, 1)
        */
        Darwin d = Darwin(4, 4);
        d.add_creature(ts, 0, 0);
        d.add_creature(tn, 3, 3);
        d.add_creature(te, 3, 0);
        d.add_creature(tw, 0, 3);
        d.add_creature(rn, 2, 1);
        d.add_creature(re, 1, 2);
        d.add_creature(rs, 2, 2);
        d.add_creature(rw, 1, 1);
        d.print_state();
        for (int i = 0; i < 10; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 10x4 Four Traps Four Rovers***" << endl;
        srand(0);
        /*
        10x4 Grid
        South Trap @ (0, 0)
        North Trap @ (7, 3)
        East Trap @ (3, 0)
        West Trap @ (0, 3)
        North Rover @ (4, 1)
        East Rover @ (1, 2)
        South Rover @ (2, 2)
        West Rover @ (0, 1)
        */
        Darwin d = Darwin(10, 4);
        d.add_creature(ts, 0, 0);
        d.add_creature(tn, 7, 3);
        d.add_creature(te, 3, 0);
        d.add_creature(tw, 0, 3);
        d.add_creature(rn, 4, 1);
        d.add_creature(re, 1, 2);
        d.add_creature(rs, 2, 2);
        d.add_creature(rw, 0, 1);
        d.print_state();
        for (int i = 0; i < 10; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 23x17 ***" << endl;
        srand(0);
        /*
        23x17 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d = Darwin(23, 17);
        int size = 23 * 17;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.add_creature(Creature(rover, dir), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.add_creature(Creature(hopper, dir), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.add_creature(Creature(trap, dir), r, c);
        }
        d.print_state();
        for (int i = 0; i < 100; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 19x23 ***" << endl;
        srand(0);
        /*
        19x23 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d = Darwin(19, 23);
        int size = 19 * 23;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.add_creature(Creature(rover, dir), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.add_creature(Creature(hopper, dir), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.add_creature(Creature(trap, dir), r, c);
        }
        d.print_state();
        for (int i = 0; i < 100; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 37x43 ***" << endl;
        srand(0);
        /*
        37x43 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d = Darwin(37, 43);
        int size = 37 * 43;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.add_creature(Creature(rover, dir), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.add_creature(Creature(hopper, dir), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.add_creature(Creature(trap, dir), r, c);
        }
        d.print_state();
        for (int i = 0; i < 100; i++) {
            d.simulate_round();
            d.print_state();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // // Eliya's Tests

    // try {
    //     cout << "*** Darwin 10X10 Test I ***" << endl;
    //     srand(0);
    //     Darwin d = Darwin(10, 10);
    //     d.add_creature(fs, 5, 5);
    //     d.add_creature(hn, 3, 5);
    //     d.add_creature(hs, 2, 6);
    //     d.add_creature(he, 1, 9);
    //     d.add_creature(he, 8, 1);
    //     d.add_creature(rs, 2, 5);
    //     for (int i = 0; i < 6; i++) {
    //         d.print_state();
    //         d.simulate_round();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // try {
    //     cout << "*** Darwin 20X20 Test II ***" << endl;
    //     srand(0);
    //     Darwin d = Darwin(20, 20);

    //     for(int i = 1; i < 9; i++){
    //         int randPos = rand() % 400; 
    //         int r = randPos / 20;
    //         int c = randPos % 20; 
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(hopper, dir), r, c);
    //     }

    //     for(int i = 1; i < 3; i++){
    //         int randPos = rand() % 400; 
    //         int r = randPos / 20;
    //         int c = randPos % 20; 
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(rover, dir), r, c);
    //     }

    //     for(int i = 1; i < 5; i++){
    //         int randPos = rand() % 400; 
    //         int r = randPos / 20;
    //         int c = randPos % 20; 
    //         int dir = rand() % 4;
    //         d.add_creature(Creature(food, dir), r, c);
    //     }

    //     d.print_state();
    //     for (int i = 0; i < 4; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // Ensign's Tests

    // try {
    //     cout << "*** Rover 1x1 ***" << endl;
    //     srand(0);
    //     /*  
    //     1x1 Darwin
    //     Rover, facing north at (0, 0)
    //     Simulate 10 moves
    //     Print every move
    //     */
    //     Darwin d(1, 1);
    //     Creature c = Creature(rover, 1);
    //     d.add_creature(c, 0, 0);
    //     d.print_state();
    //     for (int i = 1; i <= 10; i++){
    //         d.simulate_round();
    //         d.print_state();  
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}


    // try {
    //     cout << "*** Hopper Collide 10x4 ***" << endl;
    //     srand(0);
    //     /*  
    //     10x4 Darwin
    //     4 Hoppers, facing south in each column of row 0
    //     4 Hoppers, facing north in each column of row 9
    //     Simulate 10 moves
    //     Print every move
    //     */
    //     Darwin d(10, 4);
    //     Creature c1(hopper, 3);
    //     Creature c2(hopper, 3);
    //     Creature c3(hopper, 3);
    //     Creature c4(hopper, 3);
    //     Creature c5(hopper, 1);
    //     Creature c6(hopper, 1);
    //     Creature c7(hopper, 1);
    //     Creature c8(hopper, 1);
    //     d.add_creature(c1, 0, 0);
    //     d.add_creature(c2, 0, 1);
    //     d.add_creature(c3, 0, 2);
    //     d.add_creature(c4, 0, 3);
    //     d.add_creature(c5, 9, 0);
    //     d.add_creature(c6, 9, 1);
    //     d.add_creature(c7, 9, 2);
    //     d.add_creature(c8, 9, 3);
    //     d.print_state();
    //     for (int i = 1; i <= 10; i++){
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // try {
    //     cout << "*** Rover Takeover 8x8 ***" << endl;
    //     srand(0);
    //     /*  
    //     8x8 Darwin
    //     Rover, facing south at (3, 4)
    //     Food, facing south at (0, 2)
    //     Food, facing south at (7, 4)
    //     Food, facing south at (2, 7)
    //     Food, facing north at (3, 0)
    //     Food, facing north at (4, 5)
    //     Food, facing north at (5, 2)
    //     Food, facing north at (6, 3)
    //     Simulate 100 moves
    //     Print first 10 moves and multiples of 10
    //     */
    //     Darwin d(8, 8);
    //     Creature c1(rover, 3);
    //     Creature c2(food, 3);
    //     Creature c3(food, 3);
    //     Creature c4(food, 3);
    //     Creature c5(food, 1);
    //     Creature c6(food, 1);
    //     Creature c7(food, 1);
    //     Creature c8(food, 1);
    //     d.add_creature(c1, 3, 4);
    //     d.add_creature(c2, 0, 2);
    //     d.add_creature(c3, 7, 4);
    //     d.add_creature(c4, 2, 7);
    //     d.add_creature(c5, 3, 0);
    //     d.add_creature(c6, 4, 5);
    //     d.add_creature(c7, 5, 2);
    //     d.add_creature(c8, 6, 3);
    //     d.print_state();
    //     for (int i = 1; i <= 100; i++){
    //         d.simulate_round();
    //         if (i < 10 || i % 10 == 0)
    //             d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // Ethan's Tests

    // try {
    //     cout << "*** Darwin 8x8 Corners ***" << endl;
    //     /*
    //     8x8 Darwin
    //     Hopper, facing west, at (0, 3)
    //     Hopper, facing east,  at (0, 4)
    //     Hopper, facing west, at (7, 3)
    //     Hopper, facing east,  at (7, 4)
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
    //     Darwin d(8, 8);

    //     d.add_creature(hw, 0, 3);
    //     d.add_creature(he, 0, 4);
    //     d.add_creature(hw, 7, 3);
    //     d.add_creature(he, 7, 4);

    //     d.print_state();

    //     for (int i = 0; i < 5; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // try {
    //     cout << "*** Darwin 3x8 Guantlet***" << endl;
    //     /*
    //     3x8 Darwin
    //     Trap, facing south, at (0, 3)
    //     Trap, facing east,  at (0, 4)
    //     Trap, facing north, at (2, 3)
    //     Trap, facing east,  at (2, 4)
    //     Hopper, facing east,  at (1, 0)
    //     Simulate 10 moves.
    //     Print every grid.
    //     */
    //     Darwin d(3, 8);
        
    //     d.add_creature(ts, 0, 3);
    //     d.add_creature(te, 0, 4);
    //     d.add_creature(tn, 2, 3);
    //     d.add_creature(te, 2, 4);
    //     d.add_creature(he, 1, 0);

    //     d.print_state();

    //     for (int i = 0; i < 10; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}


    // try {
    //     cout << "*** Darwin 5x5 Trap!***" << endl;
    //     /*
    //     3x8 Darwin
    //     Trap, facing south, at (2, 2)
    //     Hopper, facing south,  at (0, 2)
    //     Hopper, facing west, at (2, 4)
    //     Hopper, facing north,  at (4, 2)
    //     Hopper, facing east,  at (2, 0)
    //     Simulate 10 moves.
    //     Print every grid.
    //     */
    //     Darwin d(5, 5);

    //     d.add_creature(ts, 2, 2);
    //     d.add_creature(hs, 0, 2);
    //     d.add_creature(hw, 2, 4);
    //     d.add_creature(hn, 4, 2);
    //     d.add_creature(he, 2, 0);

    //     d.print_state();

    //     for (int i = 0; i < 10; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // KVWADE's Tests

    // try {
    //      /*
    //     1x10 Darwin
    //     Hopper,   facing east, at (0, 0)
    //     Trap, facing east,  at (0, 5)
    //     Rover,  facing WEST, at (0, 9)
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
    //     cout << "*** KVWADETEST1 1x10 ***" << endl;
    //     srand(0);
    //     Darwin d(1, 10);
    //     d.add_creature(he, 0, 0);
    //     d.add_creature(te, 0, 5);
    //     d.add_creature(rw, 0, 9);

    //     d.print_state();
    //     for (int i = 0; i < 5; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // try {
    //      /*
    //     10x1 Darwin
    //     Hopper,   facing south, at (0, 0)
    //     Trap, facing east,  at (5, 0)
    //     Rover,  facing north, at (0, 9)
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
    //     cout << "*** KVWADETEST2 10x1 ***" << endl;
    //     srand(0);
    //     Darwin d(10, 1);
    //     d.add_creature(hs, 0, 0);
    //     d.add_creature(te, 5, 0);
    //     d.add_creature(rn, 9, 0);

    //     d.print_state();
    //     for (int i = 0; i < 5; i++) {
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // nlaz's Test

    // try {
    //     cout << "*** Darwin 5x5 ***" << endl;
    //     srand(0);
    //     /*
    //      4x4 Darwin
    //      Trap,   facing west, at (4, 0)
    //      Hopper,   facing north,  at (4, 1)
    //      Hopper,  facing east, at (4, 2)
    //      Hopper,   facing south,  at (4, 3)
    //      Food,  face north, at (4,4);
    //      Simulate 5 moves.
    //      Print every grid.
    //      */
    //     Darwin d(5,5);
    //     d.add_creature(tw, 4, 0);
    //     d.add_creature(hn, 4, 1);
    //     d.add_creature(he, 4, 2);
    //     d.add_creature(hs, 4, 3);
    //     d.add_creature(fn, 4, 4);
    //     d.print_state();
    //     for (int i = 0; i < 5; i++){
    //         d.simulate_round();
    //         d.print_state();
    //     }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    return 0;}
