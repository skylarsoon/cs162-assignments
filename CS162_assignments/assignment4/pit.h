#ifndef PIT_H
#define PIT_H

#include <iostream>
#include "event.h"

using namespace std;

class Pit: public Event{
private:

public:

	char get_symbol();
	void print_percept();
};

#endif 