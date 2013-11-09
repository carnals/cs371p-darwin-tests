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

	Species food_species("f");
	food_species.add_instruction(Instruction::LEFT);
	food_species.add_instruction(Instruction::GO, 0);	
	Creature food(food_species);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

	Species hopper_species("h");
	hopper_species.add_instruction(Instruction::HOP);
	hopper_species.add_instruction(Instruction::GO, 0);
	Creature hopper(hopper_species);

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

	Species rover_species("r");
	rover_species.add_instruction(Instruction::IF_ENEMY, 9);
	rover_species.add_instruction(Instruction::IF_EMPTY, 7);
	rover_species.add_instruction(Instruction::IF_RANDOM, 5);
	rover_species.add_instruction(Instruction::LEFT);
	rover_species.add_instruction(Instruction::GO, 0);
	rover_species.add_instruction(Instruction::RIGHT);
	rover_species.add_instruction(Instruction::GO, 0);
	rover_species.add_instruction(Instruction::HOP);
	rover_species.add_instruction(Instruction::GO, 0);
	rover_species.add_instruction(Instruction::INFECT);
	rover_species.add_instruction(Instruction::GO, 0);
	Creature rover(rover_species);

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
	
	Species trap_species("t");
	trap_species.add_instruction(Instruction::IF_ENEMY, 3);
	trap_species.add_instruction(Instruction::LEFT);
	trap_species.add_instruction(Instruction::GO, 0);
	trap_species.add_instruction(Instruction::INFECT);
	trap_species.add_instruction(Instruction::GO, 0);
	Creature trap(trap_species);

	// ----
	// best
	// ----

	/*
	 0: if_wall 3
	 1: if_empty 7
	 2: if_enemy 5
	 3: left
	 4: go 0
	 5: infect
	 6: go 3
	 7: hop
	 8: go 2
	*/

	Species best_species("b");
	best_species.add_instruction(Instruction::IF_WALL, 3);
	best_species.add_instruction(Instruction::IF_EMPTY, 7);
	best_species.add_instruction(Instruction::IF_ENEMY, 5);
	best_species.add_instruction(Instruction::LEFT);
	best_species.add_instruction(Instruction::GO, 0);
	best_species.add_instruction(Instruction::INFECT);
	best_species.add_instruction(Instruction::GO, 3);
	best_species.add_instruction(Instruction::HOP);
	best_species.add_instruction(Instruction::GO, 2);
	Creature best(best_species);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        
        // 8x8 Darwin
		Darwin darwin_1(8, 8);

        // Food,   facing east,  at (0, 0)
		darwin_1.add_creature(food, 0, 0, Direction::EAST);

        // Hopper, facing north, at (3, 3)
		darwin_1.add_creature(hopper, 3, 3, Direction::NORTH);

        // Hopper, facing east,  at (3, 4)
		darwin_1.add_creature(hopper, 3, 4, Direction::EAST);

        // Hopper, facing south, at (4, 4)
		darwin_1.add_creature(hopper, 4, 4, Direction::SOUTH);
        
		// Hopper, facing west,  at (4, 3)
		darwin_1.add_creature(hopper, 4, 3, Direction::WEST);
		
        // Food,   facing north, at (7, 7)
		darwin_1.add_creature(food, 7, 7, Direction::NORTH);

        // Simulate 5 moves.
        // Print every grid.

		darwin_1.print_out();
		
		for (int i = 0; i < 5; ++i)
		{
			darwin_1.step();
			darwin_1.print_out();
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
        srand(0);
        
        // 7x9 Darwin
		Darwin darwin_2(7, 9);

        // Trap,   facing south, at (0, 0)
		darwin_2.add_creature(trap, 0, 0, Direction::SOUTH);

        // Hopper, facing east,  at (3, 2)
		darwin_2.add_creature(hopper, 3, 2, Direction::EAST);

        // Rover,  facing north, at (5, 4)
		darwin_2.add_creature(rover, 5, 4, Direction::NORTH);

        // Trap,   facing west,  at (6, 8)
		darwin_2.add_creature(trap, 6, 8, Direction::WEST);

        // Simulate 5 moves.
        // Print every grid.

		darwin_2.print_out();

		for (int i = 0; i < 5; ++i)
		{
			darwin_2.step();
			darwin_2.print_out();
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
        
		Darwin darwin_3(72, 72);
        // Randomly place the following creatures facing randomly.
        // Call rand(), mod it with 5184 (72x72), and use that for the position in a row-major order grid.
        // Call rand() again, mod it with 4 and use that for it's direction with the ordering: west, north, east, south.
        // Do that for each kind of creature.
        // 10 Food
        // 10 Hopper
        // 10 Rover
        // 10 Trap
        
		for (int i = 0; i < 4; ++i)
		{
			Creature c = food;

			switch(i) 
			{
			case 0:
				c = food;
				break;
			case 1:
				c = hopper;
				break;
			case 2:
				c = rover;
				break;
			case 3:
				c = trap;
				break;
			}

			for (int j = 0; j < 10; ++j)
			{
				int full_pos = rand() % 5184;	
				int x = full_pos % 72;
				int y = full_pos / 72;

				int full_dir = rand() % 4;

				Direction direction;
				
				switch(full_dir)
				{
				case 0:
					direction = Direction::WEST;
					break;
				case 1:
					direction = Direction::NORTH;
					break;
				case 2:
					direction = Direction::EAST;
					break;
				case 3:
					direction = Direction::SOUTH;
					break;
				}

				darwin_3.add_creature(c, x, y, direction);
			}
		}

		// Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        // Print every 100th grid after that (i.e. 100, 200, 300...1000).
		darwin_3.print_out();        

		for (;darwin_3.get_turn_number() < 1000;)
		{
			darwin_3.step();
			
			if (darwin_3.get_turn_number() < 10 || !(darwin_3.get_turn_number() % 100))
			{
				darwin_3.print_out();
			}
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
		Darwin darwin_4(72, 72);
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
		
		for (int i = 0; i < 5; ++i)
		{
			Creature c = food;

			switch(i) 
			{
			case 0:
				c = food;
				break;
			case 1:
				c = hopper;
				break;
			case 2:
				c = rover;
				break;
			case 3:
				c = trap;
				break;
			case 4:
				c = best;
				break;
			}

			for (int j = 0; j < 10; ++j)
			{
				int full_pos = rand() % 5184;	
				int x = full_pos % 72;
				int y = full_pos / 72;

				int full_dir = rand() % 4;

				Direction direction;
				
				switch(full_dir)
				{
				case 0:
					direction = Direction::WEST;
					break;
				case 1:
					direction = Direction::NORTH;
					break;
				case 2:
					direction = Direction::EAST;
					break;
				case 3:
					direction = Direction::SOUTH;
					break;
				}

				darwin_4.add_creature(c, x, y, direction);
			}
		}

		// Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        // Print every 100th grid after that (i.e. 100, 200, 300...1000).
		darwin_4.print_out();        

		for (;darwin_4.get_turn_number() < 1000;)
		{
			darwin_4.step();
			if (darwin_4.get_turn_number() < 10 || !(((int)darwin_4.get_turn_number()) % 100))
			{
				darwin_4.print_out();
			}
		}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin Random with Best ***" << endl;
        srand(0);
		
		// Create a random size grid where height < 150 and width < 150
		// Fill with a random number of each creature (include best), of at most 50 of that creature
		// Place at random location
		// Run 1000x, printing at same places as before 
		int height = rand() % 150;
		int width = rand() % 150;	
		Darwin darwin_4(height, width);

		for (int i = 0; i < 5; ++i)
		{
			Creature c = food;

			switch(i) 
			{
			case 0:
				c = food;
				break;
			case 1:
				c = hopper;
				break;
			case 2:
				c = rover;
				break;
			case 3:
				c = trap;
				break;
			case 4:
				c = best;
				break;
			}

			int num_c = rand() % 50;
			for (int j = 0; j < num_c; ++j)
			{
				int full_pos = rand() % (height * width);	
				int x = full_pos % width;
				int y = full_pos / width;
				int full_dir = rand() % 4;

				Direction direction;
				
				switch(full_dir)
				{
				case 0:
					direction = Direction::WEST;
					break;
				case 1:
					direction = Direction::NORTH;
					break;
				case 2:
					direction = Direction::EAST;
					break;
				case 3:
					direction = Direction::SOUTH;
					break;
				}

				darwin_4.add_creature(c, y, x, direction);
			}
		}

		// Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        // Print every 100th grid after that (i.e. 100, 200, 300...1000).
		darwin_4.print_out();        

		for (;darwin_4.get_turn_number() < 1000;)
		{
			darwin_4.step();
			if (darwin_4.get_turn_number() < 10 || !(((int)darwin_4.get_turn_number()) % 100))
			{
				darwin_4.print_out();
			}
		}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);
	}

    try {
        cout << "*** Darwin Random without Best ***" << endl;
        srand(0);
		
		// Create a random size grid where height < 150 and width < 150
		// Fill with a random number of each creature (excluding best), of at most 50 of that creature
		// Place at random location
		// Run 1000x, printing at same places as before 
		int height = rand() % 150;
		int width = rand() % 150;	
		Darwin darwin_4(height, width);

		for (int i = 0; i < 4; ++i)
		{
			Creature c = food;

			switch(i) 
			{
			case 0:
				c = food;
				break;
			case 1:
				c = hopper;
				break;
			case 2:
				c = rover;
				break;
			case 3:
				c = trap;
				break;
			}

			int num_c = rand() % 50;
			for (int j = 0; j < num_c; ++j)
			{
				int full_pos = rand() % (height * width);	
				int x = full_pos % width;
				int y = full_pos / width;
				int full_dir = rand() % 4;

				Direction direction;
				
				switch(full_dir)
				{
				case 0:
					direction = Direction::WEST;
					break;
				case 1:
					direction = Direction::NORTH;
					break;
				case 2:
					direction = Direction::EAST;
					break;
				case 3:
					direction = Direction::SOUTH;
					break;
				}

				darwin_4.add_creature(c, y, x, direction);
			}
		}

		// Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        // Print every 100th grid after that (i.e. 100, 200, 300...1000).
		darwin_4.print_out();        

		for (;darwin_4.get_turn_number() < 1000;)
		{
			darwin_4.step();
			if (darwin_4.get_turn_number() < 10 || !(((int)darwin_4.get_turn_number()) % 100))
			{
				darwin_4.print_out();
			}
		}
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);
	}

    try {
        cout << "*** BChean's 2x2 (#1) ***" << endl;
        
		Darwin darwin(2, 2);
		darwin.add_creature(rover, 0, 0, Direction::EAST);
		darwin.add_creature(rover, 1, 1, Direction::SOUTH);

		darwin.add_creature(trap, 0, 1, Direction::EAST);
		darwin.add_creature(trap, 1, 0, Direction::WEST);

		darwin.print_out();
		for (int i = 0; i < 4; ++i)
		{
			darwin.step();
			darwin.print_out();
		}
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** BChean's 4x12 (#5) ***" << endl;
        
		Darwin darwin(12, 4);
		darwin.add_creature(food, 4, 0, Direction::SOUTH);
		darwin.add_creature(food, 5, 0, Direction::SOUTH);
		darwin.add_creature(food, 6, 0, Direction::SOUTH);
		darwin.add_creature(food, 7, 0, Direction::SOUTH);

		darwin.add_creature(rover, 0, 0, Direction::EAST);
		darwin.add_creature(rover, 0, 1, Direction::EAST);
		darwin.add_creature(rover, 11, 0, Direction::WEST);
		darwin.add_creature(rover, 11, 1, Direction::WEST);
		
		darwin.add_creature(trap, 4, 2, Direction::NORTH);
		darwin.add_creature(trap, 5, 2, Direction::NORTH);
		darwin.add_creature(trap, 6, 2, Direction::NORTH);
		darwin.add_creature(trap, 7, 2, Direction::NORTH);
		darwin.add_creature(trap, 4, 3, Direction::NORTH);
		darwin.add_creature(trap, 5, 3, Direction::NORTH);
		darwin.add_creature(trap, 6, 3, Direction::NORTH);
		darwin.add_creature(trap, 7, 3, Direction::NORTH);
		darwin.print_out();
		
		for (int i = 0; i < 28; ++i)
		{
			darwin.step();
			darwin.print_out();
		}
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** NLaz's 5x5 ***" << endl;
        
		Darwin darwin(5, 5);
		darwin.add_creature(trap, 4, 0, Direction::WEST);
		darwin.add_creature(hopper, 4, 1, Direction::NORTH);
		darwin.add_creature(hopper, 4, 2, Direction::EAST);
		darwin.add_creature(hopper, 4, 3, Direction::SOUTH);
		darwin.add_creature(food, 4, 4, Direction::NORTH);
		
		for (int i = 0; i < 5; ++i)
		{
			darwin.step();
			darwin.print_out();
		}
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
	try {
        cout << "*** Josh2Xg 5x5 ***" << endl;
        
		Darwin darwin(5, 5);
		darwin.add_creature(trap, 0, 0, Direction::SOUTH);
		darwin.add_creature(hopper, 0, 1, Direction::EAST);
		darwin.add_creature(rover, 1, 0, Direction::NORTH);
		darwin.add_creature(trap, 1, 1, Direction::WEST);
		
		for (int i = 0; i < 5; ++i)
		{
			darwin.step();
			darwin.print_out();
		}
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	return 0;
}

