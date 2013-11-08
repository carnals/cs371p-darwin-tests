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
        Environment zoo(8, 8, 5);
        zoo.generate("FOOD", "E", 0, 0);
        zoo.generate("HOPPER", "N", 3, 3);
        zoo.generate("HOPPER", "E", 3, 4);
        zoo.generate("HOPPER", "S", 4, 4);
        zoo.generate("HOPPER", "W", 4, 3);
        zoo.generate("FOOD", "N", 7, 7);
        zoo.run(1);
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
        Environment zoo(7, 9, 5);
        zoo.generate("TRAP", "S", 0, 0);
        zoo.generate("HOPPER", "E", 3, 2);
        zoo.generate("ROVER", "N", 5, 4);
        zoo.generate("TRAP", "W", 6, 8);

        zoo.run(1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hopper Collide 10x4, ensign
    // ------------------

    try {
        cout << "*** Hopper Collide 10x4 ***" << endl;
        srand(0);
            /*        
            10x4 Darwin
            4 Hoppers, facing south in each column of row 0
            4 Hoppers, facing north in each column of row 9
            Simulate 10 moves
            Print every move
            */
            Environment d(10, 4, 10);
            d.generate("HOPPER", "S", 0, 0);
            d.generate("HOPPER", "S", 0, 1);
            d.generate("HOPPER", "S", 0, 2);
            d.generate("HOPPER", "S", 0, 3);
            d.generate("HOPPER", "W", 9, 0);
            d.generate("HOPPER", "W", 9, 1);
            d.generate("HOPPER", "W", 9, 2);
            d.generate("HOPPER", "W", 9, 3);
            d.run(1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Rover Takeover 8x8, ensign
    // ------------------

    // try {
         cout << "*** Rover Takeover 8x8 ***" << endl;
    //     srand(0);
          
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
        
         Environment d(8, 8, 100);
         d.generate("ROVER", "S", 3, 4);
         d.generate("FOOD", "S", 0, 2);
         d.generate("FOOD", "S", 7, 4);
         d.generate("FOOD", "S", 2, 7);
         d.generate("FOOD", "N", 3, 0);
         d.generate("FOOD", "N", 4, 5);
         d.generate("FOOD", "N", 5, 2);
         d.generate("FOOD", "N", 6, 3);
         d.run(10);
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // ----
    // from ethan
    // ----

     try {
        cout << "*** Darwin 3x8 Guantlet***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (0, 3)
        Trap, facing east, at (0, 4)
        Trap, facing north, at (2, 3)
        Trap, facing east, at (2, 4)
        Hopper, facing east, at (1, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Environment a(3, 8, 10);
        
        a.generate("TRAP", "S", 0, 3);
        a.generate("TRAP", "E", 0, 4);
        a.generate("TRAP", "N", 2, 3);
        a.generate("TRAP", "E", 2, 4);
        a.generate("HOPPER", "E", 1, 0);

        a.run(1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// ----------
// darwin 6x6, from ryan76
// ----------

    try {
        cout << "*** Darwin 6x6 ***" << endl;
        srand(0);
        
        /*
        7x9 Darwin
        Trap, facing south, at (0, 0)
        Hopper, facing east, at (3, 2)
        Rover, facing north, at (5, 4)
        Trap, facing west, at (6, 6)
        Simulate 5 moves.
        Print every grid.
        */
        
        Environment x(7, 9, 5);
        x.generate("TRAP", "S", 0, 0);
        x.generate("HOPPER", "E", 3, 2);
        x.generate("ROVER", "N", 5, 4);
        x.generate("TRAP", "W", 6, 6);
        
        x.run(1);
        
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
	Print the first 10 grids (i.e. 0, 1, 2...9).
	Print every 100th grid after that (i.e. 100, 200, 300...1000).
	*/

		Environment zoo(72, 72, 1000);
		for (int i = 0; i < 10; i++) { //ADD 10 FOOD
			int cell = rand() % 5184;
			int x = cell / 72;
			int y = cell % 72;
			int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
				zoo.generate("FOOD", direction, x, y);
	    }
	    else
	    {
				i -= 1;
	    }
	    
	}
	
        for (int i = 0; i < 10; i++) { //ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("HOPPER", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	}
	
	for (int i = 0; i < 10; i++) {//ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("ROVER", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	}
	
	
	for (int i = 0; i < 10; i++) {//ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("TRAP", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	   
        }
         zoo.run(-2);
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
	Print the first 10 grids (i.e. 0, 1, 2...9).
	Print every 100th grid after that (i.e. 100, 200, 300...1000).
	*/
		Environment zoo(72, 72, 1000);
		for (int i = 0; i < 10; i++) { //ADD 10 FOOD
			int cell = rand() % 5184;
			int x = cell / 72;
			int y = cell % 72;
			int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
				zoo.generate("FOOD", direction, x, y);
	    }
	    else
	    {
				i -= 1;
	    }
	    
			}
	
        for (int i = 0; i < 10; i++) { //ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("HOPPER", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	}
	
	for (int i = 0; i < 10; i++) {//ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("ROVER", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	}
	
	
	for (int i = 0; i < 10; i++) {//ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("TRAP", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	   
        }

	for (int i = 0; i < 10; i++) {//ADD 10 ROVERS
            int cell = rand() % 5184;
            int x = cell / 72;
            int y = cell % 72;
            int dir = rand() % 4;
	    string direction = "";
	    if(dir == 0) direction = "W";
	    if(dir == 1) direction = "N";
	    if(dir == 2) direction = "E";
	    if(dir == 3) direction = "S";
	    
	    if(zoo.habitat[x][y].getRace().compare(".") == 0)
	    {
		zoo.generate("BEST", direction, x, y);
	    }
	    else
	    {
		i-=1;
	    }
	   
        }

         zoo.run(-2);
		}
	    catch (const invalid_argument&) {
		assert(false);}
	    catch (const out_of_range&) {
		assert(false);}

	    return 0;}
