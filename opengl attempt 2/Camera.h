#pragma once
#include "Header.h"
#include "LoadShader2.h"
#include "Gui.h"

class Camera
{
private:
	//double PrevTime = glfwGetTime();
	double PrevTime;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 0.01f;
	float sensitivity = 100.0f;
	bool firstClick = true;
	float increment = 0;
	


	
public:

	inline static Camera* CamRef;
	double MouseX;
	double MouseY;

	inline static float fov = 90.0f;
	unsigned int& width;
	unsigned int& height;

	glm::mat4 MousePos = glm::mat4(1.0f);
	glm::mat4 Projection = glm::mat4(1.0f);
	glm::mat4 View = glm::mat4(1.0f);

	Camera(unsigned int &Width, unsigned int &Height);
	void Matrix(Shader& shader, unsigned int Width, unsigned int Height);
	void inputs(GLFWwindow* window);
};


