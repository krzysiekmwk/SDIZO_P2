#pragma once
#include "GraphList.h"
#include "Edge.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Dijkstra {
public:
	void findPath(GraphList * gl, int startVertex, int endVertex);
};