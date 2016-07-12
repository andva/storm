#pragma once

#include <vector>

template <typename T>
class Node
{
public:
	Node(T* d);
	void addParent(Node* parent);
	void addChild(Node* child);
	const T* getData() const { return m_data; }
	const std::vector<Node*>& getChildren() const { return m_childrens; };

private:
	T* m_data;
	std::vector<Node*> m_parents;
	std::vector<Node*> m_childrens;
};

template<typename T>
class NodeStructure
{
public:
	NodeStructure();
	~NodeStructure();
	void connect(Node<T>* parent, Node<T>* child);
	Node<T>* addNode(T* d);
	bool hasCircularNodes() const;
	std::vector<const Node<T>*> createOrderedUniqueList(std::vector<Node<T>*> nodeList) const;
	Node<T>* getNode(T& t);
	void clear();
private:

	void recCreateOrderedUniqueList(std::vector<const Node<T>*>& vec, const Node<T>* currentNode, int32_t currentDepth, int32_t maxDepth) const;
	bool recHasCircularNodes(const Node<T>* startNode, const Node<T>* currentNode, int32_t currentDepth, int32_t maxDepth) const;

	std::vector<Node<T>> m_nodes;

};

template<typename T>
void NodeStructure<T>::clear()
{
	m_nodes.clear();
}

#include "nodestucture.inl"