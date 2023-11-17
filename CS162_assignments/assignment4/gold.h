#ifndef GOLD_H
#define GOLD_H

#include <iostream>
#include "event.h"

using namespace std;

class Gold: public Event{
private:

public:
	char get_symbol();
	void print_percept();
};

#endif 