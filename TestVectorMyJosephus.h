#ifndef TESTVECTORMYJOSEPHUS_H
#define TESTVECTORMYJOSEPHUS_H

#include "VectorMyJosephus.h"

void testVectorMyJosephus(ofstream& logFile);
int generateRandomM(int n);
void runJosephusSimulation(VectorMyJosephus& testList, ofstream& logFile, int simulationNumber);
void computeTimeTaken(double* listTime, int n, clock_t start, clock_t end);
void outputTimeData(double* listTime, ofstream& logFile);

#endif