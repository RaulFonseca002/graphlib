#include "graph.h"
#include "utils.cpp"
Graph::Graph() {
    directed = false;
}

Graph::Graph(string str) {
    set(str);
}

Graph::~Graph (){
}

void Graph::setNodes(string str){

    regex pattern(",");
    regex_token_iterator<string::iterator> tokenIterator(str.begin(), str.end(), pattern, -1);
    regex_token_iterator<string::iterator> end;
    string nodeName;   

    while (tokenIterator != end) {
        addNode(tokenIterator->str());
        tokenIterator++;
    }

}

void Graph::setEdges(string str){

    regex pattern("\\{(\\d+),([a-z]),([a-z])\\}");
    smatch matches;

    while (regex_search(str, matches, pattern)) {

        if(nodes.exists(matches[2]) && nodes.exists(matches[3]) && isNumeric(matches[1])){
            addEdge(matches[2], matches[3], stod(matches[1]));

            if(!directed){
                addEdge(matches[3], matches[2], stod(matches[1]));
            }
        }



        str = matches.suffix();
    }

}

void Graph::set(string str){

    regex pattern("/");

    regex_token_iterator<string::iterator> iterator(str.begin(), str.end(), pattern, -1);
    regex_token_iterator<string::iterator> end;

    directed = (iterator->str().compare("d") == 0) ;

    iterator++;
    setNodes(iterator->str());
    iterator++;
    setEdges(iterator->str());
}

void Graph::addEdge(string from, string to, double weight){
    edges.add(from, to, weight);
    nodes.addDegree(from,0 ,1);
    nodes.addDegree(to, 1, 0);
}

void Graph::addNode(string nodeName){
    nodes.add(nodeName);

}

void Graph::removeEdge(string from, string to){

    if(!nodes.exists(from) || !edges.existEdge(from, to)) return;
    if(!directed) edges.removeEdge(to, from);

    edges.removeEdge(from, to);
    nodes.addDegree(from, 0, -1);
    nodes.addDegree(from, -1, 0);

}

void Graph::removeNode(string nodeName){

    for(node_t n : nodes.getNodesVector()){
        removeEdge(n.name, nodeName);
    }

    nodes.remove(nodeName);
    edges.removeNode(nodeName);
}

void Graph::print(){
    nodes.print();
    edges.print();
}

void Graph::setNode(node_t node){
    nodes.setNode(node);
}

node_t Graph::getNode(string nodeName){
    return nodes.getNode(nodeName);
}

string Graph::getPath(string from, string to){

    string resp = to + ">-";
    string cameFrom = getNode(to).cameFrom;
    
    while (cameFrom.compare(from) != 0)
    {
        resp += cameFrom + ">-";
        cameFrom = getNode(cameFrom).cameFrom;

    }

    resp += from;
    reverseStr(resp);
    return resp;

}
