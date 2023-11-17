/******************************************************
** Program: linked_list.cpp
** Author: Skylar Soon
** Date: 6/10/2023
** Description: creates functions to modify and view elements of a linked list
** Input: integers 
** Output: a linked list
******************************************************/


#include "linked_list.h"

Linked_List::Linked_List(){
	this -> length = 0; 
	this -> head = NULL;
}


int Linked_List::get_length(){
	return this -> length;
	/*
	int counter = 0;

	Node* current = this -> head;
	if(current == NULL){
		return 0;
	}
	while(current != NULL){
		current = current -> next;
		counter++;
	}
	//add last node
	//counter++;
	this -> length = counter;
	return counter;
	*/
}

void Linked_List::push_front(int new_num){
	Node* new_node = new Node;

	//make new node point to what the head is pointing to
	new_node -> next = this -> head;

	//making head point to new node
	this -> head = new_node;

	//setting value to new node
	new_node -> val = new_num;
	this -> length++;
}

void Linked_List::push_back(int new_num){
	Node* new_node = new Node;

	new_node -> val = new_num;

	//traverses list until end
	Node* current = head;
	for(int i = 0; i < length - 1; i++){
		current = current -> next;
	}

	//makes pointer at end point to new node
	current -> next = new_node;

	this -> length++;
}

void Linked_List::insert(int new_num, int index){
	Node* new_node = new Node;

	new_node -> val = new_num;

	//traverses list until index starting at head
	Node* current = this -> head;

	//if index is 0
	if(index == 0){
		new_node -> next = this -> head;
		this -> head = new_node;
	}
	else{
		for(int i = 0; i < index - 1; i++){
			//checks if valid node to access
			if(current -> next == NULL)
				return;
			current = current -> next;
		}
		//makes new node point to next
		new_node -> next = current -> next;

		//makes pointer at index to new node
		current -> next = new_node;
	}

	this -> length++;
}
/*
void Linked_List::sort_ascending(){
	this -> merge_sort(this -> head);
}

int Linked_List::get_list_length(Node* list){
	int counter = 1; 
	Node* current = list;
	while(current -> next != NULL){
		current = current -> next;
		counter++;
	}
	return counter+1;
}

Node* Linked_List::merge_sort(Node*& list){
    if (list == NULL) {
        return list;     // List is empty
    }
    else if (list->next == NULL) {
        return list;    // List is length 1
    }
	//create two sub lists
	Node* left = NULL; 
	Node* right = NULL;


	//create node to iterate through array
	Node* current = this -> head;

	//nodes to store ends
	Node* left_end = new Node;
	Node* right_end = new Node;

	//split lists into two
	//iterate through current list
	for(int i = 0; i < this -> get_list_length(list); i++){

		if(i < this -> get_list_length(list)/2){
			//go through list until end

			//if first case, set left* to be current
			if (get_list_length(left) < 1){
				//left points to current
				left = current; 
				left_end = left; 
			}
			//if it's not the first, then just set end next to current 
			left_end -> next = current;
			left_end = current;
		}
		else 
			if(get_list_length(right) < 1){
				right = current;
				right_end = right;
			}
			right_end -> next = current;
			right_end = current;
	}
	left = merge_sort(left);
	right = merge_sort(right);

	current = current -> next;

	return merge(left, right);
}

Node* Linked_List::merge(Node* left, Node* right){
	Node* result;
	Node* result_end = new Node;

	Node* current = NULL;

	while(left != NULL && right != NULL){
		if(left -> val <= right -> val){
			//iterate through result list and append current value
			if(this -> get_list_length(result) < 1){
				result = left;
				result_end = result;
			}
			result_end -> next = left;
			result_end = result_end -> next;

			//change left head to point to next value
			if(left -> next != NULL)
				left = left -> next;
			else //if last item in list
				left = NULL;
		} 
		else{
			if(this -> get_list_length(result) < 1){
				result = right;
				result_end = result;
			}
			result_end -> next = right;
			result_end = result_end -> next;

			//change right head to point to next value
			if(right -> next != NULL)
				right = right -> next;
			else //if last item in list
				right = NULL;
		}
	}

	while(left != NULL){
		//append what's still in left list to result
		result_end -> next = left;
		left = left -> next;
	}

	while(right != NULL){
		//append what's still in right list to result
		result_end -> next = right;
		right = right -> next;
	}

	return result;
}
*/
void Linked_List::print(){
	Node* current = this -> head;
	if(current == NULL){
		return;
	}

	while(current -> next != NULL){
		cout << current -> val << " ";
		current = current -> next;
	}
	cout << current -> val << " ";
}

void Linked_List::clear(){
	Node* current = this -> head;
	Node* temp;
	while(current != NULL){
		temp = current -> next;
		delete current;
		current = temp;
		this -> length--;
	}

}
