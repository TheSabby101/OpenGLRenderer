
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:M_Count(count)
{
	// This will identify our vertex buffer
	
	// Generate 1 buffer, put the resulting identifier in IndexBuffer
	glGenBuffers(1, &RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
