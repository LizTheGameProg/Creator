#ifndef PHYSXVARIABLES_H
#define PHYSXVARIABLES_H

//#include <PxPhysicsAPI.h>

//using namespace physx;

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

class PhysXVariables
{
public:
	PhysXVariables(void);
	~PhysXVariables(void);

	//PxFoundation *				m_PhysicsFoundation;
	//PxPhysics *					m_Physics;
	//PxScene *					m_PhysicsScene;
	//PVD::PvdConnection *		m_PVDConnection;
	//PxDefaultCpuDispatcher *	m_CPUDispatcher;
	//PxMaterial *				m_PhysicsMaterial;
	//PxCooking *					m_PhysicsCooker;
	//PxAllocatorCallback *		m_myCallback;
	//PxSimulationEventCallback * m_mycollisionCallBack;
	//
	//PxDefaultErrorCallback		m_DefaultErrorCallback;
	//PxDefaultAllocator			m_DefaultAllocatorCallback;
	//PxSimulationFilterShader	m_DefaultFilterShader;
};

#endif