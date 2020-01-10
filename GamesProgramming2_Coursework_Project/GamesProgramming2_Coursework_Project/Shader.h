#pragma once
#include <string>
#include <gl/glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);
	~Shader();

private:
	static const unsigned int N_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum {
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[N_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

