#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"
#include "Darwin.h"

// 19 functions = need 57 tests
// 9 + 13  + 28 = 50

//
// 9 instruction tests
//

TEST(Darwin, inst1) {
    Instruction i("hop");
    ASSERT_TRUE(i.id == 0);}

TEST(Darwin, inst4) {
    Instruction i("left");
    ASSERT_TRUE(i.id == 1);}
    
TEST(Darwin, inst2) {
    Instruction i("right");
    ASSERT_TRUE(i.id == 2);}
    
TEST(Darwin, inst3) {
    Instruction i("infect");
    ASSERT_TRUE(i.id == 3);}
    
TEST(Darwin, inst5) {
    Instruction i("if_empty 2");
    ASSERT_TRUE(i.id == 4);
    ASSERT_TRUE(i.jump == 2);}
    
TEST(Darwin, inst6) {
    Instruction i("if_wall 455");
    ASSERT_TRUE(i.id == 5);
    ASSERT_TRUE(i.jump == 455);}
    
TEST(Darwin, inst7) {
    Instruction i("if_random 0");
    ASSERT_TRUE(i.id == 6);
    ASSERT_TRUE(i.jump == 0);}
    
TEST(Darwin, inst8) {
    Instruction i("if_enemy 2345");
    ASSERT_TRUE(i.id == 7);
    ASSERT_TRUE(i.jump == 2345);}
    
TEST(Darwin, inst9) {
    Instruction i("go 43");
    ASSERT_TRUE(i.id == 8);
    ASSERT_TRUE(i.jump == 43);}

//
// 13 Species tests
//

TEST(Darwin, spec1) {
    Species s;
    ASSERT_TRUE(s.idchar == '_');
    s.addInstruction("go 0");
    ASSERT_TRUE(s.idchar == '_');}

TEST(Darwin, spec2) {
    Species s;
    ASSERT_TRUE(s.instructions.size() == 0);
    s.addInstruction("go 0");
    ASSERT_TRUE(s.instructions.size() == 1);}
    
TEST(Darwin, spec3) {
    Species s('a');
    ASSERT_TRUE(s.idchar == 'a');
    s.addInstruction("go 0");
    ASSERT_TRUE(s.idchar == 'a');}

TEST(Darwin, spec4) {
    Species s('a');
    ASSERT_TRUE(s.instructions.size() == 0);
    s.addInstruction("go 0");
    ASSERT_TRUE(s.instructions.size() == 1);}
    
TEST(Darwin, spec11) {
    Species s;
    s.init('@');
    ASSERT_TRUE(s.idchar == '@');
    s.addInstruction("go 0");
    ASSERT_TRUE(s.idchar == '@');}

TEST(Darwin, spec5) {
    Species s('a');
    ASSERT_TRUE(s.instructions.size() == 0);
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    s.addInstruction("go 0");
    ASSERT_TRUE(s.instructions.size() == 7);}

TEST(Darwin, spec6) {
    Species s('a');
    s.addInstruction("left");
    s.addInstruction("if_empty 2");
    s.addInstruction("go 7890786");
    ASSERT_TRUE(s.instructions[1].id == 4);
    ASSERT_TRUE(s.instructions[1].jump == 2);}

TEST(Darwin, spec7) {
    Species s('a');
    s.addInstruction("go 13415");
    ASSERT_TRUE(s.instructions[0].id == 8);
    ASSERT_TRUE(s.instructions[0].jump == 13415);}

TEST(Darwin, spec8) {
    Species s;
    s.init('&');
    ASSERT_TRUE(s.idchar == '&');
    s.addInstruction("go 0");
    ASSERT_TRUE(s.idchar == '&');}

TEST(Darwin, spec9) {
    Species s;
    s.init('^');
    ASSERT_TRUE(s.idchar == '^');
    ASSERT_TRUE(s.instructions.size() == 0);
    s.addInstruction("go 0");
    ASSERT_TRUE(s.instructions.size() == 1);}
    
TEST(Darwin, spec10) {
    Species s;
    s.init('$');
    ASSERT_TRUE(s.idchar == '$');
    s.addInstruction("go 13415");
    ASSERT_TRUE(s.instructions[0].id == 8);
    ASSERT_TRUE(s.instructions[0].jump == 13415);}

TEST(Darwin, spec12) {
    Species s;
    s.init('@');
    ASSERT_TRUE(s.idchar == '@');
    s.init('$');
    ASSERT_TRUE(s.idchar == '$');
    s.init('^');
    ASSERT_TRUE(s.idchar == '^');
    s.init('&');
    ASSERT_TRUE(s.idchar == '&');}
    
TEST(Darwin, spec13) {
    Species s;
    s.init('@');
    s.addInstruction("go 13415");
    s.init('$');
    ASSERT_TRUE(s.instructions.size() == 1);}

//
// X Creature tests
//

TEST(Darwin, creat1) {
    Creature c;
    ASSERT_TRUE(c._direction == WEST);}

TEST(Darwin, creat2) {
    Creature c;
    ASSERT_TRUE(c._species == 0);}

TEST(Darwin, creat3) {
    Creature c;
    ASSERT_TRUE(c.program_counter == 0);}

TEST(Darwin, creat4) {
    Creature c;
    ASSERT_TRUE(!c.hasStepped);}

TEST(Darwin, creat5) {
    Species s;
    Creature c(&s, EAST);
    ASSERT_TRUE(c._direction == EAST);}

TEST(Darwin, creat6) {
    Species s;
    Creature c(&s, EAST);
    ASSERT_TRUE(c._species == &s);}

TEST(Darwin, creat7) {
    Species s;
    Creature c(&s, EAST);
    ASSERT_TRUE(c.program_counter == 0);}

TEST(Darwin, creat8) {
    Species s;
    Creature c(&s, EAST);
    ASSERT_TRUE(!c.hasStepped);}

TEST(Darwin, creat9) {
    Species s1, s2;
    Creature c(&s1, EAST);
    c.infect(&s2);
    ASSERT_TRUE(c._direction == EAST);}

TEST(Darwin, creat10) {
    Species s1, s2;
    Creature c(&s1, EAST);
    c.infect(&s2);
    ASSERT_TRUE(c._species == &s2);}

TEST(Darwin, creat11) {
    Species s1, s2;
    Creature c(&s1, EAST);
    c.infect(&s2);
    ASSERT_TRUE(c.program_counter == 0);}

TEST(Darwin, creat12) {
    Species s1, s2;
    Creature c(&s1, EAST);
    c.infect(&s2);
    ASSERT_TRUE(!c.hasStepped);}

TEST(Darwin, creat13) {
    Species s;
    Creature c(&s, EAST);
    c.turnLeft();
    ASSERT_TRUE(c._direction == NORTH);}

TEST(Darwin, creat14) {
    Species s;
    Creature c(&s, NORTH);
    c.turnLeft();
    ASSERT_TRUE(c._direction == WEST);}

TEST(Darwin, creat15) {
    Species s;
    Creature c(&s, WEST);
    c.turnLeft();
    ASSERT_TRUE(c._direction == SOUTH);}

TEST(Darwin, creat16) {
    Species s;
    Creature c(&s, SOUTH);
    c.turnLeft();
    ASSERT_TRUE(c._direction == EAST);}
    
TEST(Darwin, creat17) {
    Species s;
    Creature c(&s, EAST);
    c.turnRight();
    ASSERT_TRUE(c._direction == SOUTH);}

TEST(Darwin, creat18) {
    Species s;
    Creature c(&s, SOUTH);
    c.turnRight();
    ASSERT_TRUE(c._direction == WEST);}

TEST(Darwin, creat19) {
    Species s;
    Creature c(&s, WEST);
    c.turnRight();
    ASSERT_TRUE(c._direction == NORTH);}

TEST(Darwin, creat20) {
    Species s;
    Creature c(&s, NORTH);
    c.turnRight();
    ASSERT_TRUE(c._direction == EAST);}

TEST(Darwin, creat21) {
    Species s;
    Creature c(&s, EAST);
    c.incrementPC();
    ASSERT_TRUE(c._direction == EAST);}

TEST(Darwin, creat22) {
    Species s;
    Creature c(&s, EAST);
    c.incrementPC();
    ASSERT_TRUE(c._species == &s);}

TEST(Darwin, creat23) {
    Species s;
    Creature c(&s, EAST);
    c.incrementPC();
    ASSERT_TRUE(c.program_counter == 1);}

TEST(Darwin, creat24) {
    Species s;
    Creature c(&s, EAST);
    c.incrementPC();
    ASSERT_TRUE(!c.hasStepped);}
    
TEST(Darwin, creat27) {
    Species s;
    Creature c(&s, EAST);
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    ASSERT_TRUE(c.program_counter == 10);}

TEST(Darwin, creat25) {
    Species s;
    s.addInstruction("go 4");
    
    Creature c(&s, EAST);
    
    ASSERT_TRUE(s.instructions[0].id == c.readCurrentInstruction().id);}
    
TEST(Darwin, creat26) {
    Species s;
    s.addInstruction("go 4");
    s.addInstruction("go 5");
    s.addInstruction("go 6");
    
    Creature c(&s, EAST);
    
    ASSERT_TRUE(s.instructions[0].jump == c.readCurrentInstruction().jump);
    c.incrementPC();
    ASSERT_TRUE(s.instructions[1].jump == c.readCurrentInstruction().jump);
    c.incrementPC();
    ASSERT_TRUE(s.instructions[2].jump == c.readCurrentInstruction().jump);}
    
TEST(Darwin, creat28) {
    Species s;
    s.addInstruction("go 4");
    s.addInstruction("go 5");
    s.addInstruction("go 6");
    s.addInstruction("go 4");
    s.addInstruction("go 5");
    s.addInstruction("go 6");
    s.addInstruction("go 4");
    s.addInstruction("go 5");
    s.addInstruction("hop");
    
    Creature c(&s, EAST);
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    c.incrementPC();
    ASSERT_TRUE(s.instructions[8].id == c.readCurrentInstruction().id);
    ASSERT_TRUE(s.instructions[8].id == 0);}
    
//
// X Darwin tests
//

TEST(Darwin, darw1) {
    Darwin d;
    ASSERT_TRUE(d._rows == 0);
    ASSERT_TRUE(d._cols == 0);
    ASSERT_TRUE(d.turn == 0);
    }

TEST(Darwin, darw6) {
    Darwin d;
    d.initDarwin(20, 20);
    ASSERT_TRUE(d._rows == 20);
    ASSERT_TRUE(d._cols == 20);
    ASSERT_TRUE(d.turn == 0);
    }

TEST(Darwin, darw2) {
    Darwin d;
    ASSERT_TRUE(d.turn == 0);
    d.step();
    ASSERT_TRUE(d.turn == 1);
    d.step();
    ASSERT_TRUE(d.turn == 2);
    d.step();
    ASSERT_TRUE(d.turn == 3);
    }

TEST(Darwin, darw3) {
    Darwin d(10,10);
    ASSERT_TRUE(d._rows == 10);
    ASSERT_TRUE(d._cols == 10);
    }

TEST(Darwin, darw4) {
    Species s;
    s.addInstruction("go 0");
    
    Creature c(&s, EAST);
    
    Darwin d(10,10);
    d.addCreature(&c, 0, 0);
    
    ASSERT_TRUE(d.grid[0][0]._creature == &c);
    }

TEST(Darwin, darw5) {
    Species s;
    s.addInstruction("hop");
    
    Creature c(&s, EAST);
    
    Darwin d(10,10);
    d.addCreature(&c, 0, 0);
    d.step();
    
    ASSERT_TRUE(d.grid[0][0]._creature != &c);
    ASSERT_TRUE(d.grid[0][0].isEmpty);
    ASSERT_TRUE(d.grid[0][1]._creature == &c);
    }

TEST(Darwin, darw7) {
    Species s;
    s.addInstruction("hop");
    s.addInstruction("go 0");
    
    Creature c(&s, EAST);
    
    Darwin d(10,10);
    d.addCreature(&c, 0, 0);
    d.step();
    d.step();
    
    ASSERT_TRUE(d.grid[0][0]._creature != &c);
    ASSERT_TRUE(d.grid[0][1]._creature != &c);
    ASSERT_TRUE(d.grid[0][2]._creature == &c);
    }

TEST(Darwin, darw8) {
    Species s('$');
    s.addInstruction("hop");
    s.addInstruction("go 0");
    
    Creature c(&s, EAST);
    
    Darwin d(2,2);
    d.addCreature(&c, 1, 0);
    
    std::ostringstream w;
    d.printGrid(w);
    ASSERT_TRUE(w.str() == "  01\n0 ..\n1 $.\n");
    }

TEST(Darwin, darw9) {
    Species s('!');
    s.addInstruction("hop");
    s.addInstruction("go 0");
    
    Creature c(&s, EAST);
    
    Darwin d(10,10);
    d.addCreature(&c, 0, 0);
    
    std::ostringstream w;
    d.printStats(w);
    ASSERT_TRUE(w.str() == "!: 1\n");
    }

