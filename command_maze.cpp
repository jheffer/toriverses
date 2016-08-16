#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "harvester.h"
#include "map.h"  

char Harvester::command_maze () const {

	if(myMap->survey(x,y) == '\\' && px == 0) return 'e'; // exit
        else if(myMap->survey(x+1,y) != '@' && px == 0) return 'X'; // start moving
        else if(myMap->survey(x,y-1) != '@' && px == 0) return 'y'; // start down
	else if(myMap->survey(x-1,y) != '@' && px == 0) return 'x'; // start left
	else if(myMap->survey(x,y+1) != '@' && px == 0) return 'Y'; // start up
	else return 'w';
}









//use  if map toroid (myMap->getXtor(x),y)
