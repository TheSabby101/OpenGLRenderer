#include "Object.h"


Object::Object(const char* Name, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()),Cam(CamRef),Width(CamRef.width),Height(CamRef.height), OBJName(Name)
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
	texCoords coords;
	shaderlight->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms2fv("texturecoords", 1, (coords.a, coords.b));
	shaderlight->SetUniforms1i("Texture", 0);
	shaderlight->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
	
	VAO* object2 = new VAO(*lightBuffer, *LightArray, *shaderlight, *Texture2);
	object = object2;
	ShaderRef = shaderlight;
	//object->UnBind();
	if (!shaderlight->LinkStatus)
	{
		std::cout << OBJName << " Failed to link shader \n";
	}
	else
	{
		std::cout << OBJName << " Linked \n";
	}
}

Object::Object(const char* Name, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(0), Cam(CamRef), Width(CamRef.width), Height(CamRef.height),OBJName(Name)
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
	shaderlight->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
	shaderlight->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);
	shaderlight->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
	VAO* object2 = new VAO(*lightBuffer, *LightArray, *shaderlight);
	object = object2;
	ShaderRef = shaderlight;
	//object->UnBind();
	if (!shaderlight->LinkStatus)
	{
		std::cout << OBJName << " Failed to link shader \n";
	}
	else
	{
		std::cout << OBJName << " Linked \n";
	}
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


void Object::DrawAt(float X, float Y, float Z, float W, float H, float D)
{
	
	
	

	


	//Bind();
	ShaderRef->SetUniforms3f("scale", W, H, D);
	ShaderRef->SetUniforms3f("coordinates", X, Z, Y);
	Cam.Matrix(*ShaderRef, Width, Height);

	//glGenQueries(3, QID);



//	glBeginQuery(GL_ANY_SAMPLES_PASSED, QID[1]);
	

	//glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, QID[2]);

	
	





		//glEndQuery(GL_ANY_SAMPLES_PASSED);
	
	//glGetQueryObjectiv(GL_SAMPLES_PASSED, GL_QUERY_RESULT, &any_samples_passed);

	//glEndQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE);

	//std::cout << any_samples_passed << "\n";

	

	//std::future<bool> Futures = std::launch::async,RTest.Begin();
	//std::vector<std::future<int>> ran;
	//ran.push_back(std::async(std::launch::async,RTest.Begin()));
	//std::future<int> f = std::launch::async,&Query::Begin, std::ref(RTest));
	//int i = Begin();

//	std::future<void> foo = std::async(std::launch::async, Begin);
    auto a1 = std::async(RTest.Begin);

	//Begin();
	if (RTest.any_samples_passed)
	{
		std::cout << "woo" << std::endl;
		glBeginConditionalRender(*RTest.any_samples_passed, GL_QUERY_BY_REGION_NO_WAIT);
		glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
		glEndConditionalRender();
		
		
}
	else if(!*RTest.any_samples_passed)
	{
	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
	//std::cout << "fuck" << std::endl;
	}

	auto ret = a1.get();
	auto a2 = std::async(RTest.End);
	auto ret2 = a2.get();
	//End();
	
	//glDeleteQueries(3, QID);
	
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

void Object::AddToList(float X, float Y, float Z,float W,float H, float D)
{
	ObjectV3 V3(X, Y, Z, W, H,D);
	DrawIndex.push_back(V3);
}

void Object::ShaderToy()
{
	ShaderRef->SetUniforms3f("iResolution", (float)Width, (float)Height, (float)Width* (float)Height);
	ShaderRef->SetUniforms1f("iTime", glfwGetTime());
	//std::cout << glfwGetTime() << std::endl;
}

void Object::DrawList()
{
	Bind();
	ShaderToy();
	for(size_t i=0; i< DrawIndex.size();i++)
	{
		
	
		DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z,DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth);
	

	}
}

/*
void Object::GenQueries()
{
	if (any_samples_passed)
		glGenQueries(1, &Test);
}

int Object::Begin()
{
	GenQueries();
	glBeginQuery(GL_SAMPLES_PASSED, Test);
	return 0;
}

void Object::End()
{

	glEndQuery(GL_SAMPLES_PASSED);
	glGetQueryiv(GL_SAMPLES_PASSED, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	//glGetQueryObjectiv(Test, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
}





*/







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