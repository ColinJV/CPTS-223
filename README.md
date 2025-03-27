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