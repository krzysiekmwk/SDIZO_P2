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
	vector<Edge> list = gl->getConectedVertex(startVertex);
	if (list.size() != 0 && startVertex != endVertex) { //Koniec. Z poszukiwanego wierzcho³ka nie ma zadnych wyjsc

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
		int *visited = new int[gl->getVertex()];

		for (int i = 0; i < gl->getVertex(); i++) {
			distances[i] = 999; // Jakas duza liczba - bliska nieskonczonosci. I tak liczby wylosowane to 1-100
			prev[i] = -1; // Algorytm jeszcze nie odwiedzil zadnego wierzcholka
			visited[i] = false; //tablica sluzaca do okreslania czy juz jakis wierzcholek nie zostal odwiedzony
		}

		distances[startVertex] = 0; // Wierzcholek z ktorego sie zaczyna, ma wartosc 0 (najkrotsza droga).
		visited[startVertex] = true;

		vector<int> heap;
		int actualVertex = startVertex;

		//Pierwsze wyznaczenie odleglosci do najblizszych wierzcholkow
		/*for (int i = 0; i < list.size(); i++) {
			distances[list.at(i).v2] = list.at(i).weight; //Aktualizacja odleglosci do najblizszych punktow
		}
		actualVertex = list.at(0).v2; // Pobranie wierzcholka, do ktorego widzie sciezka o najmniejszej wartosci

		for (int i = 0; i < gl->getVertex(); i++) {
			cout << i << " " << distances[i] << endl;
		}
		cout << endl;*/
		// Wyznaczanie sciezki

		/*Dzialanie algorytmu:
			Bierzemy pierwszy punkt startowy, nastepnie przeszukujemy polaczone wierzcholki i wagi krawedzi
			Wybieramy ta krawedz, ktora ma najkrotsza droge i idziemy do tamtego wierzcholka.
			Zaznaczamy ze wierzcholek zostal odwiedzony i znowu przeszukujemy jego sasiadow
			Nastepnie wybieramy kolejny element, ktory ma namniejsza sciezke, ale ktory nie byl jeszcze odwiedzony
			Powtarzamy az przejdzie sie wszystkie wierzcholki badz osiagnie cel

			Jak okaze sie ze nie ma wybranej drogi, to sciagamy wierzcholek ze stosu, a jak jest, to idziemy do niego i wrzucamy na stos
		*/

		actualVertex = startVertex;
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

		
		for (int j = 0; j < gl->getVertex(); j++) {
			cout << prev[j] << " ";
		}
		cout << endl;

		heap.push_back(endVertex);
		for (int j = 0; j < gl->getVertex(); j++) {
			if (prev[heap.back()] == -1) {
				break;
			}
			heap.push_back(prev[heap.back()]);
		}
		

		std::reverse(heap.begin(), heap.end());


		if (heap.size() < 2)
			cout << "Nie ma takiej drogi" << endl;
		else {
			for (int i = 0; i < heap.size(); i++) {
				cout << heap.at(i) << " ";
			}
			cout << "dlugosc: " << distances[endVertex] << endl;
		}

	}

		/*while (!heap.empty()) {
			list = gl->getConectedVertex(actualVertex);	// Pobranie i aktualizacja nowych krawedzi
			visited[actualVertex] = true;
			sort(list.begin(), list.end(), less_than_key());

			for (int i = 0; i < list.size(); i++) {
				if (distances[list.at(i).v2] > distances[actualVertex] + gl->searchWeight(actualVertex, list.at(i).v2)) {
					distances[list.at(i).v2] = distances[actualVertex] + gl->searchWeight(actualVertex, list.at(i).v2);
					prev[list.at(i).v2] = actualVertex;
				}
			}

			for (int i = 0; i < gl->getVertex(); i++) {
				cout << i << " " << distances[i] << endl;
			}
			cout << endl;

			if (list.size() == 0) {
				if (actualVertex == endVertex) {
					break;
				}

				actualVertex = heap.back();	//cofniecie do poprzedniego wierzcholka i wybranie drogi do kolejnego
				heap.pop_back();
				list = gl->getConectedVertex(actualVertex);
				sort(list.begin(), list.end(), less_than_key());
				bool isNext = false;
				for (int i = 0; i < list.size(); i++) {
					if (visited[list.at(i).v2] != true) {	//Sprawdza czy zostaly odwiedzone pozostale wierzcholki. Jesli nie, to idzie do kolejnego z najmniejsza krawedza.
						heap.push_back(actualVertex);
						actualVertex = list.at(i).v2;
						isNext = true;
						break;
					}
				}
				if (!isNext) {
					heap.clear();
					break;
				}
			}
			else {
				heap.push_back(actualVertex);	//Mozna isc do kolejnego wierzcholka o najnizszej krawedzi
				actualVertex = list.at(0).v2;
				while (visited[actualVertex] == true) {
					actualVertex = heap.back();
					heap.pop_back();
				}

				if (actualVertex == endVertex) {
					heap.push_back(actualVertex);
					break;
				}
			}
		}

		if(heap.empty())
			cout << "Nie ma takiej drogi" << endl;

		for (int i = 0; i < heap.size(); i++) {
			cout << heap.at(i) << " ";
		}
	}
	else {
		cout << "Zaczyna sie z tego samego punktu co konczy" << endl;
	}*/

}