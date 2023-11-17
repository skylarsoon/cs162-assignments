#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "event.h"
//#include "wumpus.h"

using namespace std;

class Room{
private:
	bool adventurer;
	Event* room_event;
public:
	Room();
	//~Room();
	Room(char c);

	bool get_adventurer();

	void set_adventurer(const bool adventurer_input);

	void set_event(Event*);
	Event* get_event();

};

#endif 