// ------------------------------------
// TestDarwin.c++
// Copyright (C) 2013
// Kurt E. Bixby & Alyssa N. Williams
// ------------------------------------

///--------
///includes
///--------

#include <iostream>

#include "gtest/gtest.h"
#define private public
#define protected public
#define class struct
#include "Darwin.h"

using std::endl;

/// ----------
/// TestDarwin
/// ----------



/// -------
/// Species
/// -------

/// ---------
/// op_to_int
/// ---------

TEST(Darwin, op_to_int_left)
{
	string r = "left";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 0);
}

TEST(Darwin, op_to_int_right)
{
	string r = "right";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 1);
}

TEST(Darwin, op_to_int_hop)
{
	string r = "hop";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 2);
}

TEST(Darwin, op_to_int_infect)
{
	string r = "infect";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 3);
}

TEST(Darwin, op_to_int_if_empty)
{
	string r = "if_empty";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 4);
}

TEST(Darwin, op_to_int_if_wall)
{
	string r = "if_wall";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 5);
}

TEST(Darwin, op_to_int_if_random)
{
	string r = "if_random";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 6);
}

TEST(Darwin, op_to_int_if_enemy)
{
	string r = "if_enemy";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 7);
}

TEST(Darwin, op_to_int_go)
{
	string r = "go";
	int ret = op_to_int(r);
	ASSERT_EQ(ret, 8);
}

// ------------
// constructors
// ------------

TEST(Darwin, Species_constr_default)
{
	Species def = Species();
	ASSERT_EQ(def._name, '.');
}

TEST(Darwin, Species_constr_food)
{
	Species def = Species('f');
	ASSERT_EQ(def._name, 'f');
}

TEST(Darwin, Species_constr_hopper)
{
	Species def = Species('h');
	ASSERT_EQ(def._name, 'h');
}

TEST(Darwin, Species_constr_rover)
{
	Species def = Species('r');
	ASSERT_EQ(def._name, 'r');
}

TEST(Darwin, Species_constr_trap)
{
	Species def = Species('t');
	ASSERT_EQ(def._name, 't');
}

TEST(Darwin, Species_constr_best)
{
	Species def = Species('b');
	ASSERT_EQ(def._name, 'b');
}

// ---------------
// add_instruction
// ---------------

TEST(Darwin, Species_add_instruction_control)
{
	Species spec = Species('a');
	spec.add_instruction("if_empty 2");
	spec.add_instruction("if_wall 4");
	spec.add_instruction("if_random 0");
	spec.add_instruction("if_enemy 1");
	spec.add_instruction("go 0");
	ASSERT_EQ(spec._inst[0], "if_empty 2");
	ASSERT_EQ(spec._inst[1], "if_wall 4");
	ASSERT_EQ(spec._inst[2], "if_random 0");
	ASSERT_EQ(spec._inst[3], "if_enemy 1");
	ASSERT_EQ(spec._inst[4], "go 0");
}

TEST(Darwin, Species_add_instruction_action)
{
	Species spec = Species('b');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("hop");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	ASSERT_EQ(spec._inst[0], "left");
	ASSERT_EQ(spec._inst[1], "right");
	ASSERT_EQ(spec._inst[2], "hop");
	ASSERT_EQ(spec._inst[3], "infect");
	ASSERT_EQ(spec._inst[4], "go 0");
}

TEST(Darwin, Species_add_instruction_mix_1)
{
	Species spec = Species('c');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("if_enemy 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	ASSERT_EQ(spec._inst[0], "left");
	ASSERT_EQ(spec._inst[1], "right");
	ASSERT_EQ(spec._inst[2], "if_enemy 0");
	ASSERT_EQ(spec._inst[3], "infect");
	ASSERT_EQ(spec._inst[4], "go 0");
}

TEST(Darwin, Species_add_instruction_mix_2)
{
	Species spec = Species('d');
	spec.add_instruction("left");
	spec.add_instruction("if_enemy 4");
	spec.add_instruction("hop");
	spec.add_instruction("if_empty 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	ASSERT_EQ(spec._inst[0], "left");
	ASSERT_EQ(spec._inst[1], "if_enemy 4");
	ASSERT_EQ(spec._inst[2], "hop");
	ASSERT_EQ(spec._inst[3], "if_empty 0");
	ASSERT_EQ(spec._inst[4], "infect");
	ASSERT_EQ(spec._inst[5], "go 0");
}

// ---------------
// get_instruction
// ---------------

TEST(Darwin, Species_get_instruction_control)
{
	Species spec = Species('a');
	spec.add_instruction("if_empty 2");
	spec.add_instruction("if_wall 4");
	spec.add_instruction("if_random 0");
	spec.add_instruction("if_enemy 1");
	spec.add_instruction("go 0");

	string instr0 = spec.get_instruction(0);
	ASSERT_EQ(instr0, "if_empty 2");
	string instr1 = spec.get_instruction(1);
	ASSERT_EQ(instr1, "if_wall 4");
	string instr2 = spec.get_instruction(2);
	ASSERT_EQ(instr2, "if_random 0");
	string instr3 = spec.get_instruction(3);
	ASSERT_EQ(instr3, "if_enemy 1");
	string instr4 = spec.get_instruction(4);
	ASSERT_EQ(instr4, "go 0");
}

TEST(Darwin, Species_get_instruction_action)
{
	Species spec = Species('b');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("hop");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	string instr0 = spec.get_instruction(0);
	ASSERT_EQ(instr0, "left");
	string instr1 = spec.get_instruction(1);
	ASSERT_EQ(instr1, "right");
	string instr2 = spec.get_instruction(2);
	ASSERT_EQ(instr2, "hop");
	string instr3 = spec.get_instruction(3);
	ASSERT_EQ(instr3, "infect");
	string instr4 = spec.get_instruction(4);
	ASSERT_EQ(instr4, "go 0");
}

TEST(Darwin, Species_get_instruction_mix_1)
{
	Species spec = Species('c');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("if_enemy 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	string instr0 = spec.get_instruction(0);
	ASSERT_EQ(instr0, "left");
	string instr1 = spec.get_instruction(1);
	ASSERT_EQ(instr1, "right");
	string instr2 = spec.get_instruction(2);
	ASSERT_EQ(instr2, "if_enemy 0");
	string instr3 = spec.get_instruction(3);
	ASSERT_EQ(instr3, "infect");
	string instr4 = spec.get_instruction(4);
	ASSERT_EQ(instr4, "go 0");
}

TEST(Darwin, Species_get_instruction_mix_2)
{
	Species spec = Species('d');
	spec.add_instruction("left");
	spec.add_instruction("if_enemy 4");
	spec.add_instruction("hop");
	spec.add_instruction("if_empty 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	string instr0 = spec.get_instruction(0);
	ASSERT_EQ(instr0, "left");
	string instr1 = spec.get_instruction(1);
	ASSERT_EQ(instr1, "if_enemy 4");
	string instr2 = spec.get_instruction(2);
	ASSERT_EQ(instr2, "hop");
	string instr3 = spec.get_instruction(3);
	ASSERT_EQ(instr3, "if_empty 0");
	string instr4 = spec.get_instruction(4);
	ASSERT_EQ(instr4, "infect");
	string instr5 = spec.get_instruction(5);
	ASSERT_EQ(instr5, "go 0");
}

// -----
// equal
// -----

TEST(Darwin, Species_default)
{
	Species spec1 = Species();
	Species spec2 = Species();
	bool match1 = spec1.equal(spec2);
	bool match2 = spec2.equal(spec1);
	ASSERT_EQ(spec1._name, spec2._name);
	ASSERT_TRUE(match1);
	ASSERT_TRUE(match2);
}

TEST(Darwin, Species_equal1)
{
	Species spec1 = Species('a');
	Species spec2 = Species('a');
	bool match1 = spec1.equal(spec2);
	bool match2 = spec2.equal(spec1);
	ASSERT_EQ(spec1._name, spec2._name);
	ASSERT_TRUE(match1);
	ASSERT_TRUE(match2);
}

TEST(Darwin, Species_equal2)
{
	Species spec1 = Species('a');
	Species spec2 = Species('b');
	bool match1 = spec1.equal(spec2);
	bool match2 = spec2.equal(spec1);
	ASSERT_TRUE(spec1._name != spec2._name);
	ASSERT_TRUE(!match1);
	ASSERT_TRUE(!match2);
}

/// --------
/// Creature
/// --------

/// ------------
/// constructors
/// ------------


TEST(Darwin, Creature_constr_default) {
	Creature cr1 = Creature();
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, 0);
	ASSERT_EQ(cr1._sp._name, '.');
	ASSERT_EQ(cr1._acted, true);
}

TEST(Darwin, Creature_constr_food)
{
	Species spec = Species('f');
	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, NORTH);
	ASSERT_EQ(cr1._sp._name, 'f');
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_constr_hopper)
{
	Species spec = Species('h');
	Creature cr1 = Creature(spec, WEST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, WEST);
	ASSERT_EQ(cr1._sp._name, 'h');
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_constr_rover)
{
	Species spec = Species('r');
	Creature cr1 = Creature(spec, EAST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, EAST);
	ASSERT_EQ(cr1._sp._name, 'r');
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_constr_trap)
{
	Species spec = Species('t');
	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_EQ(cr1._sp._name, 't');
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_constr_best)
{
	Species spec = Species('b');
	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, NORTH);
	ASSERT_EQ(cr1._sp._name, 'b');
	ASSERT_EQ(cr1._acted, false);
}

/// -------------
/// species_equal
/// -------------

TEST(Darwin, Creature_species_equal)
{
	Species spec1 = Species();
	Species spec2 = Species();
	Creature cr1 = Creature(spec1, NORTH);
	Creature cr2 = Creature(spec2, NORTH);
	bool match1 = cr1.species_equal(cr2);
	bool match2 = cr2.species_equal(cr1);
	ASSERT_EQ(cr1._sp._name, cr2._sp._name);
	ASSERT_TRUE(match1);
	ASSERT_TRUE(match2);
}

TEST(Darwin, Creature_species_equal1)
{
	Species spec1 = Species('a');
	Species spec2 = Species('a');
	Creature cr1 = Creature(spec1, NORTH);
	Creature cr2 = Creature(spec2, SOUTH);
	bool match1 = cr1.species_equal(cr2);
	bool match2 = cr2.species_equal(cr1);
	ASSERT_EQ(cr1._sp._name, cr2._sp._name);
	ASSERT_TRUE(match1);
	ASSERT_TRUE(match2);
}

TEST(Darwin, Creature_species_equal2)
{
	Species spec1 = Species('a');
	Species spec2 = Species('b');
	Creature cr1 = Creature(spec1, EAST);
	Creature cr2 = Creature(spec2, EAST);
	bool match1 = cr1.species_equal(cr2);
	bool match2 = cr2.species_equal(cr1);
	ASSERT_TRUE(cr1._sp._name != cr2._sp._name);
	ASSERT_TRUE(!match1);
	ASSERT_TRUE(!match2);
}

/// -------------
/// get_direction
/// -------------

TEST(Darwin, Creature_get_direction_default) {
	Creature cr1 = Creature();
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, 0);
	ASSERT_EQ(dir, 0);
}

TEST(Darwin, Creature_get_direction_food)
{
	Species spec = Species('f');
	Creature cr1 = Creature(spec, NORTH);
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, NORTH);
	ASSERT_EQ(dir, NORTH);
}

TEST(Darwin, Creature_get_direction_hopper)
{
	Species spec = Species('h');
	Creature cr1 = Creature(spec, WEST);
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, WEST);
	ASSERT_EQ(dir, WEST);
}

TEST(Darwin, Creature_get_direction_rover)
{
	Species spec = Species('r');
	Creature cr1 = Creature(spec, EAST);
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, EAST);
	ASSERT_EQ(dir, EAST);
}

TEST(Darwin, Creature_get_direction_trap)
{
	Species spec = Species('t');
	Creature cr1 = Creature(spec, SOUTH);
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_EQ(dir, SOUTH);
}

TEST(Darwin, Creature_get_direction_best)
{
	Species spec = Species('b');
	Creature cr1 = Creature(spec, NORTH);
	int dir = cr1.get_direction();
	ASSERT_EQ(cr1._dir, dir);
	ASSERT_EQ(cr1._dir, NORTH);
	ASSERT_EQ(dir, NORTH);
}

/// -------------------
/// current_instruction
/// -------------------

TEST(Darwin, Creature_current_instruction_control)
{
	Species spec = Species('a');
	spec.add_instruction("if_empty 2");
	spec.add_instruction("if_wall 4");
	spec.add_instruction("if_random 0");
	spec.add_instruction("if_enemy 1");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	string curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_empty");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_wall");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_random");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_enemy");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "go");
}

TEST(Darwin, Creature_current_instruction_action)
{
	Species spec = Species('b');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("hop");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	string curr = cr1.current_instruction();
	ASSERT_EQ(curr, "left");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "right");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "hop");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "infect");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "go");
}

TEST(Darwin, Creature_current_instruction_mix_1)
{
	Species spec = Species('c');
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("if_enemy 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	string curr = cr1.current_instruction();
	ASSERT_EQ(curr, "left");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "right");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_enemy");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "infect");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "go");
}

TEST(Darwin, Creature_current_instruction_mix_2)
{
	Species spec = Species('d');
	spec.add_instruction("left");
	spec.add_instruction("if_enemy 4");
	spec.add_instruction("hop");
	spec.add_instruction("if_empty 0");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");
	
	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	string curr = cr1.current_instruction();
	ASSERT_EQ(curr, "left");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_enemy");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "hop");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "if_empty");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "infect");
	cr1._pc++;
	curr = cr1.current_instruction();
	ASSERT_EQ(curr, "go");
}

/// ---------------
/// infect_creature
/// ---------------

TEST(Darwin, Creature_infect_creature_defaultspec)
{
	Species spec1 = Species();
	Species spec2 = Species();
	Creature cr1 = Creature(spec1, NORTH);
	Creature cr2 = Creature(spec2, NORTH);
	cr1.infect_creature(cr2);
	ASSERT_EQ(cr1._sp._name, '.');
	ASSERT_EQ(cr2._sp._name, '.');
}

TEST(Darwin, Creature_infect_creature_samespec)
{
	Species spec1 = Species('a');
	Species spec2 = Species('a');
	Creature cr1 = Creature(spec1, EAST);
	Creature cr2 = Creature(spec2, SOUTH);
	cr1._pc += 1;
	cr2._pc += 2;
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr2._pc, 2);
	cr1.infect_creature(cr2);
	ASSERT_EQ(cr1._sp._name, 'a');
	ASSERT_EQ(cr2._sp._name, 'a');
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr2._pc, 2);
}

TEST(Darwin, Creature_infect_creature_diffspec)
{
	Species spec1 = Species('a');
	Species spec2 = Species('b');
	Creature cr1 = Creature(spec1, EAST);
	Creature cr2 = Creature(spec2, EAST);
	cr1._pc += 1;
	cr2._pc += 2;
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr2._pc, 2);
	cr1.infect_creature(cr2);
	ASSERT_EQ(cr1._sp._name, 'a');
	ASSERT_EQ(cr2._sp._name, 'a');
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr2._pc, 0);
}

TEST(Darwin, Creature_infect_creature_multdiffspec)
{
	Species spec1 = Species('a');
	Species spec2 = Species('b');
	Species spec3 = Species('c');
	Creature cr1 = Creature(spec1, EAST);
	Creature cr2 = Creature(spec2, NORTH);
	Creature cr3 = Creature(spec3, SOUTH);
	cr2.infect_creature(cr1);
	ASSERT_EQ(cr1._sp._name, 'b');
	ASSERT_EQ(cr2._sp._name, 'b');
	ASSERT_EQ(cr3._sp._name, 'c');

	cr3.infect_creature(cr1);
	ASSERT_EQ(cr1._sp._name, 'c');
	ASSERT_EQ(cr2._sp._name, 'b');
	ASSERT_EQ(cr3._sp._name, 'c');

	cr1.infect_creature(cr2);
	ASSERT_EQ(cr1._sp._name, 'c');
	ASSERT_EQ(cr2._sp._name, 'c');
	ASSERT_EQ(cr3._sp._name, 'c');
}

/// ---
/// act
/// ---

TEST(Darwin, Creature_act1)
{
	Species spec = Species('a');
	spec.add_instruction("left");
	spec.add_instruction("left");
	spec.add_instruction("hop");
	spec.add_instruction("left");
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("hop");
	spec.add_instruction("infect");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, NORTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, NORTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr1._dir, WEST);

	cr1.act();
	ASSERT_EQ(cr1._pc, 2);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 4);
	ASSERT_EQ(cr1._dir, EAST);

	cr1.act();
	ASSERT_EQ(cr1._pc, 5);
	ASSERT_EQ(cr1._dir, NORTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 6);
	ASSERT_EQ(cr1._dir, EAST);

	cr1.act();
	ASSERT_EQ(cr1._pc, 7);
	ASSERT_EQ(cr1._dir, EAST);

	cr1.act();
	ASSERT_EQ(cr1._pc, 8);
	ASSERT_EQ(cr1._dir, EAST);
}

TEST(Darwin, Creature_act2)
{
	Species spec = Species('b');
	spec.add_instruction("right");
	spec.add_instruction("left");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr1._dir, WEST);

	cr1.act();
	ASSERT_EQ(cr1._pc, 2);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 4);
	ASSERT_EQ(cr1._dir, EAST);
}

TEST(Darwin, Creature_act3)
{
	Species spec = Species('c');
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 2);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_EQ(cr1._dir, SOUTH);

	cr1.act();
	ASSERT_EQ(cr1._pc, 4);
	ASSERT_EQ(cr1._dir, EAST);
}

/// -------
/// control
/// -------

TEST(Darwin, Creature_control1) 
{
	Species spec = Species('a');
	spec.add_instruction("if_enemy 3");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, WEST);
	cr1.control(true);
	ASSERT_EQ(cr1._pc, 3);
}

TEST(Darwin, Creature_control2) 
{
	Species spec = Species('b');
	spec.add_instruction("if_wall 3");
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, WEST);
	cr1.control(false);
	ASSERT_EQ(cr1._pc, 1);
}

TEST(Darwin, Creature_control3) 
{
	Species spec = Species('c');
	spec.add_instruction("if_random 2");
	spec.add_instruction("left");
	spec.add_instruction("right");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, WEST);
	cr1.control(true);
	ASSERT_EQ(cr1._pc, 2);
}

/// --------------
/// out_of_actions
/// --------------

TEST(Darwin, Creature_out_of_actions1) 
{
	Species spec = Species('a');
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, SOUTH);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.act();
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_TRUE(cr1.out_of_actions());
}

TEST(Darwin, Creature_out_of_actions2) 
{
	Species spec = Species('b');
	spec.add_instruction("if_enemy 2");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, EAST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, EAST);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.control(true);
	ASSERT_TRUE(!cr1.out_of_actions());
	ASSERT_EQ(cr1._pc, 2);
	cr1.act();
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_EQ(cr1._dir, EAST);
	ASSERT_TRUE(cr1.out_of_actions());
}

TEST(Darwin, Creature_out_of_actions3) 
{
	Species spec = Species('c');
	spec.add_instruction("if_wall 2");
	spec.add_instruction("if_enemy 3");
	spec.add_instruction("hop");
	spec.add_instruction("left");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, WEST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, WEST);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.control(false);
	ASSERT_TRUE(!cr1.out_of_actions());

	ASSERT_EQ(cr1._pc, 1);
	cr1.control(true);
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_TRUE(!cr1.out_of_actions());

	cr1.act();
	ASSERT_EQ(cr1._pc, 4);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_TRUE(cr1.out_of_actions());
}

/// -------------
/// reset_actions
/// -------------

TEST(Darwin, Creature_reset_actions1) 
{
	Species spec = Species('a');
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, SOUTH);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, SOUTH);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.act();
	ASSERT_EQ(cr1._pc, 1);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_TRUE(cr1.out_of_actions());

	cr1.reset_actions();
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_reset_actions2) 
{
	Species spec = Species('b');
	spec.add_instruction("if_enemy 2");
	spec.add_instruction("hop");
	spec.add_instruction("hop");
	spec.add_instruction("left");

	Creature cr1 = Creature(spec, EAST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, EAST);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.control(true);
	ASSERT_TRUE(!cr1.out_of_actions());
	ASSERT_EQ(cr1._pc, 2);
	cr1.act();
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_EQ(cr1._dir, EAST);
	ASSERT_TRUE(cr1.out_of_actions());

	cr1.reset_actions();
	ASSERT_EQ(cr1._acted, false);
}

TEST(Darwin, Creature_reset_actions3) 
{
	Species spec = Species('c');
	spec.add_instruction("if_wall 2");
	spec.add_instruction("if_enemy 3");
	spec.add_instruction("hop");
	spec.add_instruction("left");
	spec.add_instruction("go 0");

	Creature cr1 = Creature(spec, WEST);
	ASSERT_EQ(cr1._pc, 0);
	ASSERT_EQ(cr1._dir, WEST);

	ASSERT_TRUE(!cr1.out_of_actions());
	cr1.control(false);
	ASSERT_TRUE(!cr1.out_of_actions());

	ASSERT_EQ(cr1._pc, 1);
	cr1.control(true);
	ASSERT_EQ(cr1._pc, 3);
	ASSERT_TRUE(!cr1.out_of_actions());

	cr1.act();
	ASSERT_EQ(cr1._pc, 4);
	ASSERT_EQ(cr1._dir, SOUTH);
	ASSERT_TRUE(cr1.out_of_actions());

	cr1.reset_actions();
	ASSERT_EQ(cr1._acted, false);
}


/// ------
/// Darwin
/// ------

/// ------------
/// constructors
/// ------------

TEST(Darwin, Darwin_constr1) 
{
	Darwin d = Darwin(1, 2);
	ASSERT_EQ(d.board[0][0]._sp._name, '.');
	ASSERT_EQ(d.board[0][1]._sp._name, '.');
}

TEST(Darwin, Darwin_constr2) 
{
	Darwin d = Darwin(2, 3);
	ASSERT_EQ(d.board[0][0]._sp._name, '.');
	ASSERT_EQ(d.board[0][1]._sp._name, '.');
	ASSERT_EQ(d.board[0][2]._sp._name, '.');
	ASSERT_EQ(d.board[1][0]._sp._name, '.');
	ASSERT_EQ(d.board[1][1]._sp._name, '.');
	ASSERT_EQ(d.board[1][2]._sp._name, '.');
}

TEST(Darwin, Darwin_constr3) 
{
	Darwin d = Darwin(3, 3);
	ASSERT_EQ(d.board[0][0]._sp._name, '.');
	ASSERT_EQ(d.board[0][1]._sp._name, '.');
	ASSERT_EQ(d.board[0][2]._sp._name, '.');
	ASSERT_EQ(d.board[1][0]._sp._name, '.');
	ASSERT_EQ(d.board[1][1]._sp._name, '.');
	ASSERT_EQ(d.board[1][2]._sp._name, '.');
	ASSERT_EQ(d.board[2][0]._sp._name, '.');
	ASSERT_EQ(d.board[2][1]._sp._name, '.');
	ASSERT_EQ(d.board[2][2]._sp._name, '.');
}

/// -------
/// is_wall
/// -------

TEST(Darwin, Darwin_is_wall1)
{
	Darwin d = Darwin(1, 2);
	bool ret = d.is_wall(0, 1, NORTH);
	ASSERT_TRUE(ret);
	ret = d.is_wall(0, 1, SOUTH);
	ASSERT_TRUE(ret);
	ret = d.is_wall(0, 1, EAST);
	ASSERT_TRUE(ret);
	ret = d.is_wall(0, 1, WEST);
	ASSERT_TRUE(!ret);
}

TEST(Darwin, Darwin_is_wall2)
{
	Darwin d = Darwin(3, 3);
	bool ret = d.is_wall(2, 2, SOUTH);
	ASSERT_TRUE(ret);
	ret = d.is_wall(2, 2, EAST);
	ASSERT_TRUE(ret);
	ret = d.is_wall(2, 2, NORTH);
	ASSERT_TRUE(!ret);
	ret = d.is_wall(2, 2, WEST);
	ASSERT_TRUE(!ret);
}

TEST(Darwin, Darwin_is_wall3)
{
	Darwin d = Darwin(2, 2);
	bool ret = d.is_wall(0, 0, SOUTH);
	ASSERT_TRUE(!ret);
	ret = d.is_wall(0, 0, EAST);
	ASSERT_TRUE(!ret);
	ret = d.is_wall(0, 0, NORTH);
	ASSERT_TRUE(ret);
	ret = d.is_wall(0, 0, WEST);
	ASSERT_TRUE(ret);
}

TEST(Darwin, Darwin_is_wall4)
{
	Darwin d = Darwin(2, 2);

	Species spec = Species('a');
	Creature cr1 = Creature(spec, EAST);
	d.add_creature(cr1, 0, 0);

	bool ret = d.is_wall(1, 0, NORTH);
	ASSERT_TRUE(!ret);
	ret = d.is_wall(0, 0, EAST);
	ASSERT_TRUE(!ret);
	ret = d.is_wall(0, 0, NORTH);
	ASSERT_TRUE(ret);
	ret = d.is_wall(0, 0, WEST);
	ASSERT_TRUE(ret);
}

// -----------
// is_creature
// -----------

TEST(Darwin, Darwin_is_creature1)
{
	Darwin d = Darwin(2, 2);

	Species spec = Species('a');
	Creature cr1 = Creature(spec, NORTH);
	d.add_creature(cr1, 0, 0);

	bool ret = d.is_creature(d.board[0][0]);
	ASSERT_TRUE(ret);
	ret = d.is_creature(d.board[1][1]);
	ASSERT_TRUE(!ret);
}

TEST(Darwin, Darwin_is_creature2)
{
	Darwin d = Darwin(2, 2);

	Species spec = Species('b');
	Creature cr1 = Creature(spec, SOUTH);
	d.add_creature(cr1, 1, 1);

	bool ret = d.is_creature(d.board[1][1]);
	ASSERT_TRUE(ret);
	ret = d.is_creature(d.board[0][0]);
	ASSERT_TRUE(!ret);
}

TEST(Darwin, Darwin_is_creature3)
{
	Darwin d = Darwin(2, 2);

	Species spec = Species('c');
	Creature cr1 = Creature(spec, EAST);
	d.add_creature(cr1, 0, 1);

	bool ret = d.is_creature(d.board[0][1]);
	ASSERT_TRUE(ret);
	ret = d.is_creature(d.board[0][0]);
	ASSERT_TRUE(!ret);
}

/// --------
/// is_empty
/// --------

TEST(Darwin, Darwin_is_empty1)
{
	Darwin d = Darwin(1, 2);
	bool ret = d.is_empty(0, 1);
	ASSERT_TRUE(ret);
}

TEST(Darwin, Darwin_is_empty2)
{
	Darwin d = Darwin(3, 3);
	bool ret = d.is_empty(1, 1);
	ASSERT_TRUE(ret);

	Species spec = Species('a');
	Creature cr1 = Creature(spec, WEST);
	d.add_creature(cr1, 1, 1);
	ret = d.is_empty(1, 1);
	ASSERT_TRUE(!ret);
}

TEST(Darwin, Darwin_is_empty3)
{
	Darwin d = Darwin(5, 5);
	bool ret = d.is_empty(1, 1);
	ASSERT_TRUE(ret);

	Species spec = Species('b');
	Creature cr1 = Creature(spec, EAST);
	d.add_creature(cr1, 2, 3);
	ret = d.is_empty(2, 3);
	ASSERT_TRUE(!ret);
}

/// --------
/// is_enemy
/// --------

TEST(Darwin, Darwin_is_enemy1)
{
	Species spec1 = Species('a');
	Creature cr1 = Creature(spec1, EAST);

	Species spec2 = Species('b');
	Creature cr2 = Creature(spec2, WEST);

	Darwin d = Darwin(3, 3);
	d.add_creature(cr1, 1, 1);
	d.add_creature(cr2, 1, 2);

	bool ret = d.is_enemy(cr1, 1, 2);
	ASSERT_TRUE(ret);
}

TEST(Darwin, Darwin_is_enemy2)
{
	Species spec1 = Species('a');
	Creature cr1 = Creature(spec1, EAST);

	Species spec2 = Species('a');
	Creature cr2 = Creature(spec2, WEST);

	Darwin d = Darwin(3, 3);
	d.add_creature(cr1, 1, 1);
	d.add_creature(cr2, 1, 2);

	bool ret = d.is_enemy(cr1, 1, 2);
	ASSERT_TRUE(!ret);
}