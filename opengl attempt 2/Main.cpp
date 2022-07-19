
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "Vertexbufferlayout.h"

#include "Textures.h"
#include "LoadShader2.h"
#include "VAIO.h"
#include "Error.h"


float increment = 0;
const unsigned int width = 1080;
const unsigned int height = 1080;
int objectcount = 0;




/*
struct camera
{
	double PrevTime;
	camera(double prevTime)
		:PrevTime(prevTime)
	{}
	void update(Shader& shader)
	{



		double crntTime = glfwGetTime();
		if (crntTime - PrevTime >= 1.0 / 60.0)
		{
			increment += 0.5f;
			PrevTime = crntTime;

		}
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 Projection = glm::mat4(1.0f);
		glm::mat4 View = glm::mat4(1.0f);



		Model = glm::rotate(Model, glm::radians(increment), glm::vec3(0.5f, 1.0f, 0.3f));
		View = glm::translate(View, glm::vec3(0.0f, 0.0f, -2.5f));
		Projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);


		shader.UniformMatrix4fv("Model", Model);
		shader.UniformMatrix4fv("Projection", Projection);
		shader.UniformMatrix4fv("View", View);


	}


};
*/

struct camera
{
	double PrevTime;
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 0.01f;
	float sensitivity = 100.0f;
	bool firstClick = true;
	camera(double prevTime, glm::vec3 position)
		:PrevTime(prevTime),Position(position)
	{
	
	}

	void Matrix(Shader& shader)
	{



		double crntTime = glfwGetTime();
		if (crntTime - PrevTime >= 1.0 / 60.0)
		{
			increment += 0.5f;
			PrevTime = crntTime;

		}

	
		glm::mat4 Projection = glm::mat4(1.0f);
		glm::mat4 View = glm::mat4(1.0f);




		View = glm::lookAt(Position, Position + Orientation, Up);
		Projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		shader.UniformMatrix4fv("CamMat", Projection*View);


	}

	void inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Position += speed * Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		}	
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Position += speed * -Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Position += speed * Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			Position += speed * -Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 0.2f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = 0.05f;
		}



		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

			// Calculates upcoming vertical change in the Orientation

			
			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Orientation = newOrientation;
			}

			// Rotates the Orientation left and right
			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		
			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}





	}
};


class object
{
private:
	unsigned int ID;


public:

	object(int input)
		:ID(objectcount+1)
	{

		switch (input)
		{
		case 0: Cube(); break;
		case 1: Cube(); break;
		case 2: Cube(); break;
		}

	}
	~object()
	{

	}

	void Cube()
	{
		objectcount++;
		float VertexBufferData[] =
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

		GLuint Indices[] = {
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
		VertexBuffer vb(VertexBufferData, sizeof(VertexBufferData) * 4);

		VertexArray va;
		VertexBufferLayout layout;
		layout.PushFloat(3);
		layout.PushFloat(2);
		vb.Bind();
		va.Bind();

		va.AddBuffer(vb, layout);

		IndexBuffer IB(Indices, sizeof(Indices));;

		Shader shader("Shaders/vertex.shader", "Shaders/fragment.shader");

		Textures Texture("res/test4.png");

		shader.Bind();
		Texture.Bind();

		shader.SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.SetUniforms1i("Texture", 0);

	}



	


};





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

	
	float VertexBufferData[] =
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

	float VertexBufferDatalight[] =
	{
		// x    y    z		
		 -0.5f,-0.5f,-0.5f, 	   
		 -0.5f,-0.5f, 0.5f, 	   
		 -0.5f, 0.5f, 0.5f, 	   
		 -0.5f, 0.5f,-0.5f, 	   
		  0.5f,-0.5f,-0.5f, 	   
		  0.5f,-0.5f, 0.5f, 	   
		  0.5f, 0.5f, 0.5f, 	   
		  0.5f, 0.5f,-0.5f 		

	};

	GLuint Indices[] = {
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
	GLuint LightIndices[] = {
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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	

		//LOOK HERE
		VertexBuffer vb(VertexBufferData, sizeof(VertexBufferData) * 4);
		VertexArray va;
		VertexBufferLayout layout;
		layout.PushFloat(3);
		layout.PushFloat(2);
		vb.Bind();
		va.Bind();
		va.AddBuffer(vb, layout);
		IndexBuffer IB(Indices, sizeof(Indices));;
		Shader shader("Shaders/vertex.shader", "Shaders/fragment.shader");
		Textures Texture("res/test4.png");
	    shader.Bind();
		Texture.Bind();
		shader.SetUniforms4f("u_colour", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.SetUniforms1i("Texture", 0);
		shader.SetUniforms3f("coordinates", 1.0f, 1.0f, 2.0f);
		VAIO ObjectOne(vb,va,shader,Texture);

		vb.Unbind();
		va.Unbind();
		shader.UnBind();



		double prevTime = glfwGetTime();
		const wchar_t* path = L"res/rat.wav";
		PlaySound(path,NULL,SND_ASYNC);

		VertexBuffer lightBuffer(VertexBufferDatalight, sizeof(VertexBufferDatalight)*4);
		VertexArray LightArray;
		VertexBufferLayout LightLayout;
		LightLayout.PushFloat(3);
		//LightLayout.PushFloat(2);
		lightBuffer.Bind();
		LightArray.Bind();
		IndexBuffer LightIndexBuffer(LightIndices, sizeof(LightIndices));;
		LightArray.AddBuffer(lightBuffer, LightLayout);
		Shader shaderlight("Shaders/LightVertex.shader", "Shaders/LightFrag.shader");
		shaderlight.Bind();
		shaderlight.SetUniforms4f("u_colour", 0.0f, 0.5f, 1.0f, 0.8f);
		shaderlight.SetUniforms3f("coordinates", 0.0f, 0.0f, 1.0f);
		VAIO ObjectTwo(lightBuffer, LightArray, shaderlight, Texture);

		lightBuffer.Unbind();
		LightArray.Unbind();
		shaderlight.UnBind();
	

		
		glEnable(GL_DEPTH_TEST);
		camera Camera(prevTime, glm::vec3(0.0f,0.0f,2.0f));


		
	do {
		
		
		glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
		
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		ObjectOne.Bind();
		Camera.inputs(window);
		Camera.Matrix(shader);
		glDrawElements(GL_TRIANGLES, sizeof(Indices)/ sizeof(int), GL_UNSIGNED_INT, nullptr);
		//ObjectOne.UnBind();



		ObjectTwo.Bind();
		Camera.Matrix(shaderlight);
		glDrawElements(GL_TRIANGLES, sizeof(LightIndices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
		//ObjectTwo.UnBind();
	
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	
		
	} 
	// Check if ESC was pressed or if the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}