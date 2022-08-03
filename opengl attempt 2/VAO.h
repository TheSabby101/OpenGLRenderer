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
	bool TexUsed = false;
	VertexBuffer& LocalVB;
	VertexArray& LocalVA;
	Shader& LocalShader;
	Textures* LocalTexture = 0;
	unsigned int* LocalRBO = 0;
	

public:
	
	VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture);
	VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, unsigned int& RBO);
	VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader);
	~VAO();
	void Bind();
	void BindRBO();
	void UnBind();
	void update(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture);
	void update(VertexBuffer& VB, VertexArray& VA, Shader& Shader);
};