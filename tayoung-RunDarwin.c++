// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// Modified by:
// Tyler A. Young
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

// ------------
// add_randomly
// ------------
void add_randomly(Darwin& g, Species* s)
{
	using namespace std;
	unsigned int rows = g.gameboard.size();
	unsigned int cols = g.gameboard[0].size();
	unsigned int ran = rand() % (rows*cols);
	//	cout << rows << " " << cols << endl;
	int x = ran/rows;
	int y = ran%cols;
	cout << x << " " << y << endl;
	int facing = rand()%4;
	g.add_creature(*s, x,y, facing);
}

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

	// Species
	Species trap("trap");
	Species food("food");
	Species rover("rover");
	Species hopper("hopper");

	// Instructions
	string trap_i[] = {"if_enemy 3","left","go 0","infect","go 0"};
	string food_i[] = {"left","go 0"};
	string rover_i[] = {"if_enemy 9","if_empty 7","if_random 5","left",
			"go 0","right","go 0","hop","go 0","infect","go 0"};
	string hopper_i[] = {"hop","go 0"};

	for(int i=0; i < 5; i++)
		trap.add_instruction(trap_i[i]);
	for(int i=0; i < 2; i++)
		food.add_instruction(food_i[i]);
	for(int i=0; i < 11; i++)
		rover.add_instruction(rover_i[i]);
	for(int i=0; i < 2; i++)
		hopper.add_instruction(hopper_i[i]);

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
		Darwin game(8,8);

		// Add creatures at the specified positions.
		Creature f1(&game.gameboard,food, 0,0, East);
		Creature h1(&game.gameboard,hopper, 3,3, North);
		Creature h2(&game.gameboard,hopper, 3,4, East);
		Creature h3(&game.gameboard,hopper, 4,4, South);
		Creature h4(&game.gameboard,hopper, 4,3, West);
		Creature f2(&game.gameboard,food, 7,7, North);

		// Run the simulation for 5 steps.
		game.run_simulation(5, true, 5);

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
		Darwin game(7,9);

		// Add creatures at the specified positions.
		Creature t1(&game.gameboard,trap,  0,0, South);
		Creature h(&game.gameboard,hopper, 3,2, East);
		Creature r(&game.gameboard,rover,  5,4, North);
		Creature t2(&game.gameboard,trap,  6,8, West);

		// Run the simulation for 5 steps.
		game.run_simulation(5, true, 5);

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

		int rows = 72;
		int cols = 72;
		Darwin game(rows,cols);


		// Add creatures randomly.

		// Food
		for(int i=0; i < 10; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(food, x,y, facing);
		}
		// Hopper
		for(int i=0; i < 10; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(hopper, x,y, facing);
		}
		// Rover
		for(int i=0; i < 10; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(rover, x,y, facing);
		}
		// Trap
		for(int i=0; i < 10; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(trap, x,y, facing);
		}

		// Run the simulation for 1000 steps. Print first 10, after that, every 100.
		game.run_simulation(1000, true, 10);
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// MINE
	try {
		cout << "*** Darwin 17x17 ***" << endl;
		srand(0);

		int rows = 17;
		int cols = 17;
		Darwin game(rows,cols);

		// Add creatures randomly.

		// Food
		for(int i=0; i < 5; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(food, x,y, facing);
		}
		// Hopper
		for(int i=0; i < 5; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(hopper, x,y, facing);
		}
		// Rover
		for(int i=0; i < 5; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(rover, x,y, facing);
		}
		// Trap
		for(int i=0; i < 2; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(trap, x,y, facing);
		}

		// Run the simulation for 51 steps, print every 17th
		game.run_simulation(51, true, 0, 17);
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 34x34 ***" << endl;
		srand(34);

		int rows = 34;
		int cols = 34;
		Darwin game(rows,cols);

		// Add creatures randomly.

		// Food
		for(int i=0; i < 7; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(food, x,y, facing);
		}
		// Hopper
		for(int i=0; i < 8; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(hopper, x,y, facing);
		}
		// Rover
		for(int i=0; i < 6; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(rover, x,y, facing);
		}
		// Trap
		for(int i=0; i < 7; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(trap, x,y, facing);
		}

		// Run the simulation for 85 steps, print every 17th
		game.run_simulation(85, true, 0, 17);
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 11x11 ***" << endl;
		srand(0);

		Darwin game(11,11);

		// Add creatures at the specified positions.
		Creature t1(&game.gameboard,trap,  0,0, South);
		Creature h(&game.gameboard,hopper, 3,2, East);
		Creature r(&game.gameboard,rover,  5,4, North);
		Creature t2(&game.gameboard,trap,  7,8, West);
		Creature f(&game.gameboard,rover,  3,6, North);
		Creature f2(&game.gameboard,trap,  8,8, West);
		Creature h2(&game.gameboard,hopper, 1,5, East);
		Creature h3(&game.gameboard,hopper, 10,10, North);

		// Run the simulation for 12 steps.
		game.run_simulation(12, true, 12);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 75x75 ***" << endl;
		srand(666);

		int rows = 75;
		int cols = 75;
		Darwin game(rows,cols);

		// Add creatures randomly.

		// Food
		for(int i=0; i < 13; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(food, x,y, facing);
		}
		// Hopper
		for(int i=0; i < 22; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(hopper, x,y, facing);
		}
		// Rover
		for(int i=0; i < 17; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(rover, x,y, facing);
		}
		// Trap
		for(int i=0; i < 9; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(trap, x,y, facing);
		}

		// Run the simulation for 247 steps, print every 19th
		game.run_simulation(247, true, 0, 19);
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 50x25 ***" << endl;
		srand(89);

		int rows = 50;
		int cols = 25;
		Darwin game(rows,cols);

		// Add creatures randomly.

		// Food
		for(int i=0; i < 11; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(food, x,y, facing);
		}
		// Hopper
		for(int i=0; i < 8; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(hopper, x,y, facing);
		}
		// Rover
		for(int i=0; i < 5; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(rover, x,y, facing);
		}
		// Trap
		for(int i=0; i < 3; i++)
		{
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			game.add_creature(trap, x,y, facing);
		}

		// Run the simulation for 50 steps, print every 10th
		game.run_simulation(50, true, 0, 10);
	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	// OTHER PEOPLE'S TESTS
	// osaprych
	try {
		cout << "*** Darwin 2x2 without Best ***" << endl;
		srand(0);
		int rows = 2;
		int cols = 2;

		Darwin game(rows,cols);

		// Add Creatures
		int ran = rand() % (rows*cols);
		int x = ran/rows;
		int y = ran%cols;
		int facing = rand()%4;
		game.add_creature(rover, x,y, facing);

		ran = rand() % (rows*cols);
		x = ran/rows;
		y = ran%cols;
		facing = rand()%4;
		game.add_creature(hopper, x,y, facing);

		game.run_simulation(7, true, 7);
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	try {
		cout << "*** Darwin 10x10 without Best ***" << endl;
		srand(0);
		int rows = 10;
		int cols = 10;

		Darwin game(rows,cols);

		// Add Creatures
		int ran = rand() % (rows*cols);
		int x = ran/rows;
		int y = ran%cols;
		int facing = rand()%4;
		game.add_creature(rover, x,y, facing);

		game.run_simulation(1000, true, 0);
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// nlaz
	try {
		cout << "*** Darwin 5x5 ***" << endl;
		srand(0);
		/*
         5x5 Darwin
         Trap,   facing west, at (4, 0)
         Hopper,   facing north,  at (4, 1)
         Hopper,  facing east, at (4, 2)
         Hopper,   facing south,  at (4, 3)
         Food,  face north, at (4,4);
         Simulate 5 moves.
         Print every grid.
		 */
		Darwin game(5,5);

		game.add_creature(trap,   4,0, West);
		game.add_creature(hopper, 4,1, North);
		game.add_creature(hopper, 4,2, East);
		game.add_creature(hopper, 4,3, South);
		game.add_creature(food,   4,4, North);

		game.run_simulation(5, true, 5);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// psteiner
	try {
		cout << "*** Darwin direction infection test all directions, all types ***" << endl;
		Darwin darwin(5, 5);
		darwin.add_creature(food, 0, 2, South);
		darwin.add_creature(trap, 1, 2, North);
		darwin.add_creature(hopper, 2, 0, East);
		darwin.add_creature(trap, 2, 1, West);
		darwin.add_creature(trap, 2, 3, East);
		darwin.add_creature(hopper, 2, 4, West);
		darwin.add_creature(trap, 3, 2, South);
		darwin.add_creature(rover, 4, 2, South);

		darwin.run_simulation(1,true,1);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 6x6 rover motion sanity ***" << endl;
		Darwin darwin(6, 6);
		darwin.add_creature(rover, 3, 3, West);

		darwin.run_simulation(10,true,10,25);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 10x10 random placement ***" << endl;

		const int rows = 10;
		const int cols = 10;
		Darwin darwin(rows, cols);

		int ran = rand()%(rows*cols);
		int x = ran/rows;
		int y = ran%cols;
		int facing = rand()%4;
		darwin.add_creature(trap, x,y, facing);

		ran = rand()%(rows*cols);
		x = ran/rows;
		y = ran%cols;
		facing = rand()%4;
		darwin.add_creature(food, x,y, facing);

		ran = rand()%(rows*cols);
		x = ran/rows;
		y = ran%cols;
		facing = rand()%4;
		darwin.add_creature(trap, x,y, facing);

		ran = rand()%(rows*cols);
		x = ran/rows;
		y = ran%cols;
		facing = rand()%4;
		darwin.add_creature(food, x,y, facing);

		ran = rand()%(rows*cols);
		x = ran/rows;
		y = ran%cols;
		facing = rand()%4;
		darwin.add_creature(trap, x,y, facing);

		darwin.run_simulation(5, true, 5);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 10x10 trap infection ***" << endl;
		Darwin darwin(10, 10);

		for (int i=0; i < 9; i++){
			for (int j =0; j < 10; j++){
				darwin.add_creature(hopper, i,j, South);
			}
		}

		for (int j =0; j < 10; j++){
			darwin.add_creature(trap, 9, j, North);
		}

		darwin.run_simulation(25, true, 25);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 5x5 infect trap full 360 rotation ***" << endl;
		Darwin darwin(5, 5);
		darwin.add_creature(trap, 0, 0, South);
		darwin.add_creature(trap, 0, 2, West);
		darwin.add_creature(trap, 0, 4, South);
		darwin.add_creature(hopper, 4, 2, North);
		darwin.add_creature(hopper, 4, 0, North);
		darwin.add_creature(hopper, 4, 4, North);

		darwin.run_simulation(5,true,5);

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// tashar
	try {
		cout << "*** Darwin 25x25 ***" << endl;
		srand(0);
		const int rows = 25;
		const int cols = 25;
		Darwin d(rows, cols);
		for(int i = 0; i < 100; i ++) {
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			d.add_creature(hopper, x,y, facing);
		}
		for(int i = 0; i < 10; i ++) {
			int ran = rand()%(rows*cols);
			int x = ran/rows;
			int y = ran%cols;
			int facing = rand()%4;
			d.add_creature(trap, x,y, facing);
		}
		d.run_simulation(20, true, 0, 2);
	}
	catch (const invalid_argument& e) {
		assert(false);}
	catch (const out_of_range& e) {
		assert(false);}

	//

	//    try {
	//         cout << "*** Darwin 10x10 without Best ***" << endl;
	//         srand(0);
	//         Darwin game(10, 10);
	//         add_somewhere(w, &rover,  10, 10);
	//
	//         int s = 0;
	//         for (; s <= 1000; s++){
	//             w.print(cout);
	//             w.step();
	//         }
	//     } catch (const invalid_argument&) {
	//         assert(false);
	//     } catch (const out_of_range&) {
	//         assert(false);
	//     }

	return 0;}
