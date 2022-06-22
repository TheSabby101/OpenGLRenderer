#include "VertexBuffer.h"
#include "Header.h"

VertexBuffer::VertexBuffer(const void* vertexbufferdata, unsigned int size)
{
	// This will identify our vertex buffer
	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertexbufferdata, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &RendererID);
}

void VertexBuffer::Bind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, RendererID);
}

void VertexBuffer::Unbind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
