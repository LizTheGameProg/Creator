#ifndef TUTORIAL1SCENE_H
#define TUTORIAL1SCENE_H

#include "BaseScene.h"
#include <vector>

namespace AIE_2ND_YEAR
{
	class tutorial1Scene : public BaseScene
	{
	public:
		tutorial1Scene(PhysXVariables * PhysX_Variables);
		~tutorial1Scene(void);

		void update(float DeltaTime);
		void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	protected:
		float m_spawnTimer;
		float m_spawnTime;

		//std::vector<PxRigidDynamic *> m_PhysXActors;
	};
}
#endif