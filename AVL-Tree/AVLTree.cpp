#include "AVLTree.h"

AVLTree::AVLTree()
	: m_root(nullptr)
	, m_count(0)
{
}

void AVLTree::Insert(int data)
{
	m_root = Insert(m_root, data);
}

void AVLTree::Remove(int data)
{
	m_root = Remove(m_root, data);
}

bool AVLTree::Search(int data)
{
	Node *node = Search(m_root, data);

	return node == nullptr ? false : true;
}

void AVLTree::Inorder()
{
	Inorder(m_root);
	std::cout << std::endl;
}

void AVLTree::Preorder()
{
	Preorder(m_root);
	std::cout << std::endl;
}

void AVLTree::Postorder()
{
	Postorder(m_root);
	std::cout << std::endl;
}

Node *AVLTree::Insert(Node *node, int data)
{
	// Initial insertion
	if (node == nullptr)
	{
		node = new Node;
		node->data = data;
		node->left = nullptr;
		node->right = nullptr;
		node->height = 1;
		return node;
	}
	else if (data < node->data)
	{
		node->left = Insert(node->left, data);
	}
	else if (data > node->data)
	{
		node->right = Insert(node->right, data);
	}
	else
	{
		return node;
	}

	// Refresh node's height
	node->height = 1 + std::max(Height(node->left), Height(node->right));

	// Get the balance factor
	auto Balance = [this](Node *node) 
	{
		if (node == nullptr)
			return -1;

		return node == nullptr ? -1 : Height(node->left) - Height(node->right);
	};
	int balance = Balance(node);

	/*
	Handle unbalanced node with 4 cases
	*/

	// Left Left
	if (balance > 1 && data < node->left->data) return RotateRight(node);

	// Right Right
	if (balance < -1 && data > node->right->data) return RotateLeft(node);

	// Left Right
	if (balance > 1 && data > node->left->data)
	{
		node->left = RotateLeft(node->left);
		return RotateRight(node);
	}

	// Right Left
	if (balance < -1 && data < node->right->data)
	{
		node->right = RotateRight(node->right);
		return RotateLeft(node);
	}

	return node;
}

Node *AVLTree::Remove(Node *node, int data)
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

	// Return if tree had only one node
	if (node == nullptr) return node;

	// Update height of current node
	node->height = 1 + std::max(Height(node->left), Height(node->right));

	// Get balance factor of the node
	auto Balance = [this](Node *node)
	{
		if (node == nullptr)
			return -1;

		return node == nullptr ? -1 : Height(node->left) - Height(node->right);
	};
	int balance = Balance(node);

	/*
	If node is unbalanced, go through the 4 cases
	*/

	// Left Left
	if (balance > 1 && Balance(node->left) >= 0) return RotateRight(node);

	// Left Right
	if (balance > 1 && Balance(node->left) < 0)
	{
		node->left = RotateLeft(node->left);
		return RotateRight(node);
	}

	// Right Right
	if (balance < -1 && Balance(node->right) <= 0) return RotateLeft(node);

	// Right Left
	if (balance < -1 && Balance(node->right) > 0)
	{
		node->right = RotateRight(node->right);
		return RotateLeft(node);
	}

	return node;
}

Node *AVLTree::Search(Node * node, int data)
{
	// Inrement comparison counter
	m_count++;

	if (node == nullptr) return nullptr;
	if (node->data == data) return node;
	if (node->data < data) return Search(node->right, data);

	return Search(node->left, data);
}

Node *AVLTree::RotateLeft(Node *node)
{
	// Rotate the tree
	Node *balancedNode = node->right;
	node->right = balancedNode->left;
	balancedNode->left = node;

	// Update heights 
	node->height = std::max(Height(node->left), Height(node->right)) + 1;
	balancedNode->height = std::max(Height(balancedNode->left), Height(balancedNode->left)) + 1;

	// Return new root
	return balancedNode;
}

Node *AVLTree::RotateRight(Node *node)
{
	// Rotate the tree
	Node *balancedNode = node->left;
	node->left = balancedNode->right;
	balancedNode->right = node;

	// Update heights
	node->height = std::max(Height(node->left), Height(node->right)) + 1;
	balancedNode->height = std::max(Height(balancedNode->left), Height(balancedNode->left)) + 1;

	// Return new root
	return balancedNode;
}

int AVLTree::Height(Node *node)
{
	return node == nullptr ? -1 : node->height;
}

float AVLTree::AverageComparisons(int n)
{
	return static_cast<float>(n) / static_cast<float>(m_count);
}

void AVLTree::Inorder(Node * node)
{
	if (node == nullptr) return;

	// 1. Recur on left subtree
	Inorder(node->left);

	// 2. Print data of the node
	std::cout << node->data << " ";

	// 3. Recur on right subtree
	Inorder(node->right);
}

void AVLTree::Preorder(Node * node)
{
	if (node == nullptr) return;

	// 1. Print data of the node
	std::cout << node->data << " ";

	// 2. Recur on the left subtree
	Preorder(node->left);

	// 3. Recur on the right subtree
	Preorder(node->right);
}

void AVLTree::Postorder(Node * node)
{
	if (node == nullptr) return;

	// 1. Recur on the left subtree
	Postorder(node->left);

	// 2. Recur on right subtree
	Postorder(node->right);

	// 3. Print data of the node
	std::cout << node->data << " ";
}
