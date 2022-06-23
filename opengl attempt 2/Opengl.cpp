#include "LoadShader.cpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <chrono>
#include<future>
#include "VertexArray.h"
#include "Vertexbufferlayout.h"
#include <string>
#include "Textures.h"
#include "LoadShader2.h"
float increment = 0.05f;


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

void colourshuffle(GLfloat& colour)
{
	
	if (colour > 1.0f)
		increment = -0.01f;

	else if (colour < 0.0f)
		increment = 0.01f;
		
	colour += increment;
}

struct gameloop
{
  gameloop(GLFWwindow* window)
	{
		
		
		glClearColor(1.0f, 1.0f, 0.4f, 0.0f);

		
		

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use the shader
		

		glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		
	};
	~gameloop()
	{
	
	};


};




int main()
{

	if (!glfwInit())
	{
		std::cout <<  "Failed to initialize GLFW\n";

	}

	glfwWindowHint(GLFW_SAMPLES, 8); // 8x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // dont use old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; 
	window = glfwCreateWindow(1080, 1080, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout <<  "Failed to open GLFW window.\n";
		glfwTerminate();

	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		std::cout <<  "Failed to initialize GLEW" << std::endl;

	}

	//Escape key to exit the program

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//loading shaders
	//GLuint programID = LoadShaders("vertex.shader", "fragment.shader");

	Shader shader("vertex.shader", "fragment.shader");


	shader.Bind();
	//shader.UnBind();
	

	
	//Vertex Array
	
	float VertexBufferData[] =
	{
	  -0.5f, -0.5f, 0.0f, 0.0f,
	   0.5f, -0.5f, 1.0f, 0.0f,
	   0.5f,  0.5f, 1.0f, 1.0f,
	  -0.5f,  0.5f, 0.0f, 1.0f

	};
/*
	float VertexBufferData[] =
	{
	  -1.0f, -1.0f, 0.0f, 0.0f,
	   1.0f, -1.0f, 1.0f, 0.0f,
	   1.0f,  1.0f, 1.0f, 1.0f,
	  -1.0f,  1.0f, 0.0f, 1.0f

	};
*/
		GLuint Indices[] = {
			0,1,2,
			0,2,3
			
		};

		/*
		GLfloat TextureCoordinates[] =
		{
		   0.0f, 0.0f,
		   1.0f, 0.0f,
		   1.0f, 1.0f,
		   0.0f, 1.0f

		};
*/
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	

		VertexBuffer vb(VertexBufferData, 4 * 4 * sizeof(float));
		//VertexBuffer vb(&VertexBufferData, 4 * 4 * sizeof(GLfloat));
		VertexArray va;
		VertexBufferLayout layout;
		layout.PushFloat(2);
		layout.PushFloat(2);
		va.AddBuffer(vb, layout);
	
		IndexBuffer IB(Indices, sizeof(Indices));;
	
	
		Textures Texture("test2.png");

		
		
		Texture.Bind(0);
		shader.SetUniforms1i("Texture", 0);
		shader.SetUniforms4f("u_colour", 1.0f,0.5f,0.5f,1.0f);
		//shader.SetUniforms2fv("TexCoords2",1, TextureCoordinates);
	do {
		
	
		glClearColor(1.0f, 1.0f, 0.4f, 0.0f);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use the shader
		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		
	} 
	// Check if ESC was pressed or if the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	

}