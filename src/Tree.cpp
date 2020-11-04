//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Tree.h"
// simple constructor
Tree::Tree(int rootLabel):node(rootLabel),children(std::vector<Tree*>()) {}//not sure about exact implementation, what should get inside children?


// this function adds a child to the tree
void Tree::addChild(const Tree &child) {

}

// ?????????????????? what the fuck is that?
Tree *Tree::createTree(const Session &session, int rootLabel) {
    return nullptr;
}
//TreeLabel getter
int Tree::getRootLabel() {
    return node;
}
//children getter
std::vector<Tree *> Tree::getChildren() {
    return children;
}
// CycleTree constructor
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel),currCycle(_currCycle){}

//Finds the left most children in depth (currCycle)
int CycleTree::traceTree() {
    int cycleCount=currCycle;//the depth required
    int curr=getRootLabel();//initialize with root
    int prev=getRootLabel();//initialize with root
    std::vector<Tree*> child=getChildren();
    while(cycleCount>0&child[0]!= nullptr)
    {
    prev=curr;
    curr=child[0]->getRootLabel();//keep the current children label
    child=child[0]->getChildren();//get the children's children array.

    cycleCount--;
    }
    if(cycleCount==0)//then we did not encountered a nullptr on the children array
        return curr;
    return prev;
}

// MaxRankTree constructor
MaxRankTree::MaxRankTree(int _rootLabel) : Tree(_rootLabel) {}

// this used by the ContactTracer
int MaxRankTree::traceTree() {
    return 0;
}

// RootTree constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

//returns the rootLabel of the tree.
int RootTree::traceTree() {
    return getRootLabel();
}
