// ------------------------------------
// Name: Austin deBruyn
// eid: ad29763
// cs user id: austind
// email: austin.debruyn@yahoo.com
// ------------------------------------

// ------------------------------------
// Name: Steven Wilken
// eid: sdw845
// cs user id: swilken 
// email: blackrider@utexas.edu
// ------------------------------------

#include <iostream>
#include <cassert>
#include "gtest/gtest.h"
#define private public
#include "Darwin.h"

using namespace std;

TEST(Darwin, setprog1)
{
    species test1('1');
    int prog1[] = { LEFT, GO, 0 };
    test1.setProgram(prog1, 3);

    ASSERT_EQ(test1.program[1][1], 0);
 	ASSERT_EQ(test1.program[2][0], -1);
}

TEST(Darwin, setprog2)
{
    species A('A');
    int prog1[] = { GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, 
    	GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 1, GO, 2 };
    A.setProgram(prog1, 40);

    ASSERT_EQ(A.program[19][0], GO);
 	ASSERT_EQ(A.program[19][1], 2);
}

TEST(Darwin, setprog3)
{
    species mystery('?');
    int prog1[] = { INFECT, INFECT, INFECT, GO, 3, HOP };
    mystery.setProgram(prog1, 6);

    ASSERT_EQ(mystery.letter, '?');
    ASSERT_EQ(mystery.program[5][0], -1);
    ASSERT_EQ(mystery.program[4][1], -1);
 	ASSERT_EQ(mystery.program[4][0], HOP);
}

TEST(Darwin, creature1) {
	species rover('r');
    int prog3[] = { IFEMPTY, 9, IFEMPTY, 7, IFRANDOM, 5, LEFT, GO, 0, RIGHT, GO, 0, HOP, GO, 0, INFECT, GO, 0 };
    rover.setProgram(prog3, sizeof(prog3)/sizeof(int));

    creature rover1(&rover);

    ASSERT_EQ(rover1.s->letter, 'r');
}

TEST(Darwin, execute1) {
	species rover('r');
    int prog3[] = { IFENEMY, 9, IFEMPTY, 7, IFRANDOM, 5, LEFT, GO, 0, RIGHT, GO, 0, HOP, GO, 0, INFECT, GO, 0 };
    rover.setProgram(prog3, sizeof(prog3)/sizeof(int));

    creature rover1(&rover);

    ASSERT_EQ(rover1.execute(empty), HOP);
	ASSERT_EQ(rover1.pc, 8);
    ASSERT_EQ(rover1.execute(enemy), INFECT);
       
}

TEST(Darwin, execute2) {
	species boom('b');
    int boomprog[] = { HOP, GO, 0 };
    boom.setProgram(boomprog, sizeof(boomprog)/sizeof(int));

    creature hopper(&boom);

    ASSERT_EQ(hopper.execute(wall), HOP);
}

TEST(Darwin, execute3) {
	species thing('t');
    int thingprog[] = { IFEMPTY, 4, IFWALL, 4, IFENEMY, 3, LEFT, HOP, GO, 0};
    thing.setProgram(thingprog, sizeof(thingprog)/sizeof(int));

    creature austin(&thing);

	ASSERT_EQ(austin.execute(wall), HOP);
	ASSERT_EQ(austin.execute(empty), HOP);
	ASSERT_EQ(austin.execute(enemy), -1);
}

TEST(Darwin, place1){
	species boom('b');
    int boomprog[] = { HOP, GO, 0 };
    boom.setProgram(boomprog, sizeof(boomprog)/sizeof(int));

    creature hopper(&boom);

    grid<8, 8> g;
    g.place(0, 0, &boom);
    ASSERT_TRUE('b' == g.creatures.at((g.spot[0][0])).s->letter);

}

TEST(Darwin, place2){
	species boom('b');
    int boomprog[] = { HOP, GO, 0 };
    boom.setProgram(boomprog, sizeof(boomprog)/sizeof(int));

    creature hopper(&boom);

    grid<8, 8> g;
    g.place(0, 0, &boom);
    ASSERT_FALSE(g.place(0, 0, &boom));

}

TEST(Darwin, place3){
	species boom('b');
    int boomprog[] = { HOP, GO, 0 };
    boom.setProgram(boomprog, sizeof(boomprog)/sizeof(int));

    species thing('t');
    int thingprog[] = { IFEMPTY, 4, IFWALL, 4, IFENEMY, 3, LEFT, HOP, GO, 0};
    thing.setProgram(thingprog, sizeof(thingprog)/sizeof(int));

    grid<8, 8> g;
    g.place(0, 0, &boom);
    g.place(7, 7, &thing);
    ASSERT_TRUE('b' == g.creatures.at((g.spot[0][0])).s->letter);
    ASSERT_TRUE('t' == g.creatures.at((g.spot[7][7])).s->letter);
}

TEST(Darwin, takeTurn1) {
    species hopper('h');
    int hopperprog[] = { HOP, GO, 0 };
    hopper.setProgram(hopperprog, sizeof(hopperprog)/sizeof(int));

    grid<8, 8> g;
    g.place(3, 5, &hopper, SOUTH);
    g.place(4, 5, &hopper, EAST);

    g.takeTurn();

    ASSERT_TRUE('h' == g.creatures.at((g.spot[3][5])).s->letter);
    ASSERT_TRUE('h' == g.creatures.at((g.spot[4][6])).s->letter);
}

TEST(Darwin, takeTurn2) {
    species hopper('h');
    int hopperprog[] = { HOP, GO, 0 };
    hopper.setProgram(hopperprog, sizeof(hopperprog)/sizeof(int));

    species lawnmower('l');
    int lawnprog[] = { HOP, LEFT, GO, 0 };
    lawnmower.setProgram(lawnprog, sizeof(lawnprog)/sizeof(int));

    grid<5, 7> g;
    g.place(2, 2, &lawnmower);
    g.place(4, 4, &hopper, EAST);

    g.takeTurn(8);

    ASSERT_TRUE('l' == g.creatures.at((g.spot[2][2])).s->letter);
    ASSERT_TRUE('h' == g.creatures.at((g.spot[4][6])).s->letter);
}

TEST(Darwin, takeTurn3) {
    species hopper('h');
    int hopperprog[] = { HOP, GO, 0 };
    hopper.setProgram(hopperprog, sizeof(hopperprog)/sizeof(int));

    grid<400, 1> g;
    g.place(0, 0, &hopper, SOUTH);

   	for (int i=0; i<399; i++) {
		g.takeTurn();
   		ASSERT_TRUE('h' == g.creatures.at((g.spot[i+1][0])).s->letter);
	}
}

TEST(Darwin, takeTurn4) {
    species guy('g');
    int guyprog[] = { IFENEMY, GO, 3, GO, 0, -7 };
    guy.setProgram(guyprog, sizeof(guyprog)/sizeof(int));

    grid<412, 83> g;
	for (int i=0; i<412; i++)
	for (int j=0; j<83; j++) 
		g.place(i, j, &guy);

	g.takeTurn(20);
}


TEST(Darwin, infect1){
    species infector('i');
    int infectorprog[] = {INFECT, GO, 0};
    infector.setProgram(infectorprog, sizeof(infectorprog)/sizeof(int));

    species hopper('h');
    int hopperprog[] = { HOP, GO, 0 };
    hopper.setProgram(hopperprog, sizeof(hopperprog)/sizeof(int));

    grid<5, 7> g;
    g.place(0, 0, &hopper, EAST);
    g.place(1, 4, &infector, NORTH);

    g.takeTurn(5);

    ASSERT_TRUE('i' == g.creatures.at((g.spot[0][4])).s->letter);
}

TEST(Darwin, infect2){
    species a('a');
    int aprog[] = {INFECT, GO, 0};
    a.setProgram(aprog, sizeof(aprog)/sizeof(int));

    grid<1, 2> g;
    g.place(0, 0, &a, EAST);
    g.place(0, 1, &a, WEST);

    g.takeTurn(5);

    ASSERT_TRUE('a' == g.creatures.at((g.spot[0][0])).s->letter);
    ASSERT_TRUE('a' == g.creatures.at((g.spot[0][1])).s->letter);
}

TEST(Darwin, infect3){
    species zerg('z');
    int zergprog[] = {INFECT, GO, 0};
    zerg.setProgram(zergprog, sizeof(zergprog)/sizeof(int));

    species duck('d');
    int duckprog[] = {RIGHT, GO, 0};
    duck.setProgram(duckprog, sizeof(duckprog)/sizeof(int));

    grid<100, 100> g;

	for (int i=0; i<100; i++)
		for (int j=0; j<100; j++) {

			if (i == 0)
				g.place(i, j, &zerg, SOUTH);
			else
				g.place(i, j, &duck, SOUTH);
		}

    g.takeTurn();

	for (int i=0; i<100; i++)
		ASSERT_TRUE('z' == g.creatures.at((g.spot[99][i])).s->letter);

}


