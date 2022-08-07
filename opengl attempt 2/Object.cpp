#include "Object.h"




//Initialiser for Texutred Objects
Object::Object(const char* Name, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()),Cam(CamRef),Width(CamRef.width),Height(CamRef.height), OBJName(Name), textureColorbuffer(0)
{
	bool rerun = true;
	int Attempts = 1;

	VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData) * 4);
	//VertexBuffer* VBOinstance = new VertexBuffer(InstanceCoordinates);
	VertexArray* Array = new VertexArray;
	VertexBufferLayout* LayoutObject = new VertexBufferLayout;


	//if (MeshInstances != 1)
	//{
	//	VBOinstance->Bind();
	//
	//	Array->LinkAttrib(*VBOinstance, 4, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
	//	Array->LinkAttrib(*VBOinstance, 5, 3, GL_FLOAT, sizeof(glm::vec3), (void*)(1* sizeof(glm::vec3)));
	//	Array->LinkAttrib(*VBOinstance, 6, 3, GL_FLOAT, sizeof(glm::vec3), (void*)(2* sizeof(glm::vec3)));
	//
	//	glVertexAttribDivisor(4, 1);
	//	glVertexAttribDivisor(5, 1);
	//	glVertexAttribDivisor(6, 1);
	//	
	//}
	

	//InstanceCoordinates.push_back(trans * rot * scale);

	LayoutObject->PushFloat(3);	LayoutObject->PushFloat(2);	LayoutObject->PushFloat(3);
	
	VB->Bind();	Array->Bind();
	
	IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));

	Array->AddBuffer(*VB, *LayoutObject);
	VB->Add(InstanceCoordinates);
	//Due to shaders constantly failing to link, i redo this every time it fails
	while (rerun)
	{
		Shader* ShaderObject = new Shader(VertexPath, FragmentPath);
		ShaderObject->Bind();
		Textures* Texture2 = new Textures(FilePath);
		Texture2->Bind();


		if (!ShaderObject->LinkStatus)
		{
		//	std::cout << OBJName << " Failed to link shader \n";
			delete ShaderObject;
			delete Texture2;
			Attempts++;
		}
		else
		{
			VAO* object2 = new VAO(*VB, *Array, *ShaderObject, *Texture2);
			object = object2;
			ShaderRef = ShaderObject;

			//VB->Add(3 * MeshInstances);
			//object->AddAttribute(Array->arrayrenderID, (int)VB->RendererID, 1, 3, 3, 0);

			ShaderRef->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms1i("Texture", 0);
			ShaderRef->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
			ShaderRef->SetUniforms3f("LightPos", 0.0f, 0.0f, 0.0f);
			ShaderRef->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);

			object->UnBind();
			rerun = false;
			std::cout << OBJName << " Linked after " << Attempts << " Attempts \n";
		}
	}

	AddToListGui();
	ObjectDrawList.push_back(this);
}
//Initialiser for objects using a texture atlas
Object::Object(const char* Name, Block blocktype, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()), Cam(CamRef), Width(CamRef.width), Height(CamRef.height), OBJName(Name), textureColorbuffer(0)
{
	GetBlockType(blocktype);
	bool rerun = true;
	int Attempts = 1;

	VertexBuffer* VB = new VertexBuffer(VertexBufferData, sizeof(VertexBufferData));

	VertexArray* Array = new VertexArray;
	
	VertexBufferLayout* LayoutObject = new VertexBufferLayout;
	LayoutObject->PushFloat(3);	LayoutObject->PushFloat(2);	LayoutObject->PushFloat(3);

	VB->Bind();	Array->Bind();

	IndexBuffer* LightIndexBuffer = new IndexBuffer(Indices, sizeof(Indices));

	Array->AddBuffer(*VB, *LayoutObject);

	if (MeshInstances != 1)
	{
		//VertexArray* ArrayInstance = new VertexArray;
		//VBinstance->Bind(); //ArrayInstance->Bind();
	//	VertexBufferLayout* LayoutObjectInstance = new VertexBufferLayout;
		//LayoutObjectInstance->PushFloat(3);
	//	Array->AddBuffer(*VBinstance, *LayoutObjectInstance);

		//glVertexAttribDivisor(3, 1);
	}

	//Due to shaders constantly failing to link, i redo this every time it fails
	while (rerun)
	{
		Shader* ShaderObject = new Shader(VertexPath, FragmentPath);
		ShaderObject->Bind();
		Textures* Texture2 = new Textures(FilePath);
		Texture2->Bind();

	
		if (!ShaderObject->LinkStatus)
		{
			//	std::cout << OBJName << " Failed to link shader \n";
			delete ShaderObject;
			delete Texture2;
			Attempts++;
		}
		else
		{
			VAO* object2 = new VAO(*VB, *Array, *ShaderObject, *Texture2);
			object = object2;
			ShaderRef = ShaderObject;
			ShaderRef->SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms1i("Texture", 0);
			ShaderRef->SetUniforms3f("scale", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
			ShaderRef->SetUniforms3f("LightPos", 0.0f, 0.0f, 0.0f);
			ShaderRef->SetUniforms3f("objectColor", 1.0f, 1.0f, 1.0f);
			ShaderRef->SetUniforms3f("lightColor", 1.0f, 1.0f, 1.0f);
			object->UnBind();
			rerun = false;
			std::cout << OBJName << " Linked after " << Attempts << " Attempts \n";
		}
	}
	//::cout << ID  << std::endl;
	AddToListGui();
	ObjectDrawList.push_back(this);
}
//Initialiser for textureless Objects
Object::Object(const char* Name, const char* FragmentPath, const char* VertexPath, Camera& CamRef)
	:ID(glCreateProgram()), Cam(CamRef), Width(CamRef.width), Height(CamRef.height),OBJName(Name), textureColorbuffer(0)
{
	int Attempts = 1;
	bool rerun = true;
	
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
	delete ShaderRef;
}



//Binds the VAO
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


// Draws at a location
void Object::DrawAt(float X, float Y, float Z, float W, float H, float D,int DrawCount)
{
	//Bind();
	//ShaderRef->SetUniforms3f("scale", W, H, D);
	//ShaderRef->SetUniforms3f("coordinates", X, Z, Y);


	std::launch::async, glDrawElementsInstanced(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, nullptr, DrawCount);

}

void Object::SetColour(float R, float G, float B, float Transparency)
{
	ShaderRef->SetUniforms4f("u_colour", R, G, B , Transparency);

}


//sets the objects coordinates
void Object::SetCoord(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}


// Moves objecct
/*
void Object::Move(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
*/

//Adds this object to the GUI's placment selecter
void Object::AddToListGui()
{
	Objectlist[ObjectCount] = this;
	Objectlist.emplace_back();
	ObjectCount++;
}


//Adds an object location and scale into the draw list
void Object::AddToList(float X, float Y, float Z,float W,float H, float D)
{
	ObjectV3 V3(X, Y, Z, W, H,D);
	DrawIndex.push_back(V3);
}


// inputs for shadertoy compatability go here
void Object::ShaderToy()
{
	ShaderRef->SetUniforms3f("iResolution", (float)Width, (float)Height, (float)Width* (float)Height);
	ShaderRef->SetUniforms1f("iTime", time);
}


//draws this object at each location in the draw list
void Object::DrawList()
{
	//if(ShaderRef->LinkStatus)
	//{
		Bind();
		ShaderToy();

		for (size_t i = 0; i < DrawIndex.size(); i++)
		{
			//std::launch::async, DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z, DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth);
			DrawAt(DrawIndex[i].x, DrawIndex[i].y, DrawIndex[i].z, DrawIndex[i].Width, DrawIndex[i].Height, DrawIndex[i].Depth, MeshInstances);
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

void Object::Remove(int i)
{
	if(DrawIndex.size()!=0)
	DrawIndex.erase(DrawIndex.begin()+i);
}


//sets the texture coordinates for all sizes of a cube
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

//sets the texture coordinates per face of a cube, this is used for objects that dont use the same texture for every size
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

//Gets the texture coordinates of a cube from a texture atlas
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

void Object::MoveInputs(GLFWwindow* window)
{
	
	int x = ObjectDrawList[1]->X;
	int y = ObjectDrawList[1]->Y;
if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && x < 50)
{

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		x++;

		Move(ObjectDrawList[1]->X +=1, ObjectDrawList[1]->Y, 1.0f);
		

	}

}
if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && x > -50)
{

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		x--;
		Move(ObjectDrawList[1]->X -=1, ObjectDrawList[1]->Y, 1.0f);
		

	}

}
if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && y>-50)
{

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		y--;
		Move(ObjectDrawList[1]->X, ObjectDrawList[1]->Y -=1, 1.0f);
		

	}

}
if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && y < 50)
{

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		y++;
		Move(ObjectDrawList[1]->X, ObjectDrawList[1]->X +=1, 1.0f);
	
	}
}


}
