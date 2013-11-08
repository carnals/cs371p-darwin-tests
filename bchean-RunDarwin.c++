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
#include <vector>

#include "Darwin.h"

using namespace std;

void print_grid_simulation(Grid& grid, int num_steps) {
	cout << "Turn = 0.\n";
	grid.print(cout);
	cout << "\n";
	for (int i = 1; i <= num_steps; ++i) {
		grid.goad_all_creatures();
		cout << "Turn = " << i << ".\n";
		grid.print(cout);
		cout << "\n";
	}
}

int main() {
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

	Food food_species;
	Hopper hopper_species;
	Rover rover_species;
	Trap trap_species;

	int num_rows;
	int num_cols;
	int num_steps;

	// --------
	// my tests
	// --------

	{
		/*
		2x2
		2 Rover
		2 Trap
		Steps 0-4
		*/
		num_rows = 2;
		num_cols = 2;
		num_steps = 4;

		cout << "*** mine #1, " << num_rows << "x" << num_cols << " ***" << "\n";
		srand(0);

		Grid grid(num_rows, num_cols);

		Creature r1(rover_species, Direction::EAST);
		grid.place_creature(0, 0, r1);
		Creature r2(rover_species, Direction::SOUTH);
		grid.place_creature(1, 1, r2);

		Creature t1(trap_species, Direction::EAST);
		grid.place_creature(1, 0, t1);
		Creature t2(trap_species, Direction::WEST);
		grid.place_creature(0, 1, t2);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		3x12
		6 Rover
		6 Trap
		Steps 0-22
		*/
		num_rows = 3;
		num_cols = 12;
		num_steps = 22;

		cout << "*** mine #2, " << num_rows << "x" << num_cols << " ***" << "\n";
		srand(0);

		Grid grid(num_rows, num_cols);

		Creature r1(rover_species, Direction::WEST);
		grid.place_creature(0, 5, r1);
		Creature r2(rover_species, Direction::WEST);
		grid.place_creature(1, 5, r2);
		Creature r3(rover_species, Direction::WEST);
		grid.place_creature(2, 5, r3);
		Creature r4(rover_species, Direction::EAST);
		grid.place_creature(0, 6, r4);
		Creature r5(rover_species, Direction::EAST);
		grid.place_creature(1, 6, r5);
		Creature r6(rover_species, Direction::EAST);
		grid.place_creature(2, 6, r6);

		Creature t1(trap_species, Direction::EAST);
		grid.place_creature(0, 0, t1);
		Creature t2(trap_species, Direction::EAST);
		grid.place_creature(0, 1, t2);
		Creature t3(trap_species, Direction::EAST);
		grid.place_creature(1, 0, t3);
		Creature t4(trap_species, Direction::WEST);
		grid.place_creature(1, 11, t4);
		Creature t5(trap_species, Direction::WEST);
		grid.place_creature(2, 10, t5);
		Creature t6(trap_species, Direction::WEST);
		grid.place_creature(2, 11, t6);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		12x3
		9 Hopper
		1 Rover
		Steps 0-22
		*/
		num_rows = 12;
		num_cols = 3;
		num_steps = 22;

		cout << "*** mine #3, " << num_rows << "x" << num_cols << " ***" << "\n";
		srand(0);

		Grid grid(num_rows, num_cols);

		Creature h1(hopper_species, Direction::SOUTH);
		grid.place_creature(5, 0, h1);
		Creature h2(hopper_species, Direction::SOUTH);
		grid.place_creature(6, 0, h2);
		Creature h3(hopper_species, Direction::SOUTH);
		grid.place_creature(7, 0, h3);
		Creature h4(hopper_species, Direction::NORTH);
		grid.place_creature(9, 1, h4);
		Creature h5(hopper_species, Direction::NORTH);
		grid.place_creature(10, 1, h5);
		Creature h6(hopper_species, Direction::NORTH);
		grid.place_creature(11, 1, h6);
		Creature h7(hopper_species, Direction::SOUTH);
		grid.place_creature(0, 2, h7);
		Creature h8(hopper_species, Direction::SOUTH);
		grid.place_creature(1, 2, h8);
		Creature h9(hopper_species, Direction::SOUTH);
		grid.place_creature(2, 2, h9);

		Creature r1(rover_species, Direction::SOUTH);
		grid.place_creature(4, 0, r1);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		12x3
		7 Rover
		9 Trap
		Steps 0-20
		*/
		num_rows = 12;
		num_cols = 3;
		num_steps = 20;

		cout << "*** mine #4, " << num_rows << "x" << num_cols << " ***" << "\n";
		srand(0);

		Grid grid(num_rows, num_cols);

		Creature r1(rover_species, Direction::NORTH);
		grid.place_creature(4, 1, r1);
		Creature r2(rover_species, Direction::NORTH);
		grid.place_creature(5, 1, r2);
		Creature r3(rover_species, Direction::NORTH);
		grid.place_creature(6, 1, r3);
		Creature r4(rover_species, Direction::NORTH);
		grid.place_creature(7, 1, r4);
		Creature r5(rover_species, Direction::NORTH);
		grid.place_creature(8, 1, r5);
		Creature r6(rover_species, Direction::NORTH);
		grid.place_creature(9, 1, r6);
		Creature r7(rover_species, Direction::NORTH);
		grid.place_creature(10, 1, r7);

		Creature t1(trap_species, Direction::SOUTH);
		grid.place_creature(0, 0, t1);
		Creature t2(trap_species, Direction::SOUTH);
		grid.place_creature(0, 1, t2);
		Creature t3(trap_species, Direction::SOUTH);
		grid.place_creature(0, 2, t3);
		Creature t4(trap_species, Direction::SOUTH);
		grid.place_creature(1, 0, t4);
		Creature t5(trap_species, Direction::SOUTH);
		grid.place_creature(1, 1, t5);
		Creature t6(trap_species, Direction::SOUTH);
		grid.place_creature(1, 2, t6);
		Creature t7(trap_species, Direction::SOUTH);
		grid.place_creature(2, 0, t7);
		Creature t8(trap_species, Direction::SOUTH);
		grid.place_creature(2, 1, t8);
		Creature t9(trap_species, Direction::SOUTH);
		grid.place_creature(2, 2, t9);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		4x12
		4 Food
		4 Rover
		8 Trap
		Steps 0-28
		*/
		num_rows = 4;
		num_cols = 12;
		num_steps = 28;

		cout << "*** mine #5, " << num_rows << "x" << num_cols << " ***" << "\n";
		srand(0);

		Grid grid(num_rows, num_cols);

		Creature f1(food_species, Direction::SOUTH);
		grid.place_creature(0, 4, f1);
		Creature f2(food_species, Direction::SOUTH);
		grid.place_creature(0, 5, f2);
		Creature f3(food_species, Direction::SOUTH);
		grid.place_creature(0, 6, f3);
		Creature f4(food_species, Direction::SOUTH);
		grid.place_creature(0, 7, f4);

		Creature r1(rover_species, Direction::EAST);
		grid.place_creature(0, 0, r1);
		Creature r2(rover_species, Direction::EAST);
		grid.place_creature(1, 0, r2);
		Creature r3(rover_species, Direction::WEST);
		grid.place_creature(0, 11, r3);
		Creature r4(rover_species, Direction::WEST);
		grid.place_creature(1, 11, r4);

		Creature t1(trap_species, Direction::NORTH);
		grid.place_creature(2, 4, t1);
		Creature t2(trap_species, Direction::NORTH);
		grid.place_creature(2, 5, t2);
		Creature t3(trap_species, Direction::NORTH);
		grid.place_creature(2, 6, t3);
		Creature t4(trap_species, Direction::NORTH);
		grid.place_creature(2, 7, t4);
		Creature t5(trap_species, Direction::NORTH);
		grid.place_creature(3, 4, t5);
		Creature t6(trap_species, Direction::NORTH);
		grid.place_creature(3, 5, t6);
		Creature t7(trap_species, Direction::NORTH);
		grid.place_creature(3, 6, t7);
		Creature t8(trap_species, Direction::NORTH);
		grid.place_creature(3, 7, t8);

		print_grid_simulation(grid, num_steps);
	}

	// ---------------
	// downing's tests
	// ---------------

	{
		/*
		8x8
		2 Food
		4 Hopper
		Steps 0-5
		*/

		num_steps = 5;

		cout << "*** downing #1, 8x8 ***" << "\n";

		Grid grid(8, 8);

		Creature f1(food_species, Direction::EAST);
		grid.place_creature(0, 0, f1);
		Creature f2(food_species, Direction::NORTH);
		grid.place_creature(7, 7, f2);

		Creature h1(hopper_species, Direction::NORTH);
		grid.place_creature(3, 3, h1);
		Creature h2(hopper_species, Direction::EAST);
		grid.place_creature(3, 4, h2);
		Creature h3(hopper_species, Direction::SOUTH);
		grid.place_creature(4, 4, h3);
		Creature h4(hopper_species, Direction::WEST);
		grid.place_creature(4, 3, h4);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		7x9
		1 Hopper
		1 Rover
		2 Trap
		Steps 0-5
		*/

		num_steps = 5;

		cout << "*** downing #2, 7x9 ***" << "\n";
		srand(0);

		Grid grid(7, 9);

		Creature h1(hopper_species, Direction::EAST);
		grid.place_creature(3, 2, h1);

		Creature r1(rover_species, Direction::NORTH);
		grid.place_creature(5, 4, r1);

		Creature t1(trap_species, Direction::SOUTH);
		grid.place_creature(0, 0, t1);
		Creature t2(trap_species, Direction::WEST);
		grid.place_creature(6, 8, t2);

		print_grid_simulation(grid, num_steps);
	}

	{
		/*
		72x72
		10 Food
		10 Hopper
		10 Rover
		10 Trap
		Random position, random direction
		Steps 0-9, 100, 200, ..., 1000
		*/

		int N = 72;

		cout << "*** downing #3, 72x72 ***" << "\n";
		srand(0);

		Grid grid(N, N);

		Creature foods[10];
		for (int i = 0; i < 10; ++i) {
			int grid_index = rand() % (N*N);
			int row = grid_index / N;
			int col = grid_index % N;

			int direction = rand() % 4;

			foods[i] = Creature(food_species, direction);
			grid.place_creature(row, col, foods[i]);
		}

		Creature hoppers[10];
		for (int i = 0; i < 10; ++i) {
			int grid_index = rand() % (N*N);
			int row = grid_index / N;
			int col = grid_index % N;

			int direction = rand() % 4;

			hoppers[i] = Creature(hopper_species, direction);
			grid.place_creature(row, col, hoppers[i]);
		}

		Creature rovers[10];
		for (int i = 0; i < 10; ++i) {
			int grid_index = rand() % (N*N);
			int row = grid_index / N;
			int col = grid_index % N;

			int direction = rand() % 4;

			rovers[i] = Creature(rover_species, direction);
			grid.place_creature(row, col, rovers[i]);
		}

		Creature traps[10];
		for (int i = 0; i < 10; ++i) {
			int grid_index = rand() % (N*N);
			int row = grid_index / N;
			int col = grid_index % N;

			int direction = rand() % 4;

			traps[i] = Creature(trap_species, direction);
			grid.place_creature(row, col, traps[i]);
		}

		cout << "Turn = 0.\n";
		grid.print(cout);
		cout << "\n";

		for (int i = 1; i <= 9; ++i) {
			grid.goad_all_creatures();
			cout << "Turn = " << i << ".\n";
			grid.print(cout);
			cout << "\n";
		}

		for (int i = 10; i <= 1000; ++i) {
			grid.goad_all_creatures();
			if (i % 100 == 0) {
				cout << "Turn = " << i << ".\n";
				grid.print(cout);
				cout << "\n";
			}
		}
	}

	return 0;
}

