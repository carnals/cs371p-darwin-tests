
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#include "Darwin.h"


TEST(Darwin, basic_math)
{
    ASSERT_TRUE(1+1 == 2);
}

TEST(Darwin, brain_execute_hopper)
{
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);
    int pc = 0;
    for(int i=0; i<100; i++)
      ASSERT_TRUE(hopper.execute(pc, false, false, false) == HOP);
}

TEST(Darwin, brain_execute_turner)
{
    Brain turner;
    turner.addInstruction(LEFT);
    turner.addInstruction(RIGHT);
    turner.addInstruction(INFECT);
    turner.addInstruction(GO, 0);
    int pc = 0;
    for(int i=0; i<33; i++)
    {
      ASSERT_TRUE(turner.execute(pc, false, false, false) == LEFT);
      ASSERT_TRUE(turner.execute(pc, false, false, false) == RIGHT);
      ASSERT_TRUE(turner.execute(pc, false, false, false) == INFECT);
    }
}

TEST(Darwin, brain_execute_branching)
{
    Brain brancher;
    brancher.addInstruction(IF_EMPTY,5);
    brancher.addInstruction(IF_WALL,7);
    brancher.addInstruction(IF_ENEMY,9);
    brancher.addInstruction(INFECT);
    brancher.addInstruction(GO,0);
    brancher.addInstruction(HOP);
    brancher.addInstruction(GO,0);
    brancher.addInstruction(LEFT);
    brancher.addInstruction(GO,0);
    brancher.addInstruction(RIGHT);
    brancher.addInstruction(GO,0);
    int pc = 0;
    for(int i=0; i<25; i++)
    {
      ASSERT_TRUE(brancher.execute(pc, true, false, false) == LEFT);
      ASSERT_TRUE(brancher.execute(pc, false, true, false) == RIGHT);
      ASSERT_TRUE(brancher.execute(pc, false, false, true) == HOP);
      ASSERT_TRUE(brancher.execute(pc, false, false, false) == INFECT);
    }
}

TEST(Darwin, brain_print)
{
    Brain turner('a');
    std::ostringstream w;
    turner.print(w);
    ASSERT_TRUE(w.str() == "a");
}

TEST(Darwin, brain_print_default)
{
    Brain turner;
    std::ostringstream w;
    turner.print(w);
    ASSERT_TRUE(w.str() == "?");
}

TEST(Darwin, brain_add_instruction)
{
    Brain hopper;
    hopper.addInstruction(HOP);
    int pc = 0;
    hopper.execute(pc, false, false, false);
    ASSERT_TRUE(pc == 1);
    hopper.addInstruction(HOP);
    hopper.execute(pc, false, false, false);
    ASSERT_TRUE(pc == 2);
}

TEST(Darwin, brain_add_instruction_param)
{
    Brain brancher;
    brancher.addInstruction(HOP);
    int pc = 0;
    brancher.execute(pc, false, false, false);
    ASSERT_TRUE(pc == 1);
    brancher.addInstruction(GO, 0);
    brancher.execute(pc, false, false, false);
    ASSERT_TRUE(pc == 1);
}

TEST(Darwin, brain_sanity_check_no_instr)
{
    try
    {
        Brain dumb;
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, brain_sanity_check_out_of_bounds)
{
    bool madethree = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        madethree = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madethree);
    }
}

TEST(Darwin, brain_sanity_check_bad_go)
{
    bool madethree = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(GO,500);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        madethree = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madethree);
    }
}

TEST(Darwin, brain_sanity_check_negative_go)
{
    bool madethree = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(GO,-3);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        madethree = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madethree);
    }
}

TEST(Darwin, brain_sanity_check_bad_rand)
{
    bool madethree = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(IF_RANDOM,500);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        dumb.execute(pc, true, true, true);
        madethree = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madethree);
    }
}

TEST(Darwin, brain_sanity_check_bad_if_wall_self)
{
    bool madeone = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_WALL,0);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(GO,0);
        int pc = 0;
        dumb.execute(pc, false, true, true);
        madeone = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madeone);
    }
}

TEST(Darwin, brain_sanity_check_bad_if_enemy_self)
{
    bool madeone = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_ENEMY,0);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(GO,0);
        int pc = 0;
        dumb.execute(pc, true, false, true);
        madeone = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madeone);
    }
}

TEST(Darwin, brain_sanity_check_bad_if_empty_self)
{
    bool madeone = false;
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_EMPTY,0);
        dumb.addInstruction(LEFT);
        dumb.addInstruction(GO,0);
        int pc = 0;
        dumb.execute(pc, true, true, false);
        madeone = true;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(madeone);
    }
}


TEST(Darwin, brain_sanity_check_simple_go_loop)
{
    try
    {
        Brain dumb;
        dumb.addInstruction(GO,0);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, brain_sanity_check_simple_rand_loop)
{
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(GO,0);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, brain_sanity_check_fake_rand_loop)
{
    try
    {
        Brain silly;
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(LEFT);
        int pc = 0;
        silly.execute(pc, true, true, true);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, brain_sanity_check_potential_loop)
{
    srand(0);
    for(int i = 0; i < 20; i++)
    {
        try
        {
            Brain dumb;
            dumb.addInstruction(IF_RANDOM,2);
            dumb.addInstruction(LEFT);
            dumb.addInstruction(IF_RANDOM,2);
            dumb.addInstruction(IF_RANDOM,3);
            dumb.addInstruction(IF_RANDOM,4);
            dumb.addInstruction(IF_RANDOM,2);
            dumb.addInstruction(IF_RANDOM,3);
            dumb.addInstruction(IF_RANDOM,4);
            dumb.addInstruction(GO,2);
            dumb.addInstruction(LEFT);
            int pc = 0;
            dumb.execute(pc, true, true, true);
            ASSERT_TRUE(false);
        }
        catch (std::logic_error& e)
        {
        }
    }
}

TEST(Darwin, brain_sanity_check_almost_potential_loop)
{
    try
    {
        Brain silly;
        silly.addInstruction(IF_RANDOM,2);
        silly.addInstruction(LEFT);
        silly.addInstruction(IF_RANDOM,2);
        silly.addInstruction(IF_RANDOM,3);
        silly.addInstruction(IF_RANDOM,4);
        silly.addInstruction(IF_RANDOM,2);
        silly.addInstruction(IF_RANDOM,3);
        silly.addInstruction(IF_RANDOM,0);
        silly.addInstruction(GO,2);
        silly.addInstruction(LEFT);
        int pc = 0;
        silly.execute(pc, true, true, true);
    }
    catch (std::logic_error& e)
    {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, brain_sanity_check_potential_out_of_bounds)
{
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(IF_RANDOM,0);
        dumb.addInstruction(IF_RANDOM,5);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, brain_sanity_check_long_go_loop)
{
    try
    {
        Brain dumb;
        dumb.addInstruction(GO,1);
        dumb.addInstruction(GO,2);
        dumb.addInstruction(GO,3);
        dumb.addInstruction(GO,4);
        dumb.addInstruction(GO,5);
        dumb.addInstruction(GO,6);
        dumb.addInstruction(GO,7);
        dumb.addInstruction(GO,8);
        dumb.addInstruction(GO,9);
        dumb.addInstruction(GO,10);
        dumb.addInstruction(GO,11);
        dumb.addInstruction(GO,12);
        dumb.addInstruction(GO,0);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, brain_sanity_check_long_rand_loop)
{
    try
    {
        Brain dumb;
        dumb.addInstruction(IF_RANDOM,1);
        dumb.addInstruction(IF_RANDOM,2);
        dumb.addInstruction(IF_RANDOM,3);
        dumb.addInstruction(IF_RANDOM,4);
        dumb.addInstruction(IF_RANDOM,5);
        dumb.addInstruction(IF_RANDOM,6);
        dumb.addInstruction(IF_RANDOM,7);
        dumb.addInstruction(IF_RANDOM,8);
        dumb.addInstruction(IF_RANDOM,9);
        dumb.addInstruction(IF_RANDOM,10);
        dumb.addInstruction(IF_RANDOM,11);
        dumb.addInstruction(IF_RANDOM,12);
        dumb.addInstruction(GO,0);
        dumb.addInstruction(LEFT);
        int pc = 0;
        dumb.execute(pc, true, true, true);
        ASSERT_TRUE(false);
    }
    catch (std::logic_error& e)
    {
        ;
    }
}

TEST(Darwin, creature_take_turn_hop)
{
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);
    Creature chopper(&hopper, NORTH, 0, 0);
    Creature choppertwo(&hopper, NORTH, 0, 1);
    ASSERT_TRUE(chopper.isAt(0, 0));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -1));
    chopper.takeTurn(true, NULL);
    ASSERT_TRUE(chopper.isAt(0, -1));
    chopper.takeTurn(false, &choppertwo);
    ASSERT_TRUE(chopper.isAt(0, -1));
}

TEST(Darwin, creature_take_turn_infect)
{

    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(HOP);
    hopper.addInstruction(HOP);
    hopper.addInstruction(HOP);
    hopper.addInstruction(HOP);
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain infecter;
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO,0);

    Creature chopper(&hopper, NORTH, 0, 0);
    Creature cinfecter(&infecter, NORTH, 0, 1);

    ASSERT_TRUE(chopper.isAt(0, 0));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -1));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -2));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -3));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -4));
    cinfecter.takeTurn(false, NULL);
    ASSERT_TRUE(cinfecter.isAt(0, 1));
    cinfecter.takeTurn(false, &chopper);
    ASSERT_TRUE(cinfecter.isAt(0, 1));
    chopper.takeTurn(false, NULL);
    ASSERT_TRUE(chopper.isAt(0, -4));
}

TEST(Darwin, creature_take_turn_pc)
{
    Brain looker;
    looker.addInstruction(HOP);
    looker.addInstruction(LEFT);
    looker.addInstruction(LEFT);
    looker.addInstruction(HOP);
    looker.addInstruction(RIGHT);
    looker.addInstruction(INFECT);
    looker.addInstruction(INFECT);
    looker.addInstruction(HOP);
    Creature clooker(&looker, NORTH, 0, 0);
    
    ASSERT_TRUE(clooker.isAt(0, 0));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, -1));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, -1));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, -1));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, 0));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, 0));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, 0));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(0, 0));
    clooker.takeTurn(false, NULL);
    ASSERT_TRUE(clooker.isAt(-1, 0));
}

TEST(Darwin, creature_is_enemy)
{
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);
    Brain infecter;
    infecter.addInstruction(IF_ENEMY,4);
    infecter.addInstruction(IF_EMPTY,6);
    infecter.addInstruction(RIGHT);
    infecter.addInstruction(GO,0);
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO,0);
    infecter.addInstruction(HOP);
    Creature chopper(&hopper, NORTH, 0, 0);
    Creature cinfector(&infecter, NORTH, 0, 1);

    ASSERT_TRUE(cinfector.isAt(0, 1));
    cinfector.takeTurn(false, &chopper);
    ASSERT_TRUE(cinfector.isAt(0, 1));
}

TEST(Darwin, creature_is_enemy_ally)
{
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);
    Brain infecter;
    infecter.addInstruction(IF_ENEMY,4);
    infecter.addInstruction(IF_EMPTY,6);
    infecter.addInstruction(RIGHT);
    infecter.addInstruction(GO,0);
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO,0);
    infecter.addInstruction(HOP);
    Creature chopper(&hopper, NORTH, 0, 0);
    Creature cinfector(&infecter, NORTH, 0, 1);

    ASSERT_TRUE(cinfector.isAt(0, 1));
    cinfector.takeTurn(false, &chopper);
    ASSERT_TRUE(cinfector.isAt(0, 1));
    cinfector.takeTurn(false, &chopper);
    ASSERT_TRUE(cinfector.isAt(0, 1));
    cinfector.takeTurn(false, NULL);
    ASSERT_TRUE(cinfector.isAt(1, 1));
}

TEST(Darwin, creature_xfacing_left)
{
    Brain turner;
    turner.addInstruction(LEFT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    ASSERT_TRUE(cturner.xfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == -1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 0);
}

TEST(Darwin, creature_xfacing_right)
{
    Brain turner;
    turner.addInstruction(RIGHT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    ASSERT_TRUE(cturner.xfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == -1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.xfacing() == 0);
}

TEST(Darwin, creature_yfacing_left)
{
    Brain turner;
    turner.addInstruction(LEFT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    ASSERT_TRUE(cturner.yfacing() == -1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == -1);
}

TEST(Darwin, creature_yfacing_right)
{
    Brain turner;
    turner.addInstruction(RIGHT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    ASSERT_TRUE(cturner.yfacing() == -1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 1);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == 0);
    cturner.takeTurn(false, NULL);
    ASSERT_TRUE(cturner.yfacing() == -1);
}

TEST(Darwin, creature_print)
{
    Brain turner('b');
    turner.addInstruction(LEFT);
    turner.addInstruction(RIGHT);
    turner.addInstruction(INFECT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    std::ostringstream w;
    cturner.print(w);
    ASSERT_TRUE(w.str() == "b");
}

TEST(Darwin, creature_print_infect)
{
    Brain turner('b');
    turner.addInstruction(LEFT);
    turner.addInstruction(RIGHT);
    turner.addInstruction(INFECT);
    turner.addInstruction(GO,0);
    Creature cturner(&turner, NORTH, 0, 0);
    std::ostringstream w;
    cturner.print(w);
    ASSERT_TRUE(w.str() == "b");

    Brain infector('i');
    infector.addInstruction(INFECT);
    Creature cinfect(&infector, NORTH, 2, 2);
    cinfect.takeTurn(false, &cturner);

    std::ostringstream wtwo;
    cturner.print(wtwo);
    ASSERT_TRUE(wtwo.str() == "i");
}

TEST(Darwin, creature_is_at)
{
    Brain none('a');
    Creature c(&none, NORTH, 0, 0);
    ASSERT_TRUE(c.isAt(0, 0));
}

TEST(Darwin, creature_is_at_loc)
{
    Brain none('a');
    Creature c(&none, NORTH, 7, 4);
    ASSERT_TRUE(c.isAt(7, 4));
}

TEST(Darwin, creature_is_at_move)
{
    Brain hopper('a');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);
    Creature c(&hopper, NORTH, 0, 0);
    ASSERT_TRUE(c.isAt(0, 0));
    c.takeTurn(false, NULL);
    ASSERT_TRUE(c.isAt(0, -1));
}

TEST(Darwin, creature_compare_same)
{
    Brain hopper('a');
    Creature one(&hopper, NORTH, 0, 0);
    ASSERT_TRUE(one.compare(&one) == 0);
}

TEST(Darwin, creature_compare_same_loc)
{
    Brain hopper('a');
    Creature one(&hopper, NORTH, 0, 0);
    Creature two(&hopper, NORTH, 0, 0);
    ASSERT_TRUE(one.compare(&two) == 0);
    ASSERT_TRUE(two.compare(&one) == 0);
}

TEST(Darwin, creature_compare_diff_x)
{
    Brain hopper('a');
    Creature one(&hopper, NORTH, 0, 0);
    Creature two(&hopper, NORTH, 1, 0);
    ASSERT_TRUE(one.compare(&two) < 0);
    ASSERT_TRUE(two.compare(&one) > 0);
}

TEST(Darwin, creature_compare_diff_y)
{
    Brain hopper('a');
    Creature one(&hopper, NORTH, 0, 0);
    Creature two(&hopper, NORTH, 0, 1);
    ASSERT_TRUE(one.compare(&two) < 0);
    ASSERT_TRUE(two.compare(&one) > 0);
}

TEST(Darwin, creature_compare_diff_both)
{
    Brain hopper('a');
    Creature one(&hopper, NORTH, 7, 0);
    Creature two(&hopper, NORTH, 1, 1);
    ASSERT_TRUE(one.compare(&two) < 0);
    ASSERT_TRUE(two.compare(&one) > 0);
}

TEST(Darwin, world_takeTurns_empty)
{
    World w(20, 20);
    w.takeTurns(1);
    w.takeTurns(10);
    w.takeTurns(20);
    w.takeTurns(30000);
    for(int i = 0; i < 150; i++)
        w.takeTurns(1);
}

TEST(Darwin, world_takeTurns_hoppers)
{
    World w(10, 10);
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    w.addCreature(&hopper, 3, 3, NORTH);
    w.addCreature(&hopper, 5, 5, NORTH);
    w.addCreature(&hopper, 7, 7, SOUTH);

    w.takeTurns(1);
    w.takeTurns(10);
    w.takeTurns(20);
    w.takeTurns(3000);
    for(int i = 0; i < 150; i++)
        w.takeTurns(1);
}

TEST(Darwin, world_takeTurns_varied)
{
    World w(10, 10);
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain biter;
    biter.addInstruction(INFECT);
    biter.addInstruction(INFECT);
    biter.addInstruction(GO,0);

    Brain spinner;
    spinner.addInstruction(LEFT);
    spinner.addInstruction(GO,0);

    w.addCreature(&hopper, 3, 3, NORTH);
    w.addCreature(&hopper, 5, 5, NORTH);
    w.addCreature(&hopper, 7, 7, SOUTH);

    w.addCreature(&biter, 4, 3, NORTH);
    w.addCreature(&biter, 6, 5, NORTH);
    w.addCreature(&biter, 8, 7, SOUTH);

    w.addCreature(&spinner, 2, 3, NORTH);
    w.addCreature(&spinner, 4, 5, NORTH);
    w.addCreature(&spinner, 6, 7, SOUTH);

    w.takeTurns(1);
    w.takeTurns(10);
    w.takeTurns(20);
    w.takeTurns(3000);
    for(int i = 0; i < 150; i++)
        w.takeTurns(1);
}

TEST(Darwin, world_addcreature)
{
    World w(20, 20);
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    ASSERT_TRUE(w.addCreature(&hopper, 1, 1, NORTH));
    ASSERT_TRUE(w.addCreature(&hopper, 2, 2, NORTH));
    ASSERT_TRUE(w.addCreature(&hopper, 3, 3, NORTH));
}

TEST(Darwin, world_addCreature_obstacle)
{
    World w(20, 20);
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    ASSERT_TRUE(w.addCreature(&hopper, 3, 3, NORTH));
    ASSERT_TRUE(!w.addCreature(&hopper, 3, 3, NORTH));
    ASSERT_TRUE(!w.addCreature(&hopper, 3, 3, SOUTH));
    ASSERT_TRUE(w.addCreature(&hopper, 3, 4, NORTH));
    ASSERT_TRUE(w.addCreature(&hopper, 4, 3, NORTH));
    ASSERT_TRUE(!w.addCreature(&hopper, 3, 4, NORTH));
    ASSERT_TRUE(!w.addCreature(&hopper, 4, 3, NORTH));
}

TEST(Darwin, world_addCreature_out_of_bounds)
{
    World w(20, 20);
    Brain hopper;
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    try
    {
        ASSERT_TRUE(w.addCreature(&hopper, 30, 32, NORTH));
        ASSERT_TRUE(false);
    }
    catch(const std::out_of_range& e)
    {
    }
}

TEST(Darwin, world_print)
{
    World w(5, 5);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain infecter('i');
    infecter.addInstruction(INFECT);
    infecter.addInstruction(GO,0);

    w.addCreature(&hopper,   0, 0, NORTH);
    w.addCreature(&infecter, 2, 0, NORTH);
    w.addCreature(&hopper,   3, 0, NORTH);
    w.addCreature(&infecter, 1, 1, NORTH);
    w.addCreature(&hopper,   2, 1, NORTH);
    w.addCreature(&hopper,   3, 1, NORTH);
    w.addCreature(&infecter, 2, 2, NORTH);
    w.addCreature(&hopper,   3, 2, NORTH);
    w.addCreature(&infecter, 4, 2, NORTH);
    w.addCreature(&hopper,   0, 3, NORTH);
    w.addCreature(&infecter, 2, 3, NORTH);
    w.addCreature(&infecter, 4, 3, NORTH);
    w.addCreature(&hopper,   1, 4, NORTH);
    w.addCreature(&infecter, 3, 4, NORTH);
    w.addCreature(&hopper,   4, 4, NORTH);

    
    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01234\n0 h.ih.\n1 .ihh.\n2 ..ihi\n3 h.i.i\n4 .h.ih\n\n");
}

TEST(Darwin, world_print_moving)
{
    World w(2, 2);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    w.addCreature(&hopper, 0, 0, SOUTH);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 h.\n1 ..\n\n");
    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 ..\n1 h.\n\n");
}

TEST(Darwin, world_print_infect)
{
    World w(2, 2);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain biter('b');
    biter.addInstruction(INFECT);
    biter.addInstruction(GO,0);

    w.addCreature(&hopper, 0, 0, SOUTH);
    w.addCreature(&biter, 1, 1, WEST);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 h.\n1 .b\n\n");
    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 ..\n1 bb\n\n");
}

TEST(Darwin, world_print_add)
{
    World w(2, 2);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain biter('b');
    biter.addInstruction(INFECT);
    biter.addInstruction(GO,0);

    w.addCreature(&hopper, 0, 0, SOUTH);
    w.addCreature(&biter, 1, 1, WEST);

    std::ostringstream outone;
    w.print(outone);
    ASSERT_TRUE(outone.str() == "Turn = 0.\n  01\n0 h.\n1 .b\n\n");
    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 ..\n1 bb\n\n");
}


TEST(Darwin, world_in_bounds)
{
    World w(2, 2);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    w.addCreature(&hopper, 0, 0, NORTH);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 h.\n1 ..\n\n");
    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 h.\n1 ..\n\n");
}

TEST(Darwin, world_in_bounds_south)
{
    World w(2, 2);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    w.addCreature(&hopper, 1, 1, SOUTH);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 ..\n1 .h\n\n");
    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 ..\n1 .h\n\n");
}

TEST(Darwin, world_is_empty)
{
    World w(2, 2);

    Brain hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO,0);

    Brain turner('t');
    turner.addInstruction(RIGHT);
    turner.addInstruction(HOP);

    w.addCreature(&turner, 0, 0, NORTH);
    w.addCreature(&hopper, 1, 0, NORTH);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  01\n0 th\n1 ..\n\n");

    w.takeTurns(1);    
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  01\n0 th\n1 ..\n\n");

    w.takeTurns(1);
    std::ostringstream outthree;
    w.print(outthree);
    ASSERT_TRUE(outthree.str() == "Turn = 2.\n  01\n0 th\n1 ..\n\n");
}

TEST(Darwin, world_sort_creatures)
{
    World w(3, 2);

    Brain a('A');
    Brain b('B');
    a.addInstruction(INFECT);
    b.addInstruction(INFECT);

    w.addCreature(&a, 0, 0, EAST);
    w.addCreature(&b, 1, 0, WEST);
    w.addCreature(&b, 2, 1, NORTH);
    w.addCreature(&a, 2, 0, SOUTH);

    std::ostringstream out;
    w.print(out);
    ASSERT_TRUE(out.str() == "Turn = 0.\n  012\n0 ABA\n1 ..B\n\n");

    w.takeTurns(1);
    std::ostringstream outtwo;
    w.print(outtwo);
    ASSERT_TRUE(outtwo.str() == "Turn = 1.\n  012\n0 AAA\n1 ..A\n\n");
}
