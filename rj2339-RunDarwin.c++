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
    Species food("f");


    /*
     0: left
     1: go 0
    */
    
    food.addAction(LEFT, 0);
    food.addAction(GO, 1, 0);    

    // ------
    // hopper
    // ------

    Species hopper("h");
    
    /*
     0: hop
     1: go 0
    */
    
    hopper.addAction(HOP, 0);
    hopper.addAction(GO, 1, 0);

    // -----
    // rover
    // -----

    Species rover("r");

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
    
    rover.addAction(ENEMY, 0, 9);
    rover.addAction(EMPTY, 1, 7);
    rover.addAction(RANDOM, 2, 5);
    rover.addAction(LEFT, 3);
    rover.addAction(GO, 4, 0);
    rover.addAction(RIGHT, 5);
    rover.addAction(GO, 6, 0);
    rover.addAction(HOP, 7);
    rover.addAction(GO, 8, 0);
    rover.addAction(INFECT, 9);
    rover.addAction(GO, 10, 0);
    

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
    
    Species trap("t");
    trap.addAction(ENEMY, 0, 3);
    trap.addAction(LEFT, 1);
    trap.addAction(GO, 2, 0);
    
    
    
    trap.addAction(INFECT, 3);
    trap.addAction(GO, 4, 0);


        
    // ------------
    // My acceptance tests
    // ------------       
    try {
        /*
        1x1 Darwin
        hopper, facing EAST,  at (0, 0)
        Simulate 2 moves.
        Print every grid.
        */    
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);    
        
        WorldState world(1, 1);
        Creature h(hopper, EAST);
        world.addCreature(h, 0, 0);
        
        for(int i = 0; i < 3; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}    
        
    try {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);    
        
        /*
        3x3 Darwin
        Hopper, facing EAST,  at (0, 0)
        Hopper, facing WEST,  at (1, 2)
        Simulate 5 moves.
        Print every grid.
        */        
        
        WorldState world(3, 3);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 1, 2);
        
        for(int i = 0; i < 5; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}     


    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);    

        /*
        10x2 Darwin
        Hopper, facing EAST,  at (0, 0)
        Hopper, facing WEST,  at (3, 1)
        Hopper, facing WEST,  at (4, 0)
        Hopper, facing WEST,  at (7, 1)        
        Rover,  facing NORTH, at (9, 0)
        Simulate 10 moves.
        Print every grid.
        */              
        
        WorldState world(10, 2);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        Creature h3(hopper, WEST);
        Creature h4(hopper, WEST);
        Creature r(rover, NORTH);
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 3, 1);
        world.addCreature(h3, 4, 0);
        world.addCreature(h4, 7, 1);        
        world.addCreature(r, 9, 0);
        
        for(int i = 0; i < 10; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}         
        
    try {
        cout << "*** Darwin 1x20 ***" << endl;
        srand(0);    
        
        WorldState world(1, 20);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        Creature h3(hopper, WEST);
        Creature h4(hopper, EAST);
        Creature h5(hopper, WEST);
        Creature h6(hopper, EAST);
        Creature h7(hopper, EAST);
        Creature h8(hopper, WEST);
        Creature h9(hopper, WEST);
        Creature h10(hopper, WEST);
        Creature r(rover, NORTH);
        
        
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 0, 1);
        world.addCreature(h3, 0, 4);
        world.addCreature(h4, 0, 5);
        world.addCreature(h5, 0, 6);
        world.addCreature(h6, 0, 8);
        world.addCreature(h7, 0, 12);   
        world.addCreature(h8, 0, 16);
        world.addCreature(h9, 0, 17);
        world.addCreature(h10, 0, 18);        
        world.addCreature(r, 0, 19);
        
        for(int i = 0; i < 10; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}         
        
        
    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);    
        
        WorldState world(10, 10);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        Creature r(rover, NORTH);
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 1, 1);
        world.addCreature(r, 2, 1);
        
        for(int i = 0; i < 5; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}          
        

    try {
        cout << "*** Darwin 20x20 ***" << endl;
        srand(0);    
        
        WorldState world(20, 20);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        Creature r(rover, NORTH);
        Creature f1(food, EAST);
        Creature f2(food, EAST);
        Creature f3(food, EAST);
        Creature f4(food, EAST);
        Creature f5(food, EAST);
        Creature f6(food, EAST);
        Creature f7(food, EAST);
        Creature f8(food, EAST);
        Creature f9(food, EAST);
        Creature f10(food, EAST);
        
        
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 1, 1);
        world.addCreature(r, 2, 1);
        world.addCreature(f1, 3, 7);
        world.addCreature(f2, 4, 16);
        world.addCreature(f3, 6, 17);
        world.addCreature(f4, 7, 5);
        world.addCreature(f5, 8, 7);
        world.addCreature(f6, 11, 6);
        world.addCreature(f7, 11, 2);
        world.addCreature(f8, 17, 7);
        world.addCreature(f9, 18, 3);
        world.addCreature(f10, 18, 8);
        
        
        for(int i = 0; i < 10; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}          
        
        
    try {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);    
        
        WorldState world(50, 50);
        Creature h1(hopper, EAST);
        Creature h2(hopper, WEST);
        Creature h3(hopper, WEST);
        Creature h4(hopper, NORTH);
        Creature h5(hopper, WEST);
        Creature h6(hopper, EAST);
        Creature h7(hopper, SOUTH);
        Creature h8(hopper, WEST);
        Creature h9(hopper, SOUTH);
        Creature h10(hopper, WEST);
        

        Creature r(rover, NORTH);
        world.addCreature(h1, 0, 0);
        world.addCreature(h2, 1, 1);
        world.addCreature(h3, 2, 6);
        world.addCreature(h4, 10, 1);
        world.addCreature(h5, 15, 18);
        world.addCreature(h6, 3, 20);
        world.addCreature(h7, 8, 39);
        world.addCreature(h8, 40, 1);
        world.addCreature(h9, 37, 2);
        world.addCreature(h10, 22, 30);
        world.addCreature(r, 2, 1);
        
        for(int i = 0; i < 10; i++) {
          std::cout << "Turn = " << i << "\n";
          world.printGrid(std::cout);
          world.takeTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}          
        

     

    return 0;}
