// -----------------------------
// RunDarwin.c++
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

// my includes
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

	 Darwin myGame(8, 8);
         Creature f1('F',EAST);
         myGame.addCreature(f1,0,0);
         Creature h1('H',NORTH);
         myGame.addCreature(h1,3,3);
         Creature h2('H',EAST);
         myGame.addCreature(h2, 3, 4);
         Creature h3('H',SOUTH);
         myGame.addCreature(h3, 4, 4);
         Creature h4('H',WEST);
         myGame.addCreature(h4, 4, 3);
         Creature f2('F',NORTH);
         myGame.addCreature(f2,7 , 7);

	 myGame.printBoard(); 
         myGame.giveEveryoneOneTurn();
         myGame.printBoard(); 
         myGame.giveEveryoneOneTurn();
         myGame.printBoard(); 
         myGame.giveEveryoneOneTurn();
         myGame.printBoard(); 
         myGame.giveEveryoneOneTurn();
         myGame.printBoard(); 
         myGame.giveEveryoneOneTurn();
         myGame.printBoard();

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

	Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

        myGame.printBoard();
        myGame.giveEveryoneOneTurn();
        myGame.printBoard(); 
        myGame.giveEveryoneOneTurn();
        myGame.printBoard(); 
        myGame.giveEveryoneOneTurn();
        myGame.printBoard(); 
        myGame.giveEveryoneOneTurn();
        myGame.printBoard(); 
        myGame.giveEveryoneOneTurn();
        myGame.printBoard();

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

	    Darwin myGame(72, 72);
	    int rand_pos = rand() % 5184;
	    cout << "random position = " << rand_pos << endl;
	    vector<Creature*> c;	   
/* 
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature f('F', rand_dir);
		//c.push_back(f);
		myGame.addCreature(f, rx, ry);
	    }
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature h('H', rand_dir);
		myGame.addCreature(h, rx, ry);
	    }
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature r('R', rand_dir);
		myGame.addCreature(r, rx, ry);
	    }   
 	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		//Creature t('T', rand_dir);
		//myGame.addCreature(t, rx, ry);
	    }
*/

	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature f1('F', rand_dir);
		myGame.addCreature(f1, rx, ry);
		rand_pos = rand() % 5184;
		rx = rand_pos / 72;
		ry = rand_pos % 72;
		rand_dir = rand() % 4;
		Creature h2('H', rand_dir);
		myGame.addCreature(h2, rx, ry);	
		rand_pos = rand() % 5184;
		rx = rand_pos / 72;
		ry = rand_pos % 72;
		rand_dir = rand() % 4;
		Creature r3('R', rand_dir);
		myGame.addCreature(r3, rx, ry);
		rand_pos = rand() % 5184;
		rx = rand_pos / 72;
		ry = rand_pos % 72;
		rand_dir = rand() % 4;
		Creature t4('T', rand_dir);
		myGame.addCreature(t4, rx, ry);
/*
	 	rand_pos = rand() % 5184;
		rx = rand_pos / 72;
		ry = rand_pos % 72;
		rand_dir = rand() % 4;
		Creature b('B', rand_dir);
		myGame.addCreature(b, rx, ry);
*/
	    }

	    for (int i = 0; i < 1001; i++) {
		if (i < 100)
		    myGame.printBoard();
		else if (i % 100 == 0)
		    myGame.printBoard();
		myGame.giveEveryoneOneTurn();
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

	    Darwin myGame(72, 72);
	    int rand_pos = rand() % 5184;
	    cout << "random position = " << rand_pos << endl;
	   /* 
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature f('F', rand_dir);
		myGame.addCreature(f, rx, ry);
	    }
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature h('H', rand_dir);
		myGame.addCreature(h, rx, ry);
	    }
	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature r('R', rand_dir);
		myGame.addCreature(r, rx, ry);
	    }   
 	    for (int i = 0; i < 10; i++) {
		int rand_pos = rand() % 5184;
		int rx = rand_pos / 72;
		int ry = rand_pos % 72;
		int rand_dir = rand() % 4;
		Creature t('T', rand_dir);
		myGame.addCreature(t, rx, ry);
	    }
*/
	    for (int i = 0; i < 10; i++) {
    		int rand_pos = rand() % 5184;
    		int rx = rand_pos / 72;
    		int ry = rand_pos % 72;
    		int rand_dir = rand() % 4;
    		Creature f1('F', rand_dir);
    		myGame.addCreature(f1, rx, ry);
    		rand_pos = rand() % 5184;
    		rx = rand_pos / 72;
    		ry = rand_pos % 72;
    		rand_dir = rand() % 4;
    		Creature h2('H', rand_dir);
    		
            myGame.addCreature(h2, rx, ry);	
    		rand_pos = rand() % 5184;
    		rx = rand_pos / 72;
    		ry = rand_pos % 72;
    		rand_dir = rand() % 4;
    	    Creature r3('R', rand_dir);
    		myGame.addCreature(r3, rx, ry);
    		rand_pos = rand() % 5184;
    		rx = rand_pos / 72;
    		ry = rand_pos % 72;
    		rand_dir = rand() % 4;
    		Creature t4('T', rand_dir);
    		myGame.addCreature(t4, rx, ry);
    	    rand_pos = rand() % 5184;
            rx = rand_pos / 72;
            ry = rand_pos % 72;
            rand_dir = rand() % 4;
            Creature b5('B', rand_dir);
            myGame.addCreature(b5, rx, ry);
        }

	    for (int i = 0; i <= 1000; i++) {
		if (i < 100)
		    myGame.printBoard();
		else if (i % 100 == 0)
		    myGame.printBoard();
		myGame.giveEveryoneOneTurn();
	    }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
	cout << "*** Darwin 7x12 ***" << endl;
        srand(0);

        Darwin myGame(7, 12);
        Creature trap('T', SOUTH);
        myGame.addCreature(trap, 0, 0);
        Creature hopper('H', EAST);
        myGame.addCreature(hopper, 3, 2);
        Creature rover('R', NORTH);
        myGame.addCreature(rover, 5, 4);
        Creature trap2('T', WEST);
        myGame.addCreature(trap2, 6, 8);

	myGame.printBoard();
	for (int i = 0; i <= 5; i++) {
	    //myGame.printBoard();
	    myGame.giveEveryoneOneTurn();
	    myGame.printBoard();
	}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 100x100  ***" << endl;
        srand(0);

	    Darwin myGame(100, 100);
	    int rand_pos = rand() % 10000;
	    cout << "random position = " << rand_pos << endl;

	    for (int i = 0; i < 20; i++) {
		int rand_pos = rand() % 10000;
		int rx = rand_pos / 100;
		int ry = rand_pos % 100;
		int rand_dir = rand() % 4;
		Creature f1('F', rand_dir);
		myGame.addCreature(f1, rx, ry);
		rand_pos = rand() % 10000;
		rx = rand_pos / 100;
		ry = rand_pos % 100;
		rand_dir = rand() % 4;
		Creature h2('H', rand_dir);
		myGame.addCreature(h2, rx, ry);	
		rand_pos = rand() % 10000;
		rx = rand_pos / 100;
		ry = rand_pos % 100;
		rand_dir = rand() % 4;

        rand_pos = rand() % 10000;
        rx = rand_pos / 100;
        ry = rand_pos % 100;
        rand_dir = rand() % 4;
        Creature b5('B', rand_dir);
        myGame.addCreature(b5, rx, ry);

		Creature r3('R', rand_dir);
		myGame.addCreature(r3, rx, ry);
		rand_pos = rand() % 10000;
		rx = rand_pos / 100;
		ry = rand_pos % 100;
		rand_dir = rand() % 4;
		Creature t4('T', rand_dir);
		myGame.addCreature(t4, rx, ry);

        
	    }

	    for (int i = 0; i <= 1000; i++) {
		if (i < 100)
		    myGame.printBoard();
		else if (i % 100 == 0)
		    myGame.printBoard();
		myGame.giveEveryoneOneTurn();
	    }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



}









