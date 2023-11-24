#include "BreathFirstSearch.h"
#include <iostream>

#define  GRID_LENGTH 40
#define  GRID_WIDTH 24

using namespace std;

void BreathFirstSearch::InitializeBreathFirstSearch(Node* startNode) {
	//buidem frontera
	while (!frontierFIFO.empty()) frontierFIFO.pop();
	while (!iterableFrontier.empty()) iterableFrontier.pop();
	//creem el nou vector de Nodes visitats
	visitedNode.clear();
	for (int i = 0; i < GRID_LENGTH; i++) {
		std::vector<bool> tmp(GRID_WIDTH, false);
		visitedNode.push_back(tmp);
	}

	//buidem el path
	path.clear();

	//encara no sha trobat el cami
	notFound = true;

	//preparem el primer Node per la frontea
	frontierFIFO.push(startNode);
	iterableFrontier.push(startNode->position);
	Vector2D aux = Heuristics::pix2cell(startNode->position);
	visitedNode[aux.x][aux.y] = true; //afegir a visited
	startNode->previousNode = nullptr;
}

vector<Vector2D> BreathFirstSearch::Search(Node* startNode, Vector2D endPos) {

	InitializeBreathFirstSearch(startNode);
	//cout << "BFSinit success" << endl;
	while (!frontierFIFO.empty() && notFound) {
		if (Heuristics::pix2cell(frontierFIFO.front()->position) == endPos) {
			//cout << "La frontera ha trobat la endPosition" << endl;
			return FillPath(frontierFIFO.front());
			notFound = false;
			//cout << "per aqui no hauria de passar mai" << endl;
		}
		else {
			ExpandFrontier(frontierFIFO.front());

			//Vector2D aux = Heuristics::pix2cell(frontier.front()->position);
			//visitedNode[aux.x][aux.y] = true; //afegir a visited

			frontierFIFO.pop(); //treure el node de la frontera
			//cout << "encara no ha trobat la posicio final: " << aux.x << " " << aux.y << endl;
		}
	}
	//cout << "per aqui tampoc" << endl;
	return path;

}

void BreathFirstSearch::SearchPerTick(Node* startNode, Vector2D endPos) {
	if (frontierFIFO.empty() || !notFound) {
		InitializeBreathFirstSearch(startNode);
	}
	if (Heuristics::pix2cell(frontierFIFO.front()->position) == Heuristics::pix2cell(endPos)) {
		//cout << "La frontera ha trobat la endPosition" << endl;
		FillPath(frontierFIFO.front());
		notFound = false;
		//cout << "per aqui no hauria de passar mai" << endl;
	}
	else {
		ExpandFrontier(frontierFIFO.front());

		//Vector2D aux = Heuristics::pix2cell(frontier.front()->position);
		//visitedNode[aux.x][aux.y] = true; //afegir a visited

		frontierFIFO.pop(); //treure el node de la frontera
		iterableFrontier.pop();			//cout << "encara no ha trobat la posicio final: " << aux.x << " " << aux.y << endl;
	}

}

vector<Vector2D> BreathFirstSearch::DebugSearch(SceneDebugPF* scene, Node* startNode, Vector2D endPos) {
	scene->numNodesAddedToF = 0;
	scene->numNodesEvaluated = 0;
	scene->numNodesVisited = 0;
	scene->numPathNodes = 0;
	clock_t t = clock();

	InitializeBreathFirstSearch(startNode);

	while (!frontierFIFO.empty() && notFound) {
		scene->numNodesEvaluated++;
		if (Heuristics::pix2cell(frontierFIFO.front()->position) == endPos) {
			return FillPath(frontierFIFO.front(), scene->numPathNodes);
			notFound = false;
		}
		else {
			ExpandFrontier(frontierFIFO.front(), scene->numNodesVisited, scene->numNodesAddedToF);

			frontierFIFO.pop(); //treure el node de la frontera
		}
	}

	t = clock() - t;

	scene->timeOfSearch = t / CLOCKS_PER_SEC;
	return path;

}

void BreathFirstSearch::ExpandFrontier(Node* n) {
	//afegir els veins de n a la frontera
	for (int i = 0; i < n->connections.size(); i++) {
		if (!IsVisited(n->connections[i])) {
			n->connections[i]->previousNode = n;
			frontierFIFO.push(n->connections[i]);
			iterableFrontier.push(n->connections[i]->position);
			Vector2D aux = Heuristics::pix2cell(n->connections[i]->position);
			visitedNode[aux.x][aux.y] = true; //afegir a visited
		}
	}
};

void BreathFirstSearch::ExpandFrontier(Node* n, int& numNodesVisited, int& numNodesAdded) {
	//afegir els veins de n a la frontera
	for (int i = 0; i < n->connections.size(); i++) {
		numNodesVisited++;
		if (!IsVisited(n->connections[i])) {
			numNodesAdded++;
			n->connections[i]->previousNode = n;
			frontierFIFO.push(n->connections[i]);
			iterableFrontier.push(n->connections[i]->position);
			Vector2D aux = Heuristics::pix2cell(n->connections[i]->position);
			visitedNode[aux.x][aux.y] = true; //afegir a visited
		}
	}
};

bool BreathFirstSearch::IsVisited(Node* n) {
	Vector2D gridPos = Heuristics::pix2cell(n->position);
	return visitedNode[gridPos.x][gridPos.y];
}

vector<Vector2D> BreathFirstSearch::FillPath(Node* end) {
	//omplir path amb les posicions dels nodes del cami fent previousNode
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
	//omplir path amb les posicions dels nodes del cami fent previousNode
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
