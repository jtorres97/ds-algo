#pragma once

#pragma warning(disable:4996)

#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>

#include "BTreeNode.h"

template <typename T>
class BTree
{
public:
	BTree();
	explicit BTree(int k);

	void Insert(T data);
	bool Search(T data);
	int Height();
	void Inorder();
	void PostOrder();
	void PreOrder();
	void LevelOrder();
protected:
	void Insert(T data, BTreeNode<T> *&node, BTreeNode<T> *&parent);
	bool Search(T data, BTreeNode<T> *&node);
	void Split(T data, BTreeNode<T> *&node, BTreeNode<T> *&parent);
	int Height(BTreeNode<T> *&node);
	std::string Inorder(BTreeNode<T> *&node);
	std::string PostOrder(BTreeNode<T> *&node);
	std::string PreOrder(BTreeNode<T> *&node);
	std::string PrintOrder(BTreeNode<T>*& node);
	std::string PrintLevel(BTreeNode<T>*& node, int level);
private:
	int m_minElements;
	int m_order;
	BTreeNode<T> *m_root;
	std::stringstream m_buffer;
};

template <typename T>
BTree<T>::BTree()
{
	m_order = 5;
	m_root = new BTreeNode<T>(m_order);
	m_root->m_numChildren = 0;
	m_minElements = (m_order - 1) / 2;

	std::cout << "BTree of order " << m_order << std::endl;
}

template <typename T>
BTree<T>::BTree(const int k)
{
	m_order = k;
	m_root = new BTreeNode<T>(m_order);
	m_root->m_numChildren = 0;
	m_minElements = (m_order - 1) / 2;

	std::cout << "BTree of order " << m_order << std::endl;
}

template <typename T>
void BTree<T>::Insert(T data)
{
	Insert(data, m_root, m_root);
}

template <typename T>
bool BTree<T>::Search(T data)
{
	if (!Search(data, m_root))
	{
		std::cout << "{} is not in the tree." << std::endl;
		return false;
	}
	return true;
}

template <typename T>
int BTree<T>::Height()
{
	return Height(m_root);
}

template <typename T>
void BTree<T>::Inorder()
{
	std::cout << "InOrder traversal: " + Inorder(m_root) << std::endl;

	// Clear the string m_buffer after traversal is done
	m_buffer.str(std::string());
}

template <typename T>
void BTree<T>::PostOrder()
{
	std::cout << "PostOrder traversal: " + PostOrder(m_root) << std::endl;

	// Clear the string m_buffer after traversal is done
	m_buffer.str(std::string());
}

template <typename T>
void BTree<T>::PreOrder()
{
	std::cout << "PreOrder traversal: " + PreOrder(m_root) << std::endl;

	// Clear the string m_buffer after traversal is done
	m_buffer.str(std::string());
}

template <typename T>
void BTree<T>::LevelOrder()
{
	std::cout << PrintOrder(m_root) << std::endl;

	//std::cout << << m_buffer.str() << std::endl;

	// Clear the string m_buffer after traversal is done
	m_buffer.str(std::string());
}

template <typename T>
void BTree<T>::Insert(T data, BTreeNode<T>*& node, BTreeNode<T>*& parent)
{
	if (m_root == nullptr)
		m_root = new BTreeNode<T>(m_order);

	// Node is a leaf
	if (node->IsLeaf())
	{
		// Node is full, perform a split
		if (node->n_numElements == m_order - 1)
		{
			// Index the new value to be inserted
			int i = node->n_numElements - 1;
			while (i >= 0 && node->m_data[i] > data)
			{
				node->m_data[i + 1] = node->m_data[i];
				i--;
			}
			node->m_data[i + 1] = data;
			node->n_numElements += 1;

			Split(data, node, m_root);
		}
		// Node is not full, insert normally
		else
		{
			// Index the new value to be inserted
			int i = node->n_numElements - 1;
			while (i >= 0 && node->m_data[i] > data)
			{
				node->m_data[i + 1] = node->m_data[i];
				i--;
			}
			node->m_data[i + 1] = data;
			node->n_numElements += 1;
		}
	}
	// Node is not a leaf
	else
	{
		int i = node->n_numElements - 1;
		while (i >= 0 && node->m_data[i] > data)
		{
			i--;
		}
		Insert(data, node->m_children[i + 1], node);
	}
}

template <typename T>
bool BTree<T>::Search(T data, BTreeNode<T>*& node)
{
	if (node == nullptr)
	{
		return false;
	}
	else
	{
		int i = node->n_numElements - 1;
		while (i >= 0 && node->m_data[i] >= data)
		{
			if (node->m_data[i] == data)
			{
				m_buffer << data << " was found in node " << *(node);
				std::cout << m_buffer.str() << std::endl;
				m_buffer.str(std::string());

				return true;
			}
			i--;
		}
		Search(data, node->m_children[i + 1]);
	}
}

template <typename T>
void BTree<T>::Split(T data, BTreeNode<T>*& node, BTreeNode<T>*& parent)
{
	int i = parent->m_numChildren - 1;
	while (i >= 0 && parent->m_children[i] != node)
	{
		i--;
	}

	// Node is not a child of parent
	if (i == - 1 && node != m_root)
	{
		int j = parent->n_numElements - 1;
		while (j >= 0 && parent->m_data[j] > data)
			j--;

		Split(data, node, parent->m_children[j + 1]);
	}
	// Node is a child of parent
	else
	{
		auto *newNode = new BTreeNode<T>(m_order);
		int midIndex = std::ceil(static_cast<double>(node->n_numElements) / 2) - 1;
		int midValue = node->m_data[midIndex];

		int j = 0;
		int i;

		for (i = midIndex + 1; i < node->n_numElements; i++)
		{
			newNode->m_data[j] = node->m_data[i];
			j++;
		}
		newNode->n_numElements += j;
		node->n_numElements -= j;
		node->n_numElements -= 1;

		j = 0;
		for (i = midIndex + 1; i < node->m_numChildren; i++)
		{
			newNode->m_children[j] = node->m_children[i];
			j++;
		}
		node->m_numChildren -= j;
		newNode->m_numChildren += j;

		if (node != m_root)
		{
			int parentIndex = parent->n_numElements - 1;

			// Insert mid value into parent node
			while (parentIndex >= 0 && parent->m_data[parentIndex] > midValue)
			{
				// Moving m_data and children m_children
				parent->m_data[parentIndex + 1] = parent->m_data[parentIndex];
				parent->m_children[parentIndex + 2] = parent->m_children[parentIndex + 1];
				parentIndex--;
			}

			// Insert m_data
			parent->m_data[parentIndex + 1] = midValue;
			parent->n_numElements += 1;

			// Insert new child node
			parent->m_children[parentIndex + 2] = newNode;
			parent->m_numChildren += 1;

			// If the parent node is full
			if (parent->n_numElements == m_order)
				Split(midValue, parent, m_root);
		}
		// Node does equal m_root, make a new m_root node
		else
		{
			auto *newRoot = new BTreeNode<T>(m_order);
			newRoot->m_data[0] = midValue;
			newRoot->n_numElements = 1;

			newRoot->m_children[0] = node;
			newRoot->m_children[1] = newNode;
			newRoot->m_numChildren = 2;

			m_root = newRoot;
			m_root->n_numElements = newRoot->n_numElements;
			m_root->m_numChildren = newRoot->m_numChildren;
		}
	}
}

template <typename T>
int BTree<T>::Height(BTreeNode<T>*& node)
{
	if (node == nullptr)
		return -1;
	
	const int height = this->Height(node->m_children[0]);
	return height + 1;
}

template <typename T>
std::string BTree<T>::Inorder(BTreeNode<T>*& node)
{
	if (node == nullptr)
		return " ";

	Inorder(node->m_children[0]);
	for (auto i = 0; i < node->n_numElements; i++)
	{
		m_buffer << node->m_data[i] << ", ";
		Inorder(node->m_children[i + 1]);
	}

	auto s = m_buffer.str();
	s = s.substr(0, s.size() - 2); // Removes the last comma + space
	return s;
}

template <typename T>
std::string BTree<T>::PostOrder(BTreeNode<T>*& node)
{
	if (node == nullptr)
		return " ";

	PostOrder(node->m_children[0]);
	for (auto i = 0; i < node->n_numElements; i++)
	{
		PostOrder(node->m_children[i + 1]);
		m_buffer << node->m_data[i] << ", ";
	}

	auto s = m_buffer.str();
	s = s.substr(0, s.size() - 2); // Removes the last comma + space
	return s;
}

template <typename T>
std::string BTree<T>::PreOrder(BTreeNode<T>*& node)
{
	if (node == nullptr)
		return " ";

	auto i = 0;
	m_buffer << node->m_data[i] << ", ";
	PreOrder(node->m_children[0]);
	for (i = node->n_numElements; i > 0; --i)
	{
		PreOrder(node->m_children[i]);
	}

	auto s = m_buffer.str();
	s = s.substr(0, s.size() - 2); // Removes the last comma + space
	return s;
}

template <typename T>
std::string BTree<T>::PrintOrder(BTreeNode<T>*& node)
{
	const int h = Height(node);
	for (auto i = 0; i <= h; i++)
	{
		PrintLevel(node, i);
		m_buffer << std::endl;
	}
	return m_buffer.str();
}

template <typename T>
std::string BTree<T>::PrintLevel(BTreeNode<T>*& node, const int level)
{
	if (node == nullptr)
		return std::string();
	if (level == 0)
		m_buffer << " " << *(node);
	else if (level > 0)
	{
		for (auto i = 0; i < node->m_numChildren; i++)
			PrintLevel(node->m_children[i], level - 1);
	}
	return m_buffer.str();
}
