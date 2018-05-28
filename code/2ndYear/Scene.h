#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

class PhysicsObject;

class Scene
{
public:
	Scene(glm::vec3 Gravity = glm::vec3(0,-10,0), float TimeStep = 1.0f/6.0f);
	~Scene(void);

	void update();
	void render();

	typedef bool (*fn)( PhysicsObject *, PhysicsObject * );
	//function pointer array for doing our collisions
	
	static fn collisionfunctionArray[];

	static bool plane2Plane(PhysicsObject * obj1,PhysicsObject * obj2);
	static bool plane2Sphere(PhysicsObject * obj1,PhysicsObject * obj2);
	static bool plane2Box(PhysicsObject * obj1,PhysicsObject * obj2);
	
	static bool sphere2Plane(PhysicsObject * obj1,PhysicsObject * obj2){ return plane2Sphere(obj1, obj2); }
	static bool sphere2Sphere(PhysicsObject * obj1,PhysicsObject * obj2);
	static bool sphere2Box(PhysicsObject * obj1,PhysicsObject * obj2);

	static bool box2Plane(PhysicsObject * obj1,PhysicsObject * obj2){ return plane2Box(obj1, obj2); }
	static bool box2Sphere(PhysicsObject * obj1,PhysicsObject * obj2){ return sphere2Box(obj1, obj2); }
	static bool box2Box(PhysicsObject * obj1,PhysicsObject * obj2);
private:
	void checkForCollisionActor(PhysicsObject * object1, int iterator);
	static glm::vec4 getMinMax(std::vector<glm::vec3> vecs_box, glm::vec3 axis);

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	unsigned int m_defaultScreenWidth;
	unsigned int m_defaultScreenHeight;

	std::vector<PhysicsObject *> m_actors;
	std::vector<PhysicsObject *> m_jointActors;

	glm::vec3	m_gravity;
	float		m_timeStep;

	float		m_timeSinceLastUpdate;

	float time;
	int frames;
};

#endif