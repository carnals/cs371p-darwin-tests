#include <algorithm> // count
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream 
#include <vector>
#include <string>
#include <stdexcept>

#include "gtest/gtest.h"
#define private public
#include "Darwin.h"

using namespace std;
//-------------
//Species Tests
//-------------
TEST(TestDarwin, addInstruction_1){
	Species s;
	s.addInstruction("Hello");
	ASSERT_TRUE(s.instructions[0].compare("Hello") == 0);	
}

TEST(TestDarwin, addInstruction_2){
	Species s;
	s.addInstruction("Hello");
	s.addInstruction("World");
	ASSERT_TRUE(s.instructions[0].compare("Hello") == 0);
	ASSERT_TRUE(s.instructions[1].compare("World") == 0);		
}

TEST(TestDarwin, addInstruction_3){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	s.addInstruction("!!!");
	ASSERT_TRUE(s.instructions[0].compare("Hi") == 0);
	ASSERT_TRUE(s.instructions[1].compare("there") == 0);	
	ASSERT_TRUE(s.instructions[2].compare("!!!") == 0);		
}

TEST(TestDarwin, getInstructionAt_1){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	s.addInstruction("!!!");
	ASSERT_TRUE(s.getInstructionAt(0).compare("Hi") == 0);		
}

TEST(TestDarwin, getInstructionAt_2){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	s.addInstruction("!!!");
	ASSERT_TRUE(s.getInstructionAt(1).compare("there") == 0);		
}

TEST(TestDarwin, getInstructionAt_3){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	s.addInstruction("!!!");
	ASSERT_TRUE(s.getInstructionAt(2).compare("!!!") == 0);		
}

TEST(TestDarwin, getInstructionAt_4){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	s.addInstruction("!!!");
	s.addInstruction("How are you?");
	ASSERT_TRUE(s.getInstructionAt(3).compare("How are you?") == 0);		
}

TEST(TestDarwin, instructionSize_1){
	Species s;
	s.addInstruction("Hi");
	ASSERT_TRUE(s.instructionsSize() == 1);		
}


TEST(TestDarwin, instructionSize_2){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there");
	ASSERT_TRUE(s.instructionsSize() == 2);		
}

TEST(TestDarwin, instructionSize_3){
	Species s;
	ASSERT_TRUE(s.instructionsSize() == 0);		
}

TEST(TestDarwin, instructionSize_4){
	Species s;
	s.addInstruction("Hi");
	s.addInstruction("there.");
	s.addInstruction("How");
	s.addInstruction("are");
	s.addInstruction("you?");
	ASSERT_TRUE(s.instructionsSize() == 5);		
}

//--------------
//Creature tests
//--------------
 TEST(TestDarwin, Creature_1){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.sName.compare("s") == 0);		
} 

 TEST(TestDarwin, Creature_2){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.rVal == 1);
	ASSERT_TRUE(temp.cVal == 2);	
} 

 TEST(TestDarwin, Creature_3){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.direc == north);		
} 

 TEST(TestDarwin, Creature_4){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.madeMove == false);		
} 

TEST(TestDarwin, Creature_5){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.progCount == 0);		
} 

TEST(TestDarwin, Creature_6){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 2);
	ASSERT_TRUE(temp.species.getInstructionAt(1).compare("go 0") == 0);		
} 

TEST(TestDarwin, calcNextPos_1){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 1, 1);
	vector<int> nextPos = temp.calcNextPos();
	ASSERT_TRUE(nextPos[0] == 0);	
	ASSERT_TRUE(nextPos[1] == 1);	
} 

TEST(TestDarwin, calcNextPos_2){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", east, 3, 4);
	vector<int> nextPos = temp.calcNextPos();
	ASSERT_TRUE(nextPos[0] == 3);	
	ASSERT_TRUE(nextPos[1] == 5);	
} 

TEST(TestDarwin, calcNextPos_3){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 2, 5);
	vector<int> nextPos = temp.calcNextPos();
	ASSERT_TRUE(nextPos[0] == 3);	
	ASSERT_TRUE(nextPos[1] == 5);	
} 

TEST(TestDarwin, calcNextPos_4){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	vector<int> nextPos = temp.calcNextPos();
	ASSERT_TRUE(nextPos[0] == 5);	
	ASSERT_TRUE(nextPos[1] == 5);	
} 

TEST(TestDarwin, getInfected_1){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	Species j; 
	j.addInstruction("hop");
 	j.addInstruction("left");
 	temp.getInfected(j, "j");
	ASSERT_TRUE(temp.sName.compare("j") == 0);	

} 

TEST(TestDarwin, getInfected_2){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	Species j; 
	j.addInstruction("hop");
 	j.addInstruction("left");
 	temp.getInfected(j, "j");
	ASSERT_TRUE(temp.species.getInstructionAt(1).compare("left") == 0);	
} 

TEST(TestDarwin, getInfected_3){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	temp.progCount = 1;
	Species j; 
	j.addInstruction("hop");
 	j.addInstruction("left");
 	temp.getInfected(j, "j");
	ASSERT_TRUE(temp.progCount == 0);	
} 

TEST(TestDarwin, getSpecies_1){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	ASSERT_TRUE(temp.getSpecies().getInstructionAt(0).compare("hop") == 0);	
}

TEST(TestDarwin, getSpecies_2){
 	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	ASSERT_TRUE(temp.getSpecies().getInstructionAt(1).compare("go 0") == 0);	
}

TEST(TestDarwin, getSpecies_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	Species j; 
	j.addInstruction("hop");
 	j.addInstruction("left");
 	temp.getInfected(j, "j");
	ASSERT_TRUE(temp.getSpecies().getInstructionAt(1).compare("left") == 0);	
} 

TEST(TestDarwin, getName_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	ASSERT_TRUE(temp.getName().compare("s") == 0);	
} 

TEST(TestDarwin, getName_2){
	Species a;
 	a.addInstruction("hop");
 	a.addInstruction("right");
	Creature temp (a, "a", west, 5, 6);
	ASSERT_TRUE(temp.getName().compare("a") == 0);	
}

TEST(TestDarwin, getName_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	Species j; 
	j.addInstruction("hop");
 	j.addInstruction("left");
 	temp.getInfected(j, "j");
	ASSERT_TRUE(temp.getName().compare("j") == 0);	
} 

TEST(TestDarwin, hop_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	temp.hop();
	ASSERT_TRUE(temp.rVal == 5);	
	ASSERT_TRUE(temp.cVal == 5);	
} 

TEST(TestDarwin, hop_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 5, 6);
	temp.hop();
	ASSERT_TRUE(temp.rVal == 4);	
	ASSERT_TRUE(temp.cVal == 6);	
}

TEST(TestDarwin, hop_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", east, 5, 6);
	temp.hop();
	ASSERT_TRUE(temp.rVal == 5);	
	ASSERT_TRUE(temp.cVal == 7);	
}

TEST(TestDarwin, hop_4){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.hop();
	ASSERT_TRUE(temp.rVal == 6);	
	ASSERT_TRUE(temp.cVal == 6);	
}

TEST(TestDarwin, left_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 5, 6);
	temp.left();
	ASSERT_TRUE(temp.direc == west);	
}

TEST(TestDarwin, left_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", east, 5, 6);
	temp.left();
	ASSERT_TRUE(temp.direc == north);	
}

TEST(TestDarwin, left_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.left();
	ASSERT_TRUE(temp.direc == east);	
}

TEST(TestDarwin, left_4){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	temp.left();
	ASSERT_TRUE(temp.direc == south);	
}

TEST(TestDarwin, right_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", west, 5, 6);
	temp.right();
	ASSERT_TRUE(temp.direc == north);	
}

TEST(TestDarwin, right_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", north, 5, 6);
	temp.right();
	ASSERT_TRUE(temp.direc == east);	
}

TEST(TestDarwin, right_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", east, 5, 6);
	temp.right();
	ASSERT_TRUE(temp.direc == south);	
}

TEST(TestDarwin, right_4){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.right();
	ASSERT_TRUE(temp.direc == west);	
}

TEST(TestDarwin, moved_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.moved(true);
	ASSERT_TRUE(temp.madeMove == true);	
}

TEST(TestDarwin, moved_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.moved(false);
	ASSERT_TRUE(temp.madeMove == false);	
}

TEST(TestDarwin, hasMadeMove_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	ASSERT_TRUE(temp.hasMadeMove() == false);	
}

TEST(TestDarwin, hasMadeMove_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	temp.madeMove = true;
	ASSERT_TRUE(temp.hasMadeMove() == true);	
}

TEST(TestDarwin, hasMadeMove_3){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10, 10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.hasMadeMove() == true);	
}

TEST(TestDarwin, makeMove_1){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.rVal == 6);
	ASSERT_TRUE(temp.cVal == 6);
}

TEST(TestDarwin, makeMove_2){
	Species s;
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.rVal == 7);
	ASSERT_TRUE(temp.cVal == 6);
}

TEST(TestDarwin, makeMove_3){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == east);
	ASSERT_TRUE(temp.rVal == 5);
	ASSERT_TRUE(temp.cVal == 6);
}

TEST(TestDarwin, makeMove_4){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == north);
	ASSERT_TRUE(temp.rVal == 5);
	ASSERT_TRUE(temp.cVal == 6);
}

TEST(TestDarwin, makeMove_5){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == east);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.rVal == 5);
	ASSERT_TRUE(temp.cVal == 7);
}

TEST(TestDarwin, makeMove_6){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("go 0");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == east);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.rVal == 5);
	ASSERT_TRUE(temp.cVal == 7);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == north);
}

TEST(TestDarwin, makeMove_7){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("if_empty 0");
 	s.addInstruction("go 1");
	Creature temp (s, "s", south, 5, 6);
	Board b (10,10);
	b.addCreature(temp, 5, 6);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == east);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.rVal == 5);
	ASSERT_TRUE(temp.cVal == 7);
	temp.makeMove(&b);
	ASSERT_TRUE(temp.direc == north);
}


//-----------
//Board Tests
//-----------
TEST(TestDarwin, Board_1){
	Board b (10, 10);
	ASSERT_TRUE(b.width == 10);
	ASSERT_TRUE(b.height == 10);
}

TEST(TestDarwin, Board_2){
	Board b (5, 10);
	ASSERT_TRUE(b.width == 10);
	ASSERT_TRUE(b.height == 5);
}

TEST(TestDarwin, Board_3){
	Board b (4, 7);
	ASSERT_TRUE(b.width == 7);
	ASSERT_TRUE(b.height == 4);
}

TEST(TestDarwin, Board_4){
	try {
		Board b (0, 0);
	}
	catch(const invalid_argument&){
		cout << "invalid_argument exception thrown" << endl;
	}
}

TEST(TestDarwin, addCreature_1){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("if_empty 0");
 	s.addInstruction("go 1");
	Creature temp (s, "s", south, 5, 6);
	Board b (10, 10);
	b.addCreature(temp, 5, 6);
	ASSERT_TRUE(b.grid[5][6].getName().compare("s") == 0);
}

TEST(TestDarwin, addCreature_2){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("if_empty 0");
 	s.addInstruction("go 1");
	Creature temp (s, "s", north, 3, 2);
	Board b (10, 10);
	b.addCreature(temp, 3, 2);
	ASSERT_TRUE(b.grid[3][2].getName().compare("s") == 0);
}

TEST(TestDarwin, addCreature_3){
	Species s;
 	s.addInstruction("left");
 	s.addInstruction("hop");
 	s.addInstruction("if_empty 0");
 	s.addInstruction("go 1");
	Creature temp (s, "s", north, 3, 2);
	Board b (10, 10);
	b.addCreature(temp, 3, 2);
	ASSERT_TRUE(b.grid[3][2].rVal == 3);
	ASSERT_TRUE(b.grid[3][2].cVal == 2);
}

TEST(TestDarwin, addCreature_4){
	try{
		Species s;
	 	s.addInstruction("left");
	 	s.addInstruction("hop");
	 	s.addInstruction("if_empty 0");
	 	s.addInstruction("go 1");
		Creature temp (s, "s", north, 3, 2);

		Species j;
	 	j.addInstruction("left");
	 	j.addInstruction("hop");
	 	j.addInstruction("go 0");
	 	Creature temp2 (j, "j", south, 3, 2);

		Board b (10, 10);
		b.addCreature(temp, 3, 2);
		b.addCreature(temp2, 3, 2);
	}
	catch(const invalid_argument&){
		cout << "Invalid_argument: Trying to add a Creature to an occupied spot" << endl;
	}
}

TEST(TestDarwin, addCreature_5){
	try{
		Species s;
	 	s.addInstruction("left");
	 	s.addInstruction("hop");
	 	s.addInstruction("if_empty 0");
	 	s.addInstruction("go 1");
		Creature temp (s, "s", north, 12, 12);

		Board b (10, 10);
		b.addCreature(temp, 12, 12);
	}
	catch(const out_of_range&){
		cout << "out_of_range: Trying to add a Creature to outside the grid in Board class" << endl;
	}
}

TEST(TestDarwin, addCreature_6){
	try{
		Species s;
	 	s.addInstruction("left");
	 	s.addInstruction("hop");
	 	s.addInstruction("if_empty 0");
	 	s.addInstruction("go 1");
		Creature temp (s, "s", north, 12, 3);

		Board b (10, 10);
		b.addCreature(temp, 12, 3);
	}
	catch(const out_of_range&){
		cout << "out_of_range: Trying to add a Creature to outside the grid in Board class" << endl;
	}
}

TEST(TestDarwin, addCreature_7){
	try{
		Species s;
	 	s.addInstruction("left");
	 	s.addInstruction("hop");
	 	s.addInstruction("if_empty 0");
	 	s.addInstruction("go 1");
		Creature temp (s, "s", north, 1, 5);

		Board b (10, 10);
		b.addCreature(temp, -1, 5);
	}
	catch(const out_of_range&){
		cout << "out_of_range: Trying to add a Creature to outside the grid in Board class" << endl;
	}
}

TEST(TestDarwin, addCreature_8){
	try{
		Species s;
	 	s.addInstruction("left");
	 	s.addInstruction("hop");
	 	s.addInstruction("if_empty 0");
	 	s.addInstruction("go 1");
		Creature temp (s, "s", north, 1, 5);

		Board b (10, 10);
		b.addCreature(temp, -1, -5);
	}
	catch(const out_of_range&){
		cout << "out_of_range: Trying to add a Creature to outside the grid in Board class" << endl;
	}
}

TEST(TestDarwin, isMoveOk_1){
	Species s;
	s.addInstruction("left");
	s.addInstruction("hop");
	s.addInstruction("if_empty 0");
	s.addInstruction("go 1");
	Creature temp (s, "s", north, 1, 5);

	Board b (10, 10);
	b.addCreature(temp, 1, 5);
	ASSERT_TRUE(b.isMoveOk(0, 5));
}

TEST(TestDarwin, isMoveOk_2){
	Species s;
	s.addInstruction("left");
	s.addInstruction("hop");
	s.addInstruction("if_empty 0");
	s.addInstruction("go 1");
	Creature temp (s, "s", south, 1, 5);

	Board b (10, 10);
	b.addCreature(temp, 1, 5);
	ASSERT_TRUE(b.isMoveOk(2, 5));
}

TEST(TestDarwin, isMoveOk_3){
	Species s;
	s.addInstruction("left");
	s.addInstruction("hop");
	s.addInstruction("if_empty 0");
	s.addInstruction("go 1");
	Creature temp (s, "s", south, 1, 5);
	Creature temp2 (s, "s", east, 2, 5);

	Board b (10, 10);
	b.addCreature(temp, 1, 5);
	b.addCreature(temp2, 2, 5);
	ASSERT_TRUE(!b.isMoveOk(2, 5));
}

TEST(TestDarwin, isPosOnBoard_1){
	Board b (10, 10);
	ASSERT_TRUE(b.isPosOnBoard(6, 7));
}

TEST(TestDarwin, isPosOnBoard_2){
	Board b (10, 10);
	ASSERT_TRUE(!b.isPosOnBoard(-6, 7));
}

TEST(TestDarwin, isPosOnBoard_3){
	Board b (10, 10);
	ASSERT_TRUE(!b.isPosOnBoard(6, -7));
}

TEST(TestDarwin, isPosOnBoard_4){
	Board b (10, 10);
	ASSERT_TRUE(!b.isPosOnBoard(10, 10));
}

TEST(TestDarwin, isPosOnBoard_5){
	Board b (10, 10);
	ASSERT_TRUE(!b.isPosOnBoard(15, 5));
}

TEST(TestDarwin, isPosOnBoard_6){
	Board b (10, 10);
	ASSERT_TRUE(!b.isPosOnBoard(5, 15));
}

TEST(TestDarwin, if_wall_1){
	Board b (10, 10);
	ASSERT_TRUE(b.if_wall(10, 5));
}

TEST(TestDarwin, if_wall_2){
	Board b (10, 10);
	ASSERT_TRUE(b.if_wall(4, 10));
}

TEST(TestDarwin, if_wall_3){
	Board b (10, 10);
	ASSERT_TRUE(b.if_wall(-1, 4));
}

TEST(TestDarwin, if_wall_4){
	Board b (10, 10);
	ASSERT_TRUE(!b.if_wall(4, 4));
}

TEST(TestDarwin, if_wall_5){
	Board b (10, 10);
	ASSERT_TRUE(!b.if_wall(14, 4));
}

TEST(TestDarwin, if_empty_1){
	Board b (10, 10);
	ASSERT_TRUE(b.if_empty(4, 4));
}

TEST(TestDarwin, if_empty_2){
	Species s;
	s.addInstruction("left");
	s.addInstruction("hop");
	s.addInstruction("if_empty 0");
	s.addInstruction("go 1");
	Creature temp (s, "s", north, 1, 5);

	Board b (10, 10);
	b.addCreature(temp, 1, 5);
	ASSERT_TRUE(!b.if_empty(1, 5));
}

TEST(TestDarwin, if_empty_3){
	Board b (10, 10);
	ASSERT_TRUE(!b.if_empty(13, 4));
}
