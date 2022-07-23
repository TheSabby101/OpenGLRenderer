#include "Object.h"


Object::Object(const char* FilePath, const char* FragmentPath, const char* VertexPath, float x, float y, float z, Camera& CamRef)
	:ID(0),Cam(CamRef),X(x),Y(y),Z(z)
{
	
	
	VertexBuffer* lightBuffer = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData) * 4);
	VertexArray* LightArray = new VertexArray;
	VertexBufferLayout* LightLayout = new VertexBufferLayout;
	LightLayout->PushFloat(3);
	LightLayout->PushFloat(2);
	lightBuffer->Bind();
	LightArray->Bind();
	IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));
	LightArray->AddBuffer(*lightBuffer, *LightLayout);
	Shader* shaderlight = new Shader(VertexPath, FragmentPath);
	shaderlight->Bind();
	Textures* Texture2 = new Textures(FilePath);
	Texture2->Bind();
	shaderlight->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms1i("Texture", 0);
	shaderlight->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
	VAO* object2 = new VAO(*lightBuffer, *LightArray, *shaderlight, *Texture2);
	object = object2;
	ShaderRef = shaderlight;

}

Object::~Object()
{



}

void Object::Bind()
{
	object->Bind();
	
}

void Object::Draw(unsigned int Width, unsigned int Height)
{
	//Resize(Width, Height);
	Cam.Matrix(*ShaderRef,Width,Height);
	ShaderRef->SetUniforms3f("coordinates", X, Z, Y);
	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
	
}

void Object::SetColour(float R, float G, float B, float Transparency)
{
	ShaderRef->SetUniforms4f("u_colour", R, G, B , Transparency);

}



void Object::Resize(unsigned int Width, unsigned int Height)
{
	
	Cam.Projection = glm::perspective(glm::radians(Cam.fov), (float)(Width / Height), 0.1f, 1000.0f);
	Cam.width = Width;
	Cam.height = Height;
	ShaderRef->UniformMatrix4fv("CamMat", (Cam.Projection/(float)Width) * Cam.View);
}

void Object::Move(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

//old stack implement, didnt work
/*
Object::Object(const char* FilePath, const char* FragmentPath, const char* VertexPath)
	:shader(VertexPath, FragmentPath), Texture(FilePath), vb(VertexBufferData, sizeof(VertexBufferData) * 4), IB(Indices, sizeof(Indices)), ID(0), object(vb, va, shader, Texture)
{

	layout.PushFloat(3);
	layout.PushFloat(2);
	vb.Bind();
	va.Bind();
	va.AddBuffer(vb, layout);
	shader.Bind();
	Texture.Bind();
	shader.SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetUniforms1i("Texture", 0);
	shader.SetUniforms3f("coordinates", 0.0f, 0.0f, 2.0f);


	shader.UnBind();
	Texture.UnBind();
	vb.Unbind();
	va.Unbind();
}
*/