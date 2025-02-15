#include "Destination.h"

// Constructor
Destination::Destination(const int& position, const string& name)
{
	mPosition = position;
	mName = name;
}

// Destructor
Destination::~Destination()
{
	// nothing to see here
}

// Outputs a Destination's mPosition member to cout
void Destination::printPosition()
{
	cout << mPosition << endl;
}

// Outputs a Destination's mName member to cout
void Destination::printDestinationName()
{
	cout << mName << endl;
}

// Outputs a Destination's mName member to an output file
void Destination::printDestinationToLog(ofstream& logFile)
{
	logFile << this->mName << '\n';
}