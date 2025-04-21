#ifndef PRODUCTINVENTORYQUERY_H
#define PRODUCTINVENTORYQUERY_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "Product.h"

class ProductInventoryQuery
{
public:
	ProductInventoryQuery();
	~ProductInventoryQuery();

	// Main execution
	void runProgram();

private:
	HashTable<string, Product*>* mInventoryByID;
	HashTable<string, Product*>* mInventoryByCategory;

	// Private main execution
	void bootStrap();
	void printHelp();
	bool validCommand(string line);
	void evalCommand(string line);
	void readInventoryFile(ifstream& inputFile);
	void parseLine(const string& line, vector<string>& parsedTokens);
	void parseCategories(const string& categoryLine, vector<string>& categories);
	string getCategory(const string& line);
	void cleanCategoryString(string& category);

	// Find
	void find(const string& targetID);
	pair<bool, HashNode<string, Product*>*> findByID(const string& targetID);

	// Find In Category
	void listInventory(string& targetID);
};


#endif