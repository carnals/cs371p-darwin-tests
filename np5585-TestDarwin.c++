
#include "gtest/gtest.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstdlib> 
#include <ctime> 

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <iterator> 

#include "Darwin.h"


class DumbTestCell : public Cell
  {
   public:

    Cell*     ahead   (direction) { return NULL; }

    Creature* occupant(void)      { return NULL; }

    Creature* occupant(Creature* c) { 
      return NULL;
    }

    Creature* operator<< (Cell* c) {
      return NULL;
    }

  } dumb_test_cell;


class OccupiedCell : public DumbTestCell
  {
   public:
    Creature* _c;

    OccupiedCell(Creature* c) 
      : _c(c)
    { }

    Creature* occupant(void) { return _c; }
    Creature* occupant(Creature* c) { 
      Creature* old = _c;
      _c = c;
      return old;
    }

    Creature* operator<< (Cell* c) {
      Creature* left = occupant( c->occupant(NULL) );
      assert (left == NULL);
      return left;
    }
  };


class ProxyCell : public OccupiedCell
  {
   public:
    Cell* _cl;

    ProxyCell(Cell& c, Creature* cr = NULL)
      : OccupiedCell(cr)
      , _cl(&c)
    { }

    Cell* ahead(direction) { return _cl; }
  };

Program basic_program() {
  Program p('B');

  p
  .if_wall(3)
  .hop()
  .go(0)
  .left()
  .go(0);
  
  return p;
}

template<int R, int C>
void ASSERT_WRLD(World<R, C>& w, const char* arg, ...) {

  std::ostringstream buf;
  w.print(buf);
  std::stringstream out(buf.str());
  std::string row;
  std::getline(out, row);


  va_list arguments;
  va_start( arguments, arg );

  while (std::getline(out, row))
    {
      ASSERT_EQ(arg, row.substr(2, C));

      arg = va_arg( arguments, const char* );
    }

  va_end ( arguments );
}


/* WORLD */
TEST(World, create_simple) {
  World<100, 100> w;

  ASSERT_NE(w.cell(0, 0), static_cast<Cell*>(NULL));
}

TEST(World, add_fauna) {

  Program f = basic_program();

  Creature c(f, direction::NORTH);

  World<1, 1> w;

  ASSERT_WRLD(w, ".");
  w.enter(&c, 0, 0);
  ASSERT_WRLD(w, "B");
}

TEST(World, fauna_linear_hop_simlation) {

  Creature c(Program('h').hop().go(0), direction::EAST);
  World<1, 3> w;

  w.enter(&c, 0, 0);

  ASSERT_WRLD(w, "h..");
  w.simulate();
  ASSERT_WRLD(w, ".h.");
  w.simulate();
  ASSERT_WRLD(w, "..h");

}

TEST(World, fauna_detect_walls) {

  Creature c(
      Program('h').
        if_wall(3).hop().go(0).right().go(0), 
      direction::EAST
  );
  World<2, 2> w;

  w.enter(&c, 0, 0);

  ASSERT_WRLD(w, 
    "h.",
    "..");
  w.simulate();
  ASSERT_WRLD(w, 
    ".h",
    "..");
  w.simulate();
  ASSERT_WRLD(w, 
    ".h",
    "..");
  w.simulate();
  ASSERT_WRLD(w, 
    "..",
    ".h");
  w.simulate();
  ASSERT_WRLD(w, 
    "..",
    ".h");
  w.simulate();
  ASSERT_WRLD(w, 
    "..",
    "h.");
  w.simulate();
  ASSERT_WRLD(w, 
    "..",
    "h.");
  w.simulate();
  ASSERT_WRLD(w, 
    "h.",
    "..");
  w.simulate();
  ASSERT_WRLD(w, 
    "h.",
    "..");
  w.simulate();
  ASSERT_WRLD(w, 
    ".h",
    "..");
  w.simulate();


}

TEST(World, fauna_infect) {
  Creature c1(Program('I').if_enemy(3).hop().go(0).infect().go(0), 
      direction::EAST);
  Creature c2(Program('T').right(), direction::EAST);
  World<1, 4> w;

  w.enter(&c1, 0, 0);
  w.enter(&c2, 0, 1);

  ASSERT_WRLD(w, "IT..");

  w.simulate();
  // I infects T
  // T hops

  ASSERT_WRLD(w, "I.I.");

  w.simulate();
  // They both hop

  ASSERT_WRLD(w, ".I.I");
}

TEST(World, fauna_collision) {
  World<3, 1> w;

  Creature c1(
      Program('1').hop().hop(), 
      direction::SOUTH
  );
  Creature c2(
      Program('2').hop().hop(), 
      direction::NORTH
  );

  w.enter(&c1, 0, 0);
  w.enter(&c2, 2, 0);

  ASSERT_WRLD(w,
      "1",
      ".",
      "2");

  w.simulate();

  ASSERT_WRLD(w,
      ".",
      "1",
      "2");

  w.simulate();

  ASSERT_WRLD(w,
      ".",
      "1",
      "2");
}

TEST(World, fauna_bounds_limited) {

  World<1, 2> w;

  Creature c(
      Program('h').hop().hop().left().go(0), 
      direction::EAST
  );

  w.enter(&c, 0, 1);

  ASSERT_WRLD(w, ".h");
  w.simulate(); // h
  w.simulate(); // h
  w.simulate(); // NORTH
  ASSERT_WRLD(w, ".h");
  w.simulate(); // h
  w.simulate(); // h
  w.simulate(); // WEST
  ASSERT_WRLD(w, ".h");
  w.simulate(); // h
  ASSERT_WRLD(w, "h.");
  w.simulate(); // h
  ASSERT_WRLD(w, "h.");
  w.simulate(); // SOUTH
  ASSERT_WRLD(w, "h.");
  w.simulate(); // h
  ASSERT_WRLD(w, "h.");
  w.simulate(); // h
  ASSERT_WRLD(w, "h.");
  w.simulate(); // EAST
  ASSERT_WRLD(w, "h.");
  w.simulate(); // h
  ASSERT_WRLD(w, ".h");
}

/* CREATURE STUFF */


TEST(Creature, infect_1_ITW) {
  Program p_one;
  Program p_two;

  p_one.
    if_enemy(3).
    left().
    go(0).
    infect().
    go(0);

  p_two.
    right().
    go(0);

  Creature one(p_one, direction::NORTH);
  Creature two(p_two, direction::NORTH);

  OccupiedCell oc(&two);
  ProxyCell    pc(oc);

  ASSERT_NE(one, two);

  ASSERT_EQ(one.orientation(), direction::NORTH);
  ASSERT_EQ(two.orientation(), direction::NORTH);

  one.act(pc);

  ASSERT_EQ(one, two);

  one.act(pc);
  two.act(pc);

  ASSERT_EQ(one.orientation(), two.orientation());
}

TEST(Creature, infect_1) {
  Program p_one;
  Program p_two;

  p_one.
    left().
    go(0);

  p_two.
    right().
    go(0);

  Creature one(p_one, direction::NORTH);
  Creature two(p_two, direction::NORTH);

  one.act(dumb_test_cell);
  two.act(dumb_test_cell);

  ASSERT_NE(one, two);

  ASSERT_EQ(one.orientation(), direction::WEST);
  ASSERT_EQ(two.orientation(), direction::EAST);

  one = two;

  ASSERT_EQ(one, two);

  two.act(dumb_test_cell);
  two.act(dumb_test_cell);

  ASSERT_EQ(one.orientation(), two.orientation());
}

TEST(Creature, hop_1_ITW) {
  Program h_prog;
  h_prog.
    hop();

  Creature c(h_prog, direction::NORTH);

  OccupiedCell oc(NULL);
  ProxyCell    pc(oc, &c);

  ASSERT_EQ(pc.occupant(), &c);
  ASSERT_EQ(oc.occupant(), static_cast<Creature*>(NULL));
  c.act(pc);
  ASSERT_EQ(pc.occupant(), static_cast<Creature*>(NULL));
  ASSERT_EQ(oc.occupant(), &c);
}

TEST(Creature, random_1_ITW) {
  Program r_prog;
  r_prog.
    if_random(2).
    go(0).
    left();

  Creature c(r_prog, direction::NORTH);

  int tries = 100;
  int succ  = 0, 
      err   = 0;

  srand( time(NULL) );
  while (tries--) {
    c.restart();
    try
    {
      c.act(dumb_test_cell);
      ++ succ;
    }
    catch (InfiniteLoop& e)
    {
      ++ err;
    }
  }

  ASSERT_GT(succ, 0);
  ASSERT_GT(err,  0);
}

TEST(Creature, recognizes_friend_ITW) {
  // Throws infinite exception if enemy not in front
  Program prog, e_prog;
  prog.
    if_enemy(2).
    go(0).
    left().
    go(0);

  e_prog.
    if_enemy(2).
    go(0).
    left().
    go(0).
    go(0);

  Creature frend     (  prog, direction::NORTH);
  Creature test_frend(  prog, direction::SOUTH);
  Creature test_enemy(e_prog, direction::SOUTH);

  OccupiedCell oc(&frend);
  ProxyCell pc(oc);

  // Friend will enter infinite loop (line 0 -> 1 -> 0)
  try
  {
    test_frend.act(pc);
    ASSERT_FALSE(true);
  }
  catch (InfiniteLoop& l)
  { }

  // Enemy will turn left  (line 0 -> 2)
  try
  {
    test_enemy.act(pc);
  }
  catch (InfiniteLoop& l)
  { 
    ASSERT_FALSE(true);
  }
}

TEST(Creature, infinite_creature_2) {
  DumbTestCell tc;
  Program prog;

  prog.
    left().
    left().
    if_wall(7).
    if_empty(5).
    if_empty(5).
    if_empty(5).
    if_empty(5).
    go(2)
  ;

  Creature crtr(prog, direction::NORTH);
  try
  {
    crtr.act(tc);
  }
  catch (InfiniteLoop& e)
  { 
    ASSERT_FALSE(true);
  }

  try
  {
    crtr.act(tc);
  }
  catch (InfiniteLoop& e)
  { 
    ASSERT_FALSE(true);
  }

  try
  {
    crtr.act(tc);
    ASSERT_FALSE(true);
  }
  catch (InfiniteLoop& e)
  { }
}

TEST(Creature, infinite_creature) {
  DumbTestCell tc;
  Program prog;

  prog.go(0);

  Creature crtr(prog, direction::NORTH);
  try
  {
    crtr.act(tc);
    ASSERT_FALSE(true);
  }
  catch (InfiniteLoop& e) 
  { }
}

TEST(Creature, spin_creature) {
  DumbTestCell tc;
  Program prog;

  prog.left().go(0);

  Creature crtr(prog, direction::NORTH);

  ASSERT_EQ(direction::NORTH, crtr.orientation());
  crtr.act(tc);
  ASSERT_EQ(direction::WEST, crtr.orientation());
  crtr.act(tc);
  ASSERT_EQ(direction::SOUTH, crtr.orientation());
  crtr.act(tc);
  ASSERT_EQ(direction::EAST, crtr.orientation());
  crtr.act(tc);
  ASSERT_EQ(direction::NORTH, crtr.orientation());
  crtr.act(tc);
  crtr.act(tc);
  crtr.act(tc);
  crtr.act(tc);
  ASSERT_EQ(direction::NORTH, crtr.orientation());
}

TEST(Creature, can_reset) {
  Program p; 

  // act(); ..; act(); will cause infinite loop if reset doesnt work
  p.left().go(1);

  Creature a(p, direction::NORTH);
  a.act(dumb_test_cell);
  a.restart();
  try
  {
    a.act(dumb_test_cell);
  }
  catch(InfiniteLoop& e)
  {
    ASSERT_FALSE(true);
  }
}

TEST(Creature, self_is_friend) {
  Program p; p.left().go(0);

  Creature a(p, direction::NORTH);
  Creature b = a;

  ASSERT_TRUE (a == b);
  ASSERT_FALSE(a != b);
}

TEST(Creature, detects_friends) {
  Program prog;

  prog.
    left().
    go(0);

  Creature one(prog, direction::NORTH);
  Creature two(prog, direction::SOUTH);

  ASSERT_TRUE (one == two);
  ASSERT_FALSE(one != two);
}

TEST(Creature, detects_enemies) {
  Program p_one;
  Program p_two;

  p_one.
    left().
    go(0);

  p_two.
    right().
    go(0);

  Creature one(p_one, direction::NORTH);
  Creature two(p_two, direction::SOUTH);

  ASSERT_FALSE(one == two);
  ASSERT_TRUE (one != two);
}

/* PROGRAM STUFF */
TEST(Program, in_equality) {
  Program a, b;

  a.
    left().
    go(0);

  b.
    right().
    go(0);
  
  ASSERT_FALSE( a ==  b);
  ASSERT_FALSE(&a == &b);
  ASSERT_TRUE ( a !=  b);
}

TEST(Program, equality) {
  Program a; a.
    left().
    go(0);

  Program b; b.
    left().
    go(0);
  
  ASSERT_TRUE ( a ==  b);
  ASSERT_FALSE(&a == &b);
  ASSERT_FALSE( a !=  b);
}

TEST(Program, real_equality_not_computable) {
  // Gotta solving that halting problem...
  Program a; a.
    left().
    go(0).
    left().
    go(0);

  Program b; b.
    left().
    go(0);
  
  ASSERT_FALSE( a ==  b);
  ASSERT_FALSE(&a == &b);
  ASSERT_TRUE ( a !=  b);
}

TEST(Program, process_install) {
  Program p_1, p_2;

  p_1.
    left().
    go(0);

  p_2.
    right().
    go(0);

  Process proc(p_1);

  LiveInstruction* i;
  
  i = *proc;
  ASSERT_EQ(i->op, Instruction::LEFT);

  ++proc;
  i = *proc;
  ASSERT_EQ(i->op, Instruction::GO);

  proc.install(p_2);
 
  i = *proc;
  ASSERT_EQ(i->op, Instruction::RIGHT);

  ++proc;
  i = *proc;
  ASSERT_EQ(i->op, Instruction::GO);

}

TEST(Program, process_reset) {
  Program p = basic_program();
  Process proc(p);

  LiveInstruction* i;
  
  i = *proc;
  ASSERT_EQ(i->op, Instruction::IF_WALL);

  ++proc;
  i = *proc;
  ASSERT_EQ(i->op, Instruction::HOP);
  proc.reset();

  i = *proc;
  ASSERT_EQ(i->op, Instruction::IF_WALL);
}

TEST(Program, process_creation) {
  Program prog = basic_program();
  Process proc(prog); 

  int x = 0;
  for(LiveInstruction* i : proc) {

    if (x == 9) break;
    switch (x) 
      {
        case 0: 
          ASSERT_EQ(i->op, Instruction::IF_WALL); 
          break;
        case 1: 
          ASSERT_EQ(i->op, Instruction::HOP); 
          break;
        case 2: 
          ASSERT_EQ(i->op, Instruction::GO); 
          break;
        case 3: 
          ASSERT_EQ(i->op, Instruction::IF_WALL); 
          i->branch();
          break;
        case 4: 
          ASSERT_EQ(i->op, Instruction::LEFT); 
          break;
        case 5: 
          ASSERT_EQ(i->op, Instruction::GO); 
          break;
        case 6: 
          ASSERT_EQ(i->op, Instruction::IF_WALL); 
          i->branch();
          break;
        case 7: 
          ASSERT_EQ(i->op, Instruction::LEFT); 
          break;
        case 8: 
          ASSERT_EQ(i->op, Instruction::GO); 
          break;
      }
    ++x;
  }
}

TEST(Program, chaining_ability) {
  Program p;
  Program p2 = p.hop();

  EXPECT_TRUE(1 == p.num_instructions());
  EXPECT_TRUE(p.num_instructions() == p2.num_instructions());
}

TEST(Program, construction) {
  Program p = basic_program();

  EXPECT_TRUE(5 == p.num_instructions());

  EXPECT_TRUE(p[0].op   == Instruction::IF_WALL);
  EXPECT_TRUE(p[0].line == 3);
  EXPECT_TRUE(p[1].op   == Instruction::HOP);
  EXPECT_TRUE(p[2].op   == Instruction::GO);
  EXPECT_TRUE(p[2].line == 0);
  EXPECT_TRUE(p[3].op   == Instruction::LEFT);
  EXPECT_TRUE(p[4].op   == Instruction::GO);
  EXPECT_TRUE(p[4].line == 0);
  EXPECT_TRUE(p[5].op   == Instruction::NOOP);
}


/* DIRECTION STUFF */
TEST(DirectionAndRowcol, d_plus_rowcol_N) {
  rowcol o = rowcol(5, 5) + direction::NORTH;
  EXPECT_EQ(o.row, 4);
  EXPECT_EQ(o.col, 5);
}
TEST(DirectionAndRowcol, d_plus_rowcol_E) {
  rowcol o = rowcol(5, 5) + direction::EAST;
  EXPECT_EQ(o.row, 5);
  EXPECT_EQ(o.col, 6);
}
TEST(DirectionAndRowcol, d_plus_rowcol_S) {
  rowcol o = rowcol(5, 5) + direction::SOUTH;
  EXPECT_EQ(o.row, 6);
  EXPECT_EQ(o.col, 5);
}
TEST(DirectionAndRowcol, d_plus_rowcol_W) {
  rowcol o = rowcol(5, 5) + direction::WEST;
  EXPECT_EQ(o.row, 5);
  EXPECT_EQ(o.col, 4);
}
TEST(DirectionAndRowcol, travel_1) {
  rowcol o = rowcol(5, 5) 
    + direction::WEST 
    + direction::WEST 
    + direction::WEST 
    + direction::WEST 
    + direction::WEST;
  EXPECT_EQ(o.row, 5);
  EXPECT_EQ(o.col, 0);
}
TEST(DirectionAndRowcol, travel_2) {
  rowcol o = rowcol(5, 5) 
    + direction::WEST 
    + direction::NORTH 
    + direction::WEST 
    + direction::NORTH 
    + direction::WEST 
    + direction::WEST 
    + direction::NORTH 
    + direction::NORTH 
    + direction::NORTH 
    + direction::WEST;
  EXPECT_EQ(o.row, 0);
  EXPECT_EQ(o.col, 0);
}

TEST(DirectionAndTurn, turns_right) {
  EXPECT_TRUE(direction::NORTH + turn::RIGHT == direction::EAST);
  EXPECT_TRUE(direction::EAST  + turn::RIGHT == direction::SOUTH);
  EXPECT_TRUE(direction::SOUTH + turn::RIGHT == direction::WEST);
  EXPECT_TRUE(direction::WEST  + turn::RIGHT == direction::NORTH);
}

TEST(DirectionAndTurn, turns_left) {
  EXPECT_TRUE(direction::NORTH + turn::LEFT == direction::WEST);
  EXPECT_TRUE(direction::EAST  + turn::LEFT == direction::NORTH);
  EXPECT_TRUE(direction::SOUTH + turn::LEFT == direction::EAST);
  EXPECT_TRUE(direction::WEST  + turn::LEFT == direction::SOUTH);
}

TEST(DirectionAndTurn, turns_not) {
  EXPECT_TRUE(direction::NORTH + !turn::LEFT == direction::EAST);
  EXPECT_TRUE(direction::NORTH +  turn::LEFT == direction::WEST);
}

TEST(DirectionAndTurn, turn_assignment) {
  direction d = direction::NORTH;
  EXPECT_TRUE(direction::NORTH == d);

  d += turn::LEFT;
  EXPECT_TRUE(direction::WEST == d);

  d += turn::RIGHT;
  d += turn::RIGHT;
  EXPECT_TRUE(direction::EAST == d);
}

TEST(DirectionAndTurn, three_rights_make_a_left) {
  direction o = direction::NORTH;

  EXPECT_TRUE(o + turn::RIGHT + turn::RIGHT + turn::RIGHT == o + turn::LEFT);
}

TEST(DirectionAndTurn, three_lefts_make_a_right) {
  direction o = direction::NORTH;

  EXPECT_TRUE(o + turn::LEFT + turn::LEFT + turn::LEFT == o + turn::RIGHT);
}
