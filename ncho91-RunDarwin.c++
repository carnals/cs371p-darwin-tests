// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------
/* Noah Cho, ncho91
   Richard Lage, polt
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

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    Species food = Species(Food);

    food.addInstructions(left, 0);
    food.addInstructions(go, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper = Species(Hopper);

    hopper.addInstructions(hop, 0);
    hopper.addInstructions(go, 0);

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

    Species rover = Species(Rover);

    rover.addInstructions(if_enemy, 9);
    rover.addInstructions(if_empty, 7);
    rover.addInstructions(if_random, 5);
    rover.addInstructions(left, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(right, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(hop, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(infect, 0);
    rover.addInstructions(go, 0);

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

    Species trap = Species(Trap);

    trap.addInstructions(if_enemy, 3);
    trap.addInstructions(left, 0);
    trap.addInstructions(go, 0);
    trap.addInstructions(infect, 0);
    trap.addInstructions(go, 0);

    // ----
    // best
    // ----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: right
     4: go 0
     5: left
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    Species best = Species(Best);

    best.addInstructions(if_enemy, 9);
    best.addInstructions(if_empty, 7);
    best.addInstructions(if_random, 5);
    best.addInstructions(right, 0);
    best.addInstructions(go, 0);
    best.addInstructions(left, 0);
    best.addInstructions(go, 0);
    best.addInstructions(hop, 0);
    best.addInstructions(go, 0);
    best.addInstructions(infect, 0);
    best.addInstructions(go, 0);

    using namespace std;
    cout << boolalpha;

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
        Darwin x(8, 8);

        Creature f1 = Creature(food, East, 0, 0);
        Creature f2 = Creature(food, North, 7, 7);
        Creature h1 = Creature(hopper, North, 3, 3);
        Creature h2 = Creature(hopper, East, 3, 4);
        Creature h3 = Creature(hopper, South, 4, 4);
        Creature h4 = Creature(hopper, West, 4, 3);

        x.addCreature(f1);
        x.addCreature(f2);
        x.addCreature(h1);
        x.addCreature(h2);
        x.addCreature(h3);
        x.addCreature(h4);

        for (int n = 1; n <= 5; n++) {
            std::cout << "TURN #" << n << std::endl;
            //loop to print out
            std::cout << "  ";
            for (int i = 0; i < x._column; i++) {
                std::cout << i % 10;
            }
            std::cout << std::endl;
            for (int i = 0; i < x._row; i++) {
                std::cout << i % 10 << " ";
                for (int j = 0; j < x._column; j++) {
                    std::cout << x.grid[i][j]._s._c;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }
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
        Darwin x(7, 9);

        Creature t1 = Creature(trap, South, 0, 0);
        Creature t2 = Creature(trap, West, 6, 8);
        Creature h1 = Creature(hopper, East, 3, 2);
        Creature r1 = Creature(rover, North, 5, 4);

        x.addCreature(t1);
        x.addCreature(t2);
        x.addCreature(h1);
        x.addCreature(r1);

        for (int n = 1; n <= 5; n++) {
            std::cout << "TURN #" << n << std::endl;
            //loop to print out
            std::cout << "  ";
            for (int i = 0; i < x._column; i++) {
                std::cout << i % 10;
            }
            std::cout << std::endl;
            for (int i = 0; i < x._row; i++) {
                std::cout << i % 10 << " ";
                for (int j = 0; j < x._column; j++) {
                    std::cout << x.grid[i][j]._s._c;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
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
        Darwin x(72, 72);
        vector<Creature> f;
        vector<Creature> h;
        vector<Creature> r;
        vector<Creature> t;
        vector<int> position;
        for (int i = 0; i < 10; i++) {
            randomPosition(x, position);
            f.push_back(Creature(food, randomDirection(), position[0], position[1]));
            x.addCreature(f[i]);
            position.clear();

            randomPosition(x, position);
            h.push_back(Creature(hopper, randomDirection(), position[0], position[1]));
            x.addCreature(h[i]);
            position.clear();

            randomPosition(x, position);
            r.push_back(Creature(rover, randomDirection(), position[0], position[1]));
            x.addCreature(r[i]);
            position.clear();

            randomPosition(x, position);
            t.push_back(Creature(trap, randomDirection(), position[0], position[1]));
            x.addCreature(t[i]);
            position.clear();
        }

        for (int n = 1; n <= 1000; n++) {

            //loop to print out
            if (n <= 10 || n % 100 == 0) {
                std::cout << "TURN #" << n << std::endl;
                std::cout << "  ";
                for (int i = 0; i < x._column; i++) {
                    std::cout << i % 10;
                }
                std::cout << std::endl;
                for (int i = 0; i < x._row; i++) {
                    std::cout << i % 10 << " ";
                    for (int j = 0; j < x._column; j++) {
                        std::cout << x.grid[i][j]._s._c;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }

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
        Darwin x(72, 72);
        vector<Creature> f;
        vector<Creature> h;
        vector<Creature> r;
        vector<Creature> t;
        vector<Creature> b;
        vector<int> position;
        for (int i = 0; i < 10; i++) {
            randomPosition(x, position);
            f.push_back(Creature(food, randomDirection(), position[0], position[1]));
            x.addCreature(f[i]);
            position.clear();

            randomPosition(x, position);
            h.push_back(Creature(hopper, randomDirection(), position[0], position[1]));
            x.addCreature(h[i]);
            position.clear();

            randomPosition(x, position);
            r.push_back(Creature(rover, randomDirection(), position[0], position[1]));
            x.addCreature(r[i]);
            position.clear();

            randomPosition(x, position);
            t.push_back(Creature(trap, randomDirection(), position[0], position[1]));
            x.addCreature(t[i]);
            position.clear();

            randomPosition(x, position);
            b.push_back(Creature(best, randomDirection(), position[0], position[1]));
            x.addCreature(b[i]);
            position.clear();
        }

        for (int n = 1; n <= 1000; n++) {

            //loop to print out
            if (n <= 10 || n % 100 == 0) {
                std::cout << "TURN #" << n << std::endl;
                std::cout << "  ";
                for (int i = 0; i < x._column; i++) {
                    std::cout << i % 10;
                }
                std::cout << std::endl;
                for (int i = 0; i < x._row; i++) {
                    std::cout << i % 10 << " ";
                    for (int j = 0; j < x._column; j++) {
                        std::cout << x.grid[i][j]._s._c;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------
    // darwin 1000x1
    // without best
    // -------------

    try {
        cout << "*** Darwin 1000x1 without Best ***" << endl;
        srand(0);
        /*
        1 Rover
        1 Food
        Both creatures are placed at opposite sides of the grid.
        Prints out beginning and end.
        */
        Darwin x(1000, 1);

        Creature f1 = Creature(food, South, 0, 0);
        Creature r1 = Creature(rover, North, 999, 0);

        x.addCreature(f1);
        x.addCreature(r1);

        for (int n = 1; n <= 1000; n++) {

             //loop to print out
            if (n == 1 || n == 1000) {
                std::cout << "TURN #" << n << std::endl;
                std::cout << "  ";
                for (int i = 0; i < x._column; i++) {
                    std::cout << i % 10;
                }
                std::cout << std::endl;
                for (int i = 0; i < x._row; i++) {
                    std::cout << i % 10 << " ";
                    for (int j = 0; j < x._column; j++) {
                        std::cout << x.grid[i][j]._s._c;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 40x40
    // without best
    // ------------

    try {
        cout << "*** Darwin 40x40 without Best ***" << endl;
        srand(0);
        /* 
        (50^2) - 1 Food
        1 Trap
        The Trap should create a cascading effect of infections.
        After a few turns, there should only be Traps within the grid.
        Prints out beginning and end.
        */
        Darwin x(40,40);

        for (int i = 0; i < x._row; i++) {
            for (int j = 0; j < x._column; j++) {
                x.addCreature(Creature(food, South, i, j));
            }
        }
        x.grid[20][20] = Creature(trap, North, 20, 20);

        for (int n = 1; n <= 100; n++) {

             //loop to print out
            if (n == 1 || n == 100) {
                std::cout << "TURN #" << n << std::endl;
                std::cout << "  ";
                for (int i = 0; i < x._column; i++) {
                    std::cout << i % 10;
                }
                std::cout << std::endl;
                for (int i = 0; i < x._row; i++) {
                    std::cout << i % 10 << " ";
                    for (int j = 0; j < x._column; j++) {
                        std::cout << x.grid[i][j]._s._c;
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 30x30
    // without best
    // ------------

    try {
        cout << "*** Darwin 30x30 without Best ***" << endl;
        srand(0);
        /* 
        Hoppers all around the perimeter of the grid.
        They all move towards each other.
        Prints out every turn.
        Creates a really cool-looking X!
        */
        Darwin x(30,30);

        for (int i = 0; i < x._row; i++) {
            x.addCreature(Creature(hopper, East, i, 0));
            x.addCreature(Creature(hopper, South, 0, i));
            x.addCreature(Creature(hopper, West, i, x._column-1));
            if (i != x._column-1)
                x.addCreature(Creature(hopper, North, x._row-1, i));
        }

        for (int n = 1; n <= 15; n++) {
            std::cout << "TURN #" << n << std::endl;
            std::cout << "  ";
            for (int i = 0; i < x._column; i++) {
                std::cout << i % 10;
            }
            std::cout << std::endl;
            for (int i = 0; i < x._row; i++) {
                std::cout << i % 10 << " ";
                for (int j = 0; j < x._column; j++) {
                    std::cout << x.grid[i][j]._s._c;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 3x3
    // without best
    // ------------

    try {
        cout << "*** Darwin 3x3 without Best ***" << endl;
        srand(0);
        /* 
        1 Trap
        1 Rover
        3 Food
        Trap takes over in just 1 turn after being outnumbered by 4 Rovers.
        Prints out every turn.
        */
        Darwin x(3,3);

        Creature f1 = Creature(food, West, 1, 2);
        Creature f2 = Creature(food, North, 2, 2);
        Creature f3 = Creature(food, North, 2, 1);
        Creature r1 = Creature(rover, East, 1, 0);
        Creature t1 = Creature(trap, North, 0, 1);

        x.addCreature(f1);
        x.addCreature(f2);
        x.addCreature(f3);
        x.addCreature(r1);
        x.addCreature(t1);

        for (int n = 1; n <= 4; n++) {
            std::cout << "TURN #" << n << std::endl;
            std::cout << "  ";
            for (int i = 0; i < x._column; i++) {
                std::cout << i % 10;
            }
            std::cout << std::endl;
            for (int i = 0; i < x._row; i++) {
                std::cout << i % 10 << " ";
                for (int j = 0; j < x._column; j++) {
                    std::cout << x.grid[i][j]._s._c;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 10x10
    // without best
    // ------------

    try {
        cout << "*** Darwin 10x10 without Best ***" << endl;
        srand(0);
        /* 
        4 Hoppers
        Outer perimeter of Traps
        Hoppers hop into wall of traps.
        Prints out every turn.
        */
        Darwin x(10,10);

        Creature h1 = Creature(hopper, North, 4, 4);
        Creature h2 = Creature(hopper, East, 4, 5);
        Creature h3 = Creature(hopper, South, 5, 5);
        Creature h4 = Creature(hopper, West, 5, 4);

        for (int i = 0; i < x._row; i++) {
            x.addCreature(Creature(trap, North, i, 0));
            x.addCreature(Creature(trap, East, 0, i));
            x.addCreature(Creature(trap, South, i, x._column-1));
            x.addCreature(Creature(trap, West, x._row-1, i));
        }

        x.addCreature(h1);
        x.addCreature(h2);
        x.addCreature(h3);
        x.addCreature(h4);

        for (int n = 1; n <= 5; n++) {
            std::cout << "TURN #" << n << std::endl;
            std::cout << "  ";
            for (int i = 0; i < x._column; i++) {
                std::cout << i % 10;
            }
            std::cout << std::endl;
            for (int i = 0; i < x._row; i++) {
                std::cout << i % 10 << " ";
                for (int j = 0; j < x._column; j++) {
                    std::cout << x.grid[i][j]._s._c;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            //go through every creature and have them perform instruction
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    if (x.grid[i][j]._s._type != Empty) {
                        x.doInstruction(x.grid[i][j]);
                    }
                }
            }
            for (int i = 0; i < x._row; i++) {
                for (int j = 0; j < x._column; j++) {
                    x.grid[i][j]._turnPassed = false;
                }
            }
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;
}