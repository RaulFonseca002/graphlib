#include "graph.h"

int main(int argc, char const *argv[])
{
    Graph graph;
    string inputString;
    fstream inputFile("input.txt");

    while (getline(inputFile, inputString)) {
        graph.set(inputString);
    }

    graph.tagEdges();
    graph.print();
    return 0;
}