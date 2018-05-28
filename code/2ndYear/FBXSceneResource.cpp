#include "FBXSceneResource.h"
#include "Utilities.h"
#include <SOIL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

FBXSceneResource::FBXSceneResource(void)
{
	m_fbx = nullptr;
}

FBXSceneResource::FBXSceneResource(FBXFile * a_FBXFile, ShaderProgram * a_shaderProgram, bool a_UseAnimations)
{
	m_fbx = a_FBXFile;
	Init(a_shaderProgram);
	isThereBones = a_UseAnimations;
}

FBXSceneResource::FBXSceneResource(const char * a_filePath, FBXFile::UNIT_SCALE a_unitScale, ShaderProgram * a_shaderProgram)
{
	Init(a_shaderProgram, a_unitScale, a_filePath);
}

FBXSceneResource::~FBXSceneResource(void)
{
	if(m_fbx != nullptr)
	{
		Destroy();
		m_fbx->unload();
		delete m_fbx;
		m_fbx = nullptr;
	}
}

void FBXSceneResource::Init(ShaderProgram * a_shaderProgram, FBXFile::UNIT_SCALE a_unitScale, const char * a_filePath, bool a_UseAnimations)
{
	if(a_filePath != nullptr)
	{
		m_fbx = new FBXFile();
		m_fbx->load(a_filePath, a_unitScale);
	}

	m_shaderProgram = a_shaderProgram;

	isThereBones = a_UseAnimations;
	

	// how manu meshes and materials are stored within the fbx file
	unsigned int meshCount = m_fbx->getMeshCount();
	unsigned int matCount = m_fbx->getMaterialCount();

	// loop through each mesh
	for(unsigned int i=0; i<meshCount; ++i)
	{
		// get the current mesh
		FBXMeshNode *pMesh = m_fbx->getMeshByIndex(i);

		// genorate our OGL_FBXRenderData for storing the meshes VBO, IBO and VAO
		// and assign it to the meshes m_userData pointer so that we can retrive 
		// it again within the render function
		OGL_FBXRenderData *ro = new OGL_FBXRenderData();
		pMesh->m_userData = ro;

		// OPENGL: genorate the VBO, IBO and VAO
		glGenBuffers(1, &ro->VBO);
		glGenBuffers(1, &ro->IBO);
		glGenVertexArrays(1, &ro->VAO);

		// OPENGL: Bind  VAO, and then bind the VBO and IBO to the VAO
		glBindVertexArray(ro->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, ro->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro->IBO);

		if(isThereBones)
		{
			// Send the vertex data to the VBO
			glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(FBXVertex), pMesh->m_vertices.data(), GL_DYNAMIC_DRAW);

			// send the index data to the IBO
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_DYNAMIC_DRAW);
		}
		else
		{
			// Send the vertex data to the VBO
			glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(FBXVertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);

			// send the index data to the IBO
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);
		}

		// enable the attribute locations that will be used on our shaders
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);
		glEnableVertexAttribArray(8);

		// tell our shaders where the information within our buffers lie
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::PositionOffset );
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::ColourOffset	 );
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::NormalOffset	 );
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TangentOffset	 );
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::BiNormalOffset );
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::IndicesOffset	 );
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::WeightsOffset	 );
		glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord1Offset);
		glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *)FBXVertex::TexCoord2Offset);

		// finally, where done describing our mesh to the shader
		// we can describe the next mesh
		glBindVertexArray(0);
	}

	// Loop through each material and load the texture
	for(unsigned int i = 0; i<matCount; ++i)
	{
		// get the current material being loaded
		FBXMaterial *pMaterial = m_fbx->getMaterialByIndex(i);

		// each material can optionally have many different textures that can be used to describe how the object should be rendered.
		// Look at the FBXMaterial structure.
		// the following textures can be assigned to a material within the 3D modeling programs
		// we can optionally support loading these in...
		// - DiffuseTexture,
		// - AmbientTexture,
		// - GlowTexture,
		// - SpecularTexture,
		// - GlossTexture,
		// - NormalTexture,
		// - AlphaTexture,
		// - DisplacementTexture,

		for(unsigned int j = 0; j<FBXMaterial::TextureTypes_Count; ++j)
		{
			// find the path to the texture to be loaded
			std::string path = m_fbx->getPath();

			char * textureFileName = pMaterial->textureFilenames[j];

			if(*textureFileName == '\0')
			{
				isTextureLoaded[j] = false;
			}
			else
			{
				isTextureLoaded[j] = true;
			}
			// append the filename of the texture
			path += pMaterial->textureFilenames[j];

			// load the texture using SOIL
			pMaterial->textureIDs[j] = SOIL_load_OGL_texture(path.c_str(), 4, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);

			// lets just print what is loaded to the console...
			printf("Loading texture %i: %s - ID: %i\n", j, path.c_str(), pMaterial->textureIDs[j]);
		}
	}
	//TextureTypes[FBXMaterial::DiffuseTexture]		= "DiffuseTexture";
	//TextureTypes[FBXMaterial::AmbientTexture]		= "AmbientTexture";
	//TextureTypes[FBXMaterial::GlowTexture]			= "GlowTexture";
	//TextureTypes[FBXMaterial::SpecularTexture]		= "SpecularTexture";
	//TextureTypes[FBXMaterial::GlossTexture]			= "GlossTexture";
	//TextureTypes[FBXMaterial::NormalTexture]		= "NormalTexture";
	//TextureTypes[FBXMaterial::AlphaTexture]			= "AlphaTexture";
	//TextureTypes[FBXMaterial::DisplacementTexture]	= "DisplacementTexture";
	m_texture_missing = SOIL_load_OGL_texture("./Build/textures/missing.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
}

void FBXSceneResource::Destroy()
{
	// how manu meshes and materials are stored within the fbx file
	unsigned int meshCount = m_fbx->getMeshCount();
	unsigned int matCount = m_fbx->getMaterialCount();

	// remove meshes
	for(unsigned int i=0; i<meshCount; i++)
	{
		// Get the current mesh and retrive the render data we assigned to m_userData
		FBXMeshNode* pMesh = m_fbx->getMeshByIndex(i);
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *)pMesh->m_userData;

		// delete the buffers and free memory from the graphics card
		glDeleteBuffers(1, &ro->VBO);
		glDeleteBuffers(1, &ro->IBO);
		glDeleteVertexArrays(1, &ro->VAO);

		// this is memory we created earlier in the InitFBXSceneResources function
		// make sure to destroy it
		delete ro;
	}

	// loop through each of the materials
	for(unsigned int i=0; i<matCount; i++)
	{
		// get the current material
		FBXMaterial *pMaterial = m_fbx->getMaterialByIndex(i);
		for(int j=0; j<FBXMaterial::TextureTypes_Count; j++)
		{
			// delete the texture if it was loaded
			if( pMaterial->textureIDs[j] != 0 )
				glDeleteTextures(1, &pMaterial->textureIDs[j]);
		}
	}
	glDeleteTextures(1, &m_texture_missing);
}

void FBXSceneResource::Update()
{
	if(isThereBones)
	{
		FBXSkeleton* skeleton = m_fbx->getSkeletonByIndex(0);
		FBXAnimation* animation = m_fbx->getAnimationByIndex(0);

		// evaluate the animation to update bones
		skeleton->evaluate( animation, Utility::getTotalTime() );
	}

	for(unsigned int i=0; i<m_fbx->getMeshCount(); ++i)
	{
		// get the current mesh
		FBXMeshNode *mesh = m_fbx->getMeshByIndex(i);

		// if you move an object around within your scene
		// children nodes are not updated until this function is called.
		mesh->updateGlobalTransform();
	}
}

void FBXSceneResource::Render(glm::mat4 a_cameraMatrix, glm::mat4 a_ProjectionMatrix, float a_time)
{
	glm::mat4 viewMatrix = glm::inverse(a_cameraMatrix);

	// for each mesh in the model...
	for(unsigned int i=0; i<m_fbx->getMeshCount(); ++i)
	{
		//m_shaderProgram->m_uInfo["View"] = (UniformInfo(UniformType::MAT4, &viewMatrix));
		//m_shaderProgram->m_uInfo["CameraPos"] = (UniformInfo(UniformType::MAT4, &a_cameraMatrix));
		// get the current mesh and skeleton
		FBXMeshNode *mesh = m_fbx->getMeshByIndex(i);
		int isBones;
		if(isThereBones)
		{
			isBones = 1;
		}
		else
		{
			isBones = 0;
		}
		//m_shaderProgram->m_uInfo["isBones"] = UniformInfo(UniformType::INT, &isBones);
		if(isThereBones)
		{
			FBXSkeleton * skeleton = m_fbx->getSkeletonByIndex(0);
			skeleton->updateBones();
			glm::mat4 * bones = skeleton->m_bones;
			//m_shaderProgram->m_uInfo["Bones"] = UniformInfo(UniformType::MAT4, &bones[0], skeleton->m_boneCount);
		}

		//m_shaderProgram->m_uInfo["Model"] = UniformInfo(UniformType::MAT4, &mesh->m_globalTransform);
		
		//for(int j = 0; j < FBXMaterial::TextureTypes_Count; j++)
		//{
		//	if(isTextureLoaded[j])
		//	{
		//		m_shaderProgram->m_uInfo[TextureTypes[(FBXMaterial::TextureTypes)j]] = UniformInfo((UniformType)(j + 7), &m_fbx->getMeshByIndex(i)->m_material->textureIDs[(FBXMaterial::TextureTypes)j]);
		//	}
		//	else
		//	{
		//		m_shaderProgram->m_uInfo[TextureTypes[(FBXMaterial::TextureTypes)j]] = UniformInfo((UniformType)(j + 7), &m_texture_missing);
		//	}
		//}

		
		
		m_shaderProgram->UseProgram();

		// get the render data attached to the m_userData pointer for this mesh
		OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;
		
		// bind our vertex array object
		// remember in the initialise function, we bound the VAO and IBO to the VAO
		// so when we bind the VAO, openGL knows what what vertices,
		// indices and vertex attributes to send to the shader
		glBindVertexArray(ro->VAO);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	// finally, we have finished rendering the meshes
	// disable this shader
	glUseProgram(0);
}