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
#include <sstream>  // istringtstream, ostringstream
#include <string>

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

    Species food = Species("f");
    food.addInstruction("left");
    food.addInstruction("go 0");

    
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopper = Species("h");
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

    Species rover = Species("r");
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

    Species trap = Species("t");
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
    
    //----
    //best
    //----
    
    /*
     0: if_enemy 6
     1: if_empty 5
     2: if_wall 8
     3: right
     4: hop
     5: go 0
     
     6: infect
     7: go 0
     
     8: right
     9: if_enemy 15
     10: if_wall 19
     11: hop
     12: if_enemy 17 
     13: right
     14: go 21
     
     15: infect
     16: go 9
     
     17: infect
     18: go 12
     
     19: right
     20: go 0
     
     21: if_enemy 27
     22: if_empty 25
     23: if_wall 29
     24: right
     25: hop
     26: go 21
    
     27: infect
     28: go 21
     
     29: left
     30: if_enemy 36
     31: if_wall 40
     32 hop
     33: if_enemy 38
     34: left
     35: go 0
     
     36: infect
     37: go 30
     
     38: infect
     39: go 33
     
     40: left
     41: go 21
     
     */
    
    Species best = Species("b");
    best.addInstruction("if_enemy 6");
    best.addInstruction("if_empty 4");
    best.addInstruction("if_wall 8");
    best.addInstruction("right");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    
    best.addInstruction("infect");
    best.addInstruction("go 0");
    
    best.addInstruction("right");
    best.addInstruction("if_enemy 15");
    best.addInstruction("if_wall 19");
    best.addInstruction("hop");
    best.addInstruction("if_enemy 17");
    best.addInstruction("right");
    best.addInstruction("go 21");
    best.addInstruction("infect");
    best.addInstruction("go 9");
    best.addInstruction("infect");
    best.addInstruction("go 12");
    best.addInstruction("right");
    best.addInstruction("go 0");
    
    best.addInstruction("if_enemy 27");
    best.addInstruction("if_empty 25");
    best.addInstruction("if_wall 29");
    best.addInstruction("right");
    best.addInstruction("hop");
    best.addInstruction("go 21");
    best.addInstruction("infect");
    best.addInstruction("go 21");
    best.addInstruction("left");
    best.addInstruction("if_enemy 36");
    best.addInstruction("if_wall 40");
    best.addInstruction("hop");
    best.addInstruction("if_enemy 38");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 30");
    best.addInstruction("infect");
    best.addInstruction("go 33");
    best.addInstruction("left");
    best.addInstruction("go 21");
    
    
    
    // ----------
    // darwin 8x8
    // ----------

/*    try {
        cout << "*** Darwin 8x8 ***" << endl;
	Darwin x = Darwin(8, 8);*/
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
/*        Creature foodC1 = Creature(food, 2, true);
	Creature hopperC1 = Creature(hopper, 1, true);
	Creature hopperC2 = Creature(hopper, 2, true);
	Creature hopperC3 = Creature(hopper, 3, true);
	Creature hopperC4 = Creature(hopper, 0, true);
        Creature foodC2 = Creature(food, 1, true);
	
	x.addCreature(foodC1, 0, 0);
	x.addCreature(hopperC1, 3, 3);
	x.addCreature(hopperC2, 3, 4);
	x.addCreature(hopperC3, 4, 4);
	x.addCreature(hopperC4, 4, 3);
	x.addCreature(foodC2, 7, 7);

	ostringstream w;
	
	x.printBoard(w);
	
	for(int i = 0; i < 5; i++){
	  x.run_game();
	  x.printBoard(w);
	}  
	
	cout << w.str();
      }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}*/

    
    // ----------
    // darwin 15x15
    // ----------        
        
      try {
        cout << "*** Darwin 15x15 ***" << endl;
	Darwin x = Darwin(15, 15);
        /*
        15x15 Darwin
        Food,   facing east,  at (0, 0)
        Food,   facing north,  at (7, 11)
        Hopper, facing north, at (5, 5)
        Hopper, facing east,  at (3, 4)
        Hopper, facing west, at (8, 4)
        Rover, facing north, at (14, 4)
        Rover, facing south, at (1, 9)
        Trap,   facing south, at (7, 7)
        Simulate 20 moves.
        Print every grid.
        */
        
	Creature foodC1 = Creature(food, 2, true);
	Creature foodC2 = Creature(food, 1, true);
	Creature hopperC1 = Creature(hopper, 1, true);
	Creature hopperC2 = Creature(hopper, 2, true);
	Creature hopperC3 = Creature(hopper, 0, true);      
	Creature roverC1 = Creature(rover, 1, true);
	Creature roverC2 = Creature(rover, 3, true);
	Creature trapC1 = Creature(trap, 3, true);
	
	x.addCreature(foodC1, 0, 0);
	x.addCreature(foodC2, 7, 11);
	x.addCreature(hopperC1, 5, 5);
	x.addCreature(hopperC2, 3, 4);
	x.addCreature(hopperC3, 8, 4);
	x.addCreature(roverC1, 14, 4);
	x.addCreature(roverC2, 1, 9);
	x.addCreature(trapC1, 7, 7);
	
	ostringstream w;	
	x.printBoard(w);
	
	for(int i = 0; i < 20; i++){
	  x.run_game();
	  x.printBoard(w);
	}  
	
	cout << w.str();
      }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}//~31 lines
        
        
    // ----------
    // darwin 7x9
    // ----------

/*    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);*/
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
/*	Darwin x = Darwin(7, 9); 
	Creature trapC1 = Creature(trap, 3, true);
	Creature hopperC1 = Creature(hopper, 2, true);
	Creature roverC1 = Creature(rover, 1, true);
	Creature trapC2 = Creature(trap, 0, true);
	
	x.addCreature(trapC1, 0, 0);
	x.addCreature(hopperC1, 3, 2);
	x.addCreature(roverC1, 5, 4);
	x.addCreature(trapC2, 6, 8);
	
	ostringstream w;
	
	x.printBoard(w);
	
	for(int i = 0; i < 5; i++){
	  x.run_game();
	  x.printBoard(w);
	} 
	
	cout << w.str();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}*/
   
    // ----------
    // darwin 10x10
    // ----------        
        
      try {
        cout << "*** Darwin 10x10 ***" << endl;
	Darwin x = Darwin(10, 10);
        /*
        10x10 Darwin
        Food,   facing east,  at (0, 0)
        Food,   facing east,  at (9, 9)
        Food,   facing north, at (7, 7)
        Hopper, facing north, at (1, 1)
        Hopper, facing east,  at (3, 4)
        Rover, facing south, at (4, 4)
        Trap, facing west,  at (4, 3)
        Simulate 50 moves.
        Print first 5 then print every 5th grid.
        */
        
	Creature foodC1 = Creature(food, 2, true);
	Creature foodC2 = Creature(food, 2, true);
	Creature foodC3 = Creature(food, 1, true);
	Creature hopperC1 = Creature(hopper, 1, true);
	Creature hopperC2 = Creature(hopper, 2, true);        
	Creature roverC1 = Creature(rover, 3, true);
	Creature trapC1 = Creature(trap, 1, true);
	
	x.addCreature(foodC1, 0, 0);
	x.addCreature(foodC2, 9, 9);
	x.addCreature(foodC2, 7, 7);
	x.addCreature(hopperC1, 1, 1);
	x.addCreature(hopperC2, 3, 4);
	x.addCreature(roverC1, 4, 4);
	x.addCreature(trapC1, 4, 3);
	
	ostringstream w;	
	x.printBoard(w);
	
	for(int i = 1; i <= 50; i++){
	  x.run_game();
	  if(i <= 5 || (i % 5 == 0)){
	    ostringstream w;
	    x.printBoard(w);
	    cout << w.str();
	  } 
	}
      }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}//~31 lines   
   
   
    // ----------
    // darwin 15x9
    // ----------

    try {
        cout << "*** Darwin 15x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Trap,   facing south, at (13, 5)
        Trap,   facing south, at (6, 8)
        Trap,   facing west,  at (2, 3)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (12, 1)
        Rover,  facing north, at (5, 4)
        Simulate 15 moves.
        Print first 5 grids then every 5.
        */
	Darwin x = Darwin(15, 9); 
	Creature trapC1 = Creature(trap, 3, true);
	Creature trapC2 = Creature(trap, 3, true);
	Creature trapC3 = Creature(trap, 3, true);
	Creature trapC4 = Creature(trap, 0, true);
	Creature hopperC1 = Creature(hopper, 2, true);
	Creature roverC1 = Creature(rover, 1, true);	
	Creature roverC2 = Creature(rover, 1, true);
	
	x.addCreature(trapC1, 0, 0);
	x.addCreature(trapC2, 13, 5);
	x.addCreature(trapC3, 6, 8);	
	x.addCreature(trapC4, 2, 3);	
	x.addCreature(hopperC1, 3, 2);
	x.addCreature(roverC1, 12, 1);
	x.addCreature(roverC2, 5, 4);
	
	for(int i = 1; i <= 15; i++){
	  x.run_game();
	  if(i <= 5 || (i % 5 == 0)){
	    ostringstream w;
	    x.printBoard(w);
	    cout << w.str();
	  } 
	
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}//~30

    // ------------
    // darwin 35x35
    // ------------

    try {
        cout << "*** Darwin 35x35 ***" << endl;
        srand(0); 
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 1225 (35X35), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        15 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 600 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 50th grid after that (i.e. 50, 100, 150...600).
        */ 
	Darwin dar = Darwin(35, 35);

	for(int i = 0; i < 15; i++){//food
	  int ran = rand() % 1225;
	  int x = ran / 35;
	  int y = ran % 35;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(food, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Hopper
	  int ran = rand() % 1225;
	  int x = ran / 35;
	  int y = ran % 35;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(hopper, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Rover
	  int ran = rand() % 1225;
	  int x = ran / 35;
	  int y = ran % 35;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(rover, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Trap
	  int ran = rand() % 1225;
	  int x = ran / 35;
	  int y = ran % 35;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(trap, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 1; i <= 600; i++){
	  dar.run_game();
	  if(i <= 10 || (i % 50 == 0)){
	    ostringstream w;
	    dar.printBoard(w);
	    cout << w.str();
	  }
	}
	
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}//~55

    // ------------
    // darwin 25x25
    // ------------

   try {
        cout << "*** Darwin 25x25 ***" << endl;
        srand(0); 
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 625 (25X25), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        5 Food
        5 Hopper
        5 Rover
        5 Trap
        5 Best
        Simulate 400 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 50th grid after that (i.e. 50, 100, 150...400).
        */ 
	Darwin dar = Darwin(25, 25);

	for(int i = 0; i < 5; i++){//food
	  int ran = rand() % 625;
	  int x = ran / 25;
	  int y = ran % 25;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(food, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 5; i++){//Hopper
	  	  int ran = rand() % 625;
	  int x = ran / 25;
	  int y = ran % 25;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(hopper, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 5; i++){//Rover
	  int ran = rand() % 625;
	  int x = ran / 25;
	  int y = ran % 25;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(rover, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 0; i < 5; i++){//Trap
	  int ran = rand() % 625;
	  int x = ran / 25;
	  int y = ran % 25;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(trap, dir, true);
	  dar.addCreature(f, x, y);	  
	}  
	
	for(int i = 1; i <= 400; i++){
	  dar.run_game();
	  if(i <= 10 || (i % 50 == 0)){
	    ostringstream w;
	    dar.printBoard(w);
	    cout << w.str();
	  }
	  
	}
	
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}//~56

    // ------------
    // darwin 72x72
    // without best
    // ------------

 /*   try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);*/
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
        Print every 100th grid after that (i.e. 100, 200, 300...1000). */
         
/*	Darwin dar = Darwin(72, 72);

	for(int i = 0; i < 10; i++){//food
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(food, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Hopper
	  	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(hopper, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Rover
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(rover, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 0; i < 10; i++){//Trap
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(trap, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 1; i <= 1000; i++){
	  dar.run_game();
	  if(i <= 10 || (i % 100 == 0)){
	    ostringstream w;
	    dar.printBoard(w);
	    cout << w.str();
	  }
	  
	}
	
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        */
    // ------------
    // darwin 72x72
    // with best
    // ------------

/*    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);*/
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
	
/*	Darwin dar = Darwin(72, 72);

	for(int i = 0; i < 10; i++){//food
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(food, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Hopper
	  	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(hopper, dir, true);
	  dar.addCreature(f, x, y);
	}
	
	for(int i = 0; i < 10; i++){//Rover
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(rover, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 0; i < 10; i++){//Trap
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(trap, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 0; i < 10; i++){//Trap
	  int ran = rand() % 5184;
	  int x = ran / 72;
	  int y = ran % 72;
	  int dir = rand() % 4;
	  
	  Creature f = Creature(best, dir, true);
	  dar.addCreature(f, x, y);	  
	}
	
	for(int i = 1; i <= 1000; i++){
	  dar.run_game();
	  if(i <= 10 || (i % 100 == 0)){
	    ostringstream w;
	    dar.printBoard(w);
	    cout << w.str();
	  }
	  
	}
	
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    */

    // ----------
    // darwin 3x10
    // acceptance test from ericsu
    // ----------

/*    try {
        cout << "*** Darwin 3x10 ***" << endl;
        srand(0);*/
        /*
	  3x10 Darwin
	  Trap, facing south, at (2, 6)
	  Hopper, facing north, at (2, 7)
	  Rover, facing west, at (0, 0)
	  Trap, facing north, at (9, 9)
	  Simulate 10 moves.
	  Print every grid.
	*/
/*	
	Creature  t1 = Creature(trap, 3, true);
	Creature  h1 = Creature(hopper, 1, true);
	Creature  r1 = Creature(rover, 0, true);
	Creature  t2 = Creature(trap, 1, true);

	
        Darwin world = Darwin(3, 10);
        world.addCreature(t1, 2, 6);
        world.addCreature(h1, 2, 7);
        world.addCreature(r1, 0, 0);
        world.addCreature(t2, 2, 9);
        
        for(int q = 0; q<10; q++) {
	    ostringstream w;
	    world.printBoard(w);
	    cout << w.str();
            world.run_game();
        }
        
        ostringstream w;
	world.printBoard(w);
	cout << w.str();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}	//~26*/
        
        return 0;}
