#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	17/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	20/08/2015
//--------------------------------

#include "glm\mat4x4.hpp"
namespace openGL
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		glm::mat4 GetProjectionView();

	private:
		glm::mat4 m_transform;
		glm::mat4 m_projection;
		glm::mat4 m_view;
	};
}