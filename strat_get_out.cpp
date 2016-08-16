#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include "harvester.h"  
#include "map.h"

using namespace std;

// get_out map strategy
string Harvester::strat_get_out() const {

    string p; // program
    int myX = myMap->getInitialPositionX();
    int myY = myMap->getInitialPositionY();
    int dispX = myMap->gateX() - myX;
    int dispY = myMap->gateY() - myY;
    //int dimX = myMap->getDimX();
    //int dimY = myMap->getDimY();

    //cout << "Gate position = (" << myMap->gateX() << "," << myMap->gateY() << ")" << endl;
    //cout << "Initial displacement = (" << dispX << "," << dispY << ")" << endl;

  // Basic L, no toroid		326614 points
  // Horizontal motion
  if (dispX > 0) {  // go right

	p.append("X");
	for(int i=1; i<abs(dispX); i++) p.append("w");
	p.append("x");

  } else if (dispX < 0 ) { // go left

	p = p + "x";
	for(int i=1; i<abs(dispX); i++) p.append("w");
	p.append("X");

  }

  // Vertical motion
  if (dispY > 0) {  // go up

	p .append("Y");
	for(int i=1; i<abs(dispY); i++) p.append("w");
	p.append("y");

  } else if (dispY < 0 ) { // go down

	p = p + "y";
	for(int i=1; i<abs(dispY); i++) p.append("w");
	p.append("Y");

  }

  // Basic L toroid
  // Horizontal motion
  /*if (dispX == 0); // go straight up
  else if ((dispX > 0 && abs(dispX) <= dimX/2)|| ( dispX < 0 && abs(dispX) <= dimX ) ) { // move right

      p = p + "X"; // go
      for (int i = 1; i < abs(dispX); i++) p = p + "w"; // wait
      p = p + "x"; // stop

  } else if ((dispX < 0 && abs(dispX) > dimX/2) || ( dispX > 0 && abs(dispX) <= dimX ) ) { // move left

      p = p + "x"; // go

      // wait
      if (abs(dispX) <= dimX/2) { // no toroidal motion
        for (int i = 1; i < abs(dispX); i++) p = p + "w";
      } else { // toroidal motion
        for (int i = 1; i < abs(myX + (dimX - myMap->gateX())); i++) p = p + "w";
      }
      p = p + "X"; // stop
 
 }*/

  // Vertical motion
  /*if (dispY == 0); // no Y motion
  else if ((dispY > 0 && abs(dispY) <= dimY/2)|| ( dispY < 0 && abs(dispY) <= dimY ) ) { // move up
 
      p = p + "Y"; // go
      for (int i = 1; i < abs(dispY); i++) p = p + "w"; // wait
      p = p + "y"; // stop

  } else if ((dispY < 0 && abs(dispY) > dimY/2) || ( dispY > 0 && abs(dispY) <= dimY ) ) { // move down
 
      p = p + "y"; // go
      for (int i = 1; i < abs(dispY); i++) p = p + "w"; // wait
      p = p + "Y"; // stop
 
  }*/

  // Diagonial line, no toroid
  /*int dist = sqrt(pow(dispX,2) + pow(dispY,2)); // distance to exit
  pair<int,int> momentum = make_pair(0,0);
  // Horizontal motion
  if (dispX > 0) { // right
	p.append("X");
	momentum.first = 1;
  }
  else if (dispX < 0 ) { // left
	p.append("x");
	momentum.first = -1;
  }
  // Vertical motion
  if (dispY > 0) { // up
	p.append("Y");
	momentum.second = 1;
  }
  else if (dispY < 0 ) { // down
	p.append("y");
	momentum.second = -1;
  }

  for(int i=1; i<(dist-1); i++) p.append("w"); // wait
  if(momentum.second > 0) p.append("y"); // stop
  if(momentum.second < 0) p.append("Y");
  if(momentum.first > 0) p.append("x");
  if(momentum.first < 0) p.append("X");
  */
  return p.append("e"); // exit
}
