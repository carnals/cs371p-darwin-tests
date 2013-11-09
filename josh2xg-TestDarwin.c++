#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"
#include <iostream> // endl, istream, ostream
#include "Darwin.h"

using namespace std;
/*  
   TESTING STRATEGY
   INSTEADING OF TESTING INDIVIDUAL FUNCTIONS
   WE TESTED THE WHOLE CLASS AND THEIR FUNCTIONS
   AS A CLASS UNIT
*/
TEST(Darwin, Instruction_1) {
	string test = "hop";
	//constructor
	Instruction ins = Instruction(test);
	//toString
	string name = ins.toString();
	ASSERT_EQ(test, name);
	vector<string> args = ins.getArgumentSet();
	//getArgumentSet
	ASSERT_EQ(1, args.size());}

TEST(Darwin, Instruction_2) {
	string test = "if_empty 4";
	//constructor
	Instruction ins = Instruction(test);
	//toString
	string name = ins.toString();
	ASSERT_EQ(test, name);
        vector<string> args = ins.getArgumentSet();
        //getArgumentSet
        ASSERT_EQ(2, args.size());}

TEST(Darwin, Instruction_3) {
	string test = "go";
	//constructor
	Instruction ins = Instruction(test);
	//toString
	string name = ins.toString();
	ASSERT_TRUE(name == "go");
        vector<string> args = ins.getArgumentSet();
        //getArgumentSet
        ASSERT_EQ(1, args.size());}

TEST(Darwin, Species_1) {
	//constructor 
	Species species = Species("hopper");
	Instruction ins = Instruction("h");
	//addInstruction
	species.addInstruction(ins);
	//toString
	string name = species.toString();
	string test = "hopper 1";
	ASSERT_EQ(test, name);
	//getInstruction
	Instruction* instptr = species.getInstruction(0);
	ASSERT_TRUE(instptr->toString() == "h");
	//getName
	ASSERT_EQ("hopper", species.getName());
	//getTotalNumOfInstructions
	ASSERT_EQ(1,species.getTotalNumOfInstructions());}

TEST(Darwin, Species_2) {
	//constructor
        Species species = Species("r");
        Instruction ins = Instruction("go 0");
	Instruction ins2 = Instruction("if_empty 3");
	//addInstruction
        species.addInstruction(ins);
	species.addInstruction(ins2);
	//toString
        string name = species.toString();
        string test = "r 2";
        ASSERT_EQ(test, name);
	//getInstruction
        Instruction* instptr = species.getInstruction(1);
        ASSERT_TRUE(instptr->toString() == "if_empty 3");
	//getName
	ASSERT_EQ("r", species.getName());
        //getTotalNumOfInstructions
        ASSERT_EQ(2,species.getTotalNumOfInstructions());}


TEST(Darwin, Species_3) {
	Instruction ifenemy3("if_enemy 3");
	Instruction infect("infect");
	Instruction left("left");
	Instruction go0("go 0");
	//constructor
	Species trapDNA("t");
	//addInstruction
	trapDNA.addInstruction(ifenemy3);
	trapDNA.addInstruction(left);
	trapDNA.addInstruction(go0);
	trapDNA.addInstruction(infect);
	trapDNA.addInstruction(go0);
	//toString
        string name = trapDNA.toString();
        string test = "t 5";
        ASSERT_EQ(test, name);
	//getInstruction
        Instruction* ip = trapDNA.getInstruction(3);
        ASSERT_TRUE(ip->toString() == "infect");
        //getName
        ASSERT_EQ("t", trapDNA.getName());
        //getTotalNumOfInstructions
        ASSERT_EQ(5,trapDNA.getTotalNumOfInstructions());}


TEST(Darwin, CreatureTest_1){

	Species testDNA("T");
	Instruction ifwall3("if_wall 3");
	Instruction hop("hop");
	Instruction left("left");
	Instruction go0("go 0");

	testDNA.addInstruction(ifwall3);
	testDNA.addInstruction(hop);
	testDNA.addInstruction(go0);
	testDNA.addInstruction(left);
	testDNA.addInstruction(go0);
	//constructor
	Creature test(testDNA, West, 3, 7);
 	ASSERT_TRUE(!test.hasMovedThisTurn());
	//move
	test.move();
	test.resetTurn();
	ASSERT_TRUE(!test.hasMovedThisTurn());
	test.move();
	//hasMovedThisTurn
	ASSERT_TRUE(test.hasMovedThisTurn());
	test.resetTurn();
	ASSERT_TRUE(!test.hasMovedThisTurn());
	//getDirection
	const int direction = 0;
	int directiontest= test.getDirection();
	ASSERT_EQ(direction, directiontest);
	//getRow
	const int row = 3;
	ASSERT_EQ(test.getRow(), row);
	//getCol
        const int col = 7;
        ASSERT_EQ(test.getCol(), col);
	//updatevision
	//getDNA
	
	//turnLeft
	
	//turnRight

	//getAssimilated

	//updateLocation

	//getSymbol
        const string symbol = "T";
	ASSERT_EQ(test.getSymbol(), symbol);
	//toString
	const string tostring = "T West 3 7 2";
	ASSERT_EQ(test.toString(), tostring);

}

TEST(Darwin, DarwinGame_1){

        Species testDNA("T");
        Instruction ifwall3("if_wall 3");
        Instruction hop("hop");
        Instruction left("left");
        Instruction go0("go 0");

        testDNA.addInstruction(ifwall3);
        testDNA.addInstruction(hop);
        testDNA.addInstruction(go0);
        testDNA.addInstruction(left);
        testDNA.addInstruction(go0);

        Creature test(testDNA, East, 3, 7);
	//constructor
	DarwinWorld game(8,8);
	//addCreature
	game.addCreature(test);
        ASSERT_TRUE(!test.hasMovedThisTurn());
	//simulate
	game.simulate();
        ASSERT_TRUE(!test.hasMovedThisTurn());
        ASSERT_TRUE(!test.hasMovedThisTurn());
        const int direction = 1;
        int directiontest= test.getDirection();
        ASSERT_EQ(direction, directiontest);
        const int row = 3;
        ASSERT_EQ(test.getRow(), row);
        const int col = 7;
        ASSERT_EQ(test.getCol(), col);
        const string symbol = "T";
        ASSERT_EQ(test.getSymbol(), symbol);
        const string tostring = "T North 3 7 4";
        ASSERT_EQ(test.toString(), tostring);
	//successful hop
	game.simulate();
	ASSERT_EQ("T North 2 7 2", test.toString());
}

TEST(Darwin, DarwinGame_2){

        Species foodDNA("f");
        Instruction hop("hop");
        Instruction left("left");
        Instruction go0("go 0");

        foodDNA.addInstruction(left);
        foodDNA.addInstruction(go0);

        Instruction ifenemy9("if_enemy 9");
        Instruction ifempty7("if_empty 7");
        Instruction ifrandom5("if_random 5");
        Instruction right("right");

        Instruction infect("infect");
        Species roverDNA("r");
        roverDNA.addInstruction(ifenemy9);
        roverDNA.addInstruction(ifempty7);
        roverDNA.addInstruction(ifrandom5);
        roverDNA.addInstruction(left);
        roverDNA.addInstruction(go0);
        roverDNA.addInstruction(right);
        roverDNA.addInstruction(go0);
        roverDNA.addInstruction(hop);
        roverDNA.addInstruction(go0);
        roverDNA.addInstruction(infect);
        roverDNA.addInstruction(go0);

        Creature food(foodDNA, West, 1, 1);
        Creature rover(roverDNA, North, 2, 1);
	//constructor
	DarwinWorld game (4, 4);
	//addCreature
	game.addCreature(food);
	game.addCreature(rover);
        const int direction = 0;
        int directiontest= food.getDirection();
        ASSERT_EQ(direction, directiontest);
        const string symbol = "f";
        ASSERT_EQ(food.getSymbol(), symbol);
	//simulate
	game.simulate();
	//succesful infect
	ASSERT_EQ("r South 1 1 0", food.toString());  
}
TEST(Darwin, DarwinGame_3){
	//rover vs best

	Instruction ifenemy9("if_enemy 9");
	Instruction ifempty7("if_empty 7");
	Instruction ifrandom5("if_random 5");
        Instruction go0("go 0");
        Instruction left("left");
	Instruction right("right");
        Instruction hop("hop");
	Instruction infect("infect");
	Species roverDNA("r");
	roverDNA.addInstruction(ifenemy9);
	roverDNA.addInstruction(ifempty7);
	roverDNA.addInstruction(ifrandom5);
	roverDNA.addInstruction(left);
	roverDNA.addInstruction(go0);
	roverDNA.addInstruction(right);
	roverDNA.addInstruction(go0);
	roverDNA.addInstruction(hop);
	roverDNA.addInstruction(go0);
	roverDNA.addInstruction(infect);
	roverDNA.addInstruction(go0);
	
	Instruction ifwall5("if_wall 5");
	Species bestDNA("b");
	bestDNA.addInstruction(ifenemy9);//0
        bestDNA.addInstruction(ifempty7);//1
    	bestDNA.addInstruction(ifwall5);//2
	bestDNA.addInstruction(right);//3
	bestDNA.addInstruction(go0);//4
	bestDNA.addInstruction(left);//5
	bestDNA.addInstruction(go0);//6
	bestDNA.addInstruction(hop);//7
	bestDNA.addInstruction(go0);//8
	bestDNA.addInstruction(infect);//9
	bestDNA.addInstruction(go0);//10
	Creature r0(roverDNA, East, 0, 0);
	Creature r1(roverDNA, West, 4, 4);
	Creature b0(bestDNA, South, 0, 4);
	Creature b1(bestDNA, North, 4, 0);
	//constructor
	DarwinWorld game(5, 5);
	//addCreature
	game.addCreature(r0);
	game.addCreature(r1);
	game.addCreature(b0);
	game.addCreature(b1);
	//simulate
	game.simulate();
	ASSERT_EQ("b",b0.getDNA()->getName());
	//suddendeath	
} 
