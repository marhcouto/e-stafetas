//
// Created by marhc on 04/05/2021.
//

#ifndef ENTREGA2_GRAPH_H
#define ENTREGA2_GRAPH_H



#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <stack>
#include "MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Node;

#define INF std::numeric_limits<double>::max()
#define INTINF std::numeric_limits<int>::max()

class NodeDoesNotExistException {
    const std::string message;
public:
    explicit NodeDoesNotExistException(std::string message) : message(std::move(message)) {}
    std::string getMessage() const { return message; }
};


template <class T>
class Node {
    T info; // Information of the node
    const int id;
    int idM; // For Shortest-paths matrixes
    std::vector<Edge<T> *> adj; // Outgoing edges
    bool visited = false;
    bool isInStack = false; // For Tarjan's
    int num; // For Tarjan's
    int low; // For Tarjan's
    Node<T> *path = nullptr;
    int queueIndex = 0; // required by MutablePriorityQueue
    double dist = 0; // For dijkstra's

    Edge<T> * addEdge(Node<T> *dest, double w);
    void addEdge(Edge<T>* edge);
public:
    Node(T in, int id);
    //~Node();

    T getInfo() const;
    int getQueueIndex() const;
    double getDist() const;
    const Node *getPath() const;
    int getNum() const;
    int getLow() const;
    const int getId() const;
    int getIDM() const;
    bool getVisited() const;
    void setPath(Node<T>* path);
    void setVisited(bool visited);
    const vector<Edge<T> *> &getAdj() const;

    bool operator< (const Node<T> & Node) const; // required by MutablePriorityQueue

    friend class Graph<T>;
    friend class MutablePriorityQueue<Node<T>>;
};


template <class T>
class Edge {
    Node<T>* orig; // Origin Node
    Node<T>* dest; // Destination Node
    double weight; // Edge weight
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
    std::vector<std::vector<double>> distanceMatrix; // Matrix for the Floyd-Warshall distances
    std::vector<std::vector<int>> pathsMatrix; // Matrix for the Floyd-Warshall's paths
public:
    Node<T>* findNode(int id) const;
    Node<T>* findNodeMatrixId(int idM) const; // To find a node through its matrix id
    Node<T>* addNode(const T &in, int id);
    Edge<T>* addEdge(int id1, int idM, double w);
    Edge<T>* addEdge(Node<T>* node1, Node<T>* node2, double w);
    std::vector<Node<T> *> getNodeSet() const;
    ~Graph();

    // Algorithms

    // Shortest Path
    void floydWarshallShortestPath();
    void dijkstraMulti();
    void updatePaths(int id);

    // Connectivity
    void tarjan();
    int dfsTarjan(Node<T>* node, int& counter, std::stack<Node<T>*>& st);

    // Utils
    void printMatrixes();
    void eliminateInaccessible(int id);
    void assignIDM();
    std::vector<int> getShortestPath(int s, int d) const;
};


// N O D E

template <class T>
Node<T>::Node(T in, int id): info(in), id(id) {}

/*template <class T>
Node<T>::~Node() {
    for (typename std::vector<Edge<T>*>::iterator iterator = adj.begin(); iterator != adj.end();) {
        // delete *iterator;
        iterator = adj.erase(iterator);
    }
}*/

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
const Node<T> *Node<T>::getPath() const {
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

template <class T>
void Node<T>::setPath(Node<T>* path) {
    this->path = path;
}

template<class T>
bool Node<T>::getVisited() const {
    return visited;
}

template<class T>
int Node<T>::getNum() const {
    return num;
}

template<class T>
int Node<T>::getLow() const {
    return low;
}

template<class T>
const int Node<T>::getId() const {
    return id;
}

template<class T>
int Node<T>::getIDM() const {
    return idM;
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
Node<T>* Graph<T>::addNode(const T &in, int id) {
    Node<T> *v = findNode(id);
    if (v != nullptr)
        return v;
    v = new Node<T>(in, id);
    nodeSet.push_back(v);
    return v;
}

template <class T>
Edge<T>* Graph<T>::addEdge(Node<T>* node1, Node<T>* node2, double w) {
    Edge<T> *e = new Edge<T>(node1, node2, w);
    node1->addEdge(e);
    return e;
}

template <class T>
Edge<T>* Graph<T>::addEdge(int id1, int id2, double w) {
    auto s = findNode(id1);
    auto d = findNode(id2);
    if (s == nullptr || d == nullptr)
        return nullptr;
    Edge<T> *e = new Edge<T>(s, d, w);
    s->addEdge(e);
    return e;
}

template <class T>
Node<T>* Graph<T>::findNode(int id) const {
    for (auto v : nodeSet)
        if (v->id == id)
            return v;
    return nullptr;
}

template <class T>
Node<T>* Graph<T>::findNodeMatrixId(int idM) const {
    for (auto v : nodeSet)
        if (v->idM == idM)
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

template <class T>
void Graph<T>::dijkstraMulti() {

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        std::vector<double> temp1;
        std::vector<int> temp2;
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            temp1.push_back(INF);
            temp2.push_back(0);
        }
        distanceMatrix.push_back(temp1); //Weights
        pathsMatrix.push_back(temp2); //Paths
    }

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            distanceMatrix[i][j] = INF;
            pathsMatrix[i][j] = INTINF;
        }
    }

    for (Node<T>* node : nodeSet) {

        for (Node<T>* n : nodeSet) {
            n->visited = false;
            n->queueIndex = 0;
            n->dist = INF;
            n->path = NULL;
        }

        MutablePriorityQueue<Node<T>> nodeQueue;
        distanceMatrix[node->getId() - 1][node->getId() - 1] = 0;
        pathsMatrix[node->getId() - 1][node->getId() - 1] = node->getId();
        node->dist = 0;
        nodeQueue.insert(node);
        while(!nodeQueue.empty()) {
            Node<T>* node1 = nodeQueue.extractMin();
            node->visited = true;
            for (Edge<T>* edge : node1->adj) {
                if (edge->dest->dist > node1->dist + edge->weight && !edge->dest->visited) {
                    double oldDist = edge->dest->dist;
                    edge->dest->dist = node1->dist + edge->weight;
                    edge->dest->path = node1;
                    distanceMatrix[node->getId() - 1][edge->dest->getId() - 1] = edge->dest->dist;
                    pathsMatrix[node1->getId() - 1][edge->dest->getId() - 1] = pathsMatrix[node->getId() - 1][node1->getId() - 1];
                    if (oldDist == INF) {
                        nodeQueue.insert(edge->dest);
                    }
                    else
                        nodeQueue.decreaseKey(edge->dest);
                }
            }
        }
        updatePaths(node->getIDM());
    }
}

template <class T>
void Graph<T>::updatePaths(int idM) {
    // Id of the origin node for the paths
    Node<T>* origin = findNodeMatrixId(idM);
    if (origin == nullptr) return;

    for (Node<T>* node : nodeSet) {
        if (node->getIDM() == idM) {
            pathsMatrix[idM][idM] = 0;
            continue;
        }
        Node<T>* node1 = node;
        std::stack<int> st;
        while (node1->getIDM() != idM) {
            if (node1->path == NULL) break;
            st.push(node1->getIDM());
            node1 = node1->path;
        }
        int id1 = idM;
        int id2 = node->getIDM();
        while (!st.empty()) {
            pathsMatrix[id1][node->getIDM()] = st.top();
            id1 = st.top();
            st.pop();
        }
    }
}

template<class T>
void Graph<T>::floydWarshallShortestPath() { //Makes matrix with all paths

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        std::vector<double> temp1;
        std::vector<int> temp2;
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            temp1.push_back(INF);
            temp2.push_back(0);
        }
        distanceMatrix.push_back(temp1); //Weights
        pathsMatrix.push_back(temp2); //Paths
    }

    for (Node<T>* node : nodeSet) {
        distanceMatrix[node->getIDM()][node->getIDM()] = 0;
        pathsMatrix[node->getIDM()][node->getIDM()] = node->getIDM();
        for (Edge<T>* edge : node->adj) { //Initial fill in
            distanceMatrix[node->idM][edge->dest->idM] = edge->weight;
            pathsMatrix[node->idM][edge->dest->idM] = edge->dest->idM;
        }
    }
    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            for (unsigned int k = 0; k < nodeSet.size(); k++) {
                if (distanceMatrix[j][k] > distanceMatrix[j][i] + distanceMatrix[i][k]) { //Checks if going through i makes the path shorter
                    distanceMatrix[j][k] = distanceMatrix[j][i] + distanceMatrix[i][k];
                    pathsMatrix[j][k] = pathsMatrix[j][i];
                }
            }
        }
    }
    this->printMatrixes();
}

template <class T>
void Graph<T>::tarjan() {
    std::stack<Node<T>*> st;

    for (Node<T>* n : nodeSet) {
        n->visited = false;
        n->isInStack = false;
    }

    int numCounter = 0;

    for (Node<T>* n : nodeSet)
        dfsTarjan(n, numCounter, st);
}

template <class T>
int Graph<T>::dfsTarjan(Node<T> *node, int& counter, std::stack<Node<T>*>& st) {
    if (node->visited)
        return node->num;
    node->visited = true;
    node->isInStack = true;
    st.push(node);
    counter++;
    node->low = counter;
    node->num = counter;

    for (Edge<T>* edge : node->adj) {
        int temp = dfsTarjan(edge->dest, counter, st);
        if (temp < node->low && edge->dest->isInStack)
            node->low = temp;
    }
    if (node->low == node->num) {
        while(node != st.top()) {
            st.top()->low = node->low;
            st.top()->isInStack = false;
            st.pop();
        }
        st.top()->isInStack = false;
        st.pop();
    }
    return node->low;
}

// UTILS FOR ALGORITHMS

template<class T>
void Graph<T>::eliminateInaccessible(int id) {
    Node<T>* node = findNode(id);
    if (node == nullptr) throw NodeDoesNotExistException(std::string("Error in ") + std::string(__func__) +
                                                         ": node selected does not belong to the graph");

    for (auto iterator = nodeSet.begin(); iterator != nodeSet.end();) {
        if ((*iterator)->low != node->low) {
            delete *iterator;
            iterator = nodeSet.erase(iterator);
        }
        else
            iterator++;
    }
}

template <class T>
void Graph<T>::printMatrixes() {
    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            std::cout << distanceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            std::cout << pathsMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<class T>
std::vector<int> Graph<T>::getShortestPath(int s, int d) const{ //Calculate the paths
    std::vector<int> res;
    Node<T>* originV = this->findNode(s);
    Node<T>* destV = this->findNode(d);
    if (originV == nullptr || destV == nullptr) return res;

    res.push_back(originV->id);
    int nextI = originV->idM;

    while (destV->idM != nextI) {
        nextI = pathsMatrix[nextI][destV->idM];
        res.push_back(findNodeMatrixId(nextI)->id);
    }

    return res;
}

template <class T>
void Graph<T>::assignIDM() {
    int counter = 0;
    for (Node<T>* node : nodeSet) {
        node->idM = counter;
        counter++;
    }
}




#endif //ENTREGA2_GRAPH_H
