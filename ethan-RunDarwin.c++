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
        
	try {
        cout << "*** Darwin 8x8 Corners ***" << endl;
        /*
        8x8 Darwin
        Hopper, facing west, at (0, 3)
        Hopper, facing east,  at (0, 4)
        Hopper, facing west, at (7, 3)
        Hopper, facing east,  at (7, 4)
        Simulate 5 moves.
        Print every grid.
        */
        Arena a(8, 8);
        
        Species h1('h');
        Species h2('h');
        Species h3('h');
        Species h4('h');

        Creature c3(&h1, west);
        Creature c4(&h2, east);
        Creature c5(&h3, west);
        Creature c6(&h4, east);

        a.insert(0, 3, &c3);
        a.insert(0, 4, &c4);
        a.insert(7, 3, &c5);
        a.insert(7, 4, &c6);

        a.print(0);

        for (int i = 0; i < 5; i++) {
            a.simulate_turns(1);
            a.print(i + 1);
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        
        try {
        cout << "*** Darwin 8x8 Rover Around ***" << endl;
        /*
        8x8 Darwin
        Rover, facing south, at (0, 0)
        Food, facing east,  at (7, 0)
        Food, facing north, at (7, 7)
        Food, facing east,  at (0, 7)
        Simulate 25 moves.
        Print every grid.
        */
        Arena a(8, 8);
        
        Species r('r');
        Species h('f');

        Creature c3(&r, south);
        Creature c4(&h, east);
        Creature c5(&h, north);
        Creature c6(&h, east);

        a.insert(0, 0, &c3);
        a.insert(7, 0, &c4);
        a.insert(7, 7, &c5);
        a.insert(0, 7, &c6);

        a.print(0);

        for (int i = 0; i < 25; i++) {
            a.simulate_turns(1);
            a.print(i + 1);
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

     try {
        cout << "*** Darwin 3x8 Guantlet***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (0, 3)
        Trap, facing east,  at (0, 4)
        Trap, facing north, at (2, 3)
        Trap, facing east,  at (2, 4)
        Hopper, facing east,  at (1, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Arena a(3, 8);
        
        Species t('t');
        Species h('h');

        Creature c1(&t, south);
        Creature c2(&t, east);
        Creature c3(&t, north);
        Creature c4(&t, east);
        Creature c5(&h, east);

        a.insert(0, 3, &c1);
        a.insert(0, 4, &c2);
        a.insert(2, 3, &c3);
        a.insert(2, 4, &c4);
        a.insert(1, 0, &c5);

        a.print(0);

        for (int i = 0; i < 10; i++) {
            a.simulate_turns(1);
            a.print(i + 1);
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


        try {
        cout << "*** Darwin 5x5 Trap!***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (2, 2)
        Hopper, facing south,  at (0, 2)
        Hopper, facing west, at (2, 4)
        Hopper, facing north,  at (4, 2)
        Hopper, facing east,  at (2, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Arena a(5, 5);
        
        Species t('t');
        Species h('h');

        Creature c1(&t, south);
        Creature c2(&h, south);
        Creature c3(&h, west);
        Creature c4(&h, north);
        Creature c5(&h, east);

        a.insert(2, 2, &c1);
        a.insert(0, 2, &c2);
        a.insert(2, 4, &c3);
        a.insert(4, 2, &c4);
        a.insert(2, 0, &c5);

        a.print(0);

        for (int i = 0; i < 10; i++) {
            a.simulate_turns(1);
            a.print(i + 1);
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


        try {
        cout << "*** Darwin 3x3 infect all***" << endl;
        /*
        3x3 Darwin
        Trap, facing south, at (1, 1)
        Food, everywhere else, facing whatever direction
        Simulate 20 moves.
        Print first and last grid.
        */
        Arena a(3, 3);
        
        Species t('t');
        Species f('f');

        Creature c1(&t, south);
        Creature c2(&f, east);
        Creature c3(&f, north);
        Creature c4(&f, east);
        Creature c5(&f, east);
        Creature c6(&f, east);
        Creature c7(&f, north);
        Creature c8(&f, east);
        Creature c9(&f, east);

        a.insert(1, 1, &c1);
        a.insert(0, 0, &c2);
        a.insert(0, 1, &c3);
        a.insert(0, 2, &c4);
        a.insert(1, 0, &c5);
        a.insert(1, 2, &c6);
        a.insert(2, 0, &c7);
        a.insert(2, 1, &c8);
        a.insert(2, 2, &c9);

        a.print(0);

        for (int i = 0; i < 20; i++) {
            a.simulate_turns(1);
            
        }
        a.print(20);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}

