#pragma once

template <typename T>
class BTreeNode
{
public:
	BTreeNode();
	explicit BTreeNode(int k);

	bool IsLeaf() const;
private:
	T *m_data;
	BTreeNode **m_children;
	int m_maxElements;
	int n_numElements;
	int m_numChildren;

	template <typename U> 
	friend class BTree;

	template <typename F>
	friend std::ostream& operator<<(std::ostream &os, const BTreeNode<F> &rhsobj);
};

template <typename T>
BTreeNode<T>::BTreeNode()
{
	m_maxElements = 5;
	m_data = new T[m_maxElements];

	m_children = new BTreeNode*[m_maxElements + 1];
	for (auto i = 0; i < m_maxElements + 1; i++)
		m_children[i] = nullptr;

	n_numElements = 0;
	m_numChildren = 0;
}

template <typename T>
BTreeNode<T>::BTreeNode(int k)
{
	m_maxElements = k;
	m_data = new T[m_maxElements]; 
	m_children = new BTreeNode*[m_maxElements + 1];
	for (auto i = 0; i < m_maxElements + 1; i++)
		m_children[i] = nullptr;

	n_numElements = 0;
	m_numChildren = 0;
}

template <typename T>
bool BTreeNode<T>::IsLeaf() const
{
	return m_numChildren == 0;
}

template <typename F>
std::ostream& operator<<(std::ostream &os, const BTreeNode<F> &rhsobj)
{
	os << "|";
	for (auto i = 0; i < rhsobj.n_numElements; i++)
	{
		os << " " << rhsobj.m_data[i] << " ";
	}
	os << "|";
	return os;
}
