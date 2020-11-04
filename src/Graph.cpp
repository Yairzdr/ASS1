//
// Created by Yairzdr on 01/11/2020.
//

#include "../include/Graph.h"
//constructor
Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix){
    std::vector<int>infectedNodesList(matrix.size());//initilizing the infectedNodeList (that 'rememmbers' which node was infected during the session) in the size of the matrix.
}
//copy constructor
Graph::Graph(Graph& toCopy) {
    edges=toCopy.edges;
    infectedNodesList=toCopy.infectedNodesList;
    }
// this function infects a node
void Graph::infectNode(int nodeInd) {
    infectedNodesList[nodeInd]=1;
    //MAKE SURE THAT THE FUNCTION THAT CALLS infectNode ADDS INFECTED TO AGENT LIST!
}
// this function checks if the given node is marked as infected in the InfectedList we are keeping.
bool Graph::isInfected(int nodeInd) {
    return(infectedNodesList[nodeInd]==1);
}


