// --------------------------------------------
// University of Texas - Austin
// CS371p: Object-Oriented Programming
// PROJECT 4: Darwin
// Ian A. Hays - IH2974
// --------------------------------------------

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

// ------------------------
// #includes
// ------------------------
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"  // Darwin runtime class

// ------------------------
// intToFacing
// ------------------------
Facing intToFacing(int num)
{
	if (num == 0) return WEST;
	else if (num == 1) return NORTH;
	else if (num == 2) return EAST;
	else return SOUTH;
}

// ------------------------
// main
// ------------------------
int main () {
    using namespace std;

	// ------------------------
	// food
	// ------------------------
    /*
     0: left
     1: go 0
    */
    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

	// ------------------------
	// hopper
	// ------------------------
    /*
     0: hop
     1: go 0
    */
    Species hopper("hopper");
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
     

	// ------------------------
	// rover
	// ------------------------
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
    Species rover("rover");
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

	// ------------------------
	// trap
	// ------------------------
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
    Species trap("trap");
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

	// ------------------------
	// darwin 1x1
	// ------------------------
    try 
	{
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        /*
        1x1 Darwin
        Hopper, facing SOUTH,  at (0, 0)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin d1x1(1,1);
		
        Creature trap1(&trap, SOUTH);
		d1x1.addCreature(trap1, 0, 0);
	
		for (int i = 0; i <= 5; i++)
		{
			if (i > 0) d1x1.nextTurn();
			cout << "Turn = " << i << ".\n";
			d1x1.printGrid(cout);
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
		
	// ------------------------
	// darwin 4x4
	// ------------------------		
    try 
	{
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);
        /*
        4x4 Darwin
        Trap,   facing south, at (1, 1)
        Trap,   facing north, at (2, 2)
        Trap,   facing east, at (1, 2)
        Trap,   facing north, at (2, 1)
        Simulate 5 moves.
        Print every grid.
        */
		Darwin d4x4(4,4);
		
        Creature trap1(&trap, SOUTH);
		d4x4.addCreature(trap1, 1, 1);
        Creature trap2(&trap, NORTH);
        d4x4.addCreature(trap2, 2, 2);
		Creature trap3(&trap, EAST);
        d4x4.addCreature(trap3, 1, 2);
		Creature trap4(&trap, NORTH);
		d4x4.addCreature(trap4, 2, 1);
	
		for (int i = 0; i <= 5; i++)
		{
			if (i > 0) d4x4.nextTurn();
			cout << "Turn = " << i << ".\n";
			d4x4.printGrid(cout);
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
		
	// ------------------------
	// darwin 11x11
	// ------------------------		
    try 
	{
        cout << "*** Darwin 11x11 ***" << endl;
        srand(0);
        /*
        11x11 Darwin
        Trap,   facing south, at (1, 1)
        Trap,   facing north, at (2, 2)
        Trap,   facing east, at (1, 2)
        Trap,   facing north, at (2, 1)
		Rover,	facing east, at (0,0)
		Rover, 	facing west, at (0, 10)
        Simulate 20 moves.
        Print every grid.
        */
		Darwin d11x11(11,11);
		
        Creature trap1(&trap, SOUTH);
		d11x11.addCreature(trap1, 1, 1);
        Creature trap2(&trap, NORTH);
        d11x11.addCreature(trap2, 2, 2);
		Creature trap3(&trap, EAST);
        d11x11.addCreature(trap3, 1, 2);
		Creature trap4(&trap, NORTH);
		d11x11.addCreature(trap4, 2, 1);
		Creature rover1(&rover, EAST);
        d11x11.addCreature(rover1, 0, 0);
		Creature rover2(&rover, WEST);
		d11x11.addCreature(rover2, 0, 10);
	
		for (int i = 0; i <= 20; i++)
		{
			if (i > 0) d11x11.nextTurn();
			cout << "Turn = " << i << ".\n";
			d11x11.printGrid(cout);
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
		
	// ------------------------
	// darwin 9x9
	// ------------------------		
    try 
	{
        cout << "*** Darwin 9x9 ***" << endl;
        srand(0);
        /*
        9x9 Darwin
        Rover,   facing south, at (0, 0)
        Hopper,   facing north, at (8, 0)
        Rover,   facing north, at (8, 8)
        Hopper,   facing south, at (0, 8)
        Simulate 10 moves.
        Print every grid.
        */
		Darwin d9x9(9,9);
		
		Creature rover1(&rover, SOUTH);
        d9x9.addCreature(rover1, 0, 0);
		Creature rover2(&rover, NORTH);
		d9x9.addCreature(rover2, 8, 8);
		
		Creature hopper1(&hopper, SOUTH);
        d9x9.addCreature(hopper1, 0, 8);
		Creature hopper2(&hopper, NORTH);
		d9x9.addCreature(hopper2, 8, 0);

		for (int i = 0; i <= 10; i++)
		{
			if (i > 0) d9x9.nextTurn();
			cout << "Turn = " << i << ".\n";
			d9x9.printGrid(cout);
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
		
	// ------------------------
	// darwin 20x20 - AT THE BAKERY
	// ------------------------		
    try 
	{
        cout << "*** Darwin 20x20 ***" << endl;
        srand(0);
        /*
        20x20 Darwin
        Trap,   facing south, at (0, 0)
        Food, 	facing north, at EVERY OTHER SPACE
        Simulate 10 moves.
        Print every grid.
        */
		Darwin d20x20(20,20);
		
		Creature trap1(&trap, SOUTH);
        d20x20.addCreature(trap1, 0, 0);
		
		Creature food1(&food, NORTH);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i == 0 && j == 0) continue;
				d20x20.addCreature(food1, i, j);
			}
		}
		
		for (int i = 0; i <= 10; i++)
		{
			if (i > 0) d20x20.nextTurn();
			cout << "Turn = " << i << ".\n";
			d20x20.printGrid(cout);
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
}