#pragma once
#include <vector>
#include <list>

template <typename T>
class ObjectPool
{
protected:
	ObjectPool();
public:
	ObjectPool(unsigned int poolSize);
	~ObjectPool();

	// Use this Request function instead of 'new'
	T* Request();

	// Use this Release function instead of 'delete'
	void Release(T* object);

protected:
	// Array that holds all of the objects
	std::vector<T*> m_pool;

	// Linked list that holds the objects that can be used
	std::list<T*> m_canUse;
};

template <typename T>
ObjectPool<T>::ObjectPool()
{

}

template <typename T>
ObjectPool<T>::ObjectPool(unsigned int a_poolSize)
{
	// Fill the pool with objects and add them all to the list of objects that can be used
	for(unsigned int i = 0; i < a_poolSize; i++)
	{
		m_pool.push_back(new T);
		m_canUse.push_back(m_pool[i]);
	}
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
	// delete all memory that we have
	for(unsigned int i = 0; i < m_pool.size(); i++)
	{
		delete m_pool[i];
	}
	m_pool.clear();
	m_canUse.clear();
}

template <typename T>
T* ObjectPool<T>::Request()
{
	if(m_canUse.size() > 0)
	{
		// Grab the object at the begining of the list
		T* requestedObject = m_canUse.front();
		// Remove it from the list of objects that are available
		m_canUse.pop_front();
		// Return the object
		return requestedObject;
	}
	return nullptr;
}

template <typename T>
void ObjectPool<T>::Release(T* a_object)
{
	// Add the object to the list of available objects for use later
	m_canUse.push_back(a_object);
}