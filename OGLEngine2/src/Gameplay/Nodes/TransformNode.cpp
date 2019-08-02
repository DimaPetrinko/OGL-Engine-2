#include <OGLEpch.h>
#include "TransformNode.h"

namespace OGLEngine2
{
	TransformNode::TransformNode(const std::string& name, Node* const parent) : Node(name, parent)
	{
		position = OGLEngine2::Vector2::Zero();
		// rotation
		scale = OGLEngine2::Vector2::One();
	}

	TransformNode::~TransformNode()
	{
		Stop();
	}

	void TransformNode::Start()
	{

	}

	void TransformNode::Update()
	{

	}

	void TransformNode::Stop()
	{

	}
}