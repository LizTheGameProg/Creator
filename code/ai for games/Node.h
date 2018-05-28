#pragma once
#include <vector>
#include "Edge.h"
#include "transform2D.h"
#include "vec2.h"

using namespace LML;

class Node
{
public:
	Node();
	Node(vec2 position);
	~Node();

	void AddEdge(Node & endNode);

	std::vector<Edge *> edges;

	//Transform2D m_transform;
};