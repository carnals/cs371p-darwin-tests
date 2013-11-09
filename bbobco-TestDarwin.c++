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

#include <string>
#include <cstdlib>
#include <stdexcept>
#include "gtest/gtest.h"

#define private public

#include "Darwin.h"
using namespace std;

// ------------
// Darwin Tests
// ------------

//note: correct functionality of my simulate() function requires EVERYTHING to work correctly, so it is only tested in acceptance tests

TEST(Darwin, game_constructor){
  game g(1,2);
  ASSERT_TRUE(g.width==2);
  ASSERT_TRUE(g.height==1);
}

TEST(Darwin, game_constructor2){
  game g(50,50);
  ASSERT_TRUE(g.width==50);
  ASSERT_TRUE(g.height==50);
}
TEST(Darwin, game_constructor3){
  game g(1,25);
  ASSERT_TRUE(g.width==25);
  ASSERT_TRUE(g.height==1);
}

TEST(Darwin, species_constructor1){
  species s('h');
  ASSERT_TRUE(s.name=='h');
}
TEST(Darwin, species_constructor2){
  species s('f');
  ASSERT_TRUE(s.name=='f');
}
TEST(Darwin, species_constructor3){
  species s('r');
  ASSERT_TRUE(s.name=='r');
}

TEST(Darwin, instruction_constructor1){
  instruction i (1,1);
  ASSERT_TRUE(i.arg1==1);
  ASSERT_TRUE(i.arg2==1);
}
TEST(Darwin, instruction_constructor2){
  instruction i (3,1);
  ASSERT_TRUE(i.arg1==3);
  ASSERT_TRUE(i.arg2==1);
}
TEST(Darwin, instruction_constructor3){
  instruction i (5,6);
  ASSERT_TRUE(i.arg1==5);
  ASSERT_TRUE(i.arg2==6);
}

TEST(Darwin, add_instruction1){
  species s('f');
  s.addInstruction(1,2);
  ASSERT_TRUE(s.instructions[0].arg1==1);
  ASSERT_TRUE(s.instructions[0].arg2==2);
}
TEST(Darwin, add_instruction2){
  species s('g');
  s.addInstruction(5,1);
  ASSERT_TRUE(s.instructions[0].arg1==5);
  ASSERT_TRUE(s.instructions[0].arg2==1);
}
TEST(Darwin, add_instruction3){
  species s('z');
  s.addInstruction(5,5);
  ASSERT_TRUE(s.instructions[0].arg1==5);
  ASSERT_TRUE(s.instructions[0].arg2==5);
}
TEST(Darwin, add_instruction4){
  species s('z');
  s.addInstruction(5);
  ASSERT_TRUE(s.instructions[0].arg1==5);
}
TEST(Darwin, add_instruction5){
  species s('g');
  s.addInstruction(6);
  ASSERT_TRUE(s.instructions[0].arg1==6);
}
TEST(Darwin, add_instruction6){
  species s('n');
  s.addInstruction(0);
  ASSERT_TRUE(s.instructions[0].arg1==0);
}
TEST(Darwin, add_instruction7){
  species s('r');
  s.addInstruction("hop");
  ASSERT_TRUE(s.instructions[0].arg1==3);
}
TEST(Darwin, add_instruction8){
  species s('r');
  s.addInstruction("go 5");
  ASSERT_TRUE(s.instructions[0].arg1==0);
  ASSERT_TRUE(s.instructions[0].arg2==5);
}
TEST(Darwin, add_instruction9){
  species s('r');
  s.addInstruction("if_empty 5");
  ASSERT_TRUE(s.instructions[0].arg1==4);
  ASSERT_TRUE(s.instructions[0].arg2==5);
}
TEST(Darwin, add_instruction10){
  species s('r');
  s.addInstruction("if_wall 4");
  ASSERT_TRUE(s.instructions[0].arg1==6);
  ASSERT_TRUE(s.instructions[0].arg2==4);
}

TEST(Darwin, creature_constructor1){
  species s('r');
  creature c (5,15,north,s);
  ASSERT_TRUE(c.x==15);
  ASSERT_TRUE(c.y==5);
  ASSERT_TRUE(c.dir==north);
  ASSERT_TRUE(c.spec.name=='r'); 
}
TEST(Darwin, creature_constructor2){
  species s('h');
  creature c (1,2,east,s);
  ASSERT_TRUE(c.x==2);
  ASSERT_TRUE(c.y==1);
  ASSERT_TRUE(c.dir==east);
  ASSERT_TRUE(c.spec.name=='h'); 
}
TEST(Darwin, creature_constructor3){
  species s('n');
  creature c (6,6,west,s);
  ASSERT_TRUE(c.x==6);
  ASSERT_TRUE(c.y==6);
  ASSERT_TRUE(c.dir==west);
  ASSERT_TRUE(c.spec.name=='n'); 
}
TEST(Darwin, hop1){
  game g(5,5);
  species s('h');
  creature c (1,1,east,s);
  c.hop();
  ASSERT_TRUE(c.x==2);
}
TEST(Darwin, hop2){
  game g(5,5);
  species s('h');
  creature c (2,2,south,s);
  c.hop();
  ASSERT_TRUE(c.y==3);
}
TEST(Darwin, hop3){
  game g(5,5);
  species s('h');
  creature c (1,1,west,s);
  c.hop();
  ASSERT_TRUE(c.x==0);
}

TEST(Darwin,infect1){
  game g(5,5);
  species r('r');
  species h('h');
  creature c1 (1,1,east,r);
  creature c2 (1,2,east,h);
  g.addCreature(c1);
  g.addCreature(c2);
  c1.infect();
  ASSERT_TRUE(c2.spec.name=='r');
}
TEST(Darwin,infect2){
  game g(5,5);
  species r('r');
  species h('h');
  creature c1 (3,3,south,r);
  creature c2 (4,3,east,h);
  g.addCreature(c1);
  g.addCreature(c2);
  c1.infect();
  ASSERT_TRUE(c2.spec.name=='r');
}
TEST(Darwin,infect3){
  game g(5,5);
  species r('r');
  species h('h');
  creature c1 (4,4,north,r);
  creature c2 (3,4,east,h);
  g.addCreature(c1);
  g.addCreature(c2);
  c1.infect();
  ASSERT_TRUE(c2.spec.name=='r');
}
TEST(Darwin,infect4){
  game g(5,5);
  species r('r');
  species h('h');
  creature c1 (2,3,east,r);
  creature c2 (2,4,east,h);
  g.addCreature(c1);
  g.addCreature(c2);
  c2.pc = 5;
  c1.infect();
  ASSERT_TRUE(c2.spec.name=='r');
  ASSERT_TRUE(c2.pc == 0);
}
TEST(Darwin, ifEmpty1){
  game g(5,5);
  species s('h');
  creature c(1,1,south,s);
  g.addCreature(c);
  ASSERT_TRUE(c.ifEmpty());
}
TEST(Darwin, ifEmpty2){
  game g(5,5);
  species s('h');
  creature c(1,1,south,s);
  creature c2(2,1,south,s);
  g.addCreature(c);
  g.addCreature(c2);
  ASSERT_FALSE(c.ifEmpty());
}
TEST(Darwin, ifEmpty3){
  game g(5,5);
  species s('h');
  creature c(4,4,east,s);
  g.addCreature(c);
  ASSERT_FALSE(c.ifEmpty());
}
TEST(Darwin, ifEmpty4){
  game g(5,5);
  species s('h');
  creature c(4,4,east,s);
  creature c2(4,3,west,s);
  g.addCreature(c);
  ASSERT_FALSE(c.ifEmpty());
}
TEST(Darwin, ifWall1){
  game g(5,5);
  species s('h');
  creature c(4,4,east,s);
  g.addCreature(c);
  ASSERT_TRUE(c.ifWall());
}
TEST(Darwin, ifWall2){
  game g(5,5);
  species s('h');
  creature c(3,3,east,s);
  g.addCreature(c);
  ASSERT_FALSE(c.ifWall());
}
TEST(Darwin, ifWall3){
  game g(5,5);
  species s('h');
  creature c(4,4,west,s);
  g.addCreature(c);
  ASSERT_FALSE(c.ifWall());
}
TEST(Darwin, ifEnemy1){
  game g(5,5);
  species s('h');
  species s2('r');
  creature c(1,1,south,s);
  creature c2(2,1,south,s2);
  g.addCreature(c);
  g.addCreature(c2);
  ASSERT_TRUE(c.ifEnemy());
}
TEST(Darwin, ifEnemy2){
  game g(5,5);
  species s('h');
  creature c(1,1,south,s);
  creature c2(2,1,south,s);
  g.addCreature(c);
  g.addCreature(c2);
  ASSERT_FALSE(c.ifEnemy());
}
TEST(Darwin, ifEnemy3){
  game g(5,5);
  species s('h');
  species s2('r');
  creature c(4,4,west,s);
  creature c2(1,1,south,s2);
  g.addCreature(c);
  g.addCreature(c2);
  ASSERT_FALSE(c.ifEnemy());
}

TEST(Darwin, action1){
  game g(5,5);
  species s('h');
  s.addInstruction("hop");
  creature c(2,2,east,s);
  s.action(c);
  ASSERT_TRUE(c.x==3);
}
TEST(Darwin, action2){
  game g(5,5);
  species s('h');
  s.addInstruction("if_empty 1");
  s.addInstruction("right");
  creature c(2,2,east,s);
  s.action(c);
  ASSERT_TRUE(c.dir==south);
}
TEST(Darwin, action3){
  game g(5,5);
  species s('h');
  s.addInstruction("if_empty 2");
  s.addInstruction("right");
  s.addInstruction("hop");
  creature c(2,2,east,s);
  s.action(c);
  ASSERT_TRUE(c.x==3);
}
TEST(Darwin, addCreature1){
  game g(5,5);
  species s('h');
  creature c(1,1,east,s);
  g.addCreature(c);
  ASSERT_TRUE(g.grid[1*game::width + 1]==&c);
}
TEST(Darwin, addCreature2){
  game g(5,5);
  species s('h');
  creature c(3,3,east,s);
  g.addCreature(c);
  ASSERT_TRUE(g.grid[1*game::width + 1]==0);
  ASSERT_TRUE(g.grid[3*game::width + 3]==&c);
}
TEST(Darwin, addCreature3){
  game g(5,5);
  species s('h');
  creature c(4,1,east,s);
  g.addCreature(c);
  ASSERT_TRUE(g.grid[4*game::width + 1]==&c);
}











