// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"
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

// -----------
// TestDarwin
// -----------

TEST(Darwin, species1) {

Species food('f');
food.instruction("left");
ASSERT_TRUE(food.name == 'f');
ASSERT_TRUE(food.program[0] == "left");
}

TEST(Darwin, species2) {

Species hopper('b');
hopper.instruction("hop");
ASSERT_TRUE(hopper.name == 'b');
ASSERT_TRUE(hopper.program[0] == "hop");
}

TEST(Darwin, species3) {

Species rover('r');
rover.instruction("if_empty 9");
ASSERT_TRUE(rover.name == 'r');
ASSERT_TRUE(rover.program[0] == "if_empty 9");
}

TEST(Darwin, species4) {

Species trap('t');
trap.instruction("if_enemy 6");
ASSERT_TRUE(trap.name == 't');
ASSERT_TRUE(trap.program[0] == "if_enemy 6");
}

TEST(Darwin, species5) {

Species best('b');
best.instruction("hop");
ASSERT_TRUE(best.name == 'b');
ASSERT_TRUE(best.program[0] == "hop");
}

TEST(Darwin, move1) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <4,4> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(0,0,f1));
}

TEST(Darwin, move2) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <5,5> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(4,4,f1));
}

TEST(Darwin, move3) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <72,72> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(71,71,f1));
}
TEST(Darwin, move4) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <100,100> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(25,98,f1));
}

TEST(Darwin, move5) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <100,100> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(12,67,f1));
}

TEST(Darwin, move6) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <72,72> w;
Creature f1(food, 2);
ASSERT_TRUE(w.move(65,54,f1));
}

TEST(Darwin, execute1) {
Species food('f');
  food.instruction("left");
  food.instruction("go 0");
World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("left", 0, 0));
}

TEST(Darwin, execute2) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("infect", 0, 0));
}

TEST(Darwin, execute3) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("right", 0, 0));
}
TEST(Darwin, execute4) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("hop", 0, 0));
}
TEST(Darwin, execute5) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("hop", 0, 0));
}
TEST(Darwin, execute6) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(24,67,f1);
ASSERT_TRUE(w.execute("left", 24, 67));
}
TEST(Darwin, execute7) {
Species food('f');

World <72,72> w;
Creature f1(food, 2);
w.move(0,0,f1);
ASSERT_TRUE(w.execute("right", 0, 0));
}

TEST(Darwin, frontEnemy1) {
Species best('b');
Species food('f');
World <72,72> w;

Creature b1(best, 2);
Creature b2(food, 0);
w.move(25,25,b1);
w.move(25,26,b2);
ASSERT_TRUE(w.frontEnemy(25,25));
}
TEST(Darwin, frontEnemy2) {
Species best('b');
Species food('f');
World <72,72> w;

Creature b1(best, 1);
Creature b2(food, 0);
w.move(25,25,b1);
w.move(24,25,b2);
ASSERT_TRUE(w.frontEnemy(25,25));
}
TEST(Darwin, frontEnemy3) {
Species best('b');
Species food('f');
World <72,72> w;

Creature b1(best, 3);
Creature b2(food, 0);
w.move(25,25,b1);
w.move(26,25,b2);
ASSERT_TRUE(w.frontEnemy(25,25));
}
TEST(Darwin, frontEnemy4) {
Species best('b');
Species food('f');
World <72,72> w;

Creature b1(best, 0);
Creature b2(food, 0);
w.move(25,25,b1);
w.move(25,24,b2);
ASSERT_TRUE(w.frontEnemy(25,25));
}

TEST(Darwin, frontEmpty1) {

Species best('b');
World<8,8> w;

Creature b1(best,0);
w.move(4,4,b1);
ASSERT_TRUE(w.frontEmpty(4,4));
}
TEST(Darwin, frontWall1) {

Species best('b');
World<8,8> w;

Creature b1(best,0);
w.move(0,0,b1);
ASSERT_TRUE(w.frontWall(0,0));
}

TEST(Darwin, frontWall2) {

Species best('b');
World<8,8> w;

Creature b1(best,1);
w.move(0,3,b1);
ASSERT_TRUE(w.frontWall(0,3));
}
TEST(Darwin, frontWall3) {

Species best('b');
World<8,8> w;

Creature b1(best,0);
w.move(3,0,b1);
ASSERT_TRUE(w.frontWall(3,0));
}
TEST(Darwin, frontWall4) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(7,7,b1);
ASSERT_TRUE(w.frontWall(7,7));
}


TEST(Darwin, nextRow1) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(0,0,b1);

ASSERT_TRUE(w.nextRow(0,3) == 1);

}
TEST(Darwin, nextRow2) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(1,0,b1);

ASSERT_TRUE(w.nextRow(1,3) == 2);

}
TEST(Darwin, nextRow3) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(2,0,b1);

ASSERT_TRUE(w.nextRow(2,3) == 3);

}

TEST(Darwin, nextColumn1) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(2,0,b1);

ASSERT_TRUE(w.nextColumn(2,0) == 1);

}

TEST(Darwin, nextColumn2) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(2,1,b1);

ASSERT_TRUE(w.nextColumn(2,1) == 2);

}
TEST(Darwin, nextColumn3) {

Species best('b');
World<8,8> w;

Creature b1(best,3);
w.move(2,2,b1);

ASSERT_TRUE(w.nextColumn(2,2) == 3);

}






