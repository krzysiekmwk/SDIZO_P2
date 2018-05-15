#pragma once
#include "Graph.h"

class GraphIncidenceMatrix : public Graph {
public:
	GraphIncidenceMatrix();
	GraphIncidenceMatrix(int vertex, int edges, bool simetric);
	~GraphIncidenceMatrix();
	void insert(int srcVertex, int dstVertex, int weight);
	int searchWeight(int srcVertex, int dstVertex);
	int **getMatrix();
	int *getWeightsArray();
	void clear();
	void setGraph(int vertex, int edges, bool simetric);
	std::vector<Edge> getConectedVertex(int vertex);

private:
	int *weights;
	int acttualEdge;
	int **matrix; // macierz   

	enum Incidence {
		NONE = 0,
		START = 1,
		END = -1,
	};
};