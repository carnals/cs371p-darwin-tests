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