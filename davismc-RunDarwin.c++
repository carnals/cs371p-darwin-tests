/******************************************************************************
 * Program:     Project 4: Darwin
 * Student:     Merrill Davis
 * Class:       CS 371p
 * Fall 2013
 *
 * Purpose: 
 * Simulates Darwin's world.  Darwin's world contains a two-dimensional grid
 * of creatures.  Each creature is of a particular species, and each species
 * runs a program that determines its behavior.   The goal is for a creature
 * to "infect" other creatures, changing them to it's species.
 *****************************************************************************/

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

// Helper function to generate random creatures
void addRandomCreature (Darwin& d, Species& s, int height, int width)
{
        int pos = rand() % (height * width);
        int row = pos / height;
        int col = pos % height;
        direction_t dir = static_cast<direction_t> (rand() % 4);
        d.addCreature(s, row, col, dir);
}

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

     Species food("food", 'f');
     food.addInstruction(LEFT);
     food.addInstruction(GO, 0);

    // ------
    // hopper
    // ------

     Species hopper("hopper", 'h');
     hopper.addInstruction(HOP);
     hopper.addInstruction(GO, 0);

    // -----
    // rover
    // -----

    Species rover("rover", 'r');
    rover.addInstruction(IF_ENEMY, 9); // 0
    rover.addInstruction(IF_EMPTY, 7); // 1
    rover.addInstruction(IF_RANDOM, 5); // 2
    rover.addInstruction(LEFT); // 3
    rover.addInstruction(GO, 0); // 4
    rover.addInstruction(RIGHT); // 5
    rover.addInstruction(GO, 0); // 6
    rover.addInstruction(HOP); // 7
    rover.addInstruction(GO, 0); // 8
    rover.addInstruction(INFECT); // 9
    rover.addInstruction(GO, 0); // 10

    // ----
    // trap
    // ----

     Species trap("trap", 't');
     trap.addInstruction(IF_ENEMY, 3);
     trap.addInstruction(LEFT);
     trap.addInstruction(GO, 0);
     trap.addInstruction(INFECT);
     trap.addInstruction(GO, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin d(8, 8);
        d.addCreature(food, 0, 0, EAST);
        d.addCreature(hopper, 3, 3, NORTH);
        d.addCreature(hopper, 3, 4, EAST);
        d.addCreature(hopper, 4, 4, SOUTH);
        d.addCreature(hopper, 4, 3, WEST);
        d.addCreature(food, 7, 7, NORTH);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
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
        Darwin d(7, 9);
        d.addCreature(trap, 0, 0, SOUTH);
        d.addCreature(hopper, 3, 2, EAST);
        d.addCreature(rover, 5, 4, NORTH);
        d.addCreature(trap, 6, 8, WEST);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
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
        Darwin d(72, 72);
        const int NUM_CREATURES = 10;
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, food, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, hopper, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, rover, 72, 72);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, trap, 72, 72);

        int NUM_MOVES = 9;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }

        NUM_MOVES = 1000;
        for (int i = 10; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 100 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // fod_walk_east 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk East 4x4 ***" << endl;
        Darwin d(4, 4);
        d.addCreature(hopper, 0, 0, EAST);
        d.addCreature(hopper, 1, 0, EAST);
        d.addCreature(hopper, 2, 0, EAST);
        d.addCreature(hopper, 3, 0, EAST);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // fod_walk_north 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk North 4x4 ***" << endl;
        Darwin d(4, 4);
        d.addCreature(hopper, 3, 0, NORTH);
        d.addCreature(hopper, 3, 1, NORTH);
        d.addCreature(hopper, 3, 2, NORTH);
        d.addCreature(hopper, 3, 3, NORTH);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   

    // ------------
    // fod_walk_west 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk West 4x4 ***" << endl;
        Darwin d(4, 4);
        d.addCreature(hopper, 0, 3, WEST);
        d.addCreature(hopper, 1, 3, WEST);
        d.addCreature(hopper, 2, 3, WEST);
        d.addCreature(hopper, 3, 3, WEST);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   

    // ------------
    // fod_walk_south 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk South 4x4 ***" << endl;
        Darwin d(4, 4);
        d.addCreature(hopper, 0, 0, SOUTH);
        d.addCreature(hopper, 0, 1, SOUTH);
        d.addCreature(hopper, 0, 2, SOUTH);
        d.addCreature(hopper, 0, 3, SOUTH);
        const int NUM_MOVES = 5;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // fod_walk_meet_in_middle 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk Meet In Middle 4x4 ***" << endl;
        Darwin d(4, 6);
        d.addCreature(hopper, 0, 0, EAST);
        d.addCreature(hopper, 1, 0, EAST);
        d.addCreature(hopper, 2, 0, EAST);
        d.addCreature(hopper, 3, 0, EAST);
        d.addCreature(hopper, 0, 5, WEST);
        d.addCreature(hopper, 1, 5, WEST);
        d.addCreature(hopper, 2, 5, WEST);
        d.addCreature(hopper, 3, 5, WEST);
        const int NUM_MOVES = 4;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}    

    // ------------
    // rover_tiny_board 1x1
    // ------------
    // Should be stuck but not crash
    try {
        cout << "*** Rover Tiny Board 1x1 ***" << endl;
        Darwin d(1, 1);
        d.addCreature(rover, 0, 0, EAST);
        const int NUM_MOVES = 3;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // rover_tiny_board 2x2
    // ------------
    // Should bounce around in his cage
    try {
        cout << "*** Rover Tiny Board 2x2 ***" << endl;
        srand(0);
        Darwin d(2, 2);
        d.addCreature(rover, 0, 0, EAST);
        const int NUM_MOVES = 100;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 10 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // center death trap 8x8
    // ------------
    // 4 traps in the center wait for the rovers
    try {
        cout << "*** Center Death Trap 8x8 ***" << endl;
        srand(0);
        Darwin d(8, 8);
        d.addCreature(rover, 0, 0, EAST);
        d.addCreature(rover, 7, 2, NORTH);
        d.addCreature(rover, 7, 6, SOUTH);
        d.addCreature(rover, 1, 6, SOUTH); 
        d.addCreature(trap, 3, 3, NORTH);
        d.addCreature(trap, 3, 4, EAST);  
        d.addCreature(trap, 4, 3, WEST);  
        d.addCreature(trap, 4, 4, SOUTH);  
        const int NUM_MOVES = 200;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 10 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // rover_skinny_board 8x1
    // ------------
    try {
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        srand(0);
        Darwin d(8, 1);
        d.addCreature(rover, 3, 0, EAST);
        const int NUM_MOVES = 100;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 10 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    // ------------
    // rover_skinny_board 1x8
    // ------------
    try {
        cout << "*** Rover Skinny Board 8x1 ***" << endl;
        srand(0);
        Darwin d(1, 8);
        d.addCreature(rover, 0, 3, EAST);
        const int NUM_MOVES = 100;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 1; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 10 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);} 

    //------------------------
    // center trap all 4 types
    //------------------------
    try {
        cout << "*** Center Trap All 4 Creatures 17x17 ***" << endl;
        srand(0);
        Darwin d(17, 17);
        const int NUM_CREATURES = 5;
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, food, 17, 17);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, hopper, 17, 17);
        for (int i = 0; i < NUM_CREATURES; ++i)
            addRandomCreature (d, rover, 17, 17);

        // Center Trap
        d.addCreature(trap, 8, 8, NORTH);
        d.addCreature(trap, 8, 9, EAST);  
        d.addCreature(trap, 9, 8, WEST);  
        d.addCreature(trap, 9, 9, SOUTH); 
        d.addCreature(trap, 9, 9, SOUTH); // Readding to same spot, shouldn't crash

        int NUM_MOVES = 9;
        d.printBoard(std::cout);
        std::cout << std::endl;
        for (int i = 0; i < NUM_MOVES; ++i) {
            d.runTurn();
            d.printBoard(std::cout);
            std::cout << endl;
        }

        NUM_MOVES = 1000;
        for (int i = 10; i <= NUM_MOVES; ++i) {
            d.runTurn();
            if (i % 100 == 0) {
                d.printBoard(std::cout);
                std::cout << endl;
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
return 0;}