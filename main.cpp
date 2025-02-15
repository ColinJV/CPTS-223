/********************************************************************************************************
* Program: CPTS 223 PA2 Josephus Problem
* Programmer: Colin Van Dyke
* Instructor: Subu Kandaswamy
* Date Created: 02/07/2025
* Date Last Modified: 02/13/2025
* Description: This program implements two data structures, ListMyJosephus and VectorMyJosephus, which
* are classes using a std::list and a std::vector respectively, to solve a challenge using a variant of
* the Josephus problem. The functions testListMyJosephus() and testVectorMyJosephus() will conduct the
* following actions: use a for loop to iterate from N=1 to N=1025. For each iteration, populate the correct
* Josephus container with N destinations from a random row of an input file, destinations.csv; randomly
* generate an integer M such that 1 <= M <= N; starting at the beginning of the list, finds the Mth element;
* deletes that element; makes M traversals to delete the next element, looping around as necessary; continues
* until only one destination remains. Writes each eliminated destination and the final destination to an
* output file results.log. Also calculates the time for each simulation, and after all simulations computes
* the average time per simulation, outputting both the per simulation and average time to results.log
********************************************************************************************************/

#include "TestListMyJosephus.h"
#include "TestVectorMyJosephus.h"

int main(void) {
	srand((unsigned int)time(NULL));
	ofstream logFile;
	logFile.open("results.log", std::ios::out);

	testListMyJosephus(logFile);
	testVectorMyJosephus(logFile);

	logFile.close();
	return 0;
}