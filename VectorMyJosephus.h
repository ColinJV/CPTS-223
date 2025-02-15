#ifndef VECTORMYJOSEPHUS_H
#define VECTORMYJOSEPHUS_H

#include "Destination.h"
#include <vector>

class VectorMyJosephus
{
public:
	// Constructor
	VectorMyJosephus(const int& M = 0, const int& N = 0);

	// Destructor
	~VectorMyJosephus();
	
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
	vector<Destination> mVector;
};

#endif