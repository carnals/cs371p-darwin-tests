// --------
// includes
// --------

#include <iostream> // cout, endl
#include "gtest/gtest.h"
#define private public
#define protected public
#define class struct
#include "Darwin.h"
using namespace std;

TEST(Darwin, species_constructor1){

	Species food('f');
	ASSERT_TRUE(food.program.size() == 0);
	ASSERT_TRUE(food.type == 'f');

}

TEST(Darwin, species_constructor2){

	Species hopper('h');
	ASSERT_TRUE(hopper.program.size() == 0);
	ASSERT_TRUE(hopper.type == 'h');

}

TEST(Darwin, species_constructor3){

	Species rover('r');
	ASSERT_TRUE(rover.program.size() == 0);
	ASSERT_TRUE(rover.type == 'r');

}

TEST(Darwin, species_constructor4){

	Species trap('t');
	ASSERT_TRUE(trap.program.size() == 0);
	ASSERT_TRUE(trap.type == 't');

}

TEST(Darwin, species_add_instruction1){
	Species trap('t');
	trap.add_instruction("TEST");
	ASSERT_TRUE(trap.program.size() == 1);
	ASSERT_TRUE(trap.program[0].compare("TEST") == 0);

}

TEST(Darwin, species_add_instruction2){
	Species trap('t');
	trap.add_instruction("TEST");
	trap.add_instruction("TEST2");
	ASSERT_TRUE(trap.program.size() == 2);
	ASSERT_TRUE(trap.program[0].compare("TEST") == 0);
	ASSERT_TRUE(trap.program[1].compare("TEST2") == 0);

}

TEST(Darwin, species_add_instruction3){
	Species trap('t');
	trap.add_instruction("TEST");
	trap.add_instruction("TEST2");
	trap.add_instruction("TEST3");
	ASSERT_TRUE(trap.program.size() == 3);
	ASSERT_TRUE(trap.program[0].compare("TEST") == 0);
	ASSERT_TRUE(trap.program[1].compare("TEST2") == 0);
	ASSERT_TRUE(trap.program[2].compare("TEST3") == 0);

}

TEST(Darwin, creature_constructor1){
	Species food('f');
	Creature f(food,'E');
	ASSERT_TRUE(f.species.type == 'f');
	ASSERT_TRUE(f.direction == 'E');	
}

TEST(Darwin, creature_constructor2){
	Species hopper('h');
	Creature h(hopper,'W');
	ASSERT_TRUE(h.species.type == 'h');
	ASSERT_TRUE(h.direction == 'W');	
}

TEST(Darwin, creature_constructor3){
	Species trap('t');
	Creature t(trap,'N');
	ASSERT_TRUE(t.species.type == 't');
	ASSERT_TRUE(t.direction == 'N');	
}

TEST(Darwin, creature_constructor4){
	Species rover('r');
	Creature r(rover,'S');
	ASSERT_TRUE(r.species.type == 'r');
	ASSERT_TRUE(r.direction == 'S');	
}

TEST(Darwin, grid_constructor1){
	Grid grid(10,10);
	ASSERT_TRUE(grid.sizeX == 10);
	ASSERT_TRUE(grid.sizeY == 10);
	ASSERT_TRUE(grid.step_count == 0);
	ASSERT_TRUE(grid.cells.size() == grid.sizeX);
	ASSERT_TRUE(grid.status.size() == grid.sizeX);
}

TEST(Darwin, grid_constructor2){
	Grid grid(10,100);
	ASSERT_TRUE(grid.sizeX == 10);
	ASSERT_TRUE(grid.sizeY == 100);
	ASSERT_TRUE(grid.step_count == 0);
	ASSERT_TRUE(grid.cells.size() == grid.sizeX);
	ASSERT_TRUE(grid.status.size() == grid.sizeX);
}

TEST(Darwin, grid_constructor3){
	Grid grid(1,1);
	ASSERT_TRUE(grid.sizeX == 1);
	ASSERT_TRUE(grid.sizeY == 1);
	ASSERT_TRUE(grid.step_count == 0);
	ASSERT_TRUE(grid.cells.size() == grid.sizeX);
	ASSERT_TRUE(grid.status.size() == grid.sizeX);
}

TEST(Darwin, grid_add_creature1){
	Grid grid(1,1);
	Species food('f');
	Creature f1(food,'E');
    grid.add_creature(f1,0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);
    ASSERT_TRUE(grid.cells[0][0].direction == 'E');
    ASSERT_TRUE(grid.cells[0][0].species.type == 'f');

}

TEST(Darwin, grid_add_creature2){
	Grid grid(1,1);
	Species hopper('h');
	Creature h1(hopper,'N');
    grid.add_creature(h1,0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);
    ASSERT_TRUE(grid.cells[0][0].direction == 'N');
    ASSERT_TRUE(grid.cells[0][0].species.type == 'h');

}

TEST(Darwin, grid_add_creature3){
	Grid grid(1,1);
	Species rover('r');
	Creature r1(rover,'W');
    grid.add_creature(r1,0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);
    ASSERT_TRUE(grid.cells[0][0].direction == 'W');
    ASSERT_TRUE(grid.cells[0][0].species.type == 'r');

}

TEST(Darwin, grid_add_creature4){
	Grid grid(1,1);
	Species trap('t');
	Creature t1(trap,'S');
    grid.add_creature(t1,0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);
    ASSERT_TRUE(grid.cells[0][0].direction == 'S');
    ASSERT_TRUE(grid.cells[0][0].species.type == 't');

}



TEST(Darwin, grid_execute1){

	Species food = Species('f');
    food.add_instruction("left");
    food.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature f1(food,'E');
    grid.add_creature(f1,0,0);

    grid.step_count++;
    grid.execute(0,0);
    ASSERT_TRUE(grid.cells[0][0].direction == 'N');
    

}

TEST(Darwin, grid_execute2){

	Species food = Species('f');
    food.add_instruction("left");
    food.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature f1(food,'E');
    grid.add_creature(f1,0,0);

    grid.step_count++;
    grid.execute(0,0);
    grid.step_count++;
    grid.execute(0,0);
    ASSERT_TRUE(grid.cells[0][0].direction == 'W');
    

}

TEST(Darwin, grid_execute3){

	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature h1(hopper,'N');
    grid.add_creature(h1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    ASSERT_TRUE(grid.status[2][3] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);
    

}


TEST(Darwin, grid_execute4){

	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature h1(hopper,'N');
    grid.add_creature(h1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    grid.step_count++;
    grid.execute(2,3);
    ASSERT_TRUE(grid.status[1][3] != -1);
    ASSERT_TRUE(grid.status[2][3] == -1);
    ASSERT_TRUE(grid.status[3][3] == -1);
    

}

TEST(Darwin, grid_execute5){

	Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature t1(trap,'N');
    grid.add_creature(t1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    ASSERT_TRUE(grid.cells[3][3].direction == 'W');
    

}

TEST(Darwin, grid_execute6){

	Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature t1(trap,'N');
    grid.add_creature(t1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    grid.step_count++;
    grid.execute(3,3);
    ASSERT_TRUE(grid.cells[3][3].direction == 'S');
    

}

TEST(Darwin, grid_execute7){

    Species rover = Species('r');
    rover.add_instruction("if_enemy 9");
    rover.add_instruction("if_empty 7");
    rover.add_instruction("if_random 5");
    rover.add_instruction("left");
    rover.add_instruction("go 0");
    rover.add_instruction("right");
    rover.add_instruction("go 0");
    rover.add_instruction("hop");
    rover.add_instruction("go 0");
    rover.add_instruction("infect");
    rover.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature r1(rover,'N');
    grid.add_creature(r1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    ASSERT_TRUE(grid.status[2][3] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);
    

}

TEST(Darwin, grid_execute8){

    Species rover = Species('r');
    rover.add_instruction("if_enemy 9");
    rover.add_instruction("if_empty 7");
    rover.add_instruction("if_random 5");
    rover.add_instruction("left");
    rover.add_instruction("go 0");
    rover.add_instruction("right");
    rover.add_instruction("go 0");
    rover.add_instruction("hop");
    rover.add_instruction("go 0");
    rover.add_instruction("infect");
    rover.add_instruction("go 0");

    Grid grid(8,8);
        
    Creature r1(rover,'N');
    grid.add_creature(r1,3,3);

    grid.step_count++;
    grid.execute(3,3);
    grid.step_count++;
    grid.execute(2,3);
    ASSERT_TRUE(grid.status[1][3] != -1);
    ASSERT_TRUE(grid.status[2][3] == -1);
    ASSERT_TRUE(grid.status[3][3] == -1);
    

}


TEST(Darwin, grid_hop1){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'N');
    grid.add_creature(t1,3,3);

    grid.hop(3,3);
    ASSERT_TRUE(grid.status[2][3] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);

}


TEST(Darwin, grid_hop2){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'E');
    grid.add_creature(t1,3,3);

    grid.hop(3,3);
    ASSERT_TRUE(grid.status[3][4] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);

}


TEST(Darwin, grid_hop3){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'S');
    grid.add_creature(t1,3,3);

    grid.hop(3,3);
    ASSERT_TRUE(grid.status[4][3] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);

}


TEST(Darwin, grid_hop4){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'W');
    grid.add_creature(t1,3,3);

    grid.hop(3,3);
    ASSERT_TRUE(grid.status[3][2] != -1);
    ASSERT_TRUE(grid.status[3][3] == -1);

}

TEST(Darwin, grid_hop5){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'N');
    grid.add_creature(t1,0,0);

    grid.hop(0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);


}


TEST(Darwin, grid_hop6){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'W');
    grid.add_creature(t1,0,0);

    grid.hop(0,0);
    ASSERT_TRUE(grid.status[0][0] != -1);

}

TEST(Darwin, grid_hop7){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'S');
    grid.add_creature(t1,7,7);

    grid.hop(7,7);
    ASSERT_TRUE(grid.status[7][7] != -1);


}


TEST(Darwin, grid_hop8){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'E');
    grid.add_creature(t1,7,7);

    grid.hop(7,7);
    ASSERT_TRUE(grid.status[7][7] != -1);

}




TEST(Darwin, grid_turn_left1){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'E');
    grid.add_creature(t1,7,7);

    grid.turn_left(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'N');

}

TEST(Darwin, grid_turn_left2){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'N');
    grid.add_creature(t1,7,7);

    grid.turn_left(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'W');

}

TEST(Darwin, grid_turn_left3){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'W');
    grid.add_creature(t1,7,7);

    grid.turn_left(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'S');

}

TEST(Darwin, grid_turn_left4){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'S');
    grid.add_creature(t1,7,7);

    grid.turn_left(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'E');

}


TEST(Darwin, grid_turn_right1){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'N');
    grid.add_creature(t1,7,7);

    grid.turn_right(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'E');

}

TEST(Darwin, grid_turn_right2){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'W');
    grid.add_creature(t1,7,7);

    grid.turn_right(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'N');

}

TEST(Darwin, grid_turn_right3){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'S');
    grid.add_creature(t1,7,7);

    grid.turn_right(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'W');

}

TEST(Darwin, grid_turn_right4){
	Species trap = Species('t');
	Grid grid(8,8);
    
    Creature t1(trap,'E');
    grid.add_creature(t1,7,7);

    grid.turn_right(7,7);
    ASSERT_TRUE(grid.cells[7][7].direction == 'S');

}

TEST(Darwin, grid_infect1){
    Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");

    Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");

    Grid grid(8,8);
    
    Creature t1(trap,'E');
    grid.add_creature(t1,7,6);

    Creature h1(hopper,'E');
    grid.add_creature(h1,7,7);

    grid.infect(7,6);

    ASSERT_TRUE(grid.cells[7][7].species.type == 't');
    ASSERT_TRUE(grid.cells[7][7].pc == 0);


}

TEST(Darwin, grid_infect2){
    Species trap = Species('t');
    trap.add_instruction("if_enemy 3");
    trap.add_instruction("left");
    trap.add_instruction("go 0");
    trap.add_instruction("infect");
    trap.add_instruction("go 0");

    Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");

    Grid grid(8,8);
    
    Creature t1(trap,'W');
    grid.add_creature(t1,7,6);

    Creature h1(hopper,'E');
    grid.add_creature(h1,7,7);

    grid.infect(7,6);

    ASSERT_TRUE(grid.cells[7][7].species.type == 'h');


}

TEST(Darwin, grid_check_wall){
	Grid grid(1,1);
	ASSERT_FALSE(grid.check_wall(0,0));
	ASSERT_TRUE(grid.check_wall(-1,0));
	ASSERT_TRUE(grid.check_wall(0,1));
}

TEST(Darwin, grid_get_space_ahead1){
	Grid grid(8,8);
	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");
    Creature h1(hopper,'E');
    grid.add_creature(h1,1,1);
	point p = grid.get_space_ahead(1,1);
	ASSERT_TRUE(p.x == 1);
	ASSERT_TRUE(p.y == 2);

}


TEST(Darwin, grid_get_space_ahead2){
	Grid grid(8,8);
	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");
    Creature h1(hopper,'S');
    grid.add_creature(h1,1,1);
	point p = grid.get_space_ahead(1,1);
	ASSERT_TRUE(p.x == 2);
	ASSERT_TRUE(p.y == 1);

}

TEST(Darwin, grid_get_space_ahead3){
	Grid grid(8,8);
	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");
    Creature h1(hopper,'W');
    grid.add_creature(h1,1,1);
	point p = grid.get_space_ahead(1,1);
	ASSERT_TRUE(p.x == 1);
	ASSERT_TRUE(p.y == 0);

}

TEST(Darwin, grid_get_space_ahead4){
	Grid grid(8,8);
	Species hopper = Species('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go 0");
    Creature h1(hopper,'N');
    grid.add_creature(h1,1,1);
	point p = grid.get_space_ahead(1,1);
	ASSERT_TRUE(p.x == 0);
	ASSERT_TRUE(p.y == 1);

}

