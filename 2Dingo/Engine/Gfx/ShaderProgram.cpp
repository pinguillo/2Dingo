#include "ShaderProgram.h"

#include <GLEW\glew.h>
#include <fstream>

#include "../Util/Logger.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::CompileShaders(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
	mProgramID = glCreateProgram();

	//Create shaders
	mVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (mVertexShaderID == 0) { Logger::Fatal("Vertex shader failed to compile"); }

	mFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (mFragmentShaderID == 0) { Logger::Fatal("Fragment shader failed to compile"); }

	//Vertex shader
	compileShader(vertexFilepath, mVertexShaderID);
	compileShader(fragmentFilepath, mFragmentShaderID);
}

void ShaderProgram::LinkShaders()
{
	glAttachShader(mProgramID, mVertexShaderID);
	glAttachShader(mProgramID, mFragmentShaderID);

	glLinkProgram(mProgramID);

	//Check errors
	int success;
	char infoLog[512];
	glGetShaderiv(mProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glDeleteShader(mVertexShaderID);
		glDeleteShader(mFragmentShaderID);

		glGetShaderInfoLog(mProgramID, 512, NULL, infoLog);
		Logger::Fatal("Error in shader linking: %s", infoLog);
	}

	glDetachShader(mProgramID, mVertexShaderID);
	glDetachShader(mProgramID, mFragmentShaderID);
	glDeleteShader(mVertexShaderID);
	glDeleteShader(mFragmentShaderID);
}

void ShaderProgram::AddAttribute(const std::string& attributeName)
{
	glBindAttribLocation(mProgramID, mNumAttributes++, attributeName.c_str());
}

int ShaderProgram::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(mProgramID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		Logger::Fatal("Uniform %s not found", uniformName);
	}
	return location;
}

void ShaderProgram::BindShader()
{
	glUseProgram(mProgramID);
	for (int i = 0; i < mNumAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::UnbindShader()
{
	glUseProgram(0);
	for (int i = 0; i < mNumAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void ShaderProgram::compileShader(const std::string& filepath, unsigned int id)
{
	std::ifstream vertexFile(filepath);
	if (vertexFile.fail()) { Logger::Fatal("Failed to open vertex shader %s", filepath); }

	std::string fileContents = "";
	std::string line;
	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();

	const GLchar* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	//Error check
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		Logger::Fatal("Error in shader compilation: %s", infoLog);
	}
}
