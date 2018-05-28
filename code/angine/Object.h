#pragma once

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <vector>

class Mesh;
class Object
{
public:
	Object();
	~Object();

	// C# like properties
	//__declspec(property(get = getPosition, put = setPosition)) glm::vec4 position;

	glm::vec4 getPosition();
	void setPosition(glm::vec3 newPosition);
	void setPosition(glm::vec4 newPosition);
	void translate(glm::vec3 translation);

	glm::vec3 getRotation();
	void setRotation(glm::vec3 newRotation);
	void rotate(glm::vec3 rotation);

	glm::vec3 getScale();
	void setScale(glm::vec3 newScale);
	void scale(glm::vec3 scale);

	void addMesh(Mesh * mesh);

	void update(float deltaTime);
	void render(glm::mat4 projectionView);

private:
	glm::mat4 Transform;
	std::vector<Mesh *> * meshes;
};