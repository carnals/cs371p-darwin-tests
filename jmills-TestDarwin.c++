// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "Darwin.h"

// ----------
// Game Tests
// ----------


// -------------
// Position Tests
// -------------

// move()

TEST(Darwin, position_move_down){
    Position p(0,0,direction_down);
    p.move();
    ASSERT_TRUE(p.y == 1 && p.x == 0);
}

TEST(Darwin, position_move_up){
    Position p(1,1,direction_up);
    p.move();
    ASSERT_TRUE(p.y == 0 && p.x == 1);
}

TEST(Darwin, position_move_right){
    Position p(0,0,direction_right);
    p.move();
    ASSERT_TRUE(p.y == 0 && p.x == 1);
}

TEST(Darwin, position_move_left){
    Position p(1,0,direction_left);
    p.move();
    ASSERT_TRUE(p.y == 0 && p.x == 0);
}

//  left()

TEST(Darwin, position_left_direction_up) {
    Position p(0,0,direction_up);
    p.left();
    ASSERT_TRUE(p.dir == direction_left);
}

TEST(Darwin, position_left_direction_left) {
    Position p(0,0,direction_left);
    p.left();
    ASSERT_TRUE(p.dir == direction_down);
}

TEST(Darwin, position_left_direction_down) {
    Position p(0,0,direction_down);
    p.left();
    ASSERT_TRUE(p.dir == direction_right);
}

TEST(Darwin, position_left_direction_right) {
    Position p(0,0,direction_right);
    p.left();
    ASSERT_TRUE(p.dir == direction_up);
}

//  right()

TEST(Darwin, position_right_direction_up) {
    Position p(0,0,direction_up);
    p.right();
    ASSERT_TRUE(p.dir == direction_right);
}

TEST(Darwin, position_right_direction_left) {
    Position p(0,0,direction_left);
    p.right();
    ASSERT_TRUE(p.dir == direction_up);
}

TEST(Darwin, position_right_direction_down) {
    Position p(0,0,direction_down);
    p.right();
    ASSERT_TRUE(p.dir == direction_left);
}

TEST(Darwin, position_right_direction_right) {
    Position p(0,0,direction_right);
    p.right();
    ASSERT_TRUE(p.dir == direction_down);
}

// --------------
// GridItem Tests
// --------------

// is_wall(position p)

TEST(Darwin, board_is_wall_true) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_left);
    ASSERT_TRUE(b.is_wall(p));
}

TEST(Darwin, board_is_wall_false) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    ASSERT_TRUE(!b.is_wall(p));
}

// is_empty(Position p)

TEST(Darwin, board_is_empty_true) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    ASSERT_TRUE(b.is_empty(p));
}

TEST(Darwin, board_is_empty_false) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    Position o(0,1,direction_up);
    Creature f(creature_type_food, p, &b);
    b.add_creature(&f, p);
    ASSERT_TRUE(!b.is_empty(o));
}

// is_enemy

TEST(Darwin, board_is_enemy) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    Position o(0,1,direction_up);
    Creature f(creature_type_food, p, &b);
    b.add_creature(&f, p);
    ASSERT_TRUE(b.is_enemy(creature_type_rover, o));
}

TEST(Darwin, board_is_enemy_false) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    Position o(0,1,direction_up);
    Creature f(creature_type_food, p, &b);
    b.add_creature(&f, p);
    ASSERT_TRUE(!b.is_enemy(creature_type_food, o));
}

TEST(Darwin, board_is_enemy_empty) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position o(0,1,direction_up);
    ASSERT_TRUE(!b.is_enemy(creature_type_food, o));
}

//next_creature

TEST(Darwin, next_creature) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position p(0,0,direction_right);
    Position o(0,1,direction_up);
    Creature f(creature_type_food, o, &b);
    b.add_creature(&f, o);
    ASSERT_TRUE(b.next_creature(p) == &f);
}

TEST(Darwin, next_creature_null) {
    GridItem g[9];
    GridItem* grid[9];
    for (int i = 0; i < 9; i++) 
      grid[i] = &g[i];
    Board b (3, 3, grid);
    Position o(0,0,direction_up);
    ASSERT_TRUE(!b.next_creature(o));
}



