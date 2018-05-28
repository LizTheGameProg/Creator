#include "ParticleEmmiter.h"
#include <iostream>
#include<vector>
#include "Gizmos.h"


//constructor
//ParticleEmitter::ParticleEmitter(int _maxParticles, PxVec3 _position,PxParticleSystem* _ps,float _releaseDelay)
//{
//	releaseDelay = _releaseDelay;
//	maxParticles = _maxParticles;  //maximum number of particles our emitter can handle
//	//allocate an array
//	activeParticles = new Particle[maxParticles]; //array of particle structs
//	time = 0; //time system has been running
//	respawnTime = 0; //time for next respawn
//	position = _position;
//	ps =_ps; //pointer to the physX particle system
//	particleMaxAge = 8; //maximum time in seconds that a particle can live for
//	//initialize the buffer
//	for(int index=0;index<maxParticles;index++)
//	{
//		activeParticles[index].active = false;
//		activeParticles[index].maxTime = 0;
//	}
//}
//
//destructure
//ParticleEmitter::~ParticleEmitter()
//{
//	//remove all the active particles
//	delete activeParticles;
//}
//
////find the next free particle, mark it as used and return it's index.  If it can't allocate a particle: returns minus one
//int ParticleEmitter::getNextFreeParticle()
//{
//	//find particle, this is a very inefficient way to do this.  A better way would be to keep a list of free particles so we can quickly find the first free one
//	for(int index=0;index<maxParticles;index++)
//	{
//		//when we find a particle which is free
//		if(!activeParticles[index].active)
//		{
//			activeParticles[index].active = true; //mark it as not free
//			activeParticles[index].maxTime = time+particleMaxAge;  //record when the particle was created so we know when to remove it
//			return index;
//		}
//	}
//	return -1; //returns minus if a particle was not allocated
//}
//
//
////releast a particle from the system using it's index to ID it
//void ParticleEmitter::releaseParticle(int index)
//{
//	if(index >= 0 && index < maxParticles)
//		activeParticles[index].active = false;
//}
//
////returns true if a particle age is greater than it's maximum allowed age
//bool ParticleEmitter::tooOld(int index)
//{
//	if(index >= 0 && index < maxParticles && time > activeParticles[index].maxTime)
//		return true;
//	return false;
//}
//
////add particle to PhysX System
//bool ParticleEmitter::addPhysXParticle(int particleIndex)
//{
//
//	//set up the data
//	//set up the buffers
//	PxU32 myIndexBuffer[] = {particleIndex};
//	PxVec3 startPos = position;
//	PxVec3 startVel(0,0,0);
//	//randomize starting velocity.
//	startVel.x += (rand()%1000 - 500)/10.0f;
//	startVel.z += (rand()%1000 - 500)/10.0f;
//
//	//we can change starting position tos get different emitter shapes
//	PxVec3 myPositionBuffer[] = {startPos};
//	PxVec3 myVelocityBuffer[] =  {startVel};
//
//	//reserve space for data
//	PxParticleCreationData particleCreationData;
//	particleCreationData.numParticles = 1;  //spawn one particle at a time,  this is inefficient and we could improve this by passing in the list of particles.
//	particleCreationData.indexBuffer = PxStrideIterator<const PxU32>(myIndexBuffer);
//	particleCreationData.positionBuffer = PxStrideIterator<const PxVec3>(myPositionBuffer);
//	particleCreationData.velocityBuffer = PxStrideIterator<const PxVec3>(myVelocityBuffer);
//	// create particles in *PxParticleSystem* ps
//	return ps->createParticles(particleCreationData);
//}
//
////updateParticle
//void ParticleEmitter::upDate(float delta)
//{
//	//tick the emitter
//	time += delta;
//	respawnTime+= delta;
//	int numberSpawn = 0;
//	//if respawn time is greater than our release delay then we spawn at least one particle so work out how many to spawn
//	if(respawnTime>releaseDelay)
//	{
//		numberSpawn = (int)(respawnTime/releaseDelay);
//		respawnTime -= (numberSpawn * releaseDelay);
//	}
//	// spawn the required number of particles 
//	for(int count = 0;count < numberSpawn;count++)
//	{
//		//get the next free particle
//		int particleIndex = getNextFreeParticle();
//		if(particleIndex >=0)
//		{
//			//if we got a particle ID then spawn it
//			addPhysXParticle(particleIndex);
//		}
//	}
//	//check to see if we need to release particles because they are either too old or have hit the particle sink
//	//lock the particle buffer so we can work on it and get a pointer to read data
//	PxParticleReadData* rd = ps->lockParticleReadData();
//	// access particle data from PxParticleReadData was OK
//	if (rd)
//	{
//		vector<PxU32> particlesToRemove; //we need to build a list of particles to remove so we can do it all in one go
//		PxStrideIterator<const PxParticleFlags> flagsIt(rd->flagsBuffer);
//
//		for (unsigned i = 0; i < rd->validParticleRange; ++i, ++flagsIt)
//		{
//			if (*flagsIt & PxParticleFlag::eVALID)
//				{
//					//if particle is either too old or has hit the sink then mark it for removal.  We can't remove it here because we buffer is locked
//					if (*flagsIt & PxParticleFlag::eCOLLISION_WITH_DRAIN || tooOld(i))
//					{
//						//mark our local copy of the particle free
//						releaseParticle(i);
//						//add to our list of particles to remove
//						particlesToRemove.push_back(i);
//					}
//				}
//		}
//		// return ownership of the buffers back to the SDK
//		rd->unlock();
//		//if we have particles to release then pass the particles to remove to PhysX so it can release them
//		if(particlesToRemove.size()>0)
//		{
//			//create a buffer of particle indicies which we are going to remove
//			PxStrideIterator<const PxU32> indexBuffer(&particlesToRemove[0]);
//			//free particles from the physics system
//			ps->releaseParticles(particlesToRemove.size(), indexBuffer);
//		}
//	}
//}
//
////simple routine to render our particles
//void ParticleEmitter::renderParticles()
//{
//	// lock SDK buffers of *PxParticleSystem* ps for reading
//	PxParticleReadData* rd = ps->lockParticleReadData();
//	// access particle data from PxParticleReadData
//	if (rd)
//	{
//		PxStrideIterator<const PxParticleFlags> flagsIt(rd->flagsBuffer);
//		PxStrideIterator<const PxVec3> positionIt(rd->positionBuffer);
//
//		for (unsigned i = 0; i < rd->validParticleRange; ++i, ++flagsIt, ++positionIt)
//		{
//				if (*flagsIt & PxParticleFlag::eVALID)
//				{
//						//convert physx vector to a glm vec3
//						glm::vec3 pos(positionIt->x,positionIt->y,positionIt->z);
//						//use a gizmo box to visualize particle.  This would be much better done using a facing quad preferably done using the geometry shader
//						Gizmos::addAABBFilled(pos,glm::vec3(.1,.1,.1),glm::vec4(1,0,1,1));
//				}
//		}
//		// return ownership of the buffers back to the SDK
//		rd->unlock();
//	}
//}