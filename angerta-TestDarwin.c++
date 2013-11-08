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

    % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

    % valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// -------
// species
// -------
    
enum direction {WEST,NORTH,EAST,SOUTH};
enum instruction {HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};

TEST(Darwin, Species_food_1) {

    Darwin world = Darwin();
    world.init_world(8,8);

    Species food = Species("food");
    food.add_instruction("left");
    food.add_instruction("go", 0);

    Creature FE = Creature(food, EAST);

    world.add_creature(FE,0,0);

    ASSERT_TRUE(food.name == "food");
    ASSERT_TRUE(food.program[0].first == LEFT);
    ASSERT_TRUE(food.program[0].second == -1);
    ASSERT_TRUE(food.get_abreviation() == *"f");

    ASSERT_TRUE(FE.direction == EAST);
    world.run_World_turn();
    ASSERT_TRUE(FE.direction == EAST);
}

TEST(Darwin, Species_food_2) {

    Darwin world = Darwin();
    world.init_world(8,8);

    Species food = Species("food");
    food.add_instruction("left");
    food.add_instruction("go", 0);

    Creature FN = Creature(food, NORTH);

    world.add_creature(FN,7,7);

    ASSERT_TRUE(food.name == "food");
    ASSERT_TRUE(food.program[0].first == LEFT);
    ASSERT_TRUE(food.program[0].second == -1);
    ASSERT_TRUE(food.get_abreviation() == *"f");
    ASSERT_TRUE(FN.direction == NORTH);

    world.run_World_turn();
    ASSERT_TRUE(FN.direction == NORTH);
}

TEST(Darwin, Species_hopper_1) {

    Darwin world = Darwin();
    world.init_world(8,8);

    Species hopper = Species("hopper");
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);
    Creature HN = Creature(hopper, NORTH);
    world.add_creature(HN,3,3);

    ASSERT_TRUE(hopper.name == "hopper");
    ASSERT_TRUE(hopper.program[0].first == HOP);
    ASSERT_TRUE(hopper.program[0].second == -1);
    ASSERT_TRUE(hopper.get_abreviation() == *"h");
    ASSERT_TRUE(HN.direction == NORTH);

    world.run_World_turn();
    ASSERT_TRUE(HN.direction == NORTH);
}

TEST(Darwin, Species_hopper_2) {

    Darwin world = Darwin();
    world.init_world(8,8);

    Species hopper = Species("hopper");
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);
    Creature HE = Creature(hopper, EAST);
    world.add_creature(HE,3,4);

    ASSERT_TRUE(hopper.name == "hopper");
    ASSERT_TRUE(hopper.program[0].first == HOP);
    ASSERT_TRUE(hopper.program[0].second == -1);
    ASSERT_TRUE(hopper.get_abreviation() == *"h");
    ASSERT_TRUE(HE.direction == EAST);

    world.run_World_turn();
    ASSERT_TRUE(HE.direction == EAST);
}

TEST(Darwin, if_enemy_1) {

    Species rover = Species("rover");

    Darwin world = Darwin();
    world.init_world(8,8);

    Creature RE1 = Creature(rover, EAST);
    world.add_creature(RE1,3,4);

    Creature RE2 = Creature(rover, EAST);
    world.add_creature(RE2,3,5);

    ASSERT_TRUE(RE1.is_enemy(RE2) == false);
}


TEST(Darwin, if_enemy_2) {

    Species rover = Species("rover");
    Species food = Species("food");

    Darwin world = Darwin();
    world.init_world(8,8);

    Creature RE = Creature(rover, EAST);
    world.add_creature(RE,3,4);

    Creature FE = Creature(food, EAST);
    world.add_creature(FE,3,5);

    ASSERT_TRUE(RE.is_enemy(FE) == true);
}


TEST(Darwin, is_empty_1) {

    Species rover = Species("rover");

    Darwin world = Darwin();
    world.init_world(8,8);

    Creature RE1 = Creature(rover, EAST);
    world.add_creature(RE1,3,4);

    Creature RE2 = Creature(rover, SOUTH);
    world.add_creature(RE2,3,5);

    ASSERT_TRUE(RE1.is_empty == false);
}

TEST(Darwin, is_infect_1) {

    Species rover = Species("rover");
    Species food = Species("food");

    rover.add_instruction("infect");

    Darwin world = Darwin();
    world.init_world(8,8);

    Creature RE1 = Creature(rover, EAST);
    world.add_creature(RE1,3,4);

    Creature FE = Creature(food, EAST);
    world.add_creature(FE,3,5);

    world.run_World_turn();
    
    ASSERT_TRUE(world.Grid[3][5].s.name == "rover");
}
