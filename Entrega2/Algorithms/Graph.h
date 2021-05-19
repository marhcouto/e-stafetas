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
#include <iostream>
#include "MutablePriorityQueue.h"
#include "NodesInfo.h"

class Edge;
class Graph;
class Node;

#define INF std::numeric_limits<double>::max()
#define INTINF std::numeric_limits<int>::max()

class NodeDoesNotExistException {
    const std::string message;
public:
    explicit NodeDoesNotExistException(std::string message) : message(std::move(message)) {}
    std::string getMessage() const { return message; }
};


class Node {
    NodeInfo info; // Information of the node
    const int id;
    int idM; // For Shortest-paths matrixes
    std::vector<Edge*> adj; // Outgoing edges
    bool visited = false;
    bool isInStack = false; // For Tarjan's
    int num; // For Tarjan's
    int low; // For Tarjan's
    Node* path = nullptr;
    int queueIndex = 0; // required by MutablePriorityQueue
    double dist = 0; // For dijkstra's
    double distR = 0; // for bi directional
    int way = 0; // ????????' For bidirectional dijkstra's

    Edge* addEdge(Node* dest, double w);
    void addEdge(Edge* edge);
public:
    Node(NodeInfo in, int id);
    //~Node();

    NodeInfo getInfo() const;
    int getQueueIndex() const;
    double getDist() const;
    const Node *getPath() const;
    int getNum() const;
    int getLow() const;
    int getId() const;
    int getIDM() const;
    bool getVisited() const;
    void setPath(Node* path);
    void setVisited(bool visited);
    const vector<Edge*> &getAdj() const;

    bool operator< (const Node & Node) const; // required by MutablePriorityQueue

    friend class Graph;
    friend class MutablePriorityQueue<Node>;
};


class Edge {
    Node* orig; // Origin Node
    Node* dest; // Destination Node
    double weight; // Edge weight
public:
    Edge(Node *o, Node *d, double w);

    double getWeight() const;
    Node *getOrig() const;
    Node *getDest() const;

    friend class Graph;
    friend class Node;
};


class Graph {
    std::vector<Node*> nodeSet; // Nodes
    std::vector<std::vector<double>> distanceMatrix; // Matrix for the Floyd-Warshall distances
    std::vector<std::vector<int>> pathsMatrix; // Matrix for the Floyd-Warshall's paths
public:
    Node* findNode(int id) const;
    Node* findNodeMatrixId(int idM) const; // To find a node through its matrix id
    Node* addNode(const NodeInfo &in, int id);
    Edge* addEdge(int id1, int idM, double w);
    Edge* addEdge(Node* node1, Node* node2, double w);
    std::vector<Node*> getNodeSet() const;
    ~Graph();

    // Algorithms

    // Shortest Path
    double bidirectionalDijkstra(int start, int finish);
    void floydWarshallShortestPath();
    void dijkstraMulti();
    void updatePaths(int id);

    // Connectivity
    void tarjan();
    int dfsTarjan(Node* node, int& counter, std::stack<Node*>& st);

    // Clustering
    std::vector<std::vector<Node*>> clustering(std::vector<Node*> nodes, int noSets);
    double getSetDistances(std::vector<Node*> v1, std::vector<Node*> v2);
    void mergeSets(std::vector<std::vector<Node*>>& clusters, int i, int j);

    // Utils
    void printMatrixes();
    void eliminateInaccessible(int id);
    void assignIDM();
    std::vector<int> getShortestPath(int s, int d) const;
};



#endif //ENTREGA2_GRAPH_H
