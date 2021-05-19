//
// Created by marhc on 17/05/2021.
//

#include "Graph.h"

// N O D E

Node::Node(NodeInfo in, int id): info(in), id(id) {}

/*template <class T>
Node::~Node() {
    for (typename std::vector<Edge*>::iterator iterator = adj.begin(); iterator != adj.end();) {
        // delete *iterator;
        iterator = adj.erase(iterator);
    }
}*/

Edge *Node::addEdge(Node *d, double w) {
    Edge *e = new Edge(this, d, w);
    adj.push_back(e);
    return e;
}

void Node::addEdge(Edge* edge) {
    adj.push_back(edge);
}

bool Node::operator<(const Node & Node) const {
    return this->dist < Node.dist;
}

NodeInfo Node::getInfo() const {
    return this->info;
}

double Node::getDist() const {
    return this->dist;
}

int Node::getQueueIndex() const {
    return this->queueIndex;
}

const Node *Node::getPath() const {
    return this->path;
}

const std::vector<Edge *> &Node::getAdj() const {
    return adj;
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}

void Node::setPath(Node* path) {
    this->path = path;
}

bool Node::getVisited() const {
    return visited;
}

int Node::getNum() const {
    return num;
}

int Node::getLow() const {
    return low;
}

int Node::getId() const {
    return id;
}

int Node::getIDM() const {
    return idM;
}


// E D G E

Edge::Edge(Node *o, Node *d, double w): orig(o), dest(d), weight(w) {}

double Edge::getWeight() const {
    return weight;
}

Node *Edge::getOrig() const {
    return orig;
}

Node *Edge::getDest() const {
    return dest;
}


// G R A P H

std::vector<Node *> Graph::getNodeSet() const {
    return this->nodeSet;
}

Node* Graph::addNode(const NodeInfo &in, int id) {
    Node *v = findNode(id);
    if (v != nullptr)
        return v;
    v = new Node(in, id);
    nodeSet.push_back(v);
    return v;
}

Edge* Graph::addEdge(Node* node1, Node* node2, double w) {
    Edge *e = new Edge(node1, node2, w);
    node1->addEdge(e);
    return e;
}

Edge* Graph::addEdge(int id1, int id2, double w) {
    auto s = findNode(id1);
    auto d = findNode(id2);
    if (s == nullptr || d == nullptr)
        return nullptr;
    Edge *e = new Edge(s, d, w);
    s->addEdge(e);
    return e;
}

Node* Graph::findNode(int id) const {
    for (auto v : nodeSet)
        if (v->id == id)
            return v;
    return nullptr;
}

Node* Graph::findNodeMatrixId(int idM) const {
    for (auto v : nodeSet)
        if (v->idM == idM)
            return v;
    return nullptr;
}

Graph::~Graph() {
    for (auto v : nodeSet) {
        for (auto e : v->adj)
            delete e;
        delete v;
    }
}


// A L G O R I T H M S

// Shortest Path

double Graph::bidirectionalDijkstra(int start, int finish) {

    double bestDist = INF;

    Node* s = this->findNode(start);
    Node* p = this->findNode(finish);
    if (s == nullptr || p == nullptr) 1;

    for (Node *n : nodeSet) {
        n->visited = false;
        n->queueIndex = 0;
        n->dist = INF;
        n->distR = INF;
        n->way = 0;
        n->path = NULL;
    }

    s->way = 1;
    p->way = 2;

    MutablePriorityQueue<Node> nodeF;
    MutablePriorityQueue<Node> nodeB;

    s->dist = 0;
    p->distR = 0;
    nodeF.insert(s);
    nodeB.insert(p);

    while(!nodeF.empty() && !nodeB.empty()) {
        Node* node1 = nodeF.extractMin();
        Node* node2 = nodeB.extractMin();
        node1->visited = true;
        node2->visited = true;

        if(node1->dist + node2->dist >= bestDist)
            return bestDist;

        //FRONT
        for (Edge* edge : node1->adj) {
            double oldDist = edge->dest->dist;
            if (bestDist > edge->dest->distR + edge->weight + node1->dist && !edge->dest->visited && edge->dest->way == 2) {
                bestDist = edge->dest->distR + edge->weight + node1->dist;
            }
            else {
                edge->dest->way = 1;
                //MiniDijkstraStep
                if (edge->dest->dist > node1->dist + edge->weight) {
                    edge->dest->dist = node1->dist + edge->weight;
                    edge->dest->path = node1;

                    if(oldDist == INF)
                        nodeF.insert(edge->dest);
                    else
                        nodeF.decreaseKey(edge->dest);
                }
            }
        }

        //BACK
        for (Edge* edge : node2->adj) {
            double oldDist = edge->dest->dist;
            if (bestDist > node2->distR + edge->weight + edge->dest->dist && !edge->dest->visited && edge->dest->way == 1) {

                bestDist = node2->distR + edge->weight + edge->dest->dist;
            }
            else {
                edge->dest->way = 2;

                //MiniDijkstraStep
                if (edge->dest->dist > node2->dist + edge->weight) {
                    edge->dest->dist = node2->dist + edge->weight;
                    edge->dest->path = node2;

                    if(oldDist == INF)
                        nodeB.insert(edge->dest);
                    else
                        nodeB.decreaseKey(edge->dest);
                }
            }
        }
    }
    return INF;
}

void Graph::dijkstraMulti() {

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

    for (Node* node : nodeSet) {

        for (Node* n : nodeSet) {
            n->visited = false;
            n->queueIndex = 0;
            n->dist = INF;
            n->path = NULL;
        }

        MutablePriorityQueue<Node> nodeQueue;
        distanceMatrix[node->getIDM()][node->getIDM()] = 0;
        node->dist = 0;
        nodeQueue.insert(node);
        while(!nodeQueue.empty()) {
            Node* node1 = nodeQueue.extractMin();
            node->visited = true;
            for (Edge* edge : node1->adj) {
                if (edge->dest->dist > node1->dist + edge->weight && !edge->dest->visited) {
                    double oldDist = edge->dest->dist;
                    edge->dest->dist = node1->dist + edge->weight;
                    edge->dest->path = node1;
                    distanceMatrix[node->getIDM()][edge->dest->getIDM()] = edge->dest->dist;
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

void Graph::updatePaths(int idM) {
    // Id of the origin node for the paths
    Node* origin = findNodeMatrixId(idM);
    if (origin == nullptr) return;

    for (Node* node : nodeSet) {
        if (node->getIDM() == idM) {
            pathsMatrix[idM][idM] = idM;
            continue;
        }
        Node* node1 = node;
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

void Graph::floydWarshallShortestPath() { //Makes matrix with all paths

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

    for (Node* node : nodeSet) {
        distanceMatrix[node->getIDM()][node->getIDM()] = 0;
        pathsMatrix[node->getIDM()][node->getIDM()] = node->getIDM();
        for (Edge* edge : node->adj) { //Initial fill in
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
}

// Connectivity

void Graph::tarjan() {
    std::stack<Node*> st;

    for (Node* n : nodeSet) {
        n->visited = false;
        n->isInStack = false;
    }

    int numCounter = 0;

    for (Node* n : nodeSet)
        dfsTarjan(n, numCounter, st);
}

int Graph::dfsTarjan(Node *node, int& counter, std::stack<Node*>& st) {
    if (node->visited)
        return node->num;
    node->visited = true;
    node->isInStack = true;
    st.push(node);
    counter++;
    node->low = counter;
    node->num = counter;

    for (Edge* edge : node->adj) {
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

// Clustering

std::vector<std::vector<Node*>> Graph::clustering(std::vector<Node*> nodes, int noSets) {
    std::vector<std::vector<Node*>> clusters;
    for (Node* node : nodes) {
        std::vector<Node*> temp;
        temp.push_back(node);
        clusters.push_back(temp);
    }
    while (clusters.size() > noSets) {
        double bestDist = INF;
        int i1 = 0, j1 = 0;
        for (unsigned int i = 0; i < clusters.size(); i++) {
            for (unsigned int j = i + 1; j < clusters.size(); j++) {
                double possibleDist = getSetDistances(clusters[i], clusters[j]);
                if (bestDist > possibleDist ||
                    (bestDist == possibleDist && clusters[i].size() + clusters[j].size() < clusters[i1].size() + clusters[j1].size())) {
                    bestDist = possibleDist;
                    i1 = i;
                    j1 = j;
                }
            }
        }
        mergeSets(clusters, i1, j1);
    }
    return clusters;
}

double Graph::getSetDistances(std::vector<Node*> v1, std::vector<Node*> v2) {
    double bestDistance = INF;
    for (Node* n1 : v1) {
        for (Node* n2 : v2) {
            double possibleDistance = (distanceMatrix[n1->getIDM()][n2->getIDM()] + distanceMatrix[n2->getIDM()][n1->getIDM()]) / 2;
            if (possibleDistance < bestDistance)
                bestDistance = possibleDistance;
        }
    }
    return bestDistance;
}

void Graph::mergeSets(std::vector<std::vector<Node*>>& clusters, int i, int j) {
    clusters[i].insert(clusters[i].end(), clusters[j].begin(), clusters[j].end());
    clusters.erase(clusters.begin() + j);
}


// UTILS FOR ALGORITHMS

void Graph::eliminateInaccessible(int id) {
    Node* node = findNode(id);
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

void Graph::printMatrixes() {
    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            std::cout << distanceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n\n";

    for (unsigned int i = 0; i < nodeSet.size(); i++) {
        for (unsigned int j = 0; j < nodeSet.size(); j++) {
            std::cout << pathsMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> Graph::getShortestPath(int s, int d) const{ //Calculate the paths
    std::vector<int> res;
    Node* originV = this->findNode(s);
    Node* destV = this->findNode(d);
    if (originV == nullptr || destV == nullptr) return res;

    res.push_back(originV->id);
    int nextI = originV->idM;

    while (destV->idM != nextI) {
        nextI = pathsMatrix[nextI][destV->idM];
        res.push_back(findNodeMatrixId(nextI)->id);
    }

    return res;
}

void Graph::assignIDM() {
    int counter = 0;
    for (Node* node : nodeSet) {
        node->idM = counter;
        counter++;
    }
}

