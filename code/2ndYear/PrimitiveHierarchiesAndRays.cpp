#include "PrimitiveHierarchiesAndRays.h"

#include <GL/glew.h>
#include <GLFW\glfw3.h>
//#include <PxTkStream.h>

#include <iostream>

#include <Utilities.h>
#include <Gizmos.h>

//PrimitiveHierarchiesAndRays::PrimitiveHierarchiesAndRays(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
//{
//	createShaderPrograms();
//
//	m_fbx = new FBXFile();
//	m_fbx->load( "./models/tanks/battle_tank.fbx", FBXFile::UNITS_DECIMETER);
//	InitFBXSceneResource( m_fbx );
//
//	PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(PxHalfPi*1, PxVec3(0.0f, 1.0f, 0.0f)));
//	//PxRigidStatic * plane = PxCreateStatic(*m_physX_Variables->m_Physics, pose,PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
//
//	//add it to the physX scene
//	//m_physX_Variables->m_PhysicsScene->addActor(*plane);
//
//	//FBXFile* fbxFile = loadFBX(); //loads an FBX file and returns a pointer to it
//
//	//float density = 10;
//	//create our first box for the tank body
//	PxBoxGeometry box(10, 0.1f, 10);
//	
//	PxRigidStatic * staticObject = PxCreateStatic(*m_physX_Variables->m_Physics,pose,box,*m_physX_Variables->m_PhysicsMaterial);
//	
//	//add it to the physX scene
//	m_physX_Variables->m_PhysicsScene->addActor(*staticObject);
//	m_PhysXActors.push_back(staticObject);
//	
//	PxTransform transform(PxVec3(0,5,0));
//	
//	//PxCreateDynamic(*m_physX_Variables->m_Physics, transform, box,*m_physX_Variables->m_PhysicsMaterial, density);	
//	PxRigidDynamic * dynamicActor = addFBXWithConvexCollision(m_fbx, transform);
//	
//	//addStaticFBXWithTriangleCollision(m_fbx, transform);
//
//	transform = PxTransform(PxVec3(-35,-10,-40));
//	addStaticHeightMapCollision(transform);
//
//	////reposition the first box so it's in the right place
//	////find out how many shapes are in the actor
//    //const PxU32 numShapes = dynamicActor->getNbShapes();
//	////reserve space for them
//	//PxShape** shapes = (PxShape**)_aligned_malloc(sizeof(PxShape*)*numShapes,16);
//	////get them into our buffer
//    //dynamicActor->getShapes(shapes, numShapes);
//	////reset the local transform for the first one (our box)
//	//shapes[0]->setLocalPose(PxTransform(PxVec3(0,3.5,0))); //reposition it
//	////give it a name
//	//shapes[0]->setName("Tank hull");
//	//
//	////create our second box for the turret
//	//PxBoxGeometry turret(8,4,8);
//	//PxTransform turretPose = PxTransform( PxVec3(0.0f, 7.0, -3.0f));
//	//dynamicActor->createShape(turret,*m_physX_Variables->m_PhysicsMaterial,turretPose);
//
//	//add the actor to the PhysX scene
//	//m_physX_Variables->m_PhysicsScene->addActor(*dynamicActor);
//	//add it to our copy of the scene
//	//m_PhysXActors.push_back(dynamicActor);
//	//create a scene node
//	//SceneNode* sceneNode = new SceneNode();
//	//sceneNode->fbxFile = m_fbx; //set up the FBXFile
//	//sceneNode->physXActor = dynamicActor; //link our scene node to the physics Object
//	//sceneNodes.push_back(sceneNode); //add it to the scene graph
//	//dynamicActor->userData = (void*) sceneNode;  //Link the dynamic actor to the scene node
//}
//
//PrimitiveHierarchiesAndRays::~PrimitiveHierarchiesAndRays(void)
//{
//	for(auto shaderProgram : m_shaderMap)
//	{
//		glDeleteProgram(shaderProgram.second);
//	}
//	for(auto sceneNode : sceneNodes)
//	{
//		if(sceneNode->fbxFile != nullptr)
//		{
//			DestroyFBXSceneResource(sceneNode->fbxFile);
//			sceneNode->fbxFile->unload();
//			delete sceneNode->fbxFile;
//			sceneNode->fbxFile = nullptr;
//		}
//		delete sceneNode;
//		sceneNode = nullptr;
//	}
//}
//
//void PrimitiveHierarchiesAndRays::update(float a_DeltaTime)
//{
//	for(auto sceneNode:sceneNodes)
//	{
//		UpdateFBXSceneResource(m_fbx);
//	}
//}
//
//void PrimitiveHierarchiesAndRays::render(glm::mat4 a_ProjectionMatrix, glm::mat4 a_ViewMatrix)
//{
//	for(auto sceneNode : sceneNodes)
//	{
//		//get a pointer to the physX actor for this scene node
//		PxRigidActor* thisActor = sceneNode->physXActor;
//		//set the transform for this scene node to be that of the physx actor
//		setFBXTransform(thisActor->getGlobalPose(),sceneNode);
//		RenderFBXSceneResource( m_fbx, a_ViewMatrix, a_ProjectionMatrix, sceneNode->transform );
//		PxU32 nShapes = sceneNode->physXActor->getNbShapes();
//		PxShape** shapes = new PxShape*[nShapes];
//		sceneNode->physXActor->getShapes(shapes, nShapes);
//		// Render all the shapes in the physx actor (for early tutorials there is just one)
//		while (nShapes--)
//		{
//			 addWidget(shapes[nShapes],sceneNode->physXActor); 
//		}
//		delete [] shapes;
//	}
//	
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
//
//	renderHeightMap();
//}
//
//void PrimitiveHierarchiesAndRays::setFBXTransform(PxTransform a_Transform, SceneNode* a_SceneNode)
//{
//	PxMat44 m(a_Transform); //convert tranform to a 4X4 matrix
//	//then convert it to a glm matrix... 
//	glm::mat4 M(m.column0.x, m.column0.y, m.column0.z, m.column0.w,
//				m.column1.x, m.column1.y, m.column1.z, m.column1.w,
//				m.column2.x, m.column2.y, m.column2.z, m.column2.w,
//				m.column3.x, m.column3.y, m.column3.z, m.column3.w);
//	a_SceneNode->transform = M;  //set the meshes global tranform to this
//}
//
//void PrimitiveHierarchiesAndRays::pickingExample1(glm::mat4 a_CameraMatrix)
//{
//	GLFWwindow* window = glfwGetCurrentContext();
//	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
//	{
//		//get the camera position from the camera matrix
//		glm::vec3 position(a_CameraMatrix[3]);
//		//get the camera rotationfrom the camera matrix
//		glm::vec3 direction(glm::normalize(a_CameraMatrix[2]));
//		PxVec3 origin = glm2Px(position);                 // [in] Ray origin
//		PxVec3 unitDir = glm2Px(-direction);                // [in] Normalized ray direction
//		PxReal maxDistance = 1000;            // [in] Raycast max distance
//		PxRaycastHit hit;                 // [out] Raycast results
//
//		// Raycast against all static & dynamic objects (no filtering)
//		// The main result from this call is the boolean 'status'
//		m_physX_Variables->m_PhysicsScene->raycastSingle(origin, unitDir, PX_MAX_F32, PxSceneQueryFlag::eIMPACT, hit, PxSceneQueryFilterData());
//		if(hit.shape)
//		{ 
//			std::cout<<"hit shape: ";
//			const char* shapeName = hit.shape->getName();
//			if(shapeName)
//			{
//				//printf("Picked shape name: %s\n", shapeName);
//				std::cout<<shapeName<<std::endl;
//			}
//			std::cout<<std::endl;
//		}
//		else
//		{
//			std::cout<<"no hits"<<std::endl;
//		}
//	}
//}
//
//PxRigidDynamic * PrimitiveHierarchiesAndRays::addFBXWithConvexCollision(FBXFile* fbxFile,PxTransform transform)
//{
//	//create a phsyics material for our tank wiuth low friction
//	//because we want to push it around
//	PxMaterial * tankMaterial = m_physX_Variables->m_Physics->createMaterial(0.2f, 0.2f, 0.2f);    //static friction, dynamic friction, restitution
//	//load and cook a mesh
//	PxRigidDynamic * dynamicActor;
//	//PxBoxGeometry box(1,1,1);
//	float density = 10;
//	
//	for ( unsigned int i = 0 ; i < fbxFile->getMeshCount() ; ++i )
//	{
//		FBXMeshNode * mesh = fbxFile->getMeshByIndex(i);
//		int numberVerts = mesh->m_vertices.size();
//		PxVec3 *verts = new PxVec3[numberVerts];
//		//unfortunately we need to convert verts from glm to Px format
//		for(int vertIDX = 0;vertIDX< numberVerts;vertIDX++)
//		{
//			glm::vec4 temp =  mesh->m_vertices[vertIDX].position;
//			//hack to remove antenna from collision mesh
//			if(temp.y > 110)
//			{
//				temp.y = 110;
//			}
//			verts[vertIDX] = PxVec3(temp.x,temp.y,temp.z) * .1f;  //scale the mesh because it's way too big
//		}
//		//control structure for convex mesh cooker
//		PxConvexMeshDesc convexDesc;
//		convexDesc.points.count     = numberVerts;
//		convexDesc.points.stride    = sizeof(PxVec3);
//		convexDesc.points.data      = verts;
//		convexDesc.flags            = PxConvexFlag::eCOMPUTE_CONVEX;
//		PxToolkit::MemoryOutputStream buf;
//		//cook the mesh
//		if(!m_physX_Variables->m_PhysicsCooker->cookConvexMesh(convexDesc, buf))
//			return NULL;
//		PxToolkit::MemoryInputData input(buf.getData(), buf.getSize());
//		PxConvexMesh * convexMesh = m_physX_Variables->m_Physics->createConvexMesh(input);
//		PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(0, PxVec3(0.0f, 0.0f, 1.0f)));
//		if(i == 0)
//		{
//			dynamicActor = PxCreateDynamic(*m_physX_Variables->m_Physics, transform, (PxConvexMeshGeometry)convexMesh, *tankMaterial, density);
//			dynamicActor->setLinearDamping(.5f);
//			dynamicActor->setAngularDamping(100);
//		}
//		else
//		{
//			dynamicActor->createShape((PxConvexMeshGeometry)convexMesh,*m_physX_Variables->m_PhysicsMaterial,pose);
//		}
//		//add it to the physX scene
//		delete(verts);
//	}
//	SceneNode* sceneNode = new SceneNode();
//	sceneNode->fbxFile = fbxFile; //set up the FBXFile
//	setFBXTransform(transform, sceneNode);
//	sceneNode->physXActor = dynamicActor; //link our scene node to the physics Object
//	sceneNodes.push_back(sceneNode); //add it to the scene graph
//	m_physX_Variables->m_PhysicsScene->addActor(*dynamicActor);
//	return dynamicActor;
//}
//
//void PrimitiveHierarchiesAndRays::addStaticFBXWithTriangleCollision(FBXFile* fbxFile,PxTransform transform)
//{
//	//load and cook a mesh
//	PxRigidStatic * staticObject;
//	
//	for ( unsigned int i = 0 ; i < fbxFile->getMeshCount() ; ++i )
//	{
//		FBXMeshNode * mesh = fbxFile->getMeshByIndex(i);
//		int numberVerts = mesh->m_vertices.size();
//		PxVec3 * verts = new PxVec3[numberVerts];
//		for(int vertIDX = 0;vertIDX< numberVerts;vertIDX++)
//		{
//			glm::vec4 temp =  mesh->m_vertices[vertIDX].position;
//			verts[vertIDX] = PxVec3(temp.x,temp.y,temp.z) * .1f;  //scale the mesh because it's way too big
//		}
//		PxTriangleMeshDesc meshDesc;
//		meshDesc.points.count     = numberVerts;
//		meshDesc.points.stride    = sizeof(PxVec3);
//		meshDesc.points.data      = verts;
//		int triCount = mesh->m_indices.size()/3;
//		meshDesc.triangles.count        = triCount;
//		meshDesc.triangles.stride       = 3*sizeof(PxU32);
//		meshDesc.triangles.data     =   mesh->m_indices.data();
//		PxToolkit::MemoryOutputStream buf;
//		if(!m_physX_Variables->m_PhysicsCooker->cookTriangleMesh(meshDesc, buf))
//			return;
//		PxToolkit::MemoryInputData input(buf.getData(), buf.getSize());
//		PxTriangleMesh * triangleMesh = m_physX_Variables->m_Physics->createTriangleMesh(input);
//		PxTransform pose = PxTransform( PxVec3(0.0f, 0, 0.0f),PxQuat(0, PxVec3(0.0f, 0.0f, 1.0f)));
//		if(i == 0)
//			staticObject = PxCreateStatic(*m_physX_Variables->m_Physics, transform, (PxTriangleMeshGeometry)triangleMesh, *m_physX_Variables->m_PhysicsMaterial);
//		else
//			staticObject->createShape((PxTriangleMeshGeometry)triangleMesh, *m_physX_Variables->m_PhysicsMaterial, pose);
//		delete(verts);
//	}
//	SceneNode* sceneNode = new SceneNode();
//	sceneNode->fbxFile = fbxFile; //set up the FBXFile
//	sceneNode->physXActor = staticObject; //link our scene node to the physics Object
//	sceneNodes.push_back(sceneNode); //add it to the scene graph
//	//add it to the physX scene
//	m_physX_Variables->m_PhysicsScene->addActor(*staticObject);
//}
//
//void PrimitiveHierarchiesAndRays::addStaticHeightMapCollision(PxTransform transform)
//{
//	heightMap.numRows = 60;
//	heightMap.numCols = 60;
//	heightMap.heightScale = .12f;
//	heightMap.rowScale = 2; 
//	heightMap.colScale = 2;
//	heightMap.center = Px2GlV3(transform.p);
//	heightMap.transform = Px2Glm(transform);
//	heightMap.samples = (PxHeightFieldSample*)_aligned_malloc(sizeof(PxHeightFieldSample)*(heightMap.numRows*heightMap.numCols),16);
//	heightMap.enabled = true;
//	//make height map
//	PxHeightFieldSample* samplePtr = heightMap.samples;
//	for(int row = 0;row<heightMap.numRows;row++)
//	{
//		for(int col = 0;col<heightMap.numCols;col++)
//		{
//			float height = sin(row/10.0f) * cos(col/10.0f);
//			samplePtr->height = height * 30.0f;
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
//	PxHeightField* aHeightField = m_physX_Variables->m_Physics->createHeightField(hfDesc);
//	PxHeightFieldGeometry hfGeom(aHeightField, PxMeshGeometryFlags(), heightMap.heightScale, heightMap.rowScale, heightMap.colScale);
//		
//	PxRigidStatic * staticObject;
//	staticObject = PxCreateStatic(*m_physX_Variables->m_Physics,transform,(PxHeightFieldGeometry)hfGeom,*m_physX_Variables->m_PhysicsMaterial);
//	//staticObject->createShape((PxHeightFieldGeometry)hfGeom,*m_physX_Variables->m_PhysicsMaterial,pose);
//	m_physX_Variables->m_PhysicsScene->addActor(*staticObject);
//}
//
//void PrimitiveHierarchiesAndRays::renderHeightMap()
//{
//	int w = heightMap.numRows;
//    int h = heightMap.numCols;
//    float sw = heightMap.rowScale;
//    float sh = heightMap.colScale;
//	//float scale = 1.0f / 512;
//	float scale = heightMap.heightScale;
//	glm::mat4 matrix = heightMap.transform;
//
//	for(int i = 0; i < w-1; i++)
//	{
//		for(int j = 0; j < h-1; j++)		
//		{
//			glm::vec3 vec00 = (matrix * glm::vec4(float(j + 0)*sh, heightMap.samples[(j + 0)*w + (i + 0)].height*scale, float(i + 0)*sw, 1)).xyz;
//            glm::vec3 vec10 = (matrix * glm::vec4(float(j + 0)*sh, heightMap.samples[(j + 0)*w + (i + 1)].height*scale, float(i + 1)*sw, 1)).xyz;
//            glm::vec3 vec01 = (matrix * glm::vec4(float(j + 1)*sh, heightMap.samples[(j + 1)*w + (i + 0)].height*scale, float(i + 0)*sw, 1)).xyz;
//            glm::vec3 vec11 = (matrix * glm::vec4(float(j + 1)*sh, heightMap.samples[(j + 1)*w + (i + 1)].height*scale, float(i + 1)*sw, 1)).xyz;
//
//			Gizmos::addLine(vec00, vec01, glm::vec4(1,0,0,1));
//            Gizmos::addLine(vec00, vec10, glm::vec4(1,0,0,1));
//		}
//	}
//}
