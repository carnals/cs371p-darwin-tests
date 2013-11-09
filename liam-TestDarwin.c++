#include "Darwin.h"
#include <stdexcept>

using namespace std;

#include "gtest/gtest.h"

TEST(Instruction, HOP) {
	ASSERT_TRUE(Instruction(Instruction::HOP).isAction());
	try {
		Instruction(Instruction::HOP, 1);
		ASSERT_TRUE(false);
	} catch (const invalid_argument& expected) {
	}
}

TEST(Instruction, LEFT) {
	ASSERT_TRUE(Instruction(Instruction::LEFT).isAction());
	try {
		Instruction(Instruction::LEFT, 1);
		ASSERT_TRUE(false);
	} catch (const invalid_argument& expected) {
	}
}

TEST(Instruction, RIGHT) {
	ASSERT_TRUE(Instruction(Instruction::RIGHT).isAction());
	try {
		Instruction(Instruction::RIGHT, 1);
		ASSERT_TRUE(false);
	} catch (const invalid_argument& expected) {
	}
}

TEST(Instruction, INFECT) {
	ASSERT_TRUE(Instruction(Instruction::INFECT).isAction());
	try {
		Instruction(Instruction::INFECT, 1);
		ASSERT_TRUE(false);
	} catch (const invalid_argument& expected) {
	}
}

TEST(Instruction, IF_EMPTY) {
	ASSERT_FALSE(Instruction(Instruction::IF_EMPTY, 0).isAction());
}

TEST(Instruction, IF_WALL) {
	ASSERT_FALSE(Instruction(Instruction::IF_WALL, 0).isAction());
}

TEST(Instruction, IF_RANDOM) {
	ASSERT_FALSE(Instruction(Instruction::IF_RANDOM, 0).isAction());
}

TEST(Instruction, IF_ENEMY) {
	ASSERT_FALSE(Instruction(Instruction::IF_ENEMY, 0).isAction());
}

TEST(Instruction, GO) {
	ASSERT_FALSE(Instruction(Instruction::GO, 0).isAction());
}

TEST(World, ADD) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_WALL) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_multiple) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, HOP_WALL_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 3);

	w.step();
	ASSERT_NE(w.cellContents(0, 3), (Creature*)NULL);
}

TEST(World, HOP_multiple_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 2), (Creature*)NULL);
}

TEST(World, turn_HOP) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_WALL) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_multiple) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 2);

	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, turn_HOP_WALL_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 3);

	w.step();
	ASSERT_NE(w.cellContents(0, 3), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 3), (Creature*)NULL);
}

TEST(World, turn_HOP_multiple_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 3, 0);

	w.step();
	ASSERT_NE(w.cellContents(3, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, right_HOP) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
}

TEST(World, right_HOP_WALL) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 3);

	w.step();
	ASSERT_NE(w.cellContents(1, 3), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 3), (Creature*)NULL);
}

TEST(World, right_HOP_multiple) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 0);

	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
}

TEST(World, right_HOP_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, right_HOP_WALL_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 3, 0);

	w.step();
	ASSERT_NE(w.cellContents(3, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(3, 0), (Creature*)NULL);
}

TEST(World, right_HOP_multiple_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
}

TEST(World, right_left_HOP) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, right_left_HOP_WALL) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 1);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, right_left_HOP_multiple) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 2);

	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 2), (Creature*)NULL);
}

TEST(World, right_left_HOP_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
}

TEST(World, right_left_HOP_WALL_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 3);

	w.step();
	ASSERT_NE(w.cellContents(1, 3), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 3), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 3), (Creature*)NULL);
}

TEST(World, right_left_HOP_multiple_east) {
	World w(4, 4);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
}

TEST(World, ADD_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_WALL_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_multiple_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, HOP_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, HOP_WALL_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 99);

	w.step();
	ASSERT_NE(w.cellContents(0, 99), (Creature*)NULL);
}

TEST(World, HOP_multiple_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 2), (Creature*)NULL);
}

TEST(World, turn_HOP_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_WALL_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_multiple_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 2);

	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
}

TEST(World, turn_HOP_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, turn_HOP_WALL_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 3);

	w.step();
	ASSERT_NE(w.cellContents(0, 3), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 3), (Creature*)NULL);
}

TEST(World, turn_HOP_multiple_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 3, 0);

	w.step();
	ASSERT_NE(w.cellContents(3, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, right_HOP_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 0));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
}

TEST(World, right_HOP_WALL_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 99);

	w.step();
	ASSERT_NE(w.cellContents(1, 99), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 99), (Creature*)NULL);
}

TEST(World, right_HOP_multiple_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 0);

	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
}

TEST(World, right_HOP_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
}

TEST(World, right_HOP_WALL_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 99, 0);

	w.step();
	ASSERT_NE(w.cellContents(99, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(99, 0), (Creature*)NULL);
}

TEST(World, right_HOP_multiple_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 1));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 0, 0);

	w.step();
	ASSERT_NE(w.cellContents(0, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 0), (Creature*)NULL);
}

TEST(World, right_left_HOP_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, right_left_HOP_WALL_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 0, 1);

	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 1), (Creature*)NULL);
}

TEST(World, right_left_HOP_multiple_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, UP, 'h');
	w.add(hop, 2, 2);

	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(2, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(0, 2), (Creature*)NULL);
}

TEST(World, right_left_HOP_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 1);

	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
}

TEST(World, right_left_HOP_WALL_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 99);

	w.step();
	ASSERT_NE(w.cellContents(1, 99), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 99), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 99), (Creature*)NULL);
}

TEST(World, right_left_HOP_multiple_east_largeGrid) {
	World w(100, 100);
	Species Hopper;
	Hopper.push_back(Instruction(Instruction::RIGHT));
	Hopper.push_back(Instruction(Instruction::LEFT));
	Hopper.push_back(Instruction(Instruction::HOP));
	Hopper.push_back(Instruction(Instruction::GO, 2));

	Creature hop(Hopper, RIGHT, 'h');
	w.add(hop, 1, 0);

	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 0), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 1), (Creature*)NULL);
	w.step();
	ASSERT_NE(w.cellContents(1, 2), (Creature*)NULL);
}

