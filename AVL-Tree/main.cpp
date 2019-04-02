#include <random>
#include <array>
#include <iomanip> 
#include <algorithm>

#include "AVLTree.h"

namespace {
	const int NUM_DATA = 8;
	const int MIN = 1;
	const int MAX = 10;
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
	std::cout << "AVL Tree with dataset: ";

	// Instantiate AVL instances
	AVLTree *tree1 = new AVLTree;
	AVLTree *tree2 = new AVLTree;

	// Define data to be inserted to AVL
	std::vector<int> data;
	while (data.size() != NUM_DATA)
	{
		data.emplace_back(RandomNum(MIN, MAX)); // Create new random number
		std::sort(begin(data), end(data)); // Sort before calling std::unique
		auto last = std::unique(begin(data), end(data));
		data.erase(last, end(data)); // Erase dupes
	}

	// Shuffle and display the sequence;
	std::shuffle(begin(data), end(data), std::mt19937(std::random_device()()));
	for (const auto &d : data)
		std::cout << d << " ";
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	// Inserting unsorted data
	for (const auto &d : data)
		tree1->Insert(d);

	// Inserting sorted data
	std::sort(begin(data), end(data));
	for (const auto &d : data)
		tree2->Insert(d);
	

	// Traversing tree in various orders then print all data
	std::cout << "Tree 1 data (Inorder): ";
	tree1->Inorder();

	std::cout << "Tree 1 data (Preorder): ";
	tree1->Preorder();

	std::cout << "Tree 1 data (Postorder): ";
	tree1->Postorder();

	// Search for random value
	int randomSearchValue = RandomNum(MIN, MAX);
	std::cout << "Search value " << randomSearchValue << " in Tree 1" << std::endl;
	if (tree1->Search(randomSearchValue))
	{
		std::cout << "FOUND" << std::endl;

		// Deletion
		std::cout << "Removing value " << randomSearchValue << std::endl;
		tree1->Remove(randomSearchValue);
	}
	else
	{
		std::cout << "NOT FOUND" << std::endl;
	}
	std::cout << std::endl;

	// Traversing other tree in various order then print all data
	std::cout << "Tree 2 (Inorder): ";
	tree2->Inorder();

	std::cout << "Tree 2 (Preorder): ";
	tree2->Preorder();

	std::cout << "Tree 2 (Postorder): ";
	tree2->Postorder();

	// Search for random value
	std::cout << "Search value " << randomSearchValue << " in Tree 2" << std::endl;
	if (tree2->Search(randomSearchValue))
	{
		std::cout << "FOUND" << std::endl;

		// Deletion
		std::cout << "Removing value " << randomSearchValue << std::endl;
		tree2->Remove(randomSearchValue);
	}
	else
	{
		std::cout << "NOT FOUND" << std::endl;
	}
	std::cout << std::endl;

	// Print all data again 
	std::cout << "Tree 1 data (Inorder): ";
	tree1->Inorder();

	// Print all data again 
	std::cout << "Tree 2 data (Inorder): ";
	tree2->Inorder();

	// Average no. comparisons
	std::cout << "--------------------------------------------------------------";
	std::cout << "\nAverage number of comparisons in Tree 1 (Unsorted dataset): " << std::endl;
	std::cout << std::setprecision(2) << std::fixed << tree1->AverageComparisons(NUM_DATA) << std::endl;

	std::cout << "Average number of comparisons in Tree 2 (Sorted dataset): " << std::endl;
	std::cout << std::setprecision(2) << std::fixed << tree2->AverageComparisons(NUM_DATA) << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;

	return 0;
}