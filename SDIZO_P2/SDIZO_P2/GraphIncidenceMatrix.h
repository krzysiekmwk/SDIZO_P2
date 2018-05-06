#pragma once
class GraphIncidenceMatrix
{
public:
	GraphIncidenceMatrix(int vertex, int edges,bool simetric);
	~GraphIncidenceMatrix();
	void insert(int srcVertex, int dstVertex, int weight);
	int searchWeight(int srcVertex, int dstVertex);
	int **getMatrix();
	void setSimetric(bool sim);
	int getVertex();
	int getEdges();
	void clear();

private:
	int vertex, edges;       // liczba wierzcholkow i krawedzi
	int *weights;
	int acttualEdge;
	bool simetric;
	int **matrix; // macierz   

	enum Incidence {
		NONE = 0,
		START = 1,
		END = -1,
	};
};