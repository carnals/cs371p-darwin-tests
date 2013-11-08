// ----------
// includes
// ----------

#include "Darwin.h"
#include "gtest/gtest.h"
using namespace std;
#define private public
// ----------
// TestDarwin
// ----------

////////////////////////////////////
//Species Tests
////////////////////////////////////
//Species.addInstruction - Species.getInstruction
TEST(Species,addInstruction1){
	Species x('t');
	x.addInstruction(0,"if_enemy 2");
	ASSERT_TRUE(x.getInstruction(0) == "if_enemy 2");
}
TEST(Species,addInstruction2){
        Species x('t');
        x.addInstruction(0,"if_enemy 2");
	x.addInstruction(1,"hop");
	x.addInstruction(2,"go 0");
        ASSERT_TRUE(x.getInstruction(1) == "hop");
}
TEST(Species,addInstruction3){
        Species x('t');
        x.addInstruction(0,"if_enemy 2");
	x.addInstruction(1,"hop");
	x.addInstruction(2,"go 0");
        ASSERT_TRUE(x.getInstruction(2) == "go 0");
}
//Species.getSymbol
TEST(Species,getSymbol1){
        Species x('t');
        ASSERT_TRUE(x.getSymbol() == 't');
}
TEST(Species,getSymbol2){
        Species x('f');
        ASSERT_TRUE(x.getSymbol() == 'f');
}
TEST(Species,getSymbol3){
        Species x('r');
        ASSERT_TRUE(x.getSymbol() == 'r');
}
////////////////////////////////////////
//Creature Tests
////////////////////////////////////////
//Creature.getSymbol
TEST(Creature,getSymbol1){
	Species x('t');
	Creature c(&x,EAST);
	ASSERT_TRUE(x.getSymbol() == (*c.getSpecies()).getSymbol());
}
TEST(Creature,getSymbol2){
        Species x('q');
        Creature c(&x,EAST);
        ASSERT_TRUE(x.getSymbol() == (*c.getSpecies()).getSymbol());
}
TEST(Creature,getSymbol3){
        Species x('f');
        Creature c(&x,EAST);
        ASSERT_TRUE(x.getSymbol() == (*c.getSpecies()).getSymbol());
}
//Creature.getSpecies
TEST(Creature,getSpecies1){
	Species x('t');
	Creature c(&x,EAST);
	ASSERT_TRUE(c.getSymbol() == 't');
}
TEST(Creature,getSpecies2){
        Species x('f');
        Creature c(&x,EAST);
        ASSERT_TRUE(c.getSymbol() == 'f');
}
TEST(Creature,getSpecies3){
        Species x('r');
        Creature c(&x,EAST);
        ASSERT_TRUE(c.getSymbol() == 'r');
}
//Creature.setSpecies
TEST(Creature,setSpecies1){
	Species x('t');
	Species y('r');
	Creature c(&y,EAST);
	c.setSpecies(&x);
	ASSERT_TRUE(c.getSpecies() == &x);
}
TEST(Creature,setSpecies2){
        Species x('q');
        Species y('r');
        Creature c(&y,EAST);
        c.setSpecies(&x);
        ASSERT_TRUE(c.getSpecies() == &x);
}
TEST(Creature,setSpecies3){
        Species x('r');
        Species y('r');
        Creature c(&y,EAST);
        c.setSpecies(&x);
        ASSERT_TRUE(c.getSpecies() == &x);
}
//Creature.getDirection
TEST(Creature,getDirection1){
	Species x('t');
	Creature c(&x,EAST);
	ASSERT_TRUE(c.getDirection() == EAST);
}
TEST(Creature,getDirection2){
        Species x('t');
        Creature c(&x,WEST);
        ASSERT_TRUE(c.getDirection() == WEST);
}
TEST(Creature,getDirection3){
        Species x('t');
        Creature c(&x,SOUTH);
        ASSERT_TRUE(c.getDirection() == SOUTH);
}

//Creature,setDirection
TEST(Creature,setDirection1){
	Species x('t');
	Creature c(&x,EAST);
	c.setDirection(WEST);
	ASSERT_TRUE(c.getDirection() == WEST);
}
TEST(Creature,setDirection2){
        Species x('t');
        Creature c(&x,EAST);
        c.setDirection(NORTH);
        ASSERT_TRUE(c.getDirection() == NORTH);
}
TEST(Creature,setDirection3){
        Species x('t');
        Creature c(&x,EAST);
        c.setDirection(SOUTH);
        ASSERT_TRUE(c.getDirection() == SOUTH);
}
//Creature,getInstruction
TEST(Creature,getInstruction1){
	Species x('t');
	x.addInstruction(0,"EXAMPLE INSTR");
	Creature c(&x,EAST);
	ASSERT_TRUE(c.getInstruction(0) == "EXAMPLE INSTR");
}
TEST(Creature,getInstruction2){
        Species x('t');
        x.addInstruction(0,"EXAMPLE INSTR");
	x.addInstruction(1,"HMM");
        Creature c(&x,EAST);
        ASSERT_TRUE(c.getInstruction(1) == "HMM");
}
TEST(Creature,getInstruction3){
        Species x('t');
        x.addInstruction(0,"EXAMPLE INSTR");
	x.addInstruction(1,"HMM");
	x.addInstruction(2,"NUM 2");
        Creature c(&x,EAST);
        ASSERT_TRUE(c.getInstruction(2) == "NUM 2");
}

////////////////////////////////////////
//DarwinGame Tests
////////////////////////////////////////
//DarwinGame.simulateMove
TEST(DarwinGame,simulateMove1){
}
//DarwinGame.addCreature
TEST(DarwinGame,addCreature1){
}
//DarwinGame.executeInstructions
TEST(DarwinGame,executeInstructions1){
}
//DarwinGame.executeHOP
TEST(DarwinGame,executeHOP1){
	DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
        game.addCreature(c,0,0);
        game.executeHOP(c,0);
        //ASSERT_TRUE(game.board[1] != 0); // wont let me even if i define private public
}
//DarwinGame.executeLEFT
TEST(DarwinGame,executeLEFT1){
	DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,NORTH);
        game.addCreature(c,0,0);
        game.executeLEFT(c,0);
        ASSERT_TRUE(c.getDirection() == WEST);
}
TEST(DarwinGame,executeLEFT2){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
        game.addCreature(c,0,0);
        game.executeLEFT(c,0);
        ASSERT_TRUE(c.getDirection() == NORTH);
}
TEST(DarwinGame,executeLEFT3){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,SOUTH);
        game.addCreature(c,0,0);
        game.executeLEFT(c,0);
        ASSERT_TRUE(c.getDirection() == EAST);
}
//DarwinGame.executeRIGHT
TEST(DarwinGame,executeRIGHT1){
	DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,NORTH);
        game.addCreature(c,0,0);
	game.executeRIGHT(c,0);
        ASSERT_TRUE(c.getDirection() == EAST);
}
TEST(DarwinGame,executeRIGHT2){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
        game.addCreature(c,0,0);
        game.executeRIGHT(c,0);
        ASSERT_TRUE(c.getDirection() == SOUTH);
}
TEST(DarwinGame,executeRIGHT3){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,SOUTH);
        game.addCreature(c,0,0);
        game.executeRIGHT(c,0);
        ASSERT_TRUE(c.getDirection() == WEST);
}

//DarwinGame.executeINFECT
TEST(DarwinGame,executeINFECT1){
	DarwinGame game(10,10);
        Species hop('h');
        Species rov('r');
        Creature c(&hop,EAST);
        Creature r(&rov,WEST);
        game.addCreature(c,0,0);
        game.addCreature(r,0,1);
	game.executeINFECT(c,0);
        ASSERT_TRUE(r.getSpecies() == &hop);
}/*
TEST(DarwinGame,executeINFECT2){
        DarwinGame game(10,10);
        Species hop('h');
        Species rov('r');
        Creature c(&hop,NORTH);
        Creature r(&rov,WEST);
        game.addCreature(c,1,1);
        game.addCreature(r,0,1);
        game.executeINFECT(c,0);
        ASSERT_TRUE(r.getSpecies() == &hop);
}
TEST(DarwinGame,executeINFECT3){
        DarwinGame game(10,10);
        Species hop('h');
        Species rov('r');
        Creature c(&hop,EAST);
        Creature r(&rov,WEST);
        game.addCreature(c,1,1);
        game.addCreature(r,1,2);
        game.executeINFECT(c,0);
        ASSERT_TRUE(r.getSpecies() == &hop);
}*/

//DarwinGame.is_empty
TEST(DarwinGame,is_empty1){
	DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
        game.addCreature(c,0,0);
        ASSERT_TRUE(game.is_empty(c,0) == true);
}
TEST(DarwinGame,is_empty2){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
	Creature c1(&hop,EAST);
        game.addCreature(c,0,0);
	game.addCreature(c,0,1);
        ASSERT_TRUE(game.is_empty(c,0) == false);
}
TEST(DarwinGame,is_empty3){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,NORTH);
        game.addCreature(c,0,0);
        ASSERT_TRUE(game.is_empty(c,0) == false);
}

//DarwinGame.is_wall
TEST(DarwinGame,is_wall1){
	DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,NORTH);
        game.addCreature(c,0,0);
        ASSERT_TRUE(game.is_wall(c,0) == true);
}
TEST(DarwinGame,is_wall2){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,EAST);
        game.addCreature(c,0,0);
        ASSERT_TRUE(game.is_wall(c,0) == false);
}
TEST(DarwinGame,is_wall3){
        DarwinGame game(10,10);
        Species hop('h');
        Creature c(&hop,WEST);
        game.addCreature(c,0,0);
        ASSERT_TRUE(game.is_wall(c,0) == false);
}
 
//DarwinGame.is_enemy
TEST(DarwinGame,is_enemy1){
	DarwinGame game(10,10);
	Species hop('h');
	Species rov('r');
	Creature c(&hop,EAST);
	Creature r(&rov,WEST);
	game.addCreature(c,0,0);
	game.addCreature(r,0,1);
	ASSERT_TRUE(game.is_enemy(c,0) == true);
}
TEST(DarwinGame,is_enemy2){
        DarwinGame game(10,10);
        Species hop('h');
        Species rov('r');
        Creature c(&hop,EAST);
        Creature r(&rov,WEST);
        game.addCreature(c,0,0);
        game.addCreature(r,0,2);
        ASSERT_TRUE(game.is_enemy(c,0) == false);
}
TEST(DarwinGame,is_enemy3){
        DarwinGame game(10,10);
        Species hop('h');
        Species rov('r');
        Creature c(&hop,SOUTH);
        Creature r(&rov,WEST);
        game.addCreature(c,0,0);
        game.addCreature(r,1,0);
        ASSERT_TRUE(game.is_enemy(c,0) == true);
}

