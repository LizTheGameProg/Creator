#pragma once
#include "Node.h"
#include <vector>
#include <list>

using std::vector;
using std::list;

class SpriteBatch;
class Texture;

//#define RUN_ALL_AT_ONCE

#ifdef AILIBRARY_EXPORTS
#define AILIB __declspec(dllexport)
#else
#define AILIB __declspec(dllimport)
#endif

enum class PATHRESULTS : int
{
	NO_PATH_FOUND,
	PATH_FOUND,
	STILL_CALCULATING
};

struct Path
{
	list<Node *>	closed;		// Evaluated Nodes
	list<Node *>	open;		// To be evaluated
	vector<Node *>	cameFrom;	// Map of navigated nodes
	vector<Node *>	totalPath;
	vector<float>	gScore;
	vector<float>	fScore;
	Node * start;
	Node * end;
	Node * current;
};

class Graph
{
public:
	AILIB Graph();
	AILIB ~Graph();

	AILIB void LoadTexture();

	AILIB void AddNode(Node & node);
	AILIB void ConnectNodes(Node & node1, Node & node2);

	AILIB void InitAStar(Node & a_start, Node & a_end, Path & a_path);
	AILIB PATHRESULTS AStar(Path & a_path);
	AILIB void ReconstructPath(Path & path);

	AILIB float calculateHeuristic(Node & node1, Node & node2);

	AILIB static int findIndexofNodeInNodes(Node & node);
	AILIB static float distanceBetween(Node & node1, Node & node2);

	AILIB void DrawNodes(SpriteBatch & spriteBatch);
	AILIB void DrawPath(SpriteBatch & spriteBatch, Path & path);

	AILIB static vector<Node *> nodes;

	Texture * nodeTexture;
};