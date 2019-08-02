#pragma once

#include "Node.h"
#include "Gameplay/Structures/Math.h"

namespace OGLEngine2
{
	class TransformNode : public Node
	{
	public:
		Vector2 position;
		// Quaternion rotation
		Vector2 scale;

	public:
		TransformNode(const std::string& name, Node* const parent = nullptr);
		~TransformNode();
		void Start() override;
		void Update() override;
		void Stop() override;
	};
}