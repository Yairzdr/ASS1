//
// Created by Yairzdr on 01/11/2020.
//
#include "../include/Tree.h"
// simple constructor
Tree::Tree(int rootLabel):node(rootLabel),children() {}//not sure about exact implementation, what should get inside children?
// destructor

// copy constructor

// copy assignment operator

// move constructor

// move assignment operator

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

// CycleTree simple constructor
CycleTree::CycleTree(int _rootLabel, int _currCycle) : Tree(_rootLabel),currCycle(_currCycle){}

// this used by the ContactTracer
int CycleTree::traceTree() {
    int curr=currCycle;
    std::vector<Tree*> child=getChildren();
    while(curr>0&child[0]!= nullptr)
    {

    }
    return 0;
}

// MaxRankTree simple constructor
MaxRankTree::MaxRankTree(int _rootLabel) : Tree(_rootLabel) {}

// this used by the ContactTracer
int MaxRankTree::traceTree() {
    return 0;
}

// RootTree simple constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

// this used by the ContactTracer
int RootTree::traceTree() {
    return getRootLabel();
}
