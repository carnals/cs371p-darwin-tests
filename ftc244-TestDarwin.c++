// --------------------------------
// projects/Darwin/TestDarwin.c++
// Frank Cerasoli
// Tim Carroll
// --------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

    % valgrind TestDarwin > TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

TEST(Game, constructor_big){
        Game d(99,100);
        ASSERT_TRUE(d.numRows == 99);
        ASSERT_TRUE(d.numCols == 100);
}

TEST(Game, constructor_empty){
        Game d(0,0);
        ASSERT_TRUE(d.numRows == 0);
        ASSERT_TRUE(d.numCols == 0);
}

TEST(Game, if_wall_west) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(0,0,&s,0);
    ASSERT_TRUE(g.if_wall(&c));
    }

TEST(Game, if_wall_north) {
    Game g(8,8);
    Species s = Species(1);
    Creature c = Creature(0,0,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, if_wall_east) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(7,7,&s,2);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, if_wall_south) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(7,7,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, if_wall_west_2) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(2,0,&s,0);
    ASSERT_TRUE(g.if_wall(&c));
    }

TEST(Game, if_wall_north_2) {
    Game g(8,8);
    Species s = Species(1);
    Creature c = Creature(0,2,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, if_wall_east_2) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(6,7,&s,2);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, if_wall_south_2) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(7,6,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
}

TEST(Game, check_empty) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(0,0,&s,2);
    Creature c2 = Creature(0,1,&s, 0);
    g.if_wall(&c);
    ASSERT_TRUE(g.if_empty(&c2));
    }

TEST(Game, check_empty_2) {
    Game g(8,8);
    Species s = Species(1);
    Creature c = Creature(0,0,&s,3);
    Creature c2 = Creature(1,0,&s, 1);
    g.if_wall(&c2);
    ASSERT_TRUE(g.if_empty(&c));
}

TEST(Game, check_empty_3) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(7,7,&s,1);
    Creature c2 = Creature(6,7,&s, 0);
    g.if_wall(&c);
    ASSERT_TRUE(g.if_empty(&c2));
}

TEST(Game, check_empty_4) {
    Game g(8,8);
    Species s = Species(0);
    Creature c = Creature(7,7,&s,0);
    Creature c2 = Creature(7,6,&s, 0);
    g.if_wall(&c);
    ASSERT_TRUE(g.if_empty(&c2));
}
TEST(Game, if_wall_1) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,0,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_2) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,1,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_3) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,2,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_4) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,3,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_5) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,4,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_6) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,5,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_7) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,6,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_8) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,7,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_9) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,8,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_10) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,9,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_11) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,10,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_12) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,11,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_13) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,12,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_14) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,13,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_15) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,14,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_16) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,15,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_17) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,16,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_18) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,17,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_19) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,18,&s,3);
    ASSERT_TRUE(g.if_wall(&c));
    }

    TEST(Game, if_wall_20) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,1);
    ASSERT_TRUE(g.if_wall(&c));
    }


TEST(Game, if_empty_1) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,0,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_2) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,1,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_3) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,2,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_4) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,3,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_5) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,4,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_6) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,5,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_7) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,6,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_8) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,7,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_9) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,8,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_10) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,9,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_11) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,10,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_12) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,11,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_13) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,12,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_14) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,13,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_15) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,14,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_16) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,15,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_17) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,16,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_18) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,17,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_19) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,18,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}

TEST(Game, if_empty_20) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,1);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_21) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_22) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_23) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_24) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,19,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_25) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,2,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
TEST(Game, if_empty_26) {
    Game g(1,25);
    Species s = Species(0);
    Creature c = Creature(0,1,&s,3);
    ASSERT_FALSE(g.if_empty(&c));
}
