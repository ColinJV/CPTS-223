#include "testAVLMap.h"

// Empty constructor, wrapper object has no data members
testAVLMap::testAVLMap() {

}

// Empty destructor, wrapper object has no data members
testAVLMap::~testAVLMap() {

}

// Compares the performance of my custom AVL_Map class with std::map by conducting the following steps
// Creates an AVL_Map object and a std::map with pair<int, USCity>
// Creates a std::list<int> for storing zip codes
// Calls populateMaps() which populates both the AVL_Map and std::map with data from uszips.csv
// Calls populateLookups() which populates an array of size LOOKUP_SIZE with randomly selected zip codes from the std::list
// Calls lookupAVLMap() which looks up every zip code from the integer array in the AVL_Map and returns how much time it took to complete the task.
// Calls lookupStdMap() which looks up every zip code from the integer array in the std::map and returns how much time it took to complete the task.
// Calls displayLookupTimes() which displays visually a time comparison of the elapsed time for lookupAVLMap() and lookupStdMap()
void testAVLMap::comparePerformance(void) {
	AVL_Map<int, USCity> zipAVLMap;
	std::map<int, USCity> zipStdMap;
	list<int> zipCodeList;
	populateMaps(&zipAVLMap, &zipStdMap, &zipCodeList);

	int lookupZips[LOOKUP_SIZE] = { 0 };
	populateLookups(lookupZips, &zipCodeList);
	double avlTime = lookupAVLMap(&zipAVLMap, lookupZips);
	double mapTime = lookupStdMap(&zipStdMap, lookupZips);
	displayLookupTimes(avlTime, mapTime);
}


// Populates a custom AVL_Map, a std::map, and a std::list with US City data from uszips.csv
// Both AVL_Map and std::map are given an integer zip code as a key and a USCity object as a value.
// The std::list is given only integer zip codes for use in generating a random list of zip codes later.
// Opens uszips.csv for reading, and while it has not reached the end of the file and the input stream is good,
//		parses lines based on the expected format of each line. Once a line has been parsed into individual strings,
//		creates a USCity object on the heap and adds it and its associated zip code as a key to the AVL_Map and the std::map.
//		Adds the zip code to the std::list. Reiterates through the .csv until it reaches the end.
void testAVLMap::populateMaps(AVL_Map<int, USCity>* zipAVLMap, map<int, USCity>* zipStdMap, list<int>* zipCodeList)
{
	cout << "Populating AVL Map, std::map, and list of all zip codes..." << endl;
	ifstream zipcodes;
	zipcodes.open("uszips.csv", std::ios::in);
	string buffer;
	getline(zipcodes, buffer);

	while (zipcodes.peek() != ifstream::traits_type::eof() && zipcodes.good()) {
		string latitude, longitude, cityName, stateID, stateName, ZCTA, parentZCTA,
			population, popDensity, countyFIPS, countyName, countyWeights, countyNamesAll,
			countyFIPSAll, imprecise, military, timezone;
		int newZipKey = 0;

		getline(zipcodes, buffer, '"');
		getline(zipcodes, buffer, '"');
		newZipKey = stoi(buffer);

		getline(zipcodes, buffer, '"');
		getline(zipcodes, latitude, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, longitude, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, cityName, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, stateID, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, stateName, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, parentZCTA, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, population, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, popDensity, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, countyFIPS, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, countyName, '"');

		getline(zipcodes, buffer, '{');
		getline(zipcodes, countyWeights, '}');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, buffer, '"');
		getline(zipcodes, countyNamesAll, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, countyFIPSAll, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, imprecise, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, military, '"');

		getline(zipcodes, buffer, '"');
		getline(zipcodes, timezone, '"');
		getline(zipcodes, buffer, '\n');

		USCity *newCity = new USCity(latitude, longitude, cityName, stateID, stateName, ZCTA, parentZCTA,
			population, popDensity, countyFIPS, countyName, countyWeights, countyNamesAll, countyFIPSAll,
			imprecise, military, timezone);

		zipAVLMap->insert(newZipKey, *newCity);
		zipStdMap->insert({ newZipKey, *newCity });
		zipCodeList->push_front(newZipKey);
	}

	cout << "Maps populated." << endl;
	cout << "std::map size: " << zipStdMap->size() << endl;
	cout << "AVL_Map size: " << zipAVLMap->size() << endl;
	zipcodes.close();
}


// Populates an integer array of size LOOKUP_SIZE with zip codes from the std::list of zip codes.
// Randomly selects which zip code to add next by calling rand() and modding by 400 and iterating
//		through the list 
void testAVLMap::populateLookups(int* lookupZips, list<int>* zipCodeList) {
	cout << "Populating list of random zip codes to look up..." << endl;
	auto it = zipCodeList->begin();
	for (int i = 0; i < LOOKUP_SIZE; ++i) {
		int randomNum = rand() % 400;
		for (int j = 0; j < randomNum; j++) {
			it++;
			if (it == zipCodeList->end()) {
				it = zipCodeList->begin();
			}
		}
		lookupZips[i] = *it;
	}
	cout << "List populated." << endl;
}


// Looks up every zip code from an integer array of zip codes in an AVL_Map. Returns the
//		elapsed time for the number of lookups.
double testAVLMap::lookupAVLMap(AVL_Map<int, USCity>* zipAVLMap, int* lookupZips) {
	clock_t k = clock();
	clock_t start;
	do start = clock();
	while (start == k);

	for (int i = 0; i < LOOKUP_SIZE; i++) {
		auto it = zipAVLMap->find(lookupZips[i]);
	}

	clock_t end = clock();
	double time = ((double)end - (double)start) / CLOCKS_PER_SEC;
	return(time);
}


// Looks up every zip code from an integer array of zip codes in a std::map. Returns
//		the elapsed time for the number of lookups.
double testAVLMap::lookupStdMap(map<int, USCity>* zipStdMap, int* lookupZips) {
	clock_t k = clock();
	clock_t start;
	do start = clock();
	while (start == k);

	for (int i = 0; i < LOOKUP_SIZE; i++) {
		auto it = zipStdMap->find(lookupZips[i]);
	}

	clock_t end = clock();
	double time = ((double)end - (double)start) / CLOCKS_PER_SEC;
	return(time);
}


// Displays the elapsed time for LOOKUP_SIZE lookups in an AVL_Map and a std::map.
void testAVLMap::displayLookupTimes(double avlLookup, double stdMapLookup) {
	cout << "Performed " << LOOKUP_SIZE << " lookups in custom implementation of an AVL Map in " << avlLookup << " seconds." << endl;
	cout << "Performed " << LOOKUP_SIZE << " lookups in std::map in " << stdMapLookup << " seconds." << endl;
}