// ----------------------------
// Project by:
//    Mitch Stephan (mjs4373)
//    Daniel Roberston (cdr966)
// cs371p-darwin/TestDarwin.c++
// ----------------------------

// --------
// includes
// --------
#include "gtest/gtest.h"

// -------
// defines
// -------
#define class struct
#define protected public
#define private public

#include "Darwin.h"

// ---------------------
// Creature Constructors
// ---------------------
TEST(Creature, construct_with_invalid_species)
{
	bool exception_thrown = false;

	try
	{
		Creature f('a');
	}
	catch(std::invalid_argument& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);	
}

TEST(Food, construct)
{
	Creature c('f');
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'f');
}

TEST(Food, construct_with_turn_counter)
{
	Creature c('f', WEST, 0);
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'f');
}

TEST(Food, construct_without_turn_counter)
{
	Creature c('f', SOUTH);
	ASSERT_TRUE(c._direction == SOUTH);
	ASSERT_TRUE(c._direction == 3);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'f');
}

TEST(Hopper, construct)
{
	Creature c('h');
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'h');
}

TEST(Hopper, construct_with_turn_counter)
{
	Creature c('h', WEST ,0);
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'h');
}

TEST(Hopper, construct_without_turn_counter)
{
	Creature c('h', NORTH);
	ASSERT_TRUE(c._direction == NORTH);
	ASSERT_TRUE(c._direction == 1);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'h');
}

TEST(Trap, construct)
{
	Creature c('t');
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 't');
}

TEST(Trap, construct_with_turn_counter)
{
	Creature c('t', WEST, 0);
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 't');
}

TEST(Trap, construct_without_turn_counter)
{
	Creature c('t', NORTH);
	ASSERT_TRUE(c._direction == NORTH);
	ASSERT_TRUE(c._direction == 1);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 't');
}

TEST(Rover, construct)
{
	Creature c('r');
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'r');
}

TEST(Rover, construct_with_turn_counter)
{
	Creature c('r', WEST, 0);
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'r');
}

TEST(Rover, construct_without_turn_counter)
{
	Creature c('r', NORTH);
	ASSERT_TRUE(c._direction == NORTH);
	ASSERT_TRUE(c._direction == 1);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'r');
}

TEST(Best, construct)
{
	Creature c('b');
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'b');
}

TEST(Best, construct_with_turn_counter)
{
	Creature c('b', WEST, 0);
	ASSERT_TRUE(c._direction == WEST);
	ASSERT_TRUE(c._direction == 0);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'b');
}

TEST(Best, construct_without_turn_counter)
{
	Creature c('b', NORTH);
	ASSERT_TRUE(c._direction == NORTH);
	ASSERT_TRUE(c._direction == 1);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._species == 'b');
}

// --------------------
// Creatures if_enemy()
// --------------------
TEST(Food, if_enemy_when_same_species)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy(c._species, 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Food, if_enemy_when_enemy)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('t', 2);
	ASSERT_TRUE(c._program_counter == 2);
}

TEST(Food, if_enemy_when_empty)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('.', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Food, if_enemy_when_wall)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('w', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_enemy_when_same_species)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy(c._species, 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_enemy_when_enemy)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('f', 2);
	ASSERT_TRUE(c._program_counter == 2);
}

TEST(Trap, if_enemy_when_empty)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('.', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_enemy_when_wall)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('w', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_enemy_when_same_species)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy(c._species, 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_enemy_when_enemy)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('f', 2);
	ASSERT_TRUE(c._program_counter == 2);
}

TEST(Hopper, if_enemy_when_empty)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('.', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_enemy_when_wall)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('w', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_enemy_when_same_species)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy(c._species, 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_enemy_when_enemy)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('f', 2);
	ASSERT_TRUE(c._program_counter == 2);
}

TEST(Rover, if_enemy_when_empty)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('.', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_enemy_when_wall)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('w', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_enemy_when_same_species)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy(c._species, 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_enemy_when_enemy)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('f', 2);
	ASSERT_TRUE(c._program_counter == 2);
}

TEST(Best, if_enemy_when_empty)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('.', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_enemy_when_wall)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_enemy('w', 2);
	ASSERT_TRUE(c._program_counter == 1);
}

// --------------------
// Creatures if_empty()
// --------------------
TEST(Food, if_empty_when_full)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Food, if_empty_when_empty)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('.', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Hopper, if_empty_when_full)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_empty_when_empty)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('.', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Trap, if_empty_when_full)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_empty_when_empty)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('.', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Rover, if_empty_when_full)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_empty_when_empty)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('.', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Best, if_empty_when_full)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_empty_when_empty)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_empty('.', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

// -------------------
// Creatures if_wall()
// -------------------
TEST(Food, if_wall_when_empty)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('.', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Food, if_wall_when_wall)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('w', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Food, if_wall_when_creature)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('t', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_wall_when_empty)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('.', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, if_wall_when_wall)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('w', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Hopper, if_wall_when_creature)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_wall_when_empty)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('.', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Trap, if_wall_when_wall)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('w', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Trap, if_wall_when_creature)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_wall_when_empty)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('.', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Rover, if_wall_when_wall)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('w', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Rover, if_wall_when_creature)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_wall_when_empty)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('.', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

TEST(Best, if_wall_when_wall)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('w', 10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Best, if_wall_when_creature)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_wall('f', 10);
	ASSERT_TRUE(c._program_counter == 1);
}

// -----------------
// Creatures if_rand
// -----------------
TEST(Food, if_rand)
{
	srand(0);
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_rand(10);
	ASSERT_TRUE(c._program_counter == 10);
	c.if_rand(20);
	ASSERT_TRUE(c._program_counter == 11);
	c.if_rand(30);
	ASSERT_TRUE(c._program_counter == 30);
}

TEST(Trap, if_rand)
{
	srand(0);
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_rand(10);
	ASSERT_TRUE(c._program_counter == 10);
	c.if_rand(20);
	ASSERT_TRUE(c._program_counter == 11);
	c.if_rand(30);
	ASSERT_TRUE(c._program_counter == 30);
}

TEST(Hopper, if_rand)
{
	srand(0);
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_rand(10);
	ASSERT_TRUE(c._program_counter == 10);
	c.if_rand(20);
	ASSERT_TRUE(c._program_counter == 11);
	c.if_rand(30);
	ASSERT_TRUE(c._program_counter == 30);
}

TEST(Rover, if_rand)
{
	srand(0);
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_rand(10);
	ASSERT_TRUE(c._program_counter == 10);
	c.if_rand(20);
	ASSERT_TRUE(c._program_counter == 11);
	c.if_rand(30);
	ASSERT_TRUE(c._program_counter == 30);
}

TEST(Best, if_rand)
{
	srand(0);
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.if_rand(10);
	ASSERT_TRUE(c._program_counter == 10);
	c.if_rand(20);
	ASSERT_TRUE(c._program_counter == 11);
	c.if_rand(30);
	ASSERT_TRUE(c._program_counter == 30);
}

// --------------
// Creatures go()
// --------------
TEST(Food, go_to_10)
{
	Creature c('f');
	ASSERT_TRUE(c._program_counter == 0);
	c.go(10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Hopper, go_to_10)
{
	Creature c('h');
	ASSERT_TRUE(c._program_counter == 0);
	c.go(10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Trap, go_to_10)
{
	Creature c('t');
	ASSERT_TRUE(c._program_counter == 0);
	c.go(10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Rover, go_to_10)
{
	Creature c('r');
	ASSERT_TRUE(c._program_counter == 0);
	c.go(10);
	ASSERT_TRUE(c._program_counter == 10);
}

TEST(Best, go_to_10)
{
	Creature c('b');
	ASSERT_TRUE(c._program_counter == 0);
	c.go(10);
	ASSERT_TRUE(c._program_counter == 10);
}

// --------------------
// Creature turn_left()
// --------------------
TEST(Creature, turn_left_4_times)
{
	Creature c('t');
	ASSERT_TRUE(c._direction == WEST);
	c.turn_left();
	ASSERT_TRUE(c._direction == SOUTH);
	c.turn_left();
	ASSERT_TRUE(c._direction == EAST);
	c.turn_left();
	ASSERT_TRUE(c._direction == NORTH);
	c.turn_left();
	ASSERT_TRUE(c._direction == WEST);
}

// ---------------------
// Creature turn_right()
// ---------------------
TEST(Creature, turn_right_4_times)
{
	Creature c('r');
	ASSERT_TRUE(c._direction == WEST);
	c.turn_right();
	ASSERT_TRUE(c._direction == NORTH);
	c.turn_right();
	ASSERT_TRUE(c._direction == EAST);
	c.turn_right();
	ASSERT_TRUE(c._direction == SOUTH);
	c.turn_right();
	ASSERT_TRUE(c._direction == WEST);
}


// -----------------------------
// Creatures operator<< override 
// -----------------------------
TEST(Food, operator_override)
{
	Creature c('f', NORTH);
	std::ostringstream w;
	w << c;
	ASSERT_TRUE(w.str() == "f");
}

TEST(Hopper, operator_override)
{
	Creature c('h', NORTH);
	std::ostringstream w;
	w << c;
	ASSERT_TRUE(w.str() == "h");
}

TEST(Trap, operator_override)
{
	Creature c('t', NORTH);
	std::ostringstream w;
	w << c;
	ASSERT_TRUE(w.str() == "t");
}

TEST(Rover, operator_override)
{
	Creature c('r', NORTH);
	std::ostringstream w;
	w << c;
	ASSERT_TRUE(w.str() == "r");
}

TEST(Best, operator_override)
{
	Creature c('b', NORTH);
	std::ostringstream w;
	w << c;
	ASSERT_TRUE(w.str() == "b");
}

// --------------------------
// Creature food_instructions
// --------------------------
TEST(Food, food_instructions_when_move_is_valid)
{
    Creature c('f');
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.food_instructions();
    ASSERT_TRUE(c._direction == SOUTH);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 1);
}

TEST(Food, food_instructions_multiple_times)
{
    Creature c('f');
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.food_instructions();
    ASSERT_TRUE(c._direction == SOUTH);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 1);
    action = c.food_instructions();
    ASSERT_TRUE(c._direction == EAST);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 2);
    ASSERT_TRUE(c._program_counter == 1);
}

// ----------------------------
// Creature hopper_instructions
// ----------------------------
TEST(Hopper, hopper_instructions_when_move_is_valid)
{
    Creature c('h');
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.hopper_instructions();
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == HOP);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 1);
}

TEST(Hopper, hopper_instructions_multiple_times)
{
    Creature c('h');
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.hopper_instructions();
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == HOP);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 1);
    action = c.hopper_instructions();
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == HOP);
    ASSERT_TRUE(c._turn_counter == 2);
    ASSERT_TRUE(c._program_counter == 1);
}

// --------------------------
// Creature trap_instructions
// --------------------------
TEST(Trap, trap_instructions_when_empty)
{
	Creature c('t');
    char border[4] = {'.'};
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.trap_instructions(border);
    ASSERT_TRUE(c._direction == SOUTH);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 2);
}

TEST(Trap, trap_instructions_with_enemy)
{
	Creature c('t');
    char border[4] = {'f'};
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.trap_instructions(border);
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == INFECT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 4);
}

TEST(Trap, trap_instructions_multiple_times)
{
	Creature c('t');
    char border[4] = {'.'};
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.trap_instructions(border);
    ASSERT_TRUE(c._direction == SOUTH);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 2);
    border[0] = 'f';
    action = c.trap_instructions(border);
    ASSERT_TRUE(c._direction == SOUTH);
    ASSERT_TRUE(action == INFECT);
    ASSERT_TRUE(c._turn_counter == 2);
    ASSERT_TRUE(c._program_counter == 4);
}

// ---------------------------
// Creature rover_instructions
// ---------------------------
TEST(Rover, rover_instructions_when_empty)
{
	Creature c('r');
    char border[4] = {'.'};
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.rover_instructions(border);
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == HOP);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 8);	
}

TEST(Rover, rover_instructions_with_enemy)
{
	Creature c('r');
    char border[4] = {'f'};
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.rover_instructions(border);
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == INFECT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 10);
}

TEST(Rover, rover_instructions_when_rand)
{
	srand(0);
	Creature c('r');
	char border[4] = {'w', 'r'};
	ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(c._turn_counter == 0);
    action_enum action = c.rover_instructions(border);
    ASSERT_TRUE(c._direction == NORTH);
    ASSERT_TRUE(action == RIGHT);
    ASSERT_TRUE(c._turn_counter == 1);
    ASSERT_TRUE(c._program_counter == 6);
    action = c.rover_instructions(border);
    std::cout << action << std::endl;
    ASSERT_TRUE(c._direction == WEST);
    ASSERT_TRUE(action == LEFT);
    ASSERT_TRUE(c._turn_counter == 2);
    ASSERT_TRUE(c._program_counter == 4);
}

// ----------------------
// Creature next_action()
// ----------------------
TEST(Food, next_action_when_already_moved)
{
	Creature c('f');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(0, border, direction);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._direction == direction);
}

TEST(Food, next_action_when_valid)
{
	Creature c('f');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(1, border, direction);
	ASSERT_TRUE(action == LEFT);
	ASSERT_TRUE(c._turn_counter == 1);
	ASSERT_TRUE(c._program_counter == 1);
	ASSERT_TRUE(c._direction == direction);	
}

TEST(Hopper, next_action_when_already_moved)
{
	Creature c('h');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(0, border, direction);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._direction == direction);
}

TEST(Hopper, next_action_when_valid)
{
	Creature c('h');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(1, border, direction);
	ASSERT_TRUE(action == HOP);
	ASSERT_TRUE(c._turn_counter == 1);
	ASSERT_TRUE(c._program_counter == 1);
	ASSERT_TRUE(c._direction == direction);	
}

TEST(Trap, next_action_when_already_moved)
{
	Creature c('t');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(0, border, direction);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._direction == direction);
}

TEST(Trap, next_action_when_valid)
{
	Creature c('t');
	char border[4] = {'f', '.', '.', '.'};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(1, border, direction);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE(c._turn_counter == 1);
	ASSERT_TRUE(c._program_counter == 4);
	ASSERT_TRUE(c._direction == direction);	
}

TEST(Rover, next_action_when_already_moved)
{
	Creature c('r');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(0, border, direction);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._direction == direction);
}

TEST(Rover, next_action_when_valid)
{
	Creature c('r');
	char border[4] = {'b', '.', '.', '.'};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(1, border, direction);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE(c._turn_counter == 1);
	ASSERT_TRUE(c._program_counter == 10);
	ASSERT_TRUE(c._direction == direction);	
}

TEST(Best, next_action_when_already_moved)
{
	Creature c('b');
	char border[4] = {};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(0, border, direction);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE(c._turn_counter == 0);
	ASSERT_TRUE(c._program_counter == 0);
	ASSERT_TRUE(c._direction == direction);
}

TEST(Best, next_action_when_valid)
{
	Creature c('b');
	char border[4] = {'r', '.', '.', '.'};
	direction_enum direction;
	action_enum action;
	
	action = c.next_action(1, border, direction);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE(c._turn_counter == 1);
	ASSERT_TRUE(c._program_counter == 10);
	ASSERT_TRUE(c._direction == direction);	
}

// -----------------
// World Constructor
// -----------------
TEST(World, construct_10x10_world)
{
	World w(10, 10);
	ASSERT_TRUE(w._board.size() == 10);
	ASSERT_TRUE(w._board[0].size() == 10);
	ASSERT_TRUE(w._world_turn_counter == 0);
}

TEST(World, construct_2x3_world)
{
	World w(2, 3);
	ASSERT_TRUE(w._board.size() == 2);
	ASSERT_TRUE(w._board[0].size() == 3);
	ASSERT_TRUE(w._world_turn_counter == 0);
}

TEST(World, construct_100x1_world)
{
	World w(100, 1);
	ASSERT_TRUE(w._board.size() == 100);
	ASSERT_TRUE(w._board[0].size() == 1);
	ASSERT_TRUE(w._world_turn_counter == 0);
}

// -------------------------
// World operator<< override 
// -------------------------
TEST(World, operator_override_after_2x2_constructor)
{
	World world(2, 2);
	std::ostringstream w;
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n");
}
TEST(World, operator_override_after_1x11_constructor)
{
	World world(1, 11);
	std::ostringstream w;
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01234567890\n0 ...........\n");
}

TEST(World, operator_override_after_11x1_constructor)
{
	World world(11, 1);
	std::ostringstream w;
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  0\n0 .\n1 .\n2 .\n3 .\n4 .\n5 .\n6 .\n7 .\n8 .\n9 .\n0 .\n");
}

TEST(World, operator_override_with_data)
{
	World world(3, 3);
	Creature f('f', WEST);
	Creature h('h', NORTH, 2);
	Creature t('t', EAST, 1);
	Creature r('r', SOUTH, 10);
	Creature b('b');

	world._world_turn_counter = 10;
	world._board[0][0] = &f;
	world._board[0][2] = &h;
	world._board[1][1] = &t;
	world._board[2][0] = &r;
	world._board[2][2] = &b;
	std::ostringstream w;
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 10.\n  012\n0 f.h\n1 .t.\n2 r.b\n");
}

// --------------
// add_creature()
// --------------
TEST(World, add_creatures_with_turn_counter)
{
	World world(5, 5);
	Creature f('f', WEST, 0);
	Creature h('h', NORTH, 1);
	Creature t('t', EAST, 2);
	Creature r('r', SOUTH, 3);
	Creature b('b', WEST, 4);

	world.add_creature(f, 0, 0);
	world.add_creature(h, 1, 1);
	world.add_creature(t, 2, 2);
	world.add_creature(r, 3, 3);
	world.add_creature(b, 4, 4);

	ASSERT_TRUE((*world._board[0][0])._species == 'f');
	ASSERT_TRUE((*world._board[0][0])._direction == WEST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 0);
	ASSERT_TRUE((*world._board[0][0])._program_counter == 0);
	
	ASSERT_TRUE((*world._board[1][1])._species == 'h');
	ASSERT_TRUE((*world._board[1][1])._direction == NORTH);
	ASSERT_TRUE((*world._board[1][1])._turn_counter == 1);
	ASSERT_TRUE((*world._board[1][1])._program_counter == 0);

	ASSERT_TRUE((*world._board[2][2])._species == 't');
	ASSERT_TRUE((*world._board[2][2])._direction == EAST);
	ASSERT_TRUE((*world._board[2][2])._turn_counter == 2);
	ASSERT_TRUE((*world._board[2][2])._program_counter == 0);

	ASSERT_TRUE((*world._board[3][3])._species == 'r');
	ASSERT_TRUE((*world._board[3][3])._direction == SOUTH);
	ASSERT_TRUE((*world._board[3][3])._turn_counter == 3);
	ASSERT_TRUE((*world._board[3][3])._program_counter == 0);

	ASSERT_TRUE((*world._board[4][4])._species == 'b');
	ASSERT_TRUE((*world._board[4][4])._direction == WEST);
	ASSERT_TRUE((*world._board[4][4])._turn_counter == 4);
	ASSERT_TRUE((*world._board[4][4])._program_counter == 0);
}

TEST(World, add_creatures_without_turn_counter)
{
	World world(5, 5);
	Creature f('f', WEST);
	Creature h('h', NORTH);
	Creature t('t', EAST);
	Creature r('r', SOUTH);
	Creature b('b', WEST);

	world.add_creature(f, 0, 0);
	world.add_creature(h, 1, 1);
	world.add_creature(t, 2, 2);
	world.add_creature(r, 3, 3);
	world.add_creature(b, 4, 4);

	ASSERT_TRUE((*world._board[0][0])._species == 'f');
	ASSERT_TRUE((*world._board[0][0])._direction == WEST);
	ASSERT_TRUE((*world._board[0][0])._program_counter == 0);
	
	ASSERT_TRUE((*world._board[1][1])._species == 'h');
	ASSERT_TRUE((*world._board[1][1])._direction == NORTH);
	ASSERT_TRUE((*world._board[1][1])._program_counter == 0);

	ASSERT_TRUE((*world._board[2][2])._species == 't');
	ASSERT_TRUE((*world._board[2][2])._direction == EAST);
	ASSERT_TRUE((*world._board[2][2])._program_counter == 0);

	ASSERT_TRUE((*world._board[3][3])._species == 'r');
	ASSERT_TRUE((*world._board[3][3])._direction == SOUTH);
	ASSERT_TRUE((*world._board[3][3])._program_counter == 0);

	ASSERT_TRUE((*world._board[4][4])._species == 'b');
	ASSERT_TRUE((*world._board[4][4])._direction == WEST);
	ASSERT_TRUE((*world._board[4][4])._program_counter == 0);
}

TEST(World, add_creature_on_top_of_another)
{
	World world(1, 1);
	Creature f('f', WEST);
	Creature h('h', EAST, 2);

	world.add_creature(f, 0, 0);
	ASSERT_TRUE((*world._board[0][0])._species == 'f');
	ASSERT_TRUE((*world._board[0][0])._direction == WEST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 0);
	ASSERT_TRUE((*world._board[0][0])._program_counter == 0);

	world.add_creature(h, 0, 0);
	ASSERT_TRUE((*world._board[0][0])._species == 'h');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 2);
	ASSERT_TRUE((*world._board[0][0])._program_counter == 0);
}

TEST(World, add_creature_with_negative_i)
{
	World world(1, 1);
	Creature f('f');
	bool exception_thrown = false;

	try
	{
		world.add_creature(f, -1, 0);
	}
	catch(std::out_of_range& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);
}

TEST(World, add_creature_with_negative_j)
{
	World world(1, 1);
	Creature f('f');
	bool exception_thrown = false;

	try
	{
		world.add_creature(f, 0, -1);
	}
	catch(std::out_of_range& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);
}

TEST(World, add_creature_with_i_exceeding_size)
{
	World world(1, 1);
	Creature f('f');
	bool exception_thrown = false;

	try
	{
		world.add_creature(f, 0, 1);
	}
	catch(std::out_of_range& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);
}

TEST(World, add_creature_with_j_exceeding_size)
{
	World world(1, 1);
	Creature f('f');
	bool exception_thrown = false;

	try
	{
		world.add_creature(f, 0, 1);
	}
	catch(std::out_of_range& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);
}

// ---------------------
// World count_species()
// ---------------------
TEST(World, count_species_with_empty_world)
{
	World world(1, 1);
	size_t count = world.count_species('f');
	ASSERT_TRUE(count == 0);
}

TEST(World, count_species_when_0_of_given_species)
{
	World world(2, 2);
	Creature f('f');
	world.add_creature(f, 1, 1);
	size_t count = world.count_species('b');
	ASSERT_TRUE(count == 0);
}

TEST(World, count_species_with_muliple_species)
{
	World world(2, 2);
	Creature f('f');
	Creature b('b');
	Creature b2('b');
	world.add_creature(b, 0, 0);
	world.add_creature(b, 1, 0);
	world.add_creature(f, 1, 1);
	size_t count = world.count_species('b');
	ASSERT_TRUE(count == 2);
}

TEST(World, count_species_with_invalid_species)
{
	World world(1, 1);
	bool exception_thrown = false;

	try
	{
		world.count_species('a');
	}
	catch(std::invalid_argument& e)
	{
		exception_thrown = true;
	}
	ASSERT_TRUE(exception_thrown);	
}

// --------------------
// World build_border()
// --------------------
TEST(World, build_border_with_species)
{
	World world (10, 10);
	char border[4] = {};
	world.build_border(2, 2, border);
	ASSERT_TRUE(border[WEST] == '.');
	ASSERT_TRUE(border[NORTH] == '.');
	ASSERT_TRUE(border[EAST] == '.');
	ASSERT_TRUE(border[SOUTH] == '.');
}

TEST(World, build_border_with_walls)
{
	World world (1, 1);
	char border[4] = {};
	world.build_border(0, 0, border);
	ASSERT_TRUE(border[WEST] == 'w');
	ASSERT_TRUE(border[NORTH] == 'w');
	ASSERT_TRUE(border[EAST] == 'w');
	ASSERT_TRUE(border[SOUTH] == 'w');
}

TEST(World, build_border_with_mix)
{
	World world (2, 2);
	Creature f('f');
	world.add_creature(f, 1, 0);
	char border[4] = {};
	world.build_border(0, 0, border);
	ASSERT_TRUE(border[WEST] == 'w');
	ASSERT_TRUE(border[NORTH] == 'w');
	ASSERT_TRUE(border[EAST] == '.');
	ASSERT_TRUE(border[SOUTH] == 'f');
}

// -----------------------
// World validate_action()
// -----------------------
TEST(World, validate_action_with_nothing)
{
	World world (4, 4);
	char border[4] = {};
	std::ostringstream before;
	std::ostringstream after;
	action_enum action;
	Creature h('h', NORTH);

	world.add_creature(h, 0, 0);
	world.build_border(0, 0, border);
	before << world;
	action = world.validate_action(0, 0, NOTHING, NORTH, border);
	after << world;
	ASSERT_TRUE(before.str() == after.str());
	ASSERT_TRUE(action == NOTHING);
}

TEST(World, validate_action_with_left)
{
	World world (4, 4);
	char border[4] = {};
	std::ostringstream before;
	std::ostringstream after;
	action_enum action;
	Creature t('t', NORTH);

	world.add_creature(t, 0, 0);
	world.build_border(0, 0, border);
	before << world;
	action = world.validate_action(0, 0, LEFT, SOUTH, border);
	after << world;
	ASSERT_TRUE(before.str() == after.str());
	ASSERT_TRUE(action == NOTHING);
}

TEST(World, validate_action_with_right)
{
	World world (4, 4);
	char border[4] = {};
	std::ostringstream before;
	std::ostringstream after;
	action_enum action;
	Creature r('r', NORTH);

	world.add_creature(r, 0, 0);
	world.build_border(0, 0, border);
	before << world;
	action = world.validate_action(0, 0, RIGHT, SOUTH, border);
	after << world;
	ASSERT_TRUE(before.str() == after.str());
	ASSERT_TRUE(action == NOTHING);
}

TEST(World, validate_action_with_valid_hop)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature h('h', EAST, 10);

	world.add_creature(h, 0, 0);
	world.build_border(0, 0, border);
	action = world.validate_action(0, 0, HOP, EAST, border);
	ASSERT_TRUE(action == HOP);
	ASSERT_TRUE(world._board[0][0] == 0);
	ASSERT_TRUE((*world._board[0][1])._species == 'h');
	ASSERT_TRUE((*world._board[0][1])._direction == EAST);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 10);
}

TEST(World, validate_action_with_invalid_hop_into_wall)
{
	World world (1, 2);
	char border[4] = {};
	std::ostringstream before;
	std::ostringstream after;
	action_enum action;
	Creature h('h', EAST, 10);

	world.add_creature(h, 0, 1);
	world.build_border(0, 1, border);
	before << world;
	action = world.validate_action(0, 0, HOP, EAST, border);
	after << world;
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE((*world._board[0][1])._species == 'h');
	ASSERT_TRUE((*world._board[0][1])._direction == EAST);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 10);
	ASSERT_TRUE(before.str() == after.str());
}

TEST(World, validate_action_with_invalid_hop_into_creature)
{
	World world (1, 2);
	char border[4] = {};
	std::ostringstream before;
	std::ostringstream after;
	action_enum action;
	Creature h('h', EAST, 10);
	Creature f('f', NORTH, 20);

	world.add_creature(h, 0, 0);
	world.add_creature(f, 0, 1);
	world.build_border(0, 0, border);
	before << world;
	action = world.validate_action(0, 0, HOP, EAST, border);
	after << world;
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE((*world._board[0][0])._species == 'h');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 10);
	ASSERT_TRUE((*world._board[0][1])._species == 'f');
	ASSERT_TRUE((*world._board[0][1])._direction == NORTH);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 20);
	ASSERT_TRUE(before.str() == after.str());
}

TEST(World, validate_action_with_valid_infect)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature t('t', EAST, 10);
	Creature f('f', NORTH, 20);

	world.add_creature(t, 0, 0);
	world.add_creature(f, 0, 1);
	world.build_border(0, 0, border);
	action = world.validate_action(0, 0, INFECT, EAST, border);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE((*world._board[0][0])._species == 't');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 10);
	ASSERT_TRUE((*world._board[0][1])._species == 't');
	ASSERT_TRUE((*world._board[0][1])._direction == NORTH);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 20);
}

TEST(World, validate_action_with_invalid_infect_of_same_species)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature t('t', EAST, 10);
	Creature t2('t', NORTH, 20);

	world.add_creature(t, 0, 0);
	world.add_creature(t2, 0, 1);
	world.build_border(0, 0, border);
	action = world.validate_action(0, 0, INFECT, EAST, border);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE((*world._board[0][0])._species == 't');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 10);
	ASSERT_TRUE((*world._board[0][1])._species == 't');
	ASSERT_TRUE((*world._board[0][1])._direction == NORTH);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 20);
}

TEST(World, validate_action_with_invalid_infect_of_empty)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature t('t', EAST, 10);

	world.add_creature(t, 0, 0);
	world.build_border(0, 0, border);
	action = world.validate_action(0, 0, INFECT, EAST, border);
	ASSERT_TRUE(action == NOTHING);
	ASSERT_TRUE((*world._board[0][0])._species == 't');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 10);
	ASSERT_TRUE(world._board[0][1] == 0);
}

TEST(World, validate_action_rover_infect_best)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature r('r', EAST);
	Creature b('b', WEST, 10);

	world.add_creature(r, 0, 0);
	world.add_creature(b, 0, 1);
	world.build_border(0, 0, border);
	action = world.validate_action(0, 0, INFECT, EAST, border);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE((*world._board[0][0])._species == 'r');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 0);
	ASSERT_TRUE((*world._board[0][1])._species == 'r');
	ASSERT_TRUE((*world._board[0][1])._direction == WEST);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 10);
}

TEST(World, validate_action_best_infect_rover)
{
	World world (1, 2);
	char border[4] = {};
	action_enum action;
	Creature r('r', EAST);
	Creature b('b', WEST, 10);
	
	world.add_creature(r, 0, 0);
	world.add_creature(b, 0, 1);
	world.build_border(0, 1, border);
	action = world.validate_action(0, 1, INFECT, WEST, border);
	ASSERT_TRUE(action == INFECT);
	ASSERT_TRUE((*world._board[0][0])._species == 'b');
	ASSERT_TRUE((*world._board[0][0])._direction == EAST);
	ASSERT_TRUE((*world._board[0][0])._turn_counter == 0);
	ASSERT_TRUE((*world._board[0][1])._species == 'b');
	ASSERT_TRUE((*world._board[0][1])._direction == WEST);
	ASSERT_TRUE((*world._board[0][1])._turn_counter == 10);
}

// -----------------
// World next_turn()
// -----------------
TEST(World, next_turn_with_empty_world)
{
	World world(3, 3);
	std::ostringstream w;

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 1.\n  012\n0 ...\n1 ...\n2 ...\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 2.\n  012\n0 ...\n1 ...\n2 ...\n");
}

TEST(World, next_turn_with_multiple_hops)
{
	World world(2, 5);
	Creature h('h', EAST);
	Creature h2('h', WEST);
	std::ostringstream w;

	world.add_creature(h, 0, 0);
	world.add_creature(h2, 1, 3);

	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 h....\n1 ...h.\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 1.\n  01234\n0 .h...\n1 ..h..\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 2.\n  01234\n0 ..h..\n1 .h...\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 3.\n  01234\n0 ...h.\n1 h....\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 4.\n  01234\n0 ....h\n1 h....\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 5.\n  01234\n0 ....h\n1 h....\n");
}

TEST(World, next_turn_with_multiple_infects)
{
	World world(2, 5);
	Creature t('t', EAST);
	Creature t2('t', NORTH);
	Creature t3('t', NORTH);
	Creature f('f', SOUTH);
	Creature f2('f');
	Creature f3('f');
	std::ostringstream w;

	world.add_creature(t, 0, 0);
	world.add_creature(f, 0, 1);
	world.add_creature(f2, 0, 2);
	world.add_creature(f3, 0, 4);
	world.add_creature(t2, 1, 3);
	world.add_creature(t3, 1, 4);

	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01234\n0 tff.f\n1 ...tt\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 1.\n  01234\n0 ttf.t\n1 ...tt\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 2.\n  01234\n0 ttt.t\n1 ...tt\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 3.\n  01234\n0 ttt.t\n1 ...tt\n");
}

TEST(World, next_turn_rover_infect_best)
{
	World world (1, 2);
	Creature r('r', EAST);
	Creature b('b', WEST);
	std::ostringstream w;
	
	world.add_creature(r, 0, 0);
	world.add_creature(b, 0, 1);

	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 rb\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 1.\n  01\n0 rr\n");
}

TEST(World, next_turn_best_infect_rover)
{
	World world (1, 2);
	Creature r('r', WEST);
	Creature b('b', EAST);
	std::ostringstream w;
	
	world.add_creature(b, 0, 0);
	world.add_creature(r, 0, 1);

	w << world;
	ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 br\n");
	w.str("");

	world.next_turn();
	w << world;
	ASSERT_TRUE(w.str() == "Turn = 1.\n  01\n0 bb\n");
}
// end of file