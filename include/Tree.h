#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& other);//copy constructor
    virtual Tree* clone()const=0 ;//clone func
    virtual ~Tree();//destructor
    Tree & operator=(const Tree& other);//copy assignment operator
    void addChild(const Tree& child) ;//Adds a child to the tree - not used.
    void addChild(Tree* child) ;//Adds a child to the tree
    int getRootLabel();//RootLabler getter
    void bfsBuild(Session& session);//builds a bfs tree according to the current simulation status.
    std::vector<Tree*> getChildren();//returns the children vector
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    Tree& operator = (Tree &&other);//move assignment
    Tree(Tree &&other);//copy assignment
protected:
    int node;
    std::vector<Tree*> children;
    void clear();
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;//clone func
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;//clone func
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;//clone func
};

#endif
