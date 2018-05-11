#include "Dijkstra.h"

std::vector<int> Dijkstra::findPath(Graph * graph, int startVertex, int endVertex) {
	std::vector<int> heap;
	
	if (startVertex >= 0 && startVertex < graph->getVertex() && endVertex >= 0 && endVertex < graph->getVertex()) { //Koniec. Z poszukiwanego wierzcho³ka nie ma zadnych wyjsc
		int *distances = new int[graph->getVertex()];
		int *prev = new int[graph->getVertex()];
		bool *visited = new bool[graph->getVertex()];

		for (int i = 0; i < graph->getVertex(); i++) {
			distances[i] = 999; // Jakas duza liczba - bliska nieskonczonosci. I tak liczby wylosowane to 1-100
			prev[i] = -1; // Algorytm jeszcze nie odwiedzil zadnego wierzcholka
			visited[i] = false; //tablica sluzaca do okreslania czy juz jakis wierzcholek nie zostal odwiedzony
		}
		distances[startVertex] = 0; // Wierzcholek z ktorego sie zaczyna, ma wartosc 0 (najkrotsza droga).

		/*Dzialanie algorytmu:
			Zaznaczamy ze wierzcholek zostal odwiedzony przeszukujemy jego sasiadow
			Aktualizujemy odleglosci do pozostalych widocznych wierzcholkow
			Aktualizujemy najblizsze wierzcholki o informacje o najkrotszej sciezce (wtedy kazdy wierzcholek dokladnie bedzie wiedzial jaki jest jego poprzednik)
			Wyszukujemy ta krawedz, ktora ma najkrotsza droge i nie zostala jeszcze odwiedzona i idziemy do tamtego wierzcholka.
			Jesli to jest juz nasz poszukiwany wierzcholek, to przerywamy algorytm - znalezlismy najkrotsza sciezke

			Algorytm w najgorszym przypadku, bedzie musial przeszukac wszystkie mozliwe wierzcholki i uaktualnic droge do nich
		*/
		//= gl->getConectedVertex(startVertex);
		int actualVertex = startVertex;
		for (int i = 0; i < graph->getVertex(); i++) {
			visited[actualVertex] = true;
			std::vector<Edge> list = graph->getConectedVertex(actualVertex);	// Pobranie i aktualizacja nowych krawedzi

			for (int i = 0; i < list.size(); i++) {
				if (distances[list.at(i).v2] > distances[actualVertex] + graph->searchWeight(actualVertex, list.at(i).v2)) {
					distances[list.at(i).v2] = distances[actualVertex] + graph->searchWeight(actualVertex, list.at(i).v2);
					prev[list.at(i).v2] = actualVertex;
				}
			}

			int min = 999; //Bedziemy poszukiwac elementu minimalnego
			int minVertex = -1;
			for (int j = 0; j < graph->getVertex(); j++) {
				if (distances[j] < min && visited[j] == false) {
					min = distances[j];
					minVertex = j;
				}
			}

			if (minVertex != -1) {
				actualVertex = minVertex;

				if (actualVertex == endVertex) {
					break;
				}
			}
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
		delete[] visited;
	}

	return heap;
}