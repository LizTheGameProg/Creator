#pragma once
//#include <PxPhysicsAPI.h>
#include <glm/ext.hpp>
//using namespace physx;
//using namespace std;

//simple struct for our particles

struct FluidParticle
{
	bool active;
	float maxTime;
};


//simple class for particle emitter.  For a real system we would make this a base class and derive different emitters from it by making functions virtual and overloading them.
class ParticleFluidEmitter
{
	int maxParticles;
	FluidParticle *activeParticles;
	float releaseDelay;
	int getNextFreeParticle();
	bool addPhysXParticle(int particleIndex);
	int numberActiveParticles;

	float time;
	float respawnTime;
	float particleMaxAge;
	//PxVec3 position;
	int boxWidth;
	int boxHeight;
public:
	//PxParticleFluid* pf;
	//ParticleFluidEmitter(int _maxParticles,PxVec3 _position,PxParticleFluid* _pf,float _releaseDelay);
	~ParticleFluidEmitter();
	void upDate(float delta);
	void releaseParticle(int);
	bool tooOld(int);
	void renderParticles();
	int rows;
	int cols;
	int depth;
};