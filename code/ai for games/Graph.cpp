//#include "Graph.h"
//#include <math.h>
//#include "SpriteBatch.h"
//#include "Texture.h"
//#include <iostream>
//
//vector<Node *> Graph::nodes;
//
//Graph::Graph()
//{
//
//}
//
//Graph::~Graph()
//{
//	delete nodeTexture;
//}
//
//void Graph::LoadTexture()
//{
//	nodeTexture = new Texture("./Images/nodeTexture_white.png");
//}
//
//void Graph::AddNode(Node & a_node)
//{
//	vector<Node *>::iterator nodeIter = std::find(nodes.begin(), nodes.end(), &a_node);
//
//	if(nodeIter == nodes.end())
//	{
//		nodes.push_back(&a_node);
//	}
//}
//
//void Graph::ConnectNodes(Node & a_node1, Node & a_node2)
//{
//	a_node1.AddEdge(a_node2);
//}
//
//void Graph::InitAStar(Node & a_start, Node & a_end, Path & a_path)
//{
//	a_path.start = &a_start;
//	a_path.end = &a_end;
//
//	// Empty closed
//	a_path.closed.clear();
//
//	// Empty open
//	a_path.open.clear();
//
//	// Empty cameFrom
//	a_path.cameFrom.clear();
//
//	// Empty totalPath
//	a_path.totalPath.clear();
//
//	a_path.gScore.clear();
//
//	a_path.fScore.clear();
//
//	for(unsigned int i = 0; i < nodes.size(); i++)
//	{
//		// Set all g scores to infinity
//		a_path.gScore.push_back(std::numeric_limits<float>::infinity());
//
//		// Set all f scores to infinity
//		a_path.fScore.push_back(std::numeric_limits<float>::infinity());
//	}
//
//	a_path.cameFrom.resize(nodes.size());
//
//	int startIndex = findIndexofNodeInNodes(a_start);
//
//	// Set startNode g = 0
//	a_path.gScore[startIndex] = 0.f;
//
//	// Set startNode f = g(0) + calculateHeuristic(start, end)
//	a_path.fScore[startIndex] = calculateHeuristic(a_start, a_end);
//
//	a_path.open.push_back(&a_start);
//
//	a_path.current = &a_start;
//}
//
//PATHRESULTS Graph::AStar(Path & a_path)
//{
//#ifdef RUN_ALL_AT_ONCE
//	while(!a_path.open.empty())
//	{
//#else
//	if(!a_path.open.empty())
//	{
//#endif
//		
//		Path * l_path = &a_path;
//		auto sortFunc = [&l_path] (Node * a, Node * b) -> bool
//		{ 
//			int aIndex = Graph::findIndexofNodeInNodes(*a);
//			int bIndex = Graph::findIndexofNodeInNodes(*b);
//
//			return l_path->fScore[aIndex] < l_path->fScore[bIndex]; 
//		};
//		
//		// Sort the open list by the nodes F score
//		a_path.open.sort(sortFunc);
//
//		// current = node in open with lowest f
//		a_path.current = a_path.open.front();
//		/*Node * currentNode = a_path.open.front();*/
//		
//		// if current == end
//		if(a_path.current == a_path.end)
//		{
//			// reconstructPath(cameFrom, end)
//			ReconstructPath(a_path);
//			// return 
//			return PATHRESULTS::PATH_FOUND;
//		}
//
//		// remove current from open
//		a_path.open.pop_front();
//		/*a_path.open.remove(currentNode);*/
//
//		// add current to closed
//		a_path.closed.push_back(a_path.current);
//
//		// foreach edge in current.edges
//		for(unsigned int i = 0; i < a_path.current->edges.size(); i++)
//		{
//			// try and find the edge.end in the closed list
//			auto closedIter = std::find(a_path.closed.begin(), a_path.closed.end(), &a_path.current->edges[i]->end);
//
//			// if edge.end is in closed
//			if(closedIter != a_path.closed.end())
//				// continue
//				continue;
//
//			int currentIndex = findIndexofNodeInNodes(*a_path.current);
//
//			// newG = current g + distBetween(current, edge.end)
//			float newG = a_path.gScore[currentIndex] + distanceBetween(*a_path.current, (a_path.current->edges[i]->end));
//
//			auto openIter = std::find(a_path.open.begin(), a_path.open.end(), &a_path.current->edges[i]->end);
//
//			int endIndex = findIndexofNodeInNodes(a_path.current->edges[i]->end);
//
//			// if edge.end is not in open or
//			if( openIter == a_path.open.end() ||
//			// if newG < edge.end g
//				newG < a_path.gScore[endIndex])
//			{
//				// edge.end parent = current
//				a_path.cameFrom[endIndex] = a_path.current;
//				
//				// edge.end g = newG
//				a_path.gScore[endIndex] = newG;
//
//				// edge.end f = edge.end g + calculateHeuristic(edge.end, end)
//				a_path.fScore[endIndex] = newG + calculateHeuristic(a_path.current->edges[i]->end, *a_path.end);
//
//				// if edge.end is not in open
//				if(openIter == a_path.open.end())
//				{
//					// add edge.end to open
//					a_path.open.push_back(&a_path.current->edges[i]->end);
//				}
//			}
//		}
//#ifndef RUN_ALL_AT_ONCE
//		ReconstructPath(a_path);
//		return PATHRESULTS::STILL_CALCULATING;
//#endif//RUN_ALL_AT_ONCE
//	}
//	return PATHRESULTS::NO_PATH_FOUND;
//}
//
//void Graph::ReconstructPath(Path & a_path)
//{
//	Node * current = a_path.current;
//
//	a_path.totalPath.clear();
//	a_path.totalPath.push_back(current);
//	
//	while(current)
//	{
//		int currentIndex = findIndexofNodeInNodes(*current);
//
//		if(currentIndex == -1)
//		{
//			break;
//			current = nullptr;
//			continue;
//		}
//
//		
//		current = a_path.cameFrom[currentIndex];
//		
//		
//		a_path.totalPath.push_back(current);
//	}
//}
//
//float Graph::calculateHeuristic(Node & a_node1, Node & a_node2)
//{
//	// Get the difference in X
//	//float dx = abs(a_node1.m_transform.getTransform()[2].x - a_node2.m_transform.getTransform()[2].x);
//	// Get the difference in Y
//	//float dy = abs(a_node1.m_transform.getTransform()[2].y - a_node2.m_transform.getTransform()[2].y);
//
//	// Return difference in X + difference in Y
//	//return dx + dy;
//	return 0.0f;
//}
//
//int Graph::findIndexofNodeInNodes(Node & a_node)
//{
//	// Iterate through the nodes array to find the index of the node that was passed in
//	for(unsigned int i = 0; i < nodes.size(); i++)
//	{
//		if(nodes[i] == &a_node)
//			return i;
//	}
//	return -1;
//}
//
//float Graph::distanceBetween(Node & a_node1, Node & a_node2)
//{
//	//return (a_node1.m_transform.getTransform()[2].xy() - a_node2.m_transform.getTransform()[2].xy()).magnitude();
//	return 0.0f;
//}
//
//void Graph::DrawNodes(SpriteBatch & a_spriteBatch)
//{
//	a_spriteBatch.SetRenderColor(255, 255, 255, 64);
//
//	for(auto iter = nodes.begin(); iter != nodes.end(); ++iter)
//	{
//		for(auto jiter = (*iter)->edges.begin(); jiter != (*iter)->edges.end(); ++jiter)
//		{
//			Matrix3 mat3_1 = (*iter)->m_transform.getTransform();
//			Matrix3 mat3_2 = (*jiter)->end.m_transform.getTransform();
//			
//			a_spriteBatch.DrawLine(mat3_1[2][0], mat3_1[2][1], mat3_2[2][0], mat3_2[2][1]);
//		}
//	}
//	
//	a_spriteBatch.SetRenderColor(0, 0, 0, 255);
//
//	for(auto iter = nodes.begin(); iter != nodes.end(); ++iter)
//	{
//		
//		a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &(*iter)->m_transform.getTransform()[0][0]);
//	}
//}
//
//void Graph::DrawPath(SpriteBatch & a_spriteBatch, Path & a_path)
//{
//	a_spriteBatch.SetRenderColor(0, 255, 255, 255);
//	for(auto iter = a_path.cameFrom.begin(); iter != a_path.cameFrom.end(); ++iter)
//	{
//		if(*iter != nullptr)
//			a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &(*iter)->m_transform.getTransform()[0][0]);
//	}
//
//	a_spriteBatch.SetRenderColor(0, 0, 255, 255);
//	for(auto iter = a_path.totalPath.begin(); iter != a_path.totalPath.end(); ++iter)
//	{
//		if(*iter != nullptr)
//			a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &(*iter)->m_transform.getTransform()[0][0]);
//	}
//
//	a_spriteBatch.SetRenderColor(0, 255, 0, 255);
//	for(auto iter = a_path.open.begin(); iter != a_path.open.end(); ++iter)
//	{
//		if(*iter != nullptr)
//			a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &(*iter)->m_transform.getTransform()[0][0]);
//	}
//
//	a_spriteBatch.SetRenderColor(255, 0, 0, 255);
//
//	a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &a_path.end->m_transform.getTransform()[0][0]);
//
//	a_spriteBatch.SetRenderColor(0, 128, 128, 255);
//
//	a_spriteBatch.DrawSpriteTransformed3x3(nodeTexture, &a_path.start->m_transform.getTransform()[0][0]);
//
//	// Set the render colour back to normal
//	a_spriteBatch.SetRenderColor(255, 255, 255, 255);
//}