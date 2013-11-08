// --------------------------------
// projects/Darwin/TestDarwin.c++
// Frank Cerasoli
// Tim Carroll
// --------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin < RunDarwin.in > RunDarwin.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout
#include <fstream> //File input
#include <cassert>  // assert
#include <memory> // allocator
#include <stdexcept>
#include "Darwin.h"

// -----
// read
// -----


// ----
// main
// ----

int main () {
    using namespace std;
    Species specs[5] = {Species(0), Species(1), Species(2), Species(3), Species(4)};

    //Adds instructions for species
    Instruction inst;
        //FOOD
        inst.control = 0;
        inst.id = LEFT;
        specs[0].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[0].addInstruction(inst);

        //HOPPER
        inst.control = 0;
        inst.id = HOP;
        specs[1].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[1].addInstruction(inst);
        
        //ROVER
        inst.control = 1;
        inst.id = IF_ENEMY;
        inst.n = 9;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = IF_EMPTY;
        inst.n = 7;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = IF_RANDOM;
        inst.n = 5;
        specs[2].addInstruction(inst);
        inst.control = 0;
        inst.id = LEFT;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[2].addInstruction(inst);
        inst.control = 0;
        inst.id = RIGHT;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[2].addInstruction(inst);
        inst.control = 0;
        inst.id = HOP;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[2].addInstruction(inst);
        inst.control = 0;
        inst.id = INFECT;
        specs[2].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[2].addInstruction(inst);

        //TRAP
        inst.control = 1;
        inst.id = IF_ENEMY;
        inst.n = 3;
        specs[3].addInstruction(inst);
        inst.control = 0;
        inst.id = LEFT;
        specs[3].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[3].addInstruction(inst);
        inst.control = 0;
        inst.id = INFECT;
        specs[3].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0; 
        specs[3].addInstruction(inst);

        //BEST
        inst.control = 0;
        inst.id = HOP;
        specs[4].addInstruction(inst);
        inst.control = 0;
        inst.id = LEFT;
        specs[4].addInstruction(inst);
        inst.control = 1;
        inst.id = GO;
        inst.n = 0;
        specs[4].addInstruction(inst);


    // Test Case #1
    try {
        cout << "*** Darwin 8x8 ***" << std::endl;
        Game game (8,8);
        game.addCreature(Creature(0,0,&specs[0],2));
        game.addCreature(Creature(3,3,&specs[1],1));
        game.addCreature(Creature(3,4,&specs[1],2));
        game.addCreature(Creature(4,4,&specs[1],3));
        game.addCreature(Creature(4,3,&specs[1],0));
        game.addCreature(Creature(7,7,&specs[0],1));
        runGame(cin, cout, 5, &game);
    }
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }

    // Test Case #2
    try {
        cout << "*** Darwin 7x9 ***" << std::endl;
        Game game (7,9);
        game.addCreature(Creature(0,0,&specs[3],3));
        game.addCreature(Creature(3,2,&specs[1],2));
        game.addCreature(Creature(5,4,&specs[2],1));
        game.addCreature(Creature(6,8,&specs[3],0));
        runGame(cin, cout, 5, &game);
    }
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }
    
    //Test Case #3
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
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int turns = 1000;
        
        int gRows = 72;
        int gCols = 72;
        
        // Create our game
        Game game(gRows,gCols);
        
        int gSize = gRows * gCols;
        
        int       cPos;
        int       cRow;
        int       cCol;
        int cDir;
        int       cNum      = 20;
        int       cNumTypes = 4;
        
        for(int i = 0; i < cNumTypes; i++) {
            for(int j = 0; j < cNum; j++) {
                
                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;
                
                switch(rand() % 4) {
                    case 0:
                        cDir = 0;
                    case 1:
                        cDir = 1;
                    case 2:
                        cDir = 2;
                    case 3:
                        cDir = 3;
                }
                game.addCreature(Creature(cRow, cCol, &specs[i], cDir));
            }
        }
        runGame(cin,cout,turns,&game);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    //  Test Case #4
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
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        int turns = 1000;
        
        int gRows = 72;
        int gCols = 72;
        
        // Create our game
        Game game(gRows,gCols);
        
        int gSize = gRows * gCols;
        
        int       cPos;
        int       cRow;
        int       cCol;
        int cDir;
        int       cNum      = 20;
        int       cNumTypes = 5;
        
        for(int i = 0; i < cNumTypes; i++) {
            for(int j = 0; j < cNum; j++) {
                
                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;
                
                switch(rand() % 4) {
                    case 0:
                        cDir = 0;
                    case 1:
                        cDir = 1;
                    case 2:
                        cDir = 2;
                    case 3:
                        cDir = 3;
                }
                game.addCreature(Creature(cRow, cCol, &specs[i], cDir));
            }
        }
        runGame(cin,cout,turns,&game);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // Test Case #5
    try {
        cout << "*** Darwin 3x3 ***" << std::endl;
        Game game (3,3);
        game.addCreature(Creature(0,0,&specs[3],3));
        game.addCreature(Creature(1,2,&specs[1],2));
        game.addCreature(Creature(2,2,&specs[2],1));
        runGame(cin, cout, 5, &game);
    }
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }

    // Test Case #6
    try {
        cout << "*** Darwin 15x15 ***" << std::endl;
        Game game (15,15);
        game.addCreature(Creature(0,0,&specs[3],3));
        game.addCreature(Creature(3,2,&specs[1],2));
        game.addCreature(Creature(5,4,&specs[2],1));
        game.addCreature(Creature(6,8,&specs[3],0));
        game.addCreature(Creature(7,8,&specs[0],0));
        game.addCreature(Creature(7,9,&specs[0],1));
        game.addCreature(Creature(7,10,&specs[0],2));
        game.addCreature(Creature(7,11,&specs[0],3));
        game.addCreature(Creature(7,12,&specs[0],0));
        game.addCreature(Creature(7,13,&specs[0],0));
        game.addCreature(Creature(13,13,&specs[2],0));
        game.addCreature(Creature(14,12,&specs[3],2));
        runGame(cin, cout, 7, &game);
    }
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }
    
    // Test Case #7
    try {
        cout << "*** Darwin 32x32 Crowded Creatures ***" << std::endl;
        Game game (32,32);
        game.addCreature(Creature(3,2,&specs[1],2));
        game.addCreature(Creature(5,4,&specs[2],1));
        game.addCreature(Creature(6,8,&specs[3],0));
        game.addCreature(Creature(7,8,&specs[0],0));
        game.addCreature(Creature(7,9,&specs[0],1));
        game.addCreature(Creature(7,10,&specs[0],2));
        game.addCreature(Creature(7,11,&specs[0],3));
        game.addCreature(Creature(7,12,&specs[0],0));
        game.addCreature(Creature(7,13,&specs[0],0));
        game.addCreature(Creature(13,13,&specs[2],0));
        game.addCreature(Creature(14,12,&specs[3],2));
        game.addCreature(Creature(31,31,&specs[3],0));
        game.addCreature(Creature(0,31,&specs[3],0));
        game.addCreature(Creature(0,0,&specs[3],2));
        game.addCreature(Creature(31,0,&specs[3],2));
        game.addCreature(Creature(31,1,&specs[2],3));
        game.addCreature(Creature(25,25,&specs[2],0));
        runGame(cin, cout, 15, &game);
    }
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }

    /*
     TEST CASE FROM twpixley
     
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
     Simulate 1000 moves.
     Best MUST outnumber ALL other species for the bonus pts.
     Print the first 10 grids          (i.e. 0, 1, 2...9).
     Print every 100th grid after that (i.e. 100, 200, 300...1000).
     */
    
    try {
        cout << "*** Darwin 50x50 crowded ***" << endl;
        srand(0);
        int turns = 1000;
        
        int gRows = 50;
        int gCols = 50;
        
        // Create our game
        Game game(gRows,gCols);
        
        int gSize = gRows * gCols;
        
        int       cPos;
        int       cRow;
        int       cCol;
        int cDir;
        int       cNum      = 20;
        int       cNumTypes = 4;
        
        for(int i = 0; i < cNumTypes; i++) {
            for(int j = 0; j < cNum; j++) {
                
                cPos = rand() % gSize;
                cRow = cPos / gCols;
                cCol = cPos % gCols;
                
                switch(rand() % 4) {
                    case 0:
                        cDir = 0;
                    case 1:
                        cDir = 1;
                    case 2:
                        cDir = 2;
                    case 3:
                        cDir = 3;
                }
                game.addCreature(Creature(cRow, cCol, &specs[i], cDir));
            }
        }
        runGame(cin,cout,turns,&game);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // TEST CASE FROM ss48333
    // darwin 4x4 rovers
    // ----------
    
    try {
        cout << "*** Darwin 4x4 Cross rovers ***" << endl;
        /*
         8x8 Darwin
         Simulate 3 moves.
         Print every grid.
         */
        srand(0);
        Game game(4, 4);
        
        game.addCreature(Creature(3,0,&specs[2],1));
        game.addCreature(Creature(3,1,&specs[2],1));
        game.addCreature(Creature(3,2,&specs[2],1));
        game.addCreature(Creature(3,3,&specs[2],1));
        game.addCreature(Creature(1,0,&specs[0],1));
        game.addCreature(Creature(1,1,&specs[0],1));
        game.addCreature(Creature(1,2,&specs[0],1));
        game.addCreature(Creature(1,3,&specs[0],1));

        runGame(cin, cout, 3, &game);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // TEST CASE FROM davismc
    // fod_walk_east 4x4
    // ------------
    // hoppers march in a line, like an aircraft carrier fod walk
    try {
        cout << "*** Fod Walk East 4x4 ***" << endl;
        Game game(4, 4);
        game.addCreature(Creature(0,0,&specs[1],2));
        game.addCreature(Creature(1,0,&specs[1],2));
        game.addCreature(Creature(2,0,&specs[1],2));
        game.addCreature(Creature(3,0,&specs[1],2));
        runGame(cin,cout,5,&game);
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    /*
     * TEST CASE FOR austind
     */
    try {
        cout << "*** 1x60 Test for Meeting a Friend ***" << endl;
        /*
         1x60 Darwin
         1 Hopper,   facing east,    at (0, 0)
         1 Hopper,   facing west,    at (0, 59)
         Simulate 29 moves
         Print the first and last grid.
         */
        Game g(1,60);
        
        g.addCreature(Creature(0,0,&specs[1],2));
        g.addCreature(Creature(0,59,&specs[1],0));
        runGame(cin,cout,101,&g);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    /*
     TEST CASE FROM rgriege
     5x5 Darwin
     Trap,   facing north, at (2, 3)
     Rover,  facing north, at (4, 2)
     Rover,  facing east,  at (3, 1)
     Rover,  facing south,  at (0, 4)
     Hopper, facing east,  at (4, 0)
     Simulate 7 moves.
     Print every grid.
     */
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        Game game(5,5);
        game.addCreature(Creature(2,3,&specs[3],1));
        game.addCreature(Creature(4,2,&specs[2],1));
        game.addCreature(Creature(3,1,&specs[2],2));
        game.addCreature(Creature(0,4,&specs[2],3));
        game.addCreature(Creature(4,0,&specs[1],2));
        runGame(cin,cout,7,&game);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
