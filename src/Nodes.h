#ifndef NODES_H
#define NODES_H

#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

struct node_t {
    string name;
    int inDegree, outDegree;
    int reachTime, exitTime;
    double weight;
    string cameFrom;
    set<string> reachSet;

    node_t() : name(""), inDegree(0), outDegree(0), weight(0), reachTime(0), exitTime(0), cameFrom("") {}

    node_t(string name) : name(name), inDegree(0), outDegree(0), weight(0), reachTime(0), exitTime(0), cameFrom("") {
        reachSet.insert(name);
    }
};

class Nodes {

    private:
        map<string, node_t> nodes;

    public:
        Nodes();
        ~Nodes();
        void print();
        node_t getNode(string name);
        node_t* getNodePtr(string name);
        void add(string name);
        bool exists(string name);
        void remove(string nodeName);
        void addDegree(string nodeName, int inDegree, int outDegree);
        vector<node_t> getNodesVector ();
        void setNode(node_t node);
        vector<node_t> getBase();
        set<string> getReachSet(string nodeName);
        string toString(node_t node);
        void addSet(string from, string str);
        vector<node_t> getUnreached();
};


#endif