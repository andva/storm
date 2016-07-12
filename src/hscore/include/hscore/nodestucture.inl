

template <typename T>
Node<T>::Node(T* d)
	: m_data(d)
{

}


template <typename T>
void Node<T>::addChild(Node* child)
{
	m_childrens.push_back(child);
}

template <typename T>
void Node<T>::addParent(Node* parent)
{
	m_parents.push_back(parent);
}

template<typename T>
Node<T>* NodeStructure<T>::getNode(T& t)
{
	for (Node<T>& n : m_nodes)
	{
		if (n.getData() == &t)
		{
			return &n;
		}
	}
	return nullptr;
}

template<typename T>
std::vector<const Node<T>*> NodeStructure<T>::createOrderedUniqueList(std::vector<Node<T>*> nodeList) const
{
	std::vector<const Node<T>*> res;
	int32_t maxNodes = m_nodes.size() * (m_nodes.size() - 1) / 2;
	for (const Node<T>* node : nodeList)
	{
		recCreateOrderedUniqueList(res, node, 1, maxNodes);
	}
	return res;
}


template<typename T>
void NodeStructure<T>::recCreateOrderedUniqueList(std::vector<const Node<T>*>& vec, const Node<T>* currentNode, int32_t currentDepth, int32_t maxDepth) const
{
	++currentDepth;
	if (currentDepth == maxDepth)
		return;
	for (const Node<T>* c : currentNode->getChildren())
	{
		bool found = false;
		for (const Node<T>* ptr : vec)
		{
			if (ptr == c)
				found = true;
		}
		if (found)
			continue;
		recCreateOrderedUniqueList(vec, c, currentDepth, maxDepth);
	}
	vec.push_back(currentNode);
}

template<typename T>
bool NodeStructure<T>::recHasCircularNodes(const Node<T>* startNode, const Node<T>* currentNode, int32_t currentDepth, int32_t maxDepth) const
{
	++currentDepth;
	if (startNode == currentNode 
		|| currentDepth == maxDepth)
		return true;
	for (const Node<T>* c : currentNode->getChildren())
	{
		if (recHasCircularNodes(startNode, c, currentDepth, maxDepth))
			return true;
	}
	return false;
}

template<typename T>
bool NodeStructure<T>::hasCircularNodes() const
{
	int32_t maxNodes = m_nodes.size() * (m_nodes.size() - 1) / 2;

	for (const Node<T>& n : m_nodes)
	{
		for (const Node<T>* c : n.getChildren())
		{
			if (recHasCircularNodes(&n, c, 1, maxNodes))
			{
				return true;
			}
		}
	}
	return false;
}

template<typename T>
Node<T>* NodeStructure<T>::addNode(T* d)
{
	bool found = false;
	for (Node<T>& n : m_nodes)
	{
		if (n.getData() == d)
		{
			return &n;
		}
	}
	if (!found)
		m_nodes.push_back(d);
	return &m_nodes.back();
}

template<typename T>
void NodeStructure<T>::connect(Node<T>* parent, Node<T>* child)
{
	parent->addChild(child);
	child->addParent(parent);
}

template<typename T>
NodeStructure<T>::~NodeStructure()
{

}

template<typename T>
NodeStructure<T>::NodeStructure()
{

}