# Data Strucures and Algorithms
Implementations of various algorithms for a university data structures course.

## Building from source
Execute these commands in any of the project folders in this repo.
### Visual Studio
```
mkdir build & cd build
cmake ../ & devenv Project.sln /Build 
cd .. & cd bin\Debug
Project.exe
```

## BST
Implementation of a BST class that include the following operations:
- Insertion, Search, Deletion
- Traversals: Inorder, Preorder, Postorder

## AVL
Implementation of a class AVLTree that should consider the following operations:
- Insertion, Search, Deletion, RotateLeft, RotateRight

## B-Tree
To implement a BTree class in C++ that allows:

- the definition of the order (K) of the node (this can be implemented as a method or as a parameter directly in the constructor of the class
- A method for searching a given key "KEY" in the tree, that returns the pointer to the node that contains the KEY plus the integer index of the given key in that page or null if KEY is not present in the tree
- A method for insertions of integer numbers in the tree. This should take the value of order K into consideration, meaning that each node must store m elements where: K/2 <= m <= K 
- A method for deletions of integers numbers from the tree. Remember to consider rotations and joins operations If necessary
- All three traversals: inorder, preorder, postorder
- A method to determine the height of the tree

-------------------------

Should also be implemented an external program that instantiates an object of this class using K = 50000 and inserts 1 million (1.000.000) DISTINCT random numbers and determines the height of the resulting tree.

## Hashtable
To implement a HashTable class in C++ that allows:
- the definition of the size (M) of the static array for the hash table
- the definition of a hash function HASH(X) suitable for storing string keys (not integers). The student is expected to propose his/her own hash table.
- a method for inserting keys in the hash table. The solution MUST consider chaining (e.g. linked lists, trees, etc.) as the collision response criteria.
- a method for searching keys in the hash table. The solution has also to determine how many comparisons were necessary to find a given key or to decide that the given is absent.
- a method for deleting keys from the hash table.
- The resulting program should insert 10,000 distinct keys in the table and then present a report of the total number of collisions that occurred in the process.
- the resulting program should search 1,000 distinct keys and determine the average number of comparisons while finding these keys
- the resulting program should delete 1,000 distinct keys
- insertions, searches and deletions should occur at random times (meaning not to perform them as sequences).

## Priority Queue
In this assignment, you are expected to implement a priority queue (PQ) as a heap in a static array of size 1000 to manage a line of clients in a bank.

A record of a client is defined by the following structure: the name of a client, its date of birth, a numeric value indicating the client's account balance. Older clients should have higher priority over young ones.

The program to be implemented should then randomly generate 1000 "operations", where an operation can be a "push" of a client's record (randomly generated) or a "pop" removing the client from the front of the queue and printing its record in a single line on the screen (one line per client).
