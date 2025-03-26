#include "ProductInventoryQuery.h"

// ProductInventoryQuery constructor
ProductInventoryQuery::ProductInventoryQuery()
{
	int initialSize = 19;
	mInventoryByID = new HashTable<string, Product*>(initialSize);
	mInventoryByCategory = new HashTable<string, Product*>(initialSize);
}

// ProductInventoryQuery destructor
// Since HashTables are created on the heap, calls HashTable destructor
ProductInventoryQuery::~ProductInventoryQuery()
{
	delete mInventoryByID;
	delete mInventoryByCategory;
}

// Main program execution. Calls boostrap() to load inventory and display instructions.
// Takes and evaluates user commands. Unmodified from skeleton code main() apart from
//		incorporating this functionality into a class.
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

// Displays program instructions to the user, opens the .csv file, reads the inventory from
//		the file, then closes it. Adapted from skeleton code.
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

// Prints a help message listing valid/supported commands for the user. Adapted from skeleton
//		code.
void ProductInventoryQuery::printHelp()
{
	cout << "Supported list of commands: " << endl;
	cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
	cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
		<< endl;
}

// Returns a bool indicating if a user input command is valid. Adapted from skeleton code.
bool ProductInventoryQuery::validCommand(string line)
{
	return (line == ":help") ||
		(line.rfind("find", 0) == 0) ||
		(line.rfind("listInventory") == 0);
}

// Evaluates a command. Calls printHelp() for ":help". For "find", searches for the Product ID entered by the user
//		by calling find(). For "listInventory", calls listInventory() after parsing the target category from the
//		user inptu by calling getCategory(). Adapted from skeleton code.
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

// Parses a string reference input parameter to retrieve a category. Does this by
//		finding the first whitespace character (expected command format: "listInventory <category>").
//		Once the first whitespace character is encountered, parses the rest of the string into a string
//		meant to hold the search category and returns that string.
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

// Reads the inventory file line by line and populates a data structure according to the following algorithm.
// 1. Reads and discards the first format specifier line.
// 2. Reads a whole line and calls parseLine() to parse the line into a vector of strings called parsedTokens.
// 3. Creates a Product object on the heap using the strings in parsedTokens.
// 4. Adds this product to the HashTable called mInventoryByID, which hashes Products based on their Unique ID.
// 5. Parses the Product's categories (each Product can contain more than one) into a vector of strings called categories.
// 6. While categories is not empty, inserts the Product into the HashTable mInventoryByCategory, which hashes Products based
//		on their category. This can result in many Products being inserted to this HashTable multiple times but results in O(1)
//		find operations searching for an entry based on category name at the expense of space complexity.
// 7. Repeats steps 1 - 6 until the end of the file is reached and the input stream is good.
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
		this->mInventoryByID->insert(newProduct->getUniqueID(), newProduct);

		//cout << "Inserted Product by ID." << endl;

		// Create a vector of strings containing every category of the current product
		vector<string> categories;
		this->parseCategories(parsedTokens.at(4), categories);

		//cout << "Parsed categories." << endl;

		// Inserts new Product to the InventoryByCategory HashTable with its Category as the key
		while (!categories.empty()) {
			this->mInventoryByCategory->insert(categories.back(), newProduct);
			categories.pop_back();
		}

		//cout << "Inserted Product by Category." << endl;
	}

	cout << "> Inventory populated!" << endl;
}

// Parses an input reference to a string into multiple strings, placing them in a reference to a vector of strings called categories.
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

// Parses an input reference to a string into multiple strings, putting each in a reference to a vector of strings called parsedTokens.
// Parses according to the following algorithm.
// 1. Examines the string character by character, adding the characters to a string called currentField.
// 2. If the current character is a quote, the next character is a quote, and the subsequent character is
//		a comma, it skips the quotes. This results in the next iteration of the primary loop seeing the comma.
// 3. If the current character is a quote, the next character is a quote, this is an escaped quote. Adds a quote to the current token.
// 4. If the current character is a quote and the next character is not a quote, toggles a boolean called inQuotes. While inQuotes is
//		true, encountering a comma will not end the token.
// 5. If the current character is a comma and inQuotes is false, pushes the current token onto the back of the vector of strings and empties
//		the currentField string.
// 6. If the current character is any other character, adds the character to currentField.
// 7. Repeats until the end of the input string, at which point it pushes currentField to the vector of strings a final time.
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

// Finds an entry in the HashTable mInventoryByID by searching for a unique ID. Returns a std::pair<bool, HashNode*>.
// If the entry exists, the bool is true and the HashNode* is to the node where the Product with that Unique ID exists.
// If the entry does not exist, the bool is false and the HashNode* is the nullptr.
pair<bool, HashNode<string, Product*>*> ProductInventoryQuery::findByID(const string& targetID) {
	pair<bool, HashNode<string, Product*>*> result = { false, nullptr };
	result.second = mInventoryByID->findByUniqueID(targetID);
	if (result.second != nullptr) {
		result.first = true;
	}
	return(result);
}

// Finds an entry in the HashTable mInventoryByID by calling findByID(). If the std::pair<bool, HashNode*> that
//		is returned indicates that the product does not exist, displays "Inventory not found" message. If the std::pair
//		contains a true flag and valid address, calls display() on the address of the returned node.
void ProductInventoryQuery::find(const string& targetID) {
	pair<bool, HashNode<string, Product*>*> result = this->findByID(targetID);
	if (result.first == false) {
		cout << "Inventory not found." << endl;
	}
	else {
		result.second->display(cout);
	}
}

// Finds an entry in the HashTable mInventoryByCategory by calling listMatchingTargets(), a HashTable method.
void ProductInventoryQuery::listInventory(const string& targetID) {
	mInventoryByCategory->listMatchingTargets(cout, targetID);
}