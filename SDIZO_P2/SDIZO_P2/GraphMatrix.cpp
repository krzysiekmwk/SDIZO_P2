#include "GraphMatrix.h"

GraphMatrix::GraphMatrix(int vertex, bool simetric){
	this->vertex = vertex;
	this->simetric = simetric;

	matrix = new int * [vertex];
	for (int i = 0; i < vertex; i++){
		matrix[i] = new int[vertex];
		for (int j = 0; j < vertex; j++)
			matrix[i][j] = 0;
	}
}

GraphMatrix::~GraphMatrix(){
	clear();
}

void GraphMatrix::clear(){
	vertex = 0;
	edge = 0;

	for (int i = 0; i < vertex; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

void GraphMatrix::insert(int srcVertex, int dstVertex, int weight) {
	matrix[srcVertex][dstVertex] = weight;
	if(simetric)
		matrix[dstVertex][srcVertex] = weight;
}

int GraphMatrix::search(int srcVertex, int dstVertex) {
	return matrix[srcVertex][dstVertex];
}

void GraphMatrix::setSimetric(bool sim) {
	simetric = sim;
}

int GraphMatrix::getVertex() {
	return vertex;
}
