/*
To test the program:

% g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

% valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"



#define private public
#define protected public
#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

// ------------ Species ------------ //

// -------------------
// default constructor
// -------------------

TEST(Darwin, Sdefault_constructor1) {
    Species s;
    ASSERT_TRUE(s.type == NONCREATURE);
}

TEST(Darwin, Sdefault_constructor2) {
    Species s = Species();
    ASSERT_TRUE(s.type == NONCREATURE);
}

// -----------
// constructor
// -----------

TEST(Darwin, Sconstructor1) {
    Species food = Species(FOOD);
    ASSERT_TRUE(food.type == FOOD);
}

TEST(Darwin, Sconstructor2) {
    Species food = Species(BEST);
    ASSERT_TRUE(food.type == BEST);
}

TEST(Darwin, Sconstructor3) {
    Species food = Species(ROVER);
    ASSERT_TRUE(food.type == ROVER);
}

// --------------
// addInstruction
// --------------

TEST(Darwin, addInstruction1) {
    Species food = Species(FOOD);
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0); 
    ASSERT_TRUE(food.instructions[0].first == LEFT);
    ASSERT_TRUE(food.instructions[0].second == 0);
    ASSERT_TRUE(food.instructions[1].first == GO);
    ASSERT_TRUE(food.instructions[1].second == 0);
}

TEST(Darwin, addInstruction2) {
    Species trap = Species(TRAP);
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0); 
    ASSERT_TRUE(trap.instructions[0].first == IF_ENEMY);
    ASSERT_TRUE(trap.instructions[0].second == 3);
    ASSERT_TRUE(trap.instructions[1].first == LEFT);
    ASSERT_TRUE(trap.instructions[1].second == 0);
    ASSERT_TRUE(trap.instructions[2].first == GO);
    ASSERT_TRUE(trap.instructions[2].second == 0);
    ASSERT_TRUE(trap.instructions[3].first == INFECT);
    ASSERT_TRUE(trap.instructions[3].second == 0);
    ASSERT_TRUE(trap.instructions[4].first == GO);
    ASSERT_TRUE(trap.instructions[4].second == 0);
}

TEST(Darwin, addInstruction3) {
    Species rover2 = Species(ROVER);
    rover2.addInstruction(IF_ENEMY, 5);
    rover2.addInstruction(LEFT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(HOP);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(INFECT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(LEFT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(HOP);
    rover2.addInstruction(GO, 0); 
    ASSERT_TRUE(rover2.instructions[0].first == IF_ENEMY);
    ASSERT_TRUE(rover2.instructions[0].second == 5);
    ASSERT_TRUE(rover2.instructions[1].first == LEFT);
    ASSERT_TRUE(rover2.instructions[1].second == 0);
    ASSERT_TRUE(rover2.instructions[2].first == GO);
    ASSERT_TRUE(rover2.instructions[2].second == 0);
    ASSERT_TRUE(rover2.instructions[3].first == HOP);
    ASSERT_TRUE(rover2.instructions[3].second == 0);
    ASSERT_TRUE(rover2.instructions[4].first == GO);
    ASSERT_TRUE(rover2.instructions[4].second == 0);
    ASSERT_TRUE(rover2.instructions[5].first == INFECT);
    ASSERT_TRUE(rover2.instructions[5].second == 0);
    ASSERT_TRUE(rover2.instructions[6].first == GO);
    ASSERT_TRUE(rover2.instructions[6].second == 0);
    ASSERT_TRUE(rover2.instructions[7].first == LEFT);
    ASSERT_TRUE(rover2.instructions[7].second == 0);
    ASSERT_TRUE(rover2.instructions[8].first == GO);
    ASSERT_TRUE(rover2.instructions[8].second == 0);
    ASSERT_TRUE(rover2.instructions[9].first == HOP);
    ASSERT_TRUE(rover2.instructions[9].second == 0);
    ASSERT_TRUE(rover2.instructions[10].first == GO);
    ASSERT_TRUE(rover2.instructions[10].second == 0);
}

// ------------ Creature ------------ //

// -------------------
// default constructor
// -------------------

TEST(Darwin, Cdefault_constructor1) {
    Creature c;
    ASSERT_TRUE(c.species.type == NONCREATURE);
}

TEST(Darwin, Cdefault_constructor2) {
    Creature c = Creature();
    ASSERT_TRUE(c.species.type == NONCREATURE);
}

// -----------
// constructor
// -----------

TEST(Darwin, Cconstructor1) {
    Species food = Species(FOOD);
    Creature c = Creature(food);
    ASSERT_TRUE(c.species.type == FOOD);
    ASSERT_TRUE(c.counter == 0);
    ASSERT_TRUE(c.turnOver == false);
}

TEST(Darwin, Cconstructor2) {
    Species trap = Species(TRAP);
    Creature c = Creature(trap);
    ASSERT_TRUE(c.species.type == TRAP);
    ASSERT_TRUE(c.counter == 0);
    ASSERT_TRUE(c.turnOver == false);
}

// -----------
// instruction
// -----------

TEST(Darwin, instruction1) {
    Species food = Species(FOOD);
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature f = Creature(food); 
    ASSERT_TRUE(f.instruction().first == LEFT);
    ASSERT_TRUE(f.instruction().second == 0);
    ++f.counter;
    ASSERT_TRUE(f.instruction().first == GO);
    ASSERT_TRUE(f.instruction().second == 0);
}

TEST(Darwin, instruction2) {
    Species trap = Species(TRAP);
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);
    Creature t = Creature(trap); 
    ASSERT_TRUE(t.instruction().first == IF_ENEMY);
    ASSERT_TRUE(t.instruction().second == 3);
    ++t.counter;
    ASSERT_TRUE(t.instruction().first == LEFT);
    ASSERT_TRUE(t.instruction().second == 0);
    ++t.counter;
    ASSERT_TRUE(t.instruction().first == GO);
    ASSERT_TRUE(t.instruction().second == 0);
    ++t.counter;
    ASSERT_TRUE(t.instruction().first == INFECT);
    ASSERT_TRUE(t.instruction().second == 0);
    ++t.counter;
    ASSERT_TRUE(t.instruction().first == GO);
    ASSERT_TRUE(t.instruction().second == 0);
}

TEST(Darwin, instruction3) {
    Species rover2 = Species(ROVER);
    rover2.addInstruction(IF_ENEMY, 5);
    rover2.addInstruction(LEFT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(HOP);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(INFECT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(LEFT);
    rover2.addInstruction(GO, 0);
    rover2.addInstruction(HOP);
    rover2.addInstruction(GO, 0); 
    Creature r = Creature(rover2);
    ASSERT_TRUE(r.instruction().first == IF_ENEMY);
    ASSERT_TRUE(r.instruction().second == 5);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == LEFT);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == GO);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == HOP);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == GO);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == INFECT);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == GO);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == LEFT);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == GO);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == HOP);
    ASSERT_TRUE(r.instruction().second == 0);
    ++r.counter;
    ASSERT_TRUE(r.instruction().first == GO);
    ASSERT_TRUE(r.instruction().second == 0);
}

// -------------- Grid -------------- //

// -----------
// constructor
// -----------

TEST(Darwin, Gconstructor1) {
    Grid g = Grid(3, 3);
    ASSERT_TRUE(g.grid.size() == 3);
    ASSERT_TRUE(g.grid[0].size() == 3);
    ASSERT_TRUE(g.grid[0][0].species.type == NONCREATURE);
}

TEST(Darwin, Gconstructor2) {
    Grid g = Grid(60, 70);
    ASSERT_TRUE(g.grid.size() == 60);
    ASSERT_TRUE(g.grid[0].size() == 70);
    ASSERT_TRUE(g.grid[0][0].species.type == NONCREATURE);
}

// ---
// add
// ---

TEST(Darwin, add1) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, NORTH, 3, 4);
    ASSERT_TRUE(g.grid.size() == 5);
    ASSERT_TRUE(g.grid[0].size() == 5);
    ASSERT_TRUE(g.grid[3][4].species.type == FOOD);
    ASSERT_TRUE(g.grid[3][4].dir == NORTH);
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
}

TEST(Darwin, add2) {
    Species food = Species(FOOD);
    Species hopper = Species(HOPPER);
    Creature f1 = Creature(food);
    Creature f2 = Creature(food);
    Creature h1 = Creature(hopper);
    Creature h2 = Creature(hopper);
    Creature h3 = Creature(hopper);
    Creature h4 = Creature(hopper);

    Grid g = Grid(8, 8);
    g.add(f1, EAST, 0, 0);
    g.add(h1, NORTH, 3, 3);
    g.add(h2, EAST, 3, 4);
    g.add(h3, SOUTH, 4, 4);
    g.add(h4, WEST, 4, 3);
    g.add(f2, NORTH, 7, 7);
    ASSERT_TRUE(g.grid.size() == 8);
    ASSERT_TRUE(g.grid[0].size() == 8);
    ASSERT_TRUE(g.grid[0][0].species.type == FOOD);
    ASSERT_TRUE(g.grid[0][0].dir == EAST);
    ASSERT_TRUE(g.grid[0][0].row == 0);
    ASSERT_TRUE(g.grid[0][0].col == 0);
    ASSERT_TRUE(g.grid[3][3].species.type == HOPPER);
    ASSERT_TRUE(g.grid[3][3].dir == NORTH);
    ASSERT_TRUE(g.grid[3][3].row == 3);
    ASSERT_TRUE(g.grid[3][3].col == 3);
    ASSERT_TRUE(g.grid[3][4].species.type == HOPPER);
    ASSERT_TRUE(g.grid[3][4].dir == EAST);
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
    ASSERT_TRUE(g.grid[4][4].species.type == HOPPER);
    ASSERT_TRUE(g.grid[4][4].dir == SOUTH);
    ASSERT_TRUE(g.grid[4][4].row == 4);
    ASSERT_TRUE(g.grid[4][4].col == 4);
    ASSERT_TRUE(g.grid[4][3].species.type == HOPPER);
    ASSERT_TRUE(g.grid[4][3].dir == WEST);
    ASSERT_TRUE(g.grid[4][3].row == 4);
    ASSERT_TRUE(g.grid[4][3].col == 3);
    ASSERT_TRUE(g.grid[7][7].species.type == FOOD);
    ASSERT_TRUE(g.grid[7][7].dir == NORTH);
    ASSERT_TRUE(g.grid[7][7].row == 7);
    ASSERT_TRUE(g.grid[7][7].col == 7);
}

// ----
// wall
// ----

TEST(Darwin, wall1) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, EAST, 3, 4);
    ASSERT_TRUE(g.wall(EAST, 3, 4));
}

TEST(Darwin, wall2) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c1 = Creature(s);
    Creature c2 = Creature(s);
    g.add(c1, EAST, 2, 2);
    g.add(c2, NORTH, 2, 3);
    ASSERT_TRUE(!g.wall(EAST, 2, 2));
}

TEST(Darwin, wall3) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, WEST, 3, 3);
    ASSERT_TRUE(!g.wall(WEST, 3, 3));
}

TEST(Darwin, wall4) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, NORTH, 0, 3);
    ASSERT_TRUE(g.wall(NORTH, 0, 3));
}

TEST(Darwin, wall5) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, WEST, 2, 0);
    ASSERT_TRUE(g.wall(WEST, 2, 0));
}

TEST(Darwin, wall6) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, SOUTH, 4, 2);
    ASSERT_TRUE(g.wall(SOUTH, 4, 2));
}
// -----
// empty
// -----

TEST(Darwin, empty1) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, EAST, 3, 4);
    ASSERT_TRUE(!g.empty(EAST, 3, 4));
}

TEST(Darwin, empty2) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c1 = Creature(s);
    Creature c2 = Creature(s);
    g.add(c1, EAST, 2, 2);
    g.add(c2, NORTH, 2, 3);
    ASSERT_TRUE(!g.empty(EAST, 2, 2));
}

TEST(Darwin, empty3) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, WEST, 3, 3);
    ASSERT_TRUE(g.empty(WEST, 3, 3));
}

// -----
// enemy
// -----

TEST(Darwin, enemy1) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, EAST, 3, 4);
    ASSERT_TRUE(!g.enemy(EAST, 3, 4));
}

TEST(Darwin, enemy2) {
    Grid g = Grid(5, 5);
    Species s1 = Species(FOOD);
    Species s2 = Species(HOPPER);
    Creature c1 = Creature(s1);
    Creature c2 = Creature(s2);
    g.add(c1, EAST, 2, 2);
    g.add(c2, NORTH, 2, 3);
    ASSERT_TRUE(g.enemy(EAST, 2, 2));
}

TEST(Darwin, enemy3) {
    Grid g = Grid(5, 5);
    Species s = Species(FOOD);
    Creature c = Creature(s);
    g.add(c, WEST, 3, 3);
    ASSERT_TRUE(!g.enemy(WEST, 3, 3));
}

// -------------
// doInstruction
// -------------

TEST(Darwin, doInstruction1) {
    Grid g = Grid(5, 5);
    Species s = Species(HOPPER);
    Creature c = Creature(s);
    g.add(c, EAST, 3, 4);
    g.doInstruction(HOP, EAST, 0, 3, 4);
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
    ASSERT_TRUE(g.grid[3][4].turnOver == true);
    ASSERT_TRUE(g.grid[3][4].counter == 1);
}

TEST(Darwin, doInstruction2) {
    Grid g = Grid(5, 5);
    Species s = Species(HOPPER);
    Creature c = Creature(s);
    g.add(c, EAST, 3, 3);
    g.doInstruction(HOP, EAST, 0, 3, 3);
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
    ASSERT_TRUE(g.grid[3][4].species.type == HOPPER);
    ASSERT_TRUE(g.grid[3][3].species.type == NONCREATURE);
    ASSERT_TRUE(g.grid[3][4].turnOver == true);
    ASSERT_TRUE(g.grid[3][4].counter == 1);
}

TEST(Darwin, doInstruction3) {
    Grid g = Grid(5, 5);
    Species s1 = Species(FOOD);
    Species s2 = Species(ROVER);
    Creature c1 = Creature(s1);
    Creature c2 = Creature(s2);
    g.add(c1, EAST, 1, 3);
    g.add(c2, NORTH, 2, 3);
    g.doInstruction(LEFT, EAST, 0, 1, 3);
    g.doInstruction(INFECT, NORTH, 0, 2, 3);
    ASSERT_TRUE(g.grid[1][3].dir == NORTH);
    ASSERT_TRUE(g.grid[1][3].turnOver == true);
    ASSERT_TRUE(g.grid[1][3].counter == 0);
    ASSERT_TRUE(g.grid[1][3].species.type == ROVER);
    ASSERT_TRUE(g.grid[2][3].row == 2);
    ASSERT_TRUE(g.grid[2][3].col == 3);
    ASSERT_TRUE(g.grid[2][3].turnOver == true);
    ASSERT_TRUE(g.grid[2][3].counter == 1);
}

// ----
// turn
// ----

TEST(Darwin, turn1) {
    Grid g = Grid(5, 5);
    Species hopper = Species(HOPPER);
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Creature c = Creature(hopper);
    g.add(c, EAST, 3, 4);
    g.turn();
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
    ASSERT_TRUE(g.grid[3][4].turnOver == true);
    ASSERT_TRUE(g.grid[3][4].counter == 1);
}

TEST(Darwin, turn2) {
    Grid g = Grid(5, 5);
    Species hopper = Species(HOPPER);
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);

    Creature c = Creature(hopper);
    g.add(c, EAST, 3, 3);
    g.turn();
    ASSERT_TRUE(g.grid[3][4].row == 3);
    ASSERT_TRUE(g.grid[3][4].col == 4);
    ASSERT_TRUE(g.grid[3][4].species.type == HOPPER);
    ASSERT_TRUE(g.grid[3][3].species.type == NONCREATURE);
    ASSERT_TRUE(g.grid[3][4].turnOver == true);
    ASSERT_TRUE(g.grid[3][4].counter == 1);
}

TEST(Darwin, turn3) {
    Grid g = Grid(5, 5);
    Species food = Species(FOOD);
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);

    Species rover = Species(ROVER);
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

    Creature c1 = Creature(food);
    Creature c2 = Creature(rover);
    g.add(c1, EAST, 1, 3);
    g.add(c2, NORTH, 2, 3);
    cout << g.grid[2][3].counter << endl;
    g.turn();
    ASSERT_TRUE(g.grid[1][3].turnOver == true);
    ASSERT_TRUE(g.grid[1][3].counter == 0);
    ASSERT_TRUE(g.grid[1][3].species.type == ROVER);
    ASSERT_TRUE(g.grid[2][3].row == 2);
    ASSERT_TRUE(g.grid[2][3].col == 3);
    ASSERT_TRUE(g.grid[2][3].turnOver == true);
    cout << g.grid[2][3].counter << endl;
    ASSERT_TRUE(g.grid[2][3].counter == 10);
}