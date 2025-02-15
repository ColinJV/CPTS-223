#ifndef TESTLISTMYJOSEPHUS_H
#define TESTLISTMYJOSEPHUS_H

#include "ListMyJosephus.h"

void testListMyJosephus(ofstream& logFile);
int generateRandomM(int n);
void runJosephusSimulation(ListMyJosephus& testList, ofstream& logFile, int simulationNumber);
void computeTimeTaken(double* listTime, int n, clock_t start, clock_t end);
void outputTimeData(double* listTime, ofstream& logFile);

#endif