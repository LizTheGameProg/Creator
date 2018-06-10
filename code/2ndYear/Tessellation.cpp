#include "Tessellation.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

Tessellation::Tessellation()
{

}

Tessellation::~Tessellation()
{

}

bool Tessellation::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	Utility::build3DPlane(10, m_vao, m_vbo, m_ibo);

	m_texture = SOIL_load_OGL_texture("../../Build/textures/rock_diffuse.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	m_displacement = SOIL_load_OGL_texture("../../Build/textures/rock_displacement.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	unsigned int vs = Utility::loadShader("../../Build/shaders/displace.vert", GL_VERTEX_SHADER);
	unsigned int cs = Utility::loadShader("../../Build/shaders/displace.cont", GL_TESS_CONTROL_SHADER);
	unsigned int es = Utility::loadShader("../../Build/shaders/displace.eval", GL_TESS_EVALUATION_SHADER);
	unsigned int fs = Utility::loadShader("../../Build/shaders/displace.frag", GL_FRAGMENT_SHADER);
	m_shader = Utility::createProgram(vs, cs, es, 0, fs);
	glDeleteShader(vs);
	glDeleteShader(cs);
	glDeleteShader(es);
	glDeleteShader(fs);

	m_time = 0.0f;

	return true;
}

void Tessellation::onUpdate(float a_deltaTime) 
{
	m_time += a_deltaTime;

	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	//// add a 20x20 grid on the XZ-plane
	//for ( int i = 0 ; i < 21 ; ++i )
	//{
	//	Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//	
	//	Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void Tessellation::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	glUseProgram(m_shader);

	unsigned int location = glGetUniformLocation(m_shader, "projectionView");
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(m_projectionMatrix * viewMatrix));

	// activate texture slot 0 and bind our texture to it
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_displacement);
	
	// fetch the location of the texture sampler and bind it to 0
	location = glGetUniformLocation(m_shader,"displacementMap");
	glUniform1i(location, 1);
	
	location = glGetUniformLocation(m_shader, "displacementScale");
	glUniform1f(location, 1.0f);

	location = glGetUniformLocation(m_shader, "time");
	glUniform1f(location, m_time);

	// activate texture slot 0 and bind our texture to it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	// fetch the location of the texture sampler and bind it to 0
	location = glGetUniformLocation(m_shader,"textureMap");
	glUniform1i(location, 0);

	glBindVertexArray(m_vao);
	glPatchParameteri(GL_PATCH_VERTICES, 3);	
	glDrawElements(GL_PATCHES, 6, GL_UNSIGNED_INT, nullptr);

	glUseProgram(0);
}

void Tessellation::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new Tessellation();
//	
//	if (app->create("AIE - Tessellation",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}