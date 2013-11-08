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
    #define east   0
    #define south  1
    #define west   2
    #define north  3
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
        int rows = 25;
        int columns=25;
        int foods=3;
        int traps=3;
        int hoppers=3;
        int rovers=3;        
        srand(0);
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
                  
  // END OF MY TESTS         

    return 0;}
