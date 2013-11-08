
// --------------
// TestDarwin.c++
// --------------

// includes
#include <iostream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

TEST(Darwin, addCreature_1) {
    Darwin myGame(8, 8);
    Creature h('H', NORTH);
    myGame.addCreature(h, 0, 0);
    ASSERT_TRUE(myGame.board[0][0]->name == 'H');
    ASSERT_TRUE(myGame.board[0][0]->dir == NORTH);
}

TEST(Darwin, addCreature_2) {
    Darwin myGame(8, 8);
    Creature f('F', SOUTH);
    myGame.addCreature(f, 7, 7);
    ASSERT_TRUE(myGame.board[7][7]->name == 'F');
    ASSERT_TRUE(myGame.board[7][7]->dir == SOUTH); 
}

TEST(Darwin, addCreature_3) {
    Darwin myGame(8, 8);
    Creature r('R', EAST);
    myGame.addCreature(r, 0, 7);
    ASSERT_TRUE(myGame.board[0][7]->name == 'R');
    ASSERT_TRUE(myGame.board[0][7]->dir == EAST);
} 
TEST(Darwin, addCreature_4) {
    Darwin myGame(8, 8);
    Creature t('T', WEST);
    myGame.addCreature(t, 7, 0);
    ASSERT_TRUE(myGame.board[7][0]->name == 'T');
    ASSERT_TRUE(myGame.board[7][0]->dir == WEST);
}

TEST(Darwin, giveEveryoneOneTurn_1) {
/*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
*/
         Darwin myGame(8, 8);
         Creature f1('F',EAST);
         myGame.addCreature(f1, 0, 0);
         Creature h1('H',NORTH);
         myGame.addCreature(h1,3,3);
         Creature h2('H',EAST);
         myGame.addCreature(h2, 3, 4);
         Creature h3('H',SOUTH);
         myGame.addCreature(h3, 4, 4);
         Creature h4('H',WEST);
         myGame.addCreature(h4, 4, 3);
         Creature f2('F',NORTH);
         myGame.addCreature(f2, 7, 7);

    myGame.giveEveryoneOneTurn();
    ASSERT_TRUE(myGame.board[0][0]->name == 'F');
    ASSERT_TRUE(myGame.board[2][3]->name == 'H');
    ASSERT_TRUE(myGame.board[3][5]->name == 'H');
    ASSERT_TRUE(myGame.board[4][2]->name == 'H');
    ASSERT_TRUE(myGame.board[5][4]->name == 'H');
    ASSERT_TRUE(myGame.board[7][7]->name == 'F');
}

TEST(Darwin, giveEveryoneOneTurn_2) {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

	myGame.giveEveryoneOneTurn();

	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[3][3]->name == 'H');
	ASSERT_TRUE(myGame.board[4][4]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}


TEST(Darwin, giveEveryoneOneTurn_3) {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[3][4]->name == 'R');
	ASSERT_TRUE(myGame.board[4][4]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}
TEST(Darwin, giveEveryoneOneTurn_4) {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[3][4]->name == 'R');
	ASSERT_TRUE(myGame.board[3][5]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}


TEST(Darwin, giveEveryoneOneTurn_5) {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[2][4]->name == 'R');
	ASSERT_TRUE(myGame.board[3][6]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}

TEST(Darwin, giveEveryoneOneTurn_6) {
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[1][4]->name == 'R');
	ASSERT_TRUE(myGame.board[3][7]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}
TEST(Darwin, creatureTurn_1) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

    	myGame.creatureTurn(myGame.board[0][0], 0, 0);
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	
}
TEST(Darwin, creatureTurn_2) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

    	myGame.creatureTurn(myGame.board[3][2], 3, 2);
	ASSERT_TRUE(myGame.board[3][3]->name == 'H');
}
TEST(Darwin, creatureTurn_3) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

    	myGame.creatureTurn(myGame.board[5][4], 5, 4);
	//ASSERT_TRUE(myGame.board[4][4]->name == 'R');
}
TEST(Darwin, creatureTurn_4) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);

    	myGame.creatureTurn(myGame.board[6][8], 6, 8);
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}
TEST(Darwin, creatureTurn_5) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);
	
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[3][3]->name == 'H');
	ASSERT_TRUE(myGame.board[4][4]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');

    	myGame.creatureTurn(myGame.board[0][0], 0, 0);
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	myGame.creatureTurn(myGame.board[3][3], 3, 3);
	// bug**** Rover not H
	ASSERT_TRUE(myGame.board[3][4]->name == 'H');
	myGame.creatureTurn(myGame.board[4][4], 4, 4);
	ASSERT_TRUE(myGame.board[4][4]->name == 'R');
	myGame.creatureTurn(myGame.board[6][8], 6, 8);
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}
// bug*******
TEST(Darwin, creatureTurn_6) {

        Darwin myGame(7, 9);
        Creature t1('T',SOUTH);
        myGame.addCreature(t1,0,0);
        Creature h1('H',EAST);
        myGame.addCreature(h1, 3, 2);
        Creature r1('R',NORTH);
        myGame.addCreature(r1, 5, 4);
        Creature t2('T',WEST);
        myGame.addCreature(t2, 6, 8);
	
	myGame.giveEveryoneOneTurn();
	myGame.giveEveryoneOneTurn();
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	ASSERT_TRUE(myGame.board[3][4]->name == 'R');
	ASSERT_TRUE(myGame.board[4][4]->name == 'R');
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');

    	myGame.creatureTurn(myGame.board[0][0], 0, 0);
	ASSERT_TRUE(myGame.board[0][0]->name == 'T');
	myGame.creatureTurn(myGame.board[3][4], 3, 4);
	//ASSERT_TRUE(myGame.board[3][4]->name == 'R');
	myGame.creatureTurn(myGame.board[4][4], 4, 4);
	//ASSERT_TRUE(myGame.board[3][5]->name == 'R');
	myGame.creatureTurn(myGame.board[6][8], 6, 8);
	ASSERT_TRUE(myGame.board[6][8]->name == 'T');
}
