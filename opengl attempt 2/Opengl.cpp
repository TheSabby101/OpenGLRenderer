#include "LoadShader.cpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <chrono>
#include<future>
#include "VertexArray.h"
float increment = 0.05f;

void colourshuffle(float& colour)
{
	
	if (colour > 1.0f)
		increment = -0.01f;

	else if (colour < 0.0f)
		increment = 0.01f;
		
	colour += increment;
}
class gameloop
{
private:
	
public:



	void framecount(int& frames)
	{
		frames++;
		//std::cout << std::endl << frames << std::endl;

	}




	gameloop(int uniform, int programid, GLFWwindow *window, float one, float two, float three, float four)
	{
		
		
		glClearColor(1.0f, 1.0f, 0.4f, 0.0f);
		glUniform4f(uniform, one, two, three, four);
		//one += 0.001f;
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programid);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		//std::cout << one<< std::endl;
		
	};
	~gameloop()
	{
	
	};


};


void EnableVertexArray(int arraynumber, GLuint arraybuffername) {
	// 1st attribute buffer : vertices

}



int main() {
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
       
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	GLuint programID = LoadShaders("vertex.shader", "fragment.shader");


	// An array of 3 vectors which represents 3 vertices
	GLfloat g_vertex_buffer_data[] = {
	   -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	   0.5f,  0.5f, 0.0f,
	   -0.5f,0.5f,0.0f
	};

	GLuint indices[] = {
		0,1,2,
		2,3,0



	};

VertexBuffer VB(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
VertexArray va;
VertexBuffer vb(g_vertex_buffer_data, 4*sizeof(indices));
VertexBufferLayout layout;
layout.Push<float>(3);
va.AddBuffer(vb,layout);




	IndexBuffer IB(indices, 6);
	
	GLint Myuniform = 0;
	
		
	//glClearColor(0.0f, 0.1f, 0.4f, 0.0f);
	//float one = 0.0f;
	int frames = 0;
	double ms = 0;
	float one = 0.5f;
	float two = 0.0f;
	float three = 0.1f;
	float four = 0.0f;
	va.Bind();
	//vb.Bind();
	do {
		
		gameloop Loop(Myuniform, programID, window, one, two, three, four);
		Loop.framecount(frames);
	
		colourshuffle(one);
		colourshuffle(two);
		colourshuffle(three);
		//colourshuffle(four);
		
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	

}