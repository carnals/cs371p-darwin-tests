//----------------------------
// Jacob Kovar
// jrk2593
// CS371P 10 am - 11 am
// Professor Glenn Downing
// Project 4 - Darwin's World
// 11-07-13
//----------------------------

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

    % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

    % valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <string>   // ==
#include <cstdlib>   // rand, srand
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

// -------------------------------
// defines to test private methods
// -------------------------------
#define private public
#define protected public
#define class struct

#include "Darwin.h"

// -----------
// TestDarwin
// -----------


// -------------
// Species Tests
// -------------

// -------------------
// Species Constructor
// -------------------

TEST(Darwin, sconstructior_1)
{
    Species test("test");
    ASSERT_TRUE(test.name == "test");
}

TEST(Darwin, sconstructior_2)
{
    std::string name("test");
    Species test(name);
    ASSERT_TRUE(test.name == "test");
}

TEST(Darwin, ssconstructior_3)
{
    std::string name("");
    
    try
    {
        Species test(name);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }   
}

// -------------------
// Species::operator==
// -------------------

TEST(Darwin, sequal_1)
{
    Species stest("test");
    Species stest2("test");

    ASSERT_TRUE(stest == stest2);
}

TEST(Darwin, sequal_2)
{
    Species stest("test");
    Species stest2("test2");

    ASSERT_FALSE(stest == stest2);
}

TEST(Darwin, sequal_3)
{
    Species stest("test");
    Species stest2("test");
    stest2.addInstruction(HOP);

    ASSERT_FALSE(stest == stest2);
}

// -------------------
// Species::operator!=
// -------------------

TEST(Darwin, snequal_1)
{
    Species stest("test");
    Species stest2("test2");

    ASSERT_TRUE(stest != stest2);
}

TEST(Darwin, snequal_2)
{
    Species stest("test");
    Species stest2("test");
    stest.addInstruction(HOP);
    stest2.addInstruction(HOP, 1);

    ASSERT_TRUE(stest != stest2);
}

TEST(Darwin, snequal_3)
{
    Species stest("test");
    Species stest2("test");
    stest2.addInstruction(HOP);

    ASSERT_TRUE(stest != stest2);
}

// -----------------------
// Species::addInstruction
// -----------------------

TEST(Darwin, addIns_1)
{
    Species test("test");
    
    ASSERT_TRUE(test.actVector.size() == (unsigned int)0);
    ASSERT_TRUE(test.argVector.size() == (unsigned int)0);
    
    test.addInstruction(HOP);
    test.addInstruction(LEFT);
    test.addInstruction(RIGHT);
    test.addInstruction(INFECT);
    test.addInstruction(IF_ENEMY, 1);
    test.addInstruction(IF_EMPTY, 2);
    test.addInstruction(IF_RANDOM, 3);
    test.addInstruction(IF_WALL, 4);
    test.addInstruction(GO, 5);
    
    ASSERT_TRUE(test.actVector[0] == HOP);
    ASSERT_TRUE(test.actVector[1] == LEFT);
    ASSERT_TRUE(test.actVector[2] == RIGHT);
    ASSERT_TRUE(test.actVector[3] == INFECT);
    ASSERT_TRUE(test.actVector[4] == IF_ENEMY);
    ASSERT_TRUE(test.actVector[5] == IF_EMPTY);
    ASSERT_TRUE(test.actVector[6] == IF_RANDOM);
    ASSERT_TRUE(test.actVector[7] == IF_WALL);
    ASSERT_TRUE(test.actVector[8] == GO);
    
    ASSERT_TRUE(test.argVector[0] == 0);
    ASSERT_TRUE(test.argVector[1] == 0);
    ASSERT_TRUE(test.argVector[2] == 0);
    ASSERT_TRUE(test.argVector[3] == 0);
    ASSERT_TRUE(test.argVector[4] == 1);
    ASSERT_TRUE(test.argVector[5] == 2);
    ASSERT_TRUE(test.argVector[6] == 3);
    ASSERT_TRUE(test.argVector[7] == 4);
    ASSERT_TRUE(test.argVector[8] == 5);
    
    ASSERT_TRUE(test.actVector.size() == (unsigned int)9);
    ASSERT_TRUE(test.argVector.size() == (unsigned int)9);
}

TEST(Darwin, addIns_2)
{
    Species test("test");
    
    ASSERT_TRUE(test.actVector.size() == (unsigned int)0);
    ASSERT_TRUE(test.argVector.size() == (unsigned int)0);
    
    for(int i = 0; i < 100; i++)
    {
        test.addInstruction(HOP);
    }
    
    ASSERT_TRUE(test.actVector.size() == (unsigned int)100);
    ASSERT_TRUE(test.argVector.size() == (unsigned int)100);
    
    for(int i = 0; i < 100; i++)
    {
        ASSERT_TRUE(test.actVector[i] == HOP);
        ASSERT_TRUE(test.argVector[i] == 0);
    }
}

TEST(Darwin, addIns_3)
{
    Species test("test");
    
    try
    {
        test.addInstruction(GO, -1);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
        
    }
}

// ------------------------
// Species::nextInstruction
// ------------------------

TEST(Darwin, snxtInstr_1)
{
    Species test("test");
    
    test.addInstruction(HOP);
    Instruction i = test.nextInstruction(0);
    ASSERT_TRUE(i == HOP);
}

TEST(Darwin, snxtInstr_2)
{
    Species test("test");
    
    test.addInstruction(HOP);
    test.addInstruction(LEFT);
    test.addInstruction(RIGHT);
    test.addInstruction(INFECT);
    test.addInstruction(IF_ENEMY, 1);
    test.addInstruction(IF_EMPTY, 2);
    test.addInstruction(IF_RANDOM, 3);
    test.addInstruction(IF_WALL, 4);
    test.addInstruction(GO, 5);
    
    Instruction in;
    
    for(int i = 0; i < 9; i++)
    {
        in = test.nextInstruction(i);
        
        switch(in)
        {
            case HOP:           break;
            case LEFT:          break;
            case RIGHT:         break;
            case INFECT:        break;
            case IF_ENEMY:      break;
            case IF_RANDOM:     break;
            case IF_WALL:       break;
            case IF_EMPTY:      break;
            case GO:            break;
            default: ASSERT_TRUE(false);
        }
    }
}

TEST(Darwin, snxtInstr_3)
{
    Species test("test");   
    test.addInstruction(HOP);
    
    try
    {
        test.nextInstruction(-1);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
}

// --------------------------
// Species::getInstructionArg
// --------------------------

TEST(Darwin, getInstrArg_1)
{
    Species test("test");
    
    test.addInstruction(GO,0);
    
    int x = test.getInstructionArg(0);
    ASSERT_TRUE(x == 0);
}

TEST(Darwin, getInstrArg_2)
{
    Species test("test");

    for(int i = 0; i < 100; i++)
    {
        test.addInstruction(HOP, i);
    }
    
    for(int i = 0; i < 100; i++)
    {
        int x = test.getInstructionArg(i);
        ASSERT_TRUE(x == i);
    }
}

TEST(Darwin, getInstrArg_3)
{
    Species test("test");
    test.addInstruction(HOP);
    
    try
    {
        test.getInstructionArg(-1);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
}

// ------------------
// Species::printSelf
// ------------------

/*TEST(Darwin, sprint_1)
{
    
}

TEST(Darwin, sprint_2)
{

}

TEST(Darwin, sprint_3)
{

}*/

// --------------
// Creature Tests
// --------------

// --------------------
// Creature Constructor
// --------------------

TEST(Darwin, cconstructior_1)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.species == &stest);
    ASSERT_TRUE(ctest.dir == EAST);
    ASSERT_TRUE(ctest.pc == 0);
}

TEST(Darwin, cconstructior_2)
{
    Species stest("test");
    
    Creature ctest(&stest, WEST);
    Creature ctest2(&stest, EAST);
    
    ASSERT_TRUE(ctest.species == ctest2.species);
    ASSERT_TRUE(ctest.dir != ctest2.dir);
    ASSERT_TRUE(ctest.pc == ctest2.pc);
    
    ASSERT_TRUE(&ctest.species != &ctest2.species);
    ASSERT_TRUE(&ctest.dir != &ctest2.dir);
    ASSERT_TRUE(&ctest.pc != &ctest2.pc);
}

TEST(Darwin, cconstructior_3)
{   
    try
    {
        Creature ctest(0, EAST);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

// --------------------
// Creature::operator==
// --------------------

TEST(Darwin, cequal_1)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Creature ctest2(&stest, EAST);

    ASSERT_TRUE(ctest == ctest2);
}

TEST(Darwin, cequal_2)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Creature ctest2(&stest, WEST);

    ASSERT_FALSE(ctest == ctest2);
}

TEST(Darwin, cequal_3)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Species stest2("test");
    Creature ctest2(&stest2, EAST);

    ASSERT_TRUE(ctest == ctest2);
}

// --------------------
// Creature::operator!=
// --------------------

TEST(Darwin, cnequal_1)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Creature ctest2(&stest, WEST);

    ASSERT_TRUE(ctest != ctest2);
}

TEST(Darwin, cnequal_2)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Species stest2("test2");
    Creature ctest2(&stest2, EAST);

    ASSERT_TRUE(ctest != ctest2);
}

TEST(Darwin, cnequal_3)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    Creature ctest2(&stest, EAST);
    ctest2.pc = 1;

    ASSERT_TRUE(ctest != ctest2);
}

// -------------------------
// Creature::nextInstruction
// -------------------------

TEST(Darwin, cnxtInstr_1)
{
    Species stest("test");
    stest.addInstruction(HOP);
    stest.addInstruction(GO,0);
    
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    Instruction i = ctest.nextInstruction(0);
    
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 1);
    
    i = ctest.nextInstruction(0);
    
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 1);
}

TEST(Darwin, cnxtInstr_2)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 9);
    stest.addInstruction(IF_EMPTY, 7);
    stest.addInstruction(IF_RANDOM, 5);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.nextInstruction(0);
    
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 8);
}

TEST(Darwin, cnxtInstr_3)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 9);
    stest.addInstruction(IF_EMPTY, 7);
    stest.addInstruction(IF_RANDOM, 5);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    Instruction i = ctest.nextInstruction(&cenemy);
    
    ASSERT_TRUE(i == INFECT);
    ASSERT_TRUE(ctest.pc == 10);
}

TEST(Darwin, cnxtInstr_4)
{
    srand(0);

    Species stest("test");
    stest.addInstruction(IF_ENEMY, 9);
    stest.addInstruction(IF_EMPTY, 7);
    stest.addInstruction(IF_RANDOM, 5);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.nextInstruction(&ctest);
    
    ASSERT_TRUE(i == LEFT || i == RIGHT);
    ASSERT_TRUE(ctest.pc == 4 || ctest.pc == 6);
}

TEST(Darwin, cnxtInstr_5)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 9);
    stest.addInstruction(IF_EMPTY, 7);
    stest.addInstruction(IF_WALL, 5);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.nextInstruction(&ctest);
    
    ASSERT_TRUE(i == RIGHT);
    ASSERT_TRUE(ctest.pc == 6);
}

TEST(Darwin, cnxtInstr_6)
{
    Species stest("test");
    stest.addInstruction(HOP);
    stest.addInstruction(GO,7);
    
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    try
    {
        Instruction i = ctest.nextInstruction(0);
        
        ASSERT_TRUE(i == HOP);
        ASSERT_TRUE(ctest.pc == 1);
        
        i = ctest.nextInstruction(0);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
        
    }
}

TEST(Darwin, cnxtInstr_7)
{
    Species stest("test");
    stest.addInstruction(HOP);
    
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    try
    {
        Instruction i = ctest.nextInstruction(0);
        
        ASSERT_TRUE(i == HOP);
        ASSERT_TRUE(ctest.pc == 1);
        
        i = ctest.nextInstruction(0);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
        
    }
}

TEST(Darwin, cnxtInstr_8)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    try
    {
        ctest.nextInstruction(0);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
        
    }
}

// -----------------------
// Creature::checkIfEnemy
// -----------------------

TEST(Darwin, ckIfEn_1)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 2);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfEnemy(&ctest);
    ASSERT_TRUE(i == LEFT);
    ASSERT_TRUE(ctest.pc == 2);
}

TEST(Darwin, ckIfEn_2)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 2);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 3);
    stest.addInstruction(INFECT);
    
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    Instruction i = ctest.checkIfEnemy(&cenemy);
    ASSERT_TRUE(i == INFECT);
    ASSERT_TRUE(ctest.pc == 4);
}

TEST(Darwin, ckIfEn_3)
{
    Species stest("test");
    stest.addInstruction(IF_ENEMY, 3);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(INFECT);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfEnemy(0);
    ASSERT_TRUE(i == LEFT);
    ASSERT_TRUE(ctest.pc == 2);
}

// ----------------------
// Creature::checkIfEmpty
// ----------------------

TEST(Darwin, ckIfEm_1)
{
    Species stest("test");
    stest.addInstruction(IF_EMPTY, 3);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfEmpty(0);
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 4);
}

TEST(Darwin, ckIfEm_2)
{
    Species stest("test");
    stest.addInstruction(IF_EMPTY, 3);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfEmpty(&ctest);
    ASSERT_TRUE(i == LEFT);
    ASSERT_TRUE(ctest.pc == 2);
}

TEST(Darwin, ckIfEm_3)
{
    Species stest("test");
    stest.addInstruction(IF_EMPTY, 3);
    stest.addInstruction(LEFT);
    stest.addInstruction(GO, 0);
    stest.addInstruction(HOP);
    
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    Instruction i = ctest.checkIfEmpty(&cenemy);
    ASSERT_TRUE(i == LEFT);
    ASSERT_TRUE(ctest.pc == 2);
}

// ---------------------
// Creature::checkIfWall
// ---------------------

TEST(Darwin, ckIfWll_1)
{
    Species stest("test");
    stest.addInstruction(IF_WALL, 3);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(LEFT);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfWall(&ctest);
    ASSERT_TRUE(i == LEFT);
    ASSERT_TRUE(ctest.pc == 4);
}

TEST(Darwin, ckIfWll_2)
{
    Species stest("test");
    stest.addInstruction(IF_WALL, 3);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(LEFT);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfWall(0);
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 2);
}

TEST(Darwin, ckIfWll_3)
{
    Species stest("test");
    stest.addInstruction(IF_WALL, 3);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(LEFT);
    
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    Instruction i = ctest.checkIfWall(&cenemy);
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 2);
}

// -----------------------
// Creature::checkIfRandom
// -----------------------

TEST(Darwin, ckIfRn_1)
{
    srand(0);

    Species stest("test");
    stest.addInstruction(IF_RANDOM, 2);
    stest.addInstruction(LEFT);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfRandom(0);
    ASSERT_TRUE(i == LEFT || i == RIGHT);
    ASSERT_TRUE(ctest.pc == 2 || ctest.pc == 3);
}

TEST(Darwin, ckIfRn_2)
{
    srand(0);

    Species stest("test");
    stest.addInstruction(IF_RANDOM, 2);
    stest.addInstruction(LEFT);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.checkIfRandom(&ctest);
    ASSERT_TRUE(i == LEFT || i == RIGHT);
    ASSERT_TRUE(ctest.pc == 2 || ctest.pc == 3);
}

TEST(Darwin, ckIfRn_3)
{
    srand(0);

    Species stest("test");
    stest.addInstruction(IF_RANDOM, 2);
    stest.addInstruction(LEFT);
    stest.addInstruction(RIGHT);
    stest.addInstruction(GO, 0);
    
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    Instruction i = ctest.checkIfRandom(&cenemy);
    ASSERT_TRUE(i == LEFT || i == RIGHT);
    ASSERT_TRUE(ctest.pc == 2 || ctest.pc == 3);
}

// ------------
// Creature::go
// ------------

TEST(Darwin, go_1)
{
    Species stest("test");
    stest.addInstruction(GO, 1);
    stest.addInstruction(GO, 5);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(GO, 2);
    stest.addInstruction(GO, 4);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.go(0);
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 3);
}

TEST(Darwin, go_2)
{
    Species stest("test");
    stest.addInstruction(GO, 1);
    stest.addInstruction(GO, 5);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(GO, 2);
    stest.addInstruction(GO, 4);
    
    Creature ctest(&stest, EAST);
    
    Instruction i = ctest.go(&ctest);
    ASSERT_TRUE(i == HOP);
    ASSERT_TRUE(ctest.pc == 3);
}

TEST(Darwin, go_3)
{
    Species stest("test");
    stest.addInstruction(GO, 1);
    stest.addInstruction(GO, 5);
    stest.addInstruction(HOP);
    stest.addInstruction(GO, 0);
    stest.addInstruction(GO, 7);
    stest.addInstruction(GO, 4);
    
    Creature ctest(&stest, EAST);
    
    try
    {
        ctest.go(0);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
    
}

// ------------------
// Creature::turnLeft
// ------------------

TEST(Darwin, tL_1)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnLeft();
    
    ASSERT_TRUE(ctest.dir == WEST);
    ASSERT_TRUE(ctest.pc == 1);
}

TEST(Darwin, tL_2)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnLeft();
    ctest.turnLeft();
    ctest.turnLeft();
    ctest.turnLeft();
    
    ASSERT_TRUE(ctest.dir == NORTH);
    ASSERT_TRUE(ctest.pc == 4);
}

TEST(Darwin, tL_3)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnLeft();
    ctest.turnLeft();
    ctest.turnRight();
    ctest.turnRight();
    
    ASSERT_TRUE(ctest.dir == NORTH);
    ASSERT_TRUE(ctest.pc == 4);
}

// -------------------
// Creature::turnRight
// --------------------

TEST(Darwin, tR_1)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnRight();
    
    ASSERT_TRUE(ctest.dir == EAST);
    ASSERT_TRUE(ctest.pc == 1);
}

TEST(Darwin, tR_2)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnRight();
    ctest.turnRight();
    ctest.turnRight();
    ctest.turnRight();
    
    ASSERT_TRUE(ctest.dir == NORTH);
    ASSERT_TRUE(ctest.pc == 4);
}

TEST(Darwin, tR_3)
{
    Species stest("test");
    Creature ctest(&stest, NORTH);
    
    ASSERT_TRUE(ctest.pc == 0);
    
    ctest.turnRight();
    ctest.turnRight();
    ctest.turnLeft();
    ctest.turnLeft();
    
    ASSERT_TRUE(ctest.dir == NORTH);
    ASSERT_TRUE(ctest.pc == 4);
}

// ------------------------
// Creature::infectCreature
// ------------------------

TEST(Darwin, inCr_1)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    Species senemy("enemy");
    Creature cenemy(&senemy, EAST);
    
    ASSERT_TRUE(cenemy.pc == 0);
    cenemy.pc = 4;
    ASSERT_TRUE(cenemy.pc == 4);
    
    ctest.infectCreature(&cenemy);
    
    ASSERT_TRUE(cenemy.pc == 0);
    ASSERT_TRUE(cenemy.species == ctest.species);
    ASSERT_TRUE(&cenemy.species != &ctest.species);
}

TEST(Darwin, inCr_2)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.pc == 0);
    ctest.pc = 4;
    ASSERT_TRUE(ctest.pc == 4);
    
    ctest.infectCreature(&ctest);
    
    ASSERT_TRUE(ctest.pc == 5);
}

TEST(Darwin, inCr_3)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    Creature cfriend(&stest, EAST);
    
    ASSERT_TRUE(cfriend.pc == 0);
    cfriend.pc = 4;
    ASSERT_TRUE(cfriend.pc == 4);
    
    ctest.infectCreature(&cfriend);
    
    ASSERT_TRUE(cfriend.pc == 4);
    ASSERT_TRUE(cfriend.species == ctest.species);
    ASSERT_TRUE(&cfriend.species != &ctest.species);
}

// ----------------
// Creature::getDir
// ----------------

TEST(Darwin, getDir_1)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.getDir() == ctest.dir);
}

TEST(Darwin, getDir_2)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.getDir() == ctest.dir);
    ctest.turnLeft();
    ASSERT_TRUE(ctest.getDir() == ctest.dir);
}

TEST(Darwin, getDir_3)
{
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    ASSERT_TRUE(ctest.getDir() == ctest.dir);
    ctest.turnRight();
    ASSERT_TRUE(ctest.getDir() == ctest.dir);
}

// ------------------
// Creature::printSelf
// ------------------

/*TEST(Darwin, print_1)
{
    
}

TEST(Darwin, print_2)
{

}

TEST(Darwin, print_3)
{

}*/

// -------------
// Darwin Tests
// -------------

// -------------------
// Darwin::Constructor
// -------------------

TEST(Darwin, dconstructor_1)
{
    Darwin test(10,10);
    
    ASSERT_TRUE(test.row == 10);
    ASSERT_TRUE(test.col == 10);
    ASSERT_TRUE(test.creatures.size() == (unsigned int)0);
    ASSERT_TRUE(test.addedToGrid.size() == (unsigned int)0);
    ASSERT_TRUE(test.grid.capacity() == (unsigned int)10);
    ASSERT_TRUE(test.grid[0].capacity() == (unsigned int)10);
}

TEST(Darwin, dconstructor_2)
{
    try
    {
        Darwin g(0,0);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

// --------------------
// Darwin::loadCreature
// --------------------

TEST(Darwin, ldCR_1)
{
    Darwin g(1,1);
    
    ASSERT_TRUE(g.creatures.size() == (unsigned int)0);
    ASSERT_TRUE(g.addedToGrid.size() == (unsigned int)0);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    g.loadCreature(ctest);
    ASSERT_TRUE(g.creatures.size() == (unsigned int)1);
    ASSERT_TRUE(g.addedToGrid.size() == (unsigned int)1);
}

TEST(Darwin, ldCR_2)
{
    Darwin g(1,1);
    
    ASSERT_TRUE(g.creatures.size() == (unsigned int)0);
    ASSERT_TRUE(g.addedToGrid.size() == (unsigned int)0);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    for(int i = 0; i < 100; i++)
    {
        g.loadCreature(ctest);
    }
    
    ASSERT_TRUE(g.creatures.size() == (unsigned int)100);
    ASSERT_TRUE(g.addedToGrid.size() == (unsigned int)100);
}

// -----------------
// Darwin::addToGrid
// -----------------

TEST(Darwin, atg_1)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    ASSERT_TRUE(*g.grid[0][0] == ctest);
}

TEST(Darwin, atg_2)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    
    try
    {
        g.addToGrid(0, -1, 0);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
}

TEST(Darwin, atg_3)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    
    try
    {
        g.addToGrid(0, 0, -1);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
}

TEST(Darwin, atg_4)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    
    try
    {
        g.addToGrid(0, -1, -1);
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range&)
    {
    
    }
}

TEST(Darwin, atg_5)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    
    try
    {
        g.addToGrid(-1, 0, 0);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

TEST(Darwin, atg_6)
{
    Darwin g(10,10);
    
    Species stest("test");
    Creature ctest(&stest, EAST);
    
    g.loadCreature(ctest);
    
    try
    {
        g.addToGrid(1, 0, 0);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

TEST(Darwin, atg_7)
{
    Darwin g(10,10);
    
    Species stest("test");
    
    g.loadCreature(Creature(&stest, EAST));
    g.loadCreature(Creature(&stest, NORTH));
    
    try
    {
        g.addToGrid(0, 0, 0);
        g.addToGrid(1, 0, 0);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

TEST(Darwin, atg_8)
{
    Darwin g(10,10);
    
    Species stest("test");
    
    g.loadCreature(Creature(&stest, EAST));
    g.loadCreature(Creature(&stest, NORTH));
    
    try
    {
        g.addToGrid(0, 0, 0);
        g.addToGrid(0, 9, 9);
        ASSERT_TRUE(false);
    }
    catch(const std::invalid_argument&)
    {
    
    }
}

// -----------------
// Darwin::printGrid
// -----------------
/*
TEST(Darwin, print_1)
{
    
}

TEST(Darwin, print_2)
{

}

TEST(Darwin, print_3)
{

}*/

// ----------------
// Darwin::nextTurn
// ----------------

/*TEST(Darwin, nT_1)
{
    
}

TEST(Darwin, nT_2)
{

}

TEST(Darwin, nT_3)
{

}*/

// ------------------
// Darwin::moveObject
// ------------------

TEST(Darwin, mvObj_1)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.moveObject(0,0, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[0][0] == ctest);
}

TEST(Darwin, mvObj_2)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.moveObject(0,0, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[0][0] == ctest);
}

TEST(Darwin, mvObj_3)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.moveObject(0,0, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[0][0] == ctest);
}

TEST(Darwin, mvObj_4)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.moveObject(0,0, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[0][0] == ctest);
}

TEST(Darwin, mvObj_5)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(g.grid[1][1] == 0);
    ASSERT_TRUE(*g.grid[0][1] == ctest);
}

TEST(Darwin, mvObj_6)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(g.grid[1][1] == 0);
    ASSERT_TRUE(*g.grid[1][0] == ctest);
}

TEST(Darwin, mvObj_7)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr != 0);
    ASSERT_TRUE(g.grid[1][1] == 0);
    ASSERT_TRUE(*g.grid[2][1] == ctest);
}

TEST(Darwin, mvObj_8)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr != 0);
    ASSERT_TRUE(g.grid[1][1] == 0);
    ASSERT_TRUE(*g.grid[1][2] == ctest);
}

TEST(Darwin, mvObj_9)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 0, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[1][1] == ctest);
}

TEST(Darwin, mvObj_10)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 1, 2);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[1][1] == ctest);
}

TEST(Darwin, mvObj_11)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 2, 1);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[1][1] == ctest);
}

TEST(Darwin, mvObj_12)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 1, 0);
    
    Creature* cr = g.moveObject(1,1, dir);
    ASSERT_TRUE(cr == 0);
    ASSERT_TRUE(*g.grid[1][1] == ctest);
}

// ------------------------
// Darwin::getObjectInfront
// ------------------------

TEST(Darwin, gtObjFr_1)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.getObjectInfront(0,0, dir);
    ASSERT_TRUE(*cr == ctest);
}

TEST(Darwin, gtObjFr_2)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.getObjectInfront(0,0, dir);
    ASSERT_TRUE(*cr == ctest);
}

TEST(Darwin, gtObjFr_3)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.getObjectInfront(0,0, dir);
    ASSERT_TRUE(*cr == ctest);
}

TEST(Darwin, gtObjFr_4)
{
    Darwin g(1,1);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 0, 0);
    
    Creature* cr = g.getObjectInfront(0,0, dir);
    ASSERT_TRUE(*cr == ctest);
}

TEST(Darwin, gtObjFr_5)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(cr == 0);
}

TEST(Darwin, gtObjFr_6)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(cr == 0);
}

TEST(Darwin, gtObjFr_7)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(cr == 0);
}

TEST(Darwin, gtObjFr_8)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    g.loadCreature(ctest);
    g.addToGrid(0, 1, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(cr == 0);
}

TEST(Darwin, gtObjFr_9)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = NORTH;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 0, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(*cr == cblock);
}

TEST(Darwin, gtObjFr_10)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = EAST;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 1, 2);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(*cr == cblock);
}

TEST(Darwin, gtObjFr_11)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = SOUTH;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 2, 1);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(*cr == cblock);
}

TEST(Darwin, gtObjFr_12)
{
    Darwin g(3,3);
    
    Species stest("test");
    Direction dir = WEST;
    Creature ctest(&stest, dir);
    
    Species sblock("block");
    Creature cblock(&sblock, dir);
    
    g.loadCreature(ctest);
    g.loadCreature(cblock);
    g.addToGrid(0, 1, 1);
    g.addToGrid(1, 1, 0);
    
    Creature* cr = g.getObjectInfront(1,1, dir);
    ASSERT_TRUE(*cr == cblock);
}