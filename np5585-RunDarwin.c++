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

extern Program best;

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
    Program food = Program('f')
      .left().go(0);


    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Program hopper = Program('h')
      .hop().go(0);

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
    Program rover = Program('r')
      .if_enemy(9)
      .if_empty(7)
      .if_random(5)
        .left()
       .go(0)
        .right()
       .go(0)
        .hop()
       .go(0)
        .infect()
       .go(0);

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
    Program trap = Program('t')
      .if_enemy(3)
        .left()
       .go(0)
        .infect()
       .go(0);

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
        World<8, 8> mir;

        Creature
          f1(food, direction::EAST),
          h1(hopper, direction::NORTH),
          h2(hopper, direction::EAST),
          h3(hopper, direction::SOUTH),
          h4(hopper, direction::WEST),
          f2(food, direction::NORTH);

        mir.enter(&f1, 0, 0);
        mir.enter(&h1, 3, 3);
        mir.enter(&h2, 3, 4);
        mir.enter(&h3, 4, 4);
        mir.enter(&h4, 4, 3);
        mir.enter(&f2, 7, 7);

        mir.conduct(std::cout, 5);
        std::cout << std::endl << std::endl;

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
        World<7, 9> mir;

        Creature
          t1(trap, direction::SOUTH),
          h1(hopper, direction::EAST),
          r1(rover, direction::NORTH),
          t2(trap, direction::WEST);

        mir.enter(&t1, 0, 0);
        mir.enter(&h1, 3, 2);
        mir.enter(&r1, 5, 4);
        mir.enter(&t2, 6, 8);

        mir.conduct(std::cout, 5);
        std::cout << std::endl << std::endl;
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
        World<72, 72> mir;

        Creature 
        c0(food, static_cast<direction>(rand()%4)),
        c1(food, static_cast<direction>(rand()%4)),
        c2(food, static_cast<direction>(rand()%4)),
        c3(food, static_cast<direction>(rand()%4)),
        c4(food, static_cast<direction>(rand()%4)),
        c5(food, static_cast<direction>(rand()%4)),
        c6(food, static_cast<direction>(rand()%4)),
        c7(food, static_cast<direction>(rand()%4)),
        c8(food, static_cast<direction>(rand()%4)),
        c9(food, static_cast<direction>(rand()%4)),
        c10(hopper, static_cast<direction>(rand()%4)),
        c11(hopper, static_cast<direction>(rand()%4)),
        c12(hopper, static_cast<direction>(rand()%4)),
        c13(hopper, static_cast<direction>(rand()%4)),
        c14(hopper, static_cast<direction>(rand()%4)),
        c15(hopper, static_cast<direction>(rand()%4)),
        c16(hopper, static_cast<direction>(rand()%4)),
        c17(hopper, static_cast<direction>(rand()%4)),
        c18(hopper, static_cast<direction>(rand()%4)),
        c19(hopper, static_cast<direction>(rand()%4)),
        c20(rover, static_cast<direction>(rand()%4)),
        c21(rover, static_cast<direction>(rand()%4)),
        c22(rover, static_cast<direction>(rand()%4)),
        c23(rover, static_cast<direction>(rand()%4)),
        c24(rover, static_cast<direction>(rand()%4)),
        c25(rover, static_cast<direction>(rand()%4)),
        c26(rover, static_cast<direction>(rand()%4)),
        c27(rover, static_cast<direction>(rand()%4)),
        c28(rover, static_cast<direction>(rand()%4)),
        c29(rover, static_cast<direction>(rand()%4)),
        c30(trap, static_cast<direction>(rand()%4)),
        c31(trap, static_cast<direction>(rand()%4)),
        c32(trap, static_cast<direction>(rand()%4)),
        c33(trap, static_cast<direction>(rand()%4)),
        c34(trap, static_cast<direction>(rand()%4)),
        c35(trap, static_cast<direction>(rand()%4)),
        c36(trap, static_cast<direction>(rand()%4)),
        c37(trap, static_cast<direction>(rand()%4)),
        c38(trap, static_cast<direction>(rand()%4)),
        c39(trap, static_cast<direction>(rand()%4));

        mir.enter(&c0, rand()%72, rand()%72);
        mir.enter(&c1, rand()%72, rand()%72);
        mir.enter(&c2, rand()%72, rand()%72);
        mir.enter(&c3, rand()%72, rand()%72);
        mir.enter(&c4, rand()%72, rand()%72);
        mir.enter(&c5, rand()%72, rand()%72);
        mir.enter(&c6, rand()%72, rand()%72);
        mir.enter(&c7, rand()%72, rand()%72);
        mir.enter(&c8, rand()%72, rand()%72);
        mir.enter(&c9, rand()%72, rand()%72);
        mir.enter(&c10, rand()%72, rand()%72);
        mir.enter(&c11, rand()%72, rand()%72);
        mir.enter(&c12, rand()%72, rand()%72);
        mir.enter(&c13, rand()%72, rand()%72);
        mir.enter(&c14, rand()%72, rand()%72);
        mir.enter(&c15, rand()%72, rand()%72);
        mir.enter(&c16, rand()%72, rand()%72);
        mir.enter(&c17, rand()%72, rand()%72);
        mir.enter(&c18, rand()%72, rand()%72);
        mir.enter(&c19, rand()%72, rand()%72);
        mir.enter(&c20, rand()%72, rand()%72);
        mir.enter(&c21, rand()%72, rand()%72);
        mir.enter(&c22, rand()%72, rand()%72);
        mir.enter(&c23, rand()%72, rand()%72);
        mir.enter(&c24, rand()%72, rand()%72);
        mir.enter(&c25, rand()%72, rand()%72);
        mir.enter(&c26, rand()%72, rand()%72);
        mir.enter(&c27, rand()%72, rand()%72);
        mir.enter(&c28, rand()%72, rand()%72);
        mir.enter(&c29, rand()%72, rand()%72);
        mir.enter(&c30, rand()%72, rand()%72);
        mir.enter(&c31, rand()%72, rand()%72);
        mir.enter(&c32, rand()%72, rand()%72);
        mir.enter(&c33, rand()%72, rand()%72);
        mir.enter(&c34, rand()%72, rand()%72);
        mir.enter(&c35, rand()%72, rand()%72);
        mir.enter(&c36, rand()%72, rand()%72);
        mir.enter(&c37, rand()%72, rand()%72);
        mir.enter(&c38, rand()%72, rand()%72);
        mir.enter(&c39, rand()%72, rand()%72);
        
        mir.conduct(std::cout, 9);
        mir.conduct(std::cout, 991, 100);

        std::cout << std::endl << std::endl;
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
        World<72, 72> mir;

        Creature 
        b0(best, static_cast<direction>(rand()%4)),
        b1(best, static_cast<direction>(rand()%4)),
        b2(best, static_cast<direction>(rand()%4)),
        b3(best, static_cast<direction>(rand()%4)),
        b4(best, static_cast<direction>(rand()%4)),
        b5(best, static_cast<direction>(rand()%4)),
        b6(best, static_cast<direction>(rand()%4)),
        b7(best, static_cast<direction>(rand()%4)),
        b8(best, static_cast<direction>(rand()%4)),
        b9(best, static_cast<direction>(rand()%4)),
        c0(food, static_cast<direction>(rand()%4)),
        c1(food, static_cast<direction>(rand()%4)),
        c2(food, static_cast<direction>(rand()%4)),
        c3(food, static_cast<direction>(rand()%4)),
        c4(food, static_cast<direction>(rand()%4)),
        c5(food, static_cast<direction>(rand()%4)),
        c6(food, static_cast<direction>(rand()%4)),
        c7(food, static_cast<direction>(rand()%4)),
        c8(food, static_cast<direction>(rand()%4)),
        c9(food, static_cast<direction>(rand()%4)),
        c10(hopper, static_cast<direction>(rand()%4)),
        c11(hopper, static_cast<direction>(rand()%4)),
        c12(hopper, static_cast<direction>(rand()%4)),
        c13(hopper, static_cast<direction>(rand()%4)),
        c14(hopper, static_cast<direction>(rand()%4)),
        c15(hopper, static_cast<direction>(rand()%4)),
        c16(hopper, static_cast<direction>(rand()%4)),
        c17(hopper, static_cast<direction>(rand()%4)),
        c18(hopper, static_cast<direction>(rand()%4)),
        c19(hopper, static_cast<direction>(rand()%4)),
        c20(rover, static_cast<direction>(rand()%4)),
        c21(rover, static_cast<direction>(rand()%4)),
        c22(rover, static_cast<direction>(rand()%4)),
        c23(rover, static_cast<direction>(rand()%4)),
        c24(rover, static_cast<direction>(rand()%4)),
        c25(rover, static_cast<direction>(rand()%4)),
        c26(rover, static_cast<direction>(rand()%4)),
        c27(rover, static_cast<direction>(rand()%4)),
        c28(rover, static_cast<direction>(rand()%4)),
        c29(rover, static_cast<direction>(rand()%4)),
        c30(trap, static_cast<direction>(rand()%4)),
        c31(trap, static_cast<direction>(rand()%4)),
        c32(trap, static_cast<direction>(rand()%4)),
        c33(trap, static_cast<direction>(rand()%4)),
        c34(trap, static_cast<direction>(rand()%4)),
        c35(trap, static_cast<direction>(rand()%4)),
        c36(trap, static_cast<direction>(rand()%4)),
        c37(trap, static_cast<direction>(rand()%4)),
        c38(trap, static_cast<direction>(rand()%4)),
        c39(trap, static_cast<direction>(rand()%4));

        mir.enter(&b0, rand()%72, rand()%72);
        mir.enter(&b1, rand()%72, rand()%72);
        mir.enter(&b2, rand()%72, rand()%72);
        mir.enter(&b3, rand()%72, rand()%72);
        mir.enter(&b4, rand()%72, rand()%72);
        mir.enter(&b5, rand()%72, rand()%72);
        mir.enter(&b6, rand()%72, rand()%72);
        mir.enter(&b7, rand()%72, rand()%72);
        mir.enter(&b8, rand()%72, rand()%72);
        mir.enter(&b9, rand()%72, rand()%72);
        mir.enter(&c0, rand()%72, rand()%72);
        mir.enter(&c1, rand()%72, rand()%72);
        mir.enter(&c2, rand()%72, rand()%72);
        mir.enter(&c3, rand()%72, rand()%72);
        mir.enter(&c4, rand()%72, rand()%72);
        mir.enter(&c5, rand()%72, rand()%72);
        mir.enter(&c6, rand()%72, rand()%72);
        mir.enter(&c7, rand()%72, rand()%72);
        mir.enter(&c8, rand()%72, rand()%72);
        mir.enter(&c9, rand()%72, rand()%72);
        mir.enter(&c10, rand()%72, rand()%72);
        mir.enter(&c11, rand()%72, rand()%72);
        mir.enter(&c12, rand()%72, rand()%72);
        mir.enter(&c13, rand()%72, rand()%72);
        mir.enter(&c14, rand()%72, rand()%72);
        mir.enter(&c15, rand()%72, rand()%72);
        mir.enter(&c16, rand()%72, rand()%72);
        mir.enter(&c17, rand()%72, rand()%72);
        mir.enter(&c18, rand()%72, rand()%72);
        mir.enter(&c19, rand()%72, rand()%72);
        mir.enter(&c20, rand()%72, rand()%72);
        mir.enter(&c21, rand()%72, rand()%72);
        mir.enter(&c22, rand()%72, rand()%72);
        mir.enter(&c23, rand()%72, rand()%72);
        mir.enter(&c24, rand()%72, rand()%72);
        mir.enter(&c25, rand()%72, rand()%72);
        mir.enter(&c26, rand()%72, rand()%72);
        mir.enter(&c27, rand()%72, rand()%72);
        mir.enter(&c28, rand()%72, rand()%72);
        mir.enter(&c29, rand()%72, rand()%72);
        mir.enter(&c30, rand()%72, rand()%72);
        mir.enter(&c31, rand()%72, rand()%72);
        mir.enter(&c32, rand()%72, rand()%72);
        mir.enter(&c33, rand()%72, rand()%72);
        mir.enter(&c34, rand()%72, rand()%72);
        mir.enter(&c35, rand()%72, rand()%72);
        mir.enter(&c36, rand()%72, rand()%72);
        mir.enter(&c37, rand()%72, rand()%72);
        mir.enter(&c38, rand()%72, rand()%72);
        mir.enter(&c39, rand()%72, rand()%72);
        
        mir.conduct(std::cout, 9);
        mir.conduct(std::cout, 991, 100);

        std::cout << std::endl << std::endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}







    /* END OF DOWNING'S ACCEPTANCE TESTS */






    try {
        cout << "*** AT 1 ***" << endl;
        World<8, 8> mir;

        Creature
          h0(rover, direction::NORTH),
          h1(rover, direction::NORTH),
          h2(rover, direction::NORTH),
          h3(rover, direction::NORTH),
          h4(rover, direction::NORTH),
          h5(rover, direction::NORTH),
          f1(food, direction::NORTH),
          f2(food, direction::NORTH),
          f3(food, direction::NORTH),
          f4(food, direction::NORTH),
          f5(food, direction::NORTH),
          f6(food, direction::NORTH),
          f7(food, direction::NORTH);

        mir.enter(&h1, 3, 3);
        mir.enter(&h2, 3, 4);
        mir.enter(&h3, 4, 4);
        mir.enter(&h4, 4, 3);
        mir.enter(&h5, 7, 7);
        mir.enter(&f1, 0, 1);
        mir.enter(&f2, 0, 2);
        mir.enter(&f3, 0, 3);
        mir.enter(&f4, 0, 4);
        mir.enter(&f5, 0, 5);
        mir.enter(&f6, 0, 6);
        mir.enter(&f7, 0, 7);

        mir.conduct(std::cout, 5);
        std::cout << std::endl << std::endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** AT 2 ***" << endl;
        World<8, 8> mir;

        Creature
          h0(food, direction::NORTH),
          h1(food, direction::NORTH),
          h2(food, direction::NORTH),
          h3(food, direction::NORTH),
          h4(food, direction::NORTH),
          h5(food, direction::NORTH),
          f1(rover, direction::NORTH),
          f2(rover, direction::NORTH),
          f3(rover, direction::NORTH),
          f4(rover, direction::NORTH),
          f5(rover, direction::NORTH),
          f6(rover, direction::NORTH),
          f7(rover, direction::NORTH);

        mir.enter(&h1, 3, 3);
        mir.enter(&h2, 3, 4);
        mir.enter(&h3, 4, 4);
        mir.enter(&h4, 4, 3);
        mir.enter(&h5, 7, 7);
        mir.enter(&f1, 0, 1);
        mir.enter(&f2, 0, 2);
        mir.enter(&f3, 0, 3);
        mir.enter(&f4, 0, 4);
        mir.enter(&f5, 0, 5);
        mir.enter(&f6, 0, 6);
        mir.enter(&f7, 0, 7);

        mir.conduct(std::cout, 5);
        std::cout << std::endl << std::endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** AT3 ***" << endl;
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
        World<72, 72> mir;
        Creature 
        b0(best, static_cast<direction>(rand()%4)),
        b1(best, static_cast<direction>(rand()%4)),
        b2(best, static_cast<direction>(rand()%4)),
        b3(best, static_cast<direction>(rand()%4)),
        b4(best, static_cast<direction>(rand()%4)),
        b5(best, static_cast<direction>(rand()%4)),
        b6(best, static_cast<direction>(rand()%4)),
        b7(best, static_cast<direction>(rand()%4)),
        b8(best, static_cast<direction>(rand()%4)),
        b9(best, static_cast<direction>(rand()%4)),
        c0(food, static_cast<direction>(rand()%4)),
        c1(food, static_cast<direction>(rand()%4)),
        c2(food, static_cast<direction>(rand()%4)),
        c3(food, static_cast<direction>(rand()%4)),
        c4(food, static_cast<direction>(rand()%4)),
        c5(food, static_cast<direction>(rand()%4)),
        c6(food, static_cast<direction>(rand()%4)),
        c7(food, static_cast<direction>(rand()%4)),
        c8(food, static_cast<direction>(rand()%4)),
        c9(food, static_cast<direction>(rand()%4)),
        c10(hopper, static_cast<direction>(rand()%4)),
        c11(hopper, static_cast<direction>(rand()%4)),
        c12(hopper, static_cast<direction>(rand()%4)),
        c13(hopper, static_cast<direction>(rand()%4)),
        c14(hopper, static_cast<direction>(rand()%4)),
        c15(hopper, static_cast<direction>(rand()%4)),
        c16(hopper, static_cast<direction>(rand()%4)),
        c17(hopper, static_cast<direction>(rand()%4)),
        c18(hopper, static_cast<direction>(rand()%4)),
        c19(hopper, static_cast<direction>(rand()%4)),
        c20(rover, static_cast<direction>(rand()%4)),
        c21(rover, static_cast<direction>(rand()%4)),
        c22(rover, static_cast<direction>(rand()%4)),
        c23(rover, static_cast<direction>(rand()%4)),
        c24(rover, static_cast<direction>(rand()%4)),
        c25(rover, static_cast<direction>(rand()%4)),
        c26(rover, static_cast<direction>(rand()%4)),
        c27(rover, static_cast<direction>(rand()%4)),
        c28(rover, static_cast<direction>(rand()%4)),
        c29(rover, static_cast<direction>(rand()%4)),
        c30(trap, static_cast<direction>(rand()%4)),
        c31(trap, static_cast<direction>(rand()%4)),
        c32(trap, static_cast<direction>(rand()%4)),
        c33(trap, static_cast<direction>(rand()%4)),
        c34(trap, static_cast<direction>(rand()%4)),
        c35(trap, static_cast<direction>(rand()%4)),
        c36(trap, static_cast<direction>(rand()%4)),
        c37(trap, static_cast<direction>(rand()%4)),
        c38(trap, static_cast<direction>(rand()%4)),
        c39(trap, static_cast<direction>(rand()%4));

        mir.enter(&b0, rand()%72, rand()%72);
        mir.enter(&b1, rand()%72, rand()%72);
        mir.enter(&b2, rand()%72, rand()%72);
        mir.enter(&b3, rand()%72, rand()%72);
        mir.enter(&b4, rand()%72, rand()%72);
        mir.enter(&b5, rand()%72, rand()%72);
        mir.enter(&b6, rand()%72, rand()%72);
        mir.enter(&b7, rand()%72, rand()%72);
        mir.enter(&b8, rand()%72, rand()%72);
        mir.enter(&b9, rand()%72, rand()%72);
        mir.enter(&c0, rand()%72, rand()%72);
        mir.enter(&c1, rand()%72, rand()%72);
        mir.enter(&c2, rand()%72, rand()%72);
        mir.enter(&c3, rand()%72, rand()%72);
        mir.enter(&c4, rand()%72, rand()%72);
        mir.enter(&c5, rand()%72, rand()%72);
        mir.enter(&c6, rand()%72, rand()%72);
        mir.enter(&c7, rand()%72, rand()%72);
        mir.enter(&c8, rand()%72, rand()%72);
        mir.enter(&c9, rand()%72, rand()%72);
        mir.enter(&c10, rand()%72, rand()%72);
        mir.enter(&c11, rand()%72, rand()%72);
        mir.enter(&c12, rand()%72, rand()%72);
        mir.enter(&c13, rand()%72, rand()%72);
        mir.enter(&c14, rand()%72, rand()%72);
        mir.enter(&c15, rand()%72, rand()%72);
        mir.enter(&c16, rand()%72, rand()%72);
        mir.enter(&c17, rand()%72, rand()%72);
        mir.enter(&c18, rand()%72, rand()%72);
        mir.enter(&c19, rand()%72, rand()%72);
        mir.enter(&c20, rand()%72, rand()%72);
        mir.enter(&c21, rand()%72, rand()%72);
        mir.enter(&c22, rand()%72, rand()%72);
        mir.enter(&c23, rand()%72, rand()%72);
        mir.enter(&c24, rand()%72, rand()%72);
        mir.enter(&c25, rand()%72, rand()%72);
        mir.enter(&c26, rand()%72, rand()%72);
        mir.enter(&c27, rand()%72, rand()%72);
        mir.enter(&c28, rand()%72, rand()%72);
        mir.enter(&c29, rand()%72, rand()%72);
        mir.enter(&c30, rand()%72, rand()%72);
        mir.enter(&c31, rand()%72, rand()%72);
        mir.enter(&c32, rand()%72, rand()%72);
        mir.enter(&c33, rand()%72, rand()%72);
        mir.enter(&c34, rand()%72, rand()%72);
        mir.enter(&c35, rand()%72, rand()%72);
        mir.enter(&c36, rand()%72, rand()%72);
        mir.enter(&c37, rand()%72, rand()%72);
        mir.enter(&c38, rand()%72, rand()%72);
        mir.enter(&c39, rand()%72, rand()%72);

        
        mir.conduct(std::cout, 9);
        mir.conduct(std::cout, 991, 100);
        mir.conduct(std::cout, 10000, 1000);

        std::cout << std::endl << std::endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** AT 4 ***" << endl;
        World<8, 8> mir;

        Creature
          h0(food, direction::NORTH),
          h1(food, direction::NORTH),
          h2(food, direction::NORTH),
          h3(food, direction::NORTH),
          h4(food, direction::NORTH),
          h5(food, direction::NORTH),
          f1(food, direction::NORTH),
          f2(food, direction::NORTH),
          f3(food, direction::NORTH),
          f4(food, direction::NORTH),
          f5(food, direction::NORTH),
          f6(food, direction::NORTH),
          f7(food, direction::NORTH);

        mir.enter(&h1, 3, 3);
        mir.enter(&h2, 3, 4);
        mir.enter(&h3, 4, 4);
        mir.enter(&h4, 4, 3);
        mir.enter(&h5, 7, 7);
        mir.enter(&f1, 0, 1);
        mir.enter(&f2, 0, 2);
        mir.enter(&f3, 0, 3);
        mir.enter(&f4, 0, 4);
        mir.enter(&f5, 0, 5);
        mir.enter(&f6, 0, 6);
        mir.enter(&f7, 0, 7);

        mir.conduct(std::cout, 5);
        std::cout << std::endl << std::endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    



    /* END OF MY ACCEPTANCE TESTS */



    return 0;}
