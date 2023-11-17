/******************************************************
** Program: driver.cpp (wumpus project)
** Author: Skylar Soon
** Date: 05/30/2023
** Description: Play as an adventurer and get gold, kill the wumpus, and escape to win!
** Input: Initial input settings, and WASD directions
** Output: Percepts and descriptions of what is happening
******************************************************/

#include "game.h"
#include "room.h"

int main(){
	srand(time(NULL));
	Game g;
	g.prompt_user_mode();
	g.clear_memory();

	cout << "Thanks for playing :) " << endl;
	
	return 0;
}


/*
TO DO:
//makefile
//edit grid
//ncurses
//make player die
//make game end when player die
make play again
//print normal grid
//make option for normal grid
clean up constructor/destructor couts
error check inputs
//fix couts for input
delete gold once picked up
//game ends once arrows are empty
*/