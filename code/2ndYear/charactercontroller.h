#ifndef __CharacterController_H_
#define __CharacterController_H_

#include "Application.h"
#include <glm/glm.hpp>
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>
//#include <PxPhysicsAPI.h>
//#include<PxSceneQueryFiltering.h>
//#include "FBXFile.h"
//#include "extensions/PxJoint.h"

//using namespace physx;

struct HeightMap
{
//	PxHeightFieldSample* samples;
	int numRows;
	int numCols;
	float heightScale;
	float rowScale; 
	float colScale;
	glm::vec3 center;
	bool enabled;



public:
	HeightMap()
	{
		enabled = false;
	}
	//PxRigidStatic* actor;
};



// Derived application class that wraps up all globals neatly
class CharacterControllerTutorial : public AIE_2ND_YEAR::Application
{
public:

	CharacterControllerTutorial();
	virtual ~CharacterControllerTutorial();
	HeightMap heightMap;
	float gravity;
	//PxVec3 playerContactNormal; //set to a value if the player has contacted something;
	//PxRigidDynamic* playerActor; 
protected:
	float characterRotation;
	float characterYVelocity;
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
	//void addWidget(PxShape* shape,PxRigidActor* actor) ;
	//void addSphere(PxShape* pShape,PxRigidActor* actor) ;
	//void addBox(PxShape* pShape,PxRigidActor* actor) ;
	//void addCapsule(PxShape* pShape,PxRigidActor* actor) ;
	void setUpPhysXTutorial();
	void upDatePhysx(float upDatePhysx);
	void cleanUpPhsyx();
	void tutorial_14();
	void createCollisionGroundPlane();
	void setUpVisualDebugger();
	//PxRigidStatic* addStaticHeightMapCollision(PxTransform transform);
	void addHeightMap();
	void controlPlayer(float a_deltaTime);
	void addTestEnvironment();
	// structure assigned to an FBXMeshNode's m_userData
	struct GLData
	{
		unsigned int vbo, ibo, vao;
	};
	//FBXFile*	m_file;
	unsigned int m_program, m_vs, m_fs;
};

#endif // __CharacterController_H_