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
	Darwin game = Darwin(8, 8);
	Food food1 = Food(Direction(2), 0, 0);
	Hopper hopper1 = Hopper(Direction(1), 3, 3);
	Hopper hopper2 = Hopper(Direction(2), 3, 4);
	Hopper hopper3 = Hopper(Direction(3), 4, 4);
	Hopper hopper4 = Hopper(Direction(0), 4, 3);
	Food food2 = Food(Direction(1), 7, 7);
	game.add_creature(food1);
	game.add_creature(hopper1);
	game.add_creature(hopper2);
	game.add_creature(hopper3);
	game.add_creature(hopper4);
	game.add_creature(food2);
	game.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        /*
        10x10 Darwin
        Food,   facing north,  at (0, 0)
        Hopper, facing north, at (5, 6)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (5, 1)
        Hopper, facing south,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 3 moves.
        Print every grid.
        */
    Darwin game = Darwin(10, 10);
    Food food1 = Food(Direction(1), 0, 0);
    Hopper hopper1 = Hopper(Direction(1), 5, 6);
    Hopper hopper2 = Hopper(Direction(2), 3, 4);
    Hopper hopper3 = Hopper(Direction(3), 5, 1);
    Hopper hopper4 = Hopper(Direction(3), 4, 3);
    Food food2 = Food(Direction(1), 7, 7);
    game.add_creature(food1);
    game.add_creature(hopper1);
    game.add_creature(hopper2);
    game.add_creature(hopper3);
    game.add_creature(hopper4);
    game.add_creature(food2);
    game.simulate(3, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 12x12
    // ----------

    try {
        cout << "*** Darwin 12x12 ***" << endl;
        /*
        12x12 Darwin
        Food,   facing north,  at (6, 6)
        Hopper, facing north, at (5, 6)
        Hopper, facing west,  at (11, 11)
        Rover, facing south, at (9, 10)
        Rover, facing south,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 6 moves.
        Print every grid.
        */
    Darwin game = Darwin(12, 12);
    Food food1 = Food(Direction(1), 6, 6);
    Hopper hopper1 = Hopper(Direction(1), 5, 6);
    Hopper hopper2 = Hopper(Direction(0), 11, 11);
    Rover rover1 = Rover(Direction(3), 9, 10);
    Rover rover2 = Rover(Direction(3), 4, 3);
    Food food2 = Food(Direction(1), 0, 0);
    game.add_creature(food1);
    game.add_creature(hopper1);
    game.add_creature(hopper2);
    game.add_creature(rover1);
    game.add_creature(rover2);
    game.add_creature(food2);
    game.simulate(6, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 15x15
    // ----------

    try {
        cout << "*** Darwin 15x15 ***" << endl;
        /*
        15x15 Darwin
        Food,   facing north,  at (12, 3)
        Hopper, facing north, at (5, 6)
        Hopper, facing east,  at (3, 4)
        Rover, facing south, at (9, 10)
        Hopper, facing south,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 8 moves.
        Print every grid.
        */
    Darwin game = Darwin(15, 15);
    Food food1 = Food(Direction(1), 12, 3);
    Hopper hopper1 = Hopper(Direction(1), 5, 6);
    Hopper hopper2 = Hopper(Direction(2), 3, 4);
    Rover rover1 = Rover(Direction(3), 9, 10);
    Hopper hopper4 = Hopper(Direction(3), 4, 3);
    Food food2 = Food(Direction(1), 0, 0);
    game.add_creature(food1);
    game.add_creature(hopper1);
    game.add_creature(hopper2);
    game.add_creature(rover1);
    game.add_creature(hopper4);
    game.add_creature(food2);
    game.simulate(8, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 6x6
    // ----------

    try {
        cout << "*** Darwin 6x6 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing north,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 0)
        Hopper, facing south,  at (4, 3)
        Food,   facing north, at (1, 1)
        Simulate 5 moves.
        Print every grid.
        */
    Darwin game = Darwin(6, 6);
    Food food1 = Food(Direction(1), 0, 0);
    Hopper hopper1 = Hopper(Direction(1), 3, 3);
    Hopper hopper2 = Hopper(Direction(2), 3, 4);
    Hopper hopper3 = Hopper(Direction(3), 4, 0);
    Hopper hopper4 = Hopper(Direction(3), 4, 3);
    Food food2 = Food(Direction(1), 1, 1);
    game.add_creature(food1);
    game.add_creature(hopper1);
    game.add_creature(hopper2);
    game.add_creature(hopper3);
    game.add_creature(hopper4);
    game.add_creature(food2);
    game.simulate(5, 1);
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
	Darwin game = Darwin(7, 9);
	Trap trap1 = Trap(Direction(3), 0, 0);
	game.add_creature(trap1);
	Hopper hopper1 = Hopper(Direction(2), 3, 2);
        game.add_creature(hopper1);
	Rover rover1 = Rover(Direction(1), 5, 4);
        game.add_creature(rover1);
	Trap trap2 = Trap(Direction(0), 6, 8);
        game.add_creature(trap2);
	game.simulate(5, 1);
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
	Darwin game = Darwin(72, 72);

	vector<Food> food;
	for(int i = 0; i < 10; i++)
	{
		int position = rand() % 5184;
		int x = position / 72;
		int y = position % 72;
		int dir = rand() % 4;
		food.push_back(Food(Direction(dir), x, y));
	}

	vector<Hopper> hopper;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                hopper.push_back(Hopper(Direction(dir), x, y));
        }

 	vector<Rover> rover;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                rover.push_back(Rover(Direction(dir), x, y));
        }

 	vector<Trap> trap;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                trap.push_back(Trap(Direction(dir), x, y));
        }
	
	for(int i = 0; i < 10; i++)
	{
		game.add_creature(food[i]);
		game.add_creature(hopper[i]);
		game.add_creature(rover[i]);
		game.add_creature(trap[i]);		
	}

	game.simulate(1000, 100);

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
            Darwin game = Darwin(72, 72);

    vector<Food> food;
    for(int i = 0; i < 10; i++)
    {
        int position = rand() % 5184;
        int x = position / 72;
        int y = position % 72;
        int dir = rand() % 4;
        food.push_back(Food(Direction(dir), x, y));
    }

    vector<Hopper> hopper;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                hopper.push_back(Hopper(Direction(dir), x, y));
        }

    vector<Rover> rover;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                rover.push_back(Rover(Direction(dir), x, y));
        }

    vector<Trap> trap;
        for(int i = 0; i < 10; i++)
        {
                int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                trap.push_back(Trap(Direction(dir), x, y));
        }

    vector<Elephant> best;
    for(int i=0; i< 10; i++)
    {
        int position = rand() % 5184;
                int x = position / 72;
                int y = position % 72;
                int dir = rand() % 4;
                best.push_back(Elephant(Direction(dir), x, y));
    }

    
    for(int i = 0; i < 10; i++)
    {
        game.add_creature(food[i]);
        game.add_creature(hopper[i]);
        game.add_creature(rover[i]);
        game.add_creature(trap[i]);
        game.add_creature(best[i]);     
    }

    game.simulate(1000, 100);


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1
    // ----------

    try {
	cout << "*** Darwin 1x1 ***" << endl;
	srand(0);

	Darwin game = Darwin(1, 1);
	Hopper hopper = Hopper(Direction(0), 0, 0);
	game.add_creature(hopper);
	game.simulate(5, 1);
	}
    catch (const invalid_argument&) {
	assert(false);}
    catch (const out_of_range&) {
	assert(false);}
	



//PUBLIC TEST REPOS!!!!!

//sscheng
try {
        cout << "*** sscheng Darwin 8x8 ***" << endl;
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
        Darwin game(8, 8);

        Food f1 = Food(Direction(2), 0, 0);
        game.add_creature(f1);
        Hopper h1 = Hopper(Direction(1), 3, 3);
        game.add_creature(h1);
        Hopper h2 = Hopper(Direction(2), 3, 4);
        game.add_creature(h2);
        Hopper h3 = Hopper(Direction(3), 4, 4);
        game.add_creature(h3);
        Hopper h4 = Hopper(Direction(0), 4, 3);
        game.add_creature(h4);
        Food f2 = Food(Direction(1), 7, 7);
        game.add_creature(f2);
        game.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


//ryan76
try {
        cout << "*** ryan76 Darwin 72x72 without Best ***" << endl;
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
        
        Darwin game(72, 72);
        vector<Food> food;
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;\
            food.push_back(Food(Direction(direction), row, column));
        }
        
        vector<Hopper> hopper;
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            hopper.push_back(Hopper(Direction(direction), row, column));
        }
        
        vector<Rover> rover;
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            rover.push_back(Rover(Direction(direction), row, column));
        }
        
        vector<Trap> trap;
        for (int i = 0; i < 10; i++) {
            int direction = rand() % 4;
            int position = rand() % 5184;
            int row = position % 72;
            int column = position / 72;
            trap.push_back(Trap(Direction(direction), row, column));
        }
        
        for(int i = 0; i < 10; i++)
        {
        game.add_creature(food[i]);
        game.add_creature(hopper[i]);
        game.add_creature(rover[i]);
        game.add_creature(trap[i]);  
        }

    game.simulate(1000, 100);


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

//psteiner
try {
        cout << "*** psteiner Darwin direction infection test all directions, all types ***" << endl;
        Darwin game(5, 5);
        Food f1 = Food(Direction(3), 0, 2);
        game.add_creature(f1);
        Trap t1 = Trap(Direction(1), 1, 2);
        game.add_creature(t1);
        Hopper h1 = Hopper(Direction(0), 2, 0);
        game.add_creature(h1);
        Trap t2 = Trap(Direction(2), 2, 1);
        game.add_creature(t2);
        Trap t3 = Trap(Direction(0), 2, 3);
        game.add_creature(t3);
        Hopper h2 = Hopper(Direction(2), 2, 4);
        game.add_creature(h2);
        Trap t4 = Trap(Direction(3), 3, 2);
        game.add_creature(t4);
        Rover r1 = Rover(Direction(3), 4, 2);
        game.add_creature(t1);
        game.simulate(5, 1);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

//tashar
try {
        cout << "*** tashar Darwin 2x2 ***" << endl;
        Darwin game(2, 2);

        Hopper h1 = Hopper(Direction(0), 0, 0);
        game.add_creature(h1);
        Hopper h2 = Hopper(Direction(2), 0, 1);
        game.add_creature(h2);
        Hopper h3 = Hopper(Direction(3), 1, 0);
        game.add_creature(h3);
        Hopper h4 = Hopper(Direction(1), 1, 1);
        game.add_creature(h4);

        game.simulate(5, 1);
        }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}


//kbixby
try {
        cout << "*** kbixby Darwin 2x2 Two Rovers ***" << endl;
        srand(0);
        /*
2x2 Grid
North Rover @ (0, 0)
East Rover @ (1, 0)
*/
        Darwin game = Darwin(2, 2);
        Rover rover = Rover(Direction(1), 0, 0);
game.add_creature(rover);
Rover rover2 = Rover(Direction(2), 1, 0);
        game.add_creature(rover);
        game.simulate(10, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        return 0;}