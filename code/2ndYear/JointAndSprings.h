#ifndef JOINTANDSPRINGS_H
#define JOINTANDSPRINGS_H

#include "BaseScene.h"

namespace AIE_2ND_YEAR
{
	class JointAndSprings : public BaseScene
	{
	public:
		JointAndSprings(PhysXVariables * physX_Variables);
		~JointAndSprings(void);

		virtual void update(float DeltaTime);
		virtual void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	private:
		//std::vector<PxRigidActor *> m_PhysXActors;
	};
}
#endif