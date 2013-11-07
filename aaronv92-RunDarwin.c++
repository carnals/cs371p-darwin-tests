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


int place_random(Creature c) {
    int c_position = rand() % 5184;
    int c_direction = rand() % 4;
    c.set_direction(c_direction);
    return c_position;
}

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    Food f;

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Hopper h;

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

    Rover r;

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

     Trap t;

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        GameBoard game (8, 8);

        Creature food(f, 1);
        Creature hopper(h, 0);
        Creature hopper2(h, 1);
        Creature hopper3(h, 2);
        Creature hopper4(h, 3);
        Creature food2(f, 0);
		
        //putCreature(creature, x, y)
        game.put_creature(&food, 0, 0);
        game.put_creature(&hopper, 3, 3);
        game.put_creature(&hopper2, 3, 4);
        game.put_creature(&hopper3, 4, 4);
        game.put_creature(&hopper4, 4, 3);
        game.put_creature(&food2, 7, 7);
        for(int i = 0; i <= 5; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        cout << endl;
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
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);

        GameBoard game (7, 9);

        Creature trap(t, 2);
        game.put_creature(&trap, 0, 0);

        Creature hopper(h, 1);
        game.put_creature(&hopper, 3, 2);

        Creature rover(r, 0);
        game.put_creature(&rover, 5, 4);

        Creature trap2(t, 3);
        game.put_creature(&trap2, 6, 8);

        for(int i = 0; i <= 5; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        cout << endl;

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
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);

        GameBoard game (72, 72);
        int c_dir;

        Creature food1(f, 0);
        c_dir = place_random(food1);
        game.put_creature(&food1, c_dir%72, c_dir/72);
        Creature food2(f, 0);
        c_dir = place_random(food2);
        game.put_creature(&food2, c_dir%72, c_dir/72);
        Creature food3(f, 0);
        c_dir = place_random(food3);
        game.put_creature(&food3, c_dir%72, c_dir/72);
        Creature food4(f, 0);
        c_dir = place_random(food4);
        game.put_creature(&food4, c_dir%72, c_dir/72);
        Creature food5(f, 0);
        c_dir = place_random(food5);
        game.put_creature(&food5, c_dir%72, c_dir/72);
        Creature food6(f, 0);
        c_dir = place_random(food6);
        game.put_creature(&food6, c_dir%72, c_dir/72);
        Creature food7(f, 0);
        c_dir = place_random(food7);
        game.put_creature(&food7, c_dir%72, c_dir/72);
        Creature food8(f, 0);
        c_dir = place_random(food8);
        game.put_creature(&food8, c_dir%72, c_dir/72);
        Creature food9(f, 0);
        c_dir = place_random(food9);
        game.put_creature(&food9, c_dir%72, c_dir/72);
        Creature food10(f, 0);
        c_dir = place_random(food10);
        game.put_creature(&food10, c_dir%72, c_dir/72);

        Creature hopper1(h, 0);
        c_dir = place_random(hopper1);
        game.put_creature(&hopper1, c_dir%72, c_dir/72);
        Creature hopper2(h, 0);
        c_dir = place_random(hopper2);
        game.put_creature(&hopper2, c_dir%72, c_dir/72);
        Creature hopper3(h, 0);
        c_dir = place_random(hopper3);
        game.put_creature(&hopper3, c_dir%72, c_dir/72);
        Creature hopper4(h, 0);
        c_dir = place_random(hopper4);
        game.put_creature(&hopper4, c_dir%72, c_dir/72);
        Creature hopper5(h, 0);
        c_dir = place_random(hopper5);
        game.put_creature(&hopper5, c_dir%72, c_dir/72);
        Creature hopper6(h, 0);
        c_dir = place_random(hopper6);
        game.put_creature(&hopper6, c_dir%72, c_dir/72);
        Creature hopper7(h, 0);
        c_dir = place_random(hopper7);
        game.put_creature(&hopper7, c_dir%72, c_dir/72);
        Creature hopper8(h, 0);
        c_dir = place_random(hopper8);
        game.put_creature(&hopper8, c_dir%72, c_dir/72);
        Creature hopper9(h, 0);
        c_dir = place_random(hopper9);
        game.put_creature(&hopper9, c_dir%72, c_dir/72);
        Creature hopper10(h, 0);
        c_dir = place_random(hopper10);
        game.put_creature(&hopper10, c_dir%72, c_dir/72);

        Creature rover1(r, 0);
        c_dir = place_random(rover1);
        game.put_creature(&rover1, c_dir%72, c_dir/72);
        Creature rover2(r, 0);
        c_dir = place_random(rover2);
        game.put_creature(&rover2, c_dir%72, c_dir/72);
        Creature rover3(r, 0);
        c_dir = place_random(rover3);
        game.put_creature(&rover3, c_dir%72, c_dir/72);
        Creature rover4(r, 0);
        c_dir = place_random(rover4);
        game.put_creature(&rover4, c_dir%72, c_dir/72);
        Creature rover5(r, 0);
        c_dir = place_random(rover5);
        game.put_creature(&rover5, c_dir%72, c_dir/72);
        Creature rover6(r, 0);
        c_dir = place_random(rover6);
        game.put_creature(&rover6, c_dir%72, c_dir/72);
        Creature rover7(r, 0);
        c_dir = place_random(rover7);
        game.put_creature(&rover7, c_dir%72, c_dir/72);
        Creature rover8(r, 0);
        c_dir = place_random(rover8);
        game.put_creature(&rover8, c_dir%72, c_dir/72);
        Creature rover9(r, 0);
        c_dir = place_random(rover9);
        game.put_creature(&rover9, c_dir%72, c_dir/72);
        Creature rover10(r, 0);
        c_dir = place_random(rover10);
        game.put_creature(&rover10, c_dir%72, c_dir/72);

        Creature trap1(t, 0);
        c_dir = place_random(trap1);
        game.put_creature(&trap1, c_dir%72, c_dir/72);
        Creature trap2(t, 0);
        c_dir = place_random(trap2);
        game.put_creature(&trap2, c_dir%72, c_dir/72);
        Creature trap3(t, 0);
        c_dir = place_random(trap3);
        game.put_creature(&trap3, c_dir%72, c_dir/72);
        Creature trap4(t, 0);
        c_dir = place_random(trap4);
        game.put_creature(&trap4, c_dir%72, c_dir/72);
        Creature trap5(t, 0);
        c_dir = place_random(trap5);
        game.put_creature(&trap5, c_dir%72, c_dir/72);
        Creature trap6(t, 0);
        c_dir = place_random(trap6);
        game.put_creature(&trap6, c_dir%72, c_dir/72);
        Creature trap7(t, 0);
        c_dir = place_random(trap7);
        game.put_creature(&trap7, c_dir%72, c_dir/72);
        Creature trap8(t, 0);
        c_dir = place_random(trap8);
        game.put_creature(&trap8, c_dir%72, c_dir/72);
        Creature trap9(t, 0);
        c_dir = place_random(trap9);
        game.put_creature(&trap9, c_dir%72, c_dir/72);
        Creature trap10(t, 0);
        c_dir = place_random(trap10);
        game.put_creature(&trap10, c_dir%72, c_dir/72);

        for(int i = 0; i <= 9; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        for(int i = 10; i <= 1000; i++) {
            if(i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                game.print_board(cout);
            }
            darwin_run(game, 1);
        }
        cout << endl;        
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
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);

        GameBoard game (72, 72);
        int c_dir;

        Creature food1(f, 0);
        c_dir = place_random(food1);
        game.put_creature(&food1, c_dir%72, c_dir/72);
        Creature food2(f, 0);
        c_dir = place_random(food2);
        game.put_creature(&food2, c_dir%72, c_dir/72);
        Creature food3(f, 0);
        c_dir = place_random(food3);
        game.put_creature(&food3, c_dir%72, c_dir/72);
        Creature food4(f, 0);
        c_dir = place_random(food4);
        game.put_creature(&food4, c_dir%72, c_dir/72);
        Creature food5(f, 0);
        c_dir = place_random(food5);
        game.put_creature(&food5, c_dir%72, c_dir/72);
        Creature food6(f, 0);
        c_dir = place_random(food6);
        game.put_creature(&food6, c_dir%72, c_dir/72);
        Creature food7(f, 0);
        c_dir = place_random(food7);
        game.put_creature(&food7, c_dir%72, c_dir/72);
        Creature food8(f, 0);
        c_dir = place_random(food8);
        game.put_creature(&food8, c_dir%72, c_dir/72);
        Creature food9(f, 0);
        c_dir = place_random(food9);
        game.put_creature(&food9, c_dir%72, c_dir/72);
        Creature food10(f, 0);
        c_dir = place_random(food10);
        game.put_creature(&food10, c_dir%72, c_dir/72);

        Creature hopper1(h, 0);
        c_dir = place_random(hopper1);
        game.put_creature(&hopper1, c_dir%72, c_dir/72);
        Creature hopper2(h, 0);
        c_dir = place_random(hopper2);
        game.put_creature(&hopper2, c_dir%72, c_dir/72);
        Creature hopper3(h, 0);
        c_dir = place_random(hopper3);
        game.put_creature(&hopper3, c_dir%72, c_dir/72);
        Creature hopper4(h, 0);
        c_dir = place_random(hopper4);
        game.put_creature(&hopper4, c_dir%72, c_dir/72);
        Creature hopper5(h, 0);
        c_dir = place_random(hopper5);
        game.put_creature(&hopper5, c_dir%72, c_dir/72);
        Creature hopper6(h, 0);
        c_dir = place_random(hopper6);
        game.put_creature(&hopper6, c_dir%72, c_dir/72);
        Creature hopper7(h, 0);
        c_dir = place_random(hopper7);
        game.put_creature(&hopper7, c_dir%72, c_dir/72);
        Creature hopper8(h, 0);
        c_dir = place_random(hopper8);
        game.put_creature(&hopper8, c_dir%72, c_dir/72);
        Creature hopper9(h, 0);
        c_dir = place_random(hopper9);
        game.put_creature(&hopper9, c_dir%72, c_dir/72);
        Creature hopper10(h, 0);
        c_dir = place_random(hopper10);
        game.put_creature(&hopper10, c_dir%72, c_dir/72);

        Creature rover1(r, 0);
        c_dir = place_random(rover1);
        game.put_creature(&rover1, c_dir%72, c_dir/72);
        Creature rover2(r, 0);
        c_dir = place_random(rover2);
        game.put_creature(&rover2, c_dir%72, c_dir/72);
        Creature rover3(r, 0);
        c_dir = place_random(rover3);
        game.put_creature(&rover3, c_dir%72, c_dir/72);
        Creature rover4(r, 0);
        c_dir = place_random(rover4);
        game.put_creature(&rover4, c_dir%72, c_dir/72);
        Creature rover5(r, 0);
        c_dir = place_random(rover5);
        game.put_creature(&rover5, c_dir%72, c_dir/72);
        Creature rover6(r, 0);
        c_dir = place_random(rover6);
        game.put_creature(&rover6, c_dir%72, c_dir/72);
        Creature rover7(r, 0);
        c_dir = place_random(rover7);
        game.put_creature(&rover7, c_dir%72, c_dir/72);
        Creature rover8(r, 0);
        c_dir = place_random(rover8);
        game.put_creature(&rover8, c_dir%72, c_dir/72);
        Creature rover9(r, 0);
        c_dir = place_random(rover9);
        game.put_creature(&rover9, c_dir%72, c_dir/72);
        Creature rover10(r, 0);
        c_dir = place_random(rover10);
        game.put_creature(&rover10, c_dir%72, c_dir/72);

        Creature trap1(t, 0);
        c_dir = place_random(trap1);
        game.put_creature(&trap1, c_dir%72, c_dir/72);
        Creature trap2(t, 0);
        c_dir = place_random(trap2);
        game.put_creature(&trap2, c_dir%72, c_dir/72);
        Creature trap3(t, 0);
        c_dir = place_random(trap3);
        game.put_creature(&trap3, c_dir%72, c_dir/72);
        Creature trap4(t, 0);
        c_dir = place_random(trap4);
        game.put_creature(&trap4, c_dir%72, c_dir/72);
        Creature trap5(t, 0);
        c_dir = place_random(trap5);
        game.put_creature(&trap5, c_dir%72, c_dir/72);
        Creature trap6(t, 0);
        c_dir = place_random(trap6);
        game.put_creature(&trap6, c_dir%72, c_dir/72);
        Creature trap7(t, 0);
        c_dir = place_random(trap7);
        game.put_creature(&trap7, c_dir%72, c_dir/72);
        Creature trap8(t, 0);
        c_dir = place_random(trap8);
        game.put_creature(&trap8, c_dir%72, c_dir/72);
        Creature trap9(t, 0);
        c_dir = place_random(trap9);
        game.put_creature(&trap9, c_dir%72, c_dir/72);
        Creature trap10(t, 0);
        c_dir = place_random(trap10);
        game.put_creature(&trap10, c_dir%72, c_dir/72);
		
		Best b;
		Creature best1(b, 0);
        c_dir = place_random(best1);
        game.put_creature(&best1, c_dir%72, c_dir/72);
        Creature best2(b, 0);
        c_dir = place_random(best2);
        game.put_creature(&best2, c_dir%72, c_dir/72);
        Creature best3(b, 0);
        c_dir = place_random(best3);
        game.put_creature(&best3, c_dir%72, c_dir/72);
        Creature best4(b, 0);
        c_dir = place_random(best4);
        game.put_creature(&best4, c_dir%72, c_dir/72);
        Creature best5(b, 0);
        c_dir = place_random(best5);
        game.put_creature(&best5, c_dir%72, c_dir/72);
        Creature best6(b, 0);
        c_dir = place_random(best6);
        game.put_creature(&best6, c_dir%72, c_dir/72);
        Creature best7(b, 0);
        c_dir = place_random(best7);
        game.put_creature(&best7, c_dir%72, c_dir/72);
        Creature best8(b, 0);
        c_dir = place_random(best8);
        game.put_creature(&best8, c_dir%72, c_dir/72);
        Creature best9(b, 0);
        c_dir = place_random(best9);
        game.put_creature(&best9, c_dir%72, c_dir/72);
        Creature best10(b, 0);
        c_dir = place_random(best10);
        game.put_creature(&best10, c_dir%72, c_dir/72);


        for(int i = 0; i <= 9; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        for(int i = 10; i <= 1000; i++) {
            if(i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                game.print_board(cout);
            }
            darwin_run(game, 1);
        }
        cout << endl;     
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

    // ----------
    // darwin 7x12
    // ----------

    try {
        cout << "*** Darwin 7x12 ***" << endl;
        srand(0);

        GameBoard game (7, 12);

        Creature trap(t, 2);
        game.put_creature(&trap, 0, 0);

        Creature hopper(h, 1);
        game.put_creature(&hopper, 3, 2);

        Creature rover(r, 0);
        game.put_creature(&rover, 5, 4);

        Creature trap2(t, 3);
        game.put_creature(&trap2, 6, 8);

        for(int i = 0; i <= 5; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        cout << endl;

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

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3X3 ***" << endl;
        srand(0);

        GameBoard game (3, 3);

        Creature hopper(h, 2);
        game.put_creature(&hopper, 0, 0);

        Creature hopper1(h, 2);
        game.put_creature(&hopper1, 0, 1);

        Creature hopper2(h, 2);
        game.put_creature(&hopper2, 0, 2);

        Creature hopper3(h, 2);
        game.put_creature(&hopper3, 1, 0);

        Creature hopper4(h, 2);
        game.put_creature(&hopper4, 1, 1);

        Creature hopper5(h, 2);
        game.put_creature(&hopper5, 1, 2);

        Creature trap6(t, 2);
        game.put_creature(&trap6, 2, 0);

        Creature trap7(h, 2);
        game.put_creature(&trap7, 2, 1);


        Creature rover(r, 0);
        game.put_creature(&rover, 2, 2);

        for(int i = 0; i <= 5; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        cout << endl;

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
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


  try {
        cout << "*** Darwin 72x72 all Hoppers Two Rovers ***" << endl;
        srand(0);

        GameBoard game (72, 72);
        int c_dir;

        // Ignore variable names, focus on what species they are.
        Creature food1(h, 0);
        c_dir = place_random(food1);
        game.put_creature(&food1, c_dir%72, c_dir/72);
        Creature food2(h, 0);
        c_dir = place_random(food2);
        game.put_creature(&food2, c_dir%72, c_dir/72);
        Creature food3(h, 0);
        c_dir = place_random(food3);
        game.put_creature(&food3, c_dir%72, c_dir/72);
        Creature food4(h, 0);
        c_dir = place_random(food4);
        game.put_creature(&food4, c_dir%72, c_dir/72);
        Creature food5(h, 0);
        c_dir = place_random(food5);
        game.put_creature(&food5, c_dir%72, c_dir/72);
        Creature food6(h, 0);
        c_dir = place_random(food6);
        game.put_creature(&food6, c_dir%72, c_dir/72);
        Creature food7(h, 0);
        c_dir = place_random(food7);
        game.put_creature(&food7, c_dir%72, c_dir/72);
        Creature food8(h, 0);
        c_dir = place_random(food8);
        game.put_creature(&food8, c_dir%72, c_dir/72);
        Creature food9(h, 0);
        c_dir = place_random(food9);
        game.put_creature(&food9, c_dir%72, c_dir/72);
        Creature food10(h, 0);
        c_dir = place_random(food10);
        game.put_creature(&food10, c_dir%72, c_dir/72);
        Creature hopper1(h, 0);
        c_dir = place_random(hopper1);
        game.put_creature(&hopper1, c_dir%72, c_dir/72);
        Creature hopper2(h, 0);
        c_dir = place_random(hopper2);
        game.put_creature(&hopper2, c_dir%72, c_dir/72);
        Creature hopper3(h, 0);
        c_dir = place_random(hopper3);
        game.put_creature(&hopper3, c_dir%72, c_dir/72);
        Creature hopper4(h, 0);
        c_dir = place_random(hopper4);
        game.put_creature(&hopper4, c_dir%72, c_dir/72);
        Creature hopper5(h, 0);
        c_dir = place_random(hopper5);
        game.put_creature(&hopper5, c_dir%72, c_dir/72);
        Creature hopper6(h, 0);
        c_dir = place_random(hopper6);
        game.put_creature(&hopper6, c_dir%72, c_dir/72);
        Creature hopper7(h, 0);
        c_dir = place_random(hopper7);
        game.put_creature(&hopper7, c_dir%72, c_dir/72);
        Creature hopper8(h, 0);
        c_dir = place_random(hopper8);
        game.put_creature(&hopper8, c_dir%72, c_dir/72);
        Creature hopper9(h, 0);
        c_dir = place_random(hopper9);
        game.put_creature(&hopper9, c_dir%72, c_dir/72);
        Creature hopper10(h, 0);
        c_dir = place_random(hopper10);
        game.put_creature(&hopper10, c_dir%72, c_dir/72);
        Creature rover1(h, 0);
        c_dir = place_random(rover1);
        game.put_creature(&rover1, c_dir%72, c_dir/72);
        Creature rover2(h, 0);
        c_dir = place_random(rover2);
        game.put_creature(&rover2, c_dir%72, c_dir/72);
        Creature rover3(h, 0);
        c_dir = place_random(rover3);
        game.put_creature(&rover3, c_dir%72, c_dir/72);
        Creature rover4(h, 0);
        c_dir = place_random(rover4);
        game.put_creature(&rover4, c_dir%72, c_dir/72);
        Creature rover5(h, 0);
        c_dir = place_random(rover5);
        game.put_creature(&rover5, c_dir%72, c_dir/72);
        Creature rover6(h, 0);
        c_dir = place_random(rover6);
        game.put_creature(&rover6, c_dir%72, c_dir/72);
        Creature rover7(h, 0);
        c_dir = place_random(rover7);
        game.put_creature(&rover7, c_dir%72, c_dir/72);
        Creature rover8(h, 0);
        c_dir = place_random(rover8);
        game.put_creature(&rover8, c_dir%72, c_dir/72);
        Creature rover9(h, 0);
        c_dir = place_random(rover9);
        game.put_creature(&rover9, c_dir%72, c_dir/72);
        Creature rover10(h, 0);
        c_dir = place_random(rover10);
        game.put_creature(&rover10, c_dir%72, c_dir/72);
        Creature trap1(h, 0);
        c_dir = place_random(trap1);
        game.put_creature(&trap1, c_dir%72, c_dir/72);
        Creature trap2(h, 0);
        c_dir = place_random(trap2);
        game.put_creature(&trap2, c_dir%72, c_dir/72);
        Creature trap3(h, 0);
        c_dir = place_random(trap3);
        game.put_creature(&trap3, c_dir%72, c_dir/72);
        Creature trap4(h, 0);
        c_dir = place_random(trap4);
        game.put_creature(&trap4, c_dir%72, c_dir/72);
        Creature trap5(h, 0);
        c_dir = place_random(trap5);
        game.put_creature(&trap5, c_dir%72, c_dir/72);
        Creature trap6(h, 0);
        c_dir = place_random(trap6);
        game.put_creature(&trap6, c_dir%72, c_dir/72);
        Creature trap7(h, 0);
        c_dir = place_random(trap7);
        game.put_creature(&trap7, c_dir%72, c_dir/72);
        Creature trap8(h, 0);
        c_dir = place_random(trap8);
        game.put_creature(&trap8, c_dir%72, c_dir/72);
        Creature trap9(h, 0);
        c_dir = place_random(trap9);
        game.put_creature(&trap9, c_dir%72, c_dir/72);
        Creature trap10(h, 0);
        c_dir = place_random(trap10);
        game.put_creature(&trap10, c_dir%72, c_dir/72);
        Creature best1(h, 0);
        c_dir = place_random(best1);
        game.put_creature(&best1, c_dir%72, c_dir/72);
        Creature best2(h, 0);
        c_dir = place_random(best2);
        game.put_creature(&best2, c_dir%72, c_dir/72);
        Creature best3(h, 0);
        c_dir = place_random(best3);
        game.put_creature(&best3, c_dir%72, c_dir/72);
        Creature best4(h, 0);
        c_dir = place_random(best4);
        game.put_creature(&best4, c_dir%72, c_dir/72);
        Creature best5(h, 0);
        c_dir = place_random(best5);
        game.put_creature(&best5, c_dir%72, c_dir/72);
        Creature best6(h, 0);
        c_dir = place_random(best6);
        game.put_creature(&best6, c_dir%72, c_dir/72);
        Creature best7(h, 0);
        c_dir = place_random(best7);
        game.put_creature(&best7, c_dir%72, c_dir/72);
        Creature best8(h, 0);
        c_dir = place_random(best8);
        game.put_creature(&best8, c_dir%72, c_dir/72);

        //Two rovers
        Creature r1(r, 0);
        c_dir = place_random(r1);
        game.put_creature(&r1, c_dir%72, c_dir/72);


        Creature r2(r, 0);
        c_dir = place_random(r2);
        game.put_creature(&r2, c_dir%72, c_dir/72);


        for(int i = 0; i <= 9; i++){
            cout << "Turn = " << i << "." << endl;
            game.print_board(cout);
            darwin_run(game, 1); 
            cout << endl;
        }
        for(int i = 10; i <= 1000; i++) {
            if(i%100 == 0) {
                cout << "Turn = " << i << "." << endl;
                game.print_board(cout);
            }
            darwin_run(game, 1);
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        48 Hoppers
        2 Rovers
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




