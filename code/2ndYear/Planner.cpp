#include "Planner.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

class GoToTask : public Task
{
public:
	GoToTask(const glm::vec3 & a_location, float a_range) : m_location(a_location), m_range2(a_range*a_range) {}
	virtual ~GoToTask() {}

	virtual bool performTask(Agent * a_agent)
	{
		// get difference
		glm::vec3 diff = m_location - a_agent->getPosition();
		
		// check if task complete
		m_complete = glm::length2(diff) <= m_range2;

		diff = glm::normalize(diff) * Utility::getDeltaTime();

		a_agent->setPosition(a_agent->getPosition() + diff);

		return m_complete;
	}

	glm::vec3 m_location;
	float m_range2;
};

class TimeoutTask : public Task
{
public:
	TimeoutTask(float a_duration) : m_duration(a_duration) {}
	virtual ~TimeoutTask() {}

	virtual bool performTask(Agent * a_agent)
	{
		m_duration -= Utility::getDeltaTime();
		m_complete = m_duration <= 0;
		return m_complete;
	}

	float m_duration;

};

Planner::Planner()
{

}

Planner::~Planner()
{

}

bool Planner::onCreate(int a_argc, char* a_argv[]) 
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

	m_agent = new Agent();

	CompoundTask * goBuyEggs = new CompoundTask();

	CompoundTask * goToShops = new CompoundTask();
	Task * getInCar = new GoToTask(glm::vec3(2,0,0), 0.1f);
	Task * driveToShops = new GoToTask(glm::vec3(2,0,10), 0.1f);
	Task * walkIntoShops = new GoToTask(glm::vec3(0,0,10), 0.1f);

	Task * shopping = new TimeoutTask(5);

	CompoundTask * goHome = new CompoundTask();
	Task * getBackInCar = new GoToTask(glm::vec3(2,0,10), 0.1f);
	Task * driveBackHome = new GoToTask(glm::vec3(2,0,0), 0.1f);
	Task * goInside = new GoToTask(glm::vec3(0,0,0), 0.1f);

	goBuyEggs->addTask(goToShops);
		goToShops->addTask(getInCar);
		goToShops->addTask(driveToShops);
		goToShops->addTask(walkIntoShops);	
	
	goBuyEggs->addTask(shopping);
	
	goBuyEggs->addTask(goHome);
		goHome->addTask(getBackInCar);
		goHome->addTask(driveBackHome);
		goHome->addTask(goInside);	
	
	m_task = goBuyEggs;

	return true;
}

void Planner::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	if(!m_task->isComplete())
		m_task->performTask(m_agent);

	Gizmos::addAABBFilled(m_agent->getPosition(),
		glm::vec3(0.2f), glm::vec4(1,2,0,1));

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void Planner::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void Planner::onDestroy()
{
	delete m_agent;
	delete m_task;

	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new Planner();
	
	if (app->create("AIE - Planner",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}