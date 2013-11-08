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
#include <vector>
#include <algorithm>
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

	//init creatures vector
	vector<Creatures> animals;
	Creatures F1 = Creatures(0, 0, EAST, Food);
	Creatures F2 = Creatures(7, 7, NORTH, Food);
	Creatures H1 = Creatures(3, 3, NORTH, Hopper);
	Creatures H2 = Creatures(3, 4, EAST, Hopper);
	Creatures H3 = Creatures(4, 4, SOUTH, Hopper);
	Creatures H4 = Creatures(4, 3, WEST, Hopper);
	animals.push_back(F1);
	animals.push_back(F2);
	animals.push_back(H1);
	animals.push_back(H2);
	animals.push_back(H3);
	animals.push_back(H4);
	sort(animals.begin(), animals.end());
	//map m(x, y) contains 8x8 vector of creatures
	Map board(8, 8, 0);
	//fill creatures
	board.placeCreature(F1);
	board.placeCreature(F2);
	board.placeCreature(H1);
	board.placeCreature(H2);
	board.placeCreature(H3);
	board.placeCreature(H4);
	//sort creatures - done in placeCreature

	//simulate map
    board.toString();
	simulate(5, 1, animals, board);
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
	
		vector<Creatures> animals;
		Creatures T = Creatures(0,0, SOUTH, Trap);
		Creatures H = Creatures(3,2, EAST, Hopper);
		Creatures R = Creatures(5,4, NORTH, Rover);
		Creatures T2 = Creatures(6,8,WEST, Trap);
		animals.push_back(T);
		animals.push_back(H);
		animals.push_back(R);
		animals.push_back(T2);
		sort(animals.begin(), animals.end());

		Map board(7, 9, 0);

		board.placeCreature(T);
		board.placeCreature(H);
		board.placeCreature(R);
		board.placeCreature(T2);

		cout << "TESTING: " << (&animals[1] == &board.board[3*7+2]) <<endl;

        cout<<"Turn: 0"<<endl;
        board.toString();
		simulate(5, 1, animals, board);

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

	vector<Creatures> animals;
	Map board(72,72,1);
	int i, size = 72*72;
	for(i = 0; i < 40; i++){
		int n = rand()%size;
		if(i <10){
			Creatures F(n/72, n%72, Direct_e(rand()%4), Food);
			animals.push_back(F);
			board.placeCreature(F);
		}
		else if(i <20){
			Creatures H(n/72, n%72, Direct_e(rand()%4), Hopper);
			animals.push_back(H);
			board.placeCreature(H);
		}
		else if(i<30){
			Creatures R(n/72, n%72, Direct_e(rand()%4), Rover);
			animals.push_back(R);
			board.placeCreature(R);
		}
		else{
			Creatures T(n/72, n%72, Direct_e(rand()%4), Trap);
			animals.push_back(T);
			board.placeCreature(T);
		}

	}
    cout<<"Turn: 0"<<endl;
    board.toString();
    simulate(10, 1, animals, board);
    simulate(1000, 100, animals, board);
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
        vector<Creatures> animals;
        Map board(72,72,0);
        int i, size = 72*72;
        for(i = 0; i < 50; i++){
            int n = rand()%size;
            if(i <10){
                Creatures F(n/72, n%72, Direct_e(rand()%4), Food);
                animals.push_back(F);
                board.placeCreature(F);
            }
            else if(i <20){
                Creatures H(n/72, n%72, Direct_e(rand()%4), Hopper);
                animals.push_back(H);
                board.placeCreature(H);
            }
            else if(i<30){
                Creatures R(n/72, n%72, Direct_e(rand()%4), Rover);
                animals.push_back(R);
                board.placeCreature(R);
            }
            else if(i<40){
                Creatures T(n/72, n%72, Direct_e(rand()%4), Trap);
                animals.push_back(T);
                board.placeCreature(T);
            }
            else{
                Creatures B(n/72, n%72, Direct_e(rand()%4), Best);
                animals.push_back(B);
                board.placeCreature(B);
            }
        }
        cout<<"Turn: 0"<<endl;
        board.toString();
        simulate(10, 1, animals, board);
        simulate(990, 100, animals, board);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 10x10 Test1 ***" << endl;
        srand(0);
        /*
        Do that for each kind of creature.
        9 Food
        6 Hopper
        9 Rover
        5 Trap
        Simulate 100 moves.
        print every 2 grids
        */
        
        vector<Creatures> animals;
        Creatures F = Creatures(1,1, SOUTH, Food);
        Creatures F2 = Creatures(8,8, SOUTH, Food);
        Creatures F3 = Creatures(8,9, SOUTH, Food);
        Creatures F4 = Creatures(9,8, SOUTH, Food);
        Creatures F5 = Creatures(0,1, SOUTH, Food);
        Creatures F6 = Creatures(1,0, SOUTH, Food);
        Creatures F7 = Creatures(9,4, SOUTH, Food);
        Creatures F8 = Creatures(4,1, SOUTH, Food);
        Creatures F9 = Creatures(3,2, SOUTH, Food);

        Creatures H = Creatures(4,2, EAST, Hopper);
        Creatures H2 = Creatures(2,2, EAST, Hopper);
        Creatures H3 = Creatures(4,1, EAST, Hopper);
        Creatures H4 = Creatures(1,5, EAST, Hopper);
        Creatures H5 = Creatures(1,4, EAST, Hopper);
        Creatures H6 = Creatures(3,8, EAST, Hopper);

        Creatures R = Creatures(5,4, NORTH, Rover);
        Creatures R2 = Creatures(4,5, NORTH, Rover);
        Creatures R3 = Creatures(7,7, NORTH, Rover);
        Creatures R4 = Creatures(6,4, NORTH, Rover);
        Creatures R5 = Creatures(1,4, NORTH, Rover);
        Creatures R6 = Creatures(2,4, NORTH, Rover);
        Creatures R7 = Creatures(2,9, NORTH, Rover);
        Creatures R8 = Creatures(9,2, NORTH, Rover);
        Creatures R9 = Creatures(8,1, NORTH, Rover);

        Creatures T = Creatures(0,0, SOUTH, Trap);
        Creatures T2 = Creatures(0,9, SOUTH, Trap);
        Creatures T3 = Creatures(9,0, SOUTH, Trap);
        Creatures T4 = Creatures(9,9, SOUTH, Trap);
        Creatures T5 = Creatures(5,5, SOUTH, Trap);

        animals.push_back(T);
        animals.push_back(T2);
        animals.push_back(T3);
        animals.push_back(T4);
        animals.push_back(T5);

        animals.push_back(F);
        animals.push_back(F2);
        animals.push_back(F3);
        animals.push_back(F4);
        animals.push_back(F5);
        animals.push_back(F6);
        animals.push_back(F7);
        animals.push_back(F8);
        animals.push_back(F9);

        animals.push_back(H);
        animals.push_back(H2);
        animals.push_back(H3);
        animals.push_back(H4);
        animals.push_back(H5);
        animals.push_back(H6);

        animals.push_back(R);
        animals.push_back(R2);
        animals.push_back(R3);
        animals.push_back(R4);
        animals.push_back(R5);
        animals.push_back(R6);
        animals.push_back(R7);
        animals.push_back(R8);
        animals.push_back(R9);

        sort(animals.begin(), animals.end());

        Map board(10, 10, 100);

        board.placeCreature(T);
        board.placeCreature(T2);
        board.placeCreature(T3);
        board.placeCreature(T4);
        board.placeCreature(T5);
        board.placeCreature(F);
        board.placeCreature(F2);
        board.placeCreature(F3);
        board.placeCreature(F4);
        board.placeCreature(F5);
        board.placeCreature(F6);
        board.placeCreature(F7);
        board.placeCreature(F8);
        board.placeCreature(F9);
        board.placeCreature(H);
        board.placeCreature(H2);
        board.placeCreature(H3);
        board.placeCreature(H4);
        board.placeCreature(H5);
        board.placeCreature(H6);
        board.placeCreature(R);
        board.placeCreature(R2);
        board.placeCreature(R3);
        board.placeCreature(R4);
        board.placeCreature(R5);
        board.placeCreature(R6);
        board.placeCreature(R7);
        board.placeCreature(R8);
        board.placeCreature(R9);
        cout<<"Turn: 0"<<endl;
        board.toString();
        simulate(100, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 2x2 Test2 ***" << endl;
        /*
        Do that for each kind of creature.
        9 Food
        6 Hopper
        9 Rover
        5 Trap
        Simulate 100 moves.
        print every 2 grids
        */
        vector<Creatures> animals;
        Creatures F = Creatures(1,1, SOUTH, Food);
        Creatures F2 = Creatures(0,1, SOUTH, Food);
        Creatures F3 = Creatures(1,0, SOUTH, Food);

        Creatures T = Creatures(0,0, SOUTH, Trap);

        animals.push_back(T);
        animals.push_back(F2);
        animals.push_back(F3);
        animals.push_back(F);


        sort(animals.begin(), animals.end());

        Map board(2, 2, 0);

        board.placeCreature(T);
        board.placeCreature(F);
        board.placeCreature(F2);
        board.placeCreature(F3);
        cout<<"Turn: 0"<<endl;
        board.toString();
        simulate(10, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        srand(0);
        cout << "*** Darwin 2x20 Test3 ***" << endl;
        /*
        RYAN BROOKS TEST
            make a 2x20 world
            1 hopper on top row 0,0 facing east
            1 rovers on second row 1,0 facing east
            4 foods on tird row col 16-19 facing WEst
            4 foods on bottom row col 16-19  facing west
            20 years
            print every 
            the rover and hopper race to food.
            rover plays dirty
        */
        vector<Creatures> animals;
        Creatures F = Creatures(0,16, WEST, Food);
        Creatures F2 = Creatures(0,17, WEST, Food);
        Creatures F3 = Creatures(0,18, WEST, Food);
        Creatures F4 = Creatures(0,19, WEST, Food);
        Creatures F5 = Creatures(1,16, WEST, Food);
        Creatures F6 = Creatures(1,17, WEST, Food);
        Creatures F7 = Creatures(1,18, WEST, Food);
        Creatures F8 = Creatures(1,19, WEST, Food);

        Creatures H = Creatures(0,0, EAST, Hopper);
        Creatures R = Creatures(1,0, EAST, Rover);

        animals.push_back(H);
        animals.push_back(R);
        animals.push_back(F2);
        animals.push_back(F3);
        animals.push_back(F);
        animals.push_back(F4);
        animals.push_back(F5);
        animals.push_back(F6);
        animals.push_back(F7);
        animals.push_back(F8);


        sort(animals.begin(), animals.end());

        Map board(2, 20, 0);

        board.placeCreature(R);
        board.placeCreature(H);
        board.placeCreature(F);
        board.placeCreature(F2);
        board.placeCreature(F3);
        board.placeCreature(F4);
        board.placeCreature(F5);
        board.placeCreature(F6);
        board.placeCreature(F7);
        board.placeCreature(F8);

        board.toString();
        simulate(20, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


try {
        srand(0);
        cout << "*** Darwin 3x3 ***" << endl;
        /*
        3x3 Darwin
        Trap,   facing south, at (1, 1)
        Rover,  facing east, at (0, 0)
        Simulate 16 moves.
        Print every grid.
        */
        vector<Creatures> animals;
        Creatures T = Creatures(1,1, SOUTH, Trap);
        Creatures R = Creatures(0,0, EAST, Rover);

        animals.push_back(T);
        animals.push_back(R);


        sort(animals.begin(), animals.end());

        Map board(3, 3, 0);

        board.placeCreature(R);
        board.placeCreature(T);

        board.toString();
        simulate(16, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

try {
        srand(0);
        cout << "*** Darwin 3x3 ***" << endl;
        /*
        3X3 Darwin
        Hopper, facing north, at (0, 0)
        Hopper, facing north, at (0, 1)
        Hopper, facing north, at (0, 2)
        Hopper, facing north, at (1, 0)
        Hopper, facing north, at (1, 1)
        Hopper, facing north, at (1, 2)
        Trap, facing north, at (2, 0)
        Trap, facing north, at (2, 1)
        Rover, facing north, at (2, 2)

        Simulate 5 moves.
        Print every grid.
        */
        vector<Creatures> animals;
        Creatures H = Creatures(0,0, NORTH, Hopper);
        Creatures H2 = Creatures(0,1, NORTH, Hopper);
        Creatures H3 = Creatures(0,2, NORTH, Hopper);
        Creatures H4 = Creatures(1,0, NORTH, Hopper);
        Creatures H5 = Creatures(1,1, NORTH, Hopper);
        Creatures H6 = Creatures(1,2, NORTH, Hopper);
        Creatures T = Creatures(2,0, NORTH, Trap);
        Creatures T2 = Creatures(2,1, NORTH, Trap);
        Creatures R = Creatures(2,2, NORTH, Rover);

        animals.push_back(T);
        animals.push_back(T2);
        animals.push_back(R);
        animals.push_back(H);
        animals.push_back(H2);
        animals.push_back(H3);
        animals.push_back(H4);
        animals.push_back(H5);
        animals.push_back(H6);


        sort(animals.begin(), animals.end());

        Map board(3, 3, 0);

        board.placeCreature(R);
        board.placeCreature(T);
        board.placeCreature(T2);
        board.placeCreature(H);
        board.placeCreature(H2);
        board.placeCreature(H3);
        board.placeCreature(H4);
        board.placeCreature(H5);
        board.placeCreature(H6);

        board.toString();
        simulate(5, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

try {
        srand(0);
        cout << "*** Darwin 3x3 ***" << endl;

        /*
                     1 x 7 Darwin*
                     Trap,   facing south, at (0, 0)
                     Rover,   facing east, at (0, 3)
                     Hopper, facing west,  at (0, 5)
                     Simulate 5 moves.
                     Print every grid.
                     */

        vector<Creatures> animals;
        Creatures H = Creatures(0,5, WEST, Hopper);
        Creatures T = Creatures(0,0, SOUTH, Trap);
        Creatures R = Creatures(0,3, EAST, Rover);

        animals.push_back(T);
        animals.push_back(R);
        animals.push_back(H);


        sort(animals.begin(), animals.end());

        Map board(1, 7, 0);

        board.placeCreature(R);
        board.placeCreature(T);
        board.placeCreature(H);
        cout<<"Turn: 0"<<endl;
        board.toString();
        simulate(5, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


// ------------
// fod_walk_east 4x4
// ------------
// hoppers march in a line, like an aircraft carrier fod walk
try {
        srand(0);
        cout << "*** fod_walk_east 4x4 ***" << endl;

        vector<Creatures> animals;
        Creatures H = Creatures(0,0, EAST, Hopper);
        Creatures H2 = Creatures(1,0, EAST, Hopper);
        Creatures H3 = Creatures(2,0, EAST, Hopper);
        Creatures H4 = Creatures(3,0, EAST, Hopper);

        animals.push_back(H);
        animals.push_back(H2);
        animals.push_back(H3);
        animals.push_back(H4);


        sort(animals.begin(), animals.end());

        Map board(4, 4, 0);

        board.placeCreature(H);
        board.placeCreature(H2);
        board.placeCreature(H3);
        board.placeCreature(H4);
        cout<<"Turn: 0"<<endl;
        board.toString();
        simulate(5, 1, animals, board);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}

