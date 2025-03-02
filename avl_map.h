#ifndef AVLMAP_H
#define AVLMAP_H

#include <stack>
#include "avlNode.h"

template <class T1, class T2>
class AVL_Map {
public:
	// Constructor
	AVL_Map();

	// Copy Constructor
	AVL_Map(AVL_Map& original);

	// Destructor
	~AVL_Map();

	// Accessor
	AVL_Node<T1, T2>* getRoot();

	// Mutator
	void setRoot(AVL_Node<T1, T2>*& newRoot);

	// Iterator
	class AVL_Iterator {
	public:
		// Constructor
		AVL_Iterator();

		// Copy Constructor
		AVL_Iterator(const AVL_Iterator& original);

		// Destructor
		~AVL_Iterator();

		// Accessors
		AVL_Node<T1, T2>* getCurrent() const;
		stack<AVL_Node<T1, T2>*> getStack() const;

		// Advance
		void advanceIterator();

		// Operators
		bool operator==(const AVL_Map<T1, T2>::AVL_Iterator& it);
		bool operator!=(const AVL_Map<T1, T2>::AVL_Iterator& it);
		AVL_Map<T1, T2>::AVL_Iterator& operator=(const AVL_Map<T1, T2>::AVL_Iterator& original);
		AVL_Node<T1, T2>*& operator*();

		AVL_Node<T1, T2>* mpCurrent;
		stack<AVL_Node<T1, T2>*> mNextParent;
	};

	// Begin and End
	AVL_Map<T1, T2>::AVL_Iterator begin();
	AVL_Map<T1, T2>::AVL_Iterator end();

	// Public Methods
	void insert(const T1& newKey, const T2& newValue);
	void erase(const T1& keyValue);
	AVL_Iterator find(const T1& keyValue);
	int size();

private:
	AVL_Node<T1, T2>* mpRoot;

	// Insert Private Helpers
	AVL_Node<T1, T2>* insert(AVL_Node<T1, T2>* rootPtr, const T1& newKey, const T2& newValue);
	AVL_Node<T1, T2>* rotateLeft(AVL_Node<T1, T2>* rotateNode);
	AVL_Node<T1, T2>* rotateRight(AVL_Node<T1, T2>* rotateNode);

	// Erase Private Helpers
	AVL_Node<T1, T2>* eraseHelper(T1& keyValue, AVL_Node<T1, T2>* rootPtr);
	AVL_Node<T1, T2>* findMinimumDownstreamKey(AVL_Node<T1, T2>* rootPtr);

	// Delete Tree Private Helper
	void deleteTree(AVL_Node<T1, T2>* rootPtr);

	// Deep Copy Tree Private Helper
	AVL_Node<T1, T2> deepCopyHelper(AVL_Node<T1, T2>* original);

	// Private Size Helper
	int size(AVL_Node<T1, T2>* rootPtr);
};


// Default Template Constructor
// Constructs an AVL_Map object and initializes the mpRoot data member to the nullptr
template<class T1, class T2>
AVL_Map<T1, T2>::AVL_Map()
{
	mpRoot = nullptr;
}

// Copy Constructor
// Makes a deep copy of a tree using the helper function deepCopyHelper(), which makes
//		deep copies recursively node by node.
template<class T1, class T2>
AVL_Map<T1, T2>::AVL_Map(AVL_Map<T1, T2>& original)
{
	mpRoot = deepCopyHelper(original.mpRoot);
}

// Deep Copy Helper Method
// Makes a deep copy of a node by recursively calling itself node by node on its children
template<class T1, class T2>
AVL_Node<T1, T2> AVL_Map<T1, T2>::deepCopyHelper(AVL_Node<T1, T2>* original) {
	AVL_Node<T1, T2>* newNode = nullptr;
	if (original != nullptr) {
		newNode = new AVL_Node<T1, T2>(original);
		if (original->getLeftPointer() != nullptr) {
			newNode->setLeft(deepCopyHelper(original->getLeftPointer()));
		}
		if (original->getRightPointer() != nullptr) {
			newNode->setRight(deepCopyHelper(original->getRightPointer()));
		}
	}
	return(newNode);
}

// Destructor
// Deletes an AVL_Map object using helper function deleteTree()
template<class T1, class T2>
AVL_Map<T1, T2>::~AVL_Map()
{
	deleteTree(mpRoot);
}

// Accessor
// Returns a copy of the mpRoot data member
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::getRoot()
{
	return mpRoot;
}

// Mutator
// Sets the mpRoot data member to an input reference to a pointer to an AVL_Node
template<class T1, class T2>
void AVL_Map<T1, T2>::setRoot(AVL_Node<T1, T2>*& newRoot)
{
	mpRoot = newRoot;
}

// Returns an iterator to the beginning of the AVL_Map, i.e. the AVL_Node that holds
//		the smallest mKey member in the tree. Does this by going left in the tree as
//		much as possible, adding the current node to a stack before it does so. When
//		the pointer to the left child is a nullptr, the current node is the smallest
//		in the AVL_Map.
template<class T1, class T2>
typename AVL_Map<T1, T2>::AVL_Iterator AVL_Map<T1, T2>::begin()
{
	AVL_Iterator it;
	it.mpCurrent = mpRoot;

	while (it.mpCurrent && (it.mpCurrent)->getLeftPointer()) {
		it.mNextParent.push(it.mpCurrent);
		it.mpCurrent = it.mpCurrent->getLeftPointer();
	}
	return(it);
}

// Returns an empty iterator which holds a nullptr for the current node and an empty
//		stack of nodes. This configuration corresponds to the iterator's format when
//		it has reached the end of an AVL_Map.
template<class T1, class T2>
typename AVL_Map<T1, T2>::AVL_Iterator AVL_Map<T1, T2>::end()
{
	AVL_Map<T1, T2>::AVL_Iterator it;
	return(it);
}

// Inserts a key-value pair into the AVL_Map using helper function insert()
template<class T1, class T2>
void AVL_Map<T1, T2>::insert(const T1& newKey, const T2& newValue)
{
	mpRoot = this->insert(mpRoot, newKey, newValue);
}

// Inserts a key-value pair into an AVL_Map using the following algorithm.
// Takes a pointer to a root node. If the root is nullptr, inserts allocates heap space for
//		a new node and sets the rootPtr equal to this address. If the root is not nullptr, determines
//		which direction to insert the value by comparing to rootPtr's key, calling insert() recursively
//		on either the left or right subtree depending on the key comparison.
// Once the recursive calls have resulted in insertion, updates the height of the rootPtr and determines
//		rootPtr's balance factor.
// If the rootPtr's balance factor is greater than 1 or less than -1, then determines which of the four
//		(LL, LR, RL, RR) cases exists and performs rotations as necessary to balance the subtree. These
//		rotations may change the value of rootPtr but rootPtr will always be the top of the current subtree.
// Returns the address of the rootPtr.
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::insert(AVL_Node<T1, T2>* rootPtr, const T1& newKey, const T2& newValue)
{
	if (rootPtr == nullptr) {
		rootPtr = new AVL_Node<T1, T2>(newKey, newValue);
	}
	else if (rootPtr->getKey() > newKey) {
		rootPtr->setLeft(this->insert(rootPtr->getLeftPointer(), newKey, newValue));
	}
	else if (rootPtr->getKey() < newKey) {
		rootPtr->setRight(this->insert(rootPtr->getRightPointer(), newKey, newValue));
	}

	rootPtr->updateHeight();
	int balance = rootPtr->getBalanceFactor();

	if (balance > 1) { // right heavy
		if (rootPtr->getRightPointer()->getBalanceFactor() > 0) { // RR case
			rootPtr = rotateLeft(rootPtr);
		}
		else { // RL case
			rootPtr->setRight(rotateRight(rootPtr->getRightPointer()));
			rootPtr = rotateLeft(rootPtr);
		}
	}
	else if (balance < -1) {
		if (rootPtr->getLeftPointer()->getBalanceFactor() < 0) { // LL case
			rootPtr = rotateRight(rootPtr);
		}
		else { // LR case
			rootPtr->setLeft(rotateLeft(rootPtr->getLeftPointer()));
			rootPtr = rotateRight(rootPtr);
		}
	}

	return(rootPtr);
}

// Rotates the tree below the input parameter rotateNode left by swapping pointers.
//		rotateNode's right child hands off its left pointer to rotateNode's right
//		pointer, and rotateNode's right child takes rotateNode's left pointer.
//		rotateNode's original right child becomes the new root, and this address is
//		returned.
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::rotateLeft(AVL_Node<T1, T2>* rotateNode)
{
	AVL_Node<T1, T2>* x = rotateNode->getRightPointer();
	AVL_Node<T1, T2>* y = x->getLeftPointer();
	x->setLeft(rotateNode);
	rotateNode->setRight(y);
	x->updateHeight();
	rotateNode->updateHeight();
	return(x);

}

// Rotates the tree below the input parameter rotateNode right by swapping pointers.
//		rotateNode's left child hands off its right subtree to rotateNode's left
//		pointer, and rotateNode hands off its left pointer to its former child's right
//		pointer. rotateNode's original left child becomes the new root node of the tree,
//		and this address is returned.
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::rotateRight(AVL_Node<T1, T2>* rotateNode)
{
	AVL_Node<T1, T2>* x = rotateNode->getLeftPointer();
	AVL_Node<T1, T2>* y = x->getRightPointer();
	x->setRight(rotateNode);
	rotateNode->setLeft(y);
	x->updateHeight();
	rotateNode->updateHeight();
	return(x);
}

// Removes a node from an AVL_Map using the following algorithm.
//		Takes the rootPtr to the subtree and the key being searched for as inputs. If
//		rootPtr == nullptr, then the key does not exist on this branch and the function
//		returns. Otherwise, recursively calls eraseHelper() on either the left or right
//		subtrees depending on a comparison of keys until it finds a match for the key.
//		Once a match has been found:
//			If the matching node has no children, deletes the node and returns a nullptr.
//			If the matching node has one child, deletes the node at rootPtr and assigns
//				rootPtr the address of the child node.
//			If the matching node has two children, finds the minimum key downstream of
//				the matching node's right child. Once this node has been found, deletes
//				the node at rootPtr, creates a new node on the heap and copies the minimum
//				key's data to the new node, and deletes the minimum key's node downstream
//				by recursively calling eraseHelper(), using its return value to set the new
//				right subtree. New rootPtr node takes the original rootPtr's left subtree as
//				its own.
// Once a node has been removed, updates the height of rootPtr and computes a balance factor.
// If the tree beneath rootPtr is unbalanced, performs balancing operations identical to those
// in the insert() helper function consistent with AVL Tree balancing.
// Returns the rootPtr.
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::eraseHelper(T1& keyValue, AVL_Node<T1, T2>* rootPtr)
{
	if (rootPtr == nullptr) {
		return rootPtr;
	}
	if (keyValue < rootPtr->getValue()) {
		rootPtr->setLeft(eraseHelper(keyValue, rootPtr->getLeftPointer()));
	}
	else if (keyValue > rootPtr->getValue()) {
		rootPtr->setRight(eraseHelper(keyValue, rootPtr->getRightPointer()));
	}
	else if (keyValue == rootPtr->getValue()) {
		// case: no children
		if (rootPtr->getLeftPointer() == nullptr &&
			rootPtr->getRightPointer() == nullptr) {
			delete rootPtr;
			rootPtr = nullptr;
		}
		// case: left child, no right child
		else if (rootPtr->getLeftPointer() != nullptr &&
			rootPtr->getRightPointer() == nullptr) {
			AVL_Node<T1, T2>* temp = rootPtr->getLeftPointer();
			delete rootPtr;
			rootPtr = temp;
		}
		// case: right child, no left child
		else if (rootPtr->getLeftPointer() == nullptr &&
			rootPtr->getRightPointer() != nullptr) {
			AVL_Node<T1, T2>* temp = rootPtr->getRightPointer();
			delete rootPtr;
			rootPtr = temp;
		}
		// case: two children
		else if (rootPtr->getLeftPointer() != nullptr ||
			rootPtr->getRightPointer() != nullptr) {
			AVL_Node<T1, T2>* left = rootPtr->getLeftPointer(), * right = rootPtr->getRightPointer();
			AVL_Node<T1, T2>* minimum = findMinimumDownstreamKey(right);
			delete rootPtr;
			rootPtr = new AVL_Node<T1, T2>(minimum->getKey, minimum->getValue());
			rootPtr->setRight(eraseHelper(minimum->getKey(), right));
			rootPtr->setLeft(left);
		}
	}

	rootPtr->updateHeight();
	int balance = rootPtr->getBalanceFactor();

	if (balance < -1) { // left heavy
		if (rootPtr->getLeftPointer()->getBalanceFactor() == -1) { // LL case
			rootPtr = rotateRight(rootPtr);
		}
		else { // LR case
			rootPtr->setLeft(rotateLeft(rootPtr->getLeftPointer()));
			rootPtr = rotateRight(rootPtr);
		}
	}
	else if (balance > 1) { // right heavy
		if (rootPtr->getRightPointer()->getBalanceFactor() == 1) { // RR case
			rootPtr = rotateLeft(rootPtr);
		}
		else { // RL case
			rootPtr->setRight(rotateRight(rootPtr->getRightPointer()));
			rootPtr = rotateRight(rootPtr);
		}
	}
	return rootPtr;
}

// Finds the smallest key downstream of an input node by following left pointers until the next
// left pointer is a nullptr.
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::findMinimumDownstreamKey(AVL_Node<T1, T2>* rootPtr)
{
	AVL_Node<T1, T2>* pCurrent = rootPtr;
	while (pCurrent->getLeftPointer() != nullptr) {
		pCurrent = pCurrent->getLeftPointer();
	}
	return(pCurrent);
}

// Deletes a tree by calling deleteTree() recursively in post-order traversal.
template<class T1, class T2>
void AVL_Map<T1, T2>::deleteTree(AVL_Node<T1, T2>* rootPtr)
{
	if (rootPtr != nullptr) {
		deleteTree(rootPtr->getLeftPointer());
		deleteTree(rootPtr->getRightPointer());
		delete rootPtr;
	}
}

// Erases an AVL_Node containing an input keyValue from an AVL_Map using helper function eraseHelper()
template<class T1, class T2>
void AVL_Map<T1, T2>::erase(const T1& keyValue) {
	this->eraseHelper(keyValue, mpRoot);
}

// Constructor
// Initializes mpCurrent to nullptr. std::stack data member is empty by default.
template<class T1, class T2>
AVL_Map<T1, T2>::AVL_Iterator::AVL_Iterator()
{
	mpCurrent = nullptr;
}

// Copy Constructor
// Constructs an iterator by duplicating the data members of another iterator.
template<class T1, class T2>
AVL_Map<T1, T2>::AVL_Iterator::AVL_Iterator(const AVL_Iterator& original)
{
	this->mpCurrent = original.getCurrent();
	this->mNextParent = original.getStack();
}

// Destructor
// Destroys an iterator using a default destructor
template<class T1, class T2>
AVL_Map<T1, T2>::AVL_Iterator::~AVL_Iterator()
{
	
}

// Accessor
// Returns a copy of a pointer to the mpCurrent member of the iterator
template<class T1, class T2>
AVL_Node<T1, T2>* AVL_Map<T1, T2>::AVL_Iterator::getCurrent() const
{
	return mpCurrent;
}

// Accessor
// Returns a copy of the stack of pointers to AVL_Nodes that is the mNextParent member of an Iterator
template<class T1, class T2>
stack<AVL_Node<T1, T2>*> AVL_Map<T1, T2>::AVL_Iterator::getStack() const
{
	return(mNextParent);
}

// Advances to the next highest key node in an AVL_Map by advancing down the right subtree once if possible,
//		then left as far as possible, adding nodes to the stack each time a traversal is made. If the current
//		node has no children, then the next highest key will be found at the top of the stack. If the current
//		node has no children and the stack is empty, then the current node is the highest in the AVL_Map, and
//		advancing the iterator sets the mpCurrent member to nullptr.
template<class T1, class T2>
void AVL_Map<T1, T2>::AVL_Iterator::advanceIterator()
{
	if (mpCurrent != nullptr) {
		// if no right child and stack is not empty, take top of stack
		if (mpCurrent->getRightPointer() == nullptr && !mNextParent.empty()) {
			mpCurrent = mNextParent.top();
			mNextParent.pop();
		}
		// if right child exists
		else if (mpCurrent->getRightPointer()) {
			mpCurrent = mpCurrent->getRightPointer();
			// if left child of current node exists, add to stack and advance to the left node
			while (mpCurrent->getLeftPointer()) {
				mNextParent.push(mpCurrent);
				mpCurrent = mpCurrent->getLeftPointer();
			}
		}
		else if (mpCurrent->getRightPointer() == nullptr && mNextParent.empty()) {
			mpCurrent = nullptr;
		}
	}
}

// Overloads the equality operator for use with AVL_Map::Iterator
template<class T1, class T2>
bool AVL_Map<T1, T2>::AVL_Iterator::operator==(const AVL_Iterator& it)
{
	return this->mpCurrent == it.mpCurrent;
}

// Overloads the inequality operator for use with AVL_Map::Iterator
template<class T1, class T2>
bool AVL_Map<T1, T2>::AVL_Iterator::operator!=(const AVL_Iterator& it)
{
	return this->mpCurrent != it.mpCurrent;
}

// Overloads the assignment operator for use with AVL_Map::Iterator
template<class T1, class T2>
typename AVL_Map<T1, T2>::AVL_Iterator& AVL_Map<T1, T2>::AVL_Iterator::operator=(const AVL_Map<T1, T2>::AVL_Iterator& original)
{
	if (this != &original) {
		this->mpCurrent = original.mpCurrent;
		this->mNextParent = original.mNextParent;
	}
	return *this;
}

// Overloads the indirection operator for use with iterators. Returns a reference to the 
//		mpCurrent member which is a pointer to an AVL_Node
template<class T1, class T2>
AVL_Node<T1, T2>*& AVL_Map<T1, T2>::AVL_Iterator::operator*(void)
{
	return(this->mpCurrent);
}

// Finds a node in an AVL_Map that contains an input key. Returns an Iterator to that node.
template<class T1, class T2>
typename AVL_Map<T1, T2>::AVL_Iterator AVL_Map<T1, T2>::find(const T1& keyValue)
{
	AVL_Iterator it;
	it.mpCurrent = mpRoot;
	bool found = false;
	while (!found && it.mpCurrent != nullptr) {
		if (keyValue < it.mpCurrent->getKey()) {
			it.mNextParent.push(it.mpCurrent);
			it.mpCurrent = it.mpCurrent->getLeftPointer();
		}
		else if (keyValue > it.mpCurrent->getKey()) {
			it.mpCurrent = it.mpCurrent->getRightPointer();
		}
		else if (keyValue == it.mpCurrent->getKey()) {
			found = true;
		}
	}

	return(it);
}

// Returns the size of an AVL_Map using private helper function size()
template<class T1, class T2>
int AVL_Map<T1, T2>::size() {
	return (size(mpRoot));
}

// Calculates the size of an AVL_Map by recursively calling size() on the left and right
//		children of a root node.
template<class T1, class T2>
int AVL_Map<T1, T2>::size(AVL_Node<T1, T2>* rootPtr) {
	int treeSize = 0;
	if (rootPtr != nullptr) {
		treeSize = 1 + size(rootPtr->getRightPointer()) + size(rootPtr->getLeftPointer());
	}
	return(treeSize);
}

#endif
