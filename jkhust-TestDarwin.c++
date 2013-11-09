// ------------------------------------
// projects/allocator/TestDarwin.c++
// Copyright (C) 2013
// Justin Hust
// EID: jkh2367
// CS ID: jkhust
// Email: justin.hust@utexas.edu
// ------------------------------------

/*
To test the program:
% ls -al /usr/include/gtest/
...
gtest.h
...

% locate libgtest.a
/usr/lib/libgtest.a

% locate libpthread.a
/usr/lib/x86_64-linux-gnu/libpthread.a
/usr/lib32/libpthread.a

% locate libgtest_main.a
/usr/lib/libgtest_main.a

% g++ -pedantic -std=c++0x -Wall TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

% valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include "gtest/gtest.h"

#include "Darwin.h"

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

// -----------------
// creature_sameSpec
// -----------------
TEST(Creature, sameSpec_1) {
  Creature c1(0, West, World::Food);
  Creature c2(1, North, World::Food); 

  ASSERT_TRUE( c1.sameSpec(c2) );
 
}

TEST(Creature, sameSpec_2) {
  Creature c1(3, West, World::Hopper);
  Creature c2(7, South, World::Food); 

  ASSERT_TRUE( ! c1.sameSpec(c2) );
 
}


TEST(Creature, sameSpec_3) {
  Creature c1(0, West, World::Best);
  Creature c2(12, North, World::Rover); 

  ASSERT_TRUE( ! c1.sameSpec(c2) );
 
}

TEST(Creature, sameSpec_4) {
  Creature c1(15, West, World::Best);
  Creature c2(99, North, World::Best); 

  ASSERT_TRUE( c1.sameSpec(c2) );
 
}

// -----------------
// creature_setCoord, creature_getCoord
// -----------------
TEST(Creature, setCoord_getCoord_1) {
  Creature c(0, West, World::Food);
    
  c.setCoord(10);
  
  ASSERT_TRUE(c.getCoord() == 10);
     
}

TEST(Creature, setCoord_getCoord_2) {
  Creature c(0, West, World::Food);
    
  c.setCoord(20383);
  
  ASSERT_TRUE(c.getCoord() == 20383);
     
}

TEST(Creature, setCoord_getCoord_3) {
  Creature c(0, West, World::Food);
    
  c.setCoord(99);
  
  ASSERT_TRUE(c.getCoord() == 99);
     
}

// -----------------
// creature_setInstr, creature_getInstr
// -----------------
TEST(Creature, setInstr_getInstr_1) {
  Creature c(0, West, World::Rover);
  c.setInstr(c.getInstr() + 1);
  
  ASSERT_TRUE(c.getInstr() == 1);
     
}

TEST(Creature, setInstr_getInstr_2) {
  Creature c(0, West, World::Rover);
    
  c.setInstr(c.getInstr() + 1);
  ASSERT_TRUE(c.getInstr() == 1);

  c.setInstr(c.getInstr() + 1);
  ASSERT_TRUE(c.getInstr() == 2);
       
}

TEST(Creature, setInstr_getInstr_3) {
  Creature c(0, West, World::Rover);
    
  c.setInstr(c.getInstr() + 1);
  ASSERT_TRUE(c.getInstr() == 1);

  c.setInstr(c.getInstr() + 1);
  ASSERT_TRUE(c.getInstr() == 2);

  c.setInstr(c.getInstr() + 1);
  c.setInstr(c.getInstr() + 1);
  c.setInstr(c.getInstr() + 1);
  ASSERT_TRUE(c.getInstr() == 5);
  
}

// -----------------
// creature_draw
// -----------------
TEST(Creature, draw_food) {
  Creature c(0, West, World::Food);
  
  std::ostringstream ss;
  c.draw(ss);
  ASSERT_TRUE( ss.str() == "f");

}

TEST(Creature, draw_rover) {
  Creature c(0, West, World::Rover);
  
  std::ostringstream ss;
  c.draw(ss);
  ASSERT_TRUE( ss.str() == "r");

}

TEST(Creature, draw_trap) {
  Creature c(0, West, World::Trap);
  
  std::ostringstream ss;
  c.draw(ss);
  ASSERT_TRUE( ss.str() == "t");

}

TEST(Creature, draw_hopper) {
  Creature c(0, West, World::Hopper);
  
  std::ostringstream ss;
  c.draw(ss);
  ASSERT_TRUE( ss.str() == "h");

}

// -----------------
// creature_toString
// -----------------
TEST(Creature, toString_1) {
  Creature c(0, West, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 0 f");
   
}

TEST(Creature, toString_2) {
  Creature c(199, South, World::Rover);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "199 3 r");
   
}


TEST(Creature, toString_3) {
  Creature c(21, East, World::Hopper);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "21 2 h");
   
}

TEST(Creature, toString_4) {
  Creature c(38, South, World::Best);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "38 3 b");
   
}

TEST(Creature, toString_5) {
  Creature c(17, South, World::Trap);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "17 3 t");
   
}

// -----------------
// creature_turnLeft
// -----------------
TEST(Creature, turnLeft_1) {
  Creature c(0, West, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 0 f");

  ss.str("");
  ss.clear();  
  c.turnLeft();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 3 f");
   
}

TEST(Creature, turnLeft_2) {
  Creature c(0, South, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 3 f");

  ss.str("");
  ss.clear();  
  c.turnLeft();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 2 f");
   
}


TEST(Creature, turnLeft_3) {
  Creature c(0, East, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 2 f");

  ss.str("");
  ss.clear();  
  c.turnLeft();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 1 f");
   
}


TEST(Creature, turnLeft_4) {
  Creature c(0, North, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 1 f");

  ss.str("");
  ss.clear();  
  c.turnLeft();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 0 f");
   
}

// -----------------
// creature_turnRight
// -----------------
TEST(Creature, turnRight_1) {
  Creature c(0, West, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 0 f");

  ss.str("");
  ss.clear();  
  c.turnRight();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 1 f");
   
}

TEST(Creature, turnRight_2) {
  Creature c(0, North, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 1 f");

  ss.str("");
  ss.clear();  
  c.turnRight();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 2 f");
   
}


TEST(Creature, turnRight_3) {
  Creature c(0, East, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 2 f");

  ss.str("");
  ss.clear();  
  c.turnRight();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 3 f");
   
}


TEST(Creature, turnRight_4) {
  Creature c(0, South, World::Food);
  
  std::ostringstream ss;
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 3 f");

  ss.str("");
  ss.clear();  
  c.turnRight();
  c.toString(ss);
  ASSERT_TRUE( ss.str() == "0 0 f");
   
}

// -----------------
// creature_operatorLess
// -----------------
TEST(Creature, operatorLess_1) {
  Creature c1(0, South, World::Food);
  Creature c2(10, South, World::Food);

  ASSERT_TRUE( c1 < c2 );
   
}

TEST(Creature, operatorLess_2) {
  Creature c1(10, South, World::Food);
  Creature c2(10, South, World::Food);

  ASSERT_TRUE( !( c1 < c2) );
   
}

TEST(Creature, operatorLess_3) {
  Creature c1(0, South, World::Food);
  Creature c2(0, South, World::Food);

  ASSERT_TRUE( ! (c1 < c2) );
   
}

TEST(Creature, operatorLess_4) {
  Creature c1(70, South, World::Food);
  Creature c2(71, South, World::Food);

  ASSERT_TRUE( c1 < c2 );
   
}

TEST(Creature, operatorLess_5) {
  Creature c1(73, South, World::Food);
  Creature c2(71, South, World::Food);

  ASSERT_TRUE( ! (c1 < c2) );
   
}

// -----------------
// creature_tally
// -----------------
TEST(Creature, tally_1) {
  int totals[5];
  totals[FoodID] = 37;

  Creature c(73, South, World::Food);
  c.tally(totals);

  ASSERT_TRUE( totals[FoodID] == 38);
  
}

TEST(Creature, tally_2) {
  int totals[5];
  totals[FoodID] = 37;
  totals[BestID] = 0;

  Creature c(73, South, World::Best);
  c.tally(totals);

  ASSERT_TRUE( totals[FoodID] == 37 &&
               totals[BestID] == 1);
  
}

TEST(Creature, tally_3) {
  int totals[5];
  totals[FoodID] = 37;
  totals[BestID] = 0;
  totals[HopperID] = 5;
  
  Creature c1(73, South, World::Best);
  c1.tally(totals);
  Creature c2(60, South, World::Hopper);
  c2.tally(totals);

  ASSERT_TRUE( totals[FoodID] == 37 &&
               totals[BestID] == 1 &&
               totals[HopperID] == 6);
  
}

TEST(Creature, tally_4) {
  int totals[5];
  totals[FoodID] = 37;
  totals[BestID] = 0;
  totals[HopperID] = 5;
  
  Creature c1(73, South, World::Best);
  c1.tally(totals);
  Creature c2(60, South, World::Hopper);
  c2.tally(totals);
  c2.tally(totals);

  ASSERT_TRUE( totals[FoodID] == 37 &&
               totals[BestID] == 1 &&
               totals[HopperID] == 7);
  
}

// -----------------
// creature_hop
// -----------------
TEST(Creature, hopper_1) {
  World w(3, 3);  
  w.addCreature(3, West, World::Hopper);
  w.runTurn();


  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "3 0 h");
  
}

TEST(Creature, hopper_2) {
  World w(3, 3);  
  w.addCreature(5, East, World::Hopper);
  w.runTurn();


  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "5 2 h");
  
}

// ----------
// World_ctor
// ----------

TEST(World, ctor_1) {
  World w(1, 1);
  ASSERT_TRUE(true);
  
}

TEST(World, ctor_2) {
  World w(3, 3);
  ASSERT_TRUE(true);  

}

TEST(World, ctor_3) {
  World w(72, 72);
  ASSERT_TRUE(true);
  
}

// -----------------
// World_randomCoord
// -----------------
TEST(World, randomCoord_1) {
  srand(0);
  World w(1, 1);
  
  int c = w.randomCoord();
//  std::cout << c << std::endl;
  ASSERT_TRUE( c == 0 );

}

// -----------------
// World_toCoord
// -----------------
TEST(World, toCoord_1) {
  World w(1, 1);
  
  int c = w.toCoord(0, 0);
  ASSERT_TRUE( c == 0 );

}

TEST(World, toCoord_2) {
  World w(3, 3);

  int c = w.toCoord(1, 2);
//  std::cout << c << std::endl;
  ASSERT_TRUE( c == 5 );
  
}

TEST(World, toCoord_3) {
  World w(10, 10);

  int c = w.toCoord(5, 7);
//  std::cout << c << std::endl;
  ASSERT_TRUE( c == 57 );
  
}

TEST(World, toCoord_4) {
  World w(72, 72);

  int c = w.toCoord(71, 71);
  ASSERT_TRUE( c == 5183 );
  
}

// -----------------
// World_inBounds
// -----------------
TEST(World, inBounds_1) {
  World w(1, 1);
  
  ASSERT_TRUE( w.inBounds(0) );
  ASSERT_TRUE( !w.inBounds(10) );
  ASSERT_TRUE( !w.inBounds(999) ); 
  ASSERT_TRUE( !w.inBounds(-3) ); 
  
  ASSERT_TRUE( w.inBounds( w.toCoord(0, 0) ));
  ASSERT_TRUE( !w.inBounds( w.toCoord(3, 4) ));

}

TEST(World, inBounds_2) {
  World w(5, 5);
  
  ASSERT_TRUE( w.inBounds(0) );
  ASSERT_TRUE( w.inBounds(10) );
  ASSERT_TRUE( !w.inBounds(99) ); 
  ASSERT_TRUE( !w.inBounds(-3) ); 
 
  ASSERT_TRUE( w.inBounds( w.toCoord(0, 0) ));
  ASSERT_TRUE( w.inBounds( w.toCoord(3, 4) ));
  ASSERT_TRUE( !w.inBounds( w.toCoord(12, 7) ));
    
}


TEST(World, inBounds_3) {
  World w(10, 10);

  
  ASSERT_TRUE( w.inBounds(0) );
  ASSERT_TRUE( w.inBounds(10) );
  ASSERT_TRUE( w.inBounds(99) ); 
  ASSERT_TRUE( !w.inBounds(-3) ); 
  
  ASSERT_TRUE( w.inBounds(  w.toCoord(0, 0) ));
  ASSERT_TRUE( w.inBounds( w.toCoord(7, 0) ));
  ASSERT_TRUE( w.inBounds( w.toCoord(6, 2) ));
  ASSERT_TRUE( !w.inBounds( w.toCoord(10, 10) ));
  
}


TEST(World, inBounds_4) {
  World w(72, 72);

  ASSERT_TRUE( w.inBounds(0) );
  ASSERT_TRUE( w.inBounds(10) );
  ASSERT_TRUE( w.inBounds(99) ); 
  ASSERT_TRUE( w.inBounds(5183) ); 
  ASSERT_TRUE( !w.inBounds(-3) ); 
  
  ASSERT_TRUE( w.inBounds( w.toCoord(0, 0)  ));
  ASSERT_TRUE( w.inBounds( w.toCoord(7, 0)  ));
  ASSERT_TRUE( w.inBounds( w.toCoord(6, 2)  ));
  ASSERT_TRUE( w.inBounds( w.toCoord(50, 26) ));
  ASSERT_TRUE( w.inBounds( w.toCoord(66, 2) ));
  ASSERT_TRUE( !w.inBounds( w.toCoord(72, 72) ));
   
}

// -----------------
// World_outputBoard (empty)
// -----------------
TEST(World, outputBoard_Empty1) {
  World w(1, 1);
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  0\n0 .\n" );
  
}

TEST(World, outputBoard_Empty2) {
  World w(3, 3);
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 ...\n1 ...\n2 ...\n" );
  
}

TEST(World,outputBoard_Empty3) {
  World w(3, 5);
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n" );
  
}

// -----------------
// World_addCreature
// -----------------
TEST(World, addCreature_1) {
  World w(1, 1);
  
  w.addCreature( w.toCoord(0, 0), East, World::Food);

}

TEST(World, addCreature_2) {
  World w(3, 3);
  
  w.addCreature( w.toCoord(0, 0), East, World::Food);
  w.addCreature( w.toCoord(0, 1), West, World::Food);

}

// -----------------
// World_outputCreatures
// -----------------
TEST(World, outputCreatures_1) {
  World w(15, 15);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "" );
  
}

TEST(World, outputCreatures_2) {
  World w(1, 1);
  
  w.addCreature( w.toCoord(0, 0), West, World::Food);

  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 0 f" );
  
}

TEST(World, outputCreatures_3) {
  World w(3, 3);
  
  w.addCreature( w.toCoord(0, 0), East, World::Food);
  w.addCreature( w.toCoord(0, 1), West, World::Rover);

  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 f\n1 0 r" );
  
}

TEST(World, outputCreatures_4) {
  World w(5, 5);
  
  // test for opposite order.  works.
  w.addCreature( w.toCoord(0, 0), East, World::Food );
  w.addCreature( w.toCoord(4, 4), North, World::Trap );
  w.addCreature( w.toCoord(2, 1), South, World::Rover );

  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 f\n11 3 r\n24 1 t" );

}

// -----------------
// World_isValid
// -----------------
TEST(World, isValid_1) {
  World w(15, 15);
  
  ASSERT_TRUE( w.isValid() );
  
}


TEST(World, isValid_2) {
  World w(3, 3);
  
  w.addCreature( w.toCoord(0, 0), West, World::Food );
  w.addCreature( w.toCoord(0, 1), East, World::Trap );

  ASSERT_TRUE( w.isValid() );
  
}


TEST(World, isValid_3) {
  World w(3, 3);
  
  w.addCreature( w.toCoord(0, 0), South, World::Hopper );
  w.addCreature( w.toCoord(2, 1), North, World::Rover );

  ASSERT_TRUE( w.isValid() );
  
}

// -----------------
// World_outputBoard (creatures)
// -----------------
TEST(World, outputBoard_withCreatures1) {
  World w(1, 1);
  
  w.addCreature( w.toCoord(0, 0), West, World::Food );
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  0\n0 f\n" );
  
}

TEST(World, outputBoard_withCreatures2) {
  World w(3, 3);
  
  w.addCreature( w.toCoord(0, 0), West, World::Food);
  w.addCreature( w.toCoord(2, 2), South, World::Hopper );
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 f..\n1 ...\n2 ..h\n" );
  
}

TEST(World,outputBoard_withCreatures3) {
  World w(3, 5);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food );
  w.addCreature( w.toCoord(1, 1), South, World::Trap );
  w.addCreature( w.toCoord(2, 4), West, World::Rover );
  
  std::ostringstream ss;
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  01234\n0 f....\n1 .t...\n2 ....r\n" );
  
}

// -----------------
// World_tallyCreatures
// -----------------
TEST(World, outputTotals_1) {
  World w(15, 15);
  
  std::ostringstream ss;
  w.outputTotals(ss);
  ASSERT_TRUE( ss.str() == "Food: 0\nHopper: 0\nRover: 0\nTrap: 0\nBest: 0\n" );  
  
}

TEST(World, outputTotals_2) {
  World w(5, 3);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food);
  w.addCreature( w.toCoord(1, 1), South, World::Trap );
  w.addCreature( w.toCoord(4, 2), West, World::Rover );

  std::ostringstream ss;
  w.outputTotals(ss);
  ASSERT_TRUE( ss.str() == "Food: 1\nHopper: 0\nRover: 1\nTrap: 1\nBest: 0\n" );  
  
}

TEST(World, outputTotals_3) {
  World w(8, 8);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food );
  w.addCreature( w.toCoord(1, 1), South, World::Best );
  w.addCreature( w.toCoord(4, 2), West, World::Best );
  w.addCreature( w.toCoord(1, 2), East, World::Food );
  w.addCreature( w.toCoord(4, 4), North, World::Rover );
  w.addCreature( w.toCoord(2, 1), South, World::Hopper );
  w.addCreature( w.toCoord(6, 7), North, World::Food );
  w.addCreature( w.toCoord(7, 7), South, World::Hopper );

  std::ostringstream ss;
  w.outputTotals(ss);
  ASSERT_TRUE( ss.str() == "Food: 3\nHopper: 2\nRover: 1\nTrap: 0\nBest: 2\n" );  
  
}

// -----------------
// World_act
// -----------------
TEST(World, runTurn_food) {
  World w(1, 1);
  w.addCreature(0, North, World::Food);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 1 f" );
  
  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 0 f" );

}

TEST(World, runTurn_twoFood) {
  World w(2, 2);
  w.addCreature(0, North, World::Food);
  w.addCreature(3, East, World::Food);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 1 f\n3 2 f" );
  
  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 0 f\n3 1 f" );

}

TEST(World, runTurn_twoFood2) {
  World w(2, 2);
  w.addCreature(0, North, World::Food);
  w.addCreature(3, East, World::Food);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 1 f\n3 2 f" );
  
  w.runTurn();
  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 3 f\n3 0 f" );

}

TEST(World, runTurn_hopper_horizontal) {
  World w(1, 3);
  w.addCreature(0, East, World::Hopper);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 h" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 h..\n");
  
  
              
                          
                                                  
  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "1 2 h" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  012\n0 .h.\n");





  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "2 2 h" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 2.\n  012\n0 ..h\n");



  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "2 2 h" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 3.\n  012\n0 ..h\n");

}

TEST(World, runTurn_hopperIntoFood) {
  World w(1, 3);
  w.addCreature(0, East, World::Hopper);
  w.addCreature(1, North, World::Food);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 h\n1 1 f" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 hf.\n");
  
  
              
                          
            
  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 h\n1 0 f" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  012\n0 hf.\n");

}

TEST(World, runTurn_hopperRaceCond) {
  World w(3, 3);
  w.addCreature( w.toCoord(1, 0), East, World::Hopper);
  w.addCreature( w.toCoord(2, 1), North, World::Hopper);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "3 2 h\n7 1 h");
 
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 ...\n1 h..\n2 .h.\n");
  

  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "4 2 h\n7 1 h" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  012\n0 ...\n1 .h.\n2 .h.\n");
  
}

/*

...
h..
.r.

to

...
.r.
.r.

*/
TEST(World, runTurn_infectHopper) {
  World w(3, 3);
  w.addCreature( w.toCoord(1, 0), East, World::Hopper);
  w.addCreature( w.toCoord(2, 1), North, World::Rover);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "3 2 h\n7 1 r");
 
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 ...\n1 h..\n2 .r.\n");
  

  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "4 2 r\n7 1 r" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  012\n0 ...\n1 .r.\n2 .r.\n");
  
}

/*

...
h.t
...

to

...
.tt
...

*/
TEST(World, runTurn_infectTrap) {
  World w(3, 3);
  w.addCreature( w.toCoord(1, 0), East, World::Hopper);
  w.addCreature( w.toCoord(1, 2), West, World::Trap);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "3 2 h\n5 0 t");
 
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  012\n0 ...\n1 h.t\n2 ...\n");
  

  w.runTurn();
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "4 2 t\n5 0 t" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  012\n0 ...\n1 .tt\n2 ...\n");
  
}

/*

....
h..t
....

to

....
.h.t
....

to

....
..tt
....

*/
TEST(World, runTurn_infectTrap2) {
  World w(3, 4);
  w.addCreature( w.toCoord(1, 0), East, World::Hopper);
  w.addCreature( w.toCoord(1, 3), North, World::Trap);
  
  std::ostringstream ss;
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "4 2 h\n7 1 t");
 
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  0123\n0 ....\n1 h..t\n2 ....\n");
  
  

  w.runTurn();

  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "5 2 h\n7 0 t" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  0123\n0 ....\n1 .h.t\n2 ....\n");
  
  

  w.runTurn();

  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "6 2 t\n7 0 t" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 2.\n  0123\n0 ....\n1 ..tt\n2 ....\n");

  w.runTurn();

  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "6 1 t\n7 3 t" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 3.\n  0123\n0 ....\n1 ..tt\n2 ....\n");
     

}

// -----------------
// World_enemies
// -----------------
TEST(World, enemies_1) {

  World w(5, 3);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food );
  w.addCreature( w.toCoord(1, 1), South, World::Trap );
  w.addCreature( w.toCoord(4, 2), West, World::Best );
  
  ASSERT_TRUE( w.enemies(0, w.toCoord(4, 2)) );
  
}

TEST(World, enemies_2) {

  World w(5, 3);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food );
  w.addCreature( w.toCoord(1, 1), South, World::Trap );
  w.addCreature( w.toCoord(4, 2), West, World::Food );
  
  ASSERT_TRUE( ! w.enemies(0, w.toCoord(4, 2)) );
  
}

TEST(World, enemies_3) {

  World w(5, 3);
  
  w.addCreature( w.toCoord(0, 0), North, World::Food );
  w.addCreature( w.toCoord(1, 1), South, World::Food );
  w.addCreature( w.toCoord(4, 2), West, World::Best );
  
  ASSERT_TRUE( ! w.enemies(0, w.toCoord(1, 1)) );
  
}


// -----------------
// Darwin accept 1
// -----------------
TEST(Darwin, accept_1) {
  World w(8, 8);

  w.addCreature( w.toCoord(0, 0), East, World::Food);
  w.addCreature( w.toCoord(3, 3), North, World::Hopper);
  w.addCreature( w.toCoord(3, 4), East, World::Hopper);
  w.addCreature( w.toCoord(4, 4), South, World::Hopper);
  w.addCreature( w.toCoord(4, 3), West, World::Hopper);
  w.addCreature( w.toCoord(7, 7), North, World::Food);
  
  std::ostringstream ss;
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 2 f\n27 1 h\n28 2 h\n35 0 h\n36 3 h\n63 1 f" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n");
  
  
  w.runTurn();
  
  
  ss.str("");
  ss.clear();
  w.outputCreatures(ss);
  ASSERT_TRUE( ss.str() == "0 1 f\n19 1 h\n29 2 h\n34 0 h\n44 3 h\n63 0 f" );
  
  ss.str("");
  ss.clear();
  w.outputBoard(ss);
  ASSERT_TRUE( ss.str() == "Turn = 1.\n  01234567\n0 f.......\n1 ........\n2 ...h....\n3 .....h..\n4 ..h.....\n5 ....h...\n6 ........\n7 .......f\n");
  
}