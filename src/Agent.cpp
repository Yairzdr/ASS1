//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Session.h" // for Session&
#include "../include/Agent.h"

// simple constructor
Agent::Agent(Session& _session):session(_session){}

// destructor

// copy constructor

// copy assignment operator

// move constructor

// move assignment operator

// Virus simple constructor

// Virus act
void Virus::act() {

}

// ContactTracer constructor overwrite
ContactTracer::ContactTracer(Session &session) : Agent(session) {}

// ContactTracer act
void ContactTracer::act() {

}
