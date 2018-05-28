#include "HelloWorld.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

bool HelloWorld::onCreate(int a_argc, char* a_argv[]) 
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

	m_sphereSun = glm::mat4();
	m_sphereMercury = glm::mat4();
	m_sphereVenus = glm::mat4();
	m_VenusOffset = glm::mat4();
	m_sphereNeith = glm::mat4();

	m_sphereMercury[3].z	+= 12;
	m_sphereVenus[3].z		+= 16;

	return true;
}

void HelloWorld::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// Sun
	glm::mat4 sunTransform = glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	translate(m_sphereSun, a_deltaTime);
	sunTransform = glm::rotate(sunTransform, a_deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
	m_sphereSun = m_sphereSun * sunTransform;
	glm::vec4 transSun = m_sphereSun[3];
	Gizmos::addSphere(transSun.xyz, 8, 8, 10, glm::vec4(0, 0, 0, 1), &m_sphereSun);


	// Mercury
	glm::mat4 MercuryTransform = glm::mat4();
	m_sphereMercury = glm::rotate(m_sphereMercury, a_deltaTime * -1, glm::vec3(0, 1, 0));
	MercuryTransform = m_sphereSun * m_sphereMercury;
	Gizmos::addSphere(MercuryTransform[3].xyz, 8, 8, 1, glm::vec4(0,0,0,1), &m_sphereMercury);

	// Venus
	m_VenusOffset = glm::rotate(m_VenusOffset, a_deltaTime * 2, glm::vec3(0.0f, 1.0f, 0.0f));
	m_sphereVenus = glm::rotate(m_sphereVenus, a_deltaTime * 2, glm::vec3(0, 1, 0));
	glm::mat4 VenusTransform = glm::mat4();
	VenusTransform = m_VenusOffset * m_sphereVenus;
	Gizmos::addSphere(VenusTransform[3].xyz, 8, 8, 2, glm::vec4(0,0,0,1), &m_sphereVenus);

	// Neith
	m_NeithOffset = glm::rotate(VenusTransform, a_deltaTime, glm::vec3(0,1,0));
	m_sphereNeith = glm::rotate(m_sphereNeith, a_deltaTime, glm::vec3(0,1,0));
	glm::mat4 neithTransform = glm::mat4();
	neithTransform = VenusTransform * m_NeithOffset * m_sphereNeith;
	Gizmos::addSphere(neithTransform[3].xyz, 8, 8, 1, glm::vec4(0,0,0,1), &m_sphereNeith);


	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void HelloWorld::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void HelloWorld::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new HelloWorld();
	
	if (app->create("AIE - HelloWorld",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}

void HelloWorld::translate(glm::mat4 &transform, float deltaTime)
{
	GLFWwindow* window = glfwGetCurrentContext();

	glm::vec4 forward		= glm::vec4(0,0,1,0);
	glm::vec4 right			= glm::vec4(1,0,0,0);
	glm::vec4 up			= glm::vec4(0,1,0,0);
	glm::vec4 translation	= transform[3];

	float frameSpeed = deltaTime * 2;

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		translation -= forward * frameSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		translation += forward * frameSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		translation -= right * frameSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		translation += right * frameSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		translation -= up * frameSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		translation += up * frameSpeed;
	}

	transform[3] = translation;
}