#include "SoftBodies.h"

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm\ext.hpp>
#include <SOIL.h>
//#include <PxTkStream.h>
#include <Utilities.h>
#include "Gizmos.h"

namespace AIE_2ND_YEAR
{
	SoftBodies::SoftBodies(PhysXVariables * a_physX_Variables) : BaseScene(a_physX_Variables)
	{
		// set cloth properties
		float springSize = 0.2f;
		unsigned int springRows = 40;
		unsigned int springCols = 40;

		// this position will represent the top middle vertex
		glm::vec3 clothPosition = glm::vec3(-15, 12, 0);

		// shifting grid position for looks
		float halfWidth = springRows * springSize * 0.5f;

		// generate vertices for a grid with texture coordinates
		m_clothVertexCount = springRows * springCols;
		m_clothPositions = new glm::vec3[m_clothVertexCount];
		glm::vec2* clothTextureCoords = new glm::vec2[m_clothVertexCount];
		for(unsigned int r = 0; r < springRows; ++r)
		{
			for(unsigned int c = 0; c < springCols; ++c)
			{
				m_clothPositions[r * springCols + c].x = clothPosition.x + springSize * c;
				m_clothPositions[r * springCols + c].y = clothPosition.y;
				m_clothPositions[r * springCols + c].z = clothPosition.z + springSize * r - halfWidth;

				clothTextureCoords[r * springCols + c].x = 1.0f - r / (springRows - 1.0f);
				clothTextureCoords[r * springCols + c].y = 1.0f - c / (springCols - 1.0f);
			}
		}

		// set up indices for a grid
		m_clothIndexCount = (springRows - 1) * (springCols - 1) * 2 * 3;
		unsigned int * indices = new unsigned int[m_clothIndexCount];
		unsigned int * index = indices;
		for(unsigned int r = 0; r < (springRows - 1); ++r)
		{
			for(unsigned int c = 0; c < (springCols - 1); ++c)
			{
				// indices for the 4 quad corner vertices
				unsigned int i0 = r * springCols + c;
				unsigned int i1 = i0 + 1;
				unsigned int i2 = i0 + springCols;
				unsigned int i3 = i2 + 1;

				// every second quad changes the triangle order
				if((c + r) % 2)
				{
					*index++ = i0; *index++ = i2; *index++ = i1;
					*index++ = i1; *index++ = i2; *index++ = i3;
				}
				else
				{
					*index++ = i0; *index++ = i2; *index++ = i3;
					*index++ = i0; *index++ = i3; *index++ = i1;
				}
			}
		}

		// set up opengl data for the grid, with the positions as dynamic
		glGenVertexArrays(1, &m_clothVAO);
		glBindVertexArray(m_clothVAO);

		glGenBuffers(1, &m_clothIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_clothIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_clothIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_clothVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_clothVBO);
		glBufferData(GL_ARRAY_BUFFER, m_clothVertexCount * (sizeof(glm::vec3)), 0, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0); // position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (char*) 0);

		glGenBuffers(1, &m_clothTextureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_clothTextureVBO);
		glBufferData(GL_ARRAY_BUFFER, m_clothVertexCount * (sizeof(glm::vec2)), clothTextureCoords, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1); // texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (char*) 0);

		glBindVertexArray(0);

		unsigned int vs = Utility::loadShader("./shaders/basic.vert", GL_VERTEX_SHADER);
		unsigned int fs = Utility::loadShader("./shaders/basic.frag", GL_FRAGMENT_SHADER);
		m_shader = Utility::createProgram(vs, 0, 0, 0, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);

		m_texture = SOIL_load_OGL_texture("./textures/numbered_grid.tga",
			SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		//m_cloth = createCloth(clothPosition, m_clothVertexCount, m_clothIndexCount, m_clothPositions, indices);
		//m_physX_Variables->m_PhysicsScene->addActor(*m_cloth);

		// texture coords and indices no longer needed
		delete[] clothTextureCoords;
		delete[] indices;
	}

	SoftBodies::~SoftBodies(void)
	{
		//glDeleteProgram(m_shader);
		//glDeleteTextures(1, &m_texture);
	}

	void SoftBodies::update(float a_deltaTime)
	{
		//PxClothReadData* data = m_cloth->lockClothReadData();
		//for ( unsigned int i = 0 ; i < m_clothVertexCount ; ++i) 
		//{
		//	m_clothPositions[i] = glm::vec3(data->particles[i].pos.x,
		//					data->particles[i].pos.y,
		//					data->particles[i].pos.z); 
		//}
		//data->unlock();
	}

	void SoftBodies::render(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
	{
		//for (auto actor : m_PhysXActors)
		//{
		//	PxU32 nShapes = actor->getNbShapes();
		//	PxShape** shapes = new PxShape*[nShapes];
		//	actor->getShapes(shapes, nShapes);
		//	// Render all the shapes in the physx actor (for early tutorials there is just one)
		//	while (nShapes--)
		//	{
		//		 addWidget(shapes[nShapes],actor); 
		//	}
		//	delete [] shapes;
		//}

		// clear the backbuffer
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind shader and transforms, along with texture
		glUseProgram(m_shader);

		int location = glGetUniformLocation(m_shader, "projectionView");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(a_projectionMatrix * a_viewMatrix));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		// update vertex positions from the cloth
		glBindBuffer(GL_ARRAY_BUFFER, m_clothVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_clothVertexCount * sizeof(glm::vec3), m_clothPositions);

		// disable face culling so that we can draw it double-sided
		glDisable(GL_CULL_FACE);

		// bind and draw the cloth
		glBindVertexArray(m_clothVAO);
		glDrawElements(GL_TRIANGLES, m_clothIndexCount, GL_UNSIGNED_INT, 0);

		glEnable(GL_CULL_FACE);

		glBindVertexArray(0);
		glUseProgram(0);

		// draw the gizmos from this frame
		Gizmos::draw(a_viewMatrix, a_projectionMatrix);
	}

	//PxCloth* SoftBodies::createCloth(const glm::vec3& a_position, 
	//				unsigned int& a_vertexCount, unsigned int& a_indexCount, 
	//				const glm::vec3* a_vertices,
	//				unsigned int* a_indices)
	//{
	//	// set up the cloth description
	//	PxClothMeshDesc clothDesc;
	//	clothDesc.setToDefault();
	//	clothDesc.points.count = a_vertexCount; 
	//	clothDesc.triangles.count = a_indexCount / 3; 
	//	clothDesc.points.stride = sizeof(glm::vec3); 
	//	clothDesc.triangles.stride = sizeof(unsigned int) * 3; 
	//	clothDesc.points.data = a_vertices;
	//	clothDesc.triangles.data = a_indices;
	//
	//	// cook the geometry into fabric
	//	PxToolkit::MemoryOutputStream buf;
	//	if (m_physX_Variables->m_PhysicsCooker->cookClothFabric(clothDesc, PxVec3(0,-9.8f,0), buf) == false)
	//	{
	//		return nullptr;
	//	}
	//
	//	PxToolkit::MemoryInputData data(buf.getData(), buf.getSize());
	//	PxClothFabric* fabric = m_physX_Variables->m_Physics->createClothFabric(data);
	//
	//	// set up the particles for each vertex
	//	PxClothParticle* particles = new PxClothParticle[ a_vertexCount ];
	//	for ( unsigned int i = 0 ; i < a_vertexCount ; ++i )
	//	{
	//		particles[i].pos = PxVec3( a_vertices[i].x, a_vertices[i].y, a_vertices[i].z );
	//
	//		// set weights (0 means static)
	//		if ( a_vertices[i].x == a_position.x ) 
	//			particles[i].invWeight = 0;
	//		else
	//			particles[i].invWeight = 1.f;
	//	}
	//
	//	// create the cloth then setup the spring properties
	//	PxCloth* cloth = m_physX_Variables->m_Physics->createCloth(PxTransform( PxVec3(a_position.x,a_position.y,a_position.z) ), 
	//		*fabric, particles, PxClothCollisionData(), PxClothFlag::eSWEPT_CONTACT);
	//
	//	// we need to set some solver configurations
	//	if (cloth != nullptr) 
	//	{
	//		PxClothPhaseSolverConfig bendCfg;
	//		bendCfg.solverType= PxClothPhaseSolverConfig::eFAST;
	//		bendCfg.stiffness = 1;
	//		bendCfg.stretchStiffness = 0.5; 
	//		cloth->setPhaseSolverConfig(PxClothFabricPhaseType::eBENDING, bendCfg);
	//		cloth->setPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING, bendCfg);
	//		cloth->setPhaseSolverConfig(PxClothFabricPhaseType::eSHEARING, bendCfg);
	//		cloth->setPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING_HORIZONTAL, bendCfg);
	//		cloth->setDampingCoefficient(0.125f);
	//	}
	//
	//	delete[] particles;
	//
	//	return cloth;
	//}
}