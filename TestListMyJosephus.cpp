#include "TestListMyJosephus.h"

// Tests the ListMyJosephus object by running a simulation and printing the output.
// Uses a for loop to iterate N from 1 to 1025. For each iteration, takes the start and end times.
// Generates a random number M, populates a ListMyJosephus object with N Destinations, and then
// eliminates them until only one remains.
void testListMyJosephus(ofstream& logFile) {
	double listTime[1025] = { 0 };
	for (int n = 1; n <= 1025; ++n) {
		clock_t k = clock();
		clock_t start;
		do start = clock();
		while (start == k);

		int m = generateRandomM(n);
		ListMyJosephus newList(m, n);
		newList.populateListOfNDestinations();
		runJosephusSimulation(newList, logFile, n);

		clock_t end = clock();
		computeTimeTaken(listTime, n, start, end);
	}
	outputTimeData(listTime, logFile);
}

// Returns a random number between 0 and N
int generateRandomM(int n) {
	return rand() % n;
}

// Runs one round of the Josephus simulation. Calls eliminateDestinations() which repeats until
// only one destination remains. Then prints the remaining Destination to the output file.
void runJosephusSimulation(ListMyJosephus& testList, ofstream& logFile, int simulationNumber) {
	logFile << "Beginning List Simulation #" << simulationNumber << ":" << '\n';
	testList.eliminateDestinations(logFile);
	testList.printFinalDestination(logFile);
}

// Computes the time taken for a single round of simulation by subtracting the start time from the
// end time and dividing by CLOCKS_PER_SEC. Stores the result in an array as an output parameter.
void computeTimeTaken(double* listTime, int n, clock_t start, clock_t end) {
	listTime[n - 1] = ((double)end - (double)start) / CLOCKS_PER_SEC;
}

// Outputs the computed time for every round of simulation to a logfile. Then computes the average time
// and outputs it.
void outputTimeData(double* listTime, ofstream& logFile) {
	double sum = 0;
	for (int i = 0; i < 1025; ++i) {
		logFile << "CPU Time for Simulation " << (i + 1) << " in seconds: ";
		logFile << listTime[i] << '\n';
		sum += listTime[i];
	}
	logFile << "Average CPU Time in seconds: " << sum / 1025 << '\n';
}