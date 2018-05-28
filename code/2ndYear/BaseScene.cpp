#include "BaseScene.h"

#include <Gizmos.h>
#include <Utilities.h>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\ext.hpp>
namespace AIE_2ND_YEAR
{
	BaseScene::BaseScene(PhysXVariables * a_physX_Variables) : m_physX_Variables(a_physX_Variables)
	{

	}

	BaseScene::~BaseScene(void)
	{

	}

	void BaseScene::update(float a_deltaTime)
	{

	}

	void BaseScene::render(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
	{

	}

	//void BaseScene::addWidget(PxShape * shape, PxRigidActor * actor) 
	//{ 
	//    PxGeometryType::Enum type = shape->getGeometryType();
	//    switch(type) 
	//    {  
	//		case PxGeometryType::eBOX:
	//			addBox(shape,actor);
	//		break;
	//		case PxGeometryType::eSPHERE:
	//			addSphere(shape,actor);
	//		break;
	//		case PxGeometryType::eCAPSULE:
	//			addCapsule(shape,actor);
	//		break;
	//    } 
	//}
	//
	//void BaseScene::addBox(PxShape * pShape, PxRigidActor * actor) 
	//{
	//	//get the geometry for this PhysX collision volume
	//	PxBoxGeometry geometry;
	//	float width = 1, height = 1, length = 1;
	//	bool status = pShape->getBoxGeometry(geometry);
	//	if(status)
	//	{
	//		width = geometry.halfExtents.x;
	//		height = geometry.halfExtents.y;
	//		length = geometry.halfExtents.z;
	//	}
	//	//get the transform for this PhysX collision volume
	//	PxMat44 m(PxShapeExt::getGlobalPose(*pShape));
	//	glm::mat4 M = Px2Glm(m);
	//	glm::vec3 position = Px2GlV3(m.getPosition());
	//	//get the position out of the transform
	//	glm::vec3 extents = glm::vec3(width,height,length);
	//	glm::vec4 colour = glm::vec4(1,0,0,1);
	//	//create our box gizmo
	//	Gizmos::addAABBFilled(position,extents,colour,&M);
	//}
	//
	//void BaseScene::addSphere(PxShape * pShape, PxRigidActor * actor)
	//{
	//	//get the geometry for this PhysX collision volume
	//	PxSphereGeometry geometry;
	//	float radius = 1;
	//	bool status = pShape->getSphereGeometry(geometry);
	//	if(status)
	//	{
	//		radius = geometry.radius;
	//	}
	//	//get the transform for this PhysX collision volume
	//	PxMat44 m(PxShapeExt::getGlobalPose(*pShape));
	//	glm::mat4 M = Px2Glm(m);
	//	glm::vec3 position = Px2GlV3(m.getPosition());
	//	//get the position out of the transform
	//	glm::vec4 colour = glm::vec4(0,1,0,1);
	//	//create our box gizmo
	//	Gizmos::addSphere(position, 4, 8, radius, colour, &M);
	//
	//}
	//
	//void BaseScene::addGrid(const glm::vec3& a_center, const glm:: mat4* a_transform,int increments,float size)
	//{
	//	int halfIncrements = increments/2;
	//	for ( int i = 0 ; i < increments+1 ; ++i )
	//	{
	//		glm::vec4 colour =  i == halfIncrements ? glm::vec4(1,0,1,1) : glm::vec4(0,0,0,1);
	//		glm::vec3 l1Start = glm::vec3((-halfIncrements + i)*size, 0, halfIncrements*size);
	//		glm::vec3 l1End = glm::vec3((-halfIncrements + i)*size, 0, -halfIncrements*size);
	//		glm::vec3 l2Start = glm::vec3(halfIncrements*size, 0, (-halfIncrements + i)*size);
	//		glm::vec3 l2End = glm::vec3(-halfIncrements*size, 0, (-halfIncrements + i)*size);
	//	
	//		l1Start = (*a_transform * glm::vec4(l1Start,0)).xyz + a_center;
	//		l1End = (*a_transform * glm::vec4(l1End,0)).xyz + a_center;
	//		l2Start = (*a_transform * glm::vec4(l2Start,0)).xyz + a_center;
	//		l2End = (*a_transform * glm::vec4(l2End,0)).xyz + a_center;
	//		Gizmos::addLine( l1Start, l1End, colour);
	//		Gizmos::addLine(l2Start, l2End, colour);
	//	}
	//}
	//
	//void BaseScene::addCapsule(PxShape* pShape,PxRigidActor* actor) 
	//{
	//	//creates a gizmo representation of a capsule using 2 spheres and a cylinder
	//
	//	glm::vec4 colour(0,0,1,1);  //make our capsule blue
	//	PxCapsuleGeometry capsuleGeometry;
	//	float radius = 1; //temporary values whilst we try and get the real value from PhysX
	//	float halfHeight = 1;;
	//	//get the geometry for this PhysX collision volume
	//	bool status = pShape->getCapsuleGeometry(capsuleGeometry);
	//	if(status)
	//	{
	//		//this should always happen but just to be safe we check the status flag
	//		radius = capsuleGeometry.radius; //copy out capsule radius
	//		halfHeight = capsuleGeometry.halfHeight; //copy out capsule half length
	//	}
	//	//get the world transform for the centre of this PhysX collision volume
	//	PxTransform transform = PxShapeExt::getGlobalPose(*pShape);
	//	//use it to create a matrix
	//	PxMat44 m(transform);
	//	//convert it to an open gl matrix for adding our gizmos
	//	glm::mat4 M = Px2Glm(m);
	//	//get the world position from the PhysX tranform
	//	glm::vec3 position = Px2GlV3(transform.p); 
	//	glm::vec4 axis(halfHeight,0,0,0);	//axis for the capsule
	//	axis = M * axis; //rotate axis to correct orientation
	//	//add our 2 end cap spheres...
	//	Gizmos::addSphere(position+axis.xyz,10,10,radius,colour);
	//	Gizmos::addSphere(position-axis.xyz,10,10,radius,colour);
	//	//the cylinder gizmo is oriented 90 degrees to what we want so we need to change the rotation matrix...
	//	glm::mat4 m2 = glm::rotate(M,11/7.0f,0.0f,0.0f,1.0f); //adds an additional rotation onto the matrix
	//	//now we can use this matrix and the other data to create the cylinder...
	//	Gizmos::addCylinderFilled(position,radius,halfHeight,10,colour,&m2);
	//}
	//
	//glm::mat4 BaseScene::Px2Glm(PxMat44 a_matrix4)
	//{
	//	glm::mat4 m4;
	//	m4[0][0] = a_matrix4[0][0];
	//	m4[0][1] = a_matrix4[0][1];
	//	m4[0][2] = a_matrix4[0][2];
	//	m4[0][3] = a_matrix4[0][3];
	//
	//	m4[1][0] = a_matrix4[1][0];
	//	m4[1][1] = a_matrix4[1][1];
	//	m4[1][2] = a_matrix4[1][2];
	//	m4[1][3] = a_matrix4[1][3];
	//
	//	m4[2][0] = a_matrix4[2][0];
	//	m4[2][1] = a_matrix4[2][1];
	//	m4[2][2] = a_matrix4[2][2];
	//	m4[2][3] = a_matrix4[2][3];
	//
	//	m4[3][0] = a_matrix4[3][0];
	//	m4[3][1] = a_matrix4[3][1];
	//	m4[3][2] = a_matrix4[3][2];
	//	m4[3][3] = a_matrix4[3][3];
	//
	//	return m4;
	//}
	//
	//glm::vec3 BaseScene::Px2GlV3(PxVec3 a_vector3)
	//{
	//	glm::vec3 v3;
	//	v3.x = a_vector3.x;
	//	v3.y = a_vector3.y;
	//	v3.z = a_vector3.z;
	//	return v3;
	//}
	//
	//PxVec3 BaseScene::glm2Px(glm::vec3 a_Vector3)
	//{
	//	PxVec3 v3;
	//	v3.x = a_Vector3.x;
	//	v3.y = a_Vector3.y;
	//	v3.z = a_Vector3.z;
	//	return v3;
	//}

	void BaseScene::InitFBXSceneResource(FBXFile *a_pScene)
	{
		// how manu meshes and materials are stored within the fbx file
		unsigned int meshCount = a_pScene->getMeshCount();
		unsigned int matCount = a_pScene->getMaterialCount();

		// loop through each mesh
		for(int i = 0; i < meshCount; ++i)
		{
			// get the current mesh
			FBXMeshNode *pMesh = a_pScene->getMeshByIndex(i);

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

			// Send the vertex data to the VBO
			glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(FBXVertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);

			// send the index data to the IBO
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);

			// enable the attribute locations that will be used on our shaders
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			// tell our shaders where the information within our buffers lie
			// eg: attrubute 0 is expected to be the verticy's position. it should be 4 floats, representing xyzw
			// eg: attrubute 1 is expected to be the verticy's color. it should be 4 floats, representing rgba
			// eg: attrubute 2 is expected to be the verticy's texture coordinate. it should be 2 floats, representing U and V
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *) FBXVertex::PositionOffset);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *) FBXVertex::ColourOffset);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char *) FBXVertex::TexCoord1Offset);

			// finally, where done describing our mesh to the shader
			// we can describe the next mesh
			glBindVertexArray(0);
		}

		// Loop through each material and load the texture
		for(unsigned int i = 0; i < matCount; ++i)
		{
			// get the current material being loaded
			FBXMaterial *pMaterial = a_pScene->getMaterialByIndex(i);

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

			for(unsigned int j = 0; j < FBXMaterial::TextureTypes_Count; ++j)
			{
				// find the path to the texture to be loaded
				std::string path = a_pScene->getPath();

				// append the filename of the texture
				path += pMaterial->textureFilenames[j];

				// load the texture using SOIL
				pMaterial->textureIDs[j] = SOIL_load_OGL_texture(path.c_str(), 4, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);

				// lets just print what is loaded to the console...
				printf("Loading texture %i: %s - ID: %i\n", j, path.c_str(), pMaterial->textureIDs[j]);
			}
		}
	}

	void BaseScene::DestroyFBXSceneResource(FBXFile *a_pScene)
	{
		// how manu meshes and materials are stored within the fbx file
		unsigned int meshCount = a_pScene->getMeshCount();
		unsigned int matCount = a_pScene->getMaterialCount();

		// remove meshes
		for(unsigned int i = 0; i < meshCount; i++)
		{
			// Get the current mesh and retrive the render data we assigned to m_userData
			FBXMeshNode* pMesh = a_pScene->getMeshByIndex(i);
			OGL_FBXRenderData *ro = (OGL_FBXRenderData *) pMesh->m_userData;

			// delete the buffers and free memory from the graphics card
			glDeleteBuffers(1, &ro->VBO);
			glDeleteBuffers(1, &ro->IBO);
			glDeleteVertexArrays(1, &ro->VAO);

			// this is memory we created earlier in the InitFBXSceneResources function
			// make sure to destroy it
			delete ro;

		}

		// loop through each of the materials
		for(int i = 0; i < matCount; i++)
		{
			// get the current material
			FBXMaterial *pMaterial = a_pScene->getMaterialByIndex(i);
			for(int j = 0; j < FBXMaterial::TextureTypes_Count; j++)
			{
				// delete the texture if it was loaded
				if(pMaterial->textureIDs[j] != 0)
					glDeleteTextures(1, &pMaterial->textureIDs[j]);
			}
		}
	}

	void BaseScene::UpdateFBXSceneResource(FBXFile *a_pScene)
	{
		for(int i = 0; i < a_pScene->getMeshCount(); ++i)
		{
			// get the current mesh
			FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

			// if you move an object around within your scene
			// children nodes are not updated until this function is called.
			mesh->updateGlobalTransform();
		}
	}

	void BaseScene::RenderFBXSceneResource(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection, glm::mat4 a_globalTransform)
	{
		unsigned int m_shader = m_shaderMap["SimpleFBX_Tutorial"];

		// activate a shader
		glUseProgram(m_shader);

		// get the location of uniforms on the shader
		GLint uDiffuseTexture = glGetUniformLocation(m_shader, "DiffuseTexture");
		GLint uDiffuseColor = glGetUniformLocation(m_shader, "DiffuseColor");

		GLint uModel = glGetUniformLocation(m_shader, "Model");
		GLint uView = glGetUniformLocation(m_shader, "View");
		GLint uProjection = glGetUniformLocation(m_shader, "Projection");

		// for each mesh in the model...
		for(int i = 0; i < a_pScene->getMeshCount(); ++i)
		{
			// get the current mesh
			FBXMeshNode *mesh = a_pScene->getMeshByIndex(i);

			// get the render data attached to the m_userData pointer for this mesh
			OGL_FBXRenderData *ro = (OGL_FBXRenderData *) mesh->m_userData;

			// Bind the texture to one of the ActiveTextures
			// if your shader supported multiple textures, you would bind each texture to a new Active Texture ID here
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->m_material->textureIDs[FBXMaterial::DiffuseTexture]);

			// reset back to the default active texture
			glActiveTexture(GL_TEXTURE0);

			// tell the shader which texture to use
			glUniform1i(uDiffuseTexture, 1);

			// send the Model, View and Projection Matrices to the shader
			glUniformMatrix4fv(uModel, 1, false, glm::value_ptr(mesh->m_globalTransform));
			glUniformMatrix4fv(uView, 1, false, glm::value_ptr(a_view));
			glUniformMatrix4fv(uProjection, 1, false, glm::value_ptr(a_projection));

			// bind our vertex array object
			// remember in the initialise function, we bound the VAO and IBO to the VAO
			// so when we bind the VAO, openGL knows what what vertices,
			// indices and vertex attributes to send to the shader
			glBindVertexArray(ro->VAO);
			glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);

		}

		// finally, we have finished rendering the meshes
		// disable the vao
		glBindVertexArray(0);
		// disable this shader
		glUseProgram(0);
	}

	void BaseScene::createShaderPrograms()
	{
		// SimpleFBX_Tutorial
		{
			const char* inputs[] = {"Position", "Color", "TexCoord1"};
			const char* outputs[] = {"outColour"};

			GLuint vs = Utility::loadShader("./shaders/SimpleFBX_Tutorial.vert", GL_VERTEX_SHADER);
			GLuint fs = Utility::loadShader("./shaders/SimpleFBX_Tutorial.frag", GL_FRAGMENT_SHADER);

			m_shaderMap["SimpleFBX_Tutorial"] = Utility::createProgram(vs, 0, 0, 0, fs, 3, inputs, 1, outputs);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		// textured
		{
			const char* inputs[] = {"position", "colour", "textureCoordinate"};

			GLuint vs = Utility::loadShader("./shaders/textured.vert", GL_VERTEX_SHADER);
			GLuint fs = Utility::loadShader("./shaders/textured.frag", GL_FRAGMENT_SHADER);

			m_shaderMap["textured"] = Utility::createProgram(vs, 0, 0, 0, fs, 3, inputs);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}
	}
}