#pragma once
#include "GraphList.h"
#include "Edge.h"
#include <vector>

class Dijkstra {
public:
	std::vector<int> findPath(GraphList * gl, int startVertex, int endVertex);
};