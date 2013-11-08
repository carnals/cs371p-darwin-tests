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
    Species food('f');
    food.add_instruction("left");
    food.add_instruction("go", 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);


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
    rover.add_instruction("if_enemy", 9);
    rover.add_instruction("if_empty", 7);
    rover.add_instruction("if_random", 5);
    rover.add_instruction("left");
    rover.add_instruction("go", 0); 
    rover.add_instruction("right");   
    rover.add_instruction("go", 0);
    rover.add_instruction("hop");
    rover.add_instruction("go", 0);
    rover.add_instruction("infect");
    rover.add_instruction("go", 0);

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
    trap.add_instruction("if_enemy", 3);
    trap.add_instruction("left");
    trap.add_instruction("go", 0);
    trap.add_instruction("infect");
    trap.add_instruction("go", 0); 

    // ----
    // best
    // ----

    
    Species best('b');
    best.add_best();
    

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
        World w(8, 8);
        Creature f1(food, 2);
        w.addCreature(f1, 0, 0);
        Creature h1(hopper, 1);
        w.addCreature(h1, 3, 3);
        Creature h2(hopper, 2);
        w.addCreature(h2, 3, 4);
        Creature h3(hopper, 3);
        w.addCreature(h3, 4, 4);
        Creature h4(hopper, 0);
        w.addCreature(h4, 4, 3);
        Creature f2(food, 1);
        w.addCreature(f2, 7, 7);
        
        w.toString();
        for(int i = 1; i <= 5; i++)
        {
          w.run(i);
          w.toString(); 
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
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        World w(7, 9);
        Creature t1(trap, 3);
        w.addCreature(t1, 0, 0);
        Creature h1(hopper, 2);
        w.addCreature(h1, 3, 2);
        Creature r1(rover, 1);
        w.addCreature(r1, 5, 4);
        Creature t2(trap, 0);
        w.addCreature(t2, 6, 8);
        
        w.toString();
        for(int i = 1; i <= 5; i++)
        {
          w.run(i);
          w.toString(); 
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
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        
        World w(72, 72);
        // Adding food
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(food, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding Hopper
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(hopper, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding Rover
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(rover, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding trap
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(trap, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        
        w.toString();
        for(int i = 1; i <= 1000; i++)
        {
          if((i < 10) || (i % 100 == 0))
          {
            w.run(i);
            w.toString(); 
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
    
        World w(72, 72);
        // Adding food
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(food, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding Hopper
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(hopper, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding Rover
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(rover, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding trap
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(trap, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        // Adding best
        for(int i = 0; i < 10; i++)
        {
          int randNum = rand() % 5184;
          Creature c(best, rand() % 4);
          w.addCreature(c, randNum / 72, randNum % 72);
        }
        
        w.toString();
        for(int i = 1; i <= 1000; i++)
        {
          if((i < 10) || (i % 100 == 0))
          {
            w.run(i);
            w.toString(); 
          }
        }     
        w.numberSpecies();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // Our tests
    // ----------
    // darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 100 (10x10), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for its direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        2 Food
        2 Hopper
        2 Rover
        2 Trap
        Simulate 15 moves.
        Print each grid.
        */
        World w(10, 10);
        // Adding food
        for(int i = 0; i < 2; i++)
        {
          int randNum = rand() % 100;
          Creature c(food, rand() % 4);
          w.addCreature(c, randNum / 10, randNum % 10);
        }
        // Adding Hopper
        for(int i = 0; i < 2; i++)
        {
          int randNum = rand() % 100;
          Creature c(hopper, rand() % 4);
          w.addCreature(c, randNum / 10, randNum % 10);
        }
        // Adding Rover
        for(int i = 0; i < 2; i++)
        {
          int randNum = rand() % 100;
          Creature c(rover, rand() % 4);
          w.addCreature(c, randNum / 10, randNum % 10);
        }
        // Adding trap
        for(int i = 0; i < 2; i++)
        {
          int randNum = rand() % 100;
          Creature c(trap, rand() % 4);
          w.addCreature(c, randNum / 10, randNum % 10);
        }
        
        w.toString();
        for(int i = 1; i <= 15; i++)
        {
            w.run(i);
            w.toString(); 
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 2x2
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        /*
        2x2 Darwin
        Rover,   facing east,  at (0, 0)
        Hopper, facing north, at (0, 1)
        Hopper, facing east,  at (1, 0)
        Hopper, facing south, at (1, 1)
        Simulate 5 moves.
        Print every grid.
        */
        World w(2, 2);
        Creature r1(rover, 2);
        w.addCreature(r1, 0, 0);
        Creature h1(hopper, 1);
        w.addCreature(h1, 0, 1);
        Creature h2(hopper, 2);
        w.addCreature(h2, 1, 0);
        Creature h3(hopper, 3);
        w.addCreature(h3, 1, 1);
        
        w.toString();
        for(int i = 1; i <= 5; i++)
        {
          w.run(i);
          w.toString(); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        /*
        3x3 Darwin
        Rover,   facing east,  at (1, 1)
        Trap, facing west, at (0, 0)
        Trap, facing east,  at (0, 2)
        Trap, facing east, at (2, 2)
        Trap, facing west,  at (2, 0)
        Hopper, facing south, at (0, 1)
        Hopper, facing north,  at (1, 0)
        Hopper, facing north, at (1, 2)
        Hopper, facing east,  at (2, 1)
        Simulate 5 moves.
        Print every grid.
        */
        World w(3, 3);
        Creature r1(rover, 2);
        w.addCreature(r1, 1, 1);
        Creature t1(trap, 0);
        w.addCreature(t1, 0, 0);
        Creature t2(trap, 2);
        w.addCreature(t2, 0, 2);
        Creature t3(trap, 2);
        w.addCreature(t3, 2, 2);
        Creature t4(trap, 0);
        w.addCreature(t4, 2, 0);
        Creature h1(hopper, 3);
        w.addCreature(h1, 0, 1);
        Creature h2(hopper, 2);
        w.addCreature(h2, 1, 0);
        Creature h3(hopper, 0);
        w.addCreature(h3, 1, 2);
        Creature h4(hopper, 1);
        w.addCreature(h4, 2, 1);
        
        w.toString();
        for(int i = 1; i <= 5; i++)
        {
          w.run(i);
          w.toString(); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        /*
        3x3 Darwin
        Rover,   facing north,  at (1, 1)
        Trap, facing west, at (0, 0)
        Rover, facing east,  at (0, 2)
        Trap, facing south, at (2, 2)
        Rover, facing west,  at (2, 0)
        Hopper, facing south, at (0, 1)
        Hopper, facing north,  at (1, 0)
        Hopper, facing north, at (1, 2)
        Hopper, facing east,  at (2, 1)
        Simulate 5 moves.
        Print every grid.
        */
        World w(3, 3);
        Creature r1(rover, 1);
        w.addCreature(r1, 1, 1);
        Creature t1(trap, 0);
        w.addCreature(t1, 0, 0);
        Creature r2(rover, 2);
        w.addCreature(r2, 0, 2);
        Creature t3(trap, 3);
        w.addCreature(t3, 2, 2);
        Creature r4(rover, 0);
        w.addCreature(r4, 2, 0);
        Creature h1(hopper, 3);
        w.addCreature(h1, 0, 1);
        Creature h2(hopper, 2);
        w.addCreature(h2, 1, 0);
        Creature h3(hopper, 0);
        w.addCreature(h3, 1, 2);
        Creature h4(hopper, 1);
        w.addCreature(h4, 2, 1);
        
        w.toString();
        for(int i = 1; i <= 5; i++)
        {
          w.run(i);
          w.toString(); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 5x5
    // ----------

    try {
        cout << "*** Darwin 5x5 ***" << endl;
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 25 (5x5), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for its direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        5 Rover
        3 Trap
        Simulate 10 moves.
        Print each grid.
        */
        World w(5, 5);
        // Adding Rover
        for(int i = 0; i < 5; i++)
        {
          int randNum = rand() % 25;
          Creature c(rover, rand() % 4);
          w.addCreature(c, randNum / 5, randNum % 5);
        }
        // Adding trap
        for(int i = 0; i < 3; i++)
        {
          int randNum = rand() % 25;
          Creature c(trap, rand() % 4);
          w.addCreature(c, randNum / 5, randNum % 5);
        }
        
        w.toString();
        for(int i = 1; i <= 10; i++)
        {
          w.run(i);
          w.toString(); 
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



  return 0;}
