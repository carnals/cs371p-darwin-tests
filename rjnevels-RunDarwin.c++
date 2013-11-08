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

// the ordering: west, north, east, south.
Direction weirdDirection(int dir) {
    switch (dir) {
        case 0:
            return WEST; 
        case 1:
            return NORTH;
        case 2:
            return EAST;
        case 3:
            return SOUTH;
    }
    assert(false);
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

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper('h');
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

    Species rover('r');
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
    
    Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
    
    // ----
    // best
    // ----
    
    Species best('b');
    best.addInstruction("if_enemy 10");
    best.addInstruction("if_empty 4");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("if_random 7");
    best.addInstruction("if_random 7");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        // 8x8 Darwin
        Darwin world(8, 8);
        
        // Food,   facing east,  at (0, 0)
        Creature c1(&food, EAST);
        world.addCreature(&c1, 0, 0);
        
        // Hopper, facing north, at (3, 3)
        Creature c2(&hopper, NORTH);
        world.addCreature(&c2, 3, 3);
        
        // Hopper, facing east,  at (3, 4)
        Creature c3(&hopper, EAST);
        world.addCreature(&c3, 3, 4);
        
        // Hopper, facing south, at (4, 4)
        Creature c4(&hopper, SOUTH);
        world.addCreature(&c4, 4, 4);
        
        // Hopper, facing west,  at (4, 3)
        Creature c5(&hopper, WEST);
        world.addCreature(&c5, 4, 3);
        
        // Food,   facing north, at (7, 7)
        Creature c6(&food, NORTH);
        world.addCreature(&c6, 7, 7);
        
        // Simulate 5 moves.
        // Print every grid.
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << "Turn = " << i << "." << endl;
            world.step();
            world.printGrid(cout);
            cout << endl;
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
        Darwin world(7, 9);
        
        // Trap,   facing south, at (0, 0)
        Creature c1(&trap, SOUTH);
        world.addCreature(&c1, 0, 0);        

        // Hopper, facing east,  at (3, 2)
        Creature c2(&hopper, EAST);
        world.addCreature(&c2, 3, 2);
        
        // Rover,  facing north, at (5, 4)
        Creature c3(&rover, NORTH);
        world.addCreature(&c3, 5, 4);

        // Trap,   facing west,  at (6, 8)
        Creature c4(&trap, WEST);
        world.addCreature(&c4, 6, 8);        

        // Simulate 5 moves.
        // Print every grid.
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << "Turn = " << i << "." << endl;
            world.step();
            world.printGrid(cout);
            cout << endl;
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
        */
        Darwin world(72, 72);
        
        // 10 Food
        Creature foods[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            foods[i] = Creature(&food, static_cast<Direction>(dir));
            world.addCreature(&foods[i], pos/72, pos%72);
        }
        
        // 10 Hopper
        Creature hoppers[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            hoppers[i] = Creature(&hopper, static_cast<Direction>(dir));
            world.addCreature(&hoppers[i], pos/72, pos%72);
        }
        
        // 10 Rover
        Creature rovers[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            rovers[i] = Creature(&rover, static_cast<Direction>(dir));
            world.addCreature(&rovers[i], pos/72, pos%72);
        }
        
        // 10 Trap
        Creature traps[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            traps[i] = Creature(&trap, static_cast<Direction>(dir));
            world.addCreature(&traps[i], pos/72, pos%72);
        }
        
        // Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        //Print every 100th grid after that (i.e. 100, 200, 300...1000).
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 1000; i++) {
            world.step();
            
            if (i < 10 || i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                world.printGrid(cout);
                cout << endl;
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
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        Best MUST outnumber ALL other species for the bonus pts.
        */
        Darwin world(72, 72);
        
        // 10 Food
        Creature foods[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            foods[i] = Creature(&food, static_cast<Direction>(dir));
            world.addCreature(&foods[i], pos/72, pos%72);
        }
        
        // 10 Hopper
        Creature hoppers[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            hoppers[i] = Creature(&hopper, static_cast<Direction>(dir));
            world.addCreature(&hoppers[i], pos/72, pos%72);
        }
        
        // 10 Rover
        Creature rovers[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            rovers[i] = Creature(&rover, static_cast<Direction>(dir));
            world.addCreature(&rovers[i], pos/72, pos%72);
        }
        
        // 10 Trap
        Creature traps[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            traps[i] = Creature(&trap, static_cast<Direction>(dir));
            world.addCreature(&traps[i], pos/72, pos%72);
        }
        
        // 10 Best
        Creature bests[10];
        for (int i = 0; i < 10; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            bests[i] = Creature(&best, static_cast<Direction>(dir));
            world.addCreature(&bests[i], pos/72, pos%72);
        }
        
        // Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        //Print every 100th grid after that (i.e. 100, 200, 300...1000).
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 1000; i++) {
            world.step();
            
            if (i < 10 || i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                world.printGrid(cout);
                cout << endl;
            }
        }

        world.printStats(cout);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
        
    // ------------
    // darwin 72x72
    // without best
    // only 2 of each type
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
        */
        Darwin world(72, 72);
        
        const int num = 2;
        
        // 2 Food
        Creature foods[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            foods[i] = Creature(&food, static_cast<Direction>(dir));
            world.addCreature(&foods[i], pos/72, pos%72);
        }
        
        // 2 Hopper
        Creature hoppers[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            hoppers[i] = Creature(&hopper, static_cast<Direction>(dir));
            world.addCreature(&hoppers[i], pos/72, pos%72);
        }
        
        // 2 Rover
        Creature rovers[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            rovers[i] = Creature(&rover, static_cast<Direction>(dir));
            world.addCreature(&rovers[i], pos/72, pos%72);
        }
        
        // 2 Trap
        Creature traps[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%5184;
            int dir = weirdDirection(rand()%4);
            traps[i] = Creature(&trap, static_cast<Direction>(dir));
            world.addCreature(&traps[i], pos/72, pos%72);
        }
        
        // Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        //Print every 100th grid after that (i.e. 100, 200, 300...1000).
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 1000; i++) {
            world.step();
            
            if (i < 10 || i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                world.printGrid(cout);
                cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // darwin 72x72
    // without best
    // only 2 of each type
    // ------------

    try {
        cout << "*** Darwin 20x20 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        */
        Darwin world(20, 20);
        
        const int num = 2;
        
        // 2 Food
        Creature foods[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%400;
            int dir = weirdDirection(rand()%4);
            foods[i] = Creature(&food, static_cast<Direction>(dir));
            world.addCreature(&foods[i], pos/72, pos%72);
        }
        
        // 2 Hopper
        Creature hoppers[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%400;
            int dir = weirdDirection(rand()%4);
            hoppers[i] = Creature(&hopper, static_cast<Direction>(dir));
            world.addCreature(&hoppers[i], pos/72, pos%72);
        }
        
        // 2 Rover
        Creature rovers[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%400;
            int dir = weirdDirection(rand()%4);
            rovers[i] = Creature(&rover, static_cast<Direction>(dir));
            world.addCreature(&rovers[i], pos/72, pos%72);
        }
        
        // 2 Trap
        Creature traps[num];
        for (int i = 0; i < num; i++) {
            int pos = rand()%400;
            int dir = weirdDirection(rand()%4);
            traps[i] = Creature(&trap, static_cast<Direction>(dir));
            world.addCreature(&traps[i], pos/72, pos%72);
        }
        
        // Simulate 1000 moves.
        // Print the first 10 grids          (i.e. 0, 1, 2...9).
        //Print every 100th grid after that (i.e. 100, 200, 300...1000).
        world.printGrid(cout);
        cout << endl;
        for (int i = 0; i < 1000; i++) {
            world.step();
            
            if (i < 10 || i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                world.printGrid(cout);
                cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
