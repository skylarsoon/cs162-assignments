#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pokemon {
	int poke_level;
	string name;
	string type;
	int num_moves;
	string* moves;
};

struct Pokedex {
	string trainer;
	int trainer_level;
	int num_pokemon;
	Pokemon* dex;
};

//gets initial user inputs
void get_user_inputs(Pokedex &, string &);

//dynamically allocate an array of pokemon (of the requested size)
Pokemon* create_pokemons(int); 

//this function will fill a pokedex object with info read from dex.txt
void populate_pokedex_data(Pokedex &, ifstream &);

//this function will dynamically allocate an array of moves of a pokemon)
string* create_moves(int);

//this function will fill a single pokemon object with info read from dex.txt
void populate_pokemon(Pokemon &, ifstream &);

//displays moves to the screen
void display_pokemon(Pokedex &);

//displays options for user to search
void display_options(Pokedex &);

void search_by_name(Pokedex &);

void evolve_pokemon(Pokedex &);

void search_by_type(Pokedex &pokedex_main);

int get_evolve_level(Pokedex &pokedex_main);

void add_new_pokemon(Pokedex &);

int display_or_print();

void print_to_screen(Pokemon &pokemon_object);

void print_to_file(Pokemon &pokemon_object, ofstream &fout);

//delete memory that is dynamically allocated
void delete_info(Pokedex &);

#endif