#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "Grid.h"
#include "Node.h"
#include <queue>
#include "Heuristics.h"

template<typename Template, typename Container = std::deque<Template>>

class iterable_queue : public std::queue<Template, Container>
{
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c, end(); }
	
	const_iterator begin() const { return this->c.begin(); }
	const_iterator end() const { return this->c, end(); }
};

class BreathFirstSearch
{
public:
	void InitializeBreathFirstSearch(Node* startNode);
	vector<Vector2D> Search(Node* n, Vector2D v);
	void SearchPerTick(Node* n, Vector2D v);
	vector<Vector2D> DebugSearch(Scene* s, Node* n, Vector2D v);
	void ExpandFrontier(Node* n);
	void ExpandFrontier(Node* n, int&, int&);
	vector<Vector2D> FillPath(Node* n);
	vector<Vector2D> FillPath(Node* n, int&);
	bool IsVisited(Node* n);

private:
	std::queue<Node*> frontierFIFO;
	iterable_queue<Vector2D> iterableFrontier;
	vector<vector<bool>> visitedNode;
	vector<Vector2D> path;
	bool notFound;
};

