// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
name: Seung Youp Baek
eid: sb32676
csid: sb32676
email: bsy6766@gmail.com
course: CS371p 10am

name: Kyeong Su Park
eid: ksp499
csid: ksp499
email: ksp499@gmail.com
*/

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

#define NORTH 1
#define WEST 0
#define SOUTH 3
#define EAST 2

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
	Species foodSpecie('f');
	foodSpecie.pushInstruction("left");
	foodSpecie.pushInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species hopSpecie('h');
	hopSpecie.pushInstruction("hop");
	hopSpecie.pushInstruction("go 0");

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
	Species roverSpecie('r');
	roverSpecie.pushInstruction("if_enemy 9");
	roverSpecie.pushInstruction("if_empty 7");
	roverSpecie.pushInstruction("if_random 5");
	roverSpecie.pushInstruction("left");
	roverSpecie.pushInstruction("go 0");
	roverSpecie.pushInstruction("right");
	roverSpecie.pushInstruction("go 0");
	roverSpecie.pushInstruction("hop");
	roverSpecie.pushInstruction("go 0");
	roverSpecie.pushInstruction("infect");
	roverSpecie.pushInstruction("go 0");
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
	Species trapSpecie('t');
	trapSpecie.pushInstruction("if_enemy 3");
	trapSpecie.pushInstruction("left");
	trapSpecie.pushInstruction("go 0");
	trapSpecie.pushInstruction("infect");
	trapSpecie.pushInstruction("go 0");

	
	// ----
	// best
	// ----
	/*
	?????
    Use your own best here
	*/

    //at least 200 lines of test
    try {
        cout << "*** Darwin 100x100 with everyone ***" << endl;
        srand(0);
        //init map
        Grid map(100, 100);

        for(int i = 0; i<10; i++){
            Creature food(rand()%4, &foodSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(food, randPos%100, randPos/100);
        }
        for(int i = 0; i<10; i++){
            Creature hopper(rand()%4, &hopSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(hopper, randPos%100, randPos/100);
        }
        for(int i = 0; i<10; i++){
            Creature rover(rand()%4, &roverSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(rover, randPos%100, randPos/100);
        }  
        for(int i = 0; i<10; i++){
            Creature trap(rand()%4, &trapSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(trap, randPos%100, randPos/100);
        }  
        for(int i = 0; i<10; i++){
            Creature best(rand()%4, &bestSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(best, randPos%100, randPos/100);
        }
        map.printMap(0);

        for(int i = 1; i<=100; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2500 (50x50), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 100 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try{
        cout << "*** Darwin 50x50 with hoppers ***" << endl;
        srand(0);
        //init map
        Grid map(50, 50);

        for(int i = 0; i<50; i++){
            Creature hopper(rand()%4, &hopSpecie);
            int randPos = rand() % 2500;
            map.setCreaturePos(hopper, randPos%50, randPos/50);
        }
        map.printMap(0);

        for(int i = 1; i<=100; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2500 (50x50), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        50 Hopper
        Simulate 100 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 100x100 with everyone ***" << endl;
        srand(0);
        //init map
        Grid map(100, 100);

        for(int i = 0; i<5; i++){
            Creature food(rand()%4, &foodSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(food, randPos%100, randPos/100);
        }
        for(int i = 0; i<10; i++){
            Creature hopper(rand()%4, &hopSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(hopper, randPos%100, randPos/100);
        }
        for(int i = 0; i<10; i++){
            Creature rover(rand()%4, &roverSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(rover, randPos%100, randPos/100);
        }  
        for(int i = 0; i<5; i++){
            Creature trap(rand()%4, &trapSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(trap, randPos%100, randPos/100);
        }  
        for(int i = 0; i<20; i++){
            Creature best(rand()%4, &bestSpecie);
            int randPos = rand() % 10000;
            map.setCreaturePos(best, randPos%100, randPos/100);
        }
        map.printMap(0);

        for(int i = 1; i<=200; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2500 (50x50), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        20 Best
        Simulate 200 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
        cout << "*** Darwin 5X5 with rover and best ***" << endl;
        srand(0);
        //init map
        Grid map(5, 5);

        for(int i = 0; i<1; i++){
            Creature rover(rand()%4, &roverSpecie);
            int randPos = rand() % 25;
            map.setCreaturePos(rover, randPos%5, randPos/5);
        }
        for(int i = 0; i<1; i++){
            Creature best(rand()%4, &bestSpecie);
            int randPos = rand() % 25;
            map.setCreaturePos(best, randPos%5, randPos/5);
        }
        map.printMap(0);

        for(int i = 1; i<=1000; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 25 (5x5), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        1 Rover
        1 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 44x65 with rover and best ***" << endl;
        srand(0);
        //init map
        Grid map(44, 65);

        for(int i = 0; i<15; i++){
            Creature rover(rand()%4, &roverSpecie);
            int randPos = rand() % 2860;
            map.setCreaturePos(rover, randPos%44, randPos%65);
        }
        for(int i = 0; i<15; i++){
            Creature best(rand()%4, &bestSpecie);
            int randPos = rand() % 2860;
            map.setCreaturePos(best, randPos%44, randPos%65);
        }
        map.printMap(0);

        for(int i = 1; i<=648; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 2860 (44x65), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        15 Rover
        15 Best
        Simulate 648 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
        cout << "*** Darwin 73x12 with rover and best with foods ***" << endl;
        srand(0);
        //init map
        Grid map(73, 12);

        for(int i = 0; i<5; i++){
            Creature food(rand()%4, &foodSpecie);
            int randPos = rand() % 876;
            map.setCreaturePos(food, randPos%73, randPos%12);
        }
        for(int i = 0; i<5; i++){
            Creature rover(rand()%4, &roverSpecie);
            int randPos = rand() % 876;
            map.setCreaturePos(rover, randPos%73, randPos%12);
        }
        for(int i = 0; i<5; i++){
            Creature best(rand()%4, &bestSpecie);
            int randPos = rand() % 876;
            map.setCreaturePos(best, randPos%73, randPos%12);
        }
        map.printMap(0);

        for(int i = 1; i<=475; i++){
            map.nextTurn();
            if(i < 10)
                map.printMap(i);
            else{
                if(i % 100 == 0)
                    map.printMap(i);
            }
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 876 (73x12), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        5 food
        5 Rover
        5 Best
        Simulate 475 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...500).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
