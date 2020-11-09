#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& other);
    virtual Tree* clone()const=0 ;
    virtual ~Tree();
    void addChild(const Tree& child) ;
    void addChild(Tree* child) ;
    int getRootLabel();
    Tree* bfsBuild(Session& session);
    std::vector<Tree*> getChildren();


    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

protected:
    int node;
    std::vector<Tree*> children;
    void clear();

};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};


class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
