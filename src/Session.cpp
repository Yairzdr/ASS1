//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "fstream"
#include "../include/Agent.h"

using json=nlohmann::json;
using namespace std;

/*
 * Session constructor.
 *reads the input json file, and initialize the TreeType, AgentList and the Graph edges.
 */
Session::Session(const std::string &path):g(std::vector<std::vector<int>>()), agents(), currentCycleNum(0) {
    std::ifstream i(path);
    json j;
    i >> j;
    string Ttype =(string)j["tree"];//Reads the input for the treetype from the json file
    if (Ttype == "M")
        treeType=MaxRank;
    else if (Ttype == "C")
        treeType=Cycle;
    else
        treeType=Root;
    g=Graph(j["graph"]);
    for(int i =0;i<(int)j["agents"].size();++i)
    {
        Agent* newAgent;
        if(j["agents"][i][0]=="V") {
            newAgent = new Virus((int) j["agents"][i][1]);
            g.infectNode(j["agents"][i][1]);//Create a new virus on node i
        }
        else
            newAgent = new ContactTracer();
        agents.push_back(newAgent);
    }
}

/*
 * Triggers the session, runs the cycles loop and terminates when the conditions are satisfied.
*/
 void Session::simulate()
{
    bool terminated=false;
    while(!terminated)//The conditions are not satesfied yet
    {
        int listSize=(int)agents.size();
        for(int i=0;i<listSize;i++)
            agents[i]->act(*this);
        terminated=(listSize==(int)agents.size());//If the agents vector did not grew up during the cycle, the termination conditions are satisfied.
        currentCycleNum++;
    }
    //Creating the output json file.
    json output;
    output["graph"]=g.getEdges();
    output["infected"]=g.getInfected();
    std::ofstream file("./output.json");
    file << output;
}

/*
 * Removes the edges of J on the graph.
 */
void Session::removeEdges(int j)
{
g.removeEdges(j);
}

void Session::addAgent(const Agent &agent) {
    Agent* cloned = agent.clone();
    agents.push_back(cloned);
}

void Session::setGraph(const Graph &graph) {//Setter
    g = graph;
}

/*
 * Finds the next available node to infect (that is not infected yet, and connected to the node the virus occupies)
 * Creates a new Virus on the found node, and adds it to the Agent list.
 */
int Session::findNotInfected(int nodeID) {
    for (int i = 0; i <(int)g.getSize(); i++)
        if(g.getEdge(nodeID,i)==1&&!g.isInfected(i))
        {
            g.infectNode(i);
            Agent* newAgent=new Virus(i);
            agents.push_back(newAgent);
            return i;
        }
    return -1;
}

/*
 *Pushing the given node index to the end of the infected queue vector, and changing it's value on InfectedNodeList to 2 (that represents a node that is SICK and not only infected(1).
 */
void Session::enqueueInfected(int nodeInd) {
infectedQueue.push_back(nodeInd);
g.infectedNodesList[nodeInd]=2;//=2 means that a node is SICK (red according to the logic on the instructions).
}

/*
 * Poping the first node in the queue and removing it (if there is one).
 */
int Session::dequeueInfected() {
    if(infectedQueue.empty())
        return -1;
    int pop = infectedQueue[0];
    infectedQueue.erase(infectedQueue.begin());//removes the first element.
    return pop;
}

/*
 * Returns the TreeType Cycle/MaxRank/Root
 */
TreeType Session::getTreeType() const{
    return treeType;
}

/*
 * //'attacks' the node - changes a node status to SICK (infected) by using enqueInfected.
 */
void Session::attack(int nodeID) {
    if(g.infectedNodesList[nodeID]==1)//=1 means that the node is Infected but not SICK yet. (so it should get SICK now, and inserted to the infected queue).
        enqueueInfected(nodeID);
}

/*
 * Calls Graph::neighboorsOfNode which returns a list of all nodes that still has an edge with the given node.
 */
std::vector<int> Session::neighboorsOfNode(int i) {
    return g.neighboorsOfNode(i);
}

/*
 * //Returns the size of the graph (amount of nodes in the session).
 */
int Session::getSize() {
    return g.getSize();
}

/*
 * Destructor. deletes all the agents from the agents list
 */
Session::~Session()
{
    Agent* agentToRemove;
   while(!agents.empty())
   {
       agentToRemove = agents.front();
       agents.erase(agents.begin());
       delete agentToRemove;
   }
}
//Move constructor
Session::Session(Session &&other):g(other.g), treeType(other.treeType), infectedQueue(other.infectedQueue) {
for(int i=0;i<(int)other.agents.size();i++)
{
    agents.push_back(other.agents[i]);
    other.agents[i]= nullptr;
}
}

//Move Assignment
Session &Session::operator=(Session &&other) {
    if (this!=&other){
        this->clear();
        g=other.g;
        treeType=other.treeType;
        infectedQueue=other.infectedQueue;
        for(int i=0;i<(int)other.agents.size();i++)
        {
            agents.push_back(other.agents[i]);
            other.agents[i]= nullptr;
        }
    }
}
//clear func (delete agent list)
void Session::clear() {
    for(int i=0;i<(int)agents.size();i++)
    {
        delete(agents[i]);
        agents.clear();
    }
}
//Copy Constructor
Session::Session(const Session &other): treeType(other.treeType), infectedQueue(other.infectedQueue), g(other.g) {
    for(int i=0;i<(int)other.agents.size();i++)
    {
        agents.push_back(other.agents[i]->clone());
    }
}

//Copy Assignment
Session &Session::operator=(const Session &other) {
    if (this!=&other){
        this->clear();
        g=other.g;
        treeType=other.treeType;
        infectedQueue=other.infectedQueue;
        for(int i=0;i<(int)other.agents.size();i++)
        {
            agents.push_back(other.agents[i]->clone());
        }
    }
    return *this;
}


