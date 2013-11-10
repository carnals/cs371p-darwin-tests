// -----------------------------
// /cs371p-darwin/TestDarwin.c++
// Copyright (C) 2013
// CS371p Fall 2013
// Kevin Tran
// -----------------------------


#include <iostream>
#include <sstream>
#include <string> 
#include <stdexcept>

#include "gtest/gtest.h"

#define private public

#include "Darwin.h"


// -----------------------
// Test Instruction class
// -----------------------

TEST(Instruction, constructor1)
{
    Instruction one("one", 1);

    ASSERT_EQ("one", one._inst);
    ASSERT_EQ(1, one._param);
}


TEST(Instruction, constructor2)
{
    Instruction two("two", 1);

    ASSERT_EQ("two", two._inst);
    ASSERT_EQ(1, two._param);
}


TEST(Instruction, constructor3)
{
    Instruction test("test", 3);

    ASSERT_EQ("test", test._inst);
    ASSERT_EQ(3, test._param);
}


// ------------------
// Test Species class
// ------------------


TEST(Species, def_constructor1) 
{
    Species test;

    ASSERT_EQ('.', test.myName());
}


TEST(Species, def_constructor2)
{
    Species test;
    test.addInstruction("one", 1);

    ASSERT_EQ('.', test.myName());

    Instruction one = test.instruct(0);

    ASSERT_EQ("one", one._inst);
    ASSERT_EQ(1, one._param);
}


TEST(Species, def_constructor3)
{
    Species test;
    test.addInstruction("one", 1);
    test.addInstruction("two", 2);

    ASSERT_EQ('.', test.myName());

    Instruction one = test.instruct(1);

    ASSERT_EQ("two", one._inst);
    ASSERT_EQ(2, one._param);
}


TEST(Species, name_constructor1)
{
    Species test('a');

    ASSERT_EQ('a', test.myName());
}


TEST(Species, name_constructor2)
{
    Species test('b');
    test.addInstruction("one", 1);

    ASSERT_EQ('b', test.myName());

    Instruction one = test.instruct(0);

    ASSERT_EQ("one", one._inst);
    ASSERT_EQ(1, one._param);
}


TEST(Species, name_constructor3)
{
    Species test('c');
    test.addInstruction("one", 1);
    test.addInstruction("two", 2);

    ASSERT_EQ('c', test.myName());

    Instruction one = test.instruct(1);

    ASSERT_EQ("two", one._inst);
    ASSERT_EQ(2, one._param);
}


TEST(Species, addInstruction1)
{
    Species test('a');
    test.addInstruction("one", 1);

    ASSERT_EQ('a', test.myName());

    Instruction one = test.instruct(0);

    ASSERT_EQ("one", one._inst);
    ASSERT_EQ(1, one._param);
}


TEST(Species, addInstruction2)
{
    Species test('b');
    test.addInstruction("one", 1);
    test.addInstruction("one", 1);
    test.addInstruction("three", 3);
    test.addInstruction("one", 1);
    test.addInstruction("one", 1);

    ASSERT_EQ('b', test.myName());

    Instruction three = test.instruct(2);

    ASSERT_EQ("three", three._inst);
    ASSERT_EQ(3, three._param);
}


TEST(Species, addInstruction3)
{
    Species test('c');
    test.addInstruction("one", 1);
    test.addInstruction("two", 2);
    test.addInstruction("three", 3);
    test.addInstruction("four", 4);
    test.addInstruction("five", 5);
    test.addInstruction("six", 6);
    test.addInstruction("seven", 7);
    test.addInstruction("eight", 8);
    test.addInstruction("nine", 9);
    test.addInstruction("ten", 10);

    ASSERT_EQ('c', test.myName());

    Instruction ten = test.instruct(9);

    ASSERT_EQ("ten", ten._inst);
    ASSERT_EQ(10, ten._param);
}


TEST(Species, myName1)
{
    Species test;
    ASSERT_EQ('.', test.myName());
}


TEST(Species, myName2)
{
    Species test('A');
    ASSERT_EQ('A', test.myName());
    ASSERT_TRUE(test.myName() != 'a');
}


TEST(Species, myName3)
{
    Species test('z');
    ASSERT_EQ('z', test.myName());
}


TEST(Species, instruct1)
{
    Species test('a');
    test.addInstruction("one", 1);

    ASSERT_EQ('a', test.myName());

    Instruction one = test.instruct(0);

    ASSERT_EQ("one", one._inst);
    ASSERT_EQ(1, one._param);
}


TEST(Species, instruct2)
{
    Species test('b');
    test.addInstruction("one", 1);
    test.addInstruction("one", 1);
    test.addInstruction("one", 3);
    test.addInstruction("one", 1);
    test.addInstruction("one", 1);

    ASSERT_EQ('b', test.myName());

    Instruction three = test.instruct(2);

    ASSERT_EQ("one", three._inst);
    ASSERT_EQ(3, three._param);
}


TEST(Species, instruct3)
{
    Species test('c');
    test.addInstruction("one", 0);
    test.addInstruction("two", 0);
    test.addInstruction("three", 0);
    test.addInstruction("four", 0);
    test.addInstruction("five", 0);
    test.addInstruction("six", 0);
    test.addInstruction("seven", 0);
    test.addInstruction("eight", 0);
    test.addInstruction("nine", 0);
    test.addInstruction("ten", 0);

    ASSERT_EQ('c', test.myName());

    Instruction ten = test.instruct(0);

    ASSERT_EQ("one", ten._inst);
    ASSERT_EQ(0, ten._param);
}


// --------------------
// Test Creature class
// --------------------


TEST(Creature, def_constructor1)
{
    Creature test;

    ASSERT_EQ(0, test._pc);
    ASSERT_EQ('n', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, def_constructor2)
{
    Creature test;
    test.changePC(5);

    ASSERT_EQ(5, test._pc);
    ASSERT_EQ('n', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, def_constructor3)
{
    Creature test;
    test.incrPC();
    test.turnRight();

    ASSERT_EQ(1, test._pc);
    ASSERT_EQ('e', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, constructor1)
{
    Species a('a');
    Creature test(&a, 'e');

    ASSERT_EQ('a', test.speciesType());
    ASSERT_EQ(0, test._pc);
    ASSERT_EQ('e', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, constructor2)
{
    Species a('b');    
    Creature test(&a, 's');
    test.changePC(5);

    ASSERT_EQ('b', test.speciesType());
    ASSERT_EQ(5, test._pc);
    ASSERT_EQ('s', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, constructor3)
{
    Species a('c');
    Creature test(&a, 'w');
    test.incrPC();
    test.turnRight();

    ASSERT_EQ('c', test.speciesType());
    ASSERT_EQ(1, test._pc);
    ASSERT_EQ('n', test._dir);
    ASSERT_EQ(0, test._turnMoved);
}


TEST(Creature, infect1)
{
    Species sa('a');
    Species sb('b');
    Creature ca(&sa, 'n');
    Creature cb(&sb, 's');

    ca.infect(&cb);

    ASSERT_EQ('a', cb.speciesType());
    ASSERT_EQ(0, cb._pc);
    ASSERT_EQ('s', cb._dir);
    ASSERT_EQ(0, cb._turnMoved);
}


TEST(Creature, infect2)
{
    Species sa('a');
    Species sb('b');
    Creature ca(&sa, 'n');
    Creature cb(&sb, 's');

    cb.changePC(5);
    ca.infect(&cb);
    cb.incrPC();

    ASSERT_EQ('a', cb.speciesType());
    ASSERT_EQ(1, cb._pc);
    ASSERT_EQ('s', cb._dir);
    ASSERT_EQ(0, cb._turnMoved);
}


TEST(Creature, infect3)
{
    Species sa('a');
    Species sb('b');
    Creature ca(&sa, 'n');
    Creature cb(&sb, 's');

    ca.infect(&cb);
    ca.infect(&cb);
    ca.infect(&cb);
    ca.infect(&cb);
    ca.infect(&cb);


    ASSERT_EQ('a', cb.speciesType());
    ASSERT_EQ(0, cb._pc);
    ASSERT_EQ('s', cb._dir);
    ASSERT_EQ(0, cb._turnMoved);
}


TEST(Creature, instruct1)
{
    Species a('c');
    a.addInstruction("zero", 0);

    Creature test(&a, 'w');

    Instruction i = test.instruct();

    ASSERT_EQ("zero", i._inst);
    ASSERT_EQ(0, i._param);
}


TEST(Creature, instruct2)
{
    Species a('c');
    a.addInstruction("zero", 0);
    a.addInstruction("one", 0);
    a.addInstruction("two", 0);
    a.addInstruction("three", 0);
    a.addInstruction("four", 0);

    Creature test(&a, 'w');
    test.incrPC();

    Instruction i = test.instruct();

    ASSERT_EQ("one", i._inst);
    ASSERT_EQ(0, i._param);
}


TEST(Creature, instruct3)
{
    Species a('c');
    a.addInstruction("zero", 0);
    a.addInstruction("one", 0);
    a.addInstruction("two", 0);
    a.addInstruction("three", 0);
    a.addInstruction("four", 0);

    Creature test(&a, 'w');
    test.changePC(2);

    Instruction i = test.instruct();

    ASSERT_EQ("two", i._inst);
    ASSERT_EQ(0, i._param);
}


TEST(Creature, changePC1)
{
    Species a('c');
    Creature test(&a, 'w');
    test.changePC(0); 

    ASSERT_EQ(0, test._pc);
}


TEST(Creature, changePC2)
{
    Species a('c');
    Creature test(&a, 'w');
    test.changePC(5); 

    ASSERT_EQ(5, test._pc);
}


TEST(Creature, changePC3)
{
    Species a('c');
    Creature test(&a, 'w');
    test.changePC(10); 
    test.changePC(10); 
    test.changePC(10); 
    test.changePC(10); 
    test.changePC(10); 

    ASSERT_EQ(10, test._pc);
}


TEST(Creature, incrPC1)
{
    Species a('c');
    Creature test(&a, 'w');
    test.incrPC(); 

    ASSERT_EQ(1, test._pc);    
}


TEST(Creature, incrPC2)
{
    Species a('c');
    Creature test(&a, 'w');
    test.incrPC(); 
    test.incrPC(); 
    test.incrPC(); 
    test.incrPC(); 
    test.incrPC(); 

    ASSERT_EQ(5, test._pc);    
}


TEST(Creature, incrPC3)
{
    Species a('c');
    Creature test(&a, 'w');
    test.changePC(5);
    test.incrPC(); 

    ASSERT_EQ(6, test._pc);    
}


TEST(Creature, turnLeft1)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnLeft();

    ASSERT_EQ('w', test._dir);     
}


TEST(Creature, turnLeft2)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnLeft();
    test.turnLeft();

    ASSERT_EQ('s', test._dir);     
}


TEST(Creature, turnLeft3)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnLeft();
    test.turnLeft();
    test.turnLeft();
    test.turnLeft();

    ASSERT_EQ('n', test._dir);     
}


TEST(Creature, turnRight1)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnRight();

    ASSERT_EQ('e', test._dir);     
}


TEST(Creature, turnRight2)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnRight();
    test.turnRight();

    ASSERT_EQ('s', test._dir);     
}


TEST(Creature, turnRight3)
{
    Species a('c');
    Creature test(&a, 'n');
    test.turnRight();
    test.turnRight();
    test.turnRight();
    test.turnRight();

    ASSERT_EQ('n', test._dir);     
}


TEST(Creature, speciesType1)
{
    Species sa('a');
    Creature ca(&sa, 'n');

    ASSERT_EQ('a', ca.speciesType());
}


TEST(Creature, speciesType2)
{
    Species sa('a');
    Species sb('b');
    Creature ca(&sa, 'n');
    Creature cb(&sb, 's');

    ca.infect(&cb);

    ASSERT_EQ('a', cb.speciesType());
}


TEST(Creature, speciesType3)
{
    Species sa('a');
    Creature ca(&sa, 'n');

    ca.turnRight();
    ca.turnRight();
    ca.turnRight();
    ca.turnRight();

    ASSERT_EQ('a', ca.speciesType());
}


// ------------------
// Test Darwin class
// ------------------


TEST(Darwin, constructor1)
{
    Darwin world(5, 10);

    ASSERT_EQ(5, world._world.size());
    ASSERT_EQ(10, world._world[0].size());
}


TEST(Darwin, constructor2)
{
    Darwin world(2, 4);
    std::ostringstream w;

    world.printWorld(w);
    ASSERT_EQ("Turn = 0.\n  0123\n0 ....\n1 ....\n\n", w.str());
}


TEST(Darwin, constructor3)
{
    Darwin world(5, 5);

    ASSERT_TRUE(world.validRange(0, 0));
    ASSERT_TRUE(world.validRange(0, 4));
    ASSERT_TRUE(world.validRange(4, 0));
    ASSERT_TRUE(world.validRange(4, 4));
}


TEST(Darwin, validRange1)
{
    Darwin world(5, 5);

    ASSERT_TRUE(world.validRange(0, 0));
    ASSERT_TRUE(world.validRange(0, 4));
    ASSERT_TRUE(world.validRange(4, 0));
    ASSERT_TRUE(world.validRange(4, 4));
}


TEST(Darwin, validRange2)
{
    Darwin world(100, 100);

    ASSERT_TRUE(world.validRange(0, 0));
    ASSERT_TRUE(world.validRange(0, 99));
    ASSERT_TRUE(world.validRange(99, 0));
    ASSERT_TRUE(world.validRange(99, 99));
}


TEST(Darwin, validRange3)
{
    Darwin world(100, 100);

    ASSERT_TRUE(!world.validRange(-1, -1));
    ASSERT_TRUE(!world.validRange(100, 100));
    ASSERT_TRUE(!world.validRange(1000, 1000));
    ASSERT_TRUE(!world.validRange(50, 100));
}


TEST(Darwin, addCreature1)
{
    std::ostringstream w;
    Darwin world(5, 5);
    Species sa('a');
    Creature ca(&sa, 'n');

    world.addCreature(ca, 0, 0);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  01234\n0 a....\n1 .....\n2 .....\n3 .....\n4 .....\n\n", w.str());
}


TEST(Darwin, addCreature2)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    Creature allCreature[6];

    allCreature[0] = Creature(&sa, 'n');
    world.addCreature(allCreature[0], 0, 0);
    allCreature[1] = Creature(&sa, 's');
    world.addCreature(allCreature[1], 1, 1);
    allCreature[2] = Creature(&sa, 'e');
    world.addCreature(allCreature[2], 2, 2);
    allCreature[3] = Creature(&sa, 'w');
    world.addCreature(allCreature[3], 0, 2);
    allCreature[4] = Creature(&sa, 'n');
    world.addCreature(allCreature[4], 2, 0);
    allCreature[5] = Creature(&sa, 's');
    world.addCreature(allCreature[5], 0, 1);

    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 aaa\n1 .a.\n2 a.a\n\n", w.str());
}


TEST(Darwin, addCreature3)
{
    std::ostringstream w;
    Darwin world(1, 10);
    Species sa('a');
    Creature allCreature[5];
    
    for (int i = 0; i < 5; i++) {
        allCreature[i] = Creature(&sa, 'e');
        world.addCreature(allCreature[i], 0, i*2+1);
    }
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  0123456789\n0 .a.a.a.a.a\n\n", w.str());
}


TEST(Darwin, simulate1)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("hop", 0);
    sa.addInstruction("go", 0);
    Creature allCreature[6];

    allCreature[0] = Creature(&sa, 'n');
    world.addCreature(allCreature[0], 0, 0);
    allCreature[1] = Creature(&sa, 's');
    world.addCreature(allCreature[1], 1, 1);
    allCreature[2] = Creature(&sa, 'e');
    world.addCreature(allCreature[2], 2, 2);
    allCreature[3] = Creature(&sa, 'w');
    world.addCreature(allCreature[3], 0, 2);
    allCreature[4] = Creature(&sa, 'n');
    world.addCreature(allCreature[4], 2, 0);
    allCreature[5] = Creature(&sa, 's');
    world.addCreature(allCreature[5], 0, 1);

    world.simulate(10, true, w);

    ASSERT_EQ("Turn = 0.\n  012\n0 aaa\n1 .a.\n2 a.a\n\nTurn = 1.\n  012\n0 aaa\n1 a..\n2 .aa\n\nTurn = 2.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 3.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 4.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 5.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 6.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 7.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 8.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 9.\n  012\n0 aa.\n1 aa.\n2 .aa\n\nTurn = 10.\n  012\n0 aa.\n1 aa.\n2 .aa\n\n", w.str());
}


TEST(Darwin, simulate2)
{
    std::ostringstream w;
    Darwin world(4, 4);
    Species sa('a');
    sa.addInstruction("hop", 0);
    sa.addInstruction("go", 0);
    Creature allCreature[4];

    allCreature[0] = Creature(&sa, 'e');
    world.addCreature(allCreature[0], 0, 0);
    allCreature[1] = Creature(&sa, 'e');
    world.addCreature(allCreature[1], 1, 0);
    allCreature[2] = Creature(&sa, 'e');
    world.addCreature(allCreature[2], 2, 0);
    allCreature[3] = Creature(&sa, 'e');
    world.addCreature(allCreature[3], 3, 0);

    world.simulate(5, true, w);

    ASSERT_EQ( "Turn = 0.\n  0123\n0 a...\n1 a...\n2 a...\n3 a...\n\nTurn = 1.\n  0123\n0 .a..\n1 .a..\n2 .a..\n3 .a..\n\nTurn = 2.\n  0123\n0 ..a.\n1 ..a.\n2 ..a.\n3 ..a.\n\nTurn = 3.\n  0123\n0 ...a\n1 ...a\n2 ...a\n3 ...a\n\nTurn = 4.\n  0123\n0 ...a\n1 ...a\n2 ...a\n3 ...a\n\nTurn = 5.\n  0123\n0 ...a\n1 ...a\n2 ...a\n3 ...a\n\n", w.str());
}


TEST(Darwin, simulate3)
{
    std::ostringstream w;
    Darwin world(1, 10);
    Species sa('a');
    sa.addInstruction("hop", 0);
    sa.addInstruction("go", 0);
    Creature allCreature[10];

    allCreature[0] = Creature(&sa, 'e');
    world.addCreature(allCreature[0], 0, 0);
    allCreature[1] = Creature(&sa, 'e');
    world.addCreature(allCreature[1], 0, 1);
    allCreature[2] = Creature(&sa, 'e');
    world.addCreature(allCreature[2], 0, 2);
    allCreature[3] = Creature(&sa, 'e');
    world.addCreature(allCreature[3], 0, 3);
    allCreature[4] = Creature(&sa, 'e');
    world.addCreature(allCreature[4], 0, 4);
    allCreature[5] = Creature(&sa, 'e');
    world.addCreature(allCreature[5], 0, 5);
    allCreature[6] = Creature(&sa, 'e');
    world.addCreature(allCreature[6], 0, 6);
    allCreature[7] = Creature(&sa, 'e');
    world.addCreature(allCreature[7], 0, 7);
    allCreature[8] = Creature(&sa, 'e');
    world.addCreature(allCreature[8], 0, 8);
    allCreature[9] = Creature(&sa, 'e');
    world.addCreature(allCreature[9], 0, 9);

    world.simulate(1, true, w);

    ASSERT_EQ("Turn = 0.\n  0123456789\n0 aaaaaaaaaa\n\nTurn = 1.\n  0123456789\n0 aaaaaaaaaa\n\n", w.str());
}


TEST(Darwin, execute1)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("hop", 0);

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.execute(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 .a.\n2 ...\n\n", w.str());
}


TEST(Darwin, execute2)
{
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("left", 0);

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.execute(&ca, 2, 1);

    ASSERT_EQ('w', ca._dir);
}


TEST(Darwin, execute3)
{
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("right", 0);
    sa.addInstruction("right", 0);
    sa.addInstruction("right", 0);
    sa.addInstruction("right", 0);

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);

    ASSERT_EQ('n', ca._dir);
    world.execute(&ca, 2, 1);
    ++world._iteration;
    ASSERT_EQ('e', ca._dir);
    world.execute(&ca, 2, 1);
    ++world._iteration;
    ASSERT_EQ('s', ca._dir);
    world.execute(&ca, 2, 1);
    ++world._iteration;
    ASSERT_EQ('w', ca._dir);
    world.execute(&ca, 2, 1);
    ++world._iteration;
    ASSERT_EQ('n', ca._dir);
}


TEST(Darwin, hop1)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.hop(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ('n', ca._dir);
    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 .a.\n2 ...\n\n", w.str());
}


TEST(Darwin, hop2)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.hop(&ca, 2, 1);
    world.hop(&ca, 1, 1);
    world.printWorld(w);

    ASSERT_EQ('n', ca._dir);
    ASSERT_EQ("Turn = 0.\n  012\n0 .a.\n1 ...\n2 ...\n\n", w.str());
}


TEST(Darwin, hop3)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.hop(&ca, 2, 1);
    world.hop(&ca, 1, 1);
    world.hop(&ca, 0, 1);
    world.printWorld(w);

    ASSERT_EQ('n', ca._dir);
    ASSERT_EQ("Turn = 0.\n  012\n0 .a.\n1 ...\n2 ...\n\n", w.str());
}


TEST(Darwin, infect1)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.infect(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 ...\n2 .a.\n\n", w.str());
}


TEST(Darwin, infect2)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 'n');
    Creature cb(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.addCreature(cb, 1, 1);
    world.infect(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 .a.\n2 .a.\n\n", w.str());
}


TEST(Darwin, infect3)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    Species sb('b');

    Creature ca(&sa, 'n');
    Creature cb(&sb, 'n');
    world.addCreature(ca, 2, 1);
    world.addCreature(cb, 1, 1);
    world.infect(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 .a.\n2 .a.\n\n", w.str());
}


TEST(Darwin, if_empty1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 2, 1);
    bool result = world.if_empty(&ca, 2, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_empty2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    bool result = world.if_empty(&ca, 1, 1);

    ASSERT_EQ(true, result);
}


TEST(Darwin, if_empty3)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    Creature cb(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    bool result = world.if_empty(&ca, 1, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_wall1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    bool result = world.if_wall(&ca, 1, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_wall2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 2, 1);
    bool result = world.if_wall(&ca, 2, 1);

    ASSERT_EQ(true, result);
}


TEST(Darwin, if_wall3)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    Creature cb(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    bool result = world.if_wall(&ca, 1, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_random1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    Creature cb(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    world.if_random();

    ASSERT_TRUE(true);
}


TEST(Darwin, if_random2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 2, 1);
    world.if_random();

    ASSERT_TRUE(true);
}


TEST(Darwin, if_random3)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    Creature cb(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    world.if_random();

    ASSERT_TRUE(true);
}


TEST(Darwin, if_enemy1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    bool result = world.if_enemy(&ca, 1, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_enemy2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 2, 1);
    bool result = world.if_enemy(&ca, 2, 1);

    ASSERT_FALSE(result);
}


TEST(Darwin, if_enemy3)
{
    Darwin world(3, 3);
    Species sa('a');
    Species sb('b');

    Creature ca(&sa, 's');
    Creature cb(&sb, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    bool result = world.if_enemy(&ca, 1, 1);

    ASSERT_EQ(true, result);
}


TEST(Darwin, go1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.go(&ca, 10);

    ASSERT_EQ(10, ca._pc);
}


TEST(Darwin, go2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 2, 1);
    world.go(&ca, 1);
    world.go(&ca, 2);
    world.go(&ca, 5);

    ASSERT_EQ(5, ca._pc);
}


TEST(Darwin, go3)
{
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("zero", 0);
    sa.addInstruction("one", 1);
    sa.addInstruction("two", 2);

    Creature ca(&sa, 's');
    Creature cb(&sa, 's');
    world.addCreature(ca, 1, 1);
    world.addCreature(cb, 2, 1);
    world.go(&ca, 1);

    Instruction i = ca.instruct();


    ASSERT_EQ("one", i._inst);
    ASSERT_EQ(1, i._param);
}


TEST(Darwin, space_ahead1)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    unsigned int row = 0;
    unsigned int col = 0;
    world.space_ahead(&ca, row, col);

    ASSERT_EQ(1, row);
    ASSERT_EQ(0, col);
}


TEST(Darwin, space_ahead2)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    unsigned int row = 2;
    unsigned int col = 0;
    world.space_ahead(&ca, row, col);

    ASSERT_EQ(3, row);
    ASSERT_EQ(0, col);
}


TEST(Darwin, space_ahead3)
{
    Darwin world(3, 3);
    Species sa('a');

    Creature ca(&sa, 's');
    world.addCreature(ca, 1, 1);
    unsigned int row = 0;
    unsigned int col = 0;
    world.space_ahead(&ca, row, col);
    ca._dir = 'e';
    world.space_ahead(&ca, row, col);

    ASSERT_EQ(1, row);
    ASSERT_EQ(1, col);
}


TEST(Darwin, printWorld1)
{
    Darwin world(2, 4);
    std::ostringstream w;

    world.printWorld(w);
    ASSERT_EQ("Turn = 0.\n  0123\n0 ....\n1 ....\n\n", w.str());
}


TEST(Darwin, printWorld2)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("hop", 0);

    Creature ca(&sa, 'n');
    world.addCreature(ca, 2, 1);
    world.execute(&ca, 2, 1);
    world.printWorld(w);

    ASSERT_EQ("Turn = 0.\n  012\n0 ...\n1 .a.\n2 ...\n\n", w.str());
}


TEST(Darwin, printWorld3)
{
    std::ostringstream w;
    Darwin world(3, 3);
    Species sa('a');
    sa.addInstruction("hop", 0);
    sa.addInstruction("go", 0);
    Creature allCreature[6];

    allCreature[0] = Creature(&sa, 'n');
    world.addCreature(allCreature[0], 0, 0);
    allCreature[1] = Creature(&sa, 's');
    world.addCreature(allCreature[1], 1, 1);
    allCreature[2] = Creature(&sa, 'e');
    world.addCreature(allCreature[2], 2, 2);
    allCreature[3] = Creature(&sa, 'w');
    world.addCreature(allCreature[3], 0, 2);
    allCreature[4] = Creature(&sa, 'n');
    world.addCreature(allCreature[4], 2, 0);
    allCreature[5] = Creature(&sa, 's');
    world.addCreature(allCreature[5], 0, 1);

    world.simulate(10, false, w);
    world.printWorld(w);

    ASSERT_EQ("Turn = 10.\n  012\n0 aa.\n1 aa.\n2 .aa\n\n", w.str());
}
