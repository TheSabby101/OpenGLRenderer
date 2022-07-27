#pragma once
#include "Header.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "LoadShader2.h"
#include "Textures.h"
#include "VAO.h"
#include "Camera.h"


class Object
{
private:
	unsigned int& Width;
	unsigned int& Height;
	unsigned int ID;
	float VertexBufferData[40] =
	{
		// x    y    z							   Texture Coords
		 -0.5f,-0.5f,-0.5f, /* 0 Left  Bottom Back */  0.0f, 0.0f,
		 -0.5f,-0.5f, 0.5f, /* 1 Left  Bottom Front*/  1.0f, 1.0f,
		 -0.5f, 0.5f, 0.5f, /* 2 Left  Top    Front*/  1.0f, 0.0f,
		 -0.5f, 0.5f,-0.5f, /* 3 Left  Top    Back */  0.0f, 1.0f,
		  0.5f,-0.5f,-0.5f, /* 4 Right Bottom Back */  1.0f, 1.0f,
		  0.5f,-0.5f, 0.5f, /* 5 Right Bottom Front*/  0.0f, 1.0f,
		  0.5f, 0.5f, 0.5f, /* 6 Right Top	   Front*/ 0.0f, 0.0f,
		  0.5f, 0.5f,-0.5f, /* 7 Right Top	   Back */ 0.0f, 1.0f

	};

	GLuint Indices[36] = {
			1,2,5,//front face bottomleft
			5,2,6,//front face top right

			2,3,6,//top face bottom left
			6,3,7,//top face top right

			4,5,0,//bottom face bottom left
			0,5,1,//bottom face top right

			0,3,1,//left face bottom left
			1,3,2,//left face top right

			5,6,4,//right face bottom left
			4,6,7,//right face top right

			4,7,3,//bottom face bottom left
			3,4,0 //bottom face top right

	};

public:
	
	//Textures Texture;
	//VertexBuffer vb;
	//VertexArray va;
	//VertexBufferLayout layout;
	//IndexBuffer IB;
	Shader* ShaderRef;
	VAO* object;
	Camera& Cam;
	float X;
	float Y;
	float Z;



	
	
	Object(const char* FilePath, const char* FragmentPath, const char* VertexPath, float x, float y, float z, Camera& CamRef);
	Object(const char* FragmentPath, const char* VertexPath, float x, float y, float z, Camera& CamRef);
	~Object();
	void Bind();
	void SetColour(float R, float G, float B,float Transparency);
	
	void Draw();
	void DrawAt(float X, float Y, float Z);
	void Move(float X, float Y, float Z);




	//void Resize();
};