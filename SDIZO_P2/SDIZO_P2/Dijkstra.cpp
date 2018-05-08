#include "Dijkstra.h"

using namespace std;

struct less_than_key
{
	inline bool operator() (const Edge& struct1, const Edge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};

void Dijkstra::findPath(GraphList * gl, int startVertex, int endVertex) {
	//sciezka: 5 -> 2; 5 -> 0(1) -> 1(2) -> 2(1) || 5 -> 1(8) -> 2(1)
	vector<Edge> list = gl->getConectedVertex(startVertex);

	cout << "Start DIJ" << endl;
	cout << "Vertex before" << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].v2 << " " << list[i].weight << endl;
	}

	sort(list.begin(), list.end(), less_than_key());
	cout << "Vertex after" << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << list[i].v2 << " " << list[i].weight << endl;
	}
	cout << "rest alg" << endl;


	int *distances = new int[gl->getVertex()];
	int *prev = new int[gl->getVertex()];

	for (int i = 0; i < gl->getVertex(); i++) {
		distances[i] = 999; // Jakas duza liczba - bliska nieskonczonosci. I tak liczby wylosowane to 1-100
		prev[i] = -1; // Algorytm jeszcze nie odwiedzil zadnego wierzcholka
	}

	distances[startVertex] = 0; // Wierzcholek z ktorego sie zaczyna, ma wartosc 0 (najkrotsza droga).

	vector<int> heap;

	// Wyznaczanie sciezki

	if (list.size() == 0) { cout << "lista pusta" << endl; return; } //Koniec. Z poszukiwanego wierzcho³ka nie ma zadnych wyjsc

	for (int i = 0; i < list.size(); i++) {
		distances[list.at(i).v2] = list.at(i).weight; //Aktualizacja odleglosci do najblizszych punktow
	}

	int nextVertex = list.at(0).v2; //Pobranie sciezki o najmniejszej wartosci
	cout << nextVertex << endl;

	for (int i = 0; i < gl->getVertex(); i++) {
		cout << i << " " << distances[i] << endl; //Aktualizacja odleglosci do najblizszych punktow
	}




}