#pragma once
#include "Edge.h"
#include <vector>

class Graph {
public:
	virtual void insert(int srcVertex, int dstVertex, int weight) = 0;
	virtual int searchWeight(int srcVertex, int dstVertex) = 0;
	void setSimetric(bool sim);
	int getVertex();
	int getEdges();
	virtual void clear() = 0;
	virtual void setGraph(int vertex, int edges, bool simetric) = 0;
	virtual std::vector<Edge> getConectedVertex(int vertex) = 0;

protected:
	int vertex, edges;       // liczba wierzcholkow i krawedzi
	bool simetric;			//Czy Graf jest symetryczny (spojny / niespojny)
};