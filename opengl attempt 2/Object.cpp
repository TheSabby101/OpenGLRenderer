#include "Object.h"


Object::Object(const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(0),Cam(CamRef),Width(CamRef.width),Height(CamRef.height)
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
	//Texture2->Bind();
	shaderlight->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms1i("Texture", 0);
	shaderlight->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
	VAO* object2 = new VAO(*lightBuffer, *LightArray, *shaderlight, *Texture2);
	object = object2;
	ShaderRef = shaderlight;

}

Object::Object(const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(0), Cam(CamRef), Width(CamRef.width), Height(CamRef.height)
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
	shaderlight->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
	VAO* object2 = new VAO(*lightBuffer, *LightArray, *shaderlight);
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

void Object::Draw()
{
	//Bind();
	Cam.Matrix(*ShaderRef,Width,Height);
	ShaderRef->SetUniforms3f("coordinates", X, Z, Y);
	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
}

void Object::DrawAt(float X, float Y, float Z)
{
//	Bind();
	ShaderRef->SetUniforms3f("coordinates", X, Z, Y);
	Cam.Matrix(*ShaderRef, Width, Height);
	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
}

void Object::SetColour(float R, float G, float B, float Transparency)
{
	ShaderRef->SetUniforms4f("u_colour", R, G, B , Transparency);

}

void Object::SetCoord(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}


void Object::Move(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

void Object::AddToList(float X, float Y, float Z)
{
	ObjectV3 V3(X, Y, Z);
	DrawIndex.push_back(V3);
}

void Object::DrawList()
{
	Bind();
	for(size_t i=0; i< DrawIndex.size();i++)
	{
	
		DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z);

	}
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

//no longer needed after swapping to references
/*
void Object::Resize()
{

	Cam.Projection = glm::perspective(glm::radians(Cam.fov), ((float)Width / (float)Height), 0.1f, 1000.0f);
	//Cam.width = Width;
	//Cam.height = Height;
	ShaderRef->UniformMatrix4fv("CamMat", (Cam.Projection/(float)Width) * Cam.View);
}
*/