#pragma once
#include "Graph.h"
#include "GraphList.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Kruskal {
public:
	GraphList* makeMST(Graph * graph);
};
