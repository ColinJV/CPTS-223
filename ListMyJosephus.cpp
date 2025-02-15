#include "ListMyJosephus.h"

// Constructor
ListMyJosephus::ListMyJosephus(const int& M, const int& N) {
	mM = M;
	mN = N;
}

// Destructor
ListMyJosephus::~ListMyJosephus()
{
	// nothing to see here
	// our list doesn't store pointers to heap memory so std::list's destructor does all the work
}

// Returns the value of the mM member of a ListMyJosephus object, the number of traversals to
// be conducted before deleting an item
int ListMyJosephus::getEliminationInterval()
{
	return mM;
}

// Returns the value of the mN member of a ListMyJosephus object, the original size of the list
int ListMyJosephus::getTotalDestinations()
{
	return mN;
}

// Adds a Destination to end of the mList member by calling std::list.push_back()
void ListMyJosephus::addDestinationToList(const Destination& newDestination)
{
	mList.push_back(newDestination);
}

// Adds N Destinations read from a file, destinations.csv, to a ListMyJosephus object's mList
// member. Randomly selects the line to be read from.
void ListMyJosephus::populateListOfNDestinations()
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

// Deletes all entries in the list
void ListMyJosephus::clear()
{
	mList.clear();
}

// Returns an int (implicitly cast from a size_t) indicating the size of the list.
int ListMyJosephus::currentSize()
{
	return mList.size();
}

// Returns a bool indicating whether the list is empty.
bool ListMyJosephus::isEmpty()
{
	return mList.empty();
}

// Starting at the beginning of the list, iterates through the list M times
// looping as necessary, deleting the Mth item. Repeats until N-1 entries have
// been deleted.
void ListMyJosephus::eliminateDestinations(ofstream& logFile)
{
	if (!mList.empty()) {
		auto it = mList.begin();
		for (int i = 1; i < mN; ++i) {
			for (int j = 0; j < mM; ++j) {
				++it;
				if (it == mList.end()) it = mList.begin();
			}
			logFile << "Eliminating: ";
			it->printDestinationToLog(logFile);
			it = mList.erase(it);
			if (it == mList.end()) it = mList.begin();
		}
	}
}

// Uses a range based for loop to print all destinations in the list
// This is never called but was required.
void ListMyJosephus::printAllDestinations()
{
	for (Destination d : mList) {
		d.printDestinationName();
	}
}

// Prints the destination at the beginning of the list to an output file.
// Meant to be called when only one more Destination exists in the list.
void ListMyJosephus::printFinalDestination(ofstream& logFile) {
	logFile << "Destination: ";
	auto it = mList.begin();
	it->printDestinationToLog(logFile);
}
