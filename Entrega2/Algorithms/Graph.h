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

class NodeDoesNotExistException {
    const std::string message;
public:
    explicit NodeDoesNotExistException(std::string &message) : message(message) {}
    std::string getMessage() const { return message; }
};


template <class T>
class Node {
    T info; //Information of the node
    std::vector<Edge<T> *> adj; //Outgoing edges
    bool visited = false;
    bool unachievable = false; // For Tarjan's
    int num; // For Tarjan's
    int low; // For Tarjan's
    Node<T> *path = nullptr;
    int queueIndex = 0; // required by MutablePriorityQueue
    double dist = 0;

    Edge<T> * addEdge(Node<T> *dest, double w);
    void addEdge(Edge<T>* edge);
public:
    Node(T in);

    T getInfo() const;
    int getQueueIndex() const;
    double getDist() const;
    Node *getPath() const;
    bool getVisited() const;
    void setVisited(bool visited);
    const vector<Edge<T> *> &getAdj() const;

    bool operator< (const Node<T> & Node) const; // required by MutablePriorityQueue

    friend class Graph<T>;
    friend class MutablePriorityQueue<Node<T>>;
};


template <class T>
class Edge {
    Node<T>* orig; 		    // Origin Node
    Node<T>* dest;           // Destination Node
    double weight;              // Edge weight
    // Edge<T>* reverse = nullptr;
public:
    Edge(Node<T> *o, Node<T> *d, double w);

    double getWeight() const;
    Node<T> *getOrig() const;
    Node<T> *getDest() const;

    friend class Graph<T>;
    friend class Node<T>;
};

template <class T>
class Graph {
    std::vector<Node<T> *> nodeSet; // Nodes
    std::vector<Edge<T> *> edgeSet; // Edges
    std::vector<std::vector<double>> floydWarshallDistanceMatrix; // Matrix for the Floyd-Warshall distances
    std::vector<std::vector<int>> floydWarshallPathsMatrix; // Matrix for the Floyd-Warshall's paths
public:
    Node<T>* findNode(const T &in) const;
    Node<T>* addNode(const T &in);
    Edge<T>* addEdge(const T &sourc, const T &dest, double w);
    std::vector<Node<T> *> getNodeSet() const;
    std::vector<Edge<T> *> getEdgeSet() const;
    ~Graph();

    // Algorithms
    void floydWarshallShortestPath();
    void tarjan(T info);
    int DFStarjan(Node<T>* node, int& counter);
};


// N O D E

template <class T>
Node<T>::Node(T in): info(in) {}

template <class T>
Edge<T> *Node<T>::addEdge(Node<T> *d, double w) {
    Edge<T> *e = new Edge<T>(this, d, w);
    adj.push_back(e);
    return e;
}

template <class T>
void Node<T>::addEdge(Edge<T>* edge) {
    adj.push_back(edge);
}

template <class T>
bool Node<T>::operator<(const Node<T> & Node) const {
    return this->dist < Node.dist;
}

template <class T>
T Node<T>::getInfo() const {
    return this->info;
}

template <class T>
double Node<T>::getDist() const {
    return this->dist;
}

template <class T>
int Node<T>::getQueueIndex() const {
    return this->queueIndex;
}

template <class T>
Node<T> *Node<T>::getPath() const {
    return this->path;
}

template<class T>
const std::vector<Edge<T> *> &Node<T>::getAdj() const {
    return adj;
}

template<class T>
void Node<T>::setVisited(bool visited) {
    this->visited = visited;
}

template<class T>
bool Node<T>::getVisited() const {
    return visited;
}


// E D G E

template <class T>
Edge<T>::Edge(Node<T> *o, Node<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
Node<T> *Edge<T>::getOrig() const {
    return orig;
}

template <class T>
Node<T> *Edge<T>::getDest() const {
    return dest;
}


// G R A P H

template <class T>
std::vector<Node<T> *> Graph<T>::getNodeSet() const {
    return this->nodeSet;
}

template <class T>
std::vector<Edge<T> *> Graph<T>::getEdgeSet() const {
    return this->edgeSet;
}

template <class T>
Node<T>* Graph<T>::addNode(const T &in) {
    Node<T> *v = findNode(in);
    if (v != nullptr)
        return v;
    v = new Node<T>(in);
    nodeSet.push_back(v);
    return v;
}

template <class T>
Edge<T>* Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto s = findNode(sourc);
    auto d = findNode(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    Edge<T> *e = new Edge<T>(s, d, w);
    s->addEdge(e);
    this->edgeSet.push_back(e);
    return e;
}

template <class T>
Node<T>* Graph<T>::findNode(const T & inf) const {
    for (auto v : nodeSet)
        if (v->info == inf)
            return v;
    return nullptr;
}

template <class T>
Graph<T>::~Graph() {
    for (auto v : nodeSet) {
        for (auto e : v->adj)
            delete e;
        delete v;
    }
}


// A L G O R I T H M S

template<class T>
void Graph<T>::floydWarshallShortestPath() { //Makes matrix with all paths

    for (unsigned int i = 0; i < nodeSet.size(); i++)
        nodeSet[i]->queueIndex = i;

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        std::vector<double> temp1;
        std::vector<int> temp2;
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            temp1.push_back(INF);
            temp2.push_back(0);
        }
        floydWarshallDistanceMatrix.push_back(temp1); //Weights
        floydWarshallPathsMatrix.push_back(temp2); //Paths
    }

    for (Node<T>* Node : nodeSet) {
        for (Edge<T>* edge : Node->adj) { //Initial fill in
            floydWarshallDistanceMatrix[Node->queueIndex][edge->dest->queueIndex] = edge->weight;
            floydWarshallPathsMatrix[Node->queueIndex][edge->dest->queueIndex] = edge->dest->queueIndex;
        }
    }

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            for (unsigned int k = 0; k < nodeSet.size(); k++) {
                if (floydWarshallDistanceMatrix[j][k] > floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k]) { //Checks if going through i makes the path shorter
                    floydWarshallDistanceMatrix[j][k] = floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k];
                    floydWarshallPathsMatrix[j][k] = floydWarshallPathsMatrix[j][i];
                }
            }
        }
    }
}


template <class T>
void Graph<T>::tarjan(T info) {
    Node<T>* node = findNode(info);
    if (node == nullptr) throw NodeDoesNotExistException(std::string("Error in ") + std::string(__func__) +
    ": node selected does not belong to the graph");

    for (Node<T>* n : nodeSet)
        node->visited = false;

    int numCounter = 0;

    for (Node<T>* n : nodeSet)
        DFStarjan(node, numCounter);

    for (Node<T>* n : nodeSet) {
        if (n->low != node->low)
            // TODO: remove node
            std::cout << "REMOVE NODE" << std::endl;
    }
}

template <class T>
int Graph<T>::DFStarjan(Node<T> *node, int& counter) {
    if (node->visited)
        return node->num;
    node->visited = true;
    counter++;
    node->low = counter;
    node->num = counter;

    for (Edge<T>* edge : node->adj) {
        int temp = DFStarjan(edge->dest, counter);
        if (temp < node->low)
            node->low = temp;
    }
    return node->low;
}

#endif //ENTREGA2_GRAPH_H
