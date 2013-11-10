// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// ----
// Board
// ----

TEST(Darwin, board) {
	int a[] = {0, 0, 0, 0};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1, 1, v);

	ASSERT_EQ(b->grid.at(0).at(0).species, None);
}

TEST(Darwin, board1) {
	int a[] = {Food, east, 0, 0};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1, 1, v);

	ASSERT_EQ(b->grid.at(0).at(0).species, Food);
}

TEST(Darwin, board2) {
        int a[] = {Food, east, 0, 0,
		   Food, west, 1, 1};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(2, 2, v);

        ASSERT_EQ(b->grid.at(0).at(0).species, Food);
	ASSERT_EQ(b->grid.at(1).at(1).species, Food);
}


// ----
// Creature
// ----

TEST(Darwin, creature) {
        int a[] = {Hopper, north, 0, 0};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1, 1, v);

        ASSERT_EQ(b->grid.at(0).at(0).species, Hopper);
        ASSERT_EQ(b->grid.at(0).at(0).direction, north);
}

TEST(Darwin, creature1) {
        int a[] = {Rover, east, 0, 0};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(1, 1, v);

        ASSERT_EQ(b->grid.at(0).at(0).species, Rover);	
        ASSERT_EQ(b->grid.at(0).at(0).direction, east);
}

TEST(Darwin, creature2) {
        int a[] = {Trap, east, 0, 0,
                   Food, west, 1, 1};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(2, 2, v);

        ASSERT_EQ(b->grid.at(0).at(0).species, Trap);
        ASSERT_EQ(b->grid.at(1).at(1).species, Food);
        ASSERT_EQ(b->grid.at(0).at(0).direction, east);
        ASSERT_EQ(b->grid.at(1).at(1).direction, west);
}

// ----
// nextTurn
// ----

TEST(Darwin, nextTurn) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

	for(int i = 0; i < 5; i++)
	{
		b->nextTurn();
	}

        ASSERT_EQ(b->turn, 5);
        ASSERT_EQ(b->grid.at(0).at(2).species, Hopper);
}

TEST(Darwin, nextTurn1) {
        int a[] = {Hopper, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

	for(int i = 0; i < 10; i++)
	{
		b->nextTurn();
	}

	ASSERT_EQ(b->turn, 10);
        ASSERT_EQ(b->grid.at(3).at(7).species, Hopper);
}

TEST(Darwin, nextTurn2) {
        int a[] = {Hopper, east, 4, 5,
                   Hopper, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

	for(int i = 0; i < 20; i++)
	{
		b->nextTurn();
	}

        ASSERT_EQ(b->turn, 20);
        ASSERT_EQ(b->grid.at(4).at(9).species, Hopper);
        ASSERT_EQ(b->grid.at(9).at(0).species, Hopper);
}

// ----
// hop
// ----

TEST(Darwin, hop) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        for(int i = 0; i < 5; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 5);
        ASSERT_EQ(b->grid.at(0).at(2).species, Hopper);
}

TEST(Darwin, hop1) {
        int a[] = {Hopper, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        for(int i = 0; i < 10; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 10);
        ASSERT_EQ(b->grid.at(3).at(7).species, Hopper);
}

TEST(Darwin, hop2) {
        int a[] = {Hopper, east, 4, 5,
                   Hopper, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        for(int i = 0; i < 20; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 20);
        ASSERT_EQ(b->grid.at(4).at(9).species, Hopper);
        ASSERT_EQ(b->grid.at(9).at(0).species, Hopper);
}

// ----
// left
// ----

TEST(Darwin, left) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).left();

        ASSERT_EQ(b->grid.at(2).at(2).direction, west);
}

TEST(Darwin, left1) {
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

	b->grid.at(3).at(3).left();

        ASSERT_EQ(b->grid.at(3).at(3).direction, north);
}

TEST(Darwin, left2) {
        int a[] = {Hopper, south, 4, 5,
                   Hopper, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).left();
	b->grid.at(4).at(5).left();
	b->grid.at(9).at(8).left();

        ASSERT_EQ(b->grid.at(4).at(5).direction, north);
        ASSERT_EQ(b->grid.at(9).at(8).direction, south);
}

// ----
// right
// ----

TEST(Darwin, right) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).right();

        ASSERT_EQ(b->grid.at(2).at(2).direction, east);
}

TEST(Darwin, right1) {
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).right();

        ASSERT_EQ(b->grid.at(3).at(3).direction, south);
}

TEST(Darwin, right2) {
        int a[] = {Hopper, south, 4, 5,
                   Hopper, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).right();
        b->grid.at(4).at(5).right();
        b->grid.at(9).at(8).right();

        ASSERT_EQ(b->grid.at(4).at(5).direction, north);
        ASSERT_EQ(b->grid.at(9).at(8).direction, north);
}

// ----
// go
// ----

TEST(Darwin, go) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).go(0, b->grid);

        ASSERT_EQ(b->grid.at(2).at(2).programcounter, 0);
}

TEST(Darwin, go1) {
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).go(0, b->grid);

        ASSERT_EQ(b->grid.at(3).at(3).programcounter, 1);
}

TEST(Darwin, go2) {
        int a[] = {Rover, south, 4, 5,
                   Trap, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).go(0, b->grid);
        b->grid.at(9).at(8).go(0, b->grid);

        ASSERT_EQ(b->grid.at(4).at(5).programcounter, 0);
        ASSERT_EQ(b->grid.at(9).at(8).programcounter, 2);
}

// ----
// move
// ----

TEST(Darwin, move) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        for(int i = 0; i < 5; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 5);
        ASSERT_EQ(b->grid.at(0).at(2).hasMoved, false);
}

TEST(Darwin, move1) {
        int a[] = {Hopper, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        for(int i = 0; i < 10; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 10);
        ASSERT_EQ(b->grid.at(3).at(7).hasMoved, false);
}

TEST(Darwin, move2) {
        int a[] = {Hopper, east, 4, 5,
                   Hopper, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        for(int i = 0; i < 20; i++)
        {
                b->nextTurn();
        }

        ASSERT_EQ(b->turn, 20);
        ASSERT_EQ(b->grid.at(4).at(9).hasMoved, false);
        ASSERT_EQ(b->grid.at(9).at(0).hasMoved, false);
}

// ----
// empty
// ----

TEST(Darwin, empty) {
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).empty(1, b->grid);

        ASSERT_EQ(b->grid.at(0).at(2).programcounter, 0);
}

TEST(Darwin, empty1) {
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).empty(1, b->grid);

        ASSERT_EQ(b->grid.at(3).at(7).programcounter, 0);
}

TEST(Darwin, empty2) {
        int a[] = {Rover, east, 4, 5,
                   Trap, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).empty(7, b->grid);
	b->grid.at(9).at(8).empty(3, b->grid);

        ASSERT_EQ(b->grid.at(4).at(9).programcounter, 0);
        ASSERT_EQ(b->grid.at(9).at(0).programcounter, 0);
}

// ----
// random
// ----

TEST(Darwin, random) {
	srand(0);
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).random(1, b->grid);

        ASSERT_EQ(b->grid.at(0).at(2).programcounter, 0);
}

TEST(Darwin, random1) {
	srand(0);
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).random(1, b->grid);

        ASSERT_EQ(b->grid.at(3).at(7).programcounter, 0);
}

TEST(Darwin, random2) {
	srand(0);
        int a[] = {Rover, east, 4, 5,
                   Trap, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).random(7, b->grid);
	b->grid.at(9).at(8).random(3, b->grid);

        ASSERT_EQ(b->grid.at(4).at(9).programcounter, 0);
        ASSERT_EQ(b->grid.at(9).at(0).programcounter, 0);
}

// ----
// infect
// ----

TEST(Darwin, infect) {
	srand(0);
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).infect(b->grid);

        ASSERT_EQ(b->grid.at(1).at(2).species, 0);
}

TEST(Darwin, infect1) {
	srand(0);
        int a[] = {Food, east, 3, 3,
		   Hopper, north, 4, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(4).at(3).infect(b->grid);

        ASSERT_EQ(b->grid.at(3).at(3).species, 2);
}

TEST(Darwin, infect2) {
	srand(0);
        int a[] = {Rover, east, 4, 5,
                   Trap, west, 4, 6};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).infect(b->grid);

        ASSERT_EQ(b->grid.at(4).at(6).species, 4);
}

// ----
// wall
// ----

TEST(Darwin, wall) {
	srand(0);
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).wall(1, b->grid);

        ASSERT_EQ(b->grid.at(0).at(2).programcounter, 0);
}

TEST(Darwin, wall1) {
	srand(0);
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).wall(1, b->grid);

        ASSERT_EQ(b->grid.at(3).at(7).programcounter, 0);
}

TEST(Darwin, wall2) {
	srand(0);
        int a[] = {Rover, east, 4, 5,
                   Trap, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).wall(7, b->grid);
	b->grid.at(9).at(8).wall(3, b->grid);

        ASSERT_EQ(b->grid.at(4).at(5).programcounter, 0);
        ASSERT_EQ(b->grid.at(9).at(8).programcounter, 2);
}

// ----
// enemy
// ----

TEST(Darwin, enemy) {
	srand(0);
        int a[] = {Hopper, north, 2, 2};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(5, 5, v);

        b->grid.at(2).at(2).enemy(1, b->grid);

        ASSERT_EQ(b->grid.at(0).at(2).programcounter, 0);
}

TEST(Darwin, enemy1) {
	srand(0);
        int a[] = {Food, east, 3, 3};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(8, 8, v);

        b->grid.at(3).at(3).enemy(1, b->grid);

        ASSERT_EQ(b->grid.at(3).at(7).programcounter, 0);
}

TEST(Darwin, enemy2) {
	srand(0);
        int a[] = {Rover, east, 4, 5,
                   Trap, west, 9, 8};

        vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
        board *b = new board(10, 10, v);

        b->grid.at(4).at(5).enemy(7, b->grid);
	b->grid.at(9).at(8).enemy(3, b->grid);

        ASSERT_EQ(b->grid.at(4).at(5).programcounter, 0);
        ASSERT_EQ(b->grid.at(9).at(8).programcounter, 2);
}
