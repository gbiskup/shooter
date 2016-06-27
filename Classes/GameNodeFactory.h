#pragma once

class GameNodeFactory
{
public:
	virtual ~GameNodeFactory() {};
protected:
	template <class NodeClass, class NodeType> NodeClass* createNode(const NodeType&);
};

template<class NodeClass, class NodeType>
inline NodeClass * GameNodeFactory::createNode(const NodeType &type)
{
	auto node = new (std::nothrow) NodeClass(type);
	if (node && node->init())
	{
		node->autorelease();
	}
	else
	{
		delete node;
		node = nullptr;
	}
	return node;
}
