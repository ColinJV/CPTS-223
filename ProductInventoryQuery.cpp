#include "ProductInventoryQuery.h"

ProductInventoryQuery::ProductInventoryQuery()
{
	// creates two empty hash tables
}

ProductInventoryQuery::~ProductInventoryQuery()
{
	// calls HashTable destructors
}

void ProductInventoryQuery::runProgram() {
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
}

void ProductInventoryQuery::bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";

	ifstream inputStream;
	inputStream.open("marketing_sample_data.csv", ios::in);
	this->readInventoryFile(inputStream);
	inputStream.close();
}

void ProductInventoryQuery::printHelp()
{
	cout << "Supported list of commands: " << endl;
	cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
	cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
		<< endl;
}

bool ProductInventoryQuery::validCommand(string line)
{
	return (line == ":help") ||
		(line.rfind("find", 0) == 0) ||
		(line.rfind("listInventory") == 0);
}

void ProductInventoryQuery::evalCommand(string line)
{
	if (line == ":help")
	{
		printHelp();
	}
	// if line starts with find
	else if (line.rfind("find", 0) == 0)
	{
		// Look up the appropriate datastructure to find if the inventory exist
		// cout << "YET TO IMPLEMENT!" << endl;
		istringstream iss(line);
		string command, productID;
		if (iss >> command >> productID) {
			if (command == "find") {
				this->find(productID);
			}
		}
		else {
			cout << "Invalid input. Format: find <productID>\n";
		}
	}
	// if line starts with listInventory
	else if (line.rfind("listInventory") == 0)
	{
		// Look up the appropriate datastructure to find all inventory belonging to a specific category
		// cout << "YET TO IMPLEMENT!" << endl;

		string category = getCategory(line);
		if (category != "") {
			this->listInventory(category);
		}
		else {
			cout << "Invalid input. Format: listInventory <category_string>\n";
		}
	}
}

string ProductInventoryQuery::getCategory(const string& line) {
	string category;
	bool stop = false;
	for (int i = 0; i < line.length(); ++i) {
		while (i < line.length() && !stop) {
			++i;
			if (line[i] == ' ') {
				++i;
				stop = true;
			}
		}
		
		char currentChar = line[i];
		category += currentChar;
	}
	return(category);
}

void ProductInventoryQuery::readInventoryFile(ifstream& inputFile)
{
	cout << "Populating Inventory..." << endl;
	string buffer;
	getline(inputFile, buffer); // eats the format specifier line

	while (inputFile.peek() != ifstream::traits_type::eof() && inputFile.good()) {
		vector<string> parsedTokens;
		getline(inputFile, buffer);
		this->parseLine(buffer, parsedTokens);
		
		//cout << "Parsed line." << endl;

		// Create a new Product on the heap using data from the parsed line
		Product* newProduct = new Product(parsedTokens.at(0), parsedTokens.at(1), parsedTokens.at(2),
			parsedTokens.at(3), parsedTokens.at(4), parsedTokens.at(5), parsedTokens.at(6),
			parsedTokens.at(7), parsedTokens.at(8), parsedTokens.at(9), parsedTokens.at(10),
			parsedTokens.at(11), parsedTokens.at(12), parsedTokens.at(13), parsedTokens.at(14),
			parsedTokens.at(15), parsedTokens.at(16), parsedTokens.at(17), parsedTokens.at(18),
			parsedTokens.at(19), parsedTokens.at(20), parsedTokens.at(21), parsedTokens.at(22),
			parsedTokens.at(23), parsedTokens.at(24), parsedTokens.at(25), parsedTokens.at(26),
			parsedTokens.at(27));

		//cout << "Created product." << endl;

		// Inserts new Product to the InventoryByID HashTable with its Unique ID as the key
		this->mInventoryByID.insert(newProduct->getUniqueID(), newProduct);

		//cout << "Inserted Product by ID." << endl;

		// Create a vector of strings containing every category of the current product
		vector<string> categories;
		this->parseCategories(parsedTokens.at(4), categories);

		//cout << "Parsed categories." << endl;

		// Inserts new Product to the InventoryByCategory HashTable with its Category as the key
		while (!categories.empty()) {
			this->mInventoryByCategory.insert(categories.back(), newProduct);
			categories.pop_back();
		}

		//cout << "Inserted Product by Category." << endl;
	}

	cout << "> Inventory populated!" << endl;
}

void ProductInventoryQuery::parseCategories(const string& categoryLine, vector<string>& categories) {
	string currentField = "";

	for (int i = 0; i < categoryLine.length(); ++i) {
		char currentChar = categoryLine[i];

		// Handle category separations
		if (currentChar == ' ' && (categoryLine.length() > (i + 2)) &&
			categoryLine[i + 1] == '|' && categoryLine[i + 2] == ' ') {
			categories.push_back(currentField);
			currentField = "";
			// skip next two characters
			i += 2;
		}
		else {
			currentField += currentChar;
		}
	}
	// Add the final entry
	categories.push_back(currentField);
}

void ProductInventoryQuery::parseLine(const string& line, vector<string>& parsedTokens)
{
	string currentField = "";
	bool inQuotes = false;

	for (int i = 0; i < line.length(); ++i)
	{
		char currentChar = line[i];
		// Handle weird double quotes followed by comma
		if (currentChar == '"' && (line.length() > (i + 2) && line[i + 1] == '"' && line[i + 2] == ',')) {
			// Skip quotes
			i++;
		}
		// Handle escaped quotes
		else if (currentChar == '"' && (line.length() > (i + 1)) && line[i + 1] == '"') {
			currentField += '"'; // Add quote to currentField
			i++; // Skip the next quote
		}
		// If single quotes, toggle inQuotes
		else if (currentChar == '"') {
			inQuotes = !inQuotes;
		}
		// If comma encountered and not in quotes
		else if (currentChar == ',' && !inQuotes) {
			parsedTokens.push_back(currentField);
			currentField.clear();
		}
		// Any other character
		else {
			currentField += currentChar;
		}
	}
	// Add the final entry
	parsedTokens.push_back(currentField);
}

pair<bool, HashNode<string, Product*>*> ProductInventoryQuery::findByID(const string& targetID) {
	pair<bool, HashNode<string, Product*>*> result = { false, nullptr };
	result.second = mInventoryByID.findByUniqueID(targetID);
	if (result.second != nullptr) {
		result.first = true;
	}
	return(result);
}

void ProductInventoryQuery::find(const string& targetID) {
	pair<bool, HashNode<string, Product*>*> result = this->findByID(targetID);
	if (result.first == false) {
		cout << "Inventory not found." << endl;
	}
	else {
		result.second->display(cout);
	}
}

void ProductInventoryQuery::listInventory(const string& targetID) {
	mInventoryByCategory.listMatchingTargets(cout, targetID);
}