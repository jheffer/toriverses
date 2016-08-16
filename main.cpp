#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>  
#include <string> 
#include "harvester.h"  
#include "map.h"

using namespace std;

// Toriverse simulator
int main () 
{
  // settings
  string mapPack("01");		// Map pack number
  string mapType("perfect");		// 1d (250) get_out (310) salesman perfect unicursal
				// 1d: 181 193 194 219 221 222 241 235 237 224 segfault
				// perfect_cover
  int totalScore(0);

  // loop through map files
  for (int i = 1; i <= 1; i++) {

    stringstream mapPath, progPath;
    mapPath << "map_pack_"<< mapPack << "/" << mapPack << "_" << mapType << "_" << setw(3) << setfill('0') << i << ".map";
    progPath << "hpg_" << mapPack << "/" << mapPack << "_" << mapType << "_" << setw(3) << setfill('0') << i << ".hpg";

    // create toriverse
    Map m1(mapPath.str().c_str());
    //cout << m1.gateX() << "," << m1.gateY() << endl;
    m1.show();

    Harvester h1(m1); // launch into world	// progPath.str().c_str()
    //string program(h1.strat_get_out());
    //h1.setProgram(program); // set strategy

    h1.showMap(); // initial map
    //cout << "Trying program: " << program << endl;
    
    //h1.execute(); // loop through program
    h1.ai(); // go your own way
    totalScore = totalScore + h1.getScore();

    // save program
    ofstream progFile(progPath.str().c_str());
    progFile << h1.getProgram();
    progFile.close();

    h1.showMap(); // final map
    cout << setw(3) << right << i << setw(8) << h1.getScore() << "| ";
    if(i % 10 == 0) cout << endl;
  }
  cout << "\nTotal score = " << totalScore << endl;

  return 0;
}
