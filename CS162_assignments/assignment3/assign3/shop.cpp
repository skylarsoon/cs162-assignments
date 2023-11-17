#include <string>
#include <iostream>
#include <fstream>
#include "menu.h"
#include "order.h"
#include "shop.h"

using namespace std;

Shop::Shop(){
	this -> m;
	this -> phone = "8081231234";
	this -> address = "Skylar Land";
	this -> revenue = 0;
	this -> order_arr = NULL;
	this -> num_orders = 0;
}


Shop::~Shop(){
	//cout << "Destructor called" << endl;
	if (this -> order_arr != NULL){
		delete [] this -> order_arr;
		this -> order_arr = NULL;
	}
}


void Shop::load_data(){
	ifstream fin; 

	//gets menu
	fin.open("menu.txt");

	if(!fin.is_open()){
		cout << "Error, unable to open file!" << endl;
		return;
	}

	this -> m.load_menu(fin);
	fin.close();

	//gets shop info
	fin.open("shop_info.txt");

	if(!fin.is_open()){
		cout << "Error, unable to open file!" << endl;
	}

	fin >> this -> phone;
	getline(fin, this -> address, '.');
}

void Shop::start_program(){
	cout << "Welcome to Cool Guy Coffee Shop!" << endl;
	char choice;

	do{
		
		cout << "Are you a customer (C) or employee (E) or would you like to quit (Q)? ";

		cin >> choice;
		cout << endl;
		if(choice == 'C')
			customer_options();
		else if (choice == 'E')
			employee_options();
		else if (choice == 'Q'){
			cout << "Thank you for visiting Cool Guy Coffee Shop! Come again! " << endl;
			break;
		}
		else{
			cout << "That is not a valid input! Please try again. " << endl;
		}
	}while(choice != 'C' && choice != 'E' && choice != 'Q');

}

void Shop::employee_options(){
	int choice = 0;
	cout << "What would you like to do? " << endl;
	cout << "1. View shop revenue " << endl;
	cout << "2. View orders " << endl;
	cout << "3. Add an item to coffee menu " << endl;
	cout << "4. Remove an item from coffee menu " << endl;
	cout << "5. View shop details: menu, address, and phone number " << endl;
	cout << "6. View Best Selling drink by quantity " << endl;
	cout << "7. Log out " << endl;
	cout << endl;


	do{
		cout << "Enter a number from the menu above" << endl;
		cout << "Selection: ";	
		cin >> choice;
		cout << endl;
		if(choice == 1){
			view_revenue();
		}
		else if(choice == 2){
			view_orders();
		}
		else if(choice == 3){
			add_to_menu();
		}
		else if(choice == 4){
			remove_from_menu();
		}
		else if(choice == 5){
			view_shop_detail_e();
		}
		else if(choice == 6){
			view_best_seller();
		}
		else if(choice == 7){
			start_program();
		}
		else{
			cout << "That's not an option. Please try again." << endl;
		}

	} while(choice < 1 || choice > 8);
		
}

void Shop::customer_options(){
	int choice = 0;
	cout << "What would you like to do? " << endl;
	cout << "1. View shop details: menu, address, and phone number " << endl;
	cout << "2. Search by price " << endl;
	cout << "3. Search by coffee name " << endl;
	cout << "4. Place an order " << endl;
	cout << "5. Log out  " << endl;
	cout << endl;


	do{
		cout << "Enter a number from the menu above" << endl;
		cout << "Selection: ";	
		cin >> choice;
		cout << endl;
		if(choice == 1){
			view_shop_detail_c();
		}
		else if(choice == 2){
			search_by_price();
		}
		else if(choice == 3){
			search_by_name();
		}
		else if(choice == 4){
			customer_input_order();
		}
		else if(choice == 5){
			start_program();
		}
		else{
			cout << "That's not an option. Please try again." << endl;
		}

	} while(choice < 1 || choice > 5);
}

void Shop::view_revenue(){
	cout << "Shop revenue: $";
	cout << this -> revenue << endl << endl; 
	employee_options();
}

void Shop::view_shop_detail_c(){
	cout << "Our phone number is: " << this -> phone << endl;
	cout << "Our address is: " << this -> address << endl;
	cout << "*******************" << endl;
	cout << "MENU" << endl;
	this -> m.print_menu();
	customer_options();
}

void Shop::view_shop_detail_e(){
	cout << "Our phone number is: " << this -> phone << endl;
	cout << "Our address is: " << this -> address << endl;
	cout << "*******************" << endl;
	cout << "MENU" << endl;
	this -> m.print_menu();
	employee_options();
}


void Shop::search_by_name(){
	Coffee c; 
	char choice;

	//get name to search for
	string name = "";
	cout << "Name of coffee (in one word): ";
	cin >> name;
	c = this -> m.search_coffee_by_name(name);
	cout << endl;

	//if it didn't find anything then return to menu
	if(c.get_name() == "No coffee here yet."){
		this -> customer_options();
	}

	c.print_coffee();

	//Place an order
	cout << "Would you like to place an order based on this search (Y or N)?";
	int index = 0;

	//this gets the users choice if they wanna place an order
	//if so, it sends an order request of the indicated coffee from the search
	do{
		cin >> choice; 
		if (choice == 'Y'){
			//finds the right coffee in the menu to create the order with
			for(int i = 0; i < this -> m.get_num_coffee(); i++){
				if (this -> m.get_coffee_name(i) == c.get_name())
					index = i; 
			}
			this -> create_order(index);
		}
		else if(choice == 'N')
			continue;
		else
			cout << "That is not an option. Please try again." << endl;
	} while(choice != 'Y' && choice != 'N');

	this -> customer_options();
}

void Shop::search_by_price(){
	float budget = 0;
	Menu temp_m;
	do{
		cout << "What is your budget? (Enter a number greater than 0): "; 
		cin >> budget;
	} while (budget <= 0);

	//creates a temporary menu of coffees within the budget
	temp_m = this -> m.search_coffee_by_price(budget);

	char choice;
	if (m.get_num_coffee() == 0){
		this -> customer_options();
		return;
	}
	if (temp_m.get_num_coffee() == 0){
		this -> customer_options();
		return;
	}
	cout << "Would you like to place an order based on this search (Y or N)?";

	//this gets the users choice if they wanna place an order
	//if so, it sends an order request of the indicated coffee from the search
	do{
		cin >> choice; 
		if (choice == 'Y'){
			int choice2 = 0; 
			temp_m.print_menu_names();
			while(choice2 > temp_m.get_num_coffee() || choice2 < 1){
				cout << "Make sure to enter an integer option from the menu above." << endl;
				cout << "Selection: ";
				cin >> choice2;
			}
			this -> create_order_from_search(temp_m, choice2 - 1);
		}
		else if(choice == 'N')
			continue;
		else
			cout << "That is not an option. Please try again." << endl;
	} while(choice != 'Y' && choice != 'N');

	this -> customer_options();
}


void Shop::customer_input_order(){
	int choice = 0; 

	cout << "What do you want to order?" << endl;
	this -> m.print_menu_names();
	do{
		cout << "Make sure to enter an integer option from the menu above." << endl;
		cout << "Selection: ";
		cin >> choice;
	} while (choice > m.get_num_coffee() || choice < 1);
	create_order(choice - 1);
	customer_options();
}

void Shop::create_order(int index_of_coffee){
	Order o;
	char size;
	int quantity = 0;

	o.set_id(num_orders+1);
	o.set_coffee_name(m.get_coffee_name(index_of_coffee));
	do{
		cout << "Enter size of coffee (just the letter) (S, M, L): ";
		cin >> size;
	} while(size != 'S' && size != 'M' && size != 'L');

	o.set_coffee_size(size);

	do {
		cout << "Enter the quantity you want (a positive integer): ";
		cin >> quantity;	
	} while(quantity < 1);

	o.set_quantity(quantity);

	calculate_total(index_of_coffee, quantity, size); //prints total
	place_order(o);
}

void Shop::create_order_from_search(Menu temp_m, int index_of_coffee){
	Order o;
	char size;
	int quantity = 0;

	o.set_id(num_orders+1);
	o.set_coffee_name(temp_m.get_coffee_name(index_of_coffee));
	do{
		cout << "Enter size of coffee (just the letter) (S, M, L): ";
		cin >> size;
	} while(size != 'S' && size != 'M' && size != 'L');

	o.set_coffee_size(size);

	do {
		cout << "Enter the quantity you want (a positive integer): ";
		cin >> quantity;	
	} while(quantity < 1);

	o.set_quantity(quantity);

	calculate_total_with_menu_object(temp_m, index_of_coffee, quantity, size); //prints total
	place_order(o);
}

void Shop::calculate_total_with_menu_object(Menu temp_m, int index_of_coffee, int quantity, char size){
	//printing total
	float price = 0;
	float total = 0;
	if(size == 'S'){
		price = temp_m.get_coffee_small(index_of_coffee);
	}
	if(size == 'M'){
		price = temp_m.get_coffee_medium(index_of_coffee);
	}
	if(size == 'L'){
		price = temp_m.get_coffee_large(index_of_coffee);
	}
	total = price * quantity;
	this -> revenue += total; //add to total shop revenue

	temp_m.add_to_coffee_revenue(index_of_coffee, total); //add to revenue for that coffee in menu

	cout << "\nYour total is: $" << total << endl << endl;
	cout << "Your order number is: " << num_orders+1 << endl << endl;
}


void Shop::calculate_total(int index_of_coffee, int quantity, char size){
	//printing total
	float price = 0;
	float total = 0;
	if(size == 'S'){
		price = m.get_coffee_small(index_of_coffee);
	}
	if(size == 'M'){
		price = m.get_coffee_medium(index_of_coffee);
	}
	if(size == 'L'){
		price = m.get_coffee_large(index_of_coffee);
	}
	total = price * quantity;
	this -> revenue += total; //add to total shop revenue

	this -> m.add_to_coffee_revenue(index_of_coffee, total); //add to revenue for that coffee in menu

	cout << "\nYour total is: $" << total << endl << endl;
	cout << "Your order number is: " << num_orders+1 << endl << endl;
}

void Shop::place_order(Order &o){
	//create temporary array of length +1 
	Order* temp_array = new Order[this -> num_orders + 1];

	//copy from old array to temp array
	for(int i = 0; i < this -> num_orders; i++){
		temp_array[i] = this -> order_arr[i];
	}

	//allocate new coffee to end of array
	temp_array[this -> num_orders] = o;

	//free current array
	delete [] this -> order_arr;

	this -> order_arr = temp_array;

	//increment numbers of coffee
	++this -> num_orders;
	this -> remake_orders();
}

void Shop::remake_orders(){
	ofstream fout;
	fout.open("orders.txt", ios::trunc);

	if(!fout.is_open()){
		cout << "Error, unable to open file!" << endl;
	}

	fout << this -> num_orders << endl;
	for(int i = 0; i < num_orders; i++){
		fout << this -> order_arr[i].get_id() << " ";
		fout << this -> order_arr[i].get_coffee_name() << " ";
		fout << this -> order_arr[i].get_coffee_size() << " ";
		fout << this -> order_arr[i].get_quantity() << " ";
		fout << endl;
	}


}

void Shop::remove_from_menu(){
	int num = 0;
	this -> m.print_menu_names();
	do{
		cout << "Which item do you want to remove (enter integer): ";
		cin >> num;
	} while (num < 0 || num > this -> m.get_num_coffee());

	this -> m.remove_from_menu(num-1);
	employee_options();
}

void Shop::add_to_menu(){
	this -> m.get_new_coffee_info();
	employee_options();
}

void Shop::view_orders(){
	if (num_orders < 1){
		cout << "There are no orders yet! \n" << endl;
	}
	for(int i = 0; i < this -> num_orders; i++){
		cout << "Order: " << this -> order_arr[i].get_id() << endl;
		cout << "Coffee: " << this -> order_arr[i].get_coffee_name() << endl;
		cout << "Size: " << this -> order_arr[i].get_coffee_size() << endl;
		cout << "Quantity: " << this -> order_arr[i].get_quantity() << endl;
	}
	employee_options();
}

/*
void Shop::view_top_3_drinks(){
	float one, two, three = 0;
	float placeholder;
	Coffee coffee_one, coffee_two, coffee_three;
	Coffee coffee_placeholder;

	for(int i = 0; i < this -> m.get_num_coffee(); i++){
		if(this -> m.get_coffee_revenue(i) >= three){
			coffee_three = m.get_coffee_array(i);
			three = this -> m.get_coffee_revenue(i);
			if(three >= two){
				//swap two and three
				placeholder = two;
				two = three;
				three = placeholder;

				coffee_placeholder = coffee_two;
				coffee_two = coffee_three;
				coffee_three = coffee_placeholder;

				if(two >= one){
					//swap one and two
					placeholder = one;
					one = two;
					two = placeholder;

					coffee_placeholder = coffee_one;
					coffee_one = coffee_two;
					coffee_two = coffee_placeholder;
				}
			}

		}
	
	}

	//cout << "The 1st highest selling coffee currently on the menu: " << coffee_one.get_name() << endl;
	cout << "The 1st highest selling coffee currently on the menu: "  << endl;
	coffee_one.print_name();
	cout << endl;
	//cout << "The 2nd highest selling coffee currently on the menu: " << coffee_two.get_name() << endl;
	cout << "The 2nd highest selling coffee currently on the menu: "  << endl;
	coffee_two.print_name();
	cout << endl;
	
	//cout << "The 3rd highest selling coffee currently on the menu: " << coffee_three.get_name() << endl << endl;
	cout << "The 3rd highest selling coffee currently on the menu: "  << endl;
	coffee_three.print_name();
	cout << endl;
	
	this -> employee_options();
}

*/

//checks for best seller by quantity
void Shop::view_best_seller(){
	string name = "";
	char size;
	int highest_quantity = 0;
	int current_quantity = 0;

	for(int i = 0; i < this -> num_orders; i++){
		current_quantity = order_arr[i].get_quantity();
		for(int j = 0; j < this -> num_orders; j++){
			if(order_arr[i].get_coffee_name() == order_arr[j].get_coffee_name() && order_arr[i].get_coffee_size() == order_arr[j].get_coffee_size() && i != j){
				current_quantity += order_arr[j].get_quantity();
			}
		}

		if(current_quantity > highest_quantity){
			highest_quantity = current_quantity;
			name = order_arr[i].get_coffee_name();
			size = order_arr[i].get_coffee_size();
		}
	}

	cout << "The best seller by quantity is: " << name << " in size " << size << endl << endl;
	this -> employee_options();
}

