//#include "BulletPool.h"
#include <vector>
#include <list>
#include "Bullet.h"

class BulletPool
{
	BulletPool();
	~BulletPool();

	Bullet * Request();
	void Release(Bullet * bullet);

	std::vector<Bullet *> m_pool;
	std::vector<bool> m_inUse;
	std::list<Bullet *> m_canUse;
};

BulletPool::BulletPool()
{
	for(int i = 0; i < 1000000; i++)
	{
		m_pool.push_back(new Bullet());
		m_inUse.push_back(false);
		m_canUse.push_back(m_pool[i]);
	}
}

BulletPool::~BulletPool()
{
	for(int i = 0; i < 1000000; i++)
	{
		delete m_pool[i];
	}
	m_pool.clear();
}

Bullet* BulletPool::Request()
{
	Bullet* foo = m_canUse.front();
	m_canUse.pop_front();
	return foo;
	//for(int i = 0; i < 1000; i++)
	//{
	//	if(m_inUse[i] == false)
	//	{
	//		m_inUse[i] = true;
	//		return m_pool[i];
	//	}
	//}
}

void BulletPool::Release(Bullet* a_bullet)
{
	m_canUse.push_back(a_bullet);
	//for(int i = 0; i < 1000; i++)
	//{
	//	if(m_pool[i] == a_bullet)
	//	{
	//		m_inUse[i] = false;
	//		return;
	//	}
	//}
}