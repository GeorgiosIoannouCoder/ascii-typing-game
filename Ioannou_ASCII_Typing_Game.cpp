// ================================================================================================
// Copyright (C) 2020 by Georgios Ioannou
//
// FILE: Ioannou_ASCII_Typing_Game.cpp
//
// This file implements an ASCII typing game. Instructions of the game are found in the README.md
// file of the repository.
// 
// Written by: Georgios Ioannou, 2020
// ================================================================================================
//
#include <iostream>  // Provides cout and endl
#include <string>    // Provides string
#include <cstdlib>   // Provides rand() and srand() functions
#include <ctime>     // Provides time() function
#include <chrono>    // Provides high_resolution clock and duration_cast function
using namespace std;
using namespace std::chrono;

//Function declarations.
//Function definitions are after the main function.

//Function printStartOfGame declaration.
void printStartOfGame(const int points, const string generatedString);

//Function generateString declaration.
string generateString(string& generatedString); 

//Function sortString declaration.
void sortString(string& generatedString);

//Function inTheInterval declaration.
bool inTheInterval(const int elapsedTime);

//Function delayedTimePoints declaration.
int delayedTimePoints(int elapsedTime, const bool withinTheInterval);

//Function compareString declaration.
bool compareStrings(const string& generatedString, const string& inputString);

//Function offset declaration.
//Function offset calculates and returns the total offset of mistaken letters between the generated random string and the input string.
int offset(const string& generatedString, string& inputString);

//Function equalButWithinTheInterval declaration.
int equalButIsWithinTheInterval(const bool withinTheInterval, const int pointsForDelayedTime);

//Function notEqualButIsWithinTheInterval declaration.
int notEqualButIsWithinTheInterval(const string& generatedString, string& inputString, const bool withinTheInterval, const int pointsForDelayedTime);

//Function totalPointsDeducted declaration.
int totalPointsDeducted(const bool equal, const string& generatedString, string& inputString, const bool withinTheInterval, const int pointsForDelayedTime);

int main()
{
	srand(time(0));
	string generatedString = "";
	string inputString = "";
	int finalPoints = 1000;
	int elapsedTime = 0;
	int pointsForDelayedTime = 0;
	int x = 0;
	int gainPoints = 0;
	int penalty = 0;
	bool equal = false;
	bool withinTheInterval = false;

	while (finalPoints <= 5000 && finalPoints >= 0) {
		//Generate a random string of 7 letters being mixed with lower and upper cases.
		generatedString = generateString(generatedString);
		
		//Print the first line of the typing lesson game.
		printStartOfGame(finalPoints, generatedString);
		
		//Sort the generated random string in ASCII (alphabetical) order.
		sortString(generatedString);
		
		//Get input string from the user and calculate the elapsed time (the time that the user needs to input the string).
		auto start = high_resolution_clock::now();
		cin >> inputString;
		auto finish = high_resolution_clock::now();
		auto totalElapsedTime = duration_cast<milliseconds>(finish - start);
		elapsedTime = totalElapsedTime.count();
		
		//Determine if the elapsed time is within the interval of 12,000 msec.
		withinTheInterval = inTheInterval(elapsedTime);
		
		//Calculate the points lost considering the delayed time. Points lost are equal to the amount of delayed time in millisecond.
		pointsForDelayedTime = delayedTimePoints(elapsedTime, withinTheInterval);
		
		//Determine if the sorted generated random string is equal to the input sring.
		equal = compareStrings(generatedString, inputString);
		
		//Calculate the total points deducted.
		x = totalPointsDeducted(equal, generatedString, inputString, withinTheInterval, pointsForDelayedTime);
		gainPoints = 0;
		penalty = 0;
		if (x > 0) {
			gainPoints = x;
		}
		else {
			penalty = -x;
		}
		
		//Calculate the final points after the gain points have been added or the penalty is subtracted.
		finalPoints = finalPoints + gainPoints - penalty;
		cout << endl;
	}
	cout << "Bye..." << endl;
	return 0;
}

//Function definitions.

//Function printStartOfGame definition.
void printStartOfGame(const int points, const string generatedString) {
	cout << "Your current points " << points << ", type in order - > " << generatedString << " : ";
}

//Function generateString definition.
string generateString(string& generatedString) {
	generatedString = "";
	int choice = -1;
	char c;
	for (int i = 0; i < 7; i++) {
		choice = rand() % 2;
		if (choice == 0) {
			c = (rand() % 26 + 65);
			generatedString.push_back(c);
		}
		else {
			c = (rand() % 26 + 97);
			generatedString.push_back(c);
		}
	}
	return generatedString;
}

//Function sortString definition.
void sortString(string& generatedString) {
	char temp;
	for (int i = 0; i < generatedString.size(); i++) {
		for (int j = i + 1; j < generatedString.size(); j++) {
			if (generatedString.at(i) > generatedString.at(j)) {
				temp = generatedString.at(j);
				generatedString.at(j) = generatedString.at(i);
				generatedString.at(i) = temp;
			}
		}
	}
}

//Function inTheInterval definition.
bool inTheInterval(const int elapsedTime) {
	bool withinTheInterval = false;
	int time = 0;
	time = 12000 - elapsedTime;
	if (time >= 0) {
		withinTheInterval = true;
	}
	return withinTheInterval;
}

//Function delayedTimePoints definition.
int delayedTimePoints(int elapsedTime, const bool withinTheInterval) {
	int totalTime = 0;
	totalTime = 12000 - elapsedTime;
	if (withinTheInterval == true) {
		cout << elapsedTime << " milliseconds, you made it wihtin the interval of 12000..." << endl;
		return 0;
	}
	else {
		cout << elapsedTime << " milliseconds, you *failed* it within the interval of 12000..." << endl;
		return abs(totalTime);
	}
}

//Function compareStrings definition.
bool compareStrings(const string& generatedString, const string& inputString) {
	bool equal = false;

	if (generatedString.compare(inputString) == 0) {
		equal = true;
	}
	return equal;
}

//Function offset definition.
//Function offset calculates and returns the total offset of mistaken letters between the generated random string and the input string.
int offset(const string& generatedString, string& inputString) {
	int offsetPointsDeducted = 0;

	while (inputString.size() != 7) {
		inputString.push_back(' ');
	}
	for (int i = 0; i < 7; i++) {
		offsetPointsDeducted = offsetPointsDeducted + abs((generatedString.at(i) - inputString.at(i)));
	}
	cout << "String offest is " << offsetPointsDeducted << ", ";
	return offsetPointsDeducted;
}

//Function equalButIsWithinTheInterval definition.
int equalButIsWithinTheInterval(const bool withinTheInterval, const int pointsForDelayedTime) {
	if (withinTheInterval == true) {
		return 500;
	}
	else {
		cout << "Your total penalty is " << pointsForDelayedTime << "..." << endl;
		return -(pointsForDelayedTime);
	}
}

//Function notEqualButIsWithinTheInterval definition.
int notEqualButIsWithinTheInterval(const string& generatedString, string& inputString, const bool withinTheInterval, const int pointsForDelayedTime) {
	if (withinTheInterval == true) {
		return -(offset(generatedString, inputString));
	}
	else {
		return -((2 * (offset(generatedString, inputString))) + pointsForDelayedTime);
	}
}

//Function totalPointsDeducted definition.
int totalPointsDeducted(const bool equal, const string& generatedString, string& inputString, const bool withinTheInterval, const int pointsForDelayedTime) {
	int penalty = 0;
	
	//The generated random string is equal to the input string.
	if (equal == true) {
		penalty = equalButIsWithinTheInterval(withinTheInterval, pointsForDelayedTime);
	}
	
	//The generated random string is not equal to the input string.
	if (equal == false) {
		cout << "Answer must be \"" << generatedString << "\"" << endl;
		penalty = notEqualButIsWithinTheInterval(generatedString, inputString, withinTheInterval, pointsForDelayedTime);
		cout << "your total penalty is " << abs(penalty) << "..." << endl;
	}
	return penalty;
}
