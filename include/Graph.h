#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);//Gets a nodeInd and infects this node (on the infectedNodeList)
    bool isInfected(int nodeInd);//Checks if a given node is infected already.
    int getSize();//returns the amount of nodes that in session.
    int getEdge(int a, int b);//returns the edge[a][b].
    void removeEdges(int i);//removes the edges that surrounds node I.
    std::vector<std::vector<int>> getEdges();//returns the Edges vector.
    std::vector<int> getInfected();//returns a vector that has the list of all infected nodes during the session
    std::vector<int> getinfectedNodesList();//getter for infectedNodesList.
    void setinfectedNodesList(int i, int j);//changes the status of node i to j.
    std::vector<int> neighboorsOfNode(int i);//returns a list of available neighbors (those that still have a edge with this node)
private:
    std::vector<int> infectedNodesList;//Will keep the infectedNodes(not the queue!)
    std::vector<std::vector<int>> edges;
};
#endif
