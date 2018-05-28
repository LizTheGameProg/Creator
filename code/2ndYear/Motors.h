#ifndef __PhysTutorrialMain_H_
#define __PhysTutorrialMain_H_

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
#include "FBXFile.h"
//#include "extensions/PxJoint.h"
#define NUMBER_WHEELS 4

//using namespace physx;
class Vehicle
{
public:
	float driveForce;
	//PxRevoluteJoint* gCarAxles[NUMBER_WHEELS];
	//PxRigidDynamic* wheels[NUMBER_WHEELS];
	float wheelRadius;
	float wheelWidth;
	Vehicle(){driveForce = 0;};
};


// Derived application class that wraps up all globals neatly
class MotorTutorial : public AIE_2ND_YEAR::Application
{
public:

	MotorTutorial();
	virtual ~MotorTutorial();


protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	//PxRigidDynamic* playerActor; 
	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
	//void addWidget(PxShape* shape,PxRigidActor* actor) ;
	//void addSphere(PxShape* pShape,PxRigidActor* actor) ;
	//void addBox(PxShape* pShape,PxRigidActor* actor) ;
	//void addCapsule(PxShape* pShape,PxRigidActor* actor) ;
	//void addWheel(PxShape* pShape,PxRigidActor* actor) ;
	void setUpPhysXTutorial();
	void upDatePhysx(float upDatePhysx);
	void cleanUpPhsyx();
	void tutorial_13();
	void tutorial_13a();
	void tutorial_13b();
	void createCollisionGroundPlane();
	void setUpVisualDebugger();
	//void makeSimpleVehicle(PxTransform transform,Vehicle* vehicle);
	void controlVehicle(float a_deltaTime);
	//PxRigidDynamic* makeWheel(PxTransform pose,float radius,float thickness);
	// structure assigned to an FBXMeshNode's m_userData
	struct GLData
	{
		unsigned int vbo, ibo, vao;
	};
	FBXFile*	m_file;
	unsigned int m_program, m_vs, m_fs;

};

#endif // __PhysTutorrialMain_H_