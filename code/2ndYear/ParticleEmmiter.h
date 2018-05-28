#pragma once
//#include <PxPhysicsAPI.h>
//using namespace physx;

//simple struct for our particles

struct Particle
{
	bool active;
	float maxTime;
};


//simple class for particle emitter.  For a real system we would make this a base class and derive different emitters from it by making functions virtual and overloading them.
class ParticleEmitter
{
	int maxParticles;
	Particle *activeParticles;
	float releaseDelay;
	int getNextFreeParticle();
	bool addPhysXParticle(int particleIndex);
	int numberActiveParticles;

	float time;
	float respawnTime;
	float particleMaxAge;
	//PxVec3 position;
	//PxParticleSystem* ps;
public:
	//ParticleEmitter(int _maxParticles,PxVec3 _position,PxParticleSystem* _ps,float _releaseDelay);
	~ParticleEmitter();
	void upDate(float delta);
	void releaseParticle(int);
	bool tooOld(int);
	void renderParticles();
};