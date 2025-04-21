Project Summary

1. Inventory Query system implemented using two hash tables.
    a. One hash table uses UniqueID as a key, allowing lookup by UniqueID in amortized O(1) time.
    b. One hash table uses Category as a key, allowing lookup of the list of items in that category in O(1) time, and displaying every item in that category in O(n) time where n is the number of items in that category. This second hash table can contain the same unique item in multiple positions, since one unique item can have multiple categories.
    c. Hashing done using std::hash.
    d. HashTable supports rehashing as explained in Part 5 below.
2. Empty data fields from the .csv are populated with "NA" including category, thus searching for category "NA" will list all items for which the "Category" field is blank.
3. No additional cleanup was performed as no further problems were encountered in testing.
4. Skeleton code was adapted into wrapper class ProductInventoryQuery.
5. HashTable implemented using an array on the heap, initially sized to 19. When load factor becomes greater than 1, a larger array is created on the heap, sized to the first prime number encountered after 2n+1 where n is the current size. Then all elements in the HashTable are rehashed and inserted to the new HashTable, and the old array is deleted.

PA5 Additions: query by category will now appear in sorted order based on Selling Price. User may select sort methods using argument "merge" or none (defaults to insertion sort), and may select descending order with argument "desc" (no argument defaults to ascending order). Various additions and changes to support this functionality are detailed in PA5 Changes documentation in comments in main.cpp.

Comparative performance of insertion sort vs. merge sort depends largely on the initial order of the list to be sorted.
	- Merge sort - best and worst case performance is O(nlogn), as the algorithm executes identically regardless of whether the list is in sorted order initially or not. Without respect to ordering, the list of n elements being sorted is broken into smaller and smaller pieces into a total of n lists of 1 element and then merged back into the original list in sorted order, continuing until the original list is sorted. This splitting and merging process occurs regardless of the order of the original list.
	- Insertion sort - best case is if the list of n elements is already sorted, in which case performance of insertion sort is O(n). For nearly sorted order lists, insertion sort is very efficient and performs near O(n), degrading in performance progressively as more and more elements are out of order. In the worst case, elements are in reverse sorted order and the time complexity of insertion sort degrades to O(n^2) as each element must be swapped up to n times.

For real world applications, insertion sort may perform better on small data sets. For medium to large data sets such as "Hobbies" category sorting with nearly 1,000 entries, merge sort is significantly faster for the order that the data is scanned from the file (~1600 microseconds on average for merge sorting Hobbies vs. ~4000 microseconds on average for insertion sort). The advantage of merge sort will widen with larger data sets than this.