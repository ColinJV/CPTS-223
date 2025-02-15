#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Destination
{
public:
	// Constructor
	Destination(const int& position = 0, const string& name = "");

	// Destructor
	~Destination();

	// Accessors
	void printPosition();
	void printDestinationName();
	void printDestinationToLog(ofstream& logFile);

private:
	int mPosition;
	string mName;
};

#endif