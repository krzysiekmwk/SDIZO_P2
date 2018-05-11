#include "FordBellman.h"

std::vector<int> FordBellman::findPath(Graph * graph, int startVertex, int endVertex) {
	std::vector<int> heap;

	if (startVertex >= 0 && startVertex < graph->getVertex() && endVertex >= 0 && endVertex < graph->getVertex()) { //Koniec. Z poszukiwanego wierzcho³ka nie ma zadnych wyjsc
		int *distances = new int[graph->getVertex()];
		int *prev = new int[graph->getVertex()];

		for (int i = 0; i < graph->getVertex(); i++) {
			distances[i] = 999; // Jakas duza liczba - bliska nieskonczonosci. I tak liczby wylosowane to 1-100
			prev[i] = -1; // Algorytm jeszcze nie odwiedzil zadnego wierzcholka
		}
		distances[startVertex] = 0; // Wierzcholek z ktorego sie zaczyna, ma wartosc 0 (najkrotsza droga).

		/*
			Algorytm dziala maksymalnie dla n-1 iteracji. Mozna to oczywiscie przerwac, jesli nie bedzie zadnej zmiany w aktualizacji sciezek
			Co kazda iteracje odwiedzamy wszystkie wierzcholki i aktualizujemy odleglosci do nich w tablicy distances
			A w tablicy prev ustawiamy skad sie przyszlo do danego wierzcholka
		*/
		std::vector<Edge> list;
		for (int vertex = 0; vertex < graph->getVertex(); vertex++) {	//Pobranie wszystkich mozliwych krawedzi.
			std::vector<Edge> tmp = graph->getConectedVertex(vertex);
			list.insert(list.end(), tmp.begin(), tmp.end());
		}

		int wasChange = false;
		for (int iteration = 0; iteration < graph->getVertex() - 1; iteration++) {
			wasChange = false;
			// Pobranie i aktualizacja nowych krawedzi

			for (int i = 0; i < list.size(); i++) {
				int v1 = list.at(i).v1;
				int v2 = list.at(i).v2;
				if (distances[v2] == 999 || distances[v2] > distances[v1] + graph->searchWeight(v1, v2)) {
					distances[v2] = distances[v1] + graph->searchWeight(v1, v2);
					prev[v2] = v1;

					wasChange = true;
				}
			}

			if (!wasChange)
				break;
		}


		/*
		W tablicy prev[] sa przechowywane informacje, gdzie index tablicy to wierzcholek w grafie
		a jego wartosc, to poprzedni wierzcholek z ktorym jest polaczony.
		Wystarczy odszukac ta sciezke od od tylu

		w tablicy distances, sa informacje o odleglosci od punktu startowego, do wszystkich pozostalych wierzcholkow
		*/
		heap.push_back(endVertex);
		for (int j = 0; j < graph->getVertex(); j++) {
			if (prev[heap.back()] == -1) {
				break;
			}
			heap.push_back(prev[heap.back()]);
		}
		heap.push_back(distances[endVertex]);

		delete[] distances;	//usuniecie wskaznikow, stworzonych na samym poczatku
		delete[] prev;

	}

	return heap;
}