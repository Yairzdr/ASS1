//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "fstream"
#include "../include/Agent.h"

using json=nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g(std::vector<std::vector<int>>()), agents() {
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
        if(j["agents"][i][0]="v")
            newAgent = new Virus((int)j["agents"][i][1], *this);
        else
            newAgent = new ContactTracer(*this);
        agents.push_back(newAgent);
    }

}
// this function triggers the session
void Session::simulate() {

}

// this function adds an agent
void Session::addAgent(const Agent &agent) {
}

void Session::setGraph(const Graph &graph) {//Setter
    g = graph;
}
//pushing the given node index to the end of the infected queue vector.
void Session::enqueueInfected(int nodeInd) {
infectedQueue.push_back(nodeInd);
}
//poping the first node in the queue and removing it.
int Session::dequeueInfected() {
    int pop = infectedQueue[0];
    infectedQueue.erase(infectedQueue.begin());//removes the first element.
    return pop;
}

// returns the TreeType Cycle/MaxRank/Root
TreeType Session::getTreeType() const{
    return treeType;
}



