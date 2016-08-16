// reading a text file
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>  
#include <string>
using namespace std;

int main () {

 int x =0;
 int y =0;
 int harvpos_x = 1;
 int harvpos_y= 1;
 int harv_energy = 0;
 int energy_density = 0;
int lifetime = 0;

  string line;
  //ifstream Map ("map_pack_01/01_1d_001.map");
ifstream Map ("map_pack_01/01_get_out_001.map");
  if (Map.is_open())
  {
    getline (Map,line);
    cout << line << '\n';
	 int cur_pos =0;
     string temp;
     cur_pos = line.find("x") ;
     temp = line.substr(0,cur_pos);
     x = atoi(temp.c_str());
     temp = line.substr(cur_pos+1);
     y = atoi(temp.c_str());
	char array [x][y];
	for ( int i=0 ; i<y ; i++)
	{
	getline (Map,line);
		for( int j=0; j<x; j++)
		{
			array [i][j] = line.at(j);
		}
	 }
	 
	 cout<< "printing array" << endl;
	 for ( int i=0 ; i<y ; i++)
	{
		for( int j=0; j<x; j++)
		{
		cout << array [i][j]; 
		}
		cout << endl;
	}
	
	getline (Map,line);
     cur_pos = line.find(":") ;
     temp = line.substr(cur_pos+2);
     lifetime = atoi(temp.c_str());
     
	 
	 getline (Map,line);
     cur_pos = line.find(": ") ;
      temp = line.substr(cur_pos+2);
      energy_density= atoi(temp.c_str());

	 getline (Map,line);
	 cur_pos = line.find(":") ;
      temp = line.substr(cur_pos+2);
      harv_energy= atoi(temp.c_str());

	 getline (Map,line);
     cur_pos = line.find(": ") ;
	 string position;
     position = line.substr(cur_pos+2);
	 cur_pos = position.find(" ") ;
     temp = position.substr(0,cur_pos);
     harvpos_x = atoi(temp.c_str());
     temp = position.substr(cur_pos+1);
     harvpos_y = atoi(temp.c_str());

    Map.close();
  }
  else cout << "Unable to open file"; 

cout << "map size " << x <<","<<y<<endl;
cout << "lifetime" << lifetime << endl;
cout << "energy_density: " << energy_density << endl;
cout <<" harvester energy: " << harv_energy<< endl;
cout <<" harvester position: " << harvpos_x <<","<< harvpos_y << endl;

  return 0;
}


