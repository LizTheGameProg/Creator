#include "ParticleEmitter.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

//ParticleEmitter::ParticleEmitter()
//	: m_particles(nullptr), 
//	m_position(0,0,0),
//	m_vao(0), m_vbo(0), m_ibo(0),
//	m_vertexData(nullptr), m_indexData(nullptr)
//{
//
//}
//
//ParticleEmitter::~ParticleEmitter()
//{
//	delete[] m_particles;
//	delete[] m_indexData;
//	delete[] m_vertexData;
//
//	glDeleteVertexArrays(1, &m_vao);
//	glDeleteBuffers(1, &m_vbo);
//	glDeleteBuffers(1, &m_ibo);
//}
//
//void ParticleEmitter::initalise(unsigned int a_maxParticles, unsigned int a_emitRate, 
//								float a_lifetimeMin, float a_lifetimeMax, 
//								float a_velocityMin, float a_velocityMax, 
//								float a_startSize, float a_endSize, 
//								const glm::vec4& a_startColour, const glm::vec4& a_endColour,
//								char * texturePath, char * vertPath, char * fragPath, const char* inputs[], const char * outputs[])
//{
//	m_texture = SOIL_load_OGL_texture(texturePath,
//					  SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);
//
//	// load shaders and link shader program
//	unsigned int m_vertShader = Utility::loadShader(vertPath, GL_VERTEX_SHADER);
//	unsigned int m_fragShader = Utility::loadShader(fragPath, GL_FRAGMENT_SHADER);
//
//	// our vertex buffer has 3 properties per-vertex
//	
//	m_shader = Utility::createProgram(m_vertShader,0,0,0,m_fragShader, 3, inputs, 2, outputs);
//
//	// set up emit timers
//	m_emitTimer = 0;
//	m_emitRate = 1.0f / a_emitRate;
//
//	// store all variables passed in
//	m_startColour = a_startColour;
//	m_endColour = a_endColour;
//	m_startSize = a_startSize;
//	m_endSize = a_endSize;
//	m_velocityMin = a_velocityMin;
//	m_velocityMax = a_velocityMax;
//	m_lifespanMin = a_lifetimeMin;
//	m_lifespanMax = a_lifetimeMax;
//
//	// create particle array and store them in the dead pool
//	m_particles = new Particle[ a_maxParticles ];
//	for ( unsigned int i = 0 ; i < a_maxParticles ; ++i )
//		m_deadParticles.push_back( &m_particles[i] );
//
//	// create the array of vertices for the particles
//	// 4 vertices per particle for a quad.
//	// will be filled during update
//	m_vertexData = new ParticleVertex[ a_maxParticles * 4 ];
//
//	// create the index buffeer data for the particles
//	// 6 indices per quad of 2 triangles
//	// fill it now as it never changes
//	m_indexData = new unsigned int[ a_maxParticles * 6 ];
//	for ( unsigned int i = 0 ; i < a_maxParticles ; ++i )
//	{
//		m_indexData[i * 6 + 0] = i * 4 + 0;
//		m_indexData[i * 6 + 1] = i * 4 + 1;
//		m_indexData[i * 6 + 2] = i * 4 + 2;
//
//		m_indexData[i * 6 + 3] = i * 4 + 0;
//		m_indexData[i * 6 + 4] = i * 4 + 2;
//		m_indexData[i * 6 + 5] = i * 4 + 3;
//	}
//	
//	// create opengl buffers
//	
//
//	glGenVertexArrays(1, &m_vao);
//	glBindVertexArray(m_vao);
//
//	glGenBuffers(1, &m_vbo);
//	glGenBuffers(1, &m_ibo);	
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//	glBufferData(GL_ARRAY_BUFFER, a_maxParticles * 4 * sizeof(ParticleVertex), m_vertexData, GL_DYNAMIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_maxParticles * 6 * sizeof(unsigned int), m_indexData, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0); // position
//	glEnableVertexAttribArray(1); // colour
//	glEnableVertexAttribArray(2); // texCord
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + sizeof(glm::vec4));
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + sizeof(glm::vec4) + sizeof(glm::vec4));
//
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//void ParticleEmitter::emit()
//{
//	// only emit if there is a dead particle to use
//	if (m_deadParticles.empty())
//		return;
//
//	// remove it from the dead-pool
//	Particle* particle = m_deadParticles.back();
//	m_deadParticles.pop_back();
//
//	// assign its starting position
//	particle->position = m_position;
//
//	// randomise its lifespan
//	particle->lifetime = 0;
//	particle->lifespan = (rand() / (float)RAND_MAX) * (m_lifespanMax - m_lifespanMin) + m_lifespanMin;
//
//	// set starting size and colour
//	particle->colour = m_startColour;
//	particle->size = m_startSize;
//
//	// randomise velocity direction and strength
//	float velocity = (rand() / (float)RAND_MAX) * (m_velocityMax - m_velocityMin) + m_velocityMin;
//	particle->velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
//	particle->velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
//	particle->velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;
//	particle->velocity = glm::normalize( particle->velocity ) * velocity;
//
//	// add it to the alive-pool
//	m_aliveParticles.push_back(particle);
//}
//
//void ParticleEmitter::update(float a_deltaTime, const glm::mat4& a_cameraTransform)
//{
//	// spawn particles
//	m_emitTimer += a_deltaTime;
//	while (m_emitTimer > m_emitRate)
//	{
//		emit();
//		m_emitTimer -= m_emitRate;
//	}
//
//	auto iter = m_aliveParticles.begin();
//	unsigned int quad = 0;
//
//	// update particles and turn live particles into billboarded quads
//	while (iter != m_aliveParticles.end())
//	{
//		Particle* particle = (*iter);
//
//		particle->lifetime += a_deltaTime;
//		if (particle->lifetime >= particle->lifespan)
//		{
//			// return to dead pool
//			m_deadParticles.push_back(particle);
//			iter = m_aliveParticles.erase(iter);
//		}
//		else
//		{
//			// move particle
//			particle->position += particle->velocity * a_deltaTime;
//
//			// size particle
//			particle->size = glm::mix( m_startSize, m_endSize, particle->lifetime / particle->lifespan );
//
//			// colour particle
//			particle->colour = glm::mix( m_startColour, m_endColour, particle->lifetime / particle->lifespan );
//
//			// make a quad the correct size and colour
//			float halfSize = particle->size * 0.5f;
//
//			m_vertexData[quad * 4 + 0].position = glm::vec4( halfSize, halfSize, 0, 1 );
//			m_vertexData[quad * 4 + 0].colour = particle->colour;
//			m_vertexData[quad * 4 + 0].texCord = glm::vec2(1, 1);
//
//			m_vertexData[quad * 4 + 1].position = glm::vec4( -halfSize, halfSize, 0, 1 );
//			m_vertexData[quad * 4 + 1].colour = particle->colour;
//			m_vertexData[quad * 4 + 1].texCord = glm::vec2(0, 1);
//
//			m_vertexData[quad * 4 + 2].position = glm::vec4( -halfSize, -halfSize, 0, 1 );
//			m_vertexData[quad * 4 + 2].colour = particle->colour;
//			m_vertexData[quad * 4 + 2].texCord = glm::vec2(0, 0);
//
//			m_vertexData[quad * 4 + 3].position = glm::vec4( halfSize, -halfSize, 0, 1 );
//			m_vertexData[quad * 4 + 3].colour = particle->colour;
//			m_vertexData[quad * 4 + 3].texCord = glm::vec2(1, 0);
//			
//			// create billboard transform
//			glm::vec3 zAxis = glm::normalize( a_cameraTransform[3].xyz - particle->position );
//			glm::vec3 xAxis = glm::cross( glm::vec3(a_cameraTransform[1].xyz), zAxis );
//			glm::vec3 yAxis = glm::cross( zAxis, xAxis );
//			glm::mat3 billboard(xAxis,yAxis,zAxis);
//			
//			m_vertexData[quad * 4 + 0].position.xyz = billboard * m_vertexData[quad * 4 + 0].position.xyz + particle->position;
//			m_vertexData[quad * 4 + 1].position.xyz = billboard * m_vertexData[quad * 4 + 1].position.xyz + particle->position;
//			m_vertexData[quad * 4 + 2].position.xyz = billboard * m_vertexData[quad * 4 + 2].position.xyz + particle->position;
//			m_vertexData[quad * 4 + 3].position.xyz = billboard * m_vertexData[quad * 4 + 3].position.xyz + particle->position;
//			
//			++quad;
//			++iter;
//		}
//	}
//}
//
//void ParticleEmitter::draw(glm::mat4 a_viewMatrix, glm::mat4 a_projectionMatrix)
//{
//	glDisable(GL_DEPTH_TEST);
//
//	// sync the particle vertex buffer based on how many alive particles there are
//	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, m_aliveParticles.size() * 4 * sizeof(ParticleVertex), m_vertexData);
//
//	// bind shader to the GPU
//	glUseProgram(m_shader);
//
//	// fetch locations of the view and projection matrices and bind them
//	unsigned int location = glGetUniformLocation(m_shader,"view");
//	glUniformMatrix4fv(location, 1, false, glm::value_ptr(a_viewMatrix));
//
//	location = glGetUniformLocation(m_shader,"projection");
//	glUniformMatrix4fv(location, 1, false, glm::value_ptr(a_projectionMatrix));
//
//	// activate texture slot 0 and bind our texture to it
//	glActiveTexture(0);
//	glBindTexture(GL_TEXTURE_2D, m_texture);
//
//	// fetch the location of the texture sampler and bind it to 0
//	location = glGetUniformLocation(m_shader,"textureMap");
//	glUniform1i(location, 0);
//
//	// draw particles
//	glBindVertexArray( m_vao );
//	glDrawElements(GL_TRIANGLES, (unsigned int)m_aliveParticles.size() * 6, GL_UNSIGNED_INT, 0);
//	glEnable(GL_DEPTH_TEST);
//}
