#include "LoadShader2.h"


Shader::Shader(std::string VertexPath, std::string FragmentPath)
	:ID(glCreateProgram())

{

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(CompileShader(VertexShaderID, CreateShader(VertexPath)));

	GLCall(CompileShader(FragmentShaderID, CreateShader(FragmentPath)));

	glAttachShader(ID, VertexShaderID);

	glAttachShader(ID, FragmentShaderID);

	GLCall(glLinkProgram(ID));

	//Check(VertexShaderID, Result, InfoLogLength);
	//Check(FragmentShaderID, Result, InfoLogLength);

	//glDetachShader(ID, VertexShaderID);
	//glDetachShader(ID, FragmentShaderID);

	//glDeleteShader(VertexShaderID);
    //glDeleteShader(FragmentShaderID);
	
	
}

Shader::~Shader()
{
	UnBind();
	std::cout << "destroyed shader " << glGetError() << std::endl;
	glDeleteProgram(ID);
}

void Shader::Bind()
{
	GLint CompileStatus = 0;
	GLint LinkStatus = 0;
	
	glGetProgramiv(ID, GL_LINK_STATUS, &LinkStatus);
	glGetShaderiv(ID, GL_COMPILE_STATUS, &CompileStatus);
	std::cout << "binding shader " << &ID << std::endl;
	std::cout << CompileStatus << std::endl << LinkStatus << std::endl;


	


	//GLCall(glUseProgram(ID));
	glUseProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &LinkStatus);
	glGetShaderiv(ID, GL_COMPILE_STATUS, &CompileStatus);
	std::cout << CompileStatus << std::endl << LinkStatus << std::endl;
	if (!LinkStatus) std::cout << "failed to link" << std::endl;
	else std::cout << "Linked" << std::endl;
}

void Shader::UnBind()
{
	std::cout << "unbound shader " << &ID << std::endl;
	glUseProgram(0);
}

void Shader::SetUniforms4f(std::string name, float one, float two, float three, float four)
{
	glUniform4f(GetUniformLocation(name), one, two, three,four);

}

void Shader::UniformMatrix4fv(std::string name, glm::mat4 type)
{
	
	glUniformMatrix4fv(GetUniformLocation(name), 1,GL_FALSE, glm::value_ptr(type));
}

void Shader::SetUniforms1i(std::string name, int value)
{
	std::cout << "Uniform " << name << std::endl;
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniforms2fv(std::string name, float one,const float* two )
{
	glUniform2fv(GetUniformLocation(name), one, two);

}

const char* Shader::CreateShader(std::string ShaderPath)
{
	std::cout << "Created Shader using " << ShaderPath << std::endl;
	std::string ShaderCode;
	std::ifstream ShaderStream(ShaderPath, std::ios::in);
	if (ShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	//	std::cout << ShaderCode << std::endl;
	}
	else {
		std::cout << "Impossible to open." << std::endl << ShaderPath << std::endl;
		return 0;
	}
	char const* SourcePointer = ShaderCode.c_str();
	return SourcePointer;
}

unsigned int Shader::CompileShader(GLuint ShaderID, const char* ShaderSourcePointer)
{
	
	glShaderSource(ShaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(ShaderID);
	

	return ShaderID;
}

int Shader::GetUniformLocation(std::string& name)
{
	if (CachedLocation.find(name) != CachedLocation.end())
		return CachedLocation[name];


	unsigned int location = glGetUniformLocation(ID, name.c_str());
	CachedLocation[name] = location;

	if (location == -1)
	{
		std::cout << "Uniform named '" << name << "' Does not exist or was not used " << std::endl;
		return location;
	}
	else
		std::cout << name << " Located at " << location << std::endl;
	return location;
}

int Shader::GetUniformLocationnomap(const std::string& name)
{


	int location = glGetUniformLocation(ID, name.c_str());

	if (location == -1)
	{
		std::cout <<"Uniform named '" << name << "' Does not exist or was not used " << std::endl;
		return location;
	}
	else
	

	std::cout << name << " Located at " << location<< std::endl;
	return location;
}

