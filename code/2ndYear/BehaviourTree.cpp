#include "BehaviourTree.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Agent.h"

using namespace AIE_2ND_YEAR;

// WithinRange
// RandomiseTarget
// SeekTarget

// if WithinRange then RandomiseTarget else SeekTarget

class WithinRange : public Behaviour
{
public:
	WithinRange(float a_range) : m_range2(a_range * a_range) {}
	virtual ~WithinRange() {}

	virtual bool execute(Agent * a_agent)
	{
		float dist2 = glm::distance2( a_agent->getPosition(), a_agent->getTarget());

		if(dist2 < m_range2)
			return true;
		return false;
	}

	float m_range2;
};

class RandomiseTarget : public Behaviour
{
public:
	RandomiseTarget(float a_radius) : m_radius(a_radius) {}
	virtual ~RandomiseTarget() {}

	virtual bool execute(Agent * a_agent)
	{
		glm::vec2 target(0);

		target = glm::circularRand(m_radius);

		a_agent->setTarget(glm::vec3(target, 0));
		return true;
	}


	float m_radius;
};

class SeekTarget : public Behaviour
{
public:
	SeekTarget(float a_speed) : m_speed(a_speed){}
	virtual ~SeekTarget() {}

	virtual bool execute(Agent * a_agent)
	{
		glm::vec3 pos = a_agent->getPosition();
		glm::vec3 dir = glm::normalize(a_agent->getTarget() - pos);

		a_agent->setPosition( pos + dir * m_speed * Utility::getDeltaTime() );
		return true;
	}

	float m_speed;

};

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

BehaviourTree::BehaviourTree()
{

}

BehaviourTree::~BehaviourTree()
{

}

bool BehaviourTree::onCreate(int a_argc, char* a_argv[]) 
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

	Behaviour * seek = new SeekTarget(120);
	Behaviour * random = new RandomiseTarget(10);
	Behaviour * within = new WithinRange(1.0f);

	Sequence * seq = new Sequence();
	seq->addChild(within);
	seq->addChild(random);

	Selector * root = new Selector();
	root->addChild(seq);
	root->addChild(seek);

	m_behaviour = root;

	m_agent->setBehaviour(m_behaviour);


	return true;
}

void BehaviourTree::onUpdate(float a_deltaTime) 
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

	m_agent->update(a_deltaTime);

	Gizmos::addAABBFilled(m_agent->getPosition(),
		glm::vec3(0.5f), glm::vec4(1,1,0,1));

	Gizmos::addAABBFilled(m_agent->getTarget(),
		glm::vec3(0.5f), glm::vec4(1,0,0,1));

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void BehaviourTree::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void BehaviourTree::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	AIE_2ND_YEAR::Application* app = new BehaviourTree();
	
	if (app->create("AIE - BehaviourTree",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}