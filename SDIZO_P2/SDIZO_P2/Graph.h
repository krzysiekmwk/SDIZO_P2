#pragma once
class Graph {

public:
	virtual void insert(int srcVertex, int dstVertex, int weight) = 0;
	virtual int searchWeight(int srcVertex, int dstVertex) = 0;
	virtual void setSimetric(bool sim) = 0;
	virtual int getVertex() = 0;
	virtual int getEdges() = 0;
	virtual void clear() = 0;

protected:
	int vertex, edges;       // liczba wierzcholkow i krawedzi
	bool simetric;			//Czy Graf jest symetryczny (spojny / niespojny)



};