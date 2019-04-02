// My includes
#include "RNG.h"

// Data structures
#include "BTree.h"

// Others
#include <iterator>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <vector> 

namespace {
	const int N = 1000000;
	const int MIN = 1;
	const int MAX = std::numeric_limits<int>::max();
	int K = 50000;
}

struct Measure
{
	template <typename F>
	static void Execution(F const &func)
	{
		const auto t1 = std::chrono::steady_clock::now();
		func();
		const auto t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = t2 - t1;
		std::cout << "That took " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds." << std::endl;
	}
};

std::vector<int> PopulateData(int numData, int minVal, int maxVal)
{
	// Populate some data
	std::vector<int> v;
	RNG rng(numData, minVal, maxVal);
	while (rng.HasNext())
	{
		v.push_back(rng.NextInt());
	}

	// Shuffle for further randomization
	std::shuffle(begin(v), end(v), std::mt19937(std::random_device()()));
	return v;
}

void Test()
{
	//--------------------------------------------------------------------------
	int order = 0;
	std::cout << "Define BTree order: ";
	std::cin >> order;

	// BTree instance
	auto tree = std::make_unique<BTree<int>>(order);

	int n = 0, min = 0, max = 0;
	std::cout << "Input [number of elements, min value, max value.]: ";
	std::cin >> n >> min >> max;
	std::vector<int> data = PopulateData(n, min, max);

	for (const auto &d : data)
		tree->Insert(d);
	//--------------------------------------------------------------------------

	std::cout << "The resulting height of the tree = " << tree->Height() << std::endl;
	tree->LevelOrder();
}

int main()
{
	Measure::Execution(Test);
}