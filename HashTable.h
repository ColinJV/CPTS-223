#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <unordered_map>
#include <cmath>
#include <chrono>

using namespace std;

template<class T1, class T2>
class HashTable {
public:
	// Constructor
	HashTable(int tableSize);

	// Destructor
	~HashTable();

	// Copy Constructor
	HashTable(HashTable& original);

	// Accessor
	double getLoadFactor();
	int size();

	// Insert
	void insert(const T1& key, T2& value);

	// Contains
	bool contains(T1& searchKey);

	// Find
	HashNode<T1, T2>* findByUniqueID(const T1& targetKey);

	// Display
	void display(ostream& out, T1& targetKey);
	void listMatchingTargets(ostream& out, const T1& targetKey);
	void mergeSortAndListMatchingTargets(ostream& out, const T1& targetKey, bool descending);
	void insertionSortAndListMatchingTargets(ostream& out, const T1& targetKey, bool descending);
	vector<HashNode<T1, T2>*> buildVector(const T1& targetKey);

	// Sorting
	void mergeSort(vector<HashNode<T1, T2>*>& categories, bool descending);
	void insertionSort(vector<HashNode<T1, T2>*>& categories, bool descending);

	// Resize and Rehash
	void resize();
	int getNextPrime(int number);
	bool isPrime(int number);

private:
	HashNode<T1, T2>** table;
	int currentSize;
	int numberElements;
	double loadFactor;

	void mergeSortHelper(vector<HashNode<T1, T2>*>& categories, bool descending, int left, int right);
	void merge(vector<HashNode<T1, T2>*>& categories, bool descending, int left, int mid, int right);

};

// HashTable constructor, declares an array of pointers to HashNodes on the heap
// using an initial size passed in by value
template <class T1, class T2>
HashTable<T1, T2>::HashTable(int tableSize) {
	table = new HashNode<T1, T2>*[tableSize];
	for (int i = 0; i < tableSize; i++) {
		table[i] = nullptr;
	}
	currentSize = tableSize;
	numberElements = 0;
	loadFactor = 0;
}

// HashTable destructor, iterates through the array of pointers to HashNodes and
//		deletes the contents one by one.
template <class T1, class T2>
HashTable<T1, T2>::~HashTable() {
	for (int i = 0; i < currentSize; ++i)
	{
		HashNode<T1, T2>* pCurrent = table[i];
		while (pCurrent != nullptr) {
			HashNode<T1, T2>* pNext = pCurrent->getNextPtr();
			delete pCurrent;
			pCurrent = pNext;
		}
	}
	delete[] table;
}

// HashTable Copy Constructor
template <class T1, class T2>
HashTable<T1, T2>::HashTable(HashTable& original) {
	currentSize = original.currentSize;
	table = new HashNode<T1, T2>* [currentSize];
	for (int i = 0; i < currentSize; i++) {
		HashNode<T1, T2>* pCurrent = original.table[i];
		table[i] = pCurrent;
		while (pCurrent != nullptr) {
			HashNode<T1, T2>* pNext = pCurrent->getNextPtr();
			table[i]->setNext(pNext);
			pCurrent = pNext;
		}
	}
	numberElements = original.numberElements;
	loadFactor = original.loadFactor;
}

// Accessor for loadFactor
template<class T1, class T2>
inline double HashTable<T1, T2>::getLoadFactor()
{
	return loadFactor;
}

// Accessor for numberElements
template<class T1, class T2>
inline int HashTable<T1, T2>::size()
{
	return numberElements;
}

// Inserts a key-value pair into the HashTable according to the following algorithm.
// 1. If the HashTable's loadFactor is greater than 1, resizes and rehashes the table.
// 2. Hashes the key and attempts to insert it in the hash table.
//		If the target index of the HashTable is empty, inserts.
//		If the target index is occupied, traverses the linked list that begins at the index
//			head (separate chaining) until it reaches the end and inserts the new value to the end.
// 3. Increments numberElements and recomputes loadFactor.
template <class T1, class T2>
void HashTable<T1, T2>::insert(const T1& key, T2& value) {

	if (loadFactor > 1) {
		this->resize();
	}

	hash<T1> hasher;
	int hashedIndex = hasher(key) % currentSize;

	HashNode<T1, T2>* newNode = new HashNode<T1, T2>(key, value);

	if (table[hashedIndex] == nullptr) {
		table[hashedIndex] = newNode;
	}
	else {
		HashNode<T1, T2>* pCurrent = table[hashedIndex];
		while (pCurrent->getNextPtr() != nullptr) {
			pCurrent = pCurrent->getNextPtr();
		}
		pCurrent->setNext(newNode);
	}
	++numberElements;
	loadFactor = static_cast<double>(numberElements) / currentSize;
}

// Resizes the array of pointers to HashNodes that is the primary container of the HashTable.
// Does this in accordance with the following algorithm:
// 1. Whatever the currentSize of the table is, doubles it and adds one, then finds the next
//		prime number past this value. Once this prime number is found, sets currentSize equal to it.
// 2. Instantiates a new array of pointers to HashNode on the heap, of size currentSize. Initializes
//		the array's elements to nullptr.
// 3. For each element in the original array (named table), rehashes and inserts into the new array
//		at the correct index.
// 4. Deletes the original array, then assigns the member pointer to a pointer to HashNode named table
//		the address of the new array of pointers to HashNode on the heap.
// 5. Recomputes loadFactor for the new size.
template <class T1, class T2>
void HashTable<T1, T2>::resize() {
	int oldSize = currentSize;
	currentSize = getNextPrime(currentSize * 2 + 1);

	HashNode<T1, T2>** newTable = new HashNode<T1, T2>*[currentSize];
	for (int i = 0; i < currentSize; i++) {
		newTable[i] = nullptr;
	}

	for (int i = 0; i < oldSize; ++i) {
		HashNode<T1, T2>* pCurrent = table[i];
		while (pCurrent != nullptr) {
			HashNode<T1, T2>* pNext = pCurrent->getNextPtr();
			hash<T1> hasher;
			int hashedIndex = hasher(pCurrent->getKey()) % currentSize;
			pCurrent->setNext(newTable[hashedIndex]);
			newTable[hashedIndex] = pCurrent;
			pCurrent = pNext;
		}
	}

	delete[] table;
	table = newTable;
	loadFactor = static_cast<double>(numberElements) / currentSize;
}

// Returns a bool if a HashTable contains a key. Deprecated function from
//	a previous implementation, never called.
template <class T1, class T2>
bool HashTable<T1, T2>::contains(T1& searchKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(searchKey) % currentSize;
	bool contains = false;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];

	while (pCurrent != nullptr && !contains) {
		if (pCurrent->getKey() == searchKey) {
			contains = true;
		}
		pCurrent = pCurrent->getNextPtr();
	}

	return(contains);
}

// Finds an element in a HashTable by its key. Returns the address of that node.
template<class T1, class T2>
HashNode<T1, T2>* HashTable<T1, T2>::findByUniqueID(const T1& targetKey)
{
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % currentSize;
	bool found = false;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];

	while (pCurrent != nullptr && !found) {
		if (pCurrent->getKey() == targetKey) {
			found = true;
		}
		else {
			pCurrent = pCurrent->getNextPtr();
		}
	}

	return(pCurrent);
}

// Displays the contents of an index of a HashTable by calling display() on
// a node containing a target key.
template <class T1, class T2>
void HashTable<T1, T2>::display(ostream& out, T1& targetKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % currentSize;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];

	while (pCurrent != nullptr) {
		if (pCurrent->getKey() == targetKey) {
			pCurrent->display(out);
		}
		pCurrent = pCurrent->getNextPtr();
	}
}

// Lists every element at an index containing a key. Called by listInventory() for
//	display of products that match a category.
//  Deprecated as of PA5.
template<class T1, class T2>
void HashTable<T1, T2>::listMatchingTargets(ostream& out, const T1& targetKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % currentSize;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];
	if (pCurrent == nullptr) {
		out << "No item found." << endl;
	}
	while (pCurrent != nullptr) {
		pCurrent->getValue()->displayIDandName(out);
		pCurrent = pCurrent->getNextPtr();
	}
}

// Merge sorts and prints a list of Products according to the following algorithm.
//		1. Builds a vector of pointers to HashNodes that contain data of type T2 whose categories match an input parameter
//		   targetKey.
//		2. Sorts that vector using a custom implementation of merge sort which will sort based on sellingPrice either
//		   in ascending or descending order based on the value of a Boolean input parameter called descending.
//		3. Displays the Products in sorted order by calling displayIDandName() on those products one at a time.
template<class T1, class T2>
void HashTable<T1, T2>::mergeSortAndListMatchingTargets(ostream& out, const T1& targetKey, bool descending) {
	vector<HashNode<T1, T2>*> printList = buildVector(targetKey);
	auto start = chrono::high_resolution_clock::now();
	mergeSort(printList, descending);
	auto end = chrono::high_resolution_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
	out << "Time for merge sort: " << time << endl;
	for (int i = 0; i < printList.size(); ++i) {
		printList[i]->getValue()->displayIDandName(out);
	}
}

// Insertion sorts and prints a list of type T2 according to the following algorithm.
//		1. Builds a vector of pointers to HashNodes that contain data of type T2 whose categories match an input parameter
//		   targetKey.
//		2. Sorts that vector using a custom implementation of insertion sort which will sort based on sellingPrice either
//		   in ascending or descending order based on the value of a Boolean input parameter called descending.
//		3. Displays the Products in sorted order by calling displayIDandName() on those products one at a time.
template<class T1, class T2>
void HashTable<T1, T2>::insertionSortAndListMatchingTargets(ostream& out, const T1& targetKey, bool descending) {
	vector<HashNode<T1, T2>*> printList = buildVector(targetKey);
	auto start = chrono::high_resolution_clock::now();
	insertionSort(printList, descending);
	auto end = chrono::high_resolution_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
	out << "Time for insertion sort: " << time << endl;
	for (int i = 0; i < printList.size(); ++i) {
		printList[i]->getValue()->displayIDandName(out);
	}
}

// Sorts a vector of type T2 according to the following algorithm:
//		1. Beginning with the value at key index 1, inserts in the correct location (chosen between index 0 and 1).
//		2. Increments the key index
template<class T1, class T2>
void HashTable<T1, T2>::insertionSort(vector<HashNode<T1, T2>*>& categories, bool descending) {
	int size = categories.size();
	for (int i = 1; i < size; ++i) {
		HashNode<T1, T2>* key = categories[i];
		int j = i - 1;
		if (descending) {
			while (j >= 0 && (*(categories[j])->getValue()) < *(key->getValue())) {
				categories[j + 1] = categories[j];
				j--;
			}
			categories[j + 1] = key;
		}
		else {
			while (j >= 0 && (*(categories[j])->getValue()) > *(key->getValue())) {
				categories[j + 1] = categories[j];
				j--;
			}
			categories[j + 1] = key;
		}
	}
}

// Builds a vector of the HashNodes matching the input targetKey, which is then returned
//		and used for random access sorting.
template<class T1, class T2>
vector<HashNode<T1, T2>*> HashTable<T1, T2>::buildVector(const T1& targetKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % currentSize;

	vector<HashNode<T1, T2>*> categoryEntries;
	HashNode<T1, T2>* pCurrent = table[hashedIndex];

	while (pCurrent != nullptr) {
		categoryEntries.push_back(pCurrent);
		pCurrent = pCurrent->getNextPtr();
	}

	return(categoryEntries);
}

// Wrapper function for the merge sort algorithm. Calls mergeSortHelper() if the size of the
//		vector to be sorted is greater than 0 (i.e. it has any contents).
template<class T1, class T2>
void HashTable<T1, T2>::mergeSort(vector<HashNode<T1, T2>*>& categories, bool descending) {
	int size = categories.size();
	if (size > 0) {
		mergeSortHelper(categories, descending, 0, size - 1);
	}
}

// Breaks the vector to be sorted into smaller pieces until each section contains one value through recursive calls
//		to mergeSortHelper(). Then merges the smaller pieces by calling merge().
template<class T1, class T2>
void HashTable<T1, T2>::mergeSortHelper(vector<HashNode<T1, T2>*>& categories, bool descending, int left, int right) {
	if (left < right) {
		int mid = left + ((right - left) / 2);
		mergeSortHelper(categories, descending, left, mid);
		mergeSortHelper(categories, descending, mid + 1, right);
		merge(categories, descending, left, mid, right);
	}
}

// Merges values from smaller sections of the input vector into a local temporary vector in sorted order, then
//		moves values from the local temporary vector to the input vector so that the input vector contains the
//		sorted order values for the relevant section.
template<class T1, class T2>
void HashTable<T1, T2>::merge(vector<HashNode<T1, T2>*>& categories, bool descending, int left, int mid, int right) {
	vector<HashNode<T1, T2>*> temp;

	int i = left, j = mid + 1;

	while (i <= mid && j <= right) {
		if (descending) {
			if (*(categories[i]->getValue()) < *(categories[j]->getValue())) {
				temp.push_back(categories[j++]);
			}
			else {
				temp.push_back(categories[i++]);
			}
		}
		else {
			if (*(categories[i]->getValue()) <= *(categories[j]->getValue())) {
				temp.push_back(categories[i++]);
			}
			else {
				temp.push_back(categories[j++]);
			}
		}
	}

	while (i <= mid) {
		temp.push_back(categories[i++]);
	}

	while (j <= right) {
		temp.push_back(categories[j++]);
	}

	for (i = 0; i < temp.size(); i++) {
		categories[left + i] = temp[i];
	}
}

// Returns the next prime number greater than the input value.
template<class T1, class T2>
int HashTable<T1, T2>::getNextPrime(int number) {
	bool prime = false;
	while (!prime) {
		prime = isPrime(number);
		if (!prime) {
			number++;
		}
	}
	return(number);
}

// Returns a bool indicating if an input parameter integer is prime.
template <class T1, class T2>
bool HashTable<T1, T2>::isPrime(int number) {
	if (number < 2) {
		return false;
	}
	if (number == 2 || number == 3) {
		return true;
	}
	if (number % 2 == 0) {
		return false;
	}
	for (int i = 3; i <= sqrt(number); i += 2) {
		if (number % i == 0) {
			return false;
		}
	}
	return true;
}

#endif