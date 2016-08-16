#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "harvester.h"
#include "map.h"  

// L-shape (no toroid)
// Move to gate horizontally then vertically
char Harvester::command_2d () const {

	unsigned int gateX = myMap->getGateX(); // gate position
	unsigned int gateY = myMap->getGateY();

	if(myMap->survey(x,y) == '\\' && px == 0 && py == 0) return 'e'; // exit

	// slow down if on exit
	else if(x == gateX && px > 0) return 'x';
	else if(x == gateX && px < 0) return 'X';
	else if(y == gateY && py > 0) return 'y';
	else if(y == gateY && py < 0) return 'Y';

	// move towards gate
	else if(x > gateX && px >= 0) return 'x';
	else if(x < gateX && px <= 0) return 'X';

	// horizontal motion	1795098

	// jump @	2169755
	else if(look(+1,0) == '@' && px == 1) return 'X'; // .O@ jump (moving right)
	else if(look(-1, 0) == '@' && px == 2 && look(+1,0) != '@') return 'x'; // @O. slow down (moving right)
	else if(look(-1,0) == '@' && px == -1) return 'x'; // @O. jump (moving left)
	else if(look(+1,0) == '@' && px == -2 && look(-1,0) != '@') return 'X'; // .O@ slow down (moving left)

	else if(look(-1,0) == '@' && look(+1,0) == '@' && abs(px) == 2) return 'w'; // @O@

 	// jump @@ (moving right)
	else if(look(+1,0) != '@' && look(+2,0) != '@' && look(+3,0) == '@' && look(+4,0) == '@' && px == +1) return 'X'; // O..@@
	else if(look(+1,0) == '@' && look(+2,0) == '@' && px == +2) return 'X'; // O@@..
	else if(look(-2,0) == '@' && look(-1,0) == '@' && px == +3) return 'x'; // @@O..
	else if(look(-3,0) == '@' && look(-4,0) == '@' && px == +2) return 'x'; // @@..O

 	// jump @@ (moving left)
	else if(look(-4,0) == '@' && look(-3,0) == '@' && look(-2,0) != '@' && look(-1,0) != '@' && px == -1) return 'x'; // @@..O -> accelerate
	else if(look(+1,0) == '@' && look(+2,0) == '@' && px == -2) return 'x'; // @@O -> jump
	else if(look(+1,0) == '@' && look(+2,0) == '@' && px == -3) return 'X'; // O@@ -> deccelerate
	else if(look(+3,0) == '@' && look(+4,0) == '@' && px == -2) return 'X'; // O..@@ -> deccelerate

	// vertical
	if(x == gateX && abs(px) == 0) {

		// jump @	2498218
		if(look(0,+1) == '@' && py == 1) return 'Y'; // .O@ jump (moving up)
		else if(look(0,-1) == '@' && py == 2) return 'y'; // @O. slow down (moving up)
		else if(look(0,-1) == '@' && py == -1) return 'y'; // @O. jump (moving down)
		else if(look(0,+1) == '@' && py == -2) return 'Y'; // .O@ slow down (moving down)

		else if(look(-1,0) == '@' && look(+1,0) == '@' && abs(py) == 2 ) return 'w'; // @O@

	 	// jump @@ (moving up)
		else if(look(0,+1) != '@' && look(0,+2) != '@' && look(0,+3) == '@' && look(0,+4) == '@' && py == +1) return 'Y'; // O..@@
		else if(look(0,+1) == '@' && look(0,+2) == '@' && py == +2) return 'Y'; // O@@..
		else if(look(0,-2) == '@' && look(0,-1) == '@' && py == +3) return 'y'; // @@O..
		else if(look(0,-3) == '@' && look(0,-4) == '@' && py == +2) return 'y'; // @@..O

	 	// jump @@ (moving down)
		else if(look(0,-4) == '@' && look(0,-3) == '@' && look(0,-2) != '@' && look(0,-1) != '@' && py == -1) return 'y'; // @@..O -> accelerate
		else if(look(0,+1) == '@' && look(0,+2) == '@' && py == -2) return 'y'; // @@O -> jump
		else if(look(0,+1) == '@' && look(0,+2) == '@' && py == -3) return 'Y'; // O@@ -> deccelerate
		else if(look(0,+3) == '@' && look(0,+4) == '@' && py == -2) return 'Y'; // O..@@ -> deccelerate

		// move towards gate
		if(y > gateY && py >= 0) return 'y';
		else if(y < gateY && py <= 0) return 'Y';
	}

	return 'w';
}
