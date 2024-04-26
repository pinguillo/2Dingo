#pragma once
#include <string>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void CompileShaders(const std::string& vertexFilepath, const std::string& fragmentFilepath);

	void LinkShaders();

	void AddAttribute(const std::string& attributeName);

	int getUniformLocation(const std::string& uniformName);

	void BindShader();
	void UnbindShader();

private:
	void compileShader(const std::string& filepath, unsigned int id);

private:
	int mNumAttributes = 0;

	unsigned int mProgramID = 0;

	unsigned int mVertexShaderID = 0;
	unsigned int mFragmentShaderID = 0;
};