#include <iostream>
#include <fstream>
#include "menu.h"

using namespace std;

Menu::Menu(){
	//initialize variables
	this -> num_coffee = 0;
	this -> coffee_arr = NULL;
}

Menu::Menu(int size){
	//initialize variables
	this -> num_coffee = size;
	this -> coffee_arr = new Coffee [size];
}

Menu::~Menu(){
	//cout << "Destructor called" << endl;
	if (this -> coffee_arr != NULL){
		delete [] this -> coffee_arr;
		coffee_arr = NULL;
	}
}

Menu& Menu::operator = (const Menu &old){
	//cout << "AOO Called" << endl;
	this -> num_coffee = old.num_coffee;
	if (this -> coffee_arr != NULL){
		delete [] this -> coffee_arr;
	}
	this -> coffee_arr = new Coffee [this -> num_coffee];
	for (int i = 0; i < this -> num_coffee; i++){
		this -> coffee_arr[i] = old.coffee_arr[i];
	}

	return *this;
}

Menu::Menu(const Menu& old){
	//cout << "CC called" << endl;
	this -> num_coffee = old.num_coffee;
	
	//deep copy
	this -> coffee_arr = new Coffee [this -> num_coffee];
	for(int i = 0; i < this -> num_coffee; i++){
		this -> coffee_arr[i] = old.coffee_arr[i];
	}
}

Coffee Menu::get_coffee_array(int index) const{
	return this -> coffee_arr[index];
}

int Menu::get_coffee_revenue(int index) const{
	return this -> get_coffee_array(index).get_revenue();
}

string Menu::get_coffee_name(int index) const{
	return this -> get_coffee_array(index).get_name();
}

float Menu::get_coffee_small(int index) const{
	return this -> get_coffee_array(index).get_small_cost();
}

float Menu::get_coffee_medium(int index) const{
	return this -> get_coffee_array(index).get_medium_cost();
}

float Menu::get_coffee_large(int index) const{
	return this -> get_coffee_array(index).get_large_cost();
}

int Menu::get_num_coffee() const{
	return this -> num_coffee;
}

void Menu::load_menu(ifstream &fin){
	fin >> this -> num_coffee;
	this -> coffee_arr = new Coffee[this -> num_coffee];

	for (int i = 0; i < this -> num_coffee; i++){
		this -> coffee_arr[i].load_a_single_coffee(fin);
	}
}

void Menu::get_new_coffee_info(){
	Coffee new_coffee;
	string new_name;
	float new_small_cost;
	float new_medium_cost;
	float new_large_cost;

	cout << "Enter coffee name (in one word): ";
	cin >> new_name;
	new_coffee.set_name(new_name);

	cout << "Enter small cost: ";
	cin >> new_small_cost;
	new_coffee.set_small_cost(new_small_cost);

	cout << "Enter medium cost: ";
	cin >> new_medium_cost;
	new_coffee.set_medium_cost(new_medium_cost);

	cout << "Enter large cost: ";
	cin >> new_large_cost;
	new_coffee.set_large_cost(new_large_cost);

	this -> add_coffee(new_coffee);
}


void Menu::add_coffee(Coffee &c){
	//create temporary array of length +1 
	Coffee* temp_array = new Coffee[this -> num_coffee + 1];

	//copy from old array to temp array
	for(int i = 0; i < this -> num_coffee; i++){
		temp_array[i] = this -> coffee_arr[i];
	}

	//allocate new coffee to end of array
	temp_array[this -> num_coffee] = c;

	//free current array
	delete [] this -> coffee_arr;

	this -> coffee_arr = temp_array;

	//increment numbers of coffee
	++this -> num_coffee;

	this -> remake_menu();
	
}

void Menu::get_item_to_remove(){
	int num; 
	for(int i = 0; i < this -> num_coffee; i++){
		cout << i + 1 << ". " << this -> coffee_arr[i].get_name() << endl;
	}
	do{
		cout << "What item do you want to remove (make sure to enter the integer): ";
		cin >> num;
	} while (num > this -> num_coffee - 1 || num < 1);
	this -> remove_from_menu(num - 1);	
	

}


void Menu::remove_from_menu(int index_of_coffee_on_menu){
	//when at index, shift everything down one after

	for(int j = index_of_coffee_on_menu; j < this -> num_coffee -1; j++){
		this -> coffee_arr[j] = this -> coffee_arr[j+1];
	}

	this -> num_coffee-=1;

	this -> remake_menu();
}

void Menu::remake_menu(){
	ofstream fout;
	fout.open("menu.txt", ios::trunc);

	if(!fout.is_open()){
		cout << "Error, unable to open file!" << endl;
		return;
	}

	fout << this -> num_coffee << endl;
	for(int i = 0; i < num_coffee; i++){
		fout << this -> coffee_arr[i].get_name() << " ";
		fout << this -> coffee_arr[i].get_small_cost() << " ";
		fout << this -> coffee_arr[i].get_medium_cost() << " ";
		fout << this -> coffee_arr[i].get_large_cost() << " ";
		fout << endl;
	}

	cout << "Menu remade successfully." << endl;

}

void Menu::print_menu(){
	for (int i = 0; i < this -> num_coffee; i++){
		this -> coffee_arr[i].print_coffee();
		cout << "*******************" << endl;
	}
}

Coffee Menu::search_coffee_by_name(string name){
	Coffee default_name;
	for(int i = 0; i < this -> num_coffee; i++){
		if (this -> coffee_arr[i].get_name() == name){
			return coffee_arr[i];
		}
	}
	cout << "Sorry, we don't have that product at the moment." << endl;
	return default_name;
}

void Menu::print_lower_prices(float upper_bound){
	int counter = 0;
	for(int i = 0; i < this -> num_coffee; i++){
		if (this -> coffee_arr[i].get_small_cost() <= upper_bound){
			cout << this -> coffee_arr[i].get_name() << endl;
			cout << " - Small: " << this -> coffee_arr[i].get_small_cost() << endl;
			counter++;

			if (this -> coffee_arr[i].get_medium_cost() <= upper_bound){
				cout << " - Medium: " << this -> coffee_arr[i].get_medium_cost() << endl;
			}
			if (this -> coffee_arr[i].get_large_cost() <= upper_bound){
				cout << " - Large: " << this -> coffee_arr[i].get_large_cost() << endl;
			}
		}
	}
	if(counter < 1){
		cout << "Sorry, we don't currently have any items within your budget.\n" << endl;
	}

}

Menu Menu::search_coffee_by_price(float upper_bound){
	int numbers_of_coffee_in_range = 0;
	for(int i = 0; i < this -> num_coffee; i++){
		if (this -> coffee_arr[i].get_small_cost() <= upper_bound){
			numbers_of_coffee_in_range++;
		}
	}
	//make array to hold indices
	//Coffee* temp_array = new Coffee[numbers_of_coffee_in_range];
	int counter = 0;
	Menu temp_menu(numbers_of_coffee_in_range);
	for(int i = 0; i < this -> num_coffee; i++){
		if (this -> coffee_arr[i].get_small_cost() <= upper_bound){
			temp_menu.coffee_arr[counter] = this -> coffee_arr[i];
			counter++;
		}
	}
	print_lower_prices(upper_bound);

	return temp_menu;
}

void Menu::print_menu_names(){
	for(int i = 0; i < this -> num_coffee; i++){
		cout << i+1 << ". " << this -> coffee_arr[i].get_name() << endl;
	}
}

void Menu::add_to_coffee_revenue(int index, float addition){
	this -> coffee_arr[index].set_revenue(addition);
}

/*
void Menu::get_a_coffee_from_array(int index){
	this -> get_coffee_array()
}
*/
