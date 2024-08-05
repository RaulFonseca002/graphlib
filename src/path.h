#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>

using namespace std;

struct pathingNode {
    string name;
    double totalWeight;
    string from;

    pathingNode(string name, double weight) : name(name), totalWeight(weight) {}
};

string dfs(string from, string to);
string bfs(string from, string to);
string dijkstra(string from, string to);



#endif 
