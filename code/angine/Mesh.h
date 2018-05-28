#pragma once

#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>

class Mesh
{
public:
	//enum FileType
	//{
	//	OBJ,
	//	FBX
	//};

	Mesh();
	~Mesh();

	virtual void update(float deltaTime) {}
	virtual void render(glm::mat4 projectionView) {}

	// TODO: impliment
	//void Load(const char * filePathName, Mesh::FileType type);

protected:
	//struct Data
	//{
	//	glm::vec4 position;
	//	glm::vec2 texCoord;
	//	glm::vec4 colour;
	//};

	//void init(const unsigned int indexData[]);

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	//std::vector<Data *> verticesData;

	std::vector<unsigned int> textureIDs;
	unsigned int shaderProgramID;
};