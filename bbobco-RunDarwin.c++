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
    
    species food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    // ------
    // hopper
    // ------

    /*
0: hop
1: go 0
*/
    species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    
    //change rover's right instruction to left for BEST
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
     species rover('r');
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
     species trap('t');
     trap.addInstruction("if_enemy 3");
     trap.addInstruction("left");
     trap.addInstruction("go 0");
     trap.addInstruction("infect");
     trap.addInstruction("go 0");
     
     /* WILL BE USING RANDOMLY GENERATED DIRECTIONS,
     need to know i have this in my .h file for directions:
    #define west   0
    #define north  1
    #define east   2
    #define south  3
     */
      try{
        cout << "*** Darwin 10X10 Test 1***" << endl;
        srand(0);
        game g1(10, 10);
        creature c1 (2, 3,south,trap);
        creature c2 (3,1,north,rover);
        creature c3 (0, 0,south,hopper);
        creature c4 (0, 1,east,hopper);
        creature c5 (7, 7,east,food);
        creature c6 (4, 9,south,rover);
        g1.addCreature(c1);
        g1.addCreature(c2);
        g1.addCreature(c3);
        g1.addCreature(c4);
        g1.addCreature(c5);
        g1.addCreature(c6);
        
        g1.simulate(25,1); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
   

     
      try{
        cout << "*** Darwin 25X25 Test 2 ***" << endl;
        srand(0);
        int rows = 25;
        int columns=25;
        int foods=3;
        int traps=3;
        int hoppers=3;
        int rovers=3;        
        game g2(rows, columns);
        
        //need to use this so creatures remain in our scope outside of the loop where they are defined
        creature creatures[12];
        int count=0;

        for(int i=0;i<foods;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), food);
          g2.addCreature(creatures[count]);
          count++;
        }
        
        for(int i=0;i<traps;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), trap);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<hoppers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), hopper);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<rovers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), rover);
          g2.addCreature(creatures[count]);
          count++;
        }        
        
        g2.simulate(15,1); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
     

      try{
        cout << "*** Darwin 60X10 Test 3 ***" << endl;
        srand(0);
        int rows = 60;
        int columns=10;
        int foods=2;
        int traps=25;
        int hoppers=1;
        int rovers=1;        
        srand(0);
        game g2(rows, columns);
        
        //need to use this so creatures remain in our scope outside of the loop where they are defined
        creature creatures[2+25+1+1];
        int count=0;

        for(int i=0;i<foods;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), food);
          g2.addCreature(creatures[count]);
          count++;
        }
        
        for(int i=0;i<traps;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), trap);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<hoppers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), hopper);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<rovers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), rover);
          g2.addCreature(creatures[count]);
          count++;
        }        
        
        g2.simulate(15,1); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   
        
      try{
        cout << "*** Darwin 1X15 Test 4 ***" << endl;
        srand(0);
        int rows = 1;
        int columns=15;
        int foods=3;
        int traps=0;
        int hoppers=5;
        int rovers=1;        
        srand(0);
        game g2(rows, columns);
        
        //need to use this so creatures remain in our scope outside of the loop where they are defined
        creature creatures[3+0+5+1];
        int count=0;

        for(int i=0;i<foods;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), food);
          g2.addCreature(creatures[count]);
          count++;
        }
        
        for(int i=0;i<traps;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), trap);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<hoppers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), hopper);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<rovers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), rover);
          g2.addCreature(creatures[count]);
          count++;
        }        
        
        g2.simulate(30,1); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  


      try{
        cout << "*** Darwin 12X1 Test 5 ***" << endl;
        srand(0);
        int rows = 12;
        int columns=1;
        int foods=1;
        int traps=1;
        int hoppers=1;
        int rovers=1;        
        srand(0);
        game g2(rows, columns);
        
        //need to use this so creatures remain in our scope outside of the loop where they are defined
        creature creatures[4];
        int count=0;

        for(int i=0;i<foods;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), food);
          g2.addCreature(creatures[count]);
          count++;
        }
        
        for(int i=0;i<traps;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), trap);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<hoppers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), hopper);
          g2.addCreature(creatures[count]);
          count++;
        }
        for(int i=0;i<rovers;i++){
          int r = rand()%(rows*columns);
          creatures[count] =  creature(r/columns, r%columns, (int)(rand()%4), rover);
          g2.addCreature(creatures[count]);
          count++;
        }        
        
        g2.simulate(15,1); // 25 is number of turns, 2nd arg is how frequently I will print the board (1 is every turn, 2 is every other turn ETC)


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
                  

//OTHER PEOPLS TESTS HERE
//END OF OTHER PEOPLES TESTS

           
    try {
    /*
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
        game g (8,8);
        creature h1 (4,1,1,hopper);
        creature h2 (4,3,1,hopper);
//        creature f1 (5,5,0,'f');
        creature r1(0,0,0,rover);
//        creature t1(4,4,2,'t');
        g.addCreature(r1);
        g.addCreature(h2);
        g.addCreature(h1);
//        g.addCreature(f1);
//        g.addCreature(t1);
    //    g.printBoard(0);
        g.simulate(40,1);
        */
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
    /*
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
     */
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
    /*
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        */
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

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
    /*
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
    */
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
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
