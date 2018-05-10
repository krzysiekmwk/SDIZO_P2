#include "Kruskal.h"

using namespace std;

struct less_than_key
{
	inline bool operator() (const Edge& struct1, const Edge& struct2)
	{
		return (struct1.weight < struct2.weight);
	}
};

GraphList * Kruskal::makeMST(Graph * graph) {
	std::vector<Edge> list;

	for (int i = 0; i < graph->getVertex(); i++) {
		std::vector<Edge> tmp = graph->getConectedVertex(i);	// Pobranie wszystkich krawedzi
		list.insert(list.end(), tmp.begin(), tmp.end());
	}

	sort(list.begin(), list.end(), less_than_key());	// Posortowanie ich od najmniejszej do najwiekszej

	// Drzewo MST bedzie przechowywane w nowym grafie. Listowo - bo to rzadki graf z mala liczba krawedzi (n-1)
	GraphList *mst = new GraphList();
	mst->setGraph(graph->getVertex(), graph->getVertex() - 1, true);

	// Wybranie pierwszej najmniejszej krawedzi oraz zapisanie wybranych wierzcholkow
	mst->insert(list.at(0).v1, list.at(0).v2, list.at(0).weight);

	// wybor kolejnej najmniejszej krawedzi, ale z wierzcholkow, ktore nie utworza cyklu (nie moga dwa na raz byc w tablicy visited)
	int countEdges = 1;
	for (int i = 1; i < list.size(); i++) {
		//bool foundCycle = false;
		//foundCycle = ;
		//if(!foundCycle && mst.searchWeight(list.at(i).v1, list.at(i).v2) == 0){
		if (!mst->isPath(list.at(i).v1, list.at(i).v2, list.at(i).v1, false)) {
			mst->insert(list.at(i).v1, list.at(i).v2, list.at(i).weight);
			countEdges++;
		}

		if (countEdges == mst->getEdges())
			break;
	}

	// Po sprawdzeniu wszystkich krawedzi, otrzymuje sie najmniejsze drzewo spinajace
	/*cout << "TREE:"  << endl;
	for (int i = 0; i < mst.getVertex(); i++) {
		for (int j = 0; j < mst.getVertex(); j++) {
			cout << mst.searchWeight(i, j) << ", ";
		}
		cout << endl;
	}*/

	return mst;
}
