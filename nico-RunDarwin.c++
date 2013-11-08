// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
#include "Darwin.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <stdlib.h>
int main(){
using namespace std;
	ofstream myFile;
	myFile.open("RunDarwin.out");
// ----------
    // darwin 8x8
    // ----------

    try {
	
	
	/*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
		
		
        myFile << "*** Darwin 8x8 ***" << endl;
		Species food("food");
		Species hopper("hopper");
		Creature food1(&food, 2, 'f');
		Creature hopper1(&hopper, 1, 'h');
		Creature hopper2(&hopper, 2, 'h');
		Creature hopper3(&hopper, 3, 'h');
		Creature hopper4(&hopper, 0, 'h');
		Creature food2(&food, 1, 'f');
		Darwin x(8, 8);
		x.addCreature(&food1, 0, 0);
		x.addCreature(&hopper1, 3, 3);
		x.addCreature(&hopper2, 3, 4);
		x.addCreature(&hopper3, 4, 4);
		x.addCreature(&hopper4, 4, 3);
		x.addCreature(&food2, 7, 7);
		x.printBoard(myFile);
		x.simulate(5, myFile);
		
		
		
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
	// ----------
    // darwin 7x9
    // ----------

    try {
	
       myFile << "*** Darwin 7x9 ***" << endl;
        srand(0);
		
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
		
		Species trap("trap");
		Species hopper("hopper");
		Species rover("rover");
		
		Creature trap1(&trap, 3, 't');
		Creature hopper1(&hopper, 2, 'h');
		Creature rover1(&rover, 1, 'r');
		Creature trap2(&trap, 0, 't');
		
		Darwin x(7, 9);
		
		x.addCreature(&trap1, 0, 0);
		x.addCreature(&hopper1, 3, 2);
		x.addCreature(&rover1, 5, 4);
		x.addCreature(&trap2, 6, 8);
		x.printBoard(myFile);
		x.simulate(5, myFile);
		
		
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
		// ------------
		// Rover 1x1					//user = ensign
		// ------------
		try {
			myFile << "*** Rover 1x1 ***" << endl;
			srand(0);
		/*	
				1x1 Darwin
				Rover, facing north at (0, 0)
				Simulate 10 moves
				Print every move
				*/
			Darwin x(1, 1);
			
			Species rover("rover");
			Creature rover1(&rover, 1, 'r');
			x.addCreature(&rover1, 0, 0);
			x.simulate(10, myFile);
	
	
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		// ------------------------
        // darwin 4x4						user = ianhays
        // ------------------------                
    try 
        {
        myFile << "*** Darwin 4x4 ***" << endl;
        srand(0);
		/*
        4x4 Darwin
        Trap,   facing south, at (1, 1)
        Trap,   facing north, at (2, 2)
        Trap,   facing east, at (1, 2)
        Trap,   facing north, at (2, 1)
        Simulate 5 moves.
        Print every grid.
        */
		
		Species trap("trap");
		Creature trap1(&trap, 3, 't');
		Creature trap2(&trap, 1, 't');
		Creature trap3(&trap, 2, 't');
		Creature trap4(&trap, 1, 't');
		
		Darwin x(4, 4);
		x.addCreature(&trap1, 1, 1);
		x.addCreature(&trap2, 2, 2);
		x.addCreature(&trap3, 1, 2);
		x.addCreature(&trap4, 2, 1);
		x.simulate(3, myFile);
		
		
		
		
		
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
		//---------
		//darwin 1x15					//user = jkovar
		//---------
		try{
			myFile << "*** Darwin 1x15 ***" << endl;
			Species hopper("hopper");
			Creature hopper1(&hopper, 2, 'h');
			Darwin x(1, 15);
			x.addCreature(&hopper1, 0, 0);
			x.simulate(4, myFile);
	
		}
		catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
		
		
		//---------
		//darwin 2x2 without best					//user = osaprych
		//---------
		try{
			myFile << "*** Darwin 2x2 without Best ***" << endl;
			Species rover("rover");
			Species hopper("hopper");
			Creature rover1(&rover, 1, 'r');
			Creature hopper1(&hopper, 2, 'h');
			
			Darwin x(2, 2);
			
			x.addCreature(&rover1, 0, 0);
			x.addCreature(&hopper1, 1, 1);
			x.simulate(5, myFile);
			
			
			
			
		}
		catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
		
		// ------------
		// rover_skinny_board 8x1				//user = davismc
		// ------------
		try{
		myFile << "*** Rover Skinny Board 8x1 ***" << endl;
		Species rover("rover");
		Creature rover1(&rover, 1, 'r');
		Darwin x(8, 1);
		x.addCreature(&rover1, 0, 0);
		x.simulate(4, myFile);
		
		
		
		
		}
		catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
		
	// ------------
    // darwin 72x72
    // without best
    // ------------
	try {
        myFile << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
		
		
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.				//altered test from given one. 
        */
		
		Darwin x(72, 72);
		Species food("food");
		Species hopper("hopper");
		Species rover("rover");
		Species trap("trap");
		int vals[40];
		int directions[40];
		for(int i = 0; i < 40; i++){
			vals[i] = rand()%5184;
			directions[i] = rand()%4;
		}
		
		Creature food1(&food, directions[0], 'f');
		x.addCreature(&food1, vals[0]/72, vals[0]%72);
		Creature food2(&food, directions[1], 'f');
		x.addCreature(&food2, vals[1]/72, vals[1]%72);
		Creature food3(&food, directions[2], 'f');
		x.addCreature(&food3, vals[2]/72, vals[2]%72);
		Creature food4(&food, directions[3], 'f');
		x.addCreature(&food4, vals[3]/72, vals[3]%72);
		Creature food5(&food, directions[4], 'f');
		x.addCreature(&food5, vals[4]/72, vals[4]%72);
		Creature food6(&food, directions[5], 'f');
		x.addCreature(&food6, vals[5]/72, vals[5]%72);
		Creature food7(&food, directions[6], 'f');
		x.addCreature(&food7, vals[6]/72, vals[6]%72);
		Creature food8(&food, directions[7], 'f');
		x.addCreature(&food8, vals[7]/72, vals[7]%72);
		Creature food9(&food, directions[8], 'f');
		x.addCreature(&food9, vals[8]/72, vals[8]%72);
		Creature food10(&food, directions[9], 'f');
		x.addCreature(&food10, vals[9]/72, vals[9]%72);
		
		Creature hopper11(&hopper, directions[10], 'h');
		x.addCreature(&hopper11, vals[10]/72, vals[10]%72);
		Creature hopper12(&hopper, directions[11], 'h');
		x.addCreature(&hopper12, vals[11]/72, vals[11]%72);
		Creature hopper13(&hopper, directions[12], 'h');
		x.addCreature(&hopper13, vals[12]/72, vals[12]%72);
		Creature hopper14(&hopper, directions[13], 'h');
		x.addCreature(&hopper14, vals[13]/72, vals[13]%72);
		Creature hopper15(&hopper, directions[14], 'h');
		x.addCreature(&hopper15, vals[14]/72, vals[14]%72);
		Creature hopper16(&hopper, directions[15], 'h');
		x.addCreature(&hopper16, vals[15]/72, vals[15]%72);
		Creature hopper17(&hopper, directions[16], 'h');
		x.addCreature(&hopper17, vals[16]/72, vals[16]%72);
		Creature hopper18(&hopper, directions[17], 'h');
		x.addCreature(&hopper18, vals[17]/72, vals[17]%72);
		Creature hopper19(&hopper, directions[18], 'h');
		x.addCreature(&hopper19, vals[18]/72, vals[18]%72);
		Creature hopper20(&hopper, directions[19], 'h');
		x.addCreature(&hopper20, vals[19]/72, vals[19]%72);
		
		
		
		Creature rover21(&rover, directions[20], 'r');
		x.addCreature(&rover21, vals[20]/72, vals[20]%72);
		Creature rover22(&rover, directions[21], 'r');
		x.addCreature(&rover22, vals[21]/72, vals[21]%72);
		Creature rover23(&rover, directions[22], 'r');
		x.addCreature(&rover23, vals[22]/72, vals[22]%72);
		Creature rover24(&rover, directions[23], 'r');
		x.addCreature(&rover24, vals[23]/72, vals[23]%72);
		Creature rover25(&rover, directions[24], 'r');
		x.addCreature(&rover25, vals[24]/72, vals[24]%72);
		Creature rover26(&rover, directions[25], 'r');
		x.addCreature(&rover26, vals[25]/72, vals[25]%72);
		Creature rover27(&rover, directions[26], 'r');
		x.addCreature(&rover27, vals[26]/72, vals[26]%72);
		Creature rover28(&rover, directions[27], 'r');
		x.addCreature(&rover28, vals[27]/72, vals[27]%72);
		Creature rover29(&rover, directions[28], 'r');
		x.addCreature(&rover29, vals[28]/72, vals[28]%72);
		Creature rover30(&rover, directions[29], 'r');
		x.addCreature(&rover30, vals[29]/72, vals[29]%72);
		
		
		
		Creature trap31(&trap, directions[30], 't');
		x.addCreature(&trap31, vals[30]/72, vals[30]%72);
		Creature trap32(&trap, directions[31], 't');
		x.addCreature(&trap32, vals[31]/72, vals[31]%72);
		Creature trap33(&trap, directions[32], 't');
		x.addCreature(&trap33, vals[32]/72, vals[32]%72);
		Creature trap34(&trap, directions[33], 't');
		x.addCreature(&trap34, vals[33]/72, vals[33]%72);
		Creature trap35(&trap, directions[34], 't');
		x.addCreature(&trap35, vals[34]/72, vals[34]%72);
		Creature trap36(&trap, directions[35], 't');
		x.addCreature(&trap36, vals[35]/72, vals[35]%72);
		Creature trap37(&trap, directions[36], 't');
		x.addCreature(&trap37, vals[36]/72, vals[36]%72);
		Creature trap38(&trap, directions[37], 't');
		x.addCreature(&trap38, vals[37]/72, vals[37]%72);
		Creature trap39(&trap, directions[38], 't');
		x.addCreature(&trap39, vals[38]/72, vals[38]%72);
		Creature trap40(&trap, directions[39], 't');
		x.addCreature(&trap40, vals[39]/72, vals[39]%72);
		x.simulate(10, myFile);
		
		
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
return 0;
}

