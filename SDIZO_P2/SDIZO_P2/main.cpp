#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <chrono>

#include "GraphIncidenceMatrix.h"
#include "GraphList.h"
#include "Graph.h"

#include "Dijkstra.h"
#include "FordBellman.h"

#include "Kruskal.h"
#include "Prima.h"

#include "DoubleLinkedList.h"
#include "Edge.h"

using namespace std;

void showAndChooseMainScreen();

void displayGraphAsMatrix(Graph *gm);
void displayGraphAsList(Graph *gm);
void displayGraphAsFormForGraphOnline(Graph *gm);
void displayIncidenceGraph(GraphIncidenceMatrix *gim);

void fillGraphMatrix(Graph *&gm, bool directed);

void randData(int countOfVertexs, int density, Graph *&gm, bool directed);

int isProgramWorking;
bool representation = false; // false - lista | true - macierz
bool isDirected = false;	// false - skierowany ; true - nieskierowany

auto startTime = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::high_resolution_clock::now() - startTime;
long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
long long totalTime = 0;

Graph *gm;
GraphList *gl = new GraphList();
GraphIncidenceMatrix *gim = new GraphIncidenceMatrix();
vector<int> shortestPath;

int main() {
	srand(time(NULL));

	system("cls");
	cout << "Program testowy. Wpisz cokolwiek oraz powtwierdz eneterem by kontynuowac" << endl;
	int x;
	cin >> x;

	isProgramWorking = true;

	while (isProgramWorking)
	{
		showAndChooseMainScreen();
		system("PAUSE");
	}

	/*int V[5] = {10, 25, 50, 100, 150};
	int G[5] = {25, 50, 75, 99};


	cout << "LISTA" << endl;
	cout << "KRUSKAL" << endl;
	for (int v = 0; v < 5; v++) {
	for (int g = 0; g < 4; g++) {
	for (int i = 0; i < 100;i++) {
	gm = gim;
	randData(V[v], G[g], gm, false);

	Kruskal kruskal;

	startTime = std::chrono::high_resolution_clock::now();

	GraphList *mst = kruskal.makeMST(gim);

	elapsed = std::chrono::high_resolution_clock::now() - startTime;
	microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	totalTime += microseconds;
	delete mst;
	gm->clear();
	}
	cout << "Time: " << V[v] << " " << G[g] << " " << (totalTime / 100) << " us" << endl;
	totalTime = 0;
	}
	}

	gm = gl;
	//fillGraphMatrix(gm, false);
	//cout << "Rand" << endl;
	//randData(100, 100, gm, false);
	//displayGraphAsFormForGraphOnline(gl);
	//displayGraphAsMatrix(gl);
	//cout << "Start" << endl;
	//cout << "Kruskal" << endl;
	Kruskal kruskal;
	GraphList *mst = kruskal.makeMST(gl);
	displayGraphAsFormForGraphOnline(mst);

	cout << "Prima" << endl;
	Prima prima;
	GraphList *mst2 = prima.makeMST(gl);
	displayGraphAsFormForGraphOnline(mst2);

	cout << "Dijkstra" << endl;
	Dijkstra dijkstra;
	vector<int> shortestPath = dijkstra.findPath(gl, 56, 25);

	std::reverse(shortestPath.begin(), shortestPath.end());

	if (shortestPath.size() < 3)
	cout << "Nie ma takiej drogi" << endl;
	else {
	for (int i = 1; i < shortestPath.size(); i++) {
	cout << shortestPath.at(i) << " ";
	}
	cout << "dlugosc: " << shortestPath[0] << endl;
	}

	cout << "FordBellman" << endl;
	FordBellman fordBellman;
	vector<int> shortestPath2 = fordBellman.findPath(gl, 56, 25);

	std::reverse(shortestPath2.begin(), shortestPath2.end());

	if (shortestPath2.size() < 3)
	cout << "Nie ma takiej drogi" << endl;
	else {
	for (int i = 1; i < shortestPath2.size(); i++) {
	cout << shortestPath2.at(i) << " ";
	}
	cout << "dlugosc: " << shortestPath2[0] << endl;
	}

	cout << "END ALG" << endl;*/
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

void showAndChooseMainScreen() {
	int choose;
	system("cls");
	cout << "SDIZO P2 / Krzysztof Nowakowski / 235053" << endl;
	cout << "Aktualna reprezentacja: " << (representation ? "macierz" : "lista") << (isDirected ? " nieskierowana" : " skierowana") << endl;
	cout << "(1) Wybierz reprezentacje, ktora chcesz testowac" << endl;
	cout << "(2) Wczytaj dane z pliku" << endl;
	cout << "(3) Wygeneruj losowo graf" << endl;
	cout << "(4) Algorytm 1 Prima" << endl;
	cout << "(5) Algorytm 2 Kruskal" << endl;
	cout << "(6) Algorytm 3 Dijkstra" << endl;
	cout << "(7) Algorytm 4 Forda-Bellman" << endl;
	cout << "(8) Wyswietl listowo, macierzowo oraz jako wejscie dla strony http://graphonline.ru/en/create_graph_by_matrix" << endl;
	cout << "(9) Zakoncz" << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin >> choose;

	cout << "wpisano: " << choose << endl;

	switch (choose) {
	case 1:
		// wybor reprezentacji
		int choose;
		system("cls");
		cout << "00 - lista nieskierowana" << endl;
		cout << "10 - macierz nieskierowana" << endl;
		cout << "01 - lista skierowana" << endl;
		cout << "11 - macierz skierowana" << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choose;

		cout << "wpisano: " << choose << endl;

		switch (choose) {
		case 00:
			representation = false;
			isDirected = true;
			break;
		case 10:
			representation = true;
			isDirected = true;
			break;
		case 01:
			representation = false;
			isDirected = false;
			break;
		case 11:
			representation = true;
			isDirected = false;
			break;
		default:
			cout << "zla liczba, wybierz ponownie." << endl;
			system("PAUSE");
			break;
		}
		break;
	case 2:
		// wczytanie
		if (representation)
			gm = gim;
		else
			gm = gl;
		fillGraphMatrix(gm, isDirected);
		break;
	case 3:
		// losowanie
		int liczbaWierzcholkow;
		int gestosc;
		system("cls");
		cout << "Podaj liczbe wierzcholkow oraz gestosc grafu" << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> liczbaWierzcholkow;
		cin >> gestosc;
		if (representation)
			gm = gim;
		else
			gm = gl;

		startTime = std::chrono::high_resolution_clock::now();

		randData(liczbaWierzcholkow, gestosc, gm, isDirected);

		elapsed = std::chrono::high_resolution_clock::now() - startTime;
		microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		cout << "Czas wykonania: " << microseconds << "us" << endl;
		break;
	case 4:
		// Prima
		system("cls");
		cout << "Prima" << endl;
		Prima prima;
		GraphList *mstPrima;

		startTime = std::chrono::high_resolution_clock::now();

		if (representation) {
			mstPrima = prima.makeMST(gim);
			cout << "Waga grafu: " << mstPrima->getWeight() << endl;
		}	
		else {
			mstPrima = prima.makeMST(gl);
			cout << "Waga grafu: " << mstPrima->getWeight() << endl;
		}

		elapsed = std::chrono::high_resolution_clock::now() - startTime;
		microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		cout << "Czas wykonania: " << microseconds << "us" << endl;

		displayGraphAsList(mstPrima);
		cout << "\n\n";
		displayGraphAsMatrix(mstPrima);
		cout << "\n\n";
		displayGraphAsFormForGraphOnline(mstPrima);

		delete mstPrima;
		break;
	case 5:
		// Kruskal
		system("cls");
		cout << "Kruskal" << endl;
		Kruskal kruskal;
		GraphList *mstKruskal;

		startTime = std::chrono::high_resolution_clock::now();

		if(representation)
			mstKruskal = kruskal.makeMST(gim);
		else
			mstKruskal = kruskal.makeMST(gl);

		elapsed = std::chrono::high_resolution_clock::now() - startTime;
		microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		cout << "Czas wykonania: " << microseconds << "us" << endl;

		displayGraphAsList(mstKruskal);
		cout << "\n\n";
		displayGraphAsMatrix(mstKruskal);
		cout << "\n\n";
		displayGraphAsFormForGraphOnline(mstKruskal);
		
		delete mstKruskal;
		break;
	case 6:
		// Dijkstra
	{
		system("cls");
		cout << "Dijkstra" << endl;
		int start;
		int end;
		cout << "Podaj punkt startowy i koncowy" << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> start;
		cin >> end;
		Dijkstra dijkstra;

		startTime = std::chrono::high_resolution_clock::now();

		if (representation)
			shortestPath = dijkstra.findPath(gim, start, end);
		else
			shortestPath = dijkstra.findPath(gl, start, end);

		elapsed = std::chrono::high_resolution_clock::now() - startTime;
		microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		cout << "Czas wykonania: " << microseconds << "us" << endl;

		std::reverse(shortestPath.begin(), shortestPath.end());

		if (shortestPath.size() < 3)
			cout << "Nie ma takiej drogi" << endl;
		else {
			for (int i = 1; i < shortestPath.size(); i++) {
				cout << shortestPath.at(i) << " ";
			}
			cout << "dlugosc: " << shortestPath[0] << endl;
		}
	}
		break;
	case 7:
		// Ford
	{
		system("cls");
		cout << "Ford Bellman" << endl;
		int start;
		int end;
		cout << "Podaj punkt startowy i koncowy" << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> start;
		cin >> end;
		FordBellman fordBellman;

		startTime = std::chrono::high_resolution_clock::now();

		if (representation)
			shortestPath = fordBellman.findPath(gim, start, end);
		else
			shortestPath = fordBellman.findPath(gl, start, end);

		elapsed = std::chrono::high_resolution_clock::now() - startTime;
		microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		cout << "Czas wykonania: " << microseconds << "us" << endl;

		std::reverse(shortestPath.begin(), shortestPath.end());

		if (shortestPath.size() < 3)
			cout << "Nie ma takiej drogi" << endl;
		else {
			for (int i = 1; i < shortestPath.size(); i++) {
				cout << shortestPath.at(i) << " ";
			}
			cout << "dlugosc: " << shortestPath[0] << endl;
		}
	}
		break;
	case 8:
		//display
		system("cls");
		if (representation) {
			displayGraphAsList(gim);
			cout << "\n\n";
			displayGraphAsMatrix(gim);
			cout << "\n\n";
			displayGraphAsFormForGraphOnline(gim);
			cout << "\n\n";
		}
		else {
			displayGraphAsList(gl);
			cout << "\n\n";
			displayGraphAsMatrix(gl);
			cout << "\n\n";
			displayGraphAsFormForGraphOnline(gl);
			cout << "\n\n";
		}
		break;
	case 9:
		//exit
		isProgramWorking = false;
		break;
	default:
		cout << "zla liczba, wybierz ponownie." << endl;
		system("PAUSE");
		break;
	}
}

