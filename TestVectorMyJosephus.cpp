#include "TestVectorMyJosephus.h"

// Tests the VectorMyJosephus object by running a simulation and printing the output.
// Uses a for loop to iterate N from 1 to 1025. For each iteration, takes the start and end times.
// Generates a random number M, populates a ListMyJosephus object with N Destinations, and then
// eliminates them until only one remains.
void testVectorMyJosephus(ofstream& logFile) {
	double listTime[1025] = { 0 };
	for (int n = 1; n <= 1025; ++n) {
		clock_t k = clock();
		clock_t start;
		do start = clock();
		while (start == k);

		int m = generateRandomM(n);
		VectorMyJosephus newList(m, n);
		newList.populateListOfNDestinations();
		runJosephusSimulation(newList, logFile, n);

		clock_t end = clock();
		computeTimeTaken(listTime, n, start, end);
	}
	outputTimeData(listTime, logFile);
}

// Runs one round of the Josephus simulation. Calls eliminateDestinations() which repeats until
// only one destination remains. Then prints the remaining Destination to the output file.
void runJosephusSimulation(VectorMyJosephus& testList, ofstream& logFile, int simulationNumber) {
	logFile << "Beginning Vector Simulation #" << simulationNumber << ":" << endl;
	testList.eliminateDestinations(logFile);
	testList.printFinalDestination(logFile);
}