#include <string>
#include <iostream>
#include <fstream>
#include "menu.h"
#include "order.h"
#include "shop.h"

using namespace std;

Order::Order(){
	this -> id = 123;
	this -> coffee_name = "Default coffee";
	this -> coffee_size = 'S';
	this -> quantity = 1;
}

void Order::set_id(const int new_id){
	this -> id = new_id;
}

void Order::set_coffee_name(const string new_name){
	this -> coffee_name = new_name;
}

void Order::set_coffee_size(const char new_coffee_size){
	this -> coffee_size = new_coffee_size;
}

void Order::set_quantity(const int new_quantity){
	this -> quantity = new_quantity;
}

int Order::get_id() const{
	return this -> id;
}

string Order::get_coffee_name() const{
	return this -> coffee_name;
}

char Order::get_coffee_size() const{
	return this -> coffee_size;
}

int Order::get_quantity() const{
	return this -> quantity;
}


