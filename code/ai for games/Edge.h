#pragma once

class Node;
class Edge
{
public:
	Edge() = delete;
	Edge(Node & start, Node & end);
	~Edge();

	Node & start;
	Node & end;

	//float cost;
};