#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

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

// ----
// read
// ----
TEST(Darwin, isControl1) {
    Instruction a = Instruction(HOP, 0);
    ASSERT_TRUE(isControlcommand(a) == false);}
TEST(Darwin, isControl2) {
    Instruction a = Instruction(LEFT, 0);
    ASSERT_TRUE(isControlcommand(a) == false);}
TEST(Darwin, isControl3) {
    Instruction a = Instruction(RIGHT, 0);
    ASSERT_TRUE(isControlcommand(a) == false);}
TEST(Darwin, isControl4) {
    Instruction a = Instruction(INFECT, 0);
    ASSERT_TRUE(isControlcommand(a) == false);}
TEST(Darwin, isControl5) {
    Instruction a = Instruction(IF_EMPTY, 0);
    ASSERT_TRUE(isControlcommand(a) == true);}
TEST(Darwin, isControl6) {
    Instruction a = Instruction(IF_WALL, 0);
    ASSERT_TRUE(isControlcommand(a) == true);}
TEST(Darwin, isControl7) {
    Instruction a = Instruction(IF_RANDOM, 0);
    ASSERT_TRUE(isControlcommand(a) == true);}
TEST(Darwin, isControl8) {
    Instruction a = Instruction(IF_ENEMY, 0);
    ASSERT_TRUE(isControlcommand(a) == true);}
TEST(Darwin, isControl9) {
    Instruction a = Instruction(GO, 0);
    ASSERT_TRUE(isControlcommand(a) == true);}


TEST(Darwin, updateIns1) {
    Instruction a = updateIns(Hopper, 0);
    ASSERT_TRUE(a.ins == HOP);}
TEST(Darwin, updateIns2) {
    Instruction a = updateIns(Hopper, 1);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns3) {
    Instruction a = updateIns(Food, 0);
    ASSERT_TRUE(a.ins == LEFT);}
TEST(Darwin, updateIns4) {
    Instruction a = updateIns(Food, 1);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns5) {
    Instruction a = updateIns(Trap, 0);
    ASSERT_TRUE(a.ins == IF_ENEMY);}
TEST(Darwin, updateIns6) {
    Instruction a = updateIns(Trap, 1);
    ASSERT_TRUE(a.ins == LEFT);}
TEST(Darwin, updateIns7) {
    Instruction a = updateIns(Trap, 2);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns8) {
    Instruction a = updateIns(Trap, 3);
    ASSERT_TRUE(a.ins == INFECT);}
TEST(Darwin, updateIns9) {
    Instruction a = updateIns(Trap, 4);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns10) {
    Instruction a = updateIns(Rover, 0);
    ASSERT_TRUE(a.ins == IF_ENEMY);}
TEST(Darwin, updateIns11) {
    Instruction a = updateIns(Rover, 1);
    ASSERT_TRUE(a.ins == IF_EMPTY);}
TEST(Darwin, updateIns12) {
    Instruction a = updateIns(Rover, 2);
    ASSERT_TRUE(a.ins == IF_RANDOM);}
TEST(Darwin, updateIns13) {
    Instruction a = updateIns(Rover, 3);
    ASSERT_TRUE(a.ins == LEFT);}
TEST(Darwin, updateIns14) {
    Instruction a = updateIns(Rover, 4);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns15) {
    Instruction a = updateIns(Rover, 5);
    ASSERT_TRUE(a.ins == RIGHT);}
TEST(Darwin, updateIns16) {
    Instruction a = updateIns(Rover, 6);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns17) {
    Instruction a = updateIns(Rover, 7);
    ASSERT_TRUE(a.ins == HOP);}
TEST(Darwin, updateIns18) {
    Instruction a = updateIns(Rover, 8);
    ASSERT_TRUE(a.ins == GO);}
TEST(Darwin, updateIns19) {
    Instruction a = updateIns(Rover, 9);
    ASSERT_TRUE(a.ins == INFECT);}
TEST(Darwin, updateIns20) {
    Instruction a = updateIns(Rover, 10);
    ASSERT_TRUE(a.ins == GO);}