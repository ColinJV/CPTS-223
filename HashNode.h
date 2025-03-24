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

template<class T1, class T2>
HashNode<T1, T2>::HashNode() {
	mKey;
	mValue;
	mpNext = nullptr;
}

template<class T1, class T2>
HashNode<T1, T2>::HashNode(const T1& key, const T2& value) {
	mKey = key;
	mValue = value;
	mpNext = nullptr;
}

template<class T1, class T2>
HashNode<T1, T2>::~HashNode() {
	delete mValue;
}

template<class T1, class T2>
HashNode<T1, T2>::HashNode(HashNode& original) {
	mKey = original.getKey();
	mValue = original.getValue();
	mpNext = nullptr;
}

template<class T1, class T2>
HashNode<T1, T2>::HashNode(HashNode<T1, T2>&& original, HashNode<T1, T2>*& ptrOriginal) {
	mKey = original.getKey();
	mValue = original.getValue();
	mpNext = original.getNextPtr();
	ptrOriginal = this;
}

template<class T1, class T2>
void HashNode<T1, T2>::setNext(HashNode<T1, T2>* next) {
	mpNext = next;
}

template<class T1, class T2>
HashNode<T1, T2>*& HashNode<T1, T2>::getNextPtr(void) {
	return mpNext;
}

template<class T1, class T2>
T1 HashNode<T1, T2>::getKey(void) {
	return(mKey);
}

template<class T1, class T2>
T2 HashNode<T1, T2>::getValue(void) {
	return(mValue);
}

template<class T1, class T2>
void HashNode<T1, T2>::display(ostream& out) {
	mValue->displayProduct(out);
}

template<class T1, class T2>
bool HashNode<T1, T2>::hasCategory(string& searchCategory)
{
	return mValue.hasCategory(searchCategory);
}

#endif