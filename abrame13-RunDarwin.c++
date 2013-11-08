#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <vector>

#include "darwin.h"



int main() {

	// ----
  // food
  // ----

  /*
	0: left
	1: go 0
	*/

	Species food('f');
	food.addInstruction(I_LEFT);
	food.addInstruction(I_GO, 0);

  // ------
  // hopper
  // ------

  /*
	0: hop
	1: go 0
	*/

	Species hopper('h');
	hopper.addInstruction(I_HOP);
	hopper.addInstruction(I_GO, 0);

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
	rover.addInstruction(I_ENEMY, 9);
	rover.addInstruction(I_EMPTY, 7);
	rover.addInstruction(I_RANDOM, 5);
	rover.addInstruction(I_LEFT);
	rover.addInstruction(I_GO, 0);
	rover.addInstruction(I_RIGHT);
	rover.addInstruction(I_GO, 0);
	rover.addInstruction(I_HOP);
	rover.addInstruction(I_GO, 0);
	rover.addInstruction(I_INFECT);
	rover.addInstruction(I_GO, 0);

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
	trap.addInstruction(I_ENEMY, 3);
	trap.addInstruction(I_LEFT);
	trap.addInstruction(I_GO, 0);
	trap.addInstruction(I_INFECT);
	trap.addInstruction(I_GO, 0);


	// ----
	// best
	// ----

	Species best('b');
	best.addInstruction(I_ENEMY, 9);
	best.addInstruction(I_EMPTY, 7);
	best.addInstruction(I_RANDOM, 3);

	best.addInstruction(I_LEFT);
	best.addInstruction(I_GO, 0);

	best.addInstruction(I_RIGHT);
	best.addInstruction(I_GO, 0);

	best.addInstruction(I_HOP);
	best.addInstruction(I_GO, 0);
	best.addInstruction(I_INFECT);
	best.addInstruction(I_GO, 0);




	// ----------
  // darwin 8x8
  // ----------

  try {
    cout << "*** Darwin 8x8 ***" << endl;
    /*
		8x8 Darwin
		Food, facing east, at (0, 0)
		Hopper, facing north, at (3, 3)
		Hopper, facing east, at (3, 4)
		Hopper, facing south, at (4, 4)
		Hopper, facing west, at (4, 3)
		Food, facing north, at (7, 7)
		Simulate 5 moves.
		Print every grid.
		*/

		Darwin game(8, 8);
		game.addCreature(Creature(&food, D_EAST), 0, 0);
		game.addCreature(Creature(&hopper, D_NORTH), 3, 3);
		game.addCreature(Creature(&hopper, D_EAST), 3, 4);
		game.addCreature(Creature(&hopper, D_SOUTH), 4, 4);
		game.addCreature(Creature(&hopper, D_WEST), 4, 3);
		game.addCreature(Creature(&food, D_NORTH), 7, 7);

		int i;
		game.print(cout);
		for (i = 0; i < 5; i++) {
			game.play();
			game.print(cout);
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
    /*
		7x9 Darwin
		Trap, facing south, at (0, 0)
		Hopper, facing east, at (3, 2)
		Rover, facing north, at (5, 4)
		Trap, facing west, at (6, 8)
		Simulate 5 moves.
		Print every grid.
		*/

		Darwin game(7, 9);
		game.addCreature(Creature(&trap, D_SOUTH), 0, 0);
		game.addCreature(Creature(&hopper, D_EAST), 3, 2);
		game.addCreature(Creature(&rover, D_NORTH), 5, 4);
		game.addCreature(Creature(&trap, D_WEST), 6, 8);

		int i;
		game.print(cout);
		for (i = 0; i < 5; i++) {
			game.play();
			game.print(cout);
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
		Print the first 10 grids (i.e. 0, 1, 2...9).
		Print every 100th grid after that (i.e. 100, 200, 300...1000).
		*/

		Darwin game(72, 72);
		int r;
		int row, col;
		int dir;
		int i;

		// place foods
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&food, dir), row, col);
		}

		// place hoppers
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&hopper, dir), row, col);
		}

		// place rovers
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&rover, dir), row, col);
		}

		// place traps
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&trap, dir), row, col);
		}

		// do the sim
		game.print(cout);

		for (i = 1; i <= 1000; i++){
			game.play();

			//print sometimes
			if (i % 100 == 0 || i < 10)
				game.print(cout);
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
		Print the first 10 grids (i.e. 0, 1, 2...9).
		Print every 100th grid after that (i.e. 100, 200, 300...1000).
		*/

		Darwin game(72, 72);
		int r;
		int row, col;
		int dir;
		int i;

		// place foods
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&food, dir), row, col);
		}

		// place hoppers
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&hopper, dir), row, col);
		}

		// place rovers
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&rover, dir), row, col);
		}

		// place traps
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&trap, dir), row, col);
		}

		// place bests
		for (i = 0; i < 10; i++) {
			r = rand() % 5184;
			row = r / 72;
			col = r % 72;
			dir = rand() % 4;
			game.addCreature(Creature(&best, dir), row, col);
		}

		// do the sim
		game.print(cout);

		for (i = 1; i <= 1000; i++){
			game.play();

			//print sometimes
			if (i % 100 == 0 || i < 10)
				game.print(cout);
		}


  }
	catch (const invalid_argument&) {
	  assert(false);}
	catch (const out_of_range&) {
	  assert(false);}



  // my tests

  // ------------
  // darwin 100x100
  // without best
  // ------------

  try {
    cout << "*** Darwin 100x100 ***" << endl;
    srand(0);
    /*
	Randomly place 20 of each creature
	Simulate 100 moves.
	Print every 10.
	*/

	Darwin game(100, 100);
	int r;
	int row, col;
	int dir;
	int i;

	// place foods
	for (i = 0; i < 20; i++) {
		r = rand() % 10000;
		row = r / 100;
		col = r % 100;
		dir = rand() % 4;
		game.addCreature(Creature(&food, dir), row, col);
	}

	// place hoppers
	for (i = 0; i < 20; i++) {
		r = rand() % 10000;
		row = r / 100;
		col = r % 100;
		dir = rand() % 4;
		game.addCreature(Creature(&hopper, dir), row, col);
	}

	// place rovers
	for (i = 0; i < 20; i++) {
		r = rand() % 10000;
		row = r / 100;
		col = r % 100;
		dir = rand() % 4;
		game.addCreature(Creature(&rover, dir), row, col);
	}

	// place traps
	for (i = 0; i < 20; i++) {
		r = rand() % 10000;
		row = r / 100;
		col = r % 100;
		dir = rand() % 4;
		game.addCreature(Creature(&trap, dir), row, col);
	}

	// do the sim
	game.print(cout);

	for (i = 1; i <= 100; i++){
		game.play();

		//print sometimes
		if (i % 10 == 0)
			game.print(cout);
	}


  }
	catch (const invalid_argument&) {
	  assert(false);}
	catch (const out_of_range&) {
  		assert(false);}

  // ------------
  // darwin 32x32
  // ------------

  try {
    cout << "*** Darwin 32x32 ***" << endl;
    srand(0);
    /*
		Randomly place 50 traps
		then place a bunch of hoppers.
		Simulate 100 moves.
		Print every 10.
		*/

		Darwin game(32, 32);
		int r;
		int row, col;
		int dir;
		int i;

		// place traps
		for (i = 0; i < 50; i++) {
			r = rand() % (32*32);
			row = r / 32;
			col = r % 32;
			dir = rand() % 4;
			game.addCreature(Creature(&trap, dir), row, col);
		}

		// place hoppers
		for (i = 0; i < 50; i++) {
			r = rand() % (32*32);
			row = r / 100;
			col = r % 100;
			dir = rand() % 4;
			game.addCreature(Creature(&hopper, dir), row, col);
		}

		// do the sim
		game.print(cout);

		for (i = 1; i <= 100; i++){
			game.play();

			//print sometimes
			if (i % 10 == 0)
				game.print(cout);
		}


  }
	catch (const invalid_argument&) {
	  assert(false);}
	catch (const out_of_range&) {
  		assert(false);}

  // ------------
  // darwin 2x2
  // ------------

  try {
    cout << "*** Darwin 2x2 ***" << endl;
    srand(0);
    /*
		try to place 1000 creatures
		there should only be 4 in the end
		print the result
		*/

		Darwin game(2, 2);
		int r;
		int row, col;
		int dir;
		int i;

		// place traps
		for (i = 0; i < 1000; i++) {
			r = rand() % 4;
			row = r / 2;
			col = r % 2;
			dir = rand() % 4;
			game.addCreature(Creature(&trap, dir), row, col);
		}

		// print the sim
		game.print(cout);

  }
	catch (const invalid_argument&) {
	  assert(false);}
	catch (const out_of_range&) {
  		assert(false);}


// ------------
// darwin 1x50
// ------------

try {
cout << "*** Darwin 1x50 ***" << endl;
srand(0);
/*
	place 5 rovers and 5 hoppers in a line
	sim 20 times
	print every 5
	*/

	Darwin game(1, 50);

	int i;
	// place rovers
	for (i = 0; i < 5; i++) {
		game.addCreature(Creature(&rover, D_EAST), 0, 10* i);
	}

	// place hoppers
	for (i = 0; i < 5; i++) {
		game.addCreature(Creature(&hopper, D_SOUTH), 0, 10* i + 5);
	}

	// do the sim
	game.print(cout);

	for (i = 1; i <= 20; i++) {
		game.play();

		if (i % 5 == 0) game.print(cout);
	}
}
catch (const invalid_argument&) {
  assert(false);}
catch (const out_of_range&) {
		assert(false);}


// ------------
// darwin 1x10
// ------------

try {
cout << "*** Darwin 1x10 ***" << endl;
srand(0);
/*
	place a trap on the left and a line of hoppers to the right
	sim 1 turn
	everything should be a trap
	*/

	Darwin game(1, 10);

	game.addCreature(Creature(&trap, D_EAST), 0, 0);
	game.addCreature(Creature(&hopper, D_EAST), 0, 1);
	game.addCreature(Creature(&hopper, D_EAST), 0, 2);
	game.addCreature(Creature(&hopper, D_EAST), 0, 3);
	game.addCreature(Creature(&hopper, D_EAST), 0, 4);
	game.addCreature(Creature(&hopper, D_EAST), 0, 5);
	game.addCreature(Creature(&hopper, D_EAST), 0, 6);
	game.addCreature(Creature(&hopper, D_EAST), 0, 7);
	game.addCreature(Creature(&hopper, D_EAST), 0, 8);
	game.addCreature(Creature(&hopper, D_EAST), 0, 9);

	// do the sim
	game.print(cout);
	game.play();
	game.print(cout);
}
catch (const invalid_argument&) {
  assert(false);}
catch (const out_of_range&) {
		assert(false);}

// ------------
// darwin 1x10
// ------------

try {
cout << "*** Darwin 1x10 ***" << endl;
srand(0);
/*
	2 hoppers sit in the middle unable to move for all of time
	print the intial and after 10th turn
	*/

	Darwin game(1, 10);

	game.addCreature(Creature(&hopper, D_EAST), 0, 4);
	game.addCreature(Creature(&hopper, D_WEST), 0, 5);

	// do the sim
	game.print(cout);
	for (int i = 0; i < 10; i++) game.play();
	game.print(cout);
}
catch (const invalid_argument&) {
  assert(false);}
catch (const out_of_range&) {
		assert(false);}



	return 0;
}