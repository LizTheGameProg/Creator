#ifndef __PhysXTutorials_H_
#define __PhysXTutorials_H_

#include "Application.h"
#include <glm/glm.hpp>
//#include <PxPhysicsAPI.h>
#include <vector>
#include <iostream>


namespace AIE_2ND_YEAR
{
	class BaseScene;
}
//class PhysXVariables;

//using namespace physx;

//derived class to overide the call backs we are interested in...
//class MycollisionCallBack: public PxSimulationEventCallback
//{
//	virtual void MycollisionCallBack::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
//	{
//        for(PxU32 i=0; i < nbPairs; i++)
//        {
//            const PxContactPair& cp = pairs[i];
//            if(cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
//            {
//				std::cout<<"collision: "<< pairHeader.actors[0]->getName()<<" : "<< pairHeader.actors[1]->getName()<<std::endl;				
//			}
//        }
//	 }
//	//we have to create versions of the following functions even though we don't do anything with them...
//	virtual void    onTrigger(PxTriggerPair* pairs, PxU32 nbPairs)
//	{
//		std::cout<<"trigger between "<< pairs->triggerShape << " and " << pairs->otherShape << std::endl;
//	};
//	virtual void	onConstraintBreak(PxConstraintInfo*, PxU32){};
//	virtual void	onWake(PxActor** , PxU32 ){};
//	virtual void	onSleep(PxActor** , PxU32 ){};
//};

// Derived application class that wraps up all globals neatly
class PhysXTutorials : public AIE_2ND_YEAR::Application
{
public:
	PhysXTutorials();
	virtual ~PhysXTutorials();

protected:
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4 m_cameraMatrix;
	glm::mat4 m_projectionMatrix;

	void setUpPhysXTutorial();
	void upDatePhysx();
	
	void setUpVisualDebugger();
	void cleanUpVisualDebugger();
		
	//PhysXVariables	* m_physX_Variables;
	//BaseScene		* m_scene;
	std::vector<AIE_2ND_YEAR::BaseScene *> m_scenes;

	//void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);
};

#endif // __PhysXTutorials_H_