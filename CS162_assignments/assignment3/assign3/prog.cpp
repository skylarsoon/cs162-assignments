/*
Program: prog.cpp
Author: Skylar Soon
Date: 05/14/2023
Description: Simulates a coffee shop and keep track of useful information for both customer and employee
Input: simple user choices (char, int, string), and data from .txt files
Output: information into .txt files and to the screen
*/

#include <iostream>
#include <fstream>
#include "shop.h"
#include "coffee.h"

using namespace std;

int main()
{
	Shop coffee_shop;
	coffee_shop.load_data();
	coffee_shop.start_program();

	return 0;
}