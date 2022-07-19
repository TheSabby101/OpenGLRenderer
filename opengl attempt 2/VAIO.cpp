#include "VAIO.h"

VAIO::VAIO(VertexBuffer& VB, VertexArray& VA, Shader& Shader, Textures& Texture)
	:ID(1),LocalVB(VB), LocalVA(VA), LocalShader(Shader), LocalTexture(Texture),TexUsed(1)
{
	

}


VAIO::~VAIO()
{

}

void VAIO::Bind()
{
	LocalShader.Bind();
	LocalVB.Bind();
	LocalVA.Bind();
	if(TexUsed)
		LocalTexture.Bind();
}

void VAIO::UnBind()
{
	LocalVB.Unbind();
	LocalVA.Unbind();
	LocalShader.UnBind();
	if (TexUsed)
		LocalTexture.UnBind();

}


