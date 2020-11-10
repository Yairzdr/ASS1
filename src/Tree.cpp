//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Tree.h"
#include "../include/Session.h"
#include <queue>
// simple constructor
Tree::Tree(int rootLabel):node(rootLabel),children(std::vector<Tree*>()) {}//not sure about exact implementation, what should get inside children?

Tree::~Tree()//destructor
{
    clear();
}
//Adds a child to the tree - not used. used a addChild function that gets Tree*.
void Tree::addChild(const Tree &child){
Tree* cloned = child.clone();
children.push_back(cloned);
}

//Creates a new tree according to the session treetype.
Tree *Tree::createTree(const Session &session, int rootLabel) {
TreeType type=session.getTreeType();
Tree* newTree;
if(type==Cycle)
    newTree=new CycleTree(rootLabel,session.currentCycleNum);
else if(type==MaxRank)
    newTree=new MaxRankTree(rootLabel);
else
    newTree=new RootTree(rootLabel);
return newTree;
}
//TreeLabel getter
int Tree::getRootLabel() {
    return node;
}
//children getter
std::vector<Tree *> Tree::getChildren() {
    return children;
}

/*
 * Builds a bfs tree according to the current simulation status.
 */
void Tree::bfsBuild(Session &session)
{
    int curr;
    bool flag=true;
    Tree* copyT=this;
    std::vector<bool>visited(session.getSize());//initialize with false as default
    visited[node]=true;//marking the root so we will not add it to any of his children
    std::queue<Tree*> treeQueue ;
    while(flag||!treeQueue.empty())
    {
        if(!flag)
        {
            copyT=treeQueue.front();
            treeQueue.pop();
        }
        curr=(*copyT).getRootLabel();
        std::vector<int> neighborsVec = session.neighboorsOfNode(curr);//obtain the neighbors of the current node
        for (int i = 0; i < (int)neighborsVec.size(); i++)
        {
            if(!visited[neighborsVec[i]])
            {
                visited[neighborsVec[i]]=true;//mark i as visitd
                Tree* childTree = createTree(session,neighborsVec[i]);
                copyT->addChild(childTree);
                treeQueue.push(childTree);
            }

        }
        flag=false;
    }
}

//this function adds a child to the tree.
void Tree::addChild(Tree *child)
{
    children.push_back(child);
}

//used by Destructor
void Tree::clear()
{
    for (int i=0;i<(int)children.size();i++)
        if (children[i]!= nullptr)
            delete children[i];
}
/*
 * copy assignment operator
 */
Tree &Tree::operator=(const Tree &other) {
    if(this!= nullptr)
        clear();
    this->node=other.node;
    for(int i=0;i<(int)other.children.size();i++)
    {
        this->addChild(other.children[i]->clone());
    }
    return *this;
}
//Move assignment
Tree &Tree::operator=(Tree &&other) {
    if (this!=&other) {
        node=other.node;
        this->clear();
        for(int i=0;i<(int)other.children.size();i++)
        {
            children.push_back(other.children[i]);
            other.children[i]= nullptr;
        }
    }
    return *this;
}
//move constructor
Tree::Tree(Tree &&other):node(other.node),children(other.children.size()){
    for(int i=0;i<(int)other.children.size();i++)
    {
        children.push_back(other.children[i]);
        other.children[i]= nullptr;
    }
}
//Copy Constructor
Tree::Tree(const Tree &other):node(other.node),children(std::vector<Tree*>()) {
    for(int i=0;i<(int)other.children.size();i++)
    {
        children.push_back(other.children[i]->clone());
    }

}


// CycleTree constructor
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel),currCycle(_currCycle){}

//Finds the left most children in depth (currCycle)
int CycleTree::traceTree() {
    int cycleCount=currCycle;//the depth required
    int curr=getRootLabel();//initialize with root
    std::vector<Tree*> child=getChildren();
    while(cycleCount>0&!child.empty())
    {
        curr=child[0]->getRootLabel();//keep the current children label
        child=child[0]->getChildren();//get the children's children array.
        cycleCount--;
    }
        return curr;
}

//clone func
Tree* CycleTree::clone() const
{
    Tree* copy= new CycleTree(this->node,this->currCycle);
    if(!this->children.empty())
        for (int i=0;i< (int)this->children.size();i++)
            copy->addChild(this->children[i]->clone());
    return copy;
}


// MaxRankTree constructor
MaxRankTree::MaxRankTree(int _rootLabel) : Tree(_rootLabel) {}

/*
 * Used by contact tracers-
 */
int MaxRankTree::traceTree() {
int currMaxInd=node;
int currmaxChild=children.size();
std::queue<Tree*> treeQueue;
Tree* checkTree;
std::vector<Tree*> childrens;
treeQueue.push(this);
while(!treeQueue.empty())
{
    checkTree=treeQueue.front();
    treeQueue.pop();
    childrens=checkTree->getChildren();
    int thisRank=childrens.size();
    if(thisRank>currmaxChild)
    {
        currMaxInd=checkTree->getRootLabel();
        currmaxChild=childrens.size();
    }
    for(int i=0;i<(int)childrens.size();i++)
    {
        treeQueue.push(childrens[i]);
    }
}
return currMaxInd;
}

Tree *MaxRankTree::clone() const
{
    Tree* copy= new MaxRankTree(this->node);
    if(!this->children.empty())
        for (int i=0;i<(int)this->children.size();i++)
            copy->addChild(this->children[i]->clone());
    return copy;
}

// RootTree constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

//returns the rootLabel of the tree.
int RootTree::traceTree() {
    return getRootLabel();
}

Tree *RootTree::clone() const
{
    Tree* copy= new RootTree(this->node);
    if(!this->children.empty())
        for (int i=0;i<(int)this->children.size();i++)
            copy->addChild(this->children[i]->clone());
    return copy;
}

