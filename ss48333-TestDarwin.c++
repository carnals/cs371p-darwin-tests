// --------
// includes
// --------

#include <iostream> // cout, endl
// #include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#define private public
#include "Darwin.h"


// -----------
// TestDarwin
// -----------


// -----------
// Turning 
// -----------
TEST(Darwin, turn1) {
    Direction d = Direction::WEST;
    d = TurnLeft(d);
    ASSERT_TRUE(d == Direction::SOUTH);
    // South -> east
    d = TurnLeft(d);
    ASSERT_TRUE(d == Direction::EAST);
    // east -> north
    d = TurnLeft(d);
    ASSERT_TRUE(d == Direction::NORTH);
    // north -> west
    d = TurnLeft(d);
    ASSERT_TRUE(d == Direction::WEST);
    
}

TEST(Darwin, turn2) {
    Direction d = Direction::WEST;
    d = TurnRight(d);
    ASSERT_TRUE(d == Direction::NORTH);
    // South -> east
    d = TurnRight(d);
    ASSERT_TRUE(d == Direction::EAST);
    // east -> north
    d = TurnRight(d);
    ASSERT_TRUE(d == Direction::SOUTH);
    // north -> west
    d = TurnRight(d);
    ASSERT_TRUE(d == Direction::WEST);
}


// -----------
// Species 
// -----------
TEST(Darwin, species1)
{
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right .
     6: go 0 . 
     7: hop . 
     8: go 0 . 
     9: infect . 
    10: go 0 .
    */
    InstructionSet_t inst_rover;
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_ENEMY, 9));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_EMPTY, 7));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_RANDOM, 5));
    inst_rover.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::RIGHT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::HOP));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::INFECT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species rover('r', inst_rover);

    bool is_enemy = true;
    bool is_wall = false;
    bool is_empty = false;
    PC_t pc = 0; 
    rover.act(pc, is_enemy, is_empty, is_wall);
    ASSERT_TRUE(pc == 10);
    rover.act(pc, false, false, false);
    ASSERT_TRUE( (pc == 4) || (pc == 6));
}
TEST(Darwin, species2)
{
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right .
     6: go 0 . 
     7: hop . 
     8: go 0 . 
     9: infect . 
    10: go 0 .
    */
    InstructionSet_t inst_rover;
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_ENEMY, 9));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_EMPTY, 7));
    inst_rover.push_back(Instruction(PrimativeInstruction::IF_RANDOM, 5));
    inst_rover.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::RIGHT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::HOP));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    inst_rover.push_back(Instruction(PrimativeInstruction::INFECT));
    inst_rover.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species rover('r', inst_rover);

    bool is_enemy = false;
    bool is_wall = false;
    bool is_empty = true;
    PC_t pc = 0; 
    rover.act(pc, is_enemy, is_empty, is_wall);
    ASSERT_TRUE(pc == 8);
}
TEST(Darwin, species3)
{

    /*
     0: left
     1: go 0
    */
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food); 

    PC_t pc = 0;
    PrimativeInstruction inst = food.act(pc, false, false, false);
    ASSERT_TRUE(inst == PrimativeInstruction::LEFT); 
    ASSERT_TRUE(pc == 1);
    food.act(pc, true, true, true);
    ASSERT_TRUE(inst == PrimativeInstruction::LEFT); 
    ASSERT_TRUE(pc == 1);
    
}

TEST(Darwin, species_name)
{
    /*
     0: left
     1: go 0
    */
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food); 
    std::stringstream ss;
    food.print(ss);
    ASSERT_TRUE(ss.str() == "f");
}


// -----------
// CREATURE
// -----------
TEST(Darwin, Creature1)
{
    /*
     0: left
     1: go 0
    */
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food);
    Species other('o', inst_food); 
    Creature c1(&food, Direction::NORTH, 0, 0);
    Creature c2(&food, Direction::NORTH, 0, 0);
    Creature c3(&other, Direction::NORTH, 0, 0);
    ASSERT_TRUE(!c1.areEnemies(c2));
    ASSERT_TRUE(c1.areEnemies(c3)); 
}

TEST(Darwin, Creature_infection)
{
    /*
     0: left
     1: go 0
    */
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food);
    Species other('o', inst_food); 
    Creature c1(&food, Direction::NORTH, 0, 0);
    Creature c2(&food, Direction::NORTH, 0, 0);
    Creature c3(&other, Direction::NORTH, 0, 0);
    ASSERT_TRUE(!c1.areEnemies(c2));
    c2.acceptInfection(&c3);
    ASSERT_TRUE(c1.areEnemies(c2));
    
}

TEST(Darwin, Creature_position_ahead)
{
    GameController game(3, 3);

    /*
     0: hop
     1: go 0
    */
    InstructionSet_t inst_hopper;
    inst_hopper.push_back(Instruction(PrimativeInstruction::HOP));
    inst_hopper.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species hopper('h', inst_hopper); 
    
    game.addCreature(&hopper, Direction::NORTH, 0, 0);
    game.addCreature(&hopper, Direction::NORTH, 2, 2);

    uint32_t xn, yn; 
    bool is_pos = game.grid_[0][0]->position_ahead(game.grid_, &xn, &yn,
                                     0, 0);
    ASSERT_TRUE(!is_pos);

    is_pos = game.grid_[2][2]->position_ahead(game.grid_, &xn, &yn,
                                     2, 2);
    ASSERT_TRUE(yn == 1);
    ASSERT_TRUE(xn == 2);
    ASSERT_TRUE(is_pos);

}

TEST(Darwin, Creature_check_around)
{
    GameController game(3, 3);

    /*
     0: hop
     1: go 0
    */
    InstructionSet_t inst_hopper;
    inst_hopper.push_back(Instruction(PrimativeInstruction::HOP));
    inst_hopper.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species hopper('h', inst_hopper); 
    
    game.addCreature(&hopper, Direction::NORTH, 0, 0);
    game.addCreature(&hopper, Direction::NORTH, 2, 2);

    uint32_t xn, yn;
    bool is_enemy, is_wall, is_empty; 
    game.grid_[0][0]->check_around(game.grid_,
                                   is_enemy,
                                   is_wall,
                                   is_empty,
                                   xn,
                                   yn);
    ASSERT_TRUE(is_enemy == false);
    ASSERT_TRUE(is_wall == true);
    ASSERT_TRUE(is_empty == false); 


    game.grid_[2][2]->check_around(game.grid_,
                                   is_enemy,
                                   is_wall,
                                   is_empty,
                                   xn,
                                   yn);
    ASSERT_TRUE(is_enemy == false);
    ASSERT_TRUE(is_wall == false);
    ASSERT_TRUE(is_empty == true);
    



}


// ------------
// GameController
// ------------
TEST(Darwin, GameController1)
{
    GameController game(3, 3);
    InstructionSet_t inst_food;
    inst_food.push_back(Instruction(PrimativeInstruction::LEFT));
    inst_food.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species food('f', inst_food);
    game.addCreature(&food, Direction::EAST, 0, 0);
    game.addCreature(&food, Direction::WEST, 2, 2); 
    /*Turn = 0.
        012
      0 f..
      1 ...
      2 ..f
    */
    std::stringstream ss;
    ss << "Turn = 0.\n  012\n0 f..\n1 ...\n2 ..f\n\n";
    std::stringstream output; 
    game.print(output);
    ASSERT_TRUE(output.str() == ss.str());
}

TEST(Darwin, GameController2)
{
    GameController game(3, 3);

    /*
     0: hop
     1: go 0
    */
    InstructionSet_t inst_hopper;
    inst_hopper.push_back(Instruction(PrimativeInstruction::HOP));
    inst_hopper.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species hopper('h', inst_hopper); 
    
    game.addCreature(&hopper, Direction::SOUTH, 0, 0);
    game.addCreature(&hopper, Direction::NORTH, 2, 2); 
    /*Turn = 0.
        012
      0 h..
      1 ...
      2 ..h
    */
    std::stringstream ss;
    ss << "Turn = 0.\n  012\n0 h..\n1 ...\n2 ..h\n\n";
    std::stringstream output; 
    game.print(output);
    ASSERT_TRUE(output.str() == ss.str());

    game.run(5);
    ss.str("");
    output.str(""); 
    ss << "Turn = 5.\n  012\n0 ..h\n1 ...\n2 h..\n\n";
    game.print(output);
    ASSERT_TRUE(output.str() == ss.str());
    
}

TEST(Darwin, GameController3)
{
    GameController game(3, 3);

    /*
     0: hop
     1: go 0
    */
    InstructionSet_t inst_hopper;
    inst_hopper.push_back(Instruction(PrimativeInstruction::HOP));
    inst_hopper.push_back(Instruction(PrimativeInstruction::GO, 0));
    Species hopper('h', inst_hopper); 
    
    game.addCreature(&hopper, Direction::SOUTH, 0, 0);
    game.addCreature(&hopper, Direction::NORTH, 1, 0);
    game.addCreature(&hopper, Direction::NORTH, 1, 2);
    game.addCreature(&hopper, Direction::NORTH, 2, 0);
    game.addCreature(&hopper, Direction::NORTH, 2, 1);
    game.addCreature(&hopper, Direction::NORTH, 0, 1);
    game.addCreature(&hopper, Direction::NORTH, 1, 1);
    game.addCreature(&hopper, Direction::NORTH, 2, 2);
    game.addCreature(&hopper, Direction::NORTH, 0, 2);
    /*Turn = 0.
        012
      0 hhh
      1 hhh
      2 hhh
    */
    std::stringstream ss;
    ss << "Turn = 0.\n  012\n0 hhh\n1 hhh\n2 hhh\n\n";
    std::stringstream output; 
    game.print(output);
    ASSERT_TRUE(output.str() == ss.str());

    game.run(5);
    ss.str("");
    output.str(""); 
    ss << "Turn = 5.\n  012\n0 hhh\n1 hhh\n2 hhh\n\n";
    game.print(output);
    ASSERT_TRUE(output.str() == ss.str());
    
}

