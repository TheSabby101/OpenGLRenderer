#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "LoadShader2.h"
#include "Textures.h"


class VAIO
{
private:
	unsigned int ID;
	bool TexUsed = 0;
	VertexBuffer& LocalVB;
	VertexArray& LocalVA;
	Shader& LocalShader;
	Textures& LocalTexture;
public:

	VAIO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture);
	~VAIO();
	void Bind();
	void UnBind();
};