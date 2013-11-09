// ------------------------------------
// Name: Austin deBruyn
// cs user id: austind
// ------------------------------------

// ------------------------------------
// Name: Steven Wilken
// cs user id: swilken 
// ------------------------------------

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

#include "Darwin.h"
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

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

    species food('f');
    int prog1[] = { LEFT, GO, 0 };
    food.setProgram(prog1, sizeof(prog1)/sizeof(int));

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    species hopper('h');
    int prog2[] = { HOP, GO, 0 };
    hopper.setProgram(prog2, sizeof(prog2)/sizeof(int));

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

    species rover('r');
    int prog3[] = { IFENEMY, 9, IFEMPTY, 7, IFRANDOM, 5, LEFT, GO, 0, RIGHT, GO, 0, HOP, GO, 0, INFECT, GO, 0 };
    rover.setProgram(prog3, sizeof(prog3)/sizeof(int));

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

    species trap('t');
    int prog4[] = { IFEMPTY, 3, LEFT, GO, 0, INFECT, GO, 0 };
    trap.setProgram(prog4, sizeof(prog4)/sizeof(int));

    // ----
    // best
    // ----

    /*
     0: ??? 
    */

	//TODO: LOAD YOUR 'BEST' PROGRAM HERE
	// (don't use ours)
	assert(false);
    



	//The tests
    {
        cout << "*** 1x1 Test for Overlapping ***" << endl;
        /* 1x1 grid
            Place a hopper on top of another hopper
        */
        grid<1, 1> g;
        g.place(0, 0, &hopper);
        g.takeTurn(10);
    }

    {
        cout << "*** 4x4 Test for Jamming ***" << endl;
        /* 4x4 grid
            Fill the grid with things
        */
        grid<4, 4> g;

        for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            g.place(i, j, &hopper);
        g.takeTurn(1);
    }

    {
        cout << "*** 10x10 Test for Survival ***" << endl;
        /*
        10x10 Darwin
        10 Trap,   facing south, at (0, 1 ... 10)
        10 Rover,   facing north, at (9, 1 ... 10)
        Simulate 10 moves.
        Print the final grid.
        */
        srand(0);
        grid<10, 10> g;

        for (int j=0; j<10; j++)
            g.place(0, j, &trap, SOUTH);
        for (int j=0; j<10; j++)
            g.place(9, j, &rover);
        g.takeTurn(10);
        g.printGrid(10);
    }

    {
        cout << "*** 10x10 Test for Survival ***" << endl;
        /*
        10x10 Darwin
        10 Rover,   facing randomly, at (a, a) from top to bottom
        10 Best,   facing randomly, at (b, 9-b) from top to bottom
        Simulate 40 moves.
        Print the final grid.
        */
        srand(0);
        grid<10, 10> g;

        for (int j=0; j<10; j++)
            g.place(j, j, &rover, rand()%4);
        for (int j=0; j<10; j++)
            g.place(j, 9-j, &best, rand()%4);

        g.takeTurn(40);
        g.printGrid(40);
    }

    {
        cout << "*** 10x10 Test for Survival 2 ***" << endl;
        /*
        10x10 Darwin
        10 Rover,   facing randomly, placed along the diagonal (a, a)
        Fill the rest of the grid with traps, facing randomly
        Simulate 30 moves.
        Print the starting, 11th, and 12th grid.
        It should take that long for rovers to take over the whole area
        // Delete this test if your API doesn't allow it. With #define private public,
        // it should.
        */
        srand(0);
        grid<10, 10> g;

        for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (i == j)
                g.place( i, j, &rover, rand()%4);
            else
                g.place( i, j, &trap, rand()%4);
               
        }

        g.printGrid(0);
        g.takeTurn(11);
        g.printGrid(11);
        g.takeTurn(1);
        g.printGrid(12);
    }

    {
        cout << "*** 1x60 Test for Meeting a Friend ***" << endl;
        /*
        1x60 Darwin
        1 Hopper,   facing east,    at (0, 0)
        1 Hopper,   facing west,    at (0, 59)
        Simulate 29 moves
        Print the first and last grid.
        */
        srand(0);
        grid<1, 60> g;

        g.place(0, 0, &hopper, EAST);
        g.place(0, 59, &hopper, WEST);

        g.printGrid(0);
        g.takeTurn(29);
        g.printGrid(29);
    }

    {
        cout << "*** 1x60 Test for Meeting a Friend ***" << endl;
        /*
        1x60 Darwin
        1 Hopper,   facing east,    at (0, 0)
        1 Hopper,   facing west,    at (0, 59)
        1 Rover,   facing north,    at (0, 29)
        1 Rover,   facing south,    at (0, 30)
        Simulate 29 moves
        Print the first and last grid.
        */
        srand(0);
        grid<1, 60> g;

        g.place(0, 0, &hopper, EAST);
        g.place(0, 59, &hopper, WEST);
        g.place(0, 29, &rover, NORTH);
        g.place(0, 30, &rover, SOUTH);

        g.printGrid(0);
        g.takeTurn(29);
        g.printGrid(29);
    }

    {
        cout << "*** 1x60 Test for Bottlenecking ***" << endl;
        /*
        1x60 Darwin
        1 Rover,    facing east,    at (0, 0)
        Food filling the rest of the grid, facing EAST
        Simulate 1 move
        Print the grid.
        The whole grid should be rovers.
        */
        srand(0);
        grid<1, 60> g;

        g.place(0, 0, &rover, EAST);

        for (int i=1; i<60; i++)
        g.place(0, i, &food, EAST);

        g.takeTurn(1);
        g.printGrid(1);
    }

    {
        cout << "*** 1x60 Test for Reverse Bottlenecking ***" << endl;
        /*
        1x60 Darwin
        1 Rover,    facing west,    at (0, 59)
        Food filling the rest of the grid, facing WEST
        Simulate 271 moves
        Print the 270th and 271st grid. That's how long it should take
        for rovers to completely take over.
        */
        srand(0);
        grid<1, 60> g;

        g.place(0, 59, &rover, WEST);

        for (int i=0; i<59; i++)
        g.place(0, i, &food, WEST);

        g.takeTurn(270);
        g.printGrid(270);
        g.takeTurn(1);
        g.printGrid(271);
    }

    {
        cout << "*** 20x20 Test for Having Fun ***" << endl;
        /*
        20x20 Darwin
        1 Rover,    facing randomly, at 19, 19
        1 Rover,    facing randomly, at 18, 19
        1 Rover,    facing randomly, at 19, 18
        1 Rover,    facing randomly, at 18, 18
        1 Hopper,   facing randomly, at 0, 0
        1 Hopper,   facing randomly, at 0, 1
        1 Hopper,   facing randomly, at 1, 0
        1 Hopper,   facing randomly, at 1, 1
        Simulate 50 moves
        Print the starting and every 10 grids
        */
        srand(0);
        grid<20, 20> g;

        g.place(19, 19, &rover, rand()%4);
        g.place(18, 19, &rover, rand()%4);
        g.place(19, 18, &rover, rand()%4);
        g.place(18, 18, &rover, rand()%4);

        g.place(0, 0, &hopper, rand()%4);
        g.place(0, 1, &hopper, rand()%4);
        g.place(1, 0, &hopper, rand()%4);
        g.place(1, 1, &hopper, rand()%4);

        for (int i=0; i<5; i++) {
            g.printGrid(i*10);
            g.takeTurn(10);
        }
        
        g.printGrid(50);
    }
    
    return 0;}
