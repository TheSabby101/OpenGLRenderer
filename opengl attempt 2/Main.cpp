
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



int width = 1080;
int height = 1080;
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
	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
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
	


		double prevTime = glfwGetTime();
		Camera Camera(prevTime, glm::vec3(0.0f, 0.0f, 2.0f), width, height);
		Object Cube("res/test4.png", "Shaders/fragment.shader", "Shaders/vertex.shader", 1.0, 1.0f, 1.0f, Camera);
		Object Cube2("res/test4.png", "Shaders/LightFrag.shader", "Shaders/LightVertex.shader", 0.0f, 0.0f, 0.0f, Camera);
	
		Cube2.SetColour(0.0f, 1.0f, 1.0f, 0.5f);
	
		const wchar_t* path = L"res/rat.wav";
		//PlaySound(path,NULL,SND_ASYNC);

		
		glEnable(GL_DEPTH_TEST);
		
		
		
		int x = 1;
		int y = 1;
		do {

			glClearColor(0.3f, 0.3f, 0.4f, 0.0f);

			// Clear the screen.
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			
			Camera.inputs(window);
		
			Cube2.Bind();

			for (int z = 0; z < 1; z++)
			{
				for (int y = 0; y < 5; y++)
				{
					for (int x = 0; x < 5; x++)
					{
						Cube2.Draw(width,height);
						Cube2.Move(x, y, z);
					}
				}
			}
			Cube.Bind();
			for (int i = 0; i < x; i++)
			{
				Cube.Draw(width, height);
				Cube.Move(x, y, 1.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && x < 4)
			{
				
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
				{
					x++;
					
					Cube.Move(x, y, 1.0f);
					Cube.Draw(width, height);
				
				}
					
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && x > 0)
			{

				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
				{
					x--;
					Cube.Move(x, y, 1.0f);
					Cube.Draw(width, height);

				}

			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && y>0)
			{

				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
				{
					y--;
					Cube.Move(x, y, 1.0f);
					Cube.Draw(width, height);

				}

			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && y < 4)
			{

				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
				{
					y++;
					Cube.Move(x, y, 1.0f);
					Cube.Draw(width, height);

		

				}
			}
		 // Swap buffers
		 glfwSwapBuffers(window);
	     glfwPollEvents();
		 glfwGetWindowSize(window,&width,&height);
		 glViewport(0, 0, width, height);
		} 
	// Check if ESC was pressed or if the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}