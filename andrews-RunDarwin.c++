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

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----
	Species f(food);
    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------
     Species h(hopper);
    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----
	Species r(rover);
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----
	Species t(trap);
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);

		Grid gr(8, 8);
        Creature tempCr;

        Creature food1(f, east, &gr);
		gr.setGridLocation(0, 0, food1);

        Creature hopper1(h, north, &gr);
        gr.setGridLocation(3, 3, hopper1);

        Creature hopper2(h, east, &gr);
        gr.setGridLocation(3, 4, hopper2);

        Creature hopper3(h, south, &gr);
        gr.setGridLocation(4, 4, hopper3);

        Creature hopper4(h, west, &gr);
        gr.setGridLocation(4, 3, hopper4);

        Creature food2(f, north, &gr);
        gr.setGridLocation(7, 7, food2);

		int i = 0;
        
        std::cout << "Turn = " << i << '.' << std::endl;
        gr.printGrid();

		while (i < 5) {
            for (int r = 0; r < gr.getRowSize(); r++) {
                for (int c = 0; c < gr.getColSize(); c++) {
                    tempCr = gr.getCreature(r, c);
                    if (tempCr.checkTurn(i) && gr.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                    }
                }
            }
			i++;            
            std::cout << "Turn = " << i << '.' << std::endl;
            gr.printGrid();
		}

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
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);

		Grid gr2(7, 9);
        Creature tempCr;


        Creature trap1(t, south, &gr2);
        gr2.setGridLocation(0, 0, trap1);

        Creature hopper1(h, east, &gr2);
        gr2.setGridLocation(3, 2, hopper1);

        Creature rover1(r, north, &gr2);
        gr2.setGridLocation(5, 4, rover1);

        Creature trap2(t, west, &gr2);
        gr2.setGridLocation(6, 8, trap2);

        int j = 0;
        
        std::cout << "Turn = " << j << '.' << std::endl;
        gr2.printGrid();

        while (j < 5) {
             for (int r = 0; r < gr2.getRowSize(); r++) {
                 for (int c = 0; c < gr2.getColSize(); c++) {
                    tempCr = gr2.getCreature(r, c);
                    if (tempCr.checkTurn(j) && gr2.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        gr2.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            gr2.printGrid();
        }
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
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
        cout << "*** Darwin 72x72 without Best ***" << endl;

        Grid gr3(72, 72);
        int tempRow, tempCol;
        bool validPlace = false;
        
        srand(0);
    
        Creature food1(f, rand() % 4, &gr3);
        Creature food2(f, rand() % 4, &gr3);
        Creature food3(f, rand() % 4, &gr3);
        Creature food4(f, rand() % 4, &gr3);
        Creature food5(f, rand() % 4, &gr3);
        Creature food6(f, rand() % 4, &gr3);
        Creature food7(f, rand() % 4, &gr3);
        Creature food8(f, rand() % 4, &gr3);
        Creature food9(f, rand() % 4, &gr3);
        Creature food10(f, rand() % 4, &gr3);

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food1);
        validPlace = false;


				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food2);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
				
        gr3.setGridLocation(tempRow, tempCol, food3);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food4);
        validPlace = false;
				
        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food5);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food6);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food7);
        validPlace = false;

			  while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food8);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food9);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, food10);
        validPlace = false;

			  Creature hopper1(h, rand() % 4, &gr3);
        Creature hopper2(h, rand() % 4, &gr3);
        Creature hopper3(h, rand() % 4, &gr3);
        Creature hopper4(h, rand() % 4, &gr3);
        Creature hopper5(h, rand() % 4, &gr3);
        Creature hopper6(h, rand() % 4, &gr3);
        Creature hopper7(h, rand() % 4, &gr3);
        Creature hopper8(h, rand() % 4, &gr3);
        Creature hopper9(h, rand() % 4, &gr3);
        Creature hopper10(h, rand() % 4, &gr3);

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper1);
        validPlace = false;


				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper2);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
				
        gr3.setGridLocation(tempRow, tempCol, hopper3);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper4);
        validPlace = false;
				
        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper5);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper6);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper7);
        validPlace = false;

			  while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper8);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, hopper9);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
	
        gr3.setGridLocation(tempRow, tempCol, hopper10);
				validPlace = false;

				Creature rover1(r, rand() % 4, &gr3);
        Creature rover2(r, rand() % 4, &gr3);
        Creature rover3(r, rand() % 4, &gr3);
        Creature rover4(r, rand() % 4, &gr3);
        Creature rover5(r, rand() % 4, &gr3);
        Creature rover6(r, rand() % 4, &gr3);
        Creature rover7(r, rand() % 4, &gr3);
        Creature rover8(r, rand() % 4, &gr3);
        Creature rover9(r, rand() % 4, &gr3);
        Creature rover10(r, rand() % 4, &gr3);

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover1);
        validPlace = false;


				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover2);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
				
        gr3.setGridLocation(tempRow, tempCol, rover3);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover4);
        validPlace = false;
				
        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover5);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover6);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover7);
        validPlace = false;

			  while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover8);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, rover9);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
	
        gr3.setGridLocation(tempRow, tempCol, rover10);
				validPlace = false;

		Creature trap1(t, rand() % 4, &gr3);
        Creature trap2(t, rand() % 4, &gr3);
        Creature trap3(t, rand() % 4, &gr3);
        Creature trap4(t, rand() % 4, &gr3);
        Creature trap5(t, rand() % 4, &gr3);
        Creature trap6(t, rand() % 4, &gr3);
        Creature trap7(t, rand() % 4, &gr3);
        Creature trap8(t, rand() % 4, &gr3);
        Creature trap9(t, rand() % 4, &gr3);
        Creature trap10(t, rand() % 4, &gr3);

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap1);
        validPlace = false;


				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap2);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
				
        gr3.setGridLocation(tempRow, tempCol, trap3);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap4);
        validPlace = false;
				
        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap5);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap6);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap7);
        validPlace = false;

			  while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap8);
        validPlace = false;

        while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }

        gr3.setGridLocation(tempRow, tempCol, trap9);
        validPlace = false;

				while(!validPlace){
            int tempmod = rand() % 5184;
            tempRow = tempmod / 72;
            tempCol = tempmod % 72;
            if(gr3.checkGridLocation(tempRow,tempCol) == '.'){
							validPlace = true;
						}
        }
	
        gr3.setGridLocation(tempRow, tempCol, trap10);
				validPlace = false;


       	gr3.printGrid();
		
				Creature tempCr;
	
				int j = 0;	
        while (j < 1000) {
             for (int r = 0; r < gr3.getRowSize(); r++) {
                 for (int c = 0; c < gr3.getColSize(); c++) {
                    tempCr = gr3.getCreature(r, c);
                    if (tempCr.checkTurn(j) && gr3.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        gr3.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
    				if((j < 10) || (j % 100 == 0)){
            	std::cout << "Turn = " << j << '.' << std::endl;          
		        	gr3.printGrid();
						}
        }
  
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
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 8x8 Rover Around ***" << endl;
        /*
        8x8 Darwin
        Rover, facing south, at (0, 0)
        Food, facing east,  at (7, 0)
        Food, facing north, at (7, 7)
        Food, facing east,  at (0, 7)
        Simulate 25 moves.
        Print every grid.
        */
        Grid grid(8, 8);

        Creature c3(r, south, &grid);
        Creature c4(h, east, &grid);
        Creature c5(h, north, &grid);
        Creature c6(h, east, &grid);

        grid.setGridLocation(0, 0, c3);
        grid.setGridLocation(7, 0, c4);
        grid.setGridLocation(7, 7, c5);
        grid.setGridLocation(0, 7, c6);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 25) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 3x8 Guantlet***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (0, 3)
        Trap, facing east,  at (0, 4)
        Trap, facing north, at (2, 3)
        Trap, facing east,  at (2, 4)
        Hopper, facing east,  at (1, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Grid grid(3, 8);
        
        Creature c1(t, south, &grid);
        Creature c2(t, east, &grid);
        Creature c3(t, north, &grid);
        Creature c4(t, east, &grid);
        Creature c5(h, east, &grid);

        grid.setGridLocation(0, 3, c1);
        grid.setGridLocation(0, 4, c2);
        grid.setGridLocation(2, 3, c3);
        grid.setGridLocation(2, 4, c4);
        grid.setGridLocation(1, 0, c5);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 10) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }    
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Darwin 5x5 Trap!***" << endl;
        /*
        3x8 Darwin
        Trap, facing south, at (2, 2)
        Hopper, facing south,  at (0, 2)
        Hopper, facing west, at (2, 4)
        Hopper, facing north,  at (4, 2)
        Hopper, facing east,  at (2, 0)
        Simulate 10 moves.
        Print every grid.
        */
        Grid grid(5, 5);
        
        Creature c1(t, south, &grid);
        Creature c2(h, south, &grid);
        Creature c3(h, west, &grid);
        Creature c4(h, north, &grid);
        Creature c5(h, east, &grid);

        grid.setGridLocation(2, 2, c1);
        grid.setGridLocation(0, 2, c2);
        grid.setGridLocation(2, 4, c3);
        grid.setGridLocation(4, 2, c4);
        grid.setGridLocation(2, 0, c5);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 10) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        } 
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 3x3 infect all***" << endl;
        /*
        3x3 Darwin
        Trap, facing south, at (1, 1)
        Food, everywhere else, facing whatever direction
        Simulate 20 moves.
        Print first and last grid.
        */
        Grid grid(3, 3);
        
        Creature c1(t, south, &grid);
        Creature c2(f, east, &grid);
        Creature c3(f, north, &grid);
        Creature c4(f, east, &grid);
        Creature c5(f, east, &grid);
        Creature c6(f, east, &grid);
        Creature c7(f, north, &grid);
        Creature c8(f, east, &grid);
        Creature c9(f, east, &grid);

        grid.setGridLocation(1, 1, c1);
        grid.setGridLocation(0, 0, c2);
        grid.setGridLocation(0, 1, c3);
        grid.setGridLocation(0, 2, c4);
        grid.setGridLocation(1, 0, c5);
        grid.setGridLocation(1, 2, c6);
        grid.setGridLocation(2, 0, c7);
        grid.setGridLocation(2, 1, c8);
        grid.setGridLocation(2, 2, c9);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 10) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        } 
    } 
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 7x12 ***" << endl;
        srand(0);

        Grid grid(7, 12);

        Creature trap(t, east, &grid);
        grid.setGridLocation(0, 0, trap);

        Creature hopper(h, north, &grid);
        grid.setGridLocation(3, 2, hopper);

        Creature rover(r, west, &grid);
        grid.setGridLocation(5, 4, rover);

        Creature trap2(t, south, &grid);
        grid.setGridLocation(6, 8, trap2);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 5) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Rover 1x1 ***" << endl;
        srand(0);
        /*        
        1x1 Darwin
        Rover, facing north at (0, 0)
        Simulate 10 moves
        Print every move
        */
        Grid grid(1, 1);
        Creature c(rover, north, &grid);
        grid.setGridLocation(0, 0, c);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 5) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 4x4 Four Traps Four Rovers***" << endl;
        srand(0);
        /*
        4x4 Grid
        South Trap @ (0, 0)
        North Trap @ (3, 3)
        East Trap @ (3, 0)
        West Trap @ (0, 3)
        North Rover @ (2, 1)
        East Rover @ (1, 2)
        South Rover @ (2, 2)
        West Rover @ (1, 1)
        */
        Grid grid(4, 4);
        Creature c1(trap, south, &grid);
        Creature c2(trap, north, &grid);
        Creature c3(trap, east, &grid);
        Creature c4(trap, west, &grid);
        Creature c5(rover, north, &grid);
        Creature c6(rover, east, &grid);
        Creature c7(rover, south, &grid);
        Creature c8(rover, west, &grid);

        grid.setGridLocation(0, 0, c1);
        grid.setGridLocation(3, 3, c2);
        grid.setGridLocation(3, 0, c3);
        grid.setGridLocation(0, 3, c4);
        grid.setGridLocation(2, 1, c5);
        grid.setGridLocation(1, 2, c6);
        grid.setGridLocation(2, 2, c7);
        grid.setGridLocation(1, 1, c8);
        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 5) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try 
    {
        cout << "*** Darwin 6x6 trap island ***" << endl;
        Grid grid(6, 6);

        Creature h1(h, south, &grid);
        Creature h2(h, south, &grid);
        Creature h3(h, south, &grid);
        Creature h4(h, south, &grid);
        Creature h5(h, south, &grid);
        Creature t1(t, north, &grid);

        grid.setGridLocation(1, 3, h1);
        grid.setGridLocation(2, 3, h2);
        grid.setGridLocation(2, 4, h3);
        grid.setGridLocation(3, 4, h4);
        grid.setGridLocation(4, 5, h5);
        grid.setGridLocation(5, 5, t1);

        grid.printGrid();

        Creature tempCr;

        int j = 0;
        while (j < 5) {
             for (int r = 0; r < grid.getRowSize(); r++) {
                 for (int c = 0; c < grid.getColSize(); c++) {
                    tempCr = grid.getCreature(r, c);
                    if (tempCr.checkTurn(j) && grid.checkGridLocation(r,c) != '.') {
                        tempCr.RunInstruction();
                        grid.setGridLocation(tempCr.getRowLoc(), tempCr.getColLoc(), tempCr);
                    }
                }
            }
            j++;  
            std::cout << "Turn = " << j << '.' << std::endl;          
            grid.printGrid();
        }

        
    }
    catch (const invalid_argument&)
    {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }

    return 0;}
