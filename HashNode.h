#ifndef HASHNODE_H
#define HASHNODE_H

#include <ostream>
#include <string>

using namespace std;

template <class T1, class T2>
class HashNode {
public:
	// Constructor
	HashNode();
	HashNode(const T1& key, const T2& value);

	// Destructor
	~HashNode();

	// Copy Constructor
	HashNode(HashNode& original);

	// Move Constructor
	HashNode(HashNode&& original, HashNode*& ptrOriginal);

	// Mutator
	void setNext(HashNode* next);

	// Accessor
	HashNode*& getNextPtr(void);
	T1 getKey(void);
	T2 getValue(void);

	// Display
	void display(ostream& out);

	// Contains
	bool hasCategory(string& searchCategory);

private:
	T1 mKey;
	T2 mValue;
	HashNode<T1, T2>* mpNext;
};

// HashNode default constructor with no values
template<class T1, class T2>
HashNode<T1, T2>::HashNode() {
	mKey;
	mValue;
	mpNext = nullptr;
}

// HashNode Constructor with values passed as parameters
template<class T1, class T2>
HashNode<T1, T2>::HashNode(const T1& key, const T2& value) {
	mKey = key;
	mValue = value;
	mpNext = nullptr;
}

// HashNode destructor, all memory management is handled by HashTable object destructor
//		so no heap management required here
template<class T1, class T2>
HashNode<T1, T2>::~HashNode() {
	
}

// HashNode Copy Constructor, never called but necessary
template<class T1, class T2>
HashNode<T1, T2>::HashNode(HashNode& original) {
	mKey = original.getKey();
	mValue = original.getValue();
	mpNext = nullptr;
}

// HashNode Move constructor, also never used
template<class T1, class T2>
HashNode<T1, T2>::HashNode(HashNode<T1, T2>&& original, HashNode<T1, T2>*& ptrOriginal) {
	mKey = original.getKey();
	mValue = original.getValue();
	mpNext = original.getNextPtr();
	ptrOriginal = this;
}

// Mutator for next pointer
template<class T1, class T2>
void HashNode<T1, T2>::setNext(HashNode<T1, T2>* next) {
	mpNext = next;
}

// Accessor for next pointer
template<class T1, class T2>
HashNode<T1, T2>*& HashNode<T1, T2>::getNextPtr(void) {
	return mpNext;
}

// Accessor for key
template<class T1, class T2>
T1 HashNode<T1, T2>::getKey(void) {
	return(mKey);
}

// Accessor for value
template<class T1, class T2>
T2 HashNode<T1, T2>::getValue(void) {
	return(mValue);
}

// Calls displayProduct() on the template class T2
// Precondition: T2 must be pointer to obj type and have
//		a member called displayProduct().
template<class T1, class T2>
void HashNode<T1, T2>::display(ostream& out) {
	mValue->displayProduct(out);
}

// Returns a bool if the HashNode contains a string category
// Deprecated function from an earlier implementation of HashTable, never called
template<class T1, class T2>
bool HashNode<T1, T2>::hasCategory(string& searchCategory)
{
	return mValue.hasCategory(searchCategory);
}

#endif