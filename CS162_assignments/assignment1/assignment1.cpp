/*
Program: assignment1.cpp
Author: Skylar Soon
Date: 04/10/2023
Description: A basktball shooting contest between any number of players with
Input: integers of amount of players, selection of money ball rack per player
Output: scoreboard of missed/made shots per player, total scores per rack/player, and the winner of the game
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

int getPlayerAmount(); //get number of players
int int_checker(string); //checks if input is an integer
int getMoneyBall(int currentPlayer); // get moneyball rack for player, return value
int shootingOutput(int playerAmount); //creates a dynamic array to hold total scores and calls other functions to output scoreboards to screen
int moneyBallRackOutput(); //scoreboard output for moneyballs, returns scores for each rack
int regularRackOutput(); //scoreboard output for regular balls, returns scores for each rack
int determineWinner(int playerAmount, int array[]); //determine the winner from the array of players
void playAgainInput(int &playAgain); //ask the user if they want to play again 


int main(){
	srand(time(NULL)); //seeds random

	int playAgain = 0;
	do{
		int playerAmount = getPlayerAmount(); //gets player amount
		shootingOutput(playerAmount);
		playAgainInput(playAgain);
	}while(playAgain == 1);

	cout << "\nThank you for playing the Basketball Shooting Contest, have a nice day! \n" << endl;

	return 0;
}

int int_checker(string num){ //checks a string if it is an int and returns it as an int if it is
	int integer = 0;

	for(int i = 0; i < num.length(); i++){
		if(num[i] >= 48 && num[i] <= 57){
			integer = (integer * 10) + (num[i]-48);
		}
		else
			return 0;
	}
	return integer;

}

int getPlayerAmount(){ //prompts user to enter player amount and gets player amount
	cout << " \n------------";
	string playerAmountInput = "";
	int playerAmount = 0;
	while(true){
		cout << "\nWelcome to the Basketball Shooting Contest! \nHow many players are playing (2 + players)? Enter an integer: ";
		getline(cin, playerAmountInput);
		cout << "\n";
		playerAmount = int_checker(playerAmountInput);
		
		if(playerAmount > 1 )
			break;
		cout << "Error! Make sure to enter a positive integer greater than 1. \n " << endl;
	}

	return playerAmount;
}


int getMoneyBall(int currentPlayer){ //prompts user to enter money ball rack and returns it

	string moneyBallRackInput = "";
	int moneyBallRack = 0;
	do{
		cout << "Player " << currentPlayer+1 << ": \nPlease enter where you want to put your money ball rack (Enter 1-5): ";
		getline(cin, moneyBallRackInput);
		moneyBallRack = int_checker(moneyBallRackInput);
		cout << "\n";

		if (moneyBallRack > 0 && moneyBallRack <= 5)
			break;
		else
			cout << "Error! Make sure to enter an integer 1 - 5. \n" << endl; 

	} while(moneyBallRack < 1 || moneyBallRack > 5);
	
	return moneyBallRack;
		
}


int shootingOutput(int playerAmount){
	int *finalScores = new int[playerAmount]; //initialize dynamic array to hold all totals

	for(int i = 0; i < playerAmount; i++){ //runs for each player
		int playerTotal = 0;
		int moneyBallRack = getMoneyBall(i);

		for(int j = 0; j < 5; j++){ // runs for 5 racks per player
			cout << "Rack " << j + 1 << ": ";
			if(j == (moneyBallRack-1))
				playerTotal += moneyBallRackOutput();
			else
				playerTotal += regularRackOutput();
			cout << "\n";
		}
		cout << "\nPlayer " << i+1 << " total: " << playerTotal << "\n" << endl;
		finalScores[i] = playerTotal;
		cout << "------------ \n" << endl;
	}
	determineWinner(playerAmount, finalScores);
	delete [] finalScores; //remove memory allocation from heap
}


int moneyBallRackOutput(){ //displays money ball rack makes/misses/score, returns rack score
	string rack[5];
	int rackTotal = 0;
	for(int i = 0; i < 5; i++){
		if(rand()%2 == 0){
			rack[i] = "M ";
			rackTotal += 2;
		}
		else
			rack[i] = "X ";
		cout << rack[i];
	}
	cout << "| Score: " << rackTotal; 
	return rackTotal;
}

int regularRackOutput(){ //displays regular ball rack makes/misses/score, returns rack score
	string rack[5];
	int rackTotal = 0;
	for(int i = 0; i < 4; i++){ //first 4 balls of each rack
		if(rand()%2 == 0){
			rack[i] = "O ";
			rackTotal += 1;
		}
		else
			rack[i] = "X ";
		cout << rack[i];
	}

	if(rand()%2 == 0){ //moneyball at end of rack
		rack[4] = "M ";
		rackTotal += 2;
	}
	else
		rack[4] = "X ";
	cout << rack[4];
	cout << "| Score: " << rackTotal;
	return rackTotal;
}

int determineWinner(int playerAmount, int array[]){ //calculates the winner or determines if there's a tie
	int highestScore = 0; 
	int highestPlayer = 0;
	int highestPlayerTie = 0;
	int highestPlayerTieScore = 0;

	for(int i = 0; i < playerAmount; i++){
		cout << "Player " << i+1 << " score: " << array[i] << endl;
		if(array[i] > highestScore){
			highestScore = array[i];
			highestPlayer = i+1;
		}
		else if (array[i] == highestScore){
			highestPlayerTie = i+1;
			highestPlayerTieScore = array[i];
		}
	}
	if (highestPlayerTie > 0 && highestPlayerTieScore >= highestScore){
		cout << "\nThere has been a tie!" << endl;
		cout << "Player " << highestPlayer << " and Player " << highestPlayerTie << " have both won the game! Congratualations!" << endl;
	}
	else
		cout << "\nThe winner is Player " << highestPlayer << "! Congratualations! \n" << endl;
	cout << "------------" << endl;

}

void playAgainInput(int &playAgain){ //outputs question and returns playAgain value
	string playAgainInput = "";
	while(true){
		cout << "\nDo you want to play again? \n";
		cout << "Enter 1 if yes, or enter 0 if no: ";
		getline(cin, playAgainInput);
		playAgain = int_checker(playAgainInput)+1;

		if(playAgain >= 1 && playAgain <= 2){
			playAgain -= 1;
			break;
		}
		cout << "Error! Please enter either 1 or 0." << endl;
	}

}

