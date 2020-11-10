//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Graph.h"


/*
 * Simple constructor, initiates the edges with the edges with the input matrix,
 * and the infected list at the size of the matrix.
 */
Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix), infectedNodesList(matrix.size()){}


/*
 *This function removes the edges that surrounds the given node.
 */
void Graph::removeEdges(int j){
    for(int i=0;i<this->getSize();i++)
    {
        edges[i][j]=0;
        edges[j][i]=0;
    }
}

/*
 *This function returns the amount of nodes in the session
 */
int Graph::getSize()
{
    return edges.size();
}

/*
 * Gets a nodeInd and infects this node (on the infectedNodeList) (1=infected, 0=healty)
 */
void Graph::infectNode(int nodeInd) {
    infectedNodesList[nodeInd]=1;
}

/*
 *This function checks if the given node is marked as infected in the InfectedList we are keeping.
*/
 bool Graph::isInfected(int nodeInd) {
    return(infectedNodesList[nodeInd]!=0);
}

/*
 * //Returns the edge[a][b].
 */
int Graph::getEdge(int a, int b) {
    return edges[a][b];
}

/*
 * Returns a list of available neighbors (those that still have a edge with this node)
 */
std::vector<int> Graph::neighboorsOfNode(int i) {
    std::vector<int> neighboorsVector;
    for(int j=0;j<(int)getSize();j++)
    {
        if (edges[i][j]==1)
            neighboorsVector.push_back(j);
    }
    return neighboorsVector;
}

/*
 * Returns the edges matrix(vector).
 */
std::vector<std::vector<int>> Graph::getEdges(){
    return edges;
}

/*
 * Returns a list(vector) of all nodes infected during the session.
 */
std::vector<int> Graph::getInfected() {
    std::vector<int> result;
    for(int i=0;i<(int)infectedNodesList.size();i++) {
        if (infectedNodesList[i] == 2)
            result.push_back(i);
    }
        return result;
}


