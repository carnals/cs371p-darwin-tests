// --------
// includes
// --------

#include <iostream> // cout, endl
#include "gtest/gtest.h"
#define private public
#include "Darwin.h"


using namespace std;

TEST(Darwin, species_constructor1){
  Species food('f');
  ASSERT_TRUE(food.name == 'f');
}

TEST(Darwin, species_constructor2){
  Species hopper('h');
  ASSERT_TRUE(hopper.name == 'h');
}

TEST(Darwin, species_constructor3){
  Species rover('r');
  ASSERT_TRUE(rover.name == 'r');
}

TEST(Darwin, add_instruction1){
  Species food('f');
  food.add_instruction("left");
  ASSERT_TRUE(food.execute(0)[0] == 1);
}

TEST(Darwin, add_instruction2){
  Species food('f');
  food.add_instruction("go", 0);
  ASSERT_TRUE(food.execute(0)[0] == 8); 
  ASSERT_TRUE(food.execute(0)[1] == 0); 
}

TEST(Darwin, add_instruction3){
  Species food('f');
  food.add_instruction("left");
  food.add_instruction("go", 0);
  ASSERT_TRUE(food.execute(0)[0] == 1);
  ASSERT_TRUE(food.execute(1)[0] == 8); 
  ASSERT_TRUE(food.execute(1)[1] == 0); 
}

TEST(Darwin, execute1){
  Species rover('r');
  rover.add_instruction("if_enemy", 9);
  rover.add_instruction("if_empty", 7);
  rover.add_instruction("if_random", 5);
  rover.add_instruction("left");
  rover.add_instruction("go", 0); 
  rover.add_instruction("right");   
  rover.add_instruction("go", 0);
  rover.add_instruction("hop");
  rover.add_instruction("go", 0);
  rover.add_instruction("infect");
  rover.add_instruction("go", 0);
  ASSERT_TRUE(rover.execute(0)[0] == 7);
  ASSERT_TRUE(rover.execute(0)[1] == 9);
}

TEST(Darwin, execute2){
  Species rover('r');
  rover.add_instruction("if_enemy", 9);
  rover.add_instruction("if_empty", 7);
  rover.add_instruction("if_random", 5);
  rover.add_instruction("left");
  rover.add_instruction("go", 0); 
  rover.add_instruction("right");   
  rover.add_instruction("go", 0);
  rover.add_instruction("hop");
  rover.add_instruction("go", 0);
  rover.add_instruction("infect");
  rover.add_instruction("go", 0);
  ASSERT_TRUE(rover.execute(9)[0] == 3);
}

TEST(Darwin, execute3){
  Species rover('r');
  rover.add_instruction("if_enemy", 9);
  rover.add_instruction("if_empty", 7);
  rover.add_instruction("if_random", 5);
  rover.add_instruction("left");
  rover.add_instruction("go", 0); 
  rover.add_instruction("right");   
  rover.add_instruction("go", 0);
  rover.add_instruction("hop");
  rover.add_instruction("go", 0);
  rover.add_instruction("infect");
  rover.add_instruction("go", 0);
  ASSERT_TRUE(rover.execute(10)[0] == 8);
}

TEST(Darwin, creature_constructor1)
{
  Species food('f');
  Creature f1(food, 2);
  ASSERT_TRUE(f1.direction == 2);
}

TEST(Darwin, creature_constructor2)
{
  Species food('f');
  Creature f1(food, 2);
  ASSERT_TRUE(f1.round == 0);
}

TEST(Darwin, creature_constructor3)
{
  Species food('f');
  food.add_instruction("left");
  Creature f1(food, 2);
  ASSERT_TRUE(f1.species.name == 'f');
}

TEST(Darwin, creature_constructor4)
{
  Species hopper('h');
  hopper.add_instruction("hop");
  Creature h(hopper, 2);
  ASSERT_TRUE(h.species.name == 'h');
}

TEST(Darwin, creature_execute1)
{
  Species hopper('h');
  hopper.add_instruction("hop");
  Creature h(hopper, 2);
  ASSERT_TRUE(h.execute(0)[0] == 0);
}

TEST(Darwin, creature_execute2){
  Species rover('r');
  rover.add_instruction("if_enemy", 9);
  rover.add_instruction("if_empty", 7);
  rover.add_instruction("if_random", 5);
  rover.add_instruction("left");
  rover.add_instruction("go", 0); 
  rover.add_instruction("right");   
  rover.add_instruction("go", 0);
  rover.add_instruction("hop");
  rover.add_instruction("go", 0);
  rover.add_instruction("infect");
  rover.add_instruction("go", 0);
  Creature r(rover, 2);
  ASSERT_TRUE(r.execute(0)[0] == 7);
}

TEST(Darwin, creature_execute3){
  Species rover('r');
  rover.add_instruction("if_enemy", 9);
  rover.add_instruction("if_empty", 7);
  rover.add_instruction("if_random", 5);
  rover.add_instruction("left");
  rover.add_instruction("go", 0); 
  rover.add_instruction("right");   
  rover.add_instruction("go", 0);
  rover.add_instruction("hop");
  rover.add_instruction("go", 0);
  rover.add_instruction("infect");
  rover.add_instruction("go", 0);
  Creature r(rover, 2);
  ASSERT_TRUE(r.execute(0)[1] == 9);
}


TEST(Darwin, creature_isDefault){
  Species rover('r');
  Creature r(rover, 3);
  ASSERT_TRUE(r.isDefault() == false);
}

TEST(Darwin, turnLeft1)
{
  Species tester('t');
  Creature t(tester, 3);
  ASSERT_TRUE(t.direction == 3);
}

TEST(Darwin, turnLeft2)
{
  Species tester('t');
  Creature t(tester, 3);
  ASSERT_TRUE(t.direction == 3);
  t.turnLeft();
  ASSERT_TRUE(t.direction == 2);
}

TEST(Darwin, turnLeft3)
{
  Species tester('t');
  Creature t(tester, 2);
  ASSERT_TRUE(t.direction == 2);
  t.turnLeft();
  ASSERT_TRUE(t.direction == 1);
}

TEST(Darwin, turnLeft4)
{
  Species tester('t');
  Creature t(tester, 1);
  ASSERT_TRUE(t.direction == 1);
  t.turnLeft();
  ASSERT_TRUE(t.direction == 0);
}

TEST(Darwin, turnLeft5)
{
  Species tester('t');
  Creature t(tester, 0);
  ASSERT_TRUE(t.direction == 0);
  t.turnLeft();
  ASSERT_TRUE(t.direction == 3);
}

TEST(Darwin, turnRight1)
{
  Species tester('t');
  Creature t(tester, 0);
  ASSERT_TRUE(t.direction == 0);
  t.turnRight();
  ASSERT_TRUE(t.direction == 1);
}

TEST(Darwin, turnRight2)
{
  Species tester('t');
  Creature t(tester, 1);
  ASSERT_TRUE(t.direction == 1);
  t.turnRight();
  ASSERT_TRUE(t.direction == 2);
}

TEST(Darwin, turnRight3)
{
  Species tester('t');
  Creature t(tester, 2);
  ASSERT_TRUE(t.direction == 2);
  t.turnRight();
  ASSERT_TRUE(t.direction == 3);
}

TEST(Darwin, turnRight4)
{
  Species tester('t');
  Creature t(tester, 3);
  ASSERT_TRUE(t.direction == 3);
  t.turnRight();
  ASSERT_TRUE(t.direction == 0);
}

TEST(Darwin, changePC)
{
  Species tester('t');
  Creature t(tester, 3);
  t.changePC(5);
  ASSERT_TRUE(t.PC == 5);
}

TEST(Darwin, changePC1)
{
  Species tester('t');
  Creature t(tester, 3);
  t.changePC(0);
  ASSERT_TRUE(t.PC == 0);
}

TEST(Darwin, increment)
{
  Species tester('t');
  Creature t(tester, 3);
  t.incrementPC();
  ASSERT_TRUE(t.PC == 1);
}

TEST(Darwin, infect1)
{
  Species tester('t');
  Creature t(tester, 2);
  ASSERT_TRUE(t.species.name == 't');
}

TEST(Darwin, infect2)
{
  Species tester('t');
  Creature t(tester, 3);
  Species infecter('i');
  Creature i(infecter, 3);
  t.infectBy(i);
  ASSERT_TRUE(t.species.name == 'i');
}

TEST(Darwin, infect3)
{
  Species tester('t');
  Creature t(tester, 3);
  Species infecter('i');
  Creature i(infecter, 3);
  t.infectBy(i);
  ASSERT_TRUE(t.PC == 0);
}

TEST(Darwin, infect4)
{
  Species tester('t');
  Creature t(tester, 3);
  t.incrementPC();
  ASSERT_TRUE(t.PC == 1);
  Species infecter('i');
  Creature i(infecter, 3);
  t.infectBy(i);
  ASSERT_TRUE(t.PC == 0);
}

TEST(Darwin, word_constructor)
{
    World w(1,1);
    ASSERT_TRUE(w.length == 1);
}

TEST(Darwin, word_constructor2)
{
    World w(1,2);
    ASSERT_TRUE(w.length == 1);
}

TEST(Darwin, word_constructor3)
{
    World w(1,2);
    ASSERT_TRUE(w.width == 2);
}

TEST(Darwin, addCreature1)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(true); //make sure there are no seg faults
}

TEST(Darwin, addCreature2)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.board[0][0].species.name == 't');
}

TEST(Darwin, addCreature3)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    Species tester2('m');
    Creature m(tester2, 3);
    w.addCreature(t, 0, 0);
    w.addCreature(m, 1, 1);
    ASSERT_TRUE(w.board[0][0].species.name == 't');
    ASSERT_TRUE(w.board[1][1].species.name == 'm');
}

TEST(Darwin, nextRow1)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextRow(t, 0) == 1);
}

TEST(Darwin, nextRow2)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 1);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextRow(t, 0) == -1);
}

TEST(Darwin, nextRow3)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 0);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextRow(t, 0) == 0);
}

TEST(Darwin, nextRow4)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 2);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextRow(t, 0) == 0);
}

TEST(Darwin, nextCol)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 2);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextCol(t, 0) == 1);
}

TEST(Darwin, nextCol2)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 0);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextCol(t, 0) == -1);
}

TEST(Darwin, nextCol3)
{
    World w(1,1);
    Species tester('t');
    Creature t(tester, 1);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.nextCol(t, 0) == 0);
}

TEST(Darwin, isEmpty)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 1);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.is_empty(t, 0, 0) == 0);
}

TEST(Darwin, isEmpty1)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.is_empty(t, 0, 0) == 1);
}

TEST(Darwin, isEmpty2)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 1);
    w.addCreature(t, 1, 1);
    ASSERT_TRUE(w.is_empty(t, 1, 1) == 1);
}

TEST(Darwin, isWall)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 2);
    w.addCreature(t, 1, 1);
    ASSERT_TRUE(w.is_wall(t, 1, 1) == 1);
}

TEST(Darwin, isWall2)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 1, 1);
    ASSERT_TRUE(w.is_wall(t, 1, 1) == 1);
}

TEST(Darwin, isEnemy1)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    ASSERT_TRUE(w.is_enemy(t, 0, 0) == 0);
}

TEST(Darwin, isEnemy2)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    w.addCreature(t, 0, 1);
    w.addCreature(t, 1, 0);
    ASSERT_TRUE(w.is_enemy(t, 0, 0) == 0);
}

TEST(Darwin, isEnemy3)
{
    World w(2,2);
    Species tester('t');
    Creature t(tester, 3);
    w.addCreature(t, 0, 0);
    Species enemy('e');
    Creature e(enemy, 3);
    w.addCreature(e, 1, 0);
    ASSERT_TRUE(w.is_enemy(t, 0, 0) == 1);
}

TEST(Darwin, run1)
{
    World w(2,2);
    w.run(5);
    ASSERT_TRUE(w.round == 5);
}

TEST(Darwin, run2)
{
    World w(2,2);
    w.run(100);
    ASSERT_TRUE(w.round == 100);
}

TEST(Darwin, run3)
{
    World w(2,2);
    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);
    Creature h(hopper, 2);
    w.addCreature(h, 0, 0);
    w.run(5);
    ASSERT_TRUE(w.board[0][1].species.name == 'h');
}

TEST(Darwin, run4)
{
    World w(2,2);
    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);
    Species eater('e');
    eater.add_instruction("infect");
    eater.add_instruction("go", 0);
    Creature h(hopper, 2);
    Creature e(eater, 0);
    w.addCreature(h, 0, 0);
    w.addCreature(e, 0, 1);
    w.run(5);
    ASSERT_TRUE(w.board[0][0].species.name == 'e');
}
