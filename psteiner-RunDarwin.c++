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
    Species food('f', string("left\ngo 0"));
     

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopper('h', string("hop\ngo 0"));

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
    Species rover('r', string("if_enemy 9\nif_empty 7\nif_random 5\nleft\ngo 0\nright\ngo 0\nhop\ngo 0\ninfect\ngo 0"));

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
    Species trap('t', string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));

    // ----------
    // darwin 1x10
    // ----------
    try {
        cout << "*** Darwin 1x10 ***" << endl;
        Darwin darwin(1, 10);
        
        for (int i = 0; i < 5; i++) {
            darwin.addCreature(hopper, 0, i*2+1, east);
        }
        
        cout << darwin << endl;
        for (int i = 0; i < 4; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x1
    // ----------
    try {
        cout << "*** Darwin 10x1 ***" << endl;
        Darwin darwin(10, 1);
        
        for (int i = 0; i < 5; i++) {
            darwin.addCreature(hopper, i*2+1, 0, south);
        }
        
        cout << darwin << endl;
        for (int i = 0; i < 4; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------------------------------
    // darwin hop clockwise - direction test
    // ------------------------------------

    try {
        cout << "*** Darwin hop clockwise - direction test ***" << endl;
        Darwin darwin(4, 4);
        darwin.addCreature(hopper, 0, 0, east);
        darwin.addCreature(hopper, 0, 3, south);
        darwin.addCreature(hopper, 3, 3, west);
        darwin.addCreature(hopper, 3, 0, north);

        cout << darwin << endl;
        for (int i = 0; i < 3; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------------------------------
    // darwin trap infect - all directions, all types
    // ------------------------------------
    try {
        cout << "*** Darwin direction infection test all directions, all types ***" << endl;
        Darwin darwin(5, 5);
        darwin.addCreature(food, 0, 2, south);
        darwin.addCreature(trap, 1, 2, north);
        darwin.addCreature(hopper, 2, 0, east);
        darwin.addCreature(trap, 2, 1, west);
        darwin.addCreature(trap, 2, 3, east);
        darwin.addCreature(hopper, 2, 4, west);
        darwin.addCreature(trap, 3, 2, south);
        darwin.addCreature(rover, 4, 2, south);

        cout << darwin << endl;
        darwin.takeTurn();
        cout << darwin << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // Test the rover's random motion
    try {
        cout << "*** Darwin 6x6 rover motion sanity ***" << endl;
        Darwin darwin(6, 6);
        darwin.addCreature(rover, 3, 3, west);
        cout << darwin << endl;
        for (int i = 0; i < 10; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }
        darwin.takeTurn(15);
        cout << darwin << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

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
        Darwin darwin(8, 8);
        darwin.addCreature(food, 0, 0, east);
        darwin.addCreature(hopper, 3, 3, north);
        darwin.addCreature(hopper, 3, 4, east);
        darwin.addCreature(hopper, 4, 4, south);
        darwin.addCreature(hopper, 4, 3, west);
        darwin.addCreature(food, 7, 7, north);

        cout << darwin << endl;
        for (int i = 0; i < 5; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
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
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin darwin(7, 9);
        darwin.addCreature(trap, 0, 0, south);
        darwin.addCreature(hopper, 3, 2, east);
        darwin.addCreature(rover, 5, 4, north);
        darwin.addCreature(trap, 6, 8, west);

        cout << darwin << endl;
        for (int i = 0; i < 5; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 5x5 infect trap full 360 rotation ***" << endl;
        Darwin darwin(5, 5);
        darwin.addCreature(trap, 0, 0, south);
        darwin.addCreature(trap, 0, 2, west);
        darwin.addCreature(trap, 0, 4, south);
        darwin.addCreature(hopper, 4, 2, north);
        darwin.addCreature(hopper, 4, 0, north);
        darwin.addCreature(hopper, 4, 4, north);
        
        std::cout << darwin;
        for (int i=0; i < 6; i++) {
            darwin.takeTurn();
            std::cout << darwin << endl;
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // Test random placement of creatures
    try {
        cout << "*** Darwin 10x10 random placement ***" << endl;
        Darwin darwin(10, 10);
        
        darwin.addCreature(trap);
        cout << darwin << endl;

        darwin.addCreature(food);
        cout << darwin << endl;

        darwin.addCreature(trap);
        cout << darwin << endl;

        darwin.addCreature(food);
        cout << darwin << endl;

        darwin.addCreature(trap);
        cout << darwin << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // Test failure of random placement
    try {
        cout << "*** Darwin 4x2 random overlap - should cause exception***" << endl;
        Darwin darwin(4, 2);
        darwin.addCreature(trap);
        cout << darwin << endl;

        darwin.addCreature(food);
        cout << darwin << endl;

        darwin.addCreature(hopper);
        assert(false);
        cout << darwin << endl;

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(true);}

   // Trap infection
    try {
        cout << "*** Darwin 10x10 trap infection ***" << endl;
        Darwin darwin(10, 10);
        
        for (int i=0; i < 9; i++){
            for (int j =0; j < 10; j++){
                darwin.addCreature(hopper,i,j,south);
            }
        }

        for (int j =0; j < 10; j++){
            darwin.addCreature(trap, 9, j, north /* directionMap[j % sizeof(Direction)]*/);
        }

        cout << darwin << endl;
        for (int j =0; j < 25; j++){
            darwin.takeTurn();
            cout << darwin << endl;
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // Trap infection
    try {
        cout << "*** Darwin 100x100 trap infection 2***" << endl;
        Darwin darwin(100, 100);
        
        for (int i=0; i < 99; i++){
            for (int j =0; j < 100; j++){
                darwin.addCreature(hopper,i,j,directionMap[j % sizeof(Direction)]);
            }
        }

        for (int j =0; j < 100; j++){
            darwin.addCreature(trap, 99, j, directionMap[j % sizeof(Direction)]);
        }

        cout << darwin << endl;
        darwin.takeTurn();
        cout << darwin << endl;

        darwin.takeTurn(49);
        cout << darwin << endl;

        darwin.takeTurn(53);
        cout << darwin << endl;
        
        darwin.takeTurn();
        cout << darwin << endl;

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
        Darwin darwin(72, 72);

        int i = 0;
        for (i = 0; i < 10; i++) {
            darwin.addCreature(food);
        }
        for (i = 0; i < 10; i++) {
            darwin.addCreature(hopper);
        }
        for (i = 0; i < 10; i++) {
            darwin.addCreature(rover);
        }
        for (i = 0; i < 10; i++) {
            darwin.addCreature(trap);
        }

        cout << darwin << endl;
        for (i = 0; i < 9; i++) {
            darwin.takeTurn();
            cout << darwin << endl;
        }

        darwin.takeTurn(91);
        cout << darwin << endl;
        for (i = 0; i < 9; i++) {
            darwin.takeTurn(100);
            cout << darwin << endl;
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
        // cout << "*** Darwin 72x72 with Best ***" << endl;
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
        
        // Darwin darwin(72, 72);
        // //Species best('b', string(""));
        // int i = 0;
        // for (i = 0; i < 10; i++) {
        //     darwin.addCreature(food);
        // }
        // for (i = 0; i < 10; i++) {
        //     darwin.addCreature(hopper);
        // }
        // for (i = 0; i < 10; i++) {
        //     darwin.addCreature(rover);
        // }
        // for (i = 0; i < 10; i++) {
        //     darwin.addCreature(trap);
        // }
        /*
        for (i = 0; i < 10; i++) {
            darwin.addCreature(best);
        }
        */
        // cout << darwin << endl;
        // for (i = 0; i < 9; i++) {
        //     darwin.takeTurn();
        //     cout << darwin << endl;
        // }

        // darwin.takeTurn(91);
        // cout << darwin << endl;
        // for (i = 0; i < 9; i++) {
        //     darwin.takeTurn(100);
        //     cout << darwin << endl;
        // }
 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
