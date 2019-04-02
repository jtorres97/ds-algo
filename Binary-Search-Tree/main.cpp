#include <random>
#include <array>
#include <iomanip> 

#include "BinarySearchTree.h"
using namespace std;

namespace {
	const int NUM_DATA = 25;
	const int MIN = 1;
	const int MAX = 100;
}

int RandomNum(int a, int b)
{
	// Init RNG
	std::array<int, std::mt19937::state_size> seed_data;
	std::random_device r;
	std::generate_n(seed_data.data(), seed_data.size(), std::ref(r));
	std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
	std::mt19937 generator(seq);

	// Get random number
	std::uniform_int_distribution<int> dist(a, b);
	return dist(generator);
}

int main()
{
	cout << "Binary Search Tree" << endl;

	// Instantiate BST instances
	BinarySearchTree *tree1 = new BinarySearchTree;
	BinarySearchTree *tree2 = new BinarySearchTree;

	// Define data to be inserted to BST
	int unsortedData[NUM_DATA];

	for (int i = 0; i < NUM_DATA; i++)
		unsortedData[i] = RandomNum(MIN, MAX);

	// Print initial dataset
	cout << "Dataset: ";
	for (const auto &d : unsortedData)
		cout << d << " ";
	cout << endl;

	// Inserting unsorted data
	for (const auto &d : unsortedData)
		tree1->Insert(d);

	// Inserting sorted data
	sort(unsortedData, unsortedData + NUM_DATA);
	for (const auto &d : unsortedData)
	{
		tree2->Insert(d);
	}

	// Traversing tree in various orders then print all data
	cout << "Tree 1 data (Inorder): ";
	tree1->Inorder();

	cout << "Tree 1 data (Preorder): ";
	tree1->Preorder();

	cout << "Tree 1 data (Postorder): ";
	tree1->Postorder();

	// Search for random value
	int randomSearchValue = RandomNum(MIN, MAX);
	cout << "Search value " << randomSearchValue << " in Tree 1" << endl;
	if (tree1->Search(randomSearchValue))
	{
		cout << "FOUND" << endl;;

		// Deletion
		cout << "Removing value " << randomSearchValue << endl;
		tree1->Remove(randomSearchValue);
	}
	else
	{
		cout << "NOT FOUND" << endl;
	}
	cout << endl;

	// Traversing other tree in various order then print all data
	cout << "Tree 2 (Inorder): ";
	tree2->Inorder();

	cout << "Tree 2 (Preorder): ";
	tree2->Preorder();

	cout << "Tree 2 (Postorder): ";
	tree2->Postorder();

	// Search for random value
	cout << "Search value " << randomSearchValue << " in Tree 2" << endl;
	if (tree2->Search(randomSearchValue))
	{
		cout << "FOUND" << endl;

		// Deletion
		cout << "Removing value " << randomSearchValue << endl;
		tree2->Remove(randomSearchValue);
	}
	else
	{
		cout << "NOT FOUND" << endl;
	}
	cout << endl;

	// Print all data again 
	cout << "Tree 1 data (Inorder): ";
	tree1->Inorder();

	// Print all data again 
	cout << "Tree 2 data (Inorder): ";
	tree2->Inorder();

	// Average no. comparisons
	cout << "Average number of comparisons in Tree 1 (Unsorted dataset): " << endl;
	cout << setprecision(2) << fixed << tree1->AverageComparisons(NUM_DATA) << endl;

	cout << "Average number of comparisons in Tree 2 (Sorted dataset): " << endl;
	cout << setprecision(2) << fixed << tree2->AverageComparisons(NUM_DATA) << endl;

	return 0;
}
