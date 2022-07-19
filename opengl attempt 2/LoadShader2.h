#pragma once
#include "Header.h"


class Shader
{
private:

	GLint LinkStatus;

std::unordered_map<std::string, int> CachedLocation;
public:
	
	unsigned int ID;

	Shader(std::string VertexPath, std::string FragmentPath);
	~Shader();

	void Bind();
	void UnBind();

	void SetUniforms4f(std::string name, float one, float two, float three, float four);
	void UniformMatrix4fv(std::string name, glm::mat4 type);
	void SetUniforms1i(std::string name, int value);
	void SetUniforms2fv(std::string name,float one, const float* two);
	const char* CreateShader(std::string ShaderPath);
	unsigned int CompileShader(GLuint ShaderID, const char* ShaderSourcePointer);
	void SetUniforms3f(std::string name, float one, float two, float three);

private:
	int GetUniformLocation(std::string& name);
	int GetUniformLocationnomap(const std::string& name);
};