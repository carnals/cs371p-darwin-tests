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
#include <string>
// ----
// main
// ----

int main () {
    using namespace std;
	Species food = Species("food");
	food.addInstruction("left");
	food.addInstruction("go 0");
	
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
	
	Species hopper = Species("hopper");
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

    Species rover = Species("rover");
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

	Species trap = Species("trap");
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------
	cout << "-1\n";
    try {
        cout << "*** Darwin 8x8 ***" << endl;
        
        /*8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
		/*Grid world = Grid(8,8);
		world.addCreature(food,0,0,EAST);	
		world.addCreature(hopper,3,3,NORTH);
		world.addCreature(hopper,3,4,EAST);
		world.addCreature(hopper,4,4,SOUTH);
		world.addCreature(hopper,4,3,WEST);
		world.addCreature(food,7,7,NORTH);
		world.print();
		for(int a = 0; a<5; a++) {
			world.takeTurn();
			world.print();
		}*/
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
t
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
		Grid world = Grid(7,9);
        world.addCreature(trap,0,0,SOUTH);
        world.addCreature(hopper,3,2,EAST);
        world.addCreature(rover,5,4,NORTH);
        world.addCreature(trap,6,8,WEST);
        
        world.print();
		for(int q = 0; q<5; q++) {
			world.takeTurn();
			world.print();
		}
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x10
    // ----------

    try {
        cout << "*** Darwin 3x10 ***" << endl;
        srand(0);
        /*
        3x10 Darwin
        Trap,   facing south, at (2, 6)
t
        Hopper, facing north,  at (2, 7)
        Rover,  facing west, at (0, 0)
        Trap,   facing north,  at (9, 9)
        Simulate 10 moves.
        Print every grid.
        */
        Grid world = Grid(3,10);
        world.addCreature(trap,2,6,SOUTH);
        world.addCreature(hopper,2,7,NORTH);
        world.addCreature(rover,0,0,WEST);
        world.addCreature(trap,2,9,NORTH);
        
        world.print();
        for(int q = 0; q<10; q++) {
            world.takeTurn();
            world.print();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 1x10
    // ----------

    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        /*
        1x10 Darwin
        Hopper,   facing east, at (0, 0)
        Rover,    facing east, at (0, 1)
        Hopper,   facing east, at (0, 2)
        Rover,    facing east, at (0, 3)
        Hopper,   facing east, at (0, 4)
        Rover,    facing east, at (0, 5)
        Hopper,   facing east, at (0, 6)
        Rover,    facing east, at (0, 7)
        Hopper,   facing east, at (0, 8)
        Simulate 10 moves.
        Print every grid.
        */
        Grid world = Grid(1,10);
        world.addCreature(hopper,0,0,EAST);
        world.addCreature(rover,0,1,EAST);
        world.addCreature(hopper,0,2,EAST);
        world.addCreature(rover,0,3,EAST);
        world.addCreature(hopper,0,4,EAST);
        world.addCreature(rover,0,5,EAST);
        world.addCreature(hopper,0,6,EAST);
        world.addCreature(rover,0,7,EAST);
        world.addCreature(hopper,0,8,EAST);

        
        world.print();
        for(int q = 0; q<10; q++) {
            world.takeTurn();
            world.print();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 1x10 (corner case - creatures out of bounds)
    // ----------

    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        /*
        1x10 Darwin
        Hopper,   facing north, at (0, 0)
        Rover,    facing north, at (0, 1)
        Hopper,   facing north, at (0, 2)
        Rover,    facing north, at (0, 3)
        Hopper,   facing north, at (0, 4)
        Rover,    facing north, at (0, 5)
        Hopper,   facing north, at (0, 6)
        Rover,    facing north, at (0, 7)
        Hopper,   facing north, at (0, 8)
        Simulate 10 moves.
        Print every grid.
        */
        Grid world = Grid(1,10);
        world.addCreature(hopper,0,0,NORTH);
        world.addCreature(rover,0,1,NORTH);
        world.addCreature(hopper,0,2,NORTH);
        world.addCreature(rover,0,3,NORTH);
        world.addCreature(hopper,0,4,NORTH);
        world.addCreature(rover,0,5,NORTH);
        world.addCreature(hopper,0,6,NORTH);
        world.addCreature(rover,0,7,NORTH);
        world.addCreature(hopper,0,8,NORTH);

        
        world.print();
        for(int q = 0; q<10; q++) {
            world.takeTurn();
            world.print();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 5x5
    // ----------
    cout << "-1\n";
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        
        /*5x5 Darwin
        Rover,  facing east,  at (0, 0)
        Food,   facing east,  at (1, 0)
        Food,   facing east,  at (2, 0)
        Food,   facing east,  at (3, 0)
        Food,   facing east,  at (4, 0)
        
        Food,   facing east,  at (0, 1)
        Food,   facing east,  at (1, 1)
        Food,   facing east,  at (2, 1)
        Food,   facing east,  at (3, 1)
        Food,   facing east,  at (4, 1)

        Food,   facing east,  at (0, 2)
        Food,   facing east,  at (1, 2)
        Food,   facing east,  at (2, 2)
        Food,   facing east,  at (3, 2)
        Food,   facing east,  at (4, 2)

        Food,   facing east,  at (0, 3)
        Food,   facing east,  at (1, 3)
        Food,   facing east,  at (2, 3)
        Food,   facing east,  at (3, 3)
        Food,   facing east,  at (4, 3)

        Food,   facing east,  at (0, 5)
        Food,   facing east,  at (1, 5)
        Food,   facing east,  at (2, 5)
        Food,   facing east,  at (3, 5)
        Food,   facing east,  at (4, 5)
        
        Simulate 50 moves.
        Print every 5 grid.
        */
        Grid world = Grid(5,5);
        world.addCreature(rover,0,0,EAST);
        world.addCreature(food,1,0,EAST);
        world.addCreature(food,2,0,EAST);
        world.addCreature(food,3,0,EAST);
        world.addCreature(food,4,0,EAST);

        world.addCreature(food,0,1,EAST);
        world.addCreature(food,1,1,EAST);
        world.addCreature(food,2,1,EAST);
        world.addCreature(food,3,1,EAST);
        world.addCreature(food,4,1,EAST);

        world.addCreature(food,0,2,EAST);
        world.addCreature(food,1,2,EAST);
        world.addCreature(food,2,2,EAST);
        world.addCreature(food,3,2,EAST);
        world.addCreature(food,4,2,EAST);

        world.addCreature(food,0,3,EAST);
        world.addCreature(food,1,3,EAST);
        world.addCreature(food,2,3,EAST);
        world.addCreature(food,3,3,EAST);
        world.addCreature(food,4,3,EAST);

        world.addCreature(food,0,4,EAST);
        world.addCreature(food,1,4,EAST);
        world.addCreature(food,2,4,EAST);
        world.addCreature(food,3,4,EAST);
        world.addCreature(food,4,4,EAST);
        
        world.print();
        for(int a = 0; a<50; a++) {
            world.takeTurn();
            if((a+1) % 5 == 0) {
                world.print();}
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // darwin 10x10
    // ----------

    /* rover should change from cw to ccw, vice versa */
    cout << "-1\n";
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        
        /*10x10 Darwin
        Rover,  facing east,  at (0, 0)
        
        Simulate 50 moves.
        Print every grid.
        */
        Grid world = Grid(10,10);
        world.addCreature(rover,0,0,EAST);
        
        world.print();
        for(int a = 0; a<50; a++) {
            world.takeTurn();
            world.print();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 5x5
    // ----------
    cout << "-1\n";
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        
        /*5x5 Darwin
        Rover,  facing east,  at (0, 0)
        Hopper,   facing east,  at (1, 0)
        Hopper,   facing east,  at (2, 0)
        Hopper,   facing east,  at (3, 0)
        Hopper,   facing east,  at (4, 0)
        
        Hopper,   facing east,  at (0, 1)
        Hopper,   facing east,  at (1, 1)
        Hopper,   facing east,  at (2, 1)
        Hopper,   facing east,  at (3, 1)
        Hopper,   facing east,  at (4, 1)

        Hopper,   facing east,  at (0, 2)
        Hopper,   facing east,  at (1, 2)
        Hopper,   facing east,  at (2, 2)
        Hopper,   facing east,  at (3, 2)
        Hopper,   facing east,  at (4, 2)

        Hopper,   facing east,  at (0, 3)
        Hopper,   facing east,  at (1, 3)
        Hopper,   facing east,  at (2, 3)
        Hopper,   facing east,  at (3, 3)
        Hopper,   facing east,  at (4, 3)

        Hopper,   facing east,  at (0, 5)
        Hopper,   facing east,  at (1, 5)
        Hopper,   facing east,  at (2, 5)
        Hopper,   facing east,  at (3, 5)
        Hopper,   facing east,  at (4, 5)
        
        Simulate 50 moves.
        Print every 5 grid.
        */
        
        Grid world = Grid(5,5);
        world.addCreature(rover,0,0,EAST);
        world.addCreature(hopper,1,0,EAST);
        world.addCreature(hopper,2,0,EAST);
        world.addCreature(hopper,3,0,EAST);
        world.addCreature(hopper,4,0,EAST);

        world.addCreature(hopper,0,1,EAST);
        world.addCreature(hopper,1,1,EAST);
        world.addCreature(hopper,2,1,EAST);
        world.addCreature(hopper,3,1,EAST);
        world.addCreature(hopper,4,1,EAST);

        world.addCreature(hopper,0,2,EAST);
        world.addCreature(hopper,1,2,EAST);
        world.addCreature(hopper,2,2,EAST);
        world.addCreature(hopper,3,2,EAST);
        world.addCreature(hopper,4,2,EAST);

        world.addCreature(hopper,0,3,EAST);
        world.addCreature(hopper,1,3,EAST);
        world.addCreature(hopper,2,3,EAST);
        world.addCreature(hopper,3,3,EAST);
        world.addCreature(hopper,4,3,EAST);

        world.addCreature(hopper,0,4,EAST);
        world.addCreature(hopper,1,4,EAST);
        world.addCreature(hopper,2,4,EAST);
        world.addCreature(hopper,3,4,EAST);
        world.addCreature(hopper,4,4,EAST);
        
        world.print();
        for(int a = 0; a<50; a++) {
            world.takeTurn();
            if((a+1) % 5 == 0) {
                world.print();}
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 5x5
    // ----------
    cout << "-1\n";
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        
        /*5x5 Darwin
        Trap,     facing east,  at (0, 0)
        Hopper,   facing east,  at (1, 0)
        Hopper,   facing east,  at (2, 0)
        Hopper,   facing east,  at (3, 0)
        Hopper,   facing east,  at (4, 0)
        
        Hopper,   facing east,  at (0, 1)
        Hopper,   facing east,  at (1, 1)
        Hopper,   facing east,  at (2, 1)
        Hopper,   facing east,  at (3, 1)
        Hopper,   facing east,  at (4, 1)

        Hopper,   facing east,  at (0, 2)
        Hopper,   facing east,  at (1, 2)
        Hopper,   facing east,  at (2, 2)
        Hopper,   facing east,  at (3, 2)
        Hopper,   facing east,  at (4, 2)

        Hopper,   facing east,  at (0, 3)
        Hopper,   facing east,  at (1, 3)
        Hopper,   facing east,  at (2, 3)
        Hopper,   facing east,  at (3, 3)
        Hopper,   facing east,  at (4, 3)

        Hopper,   facing east,  at (0, 5)
        Hopper,   facing east,  at (1, 5)
        Hopper,   facing east,  at (2, 5)
        Hopper,   facing east,  at (3, 5)
        Hopper,   facing east,  at (4, 5)
        
        Simulate 50 moves.
        Print every 5 grid.
        */
        Grid world = Grid(5,5);
        world.addCreature(trap,0,0,EAST);
        world.addCreature(hopper,1,0,EAST);
        world.addCreature(hopper,2,0,EAST);
        world.addCreature(hopper,3,0,EAST);
        world.addCreature(hopper,4,0,EAST);

        world.addCreature(hopper,0,1,EAST);
        world.addCreature(hopper,1,1,EAST);
        world.addCreature(hopper,2,1,EAST);
        world.addCreature(hopper,3,1,EAST);
        world.addCreature(hopper,4,1,EAST);

        world.addCreature(hopper,0,2,EAST);
        world.addCreature(hopper,1,2,EAST);
        world.addCreature(hopper,2,2,EAST);
        world.addCreature(hopper,3,2,EAST);
        world.addCreature(hopper,4,2,EAST);

        world.addCreature(hopper,0,3,EAST);
        world.addCreature(hopper,1,3,EAST);
        world.addCreature(hopper,2,3,EAST);
        world.addCreature(hopper,3,3,EAST);
        world.addCreature(hopper,4,3,EAST);

        world.addCreature(hopper,0,4,EAST);
        world.addCreature(hopper,1,4,EAST);
        world.addCreature(hopper,2,4,EAST);
        world.addCreature(hopper,3,4,EAST);
        world.addCreature(hopper,4,4,EAST);
        
        world.print();
        for(int a = 0; a<50; a++) {
            world.takeTurn();
            if((a+1) % 5 == 0) {
                world.print();}
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}









    // ----------
    // darwin 100x100
    // ----------
    cout << "-1\n";
    try {
        cout << "*** Darwin 100x100 ***" << endl;
        
        /*100x100 Darwin
        Rover,     facing north,  at (0, 0)
        Hopper,   facing east,  at (1, 0)
        Hopper,   facing east,  at (2, 0)
        Hopper,   facing east,  at (3, 0)
        Hopper,   facing east,  at (4, 0)
        
        Hopper,   facing east,  at (0, 1)
        Hopper,   facing east,  at (1, 1)
        Hopper,   facing east,  at (2, 1)
        Hopper,   facing east,  at (3, 1)
        Hopper,   facing east,  at (4, 1)

        Hopper,   facing east,  at (0, 2)
        Hopper,   facing east,  at (1, 2)
        Hopper,   facing east,  at (2, 2)
        Hopper,   facing east,  at (3, 2)
        Hopper,   facing east,  at (4, 2)

        Hopper,   facing east,  at (0, 3)
        Hopper,   facing east,  at (1, 3)
        Hopper,   facing east,  at (2, 3)
        Hopper,   facing east,  at (3, 3)
        Hopper,   facing east,  at (4, 3)

        Hopper,   facing east,  at (0, 5)
        Hopper,   facing east,  at (1, 5)
        Hopper,   facing east,  at (2, 5)
        Hopper,   facing east,  at (3, 5)
        Hopper,   facing east,  at (4, 5)
        
        Simulate 150 moves.
        Print every 5 grid.
        */
        Grid world = Grid(100,100);
        world.addCreature(rover,99,99,NORTH);
        world.addCreature(hopper,1,0,EAST);
        world.addCreature(hopper,2,0,EAST);
        world.addCreature(hopper,3,0,EAST);
        world.addCreature(hopper,4,0,EAST);

        world.addCreature(hopper,0,1,EAST);
        world.addCreature(hopper,1,1,EAST);
        world.addCreature(hopper,2,1,EAST);
        world.addCreature(hopper,3,1,EAST);
        world.addCreature(hopper,4,1,EAST);

        world.addCreature(hopper,0,2,EAST);
        world.addCreature(hopper,1,2,EAST);
        world.addCreature(hopper,2,2,EAST);
        world.addCreature(hopper,3,2,EAST);
        world.addCreature(hopper,4,2,EAST);

        world.addCreature(hopper,0,3,EAST);
        world.addCreature(hopper,1,3,EAST);
        world.addCreature(hopper,2,3,EAST);
        world.addCreature(hopper,3,3,EAST);
        world.addCreature(hopper,4,3,EAST);

        world.addCreature(hopper,0,4,EAST);
        world.addCreature(hopper,1,4,EAST);
        world.addCreature(hopper,2,4,EAST);
        world.addCreature(hopper,3,4,EAST);
        world.addCreature(hopper,4,4,EAST);
        
        world.print();
        for(int a = 0; a<150; a++) {
            world.takeTurn();
            if((a+1) % 5 == 0) {
                world.print();}
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
        // cout << "*** Darwin 72x72 without Best ***" << endl;
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



    

    return 0;}
