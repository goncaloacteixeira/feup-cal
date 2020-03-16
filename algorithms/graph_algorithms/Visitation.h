//
// Created by skidr on 16/03/2020.
//

#ifndef FASTEST_ROUTE_VISITATION_H
#define FASTEST_ROUTE_VISITATION_H

#include <climits>
#include "Graph.h"

template <class T>
class Visitation {
    Vertex<T>* vertex;
    Vertex<T>* previous;
    int distance;
public:
    Visitation(Vertex<T> *vertex) : vertex(vertex) {
        this->previous = NULL;
        this->distance = INT_MAX;
    }

    void updateDistance(int dist);
    void updatePath(Vertex<T>* prev);
    vector<Edge<T>> getAdj();
    bool operator <(const Visitation& visitation) const;

};

template<class T>
bool Visitation<T>::operator<(const Visitation &visitation) const {
    return (this->distance > visitation.distance);
}

template<class T>
void Visitation<T>::updateDistance(int dist) {
    this->distance = dist;
}

template<class T>
void Visitation<T>::updatePath(Vertex<T> *prev) {
    this->previous = prev;
}

template<class T>
vector<Edge<T>> Visitation<T>::getAdj() {
    return this->vertex->adj;
}


#endif //FASTEST_ROUTE_VISITATION_H
