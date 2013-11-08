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
#include <cstdlib>

#include "Darwin.h"
// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ------------------------------------------------------------
    
    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // -------------------------------------------------------------

    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");


    // -----
    // rover
    // -------------------------------------------------------------

    Species rover('r');
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");


    // ----
    // trap
    // ------------------------------------------------------------

    
    Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    Species best('t');
    best.addInstruction("left");
    best.addInstruction("go 0");


    // ---------------
    // my tests
    // ---------------

    try 
    {
        /*
            make a 1x20 world
            19 foods from spot o,o to o,18 facing west
            1 trap at 0,19 facing west
            40 moves
            print first 10 and every 4th
        */
        cout << "*** Darwin 1x20 Buffet ***" << endl;
        srand(0);
        int i;
        World test(1,20);
        Critter foods[19];
        for(i = 0; i < 19; ++i)
        {
            foods[i] = Critter(WEST, food);
            test.addCritter(0, i, foods[i]);
        }
        Critter crit_trap1 = Critter(WEST, trap);
        test.addCritter(0,19, crit_trap1);

        std::cout << "    Turn: 0" << std::endl;
        test.printWorld(std::cout);

          for(i = 1; i <= 40; ++i)
          {
            test.year();
            if(i <= 10 || i % 4 == 0)
            {
                std::cout << "    Turn: " << i << std::endl;
                test.printWorld(std::cout);
            }
          }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try 
    {
        /*
            make a 1x1 world
            1 food at 0,0 facing west
            4 moves
            print every 
            watch food look for friends
            so cry:'(
        */
        cout << "*** Darwin 1x1 Lonely ***" << endl;
        srand(0);
        World test(1,1);
        
        Critter crit_food1 = Critter(WEST, food);
        test.addCritter(0,0, crit_food1);

        int i;
        std::cout << "    Turn: 0" << std::endl;
        test.printWorld(std::cout);

        for(i = 1; i <= 4; ++i)
        {

          test.year();
          std::cout << "    Turn: " << i << std::endl;
          test.printWorld(std::cout);
        }    
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try 
    {
        /*
            make a 2x2 world
            3 rovers at 0,0 0,1 and 1,0 facing west, north and east
            8 moves
            print every 
            watch the happy rovers hop around as friends
        */
        cout << "*** Darwin 2x2 Circle ***" << endl;
        srand(0);
        World test(2,2);
        
        Critter crit_rover1 = Critter(WEST, rover);
        test.addCritter(0,0, crit_rover1);
        Critter crit_rover2 = Critter(NORTH, rover);
        test.addCritter(0,1, crit_rover2);
        Critter crit_rover3 = Critter(EAST, rover);
        test.addCritter(1,0, crit_rover3);

        int i;
        std::cout << "    Turn: 0" << std::endl;
        test.printWorld(std::cout);

        for(i = 1; i <= 8; ++i)
        {

          test.year();
          std::cout << "    Turn: " << i << std::endl;
          test.printWorld(std::cout);
        }    
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try 
    {
         /*
            make a 4x4 world
            4 rovers on top row facing South
            4 rovers on second row facing west
            4 traps on tird row facing EAst
            4 traps on bottom row facing North
            10 years
            print every 
            the rovers are fed up with the traps trying to 
            take over their home turf
        */
        cout << "*** Darwin 4x4 Gang Fight ***" << endl;
        srand(0);
        World test(4,4);
        
        Critter crit_rover1 = Critter(SOUTH, rover);
        test.addCritter(0,0, crit_rover1);
        Critter crit_rover2 = Critter(SOUTH, rover);
        test.addCritter(0,1, crit_rover2);
        Critter crit_rover3 = Critter(SOUTH, rover);
        test.addCritter(0,2, crit_rover3);
        Critter crit_rover4 = Critter(SOUTH, rover);
        test.addCritter(0,3, crit_rover4);
        Critter crit_rover5 = Critter(WEST, rover);
        test.addCritter(1,0, crit_rover5);
        Critter crit_rover6 = Critter(WEST, rover);
        test.addCritter(1,1, crit_rover6);
        Critter crit_rover7 = Critter(WEST, rover);
        test.addCritter(1,2, crit_rover7);
        Critter crit_rover8 = Critter(WEST, rover);
        test.addCritter(1,3, crit_rover8);

        Critter crit_trap1 = Critter(EAST, trap);
        test.addCritter(2,0, crit_trap1);
        Critter crit_trap2 = Critter(EAST, trap);
        test.addCritter(2,1, crit_trap2);
        Critter crit_trap3 = Critter(EAST, trap);
        test.addCritter(2,2, crit_trap3);
        Critter crit_trap4 = Critter(EAST, trap);
        test.addCritter(2,3, crit_trap4);
        Critter crit_trap5 = Critter(NORTH, trap);
        test.addCritter(3,0, crit_trap5);
        Critter crit_trap6 = Critter(NORTH, trap);
        test.addCritter(3,1, crit_trap6);
        Critter crit_trap7 = Critter(NORTH, trap);
        test.addCritter(3,2, crit_trap7);
        Critter crit_trap8 = Critter(NORTH, trap);
        test.addCritter(3,3, crit_trap8);

        int i;
        std::cout << "    Turn: 0" << std::endl;
        test.printWorld(std::cout);

        for(i = 1; i <= 10; ++i)
        {
          test.year();
          
            std::cout << "    Turn: " << i << std::endl;
            test.printWorld(std::cout);
          
        }    
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try 
    {
        /*
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
        cout << "*** Darwin 2x20 Drag Race ***" << endl;
        srand(0);
        World test(2,20);
        
        Critter crit_hopper1 = Critter(EAST, hopper);
        test.addCritter(0,0, crit_hopper1);
        Critter crit_rover1 = Critter(EAST, rover);
        test.addCritter(1,0, crit_rover1);

        Critter crit_food1 = Critter(WEST, food);
        test.addCritter(0,19, crit_food1);

        Critter crit_food2 = Critter(WEST, food);
        test.addCritter(0,18, crit_food2);

        Critter crit_food3 = Critter(WEST, food);
        test.addCritter(0,17, crit_food3);

        Critter crit_food4 = Critter(WEST, food);
        test.addCritter(0,16, crit_food4);
        
        Critter crit_food5 = Critter(WEST, food);
        test.addCritter(1,19, crit_food5);
        
        Critter crit_food6 = Critter(WEST, food);
        test.addCritter(1,18, crit_food6);
        
        Critter crit_food7 = Critter(WEST, food);
        test.addCritter(1,17, crit_food7);
        
        Critter crit_food8 = Critter(WEST, food);
        test.addCritter(1,16, crit_food8);
        


        int i;
        std::cout << "    Turn: 0" << std::endl;
        test.printWorld(std::cout);

        for(i = 1; i <= 20; ++i)
        {

          test.year();
          std::cout << "    Turn: " << i << std::endl;
          test.printWorld(std::cout);
        }    
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
