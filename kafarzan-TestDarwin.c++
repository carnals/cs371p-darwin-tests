// -----------
// TestDarwin
// -----------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"
#define private public
#include "Darwin.h"


// -----
// addCreature
// -----

TEST(Darwin, addCreature1){
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Darwin board(2,2,1);
    Creature x("food", 0,food);
    board.addCreature(x,0,0);
    ASSERT_EQ("food", board.grid[0][0]._name); 
}
TEST(Darwin, addCreature2){
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Darwin board(30, 30, 1);
    Creature x("rover", 0,food);
    board.addCreature(x,15,15);
    ASSERT_EQ("rover", board.grid[15][15]._name); 
}
TEST(Darwin, addCreature3){
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Darwin board(200,200,1);
    Creature x("trap", 0,food);
    board.addCreature(x,199,199);
    ASSERT_EQ("trap", board.grid[199][199]._name); 
}

//
// change direction
//

TEST(Creature, changeDirection_1)
{
    // Darwin board(5,5,5);
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);
    
    Creature x("food", 0, food);
    // board.addCreature(x, 0, 0);
    x.changeDirection("right");
    ASSERT_EQ(1, x._direction);
}

TEST(Creature, changeDirection_2)
{
    Darwin board(5,5,5);
    Species hopper;
    hopper.addInstruction("hop", -1);
    hopper.addInstruction("go", 0);
    Creature x("hopper", 1, hopper);
    board.addCreature(x, 4, 4);
    board.grid[4][4].changeDirection("left");
    ASSERT_EQ(0, board.grid[4][4]._direction);
}

TEST(Creature, changeDirection_3)
{
    Darwin board(5,5,5);
    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0);
    Creature x("trap", 3, trap);
    board.addCreature(x, 1, 2);
    board.grid[1][2].changeDirection("left");
    board.grid[1][2].changeDirection("left");
    ASSERT_EQ(1, board.grid[1][2]._direction);

}

TEST(Creature, changeDirection_4)
{
    Darwin board(5,5,5);
    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0);
    Creature x("rover", 0, rover);
    board.addCreature(x, 2, 2);
    board.grid[2][2].changeDirection("right");
    board.grid[2][2].changeDirection("right");

    ASSERT_EQ(2, board.grid[2][2]._direction);
}

TEST(Darwin, hop1)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 2, rover);
    board.addCreature(x,0,0);
    board.hop(board.grid[0][0], 0,0,5,5);
   

    ASSERT_EQ("rover", board.grid[0][1]._name);
}
TEST(Darwin, hop2)
{
    Darwin board(5,5,5);
    Species trap;
    Creature x("trap", 2, trap);
    board.addCreature(x,0,0);
    board.hop(board.grid[0][0], 0,0,5,5);
   

    ASSERT_EQ("trap", board.grid[0][1]._name);
}
TEST(Darwin, hop3)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 2, rover);
    board.addCreature(x,4,4);
    board.hop(board.grid[4][4], 4,4,5,5);
   

    ASSERT_EQ("rover", board.grid[4][4]._name);
}

TEST(Darwin, if_Empty_1)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 1, hopper);
    board.addCreature(x,0,1);
    bool empty = board.grid[0][1].if_empty(board.grid[0][0], 0, 1, 5, 5);
    ASSERT_EQ(false, empty);
}

TEST(Darwin, if_Empty_2)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 3, rover);
    board.addCreature(x,0,0);
    bool empty = board.grid[0][0].if_empty(board.grid[1][0], 0, 0, 5, 5);
    ASSERT_EQ(true, empty);
}

TEST(Darwin, if_Empty_3)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 2, hopper);
    board.addCreature(x,2,1);
    bool empty = board.grid[2][1].if_empty(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(true, empty);
}

TEST(Darwin, if_Empty_4)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 1, hopper);
    board.addCreature(x,4,4);
    bool empty = board.grid[4][4].if_empty(board.grid[3][4], 4, 4, 5, 5);
    ASSERT_EQ(true, empty);
}

TEST(Darwin, if_Empty_5)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 0, hopper);
    board.addCreature(x,2,4);
    bool empty = board.grid[2][3].if_empty(board.grid[2][4], 2, 3, 5, 5);
    ASSERT_EQ(false, empty);
}



TEST(Creature, if_wall_1)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 3, rover);
    board.addCreature(x,4,4);
    bool isWall = board.grid[4][4].if_wall(4,4,5,5);
    ASSERT_EQ(true, isWall);
}

TEST(Creature, if_wall_2)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 2, hopper);
    board.addCreature(x,3,2);
    bool isWall = board.grid[3][2].if_wall(3,2,5,5);
    ASSERT_EQ(false, isWall);
}

TEST(Creature, if_wall_3)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 1, rover);
    board.addCreature(x,0,0);
    bool isWall = board.grid[0][0].if_wall(0,0,5,5);
    ASSERT_EQ(true, isWall);
}

TEST(Creature, if_wall_4)
{
    Darwin board(5,5,5);
    Species hopper;
    Creature x("hopper", 3, hopper);
    board.addCreature(x,0,4);
    bool isWall = board.grid[0][4].if_wall(0,4,5,5);
    ASSERT_EQ(false, isWall);
}

TEST(Creature, if_wall_5)
{
    Darwin board(7,9,5);
    Species trap;
    Creature x("trap", 3, trap);
    board.addCreature(x,6,8);
    bool isWall = board.grid[6][8].if_wall(6,8,7,9);
    ASSERT_EQ(true, isWall);
}

TEST(Creature, if_random_1)
{
    bool tempb;
    srand(0);
    int temp = rand();
    if(temp %2 == 1)
        tempb = true;
    else
        tempb = false;

    srand(0);
    Species hopper;
    Creature x("hopper", 1, hopper);
    bool isRand = x.if_random();
    ASSERT_EQ(tempb, isRand);
}

TEST(Creature, if_random_2)
{
    bool tempb;
    srand(0);
    int temp = rand();
    if(temp %2 == 1)
        tempb = true;
    else
        tempb = false;

    srand(0);
    Species rover;
    Creature x("rover", 1, rover);
    bool isRand = x.if_random();
    ASSERT_EQ(tempb, isRand);
}

TEST(Creature, if_random_3)
{
    bool tempb;
    srand(0);
    int temp = rand();
    if(temp %2 == 1)
        tempb = true;
    else
        tempb = false;

    srand(0);
    Species trap;
    Creature x("trap", 2, trap);
    bool isRand = x.if_random();
    ASSERT_EQ(tempb, isRand);
}

TEST(Creature, if_random_4)
{
    bool tempb;
    srand(0);
    int temp = rand();
    if(temp %2 == 1)
        tempb = true;
    else
        tempb = false;

    srand(0);
    Species food;
    Creature x("food", 3, food);
    bool isRand = x.if_random();
    ASSERT_EQ(tempb, isRand);
}

TEST(Creature, if_random_5)
{
    bool tempb;
    srand(0);
    int temp = rand();
    if(temp %2 == 1)
        tempb = true;
    else
        tempb = false;

    srand(0);
    Species rover;
    Creature x("rover", 2, rover);
    bool isRand = x.if_random();
    ASSERT_EQ(tempb, isRand);
}

TEST(Creature, isCreature_1)
{
    Species hopper;
    Creature x("hopper", 1, hopper);
    bool creature = x.isCreature();
    ASSERT_EQ(true, creature);
} 

TEST(Creature, isCreature_2)
{
    Species food;
    Creature x(".", 1, Species());
    bool creature = x.isCreature();
    ASSERT_EQ(false, creature);
} 

TEST(Creature, isCreature_3)
{
    Species trap;
    Creature x("trap", 1, trap);
    bool creature = x.isCreature();
    ASSERT_EQ(true, creature);
} 

TEST(Creature, isCreature_4)
{
    Species calamari;
    Creature x(".", 1, calamari);
    bool creature = x.isCreature();
    ASSERT_EQ(false, creature);
} 

TEST(Creature, isCreature_5)
{
    Species hopper;
    Creature x("hopper", 1, hopper);
    bool creature = x.isCreature();
    ASSERT_EQ(true, creature);
} 

TEST(Creature, facing_1)
{
    Species hopper;
    Creature x("hopper", 1, hopper);
    ASSERT_EQ(1, x.facing());
}

TEST(Creature, facing_2)
{
    Species rover;
    Creature x("rover", 0, rover);
    ASSERT_EQ(0, x.facing());
}

TEST(Creature, facing_3)
{
    Species trap;
    Creature x("trap", 3, trap);
    ASSERT_EQ(3, x.facing());
}

TEST(Creature, facing_4)
{
    Species food;
    Creature x("food", 2, food);
    ASSERT_EQ(2, x.facing());
}

TEST(Creature, facing_5)
{
    Species trap;
    Creature x("trap", 1, trap);
    ASSERT_EQ(1, x.facing());
}

TEST(Creature, if_enemy_1)
{
    Darwin board(5,5,5);
    Species hopper;
    Species rover;
    Creature x("hopper", 2, hopper);
    Creature y("rover", 2, rover);
    board.addCreature(x,2,1);
    board.addCreature(y,2,2);
    bool enemy = board.grid[2][1].if_enemy(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(true, enemy);
}

TEST(Creature, if_enemy_2)
{
    Darwin board(5,5,5);
    Species rover;
    Creature x("rover", 2, rover);
    Creature y("rover", 2, rover);
    board.addCreature(x,2,1);
    board.addCreature(y,2,2);
    bool enemy = board.grid[2][1].if_enemy(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(false, enemy);
}

TEST(Creature, if_enemy_3)
{
    Darwin board(5,5,5);
    Species food;
    Creature x("food", 2, food);
    Creature y("food", 2, food);
    board.addCreature(x,2,1);
    board.addCreature(y,2,2);
    bool enemy = board.grid[2][1].if_enemy(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(false, enemy);
}

TEST(Creature, if_enemy_4)
{
    Darwin board(5,5,5);
    Species hopper;
    Species trap;
    Creature x("hopper", 2, hopper);
    Creature y("trap", 2, trap);
    board.addCreature(x,2,1);
    board.addCreature(y,2,2);
    bool enemy = board.grid[2][1].if_enemy(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(true, enemy);
}

TEST(Creature, if_enemy_5)
{
    Darwin board(5,5,5);
    Species hopper;
    Species trap;
    Creature x("trap", 2, trap);
    Creature y("trap", 2, trap);
    board.addCreature(x,2,1);
    board.addCreature(y,2,2);
    bool enemy = board.grid[2][1].if_enemy(board.grid[2][2], 2, 1, 5, 5);
    ASSERT_EQ(false, enemy);
}

TEST(Species, getInstruction_1)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0); 
    string inst = food.getInstruction(0);
    ASSERT_EQ("left", inst);
}

TEST(Species, getInstruction_2)
{
    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0); 
    string inst = trap.getInstruction(3);
    ASSERT_EQ("infect", inst);
}

TEST(Species, getInstruction_3)
{
    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0); 
    string inst = rover.getInstruction(5);
    ASSERT_EQ("right", inst);
}

TEST(Species, getInstruction_4)
{
    Species hopper;
    hopper.addInstruction("hop", -1);
    hopper.addInstruction("go", 0);
    string inst = hopper.getInstruction(1);
    ASSERT_EQ("go", inst);
}

TEST(Species, getInstruction_5)
{
    Species squid;
    squid.addInstruction("boogaloo", -1);
    squid.addInstruction("shrimp", 0); 
    string inst = squid.getInstruction(0);
    ASSERT_EQ("boogaloo", inst);
}

TEST(Species, changePc_1)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0); 
    int n = food.changePc(0);
    ASSERT_EQ(-1, n);
}

TEST(Species, changePc_2)
{
    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0); 
    int n = trap.changePc(0);
    ASSERT_EQ(3, n);
}

TEST(Species, changePc_3)
{
    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0); 
    int n = rover.changePc(2);
    ASSERT_EQ(5, n);
}

TEST(Species, changePc_4)
{
    Species hopper;
    hopper.addInstruction("hop", -1);
    hopper.addInstruction("go", 0);
    int n = hopper.changePc(1);
    ASSERT_EQ(0, n);
}

TEST(Species, changePc_5)
{
    Species squid;
    squid.addInstruction("boogaloo", -1);
    squid.addInstruction("shrimp", 0); 
    int n = squid.changePc(0);
    ASSERT_EQ(-1, n);
}

TEST(Creature, Constructor_1)
{
    Species food;
    Creature x("food", 2, food);
    ASSERT_EQ("food", x._name);
}

TEST(Creature, Constructor_2)
{
    Species hopper;
    Creature x("hopper", 1, hopper);
    ASSERT_EQ(1, x._direction);
}

TEST(Creature, Constructor_3)
{
    Species squid;
    Creature x("squid", 2, squid);
    ASSERT_EQ("squid", x._name);
}

TEST(Creature, Constructor_4)
{
    Species trap;
    Creature x("trap", 2, trap);
    ASSERT_EQ("trap", x._name);
}

TEST(Creature, Constructor_5)
{
    Species rover;
    Creature x("rover", 3, rover);
    ASSERT_EQ(3, x._direction);
}

TEST(Darwin, Constructor_1)
{
    Darwin board(5,5,5);
    ASSERT_EQ(board._row, 5);
}

TEST(Darwin, Constructor_2)
{
    Darwin board(12,12,5);
    ASSERT_EQ(board._total, 5);
}

TEST(Darwin, Constructor_3)
{
    Darwin board(54,72,5);
    ASSERT_EQ(board._col, 72);
}

TEST(Darwin, Constructor_4)
{
    Darwin board(500,5,5);
    ASSERT_EQ(board._row, 500);
}

TEST(Darwin, Constructor_5)
{
    Darwin board(200,200,1);
    ASSERT_EQ(board._total, 1);
}

TEST(Creature, infect_1)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0); 
    

    Darwin board(5,5,5);

    Creature x("food", 3, food);
    Creature y("rover", 1, rover);
    board.addCreature(x, 0, 0);
    board.addCreature(y, 1, 0);
    Creature infex = board.grid[1][0].infect(x,0);
    ASSERT_EQ("rover", infex._name);

}

TEST(Creature, infect_2)
{
    Species hopper;
    hopper.addInstruction("hop", -1);
    hopper.addInstruction("go", 0);

    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0); 
    

    Darwin board(5,5,5);

    Creature x("hopper", 3, hopper);
    Creature y("rover", 1, rover);
    board.addCreature(x, 0, 0);
    board.addCreature(y, 1, 0);
    Creature infex = board.grid[1][0].infect(x,0);
    ASSERT_EQ("rover", infex._name);

}

TEST(Creature, infect_3)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0); 
    

    Darwin board(5,5,5);

    Creature x("food", 3, food);
    Creature y("rover", 1, rover);
    board.addCreature(x, 0, 0);
    board.addCreature(y, 1, 0);
    Creature infex = board.grid[1][0].infect(x,0);
    ASSERT_EQ(3, infex._direction);

}

TEST(Creature, infect_4)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0);
    

    Darwin board(5,5,5);

    Creature x("food", 3, food);
    Creature y("trap", 1, trap);
    board.addCreature(x, 0, 0);
    board.addCreature(y, 1, 0);
    Creature infex = board.grid[1][0].infect(x,0);
    ASSERT_EQ("if_enemy", infex._spec.getInstruction(0));

}

TEST(Creature, infect_5)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);

    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0);
    

    Darwin board(5,5,5);

    Creature x("food", 3, food);
    Creature y("trap", 1, trap);
    board.addCreature(x, 0, 0);
    board.addCreature(y, 1, 0);
    Creature infex = board.grid[1][0].infect(x,0);
    ASSERT_EQ("trap", infex._name);
}

TEST(Species, addInstruction_1)
{
    Species food;
    food.addInstruction("left", -1);
    food.addInstruction("go", 0);
    ASSERT_EQ("go", food.getInstruction(1));
}

TEST(Species, addInstruction_2)
{
    Species trap;
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left", -1);
    trap.addInstruction("go", 0);
    trap.addInstruction("infect", -1);
    trap.addInstruction("go", 0);
    ASSERT_EQ("infect", trap.getInstruction(3));
}

TEST(Species, addInstruction_3)
{
    Species rover;
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("right", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("hop", -1);
    rover.addInstruction("go", 0);
    rover.addInstruction("infect", -1);
    rover.addInstruction("go", 0);
    ASSERT_EQ("if_random", rover.getInstruction(2));
}

TEST(Species, addInstruction_4)
{
    Species hopper;
    hopper.addInstruction("hop", -1);
    hopper.addInstruction("go", 0);
    ASSERT_EQ("hop", hopper.getInstruction(0));
}