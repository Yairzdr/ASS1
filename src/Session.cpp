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
    // what do we add, how to insert?
}

void Session::setGraph(const Graph &graph) {//Setter
    g = graph;
}

void Session::enqueueInfected(int) {//hmm? where is the infected queue?

}

int Session::dequeueInfected() {//where is the infected queue?
    return 0;
}

// returns the TreeType Cycle/MaxRank/Root
TreeType Session::getTreeType() const{
    return treeType;
}



