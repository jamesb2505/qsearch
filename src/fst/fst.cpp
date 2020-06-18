#include "fst/fst.hpp"


fst::FST::FST() {
    this->edgeMap = new folly::AtomicHashMap<char, fst::Edge *>(ALPHABET_SIZE);
}


fst::FST::~FST() {
    

    // Breadth first search to delete all edges;


    // Kepp track of all edges to delete
    std::vector<fst::Edge *> toDelete;

    // queue for breadth first search
    std::queue<folly::AtomicHashMap<char, fst::Edge *> *> queue;


    // initialise first level for breadth first search
    for (auto& x : *(this->edgeMap)) {
        folly::AtomicHashMap<char, fst::Edge *> *edgeMap = x.second->getEdgeMap();
        queue.push(edgeMap);
        fst::Edge *edge = (x.second);     
        toDelete.push_back(edge);
    }

    while(queue.size() > 0) {
        folly::AtomicHashMap<char, fst::Edge *> *edgeMap = queue.front();
        queue.pop();
        for (auto& x : *edgeMap) {
            folly::AtomicHashMap<char, fst::Edge *> *edgeMap = x.second->getEdgeMap();
            queue.push(edgeMap);
            fst::Edge *edge = (x.second);     
            toDelete.push_back(edge);
        }
    }

    for(auto edge: toDelete) {
        delete edge;
    }

    delete this->edgeMap;
}


bool fst::FST::addWord(std::string id, double score, std::string word) {
    folly::AtomicHashMap<char, fst::Edge *> *edgeMap = this->edgeMap;
    for(std::string::size_type i = 0; i < word.size(); i++) {
        bool finalNode = (i == word.size()-1);
        fst::Edge *currentEdge = nullptr;
        fst::Node *currentNode = nullptr;
        if(edgeMap->find(word[i]) == edgeMap->end()) {
            currentNode = new fst::Node(finalNode, word[i]);
            fst::Edge *edge = new fst::Edge(currentNode);
            currentEdge = edge;
            edgeMap->insert(std::make_pair(word[i], edge));
        }else {
            currentEdge = edgeMap->find(word[i])->second;
            currentNode = currentEdge->to;
        }
        currentNode->insert(id, score);
        edgeMap = currentEdge->getEdgeMap();
    }
    return true;
}