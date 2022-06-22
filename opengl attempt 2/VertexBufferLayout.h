#pragma once
#include<vector>
#include "GL/glew.h"


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
		}
		_ASSERT(false);
		return 0;

	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> ElementsVector;
	GLuint stride;
public:
	VertexBufferLayout()
		:stride(0) {}

	template<typename t>
	void Push(GLuint count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(GLuint count)
	{
		ElementsVector.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);

	}

	template<>
	void Push<unsigned int>(GLuint count)
	{
		ElementsVector.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(GLuint count)
	{
		ElementsVector.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return ElementsVector; }
	inline unsigned int GetStride() const { return stride; }

};