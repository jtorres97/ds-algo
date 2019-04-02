#pragma once

#include <algorithm>
#include <iostream>
#include <functional>

struct Node
{
	int data;
	Node *left;
	Node *right;
	int height;
};

class AVLTree 
{
public:
	AVLTree();

	void Insert(int data);
	void Remove(int data);
	bool Search(int data);

	void Inorder();
	void Preorder();
	void Postorder();
	float AverageComparisons(int n);
protected:
	Node *Insert(Node *node, int data);
	Node *Remove(Node *node, int data);
	Node *Search(Node *node, int data);

	Node *RotateLeft(Node *node);
	Node *RotateRight(Node *node);

	int Height(Node *node);

	void Inorder(Node *node);
	void Preorder(Node *node);
	void Postorder(Node *node);
private:
	Node *m_root;
	int m_count;
};

