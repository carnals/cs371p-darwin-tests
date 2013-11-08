// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % w++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -w
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string> 
#include <vector>
#include "Darwin.h"

// ----
// main
// ----


int main () 
{
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

  // ----
  // food
  // ----

  Species food('f');
  food.instruction("left");
  food.instruction("go 0");

  // ------
  // hopper
  // ------

  Species hopper('h');
  hopper.instruction("hop");
  hopper.instruction("go 0");

  // -----
  // rover
  // -----

  Species rover('r');
  rover.instruction("if_enemy 9");
  rover.instruction("if_empty 7");
  rover.instruction("if_random 5");
  rover.instruction("left");
  rover.instruction("go 0");
  rover.instruction("right");
  rover.instruction("go 0");
  rover.instruction("hop");
  rover.instruction("go 0");
  rover.instruction("infect");
  rover.instruction("go 0");

  // ----
  // trap
  // ----

  Species trap('t');
  trap.instruction("if_enemy 3");
  trap.instruction("left");
  trap.instruction("go 0");
  trap.instruction("infect");
  trap.instruction("go 0");

  // ----
  // best
  // ----

  Species best('b');

  /*
	Include best
	*/


  // ----------
  // darwin 8x8
  // ----------
  try 
  {
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    cout << "*** Darwin 8x8 ***" << endl;
		
		World <8,8>w;
    Creature f1(food, 2);
    Creature f2(food, 1);
    Creature h1(hopper, 1);
    Creature h2(hopper, 2);
    Creature h3(hopper, 3);
    Creature h4(hopper, 0);
    w.move(0, 0, f1);
    w.move(3, 3, h1);
    w.move(3, 4, h2);
    w.move(4, 4, h3);
    w.move(4, 3, h4);
    w.move(7, 7, f2);
    cout << "\nTurn: 0";
    w.display();
    for(int i = 0; i < 5; i++)
    {
      w.turn();
      cout << "\nTurn: " << i + 1;
      w.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ----------
  // darwin 7x9
  // ----------

  try 
  {
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    cout << "*** Darwin 7x9 ***" << endl;
    World<7, 9> w;
    Creature t1(trap, 3);
    Creature t2(trap, 0);
    Creature h1(hopper, 2);
    Creature r1(rover, 1);
    w.move(0, 0, t1);
    w.move(6, 8, t2);
    w.move(3, 2, h1);
    w.move(5, 4, r1);
    cout << "\nTurn: 0";
    w.display();
    for(int i = 0; i < 5; i++)
    {
      w.turn();
      cout << "\nTurn: " << i + 1;
      w.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 72x72
  // without best
  // ------------

  try 
  {
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print every 100th grid.
    */
    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    World<72, 72> w;
    for (int a = 0; a < 10; a++) 
    {
      int pos = rand();
      Creature creature(food, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int b = 0; b < 10; b++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int c = 0; c < 10; c++) 
    {
      int pos = rand();
      Creature creature(rover, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int d = 0; d < 10; d++) 
    {
      int pos = rand();
      Creature creature(trap, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    cout << "Turn = 0.";
    w.display();
    for (int e = 1; e < 1001; ++e) 
    {
      w.turn();
      if (e % 100 == 0)
      {
        cout << "Turn = " << e << ".";
        w.display();
      }
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 72x72
  // with best
  // ------------

  try 
  {
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print every 100th grid.
    */
    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    World<72, 72> w;
    for (int a = 0; a < 10; a++) 
    {
      int pos = rand();
      Creature creature(food, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int b = 0; b < 10; b++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int c = 0; c < 10; c++) 
    {
      int pos = rand();
      Creature creature(rover, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int d = 0; d < 10; d++) 
    {
      int pos = rand();
      Creature creature(trap, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    for (int e = 0; e < 10; e++) 
    {
      int pos = rand();
      Creature creature(best, rand() % 4);
      w.move(pos % 5184 / 72, pos % 5184 % 72, creature);
    }
    cout << "Turn = 0.";
    w.display();
    for (int e = 1; e < 1001; ++e) 
    {
      w.turn();
      if (e % 100 == 0)
      {
        cout << "Turn = " << e << ".";
        w.display();
      }
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }


  // ----------
  // darwin 8x8
  // ----------

  try 
  {
    cout << "*** Darwin 8x8 ***" << endl;
    
    World<8, 8> w;
    for (int a = 0; a < 2; a++) 
    {
      int pos = rand();
      Creature creature(best, rand() % 4);
      w.move(pos % 64 / 8, pos % 64 % 8, creature);
    }
    for (int a = 0; a < 2; a++) 
    {
      int pos = rand();
      Creature creature(hopper, rand() % 4);
      w.move(pos % 64 / 8, pos % 64 % 8, creature);
    }
    cout << "Turn = 0.";
    w.display();
    for (int e = 1; e < 100; ++e) 
    {
      w.turn();
      cout << "Turn = " << e << ".";
      w.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 2 x 2
  // ------------

  try 
  {
    cout << "*** Darwin 2x2 ***" << endl;
    srand(0);

    World<2, 2> grid;
    grid.move(0, 0, Creature(rover, 0));
    grid.move(1, 0, Creature(food, 2));
    grid.move(0, 1, Creature(food, 2));
    grid.move(1, 1, Creature(food, 2));
    cout << "\nTurn: 0";
    grid.display();
    for(int i = 0; i < 5; i++)
    {
      grid.turn();
      cout << "\nTurn: " << i + 1;
      grid.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&) 
  {
    assert(false);
  }

  // ------------
  // darwin 1 x 1
  // ------------

  try 
  {
    cout << "*** Darwin 1x1 ***" << endl;
    srand(0);

    World<1, 1> grid;
    grid.move(0, 0, Creature(food, 0));
    cout << "\nTurn: 0";
    grid.display();
    for(int i = 0; i < 5; i++)
    {
      grid.turn();
      cout << "\nTurn: " << i + 1;
      grid.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }


  // ------------
  // darwin 5 x 5
  // ------------

  try 
  {
    cout << "*** Darwin 5x5 ***" << endl;
    srand(0);

    World<5, 5> grid;
    grid.move(0, 0, Creature(food, 0));
    grid.move(0, 1, Creature(food, 0));
    grid.move(0, 2, Creature(food, 0));
    grid.move(0, 3, Creature(food, 0));
    grid.move(0, 4, Creature(food, 0));
    grid.move(1, 4, Creature(rover, 1));
    cout << "\nTurn: 0";
    grid.display();
    for(int i = 0; i < 5; i++)
    {
      grid.turn();
      cout << "\nTurn: " << i + 1;
      grid.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }



  try 
  {
    cout << "*** Darwin 3x3 ***" << endl;
    srand(0);

    World<3, 3> grid;
    grid.move(0, 0, Creature(food, 0));
    grid.move(0, 1, Creature(food, 0));
    grid.move(0, 2, Creature(food, 0));
    grid.move(1, 2, Creature(trap, 1));
    cout << "\nTurn: 0";
    grid.display();
    for(int i = 0; i < 5; i++)
    {
      grid.turn();
      cout << "\nTurn: " << i + 1;
      grid.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }

  // ------------
  // darwin 2 x 2
  // ------------

  try 
  {
    cout << "*** Darwin 2x2 ***" << endl;
    srand(0);

    World<2, 2> grid;
    grid.move(0, 0, Creature(food, 0));
    grid.move(0, 1, Creature(food, 0));
    grid.move(1, 0, Creature(food, 0));
    grid.move(1, 1, Creature(trap, 1));
    cout << "\nTurn: 0";
    grid.display();
    for(int i = 0; i < 4; i++)
    {
      grid.turn();
      cout << "\nTurn: " << i + 1;
      grid.display();
    }
  }
  catch (const invalid_argument&) 
  {
    assert(false);
  }
  catch (const out_of_range&)
  {
    assert(false);
  }
	
	
	
  return 0;
}