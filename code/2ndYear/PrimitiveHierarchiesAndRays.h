#pragma once

#include "basescene.h"

//simple scene node
struct SceneNode
{
	//PxRigidActor * physXActor; //actor which controls this node
	FBXFile * fbxFile; //fbx file to use for this node
	glm::mat4 transform; //the nodes transform
};

struct HeightMap
{
	int numRows;
	int numCols;
	float heightScale;
	float rowScale;
	float colScale;
	glm::vec3 center;
	glm::mat4 transform;
	//PxHeightFieldSample * samples; 
	bool enabled;
};


namespace AIE_2ND_YEAR
{
	class PrimitiveHierarchiesAndRays : public BaseScene
	{
	public:
		PrimitiveHierarchiesAndRays(PhysXVariables * PhysX_Variables);
		~PrimitiveHierarchiesAndRays(void);

		virtual void update(float DeltaTime);
		virtual void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

		void pickingExample1(glm::mat4 cameraMatrix);

	private:
		//void setFBXTransform(PxTransform transform, SceneNode* sceneNode);
		//void renderHeightMap();
		//
		//PxRigidDynamic * addFBXWithConvexCollision(FBXFile* fbxFile,PxTransform transform);
		//void addStaticFBXWithTriangleCollision(FBXFile* fbxFile,PxTransform transform);
		//void addStaticHeightMapCollision(PxTransform transform);

		FBXFile * m_fbx;
		HeightMap heightMap;

		std::vector<SceneNode*> sceneNodes;

		//std::vector<PxRigidActor *> m_PhysXActors;

		unsigned int m_heightMapShader;
	};
}
