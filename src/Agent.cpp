//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h" // for Session&
#include "../include/Agent.h"
#include "../include/Tree.h"

// simple constructor
Agent::Agent(){}


// Virus simple constructor

void Virus::act(Session& session) {
session.attack(this->nodeInd);
int toInfect=session.findNotInfected(this->nodeInd);

}

Agent* Virus::clone() const {
    return new Virus(*this);
}

Virus::Virus(int nodeInd):nodeInd(nodeInd){}

 //ContactTracer act
void ContactTracer::act(Session& session) {
    int dequed=session.dequeueInfected();
if(dequed!=-1) {
    Tree *actTree = Tree::createTree(session, dequed);
    actTree.BFS();
    int nodeToRemove = actTree->traceTree();
    session.removeEdges(nodeToRemove);
}
}

Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

ContactTracer::ContactTracer(){

}