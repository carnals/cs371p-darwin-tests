// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
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

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Darwin.h"
#include "gtest/gtest.h"

using namespace std;


// -----------
// TestDarwin
// -----------

TEST(Darwin, species_1){
    species test('t');
    ASSERT_TRUE(test.mySymbol() == 't');
    ASSERT_TRUE(test.symbol == 't');}

TEST(Darwin, species_2){
    species best('b');
    ASSERT_TRUE(best.mySymbol() == 'b');
    ASSERT_TRUE(best.symbol == 'b');}
TEST(Darwin, species_3){
    species test('a');
    ASSERT_TRUE(test.mySymbol() == 'a');
    ASSERT_TRUE(test.symbol == 'a');}

TEST(Darwin, speciesAdd_1){
    species test('t');
    test.addInstruction(i_hop, -1);

    ASSERT_TRUE(test.get(0).a == i_hop);
    ASSERT_TRUE(test.get(0).next == -1);
    ASSERT_TRUE(test.program[0].a == i_hop);
    ASSERT_TRUE(test.program[0].next == -1);
}
TEST(Darwin, speciesAdd_2){
    species test('t');
    test.addInstruction(i_hop, -1);
    test.addInstruction(i_infect, -1);


    ASSERT_TRUE(test.get(0).a == i_hop);
    ASSERT_TRUE(test.get(0).next == -1);
    ASSERT_TRUE(test.program[0].a == i_hop);
    ASSERT_TRUE(test.program[0].next == -1);
    ASSERT_TRUE(test.get(1).a == i_infect);
    ASSERT_TRUE(test.get(1).next == -1);
    ASSERT_TRUE(test.program[1].a == i_infect);
    ASSERT_TRUE(test.program[1].next == -1);

}
TEST(Darwin, speciesAdd_3){
    species test('t');
    test.addInstruction(i_hop, -1);
    test.addInstruction(i_infect, -1);
    test.addInstruction(i_go, 0);

    ASSERT_TRUE(test.get(0).a == i_hop);
    ASSERT_TRUE(test.get(0).next == -1);
    ASSERT_TRUE(test.program[0].a == i_hop);
    ASSERT_TRUE(test.program[0].next == -1);
    ASSERT_TRUE(test.get(1).a == i_infect);
    ASSERT_TRUE(test.get(1).next == -1);
    ASSERT_TRUE(test.program[1].a == i_infect);
    ASSERT_TRUE(test.program[1].next == -1);
    ASSERT_TRUE(test.get(2).a == i_go);
    ASSERT_TRUE(test.get(2).next == 0);
    ASSERT_TRUE(test.program[2].a == i_go);
    ASSERT_TRUE(test.program[2].next == 0);
}


TEST(Darwin, creature1){
    species test('t');
    creature t(test, west);
    ASSERT_TRUE(t.d == west);
}
TEST(Darwin, creature2){
    species test('t');
    creature t(test, east);
    ASSERT_TRUE(t.d == east);
}
TEST(Darwin, creature3){
    species test('t');
    creature t(test, north);
    ASSERT_TRUE(t.d == north);
}

TEST(Darwin, creatureCopy_1){
    species test('t');
    creature t(test, east);
    creature a(test, west);
    a.copy(t);
    ASSERT_TRUE(a.d == t.d);
    ASSERT_TRUE(a.s == t.s);
    ASSERT_TRUE(a.pCounter == t.pCounter);
}

TEST(Darwin, creatureCopy_2){
    species test('t');
    species test2('a');
    creature t(test, east);
    creature a(test2, south);
    a.copy(t);
    ASSERT_TRUE(a.d == t.d);
    ASSERT_TRUE(a.s == t.s);
    ASSERT_TRUE(a.pCounter == t.pCounter);
}

TEST(Darwin, creatureCopy_3){
    species test('t');
    creature t(test, east);
    creature a(test, north);
    a.copy(t);
    ASSERT_TRUE(a.d == t.d);
    ASSERT_TRUE(a.s == t.s);
    ASSERT_TRUE(a.pCounter == t.pCounter);
}

TEST(Darwin, creatureToDo_1){
    species test('t');
    test.addInstruction(i_hop, -1);
    creature t(test, east);
    
    ASSERT_TRUE(t.toDo(0).a == i_hop);
    ASSERT_TRUE(t.toDo(0).next == -1);
}

TEST(Darwin, creatureToDo_2){
    species test('t');
    test.addInstruction(i_hop, -1);
    test.addInstruction(i_infect, -1);
    creature t(test, east);
    
    ASSERT_TRUE(t.toDo(1).a == i_infect);
    ASSERT_TRUE(t.toDo(1).next == -1);
}


TEST(Darwin, creatureToDo_3){
    species test('t');
    test.addInstruction(i_hop, -1);
    test.addInstruction(i_hop, -1);
    test.addInstruction(i_go, 0);
    creature t(test, east);
    
    ASSERT_TRUE(t.toDo(2).a == i_go);
    ASSERT_TRUE(t.toDo(2).next == 0);
}

TEST(Darwin, changeType_1){
    species test('t');
    species test2('b');

    creature t(test, north);
    creature t2(test2, east);
    t2.changeType(t.s);
    ASSERT_TRUE(t2.s == t.s);
    ASSERT_TRUE(t2.pCounter == 0);

}

TEST(Darwin, changeType_2){
    species test('t');
    species test3('b');

    creature t(test, north);
    creature t2(test3, east);
    t2.changeType(t.s);
    ASSERT_TRUE(t2.s == t.s);
    ASSERT_TRUE(t2.pCounter == 0);

}

TEST(Darwin,increaseCounter_1){
    species test('t');
    creature t(test, west);
    t.increaseCounter();
    ASSERT_TRUE(t.pCounter == 1);

}

TEST(Darwin,increaseCounter_2){
    species test('t');
    creature t(test, west);
    t.increaseCounter();
    t.increaseCounter();
    ASSERT_TRUE(t.pCounter == 2);
    
}
TEST(Darwin,increaseCounter_3){
    species test('t');
    creature t(test, west);
    t.increaseCounter();
    t.increaseCounter();
    t.increaseCounter();
    ASSERT_TRUE(t.pCounter == 3);
    
}

TEST(Darwin, turnLeft_1){
    species test('t');
    creature t(test, west);
    t.turnLeft();
    ASSERT_TRUE(t.d == south);

}

TEST(Darwin, turnLeft_2){
    species test('t');
    creature t(test, north);
    t.turnLeft();
    ASSERT_TRUE(t.d == west);
    
}
TEST(Darwin, turnLeft_3){
    species test('t');
    creature t(test, south);
    t.turnLeft();
    ASSERT_TRUE(t.d == east);
    
}

TEST(Darwin, turnRight_1){
    species test('t');
    creature t(test, west);
    t.turnRight();
    ASSERT_TRUE(t.d == north);

}

TEST(Darwin, turnRight_2){
    species test('t');
    creature t(test, north);
    t.turnRight();
    ASSERT_TRUE(t.d == east);
    
}
TEST(Darwin, turnRight_3){
    species test('t');
    creature t(test, south);
    t.turnRight();
    ASSERT_TRUE(t.d == west);
    
}

TEST(Darwin, charSymbol_1){
    species test('t');
    creature t(test, south);
    ASSERT_TRUE(t.symbol() == 't');
    
}

TEST(Darwin, charSymbol_2){
    species test('b');
    creature t(test, south);
    ASSERT_TRUE(t.symbol() == 'b');
    
}

TEST(Darwin, charSymbol_3){
    species test('c');
    creature t(test, south);
    ASSERT_TRUE(t.symbol() == 'c');
    
}

TEST(Darwin, isNull_1){
    species test('b');
    creature t;
    ASSERT_TRUE(t.isNull());
    
}

TEST(Darwin, isNull_2){
    species test('b');
    creature t(test, north);
    ASSERT_TRUE(!t.isNull());
}

TEST(Darwin, emptyBlock_1){
    species test('b');
    creature t(test, north);
    t.emptyBlock();
    ASSERT_TRUE(t.isNull());
}

TEST(Darwin, emptyBlock_2){
    species test('c');
    creature t(test, north);
    t.emptyBlock();
    ASSERT_TRUE(t.isNull());
}

TEST(Darwin, emptyBlock_3){
    species test('d');
    creature t(test, north);
    t.emptyBlock();
    ASSERT_TRUE(t.isNull());
}


TEST(Darwin, outofBounds_1){
    Darwin x(8,8);
    ASSERT_TRUE(x.outOfBounds(9,9));
}
TEST(Darwin, outofBounds_2){
    Darwin x(50,50);
    ASSERT_TRUE(x.outOfBounds(70,20));
}
TEST(Darwin, outofBounds_3){
    Darwin x(20,30);
    ASSERT_TRUE(x.outOfBounds(30,20));
}


TEST(Darwin,if_empty_1){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 0, 0);

    ASSERT_TRUE(!x.if_empty(0,0));

}

TEST(Darwin,if_empty_2){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 1, 1);

    ASSERT_TRUE(x.if_empty(1,1));

}

TEST(Darwin,if_empty_3){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 0, 0);
    x.add (t, 1, 0);
    ASSERT_TRUE(!x.if_empty(1,0));

}


TEST(Darwin, if_enemy_1){
    Darwin x(10, 10);
    species test('b');
    species test2('c');
    creature t(test, north);
    creature t2(test2,north);
    x.add(t, 0, 0);
    x.add (t2, 1, 0);
    ASSERT_TRUE(x.if_enemy(1,0));

}

TEST(Darwin, if_enemy_2){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 1, 1);
    ASSERT_TRUE(!x.if_enemy(1,1));

}
TEST(Darwin, if_enemy_3){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    creature t2(test,north);
    x.add(t, 0, 0);
    x.add (t, 1, 0);

    ASSERT_TRUE(!x.if_enemy(1,0));

}



TEST(Darwin,if_wall_1){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 0, 0);

    ASSERT_TRUE(x.if_wall(0,0));

}

TEST(Darwin,if_wall_2){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 1, 1);

    ASSERT_TRUE(!x.if_wall(1,1));

}

TEST(Darwin,if_wall_3){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 0, 0);
    x.add (t, 1, 0);
    ASSERT_TRUE(!x.if_wall(1,0));

}


TEST(Darwin,hop_1){
    Darwin x(10, 10);
    species test('b');
    creature t(test, south);
    x.add(t, 0, 0);
    x.hop(0,0);

    ASSERT_TRUE(x.grid[0][0].isNull());

}

TEST(Darwin,hop_2){
    Darwin x(10, 10);
    species test('b');
    creature t(test, north);
    x.add(t, 0, 0);
    x.hop(0,0);

    ASSERT_TRUE(!x.grid[0][0].isNull());

}

TEST(Darwin,hop_3){
    Darwin x(10, 10);
    species test('b');
    creature t(test, south);
    x.add(t, 0, 0);
    x.add(t, 1, 0);
    x.hop(1,0);

    ASSERT_TRUE(!x.grid[0][0].isNull());
    ASSERT_TRUE(x.grid[1][0].isNull());

}

TEST(Darwin,infect_1){
    Darwin x(10, 10);
    species test('b');
    species test2('a');
    creature t(test, south);
    creature t2(test2, north);
    x.add(t, 0, 0);
    x.add(t2, 1, 0);
    x.infect(1,0);

    ASSERT_TRUE(x.grid[0][0].s == t2.s);

}

TEST(Darwin,infect_2){
    Darwin x(10, 10);
    species test('b');
    species test2('a');
    creature t(test, south);
    creature t2(test2, north);
    x.add(t, 0, 0);
    x.add(t, 1, 0);
    x.infect(1,0);

    ASSERT_TRUE(!(x.grid[0][0].s == t2.s));

}

TEST(Darwin,infect_3){
    Darwin x(10, 10);
    species test('b');
    species test2('a');
    creature t(test, south);
    creature t2(test2, north);
    x.add(t, 0, 0);
    x.add(t, 1, 0);
    x.infect(1,0);

    ASSERT_TRUE(x.grid[0][0].s == t.s);

}














