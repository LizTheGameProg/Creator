#include "Particles.h"
#include <string.h>
#include <iostream>
#include <vector>
//#include<PxToolkit.h>;
//#include "PxShape.h"
//#include "PxScene.h"
//#include "PxSceneQueryReport.h"
//#include "extensions/PxJoint.h"
//#include "PxRigidDynamic.h"
//#include "extensions/PxDistanceJoint.h"
//#include "extensions/PxSphericalJoint.h"
//#include "PxArticulationLink.h"
//#include "PxShape.h"
//#include "PxBatchQueryDesc.h"

bool GLFWMouseButton1Down = false;

//ParticleTutorial::ParticleTutorial(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
//{
//	m_file = NULL;
//	m_physX_Variables->m_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
//	m_physX_Variables->m_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
//	particleEmiter1 = NULL;
//	particleFluidEmitter = NULL;
//	tutorial_14b(); //particle system
//
//}
//
//ParticleTutorial::~ParticleTutorial()
//{
//	delete(particleFluidEmitter);
//}
//
//void ParticleTutorial::update(float a_DeltaTime)
//{
//	onUpdate(a_DeltaTime);
//}
//
//void ParticleTutorial::render(glm::mat4 a_ProjectionMatrix, glm::mat4 a_ViewMatrix)
//{
//	
//}
//
//void ParticleTutorial::tutorial_14b()
//{
//
//	//PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
//	//PxRigidStatic* plane = PxCreateStatic(*m_physX_Variables->m_Physics, pose,PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
//    //const PxU32 numShapes = plane->getNbShapes();
//	//m_physX_Variables->m_PhysicsScene->addActor(*plane);
//	//
//	//PxBoxGeometry side1(4.5,1,.5);
//	//PxBoxGeometry side2(.5,1,4.5);
//	//pose = PxTransform( PxVec3(0.0f, 0.5, 4.0f));
//	//PxRigidStatic* box = PxCreateStatic(*m_physX_Variables->m_Physics, pose,side1, *m_physX_Variables->m_PhysicsMaterial);
//	//m_physX_Variables->m_PhysicsScene->addActor(*box);
//	//m_PhysXActors.push_back(box);
//	//
//	//pose = PxTransform( PxVec3(0.0f, 0.5, -4.0f));
//	//box = PxCreateStatic(*m_physX_Variables->m_Physics, pose,side1, *m_physX_Variables->m_PhysicsMaterial);
//	//m_physX_Variables->m_PhysicsScene->addActor(*box);
//	//m_PhysXActors.push_back(box);
//	//
//	//pose = PxTransform( PxVec3(4.0f, 0.5, 0));
//	//box = PxCreateStatic(*m_physX_Variables->m_Physics, pose,side2, *m_physX_Variables->m_PhysicsMaterial);
//	//m_physX_Variables->m_PhysicsScene->addActor(*box);
//	//m_PhysXActors.push_back(box);
//	//
//	//pose = PxTransform( PxVec3(-4.0f, 0.5, 0));
//	//box = PxCreateStatic(*m_physX_Variables->m_Physics, pose,side2, *m_physX_Variables->m_PhysicsMaterial);
//	//m_physX_Variables->m_PhysicsScene->addActor(*box);
//	//m_PhysXActors.push_back(box);
//
//	//create our particle system
//
//	PxParticleFluid * pf;
//	// create particle system in PhysX SDK
//	// set immutable properties.
//	PxU32 maxParticles = 4000;
//	bool perParticleRestOffset = false;
//	pf = m_physX_Variables->m_Physics->createParticleFluid(maxParticles, perParticleRestOffset);
//	pf->setRestParticleDistance(.3f);
//	pf->setDynamicFriction(0.1);
//	pf->setStaticFriction(0.1);
//	//pf->setContactOffset(.3);
//	pf->setDamping(0.1);
//	pf->setParticleMass(.1);
//	pf->setRestitution(0);
//	pf->setParticleReadDataFlag(PxParticleReadDataFlag::eDENSITY_BUFFER,true);
//	pf->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY,true);
//	if (pf)
//	{
//        m_physX_Variables->m_PhysicsScene->addActor(*pf);
//		particleFluidEmitter = new ParticleFluidEmitter(maxParticles,PxVec3(0,9,27),pf,.01);
//	}
//}	
//
//void ParticleTutorial::tutorial_14a()
//{
//	PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
//	PxRigidStatic* plane = PxCreateStatic(*m_physX_Variables->m_Physics, pose,PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
//    const PxU32 numShapes = plane->getNbShapes();
//	// set immutable properties.
//
//	//reserve space for them
//	PxShape** shapes = (PxShape**)_aligned_malloc(sizeof(PxShape*)*numShapes,16);
//	//get them into our buffer
//    plane->getShapes(shapes, numShapes);
//	//set the plane up as a particle drain so when the particles touch it we can detect it and remove them
//	shapes[0]->setFlag(PxShapeFlag::ePARTICLE_DRAIN, true);
//	//add the plane to the physX scene
//	m_physX_Variables->m_PhysicsScene->addActor(*plane);
//	
//	//create our particle system
//	// set immutable properties.
//	PxU32 maxParticles = 4000;
//	bool perParticleRestOffset = false;
//	PxParticleSystem* ps;
//	// create particle system in PhysX SDK
//	ps = m_physX_Variables->m_Physics->createParticleSystem(maxParticles, perParticleRestOffset);
//	//various flags we can set/clear to get different effects
//	//  ps->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY,true);
//	//	ps->setDamping(.01);
//	//	ps->setRestitution(2);
//	//	ps->setActorFlag(PxActorFlag::eDISABLE_GRAVITY,true);
//	// add particle system to scene, if creation was successful
//	if (ps)
//	{
//        m_physX_Variables->m_PhysicsScene->addActor(*ps);
//		//create a particle emiter to make particles for our scene
//		particleEmiter1 = new ParticleEmitter(maxParticles,PxVec3(0,10,0),ps,.002f);
//	}
//}	
//
////spawn boxes to demonstrate collision with particles
//void ParticleTutorial::spawnBoxes(float delta)
//{
//	PxBoxGeometry box(.5,.5,.5);
//	static float count = -10;
//	float density = 1;
//	PxMaterial*  boxMaterial = m_physX_Variables->m_Physics->createMaterial(.5, .5, 0);   
//	count += delta;
//	if(count > 1)
//	{
//		PxTransform boxTransform(PxVec3(0,20,0));
//		boxTransform.p.x += (rand()%1000 - 500)/1000.0f;
//		boxTransform.p.z += (rand()%1000 - 500)/1000.0f;
//		PxRigidDynamic* dynamicBox = PxCreateDynamic(*m_physX_Variables->m_Physics,boxTransform,box,*boxMaterial,density);
//		m_physX_Variables->m_PhysicsScene->addActor(*dynamicBox);
//		m_PhysXActors.push_back(dynamicBox);
//		count = 0;
//	}
//}
//
//
////spawn boxes to demonstrate collision with particles
//void ParticleTutorial::spawnBalls(float delta)
//{
//	PxSphereGeometry ball(1);
//	static float count = -50;
//	float density = 2;
//	PxMaterial*  ballMaterial = m_physX_Variables->m_Physics->createMaterial(.8, .8, 0);   
//	count += delta;
//	if(count > 4)
//	{
//		PxTransform boxTransform(PxVec3(0,20,0));
//		boxTransform.p.x += (rand()%1000 - 500)/1000.0f;
//		boxTransform.p.z += (rand()%1000 - 500)/1000.0f;
//		PxRigidDynamic* dynamicBall = PxCreateDynamic(*m_physX_Variables->m_Physics,boxTransform,ball,*ballMaterial,density);
//		m_physX_Variables->m_PhysicsScene->addActor(*dynamicBall);
//		m_PhysXActors.push_back(dynamicBall);
//		count = 0;
//	}
//}
//
//void ParticleTutorial::onUpdate(float a_deltaTime) 
//{
//	//spawnBoxes(a_deltaTime); //add this back in to demonstrate things hitting boxes
//	//spawnBalls(a_deltaTime); //add this back in to demonstrate things hitting balls
//	//update the particle emiter
//	if(particleEmiter1)
//	{
//		particleEmiter1->upDate(a_deltaTime);
//		//render all our particles
//		particleEmiter1->renderParticles();
//	}
//
//	if(particleFluidEmitter)
//	{
//		particleFluidEmitter->upDate(a_deltaTime);
//		particleFluidEmitter->renderParticles();
//	}
//}
//
//void ParticleTutorial::addWidget(PxShape* shape,PxRigidActor* actor) 
//{ 
//    PxGeometryType::Enum type = shape->getGeometryType();
//    switch(type) 
//    {  
//		case PxGeometryType::eBOX:
//			addBox(shape,actor);
//		break;
//		case PxGeometryType::eSPHERE:
//			addSphere(shape,actor);
//		break;
//		case PxGeometryType::eCAPSULE:
//			addCapsule(shape,actor);
//		break;
//    } 
//} 
//
//
//void ParticleTutorial::addSphere(PxShape* pShape,PxRigidActor* actor) 
//{
//	PxSphereGeometry geometry;
//	float radius = 1;
//	//get the geometry for this PhysX collision volume
//	bool status = pShape->getSphereGeometry(geometry);
//	if(status)
//	{
//		radius = geometry.radius;
//	}
//	//get the transform for this PhysX collision volume
//	PxMat44 m(PxShapeExt::getGlobalPose(*pShape));
//	glm::mat4 M(m.column0.x, m.column0.y, m.column0.z, m.column0.w,
//	m.column1.x, m.column1.y, m.column1.z, m.column1.w,
//	m.column2.x, m.column2.y, m.column2.z, m.column2.w,
//	m.column3.x, m.column3.y, m.column3.z, m.column3.w);
//	glm::vec3 position;
//		 
//	position.x = m.getPosition().x;
//	position.y = m.getPosition().y;
//	position.z = m.getPosition().z;
//	//create a widget to represent it
//	Gizmos::addSphere(position,10,10,radius,glm::vec4(0,1,0,1));
//}
//
////helper function to convert PhysX matrix to Opengl 
//glm::mat4 Px2Glm(PxMat44 m)
//{
//	glm::mat4 M(m.column0.x, m.column0.y, m.column0.z, m.column0.w,
//	m.column1.x, m.column1.y, m.column1.z, m.column1.w,
//	m.column2.x, m.column2.y, m.column2.z, m.column2.w,
//	m.column3.x, m.column3.y, m.column3.z, m.column3.w);
//	return M;
//}
////helper function to convert PhysX vector to Opengl 
//glm::vec3   Px2GlV3(PxVec3 v1)
//{
//	glm::vec3 v2;
//	v2.x = v1.x;
//	v2.y = v1.y;
//	v2.z = v1.z;
//	return v2;
//}
//
//void ParticleTutorial::addCapsule(PxShape* pShape,PxRigidActor* actor) 
//{
//	//creates a gizmo representation of a capsule using 2 spheres and a cylinder
//	glm::vec4 colour(0,0,1,1);  //make our capsule blue
//	PxCapsuleGeometry capsuleGeometry;
//	float radius = 1; //temporary values whilst we try and get the real value from PhysX
//	float halfHeight = 1;;
//	//get the geometry for this PhysX collision volume
//	bool status = pShape->getCapsuleGeometry(capsuleGeometry);
//	if(status)
//	{
//		//this should always happen but just to be safe we check the status flag
//		radius = capsuleGeometry.radius; //copy out capsule radius
//		halfHeight = capsuleGeometry.halfHeight; //copy out capsule half length
//	}
//	//get the world transform for the centre of this PhysX collision volume
//	PxTransform transform = PxShapeExt::getGlobalPose(*pShape);
//	//use it to create a matrix
//	PxMat44 m(transform);
//	//convert it to an open gl matrix for adding our gizmos
//	glm::mat4 M = Px2Glm(m);
//	//get the world position from the PhysX tranform
//	glm::vec3 position = Px2GlV3(transform.p); 
//	glm::vec4 axis(halfHeight,0,0,0);	//axis for the capsule
//	axis = M * axis; //rotate axis to correct orientation
//	//add our 2 end cap spheres...
//	Gizmos::addSphere(position+axis.xyz,10,10,radius,colour);
//	Gizmos::addSphere(position-axis.xyz,10,10,radius,colour);
//	//the cylinder gizmo is oriented 90 degrees to what we want so we need to change the rotation matrix...
//	glm::mat4 m2 = glm::rotate(M,11/7.0f,0.0f,0.0f,1.0f); //adds an additional rotation onto the matrix
//	//now we can use this matrix and the other data to create the cylinder...
//	Gizmos::addCylinderFilled(position,radius,halfHeight,10,colour,&m2);
//}
//
//void ParticleTutorial::addBox(PxShape* pShape,PxRigidActor* actor) 
//{
//	//get the geometry for this PhysX collision volume
//	PxBoxGeometry geometry;
//	float width = 1, height = 1, length = 1;
//	bool status = pShape->getBoxGeometry(geometry);
//	if(status)
//	{
//		width = geometry.halfExtents.x;
//		height = geometry.halfExtents.y;
//		length = geometry.halfExtents.z;
//	}
//	//get the transform for this PhysX collision volume
//	PxMat44 m(PxShapeExt::getGlobalPose(*pShape));
//	glm::mat4 M(m.column0.x, m.column0.y, m.column0.z, m.column0.w,
//	m.column1.x, m.column1.y, m.column1.z, m.column1.w,
//	m.column2.x, m.column2.y, m.column2.z, m.column2.w,
//	m.column3.x, m.column3.y, m.column3.z, m.column3.w);
//	glm::vec3 position; 
//	//get the position out of the transform
//	position.x = m.getPosition().x;
//	position.y = m.getPosition().y;
//	position.z = m.getPosition().z;
//	glm::vec3 extents = glm::vec3(width,height,length);
//	glm::vec4 colour = glm::vec4(1,0,0,1);
//	if(actor->getName()!= NULL && strcmp(actor->getName(),"Pickup1")) //seriously horrid hack so I can show pickups a different colour
//	{
//		colour = glm::vec4(0,1,0,1);
//	}
//	//create our box gizmo
//	Gizmos::addAABBFilled(position,extents,colour,&M);
//}
