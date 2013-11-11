/*
To test the program:

 % g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

 % valgrind TestDarwin > TestDarwin.out
*/
// --------
// includes
// --------
//
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
//#define class struct
#define private public
#define protected public
#include "Darwin.h"
#include "gtest/gtest.h"

#define HOP = 0;

using namespace std;


TEST(Species, name1){
	Species temp("f");
	assert(temp.thename() =="f");
}


TEST(Species,name2){
	Species temp("Lunch time");
	assert(temp.thename() == "Lunch time");
}

TEST(Species,name3){
	Species temp("Corpse");
	assert(temp.thename() == "Corpse");

}

TEST(Species,name4){
	Species temp("Akbar");
	Species temp2("General");
	assert(temp.thename() == "Akbar");
	assert(temp2.thename() == "General");
	assert(temp.thename() != temp2.thename());

}

TEST(Species2, construct){
	Species temp;
	assert(temp.thename() != "Akbar");
	assert(temp.thename() == ".");

}

TEST(Species2, construct2){
	Species temp;
	Species temp2("It's a trap");

	assert(temp.thename() != temp2.thename());

}

TEST(Species2, construct3){
	Species temp("kf kfl");
	Species temp2("kf kfl");
	assert(temp.thename() == temp2.thename());
}

TEST(Species3, Instruction){
	Species temp("Dog");
	temp.addInstruction(0,0);
	assert(temp.theInstruction(0) == "Hop 0");

}

TEST(Species3, Instruction2){
	Species temp("Cat");
	Species dog("Dog");
	temp.addInstruction(0,0);
	dog.addInstruction(3,0);
	assert(temp.theInstruction(0) == "Hop 0");
	assert(dog.theInstruction(0) == "Infect 0");
}

TEST(Species3, Instruction3){
	Species cat("Cat");
	cat.addInstruction(4,3);
	cat.addInstruction(5,4);
	cat.addInstruction(8,0);
	cat.addInstruction(0,0);
	cat.addInstruction(1,0);
	assert(cat.theInstruction(0) =="If_Empty 3");
	assert(cat.theInstruction(4) =="Left 0");

}

TEST(Species3, Instruction4){
	Species cat("Cat");
        cat.addInstruction(4,3);
	Species dog("Dog");
        dog.addInstruction(3,0);
	cat.addInstruction(3,0);
	assert(dog.theInstruction(0) == "Infect 0");
	assert(cat.theInstruction(1) == "Infect 0");
	assert(cat.theInstruction(0) == "If_Empty 3");	

}

TEST(Species3, Instruction5){
	Species c("c");
	Species cat("Cat");
	c.addInstruction(0,0);
	cat.addInstruction(0,0);
	assert(c.theInstruction(0)==cat.theInstruction(0));

}

TEST(Species3, Instruction6){
	Species thing;
	thing.addInstruction(10,9);
	assert(thing.theInstruction(0) == "That Instruction has not been entered or is unknown.");
}

TEST(Creature, construct){
	Creature thing;
	assert(thing.theDirection()=="West");
	assert(thing.prognum()==0);
	assert(thing.whtCreat().thename()==".");

}

TEST(Creature, construct2){
	Species dog("Dog");
	Creature thing(dog);
        assert(thing.theDirection()=="West");
        assert(thing.prognum()==0);
        assert(thing.whtCreat().thename()=="Dog");
}

TEST(Creature, construct3){
	Species dog("Dog");
	dog.addInstruction(0,0);
	Creature thing(dog);
	assert(thing.whtCreat().thename()=="Dog");
	assert(thing.whtCreat().theInstruction(0)=="Hop 0");

}

TEST(Creature, construct4){
	Species dog("Dog");
	Species cat("Cat");
	Creature thing(dog);
	Creature thing2(cat);
	assert(thing.whtCreat().thename()!=thing2.whtCreat().thename());
	assert(thing.whtCreat().thename() == "Dog");
	assert(thing2.whtCreat().thename() == "Cat");

}

TEST(Creature, construct5){
	Species dog("Dog");
	Creature thing(dog);
	Creature thing2(dog);
	assert(thing.whtCreat().thename() ==thing2.whtCreat().thename());
}

TEST(Creature, construct6){
	Species dog("d");
	dog.addInstruction(0,0);
	dog.addInstruction(1,0);
	Creature thing(dog);
	dog.addInstruction(2,0);
	assert(thing.whtCreat().theInstruction(2) == "That Instruction has not been entered or is unknown.");
}

TEST(Creature,construct7){
	Species dog("d");
        dog.addInstruction(0,0);
        dog.addInstruction(1,0);
        dog.addInstruction(2,0);
        Creature thing(dog);
	assert(thing.whtCreat().theInstruction(2)=="Right 0");


}

TEST(Creature, construct8){
	Species dog("dog");
	Creature thing(dog, 0);
	assert(thing.theDirection()=="West");	


}

TEST(Creature, construct9){
	Species dog("dog");
	Creature thing(dog,1);
	assert(thing.theDirection()=="North");
}

TEST(Creature, construct10){
	Species dog("dog");
	Creature thing(dog,2);
	assert(thing.theDirection()=="East");
}

TEST(Creature,construct11){
	Species dog("dog");
	Creature thing(dog,3);
	assert(thing.theDirection()=="South");
}

TEST(Creature,construct12){
	Species dog("dog");
	Creature thing(dog,4);
	assert(thing.theDirection()=="That is not a direction");
}

TEST(Creaturedir, direction){
	Species dog("dog");
	Creature thing(dog,0);
	assert(thing.changeFace(0));
	assert(thing.theDirection() =="West");
}

TEST(Creaturedir,direction2){
	Species dog("dog");
	Creature thing(dog,0);
        assert(thing.changeFace(1));
	assert(thing.theDirection()=="North");
}

TEST(Creaturedir,direction3){
        Species dog("dog");
        Creature thing(dog,0);
        assert(thing.changeFace(2));
        assert(thing.theDirection()=="East");
}

TEST(Creaturedir,direction4){
        Species dog("dog");
        Creature thing(dog,0);
        assert(thing.changeFace(3));
        assert(thing.theDirection()=="South");
}

TEST(Creaturedir,direction5){
        Species dog("dog");
        Creature thing(dog,0);
        assert(!thing.changeFace(4));
	assert(thing.theDirection()=="West");
}

TEST(Creatureinf, infect){
	Species human("human");
	Species zombie("zombie");
	Creature food(human);
	Creature hunter(zombie);
	food.infected(hunter.whtCreat());
	assert(food.whtCreat().thename()=="zombie");
}

TEST(Creatureinf, infect2){
        Species human("human");
        Species zombie("zombie");
	human.addInstruction(0,0);
        Creature food(human);
	assert(food.whtCreat().theInstruction(0)=="Hop 0");
        Creature hunter(zombie);
        food.infected(hunter.whtCreat());
        assert(food.whtCreat().thename()=="zombie");
	assert(food.whtCreat().theInstruction(0)=="That Instruction has not been entered or is unknown.");
}

TEST(Creatureinf,infect3){
	Species pink("(>\")>");
	Species ball("^(\")^");
	Species that("<(\"<)");
	Species dances("^(\")^");

	Creature thing1(pink);
	Creature thing2(ball);
	Creature thing3(that);
	Creature thing4(dances);

	thing1.infected(thing4.whtCreat());
	thing2.infected(thing3.whtCreat());
	thing4.infected(thing3.whtCreat());

	assert(thing1.whtCreat().thename() == "^(\")^");
	assert(thing2.whtCreat().thename() == "<(\"<)");
	assert(thing4.whtCreat().thename() == "<(\"<)");
}

TEST(Creatureinf, infect4){
	Species thebeginning("thebeginning");
	Species theend;

	Creature life(thebeginning);
	Creature blank(theend);
	life.infected(blank.whtCreat());
	assert(life.whtCreat().thename() == ".");
}

TEST(Creatureinf, infect5){
	Species human("human");
        Species zombie("zombie");
        human.addInstruction(0,0);
        Creature food(human);
        assert(food.whtCreat().theInstruction(0)=="Hop 0");
        Creature hunter(zombie);
        hunter.infected(food.whtCreat());
        assert(hunter.whtCreat().thename()=="human");
        assert(hunter.whtCreat().theInstruction(0)=="Hop 0");
}

TEST(World, setting){
	World place(2,2);
	assert(place.theSizeW()==2);
	assert(place.theSizeH()==2);	
}

TEST(World, setting2){
	World place(10,10);
	assert(place.theSizeW()==10);
	assert(place.theSizeH()==10);
}

TEST(World, setting3){
	World place(5,10);
	assert(place.theSizeW()==10);
	assert(place.theSizeH()==5);

}

TEST(World, setting4){
	World place(1,5);
	assert(place.theSizeW()==5);
	assert(place.theSizeH()==1);
	
}

TEST(World, setting5){
	World place(6,50);
	assert(place.theSizeW()==50);
	assert(place.theSizeH()==6);


}

TEST(Worldpl, place){
	World map(2,2);
	Species dog("d");
	Species cat("c");
	Creature thing(dog);
	Creature thing2(cat);

	map.setCreat(thing,0,0,0);
	map.setCreat(thing2,0,1,1);	
	assert(map.getName(0,0)=="d");
	assert(map.getName(1,1)=="c");
}

TEST(Worldpl, place2){
	World map(10,10);
	Species dog("d");
	Species cat("c");
	Creature thing(dog);
	Creature thing2(dog);
	Creature thing3(dog);
	Creature thing4(dog);
	Creature stuff(cat);
	Creature stuff2(cat);
	Creature stuff3(cat);

	map.setCreat(thing,0, 0, 0);
	map.setCreat(thing2,0,1,1);
	map.setCreat(thing3,0,2,2);
	map.setCreat(thing4,0,3,3);
	map.setCreat(stuff,0,0,1);
	map.setCreat(stuff2,0,1,2);
	map.setCreat(stuff3,0,5,7);
	assert(map.getName(0,0)=="d");
	assert(map.getName(5,7)=="c");
	assert(map.getName(2,2)=="d");

}

TEST(Worldpl,place3){
	World map(7,3);
	Species dog("d");
	Species cat("c");
	map.setCreat(dog,0,0,6);
	map.setCreat(cat,0,2,3);

	assert(map.getName(0,6)=="d");
	assert(map.getName(2,3)=="c");

}

TEST(Worldpl,place4){
	World map(8,5);
	Species dog("d");
        Species cat("c");
        Creature thing(dog);
        Creature thing2(dog);
        Creature thing3(dog);
        Creature thing4(dog);
        Creature stuff(cat);
        Creature stuff2(cat);
        Creature stuff3(cat);

        map.setCreat(thing,0, 0, 0);
        map.setCreat(thing2,0,1,1);
        map.setCreat(thing3,0,2,2);
        map.setCreat(thing4,0,3,3);
        map.setCreat(stuff,0,0,1);
        map.setCreat(stuff2,0,1,2);
        map.setCreat(stuff3,0,4,7);
        assert(map.getName(0,0)=="d");
        assert(map.getName(4,7)=="c");
        assert(map.getName(2,2)=="d");


}

TEST(Worldpl,place5){
	World map(5,5);
	Species dog("d");
	Species cat("c");

	Creature thing(dog);
	Creature thing2(dog);
	Creature stuff(cat);
	Creature stuff2(cat);

	map.setCreat(thing,0,4,4);
	map.setCreat(thing2,0,0,0);
	map.setCreat(stuff,0,0,4);
	map.setCreat(stuff2,0,4,0);

	assert(map.getName(0,0)=="d");
	assert(map.getName(4,4)=="d");
	assert(map.getName(0,4)=="c");
	assert(map.getName(4,0)=="c");
}

TEST(Worldturn,turn){
	World map(4,4);
	Species dog("d");
	dog.addInstruction(3,0);
	Creature b1(dog);
	//cout<<"Here we are"<<endl;
	map.setCreat(b1,2,0,0);
	//cout<<"Turns out we have set it"<<endl;
	//cout<<map.theMap()<<endl;
	map.takeTurn(0,0);
	//cout<<map.theMap()<<endl;
	assert(map.getName(0,1)==map.getName(0,0));
}

TEST(Worldturn,turn2){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(3,0);
        Creature b1(dog);
        //cout<<"Here we are"<<endl;
        map.setCreat(b1,3,0,0);
        //cout<<"Turns out we have set it"<<endl;
        //cout<<map.theMap()<<endl;
        map.takeTurn(0,0);
        //cout<<map.theMap()<<endl;
        assert(map.getName(1,0)==map.getName(0,0));
}

TEST(Worldturn,turn3){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(3,0);
        Creature b1(dog);
        //cout<<"Here we are"<<endl;
        map.setCreat(b1,1,0,0);
        //cout<<"Turns out we have set it"<<endl;
        //cout<<map.theMap()<<endl;
        map.takeTurn(0,0);
        //cout<<map.theMap()<<endl;
        assert(map.getName(0,1)!=map.getName(0,0));
	assert(map.getName(1,0)!=map.getName(0,0));
}

TEST(Worldturn, turn4){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(0,0);
        Creature b1(dog);
        //cout<<"Here we are"<<endl;
        map.setCreat(b1,2,0,0);
        //cout<<"Turns out we have set it"<<endl;
        //cout<<map.theMap()<<endl;
        map.takeTurn(0,0);
        //cout<<map.theMap()<<endl;
        assert(map.getName(0,1)=="d");
}	

TEST(Worldturn,turn5){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(0,0);
        Creature b1(dog);
        map.setCreat(b1,3,0,0);
        map.takeTurn(0,0);
        assert(map.getName(1,0)=="d");
}

TEST(Worldturn,turn6){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(0,0);
        Creature b1(dog);
        map.setCreat(b1,0,0,0);
        map.takeTurn(0,0);
        assert(map.getName(1,0) != "d" && map.getName(0,1) != "d");
}

TEST(Worldturn,turn7){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(1,0);
        Creature b1(dog);
        map.setCreat(b1,1,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "West");
}

TEST(Worldturn,turn8){
 	World map(4,4);
        Species dog("d");
        dog.addInstruction(1,0);
        Creature b1(dog);
        map.setCreat(b1,2,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "North");
}

TEST(Worldturn,turn9){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(1,0);
        Creature b1(dog);
        map.setCreat(b1,3,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "East");
}

TEST(Worldturn,turn10){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(1,0);
        Creature b1(dog);
        map.setCreat(b1,0,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "South");
}

TEST(Worldturn,turn11){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(2,0);
        Creature b1(dog);
        map.setCreat(b1,1,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "East");
}

TEST(Worldturn,turn12){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(2,0);
        Creature b1(dog);
        map.setCreat(b1,2,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "South");
}

TEST(Worldturn,turn13){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(2,0);
        Creature b1(dog);
        map.setCreat(b1,3,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "West");
}

TEST(Worldturn,turn14){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(2,0);
        Creature b1(dog);
        map.setCreat(b1,0,0,0);
        map.takeTurn(0,0);
        assert(map.getCreatu(0,0).theDirection() == "North");
}

TEST(Worldturn,turn15){
	World map(4,4);
	Species dog("d");
	dog.addInstruction(3,0);
	Creature b1(dog);
	map.setCreat(b1,2,0,0);
	map.takeTurn(0,0);
	assert(map.getName(0,1)=="d");
}

TEST(Worldturn,turn16){
	World map(4,4);
        Species dog("d");
        dog.addInstruction(3,0);
        Creature b1(dog);
        map.setCreat(b1,3,0,0);
        map.takeTurn(0,0);
        assert(map.getName(1,0)=="d");
}

TEST(Worldturn,turn17){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(3,0);
        Creature b1(dog);
        map.setCreat(b1,1,3,3);
        map.takeTurn(3,3);
        assert(map.getName(2,3)=="d");
}

TEST(Worldturn,turn18){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(3,0);
        Creature b1(dog);
        map.setCreat(b1,0,3,3);
        map.takeTurn(3,3);
        assert(map.getName(3,2)=="d");
}

TEST(Worldturn,turn19){
	World map(4,4);
	Species dog("d");
	dog.addInstruction(4,1);
	dog.addInstruction(0,0);
	Creature b1(dog);
	map.setCreat(b1,2,0,0);
	map.takeTurn(0,0);
	map.takeTurn(0,0);
	assert(map.getName(0,1)=="d");
}


TEST(Worldturn,turn20){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(4,3);
	dog.addInstruction(2,0);
	dog.addInstruction(8,0);
	dog.addInstruction(0,0);
	dog.addInstruction(8,0);
        Creature b1(dog);
        map.setCreat(b1,2,0,0);
        map.takeTurn(0,0);
        map.takeTurn(0,0);
	map.takeTurn(0,1);
	map.takeTurn(0,1);
	map.takeTurn(0,1);
        assert(map.getName(0,1)!="d" && map.getName(0,2)=="d");
}

TEST(Worldturn,turn21){
        World map(4,4);
        Species dog("d");
        dog.addInstruction(4,3);
        dog.addInstruction(2,0);
        dog.addInstruction(8,0);
        dog.addInstruction(0,0);
        dog.addInstruction(8,0);
        Creature b1(dog);
        map.setCreat(b1,2,0,0);
        map.takeTurn(0,0);
        map.takeTurn(0,0);
        map.takeTurn(0,1);
        map.takeTurn(0,1);
        map.takeTurn(0,1);
	map.takeTurn(0,2);
	map.takeTurn(0,2);
	map.takeTurn(0,2);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
        assert(map.getName(0,1)!="d" && map.getName(1,3)=="d");
}

TEST(Worldturn,turn22){
	World map(4,4);
	Species dog("d");
	dog.addInstruction(5,3);
	dog.addInstruction(0,0);
	dog.addInstruction(8,0);
	dog.addInstruction(2,0);
	dog.addInstruction(8,0);
	Creature b1(dog);
	map.setCreat(b1,2,0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(0,3);
	map.takeTurn(1,3);
	assert(map.getName(0,3)!="d" && map.getName(1,3)=="d");
}

TEST(Worldturn, turn23){
	World map(4,4);
	Species dog("d");
	srand(0);
	dog.addInstruction(6,3);
	dog.addInstruction(0,0);
	dog.addInstruction(8,0);
	dog.addInstruction(1,0);
	dog.addInstruction(0,0);
	dog.addInstruction(8,0);
	Creature b1(dog);
	map.setCreat(b1,2,2,2);
	map.takeTurn(2,2);
	map.takeTurn(2,2);
	map.takeTurn(2,2);
	assert(map.getName(1,2)=="d");
}

TEST(Worldturn, turn24){
	World map(4,4);
	Species dog("d");
	Species cat("c");
	dog.addInstruction(7,3);
	dog.addInstruction(0,0);
	dog.addInstruction(8,0);
	dog.addInstruction(3,0);
	dog.addInstruction(8,0);
	Creature b1(dog);
	Creature b2(cat);
	map.setCreat(b1,2,2,2);
	map.setCreat(b2,2,2,3);
	map.takeTurn(2,2);
	map.takeTurn(2,2);
	map.takeTurn(2,2);
	assert(map.getName(2,3)=="d");

}

TEST(Worldturn, turn25){
	World map(4,4);
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	map.setCreat(b1,2,2,2);
	map.takeTurn(2,2);
	assert(map.getName(2,2)!="d");
	assert(map.getName(2,3)=="d");
}

TEST(Worldturn, turn26){
	World map(5,5);
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	Creature b2(dog);
	map.setCreat(b1,0,2,3);
	map.setCreat(b2,2,2,2);
	map.takeTurn(2,2);	
	map.takeTurn(2,3);
	assert(map.getName(2,2)=="d");
	assert(map.getName(2,3)=="d");
}

TEST(Worldturn, turn27){
	World map(2,2);
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	Creature b2(dog);
	map.setCreat(b1,3,0,0);
	map.setCreat(b2,1,1,1);
	map.takeTurn(0,0);
	map.takeTurn(1,1);
	assert(map.getName(1,0)=="d");
	assert(map.getName(0,1)=="d");
}

TEST(Misc, misc){
	Species dog("d");
	assert(dog.thename()=="d");
}

TEST(Misc, misc2){
	Species dog("d");
	dog.addInstruction(0,0);
 	assert(dog.instret(0)==0);		
}

TEST(Misc, misc3){
	Species dog("d");
	dog.addInstruction(0,0);
	assert(dog.instructjump(0)==0);
}

TEST(Misc,misc4){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(2);
	b1.changeFace(3);
	assert(b1.theDirection()=="South");
}

TEST(Misc,misc5){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(2);
	b1.changeFace(1);
	b1.changeFace(3);
	assert(b1.theDirection()=="South");
}

TEST(Misc,misc6){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(0);
	b1.changeFace(1);
	b1.changeFace(2);
	b1.changeFace(3);
	assert(b1.theDirection()=="South");
}

TEST(Misc, misc7){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(3);
	b1.changeFace(2);
	b1.changeFace(1);
	assert(b1.theDirection()=="North");
}

TEST(Misc, misc8){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(0);
	assert(b1.theDirection()=="West");
}

TEST(Misc, misc9){
	Species dog("d");
	dog.addInstruction(0,0);
	Creature b1(dog);
	b1.changeFace(1);
	assert(b1.theDirection()=="North");
}
