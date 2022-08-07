#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	
public:
	unsigned int offset;
	unsigned int arrayrenderID;
	VertexArray();
	
	~VertexArray();
	
	void AddBuffer(const VertexBuffer& V, const VertexBufferLayout& layout);

	void LinkAttrib(VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
		void Unbind();
};