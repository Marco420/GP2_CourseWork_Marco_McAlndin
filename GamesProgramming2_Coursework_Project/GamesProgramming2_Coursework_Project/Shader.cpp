#include "stdafx.h"
#include "Shader.h"

#include <iostream>
#include <fstream>


Shader::Shader(const std::string& fileName)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader("..\\res\\shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER);
	/*shaders[2] = CreateShader(LoadShader("..\\res\\cubemap.fs"), GL_FRAGMENT_SHADER);
	shaders[3] = CreateShader(LoadShader("..\\res\\cubemap.vs"), GL_VERTEX_SHADER);
	shaders[4] = CreateShader(LoadShader("..\\res\\skybox.fs"), GL_FRAGMENT_SHADER);
	shaders[5] = CreateShader(LoadShader("..\\res\\skybox.vs"), GL_VERTEX_SHADER);
*/


	//Attach our shaders
	for (int x = 0; x < N_SHADERS; x++)
	{
		glAttachShader(program, shaders[x]);

	}


	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "textCoord");

	//Link and validate shader program
	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program not linked");
	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type) 
{
	//create shader type
	GLuint shader = glCreateShader(type); 

	//check if shader is created
	if (shader == 0)
		std::cerr << "Error type creation failed " << type << std::endl;

	//convert strings into list of c-strings
	const GLchar* stringSource[1]; 
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	//send code to opengl
	glShaderSource(shader, 1, stringSource, lengths); 
	//compile shader code with open gl
	glCompileShader(shader); 
	//check for compile error
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); 

	return shader;

}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::Bind()
{
	glUseProgram(program);
}



void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) 
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}




Shader::~Shader()
{
	for (int x = 0; x < N_SHADERS; x++)
	{
		glDetachShader(program, shaders[x]);
		glDeleteShader(shaders[x]);
	}

	glDeleteProgram(program);

}
