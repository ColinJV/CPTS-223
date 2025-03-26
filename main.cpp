// Programmer:  Colin Van Dyke
// Assignment: PA4
// Class: CPTS223 Spring 2025
// Instructor: Subu Kandaswamy
// Functionality: Reads an Amazon inventory list from a .csv file and populates two hash tables.
//		One hash table contains these products hashed by their unique ID. The other hash table
//		contains these products hashed by their categories. One product can have multiple categories,
//		and thus can be at multiple indexes in this second hash table. Prompts the user for inventory
//		query matching an expected format and returns all products that match that query.

#include "ProductInventoryQuery.h"

int main(void) {
	ProductInventoryQuery primary;
	primary.runProgram();
	return(0);
}