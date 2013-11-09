#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

// expose functionality to make testing easier teehee
#define private public
#define protected public
#define class struct

#include "Darwin.h"

using namespace std;

// there are only 20 test methods
// this is because I chose only to test methods worth testing
// constructors, getters, setters, and the like don't have any nontrivial logic,
// so I didn't write any tests for them
// the tests I did write are thorough and cover (I hope) the necessary cases
// for what it's worth, there are 68 EXPECT statements

// -------
// SPECIES
// -------

TEST(SpeciesTest, AddGetInstruction) {
	GoInstruction go(5);
	LeftInstruction left;
	InfectInstruction infect;
	IfRandomInstruction ifrandom(2);
	IfWallInstruction ifwall(10);
	HopInstruction hop;
	IfEmptyInstruction ifempty(1);
	IfEnemyInstruction ifenemy(1);
	RightInstruction right;

	Species s;
	s.add_instruction(go);
	s.add_instruction(left);
	s.add_instruction(infect);
	s.add_instruction(ifrandom);
	s.add_instruction(ifwall);
	s.add_instruction(hop);
	s.add_instruction(ifempty);
	s.add_instruction(ifenemy);
	s.add_instruction(right);

	EXPECT_EQ(go, s.get_instruction(0));
	EXPECT_EQ(left, s.get_instruction(1));
	EXPECT_EQ(infect, s.get_instruction(2));
	EXPECT_EQ(ifrandom, s.get_instruction(3));
	EXPECT_EQ(ifwall, s.get_instruction(4));
	EXPECT_EQ(hop, s.get_instruction(5));
	EXPECT_EQ(ifempty, s.get_instruction(6));
	EXPECT_EQ(ifenemy, s.get_instruction(7));
	EXPECT_EQ(right, s.get_instruction(8));
}

// --------
// CREATURE
// --------

// test PC increment of action instructions
TEST(CreatureActTest, ActionInstructions) {
	Species species;
	species.add_instruction(RightInstruction());
	species.add_instruction(InfectInstruction());
	species.add_instruction(HopInstruction());
	species.add_instruction(LeftInstruction());
	species.add_instruction(HopInstruction());
	Creature creature(species, Direction::SOUTH);

	EXPECT_EQ(0, creature._program_counter);

	CreatureActionType action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(1, creature._program_counter);

	action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::INFECT, action);
	EXPECT_EQ(2, creature._program_counter);

	action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::HOP, action);
	EXPECT_EQ(3, creature._program_counter);

	action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(4, creature._program_counter);
}

// test PC increments of control instructions

TEST(CreatureActTest, IfEmpty) {
	Species species;
	species.add_instruction(IfEmptyInstruction(2));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	species.add_instruction(IfEmptyInstruction(5));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	Creature creature(species, Direction::SOUTH);

	CreatureActionType action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(3, creature._program_counter);

	action = creature.act(GridEntity::WALL);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(5, creature._program_counter);
}

TEST(CreatureActTest, IfWall) {
	Species species;
	species.add_instruction(IfWallInstruction(2));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	species.add_instruction(IfWallInstruction(5));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	Creature creature(species, Direction::SOUTH);

	CreatureActionType action = creature.act(GridEntity::WALL);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(3, creature._program_counter);

	action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(5, creature._program_counter);
}

TEST(CreatureActTest, IfRandom) {
	srand(0);

	Species species;
	species.add_instruction(IfRandomInstruction(2));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	species.add_instruction(IfRandomInstruction(5));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	Creature creature(species, Direction::SOUTH);

	CreatureActionType action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(3, creature._program_counter);

	action = creature.act(GridEntity::WALL);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(5, creature._program_counter);
}

TEST(CreatureActTest, IfEnemy) {
	Species species;
	species.add_instruction(IfEnemyInstruction(3));
	species.add_instruction(LeftInstruction());
	species.add_instruction(GoInstruction(0));
	species.add_instruction(RightInstruction());
	species.add_instruction(LeftInstruction());
	Creature creature(species, Direction::SOUTH);
	string own_identity = species.get_identity();

	CreatureActionType action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(2, creature._program_counter);

	action = creature.act(GridEntity::WALL);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(2, creature._program_counter);

	action = creature.act(own_identity);
	EXPECT_EQ(CreatureActionType::TURN_LEFT, action);
	EXPECT_EQ(2, creature._program_counter);

	action = creature.act(string("enemy of ") + own_identity);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(4, creature._program_counter);

}

TEST(CreatureActTest, Go) {
	Species species;
	species.add_instruction(GoInstruction(2));
	species.add_instruction(LeftInstruction());
	species.add_instruction(RightInstruction());
	species.add_instruction(HopInstruction());
	Creature creature(species, Direction::SOUTH);

	CreatureActionType action = creature.act(GridEntity::NOTHING);
	EXPECT_EQ(CreatureActionType::TURN_RIGHT, action);
	EXPECT_EQ(3, creature._program_counter);
}

// more complex branching
// imagine a hyphen between Multiple and Instruction
TEST(CreatureActTest, MultipleInstructionAction) {
	// actions with logic
	Species species;
	species.add_instruction(IfEmptyInstruction(2));
	species.add_instruction(HopInstruction());
	species.add_instruction(HopInstruction());
	species.add_instruction(IfWallInstruction(0));

	Creature creature(species, Direction::SOUTH);

	EXPECT_EQ(0, creature._program_counter);

	// single branch
	// if-empty succeeds, go to 2, which takes us to 3
	creature.act(GridEntity::NOTHING);
	EXPECT_EQ(3, creature._program_counter);

	// double branch
	creature.act(GridEntity::WALL);
	// if-wall succeeds, go to 0, if-empty fails, go to 1, which takes us to 2
	EXPECT_EQ(2, creature._program_counter);
}

// ----
// GRID
// ----

TEST(GridPrintTest, Square) {
	Grid grid(4, 4);
	ostringstream oss;
	string expected(string() +
		"  0123\n" +
		"0 ....\n" +
		"1 ....\n" +
		"2 ....\n" +
		"3 ....\n"
	);

	grid.print(oss);
	EXPECT_STREQ(expected.c_str(), oss.str().c_str());
}

TEST(GridPrintTest, NotSquare) {
	Grid grid(2, 3);
	ostringstream oss;
	string expected(string() +
		"  012\n" +
		"0 ...\n" +
		"1 ...\n"
	);

	grid.print(oss);
	EXPECT_STREQ(expected.c_str(), oss.str().c_str());
}

TEST(GridPrintTest, Large) {
	Grid grid(11, 13);
	ostringstream oss;
	string expected(string() +
		"  0123456789012\n" +
		"0 .............\n" +
		"1 .............\n" +
		"2 .............\n" +
		"3 .............\n" +
		"4 .............\n" +
		"5 .............\n" +
		"6 .............\n" +
		"7 .............\n" +
		"8 .............\n" +
		"9 .............\n" +
		"0 .............\n"
	);

	grid.print(oss);
	EXPECT_STREQ(expected.c_str(), oss.str().c_str());
}

TEST(GridPrintTest, NotEmpty) {
	Grid grid(4, 4);
	Creature c1(Food(), Direction::SOUTH);
	Creature c2(Hopper(), Direction::SOUTH);
	Creature c3(Rover(), Direction::SOUTH);
	Creature c4(Trap(), Direction::SOUTH);
	grid.place_creature(0, 0, c1);
	grid.place_creature(1, 3, c2);
	grid.place_creature(2, 0, c3);
	grid.place_creature(3, 1, c4);
	ostringstream oss;
	string expected(string() +
		"  0123\n" +
		"0 f...\n" +
		"1 ...h\n" +
		"2 r...\n" +
		"3 .t..\n"
	);

	grid.print(oss);
	EXPECT_STREQ(expected.c_str(), oss.str().c_str());
}

TEST(GridPlaceCreatureTest, Success) {
	Grid grid(4, 4);
	Creature creature(Species(), Direction::SOUTH);

	bool place_succeeded = grid.place_creature(0, 0, creature);
	EXPECT_TRUE(place_succeeded);
}

TEST(GridPlaceCreatureTest, AttemptReplace) {
	Grid grid(4, 4);
	Creature creature(Species(), Direction::SOUTH);
	grid.place_creature(0, 0, creature);

	// can't place creature in occupied spot
	bool replace_succeeded = grid.place_creature(0, 0, creature);
	EXPECT_FALSE(replace_succeeded);
}

TEST(GridGoadSingleTest, Hop) {
	Grid grid(4, 4);
	// hoppers hop indefinitely
	Creature hop1(Hopper(), Direction::EAST);
	Creature hop2(Hopper(), Direction::EAST);
	Creature hop3(Hopper(), Direction::EAST);
	// food doesn't move
	Creature food(Food(), Direction::EAST);
	grid.place_creature(0, 0, hop1);
	grid.place_creature(1, 3, hop2);
	grid.place_creature(2, 1, hop3);
	grid.place_creature(2, 2, food);

	// this guy is facing nothing, so he will move
	EXPECT_NE(nullptr, grid._creature_grid[0][0]);
	grid.goad_single_creature(0, 0);
	EXPECT_EQ(&hop1, grid._creature_grid[0][1]);
	// must vacate the spot behind him
	EXPECT_EQ(nullptr, grid._creature_grid[0][0]);

	// this guy won't move, he's facing a wall
	grid.goad_single_creature(1, 3);
	EXPECT_EQ(&hop2, grid._creature_grid[1][3]);

	// this guy won't move, he's facing someone else
	grid.goad_single_creature(2, 1);
	EXPECT_EQ(&hop3, grid._creature_grid[2][1]);
}

TEST(GridGoadSingleTest, Turn) {
	Grid grid(2, 2);
	// food only turns left
	Creature food(Food(), Direction::WEST);
	// anti-food only turns right
	Species right_turner;
	right_turner.add_instruction(RightInstruction());
	right_turner.add_instruction(GoInstruction(0));
	Creature anti_food(right_turner, Direction::EAST);
	grid.place_creature(0, 0, food);
	grid.place_creature(0, 1, anti_food);

	Creature* const & food_cell = grid._creature_grid[0][0];
	Creature* const & anti_food_cell = grid._creature_grid[0][1];

	// both start facing walls, they will turn
	grid.goad_single_creature(0, 0);
	grid.goad_single_creature(0, 1);
	EXPECT_NE(nullptr, food_cell);
	EXPECT_EQ(Direction::SOUTH, food_cell->get_direction());
	EXPECT_NE(nullptr, anti_food_cell);
	EXPECT_EQ(Direction::SOUTH, anti_food_cell->get_direction());

	// now facing nothing, they will turn
	grid.goad_single_creature(0, 0);
	grid.goad_single_creature(0, 1);
	EXPECT_NE(nullptr, food_cell);
	EXPECT_EQ(Direction::EAST, food_cell->get_direction());
	EXPECT_NE(nullptr, anti_food_cell);
	EXPECT_EQ(Direction::WEST, anti_food_cell->get_direction());

	// now facing each other, they will turn
	grid.goad_single_creature(0, 0);
	grid.goad_single_creature(0, 1);
	EXPECT_NE(nullptr, food_cell);
	EXPECT_EQ(Direction::NORTH, food_cell->get_direction());
	EXPECT_NE(nullptr, anti_food_cell);
	EXPECT_EQ(Direction::NORTH, anti_food_cell->get_direction());
}

TEST(GridGoadSingleTest, Infect) {
	Grid grid(3, 2);
	// not an infector
	Creature enemy(Food(), Direction::SOUTH);
	enemy._program_counter = 1;
	Species infector("infector");
	infector.add_instruction(InfectInstruction());
	infector.add_instruction(GoInstruction(0));
	// an infector
	Creature guy(infector, Direction::WEST);
	// fellow infector
	// can't spell friend correctly unfortunately
	Creature freind(infector, Direction::NORTH);
	grid.place_creature(0, 0, enemy);
	grid.place_creature(1, 0, guy);
	grid.place_creature(1, 1, freind);

	Creature* const & enemy_cell = grid._creature_grid[0][0];
	Creature* const & guy_cell = grid._creature_grid[1][0];
	Creature* const & freind_cell = grid._creature_grid[1][1];

	// starts facing wall, will do nothing
	grid.goad_single_creature(1, 0);
	EXPECT_STREQ("infector", freind_cell->get_identity().c_str());
	EXPECT_STREQ("Food", enemy_cell->get_identity().c_str());

	guy_cell->set_direction(Direction::SOUTH);
	// now facing nothing, will do nothing
	grid.goad_single_creature(1, 0);
	EXPECT_STREQ("infector", freind_cell->get_identity().c_str());
	EXPECT_STREQ("Food", enemy_cell->get_identity().c_str());

	guy_cell->set_direction(Direction::EAST);
	// now facing friend, will do nothing
	grid.goad_single_creature(1, 0);
	EXPECT_STREQ("infector", freind_cell->get_identity().c_str());
	EXPECT_STREQ("Food", enemy_cell->get_identity().c_str());

	EXPECT_EQ(1, enemy_cell->_program_counter);
	EXPECT_EQ(Direction::SOUTH, enemy_cell->get_direction());

	guy_cell->set_direction(Direction::NORTH);
	// now facing enemy, will infect Food
	grid.goad_single_creature(1, 0);
	EXPECT_STREQ("infector", freind_cell->get_identity().c_str());
	// identity changes
	EXPECT_STREQ("infector", enemy_cell->get_identity().c_str());
	// program counter reset
	EXPECT_EQ(0, enemy_cell->_program_counter);
	// direction stays the same
	EXPECT_EQ(Direction::SOUTH, enemy_cell->get_direction());
}

TEST(GridGoadAllTest, DisparateSpecies) {
	Grid grid(2, 4);
	Creature food(Food(), Direction::NORTH);
	Creature hopper(Hopper(), Direction::WEST);
	Creature trap(Trap(), Direction::NORTH);
	grid.place_creature(0, 0, food);
	grid.place_creature(0, 2, hopper);
	grid.place_creature(1, 3, trap);

	grid.goad_all_creatures();
	// after one cycle, food and trap will have turned, and hopper will have hopped
	EXPECT_EQ(Direction::WEST, grid._creature_grid[0][0]->get_direction());
	EXPECT_NE(nullptr, grid._creature_grid[0][1]);
	EXPECT_EQ(nullptr, grid._creature_grid[0][2]);
	EXPECT_EQ(Direction::WEST, grid._creature_grid[1][3]->get_direction());

	grid.goad_all_creatures();
	// food and trap will have turned again, hopper will have stopped
	EXPECT_EQ(Direction::SOUTH, grid._creature_grid[0][0]->get_direction());
	EXPECT_NE(nullptr, grid._creature_grid[0][1]);
	EXPECT_EQ(Direction::SOUTH, grid._creature_grid[1][3]->get_direction());
}

TEST(GridGoadAllTest, SameSpecies) {
	Grid grid(2, 3);
	Creature hop1(Hopper(), Direction::EAST);
	Creature hop2(Hopper(), Direction::WEST);
	grid.place_creature(0, 0, hop1);
	grid.place_creature(1, 2, hop2);

	// two hoppers passing along each other

	grid.goad_all_creatures();
	EXPECT_EQ(nullptr, grid._creature_grid[0][0]);
	EXPECT_NE(nullptr, grid._creature_grid[0][1]);
	EXPECT_EQ(nullptr, grid._creature_grid[1][2]);
	EXPECT_NE(nullptr, grid._creature_grid[1][1]);

	grid.goad_all_creatures();
	EXPECT_EQ(nullptr, grid._creature_grid[0][1]);
	EXPECT_NE(nullptr, grid._creature_grid[0][2]);
	EXPECT_EQ(nullptr, grid._creature_grid[1][1]);
	EXPECT_NE(nullptr, grid._creature_grid[1][0]);
}

TEST(GridGoadAllTest, GoadedOnlyOnce) {
	Grid grid(3, 1);
	Creature hopper(Hopper(), Direction::SOUTH);
	grid.place_creature(0, 0, hopper);

	// hopper will move down
	// will pass over a second time during goad scan
	// but shouldn't goad again

	grid.goad_all_creatures();
	EXPECT_EQ(nullptr, grid._creature_grid[0][0]);
	EXPECT_NE(nullptr, grid._creature_grid[1][0]);

	grid.goad_all_creatures();
	EXPECT_EQ(nullptr, grid._creature_grid[1][0]);
	EXPECT_NE(nullptr, grid._creature_grid[2][0]);
}

