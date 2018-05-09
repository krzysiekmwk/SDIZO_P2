#pragma once
#include "GraphList.h"
#include "Edge.h"
#include <vector>

class Dijkstra {
public:
	std::vector<int> findPath(Graph * graph, int startVertex, int endVertex);
};