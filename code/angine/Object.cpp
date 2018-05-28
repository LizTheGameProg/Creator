#include "Object.h"
#include "Mesh.h"
#include "InputHandler.h"
#include <glm\ext.hpp>

Object::Object()
{
	Transform = glm::mat4();
	meshes = new std::vector<Mesh *>();
}

Object::~Object()
{
	for(unsigned int i = 0; i < meshes->size(); i++)
	{
		delete (*meshes)[i];
	}
	meshes->clear();
	delete meshes;
}

glm::vec4 Object::getPosition()
{
	return Transform[3];
}

void Object::setPosition(glm::vec3 a_newPosition)
{
	Transform = glm::translate(a_newPosition);
}

void Object::setPosition(glm::vec4 a_newPosition)
{
	Transform = glm::translate((glm::vec3)a_newPosition);
}

void Object::translate(glm::vec3 a_translation)
{
	Transform = glm::translate(Transform, a_translation);
}

glm::vec3 Object::getRotation()
{
	glm::vec3 rotation;
	if(Transform[0][0] == -1.f || Transform[0][0] == 1.f)
	{
		rotation = glm::vec3(atan2(Transform[0][2], Transform[2][3]));
	}
	else
	{
		rotation = glm::vec3(	atan2(-Transform[2][0], Transform[0][0]),
								asin(Transform[1][0]),
								atan2(-Transform[1][2], Transform[1][1]));
	}
	return rotation;
}

void Object::setRotation(glm::vec3 a_newRotation)
{
	glm::vec4 translation = getPosition();
	glm::vec3 scale = getScale();

	glm::mat4 rotX = glm::rotate(a_newRotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(a_newRotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(a_newRotation.z, glm::vec3(0, 0, 1));
	glm::mat4 rotation = rotX * rotY * rotZ;
	
	Transform = glm::translate((glm::vec3)translation) * rotation * glm::scale(scale);
}

void Object::rotate(glm::vec3 a_rotation)
{
	Transform = glm::rotate(Transform, a_rotation.x, glm::vec3(1, 0, 0));
	Transform = glm::rotate(Transform, a_rotation.y, glm::vec3(0, 1, 0));
	Transform = glm::rotate(Transform, a_rotation.z, glm::vec3(0, 0, 1));
}

glm::vec3 Object::getScale()
{
	glm::vec3 scale;
	scale = glm::vec3(	glm::length((glm::vec3)Transform[0]),
						glm::length((glm::vec3)Transform[1]),
						glm::length((glm::vec3)Transform[2]));
	return scale;
}

void Object::setScale(glm::vec3 a_newScale)
{
	glm::vec4 translation = getPosition();
	glm::vec3 rotation = getRotation();
	
	glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 rotMat = rotX * rotY * rotZ; // Might have to reverse this

	Transform = glm::translate((glm::vec3)translation) * rotMat * glm::scale(a_newScale);
}

void Object::scale(glm::vec3 a_scale)
{
	Transform = glm::scale(Transform, a_scale);
}

void Object::addMesh(Mesh * a_mesh)
{
	meshes->push_back(a_mesh);
}

void Object::update(float a_deltaTime)
{
	float speed = 100.f * a_deltaTime;
	glm::vec3 translation = glm::vec3();

	//if (InputHandler::Get()->IsKeyDown(KEY::KEY_LEFT))
	//{
	//	translation += glm::vec3(-speed, 0, 0);
	//}
	//if (InputHandler::Get()->IsKeyDown(KEY::KEY_RIGHT))
	//{
	//	translation += glm::vec3(speed, 0, 0);
	//}
	//if (InputHandler::Get()->IsKeyDown(KEY::KEY_UP))
	//{
	//	translation += glm::vec3(0, speed, 0);
	//}
	//if (InputHandler::Get()->IsKeyDown(KEY::KEY_DOWN))
	//{
	//	translation += glm::vec3(0, -speed, 0);
	//}
	//
	//Transform = glm::translate(Transform, translation);

	//for(unsigned int i = 0; i < meshes->size(); i++)
	//{
	//	meshes->at(i)->update(a_deltaTime);
	//}
}

void Object::render(glm::mat4 a_projectionView)
{
	for(unsigned int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i)->render(a_projectionView * Transform);
	}
}