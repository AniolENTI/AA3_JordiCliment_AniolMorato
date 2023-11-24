#pragma once
#include"Vector2D.h"
#include<vector>

struct Node
{
	Vector2D position;
	float weight;
	std::vector<Node*>connections;
	Node* cameFrom;
};

