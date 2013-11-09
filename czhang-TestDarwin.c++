#include <cstdlib>  // rand, srand
#include <iostream> // count, endl
#include <sstream>	// istringstream, ostringstream
#include <string>	// ==
#include <stdexcept>

#include "gtest/gtest.h"
#include "Darwin.h"

TEST(Species, construct_and_name) 
{
	std::string name = "one";

	Species one(name);
	ASSERT_TRUE(one.get_name().compare(name) == 0);
}

TEST(Species, add_instruction_out_of_bounds)
{
	std::string name = "one";
	size_t i = 0;

	Species one(name);
	ASSERT_THROW(one.execute_instruction(i), std::out_of_range);
}

TEST(Species, add_instruction_HOP)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::HOP;

	Species one(name);
	one.add_instruction(i1);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 1);
}

TEST(Species, add_instruction_LEFT)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::LEFT;

	Species one(name);
	one.add_instruction(i1);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 1);
}

TEST(Species, add_instruction_RIGHT)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::RIGHT;

	Species one(name);
	one.add_instruction(i1);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 1);
}

TEST(Species, add_instruction_INFECT)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::INFECT;

	Species one(name);
	one.add_instruction(i1);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 1);
}


TEST(Species, add_instruction_IF_EMPTY_bad_argument)
{
	std::string name = "one";
	Instruction i1 = Instruction::IF_EMPTY;

	Species one(name);
	ASSERT_THROW(one.add_instruction(i1), std::invalid_argument);
}

TEST(Species, add_instruction_IF_WALL_bad_argument)
{
	std::string name = "one";
	Instruction i1 = Instruction::IF_WALL;

	Species one(name);
	ASSERT_THROW(one.add_instruction(i1), std::invalid_argument);
}

TEST(Species, add_instruction_IF_RANDOM_bad_argument)
{
	std::string name = "one";
	Instruction i1 = Instruction::IF_RANDOM;

	Species one(name);
	ASSERT_THROW(one.add_instruction(i1), std::invalid_argument);
}

TEST(Species, add_instruction_IF_ENEMY_bad_argument)
{
	std::string name = "one";
	Instruction i1 = Instruction::IF_ENEMY;

	Species one(name);
	ASSERT_THROW(one.add_instruction(i1), std::invalid_argument);
}

TEST(Species, add_instruction_GO_bad_argument)
{
	std::string name = "one";
	Instruction i1 = Instruction::GO;

	Species one(name);
	ASSERT_THROW(one.add_instruction(i1), std::invalid_argument);
}

TEST(Species, add_instruction_IF_EMPTY)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::IF_EMPTY;

	Species one(name);
	one.add_instruction(i1, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 0);
}

TEST(Species, add_instruction_IF_WALL)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::IF_WALL;

	Species one(name);
	one.add_instruction(i1, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 0);
}

TEST(Species, add_instruction_IF_RANDOM)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::IF_RANDOM;

	Species one(name);
	one.add_instruction(i1, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 0);
}
TEST(Species, add_instruction_IF_ENEMY)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::IF_ENEMY;

	Species one(name);
	one.add_instruction(i1, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 0);
}

TEST(Species, add_instruction_GO)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::GO;

	Species one(name);
	one.add_instruction(i1, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 0);
}

TEST(Species, add_multiple_instructions)
{
	std::string name = "one";
	size_t i = 0;
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;

	Species one(name);
	one.add_instruction(i1);
	one.add_instruction(i2, 0);
	ASSERT_TRUE(one.execute_instruction(i) == i1);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(one.execute_instruction(i) == i2);
	ASSERT_TRUE(i == 0);
}

TEST(Creature, construct_basic_creature)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
}

TEST(Creature, get_next_instruction_HOP)
{	
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i1);
}

TEST(Creature, get_next_instruction_LEFT)
{	
	std::string name = "one";
	Instruction i1 = Instruction::LEFT;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i1);
}

TEST(Creature, get_next_instruction_RIGHT)
{	
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i1);
}

TEST(Creature, get_next_instruction_INFECT)
{	
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i1);
}

TEST(Creature, get_next_instruction_IF_EMPTY)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_EMPTY;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction(State::IS_EMPTY) == i3);
}

TEST(Creature, get_next_instruction_IF_WALL)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_WALL;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction(State::IS_WALL) == i3);
}

TEST(Creature, get_next_instruction_IF_ENEMY)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_ENEMY;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction(State::IS_ENEMY) == i3);
}

TEST(Creature, get_next_instruction_IF_EMPTY_not)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_EMPTY;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction(State::IS_ENEMY) == i2);
}

TEST(Creature, get_next_instruction_IF_WALL_not)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_WALL;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i2);
}

TEST(Creature, get_next_instruction_IF_ENEMY_not)
{	
	std::string name = "one";
	Instruction i1 = Instruction::IF_ENEMY;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i2);
}

TEST(Creature, get_next_instruction_GO)
{	
	std::string name = "one";
	Instruction i1 = Instruction::GO;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(c1.get_next_instruction() == i3);
}

TEST(Creature, get_next_instruction_IF_RANDOM)
{	
	srand(0);
	std::string name = "one";
	Instruction i1 = Instruction::IF_RANDOM;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::RIGHT;

	Species s1(name);
	s1.add_instruction(i1, 2);
	s1.add_instruction(i2);
	s1.add_instruction(i3);
	Creature c1(s1);

	Instruction instr = c1.get_next_instruction();

	ASSERT_TRUE(c1.get_species_name().compare(name) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::NORTH);
	ASSERT_TRUE(instr == i2 || instr == i3);
}

TEST(Creature, manual_turn_left_x1)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_left() == Direction::WEST);
}

TEST(Creature, manual_turn_left_x2)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_left() == Direction::WEST);
	ASSERT_TRUE(c1.turn_left() == Direction::SOUTH);
}

TEST(Creature, manual_turn_left_x3)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_left() == Direction::WEST);
	ASSERT_TRUE(c1.turn_left() == Direction::SOUTH);
	ASSERT_TRUE(c1.turn_left() == Direction::EAST);
}

TEST(Creature, manual_turn_left_x4)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_left() == Direction::WEST);
	ASSERT_TRUE(c1.turn_left() == Direction::SOUTH);
	ASSERT_TRUE(c1.turn_left() == Direction::EAST);
	ASSERT_TRUE(c1.turn_left() == Direction::NORTH);
}

TEST(Creature, manual_turn_right_x1)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_right() == Direction::EAST);
}

TEST(Creature, manual_turn_right_x2)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_right() == Direction::EAST);
	ASSERT_TRUE(c1.turn_right() == Direction::SOUTH);
}

TEST(Creature, manual_turn_right_x3)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_right() == Direction::EAST);
	ASSERT_TRUE(c1.turn_right() == Direction::SOUTH);
	ASSERT_TRUE(c1.turn_right() == Direction::WEST);
}

TEST(Creature, manual_turn_right_x4)
{
	std::string name = "one";
	Instruction i1 = Instruction::HOP;

	Species s1(name);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::NORTH);

	ASSERT_TRUE(c1.turn_right() == Direction::EAST);
	ASSERT_TRUE(c1.turn_right() == Direction::SOUTH);
	ASSERT_TRUE(c1.turn_right() == Direction::WEST);
	ASSERT_TRUE(c1.turn_right() == Direction::NORTH);
}

TEST(Creature, manual_change_species)
{
	std::string n1 = "one";
	Instruction i1 = Instruction::LEFT;
	std::string n2 = "two";
	Instruction i2 = Instruction::RIGHT;

	Species s1(n1);
	Species s2(n2);
	s1.add_instruction(i1, 0);
	s2.add_instruction(i2, 0);

	Creature c1(s1, Direction::SOUTH);

	ASSERT_TRUE(c1.get_species_name().compare(n1) == 0);
	ASSERT_TRUE(c1.get_direction() == Direction::SOUTH);
	ASSERT_TRUE(c1.get_next_instruction() == i1);
	
	c1.set_species(s2);
	ASSERT_TRUE(c1.get_direction() == Direction::SOUTH);
	ASSERT_TRUE(c1.get_next_instruction() == i2);
}

TEST(Creature, manual_infect_creature)
{
	std::string n1 = "one";
	Instruction i1 = Instruction::LEFT;
	std::string n2 = "two";
	Instruction i2 = Instruction::RIGHT;

	Species s1(n1);
	Species s2(n2);
	s1.add_instruction(i1, 0);
	s2.add_instruction(i2, 0);

	Creature c1(s1, Direction::NORTH);
	Creature c2(s2, Direction::SOUTH);

	ASSERT_TRUE(c2.get_species_name().compare(n2) == 0);
	ASSERT_TRUE(c2.get_direction() == Direction::SOUTH);
	ASSERT_TRUE(c2.get_next_instruction() == i2);
	
	c1.infect_creature(c2);

	ASSERT_TRUE(c2.get_species_name().compare(n1) == 0);
	ASSERT_TRUE(c2.get_direction() == Direction::SOUTH);
	ASSERT_TRUE(c2.get_next_instruction() == i1);
}

TEST(Creature, is_enemy)
{
	std::string n1 = "one";
	Instruction i1 = Instruction::LEFT;
	std::string n2 = "two";
	Instruction i2 = Instruction::RIGHT;

	Species s1(n1);
	Species s2(n2);
	s1.add_instruction(i1, 0);
	s2.add_instruction(i2, 0);

	Creature c1(s1);
	Creature c2(s2);

	ASSERT_TRUE(c1.is_enemy(c2));
}	

TEST(Darwin, print_out)
{
	int x = 20;
	int y = 15;

	Darwin darwin(x, y);

	darwin.print_out();
}

TEST(Darwin, add_creature_bottom_right_corner)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Species s1(n1);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::SOUTH);
	
	int c1_x_pos = 19;
	int c1_y_pos = 14;

	int x = 20;
	int y = 15;

	Darwin darwin(x, y);
	ASSERT_NO_THROW(darwin.add_creature(c1, c1_x_pos, c1_y_pos));
	darwin.print_out();
}

TEST(Darwin, add_creature_out_of_range)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Species s1(n1);
	s1.add_instruction(i1);
	Creature c1(s1, Direction::SOUTH);
	
	int c1_x_pos = 20;
	int c1_y_pos = 15;

	int x = 20;
	int y = 15;

	Darwin darwin(x, y);
	ASSERT_THROW(darwin.add_creature(c1, c1_x_pos, c1_y_pos), std::out_of_range);
	darwin.print_out();
}

TEST(Darwin, Hop_North)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2, 0);
	Creature c1(s1, Direction::NORTH);

	int c1_x = 10;
	int c1_y = 10;

	int x = 20;
	int y = 20;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 5; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Hop_South)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2, 0);
	Creature c1(s1, Direction::SOUTH);

	int c1_x = 10;
	int c1_y = 10;

	int x = 20;
	int y = 20;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 5; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Hop_East)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2, 0);
	Creature c1(s1, Direction::EAST);

	int c1_x = 10;
	int c1_y = 10;

	int x = 20;
	int y = 20;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 5; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Hop_West)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2, 0);
	Creature c1(s1, Direction::WEST);

	int c1_x = 10;
	int c1_y = 10;

	int x = 20;
	int y = 20;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 5; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Hop_Turn_Left)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2);
	s1.add_instruction(i3, 0);
	Creature c1(s1, Direction::NORTH);

	int c1_x = 1;
	int c1_y = 1;

	int x = 2;
	int y = 2;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 10; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Hop_Turn_Right)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::RIGHT;
	Instruction i3 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2);
	s1.add_instruction(i3, 0);
	Creature c1(s1, Direction::NORTH);

	int c1_x = 0;
	int c1_y = 0;

	int x = 2;
	int y = 2;

	Darwin darwin(x, y);
	darwin.add_creature(c1, c1_x, c1_y);

	darwin.print_out();
	for (int i = 0; i < 10; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

TEST(Darwin, Two_Hoppers)
{
	std::string n1 = "h";
	Instruction i1 = Instruction::HOP;
	Instruction i2 = Instruction::GO;
	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2, 0);
	Creature c1(s1, Direction::NORTH);
	Creature c2(s1, Direction::SOUTH);

	int x = 20;
	int y = 20;

	Darwin darwin(x, y);
	darwin.add_creature(c1, 5, 5);
	darwin.add_creature(c2, 15, 15);

	darwin.print_out();

	for (int i = 0; i < 10; ++i)
	{
		darwin.step();
		darwin.print_out();
	}

}


TEST(Darwin, Infect_Around)
{
	std::string n1 = "c";
	Instruction i1 = Instruction::INFECT;
	Instruction i2 = Instruction::LEFT;
	Instruction i3 = Instruction::GO;

	Species s1(n1);
	s1.add_instruction(i1);
	s1.add_instruction(i2);
	s1.add_instruction(i3, 0);
	Creature c1(s1, Direction::NORTH);

	std::string n2 = "f";
	Species s2(n2);
	s2.add_instruction(Instruction::LEFT);
	s2.add_instruction(Instruction::GO, 0);
	Creature c2(s2);

	int x = 3;
	int y = 3;

	Darwin darwin(x, y);
	darwin.add_creature(c1, 1, 1);
	darwin.add_creature(c2, 1, 0);
	darwin.add_creature(c2, 0, 1);
	darwin.add_creature(c2, 2, 1);

	ASSERT_NO_THROW(darwin.print_out());

	for (int i = 0; i < 10; ++i)
	{
		darwin.step();
		darwin.print_out();
	}
}

