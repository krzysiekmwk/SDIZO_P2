class Vertex {

};

class GraphList{

public:

	GraphList(int vertex, bool simetric);
	~GraphList();
	void insert(int srcVertex, int dstVertex, int weight);
	int search(int srcVertex, int dstVertex);
	void setSimetric(bool sim);
	int getVertex();
	void clear();

private:
	int vertex, edge;       // liczba wierzcholkow i krawedzi
	bool simetric;
	int **matrix; // macierz  

	Vertex *vPrev, *vNext, *uPrev, *uNext;

	Vertex **GLists;     // tablica wskazników na listy wierzcho³ków  
};