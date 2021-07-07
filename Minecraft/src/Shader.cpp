#include <glad/glad.h>
#include "Shader.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSrcPath, const std::string& fragmentSrcPath)
{
    std::string vertexShaderSource = ReadFile(vertexSrcPath);
    std::string fragmentShaderSource = ReadFile(fragmentSrcPath);

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    CompileShader(vertexShader);
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    CompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

}

void Shader::CompileShader(unsigned int shader){
     glCompileShader(shader);

    int isCompiled = 0;
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	int maxLength = 256;

	char infoLog[256];;

    if(isCompiled == GL_FALSE){
        
        //glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        std::cout << infoLog << std::endl;

    }
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

std::string Shader::ReadFile(const std::string& path){
    std::string result;
    std::ifstream in(path);

    if (in) 
    {
        in.seekg(0, std::ios_base::end);
        int length = in.tellg();
        result.resize(length);
        in.seekg(0, std::ios_base::beg);
        in.read(&result[0], length);

        in.close();
        
    } else 
    {
        std::cout << "Failed to read from " << path << std::endl;
    }

    return result.c_str();


}

void Shader::setMat4(const std::string& name, glm::mat4 mat)
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
	
    if(loc < 0) 
    {
        std::cout << "failed to get location of: " << name << std::endl;
    } else 
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));

    }
    
}

void Shader::setInt(const std::string& name, int value)
{
    int loc = glGetUniformLocation(ID, name.c_str());

    if(loc < 0)
    {
         std::cout << "failed to get location of " << name << std::endl;
    }
    else
    {
        glUniform1i(loc, value);
    }
}

void Shader::setFloat(const std::string& name, float value)
{
	int loc = glGetUniformLocation(ID, name.c_str());

	if (loc < 0)
	{
		std::cout << "failed to get location of " << name << std::endl;
	}
	else
	{
		glUniform1f(loc, value);
	}
}

void Shader::setVec3(const std::string& name, glm::vec3 value) 
{
	int loc = glGetUniformLocation(ID, name.c_str());

	if (loc < 0)
	{
		std::cout << "failed to get location of " << name << std::endl;
	}
	else 
	{
		glUniform3fv(loc, 1, glm::value_ptr(value));
	}
}

void Shader::setVec2(const std::string& name, glm::vec2 value)
{
	int loc = glGetUniformLocation(ID, name.c_str());

	if (loc < 0)
	{
		std::cout << "failed to get location of " << name << std::endl;
	}
	else
	{
		glUniform2fv(loc, 1, glm::value_ptr(value));
		
	}
}