#include <stdexcept>  // out_of_range
#include <sstream>    // ostringstream
#include <string>     // string

#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

#define NP UINT_MAX

template <typename T>
std::vector<T*> to_ptrs(std::vector<T>& ts) {
    std::vector<T*> ptrs;
    for (auto& t : ts) {
        ptrs.push_back(&t);
    }
    return ptrs;
}

TEST(move, 1) {
	Position p(1, 2);
	Direction d = WEST;
	move(p, d);
	ASSERT_TRUE(p.first == 1);
	ASSERT_TRUE(p.second == 1);
}

TEST(move, 2) {
	Position p(1, 2);
	Direction d = EAST;
	move(p, d);
	ASSERT_TRUE(p.first == 1);
	ASSERT_TRUE(p.second == 3);
}

TEST(move, 3) {
	Position p(1, 2);
	Direction d = NORTH;
	move(p, d);
	ASSERT_TRUE(p.first == 0);
	ASSERT_TRUE(p.second == 2);
}

TEST(move, 4) {
	Position p(1, 2);
	Direction d = SOUTH;
	move(p, d);
	ASSERT_TRUE(p.first == 2);
	ASSERT_TRUE(p.second == 2);
}

TEST(printTurn, 1) {
	Board b(5, 5, vector<Creature*>());
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  01234\n") +
		"0 .....\n"  +
		"1 .....\n"  +
		"2 .....\n"  +
		"3 .....\n"  +
		"4 .....\n\n");
}

TEST(printTurn, 2) {
	Board b(11, 11, vector<Creature*>());
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  01234567890\n") +
		"0 ...........\n"  +
		"1 ...........\n"  +
		"2 ...........\n"  +
		"3 ...........\n"  +
		"4 ...........\n"  +
		"5 ...........\n"  +
		"6 ...........\n"  +
		"7 ...........\n"  +
		"8 ...........\n"  +
		"9 ...........\n"  +
		"0 ...........\n\n");
}

TEST(printTurn, 3) {
	vector<Instruction*> i;
	Species s(i, 'x');
	vector<Creature*> c;
	Creature x(&s, NORTH, Position(0, 0));
	Creature y(&s, NORTH, Position(1, 2));
	c.push_back(&x);
	c.push_back(&y);
	Board b(3, 3, c);
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  012\n") +
		"0 x..\n"  +
		"1 ..x\n"  +
		"2 ...\n\n");
}

TEST(printTurn, 4) {
	vector<Instruction*> i;
	Species sx(i, 'x');
	Species so(i, 'o');
	vector<Creature*> c;
	Creature x(&sx, NORTH, Position(0, 0));
	Creature o(&so, NORTH, Position(0, 2));
	c.push_back(&o);
	c.push_back(&x);
	Board b(3, 3, c);
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  012\n") +
		"0 x.o\n"  +
		"1 ...\n"  +
		"2 ...\n\n");
}

TEST(printTurn, 5) {
	vector<Instruction*> i;
	Species sx(i, 'x');
	Species so(i, 'o');
	Species sf(i, 'f');
	vector<Creature*> c;
	Creature x(&sx, NORTH, Position(0, 0));
	Creature o(&so, NORTH, Position(0, 2));
	Creature f(&sf, NORTH, Position(1, 1));
	c.push_back(&f);
	c.push_back(&o);
	c.push_back(&x);
	Board b(3, 3, c);
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  012\n") +
		"0 x.o\n"  +
		"1 .f.\n"  +
		"2 ...\n\n");
}

TEST(printTurn, 6) {
	vector<Instruction*> i;
	Species sx(i, 'x');
	Species so(i, 'o');
	vector<Creature*> c;
	Creature x0(&sx, NORTH, Position(0, 0));
	Creature x1(&sx, NORTH, Position(0, 1));
	Creature x2(&sx, NORTH, Position(1, 1));
	Creature x3(&sx, NORTH, Position(2, 1));
	Creature o0(&so, NORTH, Position(0, 2));
	Creature o1(&so, NORTH, Position(1, 0));
	Creature o2(&so, NORTH, Position(2, 2));
	c.push_back(&x0);
	c.push_back(&x1);
	c.push_back(&x2);
	c.push_back(&x3);
	c.push_back(&o0);
	c.push_back(&o1);
	c.push_back(&o2);
	Board b(3, 3, c);
	ostringstream ss;
	b.printTurn(ss);
	ASSERT_TRUE(ss.str() == string(
		"  012\n") +
		"0 xxo\n"  +
		"1 ox.\n"  +
		"2 .xo\n\n");
}

TEST(isWall, 1) {
	Board b(5, 5, vector<Creature*>());
	ASSERT_TRUE(b.isWall(Position(0, 0), WEST));
	ASSERT_TRUE(!b.isWall(Position(0, 0), SOUTH));
}

TEST(isWall, 2) {
	Board b(5, 5, vector<Creature*>());
	ASSERT_TRUE(!b.isWall(Position(1, 1), SOUTH));
	ASSERT_TRUE(!b.isWall(Position(1, 1), NORTH));
}

TEST(isWall, 3) {
	Board b(6, 6, vector<Creature*>());
	ASSERT_TRUE(!b.isWall(Position(3, 3), NORTH));
	ASSERT_TRUE(!b.isWall(Position(3, 3), WEST));
}

TEST(isWall, 4) {
	Board b(6, 6, vector<Creature*>());
	bool failed = false;
	try {
		b.isWall(Position(6, 6), SOUTH);
	}
	catch (const out_of_range& e) {
		failed = true;
	}
	ASSERT_TRUE(failed);
}

TEST(isWall, 5) {
	Board b(100, 100, vector<Creature*>());
	ASSERT_TRUE(!b.isWall(Position(99, 99), NORTH));
	ASSERT_TRUE(b.isWall(Position(99, 99), EAST));
}

TEST(getNextSpace, 1) {
	vector<Instruction*> i;
	Species s(i, 'x');
	vector<Creature*> c;
	Creature x(&s, NORTH, Position(0, 0));
	c.push_back(&x);
	Board b(5, 5, c);
	ASSERT_TRUE(b.getNextSpace(Position(1, 0), NORTH));
	ASSERT_TRUE(!b.getNextSpace(Position(1, 0), SOUTH));
}

TEST(getNextSpace, 2) {
	vector<Instruction*> i;
	Species s(i, 'x');
	vector<Creature*> c;
	Creature x(&s, NORTH, Position(4, 4));
	c.push_back(&x);
	Board b(5, 5, c);
	ASSERT_TRUE(b.getNextSpace(Position(3, 4), SOUTH));
	ASSERT_TRUE(!b.getNextSpace(Position(3, 4), NORTH));
}

TEST(getNextSpace, 3) {
	vector<Instruction*> i;
	Species s(i, 'x');
	vector<Creature*> c;
	Creature x(&s, NORTH, Position(3, 3));
	c.push_back(&x);
	Board b(5, 5, c);
	ASSERT_TRUE(b.getNextSpace(Position(2, 3), SOUTH));
	ASSERT_TRUE(b.getNextSpace(Position(4, 3), NORTH));
}

TEST(getNextSpace, 4) {
	Board b(5, 5, vector<Creature*>());
	bool failed = false;
	try {
		b.getNextSpace(Position(5, 2), SOUTH);
	}
	catch (const out_of_range& e) {
		failed = true;
	}
	ASSERT_TRUE(failed);
}

TEST(lessThan, 1) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(0, 0));
	Creature y(&s, NORTH, Position(1, 1));
	ASSERT_TRUE(x < y);
}

TEST(lessThan, 2) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(0, 0));
	Creature y(&s, NORTH, Position(0, 1));
	ASSERT_TRUE(x < y);
}

TEST(lessThan, 3) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&s, NORTH, Position(0, 1));
	ASSERT_TRUE(y < x);
}

TEST(printSpecies, 1) {
	vector<Instruction*> instructions;
	Species s(instructions, 'x');
	Creature c(&s, NORTH, Position(0, 0));
	ostringstream ss;
        c.printSpecies(ss);
	ASSERT_TRUE(ss.str() == "x");
}

TEST(isSameSpecies, 1) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&s, SOUTH, Position(0, 0));
	ASSERT_TRUE(x.isSameSpecies(y));
}

TEST(isSameSpecies, 2) {
	vector<Instruction*> i;
	Species s(i, 's');
	Species t(i, 't');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&t, SOUTH, Position(0, 0));
	ASSERT_TRUE(!x.isSameSpecies(y));
}

TEST(isSameSpecies, 3) {
	vector<Instruction*> i;
	Species s(i, 's');
	Species t(i, 't');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&t, SOUTH, Position(0, 0));
	Creature z(&t, NORTH, Position(0, 1));
	ASSERT_TRUE(!x.isSameSpecies(y));
	ASSERT_TRUE(y.isSameSpecies(z));
}

TEST(infect, 1) {
	vector<Instruction*> i;
	Species s(i, 's');
	Species t(i, 't');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&t, SOUTH, Position(0, 0));
	x.infect(y);
	ASSERT_TRUE(x.isSameSpecies(y));
}

TEST(infect, 2) {
	vector<Instruction*> i;
	Species s(i, 's');
	Species t(i, 't');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&t, SOUTH, Position(0, 0));
	Creature z(&t, SOUTH, Position(1, 1));
	x.infect(y);
	y.infect(z);
	ASSERT_TRUE(x.isSameSpecies(y));
	ASSERT_TRUE(y.isSameSpecies(z));
	ASSERT_TRUE(x.isSameSpecies(z));
}

TEST(infect, 3) {
	vector<Instruction*> i;
	Species s(i, 's');
	Species t(i, 't');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&t, SOUTH, Position(0, 0));
	Creature z(&t, SOUTH, Position(1, 1));
	x.infect(y);
	z.infect(x);
	ASSERT_TRUE(!x.isSameSpecies(y));
	ASSERT_TRUE(!y.isSameSpecies(z));
	ASSERT_TRUE(x.isSameSpecies(z));
}

TEST(takeTurn, 1) {
	vector<Instruction> food_program = { {TURN_WEST, NP}, {GO, 0} };
	Species food(to_ptrs(food_program), 'f');

	vector<Creature*> c;
	Creature f(&food, NORTH, Position(0, 0));
	c.push_back(&f);
	Board b(1, 1, c);
	f.takeTurn(b);
	ASSERT_TRUE(f.positionAt(Position(0, 0)));
}

TEST(takeTurn, 2) {
	vector<Instruction> hopper_program = {{HOP},{GO, 0}};
	Species hopper(to_ptrs(hopper_program), 'h');

	vector<Creature*> c;
	Creature h(&hopper, NORTH, Position(0, 0));
	c.push_back(&h);
	Board b(2, 2, c);
	h.takeTurn(b);
	ASSERT_TRUE(h.positionAt(Position(0, 0)));
}

TEST(takeTurn, 3) {
	vector<Instruction> hopper_program = {{HOP},{GO, 0}};
	Species hopper(to_ptrs(hopper_program), 'h');

	vector<Creature*> c;
	Creature h(&hopper, SOUTH, Position(0, 0));
	c.push_back(&h);
	Board b(2, 2, c);
	h.takeTurn(b);
	ASSERT_TRUE(h.positionAt(Position(1, 0)));
}

TEST(takeTurn, 4) {
	vector<Instruction> hopper_program = {{HOP},{GO, 0}};
	Species hopper(to_ptrs(hopper_program), 'h');

	vector<Creature*> c;
	Creature h1(&hopper, SOUTH, Position(0, 0));
	Creature h2(&hopper, SOUTH, Position(1, 0));
	c.push_back(&h1);
	c.push_back(&h2);
	Board b(2, 2, c);
	h1.takeTurn(b);
	ASSERT_TRUE(h1.positionAt(Position(0, 0)));
}

TEST(positionAt, 1) {
	vector<Instruction*> i;
	Species s(i, 's');
	Creature x(&s, NORTH, Position(1, 0));
	ASSERT_TRUE(x.positionAt(Position(1, 0)));
	ASSERT_TRUE(!x.positionAt(Position(0, 1)));
}

TEST(positionAt, 2) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(1, 0));
	Creature y(&s, SOUTH, Position(0, 0));
	ASSERT_TRUE(x.positionAt(Position(1, 0)));
	ASSERT_TRUE(!x.positionAt(Position(0, 0)));
	ASSERT_TRUE(y.positionAt(Position(0, 0)));
	ASSERT_TRUE(!y.positionAt(Position(1, 0)));
}

TEST(positionAt, 3) {
	vector<Instruction*> i;
	Species s(i, 'x');
	Creature x(&s, NORTH, Position(0, 0));
	Creature y(&s, SOUTH, Position(1, 1));
	ASSERT_TRUE(x.positionAt(Position(0, 0)));
	ASSERT_TRUE(!x.positionAt(Position(2, 0)));
	ASSERT_TRUE(y.positionAt(Position(1, 1)));
	ASSERT_TRUE(!y.positionAt(Position(2, 0)));
}

TEST(getInstruction, 1) {
	vector<Instruction*> i;
	Species s(i, 'x');
	bool failed = false;
	try {
		s.getInstruction(0);
	}
	catch (const out_of_range& e) {
		failed = true;
	}
	ASSERT_TRUE(failed);
}

TEST(getInstruction, 2) {
	vector<Instruction*> instructions;
	Instruction i(TURN_WEST);
        instructions.push_back(&i);
	Species s(instructions, 'x');
	Instruction i2 = s.getInstruction(0);
	ASSERT_TRUE(i.i_type == i2.i_type);
	ASSERT_TRUE(i.param == i2.param);
}

TEST(printId, 1) {
	vector<Instruction*> instructions;
	Species s(instructions, 'x');
	ostringstream ss;
        s.printId(ss);
	ASSERT_TRUE(ss.str() == "x");
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
