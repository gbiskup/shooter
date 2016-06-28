#pragma once

class GameNodeFactory
{
public:
	virtual ~GameNodeFactory() = default;
protected:
	// TODO: Use variadic templates to initialize constructors!
	template <class NodeClass, class NodeType> NodeClass* createNode(const NodeType&);
};

// This function does what cocos macro CREAT_FUNC does but gives a chance to push give types to constructors
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
