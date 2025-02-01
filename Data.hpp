#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ostream;
using std::endl;
using std::cout;
using std::cin;
using std::ofstream;

class Data {
public:

	// Constructor
	Data();
	Data(string command, string description);

	// Copy
	Data(Data& copy);

	// Destructor
	~Data();

	// Accessors
	string getCommand(void) const;
	string getDescription(void) const;

	// Mutators
	void setCommand(string& newCommand);
	void setDescription(string& newDescription);

	// Others
	Data& operator=(const Data& rhs);
	bool checkForDuplicates(Data* targetData);
	friend ostream& operator<<(ostream& lhs, const Data& rhs);
	void printData();
	void printDataToFile(ofstream& outputFile);

private:
	string mCommand;
	string mDescription;
};

#endif