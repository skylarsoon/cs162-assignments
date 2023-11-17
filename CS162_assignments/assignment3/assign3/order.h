#ifndef ORDER_H
#define ORDER_H 

#include <string>

using namespace std;

class Order
{
private:
	int id;
	string coffee_name;
	char coffee_size;
	int quantity;

public:
	//need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate
	Order();
	void set_id (const int new_id);
	void set_coffee_name (const string new_name);
	void set_coffee_size (const char new_coffee_size);
	void set_quantity (const int new_quantity);
	
	int get_id()const;
	string get_coffee_name()const;
	char get_coffee_size()const;
	int get_quantity()const;
};
#endif