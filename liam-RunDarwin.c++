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

	Species Food;
	Food.push_back(Instruction(Instruction::LEFT));
	Food.push_back(Instruction(Instruction::GO, 0));

	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));
	
	Species Rover;
	Rover.push_back(Instruction(Instruction::IF_ENEMY, 9));
	Rover.push_back(Instruction(Instruction::IF_EMPTY, 7));
	Rover.push_back(Instruction(Instruction::IF_RANDOM, 5));
	Rover.push_back(Instruction(Instruction::LEFT));
	Rover.push_back(Instruction(Instruction::GO, 0));
	Rover.push_back(Instruction(Instruction::RIGHT));
	Rover.push_back(Instruction(Instruction::GO, 0));
	Rover.push_back(Instruction(Instruction::HOP));
	Rover.push_back(Instruction(Instruction::GO, 0));
	Rover.push_back(Instruction(Instruction::INFECT));
	Rover.push_back(Instruction(Instruction::GO, 0));

	Species Trap;
	Trap.push_back(Instruction(Instruction::IF_ENEMY, 3));
	Trap.push_back(Instruction(Instruction::LEFT));
	Trap.push_back(Instruction(Instruction::GO, 0));
	Trap.push_back(Instruction(Instruction::INFECT));
	Trap.push_back(Instruction(Instruction::GO, 0));

	Species Best;
	Best.push_back(Instruction(Instruction::IF_ENEMY, 6));
	Best.push_back(Instruction(Instruction::IF_EMPTY, 4));
	Best.push_back(Instruction(Instruction::LEFT));
	Best.push_back(Instruction(Instruction::GO, 0));
	Best.push_back(Instruction(Instruction::HOP));
	Best.push_back(Instruction(Instruction::GO, 0));
	Best.push_back(Instruction(Instruction::INFECT));
	Best.push_back(Instruction(Instruction::GO, 0));


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
		World w(8, 8);
		Creature food1 = Creature(Food, RIGHT, 'f');
		w.add(food1, 0, 0);
		Creature hopper1 = Creature(Hopper, UP, 'h');
		w.add(hopper1, 3, 3);
		Creature hopper2 = Creature(Hopper, RIGHT, 'h');
		w.add(hopper2, 3, 4);
		Creature hopper3 = Creature(Hopper, DOWN, 'h');
		w.add(hopper3, 4, 4);
		Creature hopper4 = Creature(Hopper, LEFT, 'h');
		w.add(hopper4, 4, 3);
		Creature food2 = Creature(Food, UP, 'f');
		w.add(food2, 7, 7);

		for (int i = 0; i < 6; i++) {
			cout << "Turn = " << i << "." << endl;
			w.printGrid();
			cout<<endl;
			w.step();
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
        /*
		  7x9 Darwin
		  Trap,   facing south, at (0, 0)
		  Hopper, facing east,  at (3, 2)
		  Rover,  facing north, at (5, 4)
		  Trap,   facing west,  at (6, 8)
		  Simulate 5 moves.
		  Print every grid.
        */

		World w(9, 7);
		Creature trap1 = Creature(Trap, DOWN, 't');
		w.add(trap1, 0, 0);
		Creature hopper = Creature(Hopper, RIGHT, 'h');
		w.add(hopper, 3, 2);
		Creature rover = Creature(Rover, UP, 'r');
		w.add(rover, 5, 4);
		Creature trap2 = Creature(Trap, LEFT, 't');
		w.add(trap2, 6, 8);
		

		for (int i = 0; i < 6; i++) {
			cout << "Turn = " << i << "." << endl;
			w.printGrid();
			cout<<endl;
			w.step();
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
		cout << "..." << endl << endl;
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

		World w(72, 72);
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Food, static_cast<DIR>(r2%4), 'f'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Hopper, static_cast<DIR>(r2%4), 'h'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Rover, static_cast<DIR>(r2%4), 'r'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Trap, static_cast<DIR>(r2%4), 't'), (r/72)%72, r%72);
		}

		for (int i = 0; i < 10; i++) {
			cout << "Turn = " << i << "." << endl;
			w.printGrid();
			cout<<endl;
			w.step();
		}
		for (int i = 10; i < 1001; i++) {
			cout << "Turn = " << i << "." << endl;
			if (i % 100 == 0) {
				w.printGrid();
			}
			cout<<endl;
			w.step();
		}
		
	}
    catch (const invalid_argument& a) {
		cout << a.what() << endl;
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

		cout << "..." << endl << endl;
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

		World w(72, 72);
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Best, static_cast<DIR>(r2%4), 'b'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Food, static_cast<DIR>(r2%4), 'f'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Hopper, static_cast<DIR>(r2%4), 'h'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Rover, static_cast<DIR>(r2%4), 'r'), (r/72)%72, r%72);
		}
		for (int i = 0; i < 10; i++) {
			uint r = rand();
			uint r2 = rand();
			w.add(Creature(Trap, static_cast<DIR>(r2%4), 't'), (r/72)%72, r%72);
		}

		for (int i = 0; i < 10; i++) {
			cout << "Turn = " << i << "." << endl;
			w.printGrid();
			cout<<endl;
			w.step();
		}
		for (int i = 10; i < 1001; i++) {
			cout << "Turn = " << i << "." << endl;
			if (i % 100 == 0) {
				w.printGrid();
			}
			cout<<endl;
			w.step();
		}
		
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
