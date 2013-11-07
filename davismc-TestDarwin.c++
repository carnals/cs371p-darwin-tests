/******************************************************************************
 * Program:		Project 4: Darwin
 * Student:		Merrill Davis
 * Class: 		CS 371p
 * Fall 2013
 *
 * Purpose: 
 * Simulates Darwin's world.  Darwin's world contains a two-dimensional grid
 * of creatures.  Each creature is of a particular species, and each species
 * runs a program that determines its behavior.   The goal is for a creature
 * to "infect" other creatures, changing them to it's species.
 *
 * This file: unit tests for project Darwin
 *
 *****************************************************************************/

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#define private public

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// ------------
// Class Board
// ------------

TEST(Board, printBoard_empty_board_4by4)
{
	std::ostringstream w;
    Board b(4, 4);
    b.printBoard(w);
    //std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "  0123\n0 ....\n1 ....\n2 ....\n3 ....\n");
}

TEST(Board, getIndex_row1_col2_should_be_index_6_board_4by4)
{
	std::ostringstream w;
    Board b(4, 4);	
    ASSERT_TRUE(b.getIndex(1, 2) == 6);
}

TEST(Board, getIndex_row3_col4_should_be_index_19_board_5by5)
{
	std::ostringstream w;
    Board b(5, 5);	
    ASSERT_TRUE(b.getIndex(3, 4) == 19);
}

TEST(Board, getIndex_row0_col0_should_be_index_0_board_default_size)
{
	std::ostringstream w;
    Board b;	
    ASSERT_TRUE(b.getIndex(0, 0) == 0);
}

TEST(Board, getIndex_row14_col14_should_be_index_224_board_default_size)
{
	std::ostringstream w;
    Board b;	
    ASSERT_TRUE(b.getIndex(14, 14) == 224);
}

TEST(Board, isOccupied_at_row0_col0)
{
    Board b(5, 5);
    ASSERT_TRUE(b._theBoard.at(0) == NULL);
    ASSERT_FALSE(b.isOccupied(0,0));
    Creature c;
    b.place(0, 0, c);
    ASSERT_TRUE(b._theBoard.at(0) == &c);
    ASSERT_TRUE(b.isOccupied(0,0));
}

TEST(Board, isOccupied_at_row2_col3_5by5)
{
    Board b(5, 5);
    ASSERT_TRUE(b._theBoard.at(19) == NULL);
    ASSERT_FALSE(b.isOccupied(3,4));
    Creature c;
    b.place(3, 4, c);
    ASSERT_TRUE(b._theBoard.at(19) == &c);
    ASSERT_TRUE(b.isOccupied(3,4));
}

TEST(Board, isOccupied_at_row4_col4_5by5)
{
    Board b(5, 5);
    ASSERT_TRUE(b._theBoard.at(24) == NULL);
    ASSERT_FALSE(b.isOccupied(4,4));
    Creature c;
    b.place(4, 4, c);
    ASSERT_TRUE(b._theBoard.at(24) == &c);
    ASSERT_TRUE(b.isOccupied(4,4));
}

TEST(Board, place_at_row0_col0)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(0) == NULL);
	Creature c;
	b.place(0, 0, c);
	ASSERT_TRUE(b._theBoard.at(0) == &c);
}

TEST(Board, place_at_row3_col4_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(19) == NULL);
	Creature c;
	b.place(3, 4, c);
	ASSERT_TRUE(b._theBoard.at(19) == &c);
}

TEST(Board, place_at_row4_col4_bottom_right_corner_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(24) == NULL);
	Creature c;
	b.place(4, 4, c);
	ASSERT_TRUE(b._theBoard.at(24) == &c);
}

TEST(Board, get_row0_col0)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(0) == NULL);
	Creature c;
	b.place(0, 0, c);
	ASSERT_TRUE(b._theBoard.at(0) == &c);
	ASSERT_TRUE(&b.get(0,0) == &c);
}

TEST(Board, get_row3_col4_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(19) == NULL);
	Creature c;
	b.place(3, 4, c);
	ASSERT_TRUE(b._theBoard.at(19) == &c);
	ASSERT_TRUE(&b.get(3,4) == &c);
}

TEST(Board, get_row4_col4_bottom_right_corner_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(24) == NULL);
	Creature c;
	b.place(4, 4, c);
	ASSERT_TRUE(b._theBoard.at(24) == &c);
	ASSERT_TRUE(&b.get(4,4) == &c);
}

TEST(Board, remove_row0_col0)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(0) == NULL);
	Creature c;
	b.place(0, 0, c);
	ASSERT_TRUE(b._theBoard.at(0) == &c);
	ASSERT_TRUE(&b.get(0,0) == &c);
	ASSERT_TRUE(b.remove(0,0));
	ASSERT_TRUE(b._theBoard.at(0) == NULL);
}

TEST(Board, remove_row3_col4_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(19) == NULL);
	Creature c;
	b.place(3, 4, c);
	ASSERT_TRUE(b._theBoard.at(19) == &c);
	ASSERT_TRUE(&b.get(3,4) == &c);
	ASSERT_TRUE(b.remove(3,4));
	ASSERT_TRUE(b._theBoard.at(19) == NULL);
}

TEST(Board, remove_row4_col4_bottom_right_corner_5by5)
{
	Board b(5, 5);
	ASSERT_TRUE(b._theBoard.at(24) == NULL);
	Creature c;
	b.place(4, 4, c);
	ASSERT_TRUE(b._theBoard.at(24) == &c);
	ASSERT_TRUE(&b.get(4,4) == &c);
	ASSERT_TRUE(b.remove(4,4));
	ASSERT_TRUE(b._theBoard.at(24) == NULL);
}

TEST(Board, remove_row6_col6_5by5_expect_throw_out_of_range)
{
	try {
		Board b(5, 5);
		b.remove(6,6);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row0_col0_5by5_expect_true)
{
	Board b(5,5);
	ASSERT_TRUE(b.isInBounds(0,0));
}

TEST(Board, isInBounds_row2_col3_5by5_expect_true)
{
	Board b(5,5);
	ASSERT_TRUE(b.isInBounds(2,3));
}

TEST(Board, isInBounds_row4_col4_5by5_expect_true)
{
	Board b(5,5);
	ASSERT_TRUE(b.isInBounds(4,4));
}

TEST(Board, isInBounds_row5_col5_5by5_expect_throw_out_of_range)
{
	try {
		Board b(5,5);
		b.isInBounds(5, 5);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row_neg1_col1_5by5_expect_throw_out_of_range)
{
	try {
		Board b(5,5);
		b.isInBounds(-1, 1);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row1_col_neg1_5by5_expect_throw_out_of_range)
{
	try {
		Board b(5,5);
		b.isInBounds(1,-1);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row_neg1_col_neg1_5by5_expect_throw_out_of_range)
{
	try {
		Board b(5,5);
		b.isInBounds(-1,-1);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row6_col7_7by8_expect_true)
{
	Board b(7,8);
	ASSERT_TRUE(b.isInBounds(6,7));
}

TEST(Board, isInBounds_row7_col7_7by8_expect_throw_out_of_range)
{
	try {
		Board b(7,8);
		b.isInBounds(7,7);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Board, isInBounds_row6_col8_7by8_expect_throw_out_of_range)
{
	try {
		Board b(7,8);
		b.isInBounds(6,8);
	}
	catch (const std::out_of_range&) {
		ASSERT_TRUE(true);
	}
}

TEST(Creature, printSelf)
{
	Species s("test", 't');
	Creature c(s);
	std::ostringstream w;
	c.printSelf(w);
	ASSERT_TRUE(w.str() == "t");
}

TEST(Creature, printSelf_default_expect_d)
{
	Species s;
	Creature c(s);
	std::ostringstream w;
	c.printSelf(w);
	ASSERT_TRUE(w.str() == "d"); // Default value
}

TEST(Creature, hop_north_right_edge_4by4)
{
	std::ostringstream w;
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 2, 3, NORTH, &b);
	b.place(2,3, c);
	c.hop();
	b.printBoard(w);
	//b.printBoard(std::cout);
	std::cout << w.str();
	ASSERT_TRUE(w.str() == "  0123\n0 ....\n1 ...t\n2 ....\n3 ....\n");
}

TEST(Creature, hop_south_left_edge_twice_4by4)
{
	std::ostringstream w;
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 0, SOUTH, &b);
	b.place(1, 0, c);
	c.hop();
	c.hop();
	b.printBoard(w);
	ASSERT_TRUE(w.str() == "  0123\n0 ....\n1 ....\n2 ....\n3 t...\n");
}

TEST(Creature, hop_west_right_edge_twice_4by4)
{
	std::ostringstream w;
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 3, WEST, &b);
	b.place(1, 3, c);
	c.hop();
	c.hop();
	b.printBoard(w);
	ASSERT_TRUE(w.str() == "  0123\n0 ....\n1 .t..\n2 ....\n3 ....\n");
}

TEST(Creature, hop_east_bottom_edge_twice_4by4)
{
	std::ostringstream w;
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 3, 0, EAST, &b);
	b.place(3, 0, c);
	c.hop();
	c.hop();
	b.printBoard(w);
	ASSERT_TRUE(w.str() == "  0123\n0 ....\n1 ....\n2 ....\n3 ..t.\n");
}

TEST(Creature, getFacingRowCol_east)
{
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 2, EAST, &b);
	ASSERT_TRUE(c.getFacingRowCol().first == 1);
	ASSERT_TRUE(c.getFacingRowCol().second == 3);
}

TEST(Creature, getFacingRowCol_west)
{
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 2, WEST, &b);
	ASSERT_TRUE(c.getFacingRowCol().first == 1);
	ASSERT_TRUE(c.getFacingRowCol().second == 1);
}

TEST(Creature, getFacingRowCol_south)
{
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 2, SOUTH, &b);
	ASSERT_TRUE(c.getFacingRowCol().first == 2);
	ASSERT_TRUE(c.getFacingRowCol().second == 2);
}

TEST(Creature, getFacingRowCol_north)
{
	Species t("test", 't');
	Board b(4, 4);
	Creature c(t, 1, 2, NORTH, &b);
	ASSERT_TRUE(c.getFacingRowCol().first == 0);
	ASSERT_TRUE(c.getFacingRowCol().second == 2);
}

TEST(Creature, run_facing_west_turn_left_expect_south)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	Board b;
	Creature c(t, 0, 0, WEST, &b);
	ASSERT_TRUE(c._faces == WEST);
	c.run();
	ASSERT_TRUE(c._faces == SOUTH);
}

TEST(Creature, run_facing_south_turn_left_expect_east)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	ASSERT_TRUE(c._faces == SOUTH);
	c.run();
	ASSERT_TRUE(c._faces == EAST);
}

TEST(Creature, run_facing_east_turn_left_expect_north)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	Board b;
	Creature c(t, 0, 0, EAST, &b);
	ASSERT_TRUE(c._faces == EAST);
	c.run();
	ASSERT_TRUE(c._faces == NORTH);
}

TEST(Creature, run_facing_north_turn_left_expect_west)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	Board b;
	Creature c(t, 0, 0, NORTH, &b);
	ASSERT_TRUE(c._faces == NORTH);
	c.run();
	ASSERT_TRUE(c._faces == WEST);
}

TEST(Creature, run_facing_north_turn_right_expect_east)
{
	Species t("test", 't');
	t.addInstruction(RIGHT);
	Board b;
	Creature c(t, 0, 0, NORTH, &b);
	ASSERT_TRUE(c._faces == NORTH);
	c.run();
	ASSERT_TRUE(c._faces == EAST);
}

TEST(Creature, run_facing_east_turn_right_expect_south)
{
	Species t("test", 't');
	t.addInstruction(RIGHT);
	Board b;
	Creature c(t, 0, 0, EAST, &b);
	ASSERT_TRUE(c._faces == EAST);
	c.run();
	ASSERT_TRUE(c._faces == SOUTH);
}

TEST(Creature, run_facing_south_turn_right_expect_west)
{
	Species t("test", 't');
	t.addInstruction(RIGHT);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	ASSERT_TRUE(c._faces == SOUTH);
	c.run();
	ASSERT_TRUE(c._faces == WEST);
}

TEST(Creature, run_facing_west_turn_right_expect_north)
{
	Species t("test", 't');
	t.addInstruction(RIGHT);
	Board b;
	Creature c(t, 0, 0, WEST, &b);
	ASSERT_TRUE(c._faces == WEST);
	c.run();
	ASSERT_TRUE(c._faces == NORTH);
}

TEST(Creature, infect_facing_wall_expect_exception)
{
	Species t("test", 't');
	t.addInstruction(INFECT);
	Board b;
	Creature c(t, 0, 0, WEST, &b);
    try
    {
    	c.run(); // Attempting to infect out-of-bounds
    	ASSERT_TRUE(false); // Should have thrown out_of_range
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(true);
    } 
}

TEST(Creature, isEnemy_same_species_expect_false)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	Board b;
	Creature c1(t, 0, 0, EAST, &b);
	Creature c2(t, 0, 1, WEST, &b);
    try
    {
 		ASSERT_FALSE(c1.isEnemy());
		ASSERT_FALSE(c2.isEnemy());
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);
    } 
}

TEST(Creature, isEnemy_diff_species_expect_true)
{
	Species f("foo", 'f');
	Species g("bar", 'b');
	f.addInstruction(LEFT);
	f.addInstruction(RIGHT);
	Board b;
	Creature c1(f, 0, 0, EAST, &b);
	Creature c2(g, 0, 1, WEST, &b);
	b.place(0, 0, c1);
	b.place(0, 1, c2);
    try
    {
 		ASSERT_TRUE(c1.isEnemy());
		ASSERT_TRUE(c2.isEnemy());
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);
    } 
}

TEST(Creature, infect_facing_empty_expect_do_nothing)
{
	Species t("test", 't');
	t.addInstruction(INFECT);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
    try
    {
    	c.run(); // Attempting to infect empty spot, should do nothing
    	ASSERT_TRUE(c._faces == SOUTH);  // direction shouldn't change
    	ASSERT_FALSE(b.isOccupied(1,0));
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false); // No exception should be thrown
    } 
}

TEST(Creature, run_go)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	t.addInstruction(GO,0);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_empty_is_empty)
{
	Species t("test", 't');
	t.addInstruction(LEFT);
	t.addInstruction(IF_EMPTY, 3);
	t.addInstruction(GO,0);
	t.addInstruction(RIGHT);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_empty_not_empty)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_EMPTY, 3);
	t.addInstruction(GO,0);
	t.addInstruction(RIGHT);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	Creature c2(t, 1, 0, NORTH, &b);
	b.place(0, 0, c);
	b.place(1, 0, c2);
	ASSERT_TRUE(b.isOccupied(1, 0));
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_enemy_is_enemy)
{
	Species t("test", 't');
	Species z("zebra", 'z');
	t.addInstruction(HOP);
	t.addInstruction(IF_ENEMY, 3);
	t.addInstruction(GO,0);
	t.addInstruction(RIGHT);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	Creature c2(z, 1, 0, NORTH, &b);
	b.place(0, 0, c);
	b.place(1, 0, c2);
	ASSERT_TRUE(b.isOccupied(1, 0));
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_enemy_not_enemy)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_ENEMY, 3);
	t.addInstruction(GO,0);
	t.addInstruction(RIGHT);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	Creature c2(t, 1, 0, NORTH, &b);
	b.place(0, 0, c);
	b.place(1, 0, c2);
	ASSERT_TRUE(b.isOccupied(1, 0));
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_enemy_is_empty)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_ENEMY, 3);
	t.addInstruction(GO,0);
	t.addInstruction(RIGHT);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, SOUTH, &b);
	Creature c2(t, 3, 1, NORTH, &b);
	b.place(0, 0, c);
	b.place(3, 1, c2);
	ASSERT_TRUE(b.isOccupied(3, 1));
	ASSERT_FALSE(b.isOccupied(1, 0));
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_wall_facing_west_left_edge)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 1, 0, WEST, &b);
	b.place(1, 0, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_wall_facing_east_left_edge_expect_false)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 0, EAST, &b);
	b.place(0, 0, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_wall_facing_east_right_edge)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b(6, 6);
	Creature c(t, 1, 5, EAST, &b);
	b.place(1, 5, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	std::cout << c._pc << std::endl;
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_wall_facing_west_right_edge_expect_false)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 1, 5, WEST, &b);
	b.place(1, 5, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_wall_facing_south_bottom_row)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b(6, 6);
	Creature c(t, 5, 2, SOUTH, &b);
	b.place(5, 2, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_wall_facing_north_bottom_row_expect_false)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 5, 2, NORTH, &b);
	b.place(5, 2, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

TEST(Creature, run_if_wall_facing_north_top_row)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b(6, 6);
	Creature c(t, 0, 2, NORTH, &b);
	b.place(0, 2, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 4);
}

TEST(Creature, run_if_wall_facing_south_top_row_expect_false)
{
	Species t("test", 't');
	t.addInstruction(HOP);
	t.addInstruction(IF_WALL, 3);
	t.addInstruction(GO,0);
	t.addInstruction(HOP);
	t.addInstruction(GO, 3);
	Board b;
	Creature c(t, 0, 2, SOUTH, &b);
	b.place(0, 2, c);
	ASSERT_TRUE(c._pc == 0);
	c.run();
	ASSERT_TRUE(c._pc == 1);
	c.run();
	ASSERT_TRUE(c._pc == 1);
}

// Infect is tested further in the Darwin tests, where the other
//  creature can be examined

TEST(Species, constructor)
{
	Species t("test", 't');
	ASSERT_TRUE(t._name == "test");
	ASSERT_TRUE(t._abbr == 't');
}

TEST(Species, printSelf)
{
	Species s("test", 't');
	std::ostringstream w;
	s.printSelf(w);
	ASSERT_TRUE(w.str() == "t");
}

TEST(Species, printSelf_default_expect_d)
{
	Species s;
	std::ostringstream w;
	s.printSelf(w);
	ASSERT_TRUE(w.str() == "d"); // Default value
}

TEST(Species, addInstruction_one_instruction)
{
	Species s("test", 't');
	s.addInstruction(HOP, NEXT_INSTRUCTION);
	ASSERT_TRUE(s._program.at(0).first == HOP);
	ASSERT_TRUE(s._program.at(0).second == NEXT_INSTRUCTION);
}

TEST(Species, addInstruction_two_instructions)
{
	Species s("test", 't');
	s.addInstruction(HOP);
	ASSERT_TRUE(s._program.at(0).first == HOP);
	s.addInstruction(GO, 0);
	ASSERT_TRUE(s._program.at(1).first == GO);
	ASSERT_TRUE(s._program.at(1).second == 0);
}

TEST(Species, getInstruction_two_instructions)
{
	Species s("test", 't');
	s.addInstruction(HOP);
	s.addInstruction(GO, 0);
	std::pair<instruction_t, int> ins = s.getInstruction(0);
	ASSERT_TRUE(ins.first == HOP);
	ins = s.getInstruction(1);
	ASSERT_TRUE(ins.first == GO);
	ASSERT_TRUE(ins.second == 0);
}

TEST(Species, getInstruction_no_program_expect_throw_exception)
{
	Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    d.addCreature(hoppy, 1, 3, WEST);
    try
    {
    	d.runTurn(); // Attempting run with no program, should throw
    	ASSERT_TRUE(false);
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(true);
    } 
}

TEST(Darwin, constructor)
{
	Darwin d(10, 12);
	ASSERT_TRUE(d._turn == 0);
	ASSERT_TRUE(d._theBoard._height == 10);
	ASSERT_TRUE(d._theBoard._width == 12);
}

TEST(Darwin, addCreature_at_row0_col0)
{
	Darwin d(8, 8);
	ASSERT_TRUE(&d._theBoard.get(0,0) == NULL); 
    Species s;
	d.addCreature(s, 0, 0, SOUTH);
	ASSERT_TRUE(&d._theBoard.get(0,0) != NULL);
}

TEST(Darwin, addCreature_at_row3_col4_8by8)
{
	Darwin d(8, 8);
	ASSERT_TRUE(&d._theBoard.get(3,4) == NULL);
    Species s;
	d.addCreature(s, 3, 4, WEST);
	ASSERT_TRUE(&d._theBoard.get(3,4) != NULL);
}

TEST(Darwin, addCreature_at_row7_col7_bottom_right_corner_8by8)
{
	Darwin d(8, 8);
	ASSERT_TRUE(&d._theBoard.get(7,7) == NULL);
    Species s;
	d.addCreature(s, 7, 7, WEST);
	ASSERT_TRUE(&d._theBoard.get(7,7) != NULL);
} 

TEST(Darwin, printBoard_empty_5by5)
{
    std::ostringstream w;
    Darwin d(5, 5);
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 .....\n");
}

TEST(Darwin, printBoard_1creature_topleft_5by5)
{
    std::ostringstream w;
    Darwin d(5, 5);
    Species hopper("hopper", 'h');
    d.addCreature(hopper, 0, 0, SOUTH);
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 h....\n1 .....\n2 .....\n3 .....\n4 .....\n");
}

TEST(Darwin, printBoard_1creature_bottomright_5by5)
{
    std::ostringstream w;
    Darwin d(5, 5);
    Species hopper("hopper", 'h');
    d.addCreature(hopper, 4, 4, SOUTH);
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 ....h\n");
}

TEST(Darwin, printBoard_1creature_bottomright_5by5_run_turn_expect_turn1)
{
    std::ostringstream w;
    Darwin d(5, 5);
    Species hopper("hopper", 'h');
    hopper.addInstruction(LEFT);
    d.addCreature(hopper, 4, 4, SOUTH);
    d.runTurn();
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 1.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 ....h\n");
}

TEST(Darwin, hop_go_2creatures_hit_wall)
{
    Darwin d(10, 10);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 2, 5, WEST);
    d.addCreature(hoppy, 5, 5, SOUTH);
    const int MOVES = 4;
    for (int i = 0; i < MOVES; ++i)
    {
    	d.runTurn();
    	//d.printBoard(std::cout);
    }
    ASSERT_TRUE(d._theBoard._theBoard.at(95) != NULL);
    ASSERT_TRUE(d._theBoard._theBoard.at(21) != NULL);
   	d.runTurn(); // Attempting to hop out-of-bounds, should not move
   	ASSERT_TRUE(d._theBoard._theBoard.at(95) != NULL);
    ASSERT_TRUE(d._theBoard._theBoard.at(20) != NULL);
}

TEST(Darwin, hop_go_2creatures_collide)
{
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 1, 3, WEST);
    d.addCreature(hoppy, 1, 2, EAST);
    //d.printBoard(std::cout);
    try
    {
    	d.runTurn(); // Attempting hop with collision
    	ASSERT_TRUE(true);
    	ASSERT_TRUE(d._theBoard._theBoard.at(8) != NULL);
    	ASSERT_TRUE(d._theBoard._theBoard.at(7) != NULL);
    	//d.printBoard(std::cout);
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_top_moving_right)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 0, 0, EAST);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 4;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 ....h\n1 .....\n2 .....\n3 .....\n4 .....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_bottom_moving_right)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 4, 0, EAST);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 4;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 ....h\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_bottom_moving_left)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 4, 4, WEST);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 4;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 h....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_left_moving_down)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 0, 0, SOUTH);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 4;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 h....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_right_moving_up)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 4, 4, NORTH);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 4;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 ....h\n1 .....\n2 .....\n3 .....\n4 .....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_right_hits_wall_should_stay)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 4, 4, NORTH);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 6;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 6.\n  01234\n0 ....h\n1 .....\n2 .....\n3 .....\n4 .....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, hop_go_1creature_across_bottom_moving_right_hits_wall_should_stay)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species hoppy ("hoppy", 'h');
    hoppy.addInstruction(HOP); // #1
    hoppy.addInstruction(GO, 0); // #2
    d.addCreature(hoppy, 4, 0, EAST);
    //d.printBoard(std::cout);
    try
    {
    	const int MOVES = 6;
    	for (int i = 0; i < MOVES; ++i)
    	{
    		d.runTurn();
    	}
    	d.printBoard(w);
    	ASSERT_TRUE(w.str() == "Turn = 6.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 ....h\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, infect_creature_is_there_expect_creature_change_species)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species infector ("infector", 'i');
    Species food ("food", 'f');
    infector.addInstruction(INFECT);
    food.addInstruction(LEFT);
    d.addCreature(infector, 0, 0, EAST);
    d.addCreature(food, 0, 1, WEST);
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 if...\n1 .....\n2 .....\n3 .....\n4 .....\n");
    try
    {
   		d.runTurn();
   		std::ostringstream x;
    	d.printBoard(x);
    	ASSERT_TRUE(x.str() == "Turn = 1.\n  01234\n0 ii...\n1 .....\n2 .....\n3 .....\n4 .....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}

TEST(Darwin, infect_creature_is_same_species_expect_do_nothing)
{
	std::ostringstream w;
    Darwin d(5, 5);
    Species infector ("infector", 'i');
    infector.addInstruction(INFECT); // #1
    d.addCreature(infector, 0, 0, EAST);
    d.addCreature(infector, 0, 1, WEST);
    d.printBoard(w);
    ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 ii...\n1 .....\n2 .....\n3 .....\n4 .....\n");
    try
    {
   		d.runTurn();
   		std::ostringstream x;
    	d.printBoard(x);
    	ASSERT_TRUE(x.str() == "Turn = 1.\n  01234\n0 ii...\n1 .....\n2 .....\n3 .....\n4 .....\n");
    }
    catch (const std::out_of_range&)
    {
    	ASSERT_TRUE(false);  // Should not throw
    } 
}