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
That creates the ifle Doxyfile.
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
#include <climits>
#include "Darwin.h"

#define NP UINT_MAX

template <typename T>
std::vector<T*> to_ptrs(std::vector<T>& ts) {
    std::vector<T*> ptrs;
    for (auto& t : ts) {
        ptrs.push_back(&t);
    }
    return ptrs;
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
     vector<Instruction> food_program = { {TURN_WEST, NP}, {GO, 0} };
     Species food(to_ptrs(food_program), 'f');

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

     vector<Instruction> hopper_program = {{HOP},{GO, 0}};
     Species hopper(to_ptrs(hopper_program), 'h');

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

    vector<Instruction> rover_program = { {IF_ENEMY, 9}, {IF_EMPTY, 7}, {IF_RANDOM, 5}, {TURN_WEST, NP}, 
        {GO, 0}, {TURN_EAST, NP}, {GO, 0}, {HOP, NP}, {GO, 0}, {INFECT, NP}, {GO, 0} };
    Species rover(to_ptrs(rover_program), 'r');

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
     vector<Instruction> trap_program = { {IF_ENEMY, 3}, {TURN_WEST, NP}, {GO, 0}, {INFECT, NP}, {GO, 0} };
     Species trap(to_ptrs(trap_program), 't');

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Hopper, facing south,  at (0, 0)
        Hopper, facing north, at (7, 7)
	Trap,   facing east, at (0, 7)
        Trap,   facing west, at (7, 0)
        Simulate 10 moves.
        Print every grid.
        */
        vector<Creature> creatures = {{&hopper, SOUTH, {0, 0}}, {&hopper, NORTH, {7, 7}}, 
            {&trap, EAST, {0, 7}}, {&trap, WEST, {7, 0}}};

        Board board(8, 8, to_ptrs(creatures));
        for (int i = 0; i < 10; i++) {
            cout << "Turn = " << i << endl;
            board.printTurn(cout);
            board.runTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 5x5
    // ----------

    {
        cout << "*** Darwin 5x5" << endl;
        /*
        5x5 Darwin
        Trap,   facing north, at (2, 3)
        Rover,  facing north, at (4, 2)
        Rover,  facing east,  at (3, 1)
        Rover,  facing south,  at (0, 4)
        Hopper, facing east,  at (4, 0)
        Simulate 7 moves.
        Print every grid.
        */
        vector<Creature> creatures = {{&trap, NORTH, {2, 3}}, {&rover, NORTH, {4, 2}}, 
            {&rover, EAST, {3, 1}}, {&rover, SOUTH, {0, 4}}, {&hopper, EAST, {4, 0}}};

        Board board(5, 5, to_ptrs(creatures));
        for (int i = 0; i < 7; i++) {
            cout << "Turn = " << i << endl;
            board.printTurn(cout);
            board.runTurn();
        }
    }
    
    // ----------
    // darwin 3x3
    // ----------

    {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
        /*
        3x3 Darwin
        Trap,   facing south, at (1, 1)
        Rover,  facing east, at (0, 0)
        Simulate 16 moves.
        Print every grid.
        */
        vector<Creature> creatures = {{&trap, SOUTH, {1, 1}}, {&rover, EAST, {0, 0}}};
        Board board(3, 3, to_ptrs(creatures));
        for (int i = 0; i < 16; i++) {
            cout << "Turn = " << i << endl;
            board.printTurn(cout);
            board.runTurn();
        }
    }

    return 0;}
