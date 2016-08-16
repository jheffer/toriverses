#ifndef MAP_h
#define MAP_h

#include <vector>

#include "harvester.h"

using namespace std;

// Toriverse class
class Map {

public:

  Map(string filename);  // load .map file
  void show(); // print map to screen
  void timestep(); // time step
                   // also evalute map at current time
                   // i.e. check if any lifetime remains before Toriverse collapses
  char survey(int x, int y) const; // what's at position loc(x,y)?
  void replace(int x, int y, char feature); // update a location e.g replace * with . for harvesting
                                      // returns energy density
  //void collapse(); // collapse toriverse, destroy toriverse and everything in it
  unsigned int getLife() const; // return remaining lifetime
  unsigned int getEnergyDensity() const;
  unsigned int getInitialPositionX() const; // return initial position
  unsigned int getInitialPositionY() const;
  unsigned int getInitialEnergy() const; // return initial energy
  unsigned int getDimX() const;
  unsigned int getDimY() const;
  unsigned int gateX() const; // search map for a gate
  unsigned int gateY() const;
  unsigned int getGateX() const; // return variables
  unsigned int getGateY() const;
  vector<vector<char> > getMap() const;
  unsigned int getXtor(int x) const; // fix beyond-toroid coordinates
  unsigned int getYtor(int y) const;

private:

  unsigned int dimX;
  unsigned int dimY;
  vector<vector<char> > map; // the map itself, dim_x * dim_y char array
  unsigned int life ; // remaining lifetime
  unsigned int energyDensity; // energy of each packet
  unsigned int initialEnergy; // initial harvester energy E_0
  unsigned int initialPositionX;
  unsigned int initialPositionY;
  unsigned int gatePosX;
  unsigned int gatePosY;

};

#endif
