#include "Nodes.h"

Nodes::Nodes() {
}

Nodes::~Nodes() {
}

node_t Nodes::getNode(string name) {
    return nodes[name];
}

node_t* Nodes::getNodePtr(string name){
    return &nodes[name];
}

void Nodes::add(string name){

    if(!exists(name)){
        nodes.insert({name, node_t(name)});
    }
    
}

bool Nodes::exists(string name){
    return (nodes.find(name) != nodes.end());
}

void Nodes::remove(string nodeName){
    nodes.erase(nodeName);
}

void Nodes::print(){

    for(auto x : nodes){
        printf("node: %s reach time: %i exit time: %i\n", x.first.c_str(), x.second.reachTime, x.second.exitTime);
    }
}

void Nodes::addDegree(string nodeName, int inDegree, int outDegree){
    if(exists(nodeName)){
        nodes[nodeName].inDegree += inDegree;
        nodes[nodeName].outDegree += outDegree;
    }
}

vector<node_t> Nodes::getNodesVector (){

    vector<node_t> resp;

    for(auto it : nodes){
        resp.push_back(it.second);
    }

    return resp;
}

void Nodes::setNode(node_t node){
    nodes[node.name] = node;
}

vector<node_t> Nodes::getBase(){

    vector<node_t> resp;

    for(auto it : nodes){
        if(it.second.inDegree == 0) resp.push_back(it.second);
    }

    return resp;
}