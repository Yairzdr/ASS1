//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h" // for Session&
#include "../include/Agent.h"

// simple constructor
Agent::Agent(Session& _session):session(_session){}


// Virus simple constructor

// Virus act
void Virus::act() {

}
//clones a virus
Agent* Virus::clone() const {
    Agent* newCloned = new Virus(nodeInd, this->session);
    return newCloned;
}

Virus::Virus(int nodeInd, Session &session):Agent(session),nodeInd(nodeInd){}

// ContactTracer constructor overwrite


// ContactTracer act
void ContactTracer::act() {

}
//clones a virus
Agent *ContactTracer::clone() const{
    Agent* newCloned = new ContactTracer( this->session);
    return newCloned;
}

ContactTracer::ContactTracer(Session &session) : Agent(session) {

}