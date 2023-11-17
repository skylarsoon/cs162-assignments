#ifndef LINKED_LIST
#define LINKED_LIST

#include "node.h"
#include <iostream>

using namespace std;

class Linked_List {
private:
	int length; // the number of nodes contained in the list
	Node* head; // a pointer to the first node in the list
	// anything else you need...
public:
	Linked_List();
	int get_length();
	// note: there is no set_length(unsigned int) (the reasoning should be intuitive)
   
	void print(); // output a list of all integers contained within the list
	void clear(); // delete the entire list (remove all nodes and reset length to 0)
   
	void push_front(int); // insert a new value at the front of the list 
	void push_back(int); // insert a new value at the back of the list 
	void insert(int new_num, int index); // insert a new value in the list at the specified index 
	int get_list_length(Node* list){}
	void sort_ascending(){} // sort the nodes in ascending order. You must implement the recursive Merge Sort algorithm
	// Note: it's okay if sort_ascending() calls a recursive private function to perform the sorting.
	Node* merge(Node* left, Node* right){}
	Node* merge_sort(Node*& list){}
	void sort_descending(){} // sort the nodes in descending order

	// you can add extra member variables or functions as desired

};




#endif
