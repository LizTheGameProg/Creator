#ifndef __GA_H_
#define __GA_H_

#include "Application.h"
#include <glm/glm.hpp>
#include <vector>

const int CHROMOSOME_COUNT = 8;
const int BIT_COUNT = CHROMOSOME_COUNT * 32;

// a GA agent
struct Agent
{
	int		score;
	int		genome[CHROMOSOME_COUNT];	// 2bits = 1 move

	bool operator < (const Agent& a_rhs) const
	{
		return score < a_rhs.score;
	}
};

// Derived application class that wraps up all globals neatly
class GA : public AIE_2ND_YEAR::Application
{
public:

	GA();
	virtual ~GA();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	// simple 0.0 to 1.0 over 100%
	float			unitRand()	{ return (rand() % 100) / 99.0f; }

	int				m_width, m_height;
	bool*			m_maze;
	float			m_wallRate;

	void			evaluateFitness();
	void			drawPath(const Agent& a_agent);

	void			evolve();

	void			crossover(Agent & a_agent1, Agent & a_agent2);
	void			mutate(Agent & a_agent);

	float			m_crossoverRate;
	float			m_mutationRate;

	bool			m_pathFound;
	unsigned int	m_generation;
	std::vector<Agent>	m_population;

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __GA_H_