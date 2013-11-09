// ------------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2013
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

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> 

#include "gtest/gtest.h"

#include "Darwin.h"
//#include "Darwin.c++"

using namespace std;

// -------------
// TestDarwin
// -------------

//printBoard(ostream&) in class Darwin tests

TEST(TestDarwin, printBoard_1) {
  Darwin x = Darwin(2, 2);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
}

TEST(TestDarwin, printBoard_2) {
  Darwin x = Darwin(2, 3);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  012\n0 ...\n1 ...\n\n");
}

TEST(TestDarwin, printBoard_3) {
  Darwin x = Darwin(3, 2);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n2 ..\n\n");
}

//Darwin(int, int) constructor tests

TEST(TestDarwin, Darwin_1) {
  Darwin x = Darwin(4, 2);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n2 ..\n3 ..\n\n");
}

TEST(TestDarwin, Darwin_2) {
  Darwin x = Darwin(3, 6);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  012345\n0 ......\n1 ......\n2 ......\n\n");
}

TEST(TestDarwin, Darwin_3) {
  Darwin x = Darwin(1, 1);
  ostringstream w;
  x.printBoard(w);
  
  ASSERT_TRUE(w.str() == "Turn = 0.\n  0\n0 .\n\n");
}

// Species(str) Constructor tests

TEST(TestSpecies, Species_str_const1){
  Species x = Species("h");

  ASSERT_TRUE(x.print() == "h");
}

TEST(TestSpecies, Species_str_const2){
  Species h = Species("h");
  Species i = Species("i");
  Species j = Species("j");

  ASSERT_TRUE(h.print() == "h");
  ASSERT_TRUE(i.print() == "i");
  ASSERT_TRUE(j.print() == "j");
}

TEST(TestSpecies, Species_str_const3){
  Species x = Species("h");
  Species y = Species("");

  ASSERT_TRUE(x.print() == "h");
  ASSERT_TRUE(y.print() == "");
}

TEST(TestSpecies, Species_DefaultConst){
  Species x = Species();

  ASSERT_TRUE(x.print() == ".");
}

//left() method tests

TEST(TestSpecies, left1){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(2,2);

  Species turn = Species("t");
  turn.addInstruction("left");
  turn.addInstruction("hop");
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 t.\n1 ..\n\n");

  x.run_game();
  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 2.\n  01\n0 ..\n1 t.\n\n");

}

TEST(TestSpecies, left2){ 
  Darwin x = Darwin(2,2);

  Species turn = Species("t");
  turn.addInstruction("left");
  turn.addInstruction("hop");
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 t.\n1 ..\n\n");

  x.run_game();
  x.run_game();     //makes creature go in a square and end up back where it started
  x.run_game();
  x.run_game();
  x.run_game();
  x.run_game();
  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 8.\n  01\n0 t.\n1 ..\n\n");

}

TEST(TestSpecies, left3){ 
  Darwin x = Darwin(2,2);

  Species turn = Species("t");
  turn.addInstruction("left");
  turn.addInstruction("hop");
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 0, true);
  Creature t2 = Creature(turn, 1, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 0, 0);
  x.addCreature(t2, 0, 1);
  x.printBoard(z);

  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 tt\n1 ..\n\n");

  x.run_game();
  x.run_game();     

  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 2.\n  01\n0 t.\n1 t.\n\n");

}

// Infect tests

TEST(TestSpecies, infect1){
  Darwin x = Darwin(2, 1);

  Species infect = Species("i");
  infect.addInstruction("infect");
  infect.addInstruction("go 0");

  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");

  Creature i1 = Creature(infect, 1, true);
  Creature f1 = Creature(food, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(i1, 1, 0);
  x.addCreature(f1, 0, 0);
  x.printBoard(z);


  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 1.\n  0\n0 i\n1 i\n\n");

}

TEST(TestSpecies, infect2){
  Darwin x = Darwin(2, 1);

  Species infect = Species("i");
  infect.addInstruction("infect");
  infect.addInstruction("left");
  infect.addInstruction("go 0");

  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");

  Creature i1 = Creature(infect, 2, true);
  Creature f1 = Creature(food, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(i1, 1, 0);
  x.addCreature(f1, 0, 0);
  x.run_game();

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 1.\n  0\n0 f\n1 i\n\n");
  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 3.\n  0\n0 i\n1 i\n\n");

}

TEST(TestSpecies, infect3){
  Darwin x = Darwin(2, 2);

  Species infect = Species("i");
  infect.addInstruction("infect");
  infect.addInstruction("left");
  infect.addInstruction("go 0");

  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");

  Creature i1 = Creature(infect, 2, true);
  Creature i2 = Creature(infect, 2, true);
  Creature f1 = Creature(food, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(i1, 1, 0);
  x.addCreature(i2, 1, 1);
  x.addCreature(f1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 f.\n1 ii\n\n");

  x.run_game();
  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 3.\n  01\n0 i.\n1 ii\n\n");

}

// if_wall tests

TEST(TestSpecies, if_wall1) {
  Darwin x = Darwin(2, 2);

  Species hop = Species("h");
  hop.addInstruction("if_wall 3");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  hop.addInstruction("left");
  hop.addInstruction("go 0");


  Creature h1 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(h1, 0, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 .h\n1 ..\n\n");

  x.run_game();
  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 3.\n  01\n0 ..\n1 h.\n\n");
}

TEST(TestSpecies, if_wall2){
  Darwin x = Darwin(2,2);

  Species hop = Species("h");
  hop.addInstruction("if_wall 3");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  hop.addInstruction("left");
  hop.addInstruction("go 0");

  Creature h1 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(h1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 h.\n1 ..\n\n");

  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 2.\n  01\n0 ..\n1 h.\n\n");

}

TEST(TestSpecies, if_wall3){

  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_wall 2");
  hop.addInstruction("hop");
  hop.addInstruction("left");
  hop.addInstruction("go 0");
  int hopX = 0;
  int hopY = 0;
  int hopDir = 0;
  int progCount = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.if_wall(2, progCount, hopX, hopY, hopDir, grid) == false);
  ASSERT_TRUE(progCount == 2);
}


// if_enemy tests

TEST(TestSpecies, if_enemy1) {
  Darwin x = Darwin(2, 2);

  Species detect = Species("d");
  detect.addInstruction("if_enemy 3");
  detect.addInstruction("right");
  detect.addInstruction("go 0");
  detect.addInstruction("infect");
  detect.addInstruction("go 0");

  Species food = Species("f");
  food.addInstruction("right");
  food.addInstruction("go 0");

  Creature d1 = Creature(detect, 0, true);
  Creature f1 = Creature(food, 0, true);

  x.addCreature(d1, 1, 1);
  x.addCreature(f1, 0, 1);

  ostringstream w;
  ostringstream z;

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 .f\n1 .d\n\n");

  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 2.\n  01\n0 .d\n1 .d\n\n");

}

TEST(TestSpecies, if_enemy2) {
  Darwin x = Darwin(3, 3);

  Species detect = Species("d");
  detect.addInstruction("if_enemy 3");
  detect.addInstruction("hop");
  detect.addInstruction("go 0");
  detect.addInstruction("infect");
  detect.addInstruction("go 0");

  Species food = Species("f");
  food.addInstruction("right");
  food.addInstruction("go 0");

  Creature d1 = Creature(detect, 0, true);
  Creature f1 = Creature(food, 0, true);

  x.addCreature(d1, 0, 2);
  x.addCreature(f1, 0, 0);

  ostringstream w;
  ostringstream z;

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  012\n0 f.d\n1 ...\n2 ...\n\n");

  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 2.\n  012\n0 dd.\n1 ...\n2 ...\n\n");
  
}

TEST(TestSpecies, if_enemy3) {
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_enemy 3");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  hop.addInstruction("left");
  hop.addInstruction("go 0");
  int hopX = 0;
  int hopY = 1;
  int hopDir = 0;
  int progCount = 0;

  Species evil = Species("e");
  int hopX2 = 0;
  int hopY2 = 0;
  int hopDir2 = 0;
  //int progCount2 = 0;

  Creature h1 = Creature(hop, hopDir, true);
  Creature h2 = Creature(evil, hopDir2, true);

  grid[hopX][hopY] = h1;
  grid[hopX2][hopY2] = h2;
  
  ASSERT_TRUE(hop.if_enemy(3, progCount, hopX, hopY, hopDir, grid) == false);
  ASSERT_TRUE(progCount == 3);
  
}



//Species Print tests

TEST(TestSpecies, print1){
  Species tester = Species("t");
  Creature t1 = Creature(tester, 0, true);

  ASSERT_TRUE(t1.print() == "t");
}

TEST(TestSpecies, print2){
  Species tester = Species("t");
  Species tester2 = Species("2");
  Creature t1 = Creature(tester, 0, true);
  Creature t2 = Creature(tester2, 0, true);


  ASSERT_TRUE(t1.print() == "t");
  ASSERT_TRUE(t2.print() == "2");
}

TEST(TestSpecies, print3){
  Species tester = Species("t");
  Species tester2 = Species("2");
  Species tester3 = Species("a");
  Creature t1 = Creature(tester, 0, true);
  Creature t2 = Creature(tester2, 1, false);
  Creature t3 = Creature(tester3, 2, true);


  ASSERT_TRUE(t1.print() == "t");
  ASSERT_TRUE(t2.print() == "2");
  ASSERT_TRUE(t3.print() == "a");
}

//hop tests

TEST(TestSpecies, hop_WEST){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(2,2);
  
  Species hop = Species("t");
  hop.addInstruction("hop");

  Creature t1 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 1, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 ..\n1 .t\n\n");

  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 1.\n  01\n0 ..\n1 t.\n\n");
}

TEST(TestSpecies, hop_WALL){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(2,2);
  
  Species hop = Species("t");
  hop.addInstruction("hop");

  Creature t1 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 t.\n1 ..\n\n");

  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 1.\n  01\n0 t.\n1 ..\n\n");
}

TEST(TestSpecies, hop_NORTH){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(2,2);
  
  Species hop = Species("t");
  hop.addInstruction("hop");

  Creature t1 = Creature(hop, 1, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 1, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 ..\n1 .t\n\n");

  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 1.\n  01\n0 .t\n1 ..\n\n");
}

TEST(TestSpecies, hop_CREATURE){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(3,3);
  
  Species hop = Species("t");
  hop.addInstruction("hop");

  Creature t1 = Creature(hop, 3, true);
  Creature t2 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 1, 1);
  x.addCreature(t2, 2, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  012\n0 ...\n1 .t.\n2 .t.\n\n");

  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 1.\n  012\n0 ...\n1 .t.\n2 t..\n\n");
}

TEST(TestSpecies, hop_food){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 3;
  
  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  int foodX = 1;
  int foodY = 0;
  int foodDir = 0;

  Creature h1 = Creature(hop, hopDir, true);
  Creature f1 = Creature(food, foodDir, true);

  grid[hopX][hopY] = h1;
  grid[foodX][foodY] = f1;
  
  ASSERT_TRUE(hop.hop(hopX, hopY, hopDir, hopProgCount, grid) == true);
  ASSERT_TRUE(hopProgCount == 4);
  ASSERT_TRUE(grid[hopX][hopY].print() == "h");
  hopProgCount = 3;
}

TEST(TestSpecies, hop_5){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 3");
  hop.addInstruction("left");
  hop.addInstruction("go 0");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 3;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.hop(hopX, hopY, hopDir, hopProgCount, grid) == true);
  ASSERT_TRUE(hopProgCount == 4);
  ASSERT_TRUE(grid[hopX][hopY].print() == ".");
  ASSERT_TRUE(grid[hopX][hopY-1].print() == "h");  
}

TEST(TestSpecies, right_1){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  Darwin x = Darwin(2,2);

  Species turn = Species("t");
  turn.addInstruction("right");
  turn.addInstruction("hop");
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 1, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 0, 0);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 t.\n1 ..\n\n");

  x.run_game();
  x.run_game();
  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 2.\n  01\n0 .t\n1 ..\n\n");
}

TEST(TestSpecies, right_2){ 
  Darwin x = Darwin(3,3);

  Species turn = Species("t");
  turn.addInstruction("right");
  turn.addInstruction("hop");
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 1, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  012\n0 ...\n1 .t.\n2 ...\n\n");

  x.run_game();
  x.run_game();     
  x.run_game();
  x.run_game();
  x.run_game();
  x.run_game();


  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 6.\n  012\n0 ...\n1 ..t\n2 ...\n\n");

}

TEST(TestSpecies, right_3){ 
  Darwin x = Darwin(2,2);

  Species turn = Species("t");
  turn.addInstruction("right");
  turn.addInstruction("hop");
  turn.addInstruction("right");  
  turn.addInstruction("go 0");

  Creature t1 = Creature(turn, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(t1, 1, 0);
  x.printBoard(z);

  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 ..\n1 t.\n\n");

  x.run_game();
  x.run_game();     
  x.run_game(); 
  x.run_game(); 
  x.run_game(); 
  
  x.printBoard(w);
  ASSERT_TRUE(w.str() ==  "Turn = 5.\n  01\n0 ..\n1 t.\n\n");
}

TEST(TestSpecies, right_4){ // Can't really get the direction directly, so use hop instruction to ensure it's actually turning
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("right");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.right(hopDir, hopProgCount) == true);
  ASSERT_TRUE(hopDir == 1);
  ASSERT_TRUE(hopProgCount == 1);
}

//Creature default constructor

TEST(TestCreature, default_const1){
  Darwin x = Darwin(2, 2);

  Creature c = Creature();

  ASSERT_TRUE(c.print() == ".");

}

TEST(TestCreature, default_const2){
  Darwin x = Darwin(1, 1);
  ostringstream w;

  x.printBoard(w);
  ASSERT_TRUE(w.str() =="Turn = 0.\n  0\n0 .\n\n"); //checks if default constructor runs when Darwin created

}

TEST(TestCreature, default_const3){
  Darwin x = Darwin(2, 2);
  ostringstream w;

  x.printBoard(w);
  ASSERT_TRUE(w.str() =="Turn = 0.\n  01\n0 ..\n1 ..\n\n"); //checks if default constructor runs when Darwin created

}

TEST(TestCreature, print1){
  Species test = Species("t");
  Creature testC = Creature(test, 0, true);

  ASSERT_TRUE(testC.print() == "t");
}

TEST(TestCreature, print2){
  Species test = Species("t");
  Creature testC = Creature(test, 0, true);
  Creature testC2 = Creature(test, 1, false);

  ASSERT_TRUE(testC.print() == "t");
  ASSERT_TRUE(testC2.print() == "t");
}

TEST(TestCreature, print3){
  Species test = Species("t");
  Species test2 = Species("x");
  Species test3 = Species("v");
  Creature testC = Creature(test, 0, true);
  Creature testC2 = Creature(test2, 1, false);
  Creature testC3 = Creature(test3, 3, true);

  ASSERT_TRUE(testC.print() == "t");
  ASSERT_TRUE(testC2.print() == "x");
  ASSERT_TRUE(testC3.print() == "v");
}

//Creature evolve tests
TEST(TestCreature, evolve1){
  Species infecter = Species("i");
  Species infectee = Species("j");

  Creature infectC = Creature(infecter, 0, true);
  Creature infecteeC = Creature(infectee, 0, true);

  ASSERT_TRUE(infectC.print() == "i");
  ASSERT_TRUE(infecteeC.print() == "j");

  infecteeC.evolve(&infecter);

  ASSERT_TRUE(infectC.print() == "i");
  ASSERT_TRUE(infecteeC.print() == "i");
}

TEST(TestCreature, evolve2){
  Darwin x = Darwin(3, 3);

  Species infecter = Species("i");
  infecter.addInstruction("if_enemy 6");
  infecter.addInstruction("if_empty 4");
  infecter.addInstruction("right");
  infecter.addInstruction("go 0;");
  infecter.addInstruction("hop");
  infecter.addInstruction("go 0");
  infecter.addInstruction("infect");
  infecter.addInstruction("go 0");


  Species infectee = Species("j");
  infectee.addInstruction("right");
  infectee.addInstruction("go 0");

  Creature infectC = Creature(infecter, 3, true);
  Creature infecteeC = Creature(infectee, 0, true);

  x.addCreature(infectC, 0, 2);
  x.addCreature(infecteeC, 2, 2);

  ostringstream w;
  ostringstream z;

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  012\n0 ..i\n1 ...\n2 ..j\n\n");

  x.run_game();
  x.run_game();
  x.run_game();
  x.run_game();
  

   x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 4.\n  012\n0 ...\n1 .i.\n2 ..i\n\n");
}

TEST(TestCreature, evolve3){
  Species infecter = Species("i");
  Species infectee = Species("j");

  Creature infectC = Creature(infecter, 0, true);
  Creature infecteeC = Creature(infectee, 0, true);
  Creature infecteeC2 = Creature(infectee, 1, true);


  ASSERT_TRUE(infectC.print() == "i");
  ASSERT_TRUE(infecteeC.print() == "j");
  ASSERT_TRUE(infecteeC2.print() == "j");

  infecteeC.evolve(&infecter);

  ASSERT_TRUE(infectC.print() == "i");
  ASSERT_TRUE(infecteeC.print() == "i");
  ASSERT_TRUE(infecteeC2.print() == "j");

  infecteeC2.evolve(&infecter);

  ASSERT_TRUE(infectC.print() == "i");
  ASSERT_TRUE(infecteeC.print() == "i");
  ASSERT_TRUE(infecteeC2.print() == "i");
}


TEST(TestSpecies, if_empty_1){
  Darwin x = Darwin(3,3);

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");

  Creature h1 = Creature(hop, 0, true);
  ostringstream z;
  ostringstream w;

  x.addCreature(h1, 1, 1);
  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  012\n0 ...\n1 .h.\n2 ...\n\n");

  x.run_game();
  x.run_game();
  x.run_game();

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 3.\n  012\n0 ...\n1 ...\n2 h..\n\n");
}

TEST(TestSpecies, if_empty_2){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int progCount = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.if_empty(2, progCount, hopX, hopY, hopDir, grid) == false);
  ASSERT_TRUE(progCount == 2);
}

TEST(TestSpecies, if_empty_Food){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 0;
  
  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  int foodX = 1;
  int foodY = 0;
  int foodDir = 0;

  Creature h1 = Creature(hop, hopDir, true);
  Creature f1 = Creature(food, foodDir, true);

  grid[hopX][hopY] = h1;
  grid[foodX][foodY] = f1;
  
  ASSERT_TRUE(hop.if_empty(2, hopProgCount, hopX, hopY, hopDir, grid) == false);
  ASSERT_TRUE(hopProgCount == 1);
}

TEST(TestSpecies, if_empty_Wall){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 0;
  int hopDir = 0;
  int hopProgCount = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.if_empty(2, hopProgCount, hopX, hopY, hopDir, grid) == false);
  ASSERT_TRUE(hopProgCount == 1);
}

TEST(TestSpecies, go_1){
  Species hop = Species("h");
  int progCount = 0;
  
  ASSERT_TRUE(hop.go(2, progCount) == false);
  ASSERT_TRUE(progCount == 2);
}
  
TEST(TestSpecies, go_2){
  Species hop = Species("h");
  int progCount = 3;
  
  ASSERT_TRUE(hop.go(2, progCount) == false);
  ASSERT_TRUE(progCount == 2);
}

TEST(TestSpecies, go_3){
  Species hop = Species("h");
  int progCount = 0;
  
  ASSERT_TRUE(hop.go(2, progCount) == false);
  ASSERT_TRUE(progCount == 2);
  
  ASSERT_TRUE(hop.go(1, progCount) == false);
  ASSERT_TRUE(progCount == 1);
}

//peek tests
TEST(TestSpecies, peek1){
  
  Species hop = Species("h");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  ASSERT_TRUE(hop.peek(hopX, hopY, hopDir) == true);
  ASSERT_TRUE(hopX == 1);
  ASSERT_TRUE(hopY == 0);
}

TEST(TestSpecies, peek2){
  
  Species hop = Species("o");
  int hopX = 0;
  int hopY = 0;
  int hopDir = 3;

  Creature h1 = Creature(hop, hopDir, true);


  ASSERT_TRUE(hop.peek(hopX, hopY, hopDir) == true);
  ASSERT_TRUE(hopX == 1);
  ASSERT_TRUE(hopY == 0);
}

TEST(TestSpecies, peek3){
  
  Species hop = Species("p");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 1;

  Creature h1 = Creature(hop, hopDir, true);

  ASSERT_TRUE(hop.peek(hopX, hopY, hopDir) == true);
  ASSERT_TRUE(hopX == 0);
  ASSERT_TRUE(hopY == 1);
}

//check_empty tests
TEST(TestSpecies, check_empty1){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  
  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 0;
  int hopY = 0;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.check_empty(hopX, hopY, grid) == false);
}

TEST(TestSpecies, check_empty2){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  
  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY-1] = Creature();
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.check_empty(hopX, hopY-1, grid) == true);
}

TEST(TestSpecies, check_empty3){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  
  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY-1] = Creature(hop, hopDir, true);
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.check_empty(hopX, hopY-1, grid) == false);
}


TEST(TestCreature, takeTurn_1){ 
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));
  bool gameBool = true;
  
  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == true);
}

TEST(TestCreature, takeTurn_2){ 
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));
  bool gameBool = true;

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == true);
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == false);
}

TEST(TestCreature, takeTurn_3){ 
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));
  bool gameBool = true;
  
  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);

  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == true);
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == false);
  
  gameBool = false;
  
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == true);
  ASSERT_TRUE(h1.takeTurn(grid, gameBool, hopX, hopY) == false);
}

TEST(TestCreature, Creature_SpeciesConstructor_1){
  Species hop = Species("h");

  Creature h1 = Creature(hop, 0, true);
  
  ASSERT_TRUE(h1.print() == "h");
}

TEST(TestCreature, Creature_SpeciesConstructor_2){
  Species hop = Species("h");
  Species y = Species("");

  Creature h2 = Creature(hop, 0, true);
  Creature y1 = Creature(y, 0, true);
  Creature h1 = Creature(hop, 0, true);
  
  ASSERT_TRUE(h1.print() == "h");
  ASSERT_TRUE(y1.print() == "");
  ASSERT_TRUE(h2.print() == "h");
}

TEST(TestCreature, Creature_SpeciesConstructor_3){
  Species hop = Species("h");
  Species x = Species("h");
  Species y = Species("");

  Creature x1 = Creature(x, 0, true);
  Creature y1 = Creature(y, 0, true);
  Creature h1 = Creature(hop, 0, true);
  
  ASSERT_TRUE(x1.print() == "h");
  ASSERT_TRUE(y1.print() == "");
  ASSERT_TRUE(h1.print() == "h");
}

//Darwin Add Creature tests
TEST(TestDarwin, add_Creature1){
  Darwin x = Darwin(2, 2);

  ostringstream w;
  ostringstream z;

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");

  Species spec = Species("h");
  Creature c1 = Creature(spec, 0, true);

  x.addCreature(c1, 0, 0);

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 h.\n1 ..\n\n");
}

TEST(TestDarwin, add_Creature2){
  Darwin x = Darwin(2, 2);

  ostringstream w;
  ostringstream z;

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");

  Species spec = Species("h");
  Species spec2 = Species("i");

  Creature c1 = Creature(spec, 0, true);
  Creature c2 = Creature(spec2, 0, true);

  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 hi\n1 ..\n\n");
}

TEST(TestDarwin, add_Creature3){
  Darwin x = Darwin(2, 2);

  ostringstream w;
  ostringstream z;

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");

  Species spec = Species("h");
  Species spec2 = Species("i");
  Species spec3 = Species(":");
  Species spec4 = Species(")");

  Creature c1 = Creature(spec, 0, true);
  Creature c2 = Creature(spec2, 0, true);
  Creature c3 = Creature(spec3, 0, true);
  Creature c4 = Creature(spec4, 0, true);



  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);
  x.addCreature(c3, 1, 0);
  x.addCreature(c4, 1, 1);

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 0.\n  01\n0 hi\n1 :)\n\n");
}

//Darwin run_game Tests
TEST(TestDarwin, run_game1){
  Darwin x = Darwin(2, 2);

  ostringstream w;
  ostringstream z;

  Species test = Species("t");
  test.addInstruction("hop");
  test.addInstruction("go 0");

  Creature t1 = Creature(test, 0, true);

  x.addCreature(t1, 1, 1);

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 ..\n1 .t\n\n");

  x.run_game();

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 1.\n  01\n0 ..\n1 t.\n\n");
}

TEST(TestDarwin, run_game2){
  Darwin x = Darwin(2, 2);

  ostringstream w;
  ostringstream z;

  Species test = Species("t");
  test.addInstruction("hop");
  test.addInstruction("go 0");

  Creature t1 = Creature(test, 0, true);
  Creature t2 = Creature(test, 2, true);

  x.addCreature(t1, 1, 1);
  x.addCreature(t2, 0, 0);

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  01\n0 t.\n1 .t\n\n");

  x.run_game();

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 1.\n  01\n0 .t\n1 t.\n\n");
}

TEST(TestDarwin, run_game3){
  Darwin x = Darwin(3, 3);

  ostringstream w;
  ostringstream z;

  Species test = Species("t");
  test.addInstruction("hop");
  test.addInstruction("go 0");

  Species test2 = Species("2");
  test2.addInstruction("hop");
  test2.addInstruction("right");
  test2.addInstruction("go 0");

  Creature t1 = Creature(test, 2, true);
  Creature t2 = Creature(test2, 0, true);

  x.addCreature(t1, 0, 0);
  x.addCreature(t2, 2, 2);

  x.printBoard(w);
  ASSERT_TRUE(w.str() == "Turn = 0.\n  012\n0 t..\n1 ...\n2 ..2\n\n");

  x.run_game();
  x.run_game();
  x.run_game();

  x.printBoard(z);
  ASSERT_TRUE(z.str() == "Turn = 3.\n  012\n0 ..t\n1 .2.\n2 ...\n\n");
}

TEST(TestSpecies, check_wall_true){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 0;
  int hopY = 0;
  int hopDir = 0;

  Creature h1 = Creature(hop, hopDir, true);
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.check_wall(hopX, hopY-1, grid) == true);
}

TEST(TestSpecies, check_wall_empty){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 2;
  int hopY = 2;
  int hopDir = 0;
  
  Creature h1 = Creature(hop, hopDir, true);
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.check_wall(hopX, hopY-1, grid) == false);
}

TEST(TestSpecies, check_wall_food){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 2");
  hop.addInstruction("left");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  
  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  int foodX = 1;
  int foodY = 0;
  int foodDir = 0;

  Creature h1 = Creature(hop, hopDir, true);
  Creature f1 = Creature(food, foodDir, true);

  grid[hopX][hopY] = h1;
  grid[foodX][foodY] = f1;
  
  ASSERT_TRUE(hop.check_wall(hopX, hopY-1, grid) == false);
}

TEST(TestSpecies, addInstruction_1){
  Species hop = Species("h");
  ASSERT_TRUE(hop.addInstruction("left") == true);
}

TEST(TestSpecies, addInstruction_2){
  Species hop = Species("h");
  ASSERT_TRUE(hop.addInstruction("left") == true);
  ASSERT_TRUE(hop.addInstruction("right") == true);
}

TEST(TestSpecies, addInstruction_3){
  Species hop = Species("h");
  ASSERT_TRUE(hop.addInstruction("left") == true);
  ASSERT_TRUE(hop.addInstruction("right") == true);
  
  Species turn = Species("t");
  ASSERT_TRUE(hop.addInstruction("left") == true);
  ASSERT_TRUE(hop.addInstruction("go 0") == true);
}

TEST(TestSpecies, action_1){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 3");
  hop.addInstruction("if_wall 4");
  hop.addInstruction("if_enemy 4");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  hop.addInstruction("left");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 0;

  Creature h1 = Creature(hop, hopDir, true);
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 4);
}

TEST(TestSpecies, action_2){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species hop = Species("h");
  hop.addInstruction("if_empty 3");
  hop.addInstruction("if_wall 5");
  hop.addInstruction("if_enemy 5");
  hop.addInstruction("hop");
  hop.addInstruction("go 0");
  hop.addInstruction("left");
  hop.addInstruction("go 0");
  int hopX = 1;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 0;

  Creature h1 = Creature(hop, hopDir, true);
  grid[hopX][hopY] = h1;
  
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 4);
  hopY -= 1;
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 6);
}

TEST(TestSpecies, action_3){
  vector<vector<Creature> > grid = vector<vector<Creature> >(3,vector<Creature>(3));

  Species food = Species("f");
  
  Species hop = Species("h");
  hop.addInstruction("if_empty 3");	//0
  hop.addInstruction("if_wall 5");	//1
  hop.addInstruction("if_enemy 7");	//2
  hop.addInstruction("hop");		//3
  hop.addInstruction("go 0");		//4
  hop.addInstruction("left");		//5
  hop.addInstruction("go 0");		//6
  hop.addInstruction("infect");		//7
  hop.addInstruction("go 0");		//8
  int hopX = 0;
  int hopY = 1;
  int hopDir = 0;
  int hopProgCount = 0;

  Creature h1 = Creature(hop, hopDir, true);
  Creature f1 = Creature(food, 0, true);
  
  grid[hopX][hopY] = h1;
  grid[1][0] = f1;
  
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 4);
  hopY -= 1;
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 6);
  hopDir = 3;
  ASSERT_TRUE(hop.action(hopProgCount, hopX, hopY, hopDir, grid) == true);
  ASSERT_TRUE(hopProgCount == 8);
}
