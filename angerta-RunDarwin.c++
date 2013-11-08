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
//#include "Creature.h"
//#include "Species.h"

// ----
// main
// ----

int main () {
    using namespace std;

    enum direction {WEST,NORTH,EAST,SOUTH};

    // ----
    // food
    // ----

     Species food = Species("food");
     food.add_instruction("left");
     food.add_instruction("go", 0);
    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

     Species hopper = Species("hopper");
     hopper.add_instruction("hop");
     hopper.add_instruction("go", 0);

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----
     Species rover = Species("rover");
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
     rover.add_instruction("go",0);


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


        // -----
    // rover
    // -----
     Species best = Species("best");
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
     rover.add_instruction("go",0);
     

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

     Species trap = Species("trap");
     trap.add_instruction("if_enemy", 3);
     trap.add_instruction("left");
     trap.add_instruction("go", 0);
     trap.add_instruction("infect");
     trap.add_instruction("go", 0);

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
        
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin world = Darwin();

        world.init_world(8,8);
        //world.print_World();

        Creature FE = Creature(food, EAST);
        Creature FN = Creature(food, NORTH);


        Creature HN = Creature(hopper, NORTH);
        Creature HE = Creature(hopper, EAST);
        Creature HS = Creature(hopper, SOUTH);
        Creature HW = Creature(hopper, WEST);

        world.add_creature(HN,3,3);
        world.add_creature(HE,3,4);
        world.add_creature(HS,4,4);
        world.add_creature(HW,4,3);
        world.add_creature(FE,0,0);
        world.add_creature(FN,7,7);

        world.print_World();   

        for (int i = 0; i < 5; ++i)
        {
            world.run_World_turn();
            world.print_World();
        }


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


        Darwin world = Darwin();

        world.init_world(7,9);
        //world.print_World();

        Creature TS = Creature(trap, SOUTH);
        Creature HEE = Creature(hopper, EAST);
        Creature RN = Creature(rover, NORTH);
        Creature TW = Creature(trap, SOUTH);


        world.add_creature(TS,0,0);
        world.add_creature(HEE,3,2);
        world.add_creature(RN,5,4);
        world.add_creature(TW,6,8);

        world.print_World();   

        for (int i = 0; i < 5; ++i)
        {
            world.run_World_turn();
            world.print_World();
        }
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
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
        Darwin world = Darwin();
        world.init_world(72,72);

        for (int i = 0; i < 40; ++i)
        {
            int loc = rand()%5184;
            int x = loc/72;
            int y = loc - x*72;
            int dir = rand();
            if(i<10)
             world.add_creature(Creature(food,dir%4),x,y);
             if(i<20)
             world.add_creature(Creature(hopper,dir%4),x,y);
             if(i<30)
             world.add_creature(Creature(rover,dir%4),x,y);
             if(i<40)
             world.add_creature(Creature(trap,dir%4),x,y);
        }


        for (int i = 0; i < 1000; ++i)
        {

            if(i<10||i%100==0)
            world.print_World();
            world.run_World_turn();
        }
        world.print_World();
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
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  try {
        cout << "*** Darwin 1x30 Big Trap ***" << endl;
        srand(0);
        Darwin world = Darwin();
        world.init_world(1,30);
        world.add_creature(Creature(rover,EAST),0,0);
        world.add_creature(Creature(hopper,WEST),0,29);


        for (int i = 0; i < 20; ++i)
        {

            world.print_World();
            world.run_World_turn();
        }
        world.print_World();
        /*
        in a darwin world of 1 by 30
        create a rover at the left side
        and a hopper on the right most side facing each other
        simulate 20 moves
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

  try {
        cout << "*** Darwin 4x10 without Best ***" << endl;
        srand(0);
        Darwin world = Darwin();
        world.init_world(4,10);
        world.add_creature(Creature(trap,EAST),0,0);
        world.add_creature(Creature(trap,EAST),1,0);
        world.add_creature(Creature(trap,EAST),2,0);
        world.add_creature(Creature(trap,EAST),3,0);
        world.add_creature(Creature(trap,EAST),0,1);
        world.add_creature(Creature(trap,EAST),1,1);
        world.add_creature(Creature(trap,EAST),2,1);
        world.add_creature(Creature(trap,EAST),3,1);

        world.add_creature(Creature(rover,EAST),0,9);
        world.add_creature(Creature(rover,EAST),1,9);
        world.add_creature(Creature(rover,EAST),2,9);
        world.add_creature(Creature(rover,EAST),3,9);


        for (int i = 0; i < 20; ++i)
        {

            world.print_World();
            world.run_World_turn();
        }
        world.print_World();
        /*
        in a darwin world of 4 by 10
        8 traps all on the left hand side as much as possible all facing east
        create 4 rovers all on the right side all facing east
        simulate 20 moves
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}





// //Test from aaronv92
//             try {
//         cout << "*** Darwin 3X3 ***" << endl;
//         srand(0);
//         Darwin game = Darwin();
//         game.init_world(3,3);

//         game.add_creature(Creature(hopper,NORTH), 0, 0);

//         game.add_creature(Creature(hopper,NORTH), 0, 1);

//         game.add_creature(Creature(hopper,NORTH), 0, 2);

//         game.add_creature(Creature(hopper,NORTH), 1, 0);

//         game.add_creature(Creature(hopper,NORTH), 1, 1);

//         game.add_creature(Creature(hopper,NORTH), 1, 2);

//         game.add_creature(Creature(trap,NORTH), 2, 0);

//         game.add_creature(Creature(trap,NORTH), 2, 1);

//         game.add_creature(Creature(rover,NORTH), 2, 2);

//         for(int i = 0; i <= 5; i++){
//             cout << "Turn = " << i << "." << endl;
//             game.print_World();
//             game.run_World_turn();
//             //cout << endl;
//         }
//         //cout << endl;

//         /*
//         3X3 Darwin
//         Hopper, facing north, at (0, 0)
//         Hopper, facing north, at (0, 1)
//         Hopper, facing north, at (0, 2)
//         Hopper, facing north, at (1, 0)
//         Hopper, facing north, at (1, 1)
//         Hopper, facing north, at (1, 2)
//         Trap, facing north, at (2, 0)
//         Trap, facing north, at (2, 1)
//         Rover, facing north, at (2, 2)

//         Simulate 5 moves.
//         Print every grid.
//         */
//         }
//     catch (const invalid_argument&) {
//         assert(false);}
//     catch (const out_of_range&) {
//         assert(false);}





// //daraoke

//         try {
//                 cout << "*** Darwin 10x15 ***" << endl;
//                 srand(0);
        
//                 /*
//          10x15 Darwin
//          Trap,   facing south, at (0, 0)
//          Hopper, facing east,  at (3, 2)
//          Rover,  facing north, at (5, 4)
//          Trap,   facing north, at (9,11)
//          Food,   facing west,  at (8,8)
//          Rover,  facing east,  at (2,10)
//          Hopper, facing south, at (1, 3)
//          Trap,   facing west,  at (6, 8)
//          Simulate 20 moves.
//          Print every 5th move
//          */
        
//                 Darwin world3 = Darwin();
//                 world3.init_world(10, 15);
//                 world3.add_creature(Creature(trap, SOUTH), 0, 0);
//                 world3.add_creature(Creature(hopper, EAST), 3, 2);
//                 world3.add_creature(Creature(rover, NORTH), 5, 4);
//         world3.add_creature(Creature(trap, NORTH), 9, 11);
//         world3.add_creature(Creature(food, WEST), 8,8);
//         world3.add_creature(Creature(rover, EAST), 2, 10);
//         world3.add_creature(Creature(hopper, SOUTH), 1, 3);
//                 world3.add_creature(Creature(trap, WEST), 6, 8);
        
//                 for (int i = 0; i < 20; i++) {
//                         if (i % 5 == 0) world3.print_World();
//                         world3.run_World_turn();
//                 }
//     }
//         catch (const invalid_argument&) {
//                 assert(false);}
//         catch (const out_of_range&) {
//                 assert(false);}


// //ensign

//     try {
//         cout << "*** Rover Takeover 8x8 ***" << endl;
//         srand(0);
//                                 /*        
//                                 8x8 Darwin
//                                 Rover, facing south at (3, 4)
//                                 Food, facing south at (0, 2)
//                                 Food, facing south at (7, 4)
//                                 Food, facing south at (2, 7)
//                                 Food, facing north at (3, 0)
//                                 Food, facing north at (4, 5)
//                                 Food, facing north at (5, 2)
//                                 Food, facing north at (6, 3)
//                                 Simulate 100 moves
//                                 Print first 10 moves and multiples of 10
//                                 */
//                                 Darwin d = Darwin();
//                                 d.init_world(8,8);
//                                 Creature c1(rover, 3);
//                                 Creature c2(food, 3);
//                                 Creature c3(food, 3);
//                                 Creature c4(food, 3);
//                                 Creature c5(food, 1);
//                                 Creature c6(food, 1);
//                                 Creature c7(food, 1);
//                                 Creature c8(food, 1);
//                                 d.add_creature(c1, 3, 4);
//                                 d.add_creature(c2, 0, 2);
//                                 d.add_creature(c3, 7, 4);
//                                 d.add_creature(c4, 2, 7);
//                                 d.add_creature(c5, 3, 0);
//                                 d.add_creature(c6, 4, 5);
//                                 d.add_creature(c7, 5, 2);
//                                 d.add_creature(c8, 6, 3);
//                                 d.print_World();
//                                 for (int i = 1; i <= 100; i++){
//                                         d.run_World_turn();
//                                         if (i < 10 || i % 10 == 0)
//                                                 d.print_World();
//                                 }
//     }
//     catch (const invalid_argument&) {
//         assert(false);}
//     catch (const out_of_range&) {
//         assert(false);}



// //kbixby
//   try {
//         cout << "*** Darwin 19x23 ***" << endl;
//         srand(0);
//         /*
//         19x23 Grid
//         13 Randomly placed rovers
//         11 Randomly placed hoppers
//         7  Randomly places traps
//         */
//         Darwin d = Darwin();
//         d.init_world(19,23);
//         int size = 19 * 23;
//         for (int i = 0; i < 13; i++) {
//             int cell = rand() % size;
//             int r = cell / 23;
//             int c = cell % 23;
//             int dir = rand() % 4;
//             d.add_creature(Creature(rover, dir), r, c);
//         }
//         for (int i = 0; i < 11; i++) {
//             int cell = rand() % size;
//             int r = cell / 23;
//             int c = cell % 23;
//             int dir = rand() % 4;
//             d.add_creature(Creature(hopper, dir), r, c);
//         }
//         for (int i = 0; i < 7; i++) {
//             int cell = rand() % size;
//             int r = cell / 23;
//             int c = cell % 23;
//             int dir = rand() % 4;
//             d.add_creature(Creature(trap, dir), r, c);
//         }
//         d.print_World();
//         for (int i = 0; i < 100; i++) {
//             d.run_World_turn();
//             d.print_World();
//         }
//     }
//     catch (const invalid_argument&) {
//         assert(false);}
//     catch (const out_of_range&) {
//         assert(false);}


// //rbrooks
//     try 
//     {
//         /*
//             make a 2x20 world
//             1 hopper on top row 0,0 facing east
//             1 rovers on second row 1,0 facing east
//             4 foods on tird row col 16-19 facing WEst
//             4 foods on bottom row col 16-19  facing west
//             20 years
//             print every 
//             the rover and hopper race to food.
//             rover plays dirty
//         */
//         cout << "*** Darwin 2x20 Drag Race ***" << endl;
//         srand(0);
//         Darwin test = Darwin();
//         test.init_world(2,20);
        
//         Creature crit_hopper1 = Creature(hopper,EAST );
//         test.add_creature(crit_hopper1,0,0);
//         Creature crit_rover1 = Creature(rover, EAST);
//         test.add_creature(crit_rover1,1,0);

//         Creature crit_food1 = Creature(food,WEST);
//         test.add_creature(crit_food1, 0,19 );

//         Creature crit_food2 = Creature(food, WEST);
//         test.add_creature(crit_food2,0,18 );

//         Creature crit_food3 = Creature(food, WEST);
//         test.add_creature(crit_food3,0,17);

//         Creature crit_food4 = Creature(food, WEST);
//         test.add_creature(crit_food4,0,16);
        
//         Creature crit_food5 = Creature(food, WEST);
//         test.add_creature(crit_food5,1,19);
        
//         Creature crit_food6 = Creature(food, WEST);
//         test.add_creature(crit_food6,1,18);
        
//         Creature crit_food7 = Creature(food, WEST);
//         test.add_creature(crit_food7,1,17);
        
//         Creature crit_food8 = Creature(food, WEST);
//         test.add_creature(crit_food8,1,16);
        


//         int i;
//         std::cout << "    Turn: 0" << std::endl;
//         test.print_World();

//         for(i = 1; i <= 20; ++i)
//         {

//           test.run_World_turn();
//           std::cout << "    Turn: " << i << std::endl;
//           test.print_World();
//         }    
//     }
//     catch (const invalid_argument&) {
//         assert(false);}
//     catch (const out_of_range&) {
//         assert(false);}



    return 0;}