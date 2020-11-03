//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "fstream"
using json=nlohmann::json;
using namespace std;
Session::Session(const std::string &path) {
    std::ifstream i(path);
    json j;
    i >> j;
    json agent;
    json graph;
    for (int k = 0; k != j["agents"].size(); k++) {
        agent += j["agents"][k];
    }
    for (int k = 0; k != j["graph"].size(); k++) {
        graph += j["graph"][k];
    }
    string treeType = j["tree"];
    if (treeType == "M")
        TreeType::MaxRank;
    else if (treeType == "C")
        TreeType::Cycle;
    else
        TreeType::Root;
    vector<vector<int>>  inputGraph(graph.size());
    for (int n = 0; n < graph.size(); n++){
        for(int m=0;m<graph[n].size();m++) {
            inputGraph[n][m] = graph[n][m];
        }
    }
    g=Graph(inputGraph);
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



