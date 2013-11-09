// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
 * David Woo
 * daw2399
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

int main () 
{
    using namespace std;

    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
    */
	Species food = Species("food");
	food.addInstruction("left");
	food.addInstruction("go 0");

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

	// ----
	// best
	// ----
	/*
	Camps in a corner and waits for other species to come to it.

	 0: if_enemy 12
	 1: if_empty 14
	 2: right
	 3: if_enemy 16
	 4: if_empty 18
	 5: right
	 6: if_enemy 20
	 7: right
	 8: if_enemy 22
	 9: left
	10: if_enemy 24
	11: go 7
	12: infect
	13: go 0
	14: hop
	15: go 1
	16: infect
	17: go 3
	18: hop
	19: go 4
	20: infect
	21: go 6
	22: infect
	23: go 8
	24: infect
	25: go 10
	*/
	Species best = Species("best");
	best.addInstruction("if_enemy 12");
	best.addInstruction("if_empty 14");
	best.addInstruction("right");
	best.addInstruction("if_enemy 16");
	best.addInstruction("if_empty 18");
	best.addInstruction("right");
	best.addInstruction("if_enemy 20");
	best.addInstruction("right");
	best.addInstruction("if_enemy 22");
	best.addInstruction("left");
	best.addInstruction("if_enemy 24");
	best.addInstruction("go 7");
	best.addInstruction("infect");
	best.addInstruction("go 0");
	best.addInstruction("hop");
	best.addInstruction("go 1");
	best.addInstruction("infect");
	best.addInstruction("go 3");
	best.addInstruction("hop");
	best.addInstruction("go 4");
	best.addInstruction("infect");
	best.addInstruction("go 6");
	best.addInstruction("infect");
	best.addInstruction("go 8");
	best.addInstruction("infect");
	best.addInstruction("go 10");

    // ----------
    // darwin 8x8
    // ----------

    try 
	{
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
		Darwin d = Darwin(8, 8);

		Creature f1 = (&food);
		Creature f2 = (&food);
		Creature h1 = (&hopper);
		Creature h2 = (&hopper);
		Creature h3 = (&hopper);
		Creature h4 = (&hopper);

		d.addCreature(&f1);
		d.addCreature(&h1);
		d.addCreature(&h2);
		d.addCreature(&h3);
		d.addCreature(&h4);
		d.addCreature(&f2);

		int i;
		i = d.spawnCreature("food", 0, 0, EAST);
		assert(i == 1);
		i = d.spawnCreature("hopper", 3, 3, NORTH);
		assert(i == 1);
		i = d.spawnCreature("hopper", 3, 4, EAST);
		assert(i == 1);
		i = d.spawnCreature("hopper", 4, 4, SOUTH);
		assert(i == 1);
		i = d.spawnCreature("hopper", 4, 3, WEST);
		assert(i == 1);
		i = d.spawnCreature("food", 7, 7, NORTH);
		assert(i == 1);
		
		for(int k = 0; k < 6; ++k)
			d.step();
    }
    catch (const invalid_argument&) 
	{
        assert(false);
	}
    catch (const out_of_range&) 
	{
        assert(false);
	}

    // ----------
    // darwin 7x9
    // ----------

    try 
	{
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
		
		Darwin d = Darwin(7, 9);

		Creature t1 = Creature(&trap);
		Creature t2 = Creature(&trap);
		Creature h = Creature(&hopper);
		Creature r = Creature(&rover);
		
		d.addCreature(&t1);
		d.addCreature(&h);
		d.addCreature(&r);
		d.addCreature(&t2);

		int i;
		i = d.spawnCreature("trap", 0, 0, SOUTH);
		assert(i == 1);
		i = d.spawnCreature("hopper", 3, 2, EAST);
		assert(i == 1);
		i = d.spawnCreature("rover", 5, 4, NORTH);
		assert(i == 1);
		i = d.spawnCreature("trap", 6, 8, WEST);
		assert(i == 1);


		for(int k = 0; k < 6; ++k)
		{
			d.step();
		}
    }
    catch (const invalid_argument&) 
	{
        assert(false);
	}
    catch (const out_of_range&) 
	{
        assert(false);
	}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try 
	{
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
		Darwin d = Darwin(72, 72);

		Creature f0 = Creature(&food);
		Creature f1 = Creature(&food);
		Creature f2 = Creature(&food);
		Creature f3 = Creature(&food);
		Creature f4 = Creature(&food);
		Creature f5 = Creature(&food);
		Creature f6 = Creature(&food);
		Creature f7 = Creature(&food);
		Creature f8 = Creature(&food);
		Creature f9 = Creature(&food);

		Creature h0 = Creature(&hopper);
		Creature h1 = Creature(&hopper);
		Creature h2 = Creature(&hopper);
		Creature h3 = Creature(&hopper);
		Creature h4 = Creature(&hopper);
		Creature h5 = Creature(&hopper);
		Creature h6 = Creature(&hopper);
		Creature h7 = Creature(&hopper);
		Creature h8 = Creature(&hopper);
		Creature h9 = Creature(&hopper);

		Creature r0 = Creature(&rover);
		Creature r1 = Creature(&rover);
		Creature r2 = Creature(&rover);
		Creature r3 = Creature(&rover);
		Creature r4 = Creature(&rover);
		Creature r5 = Creature(&rover);
		Creature r6 = Creature(&rover);
		Creature r7 = Creature(&rover);
		Creature r8 = Creature(&rover);
		Creature r9 = Creature(&rover);

		Creature t0 = Creature(&trap);
		Creature t1 = Creature(&trap);
		Creature t2 = Creature(&trap);
		Creature t3 = Creature(&trap);
		Creature t4 = Creature(&trap);
		Creature t5 = Creature(&trap);
		Creature t6 = Creature(&trap);
		Creature t7 = Creature(&trap);
		Creature t8 = Creature(&trap);
		Creature t9 = Creature(&trap);

		d.addCreature(&f0);
		d.addCreature(&f1);
		d.addCreature(&f2);
		d.addCreature(&f3);
		d.addCreature(&f4);
		d.addCreature(&f5);
		d.addCreature(&f6);
		d.addCreature(&f7);
		d.addCreature(&f8);
		d.addCreature(&f9);

		d.addCreature(&h0);
		d.addCreature(&h1);
		d.addCreature(&h2);
		d.addCreature(&h3);
		d.addCreature(&h4);
		d.addCreature(&h5);
		d.addCreature(&h6);
		d.addCreature(&h7);
		d.addCreature(&h8);
		d.addCreature(&h9);

		d.addCreature(&r0);
		d.addCreature(&r1);
		d.addCreature(&r2);
		d.addCreature(&r3);
		d.addCreature(&r4);
		d.addCreature(&r5);
		d.addCreature(&r6);
		d.addCreature(&r7);
		d.addCreature(&r8);
		d.addCreature(&r9);

		d.addCreature(&t0);
		d.addCreature(&t1);
		d.addCreature(&t2);
		d.addCreature(&t3);
		d.addCreature(&t4);
		d.addCreature(&t5);
		d.addCreature(&t6);
		d.addCreature(&t7);
		d.addCreature(&t8);
		d.addCreature(&t9);

		for(int a = 0; a < 10; ++a)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("food", y, x, dir);
			}
		}

		for(int b = 0; b < 10; ++b)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("hopper", y, x, dir);
			}
		}

		for(int c = 0; c < 10; ++c)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("rover", y, x, dir);
			}
		}

		for(int e = 0; e < 10; ++e)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("trap", y, x, dir);
			}
		}

		for(int f = 0; f < 1001; ++f)
		{
			d.step();
		}
    }
    catch (const invalid_argument&) 
	{
        assert(false);
	}
    catch (const out_of_range&) 
	{
        assert(false);
	}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try 
	{
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
		Darwin d = Darwin(72, 72);

		Creature f0 = Creature(&food);
		Creature f1 = Creature(&food);
		Creature f2 = Creature(&food);
		Creature f3 = Creature(&food);
		Creature f4 = Creature(&food);
		Creature f5 = Creature(&food);
		Creature f6 = Creature(&food);
		Creature f7 = Creature(&food);
		Creature f8 = Creature(&food);
		Creature f9 = Creature(&food);

		Creature h0 = Creature(&hopper);
		Creature h1 = Creature(&hopper);
		Creature h2 = Creature(&hopper);
		Creature h3 = Creature(&hopper);
		Creature h4 = Creature(&hopper);
		Creature h5 = Creature(&hopper);
		Creature h6 = Creature(&hopper);
		Creature h7 = Creature(&hopper);
		Creature h8 = Creature(&hopper);
		Creature h9 = Creature(&hopper);

		Creature r0 = Creature(&rover);
		Creature r1 = Creature(&rover);
		Creature r2 = Creature(&rover);
		Creature r3 = Creature(&rover);
		Creature r4 = Creature(&rover);
		Creature r5 = Creature(&rover);
		Creature r6 = Creature(&rover);
		Creature r7 = Creature(&rover);
		Creature r8 = Creature(&rover);
		Creature r9 = Creature(&rover);

		Creature t0 = Creature(&trap);
		Creature t1 = Creature(&trap);
		Creature t2 = Creature(&trap);
		Creature t3 = Creature(&trap);
		Creature t4 = Creature(&trap);
		Creature t5 = Creature(&trap);
		Creature t6 = Creature(&trap);
		Creature t7 = Creature(&trap);
		Creature t8 = Creature(&trap);
		Creature t9 = Creature(&trap);

		Creature b0 = Creature(&best);
		Creature b1 = Creature(&best);
		Creature b2 = Creature(&best);
		Creature b3 = Creature(&best);
		Creature b4 = Creature(&best);
		Creature b5 = Creature(&best);
		Creature b6 = Creature(&best);
		Creature b7 = Creature(&best);
		Creature b8 = Creature(&best);
		Creature b9 = Creature(&best);

		d.addCreature(&f0);
		d.addCreature(&f1);
		d.addCreature(&f2);
		d.addCreature(&f3);
		d.addCreature(&f4);
		d.addCreature(&f5);
		d.addCreature(&f6);
		d.addCreature(&f7);
		d.addCreature(&f8);
		d.addCreature(&f9);

		d.addCreature(&h0);
		d.addCreature(&h1);
		d.addCreature(&h2);
		d.addCreature(&h3);
		d.addCreature(&h4);
		d.addCreature(&h5);
		d.addCreature(&h6);
		d.addCreature(&h7);
		d.addCreature(&h8);
		d.addCreature(&h9);

		d.addCreature(&r0);
		d.addCreature(&r1);
		d.addCreature(&r2);
		d.addCreature(&r3);
		d.addCreature(&r4);
		d.addCreature(&r5);
		d.addCreature(&r6);
		d.addCreature(&r7);
		d.addCreature(&r8);
		d.addCreature(&r9);

		d.addCreature(&t0);
		d.addCreature(&t1);
		d.addCreature(&t2);
		d.addCreature(&t3);
		d.addCreature(&t4);
		d.addCreature(&t5);
		d.addCreature(&t6);
		d.addCreature(&t7);
		d.addCreature(&t8);
		d.addCreature(&t9);

		d.addCreature(&b0);
		d.addCreature(&b1);
		d.addCreature(&b2);
		d.addCreature(&b3);
		d.addCreature(&b4);
		d.addCreature(&b5);
		d.addCreature(&b6);
		d.addCreature(&b7);
		d.addCreature(&b8);
		d.addCreature(&b9);

		for(int a = 0; a < 10; ++a)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("food", y, x, dir);
			}
		}

		for(int b = 0; b < 10; ++b)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("hopper", y, x, dir);
			}
		}

		for(int c = 0; c < 10; ++c)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("rover", y, x, dir);
			}
		}

		for(int e = 0; e < 10; ++e)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("trap", y, x, dir);
			}
		}

		for(int g = 0; g < 10; ++g)
		{
			int succ = 0;
			while(succ != 1)
			{
				Direction dir;
				switch(rand() % 4)
				{
					case 0:
						dir = WEST;
						break;
					case 1:
						dir = NORTH;
						break;
					case 2:
						dir = EAST;
						break;
					case 3:
						dir = SOUTH;
						break;
					default:
						dir = NORTH;
						break;
				}
				int y = rand() % 72;
				int x = rand() % 72;
				succ = d.spawnCreature("best", y, x, dir);
			}
		}

		for(int f = 0; f < 1001; ++f)
		{
			d.step();
		}
    }
    catch (const invalid_argument&) 
	{
        assert(false);
	}
    catch (const out_of_range&) 
	{
        assert(false);
	}

    return 0;
}
