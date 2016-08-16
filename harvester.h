#ifndef HARVESTER_h
#define HARVESTER_h

#include <iostream>
#include <string>
#include <utility>
#include "map.h"

using namespace std;

class Harvester {

public:

  // creator
  Harvester(Map &m); // program can be "Xwwe" or "path/map_name.hpg"

  // actions
  void setProgram(string p);
  void execute(); // run entire program
  void ai(); // figure out a program
  void step(int n); // step through program
  void command(char command); // command = {w,X,x,Y,y,e}
  void interact(); // check energy level and interact with map
  void move(); // change position according to momentum
  void harvest(); // harvest an energy packet from map
  void exit(); // attempt to use an exit vortex
  void impulse(char command);
  void die(string obituary); // destroy harvester (reason given) and quit map

  // strategies
  char command_1d() const;
  char command_2d() const; // get_out salesman
  char command_maze() const;

  // get harvester info
  void show() const; // print status and score to screen
  void showMap() const; // print map with current location
  unsigned int getX() const; // position
  unsigned int getY() const;
  int getPx() const; // momentum
  int getPy() const;
  unsigned int getScore() const;
  string getStatus() const;
  string getProgram() const;
  char look(int dx, int dy) const; // myMap->survey(x+dx, y+dx) with toroid geometry considered

private:

  unsigned int x; //  position (x,y)
  unsigned int y;
  int px; // momentum (p_x,p_y)
  int py;
  unsigned int E; // energy
  Map * myMap; // pointer to current Toriverse
  string status;
  string program; // program e.g. 'Xwwwwe'
  unsigned int score;
  unsigned int alive;

};

#endif
