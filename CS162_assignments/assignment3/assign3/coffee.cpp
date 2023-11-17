#include <iostream>
#include "coffee.h"
#include <fstream>

using namespace std;


Coffee::Coffee(){
	this -> name = "No coffee here yet.";
	this -> small_cost = 2;
	this -> medium_cost = 3;
	this -> large_cost = 4;
	this -> revenue = 0;
}

void Coffee::set_name (const string new_name){
	this -> name = new_name;
}

void Coffee::set_small_cost(const float new_small_cost){
	this -> small_cost = new_small_cost;
}

void Coffee::set_medium_cost(const float new_medium_cost){
	this -> medium_cost = new_medium_cost;
}

void Coffee::set_large_cost(const float new_large_cost){
	this -> large_cost = new_large_cost;
}

string Coffee::get_name() const{
	return this -> name;
}

void Coffee::print_name() const{
	cout << this -> name;
}

float Coffee::get_small_cost () const{
	return this -> small_cost;
}

float Coffee::get_medium_cost () const{
	return this -> medium_cost;
}

float Coffee::get_large_cost () const{
	return this -> large_cost;
}

void Coffee::print_coffee() const{
	cout << "Name: " << this -> name << endl;
	cout << "Small cost: " << this -> small_cost << endl;
	cout << "Medium cost: " << this -> medium_cost << endl;
	cout << "Large cost: $" << this -> large_cost << endl << endl;
} //print the coffee out

void Coffee::load_a_single_coffee(ifstream &fin){
	fin >> this -> name;
	fin >> this -> small_cost;
	fin >> this -> medium_cost;
	fin >> this -> large_cost;
}

void Coffee::set_revenue(const float new_revenue){
	this -> revenue += new_revenue;
}

float Coffee::get_revenue () const{
	return this -> revenue;
}