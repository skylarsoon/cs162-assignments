#include <iostream>
#include <fstream>
#include <string>
#include "pokemon.h"

using namespace std;

int main(){
	//gets file info and opens file
	ifstream fin;
	Pokedex pokedex_main;
	string file_name = "";

	//get user inputs
	get_user_inputs(pokedex_main, file_name);
	fin.open(file_name.c_str());

	while(fin.fail()){
		cout << "<ERROR> File not found. Exiting the program..." << endl;
		return 1;
	}

	//gets number of pokemon
	fin >> pokedex_main.num_pokemon;

	//creates pokemon array
	pokedex_main.dex = create_pokemons(pokedex_main.num_pokemon);

	//populates pokemon array
	populate_pokedex_data(pokedex_main, fin);

	//displays options
	display_options(pokedex_main);
	cout <<"Thank you for playing! " << endl;

	delete_info(pokedex_main);


	return 0;
}