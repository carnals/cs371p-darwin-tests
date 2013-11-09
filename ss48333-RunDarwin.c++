// -----------------------------
// steven spohrer
// eid: ss48333
// csid: ss48333
// -----------------------------


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
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food); 
                                    

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    InstructionSet_t inst_hopper;
    inst_hopper.push_back(Instruction(PrimativeInstruction::HOP));
    inst_hopper.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species hopper('h', inst_hopper); 

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right .
     6: go 0 . 
     7: hop . 
     8: go 0 . 
     9: infect . 
    10: go 0 .
    */
    InstructionSet_t inst_rover;
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_ENEMY, 9));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_EMPTY, 7));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_RANDOM, 5));
    inst_rover.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::RIGHT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::HOP));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::INFECT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species rover('r', inst_rover); 
    // ----
    // trap
    // ----

    /*
     0: if_enemy 3 .
     1: left .
     2: go 0 .
     3: infect .
     4: go 0
    */
    InstructionSet_t inst_trap;
    inst_trap.push_back(Instruction(PrimativeInstruction::IF_ENEMY, 3));
    inst_trap.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_trap.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_trap.push_back(Instruction(PrimativeInstruction::INFECT));
    inst_trap.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species trap('t', inst_trap);

    // ----------
    // darwin 4x4 swap corners
    // ----------

    try {
        cout << "*** Darwin 4x4 Swap Corners***" << endl;
        /*
        4x4 Darwin
        Simulate 5 moves.
        Print every grid.
        */

        GameController game(4, 4);
        game.addCreature(&hopper, Direction::EAST, 0,0);
        game.addCreature(&hopper, Direction::WEST, 3,3);
        game.addCreature(&hopper, Direction::SOUTH, 0,3);
        game.addCreature(&hopper, Direction::NORTH, 3,0);
        game.print(std::cout);
        for(uint32_t i = 0; i < 5; ++i){
            game.run(1);
            game.print(std::cout); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // darwin 4x4 rovers
    // ----------

    try {
        cout << "*** Darwin 4x4 Cross rovers ***" << endl;
        /*
        8x8 Darwin
        Simulate 3 moves.
        Print every grid.
        */
        srand(0);
        GameController game(4, 4);
        game.addCreature(&rover, Direction::NORTH, 3,0);
        game.addCreature(&rover, Direction::NORTH, 3,1);
        game.addCreature(&rover, Direction::NORTH, 3,2);
        game.addCreature(&rover, Direction::NORTH, 3,3);

        game.addCreature(&food, Direction::NORTH, 1,0);
        game.addCreature(&food, Direction::NORTH, 1,1);
        game.addCreature(&food, Direction::NORTH, 1,2);
        game.addCreature(&food, Direction::NORTH, 1,3);
        
        game.print(std::cout);
        for(uint32_t i = 0; i < 2; ++i){
            game.run(1);
            game.print(std::cout); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 4x4 trap
    // ----------

    try {
        cout << "*** Darwin 4x4 Trap ***" << endl;
        /*
        8x8 Darwin
        Simulate 10 moves.
        Print the final grid. Every hopper should of been trapped. 
        */
        srand(0);
        GameController game(4, 4);
        game.addCreature(&trap, Direction::NORTH, 3,0);
        game.addCreature(&trap, Direction::NORTH, 3,1);
        game.addCreature(&trap, Direction::NORTH, 3,2);
        game.addCreature(&trap, Direction::NORTH, 3,3);

        game.addCreature(&hopper, Direction::SOUTH, 0,0);
        game.addCreature(&hopper, Direction::SOUTH, 0,1);
        game.addCreature(&hopper, Direction::SOUTH, 0,2);
        game.addCreature(&hopper, Direction::SOUTH, 0,3);
        
        game.print(std::cout);
        for(uint32_t i = 0; i < 10; ++i){
            game.run(1);
        }
        game.print(std::cout); 
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    
    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0) . 
        Hopper, facing north, at (3, 3) .
        Hopper, facing east,  at (3, 4) .
        Hopper, facing south, at (4, 4) . 
        Hopper, facing west,  at (4, 3) . 
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */

        GameController game(8, 8);
        game.addCreature(&food, Direction::EAST, 0, 0);
        game.addCreature(&hopper, Direction::NORTH, 3,3);
        game.addCreature(&hopper, Direction::EAST, 3,4);
        game.addCreature(&hopper, Direction::SOUTH, 4,4);
        game.addCreature(&hopper, Direction::WEST, 4,3);
        game.addCreature(&food, Direction::NORTH, 7, 7);
        game.print(std::cout);
        for(uint32_t i = 0; i < 5; ++i){
            game.run(1);
            game.print(std::cout); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
