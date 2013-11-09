//----------------------------
// Jacob Kovar
// jrk2593
// CS371P 10 am - 11 am
// Professor Glenn Downing
// Project 4 - Darwin's World
// 11-07-13
//----------------------------

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
#include <iostream>  // cout
#include <vector>    // vector
#include <cstdlib>   // rand, srand
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

    Species food("food");
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper("hopper");
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
     

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

    Species trap("trap");
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    // ----
    // best
    // ----

    /*
     0: 
     1: 
     2: 
     3: 
     4: 
    */

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

        Darwin g(8,8);
        g.loadCreature(Creature(&food, EAST));
        g.loadCreature(Creature(&hopper, NORTH));
        g.loadCreature(Creature(&hopper, EAST));
        g.loadCreature(Creature(&hopper, SOUTH));
        g.loadCreature(Creature(&hopper, WEST));
        g.loadCreature(Creature(&food, NORTH));
    
        g.addToGrid(0, 0, 0);
        g.addToGrid(1, 3, 3);
        g.addToGrid(2, 3, 4);
        g.addToGrid(3, 4, 4);
        g.addToGrid(4, 4, 3);
        g.addToGrid(5, 7, 7);
        
        for(int i = 0; i <= 5; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
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
        
        Darwin g(7,9);
        g.loadCreature(Creature(&trap, SOUTH));
        g.loadCreature(Creature(&hopper, EAST));
        g.loadCreature(Creature(&rover, NORTH));
        g.loadCreature(Creature(&trap, WEST));
        
        g.addToGrid(0, 0, 0);
        g.addToGrid(1, 3, 2);
        g.addToGrid(2, 5, 4);
        g.addToGrid(3, 6, 8);
        
        for(int i = 0; i <= 5; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
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
    }
    catch (const invalid_argument&)
    {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }

    try
    {
        cout << "*** Darwin 1x15 ***" << endl;

        Darwin g(1,15);
        g.loadCreature(Creature(&hopper, EAST));
        g.addToGrid(0,0,0);

        for(int i = 0; i <= 15; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
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

    try
    {
        cout << "*** Darwin 3x3 ***" << endl;

        Darwin g(3,3);
        g.loadCreature(Creature(&trap, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));

        g.addToGrid(0,1,1);
        g.addToGrid(1,0,0);
        g.addToGrid(2,0,1);
        g.addToGrid(3,0,2);
        g.addToGrid(4,1,0);
        g.addToGrid(5,1,2);
        g.addToGrid(6,2,0);
        g.addToGrid(7,2,1);
        g.addToGrid(8,2,2);
        

        for(int i = 0; i <= 6; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
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

    try
    {
        cout << "*** Darwin 11x11 ***" << endl;

        Darwin g(11,11);
        g.loadCreature(Creature(&rover, EAST));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));
        g.loadCreature(Creature(&food, NORTH));

        g.addToGrid(0,0,0);
        g.addToGrid(1,10,10);
        g.addToGrid(2,5,5);
        g.addToGrid(3,0,10);
        g.addToGrid(4,10,0);
        

        for(int i = 0; i <= 10; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
        }

        for(int i = 10; i <= 1000; i++)
        {
            if(i%100 == 0)
            {
                cout << "Turn = " << i << "." << endl;
                g.printGrid();
                g.nextTurn();
                cout << endl;
            }
            else
            {
                g.nextTurn();
            }
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

    try
    {
        cout << "*** Darwin 5x5 ***" << endl;

        Darwin g(5,5);
        
        g.loadCreature(Creature(&rover,NORTH));

        for(int i = 0; i < 3; i++)
        {
            g.loadCreature(Creature(&food, NORTH));
        }

        for(int i = 0; i < 3; i++)
        {
            g.loadCreature(Creature(&trap, NORTH));
        }

        g.addToGrid(0, 0,0);
        g.addToGrid(1, 2,2);
        g.addToGrid(2, 0,4);
        g.addToGrid(3, 4,0);
        g.addToGrid(4, 4,4);
        g.addToGrid(5, 1,1);
        g.addToGrid(6, 3,3);
        

        for(int i = 0; i <= 10; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
        }

        for(int i = 11; i <= 100; i++)
        {
            if(i%10 == 0)
            {
                cout << "Turn = " << i << "." << endl;
                g.printGrid();
                g.nextTurn();
                cout << endl;
            }
            else
            {
                g.nextTurn();
            }
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

    try
    {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);
        Darwin g(50,50);
        
        Direction d[] = {WEST, NORTH, EAST, SOUTH};

        g.loadCreature(Creature(&trap,EAST));

        for(int i = 0; i < 2499; i++)
        {
            g.loadCreature(Creature(&food, d[rand()%4]));
        }

        int x = 0;
        for(int r = 0; r < 50; r++)
        {
            for(int c = 0; c < 50; c++)
            {
                g.addToGrid(x++, r, c);
            }
        }
        

        for(int i = 0; i <= 10; i++)
        {
            cout << "Turn = " << i << "." << endl;
            g.printGrid();
            g.nextTurn();
            cout << endl;
        }

        for(int i = 11; i <= 100; i++)
        {
            if(i%10 == 0)
            {
                cout << "Turn = " << i << "." << endl;
                g.printGrid();
                g.nextTurn();
                cout << endl;
            }
            else
            {
                g.nextTurn();
            }
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