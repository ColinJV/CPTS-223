#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>
#include <algorithm>

using namespace std;

template <class T1, class T2>
class AVL_Node {
public:
	// Constructor
	AVL_Node(const T1& mKey, const T2& mValue);
	AVL_Node();

	// Copy Constructor
	AVL_Node(AVL_Node& original);

	// Destructor
	~AVL_Node();

	// Mutators
	void setKey(const T1& newKey);
	void setValue(const T2& newValue);
	void setLeft(AVL_Node* newLeft);
	void setRight(AVL_Node* newRight);
	void setHeight(const int& newHeight);

	// Accessors
	T1 getKey();
	T2 getValue();
	AVL_Node* getLeftPointer();
	AVL_Node* getRightPointer();
	int getHeight();

	// Other
	int getBalanceFactor();
	void updateHeight();
	int determineHeight();

private:
	T1 mKey;
	T2 mValue;
	AVL_Node* mpLeft;
	AVL_Node* mpRight;
	int mHeight;
};


// Template Constructor
// Sets mKey and mValue to the value of corresponding input parameters and the left and right pointers
//		to nullptr, initializing the height to 0.
template<class T1, class T2>
AVL_Node<T1, T2>::AVL_Node(const T1& newKey, const T2& newValue)
{
	mKey = newKey;
	mValue = newValue;
	mpLeft = nullptr;
	mpRight = nullptr;
	mHeight = 0;
}

// Default Template Constructor
// Sets left and right pointers to nullptr, initializing the height to 0.
template<class T1, class T2>
AVL_Node<T1, T2>::AVL_Node()
{
	mpLeft = nullptr;
	mpRight = nullptr;
	mHeight = 0;
}

// Template Copy Constructor
// Sets mKey and mValue to copies of another Node's mKey and mValue members
template<class T1, class T2>
AVL_Node<T1, T2>::AVL_Node(AVL_Node& original)
{
	mKey = original.mKey;
	mValue = original.mValue;

}

// Template Destructor
// Empty since no explicit destruction needed
template<class T1, class T2>
AVL_Node<T1, T2>::~AVL_Node()
{
	
}

// Template Mutator
// Sets an mKey value to the value of an input reference
template<class T1, class T2>
void AVL_Node<T1, T2>::setKey(const T1& newKey)
{
	mKey = newKey;
}

// Template Mutator
// Sets an mValue value to the value of an input reference
template<class T1, class T2>
void AVL_Node<T1, T2>::setValue(const T2& newValue)
{
	mValue = newValue;
}

// Template Mutator
// Sets the left pointer mpLeft to an input AVL_Node address
template<class T1, class T2>
void AVL_Node<T1, T2>::setLeft(AVL_Node<T1, T2>* newLeft)
{
	mpLeft = newLeft;
}

// Template Mutator
// Sets the right pointer mpRight to an input AVL_Node address
template<class T1, class T2>
void AVL_Node<T1, T2>::setRight(AVL_Node<T1, T2>* newRight)
{
	mpRight = newRight;
}

// Template Mutator
// Sets the mHeight of a node to a copy of an input reference integer
template<class T1, class T2>
void AVL_Node<T1, T2>::setHeight(const int& newHeight)
{
	mHeight = newHeight;
}

// Template Accessor
// Returns a copy of the mKey data member
template<class T1, class T2>
T1 AVL_Node<T1, T2>::getKey()
{
	return mKey;
}

// Template Accessor
// Returns a copy of the mValue data member
template<class T1, class T2>
T2 AVL_Node<T1, T2>::getValue()
{
	return mValue;
}

// Template Accessor
// Returns a copy of the mpLeft data member
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Node<T1, T2>::getLeftPointer()
{
	return mpLeft;
}

// Template Accessor
// Returns a copy of the mpRight data member
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Node<T1, T2>::getRightPointer()
{
	return mpRight;
}

// Template Accessor
// Returns a copy of an integer that corresponds to the height of a node.
// Checks for this != nullptr as this method can be called on a nullptr when
//		recursively determining the height of a subtree.
template<class T1, class T2>
int AVL_Node<T1, T2>::getHeight()
{
	int height = -1;
	if (this != nullptr) {
		height = mHeight;
	}
	return(height);
}

// Computes the balance factor of the subtree of which the node that calls the function
//		is the root by calling the function getHeight() on each child node and
//		subtracting the left height from the right height.
template<class T1, class T2>
int AVL_Node<T1, T2>::getBalanceFactor()
{
	int balance = 0;

	if (this != nullptr) {
		balance = mpRight->getHeight() - mpLeft->getHeight();
	}

	return(balance);
}

// Updates the height of a node after shift operations by calling recursive function
//		determineHeight().
template<class T1, class T2>
void AVL_Node<T1, T2>::updateHeight()
{
	int height = -1;

	if (this != nullptr) {
		height = this->determineHeight();
		this->setHeight(height);
	}
}

// Determines the height of an AVL_Node by taking the max of the height of the left
//		and right subtrees, found by calling determineHeight() recursively on the child
//		nodes.
template<class T1, class T2>
int AVL_Node<T1, T2>::determineHeight()
{
	int height = 0, leftHeight = 0, rightHeight = 0;
	if (this->getLeftPointer() != nullptr) {
		leftHeight = 1 + this->getLeftPointer()->determineHeight();
	}
	if (this->getRightPointer() != nullptr) {
		rightHeight = 1 + this->getRightPointer()->determineHeight();
	}
	height = max(leftHeight, rightHeight);
	return(height);
}


#endif