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
    
    Species food = Species('f');
    food.add_instruction("left");
    food.add_instruction("go 0");
    
    // ------
    // hopper
    // ------
    
    /*
     0: hop
     1: go 0
     */
    Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");
    
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
    Species rover = Species('r');
    rover.add_instruction("if_enemy 9");
    rover.add_instruction("if_empty 7");
    rover.add_instruction("if_random 5");
    rover.add_instruction("left");
    rover.add_instruction("go 0");
    rover.add_instruction("right");
    rover.add_instruction("go 0");
    rover.add_instruction("hop");
    rover.add_instruction("go 0");
    rover.add_instruction("infect");
    rover.add_instruction("go 0");
    
    
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
    
    Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");
    
    // ----
    // best
    // ----

    /*
    ?????
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
        Grid grid(8,8);
        
        Creature f1(food,'E');
        grid.add_creature(f1,0,0);
        Creature h1(hopper,'N');
        grid.add_creature(h1,3,3);
        Creature h2(hopper,'E');
        grid.add_creature(h2,3,4);
        Creature h3(hopper,'S');
        grid.add_creature(h3,4,4);
        Creature h4(hopper,'W');
        grid.add_creature(h4,4,3);
        Creature f2(food,'N');
        grid.add_creature(f2,7,7);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
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
        Grid grid(7,9);
        Creature t1(trap,'S');
        grid.add_creature(t1, 0, 0);
        Creature h1(hopper,'E');
        grid.add_creature(h1, 3, 2);
        Creature r1(rover,'N');
        grid.add_creature(r1, 5, 4);
        Creature t2(trap,'W');
        grid.add_creature(t2, 6, 8);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
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
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        /*
         1x1 Darwin
         Hopper, facing east,  at (0, 0)
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(1,1);
        Creature h1(hopper,'E');
        grid.add_creature(h1, 0, 0);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        /*
         2x2 Darwin
         Trap,   facing south, at (0, 0)
         Hopper, facing east,  at (0, 1)
         Rover,  facing north, at (1, 0)
         Trap,   facing west,  at (1, 1)
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(2,2);
        Creature t1(trap,'S');
        grid.add_creature(t1, 0, 0);
        Creature h1(hopper,'E');
        grid.add_creature(h1, 0, 1);
        Creature r1(rover,'N');
        grid.add_creature(r1, 1, 0);
        Creature t2(trap,'W');
        grid.add_creature(t2, 1, 1);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);
        /*
         4x4 Darwin
         Trap,   facing west, at (0, 0)
         Food,   facing north,  at (1, 1)
         Rover,  facing east, at (2, 2)
         Trap,   facing south,  at (3, 3)
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(4,4);
        Creature t1(trap,'W');
        grid.add_creature(t1, 0, 0);
        Creature f1(food,'N');
        grid.add_creature(f1, 1, 1);
        Creature r1(rover,'E');
        grid.add_creature(r1, 2, 2);
        Creature t2(trap,'S');
        grid.add_creature(t2, 3, 3);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);
        /*
         4x4 Darwin
         Trap,   facing west, at (0, 0)
         Food,   facing north,  at (1, 1)
         Food,  facing east, at (2, 2)
         Food,   facing south,  at (3, 3)
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(4,4);
        Creature t1(trap,'W');
        grid.add_creature(t1, 0, 0);
        Creature f1(food,'N');
        grid.add_creature(f1, 1, 1);
        Creature f2(food,'E');
        grid.add_creature(f2, 2, 2);
        Creature f3(food,'S');
        grid.add_creature(f3, 3, 3);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        /*
         4x4 Darwin
         Trap,   facing west, at (0, 0)
         Hopper,   facing north,  at (0, 1)
         Hopper,  facing east, at (0, 2)
         Hopper,   facing south,  at (0, 3)
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(5,5);
        Creature t1(trap,'W');
        grid.add_creature(t1, 0, 0);
        Creature h1(hopper,'N');
        grid.add_creature(h1, 0, 1);
        Creature h2(hopper,'E');
        grid.add_creature(h2, 0, 2);
        Creature h3(hopper,'S');
        grid.add_creature(h3, 0, 3);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}






    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        /*
         4x4 Darwin
         Trap,   facing west, at (4, 0)
         Hopper,   facing north,  at (4, 1)
         Hopper,  facing east, at (4, 2)
         Hopper,   facing south,  at (4, 3)
         Food,  face north, at (4,4);
         Simulate 5 moves.
         Print every grid.
         */
        Grid grid(5,5);
        Creature t1(trap,'W');
        grid.add_creature(t1, 4, 0);
        Creature h1(hopper,'N');
        grid.add_creature(h1, 4, 1);
        Creature h2(hopper,'E');
        grid.add_creature(h2, 4, 2);
        Creature h3(hopper,'S');
        grid.add_creature(h3, 4, 3);
        Creature f1(food,'N');
        grid.add_creature(f1,4,4);
        grid.print_grid();
        for (int i = 0; i < 5; i++){
            grid.simulate();
            grid.print_grid();
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
         int N = 72;
         Grid grid(N,N);
         for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int posX = pos / N;
            int posY = pos % N;
            int dir = rand() % 4;
            char dirc;
            switch (dir){
                case 0:
                    dirc = 'W';
                    break;
                case 1:
                    dirc = 'N';
                    break;
                case 2:
                    dirc = 'E';
                    break;
                case 3:
                    dirc = 'S';
                    break;
            }
            Creature f(food,dirc);
            grid.add_creature(f,posX,posY);
         }

         for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int posX = pos / N;
            int posY = pos % N;
            int dir = rand() % 4;
            char dirc;
            switch (dir){
                case 0:
                    dirc = 'W';
                    break;
                case 1:
                    dirc = 'N';
                    break;
                case 2:
                    dirc = 'E';
                    break;
                case 3:
                    dirc = 'S';
                    break;
            }
            Creature h(hopper,dirc);
            grid.add_creature(h,posX,posY);
         }

         for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int posX = pos / N;
            int posY = pos % N;
            int dir = rand() % 4;
            char dirc;
            switch (dir){
                case 0:
                    dirc = 'W';
                    break;
                case 1:
                    dirc = 'N';
                    break;
                case 2:
                    dirc = 'E';
                    break;
                case 3:
                    dirc = 'S';
                    break;
            }
            Creature r(rover,dirc);
            grid.add_creature(r,posX,posY);
         }


         for (int i = 0; i < 10; i++){
            int pos = rand() % (N*N);
            int posX = pos / N;
            int posY = pos % N;
            int dir = rand() % 4;
            char dirc;
            switch (dir){
                case 0:
                    dirc = 'W';
                    break;
                case 1:
                    dirc = 'N';
                    break;
                case 2:
                    dirc = 'E';
                    break;
                case 3:
                    dirc = 'S';
                    break;
            }
            Creature t(trap,dirc);
            grid.add_creature(t,posX,posY);
         }
         grid.print_grid();
         for (int i = 0; i < 1000; i++){
            grid.simulate();
            if (i < 10 || i % 100 == 99){
                grid.print_grid();
            }
         }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);
    }
    
    // ------------
    // darwin 72x72
    // with best
    // ------------
    
    // try {
    //     cout << "*** Darwin 72x72 with Best ***" << endl;
    //     srand(0);
    //     /*
    //      Randomly place the following creatures facing randomly.
    //      Call rand(), mod it with 5184 (72x72), and use that for the position
    //      in a row-major order grid.
    //      Call rand() again, mod it with 4 and use that for it's direction with
    //      the ordering: 0:west, 1:north, 2:east, 3:south.
    //      Do that for each kind of creature.
    //      10 Food
    //      10 Hopper
    //      10 Rover
    //      10 Trap
    //      10 Best
    //      Simulate 1000 moves.
    //      Best MUST outnumber ALL other species for the bonus pts.
    //      Print the first 10 grids          (i.e. 0, 1, 2...9).
    //      Print every 100th grid after that (i.e. 100, 200, 300...1000).
    //      */
    //      int N = 72;
    //      Grid grid(N,N);
    //      for (int i = 0; i < 10; i++){
    //         int pos = rand() % (N*N);
    //         int posX = pos / N;
    //         int posY = pos % N;
    //         int dir = rand() % 4;
    //         char dirc;
    //         switch (dir){
    //             case 0:
    //                 dirc = 'W';
    //                 break;
    //             case 1:
    //                 dirc = 'N';
    //                 break;
    //             case 2:
    //                 dirc = 'E';
    //                 break;
    //             case 3:
    //                 dirc = 'S';
    //                 break;
    //         }
    //         Creature f(food,dirc);
    //         grid.add_creature(f,posX,posY);
    //      }

    //      for (int i = 0; i < 10; i++){
    //         int pos = rand() % (N*N);
    //         int posX = pos / N;
    //         int posY = pos % N;
    //         int dir = rand() % 4;
    //         char dirc;
    //         switch (dir){
    //             case 0:
    //                 dirc = 'W';
    //                 break;
    //             case 1:
    //                 dirc = 'N';
    //                 break;
    //             case 2:
    //                 dirc = 'E';
    //                 break;
    //             case 3:
    //                 dirc = 'S';
    //                 break;
    //         }
    //         Creature h(hopper,dirc);
    //         grid.add_creature(h,posX,posY);
    //      }

    //      for (int i = 0; i < 10; i++){
    //         int pos = rand() % (N*N);
    //         int posX = pos / N;
    //         int posY = pos % N;
    //         int dir = rand() % 4;
    //         char dirc;
    //         switch (dir){
    //             case 0:
    //                 dirc = 'W';
    //                 break;
    //             case 1:
    //                 dirc = 'N';
    //                 break;
    //             case 2:
    //                 dirc = 'E';
    //                 break;
    //             case 3:
    //                 dirc = 'S';
    //                 break;
    //         }
    //         Creature r(rover,dirc);
    //         grid.add_creature(r,posX,posY);
    //      }


    //      for (int i = 0; i < 10; i++){
    //         int pos = rand() % (N*N);
    //         int posX = pos / N;
    //         int posY = pos % N;
    //         int dir = rand() % 4;
    //         char dirc;
    //         switch (dir){
    //             case 0:
    //                 dirc = 'W';
    //                 break;
    //             case 1:
    //                 dirc = 'N';
    //                 break;
    //             case 2:
    //                 dirc = 'E';
    //                 break;
    //             case 3:
    //                 dirc = 'S';
    //                 break;
    //         }
    //         Creature t(trap,dirc);
    //         grid.add_creature(t,posX,posY);
    //      }
    //      for (int i = 0; i < 10; i++){
    //         int pos = rand() % (N*N);
    //         int posX = pos / N;
    //         int posY = pos % N;
    //         int dir = rand() % 4;
    //         char dirc;
    //         switch (dir){
    //             case 0:
    //                 dirc = 'W';
    //                 break;
    //             case 1:
    //                 dirc = 'N';
    //                 break;
    //             case 2:
    //                 dirc = 'E';
    //                 break;
    //             case 3:
    //                 dirc = 'S';
    //                 break;
    //         }
    //         Creature b(best,dirc);
    //         grid.add_creature(b,posX,posY);
    //      }
    //      grid.print_grid();
    //      for (int i = 0; i < 1000; i++){
    //         grid.simulate();
    //         if (i < 10 || i % 100 == 99){
    //             grid.print_grid();
    //             grid.print_count();
    //         }
    //      }
    // }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}
    
    // return 0;}
