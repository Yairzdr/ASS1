#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    //Tree(const Tree &other);
    void addChild(const Tree& child) ;
    void addChild( Tree* child) ;
    int getRootLabel();
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
private:
    int currCycle;
};


class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    void addChild( Tree* child) ;
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    void addChild(Tree* child) ;
    virtual int traceTree();
};

#endif
