#include "game.h"

Game::Game(){
	this -> width = -1;
	this -> length = -1;
	this -> player_x = 0;
	this -> player_y = 0;
	this -> has_gold = 0;
	this -> bat_count = 0;
	this -> arrows_count = 3;
	this -> wumpus_alive = true;
	this -> wumpus_x = -1;
	this -> wumpus_y = -1;
	this -> initial_x = -1;
	this -> initial_y = -1;
	this -> game_won = false;
	this -> player_alive = true;
	this -> game_over = false;
	this -> new_game = true;
	//rogers example
	
}
bool Game::get_new_game(){
	return this -> new_game;
}

void Game::prompt_user_mode(){
	this -> get_dimensions();
	this -> set_up();

	string input = "";
	while(input == ""){
		cout << "Do you want to play in normal mode (n) or debug mode (d)? " << endl;
		getline(cin, input);
		if(input == "n"){
			this -> normal_mode();
		}
		else if(input == "d"){
			this -> debug_mode();
		}
		else{
			cout << "<ERROR> Invalid input!" << endl;
			input = "";
		}
	}

}


void Game::debug_mode(){
	do{
		cout << "IM BACK" << endl;
		while((this-> game_won == false && this-> player_alive == true) && this -> game_over == false){
			cout << "I'M REALLY BACK" << endl;
			print_grid();
			set_player_position();
			detect_percept();
			check_event();
			check_arrows();
			check_win_game();
		}
	}while(play_again() == '1');

}


void Game::normal_mode(){
	do{
		while((this-> game_won == false && this-> player_alive == true) && this -> game_over == false){
			print_normal_grid();
			set_player_position();
			detect_percept();
			check_event();
			check_arrows();
			check_win_game();
		}
	}while(play_again() == '1');

}

void Game::check_arrows(){
	if(this -> arrows_count < 1 && this -> wumpus_alive == true){
		cout << "You ran out of arrows. You lose!" << endl;
		this -> game_won = true;
	}
}

char Game::play_again(){
	char input = '\0';
	//reset 
	this -> game_won = false;
	this -> player_alive = true;
	this -> game_over = false;
	this -> arrows_count = 3;
	this -> wumpus_alive = true;
	this -> has_gold = 0;
	this -> player_x = this -> initial_x;
	this -> player_y = this -> initial_y;
	if(!this -> grid[wumpus_y][wumpus_x] -> get_event())
		this -> grid[wumpus_y][wumpus_x] -> set_event(new Wumpus());

	do{
		cout << "Options: " << endl;
		cout << "1. Play again with same map configuration" << endl;
		cout << "2. Quit" << endl;
		cout << "Selection: ";
		//system("stty raw");
		//input = getchar();
		//system("stty cooked");
		cin >> input;
		if(input == '1'){
			cout << "INPUT: " << input << endl;
			return '1';
		}
		if(input == '2'){
			this -> new_game = false;
			return '0'; 
		}
		cout << "<ERROR> Invalid input! Please try again." << endl;
	}while(input != '1' || input != '2');
}

void Game::print_grid(){
	cout << "\n\n\n\n\n\n\n\n\n\n";

	for(int i = 0; i < this -> length; i++){
		//tops
		for(int k = 0; k < this -> width; k++){
			cout << " ______";
		}
		cout << endl;
		//middles

		cout << "| ";
		for(int k = 0; k < this -> width; k++){
			cout << "  ";
			cout << "   ";
			cout << "| ";
		}
		cout << endl;


		cout << "| ";
		for (int j = 0; j < this -> width; j++){
			cout << "  ";
			//cout << endl;

			if(i == player_y && j == player_x){
				cout << "*  | ";
				continue;
			}

			if(this -> grid[i][j]->get_event() != NULL){
				//this is an event slot 
				cout << this -> grid[i][j]->get_event()->get_symbol();
				cout << "  | ";
				continue;
			}
			//empty slot
			cout << "   ";
			cout << "| ";
		}
		cout << endl;

		cout << "|";
		for(int k = 0; k < this -> width; k++){
			cout << "____";
			cout << "__";
			cout << "|";
		}
		cout << endl;

	}
	cout << endl;
	cout << endl;
}

void Game::print_normal_grid(){
	cout << "\n\n\n\n\n\n";

	for(int i = 0; i < this -> length; i++){
		//tops
		for(int k = 0; k < this -> width; k++){
			cout << " ______";
		}
		cout << endl;
		//middles

		cout << "| ";
		for(int k = 0; k < this -> width; k++){
			cout << "  ";
			cout << "   ";
			cout << "| ";
		}
		cout << endl;


		cout << "| ";
		for (int j = 0; j < this -> width; j++){
			cout << "  ";
			//cout << endl;

			if(i == player_y && j == player_x){
				cout << "*  | ";
				continue;
			}

			if(this -> grid[i][j]->get_event() != NULL){
				//this is an event slot 
				//cout << this -> grid[i][j]->get_event()->get_symbol();
				cout << "   | ";
				continue;
			}
			//empty slot
			cout << "   ";
			cout << "| ";
		}
		cout << endl;

		cout << "|";
		for(int k = 0; k < this -> width; k++){
			cout << "____";
			cout << "__";
			cout << "|";
		}
		cout << endl;

	}
	cout << endl;
	cout << endl;
}

void Game::set_up(){
	int i = -1, j = -1; 
	//make grid
	cout << "length: " << this -> length << endl;
	cout << "width: " << this -> width << endl;

	for(int i = 0; i < this -> length; i++){
		vector <Room*> temp(this -> width, NULL);
		this -> grid.push_back(temp);
	}
	//make player
	do{
		i = rand() % this -> length;
		j = rand() % this -> width;
	}while (this-> grid[i][j] != NULL); //regenerate if occupied already

	this -> grid[i][j] = new Room(); 
	this -> player_x = j;
	this -> player_y = i;
	this -> initial_x = j;
	this -> initial_y = i;

	//make wumpus
	do{
		i = rand() % this -> length;
		j = rand() % this -> width;
	}while (this-> grid[i][j] != NULL); //regenerate if occupied already

	this -> grid[i][j] = new Room(); 
	this -> grid[i][j] -> set_event(new Wumpus());
	this -> wumpus_x = j;
	this -> wumpus_y = i;

	//make gold
	do{
		i = rand() % this -> length;
		j = rand() % this -> width;
	}while (this-> grid[i][j] != NULL); //regenerate if occupied already

	this -> grid[i][j] = new Room(); 
	this -> grid[i][j] -> set_event(new Gold());

	//make bats
	for(int k = 0; k < 2; k++){
		do{
			i = rand() % this -> length;
			j = rand() % this -> width;
		} while (this-> grid[i][j] != NULL);
	
		this -> grid[i][j] = new Room();
		this -> grid[i][j] -> set_event(new Bats());
	}

	//make pits
	for(int k = 0; k < 2; k++){
		do{
			i = rand() % this -> length;
			j = rand() % this -> width;
		} while (this-> grid[i][j] != NULL);
	
		this -> grid[i][j] = new Room();
		this -> grid[i][j] -> set_event(new Pit());
	}

	//creates empty rooms
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			if (this -> grid[i][j] == NULL){
				this -> grid[i][j] = new Room();
			}
		}	
	}
	
}

void Game::get_dimensions(){
	string new_width, new_length;
	do{
		cout << "Enter an integer width of the board 4 or greater: ";
		getline(cin,new_width);
	}while(!atoi(new_width.c_str()) || atoi(new_width.c_str()) < 4);
	this -> width = atoi(new_width.c_str());

	do{
		cout << "Enter an integer length of the board 4 or greater: ";
		getline(cin,new_length);
	}while(!atoi(new_length.c_str()) || atoi(new_length.c_str()) < 4);
	this -> length = atoi(new_length.c_str());
	return;
}

char Game::get_user_input(){
	
	cout << "Press 'WASD' to move, 'F' to shoot an arrow, or '.' to quit: ";
	system("stty raw");
	char input = getchar();
	system("stty cooked");
	cout << endl;
	return input;
}

void Game::set_player_position(){
	char input = this -> get_user_input();
	//cout << "( " << player_x << ", " << player_y << " )" << endl;
	input = check_bats(input);
	if(player_y != 0){
		if (input == 119){ //w
			player_y -= 1;
		}	
	}

	if(player_x != 0){
		if (input == 97){ //a
			player_x -= 1;
		}
	}

	if(player_y != length - 1){
		if (input == 115){ //s
			player_y += 1;
		}	
	}

	if(player_x != width - 1){
		if (input == 100){//d
			player_x += 1;
		}
	}
	if(input == 'f'){
		if(this -> arrows_count > 0){
			this -> arrows_action();
		}
	}

	if(input == '.'){
		cout << "Exiting game..." << endl;
		this -> game_over = true;
		return;
	}
}

char Game::check_bats(char input){ // did it this way so they can't waste their bats against a wall
	char new_input = input;
	if(this -> bat_count > 0){
		if(player_y != 0){
			if (input == 115){ //w = 119, if w conditions are met and s is pressed
				new_input = 'w'; //w 
				this -> bat_count-=1;
			}	
		}

		if(player_x != 0){
			if (input == 100){ //a = 97
				new_input = 'a'; 
				this -> bat_count-=1;
			}
		}

		if(player_y != length - 1){
			if (input == 119){ //s = 115
				new_input = 's';
				this -> bat_count-=1;
			}	
		}

		if(player_x != width - 1){
			if (input == 97){//d = 100
				new_input = 'd';
				this -> bat_count-=1;
			}
		}
	}
	//cout << "Bat count: " << this -> bat_count << endl;
	return new_input;
}

void Game::arrows_action(){
	char arrow_direction = 'p';
	do{
		system("stty raw");
		cout << "You ready an arrow and aim..." << endl;
		arrow_direction = getchar();
		system("stty cooked");

		if(arrow_direction == 'w')
			this -> arrows_action_w();
		else if(arrow_direction == 'a')
			this -> arrows_action_a();
		else if(arrow_direction == 's')
			this -> arrows_action_s();
		else if(arrow_direction == 'd')
			this -> arrows_action_d();
		else
			arrow_direction = 'p';
		}while(arrow_direction == 'p');
	this -> arrows_count -=1;
}




void Game::arrows_action_w(){
	bool arrow_shot = false;
	for(int j = 1; j < 4; j++){ //bound checker
		if(arrow_shot == false){
			if(player_y >= j){ //make sure arrow won't go out of bounds
				for(int i = 1; i <= j; i++){ //run 3 squares
					if(this -> grid[player_y - i][player_x] -> get_event()){ //if there's event, check the event
						if(this -> grid[player_y - i][player_x] -> get_event() -> get_symbol() == 'W'){
							arrow_shot = true;
							this -> wumpus_death();
						}
					}
				}
			}
		}	
	}
	if(this -> wumpus_alive == true){
		this -> new_wumpus_location();
	}
}

void Game::arrows_action_a(){
	bool arrow_shot = false;
	for(int j = 1; j < 4; j++){ //bound checker
		if(arrow_shot == false){
			if(player_x >= j){ //make sure arrow won't go out of bounds
				for(int i = 1; i <= j; i++){ //run 3 squares
					if(this -> grid[player_y][player_x - i] -> get_event()){ //if there's event, check the event
						if(this -> grid[player_y][player_x - i] -> get_event() -> get_symbol() == 'W'){
							arrow_shot = true;
							this -> wumpus_death();
						}
					}
				}
			}
		}	
	}
	if(this -> wumpus_alive == true){
		this -> new_wumpus_location();
	}
}

void Game::arrows_action_d(){
	bool arrow_shot = false;
	for(int j = 1; j < 4; j++){ //bound checker
		if(arrow_shot == false){
			if(player_x <= this -> width - j){ //make sure arrow won't go out of bounds
				for(int i = 1; i <= j; i++){ //run up to 3 squares
					if(this -> grid[player_y][player_x + i - 1] -> get_event()){ //if there's event, check the event
						if(this -> grid[player_y][player_x + i - 1] -> get_event() -> get_symbol() == 'W'){
							arrow_shot = true;
							this -> wumpus_death();
						}
					}
				}
			}
		}	
	}
	if(this -> wumpus_alive == true){
		this -> new_wumpus_location();
	}
}

void Game::arrows_action_s(){
	bool arrow_shot = false;
	for(int j = 1; j < 4; j++){ //bound checker
		if(arrow_shot == false){
			if(player_y <= this -> length - j){ //make sure arrow won't go out of bounds
				for(int i = 1; i <= j; i++){ //run up to 3 squares
					if(this -> grid[player_y + i - 1][player_x] -> get_event()){ //if there's event, check the event
						if(this -> grid[player_y + i - 1][player_x] -> get_event() -> get_symbol() == 'W'){
							arrow_shot = true;
							this -> wumpus_death();
						}
					}
				}
			}
		}	
	}
	if(this -> wumpus_alive == true){
		this -> new_wumpus_location();
	}
}

void Game::wumpus_death(){
	this -> wumpus_alive = false;
	cout << "You have slain the Wumpus!" << endl;
	delete grid[wumpus_y][wumpus_x] -> get_event();
	delete grid[wumpus_y][wumpus_x];
	this -> grid[wumpus_y][wumpus_x] = new Room();

}

void Game::new_wumpus_location(){
	int i = -1, j = -1;

	if(rand()%4 == 0){
		cout << "The Wumpus remains..." << endl;
		return;
	}
	else{
		cout << "The Wumpus hears your arrow and flees!" << endl;
		delete this -> grid[wumpus_y][wumpus_x] -> get_event();
		this -> grid[wumpus_y][wumpus_x] -> set_event(NULL);
		//delete this -> grid[wumpus_y][wumpus_x];
		//this -> grid[wumpus_y][wumpus_x] = new Room(); //make new room at old wumpus spot

		do{
			i = rand() % this -> length;
			j = rand() % this -> width;
		}while (this-> grid[i][j] -> get_event() != NULL); //regenerate if occupied already

		//this -> grid[i][j] = new Room(); 
		if(this -> grid[i][j] -> get_event())
			delete this -> grid[i][j] -> get_event();
		//this -> grid[i][j] = new Room();
		this -> grid[i][j] -> set_event(new Wumpus());
		this -> wumpus_x = j;
		this -> wumpus_y = i;

	}
}

void Game::detect_percept(){
	if(this -> player_y != 0){
		if(this -> grid[player_y - 1][player_x] -> get_event()){
			this -> grid[player_y - 1][player_x] -> get_event() -> print_percept();
			cout << endl;
		}
	}

	if(this -> player_x != 0){
		if(this -> grid[player_y][player_x - 1] -> get_event()){
			this -> grid[player_y][player_x - 1] -> get_event() -> print_percept();
			cout << endl;
		}
	}

	if(this -> player_y != this -> length - 1){
		if(this -> grid[player_y + 1][player_x] -> get_event()){
			this -> grid[player_y + 1][player_x] -> get_event() -> print_percept();
			cout << endl;
		}
	}

	if(this -> player_x != this -> width - 1){
		if(this -> grid[player_y][player_x + 1] -> get_event()){
			this -> grid[player_y][player_x + 1] -> get_event() -> print_percept();
			cout << endl;
		}
	}

}

void Game::check_event(){
	if(this -> grid[player_y][player_x] -> get_event()){
		this -> pit_interaction();
		this -> wumpus_interaction();
		this -> bats_interaction();
		this -> gold_interaction();
	}
}

void Game::player_death(){
	cout << "You have died!" << endl;
	this -> player_alive = false;
}

bool Game::get_player_alive(){
	return this -> player_alive;
}

void Game::pit_interaction(){
	if(this -> grid[player_y][player_x] -> get_event() -> get_symbol() == 'O'){
		cout << "You fell into a pit! Unlucky :(" << endl << endl;
		this -> player_death();
	}
}

void Game::wumpus_interaction(){
	if(this -> grid[player_y][player_x] -> get_event() -> get_symbol() == 'W'){
		cout << "You got eaten by the Wumpus!" << endl << endl;
		this -> player_death();
	}
}

void Game::bats_interaction(){
	if(this -> grid[player_y][player_x] -> get_event() -> get_symbol() == 'B'){
		cout << "A swarm of bats disorients you! " << endl << endl;
		this -> bat_count = 5;
	}
}

void Game::gold_interaction(){
	if(this -> grid[player_y][player_x] -> get_event() -> get_symbol() == '$'){
		cout << "You picked up the gold! " << endl << endl;
		this -> has_gold = true;
	}
}

void Game::check_win_game(){
	//if at escape rope
	if(this -> player_x == this -> initial_x && this -> player_y == this -> initial_y){
		// if wumpus is dead and gold is collected
		if(wumpus_alive == false && has_gold == true){
			cout << "CONGRATUALATIONS! You killed the Wumpus and made it back to the escape rope!" << endl;
			game_won = true;
			//this -> clear_memory();
		}

	}

}

bool Game::get_game_won(){
	return this -> game_won;
}

void Game::clear_memory(){
	for(int i = 0; i < this -> length; i++){
		for(int j = 0; j < this -> width; j++){
			if(this -> grid[i][j]){
				if(this ->grid[i][j] -> get_event()){
					delete this -> grid[i][j] -> get_event();
				}

				delete this -> grid[i][j];
			}

		}
	}
}
