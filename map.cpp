#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>  
#include <string>

using namespace std;

#include "harvester.h"
#include "map.h"  

//constructor
Map::Map(string filename) 
{
	string line;
	ifstream Map (filename.c_str());
	if (Map.is_open()){

		// toriverse properties (dimX, dimY) e.g. 6x5
		getline (Map,line);
		int cur_pos =0;
	    	string temp;
		cur_pos = line.find("x") ;
		temp = line.substr(0,cur_pos);
		dimX = atoi(temp.c_str());
		temp = line.substr(cur_pos+1);
		dimY = atoi(temp.c_str());

		// map loading

		// make the vector the right size for the map

		map.resize(dimX); // width i.e. number of vectors (one vector per column)
		//cout << "***Flag A***" << endl;

		// fill map with empty columns
		for (unsigned int i=0 ; i < dimX ; i++){
			//cout << "***Flag B (i = " << i << ")***" << endl;
			vector<char> newColumn;
			newColumn.resize(dimY);
                        map.at(i) = newColumn;
			//cout << "***Flag C***" << endl;
		}

		//cout << "***Flag D***" << endl;		

		// fill vectors by reading map row-by-row
		for (int j = (dimY-1) ; j >= 0 ; j--) { // j = row index
			getline(Map,line);
			for(unsigned int i=0; i < dimX; i++){ // i = column index
				//cout << "[" << i << "," << j << "]";
				//vector<char>::iterator it;
				//it = map.at(i).at(j); // iterator at end
				//map.at(i).insert(it, line.at(j)); //line.at((dimY-1)-j)
				map.at(i).at(j) = line.at(i);
				//map.at(i).at(j) = 'A';
				//cout << line.at(i);
				//cout << "[" << i << "," << ((dimY-1)-j) << "]";
			}
		//cout << endl;
		}

		//cout << "***Flag E***" << endl;

		// lifetime
		getline (Map,line);
		cur_pos = line.find(":") ;
		temp = line.substr(cur_pos+2);
		life = atoi(temp.c_str());

		// energy density
		getline (Map,line);
		cur_pos = line.find(": ") ;
		temp = line.substr(cur_pos+2);
		energyDensity= atoi(temp.c_str());

		// initial energy
		getline (Map,line);
		cur_pos = line.find(":") ;
		initialEnergy= atoi(line.substr(cur_pos+2).c_str());

		// initial position
		getline (Map,line);
		cur_pos = line.find(": ") ;
		string position;
		position = line.substr(cur_pos+2);
		cur_pos = position.find(" ") ;
		temp = position.substr(0,cur_pos);
		initialPositionX = atoi(temp.c_str());
		temp = position.substr(cur_pos+1);
		initialPositionY = atoi(temp.c_str()); 

		// gate position
		gatePosX = gateX();
		gatePosY = gateY();

		// close file
		Map.close();
       	}
}

void Map::show() {

  cout << dimX << "x"<< dimY << " toriverse with " << life << " lifetime and ";
  cout << energyDensity << " energy density." << endl;

  for (int j = (dimY-1); j >= 0 ; j--)
    {
      for(unsigned int i=0; i<dimX; i++) {
        cout << map[i][j];
        //cout << "(" << i << "," << j << ")";
      }
      cout << endl;
    }

  cout << "Harvester starts with " << initialEnergy << " energy at (";
  cout << getInitialPositionX()<< ","<< getInitialPositionY() << ")" << endl;

}

unsigned int Map::getLife() const {
	return life;
}

unsigned int Map::getInitialEnergy()  const {
	return initialEnergy ;
}

unsigned int Map::getInitialPositionX()  const {
	return initialPositionX; 
}

unsigned int Map::getInitialPositionY()  const {
	return initialPositionY; 
}


unsigned int Map::getDimX() const{
  return dimX;
}

unsigned int Map::getDimY() const {
  return dimY;
}

void Map::timestep() {
  if(life > 0){
      life--;
  }
  if(life == 0){
    // toriverse collapse
  }
}

char Map::survey(int x, int y) const {
  return map.at(x).at(y);
}


void Map::replace(int x, int y, char feature) {
  map.at(x).at(y) = feature;
  //map.at(x).assign(y, feature);
}

vector<vector<char> > Map::getMap() const {
  return map;
}

unsigned int Map::getEnergyDensity() const {
  return energyDensity;
}

unsigned int Map::gateX() const {

  for (unsigned int j = 0; j < dimY ; j++) {
    for(unsigned int i = 0; i < dimX; i++) {
      if (map[i][j] == '\\') return i;
    }
  }
  return -1;
}

unsigned int Map::gateY() const {

  for (unsigned int j = 0; j < dimY ; j++) {
    for(unsigned int i = 0; i < dimX; i++) {
      if (map[i][j] == '\\') return j;
    }
  }
  return -1;
}

// toroidal geometry
unsigned int Map::getXtor(int x) const {

  if(x < 0)		return x + dimX;
  else if(abs(x) >= dimX)	return x % dimX;
  else return x;

}

// toroidal geometry
unsigned int Map::getYtor(int y) const {

  if(y < 0)			return y + dimY;
  else if(abs(y) >= dimY)	return y % dimY;
  else return y;
}

unsigned int Map::getGateX() const { return gatePosX; }
unsigned int Map::getGateY() const { return gatePosY; }
