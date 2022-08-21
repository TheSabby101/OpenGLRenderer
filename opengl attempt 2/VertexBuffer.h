#pragma once
#include "Header.h"
#include <vector>

class VertexBuffer
{
private:
	
public:
	unsigned int RendererID[3];
	//VertexBuffer(const std::vector<GLfloat> vertexbufferdata, unsigned int size);

	VertexBuffer(const void* vertexbufferdata, unsigned int size);
	//VertexBuffer(std::vector<glm::vec4>& vec4);
	~VertexBuffer();

	//GLuint ssboModelMatrices;

	void Add(std::vector<ObjectV4>& vec4,int location = 1);

	void Bind()const;
	void Unbind()const;

};