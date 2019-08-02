#pragma once

namespace OGLEngine2
{
	class Node
	{
	public:
		std::string name;
		Node* parent;
	protected:
		std::vector<Node*> children;

	public:
		virtual void SetParent(Node* const newParent);
		virtual void AddChild(Node* const child);
		virtual Node* GetChild(const int& index) const;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;
		virtual ~Node();
	protected:
		Node(const std::string& name, Node* const parent = nullptr);
	};
}