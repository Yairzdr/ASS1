#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    int currentCycleNum;
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    void removeEdges(int j);
    int findNotInfected(int nodeID);
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector<int> infectedQueue;//Will hold the infected Queue vector
};

#endif
