#pragma once
#include "GraphList.h"
#include "Edge.h"
#include <vector>

class FordBellman {
public:
	std::vector<int> findPath(Graph * graph, int startVertex, int endVertex);
};