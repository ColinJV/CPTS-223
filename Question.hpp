#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Question {
public:
	// Constructor
	Question() {
		mCommandName = "";
		for (int i = 0; i < 4; i++) {
			mDescriptions[i] = "";
		}
	}
	Question(string commandName, string* descriptions) {
		mCommandName = commandName;
		for (int i = 0; i < 4; i++) {
			mDescriptions[i] = descriptions[i];
		}
	}

	// Copy Constructor
	Question(Question& copy) {
		mCommandName = copy.getCommandName();
		for (int i = 0; i < 4; ++i) {
			mDescriptions[i] = copy.getDescription(i);
		}
	}

	// Destructor
	~Question() {
		// nothing
	}

	// Accessors
	string getCommandName() {
		return(mCommandName);
	}
	string getDescription(int index) {
		return(mDescriptions[index]);
	}

	// Other
	bool askQuestion() {
		bool correct = false;
		int selection = -1;
		string userInput = "";
		cout << "Command: " << mCommandName << endl;
		cout << "0. " << mDescriptions[0] << endl;
		cout << "1. " << mDescriptions[1] << endl;
		cout << "2. " << mDescriptions[2] << endl;
		cout << "3. " << mDescriptions[3] << endl;
		cin >> userInput;
		selection = stoi(userInput);
		if (selection == 0) {
			correct = true;
		}
		return(correct);
	}

	void displayCorrectAnswer() {
		cout << "Correct answer: " << mDescriptions[0] << endl;
	}

private:
	string mCommandName;
	string mDescriptions[4];

};

#endif