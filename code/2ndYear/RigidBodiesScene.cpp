#include "RigidBodiesScene.h"

#include <GLFW\glfw3.h>

//RigidBodiesScene::RigidBodiesScene(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
//{
//	// Ground Plane
//	PxTransform pose  = PxTransform(PxVec3(	0.0f,	0,  0.0f),	PxQuat(PxHalfPi, PxVec3(0.0f,  0.0f, 1.0f)));
//	//PxRigidStatic* plane  = PxCreateStatic(*m_physX_Variables->m_Physics, pose,  PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
//	//m_physX_Variables->m_PhysicsScene->addActor(*plane);
//
//	// Player Capsule
//	PxCapsuleGeometry capsule(1,2);
//    //set it's initial transform and set it vertical.
//    m_startingPlayerPos = PxTransform(PxVec3(2,10,20),PxQuat(11/7.0f,PxVec3(0,0,1)));
//	m_playerActor = PxCreateDynamic(*m_physX_Variables->m_Physics, m_startingPlayerPos, capsule,*m_physX_Variables->m_PhysicsMaterial, 1);	
//	//add it to the physX scene
//	m_physX_Variables->m_PhysicsScene->addActor(*m_playerActor);
//	m_PhysXActors.push_back(m_playerActor);
//	m_playerActor->setName("Player");
//	m_playerActor->setLinearDamping(1);
//
//	setupFiltering(m_playerActor,FilterGroup::ePLAYER,FilterGroup::eGROUND);  //set up the collision filtering for our player
//
//	m_StaticObjects.push_back(new StaticObject(3,1,20,2,1.0f,4,0,"Platform"));
//	m_StaticObjects.push_back(new StaticObject(10,1,20,2,1.0f,2,0,"Platform"));
//	m_StaticObjects.push_back(new StaticObject(17,2,20,2,2.0f,2,0,"Platform"));
//	m_StaticObjects.push_back(new StaticObject(25,4,28,10,4.0f,2,0,"Platform"));
//	m_StaticObjects.push_back(new StaticObject(25,10,37,0.5f,2,0.5f,1,"Pickup1"));
//
//	addPlatforms();
//		
//	setupFiltering(m_playerActor,FilterGroup::ePLAYER,FilterGroup::eGROUND | FilterGroup::ePLATFORM);  //set up the collision filtering for our player
//
//	//staticObject is the PxRigidStatic actor we want to turn into a trigger	
//}
//
//RigidBodiesScene::~RigidBodiesScene(void)
//{
//	for(auto actor : m_StaticObjects)
//	{
//		delete actor;
//	}
//}
//
//void RigidBodiesScene::update(float a_deltaTime)
//{
//	controlPlayer(a_deltaTime);
//}
//
//void RigidBodiesScene::render(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
//{
//	for (auto actor : m_PhysXActors)
//	{
//		PxU32 nShapes = actor->getNbShapes();
//		PxShape** shapes = new PxShape*[nShapes];
//		actor->getShapes(shapes, nShapes);
//		// Render all the shapes in the physx actor (for early tutorials there is just one)
//		while (nShapes--)
//		{
//			 addWidget(shapes[nShapes],actor); 
//		}
//		delete [] shapes;
//	}
//}
//
//void RigidBodiesScene::controlPlayer(float a_deltaTime)
//{
//	PxTransform pose = m_playerActor->getGlobalPose(); //get the pose from PhysX
//	pose.q = PxQuat(11/7.0f,PxVec3(0,0,1));  //force the actor rotation to vertical
//	m_playerActor->setGlobalPose(pose); //reset the actor pose
//	//set linear damping on our actor so it slows down when we stop pressing the ke
//
//	GLFWwindow* window = glfwGetCurrentContext();
//
//	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
//	{
//		m_playerActor->addForce(PxVec3(100,0,0));
//	}
//
//	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
//	{
//		m_playerActor->addForce(PxVec3(-100,0,0));
//	}
//
//	if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
//	{
//		m_playerActor->addForce(PxVec3(0,0,-100));
//	}
//
//	if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
//	{
//		m_playerActor->addForce(PxVec3(0,0,100));
//	}
//
//	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//	{
//		m_playerActor->addForce(PxVec3(0,1000,0));
//	}
//}
//
//void RigidBodiesScene::addPlatforms()
//{
//	for(auto staticObjectPtr : m_StaticObjects)
//	{
//		PxBoxGeometry box(staticObjectPtr->extents);
//		PxTransform pose = PxTransform( staticObjectPtr->centre);
//		PxRigidStatic * staticObject = PxCreateStatic(*m_physX_Variables->m_Physics,pose,box,*m_physX_Variables->m_PhysicsMaterial);
//		
//		if(staticObjectPtr->trigger)
//		{
//			PxShape * objectShape;
//			staticObject->getShapes(&objectShape, 1);
//			objectShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
//			objectShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
//			
//		}
//
//		//add it to the physX scene
//		m_physX_Variables->m_PhysicsScene->addActor(*staticObject);
//	
//		m_PhysXActors.push_back(staticObject);
//		staticObject->setName(staticObjectPtr->name);
//		setupFiltering(staticObject,FilterGroup::ePLATFORM,FilterGroup::ePLAYER);
//	}
//}
//
////helper function to set up filtering
//void RigidBodiesScene::setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask)
//{
//    PxFilterData filterData;
//    filterData.word0 = filterGroup; // word0 = own ID
//    filterData.word1 = filterMask;  // word1 = ID mask to filter pairs that trigger a contact callback;
//    const PxU32 numShapes = actor->getNbShapes();
//    PxShape** shapes = (PxShape**)_aligned_malloc(sizeof(PxShape*)*numShapes,16);
//    actor->getShapes(shapes, numShapes);
//    for(PxU32 i = 0; i < numShapes; i++)
//    {
//            PxShape* shape = shapes[i];
//            shape->setSimulationFilterData(filterData);
//    }
//    _aligned_free(shapes);
//}