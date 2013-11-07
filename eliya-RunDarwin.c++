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
#include <string>
#include "Darwin.h"


Direction direction(int i){
    if(i == 0)
        return west;
    if(i == 1)
        return north;
    if(i == 2)
        return east;
    if(i == 3)
        return south;
}

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
    Species food;
    food.addInstruction("left");
    food.addInstruction("go 0");
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopper;
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    
    //change rover's right instruction to left for BEST
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
     Species rover; 
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
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
     Species trap; 
     trap.addInstruction("if_enemy 3");
     trap.addInstruction("left");
     trap.addInstruction("go 0");
     trap.addInstruction("infect");
     trap.addInstruction("go 0");


     // ----
    // Best
    // ----


     
    //START MY TESTS 
    try{
        cout << "*** Darwin 10X10 Test I ***" << endl;
        Board game4 (10, 10);
        Creature f1 (food, "f", south, 5, 5);
        Creature h1 (hopper, "h", north, 3, 5);
        Creature h2 (hopper, "h", south, 2, 6);
        Creature h3 (hopper, "h", east, 1, 9);
        Creature h4 (hopper, "h", east, 8, 1);
        Creature r1 (rover, "r", south, 2, 5);
        game4.addCreature(f1, 5, 5);
        game4.addCreature(h1, 3, 5);
        game4.addCreature(h2, 2, 6);
        game4.addCreature(h3, 1, 9);
        game4.addCreature(h4, 8, 1);
        game4.addCreature(r1, 2, 5);

        cout << "Turn = 0." << endl;
        game4.drawBoard();
        for(int i = 1; i < 6; i++){
            cout << "Turn = " << i << "." << endl;
            game4.playRound();
            game4.drawBoard();

        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try{
        cout << "*** Darwin 20X20 Test II ***" << endl;
        srand(0);
        Board game4 (20, 20);
        int randPos, r, c;
        Direction direct;

        for(int i = 1; i < 9; i++){
           randPos = rand() % 400; 
            r = randPos / 20;
            c = randPos % 20; 
            direct = direction(rand() % 4);
            Creature h (hopper, "h", direct, r, c);
            game4.addCreature(h, r, c);
        }

        for(int i = 1; i < 3; i++){
           randPos = rand() % 400; 
            r = randPos / 20;
            c = randPos % 20; 
            direct = direction(rand() % 4);
            Creature rov (rover, "r", direct, r, c);
            game4.addCreature(rov, r, c);
        }

        for(int i = 1; i < 5; i++){
           randPos = rand() % 400; 
            r = randPos / 20;
            c = randPos % 20; 
            direct = direction(rand() % 4);
            Creature f (food, "f", direct, r, c);
            game4.addCreature(f, r, c);
        }

        cout << "Turn = 0." << endl;
        game4.drawBoard();
        for(int i = 1; i < 5; i++){
            cout << "Turn = " << i << "." << endl;
            game4.playRound();
            game4.drawBoard();

        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try{
        cout << "*** Darwin 50X50 Test III ***" << endl;
        srand(0);
        Board game4 (50, 50);
        int randPos, r, c;
        Direction direct;

        for(int i = 1; i < 14; i++){
           randPos = rand() % 2500; 
            r = randPos / 50;
            c = randPos % 50; 
            direct = direction(rand() % 4);
            Creature h (hopper, "h", direct, r, c);
            game4.addCreature(h, r, c);
        }

        for(int i = 1; i < 10; i++){
           randPos = rand() % 2500; 
            r = randPos / 50;
            c = randPos % 50; 
            direct = direction(rand() % 4);
            Creature rov (rover, "r", direct, r, c);
            game4.addCreature(rov, r, c);
        }

        for(int i = 1; i < 10; i++){
           randPos = rand() % 2500; 
            r = randPos / 50;
            c = randPos % 50; 
            direct = direction(rand() % 4);
            Creature f (food, "f", direct, r, c);
            game4.addCreature(f, r, c);
        }

        cout << "Turn = 0." << endl;
        game4.drawBoard();
        for(int i = 1; i < 10; i++){
            cout << "Turn = " << i << "." << endl;
            game4.playRound();
            game4.drawBoard();

        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

     try{
        cout << "*** Darwin 64X64 Test IV ***" << endl;
        srand(0);
        Board game4 (64, 64);
        int randPos, r, c;
        Direction direct;

        for(int i = 1; i < 11; i++){
           randPos = rand() % 4096; 
            r = randPos / 64;
            c = randPos % 64; 
            direct = direction(rand() % 4);
            Creature h (hopper, "h", direct, r, c);
            game4.addCreature(h, r, c);
        }

        for(int i = 1; i < 11; i++){
           randPos = rand() % 4096; 
            r = randPos / 64;
            c = randPos % 64; 
            direct = direction(rand() % 4);
            Creature rov (rover, "r", direct, r, c);
            game4.addCreature(rov, r, c);
        }

        for(int i = 1; i < 11; i++){
           randPos = rand() % 4096; 
            r = randPos / 64;
            c = randPos % 64; 
            direct = direction(rand() % 4);
            Creature t (trap, "t", direct, r, c);
            game4.addCreature(t, r, c);
        }

        for(int i = 1; i < 10; i++){
           randPos = rand() % 4096; 
            r = randPos / 64;
            c = randPos % 64; 
            direct = direction(rand() % 4);
            Creature f (food, "f", direct, r, c);
            game4.addCreature(f, r, c);
        }

        cout << "Turn = 0." << endl;
        game4.drawBoard();
        for(int i = 1; i < 100; i++){
            if(i % 10 == 0){
                cout << "Turn = " << i << "." << endl;
                game4.playRound();
                game4.drawBoard();
            }
        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

 try{
        cout << "*** Darwin 100X100 Test V ***" << endl;
        srand(0);
        Board game4 (100, 100);
        int randPos, r, c;
        Direction direct;

        for(int i = 1; i < 25; i++){
           randPos = rand() % 10000; 
            r = randPos / 100;
            c = randPos % 100; 
            direct = direction(rand() % 4);
            Creature h (hopper, "h", direct, r, c);
            game4.addCreature(h, r, c);
        }

        for(int i = 1; i < 21; i++){
           randPos = rand() % 10000; 
            r = randPos / 100;
            c = randPos % 100; 
            direct = direction(rand() % 4);
            Creature rov (rover, "r", direct, r, c);
            game4.addCreature(rov, r, c);
        }

        for(int i = 1; i < 21; i++){
           randPos = rand() % 10000; 
            r = randPos / 100;
            c = randPos % 100; 
            direct = direction(rand() % 4);
            Creature f (food, "f", direct, r, c);
            game4.addCreature(f, r, c);
        }

        for(int i = 1; i < 21; i++){
           randPos = rand() % 10000; 
            r = randPos / 100;
            c = randPos % 100; 
            direct = direction(rand() % 4);
            Creature t (trap, "t", direct, r, c);
            game4.addCreature(t, r, c);
        }

        cout << "Turn = 0." << endl;
        game4.drawBoard();
        for(int i = 1; i <= 1000; i++){
            if(i < 10){
                cout << "Turn = " << i << "." << endl;
                game4.playRound();
                game4.drawBoard();       
            }
            else if(i % 100 == 0){
                cout << "Turn = " << i << "." << endl;
                game4.playRound();
                game4.drawBoard(); 
            }
            else
                game4.playRound();
        }

    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}




