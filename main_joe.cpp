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
  int totalScore(0);

  // settings
  string mapPack("01");		// Map pack number
  string mapType("1d");		// 1d (250) get_out (310) salesman (250) perfect unicursal
					// perfect_cover (300)
					// salesman_pay_rise (300)
					// SEGFAULT 1d: 181 193 194 219 221 222 241 235 237 224
  // loop through map files
  for (int i = 1; i <= 50; i++) {

    stringstream mapPath, progPath;
    mapPath << "maps/" << mapPack << "_" << mapType << "_" << setw(3) << setfill('0') << i << ".map";
    progPath << "programs/" << mapPack << "_" << mapType << "_" << setw(3) << setfill('0') << i << ".hpg";

    // create toriverse and harvester
    Map m1(mapPath.str().c_str());
    Harvester h1(m1);

    // run mission
    //h1.setProgram("Ywwwwwwwwwwwwwwwwwwwwwwe");
    //cout << h1.getProgram() << endl;
    //h1.execute();
    h1.ai();

    // results
    totalScore = totalScore + h1.getScore();
    ofstream progFile(progPath.str().c_str());
    progFile << h1.getProgram();
    progFile.close();

    // print results
    cout << setw(4) << left << i << setw(8) << h1.getScore() << h1.getStatus() << endl;
  }
  cout << "\nTotal score = " << totalScore << endl;

  return 0;
}
