#ifndef __PhysTutorrialMain_H_
#define __PhysTutorrialMain_H_

#include "../PhysXTutorials/BaseScene.h"
#include <glm/glm.hpp>
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>
#include <PxPhysicsAPI.h>
#include<PxSceneQueryFiltering.h>
#include "FBXFile.h"

using namespace physx;

struct RagdollNode
{
	PxQuat globalRotation;  //rotation of this link in model space - we could have done this relative to the parent node but it's harder to visualize when setting up the data by hand
	PxVec3 scaledGobalPos; //Position of the link centre in world space which is calculated when we process the node.  It's easiest if we store it here so we have it when we transform the child
	int parentNodeIdx;	//Index of the parent node
	float halfLength; //half length of the capsule for this node
	float radius; //radius of capsule for thisndoe
	float parentLinkPos; //relative position of link centre in parent to this node.  0 is the centre of hte node, -1 is left end of capsule and 1 is right end of capsule relative to x 
	float childLinkPos;  //relative position of link centre in child
	char* name;	//name of link
	PxArticulationLink* linkPtr; //pointer to link if we are using articulation
	PxRigidDynamic* actorPtr;  //Pointer the PhysX actor which is linked to this node if we are using seperate actors

	//constructor
	RagdollNode(PxQuat _globalRotation,int _parentNodeIdx,float _halfLength,float _radius,float _parentLinkPos,float _childLinkPos,char* _name){globalRotation = _globalRotation,parentNodeIdx = _parentNodeIdx;halfLength = _halfLength;radius=_radius;parentLinkPos = _parentLinkPos;childLinkPos = _childLinkPos;name = _name;};
};

// Derived application class that wraps up all globals neatly
class MaddollTut : public BaseScene
{
public:
	MaddollTut(PhysXVariables * PhysX_Variables);
	virtual ~MaddollTut();
	void update(float DeltaTime);
	void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

protected:

	PxRigidDynamic* playerActor; 
	glm::mat4 *	m_cameraMatrix;
	
	void tutorial_3_ballGun();
	void tutorial_12();
	void tutorial_12a();
	void pickingExample1();
	void pickingExample2();

	void createCollisionGroundPlane();
	void setUpVisualDebugger();

	void addSteps(PxTransform transform, int numberSteps);
	PxArticulation* makeRagdoll(RagdollNode** nodes,PxTransform worldPos,float scale);
	void makeRagdollUsingActors(RagdollNode** nodes,PxTransform worldPos,float scale);	// structure assigned to an FBXMeshNode's m_userData
	struct GLData
	{
		unsigned int vbo, ibo, vao;
	};
	FBXFile*	m_file;
	unsigned int m_program, m_vs, m_fs;

	std::vector<PxRigidActor*> m_PhysXActors;
	std::vector<PxArticulation*> m_PhysXActorsRagDolls;

};

#endif // __PhysTutorrialMain_H_