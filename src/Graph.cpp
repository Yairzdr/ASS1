//
// Created by Yairzdr on 01/11/2020.
//

#include "../include/Graph.h"
// simple constructor
Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix){}//make sure that it is deep copy
Graph::Graph():edges() {}
// destructor

// copy constructor

// copy assignment operator

// move constructor

// move assignment operator

void Graph::infectNode(int nodeInd) {
    // this function infects a node
}

bool Graph::isInfected(int nodeInd) {
    // this function checks if the given node is infected
    return false;
}


