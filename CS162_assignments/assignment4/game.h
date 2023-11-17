#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cstdlib> //rand, srand
#include <ctime> // time
#include <string>
#include <stdio.h> //system calls
#include "room.h"
#include "event.h"
#include "gold.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"

using namespace std;

class Game{
private:
	vector < vector<Room*> > grid;
	int length;
	int width;
	int player_x;
	int player_y;
	bool has_gold;
	int bat_count;
	int arrows_count;
	bool wumpus_alive;
	int wumpus_x;
	int wumpus_y;
	int initial_x;
	int initial_y;
	bool game_won;
	bool player_alive;
	bool game_over;
	bool new_game;

public:

	Game();
	//~Game();
	bool get_new_game();
	void prompt_user_mode();
	void debug_mode();
	void normal_mode();
	void print_grid();
	void print_normal_grid();
	void get_dimensions();
	void set_up();
	char play_again();

	void set_player_position();
	char get_user_input();

	void detect_percept();

	//events
	void check_event();
	void player_death();
	void pit_interaction();
	void wumpus_interaction();
	void bats_interaction();
	void gold_interaction();

	char check_bats(char input);

	//arrows
	void arrows_action();
	void arrows_action_w();
	void arrows_action_a();
	void arrows_action_s();
	void arrows_action_d();
	void new_wumpus_location();
	void wumpus_death();
	void check_arrows();

	void check_win_game();
	bool get_game_won();
	bool get_player_alive();

	void clear_memory();

};

#endif