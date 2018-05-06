#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "GraphMatrix.h"
#include "GraphIncidenceMatrix.h"


using namespace std;

void displayGraphMatrixAsMatrix(GraphIncidenceMatrix *gm);
void displayGraphMatrixAsList(GraphIncidenceMatrix *gm);

void fillGraphMatrix(GraphIncidenceMatrix *&gm);

void randData(int countOfVertexs, int density, GraphIncidenceMatrix *&gm);

bool directed = false; // Czy graf ma byc skierowany czy nie

int main() {
	srand(time(NULL));
	GraphIncidenceMatrix *gm;

	fillGraphMatrix(gm);
	cout << "\n\n";
	displayGraphMatrixAsMatrix(*&gm);
	cout << "\n\n\n\n\n";
	displayGraphMatrixAsList(*&gm);
	cout << "\n\n\n\n\n";

	delete gm;
	randData(5, 50, gm);
	cout << "\n\n";
	displayGraphMatrixAsMatrix(*&gm);
	cout << "\n\n\n\n\n";
	displayGraphMatrixAsList(*&gm);
	cout << "\n\n\n\n\n";

	int x;
	cin >> x;
	return 0;
}

void displayGraphMatrixAsMatrix(GraphIncidenceMatrix *gm) {
	//Wyswietlenie macierzy incydencji
	cout << "\t";
	for (int j = 0; j < gm->getEdges(); j++) {
		cout << j << "\t";
	}
	cout << endl;

	for (int i = 0; i < gm->getVertex(); i++) {
		cout << i << "\t";
		for (int j = 0; j < gm->getEdges(); j++) {
			cout << gm->getMatrix()[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\n\n";

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

void displayGraphMatrixAsList(GraphIncidenceMatrix *gm) {
	for (int i = 0; i < gm->getVertex(); i++) {
		for (int j = 0; j < gm->getVertex(); j++) {
			int value = gm->searchWeight(i, j);
			if (value > 0) {
				cout << i << "\t" << j << "\t" << value << "\t" << endl;
			}
		}
	}
}

void fillGraphMatrix(GraphIncidenceMatrix *&gm) {
	string firstLine;
	string vertex;
	string edges;
	ifstream myfile("example.txt");

	if (myfile) {
		getline(myfile, firstLine); // Wczytanie pierwszej lini - informacja ile jest krawedzi oraz wierzcholkow
		std::size_t pos = firstLine.find(" "); //odnalezienie spacji
		edges = firstLine.substr(0, pos);
		vertex = firstLine.substr(pos);

		//cout << edges << "\t" << vertex << endl;

		gm = new GraphIncidenceMatrix(atoi(vertex.c_str()), atoi(edges.c_str()), directed);

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

			//cout << srcVertex << "\t" << dstVertex << "\t" << weight << "\t" << endl;
			gm->insert(atoi(srcVertex.c_str()), atoi(dstVertex.c_str()), atoi(weight.c_str()));
		}

		myfile.close();
	}
	else cout << "plik sie nie wczytal\n";
}

void randData(int countOfVertexs, int density, GraphIncidenceMatrix *&gm) {
	int countOfEdges = (((countOfVertexs * (countOfVertexs - 1)) / 2) * density) / 100;
	int minCountOfEdges = countOfVertexs - 1;

	if (countOfEdges < minCountOfEdges)	//Jesli dla podanej objetosci graf nie mozne bys spojny, to nalezy sprawic by byl (zwiekszyc ilosc krawedzi do minimum)
		countOfEdges = minCountOfEdges;
	countOfEdges = countOfEdges - minCountOfEdges; //Ilosc polaczen pozostala do wylosowania, po tym jak graf juz bedzie spojny

	gm = new GraphIncidenceMatrix(countOfVertexs, countOfEdges + minCountOfEdges, directed);

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

