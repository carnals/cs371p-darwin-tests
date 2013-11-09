// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Justin Hust
// EID: jkh2367
// -----------------------------

/*
To run the program:
% g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
% valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
doxygen -g
That creates the file Doxyfile.
Make the following edits:
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------

#include "Darwin.h"

#include <cassert> // assert
#include <cstdlib> // rand, srand
#include <iostream> // cout, endl
#include <sstream>
#include <stdexcept> // invalid_argument, out_of_range


// ----------
// darwin 8x8
// ----------
/*
8x8 Darwin
Food, facing east, at (0, 0)
Hopper, facing north, at (3, 3)
Hopper, facing east, at (3, 4)
Hopper, facing south, at (4, 4)
Hopper, facing west, at (4, 3)
Food, facing north, at (7, 7)
Simulate 5 moves.
Print every grid.
*/
bool default_8x8(std::ostream &o) {
  o << "*** Darwin 8x8 ***" << std::endl;
  World w(8, 8);

  w.addCreature( w.toCoord(0, 0), East, World::Food);
  w.addCreature( w.toCoord(3, 3), North, World::Hopper);
  w.addCreature( w.toCoord(3, 4), East, World::Hopper);
  w.addCreature( w.toCoord(4, 4), South, World::Hopper);
  w.addCreature( w.toCoord(4, 3), West, World::Hopper);
  w.addCreature( w.toCoord(7, 7), North, World::Food);
  w.outputBoard(o);
  o << std::endl;
  
  // run and print 5 turns
  for(int i=0;i < 5; i++) {
    w.runTurn();
    w.outputBoard(o);
    o << std::endl;
     
  }
  
  // *** verify ***
  std::ostringstream ss;
  w.outputBoard(ss);
  return( ss.str() == "Turn = 5.\n  01234567\n0 f..h....\n1 ........\n2 ........\n3 .......h\n4 h.......\n5 ........\n6 ........\n7 ....h..f\n");

}

// ----------
// darwin 7x9
// ----------
/*
7x9 Darwin
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 8)
Simulate 5 moves.
Print every grid.
*/
bool default_7x9(std::ostream &o) {
  o << "*** Darwin 7x9 ***" << std::endl;
  World w(7, 9);  

  w.addCreature( w.toCoord(0, 0), South, World::Trap);
  w.addCreature( w.toCoord(3, 2), East, World::Hopper);
  w.addCreature( w.toCoord(5, 4), North, World::Rover);
  w.addCreature( w.toCoord(6, 8), West, World::Trap);
  
  w.outputBoard(o);
  o << std::endl;
  
  // run and print 5 turns
  for(int i=0;i < 5; i++) {
    w.runTurn();
    w.outputBoard(o);
    o << std::endl;
     
  }


  // *** verify ***
  std::ostringstream ss;
  w.outputBoard(ss);
  return( ss.str() == "Turn = 5.\n  012345678\n0 t........\n1 ....r....\n2 .........\n3 .......r.\n4 .........\n5 .........\n6 ........t\n");
  
}

// ----------
// mine 10x20
// ----------
/*
10x20 Darwin
  10 random food, facing random
  5 random traps, facing random
  3 random rovers, facing random
  10 random hoppers, facing random

Simulate 10 moves.
Print every grid.
*/
void mine_10x20(std::ostream &o) {
  o << "*** Darwin 10x20 ***" << std::endl;
  World w(10, 20);

  for(int i=1; i <= 10; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Food);
  
  }
  
  for(int i=1; i <= 5; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Trap);
  
  }
  
  for(int i=1; i <= 3; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Rover);
  
  }
  
  
  for(int i=1; i <= 10; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Hopper);
  
  }
  
  
  w.outputBoard(o);
  o << std::endl;
  
  // run and print 10 turns
  for(int i=0;i < 10; i++) {
    w.runTurn();
    w.outputBoard(o);
    o << std::endl;
     
  }
  
}

// ----------
// mine 6x4
// ----------
/*
6x4 Darwin
  10 random rovers, facing random
  3 random traps, facing random
Simulate 20 moves.
Print every grid.
*/
void mine_6x4(std::ostream &o) {
  o << "*** Darwin 6x4 ***" << std::endl;
  World w(6, 4);

  for(int i=1; i <= 10; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Rover);
  
  }

  for(int i=1; i <= 3; i++) {
    int coord = w.randomCoord();
    Direction facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Trap);
  
  }
  int coord = w.randomCoord();
  Direction facing = Creature::randomFacing();
  w.addCreature(coord, facing, World::Trap);


  w.outputBoard(o);
  o << std::endl;
  
  // run and print 10 turns
  for(int i=0;i < 20; i++) {
    w.runTurn();
    w.outputBoard(o);
    o << std::endl;
     
  }
  
}


// ----------
// darwin 72x72 without best
// ----------
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
Print the first 10 grids (i.e. 0, 1, 2...9).
Print every 100th grid after that (i.e. 100, 200, 300...1000).
*/
void default_72x72(std::ostream &o) {
  o << "*** Darwin 72x72 ***" << std::endl;
  
  srand(0);
  World w(72,72);
  
  int coord = 0;
  Direction facing = West;
  
  for(int i=0;i<10;i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature( coord, facing, World::Food);

  }
  
  for(int i=0;i<10;i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature( coord, facing, World::Hopper);
          
  }
  
  for(int i=0;i<10;i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature( coord, facing, World::Rover);
          
  }
  
  for(int i=0;i<10;i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature( coord, facing, World::Trap);
          
  }


  // run 1000 turns with selective printing.
  for(int i=0;i <= 1000; i++) {
    // print grids 0-9 and then 100, 200, 300
    if( (i < 10) || (i % 100 == 0)) {
      w.outputBoard(o);
      o << std::endl;
      
    }
  
    w.runTurn();
    
  }

}

// ------------------------------------------
int student_rbrooks(std::ostream &o) {

    try
    {
        /*
        make a 1x20 world
        19 foods from spot o,o to o,18 facing west
        1 trap at 0,19 facing west
        40 moves
        print first 10 and every 4th
        */
        std::cout << "*** rbrooks: Darwin 1x20 Buffet ***" << std::endl;

        srand(0);
        World w(1, 20);
  
        for(int i=0;i < 19; ++i)
          w.addCreature(i, West, World::Food);
        
        w.addCreature(19, West, World::Trap);


        w.outputBoard(o);

          int i;
          for(i = 1; i <= 40; ++i)
          {
            w.runTurn();
            if(i <= 10 || i % 4 == 0)
            {
               w.outputBoard(o);
               o << std::endl;
            }
          }


        std::ostringstream ss1;
        w.outputBoard(ss1);
        if(ss1.str() != "Turn = 40.\n  01234567890123456789\n0 fffffffffttttttttttt\n")
          return 1;

    }
    catch (const std::invalid_argument&) {
        assert(false);}
    catch (const std::out_of_range&) {
        assert(false);}
        
        
  
        
    // ********************************************************************
    try 
    {
        /*
            make a 2x20 world
            1 hopper on top row 0,0 facing east
            1 rovers on second row 1,0 facing east
            4 foods on tird row col 16-19 facing WEst
            4 foods on bottom row col 16-19  facing west
            20 years
            print every 
            the rover and hopper race to food.
            rover plays dirty
        */
        std::cout << "*** rbrooks: Darwin 2x20 Drag Race ***" << std::endl;
        srand(0);
        World w(2,20);
        
        w.addCreature( w.toCoord(0, 0), East, World::Hopper);
        w.addCreature( w.toCoord(1, 0), East, World::Rover);
        
        
        w.addCreature( w.toCoord(0, 16), West, World::Food);
        w.addCreature( w.toCoord(0, 17), West, World::Food);
        w.addCreature( w.toCoord(0, 18), West, World::Food);
        w.addCreature( w.toCoord(0, 19), West, World::Food);
        w.addCreature( w.toCoord(1, 16), West, World::Food);
        w.addCreature( w.toCoord(1, 17), West, World::Food);
        w.addCreature( w.toCoord(1, 18), West, World::Food);
        w.addCreature( w.toCoord(1, 19), West, World::Food);
        
        int i;
        w.outputBoard(o);
        o << std::endl;

        for(i = 1; i <= 20; ++i)
        {
          w.runTurn();
          w.outputBoard(o);
          o << std::endl;
          
        }    
        
        std::ostringstream ss2;
        w.outputBoard(ss2);
        if(ss2.str() != "Turn = 20.\n  01234567890123456789\n0 ...............rrrff\n1 .............r..rrff\n")
          return 2;
          
    }
    catch (const std::invalid_argument&) {
        assert(false);}
    catch (const std::out_of_range&) {
        assert(false);}

  return -1;
  
}

// ------------------------------------------
int student_sccheng(std::ostream &o) {
  /*
  Randomly place the following creatures facing randomly.
  Call rand(), mod it with 100 (10x10), and use that for the position
  in a row-major order grid.
  Call rand() again, mod it with 4 and use that for its direction with
  the ordering: west, north, east, south.
  Do that for each kind of creature.
  2 Food
  2 Hopper
  2 Rover
  2 Trap
  Simulate 15 moves.
  Print each grid.
  */
  std::cout << "*** sccheng: Darwin 10x10 ***" << std::endl;
  srand(0);

  World w(10, 10);
  
  int coord;
  Direction facing = West;
  
  for(int i=0;i<2; i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Food);
  
  }
  
  for(int i=0;i<2; i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Hopper);
  
  }
  
  for(int i=0;i<2; i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Rover);
  
  }
  
  for(int i=0;i<2; i++) {
    coord = w.randomCoord();
    facing = Creature::randomFacing();
    w.addCreature(coord, facing, World::Trap);
  
  }
  
  w.outputBoard(o);
  
  for(int i = 1; i <= 15; i++)
  {
      w.runTurn();
      w.outputBoard(o);
      o << std::endl;
  }

  std::ostringstream ss;
  w.outputBoard(ss);
  
  if(ss.str() != "Turn = 15.\n  0123456789\n0 r.r.......\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ...t......\n7 .......f..\n8 ...fh.....\n9 t........r\n")
    return 1;
    
  return -1;

}

// ------------------------------------------------------------------
int student_osaprych(std::ostream &o) {
  try {
    std::cout << "*** osaprych: Darwin 30x50 without Best ***" << std::endl;
    srand(0);
    World w(30, 50);
    
    int coord;
    Direction facing = West;
    
    for (int i = 1; i <= 100; i++) {
      coord = w.randomCoord();
      facing = Creature::randomFacing();
      w.addCreature(coord, facing, World::Food);
    }

    for (int i = 1; i <= 10; i++) {
      coord = w.randomCoord();
      facing = Creature::randomFacing();
      w.addCreature(coord, facing, World::Hopper);
    }

    for (int i = 1; i <= 10; i++) {
      coord = w.randomCoord();
      facing = Creature::randomFacing();
      w.addCreature(coord, facing, World::Rover);
    }

    for (int i = 1; i <= 10; i++) {
      coord = w.randomCoord();
      facing = Creature::randomFacing();
      w.addCreature(coord, facing, World::Trap);
    }

    int s = 0;
    for (; s <= 20; s++){
      w.outputBoard(o);
      o << std::endl;
      w.runTurn();
      
    }
    
    for (; s <= 2000; s++) {
      w.runTurn();
    }
    
    w.outputBoard(o);
    o << std::endl;
      
    std::ostringstream ss;
    w.outputBoard(ss);
    
    if(ss.str() != "Turn = 2001.\n  01234567890123456789012345678901234567890123456789\n0 .rrrrrr..r...r...rr....r..........r...............\n1 .................r.....r..........................\n2 ......r......r.....r..............................\n3 ....r....r.......rrr............................r.\n4 ...r.........................................r....\n5 ..................................................\n6 ..................r...............................\n7 .................r................................\n8 .................r................r...............\n9 r...................r............................r\n0 ........r.....rr....r....r...r....................\n1 ..r....r.....r...........rr.........r.......r.....\n2 ...........r..r...................r...............\n3 .rr.r...r................r.r......rr..............\n4 .r.r...r..................r.......................\n5 r..r..............................................\n6 .....r.....r....r.r......rr...................r...\n7 .................r....r..........................r\n8 r....r..rr............r........r..................\n9 r..................r............r.................\n0 .....................................r............\n1 ........rr.............................r..........\n2 r..............r....r.....rrr.....................\n3 ..r................r.....r..................r.....\n4 ...r.........................r.....r...r...r...r..\n5 ..........................................r.......\n6 ....rrr.................................r........r\n7 ..rr...r.....r....r.....................rr......rr\n8 .............r............................r.....r.\n9 ..r..r.....r..........r...........................\n")
      return 1;
      
  } catch (const std::invalid_argument&) {
      assert(false);
  } catch (const std::out_of_range&) {
      assert(false);
  }

  return -1;

}

// -----------------------------------------------------
int student_tashar(std::ostream &o) {
    try {
        o << "*** tashar: Darwin 10x10 ***" << std::endl;
        srand(0);
        World w(10, 10);
        
        int coord;
        Direction facing;

        for(int i = 0; i < 50; i++) {
          coord = w.randomCoord();
          facing = Creature::randomFacing();
          w.addCreature(coord, facing, World::Hopper);
        
        }
        
        w.outputBoard(o);
        o << std::endl;
        
        for(int i = 1; i <= 10; i++) {
          w.runTurn();
          w.outputBoard(o);
          o << std::endl;
        
        }
        
        std::ostringstream ss;
        w.outputBoard(ss);
        if(ss.str() != "Turn = 10.\n  0123456789\n0 .....hhh..\n1 h....hh..h\n2 .....hh.hh\n3 hhhh.....h\n4 ...hh....h\n5 ....h.....\n6 ...hh.....\n7 h...h.hh..\n8 .h.hhhhh..\n9 hhhhh.hh.h\n")
          return 1;

    }
    catch (const std::invalid_argument& e) {
        assert(false);}
    catch (const std::out_of_range& e) {
        assert(false);}
     
  return -1;
  
  
}

// ------------------------------------------------------
int student_mjs4373(std::ostream &o) {
    // ----------------------------
    // darwin 50x50 with 15h 15t 3r
    // ----------------------------
    try 
    {
        std::cout << "*** mjs4373: Darwin 50x50 with 15h 15t 3r ***" << std::endl;
        srand(0);
        World w(50, 50);
        
        // hopper
        for(int i=1;i<=15;i++) {
          int coord = w.randomCoord();
          Direction facing = Creature::randomFacing();
          w.addCreature(coord, facing, World::Hopper);
        }

        // 
        for(int i=1;i<=3;i++) {
          int coord = w.randomCoord();
          Direction facing = Creature::randomFacing();
          w.addCreature(coord, facing, World::Rover);
        }

        for(int i=1;i<=15;i++) {
          int coord = w.randomCoord();
          Direction facing = Creature::randomFacing();
          w.addCreature(coord, facing, World::Trap);
        }
        
        w.outputBoard(o);
        o << std::endl;
        
        for(int i=1; i <= 500; i++) {
          w.runTurn();
          
          if( (i < 4) || (i % 100) == 0) {
            w.outputBoard(o);
            o << std::endl;
            
          }
        }
        
        
        std::ostringstream ss;
        w.outputBoard(ss);
        if( ss.str() != "Turn = 500.\n  01234567890123456789012345678901234567890123456789\n0 ...rr.r............r......................r.......\n1 .....r....r.......................................\n2 ..................................................\n3 ..................................................\n4 ..................................................\n5 ..................................................\n6 ..................................................\n7 ..................................................\n8 ..................................................\n9 ..................................................\n0 ..................................................\n1 ..................................................\n2 ..................................................\n3 ..................................................\n4 ...............t..................................\n5 ...r...........t..................................\n6 ....r..........tt.................................\n7 r.................................................\n8 ..................................................\n9 ..................................................\n0 ..................................................\n1 ........................................tt........\n2 .........................................t........\n3 ..................................................\n4 ...........................ttt....................\n5 r.................................................\n6 ..................................................\n7 ..........................................tt......\n8 ...........................................t......\n9 ..................................................\n0 ..................................................\n1 ....................................r.............\n2 .................................................r\n3 ..................................................\n4 ........r.........................................\n5 .................................................r\n6 ..................................................\n7 ..................................................\n8 ..................................................\n9 .................r................................\n0 ..................................................\n1 r.................................................\n2 ..................................................\n3 .................................................r\n4 ..................................................\n5 ..................................................\n6 .................r................................\n7 ..................................................\n8 ..................................................\n9 .........................................r........\n")
          return 1;
            
    }
    catch (const std::invalid_argument&)
    {
        assert(false);
    }
    catch (const std::out_of_range&)
    {
        assert(false);
    }

  return -1;
  
}

// ----
// main
// ----
int main () {
  bool default8x8 = default_8x8(std::cout);
  bool default7x9 = default_7x9(std::cout);
  
  int rbrooks = student_rbrooks(std::cout);
  int sccheng = student_sccheng(std::cout);
  int osaprych = student_osaprych(std::cout);
  int tashar = student_tashar(std::cout);
  int mjs4373 = student_mjs4373(std::cout);

  
  mine_10x20(std::cout);
  mine_6x4(std::cout);
  
  default_72x72(std::cout);

  // *** output consensus ***
  
  std::cout << std::endl;
  std::cout << "Consensus with default 8x8? ";
  if(default8x8)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO." << default8x8 << std::endl;
 
  std::cout << "Consensus with default 7x9? ";
  if(default7x9)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO." << default7x9 << std::endl;
 
  std::cout << "-----" << std::endl;
 
  std::cout << "Consensus with rbrooks? ";
  if(rbrooks == -1)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO.  Failed test " << rbrooks << std::endl;
    
  std::cout << "Consensus with sccheng? ";
  if(sccheng == -1)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO.  Failed test " << sccheng << std::endl;

  std::cout << "Consensus with osaprych? ";
  if(osaprych == -1)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO.  Failed test " << osaprych << std::endl;
 
  std::cout << "Consensus with tashar? ";
  if(tashar == -1)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO.  Failed test " << tashar << std::endl;

  std::cout << "Consensus with mjs4373? ";
  if(mjs4373 == -1)
    std::cout << "YES" << std::endl;
  else 
    std::cout << "NO.  Failed test " << mjs4373 << std::endl;
      
}
