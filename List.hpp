#ifndef LIST_H
#define LIST_H

#include "Node.hpp"
#include "Data.hpp"
#include <fstream>

using std::ofstream;

template <class T>
class List {
public:
    // Constructor
    List(const T& newData);
    List();

    // Destructor
    ~List();

    // Accessor
    Node<T>* getHeadPtr(void) const;

    // Mutator
    void setHead(Node<T>* newHeadPtr);

    // Other methods
    bool insertAtFront(T* newData);
    bool duplicateExists(T* target);
    bool removeNode(T* targetData);
    void printList();
    void printListToFile(ofstream& outputFile);
    bool deleteFront();

private:
    Node<T>* mpHead;
};

/********************************************************************************************************
* Function: List constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a List container for template data type T and creates a new Node to populate with
* data of type T.
* Input parameters: template type T newData
* Returns: List object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
List<T>::List(const T& newData) {
    mpHead = new Node<T>(newData);
}


/********************************************************************************************************
* Function: List constructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a List container for template data type T with no data initially, setting the head
* pointer to the null pointer
* Input parameters: none
* Returns: List object
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
List<T>::List() {
    mpHead = nullptr;
}

/********************************************************************************************************
* Function: List destructor
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Deletes a List container by deleting elements one at a time starting with the first element.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
List<T>::~List() {
    while (mpHead != nullptr) {
        Node<T>* pNext = mpHead->getNext();
        delete mpHead;
        this->setHead(pNext);
    }
}


/********************************************************************************************************
* Function: getHeadPtr()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Returns the head pointer of a List container, mpHead
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
Node<T>* List<T>::getHeadPtr(void) const {
    return(mpHead);
}


/********************************************************************************************************
* Function: setHead()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Modifies the head pointer of a List container, mpHead, to the input memory address.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
void List<T>::setHead(Node<T>* newHeadPtr) {
    mpHead = newHeadPtr;
}

/********************************************************************************************************
* Function: insertAtFront()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Creates a Node with the input data (generic type T) and inserts that Node at the front of
* this List container.
* Input parameters: T* newData, a pointer to generic type T containing some data to add to the list
* Returns: bool indicating whether the newly created node is the first element in the List.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
bool List<T>::insertAtFront(T* newData) {
    Node<T>* pNew = new Node<T>(newData);
    pNew->setNext(mpHead);
    this->setHead(pNew);
    return(mpHead == pNew);
}

/********************************************************************************************************
* Function: duplicateExists()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Searches a List container for a Node containing data matching the input parameter. Returns
* true if matching data is found, false otherwise.
* Input parameters: T* target, a pointer to generic data type T whose value is being searched for in the List.
* Returns: bool duplicate, true if the target value is found, false otherwise.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
bool List<T>::duplicateExists(T* target) {
    bool duplicate = false;
    Node<T>* pCurrent = this->getHeadPtr();

    while (!duplicate && pCurrent != nullptr) {
        duplicate = pCurrent->duplicateExists(target);
        if (!duplicate) {
            pCurrent = pCurrent->getNext();
        }
    }

    return(duplicate);
}

/********************************************************************************************************
* Function: removeNode()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Removes a Node containing the data matching the input parameter from a List container.
* Input parameters: T* targetData, a pointer to generic type T with data being sought in the List.
* Returns: bool removed, true if a Node was removed, false otherwise.
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
bool List<T>::removeNode(T* targetData) {
    bool removed = false;
    Node<T>* pCurrent = this->getHeadPtr(), * pLast = nullptr;

    while (pCurrent != nullptr && !removed) {
        if (pCurrent->duplicateExists(targetData)) {
            pLast->setNext(pCurrent->getNext());
            delete pCurrent;
            removed = true;
        }
        else {
            pLast = pCurrent;
            pCurrent = pCurrent->getNext();
        }
    }

    return(removed);
}


/********************************************************************************************************
* Function: printList()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Calls printNode() on each Node in the list until the end of the list has been reached.
* Outputs std::endl to std::cout for formatting purposes after all Nodes have been printed.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
void List<T>::printList() {
    Node<T>* pCurrent = this->getHeadPtr();

    while (pCurrent != nullptr) {
        pCurrent->printNode();
        pCurrent = pCurrent->getNext();
    }

    cout << endl;
}


/********************************************************************************************************
* Function: printListToFile()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Outputs the contents of the List to a file, the specific file being established elsewhere
* and passed to this function as the input parameter ofstream& outputFile.
* Input parameters: ofstream& outputFile, a reference to a std::ofstream that connects to a data file output.
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
void List<T>::printListToFile(ofstream& outputFile) {
    Node<T>* pCurrent = this->getHeadPtr();

    while (pCurrent != nullptr) {
        pCurrent->printNodeToFile(outputFile);
        pCurrent = pCurrent->getNext();
    }
}


/********************************************************************************************************
* Function: deleteFront()
* Date Created: 01/25/2025
* Date Last Modified: 01/25/2025
* Programmer: Colin Van Dyke
* Description: Deletes the first element in the List.
* Input parameters: none
* Returns: none
* Preconditions: none
* Postconditions: none
********************************************************************************************************/
template <class T>
bool List<T>::deleteFront(void) {
    Node<T>* pTemp = this->getHeadPtr()->getNext();
    delete mpHead;
    mpHead = pTemp;
    return(mpHead == pTemp);
}

#endif