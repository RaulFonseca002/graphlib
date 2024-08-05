#ifndef EDGES_H
#define EDGES_H

#include <string>
#include <map>
#include <vector>

using namespace std;


struct edge_t
{
    float weight;
    string tag;
    edge_t() : weight(0.0) {}

    edge_t (float weight) : weight(weight) {}
};

class Edges {
    private:
        map<string, map<string, edge_t>> edges;

    public:
        Edges();
        ~Edges();
        void add(string from, string to, double weight);
        void print();
        bool existNode(string nodeName);
        bool existEdge(string from, string to);
        void removeNode(string name);
        void removeEdge(string from, string to);
        map<string, edge_t> getEdges(string node);
        edge_t* getEdgePtr(string from, string to);
};

#endif
