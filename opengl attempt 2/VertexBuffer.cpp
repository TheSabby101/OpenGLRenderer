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
	glGenBuffers(1, &RendererID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, RendererID[0]);
	glBufferData(GL_ARRAY_BUFFER, size*4, vertexbufferdata, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<glm::vec4>& vec4)
{
	glGenBuffers(1, &RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, RendererID[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * vec4.size(), vec4.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}



VertexBuffer::~VertexBuffer()
{
	//std::cout << "Array Deleted" << std::endl;
	glDeleteBuffers(1, RendererID);
}



void VertexBuffer::Add(std::vector<ObjectV4>& vec4)
{
	glGenBuffers(1, &RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, RendererID[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ObjectV4) * vec4.size(), vec4.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


void VertexBuffer::Bind()const
{
//	std::cout << "Buffer Bound" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, RendererID[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER,3, RendererID[1]);
}

void VertexBuffer::Unbind()const
{
//	std::cout << "Buffer Unbound" << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
