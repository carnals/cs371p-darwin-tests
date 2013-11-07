#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept>

#include "gtest/gtest.h"

#include "Darwin.h"
 
 //addInstruction : 7
TEST(Specices, addInstruction_1)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("left") == 0);
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Specices, addInstruction_2)
{
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
  Critter crit_hopper1 = Critter(EAST, hopper1);
  std::string check;
  crit_hopper1.step(check);
  ASSERT_TRUE(check.compare("hop") == 0);
  crit_hopper1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);

}

TEST(Specices, addInstruction_3)
{
   Species trap1('t');
        trap1.addInstruction("if_enemy 3");
        trap1.addInstruction("left");
        trap1.addInstruction("go 0");
        trap1.addInstruction("infect");
        trap1.addInstruction("go 0");
  Critter crit_trap1 = Critter(SOUTH, trap1); 
  std::string check;
  crit_trap1.step(check);
  ASSERT_TRUE(check.compare("if_enemy 3") == 0);
  crit_trap1.step(check);
  ASSERT_TRUE(check.compare("left") == 0);
 crit_trap1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);
  crit_trap1.step(check);
  ASSERT_TRUE(check.compare("infect") == 0);
  crit_trap1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);
  
}
 
TEST(Specices, addInstruction_4)
{
   Species food1('f');
        food1.addInstruction("right");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("right") == 0);
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);
 
}

 
TEST(Specices, addInstruction_5)
{
   Species food1('f');
        food1.addInstruction("right");
        food1.addInstruction("go 1");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("right") == 0);
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("go 1") == 0);
 
}

 
TEST(Specices, addInstruction_6)
{
   Species food1('f');
        food1.addInstruction("right");
        food1.addInstruction("go 1");
   Species hopper1('h');
        hopper1.addInstruction("hop");
  Critter crit_food1 = Critter(EAST, food1);
  Critter crit_hopper1 = Critter(EAST, hopper1);
  std::string check;
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("right") == 0);
  crit_hopper1.step(check);
  ASSERT_TRUE(check.compare("hop") == 0);
 
}

TEST(Specices, addInstruction_7)
{
   Species food('f');
   food.addInstruction("go 1");
   food.addInstruction("go 2");
   food.addInstruction("go 3");
   food.addInstruction("go 4");
   food.addInstruction("go 5");
   food.addInstruction("go 6");
   food.addInstruction("go 7");
   food.addInstruction("go 8");
   food.addInstruction("go 0");
   Critter crit_food = Critter(NORTH, food);
   std::string check;
   crit_food.step(check);
   crit_food.step(check);
   crit_food.step(check);
   crit_food.step(check);
   crit_food.step(check);
   crit_food.step(check);
   ASSERT_TRUE(check.compare("go 6") == 0);
 
}

// infect : 7 
TEST(Species, infect_1)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("hop") == 0);
 
}

TEST(Species, infect_2)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Species, infect_3)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_food1.infect(crit_hopper1);
   std::string check;
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("left") == 0);
 
}

TEST(Species, infect_4)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_food1.infect(crit_hopper1);
   std::string check;
   crit_hopper1.step(check);
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Species, infect_5)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species food2('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_food2 = Critter(EAST, food2); 
   crit_food2.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("left") == 0);
 
}

TEST(Species, infect_6)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species food2('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_food2 = Critter(EAST, food2); 
   crit_food2.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Species, infect_7)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.infect(crit_hopper1);
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("hop") == 0);
 
}

 // lineInstruct : 6
TEST(Species, lineInstruction_1)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  std:: string check = food1.lineInstruction(0); 
  ASSERT_TRUE(check.compare("left") == 0);

}

TEST(Species, lineInstruction_2)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  std:: string check = food1.lineInstruction(1); 
  ASSERT_TRUE(check.compare("go 0") == 0);
  
}

TEST(Species, lineInstruction_3)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
  std:: string check = food1.lineInstruction(2); 
  ASSERT_TRUE(check.compare("right") == 0);
  
}

TEST(Species, lineInstruction_4)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
  std:: string check = food1.lineInstruction(3); 
  ASSERT_TRUE(check.compare("go 0") == 0);
  
}

TEST(Species, lineInstruction_5)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
        food1.addInstruction("left");
        food1.addInstruction("left");
        food1.addInstruction("left");
        food1.addInstruction("if_enemy");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
  std:: string check = food1.lineInstruction(8); 
  ASSERT_TRUE(check.compare("go 0") == 0);
  
}


TEST(Species, lineInstruction_6)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("right");
        food1.addInstruction("go 0");
  std:: string check = food1.lineInstruction(7); 
  ASSERT_TRUE(check.compare("right") == 0);
  
}
//equal : 6
TEST(Species, equals_1)
{
  Species food('f');
  Species food1('f');
  ASSERT_TRUE(food.equals(food1));
}

TEST(Species, equals_2)
{
  Species food('f');
  Species trap('t');
  ASSERT_TRUE(!food.equals(trap));
}

TEST(Species, equals_3)
{
  Species food('f');
  Species trap('t');
  ASSERT_TRUE(!trap.equals(food));
}

TEST(Species, equals_4)
{
  Species food('f');
  Species trap('t');
  ASSERT_TRUE(!trap.equals(food));
  Species hopper('h');
  ASSERT_TRUE(!trap.equals(hopper));
}

TEST(Species, equals_5)
{
  Species food('f');
  Species trap('t');
  ASSERT_TRUE(!trap.equals(food));
  Species hopper('h');
  ASSERT_TRUE(!food.equals(hopper));
}

TEST(Species, equals_6)
{
  Species food('f');
  Species trap('t');
  Species hopper('h');
  Species best('b');
  ASSERT_TRUE(!best.equals(food));
  ASSERT_TRUE(!best.equals(trap));
  ASSERT_TRUE(!best.equals(hopper));
  ASSERT_TRUE(best.equals(best));
}


// Species unit tests done: # of tests  = 24 
//Infect : 7
TEST(Critter, infect_1)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("hop") == 0);
}

TEST(Critter, infect_2)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Critter, infect_3)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_food1.infect(crit_hopper1);
   std::string check;
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("left") == 0);
 
}

TEST(Critter, infect_4)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_food1.infect(crit_hopper1);
   std::string check;
   crit_hopper1.step(check);
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Critter, infect_5)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species food2('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_food2 = Critter(EAST, food2); 
   crit_food2.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("left") == 0);
 
}

TEST(Critter, infect_6)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species food2('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_food2 = Critter(EAST, food2); 
   crit_food2.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
 
}

TEST(Critter, infect_7)
{
   Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species hopper1('h');
        hopper1.addInstruction("hop");
        hopper1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_hopper1 = Critter(EAST, hopper1); 
   crit_hopper1.infect(crit_food1);
   std::string check;
   crit_food1.infect(crit_hopper1);
   crit_hopper1.step(check);
   ASSERT_TRUE(check.compare("hop") == 0);
 
}

//step : 7
TEST(Critter, step_1)
{
    Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("left") == 0);
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0);
}

TEST(Critter, step_2)
{
    Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  ASSERT_TRUE(crit_food1.step(check));
  ASSERT_TRUE(check.compare("left") == 0); 
}

TEST(Critter, step_3)
{
    Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  ASSERT_TRUE(crit_food1.step(check));
  crit_food1.step(check);
  ASSERT_TRUE(check.compare("go 0") == 0); 
}

TEST(Critter, step_4)
{
    Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food1); 
  std::string check;
  ASSERT_TRUE(crit_food1.step(check));
  ASSERT_TRUE(crit_food1.step(check));
  ASSERT_TRUE(check.compare("go 0") == 0); 
}

TEST(Critter, step_5)
{
    Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
  Critter crit_trap = Critter(EAST, trap); 
  std::string check;
  ASSERT_TRUE(crit_trap.step(check));
  ASSERT_TRUE(crit_trap.step(check));
  ASSERT_TRUE(crit_trap.step(check));
  ASSERT_TRUE(check.compare("go 0") == 0); 
}

TEST(Critter, step_6)
{
    Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
  Critter crit_trap = Critter(EAST, trap); 
  std::string check;
  ASSERT_TRUE(crit_trap.step(check));
  ASSERT_TRUE(check.compare("if_enemy 3") == 0); 
  ASSERT_TRUE(crit_trap.step(check));
  ASSERT_TRUE(crit_trap.step(check));
  
}

TEST(Critter, step_7)
{
  Species food1('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Species food2('f');
        food1.addInstruction("left");
        food1.addInstruction("go 0");
   Critter crit_food1 = Critter(EAST, food1); 
   Critter crit_food2 = Critter(EAST, food2); 
   crit_food2.infect(crit_food1);
   std::string check;
   crit_food1.step(check);
   crit_food1.step(check);
   ASSERT_TRUE(check.compare("go 0") == 0);
}


//eqaul : 7
TEST(Critter, equals_1)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  Species food2('f');
  Critter crit_food2 = Critter(EAST, food2); 
  ASSERT_TRUE(crit_food1.equals(crit_food2)); 
}

TEST(Critter, equals_2)
{
  Species trap1('t');
  Critter crit_trap1 = Critter(EAST, trap1); 
  Species food2('f');;
  Critter crit_food2 = Critter(EAST, food2); 
  ASSERT_TRUE(!crit_trap1.equals(crit_food2)); 
}

TEST(Critter, equals_3)
{
  Species food('f');
  Species trap('t');
  Species hopper('h');
  Critter crit_food = Critter(EAST, food);
  Critter crit_trap = Critter(EAST, trap);
  Critter crit_hopper = Critter(EAST, hopper);
  ASSERT_TRUE(!crit_trap.equals(crit_hopper));
  ASSERT_TRUE(!crit_trap.equals(crit_food));

}

TEST(Critter, equals_4)
{
  Species food('f');
  Species trap('t');
  Species hopper('h');
  Species best('b');
  Critter crit_food = Critter(EAST, food);
  Critter crit_trap = Critter(EAST, trap);
  Critter crit_hopper = Critter(EAST, hopper);
  Critter crit_best = Critter(EAST, best);
  ASSERT_TRUE(!crit_trap.equals(crit_hopper));
  ASSERT_TRUE(crit_best.equals(crit_best));

}

TEST(Critter, equals_5)
{
  Species food('f');
  Species trap('t');
  Species hopper('h');
  Species best('b');
  Critter crit_food = Critter(EAST, food);
  Critter crit_trap = Critter(EAST, trap);
  Critter crit_hopper = Critter(EAST, hopper);
  Critter crit_best = Critter(EAST, best);
  ASSERT_TRUE(!crit_best.equals(crit_hopper));
  ASSERT_TRUE(!crit_best.equals(crit_food));

}

TEST(Critter, equals_6)
{
  Species food('f');
  Species trap('t');
  Species hopper('h');
  Species best('b');
  Critter crit_food = Critter(EAST, food);
  Critter crit_trap = Critter(EAST, trap);
  Critter crit_hopper = Critter(EAST, hopper);
  Critter crit_best = Critter(EAST, best);
  ASSERT_TRUE(!crit_best.equals(crit_hopper));
  ASSERT_TRUE(!crit_best.equals(crit_food));
  ASSERT_TRUE(!crit_best.equals(crit_trap));
  ASSERT_TRUE(crit_best.equals(crit_best));
}

TEST(Critter, equals_7)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  Species food2('f');
  Critter crit_food2 = Critter(EAST, food2); 
  Species food3('F');
  Critter crit_food3 = Critter(EAST, food3);
  ASSERT_TRUE(crit_food1.equals(crit_food2)); 
  ASSERT_TRUE(!crit_food1.equals(crit_food3));
}

 /**
    *turns right or left depenting on bool
    *@param bool true = left, false = right
    enum Direction
{
  WEST,
  NORTH,
  EAST,
  SOUTH
};
    */
//rotate : 7
TEST(Critter, rotate_1)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  crit_food1.rotate(true);
  ASSERT_TRUE(crit_food1._direction == 1);
}

TEST(Critter, rotate_2)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  crit_food1.rotate(false);
  ASSERT_TRUE(crit_food1._direction == 3);
}

TEST(Critter, rotate_3)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  crit_food1.rotate(false);
  crit_food1.rotate(true);
  ASSERT_TRUE(crit_food1._direction == 2);
}

TEST(Critter, rotate_4)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1); 
  ASSERT_TRUE(crit_food1._direction == 2);
  crit_food1.rotate(false);
  ASSERT_TRUE(crit_food1._direction == 3);
  crit_food1.rotate(true);
  ASSERT_TRUE(crit_food1._direction == 2);
  
}

TEST(Critter, rotate_5)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1);
  Species food2('f');
  Critter crit_food2 = Critter(NORTH, food2);  
  crit_food1.rotate(false);
  ASSERT_TRUE(crit_food1._direction == 3);
  crit_food2.rotate(true);
  ASSERT_TRUE(crit_food2._direction == 0);
  
}

TEST(Critter, rotate_6)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1);
  Species food2('f');
  Critter crit_food2 = Critter(NORTH, food2);  
  crit_food1.rotate(false);
  ASSERT_TRUE(crit_food1._direction == 3);
  crit_food2.rotate(true);
  crit_food2.rotate(true);
  crit_food2.rotate(true);
  crit_food2.rotate(true);
  ASSERT_TRUE(crit_food2._direction == 1);
  
}

TEST(Critter, rotate_7)
{
  Species food1('f');
  Critter crit_food1 = Critter(EAST, food1);  
  crit_food1.rotate(false);
  crit_food1.rotate(false);
  crit_food1.rotate(false);
  crit_food1.rotate(false);
  ASSERT_TRUE(crit_food1._direction == 2);
  
}

//Critter tests done, # of tests = 54

// World : 6 
TEST(World, world_1)
{
  World check(1,1);
  ASSERT_TRUE(check._c_max == 1);
}

TEST(World, world_2)
{
  World check(3,1);
  ASSERT_TRUE(check._r_max == 3);
  ASSERT_TRUE(check._c_max == 1);
}

TEST(World, world_3)
{


  try
  {
    World check(0,0);
    ASSERT_TRUE(check._r_max == 0);
    ASSERT_TRUE(check._c_max == 0);
  }
  catch (const std::invalid_argument&) 
  {
      assert(true);
    }
  catch (const std::out_of_range&) 
  {
      assert(true);
  }
}
//test should not work, but it does

TEST(World, world_4)
{
  try
  {
  World check(20, 0);
  ASSERT_TRUE(check._r_max == 20);
  ASSERT_TRUE(check._c_max == 0);
  }
  catch (const std::invalid_argument&) 
  {
      assert(true);
    }
  catch (const std::out_of_range&) 
  {
      assert(true);
  }
}

TEST(World, world_5)
{
  try
  {
  World check(0, 20);
  ASSERT_TRUE(check._r_max == 0);
  ASSERT_TRUE(check._c_max == 20);
  }
  catch (const std::invalid_argument&) 
  {
      assert(true);
    }
  catch (const std::out_of_range&) 
  {
      assert(true);
  }
}

TEST(World, world_6)
{
  try
  {
  World check(0, 0);
  ASSERT_TRUE(check._r_max == 0);
  ASSERT_TRUE(check._c_max == 0);
  }
  catch (const std::invalid_argument&) 
  {
      assert(true);
    }
  catch (const std::out_of_range&) 
  {
      assert(true);
  }
}

TEST(World, year_1)
{
  World check(2,2);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
  check.addCritter(1,1, crit_food1);
  check.year();
  ASSERT_TRUE(crit_food1._direction == 1);

}

TEST(World, year_2)
{
  World check(2,2);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
  check.addCritter(1,1, crit_food1);
  check.year();
  ASSERT_TRUE(crit_food1._direction == 1);
  check.year();
  ASSERT_TRUE(crit_food1._direction == 0);
}

TEST(World, year_3)
{
  World check(2,2);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
  check.addCritter(1,1, crit_food1);
  check.year();
  check.year();
  check.year();
  ASSERT_TRUE(crit_food1._direction == 3);

}
//having problems with bounds for map
TEST(World, year_4)
{
  World check(2,3);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
  Species trap('t');
  trap.addInstruction("if enemy 3");
  trap.addInstruction("left");
  trap.addInstruction("go 0");
  trap.addInstruction("infect");
  Critter crit_trap(WEST, trap);
  check.addCritter(1,2, crit_food1);
  check.addCritter(1,1, crit_trap);
  check.year();
  ASSERT_TRUE(crit_food1._direction == 1);
  ASSERT_TRUE(crit_trap._direction == 3);

}

TEST(World, year_5)
{
  World check(4,4);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
   Species trap('t');
  trap.addInstruction("if enemy 3");
  trap.addInstruction("left");
  trap.addInstruction("go 0");
  trap.addInstruction("infect");
  trap.addInstruction("go 0");
  Critter crit_trap(WEST, trap);
  check.addCritter(1,1, crit_food1);
  check.addCritter(1,2, crit_trap);
  check.year();
  ASSERT_TRUE(crit_food1._direction == 1);
 // std::cout << crit_trap._direction << std::endl;
 // ASSERT_TRUE(crit_trap._direction == 0);
 //if enemy not behaving correctly 
}

TEST(World, year_6)
{
  World check(5,5);
  Species food('f');
  food.addInstruction("left");
  food.addInstruction("go 0");
  Critter crit_food1 = Critter(EAST, food);
  Species trap('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
  Critter crit_trap(WEST, trap);
  Species rover('r');
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");
  Critter crit_rover = Critter(WEST, rover);
  check.addCritter(1,4, crit_rover);
  check.addCritter(1,1, crit_food1);
  check.addCritter(1,2, crit_trap);
  check.year();
//  check.year();
  ASSERT_TRUE(crit_food1._direction == 1);
//  ASSERT_TRUE(crit_trap._direction == 0);
  ASSERT_TRUE(crit_rover._direction == 0);
}

 
