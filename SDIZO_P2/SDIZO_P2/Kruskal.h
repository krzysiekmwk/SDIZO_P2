#pragma once
#include "Graph.h"
#include "GraphList.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Kruskal {
public:
	void makeMST(Graph * graph);
private:
	bool isCycle(GraphList * gr, int startVertex, int endVertex, int actualVertex, bool isFounded);
};
