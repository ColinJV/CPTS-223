// Programmer:  Colin Van Dyke
// Assignment: PA5
// Class: CPTS223 Spring 2025
// Instructor: Subu Kandaswamy
// Functionality: Reads an Amazon inventory list from a .csv file and populates two hash tables.
//		One hash table contains these products hashed by their unique ID. The other hash table
//		contains these products hashed by their categories. One product can have multiple categories,
//		and thus can be at multiple indexes in this second hash table. Prompts the user for inventory
//		query matching an expected format and returns all products that match that query.
// PA5 Changes: Modified printHelp() function to include instructions on how to specify sort method and order.
//				String parameter to listInventory() made non-const to enable cleaning sort and order specifiers
//				from the category string. Added function cleanCategoryString() which removes these specifiers.
//				listInventory() now calls one of two functions depending on whether merge or insertion sort are
//				specified, with a Boolean parameter that determines sort order. New function mergeSortAndListMatchingTargets()
//				merge sorts the values at a given hash corresponding to a category string based on the value of the sellingPrice
//				member, then displays the sorted list. New function insertionSortAndListMatchingTargets() insertion sorts
//				the values at a given hash corresponding to a category string based on the value of the sellingPrice member,
//				then displays the sorted list. Both sortAndList functions have various helper functions. New function buildVector() builds
//				a std::vector that contains each entry in a separately chained list in the category based hash table, this function
//				helps merge sort and insertion sort algorithms. Added double member variable to Product to aid in accurate comparisons,
//				as using strings to compare price would result in nonsensical orders based on the first numeral encountered. Added
//				function parseSellingPrice() to get a valid double selling price from the string grabbed from the data file. Added
//				debug prints to displayIDandName() which outputs the price of a Product as both a string and double to aid in verification
//				of proper sorting.

#include "ProductInventoryQuery.h"

int main(void) {
	ProductInventoryQuery primary;
	primary.runProgram();
	return(0);
}