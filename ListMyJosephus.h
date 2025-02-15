#ifndef LISTMYJOSEPHUS_H
#define LISTMYJOSEPHUS_H

#include "Destination.h"
#include <list>

class ListMyJosephus
{
public:
	// Constructor
	ListMyJosephus(const int& M = 0, const int& N = 0);

	// Destructor
	~ListMyJosephus();

	// Accessors
	int getEliminationInterval();
	int getTotalDestinations();

	// Mutator
	void addDestinationToList(const Destination& newDestination);
	void populateListOfNDestinations();

	// Other
	void clear();
	int currentSize();
	bool isEmpty();
	void eliminateDestinations(ofstream& logFile);
	void printAllDestinations();
	void printFinalDestination(ofstream& logFile);

private:
	int mM;
	int mN;
	list<Destination> mList;
};

#endif