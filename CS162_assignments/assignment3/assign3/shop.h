#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include "menu.h"
#include "order.h"

using namespace std;

class Shop {
  private:
    Menu m;
    string phone;
    string address;
    float revenue;
    Order *order_arr;
    int num_orders;
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate
    Shop();
    ~Shop();


    void start_program();
    void customer_options();
    void employee_options();
    void view_revenue();
    void customer_input_order();
    //Suggested functions
    void load_data(); //reads from files to correctly populate coffee, menu, etc.
    void search_by_price();
    void search_by_name();
    void create_order(int index_of_coffee);
    void create_order_from_search(Menu temp_m, int index_of_coffee); //creates order taking a menu object
    void place_order(Order &o);
    void calculate_total_with_menu_object(Menu temp_m, int index_of_coffee, int quantity, char size);
    void calculate_total(int index, int quantity, char size);
    void remake_orders();
    void add_to_menu();
    void remove_from_menu();
    void view_orders();

    void view_shop_detail_c();
    void view_shop_detail_e();

    void view_top_3_drinks();
    void view_best_seller();
};

#endif
