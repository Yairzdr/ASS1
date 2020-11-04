//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h" // for Session&
#include "../include/Agent.h"

// simple constructor
Agent::Agent(Session& _session):session(_session){}


// Virus simple constructor

void Virus::act() {

}

Agent* Virus::clone() const {
    return new Virus(*this);
}

Virus::Virus(int nodeInd, Session &session):Agent(session),nodeInd(nodeInd){}

 //ContactTracer act
void ContactTracer::act() {

}

Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

ContactTracer::ContactTracer(Session &session) : Agent(session) {

}