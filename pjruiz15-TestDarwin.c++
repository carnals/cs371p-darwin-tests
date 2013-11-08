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
#include <string>   // ==
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"
#define private public
#include "Darwin.h"

#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

// -----------
// TestDarwin
// -----------

//
//Species
//

//Species(char sym);
TEST(Darwin, species_1) {
  Species spec('b');
  ASSERT_EQ(spec.retSymbol(), 'b');
}

TEST(Darwin, species_2) {
  try {
    Species spec('\n');
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    ASSERT_TRUE(true);
  }
}

TEST(Darwin, species_3) {
  Species spec;
  ASSERT_EQ(spec.retSymbol(), '.');
}

//void addInstruction(std::string inst);
TEST(Darwin, addInstruction_1) {
  Species spec('b');
  spec.addInstruction("nothing");
  ASSERT_EQ(spec.nextInstruction(0).compare("nothing"), 0);
}

TEST(Darwin, addInstruction_2) {
  try {
    Species spec('b');
    spec.addInstruction("");
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    ASSERT_TRUE(true);
  } 
}

TEST(Darwin, addInstruction_3) {
  Species spec('b');
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  ASSERT_EQ(spec.nextInstruction(1).compare("nothing"), 0);
}

//std::string nextInstruction(int index);
TEST(Darwin, nextInstruction_1) {
  Species spec('b');
  spec.addInstruction("hop");
  spec.addInstruction("hop");
  spec.addInstruction("hopi");
  ASSERT_EQ(spec.nextInstruction(2).compare("hopi"), 0);
}

TEST(Darwin, nextInstruction_2) {
  Species spec('b');
  try {
    spec.addInstruction("hop");
    spec.nextInstruction(-1);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    ASSERT_TRUE(true);
  }
}

TEST(Darwin, nextInstruction_3) {
  Species spec('b');
  try {
    spec.addInstruction("hop");
    spec.nextInstruction(2);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    ASSERT_TRUE(true);
  }
}

TEST(Darwin, nextInstruction_4) {
  Species spec('b');
  try {
    spec.nextInstruction(0);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    ASSERT_TRUE(true);
  }
}

//char retSymbol();
TEST(Darwin, retSymbol_1) {
  Species spec('b');
  ASSERT_EQ(spec.retSymbol(), 'b');
}

TEST(Darwin, retSymbol_2) {
  Species spec('A');
  ASSERT_EQ(spec.retSymbol(), 'A');
}

TEST(Darwin, retSymbol_3) {
  Species spec('\t');
  ASSERT_EQ(spec.retSymbol(), '\t');
}


//
//Creature
//

//Creature(Species spec, int dir);
TEST(Darwin, creature_1) {
  Creature creature;
  ASSERT_TRUE(creature.retSpecies().retSymbol() == '.');
  ASSERT_TRUE(creature.facingDir(WEST));
}

TEST(Darwin, creature_2) {
  Species spec('b');
  Creature creature(spec);
  ASSERT_TRUE(creature.retSpecies().retSymbol() == 'b');
  ASSERT_TRUE(creature.facingDir(WEST));
}

TEST(Darwin, creature_3) {
  Species spec('b');
  Creature creature(spec, SOUTH);
  ASSERT_TRUE(creature.retSpecies().retSymbol() == 'b');
  ASSERT_TRUE(creature.facingDir(SOUTH));
}

TEST(Darwin, creature_4) {
  Species spec('b');
  try {
    Creature creature(spec, 4);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    
  }
}

TEST(Darwin, creature_5) {
  Species spec('b');
  try {
    Creature creature(spec, -1);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {
    
  }
}

//std::string nextAction();
TEST(Darwin, nextAction_1) {
  Species spec('b');
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  Creature creature(spec);
  ASSERT_EQ(creature.nextAction().compare("hop"), 0);
  ASSERT_EQ(creature.nextAction().compare("nothing"), 0);
}

TEST(Darwin, nextAction_2) {
  Species spec('b');
  Creature creature(spec);
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  try {
    creature.nextAction();
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {

  }
}

TEST(Darwin, nextAction_3) {
  Species spec('b');
  Creature creature(spec);
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  try {
    creature.nextAction();
    creature.nextAction();
    creature.nextAction();
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {

  }
}

//void changeSpecies(Species spec);
TEST(Darwin, changeSpecies_1) {
  Species spec('b');
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  Creature creature(spec);
  Species spec2('c');
  spec2.addInstruction("hop");
  spec2.addInstruction("nothing");
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
  ASSERT_EQ(spec2.retSymbol(), 'c');
  creature.changeSpecies(spec2);
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'c');
}

TEST(Darwin, changeSpecies_2) {
  Species spec('b');
  spec.addInstruction("hop");
  spec.addInstruction("nothing");
  Creature creature(spec);
  Species spec2('b');
  spec2.addInstruction("hop");
  spec2.addInstruction("nothing");
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
  ASSERT_EQ(spec2.retSymbol(), 'b');
  creature.nextAction();
  creature.changeSpecies(spec2);
  ASSERT_EQ(creature.nextAction().compare("nothing"), 0);
}

TEST(Darwin, changeSpecies_3) {
  Species spec('b');
  Creature creature(spec);
  Species spec2;
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
  ASSERT_EQ(spec2.retSymbol(), '.');
  creature.changeSpecies(spec2);
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
}

//bool facingDir(int dir);
TEST(Darwin, facingDir_1) {
  Creature creature;
  ASSERT_TRUE(creature.facingDir(WEST));
}

TEST(Darwin, facingDir_2) {
  Creature creature;
  ASSERT_FALSE(creature.facingDir(EAST));
}

TEST(Darwin, facingDir_3) {
  Creature creature(Species(), EAST);
  ASSERT_TRUE(creature.facingDir(EAST));
}

//void turnDir(bool right);
TEST(Darwin, turnDir_1) {
  Creature creature;
  ASSERT_TRUE(creature.facingDir(WEST));
  creature.turnDir(true);
  ASSERT_TRUE(creature.facingDir(NORTH));
}

TEST(Darwin, turnDir_2) {
  Creature creature;
  ASSERT_TRUE(creature.facingDir(WEST));
  creature.turnDir(false);
  ASSERT_TRUE(creature.facingDir(SOUTH));
}

TEST(Darwin, turnDir_3) {
  Creature creature(Species(), SOUTH);
  ASSERT_TRUE(creature.facingDir(SOUTH));
  creature.turnDir(true);
  ASSERT_TRUE(creature.facingDir(WEST));
}

//void action();
TEST(Darwin, action_1) {
  Creature creature;
  creature.action();
  ASSERT_TRUE(creature.turnMoved(0));
}

TEST(Darwin, action_2) {
  Creature creature;
  creature.action();
  creature.action();
  ASSERT_FALSE(creature.turnMoved(2));
}

//bool turnMoved(int turn);
TEST(Darwin, turnMoved_1) {
  Creature creature;
  ASSERT_FALSE(creature.turnMoved(0));
}

TEST(Darwin, turnMoved_2) {
  Creature creature;
  ASSERT_TRUE(creature.turnMoved(1));
}

TEST(Darwin, turnMoved_3) {
  Creature creature;
  creature.action();
  ASSERT_TRUE(creature.turnMoved(0));
}

//void jump(int ind);
TEST(Darwin, jump_1) {
  Species species('b');
  species.addInstruction("hop");
  species.addInstruction("nothing");
  Creature creature(species);
  creature.jump(1);
  ASSERT_EQ(creature.nextAction().compare("nothing"), 0);
}

TEST(Darwin, jump_2) {
  Species species('b');
  species.addInstruction("hop");
  species.addInstruction("nothing");
  Creature creature(species);
  creature.nextAction();
  creature.jump(0);
  ASSERT_EQ(creature.nextAction().compare("hop"), 0);
}

TEST(Darwin, jump_3) {
  Species species('b');
  species.addInstruction("hop");
  species.addInstruction("nothing");
  Creature creature(species);
  creature.jump(5);
  try {
    creature.nextAction();
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {

  }
}

//Species retSpecies();
TEST(Darwin, retSpecies_1) {
  Creature creature;
  ASSERT_EQ(creature.retSpecies().retSymbol(), '.');
}

TEST(Darwin, retSpecies_2) {
  Species spec('b');
  Creature creature(spec);
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
}

TEST(Darwin, retSpecies_3) {
  Species spec('b');
  Creature creature;
  creature.changeSpecies(spec);
  ASSERT_EQ(creature.retSpecies().retSymbol(), 'b');
}


//
//World
//

//World(int x, int y);
TEST(Darwin, world_1) {
  World world(3,3);
}

TEST(Darwin, world_2) {
  World world(1, 80);
}

TEST(Darwin, world_3) {
  try {
    World world(-1, 0);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {

  }
}

TEST(Darwin, world_4) {
  try {
    World world(4, -1);
    ASSERT_FALSE(true);
  } catch (const std::invalid_argument&) {

  }
}

//void doAction(int x, int y, int turn);
TEST(Darwin, doAction_1) {
  Species spec('b');
  spec.addInstruction("hop");
  Creature creature(spec, EAST);
  World world(1, 2);
  world.place(creature, 0, 0);
  world.doAction(0,0,0);
  ASSERT_EQ(world.map[0][1].retSpecies().retSymbol(), 'b');
}

TEST(Darwin, doAction_2) {
  Species spec('b');
  spec.addInstruction("infect");
  Creature creature(spec, EAST);
  Species spec2('c');
  spec2.addInstruction("nothing");
  Creature creature2(spec2, NORTH);
  World world(1, 2);
  world.place(creature, 0, 0);
  world.place(creature, 0, 1);
  world.turn(0, false);
  ASSERT_EQ(world.map[0][1].retSpecies().retSymbol(), 'b');
}

TEST(Darwin, doAction_3) {
  Species spec('b');
  spec.addInstruction("right");
  Creature creature(spec, WEST);
  World world(1, 1);
  world.place(creature, 0, 0);
  world.doAction(0,0,0);
  ASSERT_TRUE(world.map[0][0].facingDir(NORTH));
}

TEST(Darwin, doAction_4) {
  Species spec('b');
  spec.addInstruction("nothing");
  Creature creature(spec, EAST);
  World world(1, 2);
  world.place(creature, 0, 0);
  world.turn(0, false);
  ASSERT_EQ(world.map[0][0].retSpecies().retSymbol(), 'b');
}

TEST(Darwin, doAction_5) {
  Species spec('b');
  spec.addInstruction("if_wall 2");
  spec.addInstruction("right");
  spec.addInstruction("left");
  Creature creature(spec, EAST);
  World world(1, 1);
  world.place(creature, 0, 0);
  world.turn(0, false);
  ASSERT_TRUE(world.map[0][0].facingDir(NORTH));
}

TEST(Darwin, doAction_6) {
  Species spec('b');
  spec.addInstruction("if_enemy 2");
  spec.addInstruction("right");
  spec.addInstruction("left");
  Creature creature(spec, EAST);
  World world(1, 1);
  world.place(creature, 0, 0);
  world.turn(0, false);
  ASSERT_TRUE(world.map[0][0].facingDir(SOUTH));
}

