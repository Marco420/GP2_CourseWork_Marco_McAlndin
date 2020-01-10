#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
	drawCount = NULL;

}

void Mesh::InitializeMesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices,unsigned int n_indices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < n_indices; i++)
		model.indices.push_back(indices[i]);

	InitializeModel(model);
}

void Mesh::InitializeModel(const IndexedModel& model)
{
	drawCount = model.indices.size();
	//generate a vertex array and store it in the VAO
	glGenVertexArrays(1, &vertexArrayObject); 
	//bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)
	glBindVertexArray(vertexArrayObject); 
	//generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glGenBuffers(N_BUFFERS, vertexArrayBuffers); 
	//tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); 
	//move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); 
	//move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	//move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// unbind our VAO
	glBindVertexArray(0); 
}

void Mesh::LoadModel(const std::string& fileName)
{

	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitializeModel(model);
	Sphere sphere();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays

}

void Mesh::Draw() {

	glBindVertexArray(vertexArrayObject);

	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

void Mesh::UpdateSphere(glm::vec3 pos, float rad)
{
	sphere.SetPos(pos);
	sphere.SetRadius(rad);
}
