#include "BreathFirstSearch.h"
#include <iostream>

#define  GRID_LENGTH 40
#define  GRID_WIDTH 24

using namespace std;

void BreathFirstSearch::InitializeBreathFirstSearch(Node* startNode) {
	while (!frontierFIFO.empty()) frontierFIFO.pop();
	while (!iterableFrontier.empty()) iterableFrontier.pop();
	visitedNode.clear();
	for (int i = 0; i < GRID_LENGTH; i++) {
		std::vector<bool> tmp(GRID_WIDTH, false);
		visitedNode.push_back(tmp);
	}

	path.clear();

	notFound = true;

	frontierFIFO.push(startNode);
	iterableFrontier.push(startNode->position);
	Vector2D aux = Heuristics::pix2cell(startNode->position);
	visitedNode[aux.x][aux.y] = true;
	startNode->previousNode = nullptr;
}

vector<Vector2D> BreathFirstSearch::Search(Node* startNode, Vector2D endPos) {

	InitializeBreathFirstSearch(startNode);
	while (!frontierFIFO.empty() && notFound) {
		if (Heuristics::pix2cell(frontierFIFO.front()->position) == endPos) {
			return FillPath(frontierFIFO.front());
			notFound = false;
		}
		else {
			ExpandFrontier(frontierFIFO.front());
			frontierFIFO.pop();
		}
	}
	return path;

}

void BreathFirstSearch::SearchPerTick(Node* startNode, Vector2D endPos) {
	if (frontierFIFO.empty() || !notFound) {
		InitializeBreathFirstSearch(startNode);
	}
	if (Heuristics::pix2cell(frontierFIFO.front()->position) == Heuristics::pix2cell(endPos)) {
		FillPath(frontierFIFO.front());
		notFound = false;
	}
	else {
		ExpandFrontier(frontierFIFO.front());

		frontierFIFO.pop();
		iterableFrontier.pop();
	}

}

void BreathFirstSearch::ExpandFrontier(Node* n) {
	for (int i = 0; i < n->connections.size(); i++) {
		if (!IsVisited(n->connections[i])) {
			n->connections[i]->previousNode = n;
			frontierFIFO.push(n->connections[i]);
			iterableFrontier.push(n->connections[i]->position);
			Vector2D aux = Heuristics::pix2cell(n->connections[i]->position);
			visitedNode[aux.x][aux.y] = true;
		}
	}
};

void BreathFirstSearch::ExpandFrontier(Node* n, int& numNodesVisited, int& numNodesAdded) {
	for (int i = 0; i < n->connections.size(); i++) {
		numNodesVisited++;
		if (!IsVisited(n->connections[i])) {
			numNodesAdded++;
			n->connections[i]->previousNode = n;
			frontierFIFO.push(n->connections[i]);
			iterableFrontier.push(n->connections[i]->position);
			Vector2D aux = Heuristics::pix2cell(n->connections[i]->position);
			visitedNode[aux.x][aux.y] = true;
		}
	}
};

bool BreathFirstSearch::IsVisited(Node* n) {
	Vector2D gridPos = Heuristics::pix2cell(n->position);
	return visitedNode[gridPos.x][gridPos.y];
}

vector<Vector2D> BreathFirstSearch::FillPath(Node* end) {
	Node* tempNode = end;
	while (tempNode != nullptr) {
		path.push_back(tempNode->position);
		tempNode = tempNode->previousNode;
	}

	Vector2D tempVec;
	for (int i = 0; i < path.size() / 2; i++) {
		tempVec = path[i];
		path[i] = path[path.size() - 1 - i];
		path[path.size() - 1 - i] = tempVec;
	}
	return path;
};

vector<Vector2D> BreathFirstSearch::FillPath(Node* end, int& numNodes) {
	Node* tempNode = end;
	while (tempNode != nullptr) {
		path.push_back(tempNode->position);
		tempNode = tempNode->previousNode;
		numNodes++;
	}

	Vector2D tempVec;
	for (int i = 0; i < path.size() / 2; i++) {
		tempVec = path[i];
		path[i] = path[path.size() - 1 - i];
		path[path.size() - 1 - i] = tempVec;
	}
	return path;
};
