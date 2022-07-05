#pragma once
#include "Header.h"




// Error checking function
inline void Check(GLuint Checking, GLint &Result, int &InfoLogLength)
{
	glGetProgramiv(Checking, GL_LINK_STATUS, &Result);
	glGetProgramiv(Checking, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		static std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(Checking, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}
}



inline GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open." << std::endl << vertex_file_path << std::endl;
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		std::cout << "Impossible to open." << std::endl << fragment_file_path << std::endl;
		return 0;
	}



	GLint Result = GL_FALSE;
	int InfoLogLength;


	//converting from a string to a c_string
	char const* VertexSourcePointer = VertexShaderCode.c_str();

	// Compile Vertex Shader
	std::cout << "Compiling shader :" << std::endl << vertex_file_path << std::endl;

	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	Check(VertexShaderID, Result, InfoLogLength);

	//converting from a string to a c_string
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();

	// Compile Fragment Shader
	std::cout << "Compiling shader :" << std::endl << fragment_file_path << std::endl;
	
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	Check(FragmentShaderID, Result, InfoLogLength);

	// Link the program
	std::cout << "Linking program" << std::endl;
	
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	Check(ProgramID,Result,InfoLogLength);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
