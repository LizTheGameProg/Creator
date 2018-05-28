#version 150

in vec3 Position;
in vec3 Velocity;
in float Lifetime;
in float Lifespan;

out vec3 position;
out vec3 velocity;
out float lifetime;
out float lifespan;

uniform float time;
uniform float deltaTime;
uniform float one;

uniform float lifeMin;
uniform float lifeMax;

uniform vec3 emitterPosition;

const float INVERSE_MAX_UINT = 1.0f / 4294967295.0f;

float rand(uint seed, float range)
{
	uint i=(seed^12345391u)*2654435769u;
	i^=(i<<6u)^(i>>26u);
	i*=2654435769u;
	i+=(i<<5u)^(i>>12u);
	return float(range * i) * INVERSE_MAX_UINT;
}

void main()
{
	position = Position + Velocity * deltaTime;
	velocity = Velocity;
	lifetime = Lifetime + deltaTime;
	lifespan = Lifespan;
	
	// emit a new particle as soon as it dies
	if (lifetime > lifespan) 
	{
		uint seed = uint(time * 1000.0) + uint(gl_VertexID);	
		
		position.z = emitterPosition.z - rand(seed++, 100) + 50;

		position.y = rand(seed++, 40) - 20;
		position.x = rand(seed++, 30) + 20;
		position.x = position.x * one;

		velocity.x = 0;
		velocity.y = 0;
		velocity.z = abs(position.x / 50) * -1;
		//velocity = normalize( velocity );

		lifetime = 0;
		lifespan = rand(seed++, lifeMax - lifeMin) + lifeMin;
	}
}