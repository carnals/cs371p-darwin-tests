// --------
// includes
// --------

#include <cstdlib>   // rand, srand
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

// ----
// arena empty_at cases
// ----

TEST(Darwin, arena_empty_at0) {
    Arena a(4, 4);
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(3, 3));
}

TEST(Darwin, arena_empty_at1) {
    Arena a(4, 4);
    Species s('f');
    Creature c(&s, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(3, 3));
}

TEST(Darwin, arena_empty_at2) {
    Arena a(4, 4);
    ASSERT_TRUE(!a.empty_at(-1, 0));
    ASSERT_TRUE(a.empty_at(3, 3));
}

// ----
// arena wall_at cases
// ----

TEST(Darwin, arena_wall_at0) {
    Arena a(4, 4);
    ASSERT_TRUE(a.wall_at(-1, -1));
    ASSERT_TRUE(a.wall_at(4, 4));
}

TEST(Darwin, arena_wall_at1) {
    Arena a(4, 4);
    ASSERT_TRUE(!a.wall_at(0, 0));
    ASSERT_TRUE(!a.wall_at(3, 3));
}

TEST(Darwin, arena_wall_at2) {
    Arena a(4, 4);
    ASSERT_TRUE(a.wall_at(-5, 0));
    ASSERT_TRUE(!a.wall_at(3, 3));
}

// ----
// arena calculateAhead cases
// ----

TEST(Darwin, arena_calculateAhead0) {
    Arena a(4, 4);
    std::vector<int> vec(a.calculateAhead(0, 0, east));
    ASSERT_TRUE(vec[0] == 0);
    ASSERT_TRUE(vec[1] == 1);
}

TEST(Darwin, arena_calculateAhead1) {
    Arena a(4, 4);
    std::vector<int> vec(a.calculateAhead(0, 0, north));
    ASSERT_TRUE(vec[0] == -1);
    ASSERT_TRUE(vec[1] == 0);
}

TEST(Darwin, arena_calculateAhead2) {
    Arena a(4, 4);
    std::vector<int> vec(a.calculateAhead(0, 0, west));
    ASSERT_TRUE(vec[0] == 0);
    ASSERT_TRUE(vec[1] == -1);
}

// ----
// arena move cases
// ----

TEST(Darwin, arena_move0) {
    Arena a(4, 4);
    Species s('f');
    Creature c(&s, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(3, 3));

    a.move(&c, 0, 0, 1, 1);
    ASSERT_TRUE(!a.empty_at(1, 1));
}

TEST(Darwin, arena_move1) {
    Arena a(4, 4);
    Species s('h');
    Creature c(&s, north);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(3, 3));

    a.move(&c, 0, 0, 3, 3);
    ASSERT_TRUE(a.empty_at(1, 1));
    ASSERT_TRUE(!a.empty_at(3, 3));
}

// ----
// arena enemy_at cases
// ----

TEST(Darwin, arena_enemy_at0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Species st('t');
    Creature c1(&st, north);
    a.insert(0, 1, &c1);
    ASSERT_TRUE(!a.empty_at(0, 1));

    ASSERT_TRUE(a.enemy_at(&sh, 0, 1) != NULL);
}

TEST(Darwin, arena_enemy_at1) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Species st('h');
    Creature c1(&st, north);
    a.insert(0, 1, &c1);
    ASSERT_TRUE(!a.empty_at(0, 1));

    ASSERT_TRUE(!(a.enemy_at(&sh, 0, 1) != NULL));
}

TEST(Darwin, arena_enemy_at2) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    ASSERT_TRUE(!(a.enemy_at(&sh, 0, 1) != NULL));
}

// ----
// arena insert cases
// ----

TEST(Darwin, arena_insert0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));
}

TEST(Darwin, arena_insert1) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Creature c1(&sh, east);
    a.insert(1, 1, &c1);
    ASSERT_TRUE(!a.empty_at(1, 1));
}

// ----
// arena simulate_turns cases
// ----

TEST(Darwin, arena_simulate_turns0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    a.simulate_turns(0);
    ASSERT_TRUE(!a.empty_at(0, 0));
}

TEST(Darwin, arena_simulate_turns1) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    a.simulate_turns(1);
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

TEST(Darwin, arena_simulate_turns2) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Species f('f');
    Creature c1(&f, north);
    a.insert(3, 3, &c1);
    ASSERT_TRUE(!a.empty_at(3, 3));

    a.simulate_turns(1);
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
    ASSERT_TRUE(!a.empty_at(3, 3));
}

// ----
// creature get_dir cases
// ----

TEST(Darwin, creature_get_dir0) {
    Species sh('h');
    Creature c(&sh, east);
    ASSERT_TRUE(c.get_dir() == east);
}

TEST(Darwin, creature_get_dir1) {
    Species sh('f');
    Creature c(&sh, north);
    ASSERT_TRUE(c.get_dir() == north);
}

// ----
// creature is_ememy cases
// ----

TEST(Darwin, creature_is_enemy0) {
    Species sh('f');
    Creature c(&sh, north);
    ASSERT_TRUE(!c.is_enemy('f'));
}

TEST(Darwin, creature_is_enemy1) {
    Species sh('t');
    Creature c(&sh, north);
    ASSERT_TRUE(c.is_enemy('f'));
}

TEST(Darwin, creature_is_enemy2) {
    try {
        Species sh('z');
        Creature c(&sh, north);
        ASSERT_TRUE(c.is_enemy('f'));
    } catch (const invalid_argument& e) {
        ASSERT_TRUE(true);
    }
}

// ----
// creature left cases
// ----

TEST(Darwin, creature_left0) {
    Species sh('f');
    Creature c(&sh, north);
    c.left();
    ASSERT_TRUE(c.get_dir() == west);
}

TEST(Darwin, creature_left1) {
    Species sh('f');
    Creature c(&sh, east);
    c.left();
    ASSERT_TRUE(c.get_dir() == north);
}

// ----
// creature right cases
// ----

TEST(Darwin, creature_right0) {
    Species sh('f');
    Creature c(&sh, north);
    c.right();
    ASSERT_TRUE(c.get_dir() == east);
}

TEST(Darwin, creature_right1) {
    Species sh('f');
    Creature c(&sh, east);
    c.right();
    ASSERT_TRUE(c.get_dir() == south);
}

// ----
// creature hop cases
// ----

TEST(Darwin, creature_hop0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    c.hop(&a, 0, 0);
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

TEST(Darwin, creature_hop1) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, north);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    c.hop(&a, 0, 0);
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(0, 1));
}

TEST(Darwin, creature_hop2) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Creature c1(&sh, west);
    a.insert(0, 1, &c1);
    ASSERT_TRUE(!a.empty_at(0, 1));

    c.hop(&a, 0, 0);
    c1.hop(&a, 0, 1);
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

// ----
// creature takeTurn cases
// ----

TEST(Darwin, creature_takeTurn0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    c.takeTurn(&a, 0, 0, 0);
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

TEST(Darwin, creature_takeTurn1) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Species f('f');
    Creature c1(&f, north);
    a.insert(0, 1, &c1);
    ASSERT_TRUE(!a.empty_at(0, 1));

    c.takeTurn(&a, 0, 0, 0);
    c1.takeTurn(&a, 0, 1, 0);

    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

TEST(Darwin, creature_takeTurn2) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, south);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    Species f('h');
    Creature c1(&f, north);
    a.insert(0, 1, &c1);
    ASSERT_TRUE(!a.empty_at(0, 1));

    c.takeTurn(&a, 0, 0, 0);
    c1.takeTurn(&a, 0, 1, 0);

    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
    ASSERT_TRUE(!a.empty_at(1, 0));
}

// ----
// species is_enemy cases
// ----

TEST(Darwin, species_is_enemy0) {
    Species s('f');
    ASSERT_TRUE(s.is_enemy('h'));
}

TEST(Darwin, species_is_enemy1) {
    Species s('f');
    ASSERT_TRUE(!s.is_enemy('f'));
}

// ----
// species get_id cases
// ----

TEST(Darwin, species_get_id0) {
    Species s('f');
    ASSERT_TRUE(s.get_id() == 'f');
}

TEST(Darwin, species_get_id1) {
    try {
        Species s('z');
        ASSERT_TRUE(s.get_id() == 'z');
    } catch (const invalid_argument& e) {
        ASSERT_TRUE(true);
    }
}

// ----
// species runProgram cases
// ----

TEST(Darwin, species_runProgram0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.runProgram(&a, &c, 0, 0, &pc);
    
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

TEST(Darwin, species_runProgram1) {
    Arena a(4, 4);
    Species sh('f');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.runProgram(&a, &c, 0, 0, &pc);
    
    ASSERT_TRUE(!a.empty_at(0, 0));
}

// ----
// species foodProgram cases
// ----

TEST(Darwin, species_foodProgram0) {
    Arena a(4, 4);
    Species sh('f');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.foodProgram(&c, &pc);
    
    ASSERT_TRUE(!a.empty_at(0, 0));
}

// ----
// species hopperProgram cases
// ----

TEST(Darwin, species_hopperProgram0) {
    Arena a(4, 4);
    Species sh('h');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.hopperProgram(&a, &c, &pc, 0, 0);
    
    ASSERT_TRUE(a.empty_at(0, 0));
    ASSERT_TRUE(!a.empty_at(0, 1));
}

// ----
// species trapProgram cases
// ----

TEST(Darwin, species_trapProgram0) {
    Arena a(4, 4);
    Species sh('t');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.trapProgram(&a, &c, &pc, 0, 0);
    
    ASSERT_TRUE(!a.empty_at(0, 0));
}

// ----
// species roverProgram cases
// ----

TEST(Darwin, species_roverProgram0) {
    srand(0);
    Arena a(4, 4);
    Species sh('r');
    Creature c(&sh, east);
    a.insert(0, 0, &c);
    ASSERT_TRUE(!a.empty_at(0, 0));

    int pc = 0;
    sh.trapProgram(&a, &c, &pc, 0, 0);
    
    ASSERT_TRUE(!a.empty_at(0, 0));
    ASSERT_TRUE(a.empty_at(0, 1));
}
