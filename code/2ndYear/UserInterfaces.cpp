#include "UserInterfaces.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <SOIL.h>

#include "UIButton.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

UserInterfaces::UserInterfaces()
{

}

UserInterfaces::~UserInterfaces()
{

}

void buttonPress(UIButton * a_caller, void * a_userData)
{
	UIRectangle * parent = (UIRectangle*)a_userData;
	parent->setPosition(vec2(glm::linearRand<float>(200, DEFAULT_SCREENWIDTH - 200), DEFAULT_SCREENHEIGHT * 0.5f));
}

bool UserInterfaces::onCreate(int a_argc, char* a_argv[]) 
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

	m_guiProjectionMatrix = glm::ortho<float>(0, DEFAULT_SCREENWIDTH, 0, DEFAULT_SCREENHEIGHT);

	unsigned int vs = Utility::loadShader("../../Build/shaders/ui.vert", GL_VERTEX_SHADER);
	unsigned int fs = Utility::loadShader("../../Build/shaders/ui.frag", GL_FRAGMENT_SHADER);
	m_guiShader = Utility::createProgram(vs, 0, 0, 0, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	m_texture = SOIL_load_OGL_texture(	"../../Build/textures/crate.png", 
										SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	
	m_button = new UIRectangle(m_guiShader, vec2(300, 500));
	m_button->setPosition( vec2( DEFAULT_SCREENWIDTH * 0.5f, DEFAULT_SCREENHEIGHT * 0.5f ) );
	m_button->setTexture(m_texture);

	UIButton * button = new UIButton(m_guiShader, vec2(100, 50), glm::vec4(1), glm::vec4(0,0,1,1), glm::vec4(1,0,0,1));
	button->setPosition( vec2( 0, 100 ) );
	button->setTexture(m_texture);
	button->setPressedCB(buttonPress, m_button);
	m_button->addElement(button);
	
	button = new UIButton(m_guiShader, vec2(100, 50), glm::vec4(1), glm::vec4(0,0,1,1), glm::vec4(1,0,0,1));
	button->setTexture(m_texture);
	button->setPressedCB(buttonPress, m_button);
	m_button->addElement(button);

	button = new UIButton(m_guiShader, vec2(100, 50), glm::vec4(1), glm::vec4(0,0,1,1), glm::vec4(1,0,0,1));
	button->setPosition( vec2(  0, -100) );
	button->setTexture(m_texture);
	button->setPressedCB(buttonPress, m_button);
	m_button->addElement(button);

	return true;
}

void UserInterfaces::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the Z-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	//vec2 pos = glm::mix(vec2(DEFAULT_SCREENWIDTH * 0.25f, DEFAULT_SCREENHEIGHT * 0.5f),
	//					vec2(DEFAULT_SCREENWIDTH * 0.75f, DEFAULT_SCREENHEIGHT * 0.5f),
	//					sin(Utility::getTotalTime()) * 0.5f + 0.5f);
	//
	//m_button->setPosition( pos );
	//m_button->setRotation( Utility::getTotalTime() );
	m_button->update(a_deltaTime);

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void UserInterfaces::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);

	//////////////////////////////////////
	// DRAW GUI
	//////////////////////////////////////
	int depthFunc = GL_LESS;
	glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);
	glDepthFunc(GL_LEQUAL);
	m_button->draw(m_guiProjectionMatrix);
	glDepthFunc(depthFunc);
}

void UserInterfaces::onDestroy()
{
	delete m_button;
	m_button = nullptr;

	glDeleteProgram(m_guiShader);

	// clean up anything we created
	Gizmos::destroy();
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new UserInterfaces();
//	
//	if (app->create("AIE - UserInterfaces",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}