#include "Data.hpp"

/********************************************************************************************************
* Function: Data constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Data object with default values
* Input parameters: none
* Returns: Data object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data::Data() {
	mCommand = "";
	mDescription = "";
}

/********************************************************************************************************
* Function: Data constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Data object with the string input parameters assigned to the member data.
* Input parameters: string command, string description, string data corresponding to the command and
* description of a Linux shell command.
* Returns: Data object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data::Data(string command, string description) {
	mCommand = command;
	mDescription = description;
}

/********************************************************************************************************
* Function: Data copy constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Data object using data values from another Data object
* Input parameters: none
* Returns: Data object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data::Data(Data& copy) {
	mCommand = copy.getCommand();
	mDescription = copy.getDescription();
}

/********************************************************************************************************
* Function: Data destructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Destroys a Data object
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data::~Data() {
	// ok people move along nothing to see here
}

/********************************************************************************************************
* Function: getCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns the mCommand data member of a Data object
* Input parameters: none
* Returns: string mCommand, the string corresponding to a Linux shell command
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
string Data::getCommand() const {
	return(mCommand);
}

/********************************************************************************************************
* Function: getDescription()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns the mDescription data member of a Data object
* Input parameters: none
* Returns: string mDescription, the string corresponding to a description of a Linux shell command.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
string Data::getDescription() const {
	return(mDescription);
}

/********************************************************************************************************
* Function: setCommand()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mCommand data member of a Data object, setting it to the input string.
* Input parameters: string& newCommand, a reference to a string
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Data::setCommand(string& newCommand) {
	mCommand = newCommand;
}

/********************************************************************************************************
* Function: setDescription()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mDescription data member of a Data object, setting it to the input string.
* Input parameters: string& newDescription, a reference to a string
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Data::setDescription(string& newDescription) {
	mDescription = newDescription;
}

/********************************************************************************************************
* Function: operator=()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Overloads the assignment operator for use with Data objects
* Input parameters: const Data& rhs, a Data object being copied
* Returns: Data object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
Data& Data::operator=(const Data& rhs) {
	if (this != &rhs) {
		mCommand = rhs.getCommand();
		mDescription = rhs.getDescription();
	}
	return(*this);
}


/********************************************************************************************************
* Function: checkForDuplicates()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns a boolean, true if this Data's mCommand member is equivalent to another Data object's
* mCommand member, false otherwise.
* Input parameters: Data* targetData, a pointer to a Data object whose members are being compared.
* Returns: bool duplicate, true if duplicate data is found, false otherwise.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
// Before I did this I tried to just overload operator==() but it wouldn't work, don't know why
bool Data::checkForDuplicates(Data* targetData) {
	bool duplicate = this->getCommand() == targetData->getCommand();
	return(duplicate);
}

/********************************************************************************************************
* Function: operator<<()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Overloaded stream insertion operator for use with Data objects.
* Input parameters: ostream& lhs, a reference to an output stream. Data& rhs, a reference to a Data object
* being output to the ostream.
* Returns: ostream& lhs, a reference to the input parameter output stream.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
ostream& operator<<(ostream& lhs, Data& rhs) {
	lhs << rhs.getCommand() << endl;
	lhs << rhs.getDescription() << endl;
	return(lhs);
}

/********************************************************************************************************
* Function: printData()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Outputs the string members of a Data object to std::cout.
* Input parameters: void
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Data::printData() {
	cout << this->getCommand() << ": " << this->getDescription() << endl;
}

/********************************************************************************************************
* Function: printDataToFile()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mCommand data member of a Data object, setting it to the input string.
* Input parameters: string& newCommand, a reference to a string
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
void Data::printDataToFile(ofstream& outputFile) {
	outputFile << this->getCommand() << ',' << this->getDescription() << endl;
}