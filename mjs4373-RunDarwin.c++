// ----------------------------
// Project by:
//    Mitch Stephan (mjs4373)
//    Daniel Roberston (cdr966)
// cs371p-darwin/RunDarwin.c++
// ----------------------------

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
        World world(8, 8);

        Creature f('f', EAST);
        Creature h('h', NORTH);
        Creature h2('h', EAST);
        Creature h3('h', SOUTH);
        Creature h4('h', WEST);
        Creature f2('f', NORTH);

        world.add_creature(f, 0, 0);
        world.add_creature(h, 3, 3);
        world.add_creature(h2, 3, 4);
        world.add_creature(h3, 4, 4);
        world.add_creature(h4, 4, 3);
        world.add_creature(f2, 7, 7);

        cout << world << endl;
        for (size_t i = 1; i <= 5; ++i)
        {
            world.next_turn();
            cout << world << endl;
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
        World world(7, 9);

        Creature t('t', SOUTH);
        Creature h('h', EAST);
        Creature r('r', NORTH);
        Creature t2('t', WEST);

        world.add_creature(t, 0, 0);
        world.add_creature(h, 3, 2);
        world.add_creature(r, 5, 4);
        world.add_creature(t2, 6, 8);

        cout << world << endl;
        for (size_t i = 1; i <= 5; ++i)
        {
            world.next_turn();
            cout << world << endl;
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
        int position;
        direction_enum direction;

        // note: We have to create a new object for each creature
        // because World is a 2d vector of Creature pointers
        // we did so we would not have to call the constructor
        // of Creature for every element (5184)
        World world(72, 72);
        
        // food
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f('f', direction);
        world.add_creature(f, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f2('f', direction);
        world.add_creature(f2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f3('f', direction);
        world.add_creature(f3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f4('f', direction);
        world.add_creature(f4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f5('f', direction);
        world.add_creature(f5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f6('f', direction);
        world.add_creature(f6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f7('f', direction);
        world.add_creature(f7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f8('f', direction);
        world.add_creature(f8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f9('f', direction);
        world.add_creature(f9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f10('f', direction);
        world.add_creature(f10, position / 72, position % 72);

        // hopper
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h('h', direction);
        world.add_creature(h, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h2('h', direction);
        world.add_creature(h2, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h3('h', direction);
        world.add_creature(h3, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h4('h', direction);
        world.add_creature(h4, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h5('h', direction);
        world.add_creature(h5, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h6('h', direction);
        world.add_creature(h6, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h7('h', direction);
        world.add_creature(h7, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h8('h', direction);
        world.add_creature(h8, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h9('h', direction);
        world.add_creature(h9, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h10('h', direction);
        world.add_creature(h10, position / 72, position % 72);
        
        // rover
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r('r', direction);
        world.add_creature(r, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r2('r', direction);
        world.add_creature(r2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r3('r', direction);
        world.add_creature(r3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r4('r', direction);
        world.add_creature(r4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r5('r', direction);
        world.add_creature(r5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r6('r', direction);
        world.add_creature(r6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r7('r', direction);
        world.add_creature(r7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r8('r', direction);
        world.add_creature(r8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r9('r', direction);
        world.add_creature(r9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r10('r', direction);
        world.add_creature(r10, position / 72, position % 72);

        // trap
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t1('t', direction);
        world.add_creature(t1, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t2('t', direction);
        world.add_creature(t2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t3('t', direction);
        world.add_creature(t3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t4('t', direction);
        world.add_creature(t4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t5('t', direction);
        world.add_creature(t5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t6('t', direction);
        world.add_creature(t6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t7('t', direction);
        world.add_creature(t7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t8('t', direction);
        world.add_creature(t8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t9('t', direction);
        world.add_creature(t9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t10('t', direction);
        world.add_creature(t10, position / 72, position % 72);

        cout << world << endl;
        for (size_t i = 1; i <= 1000; ++i)
        {
            world.next_turn();
            if (i < 10)
            {
                cout << world << endl;   
            }
            if (i % 100 == 0)
            {
                cout << world << endl;
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
        int position;
        direction_enum direction;

        // note: We have to create a new object for each creature
        // because World is a 2d vector of Creature pointers
        // we did so we would not have to call the constructor
        // of Creature for every element (5184)
        World world(72, 72);
        
        // food
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f('f', direction);
        world.add_creature(f, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f2('f', direction);
        world.add_creature(f2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f3('f', direction);
        world.add_creature(f3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f4('f', direction);
        world.add_creature(f4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f5('f', direction);
        world.add_creature(f5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f6('f', direction);
        world.add_creature(f6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f7('f', direction);
        world.add_creature(f7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f8('f', direction);
        world.add_creature(f8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f9('f', direction);
        world.add_creature(f9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f10('f', direction);
        world.add_creature(f10, position / 72, position % 72);

        // hopper
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h('h', direction);
        world.add_creature(h, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h2('h', direction);
        world.add_creature(h2, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h3('h', direction);
        world.add_creature(h3, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h4('h', direction);
        world.add_creature(h4, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h5('h', direction);
        world.add_creature(h5, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h6('h', direction);
        world.add_creature(h6, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h7('h', direction);
        world.add_creature(h7, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h8('h', direction);
        world.add_creature(h8, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h9('h', direction);
        world.add_creature(h9, position / 72, position % 72);
        
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h10('h', direction);
        world.add_creature(h10, position / 72, position % 72);
        
        // rover
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r('r', direction);
        world.add_creature(r, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r2('r', direction);
        world.add_creature(r2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r3('r', direction);
        world.add_creature(r3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r4('r', direction);
        world.add_creature(r4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r5('r', direction);
        world.add_creature(r5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r6('r', direction);
        world.add_creature(r6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r7('r', direction);
        world.add_creature(r7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r8('r', direction);
        world.add_creature(r8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r9('r', direction);
        world.add_creature(r9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r10('r', direction);
        world.add_creature(r10, position / 72, position % 72);

        // trap
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t1('t', direction);
        world.add_creature(t1, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t2('t', direction);
        world.add_creature(t2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t3('t', direction);
        world.add_creature(t3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t4('t', direction);
        world.add_creature(t4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t5('t', direction);
        world.add_creature(t5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t6('t', direction);
        world.add_creature(t6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t7('t', direction);
        world.add_creature(t7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t8('t', direction);
        world.add_creature(t8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t9('t', direction);
        world.add_creature(t9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t10('t', direction);
        world.add_creature(t10, position / 72, position % 72);

        // best
        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b('b', direction);
        world.add_creature(b, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b2('b', direction);
        world.add_creature(b2, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b3('b', direction);
        world.add_creature(b3, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b4('b', direction);
        world.add_creature(b4, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b5('b', direction);
        world.add_creature(b5, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b6('b', direction);
        world.add_creature(b6, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b7('b', direction);
        world.add_creature(b7, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b8('b', direction);
        world.add_creature(b8, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b9('b', direction);
        world.add_creature(b9, position / 72, position % 72);

        position = rand() % 5184;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature b10('b', direction);
        world.add_creature(b10, position / 72, position % 72);

        cout << world << endl;
        for (size_t i = 1; i <= 1000; ++i)
        {
            world.next_turn();
            if (i < 10)
            {
                cout << world << endl; 
            }
            if (i % 100 == 0)
            {
                cout << world << endl;
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

    // ------------------------------
    // start our own Acceptance Tests
    // ------------------------------

    // ----------------------
    // darwin 6x6 trap island
    // ----------------------
    try 
    {
        cout << "*** Darwin 6x6 trap island ***" << endl;
        World world(6, 6);

        Creature h1('h', SOUTH);
        Creature h2('h', SOUTH);
        Creature h3('h', SOUTH);
        Creature h4('h', SOUTH);
        Creature h5('h', SOUTH);
        Creature t1('t', NORTH);

        world.add_creature(h1, 1, 3);
        world.add_creature(h2, 2, 3);
        world.add_creature(h3, 2, 4);
        world.add_creature(h4, 3, 4);
        world.add_creature(h5, 4, 5);
        world.add_creature(t1, 5, 5);

        cout << world << endl;
        for (size_t i = 1; i <= 10; ++i)
        {
            world.next_turn();
            if (i < 3)
            {
                cout << world << endl;
            }
            if (i % 5 == 0)
            {
                cout << world << endl;
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
    
    // ------------------------
    // darwin 3x3 best vs rover
    // ------------------------
    try 
    {
        srand(0);
        cout << "*** Darwin 3x3 best vs rover ***" << endl;
        World world(3, 3);

        Creature b1('b', SOUTH);
        Creature b2('b', SOUTH);
        Creature b3('b', SOUTH);
        Creature r1('r', NORTH);
        Creature r2('r', NORTH);
        Creature r3('r', NORTH);

        world.add_creature(b1, 0, 0);
        world.add_creature(b2, 1, 0);
        world.add_creature(b3, 0, 1);
        world.add_creature(r1, 2, 2);
        world.add_creature(r2, 2, 1);
        world.add_creature(r3, 1, 2);

        cout << world << endl;
        for (size_t i = 1; i <= 15; ++i)
        {
            world.next_turn();
            if (i < 3)
            {
                cout << world << endl;
            }
            if (i % 5 == 0)
            {
                cout << world << endl;
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

    // -------------------------
    // darwin 50x50 without Best
    // -------------------------
    try 
    {
        cout << "*** Darwin 50x50 without Best ***" << endl;
        srand(0);
        int position;
        direction_enum direction;

        // note: We have to create a new object for each creature
        // because World is a 2d vector of Creature pointers
        // we did so we would not have to call the constructor
        // of Creature for every element (5184)
        World world(50, 50);
        
        // food
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f('f', direction);
        world.add_creature(f, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f2('f', direction);
        world.add_creature(f2, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f3('f', direction);
        world.add_creature(f3, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f4('f', direction);
        world.add_creature(f4, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f5('f', direction);
        world.add_creature(f5, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f6('f', direction);
        world.add_creature(f6, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f7('f', direction);
        world.add_creature(f7, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f8('f', direction);
        world.add_creature(f8, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f9('f', direction);
        world.add_creature(f9, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature f10('f', direction);
        world.add_creature(f10, position / 50, position % 50);

        // hopper
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h('h', direction);
        world.add_creature(h, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h2('h', direction);
        world.add_creature(h2, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h3('h', direction);
        world.add_creature(h3, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h4('h', direction);
        world.add_creature(h4, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h5('h', direction);
        world.add_creature(h5, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h6('h', direction);
        world.add_creature(h6, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h7('h', direction);
        world.add_creature(h7, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h8('h', direction);
        world.add_creature(h8, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h9('h', direction);
        world.add_creature(h9, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h10('h', direction);
        world.add_creature(h10, position / 50, position % 50);
        
        // rover
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r('r', direction);
        world.add_creature(r, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r2('r', direction);
        world.add_creature(r2, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r3('r', direction);
        world.add_creature(r3, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r4('r', direction);
        world.add_creature(r4, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r5('r', direction);
        world.add_creature(r5, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r6('r', direction);
        world.add_creature(r6, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r7('r', direction);
        world.add_creature(r7, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r8('r', direction);
        world.add_creature(r8, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r9('r', direction);
        world.add_creature(r9, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r10('r', direction);
        world.add_creature(r10, position / 50, position % 50);

        // trap
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t1('t', direction);
        world.add_creature(t1, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t2('t', direction);
        world.add_creature(t2, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t3('t', direction);
        world.add_creature(t3, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t4('t', direction);
        world.add_creature(t4, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t5('t', direction);
        world.add_creature(t5, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t6('t', direction);
        world.add_creature(t6, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t7('t', direction);
        world.add_creature(t7, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t8('t', direction);
        world.add_creature(t8, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t9('t', direction);
        world.add_creature(t9, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t10('t', direction);
        world.add_creature(t10, position / 50, position % 50);

        cout << world << endl;
        for (size_t i = 1; i <= 500; ++i)
        {
            world.next_turn();
            if (i < 4)
            {
                cout << world << endl;   
            }
            if (i % 100 == 0)
            {
                cout << world << endl;
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

    // ----------------------------
    // darwin 50x50 with 15h 15t 3r
    // ----------------------------
    try 
    {
        cout << "*** Darwin 50x50 with 15h 15t 3r ***" << endl;
        srand(0);
        int position;
        direction_enum direction;

        // note: We have to create a new object for each creature
        // because World is a 2d vector of Creature pointers
        // we did so we would not have to call the constructor
        // of Creature for every element (5184)
        World world(50, 50);
        
        // hopper
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h1('h', direction);
        world.add_creature(h1, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h2('h', direction);
        world.add_creature(h2, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h3('h', direction);
        world.add_creature(h3, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h4('h', direction);
        world.add_creature(h4, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h5('h', direction);
        world.add_creature(h5, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h6('h', direction);
        world.add_creature(h6, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h7('h', direction);
        world.add_creature(h7, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h8('h', direction);
        world.add_creature(h8, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h9('h', direction);
        world.add_creature(h9, position / 50, position % 50);
        
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h10('h', direction);
        world.add_creature(h10, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h11('h', direction);
        world.add_creature(h11, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h12('h', direction);
        world.add_creature(h12, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h13('h', direction);
        world.add_creature(h13, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h14('h', direction);
        world.add_creature(h14, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature h15('h', direction);
        world.add_creature(h15, position / 50, position % 50);
        
        // rover
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r1('r', direction);
        world.add_creature(r1, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r2('r', direction);
        world.add_creature(r2, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature r3('r', direction);
        world.add_creature(r3, position / 50, position % 50);

        // trap
        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t1('t', direction);
        world.add_creature(t1, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t2('t', direction);
        world.add_creature(t2, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t3('t', direction);
        world.add_creature(t3, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t4('t', direction);
        world.add_creature(t4, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t5('t', direction);
        world.add_creature(t5, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t6('t', direction);
        world.add_creature(t6, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t7('t', direction);
        world.add_creature(t7, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t8('t', direction);
        world.add_creature(t8, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t9('t', direction);
        world.add_creature(t9, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t10('t', direction);
        world.add_creature(t10, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t11('t', direction);
        world.add_creature(t11, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t12('t', direction);
        world.add_creature(t12, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t13('t', direction);
        world.add_creature(t13, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t14('t', direction);
        world.add_creature(t14, position / 50, position % 50);

        position = rand() % 2500;
        direction = static_cast<direction_enum>(rand() % 4);
        Creature t15('t', direction);
        world.add_creature(t15, position / 50, position % 50);

        cout << world << endl;
        for (size_t i = 1; i <= 500; ++i)
        {
            world.next_turn();
            if (i < 4)
            {
                cout << world << endl;   
            }
            if (i % 100 == 0)
            {
                cout << world << endl;
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

    // ----------------------------
    // end our own Acceptance Tests
    // ----------------------------

    return 0;
}