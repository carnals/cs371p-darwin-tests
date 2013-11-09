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

  try {
    cout << "*** 5x1 test: two hoppers meet ***" << endl;
    /* 5x1 Darwin
       Place one hopper on top of the grid (0,0), facing south
       Place another hopper on the bottom(9,0), facing north
       Simulate 5 moves
       Print every grid 
    */
    Creature hopper_1(HOPPER,0,0,DOWN);
    Creature* h1 = &hopper_1;
    Creature hopper_2(HOPPER,4,0,UP);
    Creature* h2 = &hopper_2;
    
    World w(5,1,5);
    w.add_creature(h1);
    w.add_creature(h2);
    w.simulate(); 
  }
  catch (const invalid_argument&) {
        assert(false);}
  catch (const out_of_range&) {
        assert(false);}

  try {
    cout << "1x4 test: eat the food" << endl;
    /*
    1x4 Darwin
    Place Food on (0,0), facing west
    Place Food on (0,3), facing east
    Place Trap on (0,1), facing north
    Place Trap on (0,2), facing north
    Simulate 5 moves
    Print every grid
    */ 
    
    Creature food_1(FOOD,0,0,LEFT);
    Creature* c1 = &food_1;
    Creature food_2(FOOD,0,3,RIGHT);
    Creature* c2 = &food_2;
    Creature trap_1(TRAP,0,1,UP);
    Creature* c3 = &trap_1;
    Creature trap_2(TRAP,0,2,UP);
    Creature* c4 = &trap_2;

    World w(1,4,5);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.simulate(); 
  }
  catch (const invalid_argument&) {
        assert(false);}
  catch (const out_of_range&) {
        assert(false);}
 
  try {
    cout << "5x5 test: eat all the food!" << endl;
    /*
    5x5 Darwin
    Place a rover at (2,2), facing south
    Fill the rest of the grid with food, all facing north 
    Simulate 20 moves
    Print every grid
    Everyone, except (4,0) should be a rover after turn 16
    */
    srand(0); 
    
    Creature food_1(FOOD,0,0,UP);
    Creature* c1 = &food_1;
    Creature food_2(FOOD,0,1,UP);
    Creature* c2 = &food_2;
    Creature food_3(FOOD,0,2,UP);
    Creature* c3 = &food_3;
    Creature food_4(FOOD,0,3,UP);
    Creature* c4 = &food_4;
    Creature food_5(FOOD,1,0,UP);
    Creature* c5 = &food_5;
    Creature food_6(FOOD,1,1,UP);
    Creature* c6 = &food_6;
    Creature food_7(FOOD,1,2,UP);
    Creature* c7 = &food_7;
    Creature food_8(FOOD,1,3,UP);
    Creature* c8 = &food_8;
    Creature food_9(FOOD,1,4,UP);
    Creature* c9 = &food_9;
    Creature food_10(FOOD,2,0,UP);
    Creature* c10 = &food_10;
    Creature food_11(FOOD,2,1,UP);
    Creature* c11 = &food_11;
    Creature food_12(FOOD,2,3,UP);
    Creature* c12 = &food_12;
    Creature food_13(FOOD,2,4,UP);
    Creature* c13 = &food_13;
    Creature food_14(FOOD,3,0,UP);
    Creature* c14 = &food_14;
    Creature food_15(FOOD,3,1,UP);
    Creature* c15 = &food_15;
    Creature food_16(FOOD,3,2,UP);
    Creature* c16 = &food_16;
    Creature food_17(FOOD,3,3,UP);
    Creature* c17 = &food_17;
    Creature food_18(FOOD,3,4,UP);
    Creature* c18 = &food_18;
    Creature food_19(FOOD,4,0,UP);
    Creature* c19 = &food_19;
    Creature food_20(FOOD,4,1,UP);
    Creature* c20 = &food_20;
    Creature food_21(FOOD,4,2,UP);
    Creature* c21 = &food_21;
    Creature food_22(FOOD,4,3,UP);
    Creature* c22 = &food_22;
    Creature food_23(FOOD,4,4,UP);
    Creature* c23 = &food_23;
    Creature food_24(FOOD,0,4,UP);
    Creature* c24 = &food_24;
    Creature rover(ROVER,2,2,DOWN);
    Creature* c25 = &rover;

    World w(5,5,20);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.add_creature(c5);
    w.add_creature(c6);
    w.add_creature(c7);
    w.add_creature(c8);
    w.add_creature(c9);
    w.add_creature(c10);
    w.add_creature(c11);
    w.add_creature(c12);
    w.add_creature(c13);
    w.add_creature(c14);
    w.add_creature(c15);
    w.add_creature(c16);
    w.add_creature(c17);
    w.add_creature(c18);
    w.add_creature(c19);
    w.add_creature(c20);
    w.add_creature(c21);
    w.add_creature(c22);
    w.add_creature(c23);
    w.add_creature(c24);
    w.add_creature(c25);
    w.simulate();
  }
  catch (const invalid_argument&) {
        assert(false);}
  catch (const out_of_range&) {
        assert(false);}
  try {
    cout << "5x5 test: trapped war" << endl;
    /*
    5x5 Darwin
    Fill all of the edges with traps
    The upper edge ones face north (including (0,0) and (0,4)
    The lower edge ones face south (just (4,1), (4,2), (4,3))
    The left edge ones face west (including (4,0))
    The right edge ones face east (including (4,4))
    Put a rover on (2,1), facing west
    Put another rover on (2,3), facing east
    Simulate 15 moves
    The rovers lose after turn 11
    Print every grid 
    */
    srand(0);

    Creature trap_1(TRAP,0,0,UP);
    Creature* c1 = &trap_1;
    Creature trap_2(TRAP,0,1,UP);
    Creature* c2 = &trap_2;
    Creature trap_3(TRAP,0,2,UP);
    Creature* c3 = &trap_3;
    Creature trap_4(TRAP,0,3,UP);
    Creature* c4 = &trap_4;
    Creature trap_5(TRAP,0,4,UP);
    Creature* c5 = &trap_5;
    Creature trap_6(TRAP,1,4,RIGHT);
    Creature* c6 = &trap_6;
    Creature trap_7(TRAP,2,4,RIGHT);
    Creature* c7 = &trap_7;   
    Creature trap_8(TRAP,3,4,RIGHT);
    Creature* c8 = &trap_8;    
    Creature trap_9(TRAP,4,4,RIGHT);
    Creature* c9 = &trap_9;
    Creature trap_10(TRAP,4,3,DOWN);
    Creature* c10 = &trap_10; 
    Creature trap_11(TRAP,4,2,DOWN);
    Creature* c11 = &trap_11;
    Creature trap_12(TRAP,4,1,DOWN);
    Creature* c12 = &trap_12;
    Creature trap_13(TRAP,4,0,LEFT);
    Creature* c13 = &trap_13;
    Creature trap_14(TRAP,3,0,LEFT);
    Creature* c14 = &trap_14;
    Creature trap_15(TRAP,2,0,LEFT);
    Creature* c15 = &trap_15;
    Creature trap_16(TRAP,1,0,LEFT);
    Creature* c16 = &trap_16;
    Creature rover_1(ROVER,2,1,LEFT);
    Creature* c17 = &rover_1;
    Creature rover_2(ROVER,2,3,RIGHT);
    Creature* c18 = &rover_2;

    World w(5,5,20);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.add_creature(c5);
    w.add_creature(c6);
    w.add_creature(c7);
    w.add_creature(c8);
    w.add_creature(c9);
    w.add_creature(c10);
    w.add_creature(c11);
    w.add_creature(c12);
    w.add_creature(c13);
    w.add_creature(c14);
    w.add_creature(c15);
    w.add_creature(c16);
    w.add_creature(c17);
    w.add_creature(c18);
    w.simulate();
  }
  catch (const invalid_argument&) {
        assert(false);}
  catch (const out_of_range&) {
        assert(false);}

// ---------------------------------------------------------------------
// Now testing others' acceptance tests

  try {
    cout << "*** Fod Walk Meet In Middle 4x4 by davismc ***" << endl;
    
    Creature hopper_1(HOPPER,0,0,RIGHT);
    Creature* c1 = &hopper_1;
    Creature hopper_2(HOPPER,1,0,RIGHT);
    Creature* c2 = &hopper_2;
    Creature hopper_3(HOPPER,2,0,RIGHT);
    Creature* c3 = &hopper_3;
    Creature hopper_4(HOPPER,3,0,RIGHT);
    Creature* c4 = &hopper_4;
    Creature hopper_5(HOPPER,0,5,LEFT);
    Creature* c5 = &hopper_5;
    Creature hopper_6(HOPPER,1,5,LEFT);
    Creature* c6 = &hopper_6;
    Creature hopper_7(HOPPER,2,5,LEFT);
    Creature* c7 = &hopper_7;
    Creature hopper_8(HOPPER,3,5,LEFT);
    Creature* c8 = &hopper_8;

    World w(4,6,4);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.add_creature(c5);
    w.add_creature(c6);
    w.add_creature(c7);
    w.add_creature(c8);
    w.simulate();
  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
  try {
    cout << "*** Hopper Collide 10x4 by ensign ***" << endl;
    /*        
                                10x4 Darwin
                                4 Hoppers, facing south in each column of row 0
                                4 Hoppers, facing north in each column of row 9
                                Simulate 10 moves
                                Print every move
     */

    Creature hop_2(HOPPER,0,0,DOWN);
    Creature* c2 = &hop_2;
    Creature hop_3(HOPPER,0,1,DOWN);
    Creature* c3 = &hop_3;
    Creature hop_4(HOPPER,0,2,DOWN);
    Creature* c4 = &hop_4;
    Creature hop_5(HOPPER,0,3,DOWN);
    Creature* c5 = &hop_5;
    Creature hop_6(HOPPER,9,0,UP);
    Creature* c6 = &hop_6;
    Creature hop_7(HOPPER,9,1,UP);
    Creature* c7 = &hop_7;
    Creature hop_8(HOPPER,9,2,UP);
    Creature* c8 = &hop_8;
    Creature hop_9(HOPPER,9,3,UP);
    Creature* c9 = &hop_9;
 
    World w(10,4,10);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.add_creature(c5);
    w.add_creature(c6);
    w.add_creature(c7);
    w.add_creature(c8);
    w.add_creature(c9);
    w.simulate();

  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
  try {
    cout << "*** Darwin 3x8 Guantlet by ethan ***" << endl;
    /*
        3x8 Darwin
        Trap, facing south, at (0, 3)
        Trap, facing east,  at (0, 4)
        Trap, facing north, at (2, 3)
        Trap, facing east,  at (2, 4)
        Hopper, facing east,  at (1, 0)
        Simulate 10 moves.
        Print every grid.
    */
    Creature trap_1(TRAP,0,3,DOWN);
    Creature* c1 = &trap_1;
    Creature trap_2(TRAP,0,4,RIGHT);
    Creature* c2 = &trap_2;
    Creature trap_3(TRAP,2,3,UP);
    Creature* c3 = &trap_3;
    Creature trap_4(TRAP,2,4,RIGHT);
    Creature* c4 = &trap_4;
    Creature hop(HOPPER,1,0,RIGHT);
    Creature* c5 = &hop;

    World w(3,8,10);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.add_creature(c5);
    w.simulate();
  }
  catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
  
  try {
    cout << "*** Darwin 1x15 by jkovar ***" << endl;

    Creature hop(HOPPER,0,0,RIGHT);
    Creature* c1 = &hop;

    World w(1,15,15);
    w.add_creature(c1);
    w.simulate();
  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  try {
    cout << "*** Darwin 4x4 by nlaz ***" << endl;
    
        /*
         4x4 Darwin
         Trap,   facing west, at (0, 0)
         Food,   facing north,  at (1, 1)
         Food,  facing east, at (2, 2)
         Food,   facing south,  at (3, 3)
         Simulate 5 moves.
         Print every grid.
         */
    Creature f1(FOOD,1,1,UP);
    Creature* c1 = &f1;
    Creature f2(FOOD,2,2,RIGHT);
    Creature* c2 = &f2;
    Creature f3(FOOD,3,3,UP);
    Creature* c3 = &f3;
    Creature t(TRAP,0,0,LEFT);
    Creature* c4 = &t;

    World w(4,4,5);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.simulate();
  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  try {
    cout << "*** Darwin 4x4 Swap Corners by ss48333 ***" << endl;
    
    Creature h1(HOPPER, 0,0, RIGHT);
    Creature* c1 = &h1;
    Creature h2(HOPPER, 3,3, LEFT);
    Creature* c2 = &h2;
    Creature h3(HOPPER, 0,3, DOWN);
    Creature* c3 = &h3;
    Creature h4(HOPPER, 3,0, UP);
    Creature* c4 = &h4;

    World w(4,4,5);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.simulate();

  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  try {
    cout << "*** Fod Walk West 4x4 by davismc ***" << endl;

    Creature hopper_1(HOPPER,0,3,LEFT);
    Creature* c1 = &hopper_1;
    Creature hopper_2(HOPPER,1,3,LEFT);
    Creature* c2 = &hopper_2;
    Creature hopper_3(HOPPER,2,3,LEFT);
    Creature* c3 = &hopper_3;
    Creature hopper_4(HOPPER,3,3,LEFT);
    Creature* c4 = &hopper_4;

    World w(4,4,5);
    w.add_creature(c1);
    w.add_creature(c2);
    w.add_creature(c3);
    w.add_creature(c4);
    w.simulate();
  }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

}
