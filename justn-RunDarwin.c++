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
    Species food('f');
    food.addInstruction(Instr::left);
    food.addInstruction(Instr::go, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
     Species hopper('h');
     hopper.addInstruction(Instr::hop);
     hopper.addInstruction(Instr::go, 0);

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
    rover.addInstruction(Instr::if_enemy, 9);
    rover.addInstruction(Instr::if_empty, 7);
    rover.addInstruction(Instr::if_random, 5);
    rover.addInstruction(Instr::left);
    rover.addInstruction(Instr::go, 0);
    rover.addInstruction(Instr::right);
    rover.addInstruction(Instr::go, 0);
    rover.addInstruction(Instr::hop);
    rover.addInstruction(Instr::go, 0);
    rover.addInstruction(Instr::infect);
    rover.addInstruction(Instr::go, 0);

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
    trap.addInstruction(Instr::if_enemy, 3);
    trap.addInstruction(Instr::left);
    trap.addInstruction(Instr::go, 0);
    trap.addInstruction(Instr::infect);
    trap.addInstruction(Instr::go, 0);

    // ----
    // best
    // ----
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_wall 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    Species best('b');
    best.addInstruction(Instr::if_enemy, 9);
    best.addInstruction(Instr::if_empty, 7);
    best.addInstruction(Instr::if_wall, 5);
    best.addInstruction(Instr::left);
    best.addInstruction(Instr::go, 0);
    best.addInstruction(Instr::right);
    best.addInstruction(Instr::go, 0);
    best.addInstruction(Instr::hop);
    best.addInstruction(Instr::go, 0);
    best.addInstruction(Instr::infect);
    best.addInstruction(Instr::go, 0);

    /*
     0: if_enemy 4
     1: if_empty 6
     2: if_wall 8
     3: go 10
     4: infect
     5: go 0
     6: hop
     7: go 0
     8: left
     9: go 0
    10: left
    11: go 0
    */
    // best.addInstruction(Instr::if_enemy, 4);
    // best.addInstruction(Instr::if_empty, 6);
    // best.addInstruction(Instr::if_wall, 8);
    // best.addInstruction(Instr::go, 6);
    // best.addInstruction(Instr::infect);
    // best.addInstruction(Instr::go, 0);
    // best.addInstruction(Instr::hop);
    // best.addInstruction(Instr::go, 0);
    // best.addInstruction(Instr::left);
    // best.addInstruction(Instr::go, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
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
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin d(8, 8);

        Creature f1(food);
        d.addCreature(f1, 0, 0, Dir::east);
        Creature h2(hopper);
        d.addCreature(h2, 3, 3, Dir::north);
        Creature h3(hopper);
        d.addCreature(h3, 3, 4, Dir::east);
        Creature h4(hopper);
        d.addCreature(h4, 4, 4, Dir::south);
        Creature h5(hopper);
        d.addCreature(h5, 4, 3, Dir::west);
        Creature f6(food);
        d.addCreature(f6, 7, 7, Dir::north);

        d.printGame();
        d.simulate(5, true);
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


        Darwin d(7, 9);

        Creature t1(trap);
        d.addCreature(t1, 0, 0, Dir::south);
        Creature h2(hopper);
        d.addCreature(h2, 3, 2, Dir::east);
        Creature r3(rover);
        d.addCreature(r3, 5, 4, Dir::north);
        Creature t4(trap);
        d.addCreature(t4, 6, 8, Dir::west);

        d.printGame();
        d.simulate(5, true);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // darwin 8x8
    // ----------

    try {
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
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        Darwin d(10, 10);

        Creature f1(food);
        d.addCreature(f1, 0, 0, Dir::east);
        Creature h2(hopper);
        d.addCreature(h2, 3, 3, Dir::north);
        Creature h3(hopper);
        d.addCreature(h3, 3, 4, Dir::east);
        Creature h4(hopper);
        d.addCreature(h4, 4, 4, Dir::south);
        Creature r5(rover);
        d.addCreature(r5, 4, 3, Dir::west);
        Creature f6(food);
        d.addCreature(f6, 7, 7, Dir::north);

        d.printGame();
        d.simulate(20, true);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Hoppers Trapped 4x4 ***" << endl;
        srand(0);
        Darwin d(4, 4);
        Creature c1(hopper);
        Creature c2(hopper);
        Creature c3(hopper);
        Creature c4(hopper);
        d.addCreature(c1, 0, 0, Dir::east);
        d.addCreature(c2, 0, 1, Dir::south);
        d.addCreature(c3, 1, 1, Dir::west);
        d.addCreature(c4, 1, 0, Dir::north);
        d.printGame();
        for (int i = 1; i <= 10; i++){
            d.simulate();
            d.printGame();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 10x15 ***" << endl;
        srand(0);
        
        Darwin d(10, 15);

        Creature t1(trap);
        Creature h2(hopper);
        Creature r3(rover);
        Creature t4(trap);
        Creature f5(food);
        Creature r6(rover);
        Creature h7(hopper);
        Creature t8(trap);
        d.addCreature(t1, 0, 0, Dir::south);
        d.addCreature(h2, 3, 2, Dir::east);
        d.addCreature(r3, 5, 4, Dir::north);
        d.addCreature(t4, 9, 11, Dir::north);
        d.addCreature(f5, 8, 8, Dir::west);
        d.addCreature(r6, 2, 10, Dir::east);
        d.addCreature(h7, 1, 3, Dir::south);
        d.addCreature(t8, 6, 8, Dir::west);
        
        for (int i = 0; i < 20; i++) {
            if (i % 5 == 0) d.printGame();
            d.simulate();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        /*
        3x12
        6 Rover
        6 Trap
        Steps 0-22
        */
        cout << "*** mine #2, " << 3 << "x" << 12 << " ***" << "\n";
        srand(0);

        Darwin  d(3, 12);

        Creature r1(rover);
        d.addCreature(r1, 0, 5, Dir::west);
        Creature r2(rover);
        d.addCreature(r2, 1, 5, Dir::west);
        Creature r3(rover);
        d.addCreature(r3, 2, 5, Dir::west);
        Creature r4(rover);
        d.addCreature(r4, 0, 6, Dir::east);
        Creature r5(rover);
        d.addCreature(r5, 1, 6, Dir::east);
        Creature r6(rover);
        d.addCreature(r6, 2, 6, Dir::east);

        Creature t1(trap);
        d.addCreature(t1, 0, 0, Dir::east);
        Creature t2(trap);
        d.addCreature(t2, 0, 1, Dir::east);
        Creature t3(trap);
        d.addCreature(t3, 1, 0, Dir::east);
        Creature t4(trap);
        d.addCreature(t4, 1, 11, Dir::west);
        Creature t5(trap);
        d.addCreature(t5, 2, 10, Dir::west);
        Creature t6(trap);
        d.addCreature(t6, 2, 11, Dir::west);

        d.simulate(2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


// ------------
// darwin 10x10
// ------------

    try{
        cout << "*** Darwin 10X10 Test 1***" << endl;
        srand(0);
        Darwin d(10, 10);
        Creature c1(trap);
        Creature c2(rover);
        Creature c3(hopper);
        Creature c4(hopper);
        Creature c5(food);
        Creature c6(rover);
        d.addCreature(c1, 2, 3, Dir::south);
        d.addCreature(c2, 3, 1, Dir::north);
        d.addCreature(c3, 0, 0, Dir::south);
        d.addCreature(c4, 0, 1, Dir::east);
        d.addCreature(c5, 7, 7, Dir::east);
        d.addCreature(c6, 4, 9, Dir::south);
        d.simulate(25); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// ------------
// darwin 1x10
// ------------

try {
cout << "*** Darwin 1x10 ***" << endl;
srand(0);
/*
    place a trap on the left and a line of hoppers to the right
    sim 1 turn
    everything should be a trap
    */

    Darwin d(1, 10);

    Creature t1(trap);
    Creature h2(hopper);
    Creature h3(hopper);
    Creature h4(hopper);
    Creature h5(hopper);
    Creature h6(hopper);
    Creature h7(hopper);
    Creature h8(hopper);
    Creature h9(hopper);
    Creature h10(hopper);
    d.addCreature(t1, 0, 0, Dir::east);
    d.addCreature(h2, 0, 1, Dir::east);
    d.addCreature(h3, 0, 2, Dir::east);
    d.addCreature(h4, 0, 3, Dir::east);
    d.addCreature(h5, 0, 4, Dir::east);
    d.addCreature(h6, 0, 5, Dir::east);
    d.addCreature(h7, 0, 6, Dir::east);
    d.addCreature(h8, 0, 7, Dir::east);
    d.addCreature(h9, 0, 8, Dir::east);
    d.addCreature(h10, 0, 9, Dir::east);

    // do the sim
    d.printGame();
    d.simulate();
    d.printGame();
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
        int row, col, random, dir;

         // r = x / 72, c = x % 72

        Creature f1(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f1, row, col, dir);
        Creature f2(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f2, row, col, dir);
        Creature f3(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f3, row, col, dir);
        Creature f4(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f4, row, col, dir);
        Creature f5(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f5, row, col, dir);
        Creature f6(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f6, row, col, dir);
        Creature f7(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f7, row, col, dir);
        Creature f8(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f8, row, col, dir);
        Creature f9(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f9, row, col, dir);
        Creature f10(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f10, row, col, dir);

        Creature h1(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h1, row, col, dir);
        Creature h2(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h2, row, col, dir);
        Creature h3(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h3, row, col, dir);
        Creature h4(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h4, row, col, dir);
        Creature h5(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h5, row, col, dir);
        Creature h6(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h6, row, col, dir);
        Creature h7(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h7, row, col, dir);
        Creature h8(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h8, row, col, dir);
        Creature h9(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h9, row, col, dir);
        Creature h10(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h10, row, col, dir);

        Creature r1(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r1, row, col, dir);
        Creature r2(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r2, row, col, dir);
        Creature r3(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r3, row, col, dir);
        Creature r4(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r4, row, col, dir);
        Creature r5(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r5, row, col, dir);
        Creature r6(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r6, row, col, dir);
        Creature r7(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r7, row, col, dir);
        Creature r8(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r8, row, col, dir);
        Creature r9(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r9, row, col, dir);
        Creature r10(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r10, row, col, dir);

        Creature t1(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t1, row, col, dir);
        Creature t2(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t2, row, col, dir);
        Creature t3(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t3, row, col, dir);
        Creature t4(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t4, row, col, dir);
        Creature t5(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t5, row, col, dir);
        Creature t6(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t6, row, col, dir);
        Creature t7(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t7, row, col, dir);
        Creature t8(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t8, row, col, dir);
        Creature t9(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t9, row, col, dir);
        Creature t10(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t10, row, col, dir);


        std::cout << "Turn: " << 0 << std::endl;
        d.printGame();
        for (int i = 1; i <= 1000; i++) {
            d.simulate();
            if (i < 10) {
                std::cout << "Turn: " << i << std::endl;
                d.printGame();
            }
            if (!(i%100)) {
                std::cout << "Turn: " << i << std::endl;
                d.printGame();
            }
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

               Darwin d(72, 72);
        int row, col, random, dir;

         // r = x / 72, c = x % 72

        Creature f1(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f1, row, col, dir);
        Creature f2(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f2, row, col, dir);
        Creature f3(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f3, row, col, dir);
        Creature f4(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f4, row, col, dir);
        Creature f5(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f5, row, col, dir);
        Creature f6(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f6, row, col, dir);
        Creature f7(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f7, row, col, dir);
        Creature f8(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f8, row, col, dir);
        Creature f9(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f9, row, col, dir);
        Creature f10(food);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(f10, row, col, dir);

        Creature h1(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h1, row, col, dir);
        Creature h2(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h2, row, col, dir);
        Creature h3(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h3, row, col, dir);
        Creature h4(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h4, row, col, dir);
        Creature h5(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h5, row, col, dir);
        Creature h6(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h6, row, col, dir);
        Creature h7(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h7, row, col, dir);
        Creature h8(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h8, row, col, dir);
        Creature h9(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h9, row, col, dir);
        Creature h10(hopper);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(h10, row, col, dir);

        Creature r1(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r1, row, col, dir);
        Creature r2(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r2, row, col, dir);
        Creature r3(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r3, row, col, dir);
        Creature r4(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r4, row, col, dir);
        Creature r5(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r5, row, col, dir);
        Creature r6(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r6, row, col, dir);
        Creature r7(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r7, row, col, dir);
        Creature r8(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r8, row, col, dir);
        Creature r9(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r9, row, col, dir);
        Creature r10(rover);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(r10, row, col, dir);

        Creature t1(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t1, row, col, dir);
        Creature t2(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t2, row, col, dir);
        Creature t3(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t3, row, col, dir);
        Creature t4(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t4, row, col, dir);
        Creature t5(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t5, row, col, dir);
        Creature t6(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t6, row, col, dir);
        Creature t7(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t7, row, col, dir);
        Creature t8(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t8, row, col, dir);
        Creature t9(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t9, row, col, dir);
        Creature t10(trap);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(t10, row, col, dir);

        Creature b1(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b1, row, col, dir);
        Creature b2(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b2, row, col, dir);
        Creature b3(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b3, row, col, dir);
        Creature b4(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b4, row, col, dir);
        Creature b5(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b5, row, col, dir);
        Creature b6(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b6, row, col, dir);
        Creature b7(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b7, row, col, dir);
        Creature b8(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b8, row, col, dir);
        Creature b9(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b9, row, col, dir);
        Creature b10(best);
        random = rand() % 5184;
        row = random / 72;
        col = random % 72;
        dir = rand() % 4;
        d.addCreature(b10, row, col, dir);

        std::cout << "Turn: " << 0 << std::endl;
        d.printGame();
        for (int i = 1; i <= 1000; i++) {
            d.simulate();
            if (i < 10) {
                std::cout << "Turn: " << i << std::endl;
                d.printGame();
            }
            if (!(i%100)) {
                std::cout << "Turn: " << i << std::endl;
                d.printGame();
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
