#ifndef _HTN_H_
#define _HTN_H_

#include <glm/glm.hpp>
#include <vector>

class Agent
{
public:
	Agent() : m_position(0) {}
	virtual ~Agent() {}
	void				setPosition(const glm::vec3 & a_position) { m_position = a_position; }
	const glm::vec3 &	getPosition() const {return m_position; }

protected:
	glm::vec3 m_position;
};

class Task
{
public:
	Task() : m_complete(false) {}
	virtual ~Task() {}
	bool			isComplete() const { return m_complete; }
	virtual bool	preConditionsMet(Agent * a_agent) { return true; }
	virtual bool	performTask(Agent * a_agent) = 0;

protected:
	bool m_complete;
};

class CompoundTask : public Task
{
public:
	CompoundTask() {}
	virtual ~CompoundTask() { for (auto task : m_task) task; }
	void addTask(Task * a_task) { m_task.push_back(a_task); }

	virtual bool performTask(Agent * a_agent)
	{
		// if task is not complete
		if(m_complete == false)
		{
			if(preConditionsMet(a_agent))
			{
				for(auto task : m_task)
				{
					if(!task->isComplete() && !task->performTask(a_agent))
						return false;
				}

				// all tasks complete!
				m_complete = true;
			}
		}
		
		return m_complete;
	}

protected:
	std::vector<Task *> m_task;
};

#endif