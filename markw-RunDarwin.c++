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
#define private public
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

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
        Grid g(8,8);
        g.placeCreature(food, E, 0, 0);
        g.placeCreature(hopper, N, 3, 3);
        g.placeCreature(hopper, E, 3, 4);
        g.placeCreature(hopper, S, 4, 4);
        g.placeCreature(hopper, W, 4, 3);
        g.placeCreature(food, N, 7, 7);
        int i = 0;
        for (i = 0; i <= 5; i++)
        {
            g.printGrid();
            g.doTurn();
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
        Grid g(7,9);
        Creature t1(trap,S);
        Creature h1(hopper,E);
        Creature r1(rover,N);
        Creature t2(trap,W);

        g.placeCreature(t1, 0, 0);
        g.placeCreature(h1, 3, 2);
        g.placeCreature(r1, 5, 4);
        g.placeCreature(t2, 6, 8);

        for(int i = 0; i <= 5; i++){
            g.printGrid();
            g.doTurn();
                    }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    //// ------------
    //// darwin 72x72
    //// without best
    //// ------------

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

        Grid g(72,72);

        vector<Creature> creatures(40);
        int creatureIndex = 0;
        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(food,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(hopper,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(rover,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(trap,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for (int i = 0; i <= 1000; i++){
            if(i < 10){
                g.printGrid();
                            }
            else if(i % 100 == 0){
                g.printGrid();
                            }
            g.doTurn();
        }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    //// ------------
    //// darwin 72x72
    //// with best
    //// ------------

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
        Grid g(72,72);

        vector<Creature> creatures(50);
        int creatureIndex = 0;
        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(food,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(hopper,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(rover,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(trap,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (72*72);
            Direction dir = (Direction) (rand() % 4);
            creatures[creatureIndex] = Creature(best,dir);
            g.placeCreature(creatures[creatureIndex],pos/72, pos%72);
            creatureIndex++;
        }


        for(int i = 0; i <= 1000; i++){
            if(i < 10){
                g.printGrid();
                            }
            else if(i % 100 == 0){
                g.printGrid();
                            }
            g.doTurn();
        }

        g.printSpeciesCount();
    }
  catch (const invalid_argument&) {
    assert(false);}
  catch (const out_of_range&) {
    assert(false);}


    // --------------
    // darwin 150x150
    // --------------

    try {
        cout << "*** Darwin 150x150 ***" << endl;
        srand(0);

        Grid g(150,150);

        for(int i = 0; i < 20; i++){
            int pos = rand() % (150*150);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(hopper,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % 150;
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(food,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 40; i++){
            int pos = rand() % 150;
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(trap,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 20; i++){
            int pos = rand() % 150;
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(rover,dir,pos/150, pos%150);
        }

        for(int i = 0; i <= 12; i++){
            g.printGrid();
                        g.doTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // --------------
    // darwin 15x150
    // --------------

    try {
        cout << "*** Darwin 15x150 ***" << endl;
        srand(0);

        Grid g(15,150);

        for(int i = 0; i < 5; i++){
            int pos = rand() % (15*150);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(hopper,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 10; i++){
            int pos = rand() % (15*150);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(food,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 5; i++){
            int pos = rand() % (15*150);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(trap,dir,pos/150, pos%150);
        }

        for(int i = 0; i < 20; i++){
            int pos = rand() % (15*150);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(rover,dir,pos/150, pos%150);
        }

        for(int i = 0; i <= 20; i++){
            g.printGrid();
                        g.doTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // --------------
    // darwin 123x43
    // --------------

    try {
        cout << "*** Darwin 123x43 ***" << endl;
        srand(0);

        Grid g(123,43);

        for(int i = 0; i < 6; i++){
            int pos = rand() % (123*43);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(hopper,dir,pos/123, pos%43);
        }

        for(int i = 0; i < 3; i++){
            int pos = rand() % (123*43);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(food,dir,pos/123, pos%43);
        }

        for(int i = 0; i < 16; i++){
            int pos = rand() % (123*43);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(trap,dir,pos/123, pos%43);
        }

        for(int i = 0; i < 14; i++){
            int pos = rand() % (123*43);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(rover,dir,pos/123, pos%43);
        }

        for(int i = 0; i <= 200; i++){
            g.printGrid();
                        g.doTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // --------------
    // darwin 200x200
    // --------------

    try {
        cout << "*** Darwin 200x200 ***" << endl;
        srand(0);

        Grid g(200,200);

        for(int i = 0; i < 20; i++){
            int pos = rand() % (200*200);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(hopper,dir,pos/200, pos%200);
        }

        for(int i = 0; i < 20; i++){
            int pos = rand() % (200*200);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(food,dir,pos/200, pos%200);
        }

        for(int i = 0; i < 40; i++){
            int pos = rand() % (200*200);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(trap,dir,pos/200, pos%200);
        }

        for(int i = 0; i < 60; i++){
            int pos = rand() % (200*200);
            Direction dir = (Direction) (rand() % 4);
            g.placeCreature(rover,dir,pos/200, pos%200);
        }

        for(int i = 0; i <= 500; i++){
            g.printGrid();
                        g.doTurn();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    
    return 0;
}
