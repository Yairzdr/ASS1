#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"//was added by Yair

class Agent{
public:
    Agent();
    virtual Agent* clone() const=0;
    
    virtual void act(Session& session)=0;

protected:

};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone() const;
    
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone() const;
    
    virtual void act(Session& session);
private:
    const int nodeInd;
};

#endif
