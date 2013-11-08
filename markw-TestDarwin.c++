#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#define private public
#include "Darwin.h"

using namespace std;

class TestGrid : public Grid {
    public:
        TestGrid(SpaceContent s)
            : cr(food, N), empty_space(), creature_space(cr), wall_space(wall), sc(s), Grid(20,20)
        {}

        Space &getSpaceAhead(Creature&)
        {
            switch ( sc )
            {
                case creature:
                    return creature_space;
                case wall:
                    return wall_space;
                case nothing:
                default:
                    return empty_space;
            }
        }

        Creature cr;
        Space empty_space;
        Space creature_space;
        Space wall_space;
        SpaceContent sc;
};
class TestSpace : public Space {

};

TEST(Grid, construct){
    Grid g (3,4);
    ASSERT_EQ(g.rows,3);
    ASSERT_EQ(g.columns,4);
    ASSERT_EQ(g.spaces.size(),12);
}

TEST(Grid, getSpaceAhead_creature){
    Grid g (3,4);
    Creature c(rover, N);
    Creature d(rover, W);

    g.spaces[0] = c;
    g.spaces[1] = d;

    g.current_row = 0;
    g.current_col = 1;

    Space theSpace = g.getSpaceAhead(d);
    ASSERT_NE(&c, &theSpace.getCreature());
}

TEST(Grid, getSpaceAhead_empty){
    Grid g (3,4);
    Creature d(rover, W);

    g.spaces[1] = d;

    g.current_row = 0;
    g.current_col = 1;

    Space theSpace = g.getSpaceAhead(d);
    ASSERT_TRUE(theSpace.isEmpty());
}

TEST(Grid, getSpaceAhead_wall){
    Grid g (3,4);
    Creature d(rover, W);

    g.spaces[0] = d;

    g.current_row = 0;
    g.current_col = 0;

    Space theSpace = g.getSpaceAhead(d);
    ASSERT_TRUE(theSpace.isWall());
}

TEST(Grid, doTurn_in_spaces){
    Grid g (3,4);
    g.placeCreature(hopper, W, 0, 1);
    g.placeCreature(hopper, W, 0, 3);

    g.printGrid();
    g.doTurn();
    g.printGrid();
    ASSERT_TRUE(g.spaces[0].isCreature());
    ASSERT_TRUE(g.spaces[2].isCreature());
    Creature &d = g.spaces[0].getCreature();
    Creature &c = g.spaces[2].getCreature();
    ASSERT_TRUE(d.isSpecies(hopper));
    ASSERT_TRUE(c.isSpecies(hopper));
    ASSERT_TRUE(d.direction == W);
    ASSERT_TRUE(c.direction == W);
}

TEST(Grid, doTurn_hop_only_one_turn){
    Grid g (3,4);

    g.placeCreature(hopper, E, 0, 0);

    ASSERT_TRUE(g.spaces[0].isCreature());
    Creature& c = g.spaces[0].getCreature();
    g.printGrid();
    g.doTurn();
    g.printGrid();

    ASSERT_TRUE(g.spaces[1].isCreature());
    ASSERT_TRUE(g.spaces[1].getCreature() == c);
}

TEST(Grid, doTurn_dont_hop_into_walls){
    Grid g (3,4);
    g.placeCreature(hopper, W, 0, 0);
    Creature& c = g.spaces[0].getCreature();
    g.doTurn();
    ASSERT_TRUE(g.spaces[0].isCreature());
    Creature &c1 = g.spaces[0].getCreature();
    ASSERT_EQ(&c1, &c);
}

TEST(Grid, doTurn_hop_evacuates_old_space){
    Grid g (3,4);
    Creature c(hopper, E);

    g.spaces[0] = c;

    g.doTurn();

    ASSERT_TRUE(g.spaces[0].isEmpty());
}

class InfectorCreature : public Creature {
    public:
    InfectorCreature(SpeciesCode sc, Direction d) : Creature(sc, d), i({ICodeValue::infect})
    {}
        const Instruction& execute()
        {
            return i;
        }
        Instruction i;
};

class InfecteeCreature : public Creature {
    public:
        InfecteeCreature(SpeciesCode sc, Direction d) : Creature(sc, d), i({ICodeValue::left}), infected(false)
    {}
        Creature &operator= (const Creature& c)
        {
            infected = true;
            return *this;
        }

        const Instruction& execute()
        {
            return i;
        }
        Instruction i;
        bool infected;
};

TEST(Grid, doTurn_infect_same_species_fails){
    Grid g (3,4);
    InfectorCreature c(hopper, E);
    InfecteeCreature d(hopper, W);

    g.spaces[0] = c;
    g.spaces[1] = d;

    g.doTurn();

    ASSERT_FALSE(d.infected);
}

TEST(Grid, doTurn_infect_other_species_succeeds){
    Grid g (3,4);

    g.placeCreature(trap, E, 0, 0);
    g.placeCreature(food, W, 0, 1);

    Creature &d = g.spaces[1].getCreature();
    ASSERT_TRUE(d.isSpecies(food));
    g.printGrid();
    g.doTurn();
    g.printGrid();
    ASSERT_TRUE(d.isSpecies(trap));
}

TEST(Grid, doTurn_multiple){
    Grid g (3,4);
    g.placeCreature(hopper, W, 0, 1);
    g.placeCreature(hopper, W, 0, 3);

    g.printGrid();
    g.doTurn(5);
    g.printGrid();
    ASSERT_TRUE(g.spaces[0].isCreature());
    ASSERT_TRUE(g.spaces[1].isCreature());
    Creature &d = g.spaces[0].getCreature();
    Creature &c = g.spaces[1].getCreature();
    ASSERT_TRUE(d.isSpecies(hopper));
    ASSERT_TRUE(c.isSpecies(hopper));
    ASSERT_TRUE(d.direction == W);
    ASSERT_TRUE(c.direction == W);
}

TEST(Grid, placeCreature_1){
    Grid g (3,4);
    g.placeCreature(food, W, 0, 0);
    ASSERT_TRUE(g.spaces[0].isCreature());
    ASSERT_TRUE(g.spaces[0].getCreature().isSpecies(food));
    ASSERT_EQ(W, g.spaces[0].getCreature().direction);
}

TEST(Grid, placeCreature_same_place){
    Grid g (3,4);
    g.placeCreature(food, W, 0, 0);
    Creature& theCreature = g.spaces[0].getCreature();
    g.placeCreature(food, W, 0, 0);
    Creature& theCreatureMaybe = g.spaces[0].getCreature();
    ASSERT_EQ(&theCreature, &theCreatureMaybe);
}

TEST(Grid, placeCreature_twice){
    Grid g (3,4);
    g.placeCreature(food, W, 0, 0);
    g.placeCreature(food, W, 2, 2);
}

TEST(Grid, placeCreature_access_creature){
    Grid g (3,4);
    g.placeCreature(food, W, 0, 0);
    g.spaces[0].getCreature().pc = 0;
}

TEST(Grid, placeCreature_creature_object){
    Grid g (3,4);
    Creature c = Creature(food, W);
    g.placeCreature(c, 0, 0);
    Creature& theCreatureMaybe = g.spaces[0].getCreature();
    ASSERT_EQ(theCreatureMaybe,c);
    ASSERT_NE(&theCreatureMaybe,&c);
}

TEST(Grid, printGrid){
    Grid g (30,30);
    Creature d(hopper, W);
    Creature c(hopper, E);

    g.spaces[20] = d;
    g.spaces[89] = c;
    for (int i =0; i < 10; i++)
    {
        g.doTurn();
        g.printGrid();
    }
}

TEST(Creature, construct_pc_zero) {
    Creature c = Creature(rover, N);
    ASSERT_EQ(c.pc, 0);
}

TEST(Creature, assign_pc_same) {
    Creature c = Creature(rover, N);
    Creature d = Creature(rover, N);
    d.pc = 3;
    c = d;
    ASSERT_EQ(d.pc, 3);
    ASSERT_EQ(c.pc, 3);
}

TEST(Creature, assign_species_equal) {
    Creature c = Creature(rover, N);
    Creature d = Creature(hopper, N);
    c = d;
    ASSERT_TRUE(c.isSpecies(hopper));
}

TEST(Creature, assign_direction_same) {
    Creature c = Creature(rover, N);
    Creature d = Creature(hopper, E);
    c = d;
    ASSERT_TRUE(c.direction == E);
}

TEST(Creature, execute_action_advances_pc_by_one) {
    Creature c = Creature(hopper, N);
    int old_pc = c.pc;
    Grid g = TestGrid(nothing);
    c.execute(g);
    ASSERT_EQ(old_pc + 1, c.pc);
}

TEST(Creature, turnLeft_directions) {
    Creature c = Creature(food, N);

    ASSERT_EQ(N, c.direction);
    c.turnLeft();
    ASSERT_EQ(W, c.direction);
    c.turnLeft();
    ASSERT_EQ(S, c.direction);
    c.turnLeft();
    ASSERT_EQ(E, c.direction);
    c.turnLeft();
    ASSERT_EQ(N, c.direction);
}

TEST(Creature, turnRight_directions) {
    Creature c = Creature(food, N);

    ASSERT_EQ(N, c.direction);
    c.turnRight();
    ASSERT_EQ(E, c.direction);
    c.turnRight();
    ASSERT_EQ(S, c.direction);
    c.turnRight();
    ASSERT_EQ(W, c.direction);
    c.turnRight();
    ASSERT_EQ(N, c.direction);
}

TEST(Creature, turnRight_no_pc_change) {
    Creature c = Creature(food, N);

    int old_pc = c.pc;
    for (int i = 0; i < 4; i++)
    {
        c.turnRight();
        ASSERT_EQ(old_pc, c.pc);
    }
}

TEST(Creature, turnLeft_no_pc_change) {
    Creature c = Creature(food, N);

    int old_pc = c.pc;
    for (int i = 0; i < 4; i++)
    {
        c.turnLeft();
        ASSERT_EQ(old_pc, c.pc);
    }
}

TEST(Creature, infect_species){
    Creature f = Creature(food,N);
    Creature r = Creature(rover,W);

    r.infect(f);

    ASSERT_EQ(f.s.code(),rover);
    ASSERT_EQ(r.s.code(),rover);
}

TEST(Creature, infect_pc){
    Creature f = Creature(food,N);
    Creature r = Creature(rover,W);

    r.pc = 2;
    f.pc = 2;
    r.infect(f);

    ASSERT_EQ(f.pc,0);
    ASSERT_EQ(r.pc,2);
}

TEST(Creature, infect_direction){
    Creature f = Creature(food,N);
    Creature r = Creature(rover,W);

    r.infect(f);

    ASSERT_EQ(f.direction,N);
    ASSERT_EQ(r.direction,W);
}

TEST(Direction, addition) {
    ASSERT_EQ((N+1)%4, E);
    ASSERT_EQ((E+1)%4, S);
    ASSERT_EQ((S+1)%4, W);
}

TEST(Space, getCreature_throws_when_empty) {
    Space s = Space();
    ASSERT_THROW(s.getCreature(), creatureUnavailable);
}

TEST(Space, getCreature_assign_creature_copies) {
    Space s = Space();
    Creature c = Creature(rover, N);
    s.c = c;
    s.content = creature;
    ASSERT_NE(&c, &s.getCreature());
}

TEST(Space, assign_creature) {
    Space s = Space();
    Creature c = Creature(rover, W);
    s = c;
    ASSERT_TRUE(s.isCreature());
    Creature& c1 = s.getCreature();
    ASSERT_EQ(c1, c);
}

TEST(Species, construct_species){
    for(int i = 0; i < 5; i++){
        Species s = Species( (SpeciesCode) i);
        ASSERT_EQ(s.code(),i);
    }
}

TEST(Species, construct_species_spec){
    Species::speciesCount = 0;
    speciesSpec sc = {(SpeciesCode)0,'i',"idiot",
        {{hop},{go, 0}}};
    Species s = Species(sc);
    ASSERT_EQ(s.code(),-1);
}

TEST(Species, get_instruction){
    Species s = Species( (SpeciesCode) 0);
    Instruction i = s.getInstruction(0);
    ASSERT_EQ(i.icode,if_enemy);
    ASSERT_EQ(i.argument,9);
}