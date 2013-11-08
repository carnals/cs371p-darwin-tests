// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------


#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <unordered_set>

#include "gtest/gtest.h"

#include "Darwin.h"

// ----------
// TestDarwin
// ----------



TEST(Darwin, creature_id_1) {
  Species food("f");
  
  Creature c1(food, EAST);
  Creature c;
  Creature c2(food, WEST);
  Creature c3(food, WEST);
  
  ASSERT_TRUE(c1.id() != c2.id());
  ASSERT_TRUE(c2.id() != c3.id());
  ASSERT_TRUE(c3.id() != c1.id());
  
}

TEST(Darwin, creature_id_2) {
  Species food("f");
  
  Creature c1(food, EAST);
  Creature c2(food, EAST);
  Creature c3(food, EAST);
  
  ASSERT_TRUE(c1.id() != c2.id());
  ASSERT_TRUE(c2.id() != c3.id());
  ASSERT_TRUE(c3.id() != c1.id());
  
}

TEST(Darwin, creature_id_3) {
  Species food("f");
  
  Creature c1(food, EAST);
  Creature c2(food, EAST);
  Creature c;
  Creature c3(food, EAST);

  ASSERT_TRUE(c1.id() != c2.id());
  ASSERT_TRUE(c2.id() != c3.id());
  ASSERT_TRUE(c3.id() != c1.id());
  ASSERT_TRUE(c.id() == -1);
  
}

TEST(Creature, default_constructor) {
  Creature c;
  
  ASSERT_TRUE(c.id() == -1);
}



TEST(Darwin, print_1) {
  Species food("f");
  Species hopper("h");
  WorldState world(3, 3);
  Creature food1(food, EAST);
  Creature hopper1(hopper, NORTH);


  std::ostringstream w;

  world.addCreature(food1, 0, 0);
  world.addCreature(hopper1, 0, 1);
  world.printGrid(w);

  std::string expected = "  012\n0 fh.\n1 ...\n2 ...\n";
  std::string actual = w.str(); 
  ASSERT_TRUE(actual == expected); 
}

TEST(Darwin, creature_toString_1) {
  Species food("f");
  Creature food1(food, EAST);

  ASSERT_TRUE(food1.toString() == "f");
}

TEST(Darwin, creature_toString_default) {
 
  Creature c;

  ASSERT_TRUE(c.toString() == ".");
}

TEST(WORLDSTATE, add_creature) {
  Species food("f");
  Species hopper("h");
  WorldState world(3, 3);
  Creature food1(food, EAST);
  Creature hopper1(hopper, NORTH);


  std::ostringstream w;

  world.addCreature(food1, 0, 0);
  world.addCreature(hopper1, 0, 1);

  std::string expected = "  012\n0 fh.\n1 ...\n2 ...\n";
  world.printGrid(w);
  std::string actual = w.str();
  
  ASSERT_TRUE(expected == actual);
}

TEST(WORLDSTATE, add_creature_2) { // TODO I think this is expected behavior
  Species food("f");
  Species hopper("h");
  WorldState world(3, 3);
  Creature food1(food, EAST);
  Creature hopper1(hopper, NORTH);


  std::ostringstream w;

  world.addCreature(food1, 0, 0);
  world.addCreature(hopper1, 0, 0);

  std::string expected = "  012\n0 f..\n1 ...\n2 ...\n";
  world.printGrid(w);
  std::string actual = w.str();
  
  ASSERT_TRUE(expected == actual);
}

TEST(WORLDSTATE, add_creature_3) { 

  Species hopper("h");
  WorldState world(3, 3);
  Creature food1;
  Creature hopper1(hopper, NORTH);


  std::ostringstream w;

  world.addCreature(food1, 0, 0);
  world.addCreature(hopper1, 1, 0);

  std::string expected = "  012\n0 ...\n1 h..\n2 ...\n";
  world.printGrid(w);
  std::string actual = w.str();
  
  ASSERT_TRUE(expected == actual);
}

TEST(Darwin, program_get_action_1) {
  Program p;
  p.addAction(LEFT, 0, -1);
  p.addAction(GO, 1, 0);
  

  int pc = 0;
  Action a = p.getAction(pc, true, false, false);
  ASSERT_TRUE(a == LEFT);
  pc = 1;
  a = p.getAction(pc, true, false, false);
  ASSERT_TRUE(a == LEFT);
}


TEST(Darwin, program_getAction_2) {

  Program p;
  p.addAction(HOP, 0, -1);
  p.addAction(GO, 1, 0);

  int pc = 0;
  ASSERT_TRUE(p.getAction(pc, true, false, false) == HOP);
  pc = 1;
  ASSERT_TRUE(p.getAction(pc, true, false, false) == HOP);
}


TEST(Darwin, program_getAction_3) {

  Program rover;
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3, -1);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5, -1);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7, -1);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9, -1);
  rover.addAction(GO, 10, 0);

  int pc = 6;
  ASSERT_TRUE(rover.getAction(pc, true, false, false) == HOP); // empty, no enemy, no wall
  pc = 0;
  ASSERT_TRUE(rover.getAction(pc, false, true, false) == INFECT);
}

TEST(Darwin, program_getAction_4) {

  Program rover;
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3, -1);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5, -1);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7, -1);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9, -1);
  rover.addAction(GO, 10, 0);

  int pc = 7;
  ASSERT_TRUE(rover.getAction(pc, false, false, true) == HOP);
}

TEST(Darwin, species_getAction_1) {
  Species food("f");
  food.addAction(LEFT, 0);
  food.addAction(GO, 1, 0);

  int pc = 0;
  
  ASSERT_TRUE(food.getAction(pc, true, false, false) == LEFT);
  pc = 1;
  ASSERT_TRUE(food.getAction(pc, true, false, false) == LEFT);
}

TEST(Darwin, species_getAction_2) {
  Species hopper("f");
  hopper.addAction(HOP, 0);
  hopper.addAction(GO, 1, 0);

  int pc = 0;
  ASSERT_TRUE(hopper.getAction(pc, true, false, false) == HOP);
  pc = 1;
  ASSERT_TRUE(hopper.getAction(pc, true, false, false) == HOP);
}

TEST(Darwin, creature_get_action_1) {
  Species food("f");
  food.addAction(LEFT, 0);
  food.addAction(GO, 1, 0);

  
  Creature food1(food, EAST);
  ASSERT_TRUE(food1.getAction(true, false, false) == LEFT);
  ASSERT_TRUE(food1.getAction(true, false, false) == LEFT);
  ASSERT_TRUE(food1.getAction(true, false, false) == LEFT);

}

TEST(Darwin, creature_get_action_2) {
  Species species("f");
  species.addAction(LEFT, 0);
  species.addAction(RIGHT, 1);
  species.addAction(GO, 2, 0);

  
  Creature c(species, EAST);
  ASSERT_TRUE(c.getAction(true, false, false) == LEFT);
  ASSERT_TRUE(c.getAction(true, false, false) == RIGHT);
  ASSERT_TRUE(c.getAction(true, false, false) == LEFT);
}

// TODO more tests of getAction!!!

TEST(Darwin, creature_get_action_rover) {
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  bool empty = true;
  bool enemy = false;
  bool wall = false;
  Creature rov(rover, WEST);
  
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == HOP);
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == HOP);
  
  enemy = true;
  empty = false;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == INFECT);
  
  empty = false;  
  enemy = false;
  wall = true;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == RIGHT);
  
}

TEST(Darwin, creature_get_action_rover_2) {
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  bool empty = true;
  bool enemy = false;
  bool wall = false;
  Creature rov(rover, WEST);
  
  empty = false;  
  enemy = false;
  wall = true;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == RIGHT);
  
  
  
  empty = false;  
  enemy = false;
  wall = false;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == LEFT);
  
    
}

TEST(Darwin, creature_get_action_rover_3) {
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  bool empty = true;
  bool enemy = false;
  bool wall = false;
  Creature rov(rover, WEST);
  
  empty = false;  
  enemy = false;
  wall = true;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == RIGHT);
  
  
  
  empty = false;  
  enemy = false;
  wall = false;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == LEFT);
  
  empty = false;
  enemy = true;
  wall = false;
  ASSERT_TRUE(rov.getAction(empty, enemy, wall) == INFECT);
  
    
}


TEST(Darwin, get_next_position_1) {
  WorldState world(3, 3);

  int i = 0, j = 1;
  int ni, nj;
  
  world.getNextPosition(i, j, ni, nj, EAST);
  ASSERT_TRUE(ni == 0);
  ASSERT_TRUE(nj == 2);
 
}

TEST(Darwin, get_next_position_2) {
  WorldState world(3, 3);

  int i = 0, j = 1;
  int ni, nj;
  
  world.getNextPosition(i, j, ni, nj, SOUTH);
  ASSERT_TRUE(ni == 1);
  ASSERT_TRUE(nj == 1);

}

TEST(Darwin, get_next_position_3) {
  WorldState world(3, 3);

  int i = 0, j = 1;
  int ni, nj;
  
  world.getNextPosition(i, j, ni, nj, NORTH);
  ASSERT_TRUE(ni == -1);
  ASSERT_TRUE(nj == 1);
  ASSERT_TRUE(!world.isInBounds(ni, nj));

}

TEST(Darwin, get_next_position_4) {
  WorldState world(3, 3);

  int i = 0, j = 1;
  int ni, nj;
  
  world.getNextPosition(i, j, ni, nj, WEST);
  ASSERT_TRUE(ni == 0);
  ASSERT_TRUE(nj == 0);
  ASSERT_TRUE(world.isInBounds(ni, nj));
}

TEST(Darwin, put_in_bounds_1) {
  WorldState world(3, 3);

  int i = 0, j = 0;
  
  world.putInBounds(i, j);
  ASSERT_TRUE(i == 0);
  ASSERT_TRUE(j == 0);
}
  
TEST(Darwin, put_in_bounds_2) {  
  WorldState world(3, 3);

  int i = -1;
  int j = 0;
  world.putInBounds(i, j);

  ASSERT_TRUE(i == 0);
  ASSERT_TRUE(j == 0);
  
}
  
TEST(Darwin, put_in_bounds_3) {
    WorldState world(3, 3);

  int i = 0;
  int j = -1;  
  world.putInBounds(i, j);

  ASSERT_TRUE(i == 0);
  ASSERT_TRUE(j == 0);  
}

TEST(Darwin, put_in_bounds_4) {
  WorldState world(3, 3);

  int i = 0;
  int j = 3;  
  world.putInBounds(i, j);

  ASSERT_TRUE(i == 0);
  ASSERT_TRUE(j == 2);  
}
  
TEST(Darwin, put_in_bounds_5) {
  WorldState world(3, 3);
  int i = 4;
  int j = 0;  
  world.putInBounds(i, j);

  ASSERT_TRUE(i == 2);
  ASSERT_TRUE(j == 0);    
}

TEST(WorldState, is_in_bounds1) {
  WorldState world(2, 2);
  int i = 1;
  int j = 2;
  
  ASSERT_TRUE(world.isInBounds(i, j) == false);
}

TEST(WorldState, is_in_bounds_2) {
  WorldState world(2, 2);
  int i = 2;
  int j = 1;
  
  ASSERT_TRUE(world.isInBounds(i, j) == false);
}

TEST(WorldState, is_in_bounds_3) {
  WorldState world(2, 2);
  int i = 0;
  int j = 0;
  
  ASSERT_TRUE(world.isInBounds(i, j) == true);
}

TEST(WorldState, is_in_bounds_4) {
  WorldState world(2, 2);
  int i = 1;
  int j = 1;
  
  ASSERT_TRUE(world.isInBounds(i, j) == true);
}


TEST(Darwin, getConditionals_1) {
  WorldState world(3, 3);
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  Creature creature(rover, EAST);
  
  int i = 0;
  int j = 2;
  world.addCreature(creature, i, j);
  bool b[3];
  

  world.getConditionals(creature, i, j, b);
  ASSERT_TRUE(b[0] == false);
  ASSERT_TRUE(b[1] == false);
  ASSERT_TRUE(b[2] == true);  
}

TEST(Darwin, getConditionals_2) {
  WorldState world(3, 3);
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  Creature creature(rover, EAST);
  
  int i = 0;
  int j = 1;
  world.addCreature(creature, i, j);
  bool b[3];
  

  world.getConditionals(creature, i, j, b);
  ASSERT_TRUE(b[0] == true);
  ASSERT_TRUE(b[1] == false);
  ASSERT_TRUE(b[2] == false);  
}

TEST(Darwin, getConditionals_3) {
  WorldState world(3, 3);
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  Creature creature(rover, EAST);
  Creature creature2(rover, EAST);
  
  int i = 0;
  int j = 1;
  world.addCreature(creature, i, j);
  world.addCreature(creature2, i, j + 1);
  
  bool b[3];
  

  world.getConditionals(creature, i, j, b);
  ASSERT_TRUE(b[0] == false); // empty
  ASSERT_TRUE(b[1] == false); // enemy
  ASSERT_TRUE(b[2] == false); // wall
  
  Action a = creature.getAction(b[0], b[1], b[2]);
  ASSERT_TRUE(a == RIGHT);
}

TEST(Darwin, getConditionals_4) {
  WorldState world(3, 3);
  Species rover("r");
  srand(0);
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0);
  
  Species hopper("h");
  hopper.addAction(HOP, 0);
  hopper.addAction(GO, 1, 0);
  
  Creature creature(rover, EAST);
  Creature creature2(hopper, EAST);
  
  int i = 0;
  int j = 1;
  world.addCreature(creature, i, j);
  world.addCreature(creature2, i, j + 1);
  
  bool b[3];
  

  world.getConditionals(creature, i, j, b);
  ASSERT_TRUE(b[0] == false); // empty
  ASSERT_TRUE(b[1] == true); // enemy
  ASSERT_TRUE(b[2] == false); // wall
  
  Action a = creature.getAction(b[0], b[1], b[2]);
  ASSERT_TRUE(a == INFECT);
}

TEST(Darwin, infect_1) {
  WorldState world(3, 3);
  Species rover("r");
  srand(0);  
  
  rover.addAction(ENEMY, 0, 9);
  rover.addAction(EMPTY, 1, 7);
  rover.addAction(RANDOM, 2, 5);
  rover.addAction(LEFT, 3);
  rover.addAction(GO, 4, 0);
  rover.addAction(RIGHT, 5);
  rover.addAction(GO, 6, 0);
  rover.addAction(HOP, 7);
  rover.addAction(GO, 8, 0);
  rover.addAction(INFECT, 9);
  rover.addAction(GO, 10, 0); 
  
  Species food("f");
  food.addAction(LEFT, 0);
  food.addAction(GO, 1, 0);
  
  Creature r(rover, EAST);
  Creature f(food, EAST);
  
  world.addCreature(r, 0, 1);
  world.addCreature(f, 0, 2);
  
  ASSERT_TRUE(r.toString() == "r");
  ASSERT_TRUE(f.toString() == "f");  
  
  
  f.changeSpecies(r);
  
  ASSERT_TRUE(r.toString() == "r");
  ASSERT_TRUE(f.toString() == "r");
}

TEST(WORLDSTATE, take_turn_1) {
    Species food("f");
    WorldState world(1, 10);

    food.addAction(LEFT, 0);
    food.addAction(GO, 1, 0);    

    Species hopper("h");

    
    hopper.addAction(HOP, 0);
    hopper.addAction(GO, 1, 0);


    Species rover("r");
    
    rover.addAction(ENEMY, 0, 9);
    rover.addAction(EMPTY, 1, 7);
    rover.addAction(RANDOM, 2, 5);
    rover.addAction(LEFT, 3);
    rover.addAction(GO, 4, 0);
    rover.addAction(RIGHT, 5);
    rover.addAction(GO, 6, 0);
    rover.addAction(HOP, 7);
    rover.addAction(GO, 8, 0);
    rover.addAction(INFECT, 9);
    rover.addAction(GO, 10, 0);
    
    
    Creature h1(hopper, EAST);
    Creature r1(rover,EAST);
    Creature h2(hopper,EAST);
    Creature r2(rover,EAST);
    Creature h3(hopper,EAST);
    Creature r3(rover,EAST);
    Creature h4(hopper,EAST);
    Creature r4(rover,EAST);
    Creature h5(hopper,EAST);        
    
    world.addCreature(h1,0,0);
    world.addCreature(r1,0,1);
    world.addCreature(h2,0,2);
    world.addCreature(r2,0,3);
    world.addCreature(h3,0,4);
    world.addCreature(r3,0,5);
    world.addCreature(h4,0,6);
    world.addCreature(r4,0,7);
    world.addCreature(h5,0,8);    
    
    std::ostringstream w;
    world.printGrid(w);
    std::string actual = w.str();
    std::string expected = "  0123456789\n0 hrhrhrhrh.\n";
    
    ASSERT_TRUE(actual == expected);
}

TEST(WORLDSTATE, take_turn_2) {
    Species food("f");
    WorldState world(1, 10);

    food.addAction(LEFT, 0);
    food.addAction(GO, 1, 0);    

    Species hopper("h");

    
    hopper.addAction(HOP, 0);
    hopper.addAction(GO, 1, 0);


    Species rover("r");
    
    rover.addAction(ENEMY, 0, 9);
    rover.addAction(EMPTY, 1, 7);
    rover.addAction(RANDOM, 2, 5);
    rover.addAction(LEFT, 3);
    rover.addAction(GO, 4, 0);
    rover.addAction(RIGHT, 5);
    rover.addAction(GO, 6, 0);
    rover.addAction(HOP, 7);
    rover.addAction(GO, 8, 0);
    rover.addAction(INFECT, 9);
    rover.addAction(GO, 10, 0);
    
    
    Creature h1(hopper, EAST);
    Creature r1(rover,EAST);
    Creature h2(hopper,EAST);
    Creature r2(rover,EAST);
    Creature h3(hopper,EAST);
    Creature r3(rover,EAST);
    Creature h4(hopper,EAST);
    Creature r4(rover,EAST);
    Creature h5(hopper,EAST);        
    
    world.addCreature(h1,0,0);
    world.addCreature(r1,0,1);
    world.addCreature(h2,0,2);
    world.addCreature(r2,0,3);
    world.addCreature(h3,0,4);
    world.addCreature(r3,0,5);
    world.addCreature(h4,0,6);
    world.addCreature(r4,0,7);
    world.addCreature(h5,0,8);    
    
    std::ostringstream w;
    
    world.takeTurn();
    world.printGrid(w);
    std::string actual = w.str();
    std::string expected = "  0123456789\n0 hrrrrrrr.r\n";
    
    ASSERT_TRUE(actual == expected);
}

TEST(WORLDSTATE, take_turn_3) {
    Species food("f");
    WorldState world(1, 10);

    food.addAction(LEFT, 0);
    food.addAction(GO, 1, 0);    

    Species hopper("h");
    hopper.addAction(HOP, 0);
    hopper.addAction(GO, 1, 0);

    Species rover("r");
    
    rover.addAction(ENEMY, 0, 9);
    rover.addAction(EMPTY, 1, 7);
    rover.addAction(RANDOM, 2, 5);
    rover.addAction(LEFT, 3);
    rover.addAction(GO, 4, 0);
    rover.addAction(RIGHT, 5);
    rover.addAction(GO, 6, 0);
    rover.addAction(HOP, 7);
    rover.addAction(GO, 8, 0);
    rover.addAction(INFECT, 9);
    rover.addAction(GO, 10, 0);
    
    
    Creature h1(hopper, EAST);
    Creature r1(rover,EAST);
    Creature h2(hopper,EAST);
    Creature r2(rover,EAST);
    Creature h3(hopper,EAST);
    Creature r3(rover,EAST);
    Creature h4(hopper,EAST);
    Creature r4(rover,EAST);
    Creature h5(hopper,EAST);        
    
    world.addCreature(h1,0,0);
    world.addCreature(r1,0,1);
    world.addCreature(h2,0,2);
    world.addCreature(r2,0,3);
    world.addCreature(h3,0,4);
    world.addCreature(r3,0,5);
    world.addCreature(h4,0,6);
    world.addCreature(r4,0,7);
    world.addCreature(h5,0,8);    
    
    std::ostringstream w;
    
    world.takeTurn();
    world.takeTurn();
    world.printGrid(w);

    std::string expected = "  0123456789\n0 hrrrrrr.rr\n";
    std::string actual = w.str();

    ASSERT_TRUE(actual == expected);
}

TEST(SPECIES, get_next_counter_1) {
    
    Species rover("r");
    
    rover.addAction(ENEMY, 0, 9);
    rover.addAction(EMPTY, 1, 7);
    rover.addAction(RANDOM, 2, 5);
    rover.addAction(LEFT, 3);
    rover.addAction(GO, 4, 0);
    rover.addAction(RIGHT, 5);
    rover.addAction(GO, 6, 0);
    rover.addAction(HOP, 7);
    rover.addAction(GO, 8, 0);
    rover.addAction(INFECT, 9);
    rover.addAction(GO, 10, 0);
    
    int i = 0;
    ASSERT_TRUE(rover.getNextCounter(i) == 1);
    
}

TEST(SPECIES, get_next_counter_2) {
    Species food("f");

    food.addAction(LEFT, 0);
    food.addAction(GO, 1, 0);    

    
    int i = 1;
    ASSERT_TRUE(food.getNextCounter(i) == 0);
    
}

TEST(SPECIES, get_next_counter_3) {
    Species hopper("h");
    hopper.addAction(HOP, 0);
    hopper.addAction(GO, 1, 0); 
    
    int i = 0;
    ASSERT_TRUE(hopper.getNextCounter(i) == 1);
}

TEST(CREATURE, constructor_1) {
  Species hopper("h");
  Creature c(hopper, EAST);
  ASSERT_TRUE(c.toString() == "h");
  ASSERT_TRUE(c.getDirection() == EAST);
}

TEST(CREATURE, constructor_2) {
  Species food("f");
  Creature c(food, WEST);
  ASSERT_TRUE(c.toString() == "f");
  ASSERT_TRUE(c.getDirection() == WEST);
}

TEST(CREATURE, constructor_3) {
  Species rover("r");
  Creature c(rover, SOUTH);
  ASSERT_TRUE(c.toString() == "r");
  ASSERT_TRUE(c.getDirection() == SOUTH);
}

TEST(CREATURE, to_string_1) {
  Species rover("r");
  Creature c(rover, SOUTH);
  ASSERT_TRUE(c.toString() == "r");
}

TEST(CREATURE, to_string_2) {
  Creature c;
  ASSERT_TRUE(c.toString() == ".");
}

TEST(CREATURE, to_string_23) {
  Species s;
  Creature c(s, SOUTH);
  ASSERT_TRUE(c.toString() == ".");
}

TEST(CREATURE, get_direction) {
  Species rover("r");
  Creature c(rover, SOUTH);
  ASSERT_TRUE(c.getDirection() == SOUTH);
}

TEST(CREATURE, get_direction_2) {
  Species rover;
  Creature c(rover, NORTH);
  ASSERT_TRUE(c.getDirection() == NORTH);
}

TEST(CREATURE, different_species_1) {
  Species rover("r");
  Creature c1(rover, EAST);
  Creature c2(rover, WEST);
  
  ASSERT_TRUE(c1.differentSpecies(c2) == false);
}

TEST(CREATURE, different_species_2) {
  Species rover("r");
  Species food("f");
  Creature c1(rover, EAST);
  Creature c2(food, EAST);
  
  ASSERT_TRUE(c1.differentSpecies(c2) == true);
}


TEST(CREATURE, different_species_3) {
  Species rover("r");
  Species food("f");
  Creature c1(rover, EAST);
  Creature c2(food, EAST);
  ASSERT_TRUE(c1.differentSpecies(c2) == true);
  
  c2.changeSpecies(c1);
  ASSERT_TRUE(c1.differentSpecies(c2) == false);
}

TEST(CREATURE, change_species_1) {
  Species rover("r");
  Species food("f");
  Creature c1(rover, EAST);
  Creature c2(food, EAST);
  ASSERT_TRUE(c2.toString() == "f");
  
  c2.changeSpecies(c1);
  ASSERT_TRUE(c1.differentSpecies(c2) == false);
  ASSERT_TRUE(c2.toString() == "r");
}

TEST(CREATURE, change_species_2) {
  Species rover("r");
  Species food("f");
  Creature c1(rover, EAST);
  Creature c2(food, EAST);
  Creature c3(food, WEST);
  ASSERT_TRUE(c2.toString() == "f");
  
  c2.changeSpecies(c1);
  ASSERT_TRUE(c1.differentSpecies(c2) == false);
  ASSERT_TRUE(c2.toString() == "r");
  c2.changeSpecies(c3);
  ASSERT_TRUE(c2.toString() == "f");
  
}

TEST(CREATURE, change_species_3) {
  Species rover;
  Species food("f");
  Creature c1(rover, EAST);
  Creature c2(food, EAST);

  ASSERT_TRUE(c2.toString() == "f");
  
  c2.changeSpecies(c1);
  ASSERT_TRUE(c1.differentSpecies(c2) == false);
  ASSERT_TRUE(c2.toString() == ".");
  
}

TEST(CREATURE, turn_1) {
  Species s("s");
  Creature c(s, EAST);
  
  c.turn(LEFT);
  ASSERT_TRUE(c.getDirection() == NORTH);
}

TEST(CREATURE, turn_2) {
  Species s("s");
  Creature c(s, EAST);
  
  c.turn(RIGHT);
  ASSERT_TRUE(c.getDirection() == SOUTH);
}
   
   
TEST(CREATURE, turn_3) {
  Species s("s");
  Creature c(s, SOUTH);
  
  c.turn(RIGHT);
  ASSERT_TRUE(c.getDirection() == WEST);
}   

TEST(Species, default_constructor) {
  Species s;
  
  ASSERT_TRUE(s.toString() == "");
}

TEST(Species, constructor_1) {
  Species s("s");
  ASSERT_TRUE(s.toString() == "s");
}

TEST(Species, constructor_2) {
  Species s("h");
  ASSERT_TRUE(s.toString() == "h");
}

TEST(Species, constructor_3) {
  Species s("f");
  ASSERT_TRUE(s.toString() == "f");
}

TEST(Program, add_action_1) {
  Program p;
  
  p.addAction(LEFT, 0, -1);
  
  int i = 0;
  ASSERT_TRUE(p.getAction(i, false, false, false) == LEFT);
}

TEST(Program, add_action_2) {
  Program p;
  
  p.addAction(HOP, 5, -1);
  
  int i = 5;
  ASSERT_TRUE(p.getAction(i, false, false, false) == HOP);
}

TEST(Species, add_action_1) {
  Species s("s");
  
  s.addAction(HOP, 5);
  
  int i = 5;
  ASSERT_TRUE(s.getAction(i, false, false, false) == HOP);
}

TEST(Species, add_action_2) {
  Species p;
  
  p.addAction(LEFT, 0);
  
  int i = 0;
  ASSERT_TRUE(p.getAction(i, false, false, false) == LEFT);
}

TEST(WorldState, constructor_1) {
  WorldState world(3, 3);
  std::ostringstream w;
  world.printGrid(w);
  
  std::string expected = "  012\n0 ...\n1 ...\n2 ...\n";
  std::string actual = w.str();
  
  ASSERT_TRUE(actual == expected);
}


TEST(WorldState, constructor_2) {
  WorldState world(3, 4);
  std::ostringstream w;
  world.printGrid(w);
  
  std::string expected = "  0123\n0 ....\n1 ....\n2 ....\n";
  std::string actual = w.str();
  
  ASSERT_TRUE(actual == expected);
}


TEST(WorldState, constructor_3) {
  WorldState world(2, 14);
  std::ostringstream w;
  world.printGrid(w);
  
  std::string expected = "  01234567890123\n0 ..............\n1 ..............\n";
  std::string actual = w.str();
  
  ASSERT_TRUE(actual == expected);
}

TEST(WorldState, constructor_4) {
  WorldState world(2, 101);
  std::ostringstream w;
  world.printGrid(w);
  
  std::string expected = "  01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n0 .....................................................................................................\n1 .....................................................................................................\n";
  std::string actual = w.str();
  ASSERT_TRUE(actual == expected);
}

//TODO test all the add actions

    
