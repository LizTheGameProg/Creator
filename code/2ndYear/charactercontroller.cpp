#include "charactercontroller.h"
#include <string.h>
#include <iostream>
//#include<PxToolkit.h>
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
#include <glm/ext.hpp>
#include <SOIL.h>
#include <string.h>

//using namespace std;
//using namespace physx;

//PxFoundation* g_PhysicsFoundation = nullptr;
//PxPhysics* g_Physics = nullptr;
//PxScene* g_PhysicsScene = nullptr;
//PxControllerManager* gCharacterManager;
//PxController* gPlayerController;
//PxDefaultErrorCallback gDefaultErrorCallback;
//PxDefaultAllocator gDefaultAllocatorCallback;
//PxSimulationFilterShader gDefaultFilterShader = PxDefaultSimulationFilterShader;
//PxMaterial* g_PhysicsMaterial = nullptr;
//PxCooking* g_PhysicsCooker = nullptr;

//List of our actors
//std::vector<PxRigidActor*> g_PhysXActors;

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

CharacterControllerTutorial::CharacterControllerTutorial()
{

}

CharacterControllerTutorial::~CharacterControllerTutorial()
{
}

//class myAllocator: public PxAllocatorCallback
//{
//public:
//        virtual ~myAllocator() {}
//        virtual void* allocate(size_t size, const char* typeName, const char* filename, int line)
//		{
//			void* pointer = _aligned_malloc(size,16);
//			return pointer;
//		}
//        virtual void deallocate(void* ptr)
//		{
//			 _aligned_free(ptr);
//		}
//};

//void CharacterControllerTutorial::setUpVisualDebugger()
//{
//  // check if PvdConnection manager is available on this platform
//  if (NULL == g_Physics->getPvdConnectionManager())
//      return;
//  // setup connection parameters
//  const char*     pvd_host_ip = "127.0.0.1";  // IP of the PC which is running PVD
//  int             port        = 5425;         // TCP port to connect to, where PVD is listening
//  unsigned int    timeout     = 100;          // timeout in milliseconds to wait for PVD to respond,
//                                              // consoles and remote PCs need a higher timeout.
//  PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerConnectionFlag::Debug
//      | PxVisualDebuggerConnectionFlag::Profile | PxVisualDebuggerConnectionFlag::Memory;
//  // and now try to connect
//	    PxVisualDebuggerExt::createConnection(g_Physics->getPvdConnectionManager(),
//			pvd_host_ip, port, timeout, connectionFlags);
//}
//
//bool CharacterControllerTutorial::onCreate(int a_argc, char* a_argv[]) 
//{
//	m_file = NULL;
//
//	// initialise the Gizmos helper class
//	Gizmos::create(100000,100000);
//	setUpPhysXTutorial();
//	// create a world-space matrix for a camera
//	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,2,1),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
//	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
//	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.5f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 10000.0f);
//	// set the clear colour and enable depth testing and backface culling
//	glClearColor(0.25f,0.25f,0.25f,1);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	return true;
//}
//
//void CharacterControllerTutorial::setUpPhysXTutorial()
//{
//	gravity = -10.0f;  //sets gravity here so we have access to it in our player controller
//	//instantiate our memory allocator
//	PxAllocatorCallback *myCallback = new myAllocator();
//	g_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,*myCallback, gDefaultErrorCallback);
//	g_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxTolerancesScale());
//	g_PhysicsCooker = PxCreateCooking(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxCookingParams(PxTolerancesScale()));
//	PxInitExtensions(*g_Physics);
//	//create physics material
//	g_PhysicsMaterial = g_Physics->createMaterial(0.2f,0.2f,1.0f);
//	PxSceneDesc sceneDesc(g_Physics->getTolerancesScale());
//	sceneDesc.gravity = PxVec3(0,gravity,0);
//	//sceneDesc.gravity = PxVec3(0,0,0);
//	sceneDesc.filterShader =  &physx::PxDefaultSimulationFilterShader;
//	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
//	g_PhysicsScene = g_Physics->createScene(sceneDesc);
//	g_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
//	setUpVisualDebugger();
//	tutorial_14(); 
//
//}
//
////class to handle collisions between character controller and world.
//class MyControllerHitReport: public PxUserControllerHitReport 
//{
//	CharacterControllerTutorial* controller;
//
//	//overload the onShapeHit function
//	virtual void 	onShapeHit (const PxControllerShapeHit &hit)
//	{
//		//gets a reference to a structure which tells us what has been hit and where
//		//get the acter from the shape we hit
//		PxRigidActor* actor = &(hit.shape->getActor());
//		//get the normal of the thing we hit and store that in our contact normal so the player controller can respond correctly
//		controller->playerContactNormal = hit.worldNormal;
//		//try to cast to a dynamic actor
//		PxRigidDynamic* myActor = actor->is<PxRigidDynamic>();
//		if(myActor)
//		{
//			//if successful then this is where we can apply forces
//			//this is where we can apply forces to things we hit
//		}
//	}
// 	//other collision functions which we must overload but we don't do anything with at the moment
//	//these handle collision with other controllers and hitting obstacles
//	virtual void 	onControllerHit (const PxControllersHit &hit){};
// 	//Called when current controller hits another controller. More...
//	virtual void 	onObstacleHit (const PxControllerObstacleHit &hit){};
//	//Called when current controller hits a user-defined obstacl
//
//public:
//	//contructor which takes a pointer to the class which instantiated this one
//	MyControllerHitReport(CharacterControllerTutorial* _controller):PxUserControllerHitReport()
//	{
//		controller = _controller;
//	}
//} ;
//
//
////create a simple test scene
//void CharacterControllerTutorial::addTestEnvironment()
//{
//	//four static boxes to demonstrate collisions
//	PxBoxGeometry box1(1,1,1);
//	PxBoxGeometry box2(2,2,2);
//	PxBoxGeometry box3(2,.5,2);
//	PxBoxGeometry box4(2,.25,2);
//	float density = .1;
//	PxMaterial*  boxMaterial = g_Physics->createMaterial(.5, .5, .5);   
//	PxTransform pose = PxTransform( PxVec3(0.0f, -2, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
//	PxRigidStatic* plane = PxCreateStatic(*g_Physics, pose,PxPlaneGeometry(), *g_PhysicsMaterial);
//	//add it to the physX scene
//
//	//and a plane as the ground
//	g_PhysicsScene->addActor(*plane);
//		plane->setName("ground");
//
//	pose = PxTransform( PxVec3(4.0f, -1, 0.0f));
//	PxRigidStatic* box = PxCreateStatic(*g_Physics,pose,box1,*boxMaterial);
//	g_PhysicsScene->addActor(*box);
//	g_PhysXActors.push_back(box);
//
//	pose = PxTransform( PxVec3(8.0f, 0, 0.0f));
//	 box = PxCreateStatic(*g_Physics,pose,box2,*boxMaterial);
//	g_PhysicsScene->addActor(*box);
//	g_PhysXActors.push_back(box);
//	
//	pose = PxTransform( PxVec3(12.0f, -1.5, 0.0f));	
//	box = PxCreateStatic(*g_Physics,pose,box3,*boxMaterial);
//	g_PhysicsScene->addActor(*box);
//	g_PhysXActors.push_back(box);
//
//	pose = PxTransform( PxVec3(16.0f, -1.75, 0.0f));	
//	box = PxCreateStatic(*g_Physics,pose,box4,*boxMaterial);
//	g_PhysicsScene->addActor(*box);
//	g_PhysXActors.push_back(box);
//}
//
//void CharacterControllerTutorial::tutorial_14()
//{
//	//instantiate a controler to handle collisions between player controller and world
//	MyControllerHitReport* myHitReport= new  MyControllerHitReport(this);
//	//create a character manager
//	gCharacterManager = PxCreateControllerManager(*g_PhysicsFoundation);
//	//describe our controller...
//	PxCapsuleControllerDesc desc;
//	desc.height = 1.6;
//	desc.radius = .4;
//	desc.position.set(0,0,0);
//	desc.material = g_PhysicsMaterial;
//	desc.callback = myHitReport;  //connect it to our collision detection routine
//	desc.density = 10;
//	//create the layer controller
//	gPlayerController = gCharacterManager->createController(*g_Physics,g_PhysicsScene,desc);
//	gPlayerController->setPosition(PxExtendedVec3(0,0,0));
//
//	//set up some variables to control our player with
//	characterYVelocity = 0;
//	characterRotation = 0;
//	playerContactNormal = PxVec3(0,0,0);
//
//	//addStaticHeightMapCollision(PxTransform(PxVec3(-200,0,-200)));  //comment this in to enable our simple test scene
//	addTestEnvironment();
//}
//
////spawn boxes to demonstrate that the linear motor is physical thing which follows the laws of physics
//void spawnBoxes(float delta)
//{
//	PxBoxGeometry box(1,1,1);
//	static float count = 0;
//	float density = .1;
//	PxMaterial*  boxMaterial = g_Physics->createMaterial(.1, .1, 0);   
//	count += delta;
//	if(count > 1)
//	{
//		PxTransform boxTransform(PxVec3(8,20,0));
//		PxRigidDynamic* dynamicBox = PxCreateDynamic(*g_Physics,boxTransform,box,*boxMaterial,density);
//		g_PhysicsScene->addActor(*dynamicBox);
//		g_PhysXActors.push_back(dynamicBox);
//		count = 0;
//	}
//}
//
////simple third person control
//void thirdPersonCamera(glm::mat4& a_transform, glm::vec3 target, glm::vec3 offset, float viewAngle, float a_deltaTime)
//{
//	//define the axis to rotate camera about, we just do it around y
//	const glm::vec3 vUp2(0,1,0);
//	//create a rotational matrix using the character rotation
//	glm::mat4 mMat = glm::axisAngleMatrix( vUp2, (float)viewAngle );
//	//work out the camera position from the look at target, offset and rotation matrix
//	glm::vec3 cameraPos = target+(mMat * glm::vec4(offset,1)).xyz;
//	//move the camera transform
//	a_transform = glm::inverse( glm::lookAt(cameraPos,target, glm::vec3(0,1,0)) );
//}
//
//
//
//
//void CharacterControllerTutorial::onUpdate(float a_deltaTime) 
//{
//	Gizmos::clear();
//	if(a_deltaTime ==0)
//	{
//		a_deltaTime = 1/50;
//	}
//	static float count = 1;
//	count+= .01f;
//	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );
//	// quit our application when escape is pressed
//	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		quit();
//	upDatePhysx(a_deltaTime);
////	spawnBoxes(a_deltaTime); //add this back in to demonstrate player hitting boxes
//	addHeightMap();
//	controlPlayer(a_deltaTime);
//}
//
////convert from extended physx vector to opengl vector3
//glm::vec3 Px2GLM(PxExtendedVec3 in)
//{
//	return glm::vec3(in.x,in.y,in.z);
//}
//
//void CharacterControllerTutorial::controlPlayer(float a_deltaTime)
//{
//	glm::vec3 cameraOffset(4,3,0); //position of camera relative to player
//	bool onGround; //set to true if we are on the ground
//	//control the camera
//	thirdPersonCamera(m_cameraMatrix, Px2GLM(gPlayerController->getPosition()), cameraOffset, characterRotation, a_deltaTime);
//	float movementSpeed = .1f; //forward and back movement speed
//	float rotationSpeed = .05f; //turn speed
//	float jumpStartingSpeed = 0.5f;//initial velocity of jump
//	PxVec3 velocity(0,characterYVelocity,0); 
//
//	//check if we have a contact normal.  if y is greater than .3 we assume this is solid ground
//	//note this is a rather primitive way to do this.  Can you do better?
//	if(playerContactNormal.y > .3f)
//	{
//		characterYVelocity = -0.1;
//		onGround = true;
//	}
//	else
//	{
//		characterYVelocity+= gravity * a_deltaTime * 0.5f;
//		onGround = false;
//	}
//	//make sure we clear the contact normal so we don't respond to it next frame if there is no collision
//	playerContactNormal = PxVec3(0,0,0);
//	const PxVec3 up(0,1,0);
//	PxQuat rotation(characterRotation,up);//create a rotation so we can spin the controls relative to player facing
//	//scan the keys and set up our intended velocity based on a global transform
//	if (glfwGetKey(m_window,GLFW_KEY_UP) == GLFW_PRESS)
//	{
//		velocity.x -= movementSpeed;
//	}
//	if (glfwGetKey(m_window,GLFW_KEY_DOWN) == GLFW_PRESS)
//	{
//		velocity.x += movementSpeed;
//	}
//	if (glfwGetKey(m_window,GLFW_KEY_RIGHT) == GLFW_PRESS)
//	{
//		characterRotation -= rotationSpeed;
//	}
//	if (glfwGetKey(m_window,GLFW_KEY_LEFT) == GLFW_PRESS)
//	{
//		characterRotation += rotationSpeed;
//	}
//	if (glfwGetKey(m_window,GLFW_KEY_SPACE) == GLFW_PRESS)
//	{
//		if(onGround)
//		{
//			characterYVelocity = jumpStartingSpeed;
//		}
//	}
//	float minDistance = 0.001f;
//	PxControllerFilters filter;
//	//make controls relative to player facing
//	gPlayerController->move(rotation.rotate(velocity),minDistance,a_deltaTime,filter);
//}
//
//void CharacterControllerTutorial::upDatePhysx(float a_deltaTime)
//{
//	a_deltaTime = 1/60.0f;
//	g_PhysicsScene->simulate( a_deltaTime );
//	while (g_PhysicsScene->fetchResults() == false)
//	{
//	// don’t need to do anything here yet but we have to fetch results
//	}
//	// Add widgets to represent all the phsyX actors which are in the scene
//	for (auto actor:g_PhysXActors)
//	{
//		{
//			PxU32 nShapes = actor->getNbShapes();
//			PxShape** shapes = new PxShape*[nShapes];
//			actor->getShapes(shapes, nShapes);
//			// Render all the shapes in the physx actor (for early tutorials there is just one)
//			while (nShapes--)
//			{
//				 addWidget(shapes[nShapes],actor); 
//			}
//			delete [] shapes;
//		}
//	}
//
//	//if we have a player controller then render the collision capsule in the scene
//	//we get an actor out of it and the we can treat it just like any other actor
//	if(gPlayerController)
//	{
//		auto playerActor = gPlayerController->getActor();
//		PxU32 nShapes = playerActor->getNbShapes();
//		PxShape** shapes = new PxShape*[nShapes];
//		playerActor->getShapes(shapes, nShapes);
//		// Render all the shapes in the physx actor (for early tutorials there is just one)
//		while (nShapes--)
//		{
//				addWidget(shapes[nShapes],playerActor); 
//		}
//		delete [] shapes;
//	}
//}
//
//
//void CharacterControllerTutorial::addWidget(PxShape* shape,PxRigidActor* actor) 
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
//void CharacterControllerTutorial::addSphere(PxShape* pShape,PxRigidActor* actor) 
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
//	Gizmos::addSphere(position,10,10,radius,glm::vec4(1,0,1,1));
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
//void CharacterControllerTutorial::addCapsule(PxShape* pShape,PxRigidActor* actor) 
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
//void CharacterControllerTutorial::addBox(PxShape* pShape,PxRigidActor* actor) 
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
//
//
//void CharacterControllerTutorial::onDraw() 
//{
//	// clear the backbuffer
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	// get the view matrix from the world-space camera matrix
//	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
//
//	// draw the gizmos from this frame
//	Gizmos::draw(viewMatrix, m_projectionMatrix);
//}
//
//void CharacterControllerTutorial::onDestroy()
//{
//	// clean up anything we created
//	Gizmos::destroy();
//	cleanUpPhsyx();
//}
//
//void CharacterControllerTutorial::cleanUpPhsyx()
//{
//	g_PhysicsScene->release();
//	g_Physics->release();
//	g_PhysicsFoundation->release();
//}
//
//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	Application* app = new CharacterControllerTutorial();
//	if (app->create("AIE - Physx Tutorial",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//	// explicitly control the destruction of our application
//	delete app;
//	return 0;
//}
//void CharacterControllerTutorial::addHeightMap()
//{
//	if(!heightMap.enabled)
//	{
//		return;
//	}
//	glm::vec4 colour (0,0.5f,0,1);
//	PxHeightFieldSample* samplePtr;
//	for(int row = 0;row<heightMap.numRows-1;row++)
//	{
//		for(int col = 0;col<heightMap.numCols-1;col++)
//		{
//			samplePtr = heightMap.samples + col + (row*heightMap.numCols);
//			glm::vec3 vert1;
//			vert1.y = samplePtr->height * heightMap.heightScale;
//			vert1.x = row * heightMap.rowScale;
//			vert1.z = col * heightMap.colScale;
//			vert1+= heightMap.center;
//			
//			glm::vec3 vert2;
//			vert2.y = (samplePtr+(heightMap.numCols))->height * heightMap.heightScale;
//			vert2.x = (row+1) * heightMap.rowScale;
//			vert2.z = col * heightMap.colScale;
//			vert2+= heightMap.center;
//			
//			glm::vec3 vert3;
//			vert3.y = (samplePtr+1)->height * heightMap.heightScale;
//			vert3.x = row * heightMap.rowScale;
//			vert3.z = (col+1) * heightMap.colScale;
//			vert3+= heightMap.center;
//						
//			glm::vec3 vert4;
//			vert4.y = (samplePtr+heightMap.numCols+1)->height * heightMap.heightScale;
//			vert4.x = (row+1) * heightMap.rowScale;
//			vert4.z = (col+1) * heightMap.rowScale;
//			vert4+= heightMap.center;
//			//add lines
//			Gizmos::addLine( vert1, vert2, colour);
//			Gizmos::addLine(vert1, vert3, colour);
//			//complete the edge of the map
//			if(col == heightMap.numCols-2)
//			{
//				Gizmos::addLine( vert3, vert4, colour);
//			}
//			if(row == heightMap.numRows-2)
//			{
//				Gizmos::addLine( vert2, vert4, colour);
//			}
//			samplePtr++;
//		}
//	}
//}
//PxRigidStatic* CharacterControllerTutorial::addStaticHeightMapCollision(PxTransform transform)
//{
//	PxRigidStatic *staticObject;
//	PxBoxGeometry box(4,20,4);
//	staticObject = PxCreateStatic(*g_Physics,transform,box,*g_PhysicsMaterial);
//	heightMap.numRows = 150;
//	heightMap.numCols = 150;
//	heightMap.heightScale = .0012f;
//	heightMap.rowScale = 10; 
//	heightMap.colScale = 10;
//	heightMap.center = Px2GlV3(transform.p);
//	heightMap.samples = (PxHeightFieldSample*)_aligned_malloc(sizeof(PxHeightFieldSample)*(heightMap.numRows*heightMap.numCols),16);
//	heightMap.enabled = true;
//	//make height map
//	PxHeightFieldSample* samplePtr = heightMap.samples;
//	for(int row = 0;row<heightMap.numRows;row++)
//	{
//		for(int col = 0;col<heightMap.numCols;col++)
//		{
//			float height = sin(row/10.0f) * cos(col/10.0f);
//			samplePtr->height = height * 30000.0f;
//			samplePtr->materialIndex1 = 0;
//			samplePtr->materialIndex0 = 0;
//			samplePtr->clearTessFlag();
//			samplePtr++;
//		}
//	}
//	PxHeightFieldDesc hfDesc;
//	hfDesc.format             = PxHeightFieldFormat::eS16_TM;
//	hfDesc.nbColumns          = heightMap.numCols;
//	hfDesc.nbRows             = heightMap.numRows;
//	hfDesc.samples.data       = heightMap.samples;
//	hfDesc.samples.stride     = sizeof(PxHeightFieldSample);
//
//	PxHeightField* aHeightField = g_Physics->createHeightField(hfDesc);
//	PxHeightFieldGeometry hfGeom(aHeightField, PxMeshGeometryFlags(), heightMap.heightScale, heightMap.rowScale, heightMap.colScale);
//	PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(0, PxVec3(0.0f, 0.0f, 1.0f)));
//	staticObject->createShape((PxHeightFieldGeometry)hfGeom,*g_PhysicsMaterial,pose);
//	g_PhysicsScene->addActor(*staticObject);
//	staticObject->setName("HeightMap");
//	heightMap.actor = staticObject; 
//	return staticObject;
//}
