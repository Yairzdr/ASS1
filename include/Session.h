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
    virtual ~Session();//Destructor.
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void attack(int nodeID);//'attacks' the node - changes a node status to SICK (infected) by using enqueInfected.
    int currentCycleNum;//holds the current cycle. will be used on CycleTree treeTrace.
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    void removeEdges(int j);//Calls Graph::removeEdges.
    int findNotInfected(int nodeID);//Calls Graph::FindNotInfected.
    std::vector<int> neighboorsOfNode(int i);//calls Graph:neighboorsOfNode.
    int getSize();//Returns the size of the graph (amount of nodes in the session).
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector<int> infectedQueue;//holds the infected Queue vector("infected list").
};

#endif
