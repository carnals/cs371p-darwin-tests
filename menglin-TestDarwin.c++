/*
 * TestDarwin.c++
 *
 *  Created on: Oct 30, 2013
 *      Author: menglin
 */

#include "gtest/gtest.h"
#include "Darwin.h"

TEST(Darwin, test_food1)
{
	BoardManager test_board(5,5);
	Creature f(0, 0, DOWN, 'f');
	f.act();
	ASSERT_TRUE(board.at(0).at(0)->d == RIGHT);
}

TEST(Darwin, test_food2)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, UP, 'f');
	Creature f2(3, 3, LEFT, 'f');
	f.left();
	f.left();
	f.left();
	f2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(3).at(3)->d == DOWN);
}

TEST(Darwin, test_food3)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, UP, 'f');
	Creature f2(1, 3, LEFT, 'f');
	f.left();
	f.left();
	f.left();
	f2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(1).at(3)->d == DOWN);
}

TEST(Darwin, test_food4)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, UP, 'f');
	Creature f2(3, 2, LEFT, 'f');
	f.left();
	f.left();
	f.left();
	f2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(3).at(2)->d == DOWN);
}

TEST(Darwin, test_food5)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, UP, 'f');
	Creature f2(4, 4, LEFT, 'f');
	f.left();
	f.left();
	f.left();
	f2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(4).at(4)->d == DOWN);
}

TEST(Darwin, test_trap1)
{
	BoardManager test_board(5, 5);
	Creature t(1, 1, UP, 't');
	Creature t2(4, 4, LEFT, 't');
	t.left();
	t.left();
	t.left();
	t2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(4).at(4)->d == DOWN);
}

TEST(Darwin, test_trap2)
{
	BoardManager test_board(5, 5);
	Creature t(1, 1, UP, 't');
	Creature t2(4, 4, RIGHT, 't');
	t.left();
	t.left();
	t.left();
	t2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(4).at(4)->d == UP);
}

TEST(Darwin, test_trap3)
{
	BoardManager test_board(5, 5);
	Creature t(1, 1, UP, 't');
	Creature t2(4, 4, DOWN, 't');
	t.left();
	t.left();
	t.left();
	t2.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
	ASSERT_TRUE(board.at(4).at(4)->d == RIGHT);
}

TEST(Darwin, test_hop)
{
	BoardManager test_board(4, 4);
	Creature h(0, 0, LEFT, 'h');
	h.hop();
	ASSERT_TRUE(board.at(0).at(0));
}

TEST(Darwin, test_hop2)
{
	BoardManager test_board(4, 4);
	Creature h(2, 2, UP, 'h');
	h.hop();
	h.hop();
	h.hop();
	h.hop();
	ASSERT_TRUE(board.at(0).at(2));
}

TEST(Darwin, test_hop3)
{
	BoardManager test_board(8, 8);
	Creature h(0, 0, UP, 'h');
	Creature h2(1, 0, UP, 'h');
	h2.hop();
	ASSERT_TRUE(board.at(1).at(0));
}

TEST(Darwin, test_left)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, LEFT, 'f');
	f.left();
	f.left();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
}

TEST(Darwin, test_left2)
{
	BoardManager test_board(5, 5);
	Creature h(2, 2, RIGHT, 'h');
	h.hop();
	h.left();
	ASSERT_TRUE(board.at(2).at(3)->d == UP);
}

TEST(Darwin, test_left3)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_left4)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, DOWN, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == RIGHT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_left5)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_left6)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_left7)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_left8)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.left();
	Creature f1(1, 0, DOWN, 'f');
	f1.left();
	f1.left();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_right)
{
	BoardManager test_board(5, 5);
	Creature f(1, 1, LEFT, 'f');
	f.right();
	f.right();
	ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
}

TEST(Darwin, test_right2)
{
	BoardManager test_board(5, 5);
	Creature h(2, 2, RIGHT, 'h');
	h.hop();
	h.right();
	ASSERT_TRUE(board.at(2).at(3)->d == DOWN);
}

TEST(Darwin, test_right3)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.right();
	Creature f1(1, 0, DOWN, 'f');
	f1.right();
	f1.right();
	ASSERT_TRUE(board.at(0).at(0)->d == RIGHT);
	ASSERT_TRUE(board.at(1).at(0)->d == UP);
}

TEST(Darwin, test_right4)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, RIGHT, 'f');
	f.right();
	Creature f1(1, 0, DOWN, 'f');
	f1.right();
	f1.right();
	f1.right();
	f1.right();
	ASSERT_TRUE(board.at(0).at(0)->d == DOWN);
	ASSERT_TRUE(board.at(1).at(0)->d == DOWN);
}

TEST(Darwin, test_right5)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	f.right();
	f.right();
	f.right();
	Creature f1(1, 0, DOWN, 'f');
	f1.right();
	ASSERT_TRUE(board.at(0).at(0)->d == LEFT);
	ASSERT_TRUE(board.at(1).at(0)->d == LEFT);
}

TEST(Darwin, test_isWallAhead)
{
	BoardManager test_board(8, 8);
	Creature h(3, 4, UP, 'h');
	ASSERT_TRUE(h.isWallAhead() == false);
} 

TEST(Darwin, test_isWallAhead2)
{
	BoardManager test_board(4, 4);
	Creature h(0, 0, LEFT, 'h');
	ASSERT_TRUE(h.isWallAhead() == true);
}

TEST(Darwin, test_isWallAhead3)
{
	BoardManager test_board(4, 4);
	ASSERT_TRUE(!board.at(1).at(0));
	Creature h(1, 1, LEFT, 'h');
	h.hop();
	ASSERT_TRUE(board[1][0]->name == 'h');
}

TEST(Darwin, test_isSpaceAheadEmpty)
{
	BoardManager test_board(4, 4);
	Creature h(0, 0, LEFT, 'h');
	Creature h2(0, 1, LEFT, 'h');
	ASSERT_TRUE(h2.isSpaceAheadEmpty() == false);
}

TEST(Darwin, test_isSpaceAheadEmpty2)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, LEFT, 'f');
	Creature h2(0, 1, RIGHT, 'h');
	Creature h3(1, 1, UP, 'h');
	ASSERT_TRUE(h2.isSpaceAheadEmpty() == true);
	ASSERT_TRUE(h3.isSpaceAheadEmpty() == false);
}

TEST(Darwin, test_isSpaceAheadEmpty3)
{
	BoardManager test_board(4, 4);
	Creature h2(0, 1, RIGHT, 'h');
	Creature h3(1, 1, UP, 'h');
	Creature h4(0, 3, UP, 'h');
	ASSERT_TRUE(h2.isSpaceAheadEmpty() == true);
	ASSERT_TRUE(h3.isSpaceAheadEmpty() == false);
	h2.act();
	ASSERT_TRUE(h2.isSpaceAheadEmpty() == false);
	ASSERT_TRUE(h3.isSpaceAheadEmpty() == true);
}

TEST(Darwin, test_isEnemyAhead)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, UP, 'f');
	Creature h(1, 0, UP, 'h');
	ASSERT_TRUE(h.isEnemyAhead() == true);		
}

TEST(Darwin, test_isEnemyAhead2)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, RIGHT, 'f');
	Creature h(1, 1, UP, 'h');
	h.hop();
	ASSERT_TRUE(f.isEnemyAhead() == true);		
}


TEST(Darwin, test_isEnemyAhead3)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, RIGHT, 'f');
	Creature h(0, 1, DOWN, 'h');
	ASSERT_TRUE(f.isEnemyAhead() == true);		
	h.hop();
	ASSERT_TRUE(f.isEnemyAhead() == false);			
}

TEST(Darwin, test_isEnemyAhead4)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, RIGHT, 'f');
	Creature h(0, 1, DOWN, 'h');
	ASSERT_TRUE(f.isEnemyAhead() == true);
}

TEST(Darwin, test_isEnemyAhead5)
{
	BoardManager test_board(4, 4);
	Creature f(0, 0, RIGHT, 'f');
	Creature h(1, 1, DOWN, 'h');
	ASSERT_TRUE(f.isEnemyAhead() == false);
}

TEST(Darwin, test_isEnemyAhead6)
{
	BoardManager test_board(4, 4);
	Creature f(1, 1, RIGHT, 'f');
	Creature h(0, 1, DOWN, 'h');
	ASSERT_TRUE(h.isEnemyAhead() == true);
	ASSERT_TRUE(f.isEnemyAhead() == false);
}

TEST(Darwin, test_isEnemyAhead7)
{
        BoardManager test_board(4, 4);
        Creature f(0, 0, DOWN, 'f');
        Creature f2(1, 0, UP, 'f');
        ASSERT_TRUE(f2.isEnemyAhead() == false);
}

TEST(Darwin, test_isEnemyAhead8)
{
        BoardManager test_board(4, 4);
        Creature h(0, 1, LEFT, 'h');
        Creature f(1, 0, UP, 'f');
        ASSERT_TRUE(f.isEnemyAhead() == false);
        h.hop();
        ASSERT_TRUE(f.isEnemyAhead() == true);

}

TEST(Darwin, test_infect)
{
	BoardManager test_board(5, 5);
	Creature f(0, 0, UP, 'f');
	Creature t(1, 0, UP, 't');
	t.infect();
	ASSERT_TRUE(f.name == 't');
}

TEST(Darwin, test_infect1)
{
	BoardManager test_board(5, 5);
	Creature t(0, 0, DOWN, 't');
	Creature h(1, 0, DOWN, 'h');
	Creature r(2, 0, DOWN, 'r');
	t.infect();
	ASSERT_TRUE(h.name == 't');
	h.infect();
	ASSERT_TRUE(r.name == 't');
}

TEST(Darwin, test_infect2)
{
	BoardManager test_board(5, 5);
	Creature r(0, 0, DOWN, 'r');
	Creature h(1, 0, RIGHT, 'h');
	Creature t(0, 1, LEFT, 't');
	r.infect();
	ASSERT_TRUE(h.name == 'r');
	t.infect();
	ASSERT_TRUE(r.name == 't');
	ASSERT_TRUE(h.name == 'r');
	ASSERT_TRUE(t.name == 't');
}

TEST(Darwin, test_infect3)
{
        BoardManager test_board(5, 5);
        Creature f(0, 0, RIGHT, 'f');
        Creature f2(0, 1, UP, 'f');
        Creature t(1, 0, UP, 't');
        t.infect();
        f.infect();
        ASSERT_TRUE(f.name == 't');
        ASSERT_TRUE(f2.name == 't');
}

TEST(Darwin, test_infect4)
{
        BoardManager test_board(5, 5);
        Creature f(0, 0, RIGHT, 'f');
        Creature t(0, 1, RIGHT, 't');
        Creature r(0, 2, RIGHT, 'r');
        Creature h(0, 3, RIGHT, 'h');
        f.infect();
        t.infect();
        r.infect();
        ASSERT_TRUE(t.name == 'f');
        ASSERT_TRUE(r.name == 'f');
        ASSERT_TRUE(h.name == 'f');
}

TEST(Darwin, test_infect5)
{
        BoardManager test_board(5, 5);
        Creature f(0, 0, RIGHT, 'f');
        Creature t(0, 1, DOWN, 't');
        Creature r(0, 2, RIGHT, 'r');
        Creature h(0, 3, RIGHT, 'h');
        f.infect();
        t.infect();
        r.infect();
        ASSERT_TRUE(t.name == 'f');
        ASSERT_TRUE(h.name == 'r');
}

TEST(Darwin, test_infect6)
{
        BoardManager test_board(5, 5);
        Creature f(0, 0, UP, 'f');
        Creature t(0, 1, UP, 't');
        Creature r(0, 2, UP, 'r');
        Creature h(0, 3, UP, 'h');
        f.infect();
        t.infect();
        r.infect();
        h.infect();
        ASSERT_TRUE(f.name == 'f');
        ASSERT_TRUE(t.name == 't');
        ASSERT_TRUE(r.name == 'r');
        ASSERT_TRUE(h.name == 'h');
}

TEST(Darwin, test_infect7)
{
        BoardManager test_board(5, 5);
        Creature f(0, 0, UP, 'f');
        Creature t(0, 1, LEFT, 't');
        Creature r(1, 0, UP, 'r');
        t.infect();
        r.infect();
        ASSERT_TRUE(f.name == 'r');
        ASSERT_TRUE(t.name == 't');
        ASSERT_TRUE(r.name == 'r');
}

TEST(Darwin, test_hop4)
{
        BoardManager test_board(2, 2);
        Creature h(0, 0, RIGHT, 'h');
        h.hop();
        h.hop();
        ASSERT_TRUE(!board.at(0).at(0));
}

TEST(Darwin, test_hop5)
{
        BoardManager test_board(2, 2);
        Creature h(0, 0, RIGHT, 'h');
        h.hop();
        h.hop();
        ASSERT_TRUE(board.at(0).at(1));
}

TEST(Darwin, test_hop6)
{
        BoardManager test_board(2, 2);
        Creature h(0, 0, RIGHT, 'h');
        Creature h2(0, 1, LEFT, 'h');
        h.hop();
        h2.hop();
        ASSERT_TRUE(board.at(0).at(0));
        ASSERT_TRUE(board.at(0).at(1));
}

TEST(Darwin, test_trap)
{
	BoardManager test_board(4, 4);
	Creature t(0, 0, DOWN, 't');
	Creature h(0, 1, LEFT, 'h');
	t.act();
	h.act();
	t.act();
	ASSERT_TRUE(h.name == 'h');
}

TEST(Darwin, test_isEnemyAhead18)
{
        BoardManager test_board(4, 4);
        Creature f(0, 0, RIGHT, 'f');
        Creature h(1, 1, UP, 'h');
        ASSERT_TRUE(f.isEnemyAhead() == false);
}

TEST(Darwin, test_isEnemyAhead9)
{
        BoardManager test_board(4, 4);
        Creature f(0, 0, RIGHT, 'f');
        Creature h(1, 1, UP, 'h');
        ASSERT_TRUE(h.isEnemyAhead() == false);
}

TEST(Darwin, test_isEnemyAhead10)
{
        BoardManager test_board(4, 4);
        Creature f(0, 0, RIGHT, 'f');
        Creature t(0, 1, LEFT, 't');
        ASSERT_TRUE(t.isEnemyAhead() == true);
        ASSERT_TRUE(f.isEnemyAhead() == true);
}

TEST(Darwin, test_left18)
{
        BoardManager test_board(5, 5);
        Creature f(1, 1, DOWN, 'f');
        f.left();
        f.left();
        f.left();
        f.left();
        ASSERT_TRUE(board.at(1).at(1)->d == DOWN);
}

TEST(Darwin, test_hop11)
{
        BoardManager test_board(4, 4);
        Creature h(0, 0, RIGHT, 'h');
        Creature t(0, 1, RIGHT, 't');
        ASSERT_TRUE(board.at(0).at(1));
        ASSERT_TRUE(board.at(0).at(0));
}

TEST(Darwin, test_left9)
{
        BoardManager test_board(5, 5);
        Creature f(1, 1, UP, 'f');
        f.left();
        f.left();
        f.left();
        ASSERT_TRUE(board.at(1).at(1)->d == RIGHT);
}

TEST(Darwin, test_left10)
{
        BoardManager test_board(5, 5);
        Creature h(1, 1, RIGHT, 'statuh');
        h.left();
        h.left();
        ASSERT_TRUE(board.at(1).at(1)->d == LEFT);
}

TEST(Darwin, test_hop8)
{
        BoardManager test_board(4, 4);
        Creature h(0, 0, LEFT, 'h');
        h.hop();
        ASSERT_TRUE(board.at(0).at(0));
}

TEST(Darwin, test_hop9)
{
        BoardManager test_board(4, 4);
        Creature h(0, 0, LEFT, 'h');
        h.hop();
        h.hop();
        h.hop();
        ASSERT_TRUE(board.at(0).at(0));
}

TEST(Darwin, test_hop10)
{
        BoardManager test_board(4, 4);
        Creature h(0, 0, RIGHT, 'h');
        Creature h2(0, 1, LEFT, 'h');
        h.hop();
        h2.hop();
        h2.hop();
        ASSERT_TRUE(board.at(0).at(0));
}
