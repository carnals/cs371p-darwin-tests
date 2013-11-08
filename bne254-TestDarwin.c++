// Compile with g++ -pedantic -std=c++0x -Wall TestDarwin.c++ -o TestDarwin

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"

TEST(Darwin, generate0) {
	Environment zoo(2, 2, 4);
	zoo.generate("FOOD", "N", 0, 0);
	assert(zoo.habitat[0][0].getRace().compare("f") == 0);
}

TEST(Darwin, generate1) {
	Environment zoo(7, 6, 8192);
	zoo.generate("ROVER", "E", 3, 2);
	assert(zoo.habitat[3][2].getRace().compare("r") == 0);
}

TEST(Darwin, generate3) {
	Environment zoo(72, 72, 16384);
	zoo.generate("HOPPER", "S", 8, 8);
	assert(zoo.habitat[8][8].getRace().compare("h") == 0);
}

TEST(Darwin, generate4) {
	Environment zoo(128, 128, 10);
	zoo.generate("TRAP", "W", 64, 64);
	assert(zoo.habitat[64][64].getRace().compare("t") == 0);
}

TEST(Darwin, if_wall0) {
	Environment zoo(4, 4, 1);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.generate("TRAP", "W", 1, 0);
	assert(zoo.if_wall(&zoo.habitat[0][0], -1));
	assert(zoo.if_wall(&zoo.habitat[1][0], -1));
}

TEST(Darwin, if_wall1) {
	Environment zoo(4, 4, 1);
	zoo.generate("FOOD", "S", 3, 3);
	zoo.generate("TRAP", "E", 2, 3);
	assert(zoo.if_wall(&zoo.habitat[3][3], -1));
	assert(zoo.if_wall(&zoo.habitat[2][3], -1));
}

TEST(Darwin, if_wall3) {
	Environment zoo(4, 4, 1);
	zoo.generate("HOPPER", "E", 1, 1);
	zoo.generate("ROVER", "W", 2, 2);
	assert(!zoo.if_wall(&zoo.habitat[1][1], -1));
	assert(!zoo.if_wall(&zoo.habitat[2][2], -1));
}

TEST(Darwin, if_empty0)
{
	Environment zoo(72, 3, 4);
	zoo.generate("FOOD", "S", 0, 0);
	assert(zoo.if_empty(&zoo.habitat[0][0], -1));
}

TEST(Darwin, if_empty1) {
	Environment zoo(16, 16, 32);
	zoo.generate("ROVER", "E", 2, 2);
	zoo.generate("ROVER", "E", 2, 3);
	assert(!zoo.if_empty(&zoo.habitat[2][2], -1));
	assert( zoo.if_empty(&zoo.habitat[2][3], -1));
}

TEST(Darwin, if_empty3) {
	Environment zoo(1, 1, 1);
	zoo.generate("HOPPER", "N", 0, 0);
	assert(!zoo.if_empty(&zoo.habitat[0][0], -1));
}

TEST(Darwin, if_enemy0) {
	Environment zoo(9, 9, 3);
	zoo.generate("ROVER", "N", 8, 8);
	assert(!zoo.if_enemy(&zoo.habitat[8][8], -1));
}

TEST(Darwin, if_enemy1) {
	Environment zoo(12, 12, 9001);
	zoo.generate("ROVER", "W", 4, 6);
	zoo.generate("ROVER", "W", 4, 5);
	assert(!zoo.if_enemy(&zoo.habitat[4][6], -1));
	assert(!zoo.if_enemy(&zoo.habitat[4][5], -1));
}

TEST(Darwin, if_enemy3) {
	Environment zoo(16, 4, 64);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.generate("TRAP", "N", 1, 0);
	assert(!zoo.if_enemy(&zoo.habitat[0][0], -1));
	assert( zoo.if_enemy(&zoo.habitat[1][0], -1));
}

TEST(Darwin, incrementPC0){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.habitat[0][0].incrementPC();
	zoo.habitat[0][0].incrementPC();
	assert(zoo.habitat[0][0].getpc() == 2);
}

TEST(Darwin, incrementPC1){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 1, 1);
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	assert(zoo.habitat[1][1].getpc() == 4);
}

TEST(Darwin, incrementPC2){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 2, 2);
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	zoo.habitat[2][2].incrementPC();
	assert(zoo.habitat[2][2].getpc() == 8);
}

TEST(Darwin, incrementPC3){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 3, 3);
	for(int i = 0; i < 16; i++)
		zoo.habitat[3][3].incrementPC();

	assert(zoo.habitat[3][3].getpc() == 16);
}

TEST(Darwin, resetPC0){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.habitat[0][0].incrementPC();
	zoo.habitat[0][0].incrementPC();
	zoo.habitat[0][0].resetPC();
	assert(zoo.habitat[0][0].getpc() == 0);
}

TEST(Darwin, resetPC1){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 1, 1);
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].incrementPC();
	zoo.habitat[1][1].resetPC();
	assert(zoo.habitat[1][1].getpc() == 0);
}

TEST(Darwin, resetPC2){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 2, 2);
	for(int i = 0; i < 8; i++)
		zoo.habitat[2][2].incrementPC();

	zoo.habitat[2][2].resetPC();
	assert(zoo.habitat[2][2].getpc() == 0);
}


TEST(Darwin, resetPC3){
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 3, 3);
	for(int i = 0; i < 16; i++)
		zoo.habitat[3][3].incrementPC();

	zoo.habitat[3][3].resetPC();
	assert(zoo.habitat[3][3].getpc() == 0);
}

TEST(Darwin, die0) {
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.habitat[0][0].die();
	assert(zoo.habitat[0][0].getRace().compare("`") == 0);
}


TEST(Darwin, die1) {
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.habitat[0][0].die();
	assert(zoo.habitat[0][0].getRace().compare("`") == 0);
}

TEST(Darwin, die2) {
	Environment zoo(4, 4, 4);
	zoo.generate("TRAP", "N", 1, 1);
	zoo.habitat[1][1].die();
	assert(zoo.habitat[1][1].getRace().compare("`") == 0);
}

TEST(Darwin, die3) {
	Environment zoo(4, 4, 4);
	zoo.generate("ROVER", "N", 3, 3);
	zoo.habitat[3][3].die();
	assert(zoo.habitat[3][3].getRace().compare("`") == 0);
}

TEST(Darwin, left0) {
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.generate("FOOD", "E", 1, 1);
	zoo.generate("FOOD", "S", 2, 2);
	zoo.left(&zoo.habitat[0][0]);
	zoo.left(&zoo.habitat[1][1]);
	zoo.left(&zoo.habitat[2][2]);
	assert(zoo.habitat[0][0].getDirection().compare("W") == 0);
	assert(zoo.habitat[1][1].getDirection().compare("N") == 0);
	assert(zoo.habitat[2][2].getDirection().compare("E") == 0);
}

TEST(Darwin, left1) {
	Environment zoo(4, 4, 4);
	for(int i = 0; i < 4; i++) zoo.generate("TRAP", "N", 0, i);
	for(int i = 0; i < 4; i++) zoo.left(&zoo.habitat[0][i]);

	assert(zoo.habitat[0][0].getDirection().compare("W") == 0);
	assert(zoo.habitat[0][1].getDirection().compare("W") == 0);
	assert(zoo.habitat[0][2].getDirection().compare("W") == 0);
	assert(zoo.habitat[0][3].getDirection().compare("W") == 0);
}

TEST(Darwin, left2) {
	Environment zoo(1, 1, 4);
	zoo.generate("TRAP", "S", 0, 0);

	zoo.left(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("E") == 0);
	zoo.left(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("N") == 0);
	zoo.left(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("W") == 0);
}

TEST(Darwin, right0) {
	Environment zoo(4, 4, 4);
	zoo.generate("FOOD", "N", 0, 0);
	zoo.generate("FOOD", "E", 1, 1);
	zoo.generate("FOOD", "S", 2, 2);
	zoo.right(&zoo.habitat[0][0]);
	zoo.right(&zoo.habitat[1][1]);
	zoo.right(&zoo.habitat[2][2]);
	assert(zoo.habitat[0][0].getDirection().compare("E") == 0);
	assert(zoo.habitat[1][1].getDirection().compare("S") == 0);
	assert(zoo.habitat[2][2].getDirection().compare("W") == 0);
}

TEST(Darwin, right1) {
	Environment zoo(4, 4, 4);
	for(int i = 0; i < 4; i++) zoo.generate("TRAP", "N", 0, i);
	for(int i = 0; i < 4; i++) zoo.right(&zoo.habitat[0][i]);

	assert(zoo.habitat[0][0].getDirection().compare("E") == 0);
	assert(zoo.habitat[0][1].getDirection().compare("E") == 0);
	assert(zoo.habitat[0][2].getDirection().compare("E") == 0);
	assert(zoo.habitat[0][3].getDirection().compare("E") == 0);
}

TEST(Darwin, right2) {
	Environment zoo(1, 1, 4);
	zoo.generate("TRAP", "S", 0, 0);

	zoo.right(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("W") == 0);
	zoo.right(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("N") == 0);
	zoo.right(&zoo.habitat[0][0]);
	assert(zoo.habitat[0][0].getDirection().compare("E") == 0);
}

TEST(Darwin, hop0) {
	Environment zoo(3, 3, 3);
	zoo.generate("HOPPER", "E", 0, 0);
	zoo.hop(&zoo.habitat[0][0]);
	zoo.hop(&zoo.habitat[0][1]);
	assert(zoo.habitat[0][2].getRace().compare("h") == 0);
}

TEST(Darwin, hop1) {
	Environment zoo(3, 3, 3);
	zoo.generate("HOPPER", "E", 0, 0);
	zoo.hop(&zoo.habitat[0][0]);
	zoo.hop(&zoo.habitat[0][1]);
	zoo.hop(&zoo.habitat[0][2]);
	zoo.hop(&zoo.habitat[0][2]);
	assert(zoo.habitat[0][2].getRace().compare("h") == 0);
}

TEST(Darwin, hop2) {
	Environment zoo(4, 4, 3);
	zoo.generate("HOPPER", "E", 0, 0);
	zoo.generate("HOPPER", "W", 0, 3);
	zoo.hop(&zoo.habitat[0][0]);
	zoo.hop(&zoo.habitat[0][3]);
	zoo.hop(&zoo.habitat[0][1]);
	zoo.hop(&zoo.habitat[0][2]);
	zoo.hop(&zoo.habitat[0][1]);
	zoo.hop(&zoo.habitat[0][2]);
	assert(zoo.habitat[0][2].getRace().compare("h") == 0);
	assert(zoo.habitat[0][1].getRace().compare("h") == 0);
}

TEST(Darwin, infect0) {
	Environment zoo(4, 4, 4);
	zoo.generate("ROVER", "E", 0, 0);
	zoo.generate("FOOD", "S", 0, 1);
	zoo.infect(&zoo.habitat[0][0], &zoo.habitat[0][1]);
	assert(zoo.habitat[0][1].getRace().compare("r") == 0);
}

TEST(Darwin, infect1) {
	Environment zoo(4, 4, 4);
	zoo.generate("HOPPER", "E", 0, 0);
	zoo.generate("FOOD", "W", 0, 1);
	zoo.infect(&zoo.habitat[0][0], &zoo.habitat[0][1]);
	zoo.infect(&zoo.habitat[0][1], &zoo.habitat[0][0]);
	assert(zoo.habitat[0][1].getRace().compare("h") == 0);
}

TEST(Darwin, run0) {
	Environment zoo(4, 4, 5);
	for(int i = 0; i < 4; i++) zoo.generate("HOPPER", "S", 0, i);

	zoo.run(-1);
	assert(zoo.habitat[3][0].getRace().compare("h") == 0);
	assert(zoo.habitat[3][1].getRace().compare("h") == 0);
	assert(zoo.habitat[3][2].getRace().compare("h") == 0);
	assert(zoo.habitat[3][3].getRace().compare("h") == 0);
}

TEST(Darwin, run1) {
	Environment zoo(4, 4, 4);
	for(int i = 0; i < 4; i++) zoo.generate("TRAP", "S", 0, i);

	zoo.run(-1);
	assert(zoo.habitat[0][0].getRace().compare("t") == 0);
	assert(zoo.habitat[0][1].getRace().compare("t") == 0);
	assert(zoo.habitat[0][2].getRace().compare("t") == 0);
	assert(zoo.habitat[0][3].getRace().compare("t") == 0);
}

// looking at Downing's run()
/*
TEST(Darwin, runD0) {
	Environment zoo(8, 8, 5);
	zoo.generate("FOOD", "E", 0, 0);
	zoo.generate("HOPPER", "N", 3, 3);
	zoo.generate("HOPPER", "E", 3, 4);
	zoo.generate("HOPPER", "S", 4, 4);
	zoo.generate("HOPPER", "W", 4, 3);
	zoo.generate("FOOD", "N", 7, 7);
	zoo.run(-1);
}


TEST(Darwin, runD1) {
	Environment zoo(7, 9, 5);
	zoo.generate("TRAP", "S", 0, 0);
	zoo.generate("HOPPER", "E", 3, 2);
	zoo.generate("ROVER", "N", 5, 4);
	zoo.generate("TRAP", "W", 6, 8);
	zoo.run(-1);
}
*/
