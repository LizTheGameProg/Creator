#include "Motors.h"
#include <string.h>
#include <iostream>
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

//Vehicle* gPlayerVehicle = NULL;
//
//PxD6Joint *gLinearJoint = NULL;

//using namespace std;
//
//using namespace physx;


//create some constants for axis of rotation to make definition of quaternions a bit neater
//const PxVec3 X_AXIS = PxVec3(1,0,0);
//const PxVec3 Y_AXIS = PxVec3(0,1,0);
//const PxVec3 Z_AXIS = PxVec3(0,0,1);


//PxFoundation* g_PhysicsFoundation = nullptr;
//PxPhysics* g_Physics = nullptr;
//PxScene* g_PhysicsScene = nullptr;

//PxDefaultErrorCallback gDefaultErrorCallback;
//PxDefaultAllocator gDefaultAllocatorCallback;
//PxSimulationFilterShader gDefaultFilterShader = PxDefaultSimulationFilterShader;
//PxMaterial* g_PhysicsMaterial = nullptr;
//PxCooking* g_PhysicsCooker = nullptr;

//List of our actors
//std::vector<PxRigidActor*> g_PhysXActors;

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720
//
//bool GLFWMouseButton1Down = false;


MotorTutorial::MotorTutorial()
{

}

MotorTutorial::~MotorTutorial()
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

//void MotorTutorial::setUpVisualDebugger()
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
//  //    pvd_host_ip, port, timeout, connectionFlags));
//}
//
//bool MotorTutorial::onCreate(int a_argc, char* a_argv[]) 
//{
//	m_file = NULL;
//
//	// initialise the Gizmos helper class
//	Gizmos::create(100000,100000);
//	setUpPhysXTutorial();
//	// create a world-space matrix for a camera
//	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,2,1),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
//	
//	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
//	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.5f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 10000.0f);
//
//	// set the clear colour and enable depth testing and backface culling
//	glClearColor(0.25f,0.25f,0.25f,1);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	return true;
//}
//
//void MotorTutorial::setUpPhysXTutorial()
//{
//	PxAllocatorCallback *myCallback = new myAllocator();
//	g_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION,*myCallback, gDefaultErrorCallback);
//	g_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxTolerancesScale());
//	g_PhysicsCooker = PxCreateCooking(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxCookingParams(PxTolerancesScale()));
//	PxInitExtensions(*g_Physics);
//	//create physics material
//	g_PhysicsMaterial = g_Physics->createMaterial(0.2f,0.2f,1.0f);
//	PxSceneDesc sceneDesc(g_Physics->getTolerancesScale());
//	sceneDesc.gravity = PxVec3(0,-10.0f,0);
//	//sceneDesc.gravity = PxVec3(0,0,0);
//	sceneDesc.filterShader =  &physx::PxDefaultSimulationFilterShader;
//	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
//	g_PhysicsScene = g_Physics->createScene(sceneDesc);
//	g_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
//	g_PhysicsScene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
//	setUpVisualDebugger();
//	tutorial_13(); //the vehicle
//	//tutorial_13a(); //the rotational motor
//	//tutorial_13b(); //the linear motor  
//}
//
//void MotorTutorial::tutorial_13()
//{
//	//create a vehcile
//	gPlayerVehicle = new Vehicle();
//	makeSimpleVehicle(PxTransform(PxVec3(0,0,0)),gPlayerVehicle);
//	//create a plane
//	PxTransform pose = PxTransform( PxVec3(0.0f, -.5, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
//	PxRigidStatic* plane = PxCreateStatic(*g_Physics, pose,PxPlaneGeometry(), *g_PhysicsMaterial);
//	//add it to the physX scene
//	g_PhysicsScene->addActor(*plane);
//}
//
////demonstrate rotational motors
//void MotorTutorial::tutorial_13a()
//{
//	PxMaterial*  boxMaterial = g_Physics->createMaterial(1, 1, 1);   
//	float boxHalfSize = 1;
//	float gap = .05f;
//	float density = 1;
//	//create two boxes
//	PxBoxGeometry box(boxHalfSize,boxHalfSize,boxHalfSize);
//	PxTransform box1Transform(PxVec3(0,0,0));
//	PxTransform box2Transform(PxVec3((boxHalfSize+gap)*2,0,0));
//
//	//one static box
//	PxRigidStatic* staticBox = PxCreateStatic(*g_Physics,box1Transform,box,*boxMaterial);
//	g_PhysicsScene->addActor(*staticBox);
//	g_PhysXActors.push_back(staticBox);
//	//one dynamic box
//	PxRigidDynamic* dynamicBox = PxCreateDynamic(*g_Physics,box2Transform,box,*boxMaterial,density);
//	g_PhysicsScene->addActor(*dynamicBox);
//	g_PhysXActors.push_back(dynamicBox);
//
//	//set up constraint frames so they are correctly positioned 
//	PxTransform constraintFrame1= PxTransform(PxVec3(boxHalfSize+gap,0,0));
//	PxTransform constraintFrame2 = PxTransform(PxVec3(-(boxHalfSize+gap),0,0));
//	PxRevoluteJoint *joint = NULL;
//	//create the revolute (axle) joint
//	joint = PxRevoluteJointCreate(*g_Physics,staticBox,constraintFrame1,dynamicBox,constraintFrame2); 
//	if(joint)
//	{
//		joint->setProjectionLinearTolerance(.1f);
//		joint->setProjectionAngularTolerance(.1f);
//		joint->setBreakForce(100000,100000);
//		joint->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true); //enable the drive
//		joint->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED,false);
//		joint->setDriveVelocity(1); //give it some drive
//	}
//
//	//add another box and join it to the second one with a bit of an offset
//	PxTransform constraintFrame1a= PxTransform(PxVec3(boxHalfSize+gap,1,0));
//	PxTransform constraintFrame2a = PxTransform(PxVec3(-(.2f+gap),-3,0));
//	PxBoxGeometry box2(.2f,4,.2f);
//	PxTransform box3Transform = box2Transform;
//	box3Transform.p.x += (boxHalfSize+gap)+ .2f;
//	box3Transform.p.y -= 3;
//	PxRigidDynamic* dynamicBox2 = PxCreateDynamic(*g_Physics,box3Transform,box2,*boxMaterial,density);
//	g_PhysicsScene->addActor(*dynamicBox2);
//	g_PhysXActors.push_back(dynamicBox2);
//	PxRevoluteJoint *joint2 = NULL;
//
//	//create another joint
//	joint2 = PxRevoluteJointCreate(*g_Physics,dynamicBox,constraintFrame1a,dynamicBox2,constraintFrame2a); 
//	if(joint2)
//	{
//		joint2->setProjectionLinearTolerance(.1f);
//		joint2->setProjectionAngularTolerance(.1f);
//		joint2->setBreakForce(100000,100000);
//		joint2->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
//		joint2->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED,false);
//		joint2->setDriveVelocity(3.3);
//	}
//
//
//
//}
//
//
////demonstrate our linear motor
//void MotorTutorial::tutorial_13b()
//{
//	PxMaterial*  boxMaterial = g_Physics->createMaterial(1, 1, 1);   
//	float boxHalfSize = 1;
//	float gap = .05f;
//	float density = 1;
//	float startPos = 5;
//	PxBoxGeometry box(boxHalfSize,boxHalfSize,boxHalfSize);
//	PxTransform box1Transform(PxVec3(0,1,0));
//	PxTransform box2Transform(PxVec3(startPos*2,1,0));
//
//	PxRigidStatic* staticBox = PxCreateStatic(*g_Physics,box1Transform,box,*boxMaterial);
//	g_PhysicsScene->addActor(*staticBox);
//	g_PhysXActors.push_back(staticBox);
//
//	PxRigidDynamic* dynamicBox = PxCreateDynamic(*g_Physics,box2Transform,box,*boxMaterial,density);
//	g_PhysicsScene->addActor(*dynamicBox);
//	g_PhysXActors.push_back(dynamicBox);
//
//	PxTransform constraintFrame1= PxTransform(PxVec3(boxHalfSize+gap,0,0));
//	PxTransform constraintFrame2 = PxTransform(PxVec3(-startPos,0,0));
//
//	//join them using a D6Joint (joint is global so we can change it's drive target in update
//	gLinearJoint = PxD6JointCreate(*g_Physics,staticBox,constraintFrame1,dynamicBox,constraintFrame2); 
//	
//	if(gLinearJoint)
//	{
//		//lock all the joint axis except X so it behaves like a prismatic joint
//		gLinearJoint->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
//		gLinearJoint->setMotion(PxD6Axis::eY, PxD6Motion::eLOCKED);
//		gLinearJoint->setMotion(PxD6Axis::eZ, PxD6Motion::eLOCKED);
//		gLinearJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
//		gLinearJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLOCKED);
//		gLinearJoint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLOCKED);
//
//		//add the drive to the joint
//		PxD6JointDrive drive(10.0f, -20.0f, PX_MAX_F32, true);
//		gLinearJoint->setDrive(PxD6Drive::eX,drive);
//	}
//
//	//add a plane
//	PxTransform pose = PxTransform( PxVec3(0.0f, -.5, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
//	PxRigidStatic* plane = PxCreateStatic(*g_Physics, pose,PxPlaneGeometry(), *g_PhysicsMaterial);
//	//add it to the physX scene
//	g_PhysicsScene->addActor(*plane);
//
//}
//
//
//
//PxRigidDynamic* MotorTutorial::makeWheel(PxTransform transform,float radius,float thickness)
//{
//	PxRigidDynamic* dynamicActor;
//	PxCapsuleGeometry axle(.05,.1);
//	PxMaterial*  wheelMaterial = g_Physics->createMaterial(.5, .5, .8f);    //static friction, dynamic friction, restitution
//
//	float density = .00001;
//	dynamicActor = PxCreateDynamic(*g_Physics,transform,axle,*wheelMaterial,density);
//	//dynamicActor->setMass(.1);
//	dynamicActor->setAngularDamping(1);
//
//
//	//make wheel using a convex hull, physx doesn't have cylinder colliders...
//	const int NUMBER_WHEEL_DIVISIONS = 64;
//	PxVec3 wheelVerts[NUMBER_WHEEL_DIVISIONS*2];
//	int index = 0;
//	for(int count = 0;count<NUMBER_WHEEL_DIVISIONS;count++)
//	{
//		//find the angle
//		float angle = PxPi * 2 * count/(float)NUMBER_WHEEL_DIVISIONS;
//		//find y and z
//		float y = radius*sin(angle);
//		float z = radius*cos(angle);
//		//create the verts
//		PxVec3 vert1 = PxVec3(-thickness,y,z);
//		PxVec3 vert2 = PxVec3(thickness,y,z);
//		//add them to the list
//		wheelVerts[index++] = vert1; //inside
//		wheelVerts[index++] = vert2; //outside
//	}
//	PxConvexMeshDesc convexDesc;
//	convexDesc.points.count     = NUMBER_WHEEL_DIVISIONS*2;
//	convexDesc.points.stride    = sizeof(PxVec3);
//	convexDesc.points.data      = wheelVerts;
//	convexDesc.flags            = PxConvexFlag::eCOMPUTE_CONVEX;
//	PxToolkit::MemoryOutputStream buf;
//	//MemoryOutputStream buf;
//	if(!g_PhysicsCooker->cookConvexMesh(convexDesc, buf))
//		return NULL;
//	PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(0, PxVec3(0.0f, 0.0f, 1.0f)));
//	PxToolkit::MemoryInputData input(buf.getData(), buf.getSize());
//	PxConvexMesh* convexMesh = g_Physics->createConvexMesh(input);
//	dynamicActor->createShape((PxConvexMeshGeometry)convexMesh,*g_PhysicsMaterial,pose);
//	return dynamicActor;
//}
//
//
//void MotorTutorial::makeSimpleVehicle(PxTransform transform,Vehicle* vehicle)
//{
//	float wheelBaseLength = 1;
//	float wheelBaseWidth = .5;
//	float tireBodyGap = .15;
//	PxTransform wheelOffsets[NUMBER_WHEELS] = 
//	{
//		PxTransform(PxVec3(-(wheelBaseWidth+tireBodyGap),0,-wheelBaseLength),PxQuat(PxPi,X_AXIS)),
//		PxTransform(PxVec3(wheelBaseWidth+tireBodyGap,0,-wheelBaseLength),PxQuat(PxPi,X_AXIS)),
//		PxTransform(PxVec3(-(wheelBaseWidth+tireBodyGap),0,wheelBaseLength),PxQuat(PxPi,X_AXIS)),
//		PxTransform(PxVec3(wheelBaseWidth+tireBodyGap,0,wheelBaseLength),PxQuat(PxPi,X_AXIS)),
//	};
//	//make chassis:
//	PxRigidDynamic* chassis;
//	PxBoxGeometry box(wheelBaseWidth,.15f,wheelBaseLength*1.3);
//	PxMaterial*  wheelMaterial = g_Physics->createMaterial(0, 1.0f, .5f);    //static friction, dynamic friction, restitution
//
//	float density = .000001;
//	chassis = PxCreateDynamic(*g_Physics,transform,box,*wheelMaterial,density);
//	chassis->setLinearDamping(.1);
//	chassis->setAngularDamping(.01);
//	//chassis->setMass(.1);
//	g_PhysicsScene->addActor(*chassis);
//	g_PhysXActors.push_back(chassis);
//	//make wheels
//	vehicle->wheelRadius = .3f;
//	vehicle->wheelWidth = .1f;
//	for(int count =0;count < NUMBER_WHEELS;count++)
//	{
//		PxTransform wheelTransform = transform;
//		wheelTransform.p += wheelOffsets[count].p;
//		vehicle->wheels[count] = makeWheel(wheelTransform,vehicle->wheelRadius,vehicle->wheelWidth);
//		g_PhysicsScene->addActor(*vehicle->wheels[count]);
//		g_PhysXActors.push_back(vehicle->wheels[count]);
//	}
//	//join wheels to chassis
//	for(int count =0;count < NUMBER_WHEELS;count++)
//	{
//		PxTransform chassisConstraintFrame= wheelOffsets[count];
//		PxTransform wheelConstraintFrame = PxTransform(PxVec3(0,0,0));
//		//joint position at this point is at the centre of the wheel.  
//		//We want it between the wheel and the chassis so the following code moves it in:
//		if(chassisConstraintFrame.p.x<0)
//		{
//			wheelConstraintFrame.p.x -= .3;
//			chassisConstraintFrame.p.x -= .3;
//		}
//		else
//		{
//			wheelConstraintFrame.p.x += .3;
//			chassisConstraintFrame.p.x += .3;
//		}
//		PxRevoluteJoint *joint;
//		joint = PxRevoluteJointCreate(*g_Physics,chassis,chassisConstraintFrame,vehicle->wheels[count],wheelConstraintFrame); 
//		if(joint)
//		{
//			joint->setProjectionLinearTolerance(.1f);
//			joint->setProjectionAngularTolerance(.1f);
//			joint->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
//			joint->setBreakForce(100000,100000);
//			joint->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED,false);
//			joint->setDriveForceLimit(100);
//			vehicle->gCarAxles[count] = joint;
//		}
//	}
//}
//
//
//void MotorTutorial::controlVehicle(float a_deltaTime)
//{
//	if(gPlayerVehicle != NULL)
//	{
//		if (glfwGetKey(m_window,GLFW_KEY_UP) == GLFW_PRESS)
//		{
//			gPlayerVehicle->driveForce+= a_deltaTime*40;
//		}
//		if (glfwGetKey(m_window,GLFW_KEY_DOWN) == GLFW_PRESS)
//		{
//			gPlayerVehicle->driveForce-= a_deltaTime*40;
//		}
//		gPlayerVehicle->driveForce = PxClamp(gPlayerVehicle->driveForce,-40.0f,40.0f);
//		for(auto axle: gPlayerVehicle->gCarAxles)
//		{
//			axle->setDriveVelocity(gPlayerVehicle->driveForce);
//		}
//	}
//}
//
////simple code to provide a varying drive target for the linear motor
//void upDateLinearMotor(float delta)
//{
//	static float count = 0;
//	if(gLinearJoint != NULL)
//	{
//		//update the count
//		count+= delta;
//		//work out our target position
//		PxVec3 target = PxVec3(3 + 5*sin(count),0,0);
//		//set the target
//		gLinearJoint->setDrivePosition(PxTransform(target));
//	}
//}
//
////spawn boxes to demonstrate that the linear motor is physical thing which follows the laws of physics
//void spawnBoxes(float delta)
//{
//	PxBoxGeometry box(1,1,1);
//	static float count = 0;
//	float density = 1;
//	PxMaterial*  boxMaterial = g_Physics->createMaterial(.5, .5, .25);   
//	count += delta;
//	if(count > 1)
//	{
//		PxTransform boxTransform(PxVec3(8,20,0));
//		PxRigidDynamic* dynamicBox = PxCreateDynamic(*g_Physics,boxTransform,box,*boxMaterial,density);
//		g_PhysicsScene->addActor(*dynamicBox);
//		g_PhysXActors.push_back(dynamicBox);
//		count = 0;
//	}
//
//}
//
//void MotorTutorial::onUpdate(float a_deltaTime) 
//{
//	// update our camera matrix using the keyboard/mouse
//	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );
//	// clear all gizmos from last frame
//	Gizmos::clear();
//	if(a_deltaTime ==0)
//	{
//		a_deltaTime = 1/50;
//	}
//
//	static float count = 1;
//	count+= .01f;
//	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );
//	// quit our application when escape is pressed
//	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		quit();
//	upDateLinearMotor(a_deltaTime);
//	upDatePhysx(a_deltaTime);
//	controlVehicle(a_deltaTime);
//	//spawnBoxes(a_deltaTime); //add this back in to demonstrate things hitting boxes
//}
//
//void MotorTutorial::upDatePhysx(float a_deltaTime)
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
//}
//
//
//void MotorTutorial::addWidget(PxShape* shape,PxRigidActor* actor) 
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
//		case PxGeometryType::eCONVEXMESH:
//			addWheel(shape,actor); //For now we'll assume that if we get a convex mesh it must be a wheel...
//		break;
//    } 
//} 
//
//
//void MotorTutorial::addSphere(PxShape* pShape,PxRigidActor* actor) 
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
//void MotorTutorial::addCapsule(PxShape* pShape,PxRigidActor* actor) 
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
//void MotorTutorial::addWheel(PxShape* pShape,PxRigidActor* actor) 
//{
//	//creates a gizmo representation of a capsule using 2 spheres and a cylinder
//	glm::vec4 colour(0,0,1,1);  //make our capsule blue
//	PxConvexMeshGeometry convexMesh;
//	float radius = 1; //temporary values whilst we try and get the real value from PhysX
//	float halfHeight = 1;;
//	//get the geometry for this PhysX collision volume
//	bool status = pShape->getConvexMeshGeometry(convexMesh);
//	if(status)
//	{
//		//this should always happen but just to be safe we check the status flag
//		radius =gPlayerVehicle->wheelRadius;
//		halfHeight =gPlayerVehicle->wheelWidth;
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
//	//the cylinder gizmo is oriented 90 degrees to what we want so we need to change the rotation matrix...
//	glm::mat4 m2 = glm::rotate(M,11/7.0f,0.0f,0.0f,1.0f); //adds an additional rotation onto the matrix
//	//now we can use this matrix and the other data to create the cylinder...
//	Gizmos::addCylinderFilled(position,radius,halfHeight,64,colour,&m2);
//}
//
//
//void MotorTutorial::addBox(PxShape* pShape,PxRigidActor* actor) 
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
//void MotorTutorial::onDraw() 
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
//void MotorTutorial::onDestroy()
//{
//	// clean up anything we created
//	Gizmos::destroy();
//	cleanUpPhsyx();
//}
//
//void MotorTutorial::cleanUpPhsyx()
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
//	Application* app = new MotorTutorial();
//	if (app->create("AIE - Physx Tutorial",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//	// explicitly control the destruction of our application
//	delete app;
//	return 0;
//}
