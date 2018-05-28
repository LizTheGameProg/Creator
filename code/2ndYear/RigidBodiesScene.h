#ifndef RIGIDBODIESSCENE_H
#define RIGIDBODIESSCENE_H

#include "Basescene.h"
#include <vector>

struct StaticObject
{
	//PxVec3 centre;
	//PxVec3 extents;
	bool trigger;
	char* name;
public:
	StaticObject(float x,float y,float z, float length,float height, float width,bool trigger,char* name)
	{
		//centre.x = x;
		//centre.y = y;
		//centre.z = z;
		//extents.x = width;
		//extents.y = height;
		//extents.z = length;
		this->trigger = trigger;
		this->name = name;
	}
};

struct FilterGroup
{
    enum Enum
    {
        ePLAYER = (1 << 0),
        ePLATFORM = (1 << 1),
        eGROUND = (1 << 2)
    };
};


namespace AIE_2ND_YEAR
{
	class RigidBodiesScene : public BaseScene
	{
	public:
		RigidBodiesScene(PhysXVariables * PhysX_Variables);
		~RigidBodiesScene(void);
		void update(float DeltaTime);
		void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	protected:
		void controlPlayer(float DeltaTime);
		void addPlatforms();
		//void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);

		//std::vector<PxRigidActor *> m_PhysXActors;
		std::vector<StaticObject *> m_StaticObjects;

		//PxTransform m_startingPlayerPos;
		//PxRigidDynamic * m_playerActor;

	};
}
#endif