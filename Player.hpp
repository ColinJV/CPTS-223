#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class Player {
public:
    // Constructor
    Player();
    Player(string& name, int score) : mPlayerName(name), mPlayerScore(score) {};

    // Copy constructor
    Player(Player& copy);

    // Destructor
    ~Player();

    // Accessor
    string getPlayerName(void) const;
    int getPlayerScore(void) const;

    // Mutator
    void setPlayerName(const string& newName);
    void setPlayerScore(const int& newScore);
    void incrementPlayerScore(const int& incrementer);

    // Other
    bool checkForDuplicates(Player* targetData);
    void printDataToFile(ofstream& outputFile);

private:
    string mPlayerName;
    int mPlayerScore;
};


#endif