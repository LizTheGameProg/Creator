//#include "JointAndSprings.h"
//
//JointAndSprings::JointAndSprings(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
//{
//	PxRigidDynamic * dynamicActor;
//	PxRigidStatic * staticActor;
//	PxDistanceJoint * joint;
//	PxSphereGeometry sphere(4); // geometry for our sphere radius is 4.
//	//position of anchor sphere
//	PxTransform transform(PxVec3(2,27,0),PxQuat::createIdentity());
//	float density = 3;
//	//create static actor as anchor
//	staticActor = PxCreateStatic(*m_physX_Variables->m_Physics, transform, sphere, *m_physX_Variables->m_PhysicsMaterial);
//	m_physX_Variables->m_PhysicsScene->addActor(*staticActor);
//	m_PhysXActors.push_back(staticActor);
//	//position of bottom sphere
//	transform.p = PxVec3(-2,22,0);
//	dynamicActor = PxCreateDynamic(*m_physX_Variables->m_Physics, transform, sphere,*m_physX_Variables->m_PhysicsMaterial, density);
//	m_physX_Variables->m_PhysicsScene->addActor(*dynamicActor);
//	m_PhysXActors.push_back(dynamicActor);
//	//create joint to link the spheres
//	joint = PxDistanceJointCreate(*m_physX_Variables->m_Physics,staticActor,PxTransform::createIdentity(),dynamicActor,PxTransform::createIdentity());
//	joint->setSpring(400); //spring coefficient
//	joint->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
//}
//
//JointAndSprings::~JointAndSprings(void)
//{
//
//}
//
//void JointAndSprings::update(float a_DeltaTime)
//{
//
//}
//
//void JointAndSprings::render(glm::mat4 a_ProjectionMatrix, glm::mat4 a_ViewMatrix)
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