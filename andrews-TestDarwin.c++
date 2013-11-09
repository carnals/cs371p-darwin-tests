// ------------------------------
// project4/TestDarwin.c++
// Copyright (C) 2013
// Andrew Solis/Taylor Barnett
// ------------------------------

#include <cassert>   // assert
#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include "Darwin.h"

//Checks grid default and normal
//constructor, along with getRow and getCol functions
TEST(Grid, makeGrid1){

	Grid grid(8, 8);
	ASSERT_TRUE(grid.getRowSize() == 8);
	ASSERT_TRUE(grid.getColSize() == 8);

}

TEST(Grid, makeGrid2){

	Grid grid;
	ASSERT_TRUE(grid.getRowSize() == 0);
	ASSERT_TRUE(grid.getColSize() == 0);

}

TEST(Grid, makeGrid3){

	Grid grid(10000, 3);
	ASSERT_TRUE(grid.getRowSize() == 10000);
	ASSERT_TRUE(grid.getColSize() == 3);
}


//Check creating Species, getSpeciesName,
//and get SpeciesType() function
TEST(Species, makeSpecies1){
	Species hop(hopper);
	ASSERT_TRUE(hop.getSpeciesName() == 'h');
	ASSERT_TRUE(hop.getSpeciesType() == 1);
}

TEST(Species, makeSpecies2){
	Species sp;
	ASSERT_TRUE(sp.getSpeciesName() == ' ');
	ASSERT_TRUE(sp.getSpeciesType() == 5);
}

TEST(Species, makeSpecies3){
	Species foo(food);
	Species bes(best);
	ASSERT_TRUE(foo.getSpeciesName() == 'f');
	ASSERT_TRUE(foo.getSpeciesType() == 0);
	ASSERT_TRUE(bes.getSpeciesName() == 'b');
	ASSERT_TRUE(bes.getSpeciesType() == 4);
}

// checks Creature default constructor and
// normal constructor and getName
TEST(Creatures, makeCreatures1){
	Creature cr;
	ASSERT_TRUE(cr.getPC() == 0);
	ASSERT_TRUE(cr.getName() == ' ');
}

TEST(Creatures, makeCreatures2){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature cr(hop, north, &grid);
	ASSERT_TRUE(cr.getPC() == 0);
	ASSERT_TRUE(cr.getName() == 'h');
}

TEST(Creatures, makeCreatures3){
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
}

//setting creatures with gridLocation
// check creature location
// using getRowLoc and getColLoc
TEST(Creatures, setCreatureLoc1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		
}

TEST(Creatures, setCreatureLoc2){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);		
}

TEST(Creatures, setCreatureLoc3){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);
	Species tra(trap);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	Creature crt(tra, east, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crt);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crt.getPC() == 0);
	ASSERT_TRUE(crt.getName() == 't');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);		

	ASSERT_TRUE(crt.getRowLoc() == 3);
	ASSERT_TRUE(crt.getColLoc() == 3);		

}

// checkGridLocation function of Grid class
// as well making sure creature is placed
// in right place with other functions
// already tested 
TEST(GridCreature, checkLocation1){	
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');
}

TEST(GridCreature, checkLocation2){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);	


	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');	
}

TEST(Creatures, checkLocation3){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);
	Species tra(trap);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	Creature crt(tra, east, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crt);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crt.getPC() == 0);
	ASSERT_TRUE(crt.getName() == 't');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);		

	ASSERT_TRUE(crt.getRowLoc() == 3);
	ASSERT_TRUE(crt.getColLoc() == 3);


	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');	
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 't');	

}

//RemoveCreatureLocation for Grid tested
TEST(GridCreature, removeCreature1){	
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	grid.removeCreatureLocation(1, 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
}

TEST(GridCreature, removeCreature2){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);	


	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	grid.removeCreatureLocation(1, 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');	

	grid.removeCreatureLocation(2, 2);

	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == '.');	
}

TEST(Creatures, removeCreature3){
	Grid grid(8, 8);
	Species hop(hopper);
	Species foo(food);
	Species tra(trap);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	Creature crt(tra, east, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crt);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crt.getPC() == 0);
	ASSERT_TRUE(crt.getName() == 't');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);		

	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);		

	ASSERT_TRUE(crt.getRowLoc() == 3);
	ASSERT_TRUE(crt.getColLoc() == 3);


	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');	
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 't');

	grid.removeCreatureLocation(1, 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 't');

	// doest matter if creature not at location, still
	// frees up spot as if no creature there so code
	// doesn't break
	grid.removeCreatureLocation(1, 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');		
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 't');

	grid.removeCreatureLocation(2, 2);

	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == '.');	
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 't');

	grid.removeCreatureLocation(3, 3);

	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == '.');	
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == '.');
}

//Tests getCreature function that returns creature
//from point in grid
TEST(GridCreature, getCreature1){	
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	Creature tempCr = grid.getCreature(1, 1);
	ASSERT_TRUE(tempCr.getPC() == 0);
	ASSERT_TRUE(tempCr.getName() == 'h');
	ASSERT_TRUE(tempCr.getRowLoc() == 1);
	ASSERT_TRUE(tempCr.getColLoc() == 1);
}

TEST(GridCreature, getCreature2){	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, east, &grid);

	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');


	Creature tempCr = grid.getCreature(1, 1);
	ASSERT_TRUE(tempCr.getPC() == 0);
	ASSERT_TRUE(tempCr.getName() == 'h');
	ASSERT_TRUE(tempCr.getRowLoc() == 1);
	ASSERT_TRUE(tempCr.getColLoc() == 1);


	Creature tempCr2 = grid.getCreature(2, 2);
	ASSERT_TRUE(tempCr2.getPC() == 0);
	ASSERT_TRUE(tempCr2.getName() == 'f');
	ASSERT_TRUE(tempCr2.getRowLoc() == 2);
	ASSERT_TRUE(tempCr2.getColLoc() == 2);

}

TEST(GridCreature, getCreature3){	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);
	Species bes(best);

	Creature crh(hop, north, &grid);
	Creature crf(foo, east, &grid);
	Creature crb(bes, west, &grid);

	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crb);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	ASSERT_TRUE(crb.getPC() == 0);
	ASSERT_TRUE(crb.getName() == 'b');
	ASSERT_TRUE(crb.getRowLoc() == 3);
	ASSERT_TRUE(crb.getColLoc() == 3);
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 'b');

	Creature tempCr = grid.getCreature(1, 1);
	ASSERT_TRUE(tempCr.getPC() == 0);
	ASSERT_TRUE(tempCr.getName() == 'h');
	ASSERT_TRUE(tempCr.getRowLoc() == 1);
	ASSERT_TRUE(tempCr.getColLoc() == 1);


	Creature tempCr2 = grid.getCreature(2, 2);
	ASSERT_TRUE(tempCr2.getPC() == 0);
	ASSERT_TRUE(tempCr2.getName() == 'f');
	ASSERT_TRUE(tempCr2.getRowLoc() == 2);
	ASSERT_TRUE(tempCr2.getColLoc() == 2);

	Creature tempCr3 = grid.getCreature(3, 3);
	ASSERT_TRUE(tempCr3.getPC() == 0);
	ASSERT_TRUE(tempCr3.getName() == 'b');
	ASSERT_TRUE(tempCr3.getRowLoc() == 3);
	ASSERT_TRUE(tempCr3.getColLoc() == 3);
}

//run single instruction on hop
TEST(GridCreature, Instruction1){	
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.RunInstruction();
	ASSERT_TRUE(crh.getPC() == 1);
	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(0, 1) == 'h');
}

TEST(GridCreature, Instruction2){	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	crh.RunInstruction();
	ASSERT_TRUE(crh.getPC() == 1);
	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 1);


	crf.RunInstruction();
	ASSERT_TRUE(crf.getPC() == 1);
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
}

//run multiple instructions on hop
// doesn't perform action since at wall
TEST(GridCreature, Instruction3){	
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.RunInstruction();
	ASSERT_TRUE(crh.getPC() == 1);
	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(0, 1) == 'h');

	crh.RunInstruction();
	ASSERT_TRUE(crh.getPC() == 1);
	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == '.');
	ASSERT_TRUE(grid.checkGridLocation(0, 1) == 'h');
}

// check to make sure it is that species turn
// to go as hasn't gone before

// iterates the turnCounter variable in that Creature
// once and then performs the instruction that its
// program counter is set too to show that it has gone
TEST(Creature, checkTurn1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crh.checkTurn(0) == true);
}

TEST(GridCreature, checkTurn2){	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	ASSERT_TRUE(crh.checkTurn(0) == true);
	ASSERT_TRUE(crf.checkTurn(0) == true);
}

//creature already went so should fail check
TEST(Creature, checkTurn3){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crh.checkTurn(0) == true);
	ASSERT_TRUE(crh.checkTurn(0) == false);
}


//change a creatures species
TEST(CreatureSpecies, changeSpecies1){
	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	crf.changeSpecies(hop);

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'h');
}

TEST(CreatureSpecies, changeSpecies2){
	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);
	Species bes(best);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	Creature crb(bes, east, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crb);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	ASSERT_TRUE(crb.getPC() == 0);
	ASSERT_TRUE(crb.getName() == 'b');
	ASSERT_TRUE(crb.getRowLoc() == 3);
	ASSERT_TRUE(crb.getColLoc() == 3);
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 'b');


	crf.changeSpecies(hop);

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'h');

	crh.changeSpecies(bes);
	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'b');
}

TEST(CreatureSpecies, changeSpecies3){
	
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);
	Species bes(best);

	Creature crh(hop, north, &grid);
	Creature crf(foo, west, &grid);
	Creature crb(bes, east, &grid);
	grid.setGridLocation(1, 1, crh);
	grid.setGridLocation(2, 2, crf);
	grid.setGridLocation(3, 3, crb);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'f');
	ASSERT_TRUE(crf.getRowLoc() == 2);
	ASSERT_TRUE(crf.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(2, 2) == 'f');

	ASSERT_TRUE(crb.getPC() == 0);
	ASSERT_TRUE(crb.getName() == 'b');
	ASSERT_TRUE(crb.getRowLoc() == 3);
	ASSERT_TRUE(crb.getColLoc() == 3);
	ASSERT_TRUE(grid.checkGridLocation(3, 3) == 'b');


	crf.changeSpecies(hop);

	ASSERT_TRUE(crf.getPC() == 0);
	ASSERT_TRUE(crf.getName() == 'h');

	crh.changeSpecies(bes);
	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'b');

	crh.changeSpecies(hop);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
}


//turn creature left or right
TEST(Creature, turn1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.left();
	crh.hop();
	
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 0);
	ASSERT_TRUE(grid.checkGridLocation(1, 0) == 'h');
}

TEST(Creature, turn2){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.right();
	crh.hop();
	
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 2);
	ASSERT_TRUE(grid.checkGridLocation(1, 2) == 'h');
}

TEST(Creature, turn3){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.left();
	crh.right();
	crh.hop();
	
	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(0, 1) == 'h');
}

//able to change PC for creature and get right PC for creature
TEST(Creature, setPC1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.setPC(1);
	ASSERT_TRUE(crh.getPC() == 1);
}


TEST(Creature, setPC2){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.setPC(0);
	ASSERT_TRUE(crh.getPC() == 0);
}

TEST(Creature, setPC3){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	crh.setPC(2);
	ASSERT_TRUE(crh.getPC() == 2);
	crh.setPC(3);
	ASSERT_TRUE(crh.getPC() == 3);
}

//set creatures location attributes it has
TEST(Creature, setLocation1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);


	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');

	ASSERT_TRUE(crh.getRowLoc() == -1);
	ASSERT_TRUE(crh.getColLoc() == -1);

	grid.setGridLocation(1, 1, crh);

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
}

TEST(Creature, setLocation2){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);

	crh.setLocation(2, 2);

	ASSERT_TRUE(crh.getRowLoc() == 2);
	ASSERT_TRUE(crh.getColLoc() == 2);
}

TEST(Creature, setLocation3){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);

	crh.setLocation(2, 2);

	ASSERT_TRUE(crh.getRowLoc() == 2);
	ASSERT_TRUE(crh.getColLoc() == 2);

	grid.setGridLocation(3, 3, crh);
	// should automatically call setLocation in set
	// gridLocation and set creatures row and col 
	// attributes

	ASSERT_TRUE(crh.getRowLoc() == 3);
	ASSERT_TRUE(crh.getColLoc() == 3);
}

//check if at a wall or it is empty
TEST(CreatureGrid, wallEmptyCheck1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(1, 1, crh);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(grid.checkGridLocation(1, 1) == 'h');

	ASSERT_TRUE(crh.getRowLoc() == 1);
	ASSERT_TRUE(crh.getColLoc() == 1);
	ASSERT_TRUE(crh.if_Empty() == true);
	ASSERT_TRUE(crh.if_Wall() == false);
}

TEST(CreatureGrid, wallEmptyCheck2){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	grid.setGridLocation(0, 0, crh);

	ASSERT_TRUE(crh.getPC() == 0);
	ASSERT_TRUE(crh.getName() == 'h');
	ASSERT_TRUE(grid.checkGridLocation(0, 0) == 'h');

	ASSERT_TRUE(crh.getRowLoc() == 0);
	ASSERT_TRUE(crh.getColLoc() == 0);
	ASSERT_TRUE(crh.if_Empty() == false);
	ASSERT_TRUE(crh.if_Wall() == true);
}

TEST(CreatureGrid, wallEmptyCheck3){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	Creature crh2(hop, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crh2);

	ASSERT_TRUE(crh.if_Empty() == false);
	ASSERT_TRUE(crh.if_Wall() == false);
}

TEST(CreatureGrid, enemyCheck1){
	Grid grid(5, 5);
	Species hop(hopper);

	Creature crh(hop, north, &grid);
	Creature crh2(hop, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crh2);

	ASSERT_TRUE(crh.if_Empty() == false);
	ASSERT_TRUE(crh.if_Wall() == false);
	ASSERT_TRUE(crh.if_Enemy() == false);
}

TEST(CreatureGrid, enemyCheck2){
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crh2(food, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crh2);

	ASSERT_TRUE(crh.if_Empty() == false);
	ASSERT_TRUE(crh.if_Wall() == false);
	ASSERT_TRUE(crh.if_Enemy() == true);
}

TEST(CreatureGrid, enemyCheck3){
	Grid grid(5, 5);
	Species hop(hopper);
	Species foo(food);

	Creature crh(hop, east, &grid);
	Creature crh2(food, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crh2);

	ASSERT_TRUE(crh.if_Empty() == true);
	ASSERT_TRUE(crh.if_Wall() == false);
	ASSERT_TRUE(crh.if_Enemy() == false);
}

//check ifRandom and infect for Creature on grid
TEST(CreatureGrid, randominfect1){
	Grid grid(5, 5);
	Species hop(hopper);
	Species tra(trap);

	Creature crh(hop, north, &grid);
	Creature crt(trap, north, &grid);
	grid.setGridLocation(2, 3, crh);
	grid.setGridLocation(3, 3, crt);

	ASSERT_TRUE(crt.if_Empty() == false);
	ASSERT_TRUE(crt.if_Wall() == false);
	ASSERT_TRUE(crt.if_Enemy() == true);
	crt.RunInstruction();


	Creature crtemp = grid.getCreature(2, 3);
	std::cout << crtemp.getName() << std::endl;
	ASSERT_TRUE(crtemp.getName() == 't');
}

TEST(CreatureGrid, randominfect2){
	Grid grid(5, 5);
	Species hop(hopper);
	Species tra(trap);

	Creature crh(hop, north, &grid);
	Creature crt(trap, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crt);

	ASSERT_TRUE(crh.if_Empty() == false);
	ASSERT_TRUE(crh.if_Wall() == false);
	ASSERT_TRUE(crh.if_Enemy() == true);
	crh.infect();


	Creature crtemp = grid.getCreature(2, 3);
	ASSERT_TRUE(crtemp.getName() == 'h');
}

TEST(CreatureGrid, randominfect3){
	Grid grid(5, 5);
	Species hop(hopper);
	Species tra(trap);
	Species foo(food);

	Creature crh(hop, north, &grid);
	Creature crt(tra, north, &grid);
	Creature crf(foo, north, &grid);
	grid.setGridLocation(3, 3, crh);
	grid.setGridLocation(2, 3, crt);
	grid.setGridLocation(1, 3, crf);

	crh.infect();
	grid.getCreature(2, 3).infect();

	Creature crtemp = grid.getCreature(2, 3);
	ASSERT_TRUE(crtemp.getName() == 'h');
	Creature crtemp2 = grid.getCreature(1, 3);
	std::cout << "name: " << crtemp2.getName() << std::endl;
	ASSERT_TRUE(crtemp2.getName() == 'h');
}