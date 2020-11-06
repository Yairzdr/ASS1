#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    virtual Tree* clone()=0;
    void addChild(const Tree& child) ;
    void addChild( Tree* child) ;
    int getRootLabel();
    Tree* bfsBuild(Session& session);
    std::vector<Tree*> getChildren();


    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    void addChild(Tree* child) ;
    virtual int traceTree();
    virtual Tree* clone();
private:
    int currCycle;
};


class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    void addChild( Tree* child) ;
    virtual int traceTree();

    virtual Tree* clone();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    void addChild(Tree* child) ;
    virtual int traceTree();
    virtual Tree* clone();
};

#endif
