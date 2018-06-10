#pragma once
#include "Mesh.h"
#include "glm\mat4x4.hpp"

namespace ANGINE
{
	class Quad : public Mesh
	{
	public:
		Quad();
		Quad(unsigned int programID, unsigned int textureID);
		~Quad();

		virtual void update(float deltaTime);
		virtual void render(glm::mat4 projectionView);

		void SetProgram(unsigned int programID);
		void SetTexture(unsigned int textureID);
		void SetDimensions(float width, float height);
		void SetDimensions(glm::vec2 dimensions);

	private:
		void init();

		unsigned int programID;
		unsigned int textureID;

		// Position and uv coordinates
		float vertexData[24];
		bool vertexDataHasChanged;

	public:
		glm::mat4 transform;
	};
}