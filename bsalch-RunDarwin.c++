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
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"  // DarwinGame
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
        food.addInstruction(0,"left");
        food.addInstruction(1,"go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species hopper('h');
        hopper.addInstruction(0, "hop");
        hopper.addInstruction(1, "go 0");

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
        rover.addInstruction(0,"if_enemy 9");
        rover.addInstruction(1,"if_empty 7");
        rover.addInstruction(2,"if_random 5");
        rover.addInstruction(3,"left");
        rover.addInstruction(4,"go 0");
        rover.addInstruction(5,"right");
        rover.addInstruction(6,"go 0");
        rover.addInstruction(7,"hop");
        rover.addInstruction(8,"go 0");
        rover.addInstruction(9,"infect");
        rover.addInstruction(10,"go 0");

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
        trap.addInstruction(0,"if_enemy 3");
        trap.addInstruction(1,"left");
        trap.addInstruction(2,"go 0");
        trap.addInstruction(3,"infect");
        trap.addInstruction(4,"go 0");



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
	Creature f1(&food,EAST);
	Creature h1(&hopper,NORTH);
	Creature h2(&hopper,EAST);
	Creature h3(&hopper,SOUTH);
	Creature h4(&hopper,WEST);
	Creature f2(&food,NORTH);

	DarwinGame game(8,8);

	game.addCreature(f1,0,0);
	game.addCreature(h1,3,3);
	game.addCreature(h2,3,4);
	game.addCreature(h3,4,4);
	game.addCreature(h4,4,3);
	game.addCreature(f2,7,7);
	
	game.printBoard();
	for(int i = 0; i < 5; i++){
		game.simulateMove();
		game.printBoard();
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
	
        int N = 72;
        DarwinGame game(N,N);
	Creature foods[10];
         for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int x = pos / N;
            int y = pos % N;
            int dir = rand() % 4;
	    DIRECTION direction;
		switch(dir){
			case 0: direction = WEST;
				break;
			case 1: direction = NORTH;
				break;
			case 2: direction = EAST;
				break;
			case 3: direction = SOUTH;
				break;
		};
            foods[i]=Creature(&food,direction);
            game.addCreature(foods[i],x,y);
         }
	Creature hoppers[10];
	for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int x = pos / N;
            int y = pos % N;
            int dir = rand() % 4;
            DIRECTION direction;
                switch(dir){
                        case 0: direction = WEST;
                                break;
                        case 1: direction = NORTH;
                                break;
                        case 2: direction = EAST;
                                break;
                        case 3: direction = SOUTH;
                                break;
                };
            hoppers[i] = Creature(&hopper,direction);
            game.addCreature(hoppers[i],x,y);
         }
	Creature rovers[10];
	for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int x = pos / N;
            int y = pos % N;
            int dir = rand() % 4;
            DIRECTION direction;
                switch(dir){
                        case 0: direction = WEST;
                                break;
                        case 1: direction = NORTH;
                                break;
                        case 2: direction = EAST;
                                break;
                        case 3: direction = SOUTH;
                                break;
                };
            rovers[i] = Creature(&rover,direction);
            game.addCreature(rovers[i],x,y);
         }
	Creature traps[10];
	for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int x = pos / N;
            int y = pos % N;
            int dir = rand() % 4;
            DIRECTION direction;
                switch(dir){
                        case 0: direction = WEST;
                                break;
                        case 1: direction = NORTH;
                                break;
                        case 2: direction = EAST;
                                break;
                        case 3: direction = SOUTH;
                                break;
                };
            traps[i] = Creature(&trap,direction);
            game.addCreature(traps[i],x,y);
         }
	game.printBoard();
	for(int i = 1; i < 10; i++){
		game.simulateMove();
		game.printBoard();
	}
	for(int i = 10; i <= 1000; i++){
		game.simulateMove();
		if(i % 100 == 0){
			game.printBoard();
		}
	}
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10
    // rover roundup
    // ------------

    try {
        cout << "*** Darwin 10x10 Rover Roundup ***" << endl;
        srand(0);
	Creature b1(&best,EAST);
	Creature b2(&best,SOUTH);
	Creature b3(&best,WEST);
	Creature b4(&best,NORTH);
        Creature r1(&rover,EAST);
        Creature r2(&rover,EAST);
        Creature r3(&rover,EAST);
	Creature r4(&rover,EAST);

        DarwinGame game(10,10);

        game.addCreature(b1,0,0);
        game.addCreature(b2,0,9);
        game.addCreature(b3,9,0);
        game.addCreature(b4,9,9);
	game.addCreature(r1,4,5);
	game.addCreature(r2,5,3);
	game.addCreature(r3,6,6);
	game.addCreature(r4,7,2);

        game.printBoard();
        for(int i = 1; i <= 1000; i++){
                game.simulateMove();
                if(i%10 == 0)
			game.printBoard();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	//rbrooks 200 lines of tests
	// ---------------
    // my tests
    // ---------------

    try
    {
        /*
make a 1x20 world
19 foods from spot o,o to o,18 facing west
1 trap at 0,19 facing west
40 moves
print first 10 and every 4th
*/
        cout << "*** Darwin 1x20 Buffet ***" << endl;
        srand(0);
        int i;
        DarwinGame test(1,20);
        Creature foods[19];
        for(i = 0; i < 19; ++i)
        {
            foods[i] = Creature(&food,WEST);
            test.addCreature(foods[i],0,i);
        }
        Creature crit_trap1 = Creature(&trap,WEST);
        test.addCreature(crit_trap1,0,19);

        test.printBoard();

          for(i = 1; i <= 40; ++i)
          {
            test.simulateMove();
            if(i <= 10 || i % 4 == 0)
            {
                test.printBoard();
            }
          }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        /*
make a 1x1 world
1 food at 0,0 facing west
4 moves
print every
watch food look for friends
so cry:'(
*/

        cout << "*** Darwin 1x1 Lonely ***" << endl;
        srand(0);
        DarwinGame test(1,1);
        
        Creature crit_food1 = Creature(&food,WEST);
        test.addCreature(crit_food1,0,0);

        int i;
        test.printBoard();

        for(i = 1; i <= 4; ++i)
        {

          test.simulateMove();
          test.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        /*
make a 2x2 world
3 rovers at 0,0 0,1 and 1,0 facing west, north and east
8 moves
print every
watch the happy rovers hop around as friends
*/
        cout << "*** Darwin 2x2 Circle ***" << endl;
        srand(0);
        DarwinGame test(2,2);
        
        Creature crit_rover1 = Creature(&rover,WEST);
        test.addCreature(crit_rover1,0,0);
        Creature crit_rover2 = Creature(&rover,NORTH);
        test.addCreature(crit_rover2,0,1);
        Creature crit_rover3 = Creature(&rover,EAST);
        test.addCreature(crit_rover3,1,0);

        int i;
        test.printBoard();

        for(i = 1; i <= 8; ++i)
        {

          test.simulateMove();
          test.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
         /*
make a 4x4 world
4 rovers on top row facing South
4 rovers on second row facing west
4 traps on tird row facing EAst
4 traps on bottom row facing North
10 years
print every
the rovers are fed up with the traps trying to
take over their home turf
*/
        cout << "*** Darwin 4x4 Gang Fight ***" << endl;
        srand(0);
        DarwinGame test(4,4);
        
        Creature crit_rover1 = Creature(&rover,SOUTH);
        test.addCreature(crit_rover1,0,0);
        Creature crit_rover2 = Creature(&rover,SOUTH);
        test.addCreature(crit_rover2,0,1);
        Creature crit_rover3 = Creature(&rover,SOUTH);
        test.addCreature(crit_rover3,0,2);
        Creature crit_rover4 = Creature(&rover,SOUTH);
        test.addCreature(crit_rover4,0,3);
        Creature crit_rover5 = Creature(&rover,WEST);
        test.addCreature(crit_rover5,1,0);
        Creature crit_rover6 = Creature(&rover,WEST);
        test.addCreature(crit_rover6,1,1);
        Creature crit_rover7 = Creature(&rover, WEST);
        test.addCreature(crit_rover7,1,2);
        Creature crit_rover8 = Creature(&rover,WEST);
        test.addCreature(crit_rover8,1,3);

        Creature crit_trap1 = Creature(&trap,EAST);
        test.addCreature(crit_trap1,2,0);
        Creature crit_trap2 = Creature(&trap,EAST);
        test.addCreature(crit_trap2,2,1);
        Creature crit_trap3 = Creature(&trap,EAST);
        test.addCreature(crit_trap3,2,2);
        Creature crit_trap4 = Creature(&trap,EAST);
        test.addCreature(crit_trap4,2,3);
        Creature crit_trap5 = Creature(&trap,NORTH);
        test.addCreature(crit_trap5,3,0);
        Creature crit_trap6 = Creature(&trap,NORTH);
        test.addCreature(crit_trap6,3,1);
        Creature crit_trap7 = Creature(&trap,NORTH);
        test.addCreature(crit_trap7,3,2);
        Creature crit_trap8 = Creature(&trap,NORTH);
        test.addCreature(crit_trap8,3,3);

        int i;
        test.printBoard();

        for(i = 1; i <= 10; ++i)
        {
          test.simulateMove();
          test.printBoard();
          
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}

