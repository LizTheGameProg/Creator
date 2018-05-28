#ifndef __SpaceTrain_H_
#define __SpaceTrain_H_

#include "Application.h"
#include "FBXSceneResource.h"
#include "ParticleEmitter.h"

#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class SpaceTrain : public AIE_2ND_YEAR::Application
{
public:

	SpaceTrain();
	virtual ~SpaceTrain();

protected:
	struct OGL_FBXRenderData
	{
		unsigned int VBO;
		unsigned int IBO;
		unsigned int VAO;
	};

	//--------------------------------
	// Usual AIE stuff
	//--------------------------------
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4 m_cameraMatrix;
	glm::mat4 m_projectionMatrix;

	//--------------------------------
	// My functions
	//--------------------------------
	void freeMovement(	glm::vec3& a_transform, 
						float a_deltaTime, 
						float a_speed, 
						const glm::vec3& a_up = glm::vec3(0,1,0));
	void PrintSpherePosition();

	//--------------------------------
	// My variables
	//--------------------------------
	float time;
	
	glm::mat4 m_viewMatrix;
	glm::vec3 m_LightPos[6];
	glm::vec3 m_spherePos;
	
	FBXFile				* m_fbx;
	FBXSceneResource	* fbxSR;
	ShaderProgram		* m_basicShader;
	ParticleEmitter		* m_particleEmitter_Positive;
	ParticleEmitter		* m_particleEmitter_Negative;
};

#endif // __SpaceTrain_H_