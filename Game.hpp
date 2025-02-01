#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "List.hpp"
#include "Data.hpp"
#include "Question.hpp"
#include <fstream>
#include <iostream>

#define MAX_SIZE 10

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

class Game {
public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Methods
	void startGame();

private:
	int mPlayerListSize;
	int mCommandListSize;
    Player mPlayerList[MAX_SIZE];
    int mActivePlayer;
	List<Data> mCommandList;
    Node<Data>* mCurrent;

    void setCurrentPlace();
    int displayMainMenu();
    void displayRules();
    void playNewGame();
    void loadPreviousGame();
    void playGame();
    void addCustomCommand();
    void removeCommand();
    void displayAllCommands();
    void saveAndQuit();
    Data* makeNewCommand();
    void displayCustomCommandExists();
    void displayCustomCommandAdded();
    void displayCommandDoesNotExist();
    void displayCommandRemoved();
    void displayPlayerProfileNotFound();
    void displayEndOfGame();
    string getTargetCommand();
    void loadPlayerProfiles();
    void loadCommands();
    string getPlayerName();
    void saveCommandList();
    void savePlayerList();
    int getNumberOfQuestions();
    Question* generateQuestion();
    string getRandomDescription();
    void updatePlayerPoints(bool correct);
    bool addNewPlayerToList();
    void outputPlayerProfiles(ofstream& outputFile);
};

#endif