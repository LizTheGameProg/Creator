#ifndef FBXSceneResource_H
#define FBXSceneResource_H

#include "FBXFile.h"
#include "ShaderProgram.h"

class FBXSceneResource
{
public:
	FBXSceneResource(void);
	FBXSceneResource(FBXFile * a_FBXFile, ShaderProgram * a_shaderProgram, bool a_UseAnimations);
	FBXSceneResource(const char * filePath, FBXFile::UNIT_SCALE unitScale, ShaderProgram * a_shaderProgram);
	~FBXSceneResource(void);

	// Functions
	void Update();
	void Render(glm::mat4 viewMatrix, glm::mat4 ProjectionMatrix, float a_time);
	void Destroy();
private:
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	FBXFile * m_fbx;
	ShaderProgram * m_shaderProgram;

	bool isTextureLoaded[8];
	bool isThereBones;
	unsigned int m_texture_missing;
	//std::map<FBXMaterial::TextureTypes, const char *> TextureTypes;

	void Init(ShaderProgram * a_shaderProgram, FBXFile::UNIT_SCALE unitScale = FBXFile::UNITS_CENTIMETER, const char * filePath = nullptr, bool a_UseAnimations = false);
	void UpdateAnimation();
	
};

#endif