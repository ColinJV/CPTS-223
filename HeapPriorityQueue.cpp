#include "HeapPriorityQueue.h"
#include <iostream>

// Note: most functions use one or both of the compiler generated copy constructor or copy assignment
//      operators for PrinterJob objects. This works and is sufficient for this implementation.

// Constructor implemented
HeapPriorityQueue::HeapPriorityQueue() {
    // Initialize size to 0
    size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        // Initialize the heap priority queue's elements
        heap[i].printString = "";
        heap[i].priority = 0;
    }
}
// Destructor implemented
HeapPriorityQueue::~HeapPriorityQueue() {
    // Cleanup if necessary
    // Not necessary, nothing dynamically allocated
}

// Copy constructor implemented
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    // Copy heap elements and size
    this->size = other.size;
    for (int i = 0; i < size; ++i) {
        this->heap[i] = other.heap[i];
    }
}

// Copy assignment implemented
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {
    // Assign heap elements and size properly
    if (this != &other) {
        this->size = other.size;
        for (int i = 0; i < size; ++i) {
            this->heap[i] = other.heap[i];
        }
    }
    return *this;
}

// Implemented enqueue() function
// Returns without insertion if the queue is full
// Otherwise inserts the current job to the end of the queue and percolates up
void HeapPriorityQueue::enqueue(const string& str, int priority) {
    // Insert new PrinterJob(str, priority) while maintaining heap order using percolateUp
    if (size == MAX_SIZE) {
        return;
    }
    PrinterJob newJob(str, priority);
    heap[size] = newJob;
    this->percolateUp(size++);
}

// Implemented printJobs() function
// Prints the root node and then clears the values from it
// Finds the last leaf node, stores in a temp value then deletes the data from the leaf
// Inserts the last leaf's data in the root and percolates down
void HeapPriorityQueue::printJobs() {
    // Print and remove PrinterJobs from the heap in priority order and using percolateDown as necessary
    if (size == 0) {
        cout << "No jobs in queue." << endl;
        return;
    }
    cout << "Printing jobs in priority order: \n";
    while (size > 0) {
        // Step 1: print highest priority, i.e. minimum item in queue
        cout << heap[0].printString << "\n";

        // Step 2: delete root node
        heap[0] = { "", 0 };

        // Step 3: delete last leaf but keep the value and modify size
        PrinterJob temp(heap[--size]);
        heap[size] = { "", 0 };

        // Step 4: insert value to the root
        heap[0] = temp;

        // Step 5: percolate down
        this->percolateDown(0);
    }
}

// Implemented percolateUp() function
// Compares a PrinterJob to its parent and swaps them if the parent is lower priority than the child
void HeapPriorityQueue::percolateUp(int index) {
    // Maintain heap order when inserting a new PrinterJob
    bool inserted = false;
    while (!inserted) {
        int parent = (index - 1) / 2;
        if (heap[index].priority != 0 && heap[index] < heap[parent] && index != parent) {
            PrinterJob temp(heap[index].printString, heap[index].priority);
            heap[index] = heap[parent];
            heap[parent] = temp;
        }
        else {
            inserted = true;
        }
    }
}

// Implemented percolateDown() function
// Compares the children of a PrinterJob at an index. If a child node has a higher priority
//      than the parent, swaps positions of the index and the lowest child until the inserted
//      PrinterJob is in the correct position in the priority queue.
void HeapPriorityQueue::percolateDown(int index) {
    // Maintain heap order when removing a PrinterJob
    bool inserted = false;
    while (!inserted) {
        // Compare children
        int left = index * 2 + 1, right = index * 2 + 2;

        // Case: both children have values
        if (heap[left].priority != 0 && heap[right].priority != 0) {
            // Case: both children are greater than (i.e. lower priority) parent
            if (heap[index] < heap[left] && heap[index] < heap[right]) {
                inserted = true;
            }

            // If both children are not greater than the parent, then clearly one must be less than the parent, so
            //      we should percolate down to the lowest child

            // Case: left is smaller than right
            else if (heap[left] < heap[right]) {
                PrinterJob temp(heap[left]);
                heap[left] = heap[index];
                heap[index] = temp;
                index = left;
            }
            // Case: right is smaller than left
            else {
                PrinterJob temp(heap[right]);
                heap[right] = heap[index];
                heap[index] = temp;
                index = right;
            }
        }

        // Case: only the left child has a value
        else if (heap[left].priority != 0) {
            // Case: left child is lower than parent
            if (heap[left] < heap[index]) {
                PrinterJob temp(heap[left]);
                heap[left] = heap[index];
                heap[index] = temp;
                index = left;
            }
            // Case: left child is greater than parent
            else {
                inserted = true;
            }
        }

        // Since each tree level fills from left to right, it is not possible that only the right child has a value

        // Case: neither child has a value
        else {
            inserted = true;
        }
    }
}