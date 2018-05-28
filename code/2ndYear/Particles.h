#ifndef __PhysTutorrialMain_H_
#define __PhysTutorrialMain_H_

#include "BaseScene.h"
#include <glm/glm.hpp>
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>
//#include <PxPhysicsAPI.h>
//#include<PxSceneQueryFiltering.h>
#include "FBXFile.h"
//#include "extensions/PxJoint.h"
#include "ParticleEmmiter.h"
#include "ParticleFluidEmmiter.h"

//using namespace physx;

namespace AIE_2ND_YEAR
{
	// Derived application class that wraps up all globals neatly
	class ParticleTutorial : public BaseScene
	{
	public:
		//ParticleTutorial(PhysXVariables * PhysX_Variables = nullptr);
		virtual ~ParticleTutorial();

		virtual void update(float DeltaTime);
		virtual void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	protected:

		//marching cube variables
		glm::ivec3 m_gridSize;
		glm::vec3 m_cubeSize;
		float*** m_volume;
		int m_maxVertices;
		glm::vec3* m_vertices;
		unsigned int m_shader;
		unsigned int m_vao;
		unsigned int m_vbo;
		int m_blobCount;
		glm::vec3* m_blobPoints;
		glm::vec3* m_blobVelocities;
		glm::vec4 m_fluidColour;
		glm::mat4x4 m_fluidTransform;
		// threshold for defining solid / not-solid
		float m_volumeThreshold;

		virtual void onUpdate(float a_deltaTime);

		void setUpMarchingCubes();

		//PxRigidDynamic* playerActor; 

		ParticleEmitter* particleEmiter1;
		ParticleEmitter* particleEmiter2;
		ParticleFluidEmitter* particleFluidEmitter;
		//void addWidget(PxShape* shape,PxRigidActor* actor) ;
		//void addSphere(PxShape* pShape,PxRigidActor* actor) ;
		//void addBox(PxShape* pShape,PxRigidActor* actor) ;
		//void addCapsule(PxShape* pShape,PxRigidActor* actor) ;
		//void addWheel(PxShape* pShape,PxRigidActor* actor) ;
		void drawMarchingCubes();
		//void addParticles(PxParticleSystem* ps);
		//void addParticle(PxParticleSystem* ps,int index);
		void renderParticles();
		void setUpPhysXTutorial();
		void upDatePhysx(float upDatePhysx);
		void cleanUpPhsyx();
		void tutorial_14a();
		void tutorial_14b();
		void createCollisionGroundPlane();
		void setUpVisualDebugger();
		// structure assigned to an FBXMeshNode's m_userData
		struct GLData
		{
			unsigned int vbo, ibo, vao;
		};
		FBXFile*	m_file;
		unsigned int m_program, m_vs, m_fs;

		//std::vector<PxRigidActor *> m_PhysXActors;

		void spawnBoxes(float delta);
		void spawnBalls(float delta);
	};
}
#endif // __PhysTutorrialMain_H_