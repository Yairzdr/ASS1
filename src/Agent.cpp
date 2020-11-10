//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h"
#include "../include/Agent.h"
#include "../include/Tree.h"

//Simple constructor
Agent::Agent(){}


Agent::~Agent() {}

//Constructor.
Virus::Virus(int nodeInd):nodeInd(nodeInd){}

/*
 * 'act' uses 2 functions. The first one - attack, makes sure that the node that the virus is on gets sick when it should,
 * The second function - findNotInfected locates the next node to infect, and infects it (creates a new virus on it).
 */
void Virus::act(Session& session)
{
session.attack(this->nodeInd);//attack changes the node status to sick (if it is already infected).
session.findNotInfected(this->nodeInd);//findNotInfected returns the next available node for the virus to spread on, and infects it.
}

/*
 * Clones (this) agent and returns a copy.
 */
Agent* Virus::clone() const {
    return new Virus(*this);
}

//Constructor
ContactTracer::ContactTracer(){}

/*
 * 'act' tries to deque an infected node from the queue. If there is an infected node,
 * it creates a bfs tree (actTree), and using traceTree to remove the node's edges.
 */
void ContactTracer::act(Session& session)
{
    int dequed=session.dequeueInfected();
    if(dequed!=-1)
    {
        Tree* actTree = Tree::createTree(session, dequed);
        actTree->bfsBuild(session);//the creation of the bfs tree on actTree
        int nodeToRemove = actTree->traceTree();
        session.removeEdges(nodeToRemove);//removeEdges isolates the node from the graph.
        delete(actTree);
    }
}

/*
 * Clones (this) agent and returns a copy.
 */
Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

