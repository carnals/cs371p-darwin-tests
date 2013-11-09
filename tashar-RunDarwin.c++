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
#include <string>
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
        Darwin d(8, 8);
        Species food = getFood();
        Species hopper = getHopper();
        Creature food1(food, EAST);
        Creature hopper1(hopper, NORTH);
        Creature hopper2(hopper, EAST);
        Creature hopper3(hopper, SOUTH);
        Creature hopper4(hopper, WEST);
        Creature food2(food, NORTH);
        d.addCreature(food1, 0, 0);
        d.addCreature(hopper1, 3, 3);
        d.addCreature(hopper2, 3, 4);
        d.addCreature(hopper3, 4, 4);
        d.addCreature(hopper4, 4, 3);
        d.addCreature(food2, 7, 7);
        runDarwin(d, 5, 1);
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
        Darwin d(7, 9);
        Species hopper = getHopper();
        Species trap = getTrap();
        Species rover = getRover();
        Creature trap1(trap, SOUTH);
        Creature hopper1(hopper, EAST);
        Creature rover1(rover, NORTH);
        Creature trap2(trap, WEST);
        d.addCreature(trap1, 0, 0);
        d.addCreature(hopper1, 3, 2);
        d.addCreature(rover1, 5, 4);
        d.addCreature(trap2, 6, 8);
        runDarwin(d, 5, 1);
        }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
    
    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        Darwin d(2, 2);
        Species hopper = getHopper();
        Creature hopper1(hopper, EAST);
        Creature hopper2(hopper, WEST);
        Creature hopper3(hopper, SOUTH);
        Creature hopper4(hopper, NORTH);
        d.addCreature(hopper1, 0, 0);
        d.addCreature(hopper2, 0, 1);
        d.addCreature(hopper3, 1, 0);
        d.addCreature(hopper4, 1, 1);
        runDarwin(d, 5, 1);
        }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
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
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        Darwin d(72, 72);
        Species hopper = getHopper();
        Species trap = getTrap();
        Species rover = getRover();
        Species food = getFood();
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(food, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(rover, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(trap, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        d.print();
        for(int i = 0; i < 10; i++) {  //do 10 turns, printing the 0-9th
            d.print();
            d.takeTurn();
        }
        for(int i = 0; i < 90; i++) {  //do 90 more turns;
            d.takeTurn();
        }
        runDarwin(d, 900, 100);        //do 900 more turns, printing every 100
        string names[4] = {"Food", "Hopper", "Rover", "Trap"};
        d.printWinner(names, 4);
    }
    catch (const invalid_argument& e) {
        throw;}
    catch (const out_of_range& e) {
        throw;}

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
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        Darwin d(72, 72);
        Species hopper = getHopper();
        Species trap = getTrap();
        Species rover = getRover();
        Species food = getFood();
        Species best = getBest();
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(food, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(rover, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(trap, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % 5184;
            Creature c(best, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        d.print();
        for(int i = 0; i < 10; i++) {  //do 10 turns, printing the 0-9th
            d.print();
            d.takeTurn();
        }
        for(int i = 0; i < 90; i++) {  //do 90 more turns;
            d.takeTurn();
        }
        runDarwin(d, 900, 100);        //do 900 more turns, printing every 100
        string names[5] = {"Food", "Hopper", "Rover", "Trap", "Best"};
        d.printWinner(names, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    try {
        cout << "*** Darwin 100x100 ***" << endl;
        srand(0);
        
          Darwin d(100, 100);
        Species hopper = getHopper();
        Species trap = getTrap();
        Species rover = getRover();
        Species food = getFood();
        for(int i = 0; i < 20; i++) {
            int pos = rand() % 10000;
            Creature c(food, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 20; i++) {
            int pos = rand() % 10000;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 20; i++) {
            int pos = rand() % 10000;
            Creature c(rover, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 20; i++) {
            int pos = rand() % 10000;
            Creature c(trap, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        runDarwin(d, 500, 50);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
    try {
        cout << "*** Darwin 100x100 ***" << endl;
        srand(0);
        Darwin d(100, 100);
        Species hopper = getHopper();
        Species trap = getTrap();
        Species rover = getRover();
        Species food = getFood();
        for(int i = 0; i < 200; i++) {
            int pos = rand() % 10000;
            Creature c(food, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 200; i++) {
            int pos = rand() % 10000;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 200; i++) {
            int pos = rand() % 10000;
            Creature c(rover, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 200; i++) {
            int pos = rand() % 10000;
            Creature c(trap, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        runDarwin(d, 500, 50);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
        
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        Darwin d(10, 10);
        Species rover = getRover();
        Species food = getFood();
        for(int i = 0; i < 50; i ++) {
            Creature c(rover, static_cast<Direction>(rand()%4));
            d.addCreature(c, i);
        }
        for(int i = 50; i < 100; i ++) {
            Creature c(food, static_cast<Direction>(rand()%4));
            d.addCreature(c, i);
        }
        runDarwin(d, 30, 3);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
        
    try {
        cout << "*** Darwin 1x1 ***" << endl;      
        Darwin d(1, 1);
        Species hopper = getHopper();
        Creature c(hopper, NORTH);
        d.addCreature(c, 0);
        runDarwin(d, 5, 1);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        Darwin d(10, 10);
        Species hopper = getHopper();
        for(int i = 0; i < 50; i++) {
            int pos = rand() % 100;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        runDarwin(d, 10, 1);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
        
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        
        Darwin d(10, 10);
        Species hopper = getHopper();
        for(int i = 0; i < 50; i++) {
            int pos = rand() % 100;
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        runDarwin(d, 10, 1);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}   
    
    try {
        cout << "*** Darwin 25x25 ***" << endl;
        srand(0);
        
        Darwin d(25, 25);
        Species hopper = getHopper();
        Species trap = getTrap();
        for(int i = 0; i < 100; i++) {
            int pos = rand() % (25*25);
            Creature c(hopper, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        for(int i = 0; i < 10; i++) {
            int pos = rand() % (25*25);
            Creature c(trap, static_cast<Direction>(rand()%4));
            d.addCreature(c, pos);
        }
        runDarwin(d, 20, 2);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
        
    try {
        cout << "*** Darwin 25x25 ***" << endl;
        srand(0);
        
        Darwin d(25, 25);
        Species rover = getRover();
        Creature c(rover, EAST);
        Creature c2(rover, WEST);
        d.addCreature(c, 10, 10);
        d.addCreature(c2, 20, 20);
        runDarwin(d, 100000, 10000);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}
        
    return 0;}