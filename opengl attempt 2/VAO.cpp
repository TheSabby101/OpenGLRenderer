#include "VAO.h"

VAO::VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture)
	:ID(1),TexUsed(true),LocalVB(VB), LocalVA(VA), LocalShader(Shader), LocalTexture(&Texture)
{
	
		
}
VAO::VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, unsigned int& RBO)
	:ID(1), TexUsed(true), LocalVB(VB), LocalVA(VA), LocalShader(Shader), LocalRBO(&RBO)
{
}
VAO::VAO(VertexBuffer& VB, VertexArray& VA, Shader& Shader)
	:ID(1), LocalVB(VB), LocalVA(VA), LocalShader(Shader)
{


}
VAO::~VAO()
{

}

void VAO::Bind()
{
	LocalShader.Bind();
	LocalVB.Bind();
	LocalVA.Bind();
	if(TexUsed)
	LocalTexture->Bind();
}

void VAO::BindRBO()
{
	LocalShader.Bind();
	LocalVB.Bind();
	LocalVA.Bind();

}

void VAO::UnBind()
{
	LocalVB.Unbind();
	LocalVA.Unbind();
	LocalShader.UnBind();
	if (TexUsed)
	LocalTexture->UnBind();

}

void VAO::update(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture)
{
	LocalVB = VB;
	LocalVA = VA;
	LocalShader = Shader;
	LocalTexture = &Texture;

}

void VAO::update(VertexBuffer& VB, VertexArray& VA, Shader& Shader)
{
	LocalVB = VB;
	LocalVA = VA;
	LocalShader = Shader;
}

