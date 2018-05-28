#include "Fuzzy Logic.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <glm/ext.hpp>
#include <iostream>
#include "FuzzyLogicEngine.h"
Fuzzy fuzzyEngine;  //not much of an engine but it's a start
using namespace std;


const float PI = 22/7.0f;
bool GLFWMouseButton1Down = false;
//List of our sphere actors

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

FuzzyLogicTutorial::FuzzyLogicTutorial()
{
}

FuzzyLogicTutorial::~FuzzyLogicTutorial()
{
}


bool FuzzyLogicTutorial::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create(1000000,1000000);
	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(0,0,100), 
		glm::vec3(0,0,0), glm::vec3(0,1,0)));
	float aspectRatio = DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT;
	// create a an orthogonal projection matrix.
	float fSize = 50;
	float farPlane = 200;
	m_projectionMatrix = glm::ortho<float>(-fSize*aspectRatio,fSize*
		aspectRatio,-fSize,fSize,0,farPlane);
	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	FuzzyLogicExample();
	return true;
}

void FuzzyLogicTutorial::FuzzyLogicExample()
{
	cout<<"Fuzzy Logic Tutorial";
	worldController = new WorldController();
	SimpleAI* simpleAI = new SimpleAI(glm::vec3(0,0,0),glm::vec4(1,1,0,1),4);
	worldController->addObject(simpleAI);
	Water* water1 = new Water(glm::vec3(50,0,0));
	worldController->addObject(water1);
	Cave* cave = new Cave(glm::vec3(-50,0,0));
	worldController->addObject(cave);
	Food* food = new Food(glm::vec3(0,40,0));
	worldController->addObject(food);


	fuzzyEngine.tired = new leftShoulderMembershipFunction(0.2f,0.4f,"tired");
	fuzzyEngine.awake = new TrapezoidFunction(0.2f,0.4f,0.6f,0.8f,"awake");
	fuzzyEngine.superActive = new rightShoulderMembershipFunction(0.6f,0.8f,"SuperActive");


	fuzzyEngine.veryHungry = new leftShoulderMembershipFunction(0.2f,0.4f,"very hungry");
	fuzzyEngine.hungry = new TrapezoidFunction(.2f,.4f,.8f,.9f,"hungry");
	fuzzyEngine.full = new rightShoulderMembershipFunction(.8f,.9f,"full");

	fuzzyEngine.WeekFromThirsty = new leftShoulderMembershipFunction(0.1f,0.3f,"week from thirst");
	fuzzyEngine.veryThirsty = new TriangleFunction(0.1f,0.3f,0.5f,"very thristy");
	fuzzyEngine.thirsty = new TriangleFunction(0.3f,0.5f,0.7f,"thristy");
	fuzzyEngine.notThirsty = new rightShoulderMembershipFunction(.5f,.7f,"not thirsty");

	fuzzyEngine.veryNear = new leftShoulderMembershipFunction(2,4,"very close");
	fuzzyEngine.mediumRange = new TrapezoidFunction(2,4,50,70,"medium range");
	fuzzyEngine.farAway = new rightShoulderMembershipFunction(50,70,"far away");

	fuzzyEngine.undesirable = new leftShoulderMembershipFunction(0.3f,0.5f,"undesirable");
	fuzzyEngine.desirable = new TriangleFunction(0.3f,0.5f,0.7f,"desirable");
	fuzzyEngine.veryDesirable = new rightShoulderMembershipFunction(0.5f,0.7f,"very desirable");
}


void FuzzyLogicTutorial::onUpdate(float a_deltaTime) 
{
	Gizmos::clear();
	static float count = 0;
	worldController->update(a_deltaTime);
	worldController->draw();
	//glm::mat4 planeRotateMatrix = glm::rotate(11/7.0f,1.0f,0.0f,0.0f);
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );
		// update our camera matrix using the keyboard/mouse
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void FuzzyLogicTutorial::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void FuzzyLogicTutorial::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new FuzzyLogicTutorial();
	
	if (app->create("AIE - Physx Tutorial",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}