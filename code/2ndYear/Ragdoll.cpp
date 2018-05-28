#include "Ragdoll.h"
#include <string.h>

#include <iostream>
//#include "PxShape.h"
//#include "PxScene.h"
//#include "PxSceneQueryReport.h"
//#include "extensions/PxJoint.h"
//#include "PxRigidDynamic.h"
//#include "extensions/PxDistanceJoint.h"
//#include "extensions/PxSphericalJoint.h"
//#include "PxArticulationLink.h"
//#include "PxShape.h"

//std::vector<PxJoint *>joints;

//using namespace physx;

using namespace AIE_2ND_YEAR;

//create some constants for axis of rotation to make definition of quaternions a bit neater
//const PxVec3 X_AXIS = PxVec3(1,0,0);
//const PxVec3 Y_AXIS = PxVec3(0,1,0);
//const PxVec3 Z_AXIS = PxVec3(0,0,1);
//Parts which make up our ragdoll
enum RagDollParts
{
	NO_PARENT = -1,
	LOWER_SPINE,
	LEFT_PELVIS,
	RIGHT_PELVIS,
	LEFT_UPPER_LEG,
	RIGHT_UPPER_LEG,
	LEFT_LOWER_LEG,
	RIGHT_LOWER_LEG,
	LEFT_FOOT,
	RIGHT_FOOT,
	UPPER_SPINE,
	LEFT_CLAVICLE,
	RIGHT_CLAVICLE,
	NECK,
	HEAD,
	LEFT_UPPER_ARM,
	RIGHT_UPPER_ARM,
	LEFT_LOWER_ARM,
	RIGHT_LOWER_ARM,
	LEFT_HAND,
	RIGHT_HAND,
};

//simple ragdoll example
//format is: Local rotation, parentID, bone radius, bone length (not including radius), parent offset joint position, child offset joint position, name);
RagdollNode* ragdollSnakeData[] = 
{
	//new RagdollNode(PxQuat::createIdentity(),NO_PARENT,4,1,1,1,"root"),
	//new RagdollNode(PxQuat::createIdentity(),0,4,1,-1,1,"node1"),
	//new RagdollNode(PxQuat::createIdentity(),1,4,1,-1,1,"node2"),
	NULL
};


//example of a more complicated jointed skeleton
RagdollNode* ragdollAlienThingData[] = 
{
	//new RagdollNode(PxQuat::createIdentity(),NO_PARENT,16,1,1,1,"root"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.4f,Z_AXIS),0,8,1,-1,1,"node1"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.3f,Z_AXIS),0,8,1,-0.75,1,"node2"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.2f,Z_AXIS),0,8,1,-0.5,1,"node2"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.1f,Z_AXIS),0,8,1,-0.25,1,"node3"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),0,8,1,0,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.1f,Z_AXIS),0,8,1,0.25,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.2f,Z_AXIS),0,8,1,0.5,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.3f,Z_AXIS),0,8,1,0.75,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.4f,Z_AXIS),0,8,1,1,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.4f,Z_AXIS),1,8,0.5,-1,1,"node1"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.3f,Z_AXIS),2,8,0.5,-1,1,"node2"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.2f,Z_AXIS),3,8,0.5,-1,1,"node2"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.1f,Z_AXIS),4,8,0.5,-1,1,"node3"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),5,8,0.5,-1,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.1f,Z_AXIS),6,8,0.5,-1,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.2f,Z_AXIS),7,8,0.5,-1,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.3f,Z_AXIS),8,8,0.5,-1,1,"node"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.4f,Z_AXIS),9,8,0.5,-1,1,"node"),
	NULL
};


//complex humanoid ragdoll example
RagdollNode* ragdollData[] = 
{
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),NO_PARENT,1,3,1,1,"lower spine"),
	//new RagdollNode(PxQuat(PxPi,Z_AXIS),LOWER_SPINE,1,1,-1,1,"left pelvis"),
	//new RagdollNode(PxQuat(0,Z_AXIS),LOWER_SPINE,1,1,-1,1,"right pelvis"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.2f,Z_AXIS),LEFT_PELVIS,5,2,-1,1,"left upper leg"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.2f,Z_AXIS),RIGHT_PELVIS,5,2,-1,1,"right upper leg"),
	//new RagdollNode(PxQuat(PxPi/2.0f+0.2f,Z_AXIS),LEFT_UPPER_LEG,5,1.75,-1,1,"left lower leg"),
	//new RagdollNode(PxQuat(PxPi/2.0f-0.2f,Z_AXIS),RIGHT_UPPER_LEG,5,1.75,-1,1,"right lower leg"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Y_AXIS),LEFT_LOWER_LEG,1.5,1.5,-1,1,"left foot"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Y_AXIS),RIGHT_LOWER_LEG,1.5,1.5,-1,1,"right foot"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),LOWER_SPINE,1,3,1,-1,"upper spine"),
	//new RagdollNode(PxQuat(PxPi,Z_AXIS),UPPER_SPINE,1,1.5,1,1,"left clavicle"),
	//new RagdollNode(PxQuat(0,Z_AXIS),UPPER_SPINE,1,1.5,1,1,"right clavicle"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),UPPER_SPINE,1,1,1,-1,"neck"),
	//new RagdollNode(PxQuat(PxPi/2.0f,Z_AXIS),NECK,1,3,1,-1,"HEAD"),
	//new RagdollNode(PxQuat(PxPi-.3,Z_AXIS),LEFT_CLAVICLE,3,1.5,-1,1,"left upper arm"),
	//new RagdollNode(PxQuat(0.3,Z_AXIS),RIGHT_CLAVICLE,3,1.5,-1,1,"right upper arm"),
	//new RagdollNode(PxQuat(PxPi-.3,Z_AXIS),LEFT_UPPER_ARM,3,1,-1,1,"left lower arm"),
	//new RagdollNode(PxQuat(0.3,Z_AXIS),RIGHT_UPPER_ARM,3,1,-1,1,"right lower arm"),
	//new RagdollNode(PxQuat(PxPi-.3,Z_AXIS),LEFT_LOWER_ARM,1.0f,1.5,-1,1,"left hand"),
	//new RagdollNode(PxQuat(0.3,Z_AXIS),RIGHT_LOWER_ARM,1.0f,1.5,-1,1,"right hand"),
	NULL
};

MaddollTut::MaddollTut(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
{
	m_file = NULL;
	GLFWMouseButton1Down = false;
	tutorial_12();  //set up our tutorial
}

MaddollTut::~MaddollTut()
{

}

void MaddollTut::update(float a_deltaTime)
{
	tutorial_3_ballGun();  //add this if we want to have a ball gun in the scene
	//for(auto articulation : m_PhysXActorsRagDolls)
	//{
	//	{
	//		PxU32 nLinks = articulation->getNbLinks();
	//		PxArticulationLink** links = new PxArticulationLink*[nLinks];
	//		articulation->getLinks(links, nLinks);
	//		// Render all the shapes in the physx actor (for early tutorials there is just one)
	//		while (nLinks--)
	//		{
	//			PxArticulationLink* link = links[nLinks];
	//			PxU32 nShapes = link->getNbShapes();
	//			PxShape** shapes = new PxShape*[nShapes];
	//			link->getShapes(shapes, nShapes);
	//			while (nShapes--)
	//			{
	//				addWidget(shapes[nShapes],link); 
	//			}
	//		}
	//		delete [] links;
	//	}
	//}
}

void MaddollTut::render(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
{
	//for (auto actor : m_PhysXActors)
	//{
	//	PxU32 nShapes = actor->getNbShapes();
	//	PxShape** shapes = new PxShape*[nShapes];
	//	actor->getShapes(shapes, nShapes);
	//	// Render all the shapes in the physx actor (for early tutorials there is just one)
	//	while (nShapes--)
	//	{
	//		 addWidget(shapes[nShapes],actor); 
	//	}
	//	delete [] shapes;
	//}
}

//simple example which just creates sname
void MaddollTut::tutorial_12a()
{
	//PxArticulation* ragDollArticulation;
	////create ragdoll
	//ragDollArticulation =  makeRagdoll(ragdollSnakeData,PxTransform(PxVec3(0,0,0)),.1f);
	////add it to the physx scene
	//m_physX_Variables->m_PhysicsScene->addArticulation(*ragDollArticulation);
	////add it to our list of articulations so we can render it
	//m_PhysXActorsRagDolls.push_back(ragDollArticulation);
	////add a plane
	//PxTransform pose = PxTransform( PxVec3(0.0f, -4, 0.0f),PxQuat(PxHalfPi*1.1, PxVec3(0.0f, 0.0f, 1.0f)));
	//PxRigidStatic* plane = PxCreateStatic(*m_physX_Variables->m_Physics, pose,PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
	////add it to the physX scene
	//m_physX_Variables->m_PhysicsScene->addActor(*plane);
}

//more complex example which creates
void MaddollTut::tutorial_12()
{
	//PxTransform localPose;
	//m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(1000,0,0),glm::vec3(-2000,10,0), glm::vec3(0,1,0)) );

	//PxArticulation * ragDollArticulation;
	////create first ragdoll at the top of the stairs
	//ragDollArticulation = makeRagdoll(ragdollData,PxTransform(PxVec3(0,15,20)),.1f);
	//m_physX_Variables->m_PhysicsScene->addArticulation(*ragDollArticulation);
	//m_PhysXActorsRagDolls.push_back(ragDollArticulation);
	
	//create another three as examples
	//ragDollArticulation = makeRagdoll(ragdollData,PxTransform(PxVec3(-20,0,0)),.1f);
	//m_physX_Variables->m_PhysicsScene->addArticulation(*ragDollArticulation);
	//m_PhysXActorsRagDolls.push_back(ragDollArticulation);
	//ragDollArticulation = makeRagdoll(ragdollData,PxTransform(PxVec3(-28,0,0)),.1f);
	//m_physX_Variables->m_PhysicsScene->addArticulation(*ragDollArticulation);
	//m_PhysXActorsRagDolls.push_back(ragDollArticulation);
	//ragDollArticulation = makeRagdoll(ragdollData,PxTransform(PxVec3(-36,0,0)),.1f);
	//m_physX_Variables->m_PhysicsScene->addArticulation(*ragDollArticulation);
	//m_PhysXActorsRagDolls.push_back(ragDollArticulation);

	//add our steps
	//addSteps(PxTransform(PxVec3(20,0,0)),30);

	//add a ground plane
	//PxTransform pose = PxTransform( PxVec3(0.0f, -4, 0.0f),PxQuat(PxHalfPi*1, PxVec3(0.0f, 0.0f, 1.0f)));
	//PxRigidStatic* plane = PxCreateStatic(*m_physX_Variables->m_Physics, pose,PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
	//m_physX_Variables->m_PhysicsScene->addActor(*plane);
}

//create a flight of steps for actor to fall down
//void MaddollTut::addSteps(PxTransform transform, int numberSteps)
//{
//	for(int count = 0 ; count < numberSteps;count++)
//	{
//		//step extents
//		float width = 1.0;
//		float height = 3;
//		float length = 20;
//		PxVec3 extents(width,height,length);
//		//calculate the transform for this step
//		PxTransform pose = transform;
//		pose.p.x +=  width* 2 * count;
//		pose.p.y += height*.5f * count;
//		extents.y += height*.5f * count;
//		PxBoxGeometry box(extents);
//		PxRigidStatic*staticObject = PxCreateStatic(*m_physX_Variables->m_Physics,pose,box,*m_physX_Variables->m_PhysicsMaterial);
//		//add it to the physX scene
//		m_physX_Variables->m_PhysicsScene->addActor(*staticObject);
//		m_PhysXActors.push_back(staticObject);
//	}
//}

//make a ragdoll out of actors and joints to demonstrate stability problems
//void MaddollTut::makeRagdollUsingActors(RagdollNode** nodeArray,PxTransform worldPos,float scaleFactor)
//{	
//	//get a pointer to the first element in the array of nodes
//	RagdollNode** currentNode = nodeArray;
//	//while there are more nodes to process..
//	while(*currentNode!= NULL)
//	{
//		//get a pointer to the data for this node
//		RagdollNode* currentNodePtr = *currentNode;
//		//reserver some space for the pointer to the parent npde
//		RagdollNode* parentNode;
//		//get local copies of the links dimensions
//		float radius = currentNodePtr->radius*scaleFactor;
//		float halfLength = currentNodePtr->halfLength*scaleFactor;
//		float childHalfLength = radius + halfLength;
//		float parentHalfLength;
//		//get a local copy of the parents index
//		int parentIdx = currentNodePtr->parentNodeIdx;
//		currentNodePtr->scaledGobalPos = worldPos.p;  //set this to world pos of node for the case of the root. If it's not the root it will get over writen when we know it's actual coordinate
//		if(parentIdx!= -1)
//		{
//			//if this node has a parent then change it's global pose to be relative to the parent
//			parentNode = *(nodeArray + parentIdx);
//			//get the parents bone dimensions
//			parentHalfLength = (parentNode->radius + parentNode->halfLength) *scaleFactor;
//			PxVec3 parentNodePos = parentNode->scaledGobalPos;
//			//get the relative position of the child from the parent
//			PxVec3 currentRelative = currentNodePtr->childLinkPos * currentNodePtr->globalRotation.rotate(PxVec3(childHalfLength,0,0));
//			PxVec3 parentRelative = - currentNodePtr->parentLinkPos * parentNode->globalRotation.rotate(PxVec3(parentHalfLength,0,0));
//			//store the global pose in the node for future reference
//			currentNodePtr->scaledGobalPos = parentNodePos - (parentRelative + currentRelative);
//		}
//		//create the geometry for the shape which will be the collider for this link
//		float jointSpace = .01f;
//		float capsuleHalfLength = (halfLength>jointSpace?halfLength-jointSpace:0)+.01f; 
//		PxCapsuleGeometry capsule(radius,capsuleHalfLength);
//		float density = 1;
//		PxRigidDynamic* parentActorPtr = NULL;
//		PxQuat rotation = currentNodePtr->globalRotation;
//		PxTransform scaledTransform = PxTransform(currentNodePtr->scaledGobalPos,rotation) ;
//		scaledTransform.p = scaledTransform.p + worldPos.p;
//		//get it's world transform
//		//create the actor and add it to the physx scene and to our list of actors for rendering
//		PxRigidDynamic* thisActorPtr = PxCreateDynamic(*m_physX_Variables->m_Physics, scaledTransform, capsule,*m_physX_Variables->m_PhysicsMaterial, density);
//		m_physX_Variables->m_PhysicsScene->addActor(*thisActorPtr);
//		m_PhysXActors.push_back(thisActorPtr);
//
//		currentNodePtr->actorPtr = thisActorPtr;
//		//if the link has a parent then we need to link it to the parent with a joint
//		if(parentIdx!= -1)
//		{
//			//get a pointer to the parent
//			parentActorPtr = parentNode->actorPtr;
//			//work out the constraint frames so we know how to reposition the joint to be between the bones
//			PxQuat frameRotation = parentNode->globalRotation.getConjugate() * currentNodePtr->globalRotation;
//			PxTransform parentConstraintFrame = PxTransform(PxVec3(currentNodePtr->parentLinkPos * parentHalfLength,0,0),frameRotation);
//			PxTransform thisConstraintFrame = PxTransform(PxVec3(currentNodePtr->childLinkPos * childHalfLength,0,0));
//			PxD6Joint* d6joint = NULL;
//			//use a d6 joint because it's the best one for the jobe
//			d6joint =PxD6JointCreate(*m_physX_Variables->m_Physics,parentActorPtr,parentConstraintFrame,thisActorPtr,thisConstraintFrame); 
//			if(d6joint)
//			{
//				//set up various parameters for the joint
//				d6joint->setProjectionLinearTolerance(.1f);
//				d6joint->setProjectionAngularTolerance(.1f);
//
//				PxD6JointDrive drive(10.0f, -20.0f, PX_MAX_F32, true);
//				d6joint->setDrive(PxD6Drive::eX, drive);
//				d6joint->setDrive(PxD6Drive::eY, drive);
//				d6joint->setDrive(PxD6Drive::eZ, drive);
//
////Drive the joint to the local(actor[0]) origin - since no angular dofs are free, the angular part of the transform is ignored
//
//				d6joint->setDrivePosition(PxTransform(PxVec3(0,0,0)));
//				d6joint->setDriveVelocity(PxVec3(0,0,0),PxVec3(0,0,0));
//			}
//		}
//		thisActorPtr->putToSleep();
//		currentNode++;
//	}
//}

//make a ragdoll using an articulations
//PxArticulation* MaddollTut::makeRagdoll(RagdollNode** nodeArray,PxTransform worldPos,float scaleFactor)
//{
//
//	//create the articulation for our ragdoll
//	PxArticulation *articulation = m_physX_Variables->m_Physics->createArticulation();
//	PxMaterial* ragdollMaterial = m_physX_Variables->m_Physics->createMaterial(0.4f,0.4f,1.0f);
//	RagdollNode** currentNode = nodeArray;
//	//while there are more nodes to process...
//	while(*currentNode!= NULL)
//	{
//		//get a pointer to the current node
//		RagdollNode* currentNodePtr = *currentNode;
//		//create a pointer ready to hold the parent node pointer if there is one
//		RagdollNode* parentNode;
//		//get scaled values for capsule
//		float radius = currentNodePtr->radius*scaleFactor;
//		float halfLength = currentNodePtr->halfLength*scaleFactor;
//		float childHalfLength = radius + halfLength;
//		float parentHalfLength;
//
//		//copy the parentIDX
//		int parentIdx = currentNodePtr->parentNodeIdx;
//		//get a pointer to the parent
//		PxArticulationLink* parentLinkPtr = NULL;
//		currentNodePtr->scaledGobalPos = worldPos.p;  //set this to world pos of node. If it's not the root it will get over writen when we know it's actual coordinate
//		if(parentIdx!= -1)
//		{
//			//if there is a parent then we need to work out our local position for the link
//			//get a pointer to the parent node
//			parentNode = *(nodeArray + parentIdx);
//			//get a pointer to the link for the parent
//			parentLinkPtr = parentNode->linkPtr;
//			parentHalfLength = (parentNode->radius + parentNode->halfLength) *scaleFactor;
//
//			//work out the local position of the node
//			PxVec3 currentRelative = currentNodePtr->childLinkPos * currentNodePtr->globalRotation.rotate(PxVec3(childHalfLength,0,0));
//			PxVec3 parentRelative = - currentNodePtr->parentLinkPos * parentNode->globalRotation.rotate(PxVec3(parentHalfLength,0,0));
//			currentNodePtr->scaledGobalPos = parentNode->scaledGobalPos- (parentRelative + currentRelative);
//		}
//
//		//build the transform for the link
//		PxTransform linkTransform = PxTransform(currentNodePtr->scaledGobalPos,currentNodePtr->globalRotation) ;
//		//create the link in the articulation
//		PxArticulationLink* link = articulation->createLink(parentLinkPtr, linkTransform);
//
//		//add the pointer to this link into the ragdoll data so we have it for later when we want to link to it
//		currentNodePtr->linkPtr = link;
//		float jointSpace = .01f; //allows us to set a gap between joints
//		float capsuleHalfLength = (halfLength>jointSpace?halfLength-jointSpace:0)+.01f; 
//		PxCapsuleGeometry capsule(radius,capsuleHalfLength);
//		link->createShape(capsule,*ragdollMaterial); //adds a capsule collider to the link
//		PxRigidBodyExt::updateMassAndInertia(*link, 50.0f);  //adds some mass to the link
//
//		if(parentIdx!= -1)
//		{
//			//get the pointer to the joint from the link
//			PxArticulationJoint *joint = link->getInboundJoint();
//			//get the relative rotation of this link
//			PxQuat frameRotation = parentNode->globalRotation.getConjugate() * currentNodePtr->globalRotation;
//			//set the parent contraint frame
//			PxTransform parentConstraintFrame = PxTransform(PxVec3(currentNodePtr->parentLinkPos * parentHalfLength,0,0),frameRotation);
//			//set the child constraint frame (this the constraint frame of the newly added link)
//			PxTransform thisConstraintFrame = PxTransform(PxVec3(currentNodePtr->childLinkPos * childHalfLength,0,0));
//			//set up the poses for the joint so it is in the correct place
//			joint->setParentPose(parentConstraintFrame);
//			joint->setChildPose(thisConstraintFrame);
//
//			//set up some constraints to stop it flopping around
//			joint->setSpring(20);
//			joint->setDamping(100);
//			joint->setSwingLimitEnabled(true);
//			joint->setSwingLimit(0.4f,0.4f);
//			joint->setTwistLimit(.4f,.4f);
//			joint->setTwistLimitEnabled(true);
//		}
//		currentNode++;
//	}
//
//	//put it to sleep so we can see it in it's starting pose
//	articulation->putToSleep();
//	return articulation;
//}

//add our ball gun so we can shoot at the ragdolls
//void MaddollTut::tutorial_3_ballGun()
//{
//	float muzzleSpeed = -50;
//	GLFWwindow* window = glfwGetCurrentContext();
//	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !GLFWMouseButton1Down)
//	{
//		GLFWMouseButton1Down = true;
//		PxSphereGeometry sphere(.5);
//		//get the camera position from the camera matrix
//		glm::vec3 position(m_cameraMatrix[3]);
//		//get the camera rotationfrom the camera matrix
//		glm::vec3 direction(m_cameraMatrix[2]);
//		physx::PxVec3 velocity = physx::PxVec3(direction.x,direction.y,direction.z)* muzzleSpeed;
//		float density = 5;
//		PxTransform transform(PxVec3(position.x,position.y,position.z),PxQuat::createIdentity());
//		PxRigidDynamic *dynamicActor = PxCreateDynamic(*m_physX_Variables->m_Physics, transform, sphere,*m_physX_Variables->m_PhysicsMaterial, density);
//		dynamicActor->setLinearVelocity(velocity,true);
//		m_physX_Variables->m_PhysicsScene->addActor(*dynamicActor);
//		m_PhysXActors.push_back(dynamicActor);
//	}
//	if (!glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) )
//	{
//		GLFWMouseButton1Down = false;
//	}
//	int index = 0;
//}
