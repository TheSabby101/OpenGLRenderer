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

void VAO::AddAttribute(int vao, int vbo, int attribute, int size,int datalength,int offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glVertexAttribPointer(attribute, size, GL_FLOAT, false, datalength * 4, (void*)offset);
	glVertexAttribDivisor(attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}
