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
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
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

    Species Food("food");
    Food.addInstruction(LEFT);
    Food.addInstruction(GO, 0);
    // Food.printList();
    // cout << endl;
    
    // ------
    // hopper
    // ------

    /*
0: hop
1: go 0
*/

    Species Hopper("hopper");
    Hopper.addInstruction(HOP);
    Hopper.addInstruction(GO, 0);
    // Hopper.printList();
    // cout << endl;

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

    Species Rover("rover");
    Rover.addInstruction(IF_ENEMY, 9);
    Rover.addInstruction(IF_EMPTY, 7);
    Rover.addInstruction(IF_RANDOM, 5);
    Rover.addInstruction(LEFT);
    Rover.addInstruction(GO, 0);
    Rover.addInstruction(RIGHT);
    Rover.addInstruction(GO, 0);
    Rover.addInstruction(HOP);
    Rover.addInstruction(GO, 0);
    Rover.addInstruction(INFECT);
    Rover.addInstruction(GO, 0);
    // Rover.printList();
    // cout << endl;

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

    Species Trap("trap");
    Trap.addInstruction(IF_ENEMY, 3);
    Trap.addInstruction(LEFT);
    Trap.addInstruction(GO, 0);
    Trap.addInstruction(INFECT);
    Trap.addInstruction(GO, 0);
    // Trap.printList();
    // cout << endl;

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
        Darwin d(8,8);
        Creature f1(Food,EAST,d);
        Creature h1(Hopper,NORTH,d);
        Creature h2(Hopper,EAST,d);
        Creature h3(Hopper,SOUTH,d);
        Creature h4(Hopper,WEST,d);
        Creature f2(Food, NORTH ,d);
        d.addCreature(f1,0,0);
        d.addCreature(h1,3,3);
        d.addCreature(h2,3,4);
        d.addCreature(h3,4,4);
        d.addCreature(h4,4,3);
        d.addCreature(f2,7,7);
        cout << "turn = 0" << endl;
        d.printGrid();
        cout << endl;
        
        for (int i = 0; i < 5; ++i) {
            cout << "turn = " << i+1 << endl;
            d.play();
            d.printGrid();
            d.newTurn();
            cout << endl;
        }
        
        cout << endl;
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
        Darwin d(7,9);
        Creature t1(Trap,SOUTH,d);
        Creature h(Hopper,EAST,d);
        Creature r(Rover,NORTH,d);
        Creature t2(Trap,WEST,d);
        d.addCreature(t1,0,0);
        d.addCreature(h,3,2);
        d.addCreature(r,5,4);
        d.addCreature(t2,6,8);
        cout << "turn = 0" << endl;
        d.printGrid();
        cout << endl;
        
        for (int i = 0; i < 5; ++i) {
            cout << "turn = " << i+1 << endl;
            d.play();
            d.printGrid();
            d.newTurn();
            cout << endl;
        }
        cout << endl;
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
        cout << "*** Darwin 20x20 Test ***" << endl;
        cout << "*** eshabanov ***" << endl;
        srand(0);
        Darwin d(20,20);
        direction direct;
        int randPos, r,c;
        

        for (int i = 1; i < 9; ++i) {
            randPos = rand() % 400;
            r = randPos / 20;
            c = randPos % 20;
            direct = direction(rand() % 4);
            Creature h(Hopper,direct,d);
            d.addCreature(h,r,c);
        }

        for (int i = 1; i < 3; ++i) {
            randPos = rand() % 400;
            r = randPos / 20;
            c = randPos % 20;
            direct = direction(rand() % 4);
            Creature rov(Rover,direct,d);
            d.addCreature(rov,r,c);
        }

        for (int i = 1; i < 5; ++i) {
            randPos = rand() % 400;
            r = randPos / 20;
            c = randPos % 20;
            direct = direction(rand() % 4);
            Creature f(Food,direct,d);
            d.addCreature(f,r,c);
        }

        cout << "Turn = 0." << endl;
        d.printGrid();
        cout << endl;
        for (int i = 1; i < 5; ++i) {
            cout << "Turn = " << i << "." << endl;
            d.play();
            d.printGrid();
            d.newTurn();
            cout << endl;
        }

        cout << endl;
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
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        cout << "*** davismc ***" << endl;
        srand(0);
        Darwin d(1,8);
        Creature c(Rover,EAST,d);
        d.addCreature(c,0,3);
        const int num_moves = 100;
        cout << "Turn = 0." << endl;
        d.printGrid();
        cout << endl;
        for (int i = 1; i <= num_moves; ++i) {
            d.play();
            if (i % 10 == 0) {
                cout << "Turn = " << i << "." << endl;
                d.printGrid();
                cout << endl;
            }
            d.newTurn();
        }

        cout << endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


        try {
            cout << "*** Darwin 1x20 ***" << endl;
            cout << "*** rj2339 ***" << endl;
            srand(0);
            Darwin d(1,20);
            Creature h1(Hopper,EAST,d);
            Creature h2(Hopper,WEST,d);
            Creature h3(Hopper,WEST,d);
            Creature h4(Hopper,EAST,d);
            Creature h5(Hopper,WEST,d);
            Creature h6(Hopper,EAST,d);
            Creature h7(Hopper,EAST,d);
            Creature h8(Hopper,WEST,d);
            Creature h9(Hopper,WEST,d);
            Creature h10(Hopper,WEST,d);
            Creature r(Rover,NORTH,d);

            d.addCreature(h1,0,0);
            d.addCreature(h2,0,1);
            d.addCreature(h3,0,4);
            d.addCreature(h4,0,5);
            d.addCreature(h5,0,6);
            d.addCreature(h6,0,8);
            d.addCreature(h7,0,12);
            d.addCreature(h8,0,16);
            d.addCreature(h9,0,17);
            d.addCreature(h10,0,18);
            d.addCreature(r,0,19);

            // cout << "Turn = 0" << endl;
            // d.printGrid();
            // cout << endl;

            for (int i = 0; i < 10; ++i) {
                cout << "Turn = " << i << endl;
                d.printGrid();
                d.play();
                d.newTurn();
                cout << endl;
            }

            cout << endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
            cout << "*** Darwin 3x3 ***" << endl;
            cout << "*** jokvar ***" << endl;
            Darwin d(3,3);
            Creature c1(Trap,NORTH,d);
            Creature c2(Food,NORTH,d);
            Creature c3(Food,NORTH,d);
            Creature c4(Food,NORTH,d);
            Creature c5(Food,NORTH,d);
            Creature c6(Food,NORTH,d);
            Creature c7(Food,NORTH,d);
            Creature c8(Food,NORTH,d);
            Creature c9(Food,NORTH,d);

            d.addCreature(c1,1,1);
            d.addCreature(c2,0,0);
            d.addCreature(c3,0,1);
            d.addCreature(c4,0,2);
            d.addCreature(c5,1,0);
            d.addCreature(c6,1,2);
            d.addCreature(c7,2,0);
            d.addCreature(c8,2,1);
            d.addCreature(c9,2,2);

            for (int i = 0 ; i <= 6; ++i) {
                cout << "Turn = " << i << "." << endl;
                d.printGrid();
                d.play();
                d.newTurn();
                cout << endl;
            }

            cout << endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
            cout << "*** Darwin 11x11 ***" << endl;
            cout << "*** ianhays ***" << endl;
            Darwin d(11,11);
            Creature t1(Trap,SOUTH,d);
            Creature t2(Trap,NORTH,d);
            Creature t3(Trap,EAST,d);
            Creature t4(Trap,NORTH,d);
            Creature r1(Rover,EAST,d);
            Creature r2(Rover,WEST,d);

            d.addCreature(t1,1,1); 
            d.addCreature(t2,2,2); 
            d.addCreature(t3,1,2);
            d.addCreature(t4,2,1);
            d.addCreature(r1,0,0); 
            d.addCreature(r2,0,10); 

            cout << "Turn = 0." << endl;
            d.printGrid();
            cout << endl;

            for (int i = 1; i <= 20; ++i) {
                cout << "Turn = " << i << "." << endl;
                d.play();
                d.printGrid();
                d.newTurn();
                cout << endl;
            }

            cout << endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
