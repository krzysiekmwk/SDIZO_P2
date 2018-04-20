#include "GraphList.h"

GraphList::GraphList(int vertex, bool simetric) {
	this->vertex = vertex;
	this->simetric = simetric;

	GLists = new Vertex * [vertex];
	for (int i = 0; i < vertex; i++)
		GLists[i] = nullptr;
}

GraphList::~GraphList() {
	clear();
}

void GraphList::insert(int srcVertex, int dstVertex, int weight) {

}

int GraphList::search(int srcVertex, int dstVertex) {

}

void GraphList::setSimetric(bool sim) {
	simetric = sim;
}

int GraphList::getVertex() {
	return vertex;
}

void GraphList::clear() {

}