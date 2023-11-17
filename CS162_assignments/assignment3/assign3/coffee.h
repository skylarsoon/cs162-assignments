#ifndef COFFEE_H
#define COFFEE_H

#include <string>
#include <fstream>

using namespace std;

class Coffee {
  private:
    string name;
    float small_cost;
    float medium_cost;
    float large_cost;
    float revenue;
    
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate

    Coffee(); //Coffee constructor
    void set_name (const string);
    void set_small_cost(const float);
    void set_medium_cost(const float);
    void set_large_cost(const float);
    string get_name() const;
    void print_name() const;
    float get_small_cost () const;
    float get_medium_cost () const;
    float get_large_cost () const;
    void print_coffee() const; //print the coffee out
    void load_a_single_coffee(ifstream &fin);

//extra credit
    void set_revenue(const float new_revenue);
    float get_revenue () const;
};

#endif