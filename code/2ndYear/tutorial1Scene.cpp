#include "tutorial1Scene.h"

namespace AIE_2ND_YEAR
{
	tutorial1Scene::tutorial1Scene(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
	{
		//PxTransform pose  = PxTransform(PxVec3(	0.0f,	0,  0.0f),	PxQuat(PxHalfPi, PxVec3(0.0f,  0.0f, 1.0f)));
		//PxTransform pose2 = PxTransform(PxVec3(-10.0f,	0,	0.0f),	PxQuat(0, PxVec3(0.0f, 1.0f, 0.0f)));
		//PxTransform pose3 = PxTransform(PxVec3(	0.0f,	0,  10.0f),	PxQuat(PxHalfPi, PxVec3(0.0f,  1.0f, 0.0f)));
		//PxTransform pose4 = PxTransform(PxVec3(	0.0f,	0, -10.0f),	PxQuat(-PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
		//PxTransform pose5 = PxTransform(PxVec3(	10.0f,	0,	0.0f),	PxQuat(2 * PxHalfPi, PxVec3(0.f,  1.f, 0.0f)));
		//
		//PxRigidStatic* plane  = PxCreateStatic(*m_physX_Variables->m_Physics, pose,  PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
		//PxRigidStatic* plane2 = PxCreateStatic(*m_physX_Variables->m_Physics, pose2, PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
		//PxRigidStatic* plane3 = PxCreateStatic(*m_physX_Variables->m_Physics, pose3, PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
		//PxRigidStatic* plane4 = PxCreateStatic(*m_physX_Variables->m_Physics, pose4, PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
		//PxRigidStatic* plane5 = PxCreateStatic(*m_physX_Variables->m_Physics, pose5, PxPlaneGeometry(), *m_physX_Variables->m_PhysicsMaterial);
		//
		////add it to the physX scene
		//m_physX_Variables->m_PhysicsScene->addActor(*plane);
		//m_physX_Variables->m_PhysicsScene->addActor(*plane2);
		//m_physX_Variables->m_PhysicsScene->addActor(*plane3);
		//m_physX_Variables->m_PhysicsScene->addActor(*plane4);
		//m_physX_Variables->m_PhysicsScene->addActor(*plane5);

		m_spawnTimer = 0.f;
		m_spawnTime = 0.2f;
	}

	tutorial1Scene::~tutorial1Scene(void)
	{

	}

	void tutorial1Scene::update(float a_deltaTime)
	{
		m_spawnTimer += a_deltaTime;
		if(m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0.f;

			float density = (float) (rand() % 100 / 10 + 5);
			float radius = ((float) rand() / RAND_MAX) + .05f;
			//PxSphereGeometry sphere(radius);
			//PxTransform transform(PxVec3((PxReal)(rand()%10 - 5),(PxReal)(rand()%10 + 5),(PxReal)(rand()%10 - 5)));
			//PxRigidDynamic* dynamicActor = PxCreateDynamic(*m_physX_Variables->m_Physics, transform, sphere, *m_physX_Variables->m_PhysicsMaterial, density);	
			//dynamicActor->addForce(PxVec3(2.0f * ((float) rand() / (float) RAND_MAX) - 1.0f,0,2.0f * ((float) rand() / (float) RAND_MAX) - 1.0f) * 1000);
			//add it to the physX scene
			//m_physX_Variables->m_PhysicsScene->addActor(*dynamicActor);

			//add it to our copy of the scene
			//m_PhysXActors.push_back(dynamicActor);

		}
	}

	//void tutorial1Scene::render(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
	//{
	//	// Add widgets to represent all the phsyX actors which are in the scene
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
}