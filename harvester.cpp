#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "harvester.h"
#include "map.h"  

Harvester::Harvester(Map &m) {

  // set initial conditions
  myMap = &m; // pointer to toriverse
  x = myMap->getInitialPositionX(); // read map initial position
  y = myMap->getInitialPositionY();
  E = myMap->getInitialEnergy();
  px = 0;
  py = 0;
  score = 0;
  alive = 1;
  status = "OK";
}

void Harvester::setProgram(string p) {


  // load program from file e.g. "map_name.hpg"
  if(p.find(".") == string::npos) program = p;  // load program from string e.g "XXwwwwwxxe"
  else {

    ifstream file(p.c_str());
    getline(file, program); // read program from file

  }

  // check valid program
  program = program.substr(0, program.find("e") + 1); // programs terminate with 'e' = exit command
  if(strlen(p.c_str()) == 0) die("INVALID PROGRAM");

}

// run entire program
void Harvester::execute() {
  for(unsigned int i(0); i < program.length() && alive; i++) {
    step(i); // perform ith command
  }
}

// write program on-the-fly
void Harvester::ai() {
  int n(0);
  while (alive) {
	step(n);
	n++;
  }
}

// execute nth command
void Harvester::step(int n) {

  // toriverse lifetime
  if(!myMap->getLife()) die("DESTROYED BY TORIVERSE COLLAPSE");
  else myMap->timestep(); // toriverse time step

  // check energy
  if(!E) die("DESTROYED BY ENERGY STARVATION");

  program[n] = command_maze();
  if (alive) cout << program[n] << ": "; // current command
  if (program[n] == 'e') cout << "TRANSMISSION TERMINATED" << endl;

  if (alive) {
    status = "OK";
    command(program[n]); // evaluate command (you might die)
  }
  if (alive) {
    move();
    interact(); // interact with toriverse (you might die)
    show(); // status report
  }
}


// evaluate command
void Harvester::command(char c) {

    if(c != 'w' && c != 'X' && c != 'x' && c != 'Y' && c != 'y' && c != 'e') {
      die("DESTROYED BY INVALID COMMAND");
    } else {
      if (c == 'e') exit(); // attempt to use an exit vortex
      if (c == 'X' ||  c == 'x' || c == 'Y' || c == 'y') impulse(c); // impulse
    }
}

// interact with map
void Harvester::interact() {

  if(myMap->survey(x,y) == '*') harvest(); // harvest energy packet
  if(myMap->survey(x,y) == '@') die("DESTROYED BY BLACK HOLE");
  if(myMap->survey(x,y) == ',') myMap->replace(x, y, '@'); // collapse unstable space to black hole (must come after black hole death)
}

// add current momentum to position
void Harvester::move() {
  x = myMap->getXtor(x + px);
  y = myMap->getYtor(y + py);
}

// impulse
void Harvester::impulse (char command) {

  if (command == 'X') px++;
  if (command == 'x') px--;
  if (command == 'Y') py++;
  if (command == 'y') py--;

  // toroidal geometry
  if(abs(px) == myMap->getDimX()) px = 0;
  if(abs(py) == myMap->getDimX()) py = 0;

  // lose energy
  E--;

}

void Harvester::exit() {

  if(px != 0 || py != 0) die("DESTROYED BY EXIT WHILE MOVING");
  if(myMap->survey(x,y) != '\\') die("DESTROYED BY EXIT NOT ON EXIT VERTEX");

  // check on exit vortex and stationary
  if(myMap->survey(x,y) == '\\' && px == 0 && py == 0) {
    score = E + myMap->getLife();
    status = "RETURNED HOME";
    alive = 0;
  }
}

// increase energy and remove energy packet from current location
void Harvester::harvest() {
  myMap->replace(x, y, '.');
  E = E + myMap->getEnergyDensity();
  status = "HARVESTING";
}

void Harvester::die(string obituary) {

  alive = 0;
  status = obituary;

  // destroy harvester

  // terminate map
}

void Harvester::show() const {

  cout << "[" << setw(2) << myMap->getLife() << "] "; // toriverse remaining lifetime
  cout << "(" << myMap->survey(myMap->getXtor(x-3),y) << myMap->survey(myMap->getXtor(x-2),y) << myMap->survey(myMap->getXtor(x-1),y) << // down periscope!
  "O" << myMap->survey(myMap->getXtor(x+1),y) << myMap->survey(myMap->getXtor(x+2),y) << myMap->survey(myMap->getXtor(x+3),y) << ") ";
  cout << "E = " << E;
  cout << "\tx = (" << x << ", " << y << ")";
  cout << "\tp = (" << px << ", " << py << ")";
  cout << "\tScore = " << score;
  cout << "\tStatus:\t" << status << endl;
}

// print map with harvester shown
void Harvester::showMap() const {

  for (int j = (myMap->getDimY()-1); j >= 0 ; j--) {

    for(unsigned int i=0; i<myMap->getDimX(); i++) {

      unsigned int temp = (j); // for unsigned integer
      if(temp == y && i == x) { cout << 'O'; } // if harvester is here, print O
      else { cout << myMap->getMap()[i][j]; } // otherwise print map contents

    }
    cout << endl;
  }
  show();
}

unsigned int Harvester::getX() const { return x; }
unsigned int Harvester::getY() const { return y; }
int Harvester::getPx() const { return px; }
int Harvester::getPy() const { return py; }
unsigned int Harvester::getScore() const { return score; }
string Harvester::getProgram() const { return program.c_str(); }
char Harvester::look(int dx, int dy) const { return myMap->survey(myMap->getXtor(x+dx),myMap->getXtor(y+dy)); }
