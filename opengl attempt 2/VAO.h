#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "LoadShader2.h"
#include "Textures.h"


class VAO
{
private:
	unsigned int ID;
	VertexBuffer& LocalVB;
	VertexArray& LocalVA;
	Shader& LocalShader;
	Textures& LocalTexture;
public:

	VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture);
	~VAO();
	void Bind();
	void UnBind();
	void update(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture);
};