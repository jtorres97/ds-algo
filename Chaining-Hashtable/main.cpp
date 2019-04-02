// My includes
#include "Test.h"
#include "TestManager.h"

// Data structures
#include "HashTable.h"

// Other includes
#include <fstream>

struct Measure
{
	template <typename F>
	static void Execution(F const &func)
	{
		const auto t1 = std::chrono::steady_clock::now();
		func();
		const auto t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = t2 - t1;
		std::cout << "That took " << elapsed.count() << " seconds." << std::endl;
	}
};

void Test()
{
	// Hashtable instance
	auto hashTable = std::make_unique<Chaining::Hashtable>(11);

	// Store our user names in a container for queries
	std::vector<std::string> usernames;

	// Write user names to container
	const std::string fileName = "usernames.txt";
	std::ifstream myFile;
	myFile.open(fileName, std::ios::in);
	
	if (!myFile.is_open())
	{
		std::exit(0);
	}
	
	std::string firstLine;
	while (myFile.good())
	{
		std::getline(myFile, firstLine);
		std::stringstream ss(firstLine);
		std::string distinctInt;
	
		// Read up to whitespace
		while (std::getline(ss, distinctInt, ' '))
		{
			usernames.push_back(firstLine);
		}
	}
	myFile.close(); // End writing

	//---------------------------------------------------------------------------------------------
	// BEGIN NON-DETERMINISTIC TESTS
	//---------------------------------------------------------------------------------------------

	// Counter to keep track of how many insertions have occured
	size_t numInsertions = 0;

	// Test manager instance with various tests
	TestManager manager;
	while (manager.Run())
	{
		// Insertions
		if (manager.RunningTest(INSERTION))
		{
			hashTable->Insert(usernames[COSC::Rand(0, usernames.size() - 1)]);
			numInsertions++;
		}
		
		//Removals
		if (manager.RunningTest(REMOVE))
		{
			hashTable->Remove(usernames[COSC::Rand(0, usernames.size() - 1)]);
		}
		
		// Search queries
		if (manager.RunningTest(SEARCH))
		{
			hashTable->Search(usernames[COSC::Rand(0, usernames.size() - 1)]);
		}

		// Stop when insertions reach size of usernames container
		if (numInsertions == usernames.size())
		{
			std::cout << numInsertions << " insertions completed, ending test." << std::endl;
			std::cout << hashTable->PrintHashTable() << std::endl;
			std::cout << hashTable->CollisionCount() << " collisions occured." << std::endl;
			std::cout << hashTable->PrintCollisions() << std::endl;	
			hashTable->AverageComparisonCount();		
			break;
		}
	}	
	//---------------------------------------------------------------------------------------------
	// END NON-DETERMINISTIC TESTS
	//---------------------------------------------------------------------------------------------
}

int main()
{
	Measure::Execution(Test);
	std::cin.get();
}
