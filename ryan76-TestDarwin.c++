#include "gtest/gtest.h"
#include <sstream>
#include <stdexcept>
#include <string>

#define private public
#include "Darwin.h"
#undef private

using namespace std;

// --------
// Species
// --------

TEST(Species_tests, addInstruction1){
    Species s("s");
    s.addInstruction(ACTION, HOP, 1);
    
    ASSERT_EQ(1, s.programSize());
}

TEST(Species_tests, addInstruction2){
    Species s("s");
    s.addInstruction(ACTION, LEFT, 1);
    s.addInstruction(CONTROL, go, 0);
    
    ASSERT_EQ(2, s.programSize());
}

TEST(Species_tests, addInstruction3){
    Species trap("t");
    trap.addInstruction(CONTROL, if_enemy, 3);
    trap.addInstruction(ACTION, LEFT, 2);
    trap.addInstruction(CONTROL, go, 0);
    trap.addInstruction(ACTION, INFECT, 4);
    trap.addInstruction(CONTROL, go, 0);
    
    ASSERT_EQ(5, trap.programSize());
}

// ---------
// Creature
// ---------

TEST(Creature_tests, constructor){
    Species trap("t");
    trap.addInstruction(CONTROL, if_enemy, 3);
    trap.addInstruction(ACTION, LEFT, 2);
    trap.addInstruction(CONTROL, go, 0);
    trap.addInstruction(ACTION, INFECT, 4);
    trap.addInstruction(CONTROL, go, 0);
    
    Creature t1(trap, EAST);
        
    ASSERT_EQ("t", t1.species());
}

// -------
// Darwin
// -------

