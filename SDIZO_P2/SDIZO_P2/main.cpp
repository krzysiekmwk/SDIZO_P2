#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>

#include "GraphMatrix.h"
#include "GraphIncidenceMatrix.h"
#include "GraphList.h"
#include "Graph.h"

#include "Dijkstra.h"

using namespace std;

void displayGraphAsMatrix(Graph *gm);
void displayGraphAsList(Graph *gm);
void displayGraphAsFormForGraphOnline(Graph *gm);
void displayIncidenceGraph(GraphIncidenceMatrix *gim);

void fillGraphMatrix(Graph *&gm, bool directed);

void randData(int countOfVertexs, int density, Graph *&gm, bool directed);

struct less_than_key
{
	inline bool operator() (const Edge& struct1, const Edge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};

struct Edges {
	int v1, v2, weight;
};

int main() {
	srand(time(NULL));

	Graph *gm;
	GraphList *gl = new GraphList();
	GraphIncidenceMatrix *gim = new GraphIncidenceMatrix();

	gm = gim;
	fillGraphMatrix(gm, false);
	//randData(8, 80, gm, false);
	displayGraphAsFormForGraphOnline(gim);

	Dijkstra dijkstra;
	vector<int> shortestPath = dijkstra.findPath(gim, 0, 3);

	std::reverse(shortestPath.begin(), shortestPath.end());

	if (shortestPath.size() < 3)
		cout << "Nie ma takiej drogi" << endl;
	else {
		for (int i = 1; i < shortestPath.size(); i++) {
			cout << shortestPath.at(i) << " ";
		}
		cout << "dlugosc: " << shortestPath[0] << endl;
	}

	cout << "END ALG" << endl;

	/*gm = gl;
	
	fillGraphMatrix(gm, true);

	cout << "\n\n";
	displayGraphAsMatrix(gl);
	cout << "\n\n\n\n\n";
	displayGraphAsList(gl);
	cout << "\n\n\n\n\n";

	gm = gim;

	randData(5, 25, gm, true);
	displayGraphAsMatrix(gim);
	cout << "\n\n\n\n\n";
	displayGraphAsList(gim);
	cout << "\n\n\n\n\n";
	displayIncidenceGraph(gim);*/

	int x;
	cin >> x;
	return 0;
}

void displayIncidenceGraph(GraphIncidenceMatrix *gim) {
	//Wyswietlenie macierzy incydencji
	cout << "\t";
	for (int j = 0; j < gim->getEdges(); j++) {
		cout << j << "\t";
	}
	cout << endl;

	for (int i = 0; i < gim->getVertex(); i++) {
		cout << i << "\t";
		for (int j = 0; j < gim->getEdges(); j++) {
			cout << gim->getMatrix()[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\n\n";
}

void displayGraphAsFormForGraphOnline(Graph *gm) {
	for (int i = 0; i < gm->getVertex(); i++) {
		for (int j = 0; j < gm->getVertex(); j++) {
			cout << gm->searchWeight(i, j) << ", ";
		}
		cout << endl;
	}
}

void displayGraphAsMatrix(Graph *gm) {
	//Wyswietlenie jak w macierzy sasiedztwa - pokazanie ich wag
	cout << "\t";
	for (int j = 0; j < gm->getVertex(); j++) {
		cout << j << "\t";
	}
	cout << endl;

	for (int i = 0; i < gm->getVertex(); i++) {
		cout << i << "\t";
		for (int j = 0; j < gm->getVertex(); j++) {
			cout << gm->searchWeight(i, j) << "\t";
		}
		cout << endl;
	}
}

void displayGraphAsList(Graph *gm) {
	for (int i = 0; i < gm->getVertex(); i++) {
		for (int j = 0; j < gm->getVertex(); j++) {
			int value = gm->searchWeight(i, j);
			if (value > 0) {
				cout << i << "\t" << j << "\t" << value << "\t" << endl;
			}
		}
	}
}

void fillGraphMatrix(Graph *&gm, bool directed) {
	string firstLine;
	string vertex;
	string edges;
	ifstream myfile("example.txt");

	if (myfile) {
		getline(myfile, firstLine); // Wczytanie pierwszej lini - informacja ile jest krawedzi oraz wierzcholkow
		std::size_t pos = firstLine.find(" "); //odnalezienie spacji
		edges = firstLine.substr(0, pos);
		vertex = firstLine.substr(pos);

		gm->setGraph(atoi(vertex.c_str()), atoi(edges.c_str()), directed);

		for (int i = 0; i < atoi(edges.c_str()); i++) {
			string line;
			string srcVertex;
			string dstVertex;
			string weight;
			getline(myfile, line);

			std::size_t pos = line.find(" "); //odnalezienie spacji
			srcVertex = line.substr(0, pos);
			dstVertex = line.substr(pos, pos + 2);
			weight = line.substr(pos + 2);

			gm->insert(atoi(srcVertex.c_str()), atoi(dstVertex.c_str()), atoi(weight.c_str()));
		}

		myfile.close();
	}
	else cout << "plik sie nie wczytal\n";
}

void randData(int countOfVertexs, int density, Graph *&gm, bool directed) {
	int countOfEdges = (((countOfVertexs * (countOfVertexs - 1)) / 2) * density) / 100;
	int minCountOfEdges = countOfVertexs - 1;

	if (countOfEdges < minCountOfEdges)	//Jesli dla podanej objetosci graf nie mozne bys spojny, to nalezy sprawic by byl (zwiekszyc ilosc krawedzi do minimum)
		countOfEdges = minCountOfEdges;
	countOfEdges = countOfEdges - minCountOfEdges; //Ilosc polaczen pozostala do wylosowania, po tym jak graf juz bedzie spojny

	gm->setGraph(countOfVertexs, countOfEdges + minCountOfEdges, directed);

	/*****Najpierw tworzymy minimalny graf spojny dla N-1********/
	int *vertexTab = new int[countOfVertexs];	//Tablica przechowujaca ile wierzcholkow ma juz jakies polaczenie z czyms
	for (int i = 0; i < countOfVertexs; i++)
		vertexTab[i] = 0;

	//Losowanie peirwszego polaczenia dwoch losowych wierzcholkow
	int randV1;
	int randV2;
	int randWeight = rand() % 100 + 1;

	do {
		randV1 = rand() % countOfVertexs;
		randV2 = rand() % countOfVertexs;
	} while (randV1 == randV2);

	vertexTab[randV1] = 1;
	vertexTab[randV2] = 1;
	gm->insert(randV1, randV2, randWeight);
	minCountOfEdges--;

	//Losowanie reszty wierzcholkow, polaczonych do tych co juz sa - wynikiem bedzie powstanie graf spojny
	while (minCountOfEdges > 0) {

		do {
			randV1 = rand() % countOfVertexs;
		} while (vertexTab[randV1] == 1);	//Szukanie wierzcholka ktory nie jest jeszcze z zadnym polaczony

		do {
			randV2 = rand() % countOfVertexs;
		} while (vertexTab[randV2] != 1);	//Szukanie wierzcholka ktory ma juz jakies polaczenie

		randWeight = rand() % 100 + 1;
		gm->insert(randV1, randV2, randWeight);
		vertexTab[randV1] = 1;
		minCountOfEdges--;
	}

	delete[] vertexTab; // Tablica nie bedzie juz dalej potrzebna

	/*****Graf jest juz spojny, teraz trzeba dolosowac polaczenia, tak aby gestosc grafu byla odpowiednia********/
	
	while (countOfEdges > 0) {
		randV1 = rand() % countOfVertexs;
		randV2 = rand() % countOfVertexs;

		if (randV1 != randV2) {
			if (gm->searchWeight(randV1, randV2) == 0 && gm->searchWeight(randV2, randV1) == 0) {
				randWeight = rand() % 100 + 1;
				gm->insert(randV1, randV2, randWeight);
				countOfEdges--;
			}
		}
	}
}

