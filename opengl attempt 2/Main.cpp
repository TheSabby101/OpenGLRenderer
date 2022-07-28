#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Vertexbufferlayout.h"
#include "Textures.h"
#include "LoadShader2.h"
#include "VAO.h"
#include "Error.h"
#include "Object.h"
#include "Camera.h"
#include "Gui.h"


int ScreenWidth = 1080;
int ScreenHeight = 1080;
int objectcount = 0;

struct vec3F
{
	float x, y, z;
	vec3F(float a, float b, float c)
	{

		x = a;
		y = b;
		z = c;

	}
	
};


std::vector<GLfloat> OBJImport(std::string objfilepath)
{
	vec3F Temp(0, 0, 0);
	int i = 0;
	//reading from the OBJ file
	std::string line = "";
	std::string prefix = "";
	std::string OBJ;
	std::ifstream OBJStream(objfilepath);
	std::vector<GLfloat> Verticies;
	
	if (OBJStream.is_open())
	{
		std::cout << objfilepath << " Opened" << std::endl;
	
		std::stringstream sstr;
	//sstr << OBJStream.rdbuf();
		//OBJ = sstr.str();
		
		while (std::getline(OBJStream, line))
		{
			
			sstr.clear();
			sstr.str(line);
			sstr >> prefix;

			if (prefix == "#")
			{

			}
			else if (prefix == "o")
			{

			}
			else if (prefix == "s")
			{

			}
			else if (prefix == "vn")
			{
				sstr >> Temp.x >> Temp.y >> Temp.z;
				Verticies.push_back(Temp.x);
				Verticies.push_back(Temp.y);
				Verticies.push_back(Temp.z);
				//std::cout << Verticies[0+ i] << std::endl;
				//std::cout << Verticies[1+ i] << std::endl;
				//std::cout << Verticies[2+ i] << std::endl;
				//std::cout << line << std::endl;
				i += 3;
			}
			else
			{

			}
			
		}

		OBJStream.close();
	}
	else
	{
		std::cout << "could not open obj at " << objfilepath << std::endl;
	}

	//converting the Verticies of the OBJ into a usable vector


	


	return Verticies;
}




int main()
{

	if (!glfwInit())
	{
		std::cout <<  "Failed to initialize GLFW\n";

	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // dont use old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; 
	window = glfwCreateWindow(ScreenWidth, ScreenHeight, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout <<  "Failed to open GLFW window.\n";
		glfwTerminate();

	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	//glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout <<  "Failed to initialize GLEW" << std::endl;

	}
	
	
	//Escape key to exit the program

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	float screenspace = 0;


		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	
		
		glEnable(GL_DEPTH_TEST);
		double prevTime = glfwGetTime();
		Camera Camera(prevTime, glm::vec3(0.0f, 0.0f, 2.0f), (unsigned int&)ScreenWidth,(unsigned int&)ScreenHeight);
		MyGui gui(window);
		Object Cube("res/test4.png", "Shaders/fragment.shader", "Shaders/vertex.shader", Camera);
		
		Object Cube2("Shaders/LightFrag.shader", "Shaders/LightVertex.shader", Camera);
		Cube2.SetColour(0.6f, 0.3f, 0.4f, 1.0f);
		Cube2.SetCoord(0.0f, 0.0f, -1.0f);
		Object Cube3("res/test2.png", "Shaders/fragment.shader", "Shaders/vertex.shader", Camera);
		Cube3.SetColour(1.0f, 1.0f, 0.0f, 0.5f);
		Object Cube4("res/test.png", "Shaders/fragment.shader", "Shaders/vertex.shader", Camera);

		//Object Sphere("Shaders/SphereFrag.shader", "Shaders/SphereVertex.shader", 0.0f, 0.0f, 0.0f, Camera);
	//	Sphere.ShaderRef->SetUniforms2f("Res", 1080.0f, 1080.0f);
	
		const wchar_t* path = L"res/rat.wav";
		//PlaySound(path,NULL,SND_ASYNC);


	
	
		
		
		int x = 1;
		int y = 1;

		for (int z = -1; z < 0; z++)
		{
			for (int y = -50; y < 50; y++)
			{
				for (int x = -50; x < 50; x++)
				{


					Cube2.AddToList(x, y, z);

				}
			}
		}

		gui.AddToList(&Cube);
		gui.AddToList(&Cube2);
		gui.AddToList(&Cube3);
		gui.AddToList(&Cube4);


		do {
			gui.Render();

			glClearColor(0.3f, 0.3f, 0.4f, 0.0f);

			// Clear the screen.
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			
			Camera.inputs(window);
			Cube3.Bind();
			Cube3.DrawAt(0.0f, 0.0f, 5.0f);

			Cube.Bind();
			Cube.Draw();
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && x < 50)
			{
				
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
				{
					x++;
					
					Cube.Move(Cube.X+=1, Cube.Y, 1.0f);
					Cube.Draw();
				
				}
					
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && x > -50)
			{

				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
				{
					x--;
					Cube.Move(Cube.X-=1, Cube.Y, 1.0f);
					Cube.Draw();

				}

			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && y>-50)
			{

				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
				{
					y--;
					Cube.Move(Cube.X, Cube.Y-=1, 1.0f);
					Cube.Draw();

				}

			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && y < 50)
			{

				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
				{
					y++;
					Cube.Move(Cube.X, Cube.Y+=1, 1.0f);
					Cube.Draw();

		

				}
			}



			
			Cube.DrawList();
			Cube3.DrawList();
			Cube2.DrawList();
			Cube4.DrawList();

			Cube3.Bind();
			Cube3.Draw();



		 // Swap buffers
		
	     glfwPollEvents();
		// glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);
		 glfwGetWindowSize(window,&ScreenWidth,&ScreenHeight);
		 glViewport(0, 0, ScreenWidth, ScreenHeight);
		 gui.RenderEnder();
		 glfwSwapBuffers(window);
		} 
	// Check if ESC was pressed or if the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}