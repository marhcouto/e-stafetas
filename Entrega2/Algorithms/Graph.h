//
// Created by marhc on 04/05/2021.
//

#ifndef ENTREGA2_GRAPH_H
#define ENTREGA2_GRAPH_H



#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()


template <class T>
class Vertex {
    T info; //Information of the node
    std::vector<Edge<T> *> adj; //Outgoing edges
    bool visited;
    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    Edge<T> * addEdge(Vertex<T> *dest, double w);
public:
    Vertex(T in);
    bool operator< (const Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    T getInfo() const;
    int getQueueIndex() const;
    double getDist() const;
    Vertex *getPath() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};



template <class T>
class Edge {
    Vertex<T> *orig; 		    // Origin vertex
    Vertex<T> * dest;           // Destination vertex
    double weight;              // Edge weight
    Edge<T> *reverse = nullptr;
public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;

    double getWeight() const;
    Vertex<T> *getOrig() const;
    Vertex<T> *getDest() const;
};

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // Vertexes
    std::vector<std::vector<double>> floydWarshallDistanceMatrix;
    std::vector<std::vector<int>> floydWarshallPathsMatrix;
public:
    Vertex<T>* findVertex(const T &in) const;
    Vertex<T>* addVertex(const T &in);
    Edge<T>* addEdge(const T &sourc, const T &dest, double w);
    std::vector<Vertex<T> *> getVertexSet() const;
    ~Graph();

    // Algorithms
    void floydWarshallShortestPath();
};





#endif //ENTREGA2_GRAPH_H
