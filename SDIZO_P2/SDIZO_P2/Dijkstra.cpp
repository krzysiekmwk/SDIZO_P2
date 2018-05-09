#include "Dijkstra.h"

struct less_than_key
{
	inline bool operator() (const Edge& struct1, const Edge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};

std::vector<int> Dijkstra::findPath(GraphList * gl, int startVertex, int endVertex) {
	std::vector<int> heap;
	std::vector<Edge> list = gl->getConectedVertex(startVertex);
	if (list.size() != 0 && startVertex != endVertex) { //Koniec. Z poszukiwanego wierzcho³ka nie ma zadnych wyjsc
		int *distances = new int[gl->getVertex()];
		int *prev = new int[gl->getVertex()];
		int *visited = new int[gl->getVertex()];

		for (int i = 0; i < gl->getVertex(); i++) {
			distances[i] = 999; // Jakas duza liczba - bliska nieskonczonosci. I tak liczby wylosowane to 1-100
			prev[i] = -1; // Algorytm jeszcze nie odwiedzil zadnego wierzcholka
			visited[i] = false; //tablica sluzaca do okreslania czy juz jakis wierzcholek nie zostal odwiedzony
		}
		distances[startVertex] = 0; // Wierzcholek z ktorego sie zaczyna, ma wartosc 0 (najkrotsza droga).

		/*Dzialanie algorytmu:
			Bierzemy pierwszy punkt startowy, nastepnie przeszukujemy polaczone wierzcholki i wagi krawedzi
			Wybieramy ta krawedz, ktora ma najkrotsza droge i idziemy do tamtego wierzcholka.
			Zaznaczamy ze wierzcholek zostal odwiedzony i znowu przeszukujemy jego sasiadow
			Nastepnie wybieramy kolejny element, ktory ma namniejsza sciezke, ale ktory nie byl jeszcze odwiedzony
			Powtarzamy az przejdzie sie wszystkie wierzcholki badz osiagnie cel

			Jak okaze sie ze nie ma wybranej drogi, to sciagamy wierzcholek ze stosu, a jak jest, to idziemy do niego i wrzucamy na stos
		*/
		int actualVertex = startVertex;
		for (int i = 0; i < gl->getVertex(); i++) {
			visited[actualVertex] = true;
			list = gl->getConectedVertex(actualVertex);	// Pobranie i aktualizacja nowych krawedzi

			for (int i = 0; i < list.size(); i++) {
				if (distances[list.at(i).v2] > distances[actualVertex] + gl->searchWeight(actualVertex, list.at(i).v2)) {
					distances[list.at(i).v2] = distances[actualVertex] + gl->searchWeight(actualVertex, list.at(i).v2);
					prev[list.at(i).v2] = actualVertex;
				}
			}

			int min = 999; //Bedziemy poszukiwac elementu minimalnego
			int minVertex = -1;
			for (int j = 0; j < gl->getVertex(); j++) {
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

		heap.push_back(endVertex);
		for (int j = 0; j < gl->getVertex(); j++) {
			if (prev[heap.back()] == -1) {
				break;
			}
			heap.push_back(prev[heap.back()]);
		}
		heap.push_back(distances[endVertex]);
	}

	return heap;
}