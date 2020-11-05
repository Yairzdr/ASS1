//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "fstream"
#include "../include/Agent.h"

using json=nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g(std::vector<std::vector<int>>()), agents(), currentCycleNum(0) {
    std::ifstream i(path);
    json j;
    i >> j;
    string treeType = j["tree"];
    if (treeType == "M")
        TreeType::MaxRank;
    else if (treeType == "C")
        TreeType::Cycle;
    else
        TreeType::Root;
    g=Graph(j["Graph"]);
    for(int i =0;i<j["agents"].size();++i)
    {
        Agent* newAgent;
        if(j["agents"][i][0]="v") {
            newAgent = new Virus((int) j["agents"][i][1]);
            g.infectNode(j["agents"][i][1]);
        }
        else
            newAgent = new ContactTracer();
        agents.push_back(newAgent);
    }

}
// this function triggers the session
void Session::simulate() {
    bool terminated=false, first=true;

    while(!terminated)
    {
        int listSize=agents.size();
        for(int i=0;i<listSize;i++)
        {
            agents[i]->act(*this);
        }

        terminated=(listSize==agents.size());
        //
        currentCycleNum++;
    }
    //json output.
}

//removes the edges of J on the graph.
void Session::removeEdges(int j)
{
g.removeEdges(j);
}
// this function adds an agent
void Session::addAgent(const Agent &agent) {
    Agent* cloned = agent.clone();
    agents.push_back(cloned);
}

void Session::setGraph(const Graph &graph) {//Setter
    g = graph;
}

int Session::findNotInfected(int nodeID) {
    for (int i = 0; i < g.getSize(); i++)
    {
        if(g.getEdge(nodeID,i)==1&!g.isInfected(i))
        {
            g.infectNode(i);
            Agent* newAgent=new Virus(nodeID);
            agents.push_back(newAgent);
            return i;
        }
    }
    return -1;
}

//pushing the given node index to the end of the infected queue vector.
void Session::enqueueInfected(int nodeInd) {
infectedQueue.push_back(nodeInd);
g.infectedNodesList[nodeInd]=2;
}
//poping the first node in the queue and removing it.
int Session::dequeueInfected() {
    if(infectedQueue.empty())
    return -1;
        int pop = infectedQueue[0];
        infectedQueue.erase(infectedQueue.begin());//removes the first element.
        return pop;
}

// returns the TreeType Cycle/MaxRank/Root
TreeType Session::getTreeType() const{
    return treeType;
}

void Session::attack(int nodeID) {
    if(g.infectedNodesList[nodeID]==1)
    {
        enqueueInfected(nodeID);
    }
}



