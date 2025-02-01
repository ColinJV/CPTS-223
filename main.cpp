/********************************************************************************************************
* Programmer: Colin Van Dyke
* Date Created: 01/31/2025
* Class: CPTS223 Spring 2025
* Description: Implements a simple trivia game testing knowledge of Linux shell commands. Loads commands
* and their descriptions from a .csv file into a singly linked list and player profiles from another .csv
* file into an array of max size 10. Displays a menu allowing the player to select to see rules, play a
* game from a new profile, load an existing profile, add or remove commands, display all commands, or save
* game data and quit.
* Returns: return type and a description of what the return value is.
* Preconditions: Any conditions which MUST be true prior to calling the function
* Postconditions: Any condition which WILL be true after a function returns or at the end of a code segment
* (you can often ignore this except for in specific circumstances such as when using pointers.)
********************************************************************************************************/

#include "Game.hpp"

int main(void) {
    srand((unsigned int)time(NULL));
    Game newGame;
    newGame.startGame();
    return(0);
}