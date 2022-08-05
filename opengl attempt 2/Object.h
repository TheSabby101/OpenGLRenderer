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
#include "Query.h"
//#include "Gui.h"


class Object
{

//	Query queer;
	
private:
	
	unsigned int& Width;
	unsigned int& Height;
	unsigned int ID;
	//GLuint QID[2];
	//Query RTest;
	
	//GLint any_samples_passed;
	//GLuint Test;
	struct ObjectV3
	{
		float x,y,z;
		float Width, Height, Depth;
		ObjectV3(float inx,float iny,float inz,float inwidth,float inheight, float indepth)
			:x(inx),y(iny),z(inz),Width(inwidth),Height(inheight),Depth(indepth)
		{
			
		}
	};

	std::vector<ObjectV3> DrawIndex;


//  const inline static float VertexBufferData[40] =
//  {
//  	//COMMENTS NEED UPDATING
//  	// x    y    z							   Texture Coords
//  	-0.5f,-0.5f,-0.5f, /* 0 Left  Bottom Back */    0.0f, 0.0f,
//  	 0.5f,-0.5f,-0.5f, /* 1 Left  Bottom Front*/    1.0f, 0.0f,
//  	 0.5f, 0.5f,-0.5f, /* 2 Left  Top    Front*/    1.0f, 1.0f,
//      -0.5f, 0.5f,-0.5f, /* 3 Left  Top    Back */  0.0f, 1.0f,
//       -0.5f,-0.5f, 0.5f, /* 4 Right Bottom Back */ 0.0f, 0.0f,
//       0.5f,-0.5f, 0.5f, /* 5 Right Bottom Front*/  1.0f, 0.0f,
//       0.5f, 0.5f, 0.5f, /* 6 Right Top	   Front*/  1.0f, 1.0f,
//      -0.5f, 0.5f, 0.5f, /* 7 Right Top	   Back */  0.0f, 1.0f
//  
//  
//  
//  
//  
//  
//  
//  };
//  
	const inline static float VertexBufferData[192] =
	{
		//COMMENTS NEED UPDATING
		// x    y    z	    Texture Coords	Normals
		 0.5f,-0.5f, 0.5f,   0.0f, 0.0f,   0.0f,0.5f,0.8f, //bottom right front	   //Front Face
		-0.5f,-0.5f, 0.5f,   0.0f, 1.0f,   0.0f,0.5f,0.8f, //bottom left front	   //Front Face
	    -0.5f, 0.5f, 0.5f,   1.0f, 1.0f,   0.0f,0.5f,0.8f, //top left front		   //Front Face
		 0.5f, 0.5f, 0.5f,   1.0f, 0.0f,   0.0f,0.5f,0.8f, //top right front	   //Front Face

	    -0.5f,-0.5f,-0.5f,   0.0f, 0.0f,   0.0f,0.5f,0.8f, //bottom right back    //Back Face
	     0.5f,-0.5f,-0.5f,   0.0f, 1.0f,   0.0f,0.5f,0.8f, //bottom left back	   //Back Face
	     0.5f, 0.5f,-0.5f,   1.0f, 1.0f,   0.0f,0.5f,0.8f, //top left back		   //Back Face
	    -0.5f, 0.5f,-0.5f,   1.0f, 0.0f,   0.0f,0.5f,0.8f, //top right back	   //Back Face

		 0.5f,-0.5f,-0.5f,   0.0f, 0.0f,   0.0f,0.5f,0.0f, //bottom right back	   //Right Face
		 0.5f,-0.5f, 0.5f,   0.0f, 1.0f,   0.0f,0.5f,0.0f, //bottom right front	   //Right Face
		 0.5f, 0.5f, 0.5f,   1.0f, 1.0f,   0.0f,0.5f,0.0f, //top right front	   //Right Face
		 0.5f, 0.5f,-0.5f,   1.0f, 0.0f,   0.0f,0.5f,0.0f, //top right back	       //Right Face

		-0.5f,-0.5f, 0.5f,   0.0f, 0.0f,   0.0f,0.5f,0.0f, //bottom left front	   //Left Face
		-0.5f,-0.5f,-0.5f,   0.0f, 1.0f,   0.0f,0.5f,0.0f, //bottom left back	   //Left Face
		-0.5f, 0.5f,-0.5f,   1.0f, 1.0f,   0.0f,0.5f,0.0f, //top left back	       //Left Face
		-0.5f, 0.5f, 0.5f,   1.0f, 0.0f,   0.0f,0.5f,0.0f, //top left front	       //Left Face

	    0.5f, 0.5f, 0.5f,    0.0f, 0.0f,   0.0f,1.0f,0.0f, //top right front	   //Top Face
	   -0.5f, 0.5f, 0.5f,    0.0f, 1.0f,   0.0f,1.0f,0.0f, //top left front		   //Top Face
	   -0.5f, 0.5f, -0.5f,   1.0f, 1.0f,   0.0f,1.0f,0.0f, //top left back		   //Top Face
	    0.5f, 0.5f, -0.5f,   1.0f, 0.0f,   0.0f,1.0f,0.0f, //top right back		   //Top Face
    
       -0.5f,-0.5f,-0.5f,    0.0f, 0.0f,   0.0f,-1.0f,0.0f,  //bottom left back	   //Front Face
        0.5f,-0.5f,-0.5f,    0.0f, 1.0f,   0.0f,-1.0f,0.0f, //bottom right back	   //Front Face
        0.5f,-0.5f, 0.5f,    1.0f, 1.0f,   0.0f,-1.0f,0.0f, //bottom right front   //Front Face
       -0.5f,-0.5f, 0.5f,    1.0f, 0.0f,   0.0f,-1.0f,0.0f, //bottom left front	   //Front Face






	};



struct texCoords 
	{
	const float a[2]{0.0, 0.0};
	const float b[2]{ 1.0, 0.0 };
	const float c[2]{ 1.0, 1.0 };
	const float d[2]{ 0.0, 1.0 };
	
	



	};
	float Plane[16] =
	{0.0f,0.0f,		   0.0f, 0.0f,
	 1.0f,0.0f,		   1.0f, 1.0f,
	 1.0f,1.0f,		   1.0f, 0.0f,
	 0.0f,1.0f,		   0.0f, 1.0f
	};

	/*
	inline static const GLuint Indices[36] = {

	0, 1, 3,
	3, 1, 2,

	1, 5, 2,
	2, 5, 6,

	5, 4, 6,
	6, 4, 7,

	4, 0, 7,
	7, 0, 3,

	3, 2, 7,
	7, 2, 6,

	4, 5, 0,
	0, 5, 1

	};
	*/
	inline static const GLuint Indices[36] = {

		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,23,22,
		22,21,20

	};

	GLuint PlaneIndices[6] = {
	1,2,3,
	3,2,4
	};

public:

	inline static double time;
	const char* OBJName;
	unsigned int textureColorbuffer;

	//Textures Texture;
	//VertexBuffer vb;
	//VertexArray va;
	//VertexBufferLayout layout;
	//IndexBuffer IB;
	Shader* ShaderRef;
	VAO* object;
	Camera& Cam;
	

	
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;



	
	
	Object(const char* Name, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef);
		 
	Object(const char* Name, const char* FragmentPath, const char* VertexPath, Camera& CamRef);
	~Object();
	void Bind();
	void SetColour(float R, float G, float B,float Transparency);
	void SetCoord(float X, float Y, float Z);
	void Draw(); 
	void DrawList();
	void DrawAt(float X, float Y, float Z, float W, float H, float D);
	void Move(float X, float Y, float Z);
	void AddToList(float X, float Y, float Z, float W, float H, float D);
	void ShaderToy();

	/////////////////////////////
	////       Old Code		/////
	////////////////////////////
	//void GenQueries();
	//int Begin();
	//void End();
};