/*
1. A move constructor is a constructor used to move resource from an rvalue reference object to a new object by swapping
   ownership of pointers rather than performing a deep copy. This can be significantly faster for moving large objects or containers.
2. A move assignment operator is a special overloaded operator that transfers data from one rvalue reference object to another
   object by swapping pointers rather than making a deep copy.

BST::empty() worst case time complexity is O(1), constant time. BST::empty() checks whether the root pointer of a BST is the null pointer
	and its time complexity does not depend on the size of the BST.
BST::add() worst case time complexity is dependent on the balance of the BST being added to. If the BST is perfectly balanced, the height of
	the tree is log(n), so the worst case time complexity for insertions is O(logn). If the BST is not balanced, in the worst case a degenerate
	linked list, the worst case time complexity for an insertion is O(n).
BST::makeEmpty() must visit all nodes once and delete them, so its worst case time complexity is O(n).
BST::printLevelOrder() visits all nodes once and prints them, so its worst case time complexity is O(n).
BST::cloneTree() makes a deep copy of a BST by visiting each node in Preorder sequence (root, left, right) and its worst case
	time complexity is O(n).
*/

#include <iostream>
#include "BST.h" 

void testPrintLevelOrder(BST<string>& testTree);
void testCopyConstructor1(BST<string>& testTree);
void testCopyConstructor2(BST<string>& testTree);
void testCopyAssignment(BST<string>& testTree);
void testMoveConstructor(BST<string>& testTree);
void testMoveAssignment();

int main(){

	BST<string> testTree({ "C", "p", "t", "s", "2", "3", "B", "S", "T" });

	testPrintLevelOrder(testTree);
	testCopyConstructor1(testTree);
	testCopyConstructor2(testTree);
	testCopyAssignment(testTree);
	testMoveConstructor(testTree);
	testMoveAssignment();

	return 0;
}


void testPrintLevelOrder(BST<string>& testTree) {
	cout << "In Order Print: ";
	testTree.printInOrder();
	cout << endl;
	cout << "Level Order Print: ";
	testTree.printLevelOrder();
	cout << endl;
	cout << "Post Order Print: ";
	testTree.printPostOrder();
	cout << endl;
	cout << "Pre Order Print: ";
	testTree.printPreOrder();
	cout << endl;
}

void testCopyConstructor1(BST<string>& testTree) {
	BST<string> newTree(testTree);
	bool sameSize = false, newTreeContainsValues = false;
	
	if (newTree.size() == testTree.size()) {
		sameSize = true;
	}
	if (newTree.contains("B") &&
		newTree.contains("S") &&
		newTree.contains("T")) {
		newTreeContainsValues = true;
	}
	if (sameSize && newTreeContainsValues) {
		cout << "Copy constructor test-1 passed!" << endl;
	}
	else {
		cout << "Copy constructor test-1 failed!" << endl;
		cout << "bst_test: ";
		testTree.printLevelOrder();
		cout << endl << "bst_copy1: ";
		newTree.printLevelOrder();
	}
}

void testCopyConstructor2(BST<string>& testTree) {
	BST<string> newTree(testTree);

	newTree.getNode("B")->setValue("A");
	if (newTree.contains("A") && !newTree.contains("B")) {
		cout << "Copy constructor test-2 passed!" << endl;
	}
	else {
		cout << "Copy constructor test-2 failed!" << endl;
		newTree.printLevelOrder();
	}
}

void testCopyAssignment(BST<string>& testTree) {
	BST<string> newTree = testTree;
	bool sameSize = false, newTreeContainsValues = false;
	if (newTree.contains("B") &&
		newTree.contains("S") &&
		newTree.contains("T")) {
		newTreeContainsValues = true;
	}
	if (newTree.size() == testTree.size()) {
		sameSize = true;
	}
	if (sameSize && newTreeContainsValues) {
		cout << "Copy assignment operator test passed!" << endl;
	}
	else {
		cout << "Copy assignment operator test failed!" << endl;
		cout << "Original tree Level Order: ";
		testTree.printLevelOrder();
		cout << endl << "Copy tree Level Order: ";
		newTree.printLevelOrder();
		cout << endl;
	}
}

void testMoveConstructor(BST<string>& testTree) {
	BST<string> movedBST(move(testTree));
	bool newBSTContainsValues = false, testTreeIsEmpty = false, newTreeHasNine = false;

	if (movedBST.contains("B") &&
		movedBST.contains("S") &&
		movedBST.contains("T")) {
		newBSTContainsValues = true;
	}
	if (testTree.empty()) {
		testTreeIsEmpty = true;
	}
	if (movedBST.size() == 9) {
		newTreeHasNine = true;
	}
	if (testTreeIsEmpty && newBSTContainsValues && newTreeHasNine) {
		cout << "Move constructor test passed!" << endl;
	}
	else {
		cout << "Move constructo test failed!" << endl;
		movedBST.printLevelOrder();
	}
}

void testMoveAssignment() {
	BST<string> BST_move2 = BST<string>({ "B", "S", "T" });
	bool BSTContainsValues = false, correctSize = false;

	if (BST_move2.contains("B") &&
		BST_move2.contains("S") &&
		BST_move2.contains("T")) {
		BSTContainsValues = true;
	}
	if (BST_move2.size() == 3) {
		correctSize = true;
	}
	if (correctSize && BSTContainsValues) {
		cout << "Move assignment operator test passed!" << endl;
	}
	else {
		cout << "Move assignment operator test failed!" << endl;
		BST_move2.printLevelOrder();
	}
}