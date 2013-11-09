/*
 * RunDarwin.c++
 *
 *  Created on: Nov 5, 2013
 *      Author: menglin
 */

#include <cassert>
#include <iostream>
#include "Darwin.h"


using namespace std;

Direction randDirection(int roll){
	if(roll == 0)
		return UP;
	if(roll == 1)
		return RIGHT;
	if(roll == 2)
		return DOWN;
	if(roll == 3)
		return LEFT;
}
int main(){

	try {
		cout << "*** Darwin 8x8 ***" << endl;
		/*
			8x8 Darwin
			Hopper, facing north, at (3, 3)
			Hopper, facing east, at (3, 4)
			Hopper, facing south, at (4, 4)
			Hopper, facing west, at (4, 3)
			Simulate 5 moves.
			Print every grid.
		 */

		BoardManager test_board(8,8);
		Creature c1(3, 3, UP, 'h');
		Creature c2(3, 4, RIGHT, 'h');
		Creature c3(4, 4, DOWN, 'h');
		Creature c4(4, 3, UP, 'h');

		for(int i = 0; i < 5; i++)
		{
			cout << "Turn: " << i << endl;
			test_board.drawBoard();
			test_board.playTurn();
			test_board.refreshBoard();
		}

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 8x8 ***" << endl;
		/*
				8x8 Darwin
				Hopper, facing south, at (0, 0)
				Hopper, facing west, at (4, 3)

				Simulate 8 moves.
				Print every grid.
		 */

		BoardManager test_board(8,8);
		Creature c1(0, 0, DOWN, 'h');
		Creature c2(2, 0, RIGHT, 't');
		Creature c3(1, 1, DOWN, 'f');
		Creature c4(2, 2, LEFT, 'f');
		Creature c5(1, 6, LEFT, 'h');

		for(int i = 0; i < 8; i++)
		{
			test_board.drawBoard();
			test_board.playTurn();
			test_board.refreshBoard();
		}

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	try {
		cout << "*** Darwin 7x9 ***" << endl;
		/*
				8x8 Darwin
				Hopper, facing south, at (0, 0)
				Hopper, facing west, at (4, 3)

				Simulate 5 moves.
				Print every grid.
		 */
		srand(0);
		BoardManager test_board(7,9);
		Creature c1(0, 0, DOWN, 't');
		Creature c2(3, 2, RIGHT, 'h');
		Creature c3(5, 4, UP, 'r');
		Creature c4(6, 8, LEFT, 't');
		//Creature c5(1, 6, LEFT, 'h');

		for(int i = 0; i < 6; i++)
		{
			cout << "Turn: " << i << endl;
			test_board.drawBoard();
			test_board.playTurn();
			test_board.refreshBoard();
		}

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	try {
		cout << "*** Darwin 72x72 ***" << endl;
		/*
				8x8 Darwin
				Hopper, facing south, at (0, 0)
				Hopper, facing west, at (4, 3)

				Simulate 5 moves.
				Print every grid.
		 */
		srand(0);
		BoardManager test_board(72,72);

		Creature c0(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c1(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c2(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c3(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c4(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c5(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c6(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c7(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c8(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');
		Creature c9(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'f');

		Creature h0(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h1(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h2(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h3(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h4(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h5(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h6(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h7(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h8(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');
		Creature h9(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'h');

		Creature t0(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t1(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t2(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t3(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t4(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t5(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t6(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t7(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t8(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');
		Creature t9(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'t');

		Creature r0(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r1(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r2(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r3(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r4(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r5(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r6(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r7(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r8(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');
		Creature r9(rand()%5184/72,rand()%5184%72,randDirection(rand()%4),'r');

		int numTurns = 0;
		for(int i = 0; i < 10; i++)
		{
			cout << "Turn: " << i << endl;
			test_board.drawBoard();
			test_board.playTurn();
			test_board.refreshBoard();
			numTurns++;
		}

		for(;numTurns <= 1000; numTurns++)
		{
			if(numTurns%100 == 0)
			{
				cout << "Turn: " << numTurns << endl;
				test_board.drawBoard();
			}
			test_board.playTurn();
			test_board.refreshBoard();
		}

	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}
return 0;
}



