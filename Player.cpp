#include "Player.hpp"

/********************************************************************************************************
* Function: Player constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Player object with default data
* Input parameters: none
* Returns: Player object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Player::Player() {
	mPlayerName = "";
	mPlayerScore = 0;
}

/********************************************************************************************************
* Function: Player copy constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Player object with data from another 
* Input parameters: none
* Returns: Player object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Player::Player(Player& copy) {
	mPlayerName = copy.getPlayerName();
	mPlayerScore = copy.getPlayerScore();
}

/********************************************************************************************************
* Function: Player destructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Destroys a Player object
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Player::~Player() {
	// ok people move along nothing to see here
}

/********************************************************************************************************
* Function: getPlayerName()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns the mPlayerName data member of a Player object
* Input parameters: void
* Returns: string mPlayerName, the name of a player
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
string Player::getPlayerName(void) const {
	return(mPlayerName);
}

/********************************************************************************************************
* Function: getPlayerScore()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns the score for a Player object
* Input parameters: none
* Returns: int mPlayerScore
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
int Player::getPlayerScore(void) const {
	return(mPlayerScore);
}

/********************************************************************************************************
* Function: setPlayerName()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mPlayerName member of a Player object to the value of the string input parameter
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Player::setPlayerName(const string& newName) {
	mPlayerName = newName;
}

/********************************************************************************************************
* Function: setPlayerScore()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mPlayerScore member of a Player object to the value of the int input parameter.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Player::setPlayerScore(const int& newScore) {
	mPlayerScore = newScore;
}

/********************************************************************************************************
* Function: incrementPlayerScore()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Adds the input parameter to the mPlayerScore member of a Player object. Checks the value
* of mPlayerScore and, if it is less than 0, resets the value to 0 so that a Player's score may never be
* negative.
* Input parameters: const int& incrementer, a positive or negative integer value to modify score.
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Player::incrementPlayerScore(const int& incrementer) {
	mPlayerScore += incrementer;
	if (mPlayerScore < 0) {
		mPlayerScore = 0;
	}
}

/********************************************************************************************************
* Function: checkForDuplicates()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns a boolean based on the value of the mPlayerName member of this Player and an input
* parameter Player's mPlayerName.
* Input parameters: none
* Returns: bool, true if this Player's mPlayerName == targetData.mPlayerName, false otherwise.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
bool Player::checkForDuplicates(Player* targetData) {
	return(targetData->getPlayerName() == this->getPlayerName());
}

/********************************************************************************************************
* Function: printDataToFile()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Prints Player information to an output file provided by the input parameter
* Input parameters: ofstream& outputFile, a file to which Player information is output
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Player::printDataToFile(ofstream& outputFile) {
	outputFile << this->getPlayerName() << ',' << this->getPlayerScore() << std::endl;
}