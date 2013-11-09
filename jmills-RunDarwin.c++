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

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

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
        GridItem g[8*8];
        GridItem* grid [8*8];
        for (int i = 0; i < 8*8; i++)
          grid[i] = &g[i];
        Board b (8, 8, grid);

        Position p (0, 0, direction_right);
        Creature f1 (creature_type_food, p, &b);
        b.add_creature(&f1, p);

        p = Position (3, 3, direction_up);
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);

        p = Position (4, 3, direction_right);
        Creature h2 (creature_type_hopper, p, &b);
        b.add_creature(&h2, p);

        p = Position (4, 4, direction_down);
        Creature h3 (creature_type_hopper, p, &b);
        b.add_creature(&h3, p);

        p = Position (3, 4, direction_left);
        Creature h4 (creature_type_hopper, p, &b);
        b.add_creature(&h4, p);

        p = Position (7, 7, direction_up);
        Creature f2 (creature_type_food, p, &b);
        b.add_creature(&f2, p);

        b.print_board();

        Game game (b);
        for (int i = 0; i < 5; i++) {
            game.turn();
            b.print_board();
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
        GridItem g[9*7];
        GridItem* grid [9*7];
        for (int i = 0; i < 9*7; i++)
          grid[i] = &g[i];
        Board b (9, 7, grid);

        Position p (0, 0, direction_down);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (2, 3, direction_left);
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);

        p = Position (4, 5, direction_up);
        Creature r1 (creature_type_trap, p, &b);
        b.add_creature(&r1, p);

        p = Position (8, 6, direction_left);
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);

        Game game (b);
        for (int i = 0; i < 5; i++) {
            game.turn();
            b.print_board();
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
        GridItem g[5184];
        GridItem* grid [5184];
        for (int i = 0; i < 5184; i++)
          grid[i] = &g[i];
        Board b (72, 72, grid);

        Position p (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f1 (creature_type_food, p, &b);
        b.add_creature(&f1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f2 (creature_type_hopper, p, &b);
        b.add_creature(&f2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f3 (creature_type_hopper, p, &b);
        b.add_creature(&f3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f4 (creature_type_hopper, p, &b);
        b.add_creature(&f4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f5 (creature_type_hopper, p, &b);
        b.add_creature(&f5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f6 (creature_type_hopper, p, &b);
        b.add_creature(&f6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f7 (creature_type_hopper, p, &b);
        b.add_creature(&f7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f8 (creature_type_hopper, p, &b);
        b.add_creature(&f8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f9 (creature_type_hopper, p, &b);
        b.add_creature(&f9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f10 (creature_type_hopper, p, &b);
        b.add_creature(&f10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h2 (creature_type_hopper, p, &b);
        b.add_creature(&h2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h3 (creature_type_hopper, p, &b);
        b.add_creature(&h3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h4 (creature_type_hopper, p, &b);
        b.add_creature(&h4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h5 (creature_type_hopper, p, &b);
        b.add_creature(&h5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h6 (creature_type_hopper, p, &b);
        b.add_creature(&h6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h7 (creature_type_hopper, p, &b);
        b.add_creature(&h7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h8 (creature_type_hopper, p, &b);
        b.add_creature(&h8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h9 (creature_type_hopper, p, &b);
        b.add_creature(&h9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h10 (creature_type_hopper, p, &b);
        b.add_creature(&h10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r1 (creature_type_rover, p, &b);
        b.add_creature(&r1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r2 (creature_type_rover, p, &b);
        b.add_creature(&r2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r3 (creature_type_rover, p, &b);
        b.add_creature(&r3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r4 (creature_type_rover, p, &b);
        b.add_creature(&r4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r5 (creature_type_rover, p, &b);
        b.add_creature(&r5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r6 (creature_type_rover, p, &b);
        b.add_creature(&r6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r7 (creature_type_rover, p, &b);
        b.add_creature(&r7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r8 (creature_type_rover, p, &b);
        b.add_creature(&r8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r9 (creature_type_rover, p, &b);
        b.add_creature(&r9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r10 (creature_type_rover, p, &b);
        b.add_creature(&r10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t3 (creature_type_trap, p, &b);
        b.add_creature(&t3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t4 (creature_type_trap, p, &b);
        b.add_creature(&t4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t5 (creature_type_trap, p, &b);
        b.add_creature(&t5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t6 (creature_type_trap, p, &b);
        b.add_creature(&t6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t7 (creature_type_trap, p, &b);
        b.add_creature(&t7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t8 (creature_type_trap, p, &b);
        b.add_creature(&t8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t9 (creature_type_trap, p, &b);
        b.add_creature(&t9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t10 (creature_type_trap, p, &b);
        b.add_creature(&t10, p);

        Game game (b);
        for (int i = 0; i < 10; i++) {
            game.turn();
            b.print_board();
        }
        for (int i = 10; i < 1000; i++) {
            game.turn();
            if (i % 100 == 0)
                b.print_board();
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
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        GridItem g[5184];
        GridItem* grid [5184];
        for (int i = 0; i < 5184; i++)
          grid[i] = &g[i];
        Board b (72, 72, grid);

        Position p (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f1 (creature_type_food, p, &b);
        b.add_creature(&f1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f2 (creature_type_hopper, p, &b);
        b.add_creature(&f2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f3 (creature_type_hopper, p, &b);
        b.add_creature(&f3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f4 (creature_type_hopper, p, &b);
        b.add_creature(&f4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f5 (creature_type_hopper, p, &b);
        b.add_creature(&f5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f6 (creature_type_hopper, p, &b);
        b.add_creature(&f6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f7 (creature_type_hopper, p, &b);
        b.add_creature(&f7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f8 (creature_type_hopper, p, &b);
        b.add_creature(&f8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f9 (creature_type_hopper, p, &b);
        b.add_creature(&f9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature f10 (creature_type_hopper, p, &b);
        b.add_creature(&f10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h2 (creature_type_hopper, p, &b);
        b.add_creature(&h2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h3 (creature_type_hopper, p, &b);
        b.add_creature(&h3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h4 (creature_type_hopper, p, &b);
        b.add_creature(&h4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h5 (creature_type_hopper, p, &b);
        b.add_creature(&h5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h6 (creature_type_hopper, p, &b);
        b.add_creature(&h6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h7 (creature_type_hopper, p, &b);
        b.add_creature(&h7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h8 (creature_type_hopper, p, &b);
        b.add_creature(&h8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h9 (creature_type_hopper, p, &b);
        b.add_creature(&h9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature h10 (creature_type_hopper, p, &b);
        b.add_creature(&h10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r1 (creature_type_rover, p, &b);
        b.add_creature(&r1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r2 (creature_type_rover, p, &b);
        b.add_creature(&r2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r3 (creature_type_rover, p, &b);
        b.add_creature(&r3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r4 (creature_type_rover, p, &b);
        b.add_creature(&r4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r5 (creature_type_rover, p, &b);
        b.add_creature(&r5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r6 (creature_type_rover, p, &b);
        b.add_creature(&r6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r7 (creature_type_rover, p, &b);
        b.add_creature(&r7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r8 (creature_type_rover, p, &b);
        b.add_creature(&r8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r9 (creature_type_rover, p, &b);
        b.add_creature(&r9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature r10 (creature_type_rover, p, &b);
        b.add_creature(&r10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t3 (creature_type_trap, p, &b);
        b.add_creature(&t3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t4 (creature_type_trap, p, &b);
        b.add_creature(&t4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t5 (creature_type_trap, p, &b);
        b.add_creature(&t5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t6 (creature_type_trap, p, &b);
        b.add_creature(&t6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t7 (creature_type_trap, p, &b);
        b.add_creature(&t7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t8 (creature_type_trap, p, &b);
        b.add_creature(&t8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t9 (creature_type_trap, p, &b);
        b.add_creature(&t9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature t10 (creature_type_trap, p, &b);
        b.add_creature(&t10, p);

        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b1 (creature_type_best, p, &b);
        b.add_creature(&b1, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b2 (creature_type_best, p, &b);
        b.add_creature(&b2, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b3 (creature_type_best, p, &b);
        b.add_creature(&b3, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b4 (creature_type_best, p, &b);
        b.add_creature(&b4, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b5 (creature_type_best, p, &b);
        b.add_creature(&b5, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b6 (creature_type_best, p, &b);
        b.add_creature(&b6, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b7 (creature_type_best, p, &b);
        b.add_creature(&b7, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b8 (creature_type_best, p, &b);
        b.add_creature(&b8, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b9 (creature_type_best, p, &b);
        b.add_creature(&b9, p);
        p = Position (rand()%72, rand()%72, static_cast<direction>(rand()%4));
        Creature b10 (creature_type_best, p, &b);
        b.add_creature(&b10, p);

        Game game (b);
        for (int i = 0; i < 10; i++) {
            game.turn();
            b.print_board();
        }
        for (int i = 10; i < 1000; i++) {
            game.turn();
            if (i % 100 == 0)
                b.print_board();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
        /*
        3x3 Darwin
        Trap,   facing south, at (0, 0)
        Trap,   facing south, at (2, 2)
        Rover,  facing north, at (2, 0)
        Rover,   facing north,  at (0, 2)
        Simulate 5 moves.
        Print every grid.
        */
        GridItem g[9];
        GridItem* grid [9];
        for (int i = 0; i < 9; i++)
          grid[i] = &g[i];
        Board b (3, 3, grid);

        Position p (0, 0, direction_down);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (2, 2, direction_down);
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);

        p = Position (2, 0, direction_up);
        Creature r1 (creature_type_rover, p, &b);
        b.add_creature(&r1, p);

        p = Position (0, 2, direction_up);
        Creature r2 (creature_type_rover, p, &b);
        b.add_creature(&r2, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 5; i++) {
            game.turn();
            b.print_board();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 3x3 from rgriege
    // ----------

    {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
        /*
        3x3 Darwin
        Trap, facing south, at (1, 1)
        Rover, facing east, at (0, 0)
        Simulate 16 moves.
        Print every grid.
        */
        GridItem g[9];
        GridItem* grid [9];
        for (int i = 0; i < 9; i++)
          grid[i] = &g[i];
        Board b (3, 3, grid);

        Position p (1, 1, direction_down);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (0, 0, direction_right);
        Creature r1 (creature_type_rover, p, &b);
        b.add_creature(&r1, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 16; i++) {
            game.turn();
            b.print_board();
        }
    }

    // ----------
    // darwin 3x3 from aaronv92
    // ----------

    try {
        /*
        3X3 Darwin
        Hopper, facing north, at (0, 0)
        Hopper, facing north, at (0, 1)
        Hopper, facing north, at (0, 2)
        Hopper, facing north, at (1, 0)
        Hopper, facing north, at (1, 1)
        Hopper, facing north, at (1, 2)
        Trap, facing north, at (2, 0)
        Trap, facing north, at (2, 1)
        Rover, facing north, at (2, 2)

        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** Darwin 3X3 ***" << endl;
        srand(0);

        GridItem g[9];
        GridItem* grid [9];
        for (int i = 0; i < 9; i++)
          grid[i] = &g[i];
        Board b (3, 3, grid);

        Position p (0, 0, direction_down);
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);

        p = Position (1, 0, direction_right);
        Creature h2 (creature_type_hopper, p, &b);
        b.add_creature(&h2, p);

        p = Position (2, 0, direction_right);
        Creature h3 (creature_type_hopper, p, &b);
        b.add_creature(&h3, p);

        p = Position (0, 1, direction_right);
        Creature h4 (creature_type_hopper, p, &b);
        b.add_creature(&h4, p);

        p = Position (1, 1, direction_right);
        Creature h5 (creature_type_hopper, p, &b);
        b.add_creature(&h5, p);

        p = Position (2, 1, direction_right);
        Creature h6 (creature_type_hopper, p, &b);
        b.add_creature(&h6, p);

        p = Position (0, 2, direction_right);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (1, 2, direction_right);
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);

        p = Position (2, 2, direction_right);
        Creature r (creature_type_rover, p, &b);
        b.add_creature(&r, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 5; i++) {
            game.turn();
            b.print_board();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 1x10 from abrame13
    // ------------

    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        /*
        place a trap on the left and a line of hoppers to the right
        sim 1 turn
        everything should be a trap
        */
        GridItem g[10];
        GridItem* grid [10];
        for (int i = 0; i < 10; i++)
          grid[i] = &g[i];
        Board b (10, 1, grid);

        Position p (0, 0, direction_right);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (1, 0, direction_right);
        Creature h1 (creature_type_rover, p, &b);
        b.add_creature(&h1, p);

        p = Position (2, 0, direction_right);
        Creature h2 (creature_type_rover, p, &b);
        b.add_creature(&h2, p);

        p = Position (3, 0, direction_right);
        Creature h3 (creature_type_rover, p, &b);
        b.add_creature(&h3, p);

        p = Position (4, 0, direction_right);
        Creature h4 (creature_type_rover, p, &b);
        b.add_creature(&h4, p);

        p = Position (5, 0, direction_right);
        Creature h5 (creature_type_rover, p, &b);
        b.add_creature(&h5, p);

        p = Position (6, 0, direction_right);
        Creature h6 (creature_type_rover, p, &b);
        b.add_creature(&h6, p);

        p = Position (7, 0, direction_right);
        Creature h7 (creature_type_rover, p, &b);
        b.add_creature(&h7, p);

        p = Position (8, 0, direction_right);
        Creature h8 (creature_type_rover, p, &b);
        b.add_creature(&h8, p);

        p = Position (9, 0, direction_right);
        Creature h9 (creature_type_rover, p, &b);
        b.add_creature(&h9, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 1; i++) {
            game.turn();
            b.print_board();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    //  1x60 from austind
    // ------------

    {
        cout << "*** 1x60 Test for Meeting a Friend ***" << endl;
        /*
        1x60 Darwin
        1 Hopper, facing east, at (0, 0)
        1 Hopper, facing west, at (0, 59)
        Simulate 29 moves
        Print the first and last grid.
        */
        GridItem g[60];
        GridItem* grid [60];
        for (int i = 0; i < 60; i++)
          grid[i] = &g[i];
        Board b (60, 1, grid);

        Position p (0, 0, direction_right);
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);

        p = Position (59, 0, direction_left);
        Creature h2 (creature_type_hopper, p, &b);
        b.add_creature(&h2, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 29; i++) {
            game.turn();
            b.print_board();
        }
    }

    // ----------
    // darwin 10x10 from daraoke
    // ALL FOUR CORNERS
    // ----------
    
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        
        /*
        10x10 Darwin
        Trap, facing north, at (0, 0)
        Hopper, facing west, at (9, 0)
        Rover, facing north, at (0, 9)
        Trap, facing south, at (9, 9)
        Simulate 10 moves.
        Print every grid.
        */
        
        GridItem g[100];
        GridItem* grid [100];
        for (int i = 0; i < 100; i++)
          grid[i] = &g[i];
        Board b (10, 10, grid);

        Position p (0, 0, direction_up);
        Creature t1 (creature_type_trap, p, &b);
        b.add_creature(&t1, p);

        p = Position (0, 9, direction_left);
        Creature h1 (creature_type_hopper, p, &b);
        b.add_creature(&h1, p);

        p = Position (9, 0, direction_up);
        Creature r (creature_type_rover, p, &b);
        b.add_creature(&r, p);

        p = Position (9, 9, direction_down);
        Creature t2 (creature_type_trap, p, &b);
        b.add_creature(&t2, p);

        Game game (b);
        b.print_board();
        for (int i = 0; i < 10; i++) {
            game.turn();
            b.print_board();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}


   