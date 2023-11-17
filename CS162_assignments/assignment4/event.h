#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

class Event{
private:
	
public:
	//~Event();
	virtual char get_symbol() = 0;
	virtual void print_percept() = 0;
};

#endif 