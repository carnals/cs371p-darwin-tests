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
    // test
    // ----

    /*
     0: if_wall 3
     1: hop
     2: go 0
     3: left
     4: go 0
    */
    Species testDNA("T");
    Instruction ifwall3("if_wall 3");
    Instruction hop("hop");
    Instruction left("left");
    Instruction go0("go 0");

    testDNA.addInstruction(ifwall3);
    testDNA.addInstruction(hop);
    testDNA.addInstruction(go0);
    testDNA.addInstruction(left);
    testDNA.addInstruction(go0);

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    Species foodDNA("f");
    foodDNA.addInstruction(left);
    foodDNA.addInstruction(go0);
	
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopperDNA("h");
    hopperDNA.addInstruction(hop);
    hopperDNA.addInstruction(go0);

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
    Instruction ifenemy9("if_enemy 9");
    Instruction ifempty7("if_empty 7");
    Instruction ifrandom5("if_random 5");
    Instruction right("right");
    Instruction infect("infect");
    Species roverDNA("r");
    roverDNA.addInstruction(ifenemy9);
    roverDNA.addInstruction(ifempty7);
    roverDNA.addInstruction(ifrandom5);
    roverDNA.addInstruction(left);
    roverDNA.addInstruction(go0);
    roverDNA.addInstruction(right);
    roverDNA.addInstruction(go0);
    roverDNA.addInstruction(hop);
    roverDNA.addInstruction(go0);
    roverDNA.addInstruction(infect);
    roverDNA.addInstruction(go0);

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
    Instruction ifenemy3("if_enemy 3");

    Species trapperDNA("t");
    trapperDNA.addInstruction(ifenemy3);
    trapperDNA.addInstruction(left);
    trapperDNA.addInstruction(go0);
    trapperDNA.addInstruction(infect);
    trapperDNA.addInstruction(go0);

    // ----
    // best
    // ----

    /*
     0: if_enemy 10
     1: if_empty 8
     2: if_wall 6
     3: right
     4: right	
     5: go 0
     6: infect
     7: go 0
     8: hop
     9: go0
    10: left
    11: left
    12: go0 
    */

    Instruction ifwall10("if_wall 10");
    Instruction ifenemy6("if_enemy 6");
    Instruction ifempty8("if_empty 8");
    Species bestDNA("b");
    bestDNA.addInstruction(ifenemy6);//0
    bestDNA.addInstruction(ifempty8);//1
    bestDNA.addInstruction(ifwall10);//2
    bestDNA.addInstruction(right);//3
    bestDNA.addInstruction(right);//4
    bestDNA.addInstruction(go0);//5
    bestDNA.addInstruction(infect);//6
    bestDNA.addInstruction(go0);//7
    bestDNA.addInstruction(hop);//8
    bestDNA.addInstruction(go0);//9
    bestDNA.addInstruction(left);//10
    bestDNA.addInstruction(go0);//12

    // ----------
    // darwin 8x8
    // ----------

    try {
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

        cout << "*** Darwin 8x8 ***" << endl;
	Creature f0(foodDNA, East,0, 0);
	Creature h0(hopperDNA, North,3, 3);
	Creature h1(hopperDNA, East,3 ,4);
	Creature h2(hopperDNA, South,4 ,4);
	Creature h3(hopperDNA, West, 4, 3);
	Creature f1(foodDNA, North, 7, 7);

/*	cout << "test-------------------------" << endl;
        testDNA.printInstructions();
	cout << "food-------------------------" << endl;
	foodDNA.printInstructions();
        cout << "hopper-----------------------" << endl;
	hopperDNA.printInstructions();
        cout << "rover------------------------" << endl;
        roverDNA.printInstructions();
        cout << "trap-------------------------" << endl;
        trapDNA.printInstructions();
        cout << "best-------------------------" << endl;
        bestDNA.printInstructions();

*/
	
	DarwinWorld game(8, 8);
	
	game.addCreature(f0); 
        game.addCreature(f1);
        game.addCreature(h0);
        game.addCreature(h1);
        game.addCreature(h2);
        game.addCreature(h3);

	int numofturns = 5;
	//initial world
	game.printState();
	cout << endl;
	for(int i = 0; i < numofturns; i++){
		game.simulate();
        	game.printState();
		cout << endl;}
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
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
	srand(0);

        DarwinWorld game(7, 9);
        Creature t0(trapperDNA, South,0, 0);
        Creature h0(hopperDNA, East,3, 2);
        Creature r0(roverDNA, North,5 ,4);
        Creature t1(trapperDNA, West,6 ,8);
        game.addCreature(t0);
        game.addCreature(h0);
        game.addCreature(r0);
        game.addCreature(t1);

        int numofturns = 5;
        //initial world
        game.printState();
	cout << endl;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
                game.printState();
		cout << endl;}
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
        srand(0);

        DarwinWorld game(72, 72);

	for(int i = 0; i < 10; i++){
	  int r = rand() % 5184;
	  Creature food(foodDNA, Direction(rand() % 4), r/72, r%72);
	  game.addCreature(food);
          r = rand() % 5184;
          Creature hopper(hopperDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(hopper);	
          r = rand() % 5184;
          Creature rover(roverDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(rover);
          r = rand() % 5184;
          Creature trapper(trapperDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(trapper);} 

        //initial world
        game.printState();
        cout << endl;
	int numofturns = 1000;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
		if( (0 <= i && i <= 9) || ((i+1)%100==0)){
                  game.printState();
                  cout << endl;}}
	
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

       DarwinWorld game(72, 72);

        for(int i = 0; i < 10; i++){
          int r = rand() % 5184;
          Creature food(foodDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(food);
          r = rand() % 5184;
          Creature hopper(hopperDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(hopper);
          r = rand() % 5184;
          Creature rover(roverDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(rover);
          r = rand() % 5184;
          Creature trapper(trapperDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(trapper);
          r = rand() % 5184;
          Creature best(bestDNA, Direction(rand() % 4), r/72, r%72);
          game.addCreature(best);}

        //initial world
        game.printState();
        cout << endl;
        int numofturns = 1000;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
                if( (0 <= i && i <= 9) || ((i+1)%100==0)){
                  game.printState();
                  cout << endl;}}


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
        /*
	8x8 Darwin
	test, facing east, at (3, 7)
	Simulate 5 moves.
	Print every grid.
	*/

        Creature test(testDNA, East, 3, 7);
        //constructor
        DarwinWorld game(8,8);
        //addCreature
        game.addCreature(test);
        //simulate
        int numofturns = 5;
        //initial world
        game.printState();
        cout << endl;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
                game.printState();
                cout << endl;}

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
        food, facing west, at (1, 1)
        Rover, facing north, at (2, 1)
        Simulate 5 moves.
        Print every grid.
        */

        Creature food(foodDNA, West, 1, 1);
        Creature rover(roverDNA, North, 2, 1);
        //constructor
        DarwinWorld game (4, 4);
        //addCreature
        game.addCreature(food);
        game.addCreature(rover);
        //simulate
        int numofturns = 5;
        //initial world
        game.printState();
        cout << endl;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
                game.printState();
                cout << endl;}

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        /*
        5x5 Darwin
        Trap, facing south, at (0, 0)
        Hopper, facing east, at (0, 1)
        Rover, facing north, at (1, 0)
        Trap, facing west, at (1, 1)
        Simulate 5 moves.
        Print every grid.
        */

        Creature r0(roverDNA, East, 0, 0);
        Creature r1(roverDNA, West, 4, 4);
        Creature b0(bestDNA, South, 0, 4);
        Creature b1(bestDNA, North, 4, 0);
        //constructor
        DarwinWorld game(5, 5);
        //addCreature
        game.addCreature(r0);
        game.addCreature(r1);
        game.addCreature(b0);
        game.addCreature(b1);
        //simulate
        int numofturns = 5;
        //initial world
        game.printState();
        cout << endl;
        for(int i = 0; i < numofturns; i++){
                game.simulate();
                game.printState();
                cout << endl;}

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    return 0;}
