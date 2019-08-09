#include <OGLEpch.h>
#include "Node.h"

namespace OGLEngine2
{
	Node::Node(const std::string& name, Node* const parent)
	{
		this->name = name;
		Node::SetParent(parent);
	}

	Node::~Node() = default;

	void Node::SetParent(Node* const newParent)
	{	
		if (!newParent) return;
		parent = newParent;
		parent->AddChild(this);
	}

	void Node::AddChild(Node* const child)
	{
		if (children.empty() || std::find(children.begin(), children.end(), child) == children.end())
		{
			children.push_back(child);
			child->SetParent(this);
		}
	}

	Node* Node::GetChild(const int& index) const
	{
		return children[index];
	}
}