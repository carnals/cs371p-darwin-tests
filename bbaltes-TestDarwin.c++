/*
To test the program:

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

#define private public
#define protected public
#include "Darwin.h"

using namespace std;

// --------
// Test Darwin
// --------

// --------
// Test CREATURES
// --------
TEST(Darwin, Creature_hop1) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 0 );
	ASSERT_TRUE( creature.y == 1 );
}
TEST(Darwin, Creature_hop2) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 1,3,south,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 1 );
	ASSERT_TRUE( creature.y == 4 );
}
TEST(Darwin, Creature_hop3) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 2,2,south,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 2 );
	ASSERT_TRUE( creature.y == 3 );
}
TEST(Darwin, Creature_hopcorner) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,north,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 0 );
	ASSERT_TRUE( creature.y == 0 );
}
TEST(Darwin, Creature_hopedge) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,west,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 0 );
	ASSERT_TRUE( creature.y == 2 );
}
TEST(Darwin, Creature_edge) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,west,&board);
	creature.hopInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.x == 0 );
	ASSERT_TRUE( creature.y == 2 );
}
TEST(Darwin, Creature_right1) {
 //    Hopper h;
	// Creature c1 (h, 0);
	// c1.set_direction(0);
	// ASSERT_TRUE(c1.dir_string == "north");
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,west,&board);
	creature.rightInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == north);
}
TEST(Darwin, Creature_right2) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,north,&board);
	creature.rightInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == east);
}
TEST(Darwin, Creature_right3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,east,&board);
	creature.rightInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == south);
}
TEST(Darwin, Creature_right4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,south,&board);
	creature.rightInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == west);
}
TEST(Darwin, Creature_left1) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,south,&board);
	creature.leftInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == east);
}
TEST(Darwin, Creature_left2) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,west,&board);
	creature.leftInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == south);
}
TEST(Darwin, Creature_left3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,north,&board);
	creature.leftInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == west);
}
TEST(Darwin, Creature_left4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,east,&board);
	creature.leftInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE( creature.direction == north);
}
TEST(Darwin, Creature_infect1) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,east,&board);
	creature.infectInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.x == 0);
}
TEST(Darwin, Creature_infect2) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 2,2,east,&board);
	creature.infectInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.x == 2);
}
TEST(Darwin, Creature_infect3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,2,east,&board);
	creature.infectInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.y == 2);
}
TEST(Darwin, Creature_infect4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	creature.infectInstruction();
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.y == 3);
}

TEST(Darwin, Creature_ifempty1) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	creature.if_emptyInstruction(1);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 1);
}
TEST(Darwin, Creature_ifempty2) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	creature.if_emptyInstruction(2);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 2);
}
TEST(Darwin, Creature_ifempty3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 4,3,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, Creature_ifempty4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, Creature_ifempty5) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	board.add(&creature);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, wallInfrontcorner1){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,north,&board);
	board.add(&creature,0,0,north);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(exists);
}
TEST(Darwin, wallInfrontcorner2){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,west,&board);
	board.add(&creature,0,0,west);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(exists);
}
TEST(Darwin, wallInfrontcorner3){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 9,9,east,&board);
	board.add(&creature,9,9,east);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(exists);
}
TEST(Darwin, wallInfrontcorner4){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 9,9,south,&board);
	board.add(&creature,9,9,south);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(exists);
}
TEST(Darwin, wallInfrontcorneredges){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,9,south,&board);
	board.add(&creature,0,9,south);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(exists);
}

TEST(Darwin, wallInfrontnowall1edge){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,9,north,&board);
	board.add(&creature,0,9,north);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(!exists);
}

TEST(Darwin, wallInfrontnowall2){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 5,5,south,&board);
	board.add(&creature,5,5,south);
	bool exists = creature.existsWallInFront();

	ASSERT_TRUE(!exists);
}

TEST(Darwin, existsEnemyInFront){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 5,5,south,&board);
	Creature creature2('b', 5,6,south,&board);
	board.add(&creature,5,5,south);
	board.add(&creature2,5,6,south);
	bool exists = creature.existsEnemyInFront();

	ASSERT_TRUE(exists);
}

TEST(Darwin, existsEnemyInFront2){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 5,5,south,&board);
	Creature creature2('b', 5,6,south,&board);
	board.add(&creature,5,5,south);
	board.add(&creature2,5,6,south);
	bool exists = creature2.existsEnemyInFront();

	ASSERT_TRUE(exists);
}

TEST(Darwin, existsEnemyInFront3){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,1,south,&board);
	board.add(&creature,0,0,south);
	board.add(&creature2,1,1,south);
	bool exists = creature2.existsEnemyInFront();

	ASSERT_TRUE(exists);
}

TEST(Darwin, existsCreatureInFront){
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	board.add(&creature);
	bool exists = creature.existsCreatureInFront();

	ASSERT_TRUE(!exists);
}
TEST(Darwin, existsCreatureInFront2) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	bool exists = creature.existsCreatureInFront();
	ASSERT_TRUE(!exists);
}
TEST(Darwin, existsCreatureInFront3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 0,1,east,&board);
	Creature creature3('c', 1,0,east,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 0,1,south,&board);
	board.add(&creature3, 1,0,south,&board);
	bool exists = creature.existsCreatureInFront();
	ASSERT_TRUE(exists);
}
TEST(Darwin, existsCreatureInFront4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 0,1,east,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 0,1,south,&board);
	bool exists = creature.existsCreatureInFront();
	ASSERT_TRUE(exists);
}
TEST(Darwin, existsCreatureInFrontUP) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 0,1,north,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 0,1,south,&board);
	bool exists = creature2.existsCreatureInFront();
	ASSERT_TRUE(exists);
}
TEST(Darwin, existsCreatureInFrontWest) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	bool exists = creature2.existsCreatureInFront();
	ASSERT_TRUE(exists);
}

TEST(Darwin, BoardAdd) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	bool exists = creature2.existsCreatureInFront();
	ASSERT_TRUE(exists);
}

TEST(Darwin, boardAdd2) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	bool exists = creature2.existsCreatureInFront();
	ASSERT_TRUE(exists);
}
TEST(Darwin, boardAdd3) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	Creature* creature3 = board.get(0,0);
	ASSERT_TRUE((*creature3).x==0);
}
TEST(Darwin, boardAdd4) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	Creature* creature3 = board.get(0,0);
	ASSERT_TRUE((*creature3).y==0);
}
TEST(Darwin, boardAdd5) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	Creature* creature3 = board.get(0,0);
	ASSERT_TRUE((*creature3).toChar()=='a');
}
TEST(Darwin, boardAddontop) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 0,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 0,0,west,&board);
	Creature* creature3 = board.get(0,0);
	ASSERT_TRUE((*creature3).toChar()=='b');
}
TEST(Darwin, boardgetIndex1) {
	Creature empty;
	int x = 10;
	int y = 5;
	int width = 11;
	Board board(10,width,&empty);
	int expected = width*y+x;
	int actual = board.getIndex(x,y);
	ASSERT_TRUE(expected == actual);
}
TEST(Darwin, boardgetIndex2) {
	Creature empty;
	int x = 10;
	int y = 5;
	int width = 11;
	Board board(10,width,&empty);
	int expected = width*y+x;
	int actual = board.getIndex(x,y);
	ASSERT_TRUE(expected == actual);
}
TEST(Darwin, boardgetIndex3) {
	Creature empty;
	int x = 11;
	int y = 12;
	int width = 13;
	Board board(10,width,&empty);
	int expected = width*y+x;
	int actual = board.getIndex(x,y);
	ASSERT_TRUE(expected == actual);
}
TEST(Darwin, boardgetIndex4) {
	Creature empty;
	int x = 0;
	int y = 1;
	int width = 23;
	Board board(10,width,&empty);
	int expected = width*y+x;
	int actual = board.getIndex(x,y);
	ASSERT_TRUE(expected == actual);
}
TEST(Darwin, boardgetIndex5) {
	Creature empty;
	int x = 99;
	int y = 99;
	int width = 0;
	Board board(10,width,&empty);
	int expected = width*y+x;
	int actual = board.getIndex(x,y);
	ASSERT_TRUE(expected == actual);
}
TEST(Darwin, coordIsEmpty) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	ASSERT_TRUE( !board.coordIsEmpty(0,0) );
}
TEST(Darwin, coordIsEmpty2) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	ASSERT_TRUE( !board.coordIsEmpty(1,0) );
}
TEST(Darwin, coordIsEmpty3) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	ASSERT_TRUE( board.coordIsEmpty(2,2) );
}
TEST(Darwin, coordIsEmpty4) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	ASSERT_TRUE( board.coordIsEmpty(3,3) );
}
TEST(Darwin, coordIsEmpty5) {
	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 0,0,south,&board);
	Creature creature2('b', 1,0,west,&board);
	board.add(&creature, 0,0,south,&board);
	board.add(&creature2, 1,0,west,&board);
	ASSERT_TRUE( board.coordIsEmpty(4,3) );
}

/*
TEST(Darwin, existsCreatureInFront3) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, existsCreatureInFront4) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, existsCreatureInFront5) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, existsCreatureInFront6) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);
}
TEST(Darwin, existsCreatureInFront7) {

	Creature empty;
	Board board(10,10,&empty);
	Creature creature('a', 3,3,east,&board);
	Creature creature2('b', 3,4,east,&board);
	board.add(&creature);
	board.add(&creature2);
	creature.if_emptyInstruction(3);
	// creature.x = 0;
	// creature.y = 1;
	ASSERT_TRUE(creature.programCounter == 3);

*/