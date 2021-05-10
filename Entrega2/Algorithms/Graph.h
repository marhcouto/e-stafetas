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
template <class T> class Node;

#define INF std::numeric_limits<double>::max()


template <class T>
class Node {
    T info; //Information of the node
    std::vector<Edge<T> *> adj; //Outgoing edges
    bool visited;
    double dist = 0;
    Node<T> *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    Edge<T> * addEdge(Node<T> *dest, double w);
public:
    Node(T in);
    bool operator< (const Node<T> & Node) const; // // required by MutablePriorityQueue
    T getInfo() const;
    int getQueueIndex() const;
    double getDist() const;
    Node *getPath() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Node<T>>;
};



template <class T>
class Edge {
    Node<T> *orig; 		    // Origin Node
    Node<T> * dest;           // Destination Node
    double weight;              // Edge weight
    Edge<T> *reverse = nullptr;
public:
    Edge(Node<T> *o, Node<T> *d, double w);
    friend class Graph<T>;
    friend class Node<T>;

    double getWeight() const;
    Node<T> *getOrig() const;
    Node<T> *getDest() const;
};

template <class T>
class Graph {
    std::vector<Node<T> *> NodeSet; // Nodes
    std::vector<std::vector<double>> floydWarshallDistanceMatrix; // Matrix for the Floyd-Warshall distances
    std::vector<std::vector<int>> floydWarshallPathsMatrix; // Matrix for the Floyd-Warshall's paths
public:
    Node<T>* findNode(const T &in) const;
    Node<T>* addNode(const T &in);
    Edge<T>* addEdge(const T &sourc, const T &dest, double w);
    std::vector<Node<T> *> getNodeSet() const;
    ~Graph();

    // Algorithms
    void floydWarshallShortestPath();
};





#endif //ENTREGA2_GRAPH_H
