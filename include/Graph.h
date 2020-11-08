#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(Graph& toCopy);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    int getSize();
    int getEdge(int a, int b);
    void removeEdges(int i);
    std::vector<std::vector<int>> getEdges();
    std::vector<int> getInfected();
    std::vector<int> infectedNodesList;//Will keep the infectedNodes(not the queue!)
    std::vector<int> neighboorsOfNode(int i);
private:
    std::vector<std::vector<int>> edges;

};

#endif
