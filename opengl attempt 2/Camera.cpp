#include "Camera.h"

Camera::Camera(double prevTime, glm::vec3 position,unsigned int &Width, unsigned int &Height)
	:PrevTime(prevTime), Position(position),width(Width),height(Height)
{
	
}

void Camera::Matrix(Shader& shader,unsigned int Width, unsigned int Height)
{
	double crntTime = glfwGetTime();
	if (crntTime - PrevTime >= 1.0f / 60.0f)
	{
		increment += 0.5f;
		PrevTime = crntTime;

	}

	View = glm::lookAt(Position, Position + Orientation, Up);
	Projection = glm::perspective(glm::radians(fov), ((float)width /(float)height), 0.1f, 1000.0f);

	shader.UniformMatrix4fv("CamPos", Projection);
	shader.UniformMatrix4fv("CamMat", Projection * View);
}
//bool Sprint = true;
void Camera::inputs(GLFWwindow* window)
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
		//if (Sprint)
		//{
		//	Camera::fov = fov * 1.1;
		//	Sprint = false;
		//}
		speed = 0.2f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
	//	if (!Sprint)
	//	{
	//		Camera::fov = fov / 1.1;
	//		Sprint = true;
	//	}
		speed = 0.05f;
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		//if (Sprint)
		//{
		//	Camera::fov = fov * 1.1;
		//	Sprint = false;
		//}
		speed = 0.005f;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}