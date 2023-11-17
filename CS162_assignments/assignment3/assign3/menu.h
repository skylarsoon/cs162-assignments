#ifndef MENU_H
#define MENU_H 

#include <string>
#include <fstream>
#include "coffee.h"

using namespace std;

class Menu {
  private:
    int num_coffee;
    Coffee* coffee_arr;
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    //need to use 'const' when appropriate

    Menu();//menu constructor
    Menu(int size); //non default constructor
    ~Menu(); //menu destructor
    Menu& operator = (const Menu &); // assignment operator overload
    Menu(const Menu&); //copy constructor

    Coffee get_coffee_array(int index) const; //gets coffee object
    int get_coffee_revenue(int index) const; // gets revenue of a coffee
    string get_coffee_name(int index) const;
    float get_coffee_small(int index) const;
    float get_coffee_medium(int index) const;
    float get_coffee_large(int index) const;
    int get_num_coffee() const;

    // Suggested functions:
    Coffee search_coffee_by_name(string name); 
    Menu search_coffee_by_price(float upper_bound); 
    void print_lower_prices(float upper_bound);
    void add_to_menu(Coffee& coffee_to_add); //add a coffee object into the Menu
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu
    

    void load_menu(ifstream &fin); //loads menu from file
    void add_coffee(Coffee &c); //adds new space to array and adds new coffee to end
    void print_menu(); //print menu to screen
    void remake_menu(); // prints to file
    void get_item_to_remove();
    void get_new_coffee_info(); //gets new coffee info from user
    void print_menu_names(); //prints menu names and numbers for selection
    void add_to_coffee_revenue(int index, float addition);
    // feel free to add more member functions
};

#endif