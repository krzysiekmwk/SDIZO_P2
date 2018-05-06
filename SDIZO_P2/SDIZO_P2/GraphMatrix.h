#pragma once
class GraphMatrix {
public:
	GraphMatrix(int vertex, bool simetric);
	~GraphMatrix();
	void insert(int srcVertex, int dstVertex, int weight);
	int search(int srcVertex, int dstVertex);
	void setSimetric(bool sim);
	int getVertex();
	void clear();

private:
	int vertex, edge;       // liczba wierzcholkow i krawedzi
	bool simetric;
	int **matrix; // macierz   
};