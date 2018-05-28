#include "PhysXTutorials.h"

#include "Gizmos.h"
#include "Utilities.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "tutorial1Scene.h"
#include "RigidBodiesScene.h"
#include "PrimitiveHierarchiesAndRays.h"
#include "JointAndSprings.h"
#include "MoreJointsAndHierarchies.h"
#include "SoftBodies.h"
#include "Particles.h"
#include "ragdoll.h"

#include "PhysXVariables.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

//PxFilterFlags myFilterShader(
//        PxFilterObjectAttributes a_attributes0, PxFilterData a_filterData0,
//        PxFilterObjectAttributes a_attributes1, PxFilterData a_filterData1,
//        PxPairFlags& a_pairFlags, const void* a_constantBlock, PxU32 a_constantBlockSize)
//{
//    // let triggers through
//    if(PxFilterObjectIsTrigger(a_attributes0) || PxFilterObjectIsTrigger(a_attributes1))
//    {
//            a_pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
//            return PxFilterFlag::eDEFAULT;
//    }
//    // generate contacts for all that were not filtered above
//    a_pairFlags = PxPairFlag::eCONTACT_DEFAULT;
//    // trigger the contact callback for pairs (A,B) where
//    // the filtermask of A contains the ID of B and vice versa.
//    if((a_filterData0.word0 & a_filterData1.word1) && (a_filterData1.word0 & a_filterData0.word1))
//            a_pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
//
//    return PxFilterFlag::eDEFAULT;
//}

PhysXTutorials::PhysXTutorials()
{

}

PhysXTutorials::~PhysXTutorials()
{
	
}

bool PhysXTutorials::onCreate(int a_argc, char* a_argv[]) 
{
	//m_physX_Variables = new PhysXVariables();
	//m_physX_Variables->m_DefaultFilterShader = PxDefaultSimulationFilterShader;
	//m_physX_Variables->m_DefaultFilterShader = myFilterShader;

	// initialise the Gizmos helper class
	Gizmos::create(100000,100000);

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	setUpPhysXTutorial();
	setUpVisualDebugger();

	// Rigidbodies and character
	//m_scenes.push_back(new RigidBodiesScene(m_physX_Variables));
	
	// Tank and height map
	//m_scenes.push_back(new PrimitiveHierarchiesAndRays(m_physX_Variables));

	// Soft Bodies
	//m_scenes.push_back(new SoftBodies(m_physX_Variables));

	// Joints and springs
	//m_scenes.push_back(new JointAndSprings(m_physX_Variables));
	
	// Particles/Fluid
	//m_scenes.push_back(new ParticleTutorial(m_physX_Variables));

	// Ragdoll
	//m_scenes.push_back(new MaddollTut(m_physX_Variables));

	return true;
}

void PhysXTutorials::onUpdate(float a_deltaTime) 
{
	upDatePhysx();

	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
	//for ( int i = 0 ; i < 21 ; ++i )
	//{
	//	Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//	
	//	Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	for(auto scene : m_scenes)
	{
		scene->update(a_deltaTime);
		((PrimitiveHierarchiesAndRays *)scene)->pickingExample1(m_cameraMatrix);
	}
}

void PhysXTutorials::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	for(auto scene : m_scenes)
	{
		scene->render(m_projectionMatrix, viewMatrix);
	}

	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void PhysXTutorials::onDestroy()
{
	for(auto scene : m_scenes)
	{
		delete scene;
	}

	// clean up anything we created
	Gizmos::destroy();

	cleanUpVisualDebugger();
	
	//delete m_physX_Variables;
	//m_physX_Variables = nullptr;
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	{
		// explicitly control the creation of our application
		AIE_2ND_YEAR::Application* app = new PhysXTutorials();
		
		if (app->create("AIE - PhysXTutorials",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
			app->run();
			
		// explicitly control the destruction of our application
		delete app;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

void PhysXTutorials::setUpPhysXTutorial()
{
	//m_physX_Variables->m_myCallback = new myAllocator();
	//m_physX_Variables->m_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,*m_physX_Variables->m_myCallback, m_physX_Variables->m_DefaultErrorCallback);
	//m_physX_Variables->m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_physX_Variables->m_PhysicsFoundation, PxTolerancesScale());
	//m_physX_Variables->m_PhysicsCooker = PxCreateCooking(PX_PHYSICS_VERSION, *m_physX_Variables->m_PhysicsFoundation, PxCookingParams(PxTolerancesScale()));
	//PxInitExtensions(*m_physX_Variables->m_Physics);
	////create physics material
	//m_physX_Variables->m_PhysicsMaterial = m_physX_Variables->m_Physics->createMaterial(0.5f,0.5f,0.6f);
	//PxSceneDesc sceneDesc(m_physX_Variables->m_Physics->getTolerancesScale());
	//sceneDesc.gravity = PxVec3(0,-9.8f,0);
	//sceneDesc.filterShader = m_physX_Variables->m_DefaultFilterShader;
	//sceneDesc.filterShader = myFilterShader;
	//m_physX_Variables->m_CPUDispatcher = PxDefaultCpuDispatcherCreate(3);
	//sceneDesc.cpuDispatcher = m_physX_Variables->m_CPUDispatcher;
	//
	//m_physX_Variables->m_PhysicsScene = m_physX_Variables->m_Physics->createScene(sceneDesc);
	//
	//m_physX_Variables->m_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	//m_physX_Variables->m_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	//
	//m_physX_Variables->m_mycollisionCallBack = new MycollisionCallBack();  //instantiate our class to overload call backs
	//m_physX_Variables->m_PhysicsScene->setSimulationEventCallback(m_physX_Variables->m_mycollisionCallBack); //tell the scene to use our call back class
}

void PhysXTutorials::upDatePhysx()
{
	//m_physX_Variables->m_PhysicsScene->simulate( 1/60.f );
	//while (m_physX_Variables->m_PhysicsScene->fetchResults() == false)
	//{
	//// don’t need to do anything here yet but we still need to do the fetch
	//}
}

void PhysXTutorials::setUpVisualDebugger()
{
  //// check if PvdConnection manager is available on this platform
  //if (NULL == m_physX_Variables->m_Physics->getPvdConnectionManager())
  //    return;
  //// setup connection parameters
  //const char*     pvd_host_ip = "127.0.0.1";  // IP of the PC which is running PVD
  //int             port        = 5425;         // TCP port to connect to, where PVD is listening
  //unsigned int    timeout     = 100;          // timeout in milliseconds to wait for PVD to respond,
  //                                            // consoles and remote PCs need a higher timeout.
  //PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerConnectionFlag::Debug
  //    | PxVisualDebuggerConnectionFlag::Profile | PxVisualDebuggerConnectionFlag::Memory;
  //// and now try to connect
	//    m_physX_Variables->m_PVDConnection = PxVisualDebuggerExt::createConnection(m_physX_Variables->m_Physics->getPvdConnectionManager(),
	//		pvd_host_ip, port, timeout, connectionFlags);
  ////    pvd_host_ip, port, timeout, connectionFlags));			
}

void PhysXTutorials::cleanUpVisualDebugger()
{
	//if(m_physX_Variables->m_PVDConnection)
	//{
	//	m_physX_Variables->m_PVDConnection->release();
	//}
}