#include "GraphList.h"

Vertex::Vertex() {
	weight = 0;
	next = nullptr;
}

GraphList::GraphList(){}

GraphList::GraphList(int vertex, int edges, bool simetric) {
	clear();
	setGraph(vertex, edges, simetric);
}

void GraphList::setGraph(int vertex, int edges, bool simetric) {
	this->vertex = vertex;
	this->simetric = simetric;
	this->edges = edges;
	this->graphWeight = 0;

	GLists = new Vertex *[vertex];
	for (int i = 0; i < vertex; i++)
		GLists[i] = nullptr;
}

GraphList::~GraphList() {
	clear();
}

void GraphList::insert(int srcVertex, int dstVertex, int weight) {
	Vertex * element = new Vertex;
	element->weight = weight;
	element->vertex = dstVertex;
	element->next = GLists[srcVertex];	//Tworzenie listy nastepnikow <-prev || next -> next -> null

	GLists[srcVertex] = element;

	if (simetric) {
		Vertex * element = new Vertex;
		element->weight = weight;
		element->vertex = srcVertex;
		element->next = GLists[dstVertex];	//Tworzenie listy nastepnikow <-prev || next -> next -> null

		GLists[dstVertex] = element;
	}

	graphWeight += weight;
}

int GraphList::searchWeight(int srcVertex, int dstVertex) {

	Vertex * element = GLists[srcVertex]; //Wskazanie na pierwszy element listy
	while (element){
		if (element->vertex == dstVertex)	//Przeszukiwanie elementu w liscie w poszukiwaniu odpowiedniego wierzcholka
			return element->weight;	//Pobranie dla niego, jego wagi
		element = element->next;
	}

	return 0;
}

std::vector<Edge> GraphList::getConectedVertex(int vertex) {
	std::vector<Edge> list;

	Vertex * element = GLists[vertex]; //Wskazanie na pierwszy element listy
	while (element) {
		Edge e;
		e.v1 = vertex;
		e.v2 = element->vertex;
		e.weight = element->weight;
		
		list.push_back(e);

		element = element->next;
	}

	return list;
}

void GraphList::clear() {
	for (int i = 0; i < vertex; i++) {
		Vertex * element = GLists[i];
		while (element) {
			Vertex * elementToDelete = element;
			element = element->next;
			delete elementToDelete;
		}
	}

	delete[] GLists;

	vertex = 0;
	edges = 0;
}
