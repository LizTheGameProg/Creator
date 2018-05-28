#ifndef BASESCENE_H
#define BASESCENE_H

#include <glm/glm.hpp>
//#include <PxPhysicsAPI.h>
#include <FBXFile.h>

#include "PhysXVariables.h"

//using namespace physx;
namespace AIE_2ND_YEAR
{
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	class BaseScene
	{
	public:
		BaseScene(PhysXVariables * PhysX_Variables = nullptr);
		virtual ~BaseScene(void);
		virtual void update(float DeltaTime);
		virtual void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	protected:
		void InitFBXSceneResource(FBXFile *a_pScene);
		void UpdateFBXSceneResource(FBXFile *a_pScene);
		void RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection, glm::mat4 a_globalTransform);
		void DestroyFBXSceneResource(FBXFile *a_pScene);

		void createShaderPrograms();

		std::map<const char *, unsigned int> m_shaderMap;

		//void addWidget	(PxShape * shape,	PxRigidActor * actor);
		//void addBox		(PxShape * pShape,	PxRigidActor * actor);
		//void addGrid	(const glm::vec3 & a_center, const glm::mat4 * a_transform, int increments, float size);
		//void addSphere	(PxShape * pShape,	PxRigidActor * actor);
		//void addCapsule	(PxShape * pShape,	PxRigidActor * actor);
		//
		//glm::mat4 Px2Glm(PxMat44 Matrix4);
		//glm::vec3 Px2GlV3(PxVec3 Vector3);
		//
		//PxVec3 glm2Px(glm::vec3 Vector3);

		PhysXVariables * m_physX_Variables;
	};
}

#endif