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


class Object
{

//	Query queer;
	
private:
	


	enum BlockFace { Southface,Northface,Eastface,Westface,Topface,Bottomface};



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

public:
	
	
	inline static float AtlasX, AtlasY;
	inline static float AtlasSize = 256.0f;
	inline static float TextureSize = 16.0f;

	inline static float VertexBufferData[192]
	{
		
		// X    Y    z							 Texture Coords													Normals
		 0.5f,-0.5f, 0.5f,    AtlasX* TextureSize / AtlasSize,AtlasY*TextureSize / AtlasSize,  				 0.0f,0.5f,0.8f, //bottom right front //Front Face	 
		-0.5f,-0.5f, 0.5f,   (AtlasX + 1)*TextureSize / AtlasSize,AtlasY* TextureSize/AtlasSize, 			 0.0f,0.5f,0.8f, //bottom left front	//Front Face 
		-0.5f, 0.5f, 0.5f,   (AtlasX + 1)*TextureSize / AtlasSize,(AtlasY+1)*TextureSize/AtlasSize,			 0.0f,0.5f,0.8f, //top left front	 //Front Face	 
		 0.5f, 0.5f, 0.5f,    AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize/AtlasSize, 			 0.0f,0.5f,0.8f, //top right front	   //Front Face	 

	    -0.5f,-0.5f,-0.5f,    AtlasX* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize,  			 0.0f,0.5f,0.8f, //bottom right back    //Back Face
		 0.5f,-0.5f,-0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize, 		 0.0f,0.5f,0.8f, //bottom left back	   //Back Face
		 0.5f, 0.5f,-0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,	 0.0f,0.5f,0.8f, //top left back		   //Back Face
		-0.5f, 0.5f,-0.5f,    AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,		 0.0f,0.5f,0.8f, //top right back	   //Back Face

		 0.5f,-0.5f,-0.5f,    AtlasX* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize,  			 0.0f,0.5f,0.0f, //bottom right back	   //Right Face
		 0.5f,-0.5f, 0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize, 		 0.0f,0.5f,0.0f, //bottom right front	   //Right Face
		 0.5f, 0.5f, 0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize, 	 0.0f,0.5f,0.0f, //top right front	   //Right Face
		 0.5f, 0.5f,-0.5f,    AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,	 	 0.0f,0.5f,0.0f, //top right back	       //Right Face

		-0.5f,-0.5f, 0.5f,    AtlasX* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize,  		 	 0.0f,0.5f,0.0f, //bottom left front	   //Left Face
		-0.5f,-0.5f,-0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize, 	 	 0.0f,0.5f,0.0f, //bottom left back	   //Left Face
		-0.5f, 0.5f,-0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize, 	 0.0f,0.5f,0.0f, //top left back	       //Left Face
		-0.5f, 0.5f, 0.5f,    AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,	 	 0.0f,0.5f,0.0f, //top left front	       //Left Face

	    0.5f, 0.5f, 0.5f,     AtlasX* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize,  		 	 0.0f,1.0f,0.0f, //top right front	   //Top Face
	   -0.5f, 0.5f, 0.5f,    (AtlasX + 1)* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize, 	 	 0.0f,1.0f,0.0f, //top left front		   //Top Face
	   -0.5f, 0.5f, -0.5f,   (AtlasX + 1)* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize, 	 0.0f,1.0f,0.0f, //top left back		   //Top Face
		0.5f, 0.5f, -0.5f,    AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,	 	 0.0f,1.0f,0.0f, //top right back		   //Top Face
		
       -0.5f,-0.5f,-0.5f,     AtlasX* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize,  		 	 0.0f,-1.0f,0.0f,  //bottom left back	   //Bottom Face
		0.5f,-0.5f,-0.5f,    (AtlasX + 1)* TextureSize / AtlasSize,AtlasY* TextureSize / AtlasSize, 	 	 0.0f,-1.0f,0.0f, //bottom right back	   //Bottom Face
		0.5f,-0.5f, 0.5f,    (AtlasX + 1)* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize, 	 0.0f,-1.0f,0.0f, //bottom right front      //Bottom Face
	   -0.5f,-0.5f, 0.5f,     AtlasX* TextureSize / AtlasSize,(AtlasY + 1)* TextureSize / AtlasSize,	 	 0.0f,-1.0f,0.0f, //bottom left front	   //Bottom Face
	};

	inline static float VertexBufferDataNoAtlas[192]
	{

		// X    Y    z							 Texture Coords													Normals
		 0.5f,-0.5f, 0.5f,   0.0f, 0.0f,    	 0.0f,0.5f,0.8f, //bottom right front //Front Face	 
		-0.5f,-0.5f, 0.5f,   1.0f, 0.0f,    	 0.0f,0.5f,0.8f, //bottom left front	//Front Face 
		-0.5f, 0.5f, 0.5f,   1.0f, 1.0f,    		 0.0f,0.5f,0.8f, //top left front	 //Front Face	 
		 0.5f, 0.5f, 0.5f,   0.0f, 1.0f,    	 0.0f,0.5f,0.8f, //top right front	   //Front Face	 
							    
		-0.5f,-0.5f,-0.5f,   0.0f, 0.0f,     0.0f,0.5f,0.8f, //bottom right back    //Back Face
		 0.5f,-0.5f,-0.5f,   1.0f, 0.0f,     0.0f,0.5f,0.8f, //bottom left back	   //Back Face
		 0.5f, 0.5f,-0.5f,   1.0f, 1.0f,     0.0f,0.5f,0.8f, //top left back		   //Back Face
		-0.5f, 0.5f,-0.5f,   0.0f, 1.0f,     0.0f,0.5f,0.8f, //top right back	   //Back Face
							    
		 0.5f,-0.5f,-0.5f,   0.0f, 0.0f,     0.0f,0.5f,0.0f, //bottom right back	   //Right Face
		 0.5f,-0.5f, 0.5f,   1.0f, 0.0f,     0.0f,0.5f,0.0f, //bottom right front	   //Right Face
		 0.5f, 0.5f, 0.5f,   1.0f, 1.0f,    	 0.0f,0.5f,0.0f, //top right front	   //Right Face
		 0.5f, 0.5f,-0.5f,   0.0f, 1.0f,     0.0f,0.5f,0.0f, //top right back	       //Right Face
							    
		-0.5f,-0.5f, 0.5f,   0.0f, 0.0f,     0.0f,0.5f,0.0f, //bottom left front	   //Left Face
		-0.5f,-0.5f,-0.5f,   1.0f, 0.0f,     0.0f,0.5f,0.0f, //bottom left back	   //Left Face
		-0.5f, 0.5f,-0.5f,   1.0f, 1.0f,    	 0.0f,0.5f,0.0f, //top left back	       //Left Face
		-0.5f, 0.5f, 0.5f,   0.0f, 1.0f,     0.0f,0.5f,0.0f, //top left front	       //Left Face
							     
		0.5f, 0.5f, 0.5f,    0.0f, 0.0f,     0.0f,1.0f,0.0f, //top right front	   //Top Face
	   -0.5f, 0.5f, 0.5f,    1.0f, 0.0f,     0.0f,1.0f,0.0f, //top left front		   //Top Face
	   -0.5f, 0.5f, -0.5f,   1.0f, 1.0f,    	 0.0f,1.0f,0.0f, //top left back		   //Top Face
		0.5f, 0.5f, -0.5f,   0.0f, 1.0f,     0.0f,1.0f,0.0f, //top right back		   //Top Face
							   
	   -0.5f,-0.5f,-0.5f,    0.0f, 0.0f,     0.0f,-1.0f,0.0f,  //bottom left back	   //Bottom Face
		0.5f,-0.5f,-0.5f,    1.0f, 0.0f,     0.0f,-1.0f,0.0f, //bottom right back	   //Bottom Face
		0.5f,-0.5f, 0.5f,    1.0f, 1.0f,    	 0.0f,-1.0f,0.0f, //bottom right front      //Bottom Face
	   -0.5f,-0.5f, 0.5f,    0.0f, 1.0f,     0.0f,-1.0f,0.0f, //bottom left front	   //Bottom Face
	};


struct texCoords 
	{
	const float a[2] {0.0, 0.0};
	const float b[2]{ 1.0, 0.0 };
	const float c[2]{ 1.0, 1.0 };
	const float d[2]{ 0.0, 1.0 };
	
	



	};


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

	float Plane[16] =
	{ 0.0f,0.0f,		   0.0f, 0.0f,
	 1.0f,0.0f,		   1.0f, 1.0f,
	 1.0f,1.0f,		   1.0f, 0.0f,
	 0.0f,1.0f,		   0.0f, 1.0f
	};

	GLuint PlaneIndices[6] = {
	0,1,2,
	2,3,0,
	};



	inline static enum Block { grass, dirt, sand,craftingbench,furnace,lava};

	std::vector<ObjectV3> DrawIndex;
	inline static std::vector<Object*> Objectlist{ 0 };
	inline static int ObjectCount = 0;
	inline static double time;
	inline static std::vector< Object*> ObjectDrawList;
	inline static std::vector< Object*> BatchDrawIndex;


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



	unsigned int MeshInstances = 0;
	std::vector<ObjectV4> InstanceCoordinates{};


	Object(const char* Name, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef);
	Object(const char* Name,Block blocktype, const char* FilePath, const char* FragmentPath, const char* VertexPath, Camera& CamRef);
	Object(const char* Name, const char* FragmentPath, const char* VertexPath, Camera& CamRef);
	~Object();
	void Bind();

	void SetColour(float R, float G, float B,float Transparency);
	void SetCoord(float X, float Y, float Z);

	void Draw(); 
	void DrawList();
	void Remove(int i);
	void BatchDraw();
	void BatchAddToList(float X, float Y, float Z);
	void BatchRemove(int i);
	void DrawAt(float X, float Y, float Z, float W, float H, float D);

	

	void AddToListGui();
	void AddToList(float X, float Y, float Z, float W, float H, float D);

	void ShaderToy();
	void AtlasMapper();
	void AtlasMapperPerFace(BlockFace);
	void GetBlockType(Block blocktype);

	inline static void Move(float X, float Y, float Z);
	inline static void MoveInputs(GLFWwindow* window);
};


