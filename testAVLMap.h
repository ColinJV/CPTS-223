#ifndef TESTAVLMAP_H
#define TESTAVLMAP_H

#include "avl_map.h"
#include "USCity.h"
#include <map>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#define LOOKUP_SIZE 2000

class testAVLMap {
public:
	// Constructor
	testAVLMap();

	// Destructor
	~testAVLMap();

	// Test Procedure Methods
	void comparePerformance(void);
	void populateMaps(AVL_Map<int, USCity>* zipAVLMap, map<int, USCity>* zipStdMap, list<int>* zipCodeList);
	void populateLookups(int* lookupZips, list<int>* zipCodeList);
	double lookupAVLMap(AVL_Map<int, USCity>* zipAVLMap, int* lookupZips);
	double lookupStdMap(map<int, USCity>* zipStdMap, int* lookupZips);
	void displayLookupTimes(double avlLookup, double stdMapLookup);
};

#endif
