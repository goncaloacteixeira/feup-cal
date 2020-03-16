//
// Created by skidr on 16/03/2020.
//

#ifndef FASTEST_ROUTE_PATH_FINDERS_H
#define FASTEST_ROUTE_PATH_FINDERS_H

#include "Graph.h"
#include <iomanip>
#include "lib/fort.hpp"


template<class T>
class PathFinders {
    Graph<T>* graph;
    void setUp();

public:
    PathFinders(Graph<T> *graph);

    string dijkstra(T source);
};


template<class T>
PathFinders<T>::PathFinders(Graph<T> *graph):graph(graph) {

}


template<class T>
void PathFinders<T>::setUp() {
    for (auto& v : this->graph->vertexSet) {
        v->dist = INT_MAX;
        v->visited = false;
        v->path = NULL;
    }
}


template <class T>
string PathFinders<T>::dijkstra(T source) {
    setUp();

    auto vertexs = graph->vertexSet;

    priority_queue<Vertex<T>* > min_heap;

    for (auto v : vertexs) {
        if (v->info == source) {
            v->dist = 0;
            min_heap.push(v);
        }
    }


    while(!min_heap.empty()) {
        auto v = min_heap.top();
        min_heap.pop();
        for (auto w : v->adj) {
            if (w.dest->dist > v->dist + w.weight) {
                w.dest->dist = v->dist + w.weight;
                w.dest->path = v;
                if (!w.dest->visited) {
                    min_heap.push(w.dest);
                    w.dest->visited = true;
                }
            }
        }
    }

    fort::char_table table;
    table.set_border_style(FT_NICE_STYLE);
    table.set_cell_text_align(fort::text_align::center);
    table << fort::header << "Vertex" << "Distance" << "Prev" << fort::endr;

    for (auto & v : vertexs) {
        table << v->info << v->dist;
        (v->path == NULL) ? table << "-" : table << v->path->info;
        table << fort::endr;
    }

    return table.to_string();
}


#endif //FASTEST_ROUTE_PATH_FINDERS_H
