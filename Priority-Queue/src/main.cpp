// My includes
#include "Test.h"
#include "TestManager.h"

// Data structures
#include "Heap.h"

// Other includes
#include <fstream>

namespace
{
	const std::string RECORD_NAMES = "res/names.txt";
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
		std::cout << "That took " << elapsed.count() << "seconds." << std::endl;
	}
};

std::vector<Client> GetRecordData(const std::string &fileName)
{
	// Container to store Records
	std::vector<Client> v;

	// Write names to container
	std::ifstream myFile;
	myFile.open(fileName, std::ios::in);

	std::string firstLine;
	while (myFile.good())
	{
		std::getline(myFile, firstLine);
		std::stringstream ss(firstLine);
		std::string name;

		// Read up to whitespace
		while (std::getline(ss, name))
		{
			auto dateFormat = Utils::RandomInt(0, 3);

			// Generate a random birthdate 
			std::string dob;

			// Format date based on rng, examples below
			// case 0: 01/01/1997
			// case 1: 11/01/1997
			// case 2: 01/11/1997
			// case 3: 11/11/1997
			switch (dateFormat)
			{
			case 0:
				dob = "0" + std::to_string(Utils::RandomInt(1, 9)) + "/" + "0" + std::to_string(Utils::RandomInt(1, 9)) + "/" + std::to_string(Utils::RandomInt(1900, 2001));
				break;
			case 1:
				dob = std::to_string(Utils::RandomInt(10, 12)) + "/" + "0" + std::to_string(Utils::RandomInt(1, 9)) + "/" + std::to_string(Utils::RandomInt(1900, 2001));
				break;
			case 2:
				dob = "0" + std::to_string(Utils::RandomInt(1, 9)) + "/" + std::to_string(Utils::RandomInt(10, 12)) + "/" + std::to_string(Utils::RandomInt(1900, 2001));
				break;
			case 3:
				dob = std::to_string(Utils::RandomInt(10, 12)) + "/" + std::to_string(Utils::RandomInt(10, 12)) + "/" + std::to_string(Utils::RandomInt(1900, 2001));
				break;
			}

			// Generate a random balance 
			auto balance = Utils::RandomDouble(10.00, 1000000.00);

			// Push a random name, age, and balance for each record
			v.push_back(Client(name, dob, balance));
		}
	}
	myFile.close(); // End writing

	// Container with records
	return v;
}

void TestRun()
{
	// Priority queue instance
	auto priorityQueue = std::make_unique<PriorityQueue::Heap>();

	// Populate some data from a list of names
	std::vector<Client> records = GetRecordData(RECORD_NAMES);

	// Keep track of how many operations were done
	size_t numOperations = 0;

	// Test manager instance with various tests
	TestManager manager;
	while (manager.Run())
	{
		if (manager.RunningTest(PUSH))
		{
			std::stringstream ss; ss << records[numOperations];
			std::cout << "Push(): " << ss.str() << std::endl;

			// Perform the push
			priorityQueue->Push(records[numOperations]);
			++numOperations;
		}

		if (manager.RunningTest(POP) && !priorityQueue->IsEmpty())
		{
			// Perform the pop
			std::stringstream ss; ss << priorityQueue->Pop();
			std::cout << "Pop() : " << ss.str() << std::endl;
			++numOperations;
		}

		// Stop when operations reach 1000
		if (numOperations == records.size())
		{
			std::cout << numOperations << " operations performed." << std::endl;
			break;
		}
	}
}

void HeapSortTest()
{
	std::cout << "HeapSort() Test" << std::endl;

	// Priority queue instance
	auto priorityQueue = std::make_unique<PriorityQueue::Heap>();

	// Populate some data from a list of names
	std::vector<Client> records = GetRecordData(RECORD_NAMES);

	// Insert all the records into the priority queue
	for (const auto &record : records)
		priorityQueue->Push(record);

	// Display heap sort
	std::cout << "Begin HeapSort()" << std::endl;
	priorityQueue->HeapSort();
}

int main()
{
	Measure::Execution(TestRun);
	Measure::Execution(HeapSortTest);
}
