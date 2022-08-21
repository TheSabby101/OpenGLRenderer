#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Vertexbufferlayout.h"
#include "Textures.h"
#include "LoadShader2.h"
#include "VAO.h"
#include "Error.h"
#include "Camera.h"
#include "Gui.h"
GLint Query::any_samples_passed;
GLuint Query::Test[2];
static int ScreenWidth = 720;
static int ScreenHeight = 720;
int objectcount = 0;




//std::vector<GLfloat> OBJImport(std::string objfilepath)
//{
//	vec3F Temp(0, 0, 0);
//	int i = 0;
//	//reading from the OBJ file
//	std::string line = "";
//	std::string prefix = "";
//	std::string OBJ;
//	std::ifstream OBJStream(objfilepath);
//	std::vector<GLfloat> Verticies;
//	
//	if (OBJStream.is_open())
//	{
//		std::cout << objfilepath << " Opened" << std::endl;
//	
//		std::stringstream sstr;
//	//sstr << OBJStream.rdbuf();
//		//OBJ = sstr.str();
//		
//		while (std::getline(OBJStream, line))
//		{
//			
//			sstr.clear();
//			sstr.str(line);
//			sstr >> prefix;
//
//			if (prefix == "#")
//			{
//
//			}
//			else if (prefix == "o")
//			{
//
//			}
//			else if (prefix == "s")
//			{
//
//			}
//			else if (prefix == "vn")
//			{
//				sstr >> Temp.x >> Temp.y >> Temp.z;
//				Verticies.push_back(Temp.x);
//				Verticies.push_back(Temp.y);
//				Verticies.push_back(Temp.z);
//				//std::cout << Verticies[0+ i] << std::endl;
//				//std::cout << Verticies[1+ i] << std::endl;
//				//std::cout << Verticies[2+ i] << std::endl;
//				//std::cout << line << std::endl;
//				i += 3;
//			}
//			else
//			{
//
//			}
//			
//		}
//
//		OBJStream.close();
//	}
//	else
//	{
//		std::cout << "could not open obj at " << objfilepath << std::endl;
//	}
//
//	//converting the Verticies of the OBJ into a usable vector
//
//
//	
//
//
//	return Verticies;
//}

void DrawAll()
{
	for (size_t i = 0; i < Object::ObjectDrawList.size(); i++)
	{
		Object::ObjectDrawList[i]->DrawList();

	}

}
void BatchDrawAll()
{
	for (size_t i = 0; i < Object::BatchDrawIndex.size(); i++)
	{
		Object::BatchDrawIndex[i]->BatchDraw();
	}
}

int main()
{

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";

	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // dont use old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(ScreenWidth, ScreenHeight, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window.\n";
		glfwTerminate();

	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glfwSwapInterval(0);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;

	}


	//Escape key to exit the program

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//float screenspace = 0;


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//std::cout << GL_MAX_DRAW_BUFFERS << std::endl; std::cout << GL_DRAW_BUFFER << std::endl;


	glEnable(GL_DEPTH_TEST);

	Camera Camera((unsigned int&)ScreenWidth, (unsigned int&)ScreenHeight);



	//const wchar_t* path = L"res/DebugFolder/rat.wav";
	//PlaySound(path,NULL,SND_ASYNC);


	MyGui gui(window, (unsigned int&)ScreenWidth, (unsigned int&)ScreenHeight);

	Object Grass("Grass", Object::grass, "res/Atlas.png", "Shaders/fragment.frag", "Shaders/vertex.vert");
	Object Sand("Sand", Object::sand, "res/Atlas.png", "Shaders/fragment.frag", "Shaders/vertex.vert");
	Object CraftingBench("CraftingBench", Object::craftingbench, "res/Atlas.png", "Shaders/fragment.frag", "Shaders/vertex.vert");
	Object Furnace("Furnace", Object::furnace, "res/Atlas.png", "Shaders/fragment.frag", "Shaders/vertex.vert");
	Object Lava("Lava", Object::lava, "res/Atlas.png", "Shaders/fragment.frag", "Shaders/vertex.vert");
	Object LightingTest("LightingTest", "Shaders/LightingFragment.frag", "Shaders/LightingVertex.vert");
	Object Sphere("Sphere", "Shaders/SphereFrag.frag", "Shaders/SphereVertex.vert");
	Object Cube("Cube", "res/DebugFolder/test5.png", "Shaders/fragment.frag", "Shaders/vertex.vert");

		for (int y = -1; y < 0; y++)
		{
			for (int z = -16; z< 16; z++)
			{
				for (int x = -16; x < 16; x++)
				{


					//Cube2.AddToList(x, y, z,1,1,1);
					//Lava.AddToList(x, y, z, 1, 1, 1);
					//LightingTest.AddToList(x, y, z, 1, 1, 1);
					Grass.BatchAddToList(x, y, z);
				}
			}
		}
	

		for (int y = -10; y < -1; y++)
		{
			for (int z = -16; z < 16; z++)
			{
				for (int x = -16; x < 16; x++)
				{
					//Sand.BatchAddToList(x, y, z);
				}
			}
		}

		for (int y = -20; y < -10; y++)
		{
			for (int z = -16; z < 16; z++)
			{
				for (int x = -16; x < 16; x++)
				{
					//Lava.BatchAddToList(x, y, z);
				}
			}
		}

		do {
//			Recieving the loop duration for shader uniforms
			Object::time = glfwGetTime();
			
//			Clear the screen.
			glClearColor(0.25f, 0.4f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//			Poll Camera Inputs
			Camera.inputs(window);

//			ImGui Windows
			gui.Init();
			gui.MakeWindow();
			//gui.MakeViewport();
			
//			Draw all non batch objects
			//std::launch::async, DrawAll();

//			Draw batch objects
			BatchDrawAll();

//			ImGui Window Terminator
			gui.render();
	
//			Swap buffers
			glfwPollEvents();
			glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);
			glfwGetWindowSize(window,&ScreenWidth,&ScreenHeight);
			glViewport(0, 0, ScreenWidth, ScreenHeight);
			glfwSwapBuffers(window);
		} 
//	Check if ESC was pressed or if the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
		
}