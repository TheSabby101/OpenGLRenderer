#pragma once
#include "Header.h"
#include <vector>

class VertexBuffer
{
private:
	unsigned int RendererID;
public:
	VertexBuffer(const std::vector<GLfloat> vertexbufferdata, unsigned int size);
	VertexBuffer(const void* vertexbufferdata, unsigned int size);
	~VertexBuffer();



	void Bind()const;
	void Unbind()const;

};