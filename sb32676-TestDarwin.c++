/*
name: Seung Youp Baek
eid: sb32676
csid: sb32676
email: bsy6766@gmail.com
course: CS371p 10am

name: Kyeong Su Park
eid: ksp499
csid: ksp499
email: ksp499@gmail.com
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// -----------
// Species
// -----------
TEST(Darwin, specie1){
    Species hopSpecie('h');
    ASSERT_TRUE(hopSpecie.id == 'h');
}

TEST(Darwin, specie2){
    Species nullSpecie;
    ASSERT_TRUE(nullSpecie.id == ' ');
}

TEST(Darwin, specie3){
    Species hopSpecie('h');
    Species foodSpecie('f');
    Species roverSpecie('r');
    Species trapSpecie('t');
    ASSERT_TRUE(hopSpecie.id == 'h');
    ASSERT_TRUE(foodSpecie.id == 'f');
    ASSERT_TRUE(roverSpecie.id == 'r');
    ASSERT_TRUE(trapSpecie.id == 't');
}

// -----------
// Species::pushInstruction
// -----------
TEST(Darwin, pushInstruction1){
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");

    ASSERT_TRUE(hopSpecie.program[0].compare("hop") == 0);
    ASSERT_TRUE(hopSpecie.program[1].compare("go 0") == 0);
}

TEST(Darwin, pushInstruction2){
    Species insaneSpecie('i');
    for(int i = 0; i<10; i++)
        insaneSpecie.pushInstruction("left");

    for(int i = 0; i<10; i++)
        ASSERT_TRUE(insaneSpecie.program[i].compare("left") == 0);
}

TEST(Darwin, pushWrongInstruction1){
    Species insaneSpecie('i');
    for(int i = 0; i<10; i++)
        insaneSpecie.pushInstruction("1234567890-");

    for(int i = 0; i<10; i++)
        ASSERT_TRUE(insaneSpecie.program[i].compare("1234567890-") == 0);
}

// -----------
// Creature
// -----------
TEST(Darwin, creature1){
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");

    Creature hopper1(0, &hopSpecie);
    ASSERT_TRUE(hopper1.dir == 0);
}

TEST(Darwin, creature2){
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");

    Creature hopper1(1, &hopSpecie);
    Creature hopper2(2, &hopSpecie);
    ASSERT_TRUE(hopper1.dir == 1);
    ASSERT_TRUE(hopper1.moved == false);
    ASSERT_TRUE(hopper2.dir == 2);
    ASSERT_TRUE(hopper2.moved == false);
}

TEST(Darwin, creature3){
    Creature nothing;
    ASSERT_TRUE(nothing.dir == -1);
    ASSERT_TRUE(nothing.moved == false);
}

// -----------
// Creature::left
// -----------
TEST(Darwin, left1){
    Species hopSpecie('h');
    Creature hopper1(0, &hopSpecie);
    hopper1.left();
    ASSERT_TRUE(hopper1.dir == 3);
}

TEST(Darwin, left2){
    Species hopSpecie('h');
    Creature hopper1(0, &hopSpecie);
    hopper1.left();
    hopper1.left();
    hopper1.left();
    ASSERT_TRUE(hopper1.dir == 1);
}

TEST(Darwin, left3){
    Species hopSpecie('h');
    Creature hopper1(0, &hopSpecie);
    Creature hopper2(3, &hopSpecie);
    hopper1.left();
    hopper2.left();
    hopper1.left();
    ASSERT_TRUE(hopper1.dir == 2);
    ASSERT_TRUE(hopper2.dir == 2);
}

// -----------
// Creature::right
// -----------
TEST(Darwin, right1){
    Species hopSpecie('h');
    Creature hopper1(0, &hopSpecie);
    hopper1.right();
    ASSERT_TRUE(hopper1.dir == 1);
}

TEST(Darwin, right2){
    Species hopSpecie('h');
    Creature hopper1(3, &hopSpecie);
    hopper1.right();
    hopper1.right();
    hopper1.right();
    ASSERT_TRUE(hopper1.dir == 2);
}

TEST(Darwin, right3){
    Species hopSpecie('h');
    Creature hopper1(0, &hopSpecie);
    Creature hopper2(3, &hopSpecie);
    hopper1.right();
    hopper2.right();
    hopper1.right();
    ASSERT_TRUE(hopper1.dir == 2);
    ASSERT_TRUE(hopper2.dir == 0);
}
// -----------
// Grid
// -----------
TEST(Darwin, mapCreation1){
    Grid map(4,4);
    ASSERT_TRUE(map.rowLen == 4);
    ASSERT_TRUE(map.colLen == 4);
}

TEST(Darwin, mapCreation2){
    Grid map(4,2);
    ASSERT_TRUE(map.rowLen == 4);
    ASSERT_TRUE(map.colLen == 2);
}

TEST(Darwin, mapCreation3){
    Grid map(100,100);
    ASSERT_TRUE(map.rowLen == 100);
    ASSERT_TRUE(map.colLen == 100);
}

TEST(Darwin, mapCreation4){
    Grid map;
    ASSERT_TRUE(map.rowLen == -1);
    ASSERT_TRUE(map.colLen == -1);
}

TEST(Darwin, mapCreation5){
    try{
        Grid map(0,0);
    }
    catch(const out_of_range& oor){
        ASSERT_TRUE(strcmp(oor.what(), "row and column must be greater than 0") == 0);
    }
}

TEST(Darwin, bigMapCreation6){
    Grid map(1000,1000);
    ASSERT_TRUE(map.rowLen == 1000);
    ASSERT_TRUE(map.colLen == 1000);
}

TEST(Darwin, negativeRangeMapCreation){
    try{
        Grid map(-1,-25);
    }
    catch(const out_of_range& oor){
        ASSERT_TRUE(strcmp(oor.what(), "row and column must be greater than 0") == 0);
    }

}

// -----------
// Grid::setCreaturePos
// -----------
TEST(Darwin, setCreaturePos1){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    ASSERT_TRUE(map.mapArr[0].dir != -1);
}

TEST(Darwin, setCreaturePos2){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    Creature hopper2(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.setCreaturePos(hopper2, 0, 0);
    }
    catch (const invalid_argument& ie) {
        ASSERT_TRUE(strcmp(ie.what(), "Creature already spawned at this position") == 0);
    }
}

TEST(Darwin, setCreaturePos3){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    try{
        map.setCreaturePos(hopper1, 4, 4);
    }
    catch (const out_of_range& oor) {
        ASSERT_TRUE(strcmp(oor.what(), "This position is out of range") == 0);
    }
}

// -----------
// Grid::hop
// -----------
TEST(Darwin, hopSouth){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(3, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[3].dir != -1);
}

TEST(Darwin, hopWest){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[0].dir != -1);
}

TEST(Darwin, hopNorth){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(1, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[0].dir != -1);
}

TEST(Darwin, hopEast){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(2, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[1].dir != -1);
}

TEST(Darwin, hop1){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(3, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    map.nextTurn();
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[6].dir != -1);
}

TEST(Darwin, hop2){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(2, &hopSpecie);
    Creature hopper2(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.setCreaturePos(hopper2, 0, 1);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[0].dir != -1);
    ASSERT_TRUE(map.mapArr[1].dir != -1);
}
// -----------
// Grid::infect
// -----------
TEST(Darwin, infect1){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Species foodSpecie('f');
    foodSpecie.pushInstruction("left");
    foodSpecie.pushInstruction("go 0");
    Creature rover1(2, &roverSpecie);
    Creature food1(0, &foodSpecie);
    map.setCreaturePos(rover1, 0, 0);
    map.setCreaturePos(rover1, 1, 0);
    map.nextTurn();
    ASSERT_TRUE((map.mapArr[3].specie)->id == 'r');
}

TEST(Darwin, infect2){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(2, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[3].dir == -1);
}

// -----------
// Grid::if_empty
// -----------
TEST(Darwin, if_empty1){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(3, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(map.if_empty(0));
}

TEST(Darwin, if_empty2){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(0, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(!map.if_empty(0));
}

TEST(Darwin, if_empty3){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Species roverSpecie2('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(2, &roverSpecie);
    Creature rover2(0, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    map.setCreaturePos(rover2, 0, 1);
    ASSERT_TRUE(!map.if_empty(0));
}

// -----------
// Grid::if_wall
// -----------
TEST(Darwin, if_wall1){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(0, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(map.if_wall(0));
}

TEST(Darwin, if_wall2){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(1, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(map.if_wall(0));
}

TEST(Darwin, if_wall3){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(2, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(!map.if_wall(0));
}

TEST(Darwin, if_wall4){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(3, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    ASSERT_TRUE(!map.if_wall(0));
}

// -----------
// Grid::if_enemy
// -----------
TEST(Darwin, if_enemy1){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Species foodSpecie('f');
    foodSpecie.pushInstruction("left");
    foodSpecie.pushInstruction("go 0");
    Creature food1(3, &foodSpecie);
    Creature rover1(1, &roverSpecie);
    map.setCreaturePos(food1, 0, 0);
    map.setCreaturePos(rover1, 1, 0);
    ASSERT_TRUE(map.if_enemy(3));
}

TEST(Darwin, if_enemy2){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover2(0, &roverSpecie);
    Creature rover1(0, &roverSpecie);
    map.setCreaturePos(rover2, 0, 0);
    map.setCreaturePos(rover1, 1, 0);
    ASSERT_TRUE(!map.if_enemy(3));
}

TEST(Darwin, if_enemy3){ 
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(0, &roverSpecie);
    map.setCreaturePos(rover1, 1, 0);
    ASSERT_TRUE(!map.if_enemy(3));
}

// -----------
// Grid::resetTurn
// -----------
TEST(Darwin, reset1){
    Grid map(2,2);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(0, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[0].moved);
    map.resetTurn();
    ASSERT_TRUE(!map.mapArr[0].moved);
}

TEST(Darwin, reset2){
    Grid map(2,2);
    Species roverSpecie('r');
    roverSpecie.pushInstruction("infect");
    roverSpecie.pushInstruction("go 0");
    Creature rover1(0, &roverSpecie);
    Creature rover2(0, &roverSpecie);
    Creature rover3(0, &roverSpecie);
    Creature rover4(0, &roverSpecie);
    map.setCreaturePos(rover1, 0, 0);
    map.setCreaturePos(rover2, 0, 1);
    map.setCreaturePos(rover3, 1, 0);
    map.setCreaturePos(rover4, 1, 1);
    map.nextTurn();
    ASSERT_TRUE(map.mapArr[0].moved);
    ASSERT_TRUE(map.mapArr[1].moved);
    ASSERT_TRUE(map.mapArr[2].moved);
    ASSERT_TRUE(map.mapArr[3].moved);
    map.resetTurn();
    ASSERT_TRUE(!map.mapArr[0].moved);
    ASSERT_TRUE(!map.mapArr[1].moved);
    ASSERT_TRUE(!map.mapArr[2].moved);
    ASSERT_TRUE(!map.mapArr[3].moved);
}

TEST(Darwin, reset3){
    Grid map(2,2);
    map.resetTurn();
    ASSERT_TRUE(!map.mapArr[0].moved);
    ASSERT_TRUE(!map.mapArr[1].moved);
    ASSERT_TRUE(!map.mapArr[2].moved);
    ASSERT_TRUE(!map.mapArr[3].moved);
}
// -----------
// Grid::nextTurn
// -----------
TEST(Darwin, nextTurn1){
    Grid map(3,3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE((map.mapArr[0].specie)->id == 'h');
}

TEST(Darwin, nextTurn2){
    Grid map(3,3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(2, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.nextTurn();
    ASSERT_TRUE((map.mapArr[1].specie)->id == 'h');
}

TEST(Darwin, nextTurn3){
    Grid map(3,3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 0");
    Species foodSpecie('f');
    foodSpecie.pushInstruction("left");
    foodSpecie.pushInstruction("go 0");
    Creature hopper1(2, &hopSpecie);
    Creature food1(0, &foodSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    map.setCreaturePos(food1, 0, 1);
    map.nextTurn();
    ASSERT_TRUE((map.mapArr[0].specie)->id == 'h');
    ASSERT_TRUE((map.mapArr[1].specie)->id == 'f');
}

TEST(Darwin, nextTurn4){
    Grid map(2,2);
    Species foodSpecie('f');
    foodSpecie.pushInstruction("left");
    foodSpecie.pushInstruction("go 0");
    Creature food1(0, &foodSpecie);
    Creature food2(0, &foodSpecie);
    Creature food3(0, &foodSpecie);
    Creature food4(0, &foodSpecie);
    map.setCreaturePos(food1, 0, 0);
    map.setCreaturePos(food1, 0, 1);
    map.setCreaturePos(food1, 1, 0);
    map.setCreaturePos(food1, 1, 1);
    map.nextTurn();
    map.nextTurn();
    ASSERT_TRUE((map.mapArr[0].specie)->id == 'f');
    ASSERT_TRUE((map.mapArr[1].specie)->id == 'f');
    ASSERT_TRUE((map.mapArr[2].specie)->id == 'f');
    ASSERT_TRUE((map.mapArr[3].specie)->id == 'f');
}

TEST(Darwin, invalidInstruction1){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop1234");
    hopSpecie.pushInstruction("go 0");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const invalid_argument& ie) {
        ASSERT_TRUE(strcmp(ie.what(), "received wrong instruction") == 0);
    }
}

TEST(Darwin, invalidInstruction2){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("gogogo 0");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const invalid_argument& ie) {
        ASSERT_TRUE(strcmp(ie.what(), "received wrong instruction") == 0);
    }
}

TEST(Darwin, invalidInstruction3){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop 1");
    hopSpecie.pushInstruction("hop 2");
    hopSpecie.pushInstruction("hop 3");
    hopSpecie.pushInstruction("hop 4");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const invalid_argument& ie) {
        ASSERT_TRUE(strcmp(ie.what(), "received wrong instruction") == 0);
    }
}

TEST(Darwin, invalidInstruction4){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("You shall not pass!!! 23");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const invalid_argument& ie) {
        ASSERT_TRUE(strcmp(ie.what(), "received wrong instruction") == 0);
    }
}

TEST(Darwin, programOutOfRange1){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const out_of_range& oor) {
        ASSERT_TRUE(strcmp(oor.what(), "program counter out of range") == 0);
    }
}

TEST(Darwin, programOutOfRange2){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("go 1023");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const out_of_range& oor) {
        ASSERT_TRUE(strcmp(oor.what(), "program counter out of range") == 0);
    }
}

TEST(Darwin, programOutOfRange3){
    Grid map(3,3);
    ASSERT_TRUE(map.rowLen == 3);
    ASSERT_TRUE(map.colLen == 3);
    Species hopSpecie('h');
    hopSpecie.pushInstruction("hop");
    hopSpecie.pushInstruction("if_wall 9");
    Creature hopper1(0, &hopSpecie);
    map.setCreaturePos(hopper1, 0, 0);
    try{
        map.nextTurn();
    }
    catch (const out_of_range& oor) {
        ASSERT_TRUE(strcmp(oor.what(), "program counter out of range") == 0);
    }
}

