#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <fstream>
#include <regex>
#include <cmath>
#include <set>
#include "Nodes.h"
#include "Edges.h"

using namespace std;

class Graph {


    private:
        Nodes nodes;
        Edges edges;
        bool directed;

        void setNodes(string str);
        void setEdges(string str);
        string getPath(string from, string to);

        string dfsTag(node_t* node);


    public:
    
        Graph();
        Graph(string str);
        ~Graph();
        void set(string str);
        void print();
        void addEdge(string from, string to, double weight);
        void addNode(string nodeName);
        void removeNode(string nodeName);
        void removeEdge(string from, string to);
        void setNode(node_t node);
        node_t getNode(string nodeName);
        void tagEdges();
        // path
        string bfs(string from, string to);
        string dijkstra(string from, string to);
        string dfsTag(string from);

};


#endif 