#include "Prima.h"

Graph* Prima::makeMST(Graph * graph, bool representation) {
	// Drzewo MST bedzie przechowywane w nowym grafie. Listowo - bo to rzadki graf z mala liczba krawedzi (n-1)
	Graph *mst;
	if (representation)
		mst = new GraphIncidenceMatrix();
	else
		mst = new GraphList();

	mst->setGraph(graph->getVertex(), graph->getVertex() - 1, true);
	bool *visited = new bool[graph->getVertex()];

	for (int i = 0; i < graph->getVertex(); i++) {
		visited[i] = false;
	}

	//poczatek dla wierzcholka 0.
	std::vector<Edge> list;
	//std::vector<Edge> list = graph->getConectedVertex(0);	// Pobranie wszystkich widocznych krawedzi dla danego wierzcholka
	visited[0] = true;

	/*
		Na poczatku wybralismy ze zaczynamy tworzyc drzewo od 0 wierzcholka i dla niego zostala pobrana lista wierzcholkow.
		Nalezy wybrac najkrotszy z nich i je polaczyc jesli nie tworza cyklu
		Zaznaczyc jako odwiedzony ten wierzcholek
		Potem znowu przeszukac wszystkie najmniejsze krawedze, czyli te ktore nie sa jeszcze polaczone
	*/
	int countEdges = 0;
	while (countEdges < graph->getVertex() - 1) {
		for (int i = 0; i < graph->getVertex(); i++) {
			if (visited[i] == true) {
				std::vector<Edge> tmp = graph->getConectedVertex(i);	// Pobranie wszystkich krawedzi dla odwiedzonych wierzcholkow
				list.insert(list.end(), tmp.begin(), tmp.end());
			}
		}

		std::sort(list.begin(), list.end(), less_than_key()); //Posortowanie ich od najmniejszych
		
		for (int i = 0; i < list.size(); i++) {
			//Jesli nie sa jeszcze polaczone, oraz wybrane wierzcholki nie tworzyly by cyklu
			//to nalezy dodac najmniejsza krawedz do grafu, przerwac petle i wrocic spowrotem do przeszukania wszystkich wierzcholkow
			Edge e = list.at(i);
			if (mst->searchWeight(e.v1, e.v2) == 0 && !mst->isPath(e.v1, e.v2, e.v1, false)) {
				visited[e.v1] = true;
				visited[e.v2] = true;
				mst->insert(e.v1, e.v2, e.weight);
				countEdges++;
				break;
			}
		}

		list.clear();
	}

	delete[] visited;

	return mst;
}