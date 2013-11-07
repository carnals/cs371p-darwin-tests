// --------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

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

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <stdexcept> // invalid_argument, out_of_range
#include <string>   // ==

#include "gtest/gtest.h"

#define private public
#include "Darwin.h"

// ----
// addInstruction
// ----

TEST(Darwin, addInstructionsFood) {
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    ASSERT_TRUE(food.program[0] == LEFT);
    ASSERT_TRUE(food.program[1] == GO);

    ASSERT_TRUE(food.dest[0] == 0);
    ASSERT_TRUE(food.dest[1] == 0);
}

TEST(Darwin, addInstructionsHopper) {
    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    ASSERT_TRUE(hopper.program[0] == HOP);
    ASSERT_TRUE(hopper.program[1] == GO);

    ASSERT_TRUE(hopper.dest[0] == 0);
    ASSERT_TRUE(hopper.dest[1] == 0);
}

TEST(Darwin, addInstructionsRover) {
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    ASSERT_TRUE(rover.program[0]  == IF_ENEMY);
    ASSERT_TRUE(rover.program[1]  == IF_EMPTY);
    ASSERT_TRUE(rover.program[2]  == IF_RANDOM);
    ASSERT_TRUE(rover.program[3]  == LEFT);
    ASSERT_TRUE(rover.program[4]  == GO);
    ASSERT_TRUE(rover.program[5]  == RIGHT);
    ASSERT_TRUE(rover.program[6]  == GO);
    ASSERT_TRUE(rover.program[7]  == HOP);
    ASSERT_TRUE(rover.program[8]  == GO);
    ASSERT_TRUE(rover.program[9]  == INFECT);
    ASSERT_TRUE(rover.program[10] == GO);

    ASSERT_TRUE(rover.dest[0]  == 9);
    ASSERT_TRUE(rover.dest[1]  == 7);
    ASSERT_TRUE(rover.dest[2]  == 5);
    ASSERT_TRUE(rover.dest[3]  == 0);
    ASSERT_TRUE(rover.dest[4]  == 0);
    ASSERT_TRUE(rover.dest[5]  == 0);
    ASSERT_TRUE(rover.dest[6]  == 0);
    ASSERT_TRUE(rover.dest[7]  == 0);
    ASSERT_TRUE(rover.dest[8]  == 0);
    ASSERT_TRUE(rover.dest[9]  == 0);
    ASSERT_TRUE(rover.dest[10] == 0);
}

TEST(Darwin, addInstructionsTrap) {
    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    ASSERT_TRUE(trap.program[0] == IF_ENEMY);
    ASSERT_TRUE(trap.program[1] == LEFT);
    ASSERT_TRUE(trap.program[2] == GO);
    ASSERT_TRUE(trap.program[3] == INFECT);
    ASSERT_TRUE(trap.program[4] == GO);

    ASSERT_TRUE(trap.dest[0] == 3);
    ASSERT_TRUE(trap.dest[1] == 0);
    ASSERT_TRUE(trap.dest[2] == 0);
    ASSERT_TRUE(trap.dest[3] == 0);
    ASSERT_TRUE(trap.dest[4] == 0);
}

// ----
// empty
// ----

TEST(Darwin, emptyWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.empty(0, 0) == true);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, emptyWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.empty(0, 0, 5) == true);
    ASSERT_TRUE(hopper1.prog_count == 5);
}

TEST(Darwin, emptyEnemyWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature hopper2(&hopper, EAST);
    grid.addCreature(hopper2, 0, 1);

    ASSERT_TRUE(grid.empty(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, emptyEnemyWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature hopper2(&hopper, EAST);
    grid.addCreature(hopper2, 0, 1);

    ASSERT_TRUE(grid.empty(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

TEST(Darwin, emptyWallWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.empty(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, emptyWallWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.empty(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

// ----
// wall
// ----

TEST(Darwin, isWallWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.wall(0, 0) == true);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isWallWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.wall(0, 0, 5) == true);
    ASSERT_TRUE(hopper1.prog_count == 5);
}

TEST(Darwin, isNotWallWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.wall(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isNotWallWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.wall(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

// ----
// enemy
// ----

TEST(Darwin, isEnemyCreatureWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');
    Species trap('t');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature trap1(&trap, NORTH);
    grid.addCreature(trap1, 0, 1);

    ASSERT_TRUE(grid.enemy(0, 0) == true);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isEnemyCreatureWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');
    Species trap('t');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature trap1(&trap, NORTH);
    grid.addCreature(trap1, 0, 1);

    ASSERT_TRUE(grid.enemy(0, 0, 5) == true);
    ASSERT_TRUE(hopper1.prog_count == 5);
}

TEST(Darwin, isNotEnemyCreatureWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature hopper2(&hopper, NORTH);
    grid.addCreature(hopper2, 0, 1);

    ASSERT_TRUE(grid.enemy(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isNotEnemyCreatureWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature hopper2(&hopper, NORTH);
    grid.addCreature(hopper2, 0, 1);

    ASSERT_TRUE(grid.enemy(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

TEST(Darwin, isNotEnemyEmptyWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.enemy(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isNotEnemyEmptyWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.enemy(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

TEST(Darwin, isNotEnemyWallWithoutGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.enemy(0, 0) == false);
    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, isNotEnemyWallWithGoTo) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.enemy(0, 0, 5) == false);
    ASSERT_TRUE(hopper1.prog_count == 1);
}

// ----
// go
// ----

TEST(Darwin, go0) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    grid.go(0, 0, 0);

    ASSERT_TRUE(hopper1.prog_count == 0);
}

TEST(Darwin, go5) {
    Darwin grid(2, 2);

    Species hopper('h');

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    grid.go(0, 0, 5);

    ASSERT_TRUE(hopper1.prog_count == 5);
}

// ----
// hop
// ----

TEST(Darwin, hopIntoEmpty) {
    Darwin grid(2, 2);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    grid.hop(0, 0);
    ASSERT_TRUE(grid.grid[0][0] == NULL);
    ASSERT_TRUE(grid.grid[0][1] == &hopper1);
}

TEST(Darwin, hopIntoWall) {
    Darwin grid(1, 1);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    grid.hop(0, 0);
    ASSERT_TRUE(grid.grid[0][0] == &hopper1);
}

TEST(Darwin, hopIntoEnemy) {
    Darwin grid(1, 2);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 1);

    grid.hop(0, 0);
    ASSERT_TRUE(grid.grid[0][0] == &hopper1);    
    ASSERT_TRUE(grid.grid[0][1] == &food1);
}

// -----------
// left
// -----------

TEST(Darwin, left1) {
    Darwin grid(1, 1);

    Species food('f');

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    grid.left(0, 0);
    ASSERT_TRUE(food1.dir == NORTH);
}

TEST(Darwin, left4) {
    Darwin grid(1, 1);

    Species food('f');

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    grid.left(0, 0);
    grid.left(0, 0);
    grid.left(0, 0);
    grid.left(0, 0);
    ASSERT_TRUE(food1.dir == EAST);
}

// -----------
// right
// -----------

TEST(Darwin, right1) {
    Darwin grid(1, 1);

    Species food('f');

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    grid.right(0, 0);
    ASSERT_TRUE(food1.dir == SOUTH);
}

TEST(Darwin, right4) {
    Darwin grid(1, 1);

    Species food('f');

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    grid.right(0, 0);
    grid.right(0, 0);
    grid.right(0, 0);
    grid.right(0, 0);
    ASSERT_TRUE(food1.dir == EAST);
}

// ------
// infect
// ------

TEST(Darwin, infectEmpty) {
    Darwin grid(1, 2);
    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Creature trap1(&trap, EAST);
    grid.addCreature(trap1, 0, 0);

    grid.infect(0, 0);
    //If something were wrong, this would crash
    ASSERT_TRUE(true);
}

TEST(Darwin, infectWall) {
    Darwin grid(1, 1);

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Creature trap1(&trap, EAST);
    grid.addCreature(trap1, 0, 0);

    grid.infect(0, 0);
    //If something were wrong, this would crash
    ASSERT_TRUE(true);
}

TEST(Darwin, infectEnemy) {
    Darwin grid(1, 2);

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    Creature trap1(&trap, EAST);
    grid.addCreature(trap1, 0, 0);

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 1);

    grid.infect(0, 0);
    //If something were wrong, this would crash
    ASSERT_TRUE(true);
}

TEST(Darwin, infectAlly) {
    Darwin grid(1, 2);

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Creature trap1(&trap, EAST);
    grid.addCreature(trap1, 0, 0);

    Creature trap2(&trap, EAST);
    grid.addCreature(trap2, 0, 1);

    grid.infect(0, 0);
    //If something were wrong, this would crash
    ASSERT_TRUE(true);
}

// -----------
// action
// -----------

TEST(Darwin, actionHop) {
    Darwin grid(1, 2);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 0, 0);

    ASSERT_TRUE(grid.grid[0][0] != NULL);
    ASSERT_TRUE(grid.grid[0][1] == NULL);

    grid.action(0, 0);

    ASSERT_TRUE(grid.grid[0][0] == NULL);
    ASSERT_TRUE(grid.grid[0][1] != NULL);
}

TEST(Darwin, actionLeft) {
    Darwin grid(1, 1);

    Species leftFood('l');
    leftFood.addInstruction(LEFT);
    leftFood.addInstruction(GO, 0);

    Creature left1(&leftFood, NORTH);
    grid.addCreature(left1, 0, 0);

    ASSERT_TRUE(left1.dir == NORTH);

    grid.action(0, 0);

    ASSERT_TRUE(left1.dir == WEST);
}

TEST(Darwin, actionRight) {
    Darwin grid(1, 1);

    Species rightFood('r');
    rightFood.addInstruction(RIGHT);
    rightFood.addInstruction(GO, 0);

    Creature right1(&rightFood, NORTH);
    grid.addCreature(right1, 0, 0);

    ASSERT_TRUE(right1.dir == NORTH);

    grid.action(0, 0);

    ASSERT_TRUE(right1.dir == EAST);
}

TEST(Darwin, actionInfect) {
    Darwin grid(1, 2);

    Species food('f');

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Creature trap1(&trap, EAST);
    grid.addCreature(trap1, 0, 0);

    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 1);

    grid.action(0, 0);

    ASSERT_TRUE(grid.grid[0][1]->spec = &trap);
}

// -----------
// next round prep
// -----------

TEST(Darwin, nextRoundPrep) {
    Darwin grid(8, 8);

    Species food('f');
    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    Species hopper('h');
    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 3, 3);

    Creature hopper2(&hopper, NORTH);
    grid.addCreature(hopper2, 3, 4);

    Creature hopper3(&hopper, NORTH);
    grid.addCreature(hopper3, 4, 4);

    Creature hopper4(&hopper, NORTH);
    grid.addCreature(hopper4, 4, 3);

    Creature food2(&food, EAST);
    grid.addCreature(food2, 7, 7);
    
    hopper1.turn_taken = true;
    hopper2.turn_taken = true;
    hopper3.turn_taken = true;
    hopper4.turn_taken = true;
    food2.turn_taken = true;

    grid.next_round_prep();

    hopper1.turn_taken = false;
    hopper2.turn_taken = false;
    hopper3.turn_taken = false;
    hopper4.turn_taken = false;
    food2.turn_taken = false;
}

// -----------
// display
// -----------

TEST(Darwin, displayInitialGame) {
    Darwin grid(8, 8);

    Species food('f');
    Creature food1(&food, EAST);
    grid.addCreature(food1, 0, 0);

    Species hopper('h');
    Creature hopper1(&hopper, NORTH);
    grid.addCreature(hopper1, 3, 3);

    Creature hopper2(&hopper, NORTH);
    grid.addCreature(hopper2, 3, 4);

    Creature hopper3(&hopper, NORTH);
    grid.addCreature(hopper3, 4, 4);

    Creature hopper4(&hopper, NORTH);
    grid.addCreature(hopper4, 4, 3);

    Creature food2(&food, EAST);
    grid.addCreature(food2, 7, 7);

    grid.display(0);
}

// -----------
// simulate
// -----------

TEST(Darwin, simulateHop) {
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    Darwin grid(8, 8);

    Creature rover1(&rover, EAST);
    grid.addCreature(rover1, 4, 0);

    rover1.prog_count = 1;

    grid.simulate(1);

    rover1.prog_count = 7;

    grid.simulate(1);
}

TEST(Darwin, simulateInfectFood) {
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    Darwin grid(8, 8);

    Creature rover1(&rover, EAST);
    grid.addCreature(rover1, 4, 0);

    Creature food1(&food, EAST);
    grid.addCreature(food1, 4, 2);

    grid.simulate(3);
}

TEST(Darwin, simulateInfectHopper) {
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Darwin grid(7, 9);

    Creature rover1(&rover, NORTH);
    grid.addCreature(rover1, 5, 4);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 3, 2);

    grid.simulate(3);
}

TEST(Darwin, simulateInfectHopperWithTraps) {
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);
    rover.addInstruction(IF_EMPTY, 7);
    rover.addInstruction(IF_RANDOM, 5);
    rover.addInstruction(LEFT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(RIGHT);
    rover.addInstruction(GO, 0);
    rover.addInstruction(HOP);
    rover.addInstruction(GO, 0);
    rover.addInstruction(INFECT);
    rover.addInstruction(GO, 0);

    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Darwin grid(7, 9);

    Creature rover1(&rover, NORTH);
    grid.addCreature(rover1, 5, 4);

    Creature trap1(&trap, NORTH);
    grid.addCreature(trap1, 0, 0);

    Creature trap2(&trap, NORTH);
    grid.addCreature(trap2, 6, 8);

    Creature hopper1(&hopper, EAST);
    grid.addCreature(hopper1, 3, 2);

    rover1.prog_count = 0;

    grid.simulate(3);
}

TEST(Darwin, simulateActivatingTraps) {
    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);

    Darwin grid(7, 9);

    Creature trap1(&trap, NORTH);
    grid.addCreature(trap1, 0, 0);

    Creature trap2(&trap, NORTH);
    grid.addCreature(trap2, 6, 8);

    grid.simulate(4);
}

// -----------
// add creature
// -----------

TEST(Darwin, addCreature) {
    Species s('?');

    Darwin grid(1, 1);

    ASSERT_TRUE(grid.grid[0][0] == NULL);

    Creature creature(&s, NORTH);
    grid.addCreature(creature, 0, 0);

    ASSERT_TRUE(grid.grid[0][0] != NULL);
}

TEST(Darwin, addCreatureOutOfRange) {
    Species s('?');

    Darwin grid(1, 1);

    ASSERT_TRUE(grid.grid[0][0] == NULL);

    try {
        Creature creature(&s, NORTH);
        grid.addCreature(creature, 1, 0);
        ASSERT_TRUE(false);
    }
    catch (const out_of_range&) {
        ASSERT_TRUE(true);
    }
}

TEST(Darwin, addCreatureOnCreature) {
    Species s('?');

    Darwin grid(1, 1);

    ASSERT_TRUE(grid.grid[0][0] == NULL);

    Creature creature1(&s, NORTH);
    grid.addCreature(creature1, 0, 0);

    Creature creature2(&s, NORTH);
    grid.addCreature(creature2, 0, 0);
    
    ASSERT_TRUE(grid.grid[0][0] == &creature1);
}