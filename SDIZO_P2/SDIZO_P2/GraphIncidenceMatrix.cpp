#include "GraphIncidenceMatrix.h"

GraphIncidenceMatrix::GraphIncidenceMatrix() {}

GraphIncidenceMatrix::GraphIncidenceMatrix(int vertex, int edges, bool simetric) {
	setGraph(vertex, edges, simetric);
}

void GraphIncidenceMatrix::setGraph(int vertex, int edges, bool simetric) {
	this->vertex = vertex;
	this->edges = edges;
	this->simetric = simetric;

	//Tworzenie macierzy incydencji. Najpierw tablica wierzcholkow, a potem tablica krawedzi
	matrix = new int *[vertex];
	for (int i = 0; i < vertex; i++) {
		matrix[i] = new int[edges];
		for (int j = 0; j < edges; j++)
			matrix[i][j] = NONE;
	}

	acttualEdge = 0;
	weights = new int[edges];
}

GraphIncidenceMatrix::~GraphIncidenceMatrix() {
	clear();
}

void GraphIncidenceMatrix::insert(int srcVertex, int dstVertex, int weight) {
	matrix[srcVertex][acttualEdge] = START;	//Skad
	matrix[dstVertex][acttualEdge] = END;		//Dokad

	if(simetric)
		matrix[dstVertex][acttualEdge] = START;	//Dla nieskierowanego grafu

	weights[acttualEdge] = weight;		//Waga dla danej krawedzi
	acttualEdge++;
}

int GraphIncidenceMatrix::searchWeight(int srcVertex, int dstVertex) {
	for (int i = 0; i < edges; i++) {
		if (!simetric) {
			if (matrix[srcVertex][i] == START && matrix[dstVertex][i] == END && srcVertex != dstVertex) {
				return weights[i];
			}
		}
		else {
			if (matrix[srcVertex][i] == START && matrix[dstVertex][i] == START && srcVertex != dstVertex) {
				return weights[i];
			}
		}
	}

	return 0;
}

int ** GraphIncidenceMatrix::getMatrix() {
	return matrix;
}

void GraphIncidenceMatrix::clear() {
	for (int i = 0; i < vertex; ++i)
		delete[] matrix[i];
	delete[] matrix;

	delete[] weights;

	vertex = 0;
	edges = 0;
}