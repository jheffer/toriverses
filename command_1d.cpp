#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "harvester.h"
#include "map.h"  

char Harvester::command_1d () const {

	int started(0);
	unsigned int gateX = myMap->getGateX(); // gate position
	unsigned int gateY = myMap->getGateY();

	if(look(0,0) == '\\' && px == 0) return 'e'; // exit
	else if(look(0,0) == '\\' && px < 0) return 'X'; // stop
	else if(look(0,0) == '\\' && px > 0) return 'x';
	else if(look(0,0) == '\\' && px == -2) return 'X';
	else if(look(+1,0) == '\\' && px == -1) return 'X';

	else if(look(-1,0) == '\\' && px == 0 && !started) {
		started=1; return 'X';
	}

	// regulate speed
	else if(px > 1 && look(+1,0) != '@') return 'x';
	else if(px < -1 && look(-1,0) != '@') return 'X';

 	// jump @@ (moving right)
	else if(px == +2 && look(+1,0) == '@' && look(+2,0) == '@') return 'X'; // O@@..
	else if(look(-2,0) == '@' && look(-1,0) == '@' && px == +3) return 'x'; // @@O..
	else if(look(-3,0) == '@' && look(-4,0) == '@' && px == +2) return 'x'; // @@..O
	else if(look(+1,0) != '@' && look(+2,0) != '@' && look(+3,0) == '@' && look(+4,0) == '@' && px == +1) return 'X'; // O..@@
	else if(look(+1,0) != '@' && look(+2,0) != '@' && look(+3,0) == '@' && look(+4,0) == '@' && px == +2) return 'w'; // O..@@

 	// jump @@ (moving left)
	else if(look(-4,0) == '@' && look(-3,0) == '@' && look(-2,0) != '@' && look(-1,0) != '@' && px == -1) return 'x'; // @@..O -> accelerate
	else if(look(-4,0) == '@' && look(-3,0) == '@' && look(-2,0) != '@' && look(-1,0) != '@' && px == -2) return 'w'; // @@..O -> accelerate
	else if(look(+1,0) == '@' && look(+2,0) == '@' && px == -2) return 'x'; // @@O -> jump
	else if(look(+1,0) == '@' && look(+2,0) == '@' && px == -3) return 'X'; // O@@ -> deccelerate
	else if(look(+3,0) == '@' && look(+4,0) == '@' && px == -2) return 'X'; // O..@@ -> deccelerate

	// jump @
	else if(abs(px) == 2 && ( look(-1,0) == '@' || look(+1,0)!='@' )) return 'w';
	else if(px == +1 && look(+1,0) == '@') return 'X';
	else if(px == -1 && look(-1,0) == '@') return 'x';
	else if(look(+1,0) == '@' && px == -2 && look(-1,0) != '@') return 'X';

	// run away
	else if(look(+1,0) == '@' && look(+2,0) == '@' && look(+3,0) == '@') return 'x';
	else if(px >= 0 && look(+1,0)=='.'&&look(+2,0)=='.'&&look(+3,0)=='.'&&look(+4,0)=='.'&&look(+5,0)=='.'&&look(+6,0)=='.'&&look(+7,0)=='.'&&look(+8,0)=='.'&&look(+9,0)=='.'&&look(+10,0)=='.'&&look(+11,0)=='.'&&look(+12,0)=='.'&&look(+13,0)=='.'&&look(+14,0)=='.'&&look(+15,0)=='.'&&look(+16,0)=='.'&&look(+17,0)=='.') return 'x';

	else return 'w';
}
