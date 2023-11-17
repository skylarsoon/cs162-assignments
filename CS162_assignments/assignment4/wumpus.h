#ifndef WUMPUS_H
#define WUMPUS_H

#include <iostream>
#include "event.h"

using namespace std;

class Wumpus: public Event{
private:

public:
	char get_symbol();
	void print_percept();
};

#endif 