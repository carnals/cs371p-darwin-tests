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
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------
#include <stdio.h>
#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
#include "Darwin.c++"
#define HOP 0
#define LEFT 1
#define RIGHT 2
#define INFECT 3
#define IF_EMPTY 4
#define IF_WALL 5
#define IF_RAND 6
#define IF_ENEMY 7
#define GO 8
#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3


// ----
// main
// ----

int main () {
	using namespace std;

    // ----
    // food
    // ----

    /*
0: left
1: go 0
*/

	Species food("f");
	food.addInstruction(LEFT,0);
	food.addInstruction(GO,0);
    

    // ------
    // hopper
    // ------

    /*
0: hop
1: go 0
*/
	Species hopper("h");
	hopper.addInstruction(HOP);
	hopper.addInstruction(GO,0);
    // -----
    // rover
    // -----

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

	Species rover("r");
	rover.addInstruction(IF_ENEMY,9);
	rover.addInstruction(IF_EMPTY,7);
	rover.addInstruction(IF_RAND,5);
	rover.addInstruction(LEFT);
	rover.addInstruction(GO,0);
	rover.addInstruction(RIGHT);
	rover.addInstruction(GO,0);
	rover.addInstruction(HOP);
	rover.addInstruction(GO,0);
	rover.addInstruction(INFECT);
	rover.addInstruction(GO,0);
		

    // ----
    // trap
    // ----

    /*
0: if_enemy 3
1: left
2: go 0
3: infect
4: go 0
*/

	Species trap("t");
	trap.addInstruction(IF_ENEMY,3);
	trap.addInstruction(LEFT);
	trap.addInstruction(GO,0);
	trap.addInstruction(INFECT);
	trap.addInstruction(GO,0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
8x8 Darwin
Food, facing east, at (0, 0)
Hopper, facing north, at (3, 3)
Hopper, facing east, at (3, 4)
Hopper, facing south, at (4, 4)
Hopper, facing west, at (4, 3)
Food, facing north, at (7, 7)
Simulate 5 moves.
Print every grid.
*/
	World themap(8,8);
	Creature f1(food);
	Creature f2(food);
	Creature h1(hopper);
	Creature h2(hopper);
	Creature h3(hopper);
	Creature h4(hopper);
	themap.setCreat(f1,EAST,0,0);
        themap.setCreat(h1,NORTH,3,3);
	themap.setCreat(h2,EAST,3,4);
	themap.setCreat(h3,SOUTH,4,4);
	themap.setCreat(h4,WEST,4,3);
	themap.setCreat(f2,NORTH,7,7);

	Darwin temp(5,themap);
	temp.runGame();
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
        /*
7x9 Darwin
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 8)
Simulate 5 moves.
Print every grid.
*/    
	World themap2(9,7);
	Creature tr(trap);
	Creature tr2(trap);
	Creature hr(hopper);
	Creature rv(rover);

	themap2.setCreat(tr,SOUTH,0,0);
	themap2.setCreat(hr,EAST,3,2);
	themap2.setCreat(rv,NORTH,5,4);
	themap2.setCreat(tr2,WEST,6,8);
	Darwin temp2(5,themap2);
	srand(0);
	temp2.runGame();
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
        srand(0);
        
/*Randomly place the following creatures facing randomly.
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
Print the first 10 grids (i.e. 0, 1, 2...9).
Print every 100th grid after that (i.e. 100, 200, 300...1000).
*/
	World themap3(72,72);
	Creature fo1(food);
	Creature fo2(food);
	Creature fo3(food);
	Creature fo4(food);
	Creature fo5(food);
	Creature fo6(food);
	Creature fo7(food);
	Creature fo8(food);
	Creature fo9(food);
	Creature fo10(food);
	Creature hop1(hopper);
	Creature hop2(hopper);
	Creature hop3(hopper);
	Creature hop4(hopper);
	Creature hop5(hopper);
	Creature hop6(hopper);
	Creature hop7(hopper);
	Creature hop8(hopper);
	Creature hop9(hopper);
	Creature hop10(hopper);
	Creature rov(rover);
	Creature rov2(rover);
	Creature rov3(rover);
	Creature rov4(rover);
	Creature rov5(rover);
	Creature rov6(rover);
	Creature rov7(rover);
	Creature rov8(rover);
	Creature rov9(rover);
	Creature rov10(rover);
	Creature trp1(trap);
	Creature trp2(trap);
	Creature trp3(trap);
	Creature trp4(trap);
	Creature trp5(trap);
	Creature trp6(trap);
	Creature trp7(trap);
	Creature trp8(trap);
	Creature trp9(trap);
	Creature trp10(trap);
	int x;
	x=rand()%5184;
	themap3.setCreat(fo1,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(fo2,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(fo3,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(fo4,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(fo5,rand()%4,x/72,x%72);        
        x=rand()%5184;
        themap3.setCreat(fo6,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(fo7,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(fo8,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(fo9,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(fo10,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop1,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(hop2,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop3,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop4,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(hop5,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop6,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop7,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop8,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop9,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(hop10,rand()%4,x/72,x%72);
	x=rand()%5184;
        themap3.setCreat(rov,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov2,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov3,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov4,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov5,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov6,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov7,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov8,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov9,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(rov10,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp1,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp2,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp3,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp4,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp5,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp6,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp7,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp8,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp9,rand()%4,x/72,x%72);
        x=rand()%5184;
        themap3.setCreat(trp10,rand()%4,x/72,x%72);
	Darwin temp3(1000,themap3);
        temp3.runGame();	
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
Randomly place the following creatures facing randomly.
Call rand(), mod it with 5184 (72x72), and use that for the position
in a row-major order grid.
Call rand() again, mod it with 4 and use that for it's direction with
the ordering: 0:west, 1:north, 2:east, 3:south.
Do that for each kind of creature.
10 Food
10 Hopper
10 Rover
10 Trap
10 Best
Simulate 1000 moves.
Best MUST outnumber ALL other species for the bonus pts.
Print the first 10 grids (i.e. 0, 1, 2...9).
Print every 100th grid after that (i.e. 100, 200, 300...1000).
*/




        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


/*
4 traps
1 hopper
2 rover
2 food
*/	
	try{
	cout<<"*** Darwin 10x10 Normal***"<<endl;
	
	World themap(10,10);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
	Creature tr3(trap);
	Creature tr4(trap);
	Creature rv3(rover);
	Creature fd(food);
	Creature fd2(food);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,9,9);
	themap.setCreat(tr3,SOUTH,0,9);
	themap.setCreat(tr4,NORTH,9,0);
	themap.setCreat(fd,WEST,5,5);
	themap.setCreat(fd2,EAST,6,6);
        Darwin temp2(5,themap);
        srand(0);
        temp2.runGame();
	}
	catch(const invalid_argument&){
		assert(false);}
	catch(const out_of_range&){
		assert(false);}
/*
Same as before but larger map. Added two additional rovers.
*/


	try{
        cout<<"*** Darwin 11x11 Normal***"<<endl;
        World themap(11,11);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
        Creature tr3(trap);
        Creature tr4(trap);
        Creature rv3(rover);
        Creature fd(food);
        Creature fd2(food);
	Creature rv4(rover);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,10,10);
        themap.setCreat(tr3,SOUTH,0,10);
        themap.setCreat(tr4,NORTH,10,0);
        themap.setCreat(fd,WEST,5,5);
        themap.setCreat(fd2,EAST,6,6);
	themap.setCreat(rv3,NORTH,3,3);
	themap.setCreat(rv4,WEST,4,4);
        Darwin temp2(5,themap);
        srand(0);
        temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}


/*
Increased the grid size again.
*/
	try{
        cout<<"*** Darwin 13x13 Normal***"<<endl;
        World themap(13,13);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
        Creature tr3(trap);
        Creature tr4(trap);
        Creature rv3(rover);
        Creature fd(food);
        Creature fd2(food);
        Creature rv4(rover);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,10,10);
        themap.setCreat(tr3,SOUTH,0,10);
        themap.setCreat(tr4,NORTH,10,0);
        themap.setCreat(fd,WEST,5,5);
        themap.setCreat(fd2,EAST,6,6);
        themap.setCreat(rv3,NORTH,3,3);
        themap.setCreat(rv4,WEST,4,4);
        Darwin temp2(10,themap);
        srand(0);
        temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
       
/*
Increased the grid again, and added a trap
*/
        try{
        cout<<"*** Darwin 15x15 Normal***"<<endl;
        World themap(15,15);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
        Creature tr3(trap);
        Creature tr4(trap);
        Creature rv3(rover);
        Creature fd(food);
        Creature fd2(food);
        Creature rv4(rover);
	Creature tr5(trap);
	themap.setCreat(tr3,NORTH,7,7);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,10,10);
        themap.setCreat(tr3,SOUTH,0,10);
        themap.setCreat(tr4,NORTH,10,0);
        themap.setCreat(fd,WEST,5,5);
        themap.setCreat(fd2,EAST,6,6);
        themap.setCreat(rv3,NORTH,3,3);
        themap.setCreat(rv4,WEST,4,4);
	themap.setCreat(tr5,EAST,1,3);
        Darwin temp2(10,themap);
        srand(0);
        temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
/*
Added some additional food.
*/

       try{
        cout<<"*** Darwin 15x15 Normal***"<<endl;
        World themap(15,15);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
        Creature tr3(trap);
        Creature tr4(trap);
        Creature rv3(rover);
        Creature fd(food);
        Creature fd2(food);
        Creature rv4(rover);
        Creature tr5(trap);
	Creature food1(food);
        Creature food2(food);
	themap.setCreat(tr3,NORTH,7,7);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,10,10);
        themap.setCreat(tr3,SOUTH,0,10);
        themap.setCreat(tr4,NORTH,10,0);
        themap.setCreat(fd,WEST,5,5);
        themap.setCreat(fd2,EAST,6,6);
        themap.setCreat(rv3,NORTH,3,3);
        themap.setCreat(rv4,WEST,4,4);
        themap.setCreat(tr5,EAST,1,3);
	themap.setCreat(food1, NORTH,1,2);
	themap.setCreat(food2,SOUTH,1,1);
        Darwin temp2(10,themap);
        srand(0);
        temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}

/*
Decreased the size. Kept the creatures the same.
*/
       try{
        cout<<"*** Darwin 12x12 Normal***"<<endl;
        World themap(12,12);
        Creature tr(trap);
        Creature tr2(trap);
        Creature hr(hopper);
        Creature rv(rover);
        Creature tr3(trap);
        Creature tr4(trap);
        Creature rv3(rover);
        Creature fd(food);
        Creature fd2(food);
        Creature rv4(rover);
        Creature tr5(trap);
        Creature food1(food);
        Creature food2(food);
        themap.setCreat(tr3,NORTH,7,7);
        themap.setCreat(tr,SOUTH,0,0);
        themap.setCreat(hr,EAST,3,2);
        themap.setCreat(rv,NORTH,5,4);
        themap.setCreat(tr2,WEST,10,10);
        themap.setCreat(tr3,SOUTH,0,10);
        themap.setCreat(tr4,NORTH,10,0);
        themap.setCreat(fd,WEST,5,5);
        themap.setCreat(fd2,EAST,6,6);
        themap.setCreat(rv3,NORTH,3,3);
        themap.setCreat(rv4,WEST,4,4);
        themap.setCreat(tr5,EAST,1,3);
        themap.setCreat(food1, NORTH,1,2);
        themap.setCreat(food2,SOUTH,1,1);
        Darwin temp2(10,themap);
        srand(0);
        temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
/*
Here begins the tests that come from other people.
*/

       try{
        cout<<"*** Darwin 5x10 Based off of twpixley-RunDarwin.c++***"<<endl;
        World themap(10,5);
	Creature hopper1(hopper);
	Creature hopper2(hopper);
	Creature hopper3(hopper);
	Creature hopper4(hopper);
	Creature hopper5(hopper);
	Creature rover1(rover);
	Creature rover2(rover);
	Creature rover3(rover);
	Creature rover4(rover);
	Creature rover5(rover);
	themap.setCreat(hopper1,EAST,0,0);
	themap.setCreat(hopper2,EAST,1,0);
	themap.setCreat(hopper3,EAST,2,0);
	themap.setCreat(hopper4,EAST,3,0);
	themap.setCreat(hopper4,EAST,4,0);
	themap.setCreat(rover1,WEST,0,9);
	themap.setCreat(rover2,WEST,1,9);
	themap.setCreat(rover3,WEST,2,9);
	themap.setCreat(rover4,WEST,3,9);
	themap.setCreat(rover5,WEST,4,9);
	Darwin temp2(10,themap);
	srand(0);
	temp2.runGame();
        }
        catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
	try{
		        cout<<"*** Darwin 1x20 Based off of twpixley-RunDarwin.c++***"<<endl;
		World themap(20,1);
		Creature hopper1(hopper);
		themap.setCreat(hopper1,EAST,0,0);
		Creature hopper2(hopper);
		themap.setCreat(hopper2,WEST,0,19);
		Darwin temp2(10,themap);
		srand(0);
		temp2.runGame();
	}catch(const invalid_argument&){
		assert(false);}
	catch(const out_of_range&){
		assert(false);}
        try{
                cout<<"*** Darwin 10x4 Based off of  xman375_RunDarwin.c++***"<<endl;
                World themap(10,4);
		Creature c1(hopper);
		Creature c2(hopper);
		Creature c3(hopper);
		Creature c4(hopper);
		Creature c5(hopper);
		Creature c6(hopper);
		Creature c7(hopper);
		Creature c8(hopper);
		themap.setCreat(c1,SOUTH,0,0);
		themap.setCreat(c2,SOUTH,1,0);
		themap.setCreat(c3,SOUTH,2,0);
		themap.setCreat(c4, SOUTH,3,0);
		themap.setCreat(c5,NORTH,0,9);
		themap.setCreat(c6,NORTH,1,9);
		themap.setCreat(c7,NORTH,2,9);
		themap.setCreat(c8,NORTH,3,9);
		Darwin temp2(10,themap);
                srand(0);
                temp2.runGame();
        }catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
	try{
                cout<<"*** Darwin 10x10 Based off of  xman375_RunDarwin.c++***"<<endl;
                World themap(10,10);
                Creature c1(food);
                Creature c2(food);
                Creature c3(food);
                Creature c4(hopper);
                Creature c5(hopper);
                Creature c6(rover);
                Creature c7(trap);
                themap.setCreat(c1,EAST,0,0);
                themap.setCreat(c2,EAST,9,9);
                themap.setCreat(c3,NORTH,7,7);
                themap.setCreat(c4,NORTH,1,1);
                themap.setCreat(c5,EAST,3,4);
                themap.setCreat(c6,SOUTH,1,9);
                themap.setCreat(c7,WEST,4,3);
                Darwin temp2(10,themap);
                srand(0);
                temp2.runGame();
        }catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}

	try{
                cout<<"*** Darwin 5x5 Based off of  xman375_RunDarwin.c++***"<<endl;
                World themap(5,5);
                Creature c1(food);
		Creature c2(trap);
		Creature c3(hopper);
                Creature c4(trap);
                Creature c5(trap);
                Creature c6(hopper);
                Creature c7(trap);
		Creature c8(rover);
                themap.setCreat(c1,SOUTH,0,2);
                themap.setCreat(c2,NORTH,1,2);
                themap.setCreat(c3,EAST,2,0);
                themap.setCreat(c4,WEST,2,1);
                themap.setCreat(c5,EAST,2,3);
                themap.setCreat(c6,WEST,2,4);
                themap.setCreat(c7,SOUTH,3,2);
		themap.setCreat(c8,SOUTH,4,2);
                Darwin temp2(2,themap);
                srand(0);
                temp2.runGame();
        }catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}

	try{
                cout<<"*** Darwin 4x4 Based off of  xman375_RunDarwin.c++***"<<endl;
                World themap(4,4);
                Creature c1(hopper);
                Creature c2(hopper);
                Creature c3(hopper);
                Creature c4(hopper);
                themap.setCreat(c1,EAST,0,0);
                themap.setCreat(c2,SOUTH,0,3);
                themap.setCreat(c3,WEST,3,3);
                themap.setCreat(c4,NORTH,3,0);
                Darwin temp2(4,themap);
                srand(0);
                temp2.runGame();
        }catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}

        try{
                cout<<"*** Darwin 10x1 Based off of  xman375_RunDarwin.c++***"<<endl;
                World themap(10,1);
                Creature c1(hopper);
                Creature c2(hopper);
                Creature c3(hopper);
                Creature c4(hopper);
		Creature c5(hopper);

                themap.setCreat(c1,SOUTH,0,1);
                themap.setCreat(c2,SOUTH,0,3);
                themap.setCreat(c3,SOUTH,0,7);
                themap.setCreat(c4,SOUTH,0,9);
		themap.setCreat(c5,SOUTH,0,5);
                Darwin temp2(5,themap);
                srand(0);
                temp2.runGame();
        }catch(const invalid_argument&){
                assert(false);}
        catch(const out_of_range&){
                assert(false);}
		return 0;}	
