#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
	: m_root(nullptr)
	, m_count(0)
{
}

void BinarySearchTree::Insert(int data)
{
	m_root = Insert(m_root, data);
}

void BinarySearchTree::Remove(int data)
{
	m_root = Remove(m_root, data);
}

bool BinarySearchTree::Search(int data)
{
	Node *node = Search(m_root, data);

	return node == nullptr ? false : true;
}

void BinarySearchTree::Inorder()
{
	Inorder(m_root);
	std::cout << std::endl;
}

void BinarySearchTree::Preorder()
{
	Preorder(m_root);
	std::cout << std::endl;
}

void BinarySearchTree::Postorder()
{
	Postorder(m_root);
	std::cout << std::endl;
}

float BinarySearchTree::AverageComparisons(int n)
{
	return static_cast<float>(n) / static_cast<float>(m_count);
}

Node *BinarySearchTree::Insert(Node *node, int data)
{
	// Create new node if tree is empty
	if (node == nullptr)
	{
		Node *temp = new Node;
		temp->data = data;
		temp->left = nullptr;
		temp->right = nullptr;
		return temp;
	}

	// Recur down the tree otherwise
	if (node->data > data)
	{
		node->left = Insert(node->left, data);
	}
	else if (node->data < data)
	{
		node->right = Insert(node->right, data);
	}

	return node;
}

Node *BinarySearchTree::Remove(Node *node, int data)
{
	if (node == nullptr) return nullptr;

	// Search to the right if smaller than given data
	if (node->data < data)
	{
		node->right = Remove(node->right, data);
	}
	// Search to the left if smaller than given data
	else if (node->data > data)
	{
		node->left = Remove(node->left, data);
	}
	// Target Node is found
	else
	{
		// One child or none
		if (node->left == nullptr)
		{
			Node *temp = node->right;
			delete node;
			return temp;
		}
		else if (node->right == nullptr)
		{
			Node *temp = node->left;
			delete node;
			return temp;
		}

		// Two children: Get the successor (min value in the right subtree) 
		std::function<Node*(Node*)> Min = [this, &Min](Node *node)
		{
			Node *current = node;

			while (current->left != nullptr)
			{
				current = current->left;
			}

			return current;
		};
		Node *temp = Min(node->right);

		// Replace node's data with data of successor
		node->data = temp->data;

		// Delete the old successor's data
		node->right = Remove(node->right, temp->data);

	}
	return node;
}

Node * BinarySearchTree::Search(Node *node, int data)
{
	// Increment comparison counter
	m_count++;

	if (node == nullptr) return nullptr;
	if (node->data == data) return node;
	if (node->data < data) return Search(node->right, data);

	return Search(node->left, data);
}

void BinarySearchTree::Inorder(Node *node)
{
	if (node == nullptr) return;

	// 1. Recur on left subtree
	Inorder(node->left);

	// 2. Print data of the node
	std::cout << node->data << " ";

	// 3. Recur on right subtree
	Inorder(node->right);
}

void BinarySearchTree::Preorder(Node *node)
{
	if (node == nullptr) return;

	// 1. Print data of the node
	std::cout << node->data << " ";

	// 2. Recur on the left subtree
	Preorder(node->left);

	// 3. Recur on the right subtree
	Preorder(node->right);
}

void BinarySearchTree::Postorder(Node *node)
{
	if (node == nullptr) return;

	// 1. Recur on the left subtree
	Postorder(node->left);

	// 2. Recur on right subtree
	Postorder(node->right);

	// 3. Print data of the node
	std::cout << node->data << " ";
}
