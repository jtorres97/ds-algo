#pragma once

#include <vector>
#include <iostream>

#include "Client.h"

namespace PriorityQueue
{
	class Heap
	{
	public:
		Heap();

		void Push(const Client &client);
		Client Peek() const;
		Client Pop();
		void HeapSort();
		bool IsFull() const;
		bool IsEmpty() const;
	protected:
		void FixUp(int index);
		void FixDown(int index);
	private:
		std::vector<Client> m_heap;
		int m_size = 0;
		constexpr static int CAPACITY = 1000;
	};
}