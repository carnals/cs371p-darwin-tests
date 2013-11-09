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
     species food('f');
     food.addInstruction(i_left, -1);
     food.addInstruction(i_go, 0);


    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
     species hopper('h');
     hopper.addInstruction(i_hop, -1);
     hopper.addInstruction(i_go, 0);

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
    rover.addInstruction(i_if_enemy, 9);
    rover.addInstruction(i_if_empty, 7);
    rover.addInstruction(i_if_random, 5);
    rover.addInstruction(i_left, -1);
    rover.addInstruction(i_go, 0);
    rover.addInstruction(i_right, -1);
    rover.addInstruction(i_go, 0);
    rover.addInstruction(i_hop, -1);
    rover.addInstruction(i_go, 0);
    rover.addInstruction(i_infect, -1);
    rover.addInstruction(i_go, 0);



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
     trap.addInstruction(i_if_enemy, 3);
     trap.addInstruction(i_left, -1);
     trap.addInstruction(i_go, 0);
     trap.addInstruction(i_infect, -1);
     trap.addInstruction(i_go, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin x(8,8);
        creature f1(food, east);
        
        creature h1(hopper, north);
        creature h2(hopper, east);
        creature h3(hopper, south);
        creature h4(hopper, west);
        creature f2(food, north);


        x.add(f1, 0, 0);
        x.add(f2,7,7);
        x.add(h1,3,3);
        x.add(h2,3,4);
        x.add(h3,4,4);
        x.add(h4,4,3);
        x.printBoard();


        for (int i = 0; i < 5; i++){
            x.simulate();
            x.printBoard();
        }



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
    //     cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        Darwin y(7,9);

        creature t1(trap, south);
        creature h1(hopper, east);
        creature r1(rover, north);
        creature t2(trap, west);


        y.add(t1, 0, 0);
        y.add(h1,3,2);
        y.add(r1,5,4);
        y.add(t2,6,8);
        y.printBoard();

    //     7x9 Darwin
    //     Trap,   facing south, at (0, 0)
    //     Hopper, facing east,  at (3, 2)
    //     Rover,  facing north, at (5, 4)
    //     Trap,   facing west,  at (6, 8)
    //     Simulate 5 moves.
    //     Print every grid.
        for (int i = 0; i < 5; i ++){
            y.simulate();
            y.printBoard();
        }
        
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
        Darwin w(72,72);
        for (int i = 0; i < 10; i++){
            int pos = rand()%5184;
            int x = pos/72;
            int y = pos%72;
            direction d = (direction)(rand()%4);
            creature f(food, d);
            w.add(f, x, y);
        }
        for (int i = 0; i < 10; i++){
            int pos = rand()%5184;
            int x = pos/72;
            int y = pos%72;
            direction d = (direction)(rand()%4);
            creature h(hopper, d);
            w.add(h, x, y);
        }
        for (int i = 0; i < 10; i++){
            int pos = rand()%5184;
            int x = pos/72;
            int y = pos%72;
            direction d = (direction)(rand()%4);
            creature r(rover, d);
            w.add(r, x, y);
        }
        for (int i = 0; i < 10; i++){
            int pos = rand()%5184;
            int x = pos/72;
            int y = pos%72;
            direction d = (direction)(rand()%4);
            creature t(trap, d);
            w.add(t, x, y);
        }
        w.printBoard();

        

        for (int i = 0; i < 1000; i++){
            w.simulate();
            if(w.turn<10){
                w.printBoard();

            }
            if (w.turn%100 == 0){
                w.printBoard();
            }
        }



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
    //     }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}


  // ------------
  // darwin 2x2
  // ------------

  try {
    cout << "*** Darwin 2x2 ***" << endl;
    srand(0);
    /*
                try to place 1000 creatures
                there should only be 4 in the end
                print the result
                */

                Darwin game(2, 2);
                int r;
                int row, col;
                int dir;
                int i;

                // place traps
                for (i = 0; i < 1000; i++) {
                        r = rand() % 4;
                        row = r / 2;
                        col = r % 2;
                        dir = rand() % 4;
                        game.add(creature(trap, (direction)dir), row, col);
                }

                // print the sim
                game.printBoard();

  }
        catch (const invalid_argument&) {
         assert(false);}
        catch (const out_of_range&) {
                  assert(false);}


// ------------
// darwin 1x50
// ------------

try {
cout << "*** Darwin 1x50 ***" << endl;
srand(0);
/*
        place 5 rovers and 5 hoppers in a line
        sim 20 times
        print every 5
        */

        Darwin game(1, 50);

        int i;
        // place rovers
        for (i = 0; i < 5; i++) {
                game.add(creature(rover, east), 0, 10* i);
        }

        // place hoppers
        for (i = 0; i < 5; i++) {
                game.add(creature(hopper, south), 0, 10* i + 5);
        }

        // do the sim
        game.printBoard();

        for (i = 1; i <= 20; i++) {
                game.simulate();

                if (i % 5 == 0) game.printBoard();
        }
}
catch (const invalid_argument&) {
  assert(false);}
catch (const out_of_range&) {
                assert(false);}


// make a 1x20 world
// 19 foods from spot o,o to o,18 facing west
// 1 trap at 0,19 facing west
// 40 moves
// print first 10 and every 4th
    try{
        cout << "*** Darwin 1x20 Buffet ***" << endl;
        srand(0);
        int i;
        Darwin test(1,20);
        for(i = 0; i < 19; ++i)
        {
            creature f(food, west);
            test.add(f,0,i);
        }
    
        creature t(trap, west);
        test.add(t, 0, 19);


        test.printBoard();

          for(i = 1; i <= 40; ++i)
          {
            test.simulate();
            if(i <= 10 || i % 4 == 0)
            {
                test.printBoard();
            }
          }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 7x12 ***" << endl;
        srand(0);

        Darwin myGame(7, 12);
        creature t(trap, south);
        myGame.add(t, 0, 0);
        creature h(hopper, east);
        myGame.add(h, 3, 2);
        creature r(rover,north );
        myGame.add(r, 5, 4);
        creature t2(trap, west);
        myGame.add(t2, 6, 8);

        myGame.printBoard();
        for (int i = 0; i <= 5; i++) {
         //myGame.printBoard();
         myGame.simulate();
         myGame.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

      try {
        cout << "*** Darwin 4x10 without Best ***" << endl;
        srand(0);
        Darwin world(4, 10);
        world.add(creature(trap,east),0,0);
        world.add(creature(trap,east),1,0);
        world.add(creature(trap,east),2,0);
        world.add(creature(trap,east),3,0);
        world.add(creature(trap,east),0,1);
        world.add(creature(trap,east),1,1);
        world.add(creature(trap,east),2,1);
        world.add(creature(trap,east),3,1);

        world.add(creature(rover,east),0,9);
        world.add(creature(rover,east),1,9);
        world.add(creature(rover,east),2,9);
        world.add(creature(rover,east),3,9);

        world.printBoard();
        for (int i = 0; i < 20; ++i)
        {

            world.simulate();
            world.printBoard();
        }
        /*
        in a darwin world of 4 by 10
        8 traps all on the left hand side as much as possible all facing east
        create 4 rovers all on the right side all facing east
        simulate 20 moves
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Arena 3x8 ***" << endl;
        Darwin world(3, 8);
        
        creature c1(trap, south);
        creature c2(trap, east);
        creature c3(trap, north);
        creature c4(trap, east);
        creature c5(hopper, east);

        world.add(c1, 0, 3);
        world.add(c2, 0, 4);
        world.add(c3, 2, 3);
        world.add(c4, 2, 4);
        world.add(c5, 1, 0);

        world.printBoard();
        for (int i = 0; i < 10; i++) {
            world.simulate();
            world.printBoard();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try{
        cout << "Darwin Board Simple 5 x 10 Test"<< endl;
        srand(0);
        Darwin test(5,10);

        creature h(hopper,south);
        creature h1(hopper, north);
        creature r(rover,east);

        test.add(h, 0,0);
        test.add(h1, 4, 9);
        test.add(r, 0, 9);
        test.printBoard();

        for (int i = 0; i < 15; i++){
            test.simulate();
            if (i < 5){
                test.printBoard();
            }
            if (i % 5 == 0){
                test.printBoard();
            }
        }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try{
        cout << "Darwin 25 x 25 Huddle Spread kind of"<< endl;
        srand(0);
        Darwin test(25,25);

        creature t1(trap, north);
        creature t2(trap, north);
        creature t3(trap, north);
        creature t4(trap, north);
        creature r1(rover,east);
        creature r2(rover,west);
        creature r3(rover,east);
        creature r4(rover,west);

        test.add(t1, 0, 0);
        test.add(t2, 0, 24);
        test.add(t3, 24, 24);
        test.add(t4, 24, 0);

        test.add(r1, 12, 12);
        test.add(r2, 12, 13);
        test.add(r3, 13, 12);
        test.add(r4, 13, 13);




        test.printBoard();

        for (int i = 0; i < 15; i++){
            test.simulate();
            test.printBoard();
        }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try{
        cout << "Darwin 8 x 8 Destroy"<< endl;
        srand(0);
        Darwin test(8,8);

        creature t1(trap, north);
        creature t2(trap, north);
        creature t3(trap, north);
        creature t4(trap, north);
        creature r1(rover,east);
        creature r2(rover,west);
        creature r3(rover,east);
        creature r4(rover,west);

        test.add(t1, 0, 0);
        test.add(t2, 0, 7);
        test.add(t3, 7, 7);
        test.add(t4, 7, 0);

        test.add(r1, 4, 3);
        test.add(r2, 4, 4);
        test.add(r3, 5, 3);
        test.add(r4, 5, 4);




        test.printBoard();

        for (int i = 0; i < 15; i++){
            test.simulate();
            test.printBoard();
        }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
