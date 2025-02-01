#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

template <class T>
class Node {
public:
    // Constructor
    Node(T* newData);
    Node();

    // Destructor
    ~Node();

    // Accessor
    T* getData(void) const;
    Node<T>* getNext(void) const;

    // Mutator
    void setData(T* newData);
    void setNext(Node<T>* newNextPtr);

    // Other methods
    void printNode(void);
    void printNodeToFile(ofstream& outputFile);
    bool duplicateExists(T* targetData);

private:
    T* mData;
    Node<T>* mpNext;
};


/********************************************************************************************************
* Function: Node constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Constructs a Node with data supplied by the input parameter
* Input parameters: T* newData, a pointer to a generic data type for construction of the Node
* Returns: Node object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
Node<T>::Node(T* newData) {
    mData = newData;
    mpNext = nullptr;
}


/********************************************************************************************************
* Function: Node constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a Node with no contents
* Input parameters: none
* Returns: Node object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
Node<T>::Node() {
    mData = nullptr;
    mpNext = nullptr;
}

/********************************************************************************************************
* Function: Node destructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Destroys a Node. Explicitly the destructor for the generic data type T.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
Node<T>::~Node() {
    delete mData;
}

/********************************************************************************************************
* Function: getData()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns a pointer to a generic data type T that is the contents of a Node.
* Input parameters: none
* Returns: T* mData, the contents of a Node
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
T* Node<T>::getData(void) const {
    return(mData);
}


/********************************************************************************************************
* Function: getNext()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns a pointer to a Node that is the next Node in a List container.
* Input parameters: none
* Returns: Node<T>* mpNext, the next Node in a List
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
Node<T>* Node<T>::getNext(void) const {
    return(mpNext);
}

/********************************************************************************************************
* Function: setData()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mData member of a Node to the input parameter's value
* Input parameters: T* newData, a pointer to generic type T which will be assigned to mData
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
void Node<T>::setData(T* newData) {
    mData = newData;
}

/********************************************************************************************************
* Function: setNext()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the mpNext member of a Node to the input parameter's value
* Input parameters: Node<T>* newNextPtr, a pointer to a Node whose address will be the new value of mpNext
* Returns: void
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
void Node<T>::setNext(Node<T>* newNextPtr) {
    mpNext = newNextPtr;
}

/********************************************************************************************************
* Function: printNode()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Calls printData() on the generic data type member of the Node.
* Input parameters: none
* Returns: void
* Preconditions: The concrete data type that is instantiated in the Node must have a member printData().
* Postconditions: none
********************************************************************************************************/
template <class T>
void Node<T>::printNode(void) {
    this->getData()->printData();
}

/********************************************************************************************************
* Function: printNodeToFile()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Calls printDataToFile() on the generic data type member of the Node.
* Input parameters: ofstream& outputFile, a stream to the output file being written to.
* Returns: T* mData, the contents of a Node
* Preconditions: The concrete data type that is instantiated in the Node must have a member printDataToFile().
* Postconditions: none
********************************************************************************************************/
template <class T>
void Node<T>::printNodeToFile(ofstream& outputFile) {
    this->getData()->printDataToFile(outputFile);
}

/********************************************************************************************************
* Function: duplicateExists()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Calls checkForDuplicates() on the generic data type member of the Node.
* Input parameters: T* targetData, a pointer to generic type T whose contents are being compared.
* Returns: bool duplicate, true if a duplicate exists, false otherwise
* Preconditions: The concrete data type that is instantiated in the Node must have a member duplicateExists().
* Postconditions: none
********************************************************************************************************/
template <class T>
bool Node<T>::duplicateExists(T* targetData) {
    bool duplicate = this->getData()->checkForDuplicates(targetData);
    return(duplicate);
}

#endif