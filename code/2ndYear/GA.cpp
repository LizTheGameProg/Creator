#include "GA.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <algorithm>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

using namespace AIE_2ND_YEAR;

GA::GA()
{

}

GA::~GA()
{

}

bool GA::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(0,30,30),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//////////////////////////////////////////////////////////////////////////
	// set up maze
	m_width = 32;
	m_height = 32;
	m_wallRate = 0.25f;

	m_maze = new bool[ m_width * m_height ];
	memset(m_maze, 0, sizeof(bool) * m_width * m_height);

	srand(42);
	for ( int x = 0 ; x < m_width ; ++x )
	{
		for ( int y = 0 ; y < m_height ; ++y )
		{
			if (unitRand() < m_wallRate)
				m_maze[ x * m_height + y ] = true;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// setup population
	m_generation = 0;
	m_pathFound = false;
	m_crossoverRate = 0.7f;
	m_mutationRate = 0.1f;

	for( int i = 0; i < 1000; i++)
	{
		Agent agent;

		agent.score = m_width + m_height;

		for( int j = 0; j < CHROMOSOME_COUNT; j++)
		{
			int upperBits = rand();
			agent.genome[j] = (upperBits<<16) + rand();
		}

		m_population.push_back(agent);
	}

	return true;
}

void GA::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();

	// draw maze
	float startX = -(m_width * 0.5f);
	float startY = -(m_height * 0.5f);

	glm::vec4 black(0,0,0,1);
	glm::vec4 white(1);

	for ( int x = 0 ; x < m_width ; ++x )
	{
		for ( int y = 0 ; y < m_height ; ++y )
		{
			glm::vec3 v0(startX + x, 0, startY + y);
			glm::vec3 v1(startX + x + 1, 0, startY + y + 1);
			glm::vec3 v2(startX + x + 1, 0, startY + y);
			glm::vec3 v3(startX + x, 0, startY + y + 1);

			Gizmos::addTri(v0,v1,v2, m_maze[x * m_height + y] == true ? black : white);
			Gizmos::addTri(v0,v3,v1, m_maze[x * m_height + y] == true ? black : white);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// YOUR AI HERE
	//////////////////////////////////////////////////////////////////////////
	if(!m_pathFound)
		evaluateFitness();

	std::sort(m_population.begin(), m_population.end());
	m_pathFound = m_pathFound || m_population.front().score == 0;

	drawPath(m_population.front());

	if(!m_pathFound)
	{
		evolve();
		printf("Generation: %i\n", m_generation);
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void GA::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void GA::onDestroy()
{
	delete m_maze;

	// clean up anything we created
	Gizmos::destroy();
}

//// main that controls the creation/destruction of an application
//int main(int argc, char* argv[])
//{
//	// explicitly control the creation of our application
//	AIE_2ND_YEAR::Application* app = new GA();
//	
//	if (app->create("AIE - GA",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
//		app->run();
//		
//	// explicitly control the destruction of our application
//	delete app;
//
//	return 0;
//}

void GA::evaluateFitness()
{
	int size = (int)m_population.size();

	// loop population
	for (int i = 0 ; i < size ; ++i)
	{
		int currX = 0, currY = 0;

		// loop agents bits
		for (int bits = 0 ; bits < BIT_COUNT ; bits += 2 )
		{
			// get exact bit
			int chromosome = bits / 32;
			int bit = bits % 32;

			if ((m_population[i].genome[chromosome] & (1<<bit)) == 0)
			{
				if ((m_population[i].genome[chromosome] & (1<<(bit+1))) == 0)
				{
					// [0,0] = up
					if (currY > 0 && m_maze[currX * m_height + currY - 1] == false)
						--currY;
				}
				else
				{
					// [0,1] = down
					if (currY < (m_height-1) && m_maze[currX * m_height + currY + 1] == false)
						++currY;
				}
			}
			else
			{
				if ((m_population[i].genome[chromosome] & (1<<(bit+1))) == 0)
				{
					// [1,0] = left
					if (currX > 0 && m_maze[(currX-1) * m_height + currY] == false)
						--currX;

				}
				else
				{
					// [1,1] = right
					if (currX < (m_width-1) && m_maze[(currX+1) * m_height + currY] == false)
						++currX;
				}
			}

			// exit if we reached the goal
			if (currX == (m_width-1) && currY == (m_height-1))
				break;
		}

		// score
		m_population[i].score = abs((m_width-1) - currX) + abs((m_height-1) - currY);
	}
}

void GA::drawPath(const Agent& a_agent)
{
	float startX = -(m_width * 0.5f);
	float startY = -(m_height * 0.5f);
	glm::vec4 yellow(1,1,0,1);

	glm::vec3 v0(startX, 0.1f, startY);
	glm::vec3 v1(startX + 1, 0.1f, startY + 1);
	glm::vec3 v2(startX + 1, 0.1f, startY);
	glm::vec3 v3(startX, 0.1f, startY + 1);

	// draw starting square
	Gizmos::addTri(v0,v1,v2, yellow);
	Gizmos::addTri(v0,v3,v1, yellow);

	int currX = 0, currY = 0;

	// loop agent's bits
	for (int bits = 0 ; bits < BIT_COUNT ; bits += 2 )
	{
		// get exact bit
		int chromosome = bits / 32;
		int bit = bits % 32;

		if ((a_agent.genome[chromosome] & (1<<bit)) == 0)
		{
			if ((a_agent.genome[chromosome] & (1<<(bit+1))) == 0)
			{
				// [0,0] = up
				if (currY > 0 && m_maze[currX * m_height + currY - 1] == false)
					--currY;
			}
			else
			{
				// [0,1] = down
				if (currY < (m_height-1) && m_maze[currX * m_height + currY + 1] == false)
					++currY;
			}
		}
		else
		{
			if ((a_agent.genome[chromosome] & (1<<(bit+1))) == 0)
			{
				// [1,0] = left
				if (currX > 0 && m_maze[(currX-1) * m_height + currY] == false)
					--currX;

			}
			else
			{
				// [1,1] = right
				if (currX < (m_width-1) && m_maze[(currX+1) * m_height + currY] == false)
					++currX;
			}
		}

		v0 = glm::vec3(startX + currX, 0.1f, startY + currY);
		v1 = glm::vec3(startX + currX + 1, 0.1f, startY + currY + 1);
		v2 = glm::vec3(startX + currX + 1, 0.1f, startY + currY);
		v3 = glm::vec3(startX + currX, 0.1f, startY + currY + 1);

		Gizmos::addTri(v0,v1,v2, yellow);
		Gizmos::addTri(v0,v3,v1, yellow);

		// exit if we reached the goal
		if (currX == (m_width-1) &&
			currY == (m_height-1))
			return;
	}
}

void GA::evolve()
{
	int populationSize = (int) m_population.size();
	int target = m_width * m_height;

	int totalFitness = 0;
	for(int i = 0; i < populationSize; i++)
	{
		totalFitness += target - m_population[i].score;
	}

	std::vector<Agent> newPopulation;

	while(newPopulation.size() < populationSize)
	{
		// selection
		int roulette = rand() % totalFitness;

		Agent agent1, agent2;

		int accumulatedScore = 0;
		for(int i = 0; i < populationSize; i++)
		{
			accumulatedScore += target - m_population[i].score;
			if(accumulatedScore > roulette)
			{
				agent1 = m_population[i];
				break;
			}
		}
		
		roulette = rand() % totalFitness;

		accumulatedScore = 0;
		for(int i = 0; i < populationSize; i++)
		{
			accumulatedScore += target - m_population[i].score;
			if(accumulatedScore > roulette)
			{
				agent2 = m_population[i];
				break;
			}
		}

		// crossover
		crossover(agent1, agent2);

		// mutation
		mutate(agent1);
		mutate(agent2);

		newPopulation.push_back(agent1);
		newPopulation.push_back(agent2);
	}

	m_population = newPopulation;

	m_generation++;
}

void GA::crossover(Agent & a_agent1, Agent & a_agent2)
{
	if(unitRand() < m_crossoverRate)
	{
		int startBit = (rand() % (BIT_COUNT/2)) * 2;

		for(; startBit < BIT_COUNT; startBit++)
		{
			// which chromo?
			int chromosone = startBit / 32;

			// which bit?
			int bit = startBit % 32;

			int temp1 = a_agent1.genome[chromosone] & (1<<bit);
			int temp2 = a_agent2.genome[chromosone] & (1<<bit);

			if(temp1 == 0)
				a_agent2.genome[chromosone] &= ~(1<<bit);
			else
				a_agent2.genome[chromosone] |= (1<<bit);

			if(temp2 == 0)
				a_agent1.genome[chromosone] &= ~(1<<bit);
			else
				a_agent1.genome[chromosone] |= (1<<bit);
		}
	}
}

void GA::mutate(Agent & a_agent)
{
	for(int startBit = 0; startBit < BIT_COUNT; startBit++)
	{
		// which chromo?
		int chromosone = startBit / 32;

		// which bit?
		int bit = startBit % 32;

		if(unitRand() < m_mutationRate)
		{
			a_agent.genome[chromosone] ^= (1<<bit);
		}
	}
}