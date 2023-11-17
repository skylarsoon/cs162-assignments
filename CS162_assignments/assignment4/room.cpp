#include "room.h"

Room::Room(){
	this -> adventurer = false;
	this -> room_event = NULL;
}

/*
Room::~Room(){
	cout << "~Room()" << endl;
	delete this -> room_event;
}
*/


bool Room::get_adventurer(){
	return this -> adventurer;
}

void Room::set_adventurer(const bool adventurer_input){
	this -> adventurer = adventurer_input;
}

void Room::set_event(Event* event){
	this -> room_event = event;
}

Event* Room::get_event(){
	return this -> room_event;
}