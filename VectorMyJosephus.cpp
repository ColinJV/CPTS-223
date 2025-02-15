#include "VectorMyJosephus.h"

// Constructor
VectorMyJosephus::VectorMyJosephus(const int& M, const int& N)
{
	mM = M;
	mN = N;
}

// Destructor
VectorMyJosephus::~VectorMyJosephus()
{
	// nothing to see here
}

// Deletes all entries in the vector mVector by calling std::vector.clear()
void VectorMyJosephus::clear()
{
	mVector.clear();
}

// Returns an int (implicitly cast from size_t) representing the size of the vector mVector
int VectorMyJosephus::currentSize()
{
	return mVector.size();
}

// Returns a bool indicating whether the vector mVector is empty
bool VectorMyJosephus::isEmpty()
{
	return mVector.empty();
}

// Adds a Destination to the end of the vector mVector by calling std::vector.push_back()
void VectorMyJosephus::addDestinationToList(const Destination& newDestination)
{
	mVector.push_back(newDestination);
}

// Adds N Destinations read from a file, destinations.csv, to a VectorMyJosephus object's 
// mVector member. Randomly selects the line to be read from.
void VectorMyJosephus::populateListOfNDestinations()
{
	int lineNumber = rand() % 25;
	ifstream inputFile;
	string destination = "";

	if (!inputFile.is_open()) {
		inputFile.open("destinations.csv", std::ios::in);
	}

	while (inputFile.peek() != ifstream::traits_type::eof() && lineNumber > 0) {
		getline(inputFile, destination);
		destination.clear();
		--lineNumber;
	}

	int count = 0;
	while (count < mN) {
		getline(inputFile, destination, ';');
		Destination newDestination(count, destination);
		this->addDestinationToList(newDestination);
		++count;
	}

	inputFile.close();
}

// Starting at the beginning of the list, iterates through the list M times
// looping as necessary, deleting the Mth item. Repeats until N-1 entries have
// been deleted.
void VectorMyJosephus::eliminateDestinations(ofstream& logFile)
{
	if (!mVector.empty()) {
		auto it = mVector.begin();
		for (int i = 1; i < mN; ++i) {
			for (int j = 0; j < mM; ++j) {
				++it;
				if (it == mVector.end()) it = mVector.begin();
			}
			logFile << "Eliminating: ";
			it->printDestinationToLog(logFile);
			it = mVector.erase(it);
			if (it == mVector.end()) it = mVector.begin();
		}
	}
}

// Uses a range based for loop to print all Destinations in the vector mVector
void VectorMyJosephus::printAllDestinations()
{
	for (Destination d : mVector) {
		d.printDestinationName();
	}
}

// Prints the destination at the beginning of the vector to an output file.
// Meant to be called when only one more Destination exists in the vector.
void VectorMyJosephus::printFinalDestination(ofstream& logFile) {
	logFile << "Destination: ";
	auto it = mVector.begin();
	it->printDestinationToLog(logFile);
}