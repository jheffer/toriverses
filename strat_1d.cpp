#include <iostream>
#include <string>
#include <cmath>
#include "harvester.h"  
#include "map.h"

using namespace std;

// generate 1d-strategy for get_out maps
string Harvester::strat_1d() const {

	string p; // program
	int myX = myMap->getInitialPositionX();
	int myY = myMap->getInitialPositionY();
	//int dispX = myMap->gateX() - myX;
	//int dispY = myMap->gateY() - myY;
	int dimX = myMap->getDimX();
	//int dimY = myMap->getDimY();
	int mom_x = 0; // start stationary
	int mom_y = 0;
	int nextX = myX + mom_x;
	int nextY = myY + mom_y;
	//cout << "Gate position = (" << myMap->gateX() << "," << myMap->gateY() << ")" << endl;
	//cout << "Initial displacement = (" << dispX << "," << dispY << ")" << endl;

	// start moving right
	p.append("X");
	mom_x++;

	int stop = 0;
	while (stop == 0) {
		
		if (myX == (dimX-1)) nextX = 0; // at end of toriverse
		else  nextX = myX + mom_x;
		nextY = 0;

		if (myMap->survey(nextX, nextY) == '\\') { // gate
			p.append("x");
			mom_x--;
 			stop = 1;
		} else if (myMap->survey(nextX,nextY) == '@') { // black hole ahead
			p.replace(p.size()-1, 1, "X");
			p.append("x");
		} else if (myMap->survey(nextX,nextY) == '.' || myMap->survey(nextX,nextY) == '*') { // wait
			p.append("w");
		} else {
			stop = 1; cout << "***FAILSAFE*** at " << myX << endl;
		}
		myX = nextX; // move
		myY = nextY;
	}

	return p.append("e"); // exit
}
