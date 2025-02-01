#include "Game.hpp"

/********************************************************************************************************
* Function: Game constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Game object. Invokes List and Player constructors implicitly.
* Input parameters: none
* Returns: Game object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Game::Game() {
	mPlayerListSize = 0;
	mCommandListSize = 0;
    mCommandList.setHead(nullptr);
    mCurrent = nullptr;
    mActivePlayer = -1;
}

/********************************************************************************************************
* Function: Game destructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Destroys a Game object
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Game::~Game() {
    // ok people move along nothing to see here
}

/********************************************************************************************************
* Function: playGame()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Contains primary gameplay loop for the trivia game. Gets a number of questions to ask from
* the player and sets the current place to the head of the list. Generates questions and presents them
* to the player, modifying the player's score based on whether the answer is correct, until the
* predetermined number of questions has been asked. Displays a message indicating the game has ended.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::playGame() {
    int questions = getNumberOfQuestions();
    this->setCurrentPlace();

    while (questions > 0) {
        Question* currentQuestion = generateQuestion();
        bool correct = currentQuestion->askQuestion();
        currentQuestion->displayCorrectAnswer();
        updatePlayerPoints(correct);
        --questions;
        mCurrent = mCurrent->getNext();
        delete currentQuestion;
    }
    displayEndOfGame();
}

/********************************************************************************************************
* Function: displayEndOfGame()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Prints a chatter message to cout indicating the game has finished.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayEndOfGame() {
    cout << "End of game. Thanks for playing." << endl;
}

/********************************************************************************************************
* Function: updatePlayerPoints()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Adds positive or negative 1 to the player's score based on the value of a boolean indicating
* whether the player has answered correctly. If the player's score is not greater than 0, decrementing
* does not occur to prevent the player's score being negative.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::updatePlayerPoints(bool correct) {
    if (correct) {
        mPlayerList[mActivePlayer].incrementPlayerScore(1);
    }
    else if (mPlayerList[mActivePlayer].getPlayerScore() > 0){
        mPlayerList[mActivePlayer].incrementPlayerScore(-1);
    }
}

/********************************************************************************************************
* Function: generateQuestion()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Generates a Question to ask the player, populating the command string with a Linux shell
* command, and populating the description strings with one correct and three incorrect descriptions. Calls
* getRandomDescription() to generate incorrect descriptions.
* Input parameters: none
* Returns: Question* newQuestion, a pointer to the Question object generated
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Question* Game::generateQuestion() {
    string command = mCurrent->getData()->getCommand();
    string description[4];
    description[0] = mCurrent->getData()->getDescription();

    for (int i = 1; i < 4; ++i) {
        description[i] = getRandomDescription();
    }
    
    Question* newQuestion = new Question(command, description);
    return(newQuestion);
}

/********************************************************************************************************
* Function: getRandomDescription()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Generates a random number, then traverses the List of Linux shell commands until it has
* done that number of traversals. Grabs the description in the Node that it lands on and returns the
* description if it does not match the description of the correct answer.
* Input parameters: void
* Returns: string description, the description of a random Linux shell command
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
string Game::getRandomDescription() {
    bool validDescriptionFound = false;
    Node<Data>* pCurrent = mCurrent;
    string description = "";

    while (pCurrent != nullptr && !validDescriptionFound) {
        int targetNode = rand() % mCommandListSize;
        while (pCurrent != nullptr && targetNode > 0) {
            if (pCurrent->getNext() == nullptr) {
                pCurrent = this->mCommandList.getHeadPtr();
            }
            else {
                pCurrent = pCurrent->getNext();
                --targetNode;
            }
        }

        if (pCurrent != nullptr) {
            description = pCurrent->getData()->getDescription();
        }

        if (description != mCurrent->getData()->getDescription()) {
            validDescriptionFound = true;
        }
    }
    return description;
}

/********************************************************************************************************
* Function: setCurrentPlace()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Sets the mCurrent marker to the head of the list at the start of a game.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::setCurrentPlace() {
    this->mCurrent = mCommandList.getHeadPtr();
}

/********************************************************************************************************
* Function: getNumberOfQuestions()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Gets an input from the user for the number of questions to ask during the game.
* Input parameters: none
* Returns: int numberOfQuestions, the number of questions to ask during a game.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
int Game::getNumberOfQuestions() {
    string userInput = "";
    int numberOfQuestions = 0;
    cout << "Please enter the number of questions to answer." << endl;
    cin >> userInput;
    numberOfQuestions = stoi(userInput);
    return(numberOfQuestions);
}

/********************************************************************************************************
* Function: startGame()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Loads player profiles and command list from .csv files into memory. Displays a main menu
* and executes various functions based on player input.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::startGame() {
    int playerInput = 0;

    this->loadPlayerProfiles();
    this->loadCommands();

    do {
        playerInput = this->displayMainMenu();

        switch (playerInput) {
        case 1:
            this->displayRules();
            break;
        case 2:
            this->playNewGame();
            break;
        case 3:
            this->loadPreviousGame();
            break;
        case 4:
            this->addCustomCommand();
            break;
        case 5:
            this->removeCommand();
            break;
        case 6:
            this->displayAllCommands();
            break;
        case 7:
            this->saveAndQuit();
            break;
        default:
            break;
        }
    } while (playerInput != 7);
}

/********************************************************************************************************
* Function: displayMainMenu()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays the main menu indicating the various functionalities that the player can select.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
int Game::displayMainMenu() {
    int playerIntInput = 0;
    string playerInput = "";

    while (playerIntInput <= 0 || playerIntInput > 7) {
        cout << "Main Menu" << '\n';
        cout << "1. Game Rules" << '\n';
        cout << "2. Play New Game" << '\n';
        cout << "3. Load Previous Game" << '\n';
        cout << "4. Add Custom Command" << '\n';
        cout << "5. Remove Command" << '\n';
        cout << "6. Display All Commands" << '\n';
        cout << "7. Save and Exit" << endl;
        cin >> playerInput;

        playerIntInput = stoi(playerInput);
        if (playerIntInput <= 0 || playerIntInput > 7) {
            cout << "Invalid entry. Please try again." << endl;
        }
    }

    return(playerIntInput);
}

/********************************************************************************************************
* Function: displayRules()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays the game rules.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayRules() {
    cout << "This game tests knowledge of 30 popular Linux commands. The player will be given\n";
    cout << "a inux command and must select the correct command description from various options.\n";
    cout << "One point will be awarded for correct answers while one point is deducted for\n";
    cout << "incorrect answers." << endl;
}

/********************************************************************************************************
* Function: addCustomCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a new Data item and inserts it in the List of Linux shell commands if the command
* is not already in the list.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::addCustomCommand() {
    Data* newData = this->makeNewCommand();

    if (this->mCommandList.duplicateExists(newData)) {
        this->displayCustomCommandExists();
        delete newData;
    }
    else {
        mCommandList.insertAtFront(newData);
        this->displayCustomCommandAdded();
    }
}

/********************************************************************************************************
* Function: makeNewCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a new Data object with a user-generated command name and description. Returns the
* address of the new Data object.
* Input parameters: none
* Returns: Data* newData, the address of a newly generated Data object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data* Game::makeNewCommand() {
    string customCommand = "", customDescription = "", userConfirmInput = "";
    int userConfirm = -1;
    while (userConfirm != 1) {
        cout << "Please enter the command name: " << endl;
        cin.clear();
        cin.ignore();
        cin >> customCommand;
        cout << "Please enter the command description: " << endl;
        cin.ignore();
        getline(cin, customDescription);

        cout << "You've entered:\n";
        cout << "Command: " << customCommand << '\n';
        cout << "Description: " << customDescription << '\n';
        cout << "Press 1 to confirm the entry, or 0 to repeat.\n";
        cin >> userConfirmInput;
        userConfirm = stoi(userConfirmInput);
        if (userConfirm != 0 && userConfirm != 1) {
            cout << "Error reading input. Please repeat custom command entry.\n";
        }
    }

    Data* newData = new Data(customCommand, customDescription);
    return(newData);
}

/********************************************************************************************************
* Function: displayCustomCommandExists()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays a message indicating that a command already exists in the List.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayCustomCommandExists() {
    cout << "The command supplied already exists in the list of commands." << endl;
}

/********************************************************************************************************
* Function: displayCustomCommandAdded()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays a message indicating that a command has been added to the List.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayCustomCommandAdded() {
    cout << "The command supplied has been added to the list!" << endl;
}

/********************************************************************************************************
* Function: displayCommandDoesNotExist()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays a message indicating a command does not exist in the list.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayCommandDoesNotExist() {
    cout << "The command supplied does not exist in the list." << endl;
}

/********************************************************************************************************
* Function: displayCommandRemoved()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays a message indicating a command has been removed from the list.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayCommandRemoved() {
    cout << "The command has been removed from the list." << endl;
}

/********************************************************************************************************
* Function: displayPlayerProfileNotFound()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays a message indicating that a player profile being searched for was not found.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayPlayerProfileNotFound() {
    cout << "The supplied player profile was not found in save data. Returning to main menu." << endl;
}

/********************************************************************************************************
* Function: removeCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Prompts the player for a command to be removed from the List. Removes it if it exists, or
* displays an error message if it does not exist.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::removeCommand() {
    string targetCommand = getTargetCommand();
    Data* searchCommand = new Data(targetCommand, "");

    if (this->mCommandList.duplicateExists(searchCommand)) {
        bool success = this->mCommandList.removeNode(searchCommand);
        if (success) {
            displayCommandRemoved();
        }
    }
    else {
        displayCommandDoesNotExist();
    }

    delete searchCommand;
}

/********************************************************************************************************
* Function: getTargetCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Gets an input string from the user and returns that string.
* Input parameters: none
* Returns: void
* Preconditions: string userInput, a user input representing a Linux shell command to be searched for.
* Postconditions: none
********************************************************************************************************/
string Game::getTargetCommand() {
    string userInput = "";
    cout << "Please enter a command to be removed from the list.\n";
    cin >> userInput;
    return(userInput);
}

/********************************************************************************************************
* Function: displayAllCommands()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Displays all Linux shell commands currently in memory and their associated descriptions.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::displayAllCommands() {
    this->mCommandList.printList();
}

/********************************************************************************************************
* Function: loadPlayerProfiles()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Loads player profiles into memory from PlayerProfile.csv
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::loadPlayerProfiles() {
    ifstream playerProfileFile;
    string nameBuffer = "", scoreBuffer = "";

    if (!playerProfileFile.is_open()) {
        playerProfileFile.open("PlayerProfile.csv", std::ios::in);
    }

    cout << "Loading player profiles..." << endl;
    
    while (playerProfileFile.peek() != ifstream::traits_type::eof() && mPlayerListSize < MAX_SIZE) {
        int score = 0;
        getline(playerProfileFile, nameBuffer, ',');
        getline(playerProfileFile, scoreBuffer);
        score = stoi(scoreBuffer);

        mPlayerList[mPlayerListSize].setPlayerName(nameBuffer);
        mPlayerList[mPlayerListSize].setPlayerScore(score);
        ++mPlayerListSize;
    }

    playerProfileFile.close();

    cout << "Player profiles loaded successfully." << endl;
}

/********************************************************************************************************
* Function: loadCommands()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Loads Linux shell commands into memory from commands.csv
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::loadCommands() {
    ifstream commandDataFile;
    string commandBuffer = "", descriptionBuffer = "";

    if (!commandDataFile.is_open()) {
        commandDataFile.open("commands.csv", std::ios::in);
    }

    cout << "Loading command data..." << endl;
    while (commandDataFile.peek() != ifstream::traits_type::eof()) {
        getline(commandDataFile, commandBuffer, ',');
        getline(commandDataFile, descriptionBuffer);
        Data* newData = new Data(commandBuffer, descriptionBuffer);
        mCommandList.insertAtFront(newData);
        ++mCommandListSize;
    }

    commandDataFile.close();

    cout << "Command data loaded successfully." << endl;
}

/********************************************************************************************************
* Function: loadPreviousGame()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Sets a pre-existing player profile to the active profile and calls playGame(). If the
* player profile entered by the player does not exist, displays an error message indicating such and returns.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::loadPreviousGame() {
    string playerName = getPlayerName();
    bool found = false;
    
    for (int i = 0; i < MAX_SIZE && !found; ++i) {
        if (mPlayerList[i].getPlayerName() == playerName) {
            mActivePlayer = i;
            found = true;
        }
    }

    if (found) {
        playGame();
    }
    else {
        displayPlayerProfileNotFound();
    }
}

/********************************************************************************************************
* Function: getPlayerName()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Gets a string representing the name of a player profile from the player, then returns it.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
string Game::getPlayerName() {
    string playerName = "";
    cout << "Please enter your profile name." << endl;
    cin >> playerName;
    return(playerName);
}

/********************************************************************************************************
* Function: saveAndQuit()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Writes the current command list and player array to .csv files and returns.
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::saveAndQuit() {
    saveCommandList();
    savePlayerList();
    // deallocation of linked list memory will occur in destructors when main() returns
    // see List<T> destructor
}

/********************************************************************************************************
* Function: saveCommandList()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Writes the current command list to commands.csv
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::saveCommandList() {
    ofstream outputCommands;
    outputCommands.open("commands.csv", std::ios::out);
    mCommandList.printListToFile(outputCommands);
    outputCommands.close();
}

/********************************************************************************************************
* Function: savePlayerList()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Writes the current player list to PlayerProfile.csv
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::savePlayerList() {
    ofstream outputPlayers;
    outputPlayers.open("PlayerProfile.csv", std::ios::out);
    outputPlayerProfiles(outputPlayers);
    outputPlayers.close();
}

/********************************************************************************************************
* Function: playNewGame()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Calls addNewPlayerToList() and, if that function returns success, calls playGame().
* Input parameters: none
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::playNewGame() {
    bool playerAdded = addNewPlayerToList();
    if (playerAdded) {
        playGame();
    }
}

/********************************************************************************************************
* Function: addNewPlayerToList()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: If the player list is not full (array), gets a name for a player profile from the user. If
* that name does not exist in the list, inserts the name and sets the player score to 0.
* Input parameters: none
* Returns: bool inserted, a boolean indicating whether a new player profile was successfully created and inserted.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
bool Game::addNewPlayerToList() {
    bool inserted = false, duplicate = false;
    if (mPlayerListSize == MAX_SIZE) {
        cout << "The player profile list is full." << endl;
        inserted = true;
    }
    while (!inserted) {
        string name = this->getPlayerName();
        for (int i = 0; i < MAX_SIZE && !duplicate && !inserted; ++i) {
            if (name == mPlayerList[i].getPlayerName()) {
                duplicate = true;
                cout << "A player profile with that name already exists." << endl;
            }
            else if (mPlayerList[i].getPlayerName() == "" && mPlayerList[i].getPlayerScore() == 0) {
                mPlayerList[i].setPlayerName(name);
                mPlayerList[i].setPlayerScore(0);
                mActivePlayer = i;
                ++mPlayerListSize;
                inserted = true;
            }
        }
        duplicate = false;
    }
    return(inserted);
}

/********************************************************************************************************
* Function: outputPlayerProfiles()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: For every player profile in the list of player profiles that is not empty, outputs the
* player profile to PlayerProfile.csv, passed in as ofstream& outputFile.
* Input parameters: ofstream& outputFile, a stream to PlayerProfile.csv
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Game::outputPlayerProfiles(ofstream& outputFile) {
    for (int i = 0; i < MAX_SIZE && mPlayerList[i].getPlayerName() != ""; ++i) {
        mPlayerList[i].printDataToFile(outputFile);
    }
}