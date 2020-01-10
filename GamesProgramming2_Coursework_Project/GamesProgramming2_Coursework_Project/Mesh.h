#pragma once
#include <glm/glm.hpp>
#include<GL/glew.h>
#include <vector>
#include "obj_loader.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this-> pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;

	}

	//Getters for vertex data
	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

	

protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord; //postion on texture to map to vertex
	glm::vec3 normal;

};

struct Sphere
{
public:

	Sphere() {}

	Sphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
	}

	//Getters for sphere data
	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	//position setter
	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}
	//radius setter
	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	void InitializeMesh(Vertex* vertices, unsigned int nVertices, unsigned int* indices, unsigned int n_indices);
	void Draw();

	void UpdateSphere(glm::vec3 pos, float rad);

	void LoadModel(const std::string &fileName);
	void InitializeModel(const IndexedModel& model);

	//mesh getters
	glm::vec3 GetSpherePos() { return sphere.GetPos(); }
	float GetSphereRadius() { return sphere.GetRadius(); }

private:

	enum{POSITION_VERTEXBUFFER, TEXCOORD_VB,NORMAL_VB,INDEX_VB, N_BUFFERS};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[N_BUFFERS];

	unsigned int drawCount;

	Sphere sphere;

};


