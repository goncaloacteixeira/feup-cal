#include <iostream>
#include "Graph.h"
#include "path_finders.h"
#include <string>

#include <fstream>
#include <random>

Graph<string>* fill1() {
    auto graph = new Graph<string>();

    graph->addVertex("SF");
    graph->addVertex("SEATTLE");
    graph->addVertex("IDAHO");
    graph->addVertex("CHICAGO");
    graph->addVertex("NYC");

    graph->addEdge("SF", "SEATTLE", 3);
    graph->addEdge("SF", "IDAHO", 5);
    graph->addEdge("SEATTLE", "IDAHO", 1);
    graph->addEdge("SEATTLE", "CHICAGO", 2);
    graph->addEdge("CHICAGO", "IDAHO", 3);
    graph->addEdge("CHICAGO", "NYC", 4);
    graph->addEdge("IDAHO", "NYC", 6);

    return graph;
}

Graph<string>* fill2() {
    ifstream states("states.txt");
    vector<string> statesVec;

    auto *graph = new Graph<string>();

    if (states.is_open()) {
        string line;
        while(getline(states, line)) {
            graph->addVertex(line);
            statesVec.emplace_back(line);
        }
    }
    else {
        return nullptr;
    }

    srand(0);
    for (int i = 0; i < statesVec.size() - 1; i++) {
        int edges = rand() % 5 + 1;
        for (int j = 0; j < edges; j++) {
            string v2;
            do {
                v2 = statesVec[rand() % statesVec.size()];
            } while (statesVec[i] == v2);
            graph->addEdge(statesVec[i], v2, rand() % 20 + 1);
        }
    }
    return graph;
}


int main() {
    auto graph = fill2();

    auto pf = new PathFinders<string>(graph);

    cout << pf->dijkstra("Oregon");

    return 0;
}
