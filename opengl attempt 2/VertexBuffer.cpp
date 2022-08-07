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

	//glGenBuffers(1, &RendererID[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, RendererID[0]);
	//glBufferData(GL_ARRAY_BUFFER, vec4.size()*sizeof(glm::vec4), vec4.data(), GL_DYNAMIC_DRAW);

	
	glGenBuffers(1, &RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, RendererID[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * vec4.size(), vec4.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, RendererID[1]);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}



VertexBuffer::~VertexBuffer()
{
	//std::cout << "Array Deleted" << std::endl;
	glDeleteBuffers(1, RendererID);
}
//std::vector<glm::vec3>& vec3,
void VertexBuffer::Add(std::vector<ObjectV4>& vec4)
{




	glGenBuffers(1, &RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, RendererID[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ObjectV4) * vec4.size(), vec4.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, RendererID[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);


	//glGenBuffers(1, &RendererID[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, RendererID[1]);
	////glBufferData(GL_ARRAY_BUFFER, vec3.size() * sizeof(glm::vec3), &vec3[0], GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, count*4, nullptr, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);



//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, RendererID[1]);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//	glVertexAttribDivisor(3, 1);

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
