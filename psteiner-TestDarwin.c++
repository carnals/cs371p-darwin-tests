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

// ----
// read
// ----

TEST(Darwin, hello_world) {
    Darwin darwin(8, 8);
    std::ostringstream w;
    w << darwin;
    // std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "Turn = 0.\n"
        "  01234567\n"
        "0 ........\n"
        "1 ........\n"
        "2 ........\n"
        "3 ........\n"
        "4 ........\n"
        "5 ........\n"
        "6 ........\n"
        "7 ........\n");
}

TEST(Darwin, hello_24x24) {
    Darwin darwin(24, 24);
    std::ostringstream w;
    w << darwin;
    // std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "Turn = 0.\n"
        "  012345678901234567890123\n"
        "0 ........................\n"
        "1 ........................\n"
        "2 ........................\n"
        "3 ........................\n"
        "4 ........................\n"
        "5 ........................\n"
        "6 ........................\n"
        "7 ........................\n"
        "8 ........................\n"
        "9 ........................\n"
        "0 ........................\n"
        "1 ........................\n"
        "2 ........................\n"
        "3 ........................\n"
        "4 ........................\n"
        "5 ........................\n"
        "6 ........................\n"
        "7 ........................\n"
        "8 ........................\n"
        "9 ........................\n"
        "0 ........................\n"
        "1 ........................\n"
        "2 ........................\n"
        "3 ........................\n");
}


TEST(Darwin, hello_zero_world) {
    Darwin darwin;
    std::ostringstream w;
    w << darwin;
    // std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "Turn = 0.\n  \n");
}

TEST(Darwin, hello_1x0) {
    Darwin darwin(1,0);
    std::ostringstream w;
    w << darwin;
    //std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "Turn = 0.\n  \n0 \n");
}

TEST(Darwin, hello_0x1) {
    Darwin darwin(0,1);
    std::ostringstream w;
    w << darwin;
    //std::cout << w.str() << std::endl;
    ASSERT_TRUE(w.str() == "Turn = 0.\n  0\n");
}

TEST(Species, species_null_type) {
    Species null;
    std::ostringstream w;
    w << null;
    ASSERT_TRUE(w.str() == " ");
}

TEST(Species, species_test_type) {
    std::string prog("");
    Species best('b', prog);
    std::ostringstream w;
    w << best;
    ASSERT_TRUE(w.str() == "b");
}

TEST(Species, species_test_program) {
    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    std::string prog("left\ngo 0");
    Species food('f', prog);
    std::ostringstream w;
    w << food;
    ASSERT_TRUE(w.str() == "f");
}

TEST(Species, species_program_invalid_arg) {
    
    /*
     0: win
     1: go 0
    */
    std::string prog("win 1\ngo 0");
    try {
        Species fail('f', prog);
        ASSERT_TRUE(false);
    } catch (const std::invalid_argument& e) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Species, species_program_out_of_range1) {
    
    /*
     0: left
     1: go 2
    */
    std::string prog("left\ngo 2");
    try {
        Species food('f', prog);
        ASSERT_TRUE(false);
    } catch (const std::out_of_range& e) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Species, species_program_out_of_range2) {
    
    /*
     0: left
     1: go -1
    */
    std::string prog("left\ngo -1");
    try {
        Species food('f', prog);
        ASSERT_TRUE(false);
    } catch (const std::out_of_range& e) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, add_creature) {
    
    /*
     0: left
     1: go -1
    */
    try {
        Darwin darwin(4, 4);
        std::string prog("left\ngo 0");
        Species food('f', prog);
        darwin.addCreature(food, 3, 3, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  0123\n"
                                "0 ....\n"
                                "1 ....\n"
                                "2 ....\n"
                                "3 ...f\n");
    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, add_creature_multiple) {
    
    /*
     0: left
     1: go -1
    */
    try {
        Darwin darwin(3, 3);
        std::string prog("left\ngo 0");
        Species food('f', prog);
        darwin.addCreature(food, 0, 0, north);
        darwin.addCreature(food, 0, 2, north);
        darwin.addCreature(food, 1, 1, north);
        darwin.addCreature(food, 2, 0, north);
        darwin.addCreature(food, 2, 2, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  012\n"
                                "0 f.f\n"
                                "1 .f.\n"
                                "2 f.f\n");
    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, add_creature_invalid_argument_row) {
    
    try {
        Darwin darwin(2, 2);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 1, 1, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  01\n"
                                "0 ..\n"
                                "1 .n\n");
        darwin.addCreature(noop, 2, 1, south);
        ASSERT_TRUE(false);
    } catch (const std::invalid_argument& ia) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_invalid_argument_col) {
    
    try {
        Darwin darwin(2, 2);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 1, 1, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  01\n"
                                "0 ..\n"
                                "1 .n\n");
        darwin.addCreature(noop, 1, -1, south);
        ASSERT_TRUE(false);
    } catch (const std::invalid_argument& ia) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_overflow1) {
    
    try {
        Darwin darwin(1, 1);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 0, 0, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  0\n"
                                "0 n\n");
        darwin.addCreature(noop, 0, 0, north);
        ASSERT_TRUE(false);
    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_overflow2) {
    
    try {
        Darwin darwin(1, 1);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 0, 0, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  0\n"
                                "0 n\n");
        darwin.addCreature(noop);
        ASSERT_TRUE(false);
    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_overflow3) {
    
    try {
        Darwin darwin(1, 1);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 0, 0, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  0\n"
                                "0 n\n");
        darwin.addCreature(noop, north);
        ASSERT_TRUE(false);
    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_collision_out_of_range) {
    
    try {
        Darwin darwin(2, 2);
        std::string prog("");
        Species noop('n', prog);
        darwin.addCreature(noop, 1, 1, north);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                                "  01\n"
                                "0 ..\n"
                                "1 .n\n");
        darwin.addCreature(noop, 1, 1, south);
        ASSERT_TRUE(false);
    } catch (const std::out_of_range& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_rand) {
    
    try {
        Darwin darwin(5, 3);
        std::string prog("");
        Species food('f', prog);
        Species trap('t', prog);
        Species rover('r', prog);
        darwin.addCreature(food);
        darwin.addCreature(trap);
        darwin.addCreature(rover);
        std::ostringstream w;
        w << darwin;
        // std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "Turn = 0.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 ...\n"
                            "2 ..r\n"
                            "3 ...\n"
                            "4 tf.\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, add_creature_empty_world) {
    Darwin darwin;
    Species food('n', std::string(""));
    try {
        darwin.addCreature(food);
        ASSERT_TRUE(false);

    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}


TEST(Darwin, add_creature_1x0) {
    Darwin darwin(1,0);
    Species food('n', std::string(""));
    
    try {
        darwin.addCreature(food);
        ASSERT_TRUE(false);

    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, add_creature_0x1) {
    Darwin darwin(0,1);
    Species food('n', std::string(""));
    try {
        darwin.addCreature(food);
        ASSERT_TRUE(false);

    } catch (const std::overflow_error& ov) {
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, turn_left_west) {
    
    try {
        Darwin darwin(3, 3);
        Species trap('t', std::string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));
        Species hopper('h', std::string("hop\ngo 0"));

        darwin.addCreature(trap, 1, 1, west);
        darwin.addCreature(hopper, 2, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .t.\n"
                            "2 .h.\n");
        darwin.takeTurn(2);
        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 2.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .t.\n"
                            "2 .t.\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, turn_right_south) {
    
    try {
        Darwin darwin(3, 3);
        Species trap('t', std::string("if_enemy 3\nright\ngo 0\ninfect\ngo 0"));
        Species hopper('h', std::string("hop\ngo 0"));
        darwin.addCreature(trap, 1, 1, east);
        darwin.addCreature(hopper, 2, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .t.\n"
                            "2 .h.\n");
        darwin.takeTurn(2);
        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 2.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .t.\n"
                            "2 .t.\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, go) {
    
    try {
        Darwin darwin(3, 3);
        std::string prog("left\ngo 0");
        Species food('f', prog);
        darwin.addCreature(food, 1, 1, west);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .f.\n"
                            "2 ...\n");
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 2.\n"
                            "  012\n"
                            "0 ...\n"
                            "1 .f.\n"
                            "2 ...\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, hop_east) {
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
    try {
        Darwin darwin(3, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 1, 1, east);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .h..\n"
                            "2 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 2.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ...h\n"
                            "2 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, hop_east2) {
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
    try {
        Darwin darwin(3, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 1, 1, east);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .h..\n"
                            "2 ....\n");
        for (int i=0; i < 10; i++) {
            darwin.takeTurn();    
        }
        
        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 10.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ...h\n"
                            "2 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }   
}

TEST(Darwin, hop_south) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 0, 0, south);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 h...\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 h...\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, hop_north) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 .h..\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 .h..\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, hop_west) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 2, 3, west);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ...h\n"
                            "3 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 h...\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, two_hoppers) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("hop\ngo 0");
        Species hopper('h', prog);
        // hopper.addInstruction(hop,1);
        // hopper.addInstruction(go,0);
        darwin.addCreature(hopper, 2, 3, west);
        darwin.addCreature(hopper, 1, 0, east);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 h...\n"
                            "2 ...h\n"
                            "3 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ...h\n"
                            "2 h...\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, empty_hop_east) {
    // ------
    // hopper
    // ------

    /*
     0: if_empty 3
     1: left
     2: go 0
     3: hop
     4: go 0
    */
    try {
        Darwin darwin(3, 4);
        std::string prog("if_empty 3\nleft\ngo 0\nhop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 1, 1, east);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .h..\n"
                            "2 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 2.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ...h\n"
                            "2 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, empty_hop_west) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("if_empty 3\nleft\ngo 0\nhop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 2, 3, west);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ...h\n"
                            "3 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 h...\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, empty_hop_south) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("if_empty 3\nleft\ngo 0\nhop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 0, 0, south);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 h...\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 h...\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
    
}

TEST(Darwin, empty_hop_north) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("if_empty 3\nleft\ngo 0\nhop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 .h..\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 .h..\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, not_empty) {
        
    try {
        Darwin darwin(4, 4);
        std::string prog("if_empty 3\nleft\ngo 0\nhop\ngo 0");
        Species hopper('h', prog);
        darwin.addCreature(hopper, 3, 1, north);
        std::string prog2("left\ngo 0");
        Species food('f', prog2);
        darwin.addCreature(food, 2, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 .f..\n"
                            "3 .h..\n");
        darwin.takeTurn();
        darwin.takeTurn();
        darwin.takeTurn();

        std::ostringstream t2;
        t2 << darwin;
        // std::cout << t2.str() << std::endl;
        ASSERT_TRUE(t2.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 .f..\n"
                            "3 h...\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Darwin, if_wall_and_left) {
    
    /*
     0: if_wall 3
     1: hop
     2: go 0
     3: left
     4: go 0
    */
    
    try {
        Darwin darwin(4, 4);
        std::string prog("if_wall 3\nhop\ngo 0\nleft\ngo 0");
        Species left('l', prog);
        darwin.addCreature(left, 0, 0, west);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 l...\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");
        
        int i = 0;
        for (i=0; i < 4; i++) {
            darwin.takeTurn();    
        }
        
        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 4.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 l...\n");

        for (i=0; i < 4; i++) {
            darwin.takeTurn();    
        }
        
        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 8.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ...l\n");

        for (i=0; i < 4; i++) {
            darwin.takeTurn();    
        }
        
        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 12.\n"
                            "  0123\n"
                            "0 ...l\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");

        for (i=0; i < 4; i++) {
            darwin.takeTurn();    
        }
        
        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 16.\n"
                            "  0123\n"
                            "0 l...\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 ....\n");

    } catch (...) {
        ASSERT_TRUE(false);
    }   
}

TEST(Darwin, if_enemy_false) {
        
    // try {
        Darwin darwin(4, 4);
        // Species food('f', std::string("left\ngo 0"));
        // Species hopper('h', std::string("hop\ngo 0");
        Species left('l', std::string("if_enemy 3\nhop\ngo 0\nleft\ngo 0"));
        darwin.addCreature(left, 0, 1, south);
        darwin.addCreature(left, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 .l..\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 .l..\n");

        for (int i=0; i < 3; i++) {
            darwin.takeTurn();
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .l..\n"
                            "2 .l..\n"
                            "3 ....\n");

   
}

TEST(Darwin, if_enemy_true) {
        
    // try {
        Darwin darwin(4, 4);
        // Species food('f', std::string("left\ngo 0"));
        Species hopper('h', std::string("hop\ngo 0"));
        Species left('l', std::string("if_enemy 3\nhop\ngo 0\nleft\ngo 0"));
        darwin.addCreature(hopper, 0, 1, south);
        darwin.addCreature(left, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 .h..\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 .l..\n");

        for (int i=0; i < 3; i++) {
            darwin.takeTurn();
            // std::cout << darwin << std::endl;    
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 3.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .h..\n"
                            "2 l...\n"
                            "3 ....\n");

   
}

TEST(Darwin, if_random) {
        
    // try {
        Darwin darwin(4, 4);
        // Species food('f', std::string("left\ngo 0"));
        // Species hopper('h', std::string("hop\ngo 0");
        Species left('l', std::string("if_random 3\nhop\ngo 0\nleft\nhop\ngo 0"));
        darwin.addCreature(left, 0, 1, south);
        darwin.addCreature(left, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 .l..\n"
                            "1 ....\n"
                            "2 ....\n"
                            "3 .l..\n");

        for (int i=0; i < 4; i++) {
            darwin.takeTurn();
            // std::cout << darwin;
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 4.\n"
                            "  0123\n"
                            "0 ..l.\n"
                            "1 ....\n"
                            "2 l...\n"
                            "3 ....\n");

   
}

TEST(Darwin, infect) {
        
    // try {
        Darwin darwin(4, 4);
        Species trap('t', std::string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));
        Species hopper('h', std::string("hop\ngo 0"));
        darwin.addCreature(trap, 1, 1, west);
        darwin.addCreature(hopper, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .t..\n"
                            "2 ....\n"
                            "3 .h..\n");

        for (int i=0; i < 4; i++) {
            darwin.takeTurn();
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 4.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .t..\n"
                            "2 .t..\n"
                            "3 ....\n");

}

TEST(Darwin, infect2) {
        
    // try {
        Darwin darwin(4, 4);
        Species trap('t', std::string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));
        Species left('l', std::string("if_enemy 3\nhop\ngo 0\nleft\ngo 0"));
        darwin.addCreature(trap, 1, 1, west);
        darwin.addCreature(left, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .t..\n"
                            "2 ....\n"
                            "3 .l..\n");

        for (int i=0; i < 10; i++) {
            darwin.takeTurn();
            // std::cout << darwin;
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 10.\n"
                            "  0123\n"
                            "0 ....\n"
                            "1 .t..\n"
                            "2 .t..\n"
                            "3 ....\n");

}

TEST(Darwin, infect3) {
        
    // try {
        Darwin darwin(4, 4);
        Species trap('t', std::string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));
        Species left('l', std::string("if_enemy 3\nhop\ngo 0\nleft\ngo 0"));
        darwin.addCreature(trap, 1, 1, west);
        darwin.addCreature(trap, 0, 3, north);
        darwin.addCreature(left, 3, 3, north);
        darwin.addCreature(left, 3, 1, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  0123\n"
                            "0 ...t\n"
                            "1 .t..\n"
                            "2 ....\n"
                            "3 .l.l\n");

        for (int i=0; i < 10; i++) {
            darwin.takeTurn();
            // std::cout << darwin;
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 10.\n"
                            "  0123\n"
                            "0 ...t\n"
                            "1 .t.t\n"
                            "2 .t..\n"
                            "3 ....\n");

}

TEST(Darwin, infect_trap_full_360_rotation) {
        
    // try {
        Darwin darwin(5, 5);
        Species trap('t', std::string("if_enemy 3\nleft\ngo 0\ninfect\ngo 0"));
        Species left('l', std::string("if_enemy 3\nhop\ngo 0\nleft\ngo 0"));
        darwin.addCreature(trap, 0, 0, south);
        darwin.addCreature(trap, 0, 2, south);
        darwin.addCreature(trap, 0, 4, south);
        darwin.addCreature(left, 4, 2, north);
        darwin.addCreature(left, 4, 0, north);
        darwin.addCreature(left, 4, 4, north);
        std::ostringstream t1;
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 0.\n"
                            "  01234\n"
                            "0 t.t.t\n"
                            "1 .....\n"
                            "2 .....\n"
                            "3 .....\n"
                            "4 l.l.l\n");

        for (int i=0; i < 10; i++) {
            darwin.takeTurn();
            // std::cout << darwin;
        }

        t1.str(std::string());
        t1.clear();
        t1 << darwin;
        // std::cout << t1.str() << std::endl;
        ASSERT_TRUE(t1.str() == "Turn = 10.\n"
                            "  01234\n"
                            "0 t.t.t\n"
                            "1 t.t.t\n"
                            "2 .....\n"
                            "3 .....\n"
                            "4 .....\n");

}


