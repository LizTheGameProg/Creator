#include "Edge.h"
#include "Node.h"
#include "vec2.h"

Edge::Edge(Node & a_start, Node & a_end) : start(a_start), end(a_end)
{
	//cost = (a_end.m_transform.getTranslation() - a_start.m_transform.getTranslation()).magnitudeSquared();
}

Edge::~Edge()
{

}