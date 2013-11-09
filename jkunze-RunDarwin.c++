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



// ----------
// random_dir
// ----------

Direction random_dir() {
    int rn = rand()%4;
    if (rn == 0)
        return WEST;
    if (rn == 1)
        return NORTH;
    if (rn == 2)
        return EAST;
    return SOUTH;
}

// -----
// our_tests()
// -----

void our_tests()
{
    //Note- our tests randomly generate X, and then Y.
    //If you are using a row/column system, you may have to generate column and then row.
    using namespace std;

    // ----
    // food
    // ----
    Brain food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    // ------
    // hopper
    // ------
    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    // -----
    // rover
    // -----
    Brain rover('r');
    rover.addInstruction(IF_ENEMY,9);
    rover.addInstruction(IF_EMPTY,7);
    rover.addInstruction(IF_RANDOM,5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO,0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO,0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO,0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO,0);

    // ----
    // trap
    // ----
    Brain trap('t');
    trap.addInstruction(IF_ENEMY,3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO,0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO,0);

    // --------
    // wanderer
    // --------
    Brain wanderer('w');
    wanderer.addInstruction(IF_ENEMY,9);
    wanderer.addInstruction(IF_RANDOM,7);
    wanderer.addInstruction(IF_RANDOM,5);
    wanderer.addInstruction(RIGHT);
    wanderer.addInstruction(GO,0);
    wanderer.addInstruction(LEFT);
    wanderer.addInstruction(GO,0);
    wanderer.addInstruction(HOP);
    wanderer.addInstruction(GO,0);
    wanderer.addInstruction(INFECT);
    wanderer.addInstruction(GO,0);

    // -------
    // bouncer
    // -------
    Brain bouncer('b');
    bouncer.addInstruction(IF_ENEMY,7);
    bouncer.addInstruction(IF_EMPTY,5);
    bouncer.addInstruction(LEFT);
    bouncer.addInstruction(LEFT);
    bouncer.addInstruction(GO,0);
    bouncer.addInstruction(HOP);
    bouncer.addInstruction(GO,0);
    bouncer.addInstruction(INFECT);
    bouncer.addInstruction(GO,0);

    // -----
    // chaos
    // -----
    Brain chaos('c');
    chaos.addInstruction(IF_RANDOM,6);
    chaos.addInstruction(IF_RANDOM,4);
    chaos.addInstruction(HOP);
    chaos.addInstruction(GO,0);
    chaos.addInstruction(INFECT);
    chaos.addInstruction(GO,0);
    chaos.addInstruction(IF_RANDOM,9);
    chaos.addInstruction(LEFT);
    chaos.addInstruction(GO,0);
    chaos.addInstruction(RIGHT);
    chaos.addInstruction(GO,0);
    
    try
    {
        cout << "*** Darwin 18x18 ***" << endl;
        World w(18, 18);
        srand(0);

        for(int i = 0; i < 25; i++)
        {
            int x = rand()%18;
            int y = rand()%18;
            w.addCreature(&trap, x, y, random_dir());
        }
        for(int i = 0; i < 15; i++)
        {
            int x = rand()%18;
            int y = rand()%18;
            w.addCreature(&rover, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 25x25 ***" << endl;
        World w(25, 25);
        srand(0);

        for(int i = 0; i < 40; i++)
        {
            int x = rand()%25;
            int y = rand()%25;
            w.addCreature(&wanderer, x, y, random_dir());
        }
        for(int i = 0; i < 40; i++)
        {
            int x = rand()%25;
            int y = rand()%25;
            w.addCreature(&rover, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 30x30 ***" << endl;
        World w(30, 30);
        srand(0);

        for(int i = 0; i < 10; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&trap, x, y, random_dir());
        }
        for(int i = 0; i < 40; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&bouncer, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 30x30 ***" << endl;
        World w(30, 30);
        srand(0);

        for(int i = 0; i < 10; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&trap, x, y, random_dir());
        }
        for(int i = 0; i < 40; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&bouncer, x, y, random_dir());
        }
        for(int i = 0; i < 5; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&wanderer, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 30x30 ***" << endl;
        World w(30, 30);
        srand(0);

        for(int i = 0; i < 10; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&trap, x, y, random_dir());
        }
        for(int i = 0; i < 40; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&bouncer, x, y, random_dir());
        }
        for(int i = 0; i < 25; i++)
        {
            int x = rand()%30;
            int y = rand()%30;
            w.addCreature(&wanderer, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    try
    {
        cout << "*** Darwin 20x20 ***" << endl;
        World w(20, 20);
        srand(0);

        for(int i = 0; i < 40; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&food, x, y, random_dir());
        }
        for(int i = 0; i < 20; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&chaos, x, y, random_dir());
        }
        for(int i = 0; i < 1; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&wanderer, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    try
    {
        cout << "*** Darwin 20x20 ***" << endl;
        World w(20, 20);
        srand(0);

        for(int i = 0; i < 10; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&food, x, y, random_dir());
        }
        for(int i = 0; i < 40; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&chaos, x, y, random_dir());
        }

        for(int i = 0; i < 10; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 20x20 ***" << endl;
        World w(20, 20);
        srand(0);

        for(int i = 0; i < 2; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&rover, x, y, random_dir());
        }
        for(int i = 0; i < 50; i++)
        {
            int x = rand()%20;
            int y = rand()%20;
            w.addCreature(&chaos, x, y, random_dir());
        }

        for(int i = 0; i < 7; i++)
        {
            w.print(std::cout);
            w.takeTurns(20);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    try
    {
        cout << "*** Darwin 5x5 ***" << endl;
        World w(5, 5);
        srand(0);
        
        w.addCreature(&wanderer, 0, 0, SOUTH);
        w.addCreature(&chaos, 4, 4, NORTH);

        for(int i = 0; i < 50; i++)
        {
            w.print(std::cout);
            w.takeTurns(1);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
}

// ----
// main
// ----

int main () {

    our_tests();
    //downings_tests();
    return 0;
}
