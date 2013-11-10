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
#include "Darwin.h"  //for creatures n stuff

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
        int a[] = {Food, east, 0, 0,
      	  Hopper, north, 3, 3,
      	  Hopper, east, 3, 4,
	  Hopper, south, 4, 4,
      	  Hopper, west, 4, 3,
      	  Food, north, 7, 7};

	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);
	
	b->printGrid();	
        for(int i = 0; i < 5; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
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

	int a[] = {Trap, south, 0, 0,
        Hopper, east, 3, 2,
        Rover, north, 5, 4,
        Trap, west, 6, 8};
	
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(7, 9, v);
        b->printGrid();
        for(int i = 0; i < 5; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
	
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
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
	int x =0;
	int a[] = {Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));

	board *b = new board(72, 72, v);
        b->printGrid();

        for(int i = 0; i < 10; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
	for(int j = 10; j < 1000; j++)
	{
		b->nextTurn();
		if(j%100 == 99)
			b->printGrid();
	}
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
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);

	int x = 0;
	int a[] = {Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Food, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Hopper, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Rover, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Trap, (rand() % 4), (x=(rand() % 5184))/72, x%72,

        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
        Best, (rand() % 4), (x=(rand() % 5184))/72, x%72,
};


  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));

        board *b = new board(72, 72, v);
        b->printGrid();

        for(int i = 0; i < 10; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
	for(int j = 10; j < 1000; j++)
	{
		b->nextTurn();
		if(j%100 == 99)
			b->printGrid();
	}
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


	cout << "starting acceptance tests" << endl;


    try {
        cout << "*** Darwin 72x72 Acceptance test ***" << endl;
        srand(0);
	int x =0;
	int a[] = {
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72,
	rand()%5, (rand() % 4), (x=(rand() % 5184))/72, x%72};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));

	board *b = new board(72, 72, v);
        b->printGrid();

        for(int i = 0; i < 10; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
	for(int j = 10; j < 1000; j++)
	{
		b->nextTurn();
		if(j%100 == 99)
			b->printGrid();
	}
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature, specified by a call to rand % 5.
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }

    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 100x100 Acceptance Test***" << endl;
        srand(0);
	int x =0;
	int a[] = {
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100,
	rand()%5, (rand() % 4), (x=(rand() % 10000))/100, x%100};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	board *b = new board(100, 100, v);
        b->printGrid();

        for(int i = 0; i < 10; i++)
	{
		b->nextTurn();
		b->printGrid();
	}
	for(int j = 10; j < 1000; j++)
	{
		b->nextTurn();
		if(j%100 == 99)
			b->printGrid();
	}
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 10000 (100x100), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature, specified by a call to rand % 5.
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }

    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

try {
        cout << "*** Darwin 1x30 Big Trap ***" << endl;
        srand(0);
        int a[] = {Rover,east,0,0,
        	   Hopper,west,0,29};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1,30, v);


        for (int i = 0; i < 20; ++i)
        {

            b->printGrid();
            b->nextTurn();
        }
        b->printGrid();

        /*
        in a darwin world of 1 by 30
        create a rover at the left side
        and a hopper on the right most side facing each other
        simulate 20 moves
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

try {
        cout << "*** Darwin 4x10 without Best ***" << endl;
        srand(0);
	int a[] = {
        Trap,east,0,0,
        Trap,east,1,0,
        Trap,east,2,0,
        Trap,east,3,0,
        Trap,east,0,1,
        Trap,east,1,1,
        Trap,east,2,1,
        Trap,east,3,1,

        Rover,east,0,9,
        Rover,east,1,9,
        Rover,east,2,9,
        Rover,east,3,9
};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(4,10, v);
        for (int i = 0; i < 20; ++i)
        {

            b->printGrid();
            b->nextTurn();
        }
	b->printGrid();

        /*
        in a darwin world of 4 by 10
        8 traps all on the left hand side as much as possible all facing east
        create 4 rovers all on the right side all facing east
        simulate 20 moves
        */
        }


    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


/*1x1 world
1 food at 0,0 facing west
4 moves
print every
watch food look for friends
so cry:'(
*/
    try{
        cout << "*** Darwin 1x1 Lonely ***" << endl;
        srand(0);
        int a[] = {Food,west,0,0};

  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1,1, v);
        int i;
        b->printGrid();

        for(i = 1; i <= 4; ++i)
        {

          b->nextTurn();
          b->printGrid();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    try {
        cout << "*** BChean's 4x12 (#5) ***" << endl;
        	int a[] = {
                Food, south,4, 0,
                Food, south,5, 0, 
                Food, south,6, 0, 
                Food, south, 7, 0, 

                Rover, west,0, 0,
                Rover, west,0, 1, 
                Rover, west,11, 0,
                Rover, west,  11, 1, 
                
                Trap, north, 4, 2,
                Trap, north, 5, 2,
                Trap, north, 6, 2,
                Trap, north, 7, 2,
                Trap, north, 4, 3, 
                Trap,  north,5, 3,
                Trap, north, 6, 3, 
                Trap, north,7, 3
		};
  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
                board *b = new board(12, 4, v);


                b->printGrid();
                
                for (int i = 0; i < 28; ++i)
                {
                        b->nextTurn();
                        b->printGrid();
                }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // rover_skinny_board 8x1
    // ------------
    try {
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        srand(0);

        int a[] = {Rover, east, 3, 0};
        const int NUM_MOVES = 100;
  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 1, v);

        b->printGrid();
        for (int i = 1; i <= NUM_MOVES; ++i) {
            b->nextTurn();
            if (i % 10 == 0) {
                b->printGrid();
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 


    //START MY TESTS 
    try{
        cout << "*** Darwin 10X10 Test I ***" << endl;
        srand(0);
	int a[] = {
        Food, south, 5, 5,
        Hopper, north, 3, 5,
        Hopper, south, 2, 6,
        Hopper, east, 1, 9,
        Hopper, east, 8, 1,
        Rover,  south, 2, 5
};


  	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);
        b->printGrid();
        for(int i = 1; i < 6; i++){
            b->nextTurn();
            b->printGrid();

        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
