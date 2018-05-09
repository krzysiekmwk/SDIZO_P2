#pragma once
#include "Graph.h"

class Vertex {
public:
	Vertex();
	Vertex * next;
	int vertex;
	int weight;
};

class GraphList : public Graph{
public:
	GraphList();
	GraphList(int vertex, int edges, bool simetric);
	~GraphList();
	void insert(int srcVertex, int dstVertex, int weight);
	int searchWeight(int srcVertex, int dstVertex);
	void clear();
	void setGraph(int vertex, int edges, bool simetric);
	std::vector<Edge> getConectedVertex(int vertex);

private:
	Vertex **GLists;     // tablica wskazników na listy wierzcho³ków  
};