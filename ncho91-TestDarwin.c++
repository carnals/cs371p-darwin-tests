#include <iostream> 
#include <sstream>  
#include <string>  
#include <vector>
#include "gtest/gtest.h"
#include "Darwin.h"

TEST(Darwin, add_instructions_food) {
	Species test = Species(Food);
	test.addInstructions(left, 0);
	test.addInstructions(go, 0);

	ASSERT_TRUE(test._v[0]._i == left);
	ASSERT_TRUE(test._v[1]._i == go);
}

TEST(Darwin, add_instructions_hopper) {
	Species test = Species(Hopper);
	test.addInstructions(hop, 0);
	test.addInstructions(go, 0);

	ASSERT_TRUE(test._v[0]._i == hop);
	ASSERT_TRUE(test._v[1]._i == go);
}

TEST(Darwin, add_instructions_rover) {
	Species test = Species(Rover);

	test.addInstructions(if_enemy, 9);
	test.addInstructions(if_empty, 7);
	test.addInstructions(if_random, 5);
	test.addInstructions(left, 0);
	test.addInstructions(go, 0);
	test.addInstructions(right, 0);
	test.addInstructions(go, 0);
	test.addInstructions(hop, 0);
	test.addInstructions(go, 0);
	test.addInstructions(infect, 0);
	test.addInstructions(go, 0);

	ASSERT_TRUE(test._v[0]._i == if_enemy);
	ASSERT_TRUE(test._v[1]._i == if_empty);
	ASSERT_TRUE(test._v[2]._i == if_random);
	ASSERT_TRUE(test._v[3]._i == left);
	ASSERT_TRUE(test._v[4]._i == go);
	ASSERT_TRUE(test._v[5]._i == right);
	ASSERT_TRUE(test._v[6]._i == go);
	ASSERT_TRUE(test._v[7]._i == hop);
	ASSERT_TRUE(test._v[8]._i == go);
	ASSERT_TRUE(test._v[9]._i == infect);
	ASSERT_TRUE(test._v[10]._i == go);
}

TEST(Darwin, add_instructions_trap) {
	Species test = Species(Trap);

	test.addInstructions(if_enemy, 3);
    test.addInstructions(left, 0);
    test.addInstructions(go, 0);
    test.addInstructions(infect, 0);
    test.addInstructions(go, 0);

	ASSERT_TRUE(test._v[0]._i == if_enemy);
	ASSERT_TRUE(test._v[1]._i == left);
	ASSERT_TRUE(test._v[2]._i == go);
	ASSERT_TRUE(test._v[3]._i == infect);
	ASSERT_TRUE(test._v[4]._i == go);
}

TEST(Darwin, add_creature1) {
	Darwin x(2, 2);
	Species test1 = Species(Hopper);
	Species test2 = Species(Rover);
	Creature f1 = Creature(test1, East, 0, 0);
	Creature f2 = Creature(test2, North, 1, 0);

	x.addCreature(f1);
	x.addCreature(f2);

	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);

	ASSERT_TRUE(x.grid[0][0]._d == East);
	ASSERT_TRUE(x.grid[1][0]._d == North);
}

TEST(Darwin, add_creature2) {
	Darwin x(4, 4);
	Species h1 = Species(Hopper);
	Species r1 = Species(Rover);
	Species f1 = Species(Food);
	Species f2= Species(Food);

	Creature c1 = Creature(h1, East, 0, 0);
	Creature c2 = Creature(r1, North, 1, 0);
	Creature c3 = Creature(f1, North, 0, 3);
	Creature c4 = Creature(f2, West, 3, 3);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);

	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);
	ASSERT_TRUE(x.grid[0][3]._s._type == Food);
	ASSERT_TRUE(x.grid[3][3]._s._type == Food);

	ASSERT_TRUE(x.grid[0][0]._d == East);
	ASSERT_TRUE(x.grid[1][0]._d == North);
	ASSERT_TRUE(x.grid[0][3]._d == North);
	ASSERT_TRUE(x.grid[3][3]._d == West);
}

TEST(Darwin, add_creature3) {
	Darwin x(8, 8);
	Species h1 = Species(Hopper);
	Species h2 = Species(Hopper);
	Species h3 = Species(Hopper);
	Species r1 = Species(Rover);
	Species f1 = Species(Food);
	Species f2= Species(Food);

	Creature c1 = Creature(h1, East, 4, 4);
	Creature c2 = Creature(h2, South, 0, 7);
	Creature c3 = Creature(h3, West, 3, 0);
	Creature c4 = Creature(r1, North, 1, 0);
	Creature c5 = Creature(f1, North, 2, 3);
	Creature c6 = Creature(f2, West, 3, 3);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);
	x.addCreature(c5);
	x.addCreature(c6);

	ASSERT_TRUE(x.grid[4][4]._s._type == Hopper);
	ASSERT_TRUE(x.grid[0][7]._s._type == Hopper);
	ASSERT_TRUE(x.grid[3][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);
	ASSERT_TRUE(x.grid[2][3]._s._type == Food);
	ASSERT_TRUE(x.grid[3][3]._s._type == Food);

	ASSERT_TRUE(x.grid[4][4]._d == East);
	ASSERT_TRUE(x.grid[0][7]._d == South);
	ASSERT_TRUE(x.grid[3][0]._d == West);
	ASSERT_TRUE(x.grid[1][0]._d == North);
	ASSERT_TRUE(x.grid[2][3]._d == North);
	ASSERT_TRUE(x.grid[3][3]._d == West);
}

TEST(Darwin, do_instruction_food) {
	Darwin x(2,2);

	Species food = Species(Food);
	food.addInstructions(left, 0);
    food.addInstructions(go, 0);

	Creature f1 = Creature(food, East, 0, 0);
	x.addCreature(f1);

	x.doInstruction(x.grid[0][0]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Food);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);

	ASSERT_TRUE(x.grid[0][0]._d == North);
}

TEST(Darwin, do_instruction_hopper) {
	Darwin x(2,2);

	Species hopper = Species(Hopper);
	hopper.addInstructions(hop, 0);
    hopper.addInstructions(go, 0);

	Creature h1 = Creature(hopper, East, 0, 0);
	x.addCreature(h1);

	x.doInstruction(x.grid[0][0]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);

	x.grid[0][1]._turnPassed = false;
	x.doInstruction(x.grid[0][1]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);
}

TEST(Darwin, do_instruction_rover) {
	Darwin x(2,2);

	Species hopper = Species(Hopper);
	hopper.addInstructions(hop, 0);
    hopper.addInstructions(go, 0);

    Species rover = Species(Rover);
    rover.addInstructions(if_enemy, 9);
    rover.addInstructions(if_empty, 7);
    rover.addInstructions(if_random, 5);
    rover.addInstructions(left, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(right, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(hop, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(infect, 0);
    rover.addInstructions(go, 0);

	Creature h1 = Creature(hopper, South, 0, 1);
	Creature r1 = Creature(rover, East, 1, 0);
	x.addCreature(h1);
	x.addCreature(r1);

	x.doInstruction(x.grid[0][1]);
	x.doInstruction(x.grid[1][0]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);
	ASSERT_TRUE(x.grid[1][1]._s._type == Rover);
}

TEST(Darwin, do_instruction_trap) {
	Darwin x(3,3);

	Species hopper = Species(Hopper);
	hopper.addInstructions(hop, 0);
    hopper.addInstructions(go, 0);

    Species trap = Species(Trap);
    trap.addInstructions(if_enemy, 3);
    trap.addInstructions(left, 0);
    trap.addInstructions(go, 0);
    trap.addInstructions(infect, 0);
    trap.addInstructions(go, 0);
    
	Creature h1 = Creature(hopper, East, 2, 0);
	Creature t1 = Creature(trap, West, 2, 2);
	x.addCreature(h1);
	x.addCreature(t1);

	x.doInstruction(x.grid[2][0]);
	x.doInstruction(x.grid[2][2]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][1]._s._type == Trap);
	ASSERT_TRUE(x.grid[2][2]._s._type == Trap);

	x.grid[2][1]._turnPassed = false;
	x.grid[2][2]._turnPassed = false;

	x.doInstruction(x.grid[2][1]);
	x.doInstruction(x.grid[2][2]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][1]._s._type == Trap);
	ASSERT_TRUE(x.grid[2][2]._s._type == Trap);
	ASSERT_TRUE(x.grid[2][1]._d == North);
	ASSERT_TRUE(x.grid[2][2]._d == South);
}

TEST(Darwin, do_instruction_clash) {
	Darwin x(3,3);

    Species rover = Species(Rover);
    rover.addInstructions(if_enemy, 9);
    rover.addInstructions(if_empty, 7);
    rover.addInstructions(if_random, 5);
    rover.addInstructions(left, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(right, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(hop, 0);
    rover.addInstructions(go, 0);
    rover.addInstructions(infect, 0);
    rover.addInstructions(go, 0);

    Species trap = Species(Trap);
    trap.addInstructions(if_enemy, 3);
    trap.addInstructions(left, 0);
    trap.addInstructions(go, 0);
    trap.addInstructions(infect, 0);
    trap.addInstructions(go, 0);

	Creature r1 = Creature(rover, South, 0, 1);
	Creature t1 = Creature(trap, East, 2, 1);
	x.addCreature(r1);
	x.addCreature(t1);

	x.doInstruction(x.grid[0][1]);
	x.doInstruction(x.grid[2][1]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Rover);
	ASSERT_TRUE(x.grid[1][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][1]._s._type == Trap);
	ASSERT_TRUE(x.grid[2][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._d == South);
	ASSERT_TRUE(x.grid[2][1]._d == North);

	x.grid[1][1]._turnPassed = false;
	x.grid[2][1]._turnPassed = false;

	x.doInstruction(x.grid[1][1]);
	x.doInstruction(x.grid[2][1]);

	ASSERT_TRUE(x.grid[0][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][1]._s._type == Empty);
	ASSERT_TRUE(x.grid[0][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._s._type == Rover);
	ASSERT_TRUE(x.grid[1][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][0]._s._type == Empty);
	ASSERT_TRUE(x.grid[2][1]._s._type == Rover);
	ASSERT_TRUE(x.grid[2][2]._s._type == Empty);
	ASSERT_TRUE(x.grid[1][1]._d == South);
}

TEST(Darwin, turn_Left1){
	Darwin x(2,2);
	Species f1 = Species(Food);
	Creature c1 = Creature(f1, North, 0, 0);

	x.addCreature(c1);

	turnLeft(c1, x);

	ASSERT_TRUE(x.grid[0][0]._d == West);
}

TEST(Darwin, turn_Left2){
	Darwin x(2,2);
	Species f1 = Species(Food);
	Species f2 = Species(Food);
	Species f3 = Species(Food);
	Species f4 = Species(Food);

	Creature c1 = Creature(f1, North, 0, 0);
	Creature c2 = Creature(f2, West, 0, 1);
	Creature c3 = Creature(f3, South, 1, 0);
	Creature c4 = Creature(f4, East, 1, 1);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);

	turnLeft(c1, x);
	turnLeft(c2, x);
	turnLeft(c3, x);
	turnLeft(c4, x);

	ASSERT_TRUE(x.grid[0][0]._d == West);
	ASSERT_TRUE(x.grid[0][1]._d == South);
	ASSERT_TRUE(x.grid[1][0]._d == East);
	ASSERT_TRUE(x.grid[1][1]._d == North);
}

TEST(Darwin, turn_Left3){
	Darwin x(3,3);

	Species f1 = Species(Food);
	Species f2 = Species(Food);
	Species f3 = Species(Food);
	Species h1 = Species(Hopper);
	Species h2 = Species(Hopper);
	Species r1 = Species(Rover);
	Species t1 = Species(Trap);

	Creature c1 = Creature(f1, North, 0, 0);
	Creature c2 = Creature(f2, West, 0, 1);
	Creature c3 = Creature(f3, South, 1, 0);
	Creature c4 = Creature(h1, East, 1, 1);
	Creature c5 = Creature(h2, North, 2, 0);
	Creature c6 = Creature(r1, West, 2, 1);
	Creature c7 = Creature(t1, East, 2, 2);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);
	x.addCreature(c5);
	x.addCreature(c6);
	x.addCreature(c7);

	turnLeft(c1, x);
	turnLeft(c2, x);
	turnLeft(c3, x);
	turnLeft(c4, x);
	turnLeft(c5, x);
	turnLeft(c6, x);
	turnLeft(c7, x);

	ASSERT_TRUE(x.grid[0][0]._d == West);
	ASSERT_TRUE(x.grid[0][1]._d == South);
	ASSERT_TRUE(x.grid[1][0]._d == East);
	ASSERT_TRUE(x.grid[1][1]._d == North);
	ASSERT_TRUE(x.grid[2][0]._d == West);
	ASSERT_TRUE(x.grid[2][1]._d == South);
	ASSERT_TRUE(x.grid[2][2]._d == North);
}


TEST(Darwin, turn_Right1){
	Darwin x(2,2);
	Species f1 = Species(Food);
	Creature c1 = Creature(f1, North, 0, 0);

	x.addCreature(c1);

	turnRight(c1, x);

	ASSERT_TRUE(x.grid[0][0]._d == East);
}

TEST(Darwin, turn_Right2){
	Darwin x(2,2);
	Species f1 = Species(Food);
	Species f2 = Species(Food);
	Species f3 = Species(Food);
	Species f4 = Species(Food);

	Creature c1 = Creature(f1, North, 0, 0);
	Creature c2 = Creature(f2, West, 0, 1);
	Creature c3 = Creature(f3, South, 1, 0);
	Creature c4 = Creature(f4, East, 1, 1);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);

	turnRight(c1, x);
	turnRight(c2, x);
	turnRight(c3, x);
	turnRight(c4, x);

	ASSERT_TRUE(x.grid[0][0]._d == East);
	ASSERT_TRUE(x.grid[0][1]._d == North);
	ASSERT_TRUE(x.grid[1][0]._d == West);
	ASSERT_TRUE(x.grid[1][1]._d == South);
}

TEST(Darwin, turn_Right3){
	Darwin x(3,3);

	Species f1 = Species(Food);
	Species f2 = Species(Food);
	Species f3 = Species(Food);
	Species h1 = Species(Hopper);
	Species h2 = Species(Hopper);
	Species r1 = Species(Rover);
	Species t1 = Species(Trap);

	Creature c1 = Creature(f1, North, 0, 0);
	Creature c2 = Creature(f2, West, 0, 1);
	Creature c3 = Creature(f3, South, 1, 0);
	Creature c4 = Creature(h1, East, 1, 1);
	Creature c5 = Creature(h2, North, 2, 0);
	Creature c6 = Creature(r1, West, 2, 1);
	Creature c7 = Creature(t1, East, 2, 2);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	x.addCreature(c4);
	x.addCreature(c5);
	x.addCreature(c6);
	x.addCreature(c7);

	turnRight(c1, x);
	turnRight(c2, x);
	turnRight(c3, x);
	turnRight(c4, x);
	turnRight(c5, x);
	turnRight(c6, x);
	turnRight(c7, x);

	ASSERT_TRUE(x.grid[0][0]._d == East);
	ASSERT_TRUE(x.grid[0][1]._d == North);
	ASSERT_TRUE(x.grid[1][0]._d == West);
	ASSERT_TRUE(x.grid[1][1]._d == South);
	ASSERT_TRUE(x.grid[2][0]._d == East);
	ASSERT_TRUE(x.grid[2][1]._d == North);
	ASSERT_TRUE(x.grid[2][2]._d == South);
}

TEST(Darwin, turn_left_and_right1) {
	Darwin x(1, 1);

	Species food = Species(Food);

	Creature f1 = Creature(food, South, 0, 0);
	x.addCreature(f1);

	turnLeft(x.grid[0][0], x);
	ASSERT_TRUE(x.grid[0][0]._d == East);

	turnRight(x.grid[0][0], x);
	ASSERT_TRUE(x.grid[0][0]._d == South);
}

TEST(Darwin, turn_left_and_right2) {
	Darwin x(1, 1);

	Species food = Species(Food);

	Creature f1 = Creature(food, South, 0, 0);
	x.addCreature(f1);

	turnLeft(x.grid[0][0], x);
	turnRight(x.grid[0][0], x);
	turnRight(x.grid[0][0], x);
	turnRight(x.grid[0][0], x);
	turnLeft(x.grid[0][0], x);
	turnRight(x.grid[0][0], x);
	ASSERT_TRUE(x.grid[0][0]._d == North);
}

TEST(Darwin, do_hop1){
	Darwin x(1, 2);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, East, 0, 0);
	x.addCreature(c1);

	doHop(c1, x);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);
}

TEST(Darwin, do_hop2){
	Darwin x(1, 3);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, East, 0, 0);

	x.addCreature(c1);
	doHop(c1, x);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);

	Creature c2 = x.grid[0][1];
	doHop(c2, x);
	ASSERT_TRUE(x.grid[0][2]._s._type == Hopper);
}

TEST(Darwin, do_hop_wall){
	Darwin x(1, 2);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, East, 0, 0);

	x.addCreature(c1);
	doHop(c1, x);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);

	Creature c2 = x.grid[0][1];
	doHop(c2, x);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);
}

TEST(Darwin, infect_enemy_rover){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Species r1 = Species(Rover);
	Creature c1 = Creature(h1, East, 0, 0);
	Creature c2 = Creature(r1, North, 1, 0);

	x.addCreature(c1);
	x.addCreature(c2);
	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);

	infectEnemy(c2, x);

	ASSERT_TRUE(x.grid[0][0]._s._type == Rover);
}

TEST(Darwin, infect_enemy_trap){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Species t1 = Species(Trap);
	Creature c1 = Creature(h1, East, 0, 0);
	Creature c2 = Creature(t1, North, 1, 0);

	x.addCreature(c1);
	x.addCreature(c2);
	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Trap);

	infectEnemy(c2, x);

	ASSERT_TRUE(x.grid[0][0]._s._type == Trap);
}

TEST(Darwin, infect_enemy_different_direction){
	Darwin x(2, 2);
	Species t1 = Species(Trap);
	Species h1 = Species(Hopper);
	Species h2 = Species(Hopper);
	Creature c1 = Creature(t1, South, 0, 0);
	Creature c2 = Creature(h1, East, 1, 0);
	Creature c3 = Creature(h2, North, 1, 1);

	x.addCreature(c1);
	x.addCreature(c2);
	x.addCreature(c3);
	ASSERT_TRUE(x.grid[0][0]._s._type == Trap);
	ASSERT_TRUE(x.grid[1][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][1]._s._type == Hopper);

	infectEnemy(c1, x);
	ASSERT_TRUE(x.grid[1][0]._s._type == Trap);

	Creature c4 = x.grid[1][0];

	infectEnemy(c4, x);
	ASSERT_TRUE(x.grid[1][1]._s._type == Trap);
}

TEST(Darwin, if_empty1){
	Darwin x(3, 3);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, North, 2, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[2][0]._s._type == Hopper);
	const bool b = ifEmpty(c1, x);
	ASSERT_TRUE(b);
}

TEST(Darwin, if_empty_after_hop){
	Darwin x(3, 3);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, North, 2, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[2][0]._s._type == Hopper);

	doHop(c1, x);
	ASSERT_TRUE(x.grid[1][0]._s._type == Hopper);

	Creature c2 = x.grid[1][0];
	const bool b = ifEmpty(c2, x);

	ASSERT_TRUE(b);
}

TEST(Darwin, if_empty_false){
	Darwin x(3, 3);
	Species h1 = Species(Hopper);
	Species h2 = Species(Hopper);
	Creature c1 = Creature(h1, North, 2, 0);
	Creature c2 = Creature(h2, East, 1, 0);

	x.addCreature(c1);
	x.addCreature(c2);

	ASSERT_TRUE(x.grid[2][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Hopper);

	const bool b = ifEmpty(c1, x);

	ASSERT_FALSE(b);
}


TEST(Darwin, if_wall1){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, North, 0, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);

	const bool b = ifWall(c1, x);

	ASSERT_TRUE(b);
}

TEST(Darwin, if_wall_after_hop){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, North, 1, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[1][0]._s._type == Hopper);

	doHop(c1, x);

	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	Creature c2 = x.grid[0][0];
	
	const bool b = ifWall(c2, x);

	ASSERT_TRUE(b);
}

TEST(Darwin, if_wall_after_hop_false){
	Darwin x(3, 3);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, North, 2, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[2][0]._s._type == Hopper);

	doHop(c1, x);

	ASSERT_TRUE(x.grid[1][0]._s._type == Hopper);
	Creature c2 = x.grid[1][0];
	
	const bool b = ifWall(c2, x);

	ASSERT_FALSE(b);
}

TEST(Darwin, if_wall_West){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Creature c1 = Creature(h1, West, 0, 0);

	x.addCreature(c1);
	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);

	const bool b = ifWall(c1, x);

	ASSERT_TRUE(b);
}

TEST(Darwin, if_random_turn) {
	Darwin x(2, 2);
	Species food = Species(Food);
	Creature f1 = Creature(food, North, 0, 0);

	x.addCreature(f1);
	const bool b = ifRandom();
	if (b)
		turnLeft(x.grid[0][0], x);
	else
		turnRight(x.grid[0][0], x);

	ASSERT_TRUE((b && x.grid[0][0]._d == West) || (!b && x.grid[0][0]._d == East));
}

TEST(Darwin, if_enemy1){
	Darwin x(2, 2);
	Species h1 = Species(Hopper);
	Species r1 = Species(Rover);
	Creature c1 = Creature(h1, East, 0, 0);
	Creature c2 = Creature(r1, North, 1, 0);

	x.addCreature(c1);
	x.addCreature(c2);

	ASSERT_TRUE(x.grid[0][0]._s._type == Hopper);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);

	const bool b = ifEnemy(c2, x);
	ASSERT_TRUE(b);
}

TEST(Darwin, if_enemy_false){
	Darwin x(2, 2);
	Species r1 = Species(Rover);
	Species r2 = Species(Rover);
	Creature c1 = Creature(r1, East, 0, 0);
	Creature c2 = Creature(r2, North, 1, 0);

	x.addCreature(c1);
	x.addCreature(c2);

	ASSERT_TRUE(x.grid[0][0]._s._type == Rover);
	ASSERT_TRUE(x.grid[1][0]._s._type == Rover);

	const bool b = ifEnemy(c2, x);
	ASSERT_FALSE(b);
}

TEST(Darwin, if_enemy_true_after_hop){
	Darwin x(4, 4);
	Species h1 = Species(Hopper);
	Species r1 = Species(Rover);
	Creature c1 = Creature(h1, East, 0, 1);
	Creature c2 = Creature(r1, North, 2, 1);

	x.addCreature(c1);
	x.addCreature(c2);
	ASSERT_TRUE(x.grid[0][1]._s._type == Hopper);
	ASSERT_TRUE(x.grid[2][1]._s._type == Rover);
	ASSERT_TRUE(x.grid[1][1]._s._type == Empty);

	const bool b1 = ifEnemy(c2, x);
	ASSERT_FALSE(b1);

	doHop(c2, x);
	ASSERT_TRUE(x.grid[1][1]._s._type == Rover);

	c2 = x.grid[1][1];
	const bool b2 = ifEnemy(c2, x);
	ASSERT_TRUE(b2);
}

TEST(Darwin, randomDirection_test) {
	Darwin x(1, 1);
	Species food = Species(Food);
	Direction d = randomDirection();
	Creature f1 = Creature(food, d, 0, 0);

	x.addCreature(f1);

	ASSERT_TRUE((d == West && x.grid[0][0]._d == West) || (d == North && x.grid[0][0]._d == North)
			  || (d == East && x.grid[0][0]._d == East) || (d == South && x.grid[0][0]._d == South));
}

TEST(Darwin, randomPosition_test) {
	Darwin x(72, 72);
	Species food = Species(Food);
	std::vector<int> position;
	randomPosition(x, position);
	Creature f1 = Creature(food, East, position[0], position[1]);

	x.addCreature(f1);

	ASSERT_TRUE(f1._row == position[0] && f1._col == position[1]);
}