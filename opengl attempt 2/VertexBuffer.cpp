
#include "VertexBuffer.h"

/*
VertexBuffer::VertexBuffer(const std::vector<GLfloat> vertexbufferdata, unsigned int size)
{
	// This will identify our vertex buffer

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexbufferdata, GL_STATIC_DRAW);
}
*/
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
	std::cout << "Array Deleted" << std::endl;
	glDeleteBuffers(1, &RendererID);
}

void VertexBuffer::Bind()const
{
	std::cout << "Buffer Bound" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, RendererID);
}

void VertexBuffer::Unbind()const
{
	std::cout << "Buffer Unbound" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
