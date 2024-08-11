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
        printf("%s\n", toString(x.second).c_str());
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

string setToString(set<string> strSet){ //this should be in the ultils file

    string resp = "";
    
    for(auto it : strSet){
        resp += " " + it;
    }

    return resp;
}

set<string> Nodes::getReachSet(string nodeName){
    return getNode(nodeName).reachSet;
}

string Nodes::toString(node_t node){ 

    string resp = "";

    resp += "node name: " + node.name + " ";
    resp += "reach set: " + setToString(getReachSet(node.name));

    return resp;
}

void Nodes::addSet(string from, string to){
    set<string> setTo = getNode(to).reachSet;
    getNodePtr(from)->reachSet.insert(setTo.begin(), setTo.end());
}

vector<node_t> Nodes::getUnreached(){
    
    vector<node_t> resp;

    for(auto it : nodes){
        if (it.second.cameFrom == "") resp.push_back(it.second);
    }

    return resp;
}