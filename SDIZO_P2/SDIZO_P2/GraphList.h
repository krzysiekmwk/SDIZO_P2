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
	void setSimetric(bool sim);
	int getVertex();
	int getEdges();
	void clear();
	void setGraph(int vertex, int edges, bool simetric);

private:
	int vertex, edges;       // liczba wierzcholkow i krawedzi
	bool simetric; 

	Vertex **GLists;     // tablica wskazników na listy wierzcho³ków  
};