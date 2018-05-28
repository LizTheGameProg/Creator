#pragma once

#include "basescene.h"

namespace AIE_2ND_YEAR
{
	class SoftBodies : public BaseScene
	{
	public:
		SoftBodies(PhysXVariables * PhysX_Variables);
		~SoftBodies(void);

		virtual void update(float DeltaTime);
		virtual void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

	private:
		//std::vector<PxRigidActor *> m_PhysXActors;

		unsigned int	m_shader;
		unsigned int	m_texture;

		unsigned int	m_clothIndexCount;
		unsigned int	m_clothVertexCount;
		glm::vec3 *		m_clothPositions;

		unsigned int	m_clothVAO, m_clothVBO, m_clothTextureVBO, m_clothIBO;

		//PxCloth*		createCloth(const glm::vec3& a_position, 
		//				    unsigned int& a_vertexCount, unsigned int& a_indexCount, 
		//				    const glm::vec3* a_vertices,
		//				    unsigned int* a_indices);
		//
		//PxCloth*		m_cloth;
	};
}
