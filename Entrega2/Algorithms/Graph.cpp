//
// Created by marhc on 04/05/2021.
//

#include "Graph.h"


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
    return this->NodeSet;
}

template <class T>
Node<T>* Graph<T>::addNode(const T &in) {
    Node<T> *v = findNode(in);
    if (v != nullptr)
        return v;
    v = new Node<T>(in);
    NodeSet.push_back(v);
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
    return e;
}

template <class T>
Node<T>* Graph<T>::findNode(const T & inf) const {
    for (auto v : NodeSet)
        if (v->info == inf)
            return v;
    return nullptr;
}

template <class T>
Graph<T>::~Graph() {

    for (auto v : NodeSet) {
        for (auto e : v->adj)
            delete e;
        delete v;
    }

}


// A L G O R I T H M S

template<class T>
void Graph<T>::floydWarshallShortestPath() { //Makes matrix with all paths

    for (unsigned int i = 0; i < NodeSet.size(); i++)
        NodeSet[i]->queueIndex = i;

    for (unsigned int i = 0; i < NodeSet.size(); i++) {
        std::vector<double> temp1;
        std::vector<int> temp2;
        for (unsigned int j = 0; j < NodeSet.size(); j++) {
            temp1.push_back(INF);
            temp2.push_back(0);
        }
        floydWarshallDistanceMatrix.push_back(temp1); //Weights
        floydWarshallPathsMatrix.push_back(temp2); //Paths
    }

    for (Node<T>* Node : NodeSet) {
        for (Edge<T> edge : Node->adj) { //Initial fill in
            floydWarshallDistanceMatrix[Node->queueIndex][edge.dest->queueIndex] = edge.weight;
            floydWarshallPathsMatrix[Node->queueIndex][edge.dest->queueIndex] = edge.dest->queueIndex;
        }
    }

    for (unsigned int i = 0; i < NodeSet.size(); i++) {
        for (unsigned int j = 0; j < NodeSet.size(); j++) {
            for (unsigned int k = 0; k < NodeSet.size(); k++) {
                if (floydWarshallDistanceMatrix[j][k] > floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k]) { //Checks if going through i makes the path shorter
                    floydWarshallDistanceMatrix[j][k] = floydWarshallDistanceMatrix[j][i] + floydWarshallDistanceMatrix[i][k];
                    floydWarshallPathsMatrix[j][k] = floydWarshallPathsMatrix[j][i];
                }
            }
        }
    }
}

