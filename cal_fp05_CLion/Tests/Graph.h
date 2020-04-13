/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<int>> D;            // Floyd-Warshall
	vector<vector<T>> P;              // Floyd-Warshall

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (auto& v : this->vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }

    auto v = this->findVertex(orig);
    v->dist = 0;
    queue<Vertex<T>*> queue;
    queue.push(v);
    while (!queue.empty()) {
        v = queue.front(); queue.pop();
        for (auto& w : v->adj) {
            if (w.dest->dist == INF) {
                queue.push(w.dest);
                w.dest->dist = v->dist + 1;
                w.dest->path = v;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (auto& v : this->vertexSet) {
        v->dist = INF;
        v->path = NULL;
        v->visited = false;
    }

    auto v = this->findVertex(origin);
    v->dist = 0;
    v->visited = true;
    MutablePriorityQueue<Vertex<T>> queue;
    queue.insert(v);

    while (!queue.empty()) {
        v = queue.extractMin();
        for (auto& w : v->adj) {
            if (w.dest->dist > v->dist + w.weight) {
                w.dest->dist = v->dist + w.weight;
                w.dest->path = v;
                if (!w.dest->visited) {
                    queue.insert(w.dest);
                    w.dest->visited = true;
                }
                else
                    queue.decreaseKey(w.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (auto& v : this->vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    auto v = this->findVertex(orig);
    v->dist = 0;

    for (int i = 1; i <= this->vertexSet.size(); i++)
        for (auto& vert : this->vertexSet)
            for (auto& edge : vert->adj)
                if (edge.dest->dist > vert->dist + edge.weight) {
                    edge.dest->dist = vert->dist + edge.weight;
                    edge.dest->path = vert;
                }

    for (auto& vert : this->vertexSet)
        for (auto& edge : vert->adj)
            if (vert->dist + edge.weight < edge.dest->dist) {
                cout << "there are cycles of negative weight";
                break;
            }
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>* v = findVertex(dest);
	stack<T> stack;
	stack.push(v->info);
	while (v->getPath() != NULL) {
	    stack.push(v->getPath()->getInfo());
	    v = v->getPath();
	}

	while (!stack.empty()) {
        res.push_back(stack.top());
        stack.pop();
	}

	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // Distance initialization
    for (int i = 0; i < this->vertexSet.size(); i++) {
        vector<int> tmp;
        vector<int> tmp2;
        for (int j = 0; j < this->vertexSet.size(); j++) {
            tmp.push_back(10000000);
            tmp2.push_back(-1);
            if (i == j) {
                tmp[j] = 0;
                tmp2[j] = i;
            }
            else
                for (auto& w : this->vertexSet[i]->adj)
                    if (w.dest == this->vertexSet[j]) {
                        tmp[j] = w.weight;
                        tmp2[j] = i;
                    }

        }
        this->D.push_back(tmp);
        this->P.push_back(tmp2);
    }


    for (int k = 1; k < this->vertexSet.size(); k++) {
        for (int i = 0; i < this->vertexSet.size(); i++)
            for (int j = 0; j < this->vertexSet.size(); j++) {
                if (this->D[i][j] > this->D[i][k] + this->D[k][j]) {
                    this->D[i][j] = this->D[i][k] + this->D[k][j];
                    this->P[i][j] = k;
                }
            }
    }



}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const {
    vector<T> res;
    Vertex<T> *v = findVertex(dest);
    int i, j;
    for (i = 0; i < this->vertexSet.size(); i++)
        if (orig == this->vertexSet[i]->info)
            break;
    for (j = 0; j < this->vertexSet.size(); j++)
        if (dest == this->vertexSet[j]->info)
            break;

    if (i < j) {
        stack<int> stack;
        int path = j;
        stack.push(j);
        while (path != i) {
            path = this->P[i][path];
            stack.push(path);
        }
        while (!stack.empty()) {
            res.push_back(this->vertexSet[stack.top()]->info);
            stack.pop();
        }
    }
    else {
        int path = i;
        res.push_back(this->vertexSet[i]->info);
        while (path != j) {
            path = this->P[path][j];
            res.push_back(this->vertexSet[path]->info);
        }
    }
    return res;
}


#endif /* GRAPH_H_ */
