#include "Node.h"

Node::Node()
{

}

Node::Node(vec2 a_position) : Node()
{
	//m_transform.setTranslation(a_position);
}

Node::~Node()
{

}

void Node::AddEdge(Node & a_endNode)
{
	Node * foundEnd = nullptr;

	for(unsigned int i = 0; i < edges.size(); i++)
	{
		if(&edges[i]->end == &a_endNode && foundEnd == nullptr)
		{
			foundEnd = &edges[i]->end;
		}
	}

	if(!foundEnd)
	{
		edges.push_back(new Edge(*this, a_endNode));
	}
}