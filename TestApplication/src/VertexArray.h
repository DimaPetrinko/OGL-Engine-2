#pragma once

#include "OGLEpch.h"
#include "Renderer.h"
#include "GraphicsObject.h"
#include "VertexBuffer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			default: return 0;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride{};
public:
	template<typename T>
	void Push(const unsigned int& count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(const unsigned int& count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(const unsigned int& count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	
	template<>
	void Push<unsigned char>(const unsigned int& count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	const std::vector<VertexBufferElement>& GetElements() const { return elements; }
	unsigned int GetStride() const { return stride; }
};

class VertexArray : public GraphicsObject
{
public:
	~VertexArray();

	void Generate() override;
	void Bind() const override;
	void Unbind() const override;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
