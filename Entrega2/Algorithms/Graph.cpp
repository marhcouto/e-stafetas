//
// Created by marhc on 04/05/2021.
//

#include "Graph.h"


// N O D E

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *d, double w) {
    Edge<T> *e = new Edge<T>(this, d, w);
    adj.push_back(e);
    return e;
}

template <class T>
bool Vertex<T>::operator<(const Vertex<T> & vertex) const {
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
int Vertex<T>::getQueueIndex() const {
    return this->queueIndex;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}


// E D G E

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}

template <class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}


// G R A P H

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return this->vertexSet;
}

template <class T>
Vertex<T>* Graph<T>::addVertex(const T &in) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(in);
    vertexSet.push_back(v);
    return v;
}

template <class T>
Edge<T>* Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    Edge<T> *e = new Edge<T>(s, d, w);
    s->addEdge(e);
    return e;
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
    for (auto v : vertexSet)
        if (v->info == inf)
            return v;
    return nullptr;
}

template <class T>
Graph<T>::~Graph() {

    for (auto v : vertexSet) {
        for (auto e : v->adj)
            delete e;
        delete v;
    }

}


// A L G O R I T H M S

template<class T>
void Graph<T>::floydWarshallShortestPath() { //Makes matrix with all paths

    for (unsigned int i = 0; i < vertexSet.size(); i++)
        vertexSet[i]->queueIndex = i;

    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        std::vector<double> temp1;
        std::vector<int> temp2;
        for (unsigned int j = 0; j < vertexSet.size(); j++) {
            temp1.push_back(INF);
            temp2.push_back(0);
        }
        floydWarshallDistanceMatrix.push_back(temp1); //Weights
        floydWarshallPathsMatrix.push_back(temp2); //Paths
    }

    for (Vertex<T>* vertex : vertexSet) {
        for (Edge<T> edge : vertex->adj) { //Initial fill in
            floydWarshallDistanceMatrix[vertex->queueIndex][edge.dest->queueIndex] = edge.weight;
            floydWarshallPathsMatrix[vertex->queueIndex][edge.dest->queueIndex] = edge.dest->queueIndex;
        }
    }

    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        for (unsigned int j = 0; j < vertexSet.size(); j++) {
            for (unsigned int k = 0; k < vertexSet.size(); k++) {
                if (floydWarshallDistanceMatrix[j][k] > floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k]) { //Checks if going through i makes the path shorter
                    floydWarshallDistanceMatrix[j][k] = floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k];
                    floydWarshallPathsMatrix[j][k] = floydWarshallPathsMatrix[j][i];
                }
            }
        }
    }
}

