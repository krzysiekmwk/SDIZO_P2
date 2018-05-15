#include "Graph.h"

void Graph::setSimetric(bool sim) {
	simetric = sim;
}

int Graph::getVertex() {
	return vertex;
}

int Graph::getEdges() {
	return edges;
}

int Graph::getWeight() {
	return graphWeight;
}

//Sprawdza czy jest polaczenie dla wybranych wierzcholkow
//start - wierzcholek od ktorego sie zaczyna poszukiwanie
//end - do ktorego szukamy drogi
//actual - aktualny wierzcholek (przy wywolaniu = start)
//isFounded= czy zostalo polaczenie znalezione. przy starcie wywolywane z false.
bool Graph::isPath(int startVertex, int endVertex, int actualVertex, bool isFounded) {
	if (isFounded)
		return true;
	std::vector<Edge> list = getConectedVertex(actualVertex);

	for (int i = 0; i < list.size(); i++) {
		if (isFounded)
			return true;
		int v = list.at(i).v2;

		if (v == endVertex) {
			isFounded = true;
			return true;
		}

		if (v != startVertex)
			isFounded = isPath(actualVertex, endVertex, v, isFounded);
	}

	if (isFounded)
		return true;

	return false;
}