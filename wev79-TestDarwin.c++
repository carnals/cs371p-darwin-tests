
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#define private public

#include "Darwin.h"

using namespace std;


TEST(DarwinsWorld, print_4x4){
    ostringstream stream;
    DarwinsWorld<4,4> d;
    d.print(stream);

    ASSERT_TRUE(stream.str() == "  0123\n0 ....\n1 ....\n2 ....\n3 ....\n\n");
}

TEST(DarwinsWorld, print_3x5){
    ostringstream stream;
    DarwinsWorld<3,5> d;
    d.print(stream);
    ASSERT_TRUE(stream.str() == "  01234\n0 .....\n1 .....\n2 .....\n\n");
}

TEST(DarwinsWorld, print_1x6){
    ostringstream stream;
    DarwinsWorld<1,6> d;
    d.print(stream);
    ASSERT_TRUE(stream.str() == "  012345\n0 ......\n\n");	
}

TEST(DarwinsWorld, AddCreature1){
	ostringstream stream;
	Species food('f');
        food.addInstruction(actions::left);
        food.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature food1(food, directions::east);
        d.addCreature(food1, 1, 1);
	
	d.print(stream);
	ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'f');
    ASSERT_EQ(d.map[1][1].m_direction, directions::east);
    ASSERT_TRUE(stream.str() == "  0123\n0 ....\n1 .f..\n2 ....\n3 ....\n\n");
} 
TEST(DarwinsWorld, AddCreature2){
    ostringstream stream;
    Species hop('h');
        hop.addInstruction(actions::hop);
        hop.addInstruction(actions::go, 0);
    Species food('f');
        food.addInstruction(actions::left);
        food.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature hop1(hop, directions::north);
        d.addCreature(hop1, 1, 1);
        Creature food1(food, directions::south);
        d.addCreature(food1, 2, 1);
    
    d.print(stream);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][1].m_direction, directions::north);
    ASSERT_EQ(d.map[2][1].m_species.m_symbol, 'f');
    ASSERT_EQ(d.map[2][1].m_direction, directions::south);
    ASSERT_TRUE(stream.str() == "  0123\n0 ....\n1 .h..\n2 .f..\n3 ....\n\n");
} 
TEST(DarwinsWorld, AddCreature3){
    ostringstream stream;
    Species hop('h');
        hop.addInstruction(actions::hop);
        hop.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature hop1(hop, directions::east);
        d.addCreature(hop1, 1, 1);
    
    d.print(stream);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][1].m_direction, directions::east);
    ASSERT_TRUE(stream.str() == "  0123\n0 ....\n1 .h..\n2 ....\n3 ....\n\n");

} 
TEST(DarwinsWorld, simulate){
    ostringstream stream;
    Species circle('c');
        circle.addInstruction(actions::hop);
        circle.addInstruction(actions::left);
        circle.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature circle1(circle, directions::east);
        d.addCreature(circle1, 1, 1);
    
    d.print(stream);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'c');
    ASSERT_EQ(d.map[1][1].m_direction, directions::east);
    d.simulate();
    d.print(stream);
    ASSERT_TRUE(stream.str() == "  0123\n0 ....\n1 .c..\n2 ....\n3 ....\n\n  0123\n0 ....\n1 ..c.\n2 ....\n3 ....\n\n");
} 

//-----------------------
//  TESTING SPECIES
//-----------------------

//HOP TESTS
TEST(Species_Execute, Hop1){
    Species hop('h');
        hop.addInstruction(actions::hop);
        hop.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature hop1(hop, directions::east);
        d.addCreature(hop1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, '.');
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][2].m_direction, directions::east);
    ASSERT_EQ(d.map[1][2].m_programCounter, 1);
}
TEST(Species_Execute, Hop2){
    Species hop('h');
        hop.addInstruction(actions::hop);
        hop.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature hop1(hop, directions::east);
        d.addCreature(hop1, 1, 3);

    d.map[1][3].execute(nullptr);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][3].m_direction, directions::east);
    ASSERT_EQ(d.map[1][3].m_programCounter, 1);
}
TEST(Species_Execute, Hop3){
    Species hop('h');
        hop.addInstruction(actions::hop);
        hop.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature hop1(hop, directions::east);
        d.addCreature(hop1, 1, 2);
        Creature hop2(hop, directions::south);
        d.addCreature(hop2, 1, 3);

    d.map[1][2].execute(&d.map[1][3]);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][3].m_direction, directions::south);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'h');
    ASSERT_EQ(d.map[1][2].m_direction, directions::east);
    ASSERT_EQ(d.map[1][2].m_programCounter, 1);
}
//LEFT TESTS
TEST(Species_Execute, Left1){
    Species left('L');
        left.addInstruction(actions::left);
        left.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature left1(left, directions::east);
        d.addCreature(left1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'L');
    ASSERT_EQ(d.map[1][1].m_direction, directions::north);
    ASSERT_EQ(d.map[1][1].m_programCounter, 1);
}
//RIGHT TESTS
TEST(Species_Execute, Right1){
    Species right('R');
        right.addInstruction(actions::right);
        right.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature right1(right, directions::east);
        d.addCreature(right1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'R');
    ASSERT_EQ(d.map[1][1].m_direction, directions::south);
    ASSERT_EQ(d.map[1][1].m_programCounter, 1);
}

//infect TESTS
TEST(Species_Execute, Infect1){
    Species infect('I');
        infect.addInstruction(actions::infect);
        infect.addInstruction(actions::go, 0);
    Species food('f');
        food.addInstruction(actions::left);
        food.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature infect1(infect, directions::east);
        d.addCreature(infect1, 1, 1);
        Creature food1(food, directions::south);
        d.addCreature(food1, 1, 2);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][1].m_direction, directions::east);
    ASSERT_EQ(d.map[1][1].m_programCounter, 1);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][2].m_direction, directions::south);
    ASSERT_EQ(d.map[1][2].m_programCounter, 0);
}
TEST(Species_Execute, Infect2){
    Species infect('I');
        infect.addInstruction(actions::infect);
        infect.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature infect1(infect, directions::east);
        d.addCreature(infect1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][1].m_direction, directions::east);
    ASSERT_EQ(d.map[1][1].m_programCounter, 1);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
}
TEST(Species_Execute, Infect3){
    Species infect('I');
        infect.addInstruction(actions::infect);
        infect.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature infect1(infect, directions::east);
        d.addCreature(infect1, 1, 3);

    d.map[1][3].execute(nullptr);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][3].m_direction, directions::east);
    ASSERT_EQ(d.map[1][3].m_programCounter, 1);
}
TEST(Species_Execute, Infect4){
    Species infect('I');
        infect.addInstruction(actions::infect);
        infect.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature infect1(infect, directions::east);
        d.addCreature(infect1, 1, 2);
        Creature infect2(infect, directions::west);
        d.addCreature(infect2, 1, 3);

    d.map[1][2].execute(&d.map[1][3]);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][2].m_direction, directions::east);
    ASSERT_EQ(d.map[1][2].m_programCounter, 1);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'I');
    ASSERT_EQ(d.map[1][3].m_direction, directions::west);
    ASSERT_EQ(d.map[1][3].m_programCounter, 0);
}

//if_empty test
TEST(Species_Execute, If_empty1){
    Species ifempty('e');
        ifempty.addInstruction(actions::if_empty, 3);
        ifempty.addInstruction(actions::left);
        ifempty.addInstruction(actions::go, 0);
        ifempty.addInstruction(actions::right);
        ifempty.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifempty1(ifempty, directions::east);
        d.addCreature(ifempty1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][1].m_programCounter, 4);
    ASSERT_EQ(d.map[1][1].m_direction, directions::south);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
}
TEST(Species_Execute, If_empty2){
    Species ifempty('e');
        ifempty.addInstruction(actions::if_empty, 3);
        ifempty.addInstruction(actions::left);
        ifempty.addInstruction(actions::go, 0);
        ifempty.addInstruction(actions::right);
        ifempty.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifempty1(ifempty, directions::east);
        d.addCreature(ifempty1, 1, 1);
        Creature ifempty2(ifempty, directions::east);
        d.addCreature(ifempty2, 1, 2);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][1].m_programCounter, 2);
    ASSERT_EQ(d.map[1][1].m_direction, directions::north);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'e');
}
TEST(Species_Execute, If_empty3){
    Species ifempty('e');
        ifempty.addInstruction(actions::if_empty, 3);
        ifempty.addInstruction(actions::left);
        ifempty.addInstruction(actions::go, 0);
        ifempty.addInstruction(actions::right);
        ifempty.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifempty1(ifempty, directions::east);
        d.addCreature(ifempty1, 1, 3);

    d.map[1][3].execute(nullptr);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][3].m_direction, directions::north);
    ASSERT_EQ(d.map[1][3].m_programCounter, 2);
}

//if wall TESTS
TEST(Species_Execute, If_wall1){
    Species ifwall('w');
        ifwall.addInstruction(actions::if_wall, 3);
        ifwall.addInstruction(actions::left);
        ifwall.addInstruction(actions::go, 0);
        ifwall.addInstruction(actions::right);
        ifwall.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifwall1(ifwall, directions::east);
        d.addCreature(ifwall1, 1, 3);

    d.map[1][3].execute(nullptr);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'w');
    ASSERT_EQ(d.map[1][3].m_direction, directions::south);
    ASSERT_EQ(d.map[1][3].m_programCounter, 4);
}
TEST(Species_Execute, If_wall2){
    Species ifwall('w');
        ifwall.addInstruction(actions::if_wall, 3);
        ifwall.addInstruction(actions::left);
        ifwall.addInstruction(actions::go, 0);
        ifwall.addInstruction(actions::right);
        ifwall.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifwall1(ifwall, directions::east);
        d.addCreature(ifwall1, 1, 2);

    d.map[1][2].execute(&d.map[1][3]);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'w');
    ASSERT_EQ(d.map[1][2].m_programCounter, 2);
    ASSERT_EQ(d.map[1][2].m_direction, directions::north);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, '.');
}
TEST(Species_Execute, If_wall3){
    Species ifwall('w');
        ifwall.addInstruction(actions::if_wall, 3);
        ifwall.addInstruction(actions::left);
        ifwall.addInstruction(actions::go, 0);
        ifwall.addInstruction(actions::right);
        ifwall.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifwall1(ifwall, directions::east);
        d.addCreature(ifwall1, 1, 2);
        Creature ifwall2(ifwall, directions::west);
        d.addCreature(ifwall2, 1, 3);

    d.map[1][2].execute(&d.map[1][3]);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'w');
    ASSERT_EQ(d.map[1][2].m_programCounter, 2);
    ASSERT_EQ(d.map[1][2].m_direction, directions::north);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'w');
    ASSERT_EQ(d.map[1][3].m_direction, directions::west);
}

//if enemy tests
TEST(Species_Execute, If_enemy1){
    Species ifenemy('e');
        ifenemy.addInstruction(actions::if_enemy, 3);
        ifenemy.addInstruction(actions::left);
        ifenemy.addInstruction(actions::go, 0);
        ifenemy.addInstruction(actions::right);
        ifenemy.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifenemy1(ifenemy, directions::east);
        d.addCreature(ifenemy1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][1].m_programCounter, 2);
    ASSERT_EQ(d.map[1][1].m_direction, directions::north);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
}
TEST(Species_Execute, If_enemy2){
    Species ifenemy('e');
        ifenemy.addInstruction(actions::if_enemy, 3);
        ifenemy.addInstruction(actions::left);
        ifenemy.addInstruction(actions::go, 0);
        ifenemy.addInstruction(actions::right);
        ifenemy.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifenemy1(ifenemy, directions::east);
        d.addCreature(ifenemy1, 1, 1);
        Creature ifenemy2(ifenemy, directions::south);
        d.addCreature(ifenemy2, 1, 2);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][1].m_programCounter, 2);
    ASSERT_EQ(d.map[1][1].m_direction, directions::north);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][2].m_direction, directions::south);
}
TEST(Species_Execute, If_enemy3){
    Species ifenemy('e');
        ifenemy.addInstruction(actions::if_enemy, 3);
        ifenemy.addInstruction(actions::left);
        ifenemy.addInstruction(actions::go, 0);
        ifenemy.addInstruction(actions::right);
        ifenemy.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifenemy1(ifenemy, directions::east);
        d.addCreature(ifenemy1, 1, 3);

    d.map[1][3].execute(nullptr);
    ASSERT_EQ(d.map[1][3].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][3].m_direction, directions::north);
    ASSERT_EQ(d.map[1][3].m_programCounter, 2);
}
TEST(Species_Execute, If_enemy4){
    Species ifenemy('e');
        ifenemy.addInstruction(actions::if_enemy, 3);
        ifenemy.addInstruction(actions::left);
        ifenemy.addInstruction(actions::go, 0);
        ifenemy.addInstruction(actions::right);
        ifenemy.addInstruction(actions::go, 0);
    Species food('f');
        food.addInstruction(actions::left);
        food.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature ifenemy1(ifenemy, directions::east);
        d.addCreature(ifenemy1, 1, 1);
        Creature food1(food, directions::west);
        d.addCreature(food1, 1, 2);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'e');
    ASSERT_EQ(d.map[1][1].m_programCounter, 4);
    ASSERT_EQ(d.map[1][1].m_direction, directions::south);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, 'f');
    ASSERT_EQ(d.map[1][2].m_direction, directions::west);
}

//go tests
TEST(Species_Execute, Go1){
    Species go('g');
        go.addInstruction(actions::go, 2);
        go.addInstruction(actions::left);
        go.addInstruction(actions::right);
        go.addInstruction(actions::go, 0);
    DarwinsWorld<4,4> d;
        Creature go1(go, directions::east);
        d.addCreature(go1, 1, 1);

    d.map[1][1].execute(&d.map[1][2]);
    ASSERT_EQ(d.map[1][1].m_species.m_symbol, 'g');
    ASSERT_EQ(d.map[1][1].m_direction, directions::south);
    ASSERT_EQ(d.map[1][1].m_programCounter, 3);
    ASSERT_EQ(d.map[1][2].m_species.m_symbol, '.');
}

//species operators
TEST(Species_Operators, NotEqualSpecies1){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);
    Species other('l');
        other.addInstruction(actions::right);
        other.addInstruction(actions::go, 0);

    ASSERT_TRUE(one != other);
}
TEST(Species_Operators, NotEqualSpecies2){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);
    Species other('l');
        other.addInstruction(actions::right);
        other.addInstruction(actions::go, 0);

    ASSERT_FALSE(one != one);
}
TEST(Species_Operators, NotEqualChar1){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);

    ASSERT_TRUE(one != 'l');
}
TEST(Species_Operators, NotEqualChar2){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);

    ASSERT_FALSE(one != 'g');
}
TEST(Species_Operators, EqualChar1){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);

    ASSERT_TRUE(one == 'g');
}
TEST(Species_Operators, EqualChar2){
    Species one('g');
        one.addInstruction(actions::right);
        one.addInstruction(actions::go, 0);

    ASSERT_FALSE(one == 'l');
}

TEST(Species_Constructors, default1){
    Species one;

    ASSERT_EQ(one.m_symbol, '.');
}
TEST(Species_Constructors, typed1){
    Species one('g');

    ASSERT_EQ(one.m_symbol, 'g');
}
TEST(Species_Constructors, typed2){
    Species one('g');

    ASSERT_NE(one.m_symbol, '.');
}

TEST(Species_General, addInstruction1){
    Species go('g');
        go.addInstruction(actions::left);

    ASSERT_EQ(go.m_instructions.size(), 1);
    ASSERT_EQ(go.m_instructions[0], actions::left);
}
TEST(Species_General, addInstruction2){
    Species go('g');
        go.addInstruction(actions::go, 1);

    ASSERT_EQ(go.m_instructions.size(), 1);
    ASSERT_EQ(go.m_instructions[0], actions::go);
    ASSERT_EQ(go.m_controlParamaters.size(), 1);
    ASSERT_EQ(go.m_controlParamaters[0], 1);
}
TEST(Species_General, addInstruction3){
    Species go('g');
        go.addInstruction(actions::left);
        go.addInstruction(actions::go, 8);

    ASSERT_EQ(go.m_instructions.size(), 2);
    ASSERT_EQ(go.m_instructions[0], actions::left);
    ASSERT_EQ(go.m_instructions[1], actions::go);
    ASSERT_EQ(go.m_controlParamaters.size(), 1);
    ASSERT_EQ(go.m_controlParamaters[1], 8);
}

//-----------------------
//  TESTING CREATURE
//-----------------------

TEST(Creature_Constructors, default1){
    // Species go('g');
    //     go.addInstruction(actions::left);
    Creature go1;

    ASSERT_EQ(go1.m_species.m_symbol, '.');
    ASSERT_EQ(go1.m_roundCounter, 0);
    ASSERT_EQ(go1.m_programCounter, 0);
    ASSERT_EQ(go1.m_direction, directions::north);
}

TEST(Creature_Constructors, typed1){
    Species go('g');
        go.addInstruction(actions::left);
    Creature go1(go, directions::west);

    ASSERT_EQ(go1.m_species.m_symbol, 'g');
    ASSERT_EQ(go1.m_roundCounter, 0);
    ASSERT_EQ(go1.m_programCounter, 0);
    ASSERT_EQ(go1.m_direction, directions::west);
}

TEST(Creature_Constructors, typed2){
    Species go('g');
        go.addInstruction(actions::left);
    Creature go1(go, directions::west);

    ASSERT_NE(go1.m_species.m_symbol, '.');
    ASSERT_NE(go1.m_direction, directions::north);
}