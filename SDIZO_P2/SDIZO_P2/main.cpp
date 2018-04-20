#include <iostream>
#include <string>
#include <fstream>

#include "GraphMatrix.h"


using namespace std;

void displayGraphMatrixAsMatrix(GraphMatrix *gm);
void displayGraphMatrixAsList(GraphMatrix *gm);

void fillGraphMatrix(GraphMatrix *&gm);

int main() {
	GraphMatrix *gm = new GraphMatrix(5, false);

	fillGraphMatrix(gm);

	displayGraphMatrixAsMatrix(*&gm);
	cout << "\n\n\n\n\n";
	displayGraphMatrixAsList(*&gm);
	cout << "\n\n\n\n\n";

	int x;
	cin >> x;
	return 0;
}

void displayGraphMatrixAsMatrix(GraphMatrix *gm) {
	cout << "\t";
	for (int j = 0; j < gm->getVertex(); j++) {
		cout << j << "\t";
	}
	cout << endl;

	for (int i = 0; i < gm->getVertex(); i++) {
		cout << i << "\t";
		for (int j = 0; j < gm->getVertex(); j++) {
			cout << gm->search(i, j) << "\t";
		}
		cout << endl;
	}
}

void displayGraphMatrixAsList(GraphMatrix *gm) {
	for (int i = 0; i < gm->getVertex(); i++) {
		for (int j = 0; j < gm->getVertex(); j++) {
			int value = gm->search(i, j);
			if (value > 0) {
				cout << i << "\t" << j << "\t" << value << "\t" << endl;
			}
		}
	}
}

void fillGraphMatrix(GraphMatrix *&gm) {
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

		gm = new GraphMatrix(atoi(vertex.c_str()), false);

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

