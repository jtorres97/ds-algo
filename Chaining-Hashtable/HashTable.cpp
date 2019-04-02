#include "HashTable.h"

namespace Chaining
{
	Hashtable::Hashtable(const int size)
		: m_size(size)
		, m_keyCount(0)
	{
		// Define the size of the hash table
		this->m_table = new std::list<std::string>[m_size];

		// Allocate collision count array
		m_collisionCount = new int[m_size];
		for (auto i = 0; i < m_size; i++)
			m_collisionCount[i] = 0;

		std::cout << "Chaining Hashtable with size " << m_size << std::endl;
	}

	void Hashtable::Insert(const std::string &key) 
	{
		// Move to the index that corresponds to the calculated hash index 
		// and insert the new key at the end of the list
		const auto hashIndex = HashFunction(key);
		this->m_table[hashIndex].push_back(key);

		// Emulates the amount of keys in the index's chain and
		// increments per insertion into an index, counts the number of
		// keys that are in the chain per index
		this->m_collisionCount[hashIndex]++;

		std::cout << "Hashtable::Insert(): Inserted " << key << " to hashtable." << std::endl;

		// Increment key count
		++m_keyCount;
	}

	void Hashtable::Search(const std::string &key) const
	{
		auto comparisons = 0;
		const auto hashIndex = HashFunction(key);

		// Iterate through chaining node 
		for (auto &keyValue : m_table[hashIndex])
		{
			// Comparison counter for this specific search query
			++comparisons;

			if (key == keyValue)
			{
				std::cout << "Hashtable::Search(): Found key: " << keyValue << " <---> with No. of comparisons = " << comparisons << std::endl;
				return;
			}
		}
		 
		// Default case
		std::cout << "Hashtable::Search(): Key " << key << " was not found." << std::endl;
	}

	void Hashtable::Remove(const std::string &key) 
	{
		const auto hashIndex = HashFunction(key);

		// Traverse the chaining node (linked list)
		for (auto it = m_table[hashIndex].begin(); it != m_table[hashIndex].end(); ++it)
		{
			// if the key is found, then delete the list's element
			if (*it == key)
			{
				m_table[hashIndex].erase(it);
				std::cout << "Hashtable::Remove(): Removed " << key <<  " from hashtable." << std::endl;

				// Decrement key count
				--m_keyCount;

				return;
			}
		}
		std::cout << "Hashtable::Remove(): " << key << " doesn't exist in hashtable, can't remove key." << std::endl;
	}

	std::string Hashtable::PrintHashTable() const
	{
		std::stringstream ss;

		// Output a formatted hashtable to the string buffer
		ss << "[Printing Formatted Hashtable]";
		ss << "\n";
		for (auto i = 0; i < m_size; i++)
		{
			auto keyList = m_table[i];
			if (!keyList.empty())
			{
				ss << "\n" << "[" << i << "]";
			}
			else
			{
				ss << "\n" << "[" << i << "]" << " *";
			}

			for (auto &it : keyList)
			{
				ss << " --> " << it;
			}
		}
		ss << "\n";
		return ss.str();
	}

	std::string Hashtable::PrintCollisions() const
	{
		std::stringstream ss;

		// Print out number of collisions that occurred per index
		ss << "[Collisions in each index]: \n\n";
		for (auto i = 0; i < m_size; i++) 
		{
			ss << "[" << i << "]: " << m_collisionCount[i] << " collisions occured here." << "\n";
		}
		return ss.str();
	}

	int Hashtable::KeyCount() const
	{
		return m_keyCount;
	}

	int Hashtable::CollisionCount() const
	{
		auto collisions = 0;
		for (auto i = 0; i < m_size; i++)
			if (m_collisionCount[i] > 0)
				collisions += m_collisionCount[i];
		return collisions;
	}

	void Hashtable::AverageComparisonCount() const
	{
		std::stringstream ss;
		ss << "[Displaying number of probes to lookup]\n";
		double numLookupProbes = 0;
		for (auto i = 0; i < m_size; i++)
		{
			auto lookupProbesCounter = 0;
			auto keyList = m_table[i];
			if (!keyList.empty())
			{
				ss << "\n" << "[" << i << "]";
			}
			else
			{
				ss << "\n" << "[" << i << "]" << " *";
			}

			for (auto &it : keyList)
			{
				ss << " --> " << it;
				++lookupProbesCounter;
				ss << " " << lookupProbesCounter;
				numLookupProbes += lookupProbesCounter;
			}
		}
		ss << "\n\n";
		std::cout << ss.str() << std::endl;

		// number of probes to lookup divided by the number of keys in hashtable
		const auto averageComparisons = static_cast<double>(numLookupProbes / m_keyCount);
		std::cout << "Average comparisons = " << averageComparisons << std::endl;
	}

	int Hashtable::HashFunction(const std::string &x) const
	{
		// Sum of ASCII values of the string, then MOD it by the size of the table.
		return static_cast<int>(std::accumulate(x.begin(), x.end(), 0)) % m_size;
	}
}
