#include "LoadShader2.h"

Shader::Shader(std::string VertexPath, std::string FragmentPath)
	:ID(0),Result(GL_FALSE),InfoLogLength(0)

{
	ID = glCreateProgram();
	 
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(VertexShaderID, CreateShader(VertexPath));
	CompileShader(FragmentShaderID, CreateShader(FragmentPath));
	

	
	glAttachShader(ID, VertexShaderID);
	glAttachShader(ID, FragmentShaderID);
	glLinkProgram(ID);

	//Check(VertexShaderID, Result, InfoLogLength);
	//Check(FragmentShaderID, Result, InfoLogLength);

	//glDetachShader(ProgramID, VertexShaderID);
	//glDetachShader(ProgramID, FragmentShaderID);

	//glDeleteShader(VertexShaderID);
	//glDeleteShader(FragmentShaderID);
	
	
}

Shader::~Shader()
{
	//UnBind();
	//std::cout << "destroyed shader" << std::endl;
	//glDeleteProgram(ID);
}

void Shader::Bind()
{
	std::cout << "bound shader" << std::endl;
	glUseProgram(ID);
}

void Shader::UnBind()
{
	std::cout << "unbound shader" << std::endl;
	glUseProgram(0);
}

void Shader::SetUniforms4f(std::string name)
{
}

void Shader::SetUniforms1i(std::string name, int value)
{
	std::cout << "uniform set" << std::endl;
	glUniform1i(GetUniformLocationnomap(name), value);
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

unsigned int Shader::GetUniformLocation(std::string& name)
{
	if (CachedLocation.find(name) != CachedLocation.end())
		return CachedLocation[name];


	unsigned int location = glGetUniformLocation(ID, name.c_str());
	CachedLocation[name] = location;
	std::cout << location <<  std::endl;
	return location;
}

unsigned int Shader::GetUniformLocationnomap(std::string& name)
{



	int location = glGetUniformLocation(ID, name.c_str());
	std::cout << location << std::endl;
	if (location == -1)
	{
		std::cout << name << " Does not Exist" << std::endl;
	}
	return location;
}
void Shader::Check(GLuint Checking, GLint& Result, int& InfoLogLength)
{
	glGetProgramiv(Checking, GL_LINK_STATUS, &Result);
	glGetProgramiv(Checking, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		static std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(Checking, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}
}