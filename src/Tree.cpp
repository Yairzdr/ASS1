//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Tree.h"
#include "../include/Session.h"
#include <queue>
// simple constructor
Tree::Tree(int rootLabel):node(rootLabel),children(std::vector<Tree*>()) {}//not sure about exact implementation, what should get inside children?
//Tree::~Tree()//destructor
//{
//    std::queue<Tree*> treeQ;
//    Tree* copyT=this;
//    treeQ.push(copyT);
//    while(!treeQ.empty())
//    {
//        copyT=treeQ.front();
//        treeQ.pop();
//        //if(copyT->children.size()>0)
//        if(!copyT->children.empty())
//        {
//            for (int i=0;i< copyT->children.size();i++)
//                if (!copyT->children[i]->children.empty())
//                    treeQ.push(copyT->children[0]);
//            while(!copyT->children.empty())
//            {
//                Tree *head = copyT->children.front();
//                copyT->children.erase(copyT->children.begin());
//                delete head;
//            }
//        }
//    }
//}
Tree::~Tree()//destructor
{
    for (int i=0;i<children.size();i++){
        if (children[i]!= nullptr){
            delete children[i];
            //children[i]= nullptr;
        }
    }
}
// this function adds a child to the tree
void Tree::addChild(const Tree &child){
//    Tree* child_ptr= child.clone();
//   children.push_back(child_ptr);
//   delete child_ptr;
}
//Creates a new tree according to the session type.
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

Tree *Tree::bfsBuild(Session &session)
{
    int curr;
    bool flag=true;
    Tree* copyT=this;
    std::vector<bool>visited(session.getSize());//initialize with false as default
    visited[node]=true;
    std::queue<Tree*> treeQueue ;
    while(flag||!treeQueue.empty())
    {
        if(!flag)
        {
            copyT=treeQueue.front();
            treeQueue.pop();
        }
        curr=(*copyT).getRootLabel();
        std::vector<int> neighborsVec = session.neighboorsOfNode(curr);
        for (int i = 0; i < neighborsVec.size(); i++)
        {
            if(!visited[neighborsVec[i]])
            {
                visited[neighborsVec[i]]=true;
                Tree* childTree = createTree(session,neighborsVec[i]);
                copyT->addChild(childTree);
                treeQueue.push(childTree);
//                delete(childTree);
            }

        }
        flag=false;
    }
}

void Tree::addChild(Tree *child)
{
    children.push_back(child);
}


//Tree::Tree(const Tree &other):node(other.node) {
//}

// CycleTree constructor
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel),currCycle(_currCycle){}

//Finds the left most children in depth (currCycle)
int CycleTree::traceTree() {
    int cycleCount=currCycle;//the depth required
    int curr=getRootLabel();//initialize with root
    int prev=getRootLabel();//initialize with root
    std::vector<Tree*> child=getChildren();
//    while(cycleCount>0&child[0]!= nullptr)
    while(cycleCount>0&!child.empty())
    {
    prev=curr;
    curr=child[0]->getRootLabel();//keep the current children label
    child=child[0]->getChildren();//get the children's children array.

    cycleCount--;
    }
//    if(cycleCount==0)//then we did not encountered a nullptr on the children array
        return curr;
 //   return prev;
}

// MaxRankTree constructor
MaxRankTree::MaxRankTree(int _rootLabel) : Tree(_rootLabel) {}

// this used by the ContactTracer
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
    for(int i=0;i<childrens.size();i++)
    {
        treeQueue.push(childrens[i]);
    }
}
//delete checkTree;
return currMaxInd;
}

// RootTree constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

//returns the rootLabel of the tree.
int RootTree::traceTree() {
    return getRootLabel();
}

