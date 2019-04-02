#pragma once

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <numeric>

namespace Chaining
{
	class Hashtable
	{
	public:
		explicit Hashtable(int size);

		void Insert(const std::string &key);
		void Search(const std::string &key) const;
		void Remove(const std::string &key);
		std::string PrintHashTable() const;
		std::string PrintCollisions() const;
		int KeyCount() const;
		int CollisionCount() const;
		void AverageComparisonCount() const;
	protected:
		int HashFunction(const std::string &x) const;
	private:
		std::list<std::string> *m_table;
		std::stringstream m_buffer;
		int m_size;
		int m_keyCount;
		int *m_collisionCount;
	};
}
