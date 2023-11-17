#ifndef BATS_H
#define BATS_H

#include <iostream>
#include "event.h"

using namespace std;

class Bats: public Event{
private:

public:

	char get_symbol();
	void print_percept();
};

#endif 