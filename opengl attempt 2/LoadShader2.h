#pragma once
#include "Header.h"

class Shader
{
private:

GLint Result;
int InfoLogLength;
std::unordered_map<std::string, int> CachedLocation;
public:
	unsigned int ID;


	Shader(std::string VertexPath, std::string FragmentPath);
	~Shader();

	void Bind();
	void UnBind();

	void SetUniforms4f(std::string name, float one, float two, float three, float four);
	void SetUniforms1i(std::string name, int value);
	void SetUniforms2fv(std::string name,float one, const float* two);
	const char* CreateShader(std::string ShaderPath);
	unsigned int CompileShader(GLuint ShaderID, const char* ShaderSourcePointer);
	
private:
	int GetUniformLocation(std::string& name);
	int GetUniformLocationnomap(std::string& name);
	void Check(GLuint Checking, GLint& Result, int& InfoLogLength);
};