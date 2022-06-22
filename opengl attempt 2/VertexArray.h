#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int arrayrenderID;
public:

	VertexArray();
	
	~VertexArray();
	
	void AddBuffer(const VertexBuffer& V, const VertexBufferLayout& layout);

	void Bind();
		void Unbind();
};