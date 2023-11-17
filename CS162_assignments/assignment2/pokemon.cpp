#include <iostream>
#include <fstream>
#include <string>
#include "pokemon.h"

using namespace std;

/*
Function: get_user_inputs
Description: gets initial inputs from user
Parameters: Take in pokedex object and file name so user can edit it
Pre-Conditions: none
Post-Conditions: Pokedex trainer name/level and file name is set
*/
void get_user_inputs(Pokedex &pokedex_main, string &file_name){
	cout << "Enter your name: ";
	getline(cin, pokedex_main.trainer);

	cout << "Enter your level: ";
	cin >> pokedex_main.trainer_level;
	while (pokedex_main.trainer_level <= 0 || pokedex_main.trainer_level > 100){
		cout << "Your level must be a positive integer less than 100! " << endl;
		cout << "Enter your level: ";
		cin >> pokedex_main.trainer_level;
	}

	cout << "Enter the name of the file containing your Pokemon information: ";
	cin >> file_name;
}

/*
Function: create_pokemons
Description: creates dynamic dex array
Parameters: takes number of pokemon in file
Pre-Conditions: has read number of pokemon from file
Post-Conditions: updates the dex member of the pokedex object
*/
Pokemon* create_pokemons(int num_pokemon){
	Pokemon* dex = new Pokemon[num_pokemon];
	return dex;
}

/*
Function: populate_pokedex_data
Description: updates pokemon each pokemon object in array
Parameters: pokedex_main and file object
Pre-Conditions: must have created populate pokemon object and created array
Post-Conditions: updates array
*/
void populate_pokedex_data(Pokedex &pokedex_main, ifstream &fin){
	for(int i = 0; i < pokedex_main.num_pokemon; i++){
		Pokemon pokemon_object; 
		populate_pokemon(pokemon_object, fin);
		pokedex_main.dex[i] = pokemon_object;
	}
}

/*
Function: create_moves
Description: takes number of moves to create moves array
Parameters: takes number of moves
Pre-Conditions: has number of moves
Post-Conditions: creates moves array for each pokemon
*/
string* create_moves(int num_moves){
	string* moves = new string[num_moves];
	return moves;
}

/*
Function: populate_pokemon
Description: reads from file to update pokemon object in array
Parameters: pokemon object from array and file object
Pre-Conditions: has array of pokemon objects created
Post-Conditions: updates array of pokemon objects with information
*/
void populate_pokemon(Pokemon &pokemon_object, ifstream &fin){
	fin >> pokemon_object.poke_level;
	fin >> pokemon_object.name;
	fin >> pokemon_object.type;
	fin >> pokemon_object.num_moves;

	pokemon_object.moves = create_moves(pokemon_object.num_moves);
	for(int i = 0; i < pokemon_object.num_moves; i++){
		fin >> pokemon_object.moves[i];
	}
}

/*
Function: display_options
Description: displays options to the screen
Parameters: takes in pokedex object to edit
Pre-Conditions: must have pokedex objects and search functions completed
Post-Conditions: moves to a function or exits the program
*/
void display_options(Pokedex &pokedex_main){
	int choice = 0;
	cout << "Do you want to (1) Search by name, (2) Evolve a Pokemon, (3) Search by type, (4) Add new pokemon, (5) Quit: ";
	cin >> choice;

	if(choice == 1){
		search_by_name(pokedex_main);
	}
	else if(choice == 2){
		evolve_pokemon(pokedex_main);
	}
	else if(choice == 3){
		search_by_type(pokedex_main);
	}
	
	else if(choice == 4){
		add_new_pokemon(pokedex_main);
	}
	
	if(!(choice >= 1 && choice <= 5)){
		cout << "<ERROR> Please enter either 1, 2, 3, 4, or 5 to make your choice." << endl;
		display_options(pokedex_main);
	}
}

/*
Function: search_by_name
Description: iterates through array to search for pokemon by name and outputs (over 15 lines to get output in right order)
Parameters: needs pokedex object
Pre-Conditions: needs pokedex object and display functions
Post-Conditions: finds if there is a pokemon by name and displays
*/
void search_by_name(Pokedex &pokedex_main){
	string poke_name;
	string file_name;
	ofstream fout;
	int found_pokemon = 0; //created to check if a pokemon is found or not

	cout << "What is the Pokemon's name: ";
	cin >> poke_name;
	
	int choice = display_or_print();

	if(choice == 2){
		cout << "Please enter the name of the file you want to append to print to: ";
		cin >> file_name;
		fout.open(file_name.c_str(), ios::app);
	}

	//checks if pokemon exists and asks user what they to do with the new information
	for(int i = 0; i < pokedex_main.num_pokemon; i++){
		if(pokedex_main.dex[i].name == poke_name && pokedex_main.dex[i].poke_level <= pokedex_main.trainer_level){
			if(choice == 1){
				print_to_screen(pokedex_main.dex[i]);
			}
			if(choice == 2){
				print_to_file(pokedex_main.dex[i], fout);
			}
			found_pokemon++;
		}	
	}
	if(found_pokemon == 0){
		cout << "No pokemon found." << endl;
	}

	display_options(pokedex_main);
}

/*
Function: evolve_pokemon
Description: changes pokemon level (over 15 lines to get output in right order)
Parameters: pokedex object to edit
Pre-Conditions: needs display functions created, and get_evolve() to be created, input level is less than trainer
Post-Conditions: changes level and prints to screen
*/
void evolve_pokemon(Pokedex &pokedex_main){
	string poke_name;
	string file_name;
	ofstream fout;
	int found_pokemon = 0;

	cout << "What is the Pokemon's name: ";
	cin >> poke_name;
	
	int choice = display_or_print();

	if(choice == 2){
		cout << "Please enter the name of the file you want to append to print to: ";
		cin >> file_name;
		fout.open(file_name.c_str(), ios::app);
	}

	int evolve_level = get_evolve_level(pokedex_main);

	//checks if pokemon exists and asks user what they to do with the new information
	for(int i = 0; i < pokedex_main.num_pokemon; i++){
		if(pokedex_main.dex[i].name == poke_name && pokedex_main.dex[i].poke_level <= pokedex_main.trainer_level){
			pokedex_main.dex[i].poke_level = evolve_level;
			if(choice == 1){
				print_to_screen(pokedex_main.dex[i]);
			}
			if(choice == 2){
				print_to_file(pokedex_main.dex[i], fout);
			}
			found_pokemon++;
		}	
	}
	if(found_pokemon == 0){
		cout << "No Pokemon found." << endl;
	}

	display_options(pokedex_main);
}

/*
Function: get_evolve_level
Description: gets desired level to evolve
Parameters: pokedex object to see if user is eligible
Pre-Conditions: needs pokedex object to have trainer level
Post-Conditions: returns desired level to evolve function
*/
int get_evolve_level(Pokedex &pokedex_main){
	int level = 0;
	cout << "What is the level that you want to evolve the pokemon to? ";
	cin >> level;

	while(pokedex_main.trainer_level < level){
		cout << "You cannot evolve a Pokemon to a level greater than yours!" << endl;
		cout << "Enter a lower level: ";
		cin >> level; 
	}
	return level;
}

/*
Function: display_or_print() 
Description: gets user input on if they want to display to screen or print to file their results
Parameters: none
Pre-Conditions: ran inside of search functions
Post-Conditions: returns to respective search function the result of input
*/
int display_or_print(){
	int choice = 0;
	cout << "Do you want to print the results (1) to the screen or (2) to a file: ";
	cin >> choice;
	if(choice != 1 && choice != 2){
		cout << "<ERROR> Please enter either 1 or 2." << endl;
		display_or_print();
	}
	return choice;
}

/*
Function: search_by_type()
Description: iterates through to print/write each pokemon with a specified type (over 15 lines to get output in right order)
Parameters: pokedex object to search through
Pre-Conditions: must have chosen this option, have display functions created
Post-Conditions: writes to file/displays info on pokemon with the type
*/
void search_by_type(Pokedex &pokedex_main){
	string poke_type;
	string file_name;
	ofstream fout;
	int found_pokemon = 0;

	cout << "What type do you want to search for: ";
	cin >> poke_type;
	
	int choice = display_or_print();

	if(choice == 2){
		cout << "Please enter the name of the file you want to append to print to: ";
		cin >> file_name;
		fout.open(file_name.c_str(), ios::app);
	}

	//checks if pokemon exists and asks user what they to do with the new information
	for(int i = 0; i < pokedex_main.num_pokemon; i++){
		if(pokedex_main.dex[i].type == poke_type && pokedex_main.dex[i].poke_level <= pokedex_main.trainer_level){
			if(choice == 1){
				print_to_screen(pokedex_main.dex[i]);
			}
			if(choice == 2){
				print_to_file(pokedex_main.dex[i], fout);
			}
			found_pokemon++;
		}	
	}
	if(found_pokemon == 0){
		cout << "No pokemon found with that type." << endl;
	}

	display_options(pokedex_main);
}

/*
Function: add_new_pokemon()
Description: takes user input to create a new file and add to the dex array 
Parameters: pokedex object to edit
Pre-Conditions: must have chosen this option, initial array created
Post-Conditions: creates new array with new pokemon
*/
void add_new_pokemon(Pokedex &pokedex_main){
	Pokemon pokemon_object;
	cout << "Enter Pokemon name: ";
	cin >> pokemon_object.name;
	cout << "Enter Pokemon level: ";
	cin >> pokemon_object.poke_level;
	cout << "Enter Pokemon type: ";
	cin >> pokemon_object.type;
	cout << "Enter how many moves it will have: ";
	cin >> pokemon_object.num_moves;

	pokemon_object.moves = create_moves(pokemon_object.num_moves);
	for(int i = 0; i < pokemon_object.num_moves; i++){
		cout << "Enter move " << i + 1 << ": ";
		cin >> pokemon_object.moves[i];
	}
	pokedex_main.num_pokemon += 1;
	//create a copy of the original pokemon array and store it in copy_array
	Pokemon* copy_array = new Pokemon[pokedex_main.num_pokemon];
	for(int i = 0; i < pokedex_main.num_pokemon-1; i++){
		copy_array[i] = pokedex_main.dex[i];
	}

	copy_array[pokedex_main.num_pokemon-1] = pokemon_object;

	delete [] pokedex_main.dex;

	pokedex_main.dex = copy_array;

	cout << "Pokemon added! Search for it using one of the options below to view your new Pokemon: " << endl;
	display_options(pokedex_main);

}

/*
Function: print_to_file()
Description: prints to file the info on a pokemon
Parameters: a pokemon object and file object
Pre-Conditions: pokemon object needs to be created and so does a file output object
Post-Conditions: adds to the file the respective information
*/
void print_to_file(Pokemon &pokemon_object, ofstream &fout){
	fout << "Pokemon Level: " << pokemon_object.poke_level << endl;
	fout << "Pokemon Name: " << pokemon_object.name << endl;
	fout << "Pokemon Type: " << pokemon_object.type << endl;
	for (int j = 0; j < pokemon_object.num_moves; j++){
		fout << "Pokemon Move: " << pokemon_object.moves[j] << endl;
	}
	fout << endl;
}

/*
Function: print_to_screen()
Description: prints to screen info on a pokemon
Parameters: needs a pokemon object
Pre-Conditions: pokemon object needs to be created 
Post-Conditions: prints to screen the info
*/
void print_to_screen(Pokemon &pokemon_object){
	cout << "Pokemon Level: " << pokemon_object.poke_level << endl;
	cout << "Pokemon Name: " << pokemon_object.name << endl;
	cout << "Pokemon Type: " << pokemon_object.type << endl;
	for (int j = 0; j < pokemon_object.num_moves; j++){
		cout << "Pokemon Move: " << pokemon_object.moves[j] << endl;
	}
	cout << endl;
}

/*
Function: delete_info()
Description: frees memory space of dynamic arrays in the pokedex object
Parameters: needs the pokedex object to access the arrays
Pre-Conditions: needs the dynamic arrays to be populated
Post-Conditions: memory space/leaks freed
*/
void delete_info(Pokedex &pokedex_main){
	for(int i = 0; i < pokedex_main.num_pokemon; i++){
		delete [] pokedex_main.dex[i].moves; //deletes moves
	}
	delete [] pokedex_main.dex; //deletes whole pokemon array
}