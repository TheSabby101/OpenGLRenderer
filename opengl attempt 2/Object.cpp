#include "Object.h"


Object::Object(const char* Name, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()),Cam(CamRef),Width(CamRef.width),Height(CamRef.height), OBJName(Name), textureColorbuffer(0)
{
	bool rerun = true;
	int Attempts = 1;
		VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData) * 4);
		VertexArray* Array = new VertexArray;
		VertexBufferLayout* LayoutObject = new VertexBufferLayout;
		LayoutObject->PushFloat(3);
		LayoutObject->PushFloat(2);
		LayoutObject->PushFloat(3);
		VB->Bind();
		Array->Bind();
		IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));
		Array->AddBuffer(*VB, *LayoutObject);



		//Due to shaders constantly failing to link, i redo this every time it fails
		while (rerun)
		{
		Shader* ShaderObject = new Shader(VertexPath, FragmentPath);
		ShaderObject->Bind();
	    Textures* Texture2 = new Textures(FilePath);
		Texture2->Bind();
		//texCoords coords;


		VAO* object2 = new VAO(*VB, *Array, *ShaderObject, *Texture2);
	

		//object->UnBind();
		if (!ShaderObject->LinkStatus)
		{
		//	std::cout << OBJName << " Failed to link shader \n";
			delete ShaderObject;
			delete object2;
			delete Texture2;
			Attempts++;
		}
		else
		{
			object = object2;
			ShaderRef = ShaderObject;
			ShaderRef->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
			//ShaderRef->SetUniforms2fv("texturecoords", 1, (coords.a, coords.b));
			ShaderRef->SetUniforms1i("Texture", 0);
			ShaderRef->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
			ShaderRef->SetUniforms3f("LightPos", 0.0f, 0.0f, 0.0f);
			ShaderRef->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);
		
			rerun = false;
			std::cout << OBJName << " Linked after " << Attempts << " Attempts \n";
		}
	}
	//::cout << ID  << std::endl;
		AddToListGui();
		ObjectDrawList.push_back(this);
}

Object::Object(const char* Name, Block blocktype, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()), Cam(CamRef), Width(CamRef.width), Height(CamRef.height), OBJName(Name), textureColorbuffer(0)
{


	GetBlockType(blocktype);


	bool rerun = true;
	int Attempts = 1;
	VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData) * 4);
	VertexArray* Array = new VertexArray;
	VertexBufferLayout* LayoutObject = new VertexBufferLayout;
	LayoutObject->PushFloat(3);
	LayoutObject->PushFloat(2);
	LayoutObject->PushFloat(3);
	VB->Bind();
	Array->Bind();
	IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));
	Array->AddBuffer(*VB, *LayoutObject);



	//Due to shaders constantly failing to link, i redo this every time it fails
	while (rerun)
	{
		Shader* ShaderObject = new Shader(VertexPath, FragmentPath);
		ShaderObject->Bind();
		Textures* Texture2 = new Textures(FilePath);
		Texture2->Bind();
		//texCoords coords;


		VAO* object2 = new VAO(*VB, *Array, *ShaderObject, *Texture2);


		//object->UnBind();
		if (!ShaderObject->LinkStatus)
		{
			//	std::cout << OBJName << " Failed to link shader \n";
			delete ShaderObject;
			delete object2;
			delete Texture2;
			Attempts++;
		}
		else
		{
			object = object2;
			ShaderRef = ShaderObject;
			ShaderRef->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
			//ShaderRef->SetUniforms2fv("texturecoords", 1, (coords.a, coords.b));
			ShaderRef->SetUniforms1i("Texture", 0);
			ShaderRef->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
			ShaderRef->SetUniforms3f("LightPos", 0.0f, 0.0f, 0.0f);
			ShaderRef->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);

			rerun = false;
			std::cout << OBJName << " Linked after " << Attempts << " Attempts \n";
		}
	}
	//::cout << ID  << std::endl;
	AddToListGui();
	ObjectDrawList.push_back(this);
}

Object::Object(const char* Name, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()), Cam(CamRef), Width(CamRef.width), Height(CamRef.height),OBJName(Name), textureColorbuffer(0)
{
	int Attempts = 1;
	bool rerun = true;
	/*
		VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData) * 4);
		VertexArray* Array = new VertexArray;
		VertexBufferLayout* LayoutObject = new VertexBufferLayout;
		LayoutObject->PushFloat(3);
		LayoutObject->PushFloat(2);
		VB->Bind();
		Array->Bind();
		IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));
		Array->AddBuffer(*VB, *LayoutObject);
		*/
	
	VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData));
	VB->Bind();
	VertexArray* Array = new VertexArray;
	Array->Bind();
	VertexBufferLayout LayoutObject;
	LayoutObject.PushFloat(3);	LayoutObject.PushFloat(2);	LayoutObject.PushFloat(3);
	IndexBuffer* LightIndexBuffer =  new IndexBuffer(Indices, 36);
	Array->AddBuffer(*VB, LayoutObject);

	//Due to shaders constantly failing to link, i redo this every time it fails


	while (rerun)
	{
		Shader* ShaderObject = new Shader(VertexPath, FragmentPath);
		ShaderObject->Bind();
	
	
	
		if (!ShaderObject->LinkStatus)
		{
			//std::cout << OBJName << " Failed to link shader \n";
			//delete VB;
			//delete Array;
			//delete LightIndexBuffer;
			delete ShaderObject;
			Attempts++;
		}
		else
		{
			
			rerun = false;
			VAO* object2 = new VAO(*VB, *Array, *ShaderObject);
			object = object2;
			ShaderRef = ShaderObject;
			ShaderRef->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
			ShaderRef->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("LightPos", 0.0f, 0.5f, 1.0f);
			std::cout << OBJName << " Linked after " << Attempts << " Attempts \n";
			object->UnBind();
		}
		//std::cout << ID << std::endl;
	}
	AddToListGui();
	ObjectDrawList.push_back(this);
}

Object::~Object()
{
	//delete ShaderRef;
	

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
	//queer.Begin();
	//Bind();
	ShaderRef->SetUniforms3f("scale", W, H, D);
	ShaderRef->SetUniforms3f("coordinates", X, Z, Y);
	

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
   // auto a1 = std::async(RTest.Begin);

	//Begin();
//	if (RTest.any_samples_passed)
//	{
//		std::cout << "woo" << std::endl;
	   // queer.End();
	//	glBeginConditionalRender(queer.any_samples_passed, GL_QUERY_BY_REGION_NO_WAIT);
	//	if (queer.any_samples_passed)
	//	{
			std::launch::async, glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
			//glEndConditionalRender();
	//	}
	//	queer.any_samples_passed = 0;
		
		
//}
//	else if(!*RTest.any_samples_passed)
//	{
//	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
	//std::cout << "fuck" << std::endl;
//	}

	//auto ret = a1.get();
	//auto a2 = std::async(RTest.End);
	//auto ret2 = a2.get();
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

void Object::AddToListGui()
{
	Objectlist[ObjectCount] = this;
	Objectlist.emplace_back();
	ObjectCount++;
}

void Object::AddToList(float X, float Y, float Z,float W,float H, float D)
{
	ObjectV3 V3(X, Y, Z, W, H,D);
	DrawIndex.push_back(V3);
}

void Object::ShaderToy()
{
	ShaderRef->SetUniforms3f("iResolution", (float)Width, (float)Height, (float)Width* (float)Height);
	ShaderRef->SetUniforms1f("iTime", time);
	//std::cout << glfwGetTime() << std::endl;
}

void Object::DrawList()
{
	//if(ShaderRef->LinkStatus)
	//{
		Bind();
		ShaderToy();

		for (size_t i = 0; i < DrawIndex.size(); i++)
		{
			std::launch::async, DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z, DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth);

		}


		/*
		for (size_t i = 0; i < DrawIndex.size()/16; i += 16)
		{
			for (size_t n = 0; n < DrawIndex.size(); n++)
			{
				std::launch::async,DrawAt(DrawIndex[n].x, DrawIndex[n].y, DrawIndex[n].z, DrawIndex[n].Width, DrawIndex[n].Height, DrawIndex[n].Depth);
			}

		}
		*/

		/*
		if (DrawIndex.size() < 8)
		{
			for (size_t i = 0; i < DrawIndex.size(); i++)
			{
				std::launch::async, DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z, DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth);

			}
		}
		else
		{


			for (size_t i = 0; i < DrawIndex.size(); i += 8)
			{
				std::launch::async, DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z, DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 1].x, DrawIndex[i + 1].y, DrawIndex[i + 1].z, DrawIndex[i + 1].Width, DrawIndex[i + 1].Height, DrawIndex[i + 1].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 2].x, DrawIndex[i + 2].y, DrawIndex[i + 2].z, DrawIndex[i + 2].Width, DrawIndex[i + 2].Height, DrawIndex[i + 2].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 3].x, DrawIndex[i + 3].y, DrawIndex[i + 3].z, DrawIndex[i + 3].Width, DrawIndex[i + 3].Height, DrawIndex[i + 3].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 4].x, DrawIndex[i + 4].y, DrawIndex[i + 4].z, DrawIndex[i + 4].Width, DrawIndex[i + 4].Height, DrawIndex[i + 4].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 5].x, DrawIndex[i + 5].y, DrawIndex[i + 5].z, DrawIndex[i + 5].Width, DrawIndex[i + 5].Height, DrawIndex[i + 5].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 6].x, DrawIndex[i + 6].y, DrawIndex[i + 6].z, DrawIndex[i + 6].Width, DrawIndex[i + 6].Height, DrawIndex[i + 6].Depth);
				std::launch::async, DrawAt(DrawIndex[i + 7].x, DrawIndex[i + 7].y, DrawIndex[i + 7].z, DrawIndex[i + 7].Width, DrawIndex[i + 7].Height, DrawIndex[i + 7].Depth);
			}
		}
		*/
		Cam.Matrix(*ShaderRef, Width, Height);
	//}
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



void Object::AtlasMapper()
{
	int one = 3, two = 11, three = 19, four = 27;
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
		{
			one += 32;
			two += 32;
			three += 32;
			four += 32;
		}

		VertexBufferData[one] = AtlasX * TextureSize / AtlasSize;
		VertexBufferData[one + 1] = AtlasY * TextureSize / AtlasSize;
		VertexBufferData[two] = (AtlasX + 1) * TextureSize / AtlasSize;
		VertexBufferData[two + 1] = AtlasY * TextureSize / AtlasSize;
		VertexBufferData[three] = (AtlasX + 1) * TextureSize / AtlasSize;
		VertexBufferData[three + 1] = (AtlasY + 1) * TextureSize / AtlasSize;
		VertexBufferData[four] = AtlasX * TextureSize / AtlasSize;
		VertexBufferData[four + 1] = (AtlasY + 1) * TextureSize / AtlasSize;
	}
}


void Object::AtlasMapperPerFace(BlockFace face)
{

	int one = 3, two = 11, three = 19, four = 27;
	
		
			one += (32 * face);
			two += (32 * face);
			three += (32 * face);
			four += (32 * face);
		

		VertexBufferData[one] = AtlasX * TextureSize / AtlasSize;
		VertexBufferData[one + 1] = AtlasY * TextureSize / AtlasSize;
		VertexBufferData[two] = (AtlasX + 1) * TextureSize / AtlasSize;
		VertexBufferData[two + 1] = AtlasY * TextureSize / AtlasSize;
		VertexBufferData[three] = (AtlasX + 1) * TextureSize / AtlasSize;
		VertexBufferData[three + 1] = (AtlasY + 1) * TextureSize / AtlasSize;
		VertexBufferData[four] = AtlasX * TextureSize / AtlasSize;
		VertexBufferData[four + 1] = (AtlasY + 1) * TextureSize / AtlasSize;
	
}

void Object::GetBlockType(Block blocktype)
{
	switch (blocktype)
	{
	case grass:
		AtlasX = 0;
		AtlasY = 15;
		AtlasMapperPerFace(Topface);
		AtlasX = 3;
		AtlasY = 15;
		AtlasMapperPerFace(Northface);
		AtlasMapperPerFace(Southface);
		AtlasMapperPerFace(Eastface);
		AtlasMapperPerFace(Westface);
		AtlasX = 2;
		AtlasY = 15;
		AtlasMapperPerFace(Bottomface);

		break;


	case dirt:
		AtlasX = 2; AtlasY = 15;
		AtlasMapper();
		break;


	case sand:
		AtlasX = 2; AtlasY = 14;
		AtlasMapper();
		break;

	case craftingbench:
		AtlasX = 11; AtlasY = 13;
		AtlasMapperPerFace(Topface);
		AtlasX = 11; AtlasY = 12;
		AtlasMapperPerFace(Eastface);
		AtlasX = 12; AtlasY = 12;
		AtlasMapperPerFace(Westface);
		AtlasX = 11; AtlasY = 11;
		AtlasMapperPerFace(Southface);
		AtlasX = 10; AtlasY = 11;
		AtlasMapperPerFace(Northface);
		AtlasX = 6; AtlasY = 3;
		AtlasMapperPerFace(Bottomface);
		break;

	case furnace:
		AtlasX = 14; AtlasY = 12;
		AtlasMapperPerFace(Topface);
		AtlasX = 13; AtlasY = 13;
		AtlasMapperPerFace(Eastface);
		AtlasX = 13; AtlasY = 13;
		AtlasMapperPerFace(Westface);
		AtlasX = 12; AtlasY = 13;
		AtlasMapperPerFace(Southface);
		AtlasX = 13; AtlasY = 13;
		AtlasMapperPerFace(Northface);
		AtlasX = 14; AtlasY = 12;
		AtlasMapperPerFace(Bottomface);
		break;


	case lava:
		AtlasX = 15; AtlasY = 0;
		AtlasMapper();
		break;

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