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

#include "./Darwin.h"

#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

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
          World world(8, 8);
          Creature f1(food, EAST);
          Creature h1(hopper, NORTH);
          Creature h2(hopper, EAST);
          Creature h3(hopper, SOUTH);
          Creature h4(hopper, WEST);
          Creature f2(food, NORTH);
          
          world.place(f1, 0, 0);
          world.place(h1, 3, 3);
          world.place(h2, 3, 4);
          world.place(h3, 4, 4);
          world.place(h4, 4, 3);
          world.place(f2, 7, 7);

          for (int i = 0; i < 5; i++) {
            world.turn(i, true);
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
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 8)
Simulate 5 moves.
Print every grid.
*/
          World world(7,9);
          Creature t1(trap, SOUTH);
          Creature h(hopper, EAST);
          Creature r(rover, NORTH);
          Creature t2(trap, WEST);
          world.place(t1, 0, 0);
          world.place(h, 3, 2);
          world.place(r, 5, 4);
          world.place(t2, 6, 8);
          for (int i = 0; i < 5; i++) {
            world.turn(i, true);
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
Print the first 10 grids (i.e. 0, 1, 2...9).
Print every 100th grid after that (i.e. 100, 200, 300...1000).
*/
          World world(72, 72);
          Creature f1(food, rand()%4); Creature f2(food, rand()%4); Creature f3(food, rand()%4);
          Creature f4(food, rand()%4); Creature f5(food, rand()%4); Creature f6(food, rand()%4);
          Creature f7(food, rand()%4); Creature f8(food, rand()%4); Creature f9(food, rand()%4);
          Creature f10(food, rand()%4);
          Creature h1(hopper, rand()%4); Creature h2(hopper, rand()%4); Creature h3(hopper, rand()%4);
          Creature h4(hopper, rand()%4); Creature h5(hopper, rand()%4); Creature h6(hopper, rand()%4);
          Creature h7(hopper, rand()%4); Creature h8(hopper, rand()%4); Creature h9(hopper, rand()%4);
          Creature h10(hopper, rand()%4);
          Creature r1(rover, rand()%4); Creature r2(rover, rand()%4); Creature r3(rover, rand()%4);
          Creature r4(rover, rand()%4); Creature r5(rover, rand()%4); Creature r6(rover, rand()%4);
          Creature r7(rover, rand()%4); Creature r8(rover, rand()%4); Creature r9(rover, rand()%4);
          Creature r10(rover, rand()%4);
          Creature t1(trap, rand()%4); Creature t2(trap, rand()%4); Creature t3(trap, rand()%4);
          Creature t4(trap, rand()%4); Creature t5(trap, rand()%4); Creature t6(trap, rand()%4);
          Creature t7(trap, rand()%4); Creature t8(trap, rand()%4); Creature t9(trap, rand()%4);
          Creature t10(trap, rand()%4);
          int place = rand()%5184;
          world.place(f1, place/72, place%72); place = rand()%5184; world.place(f2, place/72, place%72); place = rand()%5184;
          world.place(f3, place/72, place%72); place = rand()%5184; world.place(f4, place/72, place%72); place = rand()%5184;
          world.place(f5, place/72, place%72); place = rand()%5184; world.place(f6, place/72, place%72); place = rand()%5184;
          world.place(f7, place/72, place%72); place = rand()%5184; world.place(f8, place/72, place%72); place = rand()%5184;
          world.place(f9, place/72, place%72); place = rand()%5184; world.place(f10, place/72, place%72); place = rand()%5184;
          world.place(h1, place/72, place%72); place = rand()%5184; world.place(h2, place/72, place%72); place = rand()%5184;
          world.place(h3, place/72, place%72); place = rand()%5184; world.place(h4, place/72, place%72); place = rand()%5184;
          world.place(h5, place/72, place%72); place = rand()%5184; world.place(h6, place/72, place%72); place = rand()%5184;
          world.place(h7, place/72, place%72); place = rand()%5184; world.place(h8, place/72, place%72); place = rand()%5184;
          world.place(h9, place/72, place%72); place = rand()%5184; world.place(h10, place/72, place%72); place = rand()%5184;
          world.place(r1, place/72, place%72); place = rand()%5184; world.place(r2, place/72, place%72); place = rand()%5184;
          world.place(r3, place/72, place%72); place = rand()%5184; world.place(r4, place/72, place%72); place = rand()%5184;
          world.place(r5, place/72, place%72); place = rand()%5184; world.place(r6, place/72, place%72); place = rand()%5184;
          world.place(r7, place/72, place%72); place = rand()%5184; world.place(r8, place/72, place%72); place = rand()%5184;
          world.place(r9, place/72, place%72); place = rand()%5184; world.place(r10, place/72, place%72); place = rand()%5184;
          world.place(t1, place/72, place%72); place = rand()%5184; world.place(t2, place/72, place%72); place = rand()%5184;
          world.place(t3, place/72, place%72); place = rand()%5184; world.place(t4, place/72, place%72); place = rand()%5184;
          world.place(t5, place/72, place%72); place = rand()%5184; world.place(t6, place/72, place%72); place = rand()%5184;
          world.place(t7, place/72, place%72); place = rand()%5184; world.place(t8, place/72, place%72); place = rand()%5184;
          world.place(t9, place/72, place%72); place = rand()%5184; world.place(t10, place/72, place%72);

          for (int i = 0; i < 10; i++) {
            world.turn(i, true);
          }
          for (int j = 10; j < 1000; j++) {
            world.turn(j, ((j+1)%100) == 0);
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
Print the first 10 grids (i.e. 0, 1, 2...9).
Print every 100th grid after that (i.e. 100, 200, 300...1000).
*/
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try
    {
        cout << "*** Darwin 1x15 ***" << endl;

        World world(1,15);
        Creature h(hopper, EAST);
        world.place(h,0,0);

        for(int i = 0; i <= 15; i++)
        {
            world.turn(i, true);
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

    try {
        cout << "*** Darwin 150x150 ***" << endl;
        srand(0);

        World world(150,150);

        for(int i = 0; i < 20; i++){
            int pos = rand() % (150*150);
            int dir = (int) (rand() % 4);
            world.place(Creature(hopper, dir), pos/150, pos%150);
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % 150;
            int dir = (int) (rand() % 4);
            world.place(Creature(food, dir),pos/150, pos%150);
        }

        for(int i = 0; i < 40; i++){
            int pos = rand() % 150;
            int dir = (int) (rand() % 4);
            world.place(Creature(trap, dir),pos/150, pos%150);
        }

        for(int i = 0; i < 20; i++){
            int pos = rand() % 150;
            int dir = (int) (rand() % 4);
            world.place(Creature(rover, dir),pos/150, pos%150);
        }

        for(int i = 0; i <= 12; i++){
            world.turn(i, true);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Arena 3x8 ***" << endl;
        World world(3, 8);
        
        Creature c1(trap, SOUTH);
        Creature c2(trap, EAST);
        Creature c3(trap, NORTH);
        Creature c4(trap, EAST);
        Creature c5(hopper, EAST);

        world.place(c1, 0, 3);
        world.place(c2, 0, 4);
        world.place(c3, 2, 3);
        world.place(c4, 2, 4);
        world.place(c5, 1, 0);


        for (int i = 0; i < 10; i++) {
            world.turn(i, true);
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Fod Walk East 4x4 ***" << endl;
        World world(4, 4);
        world.place(Creature(hopper, EAST), 0, 0);
        world.place(Creature(hopper, EAST), 1, 0);
        world.place(Creature(hopper, EAST), 2, 0);
        world.place(Creature(hopper, EAST), 3, 0);
        const int NUM_MOVES = 5;
        for (int i = 0; i < NUM_MOVES; ++i) {
          world.turn(i, true);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

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
        w.place(r1, 0, 0);
        Creature h1(hopper, 1);
        w.place(h1, 0, 1);
        Creature h2(hopper, 2);
        w.place(h2, 1, 0);
        Creature h3(hopper, 3);
        w.place(h3, 1, 1);
        
        for(int i = 0; i <= 5; i++)
        {
          w.turn(i, true);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
