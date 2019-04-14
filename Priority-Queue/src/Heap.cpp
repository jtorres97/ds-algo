#include "Heap.h"

namespace PriorityQueue
{
	Heap::Heap()
	{
		// Resize the container so that it contains n elements (CAPACITY)
		m_heap.resize(CAPACITY);
	}

	void Heap::Push(const Client &client)
	{
		// Cannot insert more items than the value of CAPACITY
		if (IsFull())
			throw std::overflow_error("Heap is full!");

		// Insert client, increment size/count
		m_heap[m_size] = client;
		++m_size;

		// Insert item to the last position of the array: Heap properties may be violated
		// so we have to fix it if necessary
		FixUp(m_size - 1);
	}

	Client Heap::Peek() const
	{
		// Cannot peek if the heap is empty
		if (IsEmpty())
			throw std::length_error("Heap is empty.");

		// Root node is always the max for a MAX HEAP
		return m_heap[0];
	}

	Client Heap::Pop()
	{
		const auto max = Peek();

		std::swap(m_heap[0], m_heap[m_size - 1]);
		--m_size;

		FixDown(0);
		return max;
	}

	void Heap::HeapSort()
	{
		// Decrease the size of the heap in the Pop() method so we have to store it!
		const auto size = m_size;

		// Call the Pop() operation as many times as the number of items in the heap
		for (auto i = 0; i < size; i++)
		{
			const auto max = Pop();
			std::stringstream ss; ss << max;
			std::cout << ss.str() << std::endl;;
		}
	}

	void Heap::FixUp(const int index)
	{
		// The parent index of the given node in the heap
		// we store the heap in an array
		const auto parentIndex = (index - 1) / 2;

		// index > 0 means until we consider all the items "above" the one we inserted
		// we have to swap the node with the parent if the heap property is violated
		// it is a MAX HEAP: largest items are in the higher layers (max item == root node)
		if (index > 0 && m_heap[index] > m_heap[parentIndex])
		{
			std::swap(m_heap[index], m_heap[parentIndex]);
			FixUp(parentIndex);
		}
	}

	void Heap::FixDown(const int index)
	{
		// Every node have children: left and right children
		// in the array the node i has left child with index 2*i+1 and right child with index 2*i+2
		const auto indexLeft = 2 * index + 1;
		const auto indexRight = 2 * index + 2;

		// Max heap so the parent node is always greater than the children
		auto indexLargest = index;

		// If the left child is greater than the parent: largest is the left node
		if (indexLeft < m_size && m_heap[indexLeft] > m_heap[index])
			indexLargest = indexLeft;

		// If the right child is greater than the left child: largest is the right node
		if (indexRight < m_size && m_heap[indexRight] > m_heap[indexLargest])
			indexLargest = indexRight;

		// We do not want to swap items with themselves
		if (index != indexLargest)
		{
			std::swap(m_heap[index], m_heap[indexLargest]);
			FixDown(indexLargest);
		}
	}

	bool Heap::IsFull() const
	{
		return m_size == CAPACITY;
	}

	bool Heap::IsEmpty() const
	{
		return m_size == 0;
	}
}
