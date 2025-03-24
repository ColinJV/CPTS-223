#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <unordered_map>

using namespace std;

// If we were allowed to use STL I would not define a static size and just use a vector
// but since I don't know how I would resize and rehash without a vector, I'm doing this.
#define TABLE_SIZE 10007

template<class T1, class T2>
class HashTable {
public:
	// Constructor
	HashTable();

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

private:
	HashNode<T1, T2>* table[TABLE_SIZE];
	int numberElements;
	double loadFactor;
};


template <class T1, class T2>
HashTable<T1, T2>::HashTable() {
	for (int i = 0; i < TABLE_SIZE; ++i) {
		table[i] = nullptr;
	}
	numberElements = 0;
	loadFactor = 0;
}

template <class T1, class T2>
HashTable<T1, T2>::~HashTable() {
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		while (table[i] != nullptr) {
			HashNode<T1, T2>* pNext = table[i]->getNextPtr();
			delete table[i];
			table[i] = pNext;
		}
	}
}

template <class T1, class T2>
HashTable<T1, T2>::HashTable(HashTable& original) {
	// do this later
}

template<class T1, class T2>
inline double HashTable<T1, T2>::getLoadFactor()
{
	return loadFactor;
}

template<class T1, class T2>
inline int HashTable<T1, T2>::size()
{
	return numberElements;
}

template <class T1, class T2>
void HashTable<T1, T2>::insert(const T1& key, T2& value) {
	hash<T1> hasher;
	int hashedIndex = hasher(key) % TABLE_SIZE;

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
	loadFactor = numberElements / TABLE_SIZE;
}

template <class T1, class T2>
bool HashTable<T1, T2>::contains(T1& searchKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(searchKey) % TABLE_SIZE;
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

template<class T1, class T2>
HashNode<T1, T2>* HashTable<T1, T2>::findByUniqueID(const T1& targetKey)
{
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % TABLE_SIZE;
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

template <class T1, class T2>
void HashTable<T1, T2>::display(ostream& out, T1& targetKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % TABLE_SIZE;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];

	while (pCurrent != nullptr) {
		if (pCurrent->getKey() == targetKey) {
			pCurrent->display(out);
		}
		pCurrent = pCurrent->getNextPtr();
	}
}

template<class T1, class T2>
void HashTable<T1, T2>::listMatchingTargets(ostream& out, const T1& targetKey) {
	hash<T1> hasher;
	int hashedIndex = hasher(targetKey) % TABLE_SIZE;

	HashNode<T1, T2>* pCurrent = table[hashedIndex];
	while (pCurrent != nullptr) {
		pCurrent->getValue()->displayIDandName(cout);
		pCurrent = pCurrent->getNextPtr();
	}
}
#endif