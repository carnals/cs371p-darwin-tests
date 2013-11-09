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
using namespace std;



enum directions{ west = 0, north = 1, east =2, south =3};
// 0:west, 1:north, 2:east, 3:south.

// ----
// main
// ----
void generateRandomValues(int rows, int cols, int&r, int&c, int&d){
        int val = rand() % (rows * cols);
        r = val / cols;
        c = val % cols;
        d = rand() % 4;
        }

int main () {


        Species food;
        food.addInstruction("left", -1);
        food.addInstruction("go", 0);

        Species hopper;
        hopper.addInstruction("hop", -1);
        hopper.addInstruction("go", 0);

        Species trap;
        trap.addInstruction("if_enemy", 3);
        trap.addInstruction("left", -1);
        trap.addInstruction("go", 0);
        trap.addInstruction("infect", -1);
        trap.addInstruction("go", 0);
    
        Species rover;
        rover.addInstruction("if_enemy", 9);
        rover.addInstruction("if_empty", 7);
        rover.addInstruction("if_random", 5);
        rover.addInstruction("left", -1);
        rover.addInstruction("go", 0);
        rover.addInstruction("right", -1);
        rover.addInstruction("go", 0);
        rover.addInstruction("hop", -1);
        rover.addInstruction("go", 0);
        rover.addInstruction("infect", -1);
        rover.addInstruction("go", 0);




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
    10: go 11
    11: if_enemy 9
    12: left
    13: go 14
    14: if_enemy 9
    15: right
    16: go 0

     */

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

     //-----
     //Best
     //-----

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
    10: go 11
    11: if_enemy 9
    12: left
    13: go 14
    14: if_enemy 9
    15: right
    16: go 0

     */

    // ----------
    // darwin 8x8
    // ----------

     // 0:west, 1:north, 2:east, 3:south.
    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);


        Darwin board(8,8,5);

        Creature f1("food", east, food);
        Creature f2("food", north, food);
        Creature h1("hopper", north, hopper);
        Creature h2("hopper", east, hopper);
        Creature h3("hopper", south, hopper);
        Creature h4("hopper", west, hopper);
        // Creature f3("food" , north, food);

        board.addCreature(f1,0,0);
        board.addCreature(h1,3,3);
        board.addCreature(h2,3,4);
        board.addCreature(h3,4,4);
        board.addCreature(h4,4,3);
        board.addCreature(f2,7,7);



        cout << "Turn = 0." << endl;
        board.printBoard();
        cout <<endl;
        int turn = 0;
        while(turn < 5)
        {
            board.Run(turn);
            cout << "Turn = " << turn+1 << "." << endl;
            board.printBoard();
            cout << endl;
            turn++;
        }



        // Food,   facing east,  at (0, 0)
        // Hopper, facing north, at (3, 3)
        // Hopper, facing east,  at (3, 4)
        // Hopper, facing south, at (4, 4)
        // Hopper, facing west,  at (4, 3)
        // Food,   facing north, at (7, 7)
        // Print every grid.
        
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
        
        Darwin board(7,9,5);



        Creature t1("trap", south, trap);
        Creature h1("hopper", east, hopper);
        Creature r1("rover", north, rover);
        Creature t2("trap", west, trap);

       
        board.addCreature(t1,0,0);
        board.addCreature(h1,3,2);
        board.addCreature(r1,5,4);
        board.addCreature(t2,6,8);

        cout << "Turn = 0." << endl;
        board.printBoard();
        cout <<endl;
        for(int i = 0; i< 5; i++)
        {
            board.Run(i);
            cout << "Turn = " << i+1 << "." << endl;
            board.printBoard();
            cout << endl;
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
        cout << "*** Darwin 72x72 Without Best ***" << endl;

            Darwin board(72,72,1000);

        int temp = rand()%5184;
        Creature f1("food", rand()%4, food);
        board.addCreature(f1,temp/72, temp%72);
        temp = rand()%5184;
        Creature f2("food", rand()%4, food);
        board.addCreature(f2,temp/72, temp%72);
        temp = rand()%5184;
        Creature f3("food", rand()%4, food);
        board.addCreature(f3,temp/72, temp%72);
        temp = rand()%5184;
        Creature f4("food", rand()%4, food);
        board.addCreature(f4,temp/72, temp%72);
        temp = rand()%5184;
        Creature f5("food", rand()%4, food);
        board.addCreature(f5,temp/72, temp%72);
        temp = rand()%5184;
        Creature f6("food", rand()%4, food);
        board.addCreature(f6,temp/72, temp%72);
        temp = rand()%5184;
        Creature f7("food", rand()%4, food);
        board.addCreature(f7,temp/72, temp%72);
        temp = rand()%5184;
        Creature f8("food", rand()%4, food);
        board.addCreature(f8,temp/72, temp%72);
        temp = rand()%5184;
        Creature f9("food", rand()%4, food);
        board.addCreature(f9,temp/72, temp%72);
        temp = rand()%5184;
        Creature f10("food", rand()%4, food);
        board.addCreature(f10,temp/72, temp%72);

        temp = rand()%5184;
        Creature h1("hopper", rand()%4, hopper);
        board.addCreature(h1,temp/72, temp%72);
        temp = rand()%5184;
        Creature h2("hopper", rand()%4, hopper);
        board.addCreature(h2,temp/72, temp%72);
        temp = rand()%5184;
        Creature h3("hopper", rand()%4, hopper);
        board.addCreature(h3,temp/72, temp%72);
        temp = rand()%5184;
        Creature h4("hopper", rand()%4, hopper);
        board.addCreature(h4,temp/72, temp%72);
        temp = rand()%5184;
        Creature h5("hopper", rand()%4, hopper);
        board.addCreature(h5,temp/72, temp%72);
        temp = rand()%5184;
        Creature h6("hopper", rand()%4, hopper);
        board.addCreature(h6,temp/72, temp%72);
        temp = rand()%5184;
        Creature h7("hopper", rand()%4, hopper);
        board.addCreature(h7,temp/72, temp%72);
        temp = rand()%5184;
        Creature h8("hopper", rand()%4, hopper);
        board.addCreature(h8,temp/72, temp%72);
        temp = rand()%5184;
        Creature h9("hopper", rand()%4, hopper);
        board.addCreature(h9,temp/72, temp%72);
        temp = rand()%5184;
        Creature h10("hopper", rand()%4, hopper);
        board.addCreature(h10,temp/72, temp%72);

        temp = rand()%5184;
        Creature r1("rover", rand()%4, rover);
        board.addCreature(r1,temp/72, temp%72);
        temp = rand()%5184;
        Creature r2("rover", rand()%4, rover);
        board.addCreature(r2,temp/72, temp%72);
        temp = rand()%5184;
        Creature r3("rover", rand()%4, rover);
        board.addCreature(r3,temp/72, temp%72);
        temp = rand()%5184;
        Creature r4("rover", rand()%4, rover);
        board.addCreature(r4,temp/72, temp%72);
        temp = rand()%5184;
        Creature r5("rover", rand()%4, rover);
        board.addCreature(r5,temp/72, temp%72);
        temp = rand()%5184;
        Creature r6("rover", rand()%4, rover);
        board.addCreature(r6,temp/72, temp%72);
        temp = rand()%5184;
        Creature r7("rover", rand()%4, rover);
        board.addCreature(r7,temp/72, temp%72);
        temp = rand()%5184;
        Creature r8("rover", rand()%4, rover);
        board.addCreature(r8,temp/72, temp%72);
        temp = rand()%5184;
        Creature r9("rover", rand()%4, rover);
        board.addCreature(r9,temp/72, temp%72);
        temp = rand()%5184;
        Creature r10("rover", rand()%4, rover);
        board.addCreature(r10,temp/72, temp%72);

        temp = rand()%5184;
        Creature t1("trap", rand()%4, trap);
        board.addCreature(t1,temp/72, temp%72);
        temp = rand()%5184;
        Creature t2("trap", rand()%4, trap);
        board.addCreature(t2,temp/72, temp%72);
        temp = rand()%5184;
        Creature t3("trap", rand()%4, trap);
        board.addCreature(t3,temp/72, temp%72);
        temp = rand()%5184;
        Creature t4("trap", rand()%4, trap);
        board.addCreature(t4,temp/72, temp%72);
        temp = rand()%5184;
        Creature t5("trap", rand()%4, trap);
        board.addCreature(t5,temp/72, temp%72);
        temp = rand()%5184;
        Creature t6("trap", rand()%4, trap);
        board.addCreature(t6,temp/72, temp%72);
        temp = rand()%5184;
        Creature t7("trap", rand()%4, trap);
        board.addCreature(t7,temp/72, temp%72);
        temp = rand()%5184;
        Creature t8("trap", rand()%4, trap);
        board.addCreature(t8,temp/72, temp%72);
        temp = rand()%5184;
        Creature t9("trap", rand()%4, trap);
        board.addCreature(t9, temp/72, temp%72);
        temp = rand()%5184;
        Creature t10("trap", rand()%4, trap);
        board.addCreature(t10,temp/72, temp%72);

        cout << "Turn = 0." << endl;
        board.printBoard();
        cout <<endl;
        for(int i = 1; i<= 1000; i++)
        {
            board.Run(i);
            if(i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 ||
                     i == 9  || i == 100 || i == 200 ||i == 300 ||i == 400 || i == 500 || i == 600 || i == 700 ||i == 800 || i == 900 ||i == 1000)
            {
                cout << "Turn = " << i << "." << endl;
                board.printBoard();
                cout << endl;
            }
        }

      }
      catch (const invalid_argument&) {
           assert(false);}
      catch (const out_of_range&) {
           assert(false);}

    // try {
    //     cout << "*** Darwin 72x72 Best ***" << endl;
    //     srand(0);
    //         Darwin board(72,72,1000);

    //     int temp = rand()%5184;
    //     Creature f1("food", rand()%4, food);
    //     board.addCreature(f1,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f2("food", rand()%4, food);
    //     board.addCreature(f2,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f3("food", rand()%4, food);
    //     board.addCreature(f3,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f4("food", rand()%4, food);
    //     board.addCreature(f4,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f5("food", rand()%4, food);
    //     board.addCreature(f5,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f6("food", rand()%4, food);
    //     board.addCreature(f6,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f7("food", rand()%4, food);
    //     board.addCreature(f7,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f8("food", rand()%4, food);
    //     board.addCreature(f8,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f9("food", rand()%4, food);
    //     board.addCreature(f9,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature f10("food", rand()%4, food);
    //     board.addCreature(f10,temp/72, temp%72);

    //     temp = rand()%5184;
    //     Creature h1("hopper", rand()%4, hopper);
    //     board.addCreature(h1,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h2("hopper", rand()%4, hopper);
    //     board.addCreature(h2,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h3("hopper", rand()%4, hopper);
    //     board.addCreature(h3,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h4("hopper", rand()%4, hopper);
    //     board.addCreature(h4,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h5("hopper", rand()%4, hopper);
    //     board.addCreature(h5,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h6("hopper", rand()%4, hopper);
    //     board.addCreature(h6,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h7("hopper", rand()%4, hopper);
    //     board.addCreature(h7,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h8("hopper", rand()%4, hopper);
    //     board.addCreature(h8,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h9("hopper", rand()%4, hopper);
    //     board.addCreature(h9,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature h10("hopper", rand()%4, hopper);
    //     board.addCreature(h10,temp/72, temp%72);

    //     temp = rand()%5184;
    //     Creature r1("rover", rand()%4, rover);
    //     board.addCreature(r1,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r2("rover", rand()%4, rover);
    //     board.addCreature(r2,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r3("rover", rand()%4, rover);
    //     board.addCreature(r3,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r4("rover", rand()%4, rover);
    //     board.addCreature(r4,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r5("rover", rand()%4, rover);
    //     board.addCreature(r5,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r6("rover", rand()%4, rover);
    //     board.addCreature(r6,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r7("rover", rand()%4, rover);
    //     board.addCreature(r7,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r8("rover", rand()%4, rover);
    //     board.addCreature(r8,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r9("rover", rand()%4, rover);
    //     board.addCreature(r9,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature r10("rover", rand()%4, rover);
    //     board.addCreature(r10,temp/72, temp%72);

    //     temp = rand()%5184;
    //     Creature t1("trap", rand()%4, trap);
    //     board.addCreature(t1,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t2("trap", rand()%4, trap);
    //     board.addCreature(t2,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t3("trap", rand()%4, trap);
    //     board.addCreature(t3,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t4("trap", rand()%4, trap);
    //     board.addCreature(t4,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t5("trap", rand()%4, trap);
    //     board.addCreature(t5,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t6("trap", rand()%4, trap);
    //     board.addCreature(t6,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t7("trap", rand()%4, trap);
    //     board.addCreature(t7,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t8("trap", rand()%4, trap);
    //     board.addCreature(t8,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t9("trap", rand()%4, trap);
    //     board.addCreature(t9, temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature t10("trap", rand()%4, trap);
    //     board.addCreature(t10,temp/72, temp%72);

    //     temp = rand()%5184;
    //     Creature b1("best", rand()%4, best);
    //     board.addCreature(b1,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b2("best", rand()%4, best);
    //     board.addCreature(b2,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b3("best", rand()%4, best);
    //     board.addCreature(b3,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b4("best", rand()%4, best);
    //     board.addCreature(b4,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b5("best", rand()%4, best);
    //     board.addCreature(b5,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b6("best", rand()%4, best);
    //     board.addCreature(b6,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b7("best", rand()%4, best);
    //     board.addCreature(b7,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b8("best", rand()%4, best);
    //     board.addCreature(b8,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b9("best", rand()%4, best);
    //     board.addCreature(b9,temp/72, temp%72);
    //     temp = rand()%5184;
    //     Creature b10("best", rand()%4, best);
    //     board.addCreature(b10,temp/72, temp%72);

    //     cout << "Turn = 0." << endl;
    //     board.printBoard();
    //     cout <<endl;
    //     for(int i = 1; i<= 1000; i++)
    //     {
    //         board.Run(i);
    //         if(i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 ||
    //                  i == 9  || i == 100 || i == 200 ||i == 300 ||i == 400 || i == 500 || i == 600 || i == 700 ||i == 800 || i == 900 ||i == 1000)
    //         {
    //             cout << "Turn = " << i << "." << endl;
    //             board.printBoard();
    //             cout << endl;
    //         }
    //     }

    //   }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

//***************************OUR TESTS*********************
//------------
// Darwin 5x5
// Acceptance Test 1
//------------
 try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);


        Darwin board(5,5,5);

        Creature f1("food", east, food);
        Creature f2("food", north, food);
        Creature h1("hopper", east, hopper);
        Creature h2("hopper", north, hopper);

        board.addCreature(f1,0,0);
        board.addCreature(h1,3,3);
        board.addCreature(h2,3,4);
        board.addCreature(f2,1,2);



        cout << "Turn = 0." << endl;
        board.printBoard();
        cout <<endl;
        int turn = 0;
        while(turn < 5)
        {
            board.Run(turn);
            cout << "Turn = " << turn+1 << "." << endl;
            board.printBoard();
            cout << endl;
            turn++;
        }



        // Food, facing east, at (0, 0)
        // Hopper, facing north, at (3, 3)
        // Hopper, facing east, at (3, 4)
        // Hopper, facing south, at (4, 4)
        // Hopper, facing west, at (4, 3)
        // Food, facing north, at (7, 7)
        // Print every grid.
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


//------------
// Darwin 16x16
// Acceptance Test 2
//------------
 try {
        cout << "*** Darwin 16x16 ***" << endl;
        srand(0);


        Darwin board(16,16,10);

        Creature f1("food", east, food);
        Creature f2("food", north, food);
        Creature h1("hopper", east, hopper);
        Creature h2("hopper", north, hopper);
        Creature f3("food", south, food);
        Creature f4("food", west, food);
        Creature h3("hopper", east, hopper);
        Creature h4("hopper", north, hopper);

        board.addCreature(f1,0,0);
        board.addCreature(h1,3,3);
        board.addCreature(h2,3,4);
        board.addCreature(f2,1,2);
        board.addCreature(f3,0,12);
        board.addCreature(h3,12,0);
        board.addCreature(h4,15,15);
        board.addCreature(f4,8,9);



        cout << "Turn = 0." << endl;
        board.printBoard();
        cout <<endl;
        int turn = 0;
        while(turn < 10)
        {
            board.Run(turn);
            cout << "Turn = " << turn+1 << "." << endl;
            board.printBoard();
            cout << endl;
            turn++;
        }



        // Food, facing east, at (0, 0)
        // Hopper, facing north, at (3, 3)
        // Hopper, facing east, at (3, 4)
        // Hopper, facing south, at (4, 4)
        // Hopper, facing west, at (4, 3)
        // Food, facing north, at (7, 7)
        // Print every grid.
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


        //********************************ensign***********************************

   try {
        cout << "*** Rover 1x1 ***" << endl;
        srand(0);
                                /*        
                                1x1 Darwin
                                Rover, facing north at (0, 0)
                                Simulate 10 moves
                                Print every move
                                */
                                Darwin d(1, 1, 10);
                                Creature c = Creature("rover", 1, rover);
                                d.addCreature(c, 0, 0);
                                cout << " Turn = 0." << endl;
                                d.printBoard();
                                for (int i = 1; i <= 10; i++){
                                        d.Run(i);
                                        cout << "Turn = " << i << "." << endl;

                                        d.printBoard();        
                    }
                }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------------------
    // Full Grid, 1 Trap 20x20
    // -------------------------

    try {
        cout << "*** Full Grid, 1 Trap 20x20 ***" << endl;
        srand(0);
                                /*        
                                20x20 Darwin
                                1 Trap, facing west at (10, 10)
                                399 Food, facing north at each location except (10, 10)
                                Simulate 50 moves
                                Print first 10 moves and every multiple of 10
                                */
                                Darwin d(20, 20, 50);
                                Creature t("trap",0,trap);
                                d.addCreature(t, 10, 10);
                                for (int i = 0; i < 20; i++){
                                        for (int j = 0; j < 20; j++){
                                                if (!(i == 10 && j == 10)){
                                                        Creature x("food", 1, food);
                                                        d.addCreature(x, i, j);
                                                }
                                        }
                                }
                                cout << " Turn = 0." << endl;
                                d.printBoard();
                                for (int i = 1; i <= 50; i++){
                                        d.Run(i);
                                        if ((i < 10) || (i % 10 == 0)) 
                                        {   
                                             cout << "Turn = " << i << "." << endl;
   
                                             d.printBoard();        
                                        }
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------------
    // Hopper Collide 10x4
    // ------------------

    try {
        cout << "*** Hopper Collide 10x4 ***" << endl;
        srand(0);
                                /*        
                                10x4 Darwin
                                4 Hoppers, facing south in each column of row 0
                                4 Hoppers, facing north in each column of row 9
                                Simulate 10 moves
                                Print every move
                                */
                                Darwin d(10, 4, 10);
                                Creature c1("hopper", 3,hopper);
                                Creature c2("hopper", 3,hopper);
                                Creature c3("hopper", 3,hopper);
                                Creature c4("hopper", 3,hopper);
                                Creature c5("hopper", 1,hopper);
                                Creature c6("hopper", 1,hopper);
                                Creature c7("hopper", 1,hopper);
                                Creature c8("hopper", 1,hopper);
                                d.addCreature(c1, 0, 0);
                                d.addCreature(c2, 0, 1);
                                d.addCreature(c3, 0, 2);
                                d.addCreature(c4, 0, 3);
                                d.addCreature(c5, 9, 0);
                                d.addCreature(c6, 9, 1);
                                d.addCreature(c7, 9, 2);
                                d.addCreature(c8, 9, 3);
                                cout << " Turn = 0." << endl;

                                d.printBoard();
                                for (int i = 1; i <= 10; i++){
                                        d.Run(i);
                                        cout << "Turn = " << i << "." << endl;

                                        d.printBoard();
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------------
    // Rover Takeover 8x8
    // ------------------

    try {
        cout << "*** Rover Takeover 8x8 ***" << endl;
        srand(0);
                                /*        
                                8x8 Darwin
                                Rover, facing south at (3, 4)
                                Food, facing south at (0, 2)
                                Food, facing south at (7, 4)
                                Food, facing south at (2, 7)
                                Food, facing north at (3, 0)
                                Food, facing north at (4, 5)
                                Food, facing north at (5, 2)
                                Food, facing north at (6, 3)
                                Simulate 100 moves
                                Print first 10 moves and multiples of 10
                                */
                                Darwin d(8, 8, 100);
                                Creature c1("rover", 3, rover);
                                Creature c2("food", 3, food);
                                Creature c3("food", 3, food);
                                Creature c4("food", 3, food);
                                Creature c5("food", 1, food);
                                Creature c6("food", 1, food);
                                Creature c7("food", 1, food);
                                Creature c8("food", 1, food);
                                d.addCreature(c1, 3, 4);
                                d.addCreature(c2, 0, 2);
                                d.addCreature(c3, 7, 4);
                                d.addCreature(c4, 2, 7);
                                d.addCreature(c5, 3, 0);
                                d.addCreature(c6, 4, 5);
                                d.addCreature(c7, 5, 2);
                                d.addCreature(c8, 6, 3);
                                cout << " Turn = 0." << endl;
                                d.printBoard();
                                for (int i = 1; i <= 100; i++){
                                        d.Run(i);
                                        if (i < 10 || i % 10 == 0)
                                        {
                                                cout << "Turn = " << i << "." << endl;
                                                d.printBoard();
                                            }
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hop Down 10x1
    // ------------------

    try {
        cout << "*** Hop Down 10x1 ***" << endl;
        srand(0);
                                /*        
                                10x1 Darwin
                                Hopper, facing south at (0, 0)
                                Simulate 9 moves
                                Print every move
                                */
                                Darwin d(10, 1,9);
                                Creature c1("hopper", 3, hopper);
                                d.addCreature(c1, 0, 0);
                                cout << " Turn = 0." << endl;

                                d.printBoard();
                                for (int i = 1; i <= 9; i++){
                                        cout << "Turn = " << i << "." << endl;
                                        d.Run(i);
                                        d.printBoard();
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hoppers Trapped 4x4
    // ------------------

    try {
        cout << "*** Hoppers Trapped 4x4 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                Darwin d(4, 4,10);
                                Creature c1("hopper", 2, hopper);
                                Creature c2("hopper", 3,hopper );
                                Creature c3("hopper", 0,hopper);
                                Creature c4("hopper", 1,hopper);
                                d.addCreature(c1, 0, 0);
                                d.addCreature(c2, 0, 1);
                                d.addCreature(c3, 1, 1);
                                d.addCreature(c4, 1, 0);
                                cout << " Turn = 0." << endl;

                                d.printBoard();
                                for (int i = 1; i <= 10; i++){
                                        d.Run(i);
                                        cout << "Turn = " << i << "." << endl;

                                        d.printBoard();
                                }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// ************************************ KBixby****************************************

        try {
        cout << "*** Darwin 2x2 Two Rovers ***" << endl;
        srand(0);
        /*
        2x2 Grid

        North Rover @ (0, 0)
        East Rover @ (1, 0)
        */
        Creature r1("rover", north, rover);
        Creature r2("rover", east, rover);
        Darwin d = Darwin(2, 2,10);
        d.addCreature(r1, 0, 0);
        d.addCreature(r2, 1, 0);
        d.printBoard();
        for (int i = 0; i < 10; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 4x4 Four Traps Four Rovers***" << endl;
        srand(0);
        /*
        4x4 Grid
        South Trap @ (0, 0)
        North Trap @ (3, 3)
        East Trap @ (3, 0)
        West Trap @ (0, 3)
        North Rover @ (2, 1)
        East Rover @ (1, 2)
        South Rover @ (2, 2)
        West Rover @ (1, 1)
        */
        Creature t1("trap", south, trap);
        Creature t2("trap", north, trap);
        Creature t3("trap", east, trap);
        Creature t4("trap", west, trap);
        Creature r1("rover", north, rover);
        Creature r2("rover", east, rover);
        Creature r3("rover", south, rover);
        Creature r4("rover", west, rover);



        Darwin d = Darwin(4, 4, 10);
        d.addCreature(t1, 0, 0);
        d.addCreature(t2, 3, 3);
        d.addCreature(t3, 3, 0);
        d.addCreature(t4, 0, 3);
        d.addCreature(r1, 2, 1);
        d.addCreature(r2, 1, 2);
        d.addCreature(r3, 2, 2);
        d.addCreature(r4, 1, 1);
        d.printBoard();
        for (int i = 0; i < 10; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 10x4 Four Traps Four Rovers***" << endl;
        srand(0);
        /*
        10x4 Grid
        South Trap @ (0, 0)
        North Trap @ (7, 3)
        East Trap @ (3, 0)
        West Trap @ (0, 3)
        North Rover @ (4, 1)
        East Rover @ (1, 2)
        South Rover @ (2, 2)
        West Rover @ (0, 1)
        */

        Creature t1("trap", south, trap);
        Creature t2("trap", north, trap);
        Creature t3("trap", east, trap);
        Creature t4("trap", west, trap);
        Creature r1("rover", north, rover);
        Creature r2("rover", east, rover);
        Creature r3("rover", south, rover);
        Creature r4("rover", west, rover);

        Darwin d (10, 4,10);
        d.addCreature(t1, 0, 0);
        d.addCreature(t2, 7, 3);
        d.addCreature(t3, 3, 0);
        d.addCreature(t4, 0, 3);
        d.addCreature(r1, 4, 1);
        d.addCreature(r2, 1, 2);
        d.addCreature(r3, 2, 2);
        d.addCreature(r4, 0, 1);
        d.printBoard();
        for (int i = 0; i < 10; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 23x17 ***" << endl;
        srand(0);
        /*
        23x17 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d(23, 17, 100);
        int size = 23 * 17;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.addCreature(Creature("rover", dir, rover), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.addCreature(Creature("hopper", dir, hopper), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 17;
            int c = cell % 17;
            int dir = rand() % 4;
            d.addCreature(Creature("trap", dir, trap), r, c);
        }
        d.printBoard();
        for (int i = 0; i < 100; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 19x23 ***" << endl;
        srand(0);
        /*
        19x23 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d (19, 23,100);
        int size = 19 * 23;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.addCreature(Creature("rover", dir, rover), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.addCreature(Creature("hopper", dir, hopper), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 23;
            int c = cell % 23;
            int dir = rand() % 4;
            d.addCreature(Creature("trap", dir, trap), r, c);
        }
        d.printBoard();
        for (int i = 0; i < 100; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 37x43 ***" << endl;
        srand(0);
        /*
        37x43 Grid
        13 Randomly placed rovers
        11 Randomly placed hoppers
        7  Randomly places traps
        */
        Darwin d = Darwin(37, 43, 100);
        int size = 37 * 43;
        for (int i = 0; i < 13; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.addCreature(Creature("rover", dir,rover), r, c);
        }
        for (int i = 0; i < 11; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.addCreature(Creature("hopper", dir, hopper), r, c);
        }
        for (int i = 0; i < 7; i++) {
            int cell = rand() % size;
            int r = cell / 43;
            int c = cell % 43;
            int dir = rand() % 4;
            d.addCreature(Creature("trap", dir, trap), r, c);
        }
        d.printBoard();
        for (int i = 0; i < 100; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


  // *******************************Eliya's Tests************************************

    try {
        cout << "*** Darwin 10X10 Test I ***" << endl;
        srand(0);
        Darwin d (10, 10, 6);
        Creature f1("food", south, food);
        Creature h1("hopper", north, hopper);
        Creature h2("hopper", south, hopper);
        Creature h3("hopper", east, hopper);
        Creature h4("hopper", east, hopper);
        Creature r5("rover", south, rover);

        d.addCreature(f1, 5, 5);
        d.addCreature(h1, 3, 5);
        d.addCreature(h2, 2, 6);
        d.addCreature(h3, 1, 9);
        d.addCreature(h4, 8, 1);
        d.addCreature(r5, 2, 5);
        for (int i = 0; i < 6; i++) {
            d.printBoard();
            d.Run(i);
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    try {
        cout << "*** Darwin 20X20 Test II ***" << endl;
        srand(0);
        Darwin d = Darwin(20, 20, 4);

        for(int i = 1; i < 9; i++){
            int randPos = rand() % 400; 
            int r = randPos / 20;
            int c = randPos % 20; 
            int dir = rand() % 4;
            d.addCreature(Creature("hopper", dir, hopper), r, c);
        }

        for(int i = 1; i < 3; i++){
            int randPos = rand() % 400; 
            int r = randPos / 20;
            int c = randPos % 20; 
            int dir = rand() % 4;
            d.addCreature(Creature("rover", dir, rover), r, c);
        }

        for(int i = 1; i < 5; i++){
            int randPos = rand() % 400; 
            int r = randPos / 20;
            int c = randPos % 20; 
            int dir = rand() % 4;
            d.addCreature(Creature("food", dir, food), r, c);
        }

        d.printBoard();
        for (int i = 0; i < 4; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // *************************** KVWADE's Tests*****************************

    try {
         /*
        1x10 Darwin
        Hopper,   facing east, at (0, 0)
        Trap, facing east,  at (0, 5)
        Rover,  facing WEST, at (0, 9)
        Simulate 5 moves.
        Print every grid.
        */

        cout << "*** KVWADETEST1 1x10 ***" << endl;
        srand(0);
        Darwin d(1, 10, 5);

        Creature h1("hopper", east, hopper);
        Creature t1("trap", east, trap);
        Creature r1("rover", west, rover);

        d.addCreature(h1, 0, 0);
        d.addCreature(t1, 0, 5);
        d.addCreature(r1, 0, 9);

        d.printBoard();
        for (int i = 0; i < 5; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
         /*
        10x1 Darwin
        Hopper,   facing south, at (0, 0)
        Trap, facing east,  at (5, 0)
        Rover,  facing north, at (0, 9)
        Simulate 5 moves.
        Print every grid.
        */
        cout << "*** KVWADETEST2 10x1 ***" << endl;
        srand(0);
        Darwin d(10, 1, 5);
        Creature h1("hopper", south, hopper);
        Creature t1("trap", east, trap);
        Creature r1("rover", north, rover);
        d.addCreature(h1, 0, 0);
        d.addCreature(t1, 5, 0);
        d.addCreature(r1, 9, 0);

        d.printBoard();
        for (int i = 0; i < 5; i++) {
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    //**************************************nlaz's Test***************************

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
        Darwin d(5,5,5);
        Creature t1("trap", west, trap);
        Creature h1("hopper", north, hopper);
        Creature h2("hopper", east, hopper);
        Creature h3("hopper", south, hopper);
        Creature f1("food", north, food);
        d.addCreature(t1, 4, 0);
        d.addCreature(h1, 4, 1);
        d.addCreature(h2, 4, 2);
        d.addCreature(h3, 4, 3);
        d.addCreature(f1, 4, 4);
        d.printBoard();
        for (int i = 0; i < 5; i++){
            d.Run(i);
            d.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



                return 0;}
